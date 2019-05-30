# B A N
## Boolean Algebra Notation (PRE-ALPHA) 0.0.1
---
Boolean Algebra Notation is a programming language that allows the execution of Boolean expressions.
### Abstract Datatypes
##### Stack
The virtual stack is a linked list which can be popped (retrieve value but delete after retrieval) or pushed (append the list). It is a FILO (First In, Last Out) data type. 
##### Variables
Variables are stored on two lists. A key list, and a data list. The location of a key will correlate directly to the location of the data. This is similar to a dictionary in modern programming languages. It currently has a worst-case compute time of `O(n)`, but that will be fixed with the hash table in later releases.
##### Functions
Functions work exactly like variables, except the key is the function name and the data is the line of code where the function starts.
### Datatypes
The Boolean Algebra Notation language contains one and only one data type. 1, and 0.
Expressions can be used to deliver a one or a zero, but the foundation of `ON` and `OFF` stay the same. Data can be set using the `set` opcode, or by `pop`ing data off the stack and into a variable.

### Special Rules
All Boolean expressions are pushed onto the stack. For example, One could access the value of `+ 1 x` by popping data off the stack. Popping can be done in two ways.
1. `pop <variablename>`. This will set a definied variable to the first element of the stack, and then removes the first element on the stack.
2. `[pop]` is a special variable. When derefrenced, it will return the top most element on the stack, and then remove that element.

Nested parenthesis are allowed. For example, the **xor** gate could be created in one line using nested parenthesis.
`+ (* (! x) y) (* (! y) x)`
Once again, to retrieve this value, pop it off the stack.
### Syntax
The Boolean Algebra Notation language has a Assembly-like syntax. Here is the current special statements.

---
##### define
Define creates a variable with the value `NULL`.

`define <variablename>;`

----
##### set
Set sets the value of a defined variable to the input. Data may be 1 or 0, or another variable.

`set  <variablename> = <data>;`

---
##### *
This is the **and** operator. Will return true only when both inputs are true.

`* <a> <b>;`

---
##### +
This is the **or** operator. Will return true if either input is true.

`+ <a> <b>;`

---
##### !
This is the **not** operator. Will return the inverse of the input.

`! <a>;`

---
##### push
This pushes an item on the stack. This can be a boolean value or a variable. Keep in mind that boolean expressions are *automatically* pushed onto the stack.

`push <data>;`

---
##### pop
This sets the value of a defined variable as the first item of the stack and then deletes the item.

`pop <variablename>;`

This also can be used through the `[pop]` special variable.

`set <variablename> = [pop];`

---
##### func
Create a pointer to the line under this statement, labeled by the second arguement. **Keep in mind code within a function must be tabbed or have 4 prefixed whitespaces.**
```
func xor;
  define x;
  define y;
  pop x;
  pop y;
  + (* (! x) y) (* (! y) x);
  return;
```
----
##### return
Return is used to notate the end of a function. Without a return statement, you will have an endless loop.

`return;`

---
##### call
Call sets the instruction pointer to the pointer of second arguement. Above, I created the xor function. Call will jump to that code and keep running from the position until it hits the  `return` keyword. At that point, it will resume execution from the original area.

`call <functionname>`;

---
##### debug
Debug will dump all data storage to standard output. This includes the stack, variables, and functions. As of now, this is going to be your print method.

`debug;`
