package org.ioopm.calculator.ast;

public class Assignment extends Binary {
    public Assignment(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(getName(), lhs, rhs);
    }

    /**
     * Used to get the name of the operation
     * @return the String representing this operation
     */
    public static String getName(){
        return "=";
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }

    
}
