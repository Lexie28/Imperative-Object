package org.ioopm.calculator.ast;

public class SyntaxErrorException extends RuntimeException {
    
    /**
     * Used to create an exception
     * @param errormessage the errormessage to send
     */
    public SyntaxErrorException (String errormessage) {
        super(errormessage);
    }
    
}
