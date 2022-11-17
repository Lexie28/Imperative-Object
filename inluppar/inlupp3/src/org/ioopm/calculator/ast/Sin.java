package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class Sin extends Unary {

 
    public Sin(SymbolicExpression expression)
    {
        super(expression);
    }

    public String getName() {
        return ("sin");
    }

    public SymbolicExpression eval(HashMap<Variable, SymbolicExpression> vars) {
    SymbolicExpression expression = this.expression.eval();
    if (expression.isConstant()) {
        return new Constant(Math.sin(expression.getValue()));
    } else {
        return new Sin(expression);
    }
    }
}

