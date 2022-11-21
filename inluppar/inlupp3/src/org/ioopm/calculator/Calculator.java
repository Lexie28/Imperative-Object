package inluppar.inlupp3.src.org.ioopm.calculator;

import inluppar.inlupp3.src.org.ioopm.calculator.ast.*;
import inluppar.inlupp3.src.org.ioopm.calculator.parser.CalculatorParser;

public class Calculator {
    
    public static void main(String[] args) {
        final CalculatorParser parser = new CalculatorParser();
        final Environment vars = new Environment();
        
        while (true) {
            String input = System.console().readLine();
            try {
                SymbolicExpression ob = parser.parse(input, vars);
                if (ob.isCommand())
                {
                    if (ob instanceof Clear) {
                        vars.clear();
                    }
                    if (ob instanceof Vars) {
                        System.out.println(vars.toString());
                    }
                    if (ob instanceof Quit) {
                        break;
                    }
                } 
                else
                {
                    SymbolicExpression evaluatedob = ob.eval(vars);
                    System.out.println("" + evaluatedob);
                    vars.put(new Variable("ans"), evaluatedob);
                }
            } catch (Exception e) {
                System.out.println("Error!" + e);
            }
            

        }
    }
}