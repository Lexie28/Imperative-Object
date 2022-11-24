package org.ioopm.calculator.ast;

import java.beans.Expression;

public class Negation extends Unary {
    
    public Negation(SymbolicExpression expression)
    {
        super(expression);
    }
    
    /**
     * Used to get the name of the operation
     * @return the String representing this operation
     */
    public String getName() {
        return ("-");
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }

}
