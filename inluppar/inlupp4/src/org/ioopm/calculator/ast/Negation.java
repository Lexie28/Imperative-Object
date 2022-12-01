package org.ioopm.calculator.ast;

public class Negation extends Unary {
    
    public Negation(SymbolicExpression expression)
    {
        super(getName(), expression);
    }
    
    /**
     * Used to get the name of the operation
     * @return the String representing this operation
     */
    public static String getName() {
        return ("-");
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }

}
