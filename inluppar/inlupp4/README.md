# DOCUMENTATION OF PROGRAM

This program serves as a symbolic calculator. The calculator offers different functionalities:
- Addition
- Subtraction
- Multiplication
- Division
- Assignment
- Sin
- Cos
- Exponential
- Logarithms (base 10)
- Negation
- Commands
- Scopes
- Conditional expressions
- Functions

The commands offered to the user are Vars (listing all of our stored values), Quit (quitting the program), End (finishing the definition of a function) and Clear (clearing the contents of Vars).

Additional documentation is located at html/index.html

# RUNNING THE PROGRAM & TESTS

Running and interacting with the calculator
Makefile:

all:
	javac -d classes -sourcepath src src/org/ioopm/calculator/ast/*.java src/org/ioopm/calculator/parser/*.java src/org/ioopm/calculator/*.java

run: all
	java -cp classes org.ioopm.calculator.Calculator

As can be seen here the run-command uses the all-command where we compile all relevant parts of our program.

In terminal:
make run

Running tests:
In Makefile:
test: all
	java -cp classes org.ioopm.calculator.Test

In terminal:
make test


# Profiling Results

# IN TESTS

Following things were covered in the test file:
- All basic operations
- Branches and how they were dealt with
    - in both calculation,
    - and printing
- Assignment of variables
- Use of named constants
- Overwriting assigned variables
- Scopes
- Conditional expressions
