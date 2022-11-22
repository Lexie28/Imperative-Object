package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class Exp extends Unary {

    public Exp(SymbolicExpression expression)
    {
        super(expression);
    }

    /**
     * Used to get the name of the operation
     * @return the String representing this operation
     */
    public String getName() {
        return ("exp");
   
    }
    
    /**
     * Used to evaluate an expression using a hash-table of variables
     * @param vars the environment vars to store the variables in
     * @return a symbolicexpression that has been evaluated
     */
    public SymbolicExpression eval(Environment vars) {
    SymbolicExpression expression = this.expression.eval(vars);
    if (expression.isConstant()) {
        return new Constant(Math.exp(expression.getValue()));
    } else {
        return new Exp(expression);
    }
    }
}
