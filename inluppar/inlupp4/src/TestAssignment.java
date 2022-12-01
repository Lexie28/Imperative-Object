import org.ioopm.calculator.ast.*;

import org.junit.Test;

public class TestAssignment {
    Constant c = new Constant(2.0);
    Variable x = new Variable("x");
    Assignment a = new Assignment(c, x);
    Assignment a2 = new Assignment(c, x);
    //Addition a2 = new Addition(c2, c1);

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
        assert "=".equals(Assignment.getName());
    }

    @Test
    public void testIsCommand() {
        assert false == a.isCommand();
    }

    @Test
    public void testPriority() {
        assert 0 == a.getPriority();
    }

    @Test
    public void testToString() {
        assert "2.0 = x".equals(a.toString());
    }

    @Test
    public void testEquals() {
        assert a.equals(a2);
    }

    @Test
    public void testEval() {
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assert c.equals(ev.evaluate(a, vars));
    }
}