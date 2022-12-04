import org.ioopm.calculator.ast.*;

public class UnitTest {


    public static void testPrinting(String expected, SymbolicExpression e){
        if (expected.equals("" + e)) {
            System.out.println("Passed: " + e);
        } else {
            System.out.println("Error: expected '" + expected + "' but got '" + e + "'");
        }
    }

    public static void testEvaluating(SymbolicExpression expected, SymbolicExpression e, Environment vars, Environment funcs) {
        EvaluationVisitor ev = new EvaluationVisitor();
        SymbolicExpression r = ev.evaluate(e, vars, funcs);
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
        Environment funcs1 = new Environment();
        SymbolicExpression a3 = new Addition(new Constant(5), new Constant(37));
        SymbolicExpression b3 = new Constant(42);
        testEvaluating(b3, a3, vars1, funcs1); /// Tests if reducing a returns b (it should!)

        // testing correct subtraction
        Environment vars2 = new Environment();
        Environment funcs2 = new Environment();

        SymbolicExpression a4 = new Subtraction(new Constant(12), new Constant(8));
        SymbolicExpression b4 = new Constant(4);
        testEvaluating(b4, a4, vars2, funcs2); /// Tests if reducing a returns b (it should!)

        // testing branches addition
        Environment vars3 = new Environment();
        Environment funcs3 = new Environment();
        SymbolicExpression a5 = new Addition(new Constant(13), new Constant(20)); //33
        SymbolicExpression b5 = new Subtraction(new Constant(5), new Constant(2)); //3
        SymbolicExpression c5 = new Addition(a5, b5);
        SymbolicExpression d5 = new Constant(36);
        testEvaluating(d5, c5, vars3, funcs3); /// Tests if reducing a returns b (it should!)

        //testing variables
        Environment vars4 = new Environment();
        Environment funcs4 = new Environment();
        SymbolicExpression x = new Variable("x");
        SymbolicExpression c3 = new Constant(20);
        SymbolicExpression ass1 = new Assignment(c3, x);
        testEvaluating(c3, ass1, vars4, funcs4);
        SymbolicExpression a6 = new Addition(x, new Constant(10));
        testEvaluating(new Constant(30), a6, vars4, funcs4);

        //testing branch and variables
        Environment vars5 = new Environment();
        Environment funcs5 = new Environment();
        SymbolicExpression y = new Variable("y");
        SymbolicExpression aa5 = new Constant(20);
        SymbolicExpression bb5 = new Assignment(aa5, y); //y = 20
        testEvaluating(aa5, bb5, vars5, funcs5);
        SymbolicExpression cc5 = new Addition(new Constant(3), new Constant(2)); //5
        SymbolicExpression dd5 = new Addition(cc5, y);
        testEvaluating(new Constant(25), dd5, vars5, funcs5);

        //testing overwriting values
        Environment vars6 = new Environment();
        Environment funcs6 = new Environment();
        SymbolicExpression x6 = new Variable("x");
        SymbolicExpression c6 = new Constant(20); //putting x to 20
        SymbolicExpression ass6 = new Assignment(c6, x6);
        testEvaluating(c6, ass6, vars6, funcs6);
        SymbolicExpression b6 = new Addition(x6, new Constant(10));
        testEvaluating(new Constant(30), b6, vars6, funcs6);
        SymbolicExpression d6 = new Constant(10);
        SymbolicExpression ass61 = new Assignment(d6, x6); //putting x to 10
        testEvaluating(d6, ass61, vars6, funcs6);
        SymbolicExpression e6 = new Addition(x6, new Constant(4));
        testEvaluating(new Constant(14), e6, vars6, funcs6);

        //test subtraction overwriting
        Environment vars7 = new Environment();
        Environment funcs7 = new Environment();
        SymbolicExpression x7 = new Variable("x");
        SymbolicExpression c7 = new Constant(20); //putting x to 20
        SymbolicExpression ass7 = new Assignment(c7, x7);
        testEvaluating(c7, ass7, vars7, funcs7);
        SymbolicExpression b7 = new Subtraction(x7, new Constant(10));
        testEvaluating(new Constant(10), b7, vars7, funcs7);
        SymbolicExpression d7 = new Constant(10);
        SymbolicExpression ass71 = new Assignment(d7, x7); //putting x to 10
        testEvaluating(d7, ass71, vars7, funcs7);
        SymbolicExpression e7 = new Subtraction(x7, new Constant(5));
        testEvaluating(new Constant(5), e7, vars7, funcs7);

        //test using cosinus
        Environment vars8 = new Environment();
        Environment funcs8 = new Environment();
        SymbolicExpression a8 = new Addition(new Cos(new Constant(0)), new Constant(37));
        SymbolicExpression b8 = new Constant(38);
        testEvaluating(b8, a8, vars8, funcs8);

        //test using sinus
        Environment vars9 = new Environment();
        Environment funcs9 = new Environment();
        SymbolicExpression a9 = new Addition(new Sin(new Constant(0)), new Constant(37));
        SymbolicExpression b9 = new Constant(37);
        testEvaluating(b9, a9, vars9, funcs9);

        //test using division and multiplication
        Environment vars10 = new Environment();
        Environment funcs10 = new Environment();
        SymbolicExpression a10 = new Multiplication(new Constant(5), new Constant(2));
        SymbolicExpression b10 = new Constant(10);
        testEvaluating(b10, a10, vars10, funcs10);
        SymbolicExpression c10 = new Division(new Constant(5), new Constant(2));
        SymbolicExpression d10 = new Constant(2.5);
        testEvaluating(d10, c10, vars10, funcs10);

        //test multiplying with 0
        Environment vars11 = new Environment();
        Environment funcs11 = new Environment();
        SymbolicExpression a11 = new Multiplication(new Sin(new Constant(0)), new Constant(37));
        SymbolicExpression b11 = new Constant(0);
        testEvaluating(b11, a11, vars11, funcs11);

        //testing with negative values
        Environment vars12 = new Environment();
        Environment funcs12 = new Environment();
        SymbolicExpression a12 = new Multiplication(new Constant(-5), new Constant(2));
        SymbolicExpression b12 = new Constant(-10);
        testEvaluating(b12, a12, vars12, funcs12);

        //testing named constants
        Environment vars13 = new Environment();
        Environment funcs13 = new Environment();
        SymbolicExpression a13 = new Addition(new Constant(Constants.namedConstants.get("pi")), new Constant(1));
        SymbolicExpression b13 = new Constant(Math.PI + 1);
        testEvaluating(b13, a13, vars13, funcs13);

        //testing named constants mult.
        Environment vars14 = new Environment();
        Environment funcs14 = new Environment();
        SymbolicExpression a14 = new Multiplication(new Constant(Constants.namedConstants.get("Answer")), new Constant(2));
        SymbolicExpression b14 = new Constant(84);
        testEvaluating(b14, a14, vars14, funcs14);

    }
}
