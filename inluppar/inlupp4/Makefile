
all:
	javac -d classes -sourcepath src src\org\ioopm\calculator\Calculator.java

run:
	java -cp classes org.ioopm.calculator.Calculator

clean:
	rmdir /s classes

test: all
	java -cp classes org.ioopm.calculator.Test

test_input: 
	javac -d classes -sourcepath src src\org\ioopm\calculator\TestCalculator.java
	java -cp classes org.ioopm.calculator.TestCalculator input.txt output.txt
	FC output.txt expected_output.txt
	java -cp classes org.ioopm.calculator.TestCalculator inputtwo.txt output.txt
	FC output.txt expectedoutputtwo.txt
