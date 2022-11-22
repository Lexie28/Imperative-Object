package org.ioopm.calculator.ast;

public class Cos extends Unary {

    public Cos(SymbolicExpression expression)
    {
        super(expression);
    }

    /**
     * Used to get the name of this object
     * @return a String representing the name
     */
    public String getName() {
        return ("cos");
    }
    
    /**
     * Used to evaluate an expression using a hash-table of variables
     * @param vars the environment vars which stores the variables
     * @return a symbolicexpression that has been evaluated
     */
    public SymbolicExpression eval(Environment vars) {
    SymbolicExpression expression = this.expression.eval(vars);
    if (expression.isConstant()) {
        return new Constant(Math.cos(expression.getValue()));
    } else {
        return new Cos(expression);
    }
    }
}

