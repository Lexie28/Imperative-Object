package org.ioopm.calculator.ast;

public class Equals extends Conditionals{

    public Equals(SymbolicExpression lhs, SymbolicExpression rhs, SymbolicExpression ifstate, SymbolicExpression elsestate) {
        super(getName(), lhs, rhs, ifstate, elsestate);
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }

    public static String getName() {
        return "==";
    }
    
}
