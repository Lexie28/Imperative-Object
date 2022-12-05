import org.ioopm.calculator.ast.*;

import org.junit.Test;

public class TestMultiplication {
    Constant c1 = new Constant(2.0);
    Constant c2 = new Constant(2.0);
    Constant c3 = new Constant(4);
    Multiplication a = new Multiplication(c1, c2);
    Multiplication a2 = new Multiplication(c2, c1);
    
    Constant c4 = new Constant(0);
    Constant c5 = new Constant(4);
    Constant c6 = new Constant(0);
    Multiplication a3 = new Multiplication(c4, c5);
    Multiplication a4 = new Multiplication(c5, c4);

    @Test
    public void testGetValue() {
        try {
            a.getValue();
            assert false;
        } catch(RuntimeException e) {
            assert true;
        }
    }

    @Test
    public void testGetValue2() {
        try {
            a3.getValue();
            assert false;
        } catch(RuntimeException e) {
            assert true;
        }
    }

    @Test
    public void testIsConstant() {
        assert false == a.isConstant();
        assert false == a3.isConstant();
    }

    @Test
    public void testGetName() {
        assert "*".equals(Multiplication.getName());
    }

    @Test
    public void testIsCommand() {
        assert false == a.isCommand();
        assert false == a3.isCommand();
    }

    @Test
    public void testPriority() {
        assert 100 == a.getPriority();
        assert 100 == a3.getPriority();
    }

    @Test
    public void testToString() {
        assert "2.0 * 2.0".equals(a.toString());
    }

    @Test
    public void testToString2() {
        assert "0.0 * 4.0".equals(a3.toString());
    }

    @Test
    public void testEquals() {
        assert a.equals(a2);
    }

    @Test
    public void testEval() {
        Environment vars = new Environment();
        Environment funcs = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assert c3.equals(ev.evaluate(a, vars, funcs));
    }

    @Test
    public void testEval2() {
        Environment vars = new Environment();
        Environment funcs = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assert c6.equals(ev.evaluate(a3, vars, funcs));
    }
}