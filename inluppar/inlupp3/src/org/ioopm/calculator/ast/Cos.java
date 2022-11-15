package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class Cos extends Unary {
    
    public Cos(SymbolicExpression expression)
    {
        super(expression);
    }

    public String getName() {
        return ("cos");
    }
    
}
