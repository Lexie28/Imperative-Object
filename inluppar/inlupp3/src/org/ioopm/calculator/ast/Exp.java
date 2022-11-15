package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class Exp extends Unary {

    public Exp(SymbolicExpression expression)
    {
        super(expression);
    }

    public String getName() {
        return ("exp");
    }
    
}
