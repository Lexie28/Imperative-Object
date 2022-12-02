package org.ioopm.calculator.ast;

public class FunctionDeclaration extends SymbolicExpression {
    
    String identifier;
    Variable[] args;
    Sequence seq;

    public FunctionDeclaration(String name,Sequence sequence, Variable... args ) {
        super(name);
        this.identifier = name;
        this.seq = sequence;
        this.args = args;
    }


    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }

    

}
