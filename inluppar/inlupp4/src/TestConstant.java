import org.ioopm.calculator.ast.*;

import org.junit.Test;


public class TestConstant {
    Constant c1 = new Constant(2.0);
    Constant c2 = new Constant(2.0);

    @Test 
    public void testGetValue() {
        assert 2.0 == c1.getValue();
    }

    @Test
    public void testIsConstant() {
        assert c1.isConstant() == true;
    }

    @Test
    public void testGetName() {
        try {
            Constant.getName();
            assert false;
        } catch(RuntimeException e) {
            assert true;
        }
    }

    @Test
    public void testIsCommand() {
        assert false == c1.isCommand();
    }

    @Test
    public void testPriority() {
        assert 200 == c1.getPriority();
    }

    @Test
    public void testToString() {
        assert "2.0".equals(c1.toString());
    }

    @Test
    public void testEquals() {
        assert c1.equals(c2);
    }

    @Test
    public void testEval() {
        Environment vars = new Environment();
        Environment funcs = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assert c1.equals(ev.evaluate(c2, vars, funcs));
    }
}

