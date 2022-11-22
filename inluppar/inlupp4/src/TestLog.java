import org.ioopm.calculator.ast.*;

import org.junit.Test;


public class TestLog {
    Constant c = new Constant(2.0);
    Log n = new Log(c);
    Log n2 = new Log(c);

    @Test 
    public void testGetValue() {
        try{
            n.getValue();
            assert false;
        } catch (RuntimeException e) {
            assert true;
        }
    }

    @Test
    public void testIsConstant() {
        assert n.isConstant() == false;
    }

    @Test
    public void testGetName() {
        assert "log".equals(n.getName());
    }

    @Test
    public void testIsCommand() {
        assert false == n.isCommand();
    }

    @Test
    public void testPriority() {
        assert 150 == n.getPriority();
    }

    @Test
    public void testToString() {
        assert "log 2.0".equals(n.toString());
    }

    @Test
    public void testEquals() {
        assert n.equals(n2);
    }

    @Test
    public void testEval() {
        Environment vars = new Environment();
        assert Math.log(2.0) == n.eval(vars).getValue();
    }
}
