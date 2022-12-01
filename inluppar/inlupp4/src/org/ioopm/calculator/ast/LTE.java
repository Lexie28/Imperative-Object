package org.ioopm.calculator.ast;

public class LTE extends Conditionals{

    public LTE(SymbolicExpression lhs, SymbolicExpression rhs, SymbolicExpression ifstate, SymbolicExpression elsestate) {
        super(getName(), lhs, rhs, ifstate, elsestate);
    }

    /**
     * Accepts the visitor class to LTE
     * @return the visited LTE
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
        return "<=";
    }
}
