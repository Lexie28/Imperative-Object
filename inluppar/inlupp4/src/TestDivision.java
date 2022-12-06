import org.ioopm.calculator.ast.*;

import org.junit.Test;

public class TestDivision {
    Constant c1 = new Constant(2.0);
    Constant c2 = new Constant(2.0);
    Constant c3 = new Constant(1);
    Division a = new Division(c1, c2);
    Division a2 = new Division(c2, c1);

    Constant c4 = new Constant(10.0);
    Constant c5 = new Constant(5.0);
    Constant c6 = new Constant(2.0);
    Division a3 = new Division(c4, c5);

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
        assert false == a3.isConstant();
    }

    @Test
    public void testGetName() {
        assert "/".equals(Division.getName());
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
        assert "2.0 / 2.0".equals(a.toString());
        assert "10.0 / 5.0".equals(a3.toString());
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