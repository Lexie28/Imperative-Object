package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class Sin extends Unary {
 
    public Sin(SymbolicExpression expression)
    {
        super(expression);
    }

    public String getName() {
        return ("sin");
    }
}
