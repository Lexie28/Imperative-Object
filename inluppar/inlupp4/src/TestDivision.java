import org.ioopm.calculator.ast.*;

import org.junit.Test;

public class TestDivision {
    Constant c1 = new Constant(2.0);
    Constant c2 = new Constant(2.0);
    Division a = new Division(c1, c2);
    Division a2 = new Division(c2, c1);

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
        assert "/".equals(a.getName());
    }

    @Test
    public void testIsCommand() {
        assert false == a.isCommand();
    }

    @Test
    public void testPriority() {
        assert 100 == a.getPriority();
    }

    @Test
    public void testToString() {
        assert "2.0 / 2.0".equals(a.toString());
    }

    @Test
    public void testEquals() {
        assert a.equals(a2);
    }

    @Test
    public void testEval() {
        Environment vars = new Environment();
        assert 1.0 == a.eval(vars).getValue();
    }
}