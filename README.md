# L-Script
A Functional Interpreted Language for Microcontrollers

## Motivation and Goals
* Fill the need to update microcontroller code on-the-fly without modifying firmware.
* Provide a mechanism to supply pure functions that map inputs to outputs.
* Easy to include as part of an application; only a single import statement needed to bundle the interpreter.
* Robust – must guarantee that programs always complete and don’t cause memory issues.

## Example program
Calculate the 10th Fibonacci number.
```
`(
  (fun fib `(x)
    (if (= 1 x) 1
      (if (> 1 x)
        (+ (fib (- 1 x)) (fib (- 2 x)))
        0
      )
    )
  )
  (fib 10)
)
```

## Progress
- [x] Write an efficient linear parser
- [x] Create unit tests to test the parser
- [ ] Write the runtime evaluator
- [ ] Create integration test programs to test the evaluator
