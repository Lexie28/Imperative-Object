import org.ioopm.calculator.ast.*;

import org.junit.Test;


public class TestGTE {
    Constant c1 = new Constant(2.0);
    Constant c2 = new Constant(3.0);
    GTE a = new GTE(c2, c1, c2, c1);
    GTE a2 = new GTE(c1, c2, c1, c2);

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
        assert ">=".equals(GTE.getName());
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
        assert "if3.0>=2.03.0 else 2.0".equals(a.toString());
    }

    @Test
    public void testEquals() {
        assert !a.equals(a2);
    }

    @Test
    public void testEval() {
        Environment vars = new Environment();
        Environment funcs = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assert c2.equals(ev.evaluate(a, vars, funcs));

    }   
}
