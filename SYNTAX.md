## Variables

let x = 42

## Constants

const PI = 3.14159

## Array

let arr: Array<Float> = [1.2, 75.4]

## Function declaration

fn add(x, y) {
return x + y
}

## Function call

let result = add(5, 7)

## Function with type annotations

fn add(x: Int, y: Int): Int {
return x + y
}

## Importing modules

import Math
import List as L

## Using imported functions

let result = Math.sqrt(16)
let sum = L.sum([1, 2, 3, 4, 5])

## Imperative-style loop

for i = 1 to 10 {
print(i)
}

## Object-oriented class definition

```
class Rectangle {
    constructor(width, height) {
        this.width = width
        this.height = height
    }

    method area() {
        return this.width * this.height
    }

}
```

## First-Class Functions and Higher-Order Functions

let add = fn (x, y) => x + y
let double = fn (x) => x \* 2
let apply = fn (func, arg) => func(arg)

## Immutable Data

let immutableVar = const 42

## Pattern Matching

let a = match x {
| 0 => "Zero"
| n if n < 0 => "Negative"
| \_ => "Positive"
}

## Anonymous Functions (Lambdas)

let square = fn (x) => x \* x

## Closures

let makeCounter = fn () => {
let count = ref 0
fn () => {
count := !count + 1
!count
}
}

## Recursion (with Tail Call Optimization)

let rec factorial = fn (n, acc = 1) =>
if n <= 1 then acc else factorial(n - 1, n \* acc)

## Lazy Evaluation

let lazyVal = lazy {
print("This will be evaluated lazily")
42
}

## Pure Functions

let pureAdd = fn (x, y) => x + y

## Monads and Functors

let maybeDouble = fn (x) => if x? then Just(x \* 2) else Nothing

## Type Inference

let add = fn (x, y) => x + y -- Inferred as Int -> Int -> Int

## Algebraic Data Types (Sum Types and Product Types)

type Shape =
| Circle of Float
| Rectangle of { width: Float, height: Float }

## Tail Recursion Optimization

let rec factorial = fn (n, acc = 1) =>
if n <= 1 then acc else factorial(n - 1, n \* acc)

## Currying

let curryAdd = fn (x) => fn (y) => x + y

## Type Classes (Inspired by Haskell)

type Num a = {
add: a -> a -> a,
mul: a -> a -> a
}

instance Num Int where
add = fn (x, y) => x + y
mul = fn (x, y) => x \* y

## High-Order Type Systems (Dependent Types)

type List a =
| Nil
| Cons a (List a)

## Garbage Collection

gc.collect()

## Lazy Lists

let nums = range(1, Infinity)
let squares = map(fn (x) => x \* x, nums)

## Monadic Composition

let result = do {
a <- doSomething()
b <- doSomethingElse(a)
c <- andFinally(b)
return c
}
