package org.ioopm.calculator.ast;

public class LT extends Conditionals {

    public LT(SymbolicExpression lhs, SymbolicExpression rhs, SymbolicExpression ifstate, SymbolicExpression elsestate) {
        super(getName(), lhs, rhs, ifstate, elsestate);
    }

    /**
     * Accepts the visitor class to LT
     * @return the visited LT
     */
    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }

    /**
     * Used to get the name of the operation
     * @return the String representing this operation
     */
    public static String getName() {
        return "<";
    }
    
}
