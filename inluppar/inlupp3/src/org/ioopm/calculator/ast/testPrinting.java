package inluppar.inlupp3.src.org.ioopm.calculator.ast;


public class testPrinting{
    
    public testPrinting(String expected, SymbolicExpression e) {
        if (expected.equals("" + e)) {
            System.out.println("Passed: " + e);
        } else {
            System.out.println("Error: expected '" + expected + "' but got '" + e + "'");
        }
    }
    
}