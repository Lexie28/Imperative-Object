package org.ioopm.calculator.ast;

public class GT extends Conditionals {

    public GT(SymbolicExpression lhs, SymbolicExpression rhs, SymbolicExpression ifstate, SymbolicExpression elsestate) {
        super(getName(), lhs, rhs, ifstate, elsestate);
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }

    public static String getName() {
        return ">";
    }

    
}
