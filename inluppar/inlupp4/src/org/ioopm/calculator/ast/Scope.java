package org.ioopm.calculator.ast;

public class Scope extends Unary {
    SymbolicExpression expression; 
    public Scope(SymbolicExpression expression) {
        super(getName(), expression);
        this.expression = expression;
    }

    public static String getName() {
        return "scope";
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        
        return v.visit(this);
    }
}
