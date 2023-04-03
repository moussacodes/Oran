# Haïfa language syntax:
```
// one line comment

{
*multi line 
comments
*}
```
## package import:

```
magma "main" // basically file name without extension
get "main" // it will import file
```

## Program entry:
```
//main is the entry to the program
set main(arg1: int, arg2: char) -> int {

}
```
## Types:

**bool:** represents a boolean value of either true or false.
**char:** represents a single Unicode character.
**signed integers:** i8, i16, i32, i64, and i128: represent signed integers with 8, 16, 32, 64, and 128 bits, respectively.
**unsigned integers:** u8, u16, u32, u64, and u128: represent unsigned integers with 8, 16, 32, 64, and 128 bits, respectively.
**float:** f32 and f64: represent single-precision and double-precision floating-point numbers, respectively.
**enum:** represents a type with named values, which can be used to represent a finite set of possible values.
**struct:** represents a type with named fields, which can be used to group related values.
**union:** represents a type with multiple fields that can overlap in memory.
**tuple:** represents a type with 2 or 3 fields max that can be used in group.

***example:***

**bool:**
```
let is_true: bool = true;
let is_false: bool = false;
```
**char:**
```
let c: char = 'a';
```
**signed integers:**
```
let i8_num: i8 = -128;
let i16_num: i16 = -32768;
let i32_num: i32 = -2147483648;
let i64_num: i64 = -9223372036854775808;
let i128_num: i128 = -170141183460469231731687303715884105728;
```
**unsigned integers:**
```
let u8_num: u8 = 255;
let u16_num: u16 = 65535;
let u32_num: u32 = 4294967295;
let u64_num: u64 = 18446744073709551615;
let u128_num: u128 = 340282366920938463463374607431768211455;
```
**float:**
```
let f32_num: f32 = 3.14;
let f64_num: f64 = 3.141592653589793;
```
**enum:**
```
enum Direction {
    Up,
    Down,
    Left,
    Right,
}
let dir: Direction = Direction::Up;
```
**struct:**
```
struct Point {
    x: i32,
    y: i32,
}

let point: Point = Point { x: 10, y: 20 };
```

**tuple:**
```
let tuple2: (u16, u16) = (1, 2);
let tuple3: (string, u16, f32) = ("hello", 3, 4.56);
```

## Data structure:

they will be implemented as a part of the standard library
**Stack**
**Heap**
**Graph**
**Hashmap**

## IO
```
write("hello world"); -> to print hello world
let choice: string = input("(y/n): ") -> returns what the user entered
```
## Assignement:
```
define PI   3.14;
const var: f32 = 0.1;
let var: u32 = 10;
let p: i32 = undefined
let a: string = "value"
let b: char = 'a' -> char should be inside ' '
```
**reassign to variable:**
```
var <- 11;
```
## Interfaces: 
```
Interface Car{
    name: string,
    model: 
}
```
## Objects:
```
mut person: obj = {
name: "person",
age: 20,
};;
```
## Arrays:
```
let arr: u32[10] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
let arr: char[5] = ['a', 'b', 'c', 'd', 'e'];
```
### Array manipulation:
```
arr.len -> size of the array
arr.push(el)
arr.pop()
arr.at(index: u32)
arr.concat(arr2)
arr.splitAt(index: u32) -> return 2 new arrays split ar index
arr.find(|x| -> x == 5) -> returns the the item and index in a tuple
arr.loop(|x| -> write(x)) -> loop through array and print each item
arr.map(|x| -> x2) -> return new array with the result of the callback function
more to come.
```
## Conditionals:
```
if(a > 10){

} else if(a < 5){

}else{

}

let stop: bool = true;
```
**one line if**: 
```
if(stop) then {expressions} else {expression2};;
```
## Loop

**type1:**
```
while(true){

}
```
**type2:**
```
for x = 10 to 150 do {
{expressions}
}
```
**type3:**
```
for x in (10, 150) do {
{expressions}
}
```
**type4:**
```
let arr: char[3] = ['a', 'b', 'c'];

for (_, index) in arr do {
    write("$ is at index $", _, index);
}
```
## Functions:

**type1:**
```
set func1(arg1: u8, arg2: u8) -> u8 {
    return arg1 + arg2;;
}
function can also return walo (aka void)
```
**type2:**
```
let ret: u32 = |x: u32, y: u32| -> {
    {expressions}
}
```
**type3:**
```
let ret: u32 = |x: u32, y: u32| -> x + y;;
```

**type4:**
set func1(arg1: u8, arg2: |u8| -> walo) -> u8{
    return arg1 + arg2;
}
arg2 here is a callback function