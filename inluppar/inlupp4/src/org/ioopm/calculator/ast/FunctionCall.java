package org.ioopm.calculator.ast;

public class FunctionCall extends SymbolicExpression{

    String identifier;

    public FunctionCall(String name, Variable... args) {
        super(name);
    }



    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }


}
