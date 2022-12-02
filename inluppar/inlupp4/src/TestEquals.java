import org.ioopm.calculator.ast.*;

import org.junit.Test;


public class TestEquals {
    Constant c1 = new Constant(2.0);
    Constant c2 = new Constant(3.0);
    Equals a = new Equals(c2, c1, c2, c1);
    Equals a2 = new Equals(c1, c2, c1, c2);
    Equals a3 = new Equals(c1, c1, c1, c2);

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
        assert "==".equals(Equals.getName());
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
        assert "if3.0==2.03.0 else 2.0".equals(a.toString());
    }

    @Test
    public void testEquals() {
        assert !a.equals(a2);
    }

    @Test
    public void testEval() {
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        System.out.println(ev.evaluate(a, vars).toString());
        assert c1.equals(ev.evaluate(a, vars));
        assert c1.equals(ev.evaluate(a3, vars));

    }   
}
