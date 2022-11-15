
all:
	javac -d classes src/org/ioopm/calculator/ast/*.java

run: all
	java -cp classes inluppar.inlupp3.src.org.ioopm.calculator.Calculator

clean:
	rm -rf classes

test: all
	javac -d classes src/org/ioopm/calculator/Test.java
	java -cp classes inluppar.inlupp3.src.org.ioopm.calculator.Test
