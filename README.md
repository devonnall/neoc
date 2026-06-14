# NeoC

A variant of C that aims to add quality of life improvements and address some of its weird quirks.

## Overview

NeoC is a statically typed programming language I am designing. I have been interested in building a compiler for a long time, and
this is my first major attempt. I am aiming to just make a slightly better version of C without making it an entirely different language like C++. 

Currently, the scanner is close to its final form, with minor tweaks to come. The roadmap looks like this:

- [x] Scanner
- [ ] Parser
- [ ] Semantic analyzer
- [ ] C code generation

## Features

### Scanner

The scanner is the only implemented feature right now. It reads the entire source `.dy` file into a buffer and reads
character by character constructing an array of tokens. Each token has a type, start position, line number, column
number, and lexeme. 

Initially I was doing validation for numbers while scanning. Then I looked at how clang does validation and it actually
doesn't do validation for things like numbers during the lexing phase. If a token starts with a number, then it will be classified
as a number regardless of what characters come after. So my scanner does the same. Validation will be done during/after the
parsing stage. 

#### Keywords

`int`, `float`, `double`, `char`, `string`, `if`, `else`, `fn`, `for`, `while`, `return`, `break`

#### Operators

Basic operators like `+`, `-`, `*`, `/`, `%`, `&`, `|`, `^`, `!` will be supported along with their shorthand counterparts including
`++`, `+=`, `--`, `-=, `*=, `/=`, `%=`, `&&`, `&=`, `|=, `^=`, and `!=`. 

There are several more token types, including ones for numeric and string literals. 

#### Printing

The parser is not implemented yet, so you can't do anything useful with the constructed array of tokens besides printing to them
to the console. 

### Syntax

Syntax is basically the same as C with some slight modifications.

#### Variable Declarations

Types come after the variable name:

```
x: int = 10;
```

This is how modern languages like Rust and Go do it. It makes parsing easier. 

#### Function Declarations

Functions are similar to variables, with the return type coming after:

```
fn add(a: int, b: int): int {
  return a + b;
}
```

If a function doesn't return anything, simply omit the type:

```
fn say_hello(name: string) {
  print(name);
}
```

#### Pointers

As of now, pointers will be declared and dereferenced with a tilde (`~`). I want to avoid ambiguity with `*`.

```
x: ~int = new int[50];
x[0] = 1;
print("{~x}");
# or
print("{x[0]}")
```

## Planned Features

### Parser

The parser will be a handwriiten and use recursive descent. More information to come soon.

### Semantic Analyzer

<Description to come soon>

### C Code Generator

NeoC will be compiled to C.

<More information to come soon>

### Language Features

#### Multiple Possible Types

To avoid macros or writing multiple almost identical functions, the plan is to allow specifying multiple return types
for a single function:

```
fn pow(num: int, float, double, exp: int): int, float, double {
  res: (num) = num;
  for (i: int = 1; i < exp; i++) {
    res *= num;
  }
  return res;
}
```

Use more concise syntax by defining a variable to hold the types:

```
number: type = int, float, double;

fn pow(num: [number], exp: int): [number] {
  res: (num) = num;
  for (i: int = 1; i < exp; i++) {
    res *= num;
  }
  return res;
}
```

#### Function Pointers

Declare a function pointer:

```
fn add(a: int, b: int): int {
  return a + b;
}
fp: fn(int, int): int = add;
```

#### Memory Allocation

Syntax for allocating and freeing memory on the heap will hopefully be better:

```
fn main() {
  lexemes: string[] = new string[50];
  types: string[] = new string[50];
  // do things
  free lexemes, types;
}
```

**TBD**

# Build and Run

**NOTE**: Currently only tested on Apple Silicon (M1).

Clone the repository and build:

```bash
git clone https://github.com/devonnall/neoc.git
cd neoc && make
```

Run the tests:

```bash
cd tests/scanner
chmod +x ./run-scanner-tests.sh
./run-scanner-tests.sh
```

You can find sample dummy programs in tests/scanner. Run the scanner on a file to get a list of tokens (from project root):

```bash
./bin/neoc path/to/source/file
```

For example:

```bash
./bin/neoc test.neoc
```
