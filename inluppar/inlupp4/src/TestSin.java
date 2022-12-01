import org.ioopm.calculator.ast.*;

import org.junit.Test;

public class TestSin {
    Constant c1 = new Constant(0);
    Sin a = new Sin(c1); //=0
    Sin b = new Sin(c1);

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
        assert "sin".equals(Sin.getName());
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
        System.out.println(a.toString());
        assert "sin 0.0".equals(a.toString());
    }

    @Test
    public void testEquals() {
        assert a.equals(b);
    }

    @Test
    public void testEval() {
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assert c1.equals(ev.evaluate(a, vars));
    }
}