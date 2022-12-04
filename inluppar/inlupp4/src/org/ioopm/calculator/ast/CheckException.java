package org.ioopm.calculator.ast;

public class CheckException extends RuntimeException {
    public SymbolicExpression expression;
    
    /**
     * Used to create an exception
     * @param errormessage the errormessage to send
     * @param expression expression associated with the error
     */
    public CheckException (String errormessage, SymbolicExpression expression) {
        super(errormessage);
        this.expression = expression;
    }
    
}
