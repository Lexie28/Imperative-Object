import org.ioopm.calculator.ast.*;

import org.junit.Test;


public class TestExp {
    Constant c = new Constant(2.0);
    Constant c1 = new Constant(Math.exp(2.0));
    Exp n = new Exp(c);
    Exp n2 = new Exp(c);

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
        assert "exp".equals(Exp.getName());
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
        assert "exp 2.0".equals(n.toString());
    }

    @Test
    public void testEquals() {
        assert n.equals(n2);
    }

    @Test
    public void testEval() {
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assert c1.equals(ev.evaluate(n, vars));
    }
}
