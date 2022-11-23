package org.ioopm.calculator.ast;

import java.beans.Expression;

public class Negation extends Unary {
    
    public Negation(SymbolicExpression expression)
    {
        super(expression);
    }
    
    /**
     * Used to get the name of the operation
     * @return the String representing this operation
     */
    public String getName() {
        return ("-");
    }

    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression rhs = super.expression.eval(vars);
        if(rhs.isConstant()) {
            return new Constant(-rhs.getValue());

        } else {
            return new Negation(rhs);
        }
    }

    
}
