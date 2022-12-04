import org.ioopm.calculator.ast.*;

import org.junit.Test;


public class TestScope {
    Constant c1 = new Constant(2.0);
    Constant c2 = new Constant(3.0);
    Scope a = new Scope(c1);
    Scope a2 = new Scope(new Assignment(c1, new Variable("x")));

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
        assert "scope".equals(Scope.getName());
    }

    @Test
    public void testIsCommand() {
        assert false == a.isCommand();
    }

    @Test
    public void testPriority() {
        assert 150 == a.getPriority();
    }

    @Test
    public void testToString() {
        assert "{2.0}".equals(a.toString());
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
        assert c1.equals(ev.evaluate(a, vars, funcs));
        assert c1.equals(ev.evaluate(a2, vars, funcs));

    } 
}
