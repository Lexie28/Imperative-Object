package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public abstract class Binary extends SymbolicExpression {
    private SymbolicExpression lhs;
    private SymbolicExpression rhs;

    public Binary(SymbolicExpression lhs, SymbolicExpression rhs) {
        this.lhs = lhs;
        this.rhs = rhs;
    }

    public String toString() {
        /// Note how the call to toString() is not necessary
        String lhsString = this.lhs.toString();
        String rhsString = this.rhs.toString();
        if (this.lhs.getPriority() < this.getPriority()) {
            lhsString = "(" + lhsString + ")";
        }
        if (this.rhs.getPriority() < this.getPriority()) {
            rhsString = "(" + rhsString + ")";
        }
        return lhsString + " " + this.getName() + " " + rhsString;
    }
}

