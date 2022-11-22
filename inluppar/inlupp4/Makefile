
all:
	javac -d classes -sourcepath src src/org/ioopm/calculator/ast/*.java src/org/ioopm/calculator/parser/*.java src/org/ioopm/calculator/*.java

run: all
	java -cp classes src.org.ioopm.calculator.Calculator

clean:
	rm -rf classes

test: all
	java -cp classes src.org.ioopm.calculator.Test
