package org.ioopm.calculator;

import java.util.Scanner;

import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.CalculatorParser;

public class Calculator {
    
    public static void main(String[] args) {
        
        final CalculatorParser parser = new CalculatorParser();
        final Environment vars = new Environment();
        final Environment funcs = new Environment();
        final Stats stats = new Stats();
        final EvaluationVisitor ev = new EvaluationVisitor();
        Scanner sc = new Scanner(System.in);

        Variable currentFuncName = new Variable("");
        
        while (true) {

            NamedConstantChecker ncc = new NamedConstantChecker();
            ReassignmentChecker reassc = new ReassignmentChecker();
            String input = sc.nextLine();
            try {
                SymbolicExpression ob = parser.parse(input, vars, funcs);

                if (ob.isCommand())
                {
                    if (ob instanceof Clear) {
                        vars.clear();
                    }
                    if (ob instanceof Vars) {
                        System.out.println("" + vars);
                    }
                    if (ob instanceof Quit) {
                        break;
                    }
                    if (ob instanceof End) {

                        currentFuncName = new Variable("");

                    }
                } else if (parser.getFunctionParsingMode()){
                    if(ob instanceof FunctionDeclaration fd) {
                        funcs.put(new Variable(fd.getIdentifier()), fd);
                        currentFuncName = new Variable(fd.getIdentifier());
                    } else {
                        if(ncc.check(ob) == false) {
                            System.out.println("Error, assignment to named constants:");
                            for(SymbolicExpression expression : ncc.checkList) {
                                System.out.println("" + expression);
                            }
                            continue;
                        }
                        if(reassc.check(ob) == false) {
                            for(SymbolicExpression expression : reassc.reassignmentList) {
                                System.out.println("Error, the variable " + expression + " is reassigned." );
                            }
                            continue;
                        } else {
                            ((FunctionDeclaration) funcs.get(currentFuncName)).addExpression(ob);
                        }
                    }
                } else {
                    stats.addExpression();

                    // Namned Constant Checker
                    if(ncc.check(ob) == false) {
                        System.out.println("Error, assignment to named constants:");
                        for(SymbolicExpression expression : ncc.checkList) {
                            System.out.println("" + expression);
                        }
                        continue;
                    }

                    // Variable Reassignment Checker
                    if(reassc.check(ob) == false) {
                        for(SymbolicExpression expression : reassc.reassignmentList) {
                            System.out.println("Error, the variable " + expression + " is reassigned." );
                        }
                        continue;
                    }

                    SymbolicExpression evaluatedob = ev.evaluate(ob, vars, funcs);
                    

                    System.out.println("" + evaluatedob);
                    vars.put(new Variable("ans"), evaluatedob);

                    if (evaluatedob.isConstant()) {
                        stats.addFullEval();
                        //kom ihåg att här adda till både full o succcess eval här då en full eval inkl. success eval
                    } else {
                        stats.addSuccEval();
                    }
                }
            } catch (Exception e) {
                stats.addExpression();
                System.out.println("" + e.getMessage());
            }
        }
        stats.printstats();
        sc.close();
    }
}