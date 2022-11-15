package inluppar.inlupp3.src.org.ioopm.calculator.ast; /// could place this in parser *for now*

public abstract class SymbolicExpression {
    
    public boolean isConstant() {
        return false;
    }

    public String getName() {
        throw new RuntimeException("getName() called on expression with no operator");
    }

    public int getPriority() {
        return 0;
    }

    public double getValue() {
        throw new RuntimeException("getValue() called on expression with no value");
    }
}