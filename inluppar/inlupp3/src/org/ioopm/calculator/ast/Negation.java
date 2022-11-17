package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class Negation extends Unary {
    
    public Negation(SymbolicExpression expression)
    {
        super(expression);
    }

    public String getName() {
        return ("-");
    }

    
}
