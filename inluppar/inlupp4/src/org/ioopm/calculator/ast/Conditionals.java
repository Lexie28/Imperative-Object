package org.ioopm.calculator.ast;

public abstract class Conditionals extends Binary {
    public SymbolicExpression ifstate;
    public SymbolicExpression elsestate;

    public Conditionals(String name, SymbolicExpression lhs, SymbolicExpression rhs, SymbolicExpression ifstate, SymbolicExpression elsestate) {
        super(getName(), lhs, rhs);
    }

    public String toString() {
        return ("if" + this.lhs + getName() + this.rhs + "{" + this.ifstate + "} else {" + this.elsestate + "}");
    }

    
}