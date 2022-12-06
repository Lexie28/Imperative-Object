import org.ioopm.calculator.ast.*;

import org.junit.Test;


public class TestNegation {
    Constant c = new Constant(2.0);
    Constant c1 = new Constant(-2);
    Negation n = new Negation(c);
    Negation n2 = new Negation(c);

    Constant c2 = new Constant(1);
    Constant c3 = new Constant(-1);
    Constant c4 = new Constant(-1);
    Negation n3 = new Negation(c2);

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
        assert n3.isConstant() == false;
    }

    @Test
    public void testGetName() {
        assert "-".equals(Negation.getName());
    }

    @Test
    public void testIsCommand() {
        assert false == n.isCommand();
        assert false == n3.isCommand();
    }

    @Test
    public void testPriority() {
        assert 150 == n.getPriority();
        assert 150 == n3.getPriority();
    }

    @Test
    public void testToString() {
        assert "- 2.0".equals(n.toString());
        assert "- 1.0".equals(n3.toString());
    }

    @Test
    public void testEquals() {
        assert n.equals(n2);
    }

    @Test
    public void testEval() {
        Environment vars = new Environment();
        Environment funcs = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assert c1.equals(ev.evaluate(n, vars, funcs));
    }

    @Test
    public void testEval2() {
        Environment vars = new Environment();
        Environment funcs = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assert c3.equals(ev.evaluate(n3, vars, funcs));
    }
}
