package inluppar.inlupp3.src.org.ioopm.calculator;

import inluppar.inlupp3.src.org.ioopm.calculator.ast.*;


public class Test {
    
    public void testPrinting(String expected, SymbolicExpression e) {
        if (expected.equals("" + e)) {
            System.out.println("Passed: " + e);
        } else {
            System.out.println("Error: expected '" + expected + "' but got '" + e + "'");
        }
    }

    public static void main(String[] args) {
        
        
        
        
        SymbolicExpression m = new Multiplication(new Addition(new Constant(5), new Variable("x")), new Constant(2));
        System.out.println("(5 + x) * 2 ==> " + m);

        SymbolicExpression y = new Division(new Subtraction(new Constant(5), new Variable ("z")), new Constant(5)); // writing test by anik
        System.out.println("(5 - z) / 5 ==> " + y);
        
        
        
    }
}
