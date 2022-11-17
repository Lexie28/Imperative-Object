package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public abstract class Binary extends SymbolicExpression {
    public SymbolicExpression lhs;
    public SymbolicExpression rhs;

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


    public boolean equals(Object other) {
        if (other instanceof Binary) {
            return this.equals((Binary) other);
        } else {
            return false;
        }
    }

    public boolean equals(Binary other) {
        /// access a private field of other!
        boolean a =this.lhs == other.lhs;
        boolean b = this.rhs == other.rhs;
        boolean c = this.getName() == other.getName();
        if (a == true && b == true && c == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

