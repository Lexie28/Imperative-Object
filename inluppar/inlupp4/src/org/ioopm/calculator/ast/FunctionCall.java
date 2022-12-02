package org.ioopm.calculator.ast;

import java.util.ArrayList;

public class FunctionCall extends SymbolicExpression{

    String identifier;
    ArrayList<SymbolicExpression> args;
    Sequence seq;

    public FunctionCall(String name, Sequence sequence) {
        super(name);
        args = new ArrayList<>();
        this.seq = sequence;
    }

    public void addArg(SymbolicExpression arg) {
        args.add(arg);
    }


    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(seq);
    }


}
