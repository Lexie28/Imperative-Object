package src.org.ioopm.calculator.ast;

public class SyntaxErrorException extends RuntimeException {
    public SyntaxErrorException (String errormessage) {
        super(errormessage);
    }
    
}
