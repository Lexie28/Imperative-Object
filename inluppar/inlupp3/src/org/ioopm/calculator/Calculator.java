package inluppar.inlupp3.src.org.ioopm.calculator;

import inluppar.inlupp3.src.org.ioopm.calculator.ast.*;
import inluppar.inlupp3.src.org.ioopm.calculator.parser.CalculatorParser;

public class Calculator {
    
    public static void main(String[] args) {
        final CalculatorParser parser = new CalculatorParser();
        final Environment vars = new Environment();

        while (true) {
            String input = System.console().readLine();
            SymbolicExpression ob = parser //feeding input into parser?
            if (ob.isCommand())
            {
                
            }

        }
    }
}
