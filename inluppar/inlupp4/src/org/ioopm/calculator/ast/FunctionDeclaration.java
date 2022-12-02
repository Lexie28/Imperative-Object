package org.ioopm.calculator.ast;

import java.util.ArrayList;

public class FunctionDeclaration extends SymbolicExpression {
    
    String identifier;
    ArrayList<SymbolicExpression> args;
    Sequence seq;

    public FunctionDeclaration(String name) {
        super(name);
        this.identifier = name;
        args = new ArrayList<>();
    }

    public void addArg(SymbolicExpression arg) {
        args.add(arg);
    }


    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }

    

}
