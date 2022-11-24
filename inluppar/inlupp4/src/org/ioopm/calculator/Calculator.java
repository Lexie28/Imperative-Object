package org.ioopm.calculator;

import java.io.IOException;
import java.util.Scanner;

import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.CalculatorParser;

public class Calculator {
    
    public static void main(String[] args) {
        final CalculatorParser parser = new CalculatorParser();
        final Environment vars = new Environment();
        final Stats stats = new Stats();
        final EvaluationVisitor ev = new EvaluationVisitor();
        Scanner sc = new Scanner(System.in);
        
        while (true) {
            NamedConstantChecker ncc = new NamedConstantChecker();
            String input = sc.nextLine();
            try {
                SymbolicExpression ob = parser.parse(input, vars);
                if (ob.isCommand())
                {
                    if (ob instanceof Clear) {
                        vars.clear();
                    }
                    if (ob instanceof Vars) {
                        System.out.println(vars);
                    }
                    if (ob instanceof Quit) {
                        break;
                    }
                } 
                else
                {
                    stats.addExpression();

                    boolean notIllegal = ncc.check(ob);
                    if(!notIllegal) {
                        System.out.println(ncc.getCheckFlags());
                    }
                    SymbolicExpression evaluatedob = ev.evaluate(ob, vars);
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
        sc.close();
    }
}