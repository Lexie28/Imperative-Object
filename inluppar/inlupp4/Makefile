
all:
	javac -d classes -sourcepath src src\org\ioopm\calculator\Calculator.java

run:
	java -cp classes org.ioopm.calculator.Calculator

clean:
	rmdir /s classes

test: all
	java -cp classes org.ioopm.calculator.Test

test_input: 
	java -cp classes org.ioopm.calculator.Calculator < input.txt > output.txt
	FC output.txt expected_output.txt
