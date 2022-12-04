package org.ioopm.calculator.ast;

import java.util.ArrayList;

public class FunctionCall extends SymbolicExpression{

    String identifier;
    ArrayList<SymbolicExpression> args;
    Sequence seq;

    public FunctionCall(String name, Sequence sequence) {
        super(name);
        this.identifier = name;
        args = new ArrayList<>();
        this.seq = sequence;
    }

    /**
     * Used to add arguments to the function call list
     * @param arg the argument to be added to this list
     */
    public void addArg(SymbolicExpression arg) {
        args.add(arg);
    }


    /**
     * Accepts the visitor class to function call
     * @return the visited function call
     */
    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }


}
