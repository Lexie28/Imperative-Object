package org.ioopm.calculator.ast;

public class FunctionCall extends SymbolicExpression{

    String identifier;
    Atom[] args;

    public FunctionCall(String name, ... args) {
        super(name);
        this.args = args;

    }



    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }


}
