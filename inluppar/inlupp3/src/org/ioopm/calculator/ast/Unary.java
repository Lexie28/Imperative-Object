package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public abstract class Unary extends SymbolicExpression {
    public SymbolicExpression expression;

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

    public boolean equals(Object other) {
        if (other instanceof Unary) {
            return this.equals((Unary) other);
        } else {
            return false;
        }
    }

    public boolean equals(Unary other) {
        boolean a = this.getName() == other.getName();
        boolean b = this.expression == other.expression;
        if(a == true && b == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
