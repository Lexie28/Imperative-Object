package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public abstract class Unary extends SymbolicExpression {
    private SymbolicExpression expression;

    public Unary(SymbolicExpression expression)
    {
        this.expression = expression;
    }

    public int getPriority() {
        return 150;
    }

    public String toString() {
        /// Note how the call to toString() is not necessary

        return this.getName() + " " + this.expression.toString();
    }
}
