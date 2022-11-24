package org.ioopm.calculator.ast;

public class Log extends Unary {

    public Log(SymbolicExpression expression)
    {
        super(getName(), expression);
    }

    /**
     * Used to get the name of the operation
     * @return the String representing this operation
     */
    public static String getName() {
        return ("log");
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}

