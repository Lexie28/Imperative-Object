


package inluppar.inlupp3.src.org.ioopm.calculator.ast; /// could place this in parser *for now*
import java.util.HashMap;

public abstract class SymbolicExpression {
    
    public boolean isConstant() {
        return false;
    }

    public boolean isVariable() {
        return false;
    }

    public boolean isCommand() {
        return false;
    }

    public boolean isNamedConstant() {
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

    public String toString() {
        throw new RuntimeException("toString() called on expression with no value");
    }

    public SymbolicExpression eval(Environment vars) {
        throw new RuntimeException("eval() called on expression with no value");
    }
}