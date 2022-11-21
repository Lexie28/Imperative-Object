
package inluppar.inlupp3.src.org.ioopm.calculator;

import inluppar.inlupp3.src.org.ioopm.calculator.ast.*;
import java.util.HashMap;


public class Test {

    public static void testPrinting(String expected, SymbolicExpression e){
        if (expected.equals("" + e)) {
            System.out.println("Passed: " + e);
        } else {
            System.out.println("Error: expected '" + expected + "' but got '" + e + "'");
        }
    }

    public static void testEvaluating(SymbolicExpression expected, SymbolicExpression e, Environment vars) {
        SymbolicExpression r = e.eval(vars);
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
        Environment vars1 = new Environment();
        SymbolicExpression a3 = new Addition(new Constant(5), new Constant(37));
        SymbolicExpression b3 = new Constant(42);
        testEvaluating(b3, a3, vars1); /// Tests if reducing a returns b (it should!)

        // testing correct subtraction
        Environment vars2 = new Environment();
        SymbolicExpression a4 = new Subtraction(new Constant(12), new Constant(8));
        SymbolicExpression b4 = new Constant(4);
        testEvaluating(b4, a4, vars2); /// Tests if reducing a returns b (it should!)

        // testing branches addition
        Environment vars3 = new Environment();
        SymbolicExpression a5 = new Addition(new Constant(13), new Constant(20)); //33
        SymbolicExpression b5 = new Subtraction(new Constant(5), new Constant(2)); //3
        SymbolicExpression c5 = new Addition(a5, b5);
        SymbolicExpression d5 = new Constant(36);
        testEvaluating(d5, c5, vars3); /// Tests if reducing a returns b (it should!)

        //testing variables
        Environment vars4 = new Environment();
        SymbolicExpression x = new Variable("x");
        SymbolicExpression c3 = new Constant(20);
        SymbolicExpression ass1 = new Assignment(c3, x);
        testEvaluating(c3, ass1, vars4);
        SymbolicExpression a6 = new Addition(x, new Constant(10));
        testEvaluating(new Constant(30), a6, vars4);

        //testing branch and variables
        Environment vars5 = new Environment();
        SymbolicExpression y = new Variable("y");
        SymbolicExpression aa5 = new Constant(20);
        SymbolicExpression bb5 = new Assignment(aa5, y); //y = 20
        testEvaluating(aa5, bb5, vars5);
        SymbolicExpression cc5 = new Addition(new Constant(3), new Constant(2)); //5
        SymbolicExpression dd5 = new Addition(cc5, y);
        testEvaluating(new Constant(25), dd5, vars5);

        //testing overwriting values
        Environment vars6 = new Environment();
        SymbolicExpression x6 = new Variable("x");
        SymbolicExpression c6 = new Constant(20); //putting x to 20
        SymbolicExpression ass6 = new Assignment(c6, x6);
        testEvaluating(c6, ass6, vars6);
        SymbolicExpression b6 = new Addition(x6, new Constant(10));
        testEvaluating(new Constant(30), b6, vars6);
        SymbolicExpression d6 = new Constant(10);
        SymbolicExpression ass61 = new Assignment(d6, x6); //putting x to 10
        testEvaluating(d6, ass61, vars6);
        SymbolicExpression e6 = new Addition(x6, new Constant(4));
        testEvaluating(new Constant(14), e6, vars6);

        //test subtraction overwriting
        Environment vars7 = new Environment();
        SymbolicExpression x7 = new Variable("x");
        SymbolicExpression c7 = new Constant(20); //putting x to 20
        SymbolicExpression ass7 = new Assignment(c7, x7);
        testEvaluating(c7, ass7, vars7);
        SymbolicExpression b7 = new Subtraction(x7, new Constant(10));
        testEvaluating(new Constant(10), b7, vars7);
        SymbolicExpression d7 = new Constant(10);
        SymbolicExpression ass71 = new Assignment(d7, x7); //putting x to 10
        testEvaluating(d7, ass71, vars7);
        SymbolicExpression e7 = new Subtraction(x7, new Constant(5));
        testEvaluating(new Constant(5), e7, vars7);

        //test using cosinus
        Environment vars8 = new Environment();
        SymbolicExpression a8 = new Addition(new Cos(new Constant(0)), new Constant(37));
        SymbolicExpression b8 = new Constant(38);
        testEvaluating(b8, a8, vars8);


        //IDEA testing negative values
        //test med sin(0) etc.

        
    }
}
