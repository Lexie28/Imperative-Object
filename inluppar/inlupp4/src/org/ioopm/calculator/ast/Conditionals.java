package org.ioopm.calculator.ast;

public abstract class Conditionals extends Binary {
    public SymbolicExpression lhsexp;
    public SymbolicExpression rhsexp;
    public String op;
    public SymbolicExpression ifstate;
    public SymbolicExpression elsestate;

    public Conditionals(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(getName(), lhs, rhs);
        this.lhsexp = lhs;
        this.rhsexp = rhs;
    }

    public static String getName() {
        return "conditionals";
    }

    public String toString() {
        return ("if" + this.lhs + this.op + this.rhs + "{" + this.ifstate + "} else {" + this.elsestate + "}");
    }

    
}
