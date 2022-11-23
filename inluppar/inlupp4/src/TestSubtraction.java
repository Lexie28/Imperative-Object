import org.ioopm.calculator.ast.*;

import org.junit.Test;

public class TestSubtraction {
    Constant c1 = new Constant(2.0);
    Constant c2 = new Constant(2.0);
    Subtraction a = new Subtraction(c1, c2);
    Subtraction a2 = new Subtraction(c2, c1);

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
        assert "-".equals(a.getName());
    }

    @Test
    public void testIsCommand() {
        assert false == a.isCommand();
    }

    @Test
    public void testPriority() {
        assert 50 == a.getPriority();
    }

    @Test
    public void testToString() {
        assert "2.0 - 2.0".equals(a.toString());
    }

    @Test
    public void testEquals() {
        assert a.equals(a2);
    }

    @Test
    public void testEval() {
        Environment vars = new Environment();
        assert 0.0 == a.eval(vars).getValue();
    }
}