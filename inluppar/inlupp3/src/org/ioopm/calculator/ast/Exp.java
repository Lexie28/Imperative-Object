package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class Exp extends Unary {

    public Exp(SymbolicExpression expression)
    {
        super(expression);
    }

    public String getName() {
        return ("exp");
   
    }
    
    public SymbolicExpression eval() {
    SymbolicExpression expression = this.expression.eval();
    if (expression.isConstant()) {
        return new Constant(Math.exp(expression.getValue()));
    } else {
        return new Exp(expression);
    }
    }
}
