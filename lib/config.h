/*
 * config.h
 *
 * Defines preprocessor directives that control how the L-Script
 * engine is built.
 */

/*
 * Define the maximum number of characters for a symbol.
 */
#ifndef LS_MAX_SYM_LEN
    #define LS_MAX_SYM_LEN 15
#endif

/*
 * Define the maximum number of mapped names.
 */
#ifndef LS_MAX_NAMES
    #define LS_MAX_NAMES 64
#endif

/*
 * Define the number of levels deep the AST can grow to.
 */
#ifndef LS_HEAP_DEPTH
    #define LS_HEAP_DEPTH 12
#endif

/*
 * The size of the memory pool used for storing elements
 */
#ifndef LS_POOL_SIZE
    #define LS_POOL_SIZE 256
#endif

/*
 * These two directives define what characters are allowable
 * as whitespace and in symbols.
 */
#ifndef LS_ALLOWED_WHITESPACE_CHARS
    #define LS_ALLOWED_WHITESPACE_CHARS " \t\n\r"
#endif

#ifndef LS_ALLOWED_SYMBOL_CHARS
    #define LS_ALLOWED_SYMBOL_CHARS "!$%&*+,-./:;<=>?@0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_abcdefghijklmnopqrstuvwxyz{|}~"
#endif
