package org.ioopm.calculator;

import java.io.IOException;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.util.Scanner;

import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.CalculatorParser;

public class TestCalculator {
    
    public static void main(String[] args) throws IOException {
        final CalculatorParser parser = new CalculatorParser();
        final Environment vars = new Environment();
        final Stats stats = new Stats();

        Scanner sc = new Scanner(new File(args[0]));
        FileWriter fw = new FileWriter(args[1]);
        
        while (sc.hasNextLine()) {
            String input = sc.nextLine();
            try {
                SymbolicExpression ob = parser.parse(input, vars);
                if (ob.isCommand())
                {
                    if (ob instanceof Clear) {
                        vars.clear();
                    }
                    if (ob instanceof Vars) {
                        fw.write(vars.toString());
                    }
                    if (ob instanceof Quit) {
                        break;
                    }
                } 
                else
                {
                    stats.addExpression();
                    SymbolicExpression evaluatedob = ob.eval(vars);
                    fw.write("" + evaluatedob);
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
                fw.write(e.getMessage());
            }
            fw.write("\n");
        }
        fw.close();
        sc.close();
    }
}
