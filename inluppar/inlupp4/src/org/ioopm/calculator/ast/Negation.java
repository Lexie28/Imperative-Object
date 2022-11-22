package org.ioopm.calculator.ast;

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

    
}
