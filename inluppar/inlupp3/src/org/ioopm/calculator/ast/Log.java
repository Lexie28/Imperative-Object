package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class Log extends Unary {

    public Log(SymbolicExpression expression)
    {
        super(expression);
    }

    public String getName() {
        return ("log");
    }

    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression expression = this.expression.eval(vars);
        if (expression.isConstant()) {
            return new Constant(Math.log10(expression.getValue()));
        } else {
            return new Sin(expression);
        }
        }
}

