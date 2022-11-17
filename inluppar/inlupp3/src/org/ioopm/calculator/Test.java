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
        
    }
}
