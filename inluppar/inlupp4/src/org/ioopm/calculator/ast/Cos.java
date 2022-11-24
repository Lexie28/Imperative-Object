package org.ioopm.calculator.ast;

public class Cos extends Unary {

    public Cos(SymbolicExpression expression)
    {
        super(getName(), expression);
    }

    /**
     * Used to get the name of this object
     * @return a String representing the name
     */
    public static String getName() {
        return ("cos");
    }
    
    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}

