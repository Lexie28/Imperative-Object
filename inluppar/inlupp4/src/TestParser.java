import java.io.IOException;

import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;

import org.junit.Test;


public class TestParser {
    @Test
    public void testEquals() {
        Addition a = new Addition(new Constant(42), new Negation(new Constant(4711)));
        CalculatorParser parser = new CalculatorParser();
        Environment vars = new Environment();
        
        try {
            SymbolicExpression s = parser.parse(a.toString(), vars);
            assert a.equals(s);
        } catch(IOException e) {
            assert false;
        }
    }

    @Test
    public void testVariableNegation() {
        Negation n = new Negation(new Negation(new Negation(new Variable("x"))));
        CalculatorParser parser = new CalculatorParser();
        Environment vars = new Environment();

        try {
            SymbolicExpression s = parser.parse(n.toString(), vars);
            assert n.equals(s);
        } catch(IOException e) {
            assert false;
        }
    }

    @Test
    public void testNamedConstantNegation() {
        Negation n = new Negation(new Negation(new Negation(new Variable("pi"))));
        CalculatorParser parser = new CalculatorParser();
        Environment vars = new Environment();

        try {
            SymbolicExpression s = parser.parse(n.toString(), vars);
            assert n.eval(vars).equals(s.eval(vars)); // May cause problems in the future
        } catch(IOException e) {
            assert false;
        }
    }


}
