package org.ioopm.calculator.ast;

public class Exp extends Unary {

    public Exp(SymbolicExpression expression)
    {
        super(expression);
    }

    /**
     * Used to get the name of the operation
     * @return the String representing this operation
     */
    public String getName() {
        return ("exp");
   
    }
    
    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
