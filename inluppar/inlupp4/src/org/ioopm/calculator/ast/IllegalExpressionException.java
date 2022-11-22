package src.org.ioopm.calculator.ast;

public class IllegalExpressionException extends RuntimeException {
    
    /**
     * Used to create an exception
     * @param errormessage the errormessage to send
     */
    public IllegalExpressionException (String errormessage) {
        super(errormessage);
    }
}
