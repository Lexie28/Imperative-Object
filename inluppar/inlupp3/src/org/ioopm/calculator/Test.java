package inluppar.inlupp3.src.org.ioopm.calculator;

import inluppar.inlupp3.src.org.ioopm.calculator.ast.*;


public class Test {

    public static void main(String[] args) {
        
        
        
        // multiplication with addtion
        Constant c1 = new Constant(5);
        Constant c2 = new Constant(2);
        Variable v = new Variable("x");
        Addition a = new Addition(c1, v);
        Multiplication m = new Multiplication(a, c2);   
        System.out.println("(5 + x) * 2 ==> " + m);

        // multiplication with subtraction
        Constant b1 = new Constant(3);
        Constant b2 = new Constant(4);
        Variable v1 = new Variable("y");
        Subtraction a1 = new Subtraction(b1, v1);
        Multiplication n = new Multiplication(a1, b2);  
        System.out.println("(3 - y) * 4 ==> " + n);

        // division with subtraction
        Constant d1 = new Constant(8);
        Constant d2 = new Constant(2);
        Variable v2 = new Variable("y");
        Subtraction a2 = new Subtraction(d1, v2);
        Division g = new Division(a2, d2);  
        System.out.println("(8 - y) / 2 ==> " + g);




        
        
        
    }
}
