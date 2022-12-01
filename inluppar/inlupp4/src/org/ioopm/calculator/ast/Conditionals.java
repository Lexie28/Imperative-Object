package org.ioopm.calculator.ast;

public abstract class Conditionals extends Binary {
    public SymbolicExpression ifstate;
    public SymbolicExpression elsestate;

    public Conditionals(String name, SymbolicExpression lhs, SymbolicExpression rhs, SymbolicExpression ifstate, SymbolicExpression elsestate) {
        super(name, lhs, rhs);
        this.ifstate = ifstate;
        this.elsestate = elsestate;
    }

    /**
     * Used to get the string version of this operation
     * @return the String representing this operation
     */
    public String toString() {
        return ("if" + this.lhs + name + this.rhs + this.ifstate +  " else " + this.elsestate);
    }
    

    
}