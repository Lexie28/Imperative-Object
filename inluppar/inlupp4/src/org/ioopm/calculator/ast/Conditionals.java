package org.ioopm.calculator.ast;

public class Conditionals extends SymbolicExpression {
    public SymbolicExpression lhsexp;
    public SymbolicExpression rhsexp;
    public String op;
    public SymbolicExpression ifstate;
    public SymbolicExpression elsestate;

    public ArrayList<String> operationslist = 

    public Conditionals(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(getName(), lhs, rhs);
        this.lhsexp = lhs;
        this.rhsexp = rhs;
    }

    public static String getName() {
        return "conditionals";
    }

    public String toString() {
        return ("if" + this.lhs + this.op + "{" + this.ifstate + "} else {" this.elsestate + "}");
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }

    
}
