package inluppar.inlupp3.src.org.ioopm.calculator;

import java.io.IOException;

import inluppar.inlupp3.src.org.ioopm.calculator.ast.*;
import inluppar.inlupp3.src.org.ioopm.calculator.parser.CalculatorParser;

public class Calculator {
    
    public static void main(String[] args) {
        final CalculatorParser parser = new CalculatorParser();
        final Environment vars = new Environment();
        final Stats stats = new Stats();
        
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
                    stats.addExpression();
                    SymbolicExpression evaluatedob = ob.eval(vars);
                    System.out.println("" + evaluatedob);
                    vars.put(new Variable("ans"), evaluatedob);
                    if (evaluatedob.isConstant()) {
                        stats.addFullEval();
                        //kom ihåg att här adda till både full o succcess eval här då en full eval inkl. success eval
                    } else {
                        stats.addSuccEval();
                    }
                }
            }
             catch (Exception e) {
                stats.addExpression();
                System.out.println(e.getMessage());
            }
        }
        stats.printstats();
    }
}