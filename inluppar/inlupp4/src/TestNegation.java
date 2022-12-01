import org.ioopm.calculator.ast.*;

import org.junit.Test;


public class TestNegation {
    Constant c = new Constant(2.0);
    Constant c1 = new Constant(-2);
    Negation n = new Negation(c);
    Negation n2 = new Negation(c);

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
        assert "-".equals(Negation.getName());
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
        System.out.println(n.toString());
        assert "- 2.0".equals(n.toString());
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
