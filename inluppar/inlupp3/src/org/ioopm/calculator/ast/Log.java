package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class Log extends Unary {

    public Log(SymbolicExpression expression)
    {
        super(expression);
    }

    public String getName() {
        return ("log");
    }
    
}

