import org.ioopm.calculator.ast.*;

import org.junit.Test;

public class TestVariable {
    Variable a = new Variable("x");
    Variable b = new Variable("x");

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
        try {
            Variable.getName();
            assert false;
        }
            catch(RuntimeException e) {
                assert true;
            }
    }

    @Test
    public void testIsCommand() {
        assert false == a.isCommand();
    }

    @Test
    public void testPriority() {
        assert 200 == a.getPriority();
    }

    @Test
    public void testToString() {
        assert "x".equals(a.toString());
    }

    @Test
    public void testEquals() {
        assert a.equals(b);
    }

    @Test
    public void testEval() {
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assert b.equals(ev.evaluate(a, vars));
    }
}