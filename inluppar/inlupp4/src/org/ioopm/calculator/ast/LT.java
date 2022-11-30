package org.ioopm.calculator.ast;

public class LT extends Conditionals {

    public LT(SymbolicExpression lhs, SymbolicExpression rhs, SymbolicExpression ifstate, SymbolicExpression elsestate) {
        super(getName(), lhs, rhs, ifstate, elsestate);
        //TODO Auto-generated constructor stub
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }

    public static String getName() {
        return "<";
    }

    public String toString() {
        return ("if" + this.lhs + getName() + this.rhs + "{" + this.ifstate + "} else {" + this.elsestate + "}");
    }
    
}
