import org.ioopm.calculator.ast.*;

import org.junit.Test;

public class TestCos {
    Constant c1 = new Constant(0);
    Constant c2 = new Constant(1);
    Cos a = new Cos(c1); //=0
    Cos b = new Cos(c1);

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
    public void testIsConstant() {
        assert false == a.isConstant();
    }

    @Test
    public void testGetName() {
        assert "cos".equals(Cos.getName());
    }

    @Test
    public void testIsCommand() {
        assert false == a.isCommand();
    }

    @Test
    public void testPriority() {
        assert 150 == a.getPriority();
    }

    @Test
    public void testToString() {
        assert "cos 0.0".equals(a.toString());
    }

    @Test
    public void testEquals() {
        assert a.equals(b);
    }

    @Test
    public void testEval() {
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assert c2.equals(ev.evaluate(a, vars));
    }
}