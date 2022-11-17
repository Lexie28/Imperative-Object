package inluppar.inlupp3.src.org.ioopm.calculator;

import inluppar.inlupp3.src.org.ioopm.calculator.ast.*;


public class Test {


    public static void testPrinting(String expected, SymbolicExpression e){
        if (expected.equals("" + e)) {
            System.out.println("Passed: " + e);
        } else {
            System.out.println("Error: expected '" + expected + "' but got '" + e + "'");
        }
    }

    public static void testEvaluating(SymbolicExpression expected, SymbolicExpression e) {
        SymbolicExpression r = e.eval();
        if (r.equals(expected)) {
            System.out.println("Passed: " + expected + " " + "=" + " " + e);
        } else {
            System.out.println("Error: expected '" + expected + "' but got '" + e + "'");
        }
    }

    public static void main(String[] args) {
        
        // multiplication with addtion
        Constant c1 = new Constant(5);
        Constant c2 = new Constant(2);
        Variable v = new Variable("x");
        Addition a = new Addition(c1, v);
        Multiplication m = new Multiplication(a, c2);   
        testPrinting("(5.0 + x) * 2.0", m);

        // multiplication with subtraction
        Constant b1 = new Constant(3);
        Constant b2 = new Constant(4);
        Variable v1 = new Variable("y");
        Subtraction a1 = new Subtraction(b1, v1);
        Multiplication n = new Multiplication(a1, b2);  
        testPrinting("(3.0 - y) * 4.0", n);

        // division with subtraction
        Constant d1 = new Constant(8);
        Constant d2 = new Constant(2);
        Variable v2 = new Variable("y");
        Subtraction a2 = new Subtraction(d1, v2);
        Division g = new Division(a2, d2);  
        testPrinting("(8.0 - y) / 2.0", g);

        // testing correct addition
        SymbolicExpression a3 = new Addition(new Constant(5), new Constant(37));
        SymbolicExpression b3 = new Constant(42);
        testEvaluating(b3, a3); /// Tests if reducing a returns b (it should!)

        // testing correct subtraction
        SymbolicExpression a4 = new Subtraction(new Constant(12), new Constant(8));
        SymbolicExpression b4 = new Constant(4);
        testEvaluating(b4, a4); /// Tests if reducing a returns b (it should!)

        // testing incorrect addition
        SymbolicExpression a5 = new Addition(new Constant(12), new Constant(20));
        SymbolicExpression b5 = new Constant(42);
        testEvaluating(b5, a5); /// Tests if reducing a returns b (it should!)

        //IDEA testing incorrect and negative values

        
    }
}
