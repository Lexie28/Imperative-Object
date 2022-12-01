package org.ioopm.calculator.ast;

public class CheckException extends RuntimeException {
    public SymbolicExpression expression;
    public CheckException (String errormessage, SymbolicExpression expression) {
        super(errormessage);
        this.expression = expression;
    }
    
}
