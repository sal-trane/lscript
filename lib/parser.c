#include "parser.h"
#include "progheap.h"
#include "util.h"
#include "errors.h"

#define FIRST(s) ((*s)[0])
#define CONSUME(c) \
    if (FIRST(streamptr) != c) {\
        LSERR = EUNEXPECTEDTOKEN; \
        return LS_NULL; \
    } \
    (*streamptr)++

/*
 * Helper functions
 */
bool is_whitespace(char c)
{
    int i;
    for (i = 0; LS_ALLOWED_WHITESPACE_CHARS[i] != '\0'; i++)
    {
        if (c == LS_ALLOWED_WHITESPACE_CHARS[i])
        {
            return true;
        }
    }
    return false;
}

const char* skip_whitespace(const char* stream)
{
    while(is_whitespace(stream[0]))
    {
        stream++;
    }

    return stream;
}

/*
 * Parse expressions.
 */
LSData parse_expr(const char** streamptr)
{
    LSData result;
    *streamptr = skip_whitespace(*streamptr);
    
    result.type = LS_FUNC_T;
    *streamptr = sym_copy(*streamptr, result.sym);
    return result;
}

/*
 * Parse lists
 */
LSData parse_list(const char** streamptr)
{
    LSData result;
    CONSUME('(');
    result.type = LS_LIST_T;
    return result;
}

/*
 * Parse character literals.
 */
LSData parse_char(const char** streamptr)
{
    LSData result;
    result.type = LS_CHAR_T;
    result.cval = FIRST(streamptr);
    *streamptr += 1;
    CONSUME('\'');
    return result;
}

/*
 * Parse boolean literals.
 */
LSData parse_bool(const char** streamptr)
{
    char tok = FIRST(streamptr);
    LSData result;

    if (tok == 't')
    {
        result.bval = true;
    }
    else if (tok == 'f')
    {
        result.bval = false;
    }
    else
    {
        LSERR = EUNEXPECTEDTOKEN;
        return LS_NULL;
    }
    result.type = LS_BOOL_T;
    *streamptr += 1;
    return result;
}

/*
 * Parse numeric literals.
 */
LSData parse_number(const char** streamptr)
{
    LSData result;
    int place = 10, sign = 1;

    result.type = LS_INT_T;
    result.ival = 0;
    if (FIRST(streamptr) == '-')
    {
        sign = -1;
        *streamptr += 1;
    }
    else if (FIRST(streamptr) == '+')
    {
        *streamptr += 1;
    }

    while (FIRST(streamptr) >= '0' && FIRST(streamptr) <= '9')
    {
        result.ival *= 10;
        result.ival += (FIRST(streamptr) - '0');
        *streamptr += 1;
    }

    if (FIRST(streamptr) == '.')
    {
        result.type = LS_FLOAT_T;
        result.fval = (float)result.ival;
        *streamptr += 1;
        while (FIRST(streamptr) >= '0' && FIRST(streamptr) <= '9')
        {
            result.fval += (FIRST(streamptr) - '0') / (float)place;
            place *= 10;
            *streamptr += 1;
        }
        result.fval *= sign;
    }
    else
    {
        result.ival *= sign;
    }
    
    return result;
}

/*
 * Parse symbol.
 */
LSData parse_symbol(const char** streamptr)
{
    LSData result;
    if (FIRST(streamptr) == '\0')
    {
        LSERR = EUNEXPECTEDEOF;
        return LS_NULL;
    }
    result.type = LS_SYMBOL_T;
    *streamptr = sym_copy(*streamptr, result.sym);

    return result;
}

LSData parse_next_obj(const char** streamptr)
{
    LSData result;
    *streamptr = skip_whitespace(*streamptr);
    switch (FIRST(streamptr))
    {
        case '(':
            // Expression
            *streamptr += 1;
            result = parse_expr(streamptr);
            break;
        case '`':
            // List
            *streamptr += 1;
            // Return early to skip whitespace check
            return parse_list(streamptr);
        case '\'':
            *streamptr += 1;
            result = parse_char(streamptr);
            break;
        case '#':
            *streamptr += 1;
            result = parse_bool(streamptr);
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '-':
        case '+':
        case '.':
            result = parse_number(streamptr);
            break;
        default:
            result = parse_symbol(streamptr);
    }

    // Check next char is whitespace, ')', or EOF
    if (!(is_whitespace(FIRST(streamptr))
            || FIRST(streamptr) == '\0'
            || FIRST(streamptr) == ')'))
    {
        LSERR = EUNEXPECTEDTOKEN;
        return LS_NULL;
    }
    LSERR = NOERR;
    return result;
}

/*
 * Parses a l-script program in one pass.
 */
bool parse_program_body(const char** streamptr)
{
    int parent = 0, left = 0, stackptr = 0;
    LSData next = parse_next_obj(streamptr);
    int nodeStack[LS_HEAP_DEPTH];
    
    // This acts as a sentinal to see if we went past the root
    nodeStack[0] = -1;

    do
    {
        if (LS_IS_NULL(next))
        {
            return false;
        }

        // Throw next element left
        left = insert_left(parent, next);
        if (left == -1)
        {
            return false;
        }

        // Check if we're at the end of one or more lists
        *streamptr = skip_whitespace(*streamptr);
        if (FIRST(streamptr) == ')')
        {
            while (FIRST(streamptr) == ')')
            {
                if (insert_right(parent, LS_NULL) == -1)
                {
                    return false;
                }
                *streamptr += 1;

                // Move up a level in the tree
                parent = nodeStack[stackptr--];
                if (parent > 0)
                {
                    //Move to unfinished right branch
                    next.type = LS_LIST_T;
                    parent = insert_right(parent, next);
                    *streamptr = skip_whitespace(*streamptr);
                }
            }
        }
        else
        {
            // Move to a branch
            if (next.type & LS_ATOMIC_T)
            {
                // The item on the left is an atom, move to the right
                next.type = LS_LIST_T;
                parent = insert_right(parent, next);
                if (parent == -1)
                {
                    return false;
                }
            }
            else
            {
                // Move down left branch, mark right to come back to
                nodeStack[++stackptr] = parent;
                parent = left;
            }
        }

        // Grab the next element and throw it to the left
        next = parse_next_obj(streamptr);
    } while(FIRST(streamptr) != '\0');
    return true;
}
 

/*
 * Public funtions
 */
bool parse_lscript(const char* stream)
{
    LSData root = parse_next_obj(&stream);
    if (!LS_IS_NULL(root))
    {
        set_program_root(root);
    }
    else
    {
        // LSERR is set from callee
        return false;
    }

    if (root.type & LS_ATOMIC_T)
    {
        // If we have an atom as the program, it's now done
        return true;
    }
    return parse_program_body(&stream);
}
