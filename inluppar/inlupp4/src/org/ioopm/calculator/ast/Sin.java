package org.ioopm.calculator.ast;

public class Sin extends Unary {

 
    public Sin(SymbolicExpression expression)
    {
        super(expression);
    }

    /**
     * Used to get the name of the operation
     * @return the String representing this operation
     */
    public String getName() {
        return ("sin");
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
    return v.visit(this);
    }

}

