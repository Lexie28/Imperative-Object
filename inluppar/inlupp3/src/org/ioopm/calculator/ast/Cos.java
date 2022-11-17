package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class Cos extends Unary {

    public Cos(SymbolicExpression expression)
    {
        super(expression);
    }

    public String getName() {
        return ("cos");
    }
    
    public SymbolicExpression eval(Environment vars) {
    SymbolicExpression expression = this.expression.eval(vars);
    if (expression.isConstant()) {
        return new Constant(Math.cos(expression.getValue()));
    } else {
        return new Cos(expression);
    }
    }
}

