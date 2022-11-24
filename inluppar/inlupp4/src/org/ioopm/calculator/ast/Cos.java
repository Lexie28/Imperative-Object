package org.ioopm.calculator.ast;

public class Cos extends Unary {

    public Cos(SymbolicExpression expression)
    {
        super(expression);
    }

    /**
     * Used to get the name of this object
     * @return a String representing the name
     */
    public String getName() {
        return ("cos");
    }
    
    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}

