package org.ioopm.calculator.ast;

import java.beans.Expression;

public class CheckException extends RuntimeException {
    public SymbolicExpression expression;
    public CheckException (String errormessage, SymbolicExpression expression) {
        super(errormessage);
        this.expression = expression;
    }
    
}
