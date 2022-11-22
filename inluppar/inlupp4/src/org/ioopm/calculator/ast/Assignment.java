package org.ioopm.calculator.ast;

public class Assignment extends Binary {
    public Assignment(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    /**
     * Used to get the name of the operation
     * @return the String representing this operation
     */
    public String getName(){
        return ("=");
    }

    /**
     * Used to evaluate an expression using a hash-table of variables
     * @param vars the environment vars to store the variables in
     * @return a symbolicexpression that has been evaluated
     */
    public SymbolicExpression eval(Environment vars)  {
        SymbolicExpression lhs = this.lhs.eval(vars);
        SymbolicExpression rhs = this.rhs;

        if (rhs.isNamedConstant())
        {
            throw new IllegalExpressionException("Error: cannot redefine named constant");
        }
        else{
            
            if(rhs.isVariable())
        {
            //rhs måste bli en variable. TODO är detta rätt sätt?
            vars.put((Variable) rhs, lhs);
            return lhs;
        }
        else
        {
            return new Assignment(lhs, rhs);
        }
        }
    }
    
}
