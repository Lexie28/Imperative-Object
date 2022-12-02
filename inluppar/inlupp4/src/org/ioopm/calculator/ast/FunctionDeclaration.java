package org.ioopm.calculator.ast;

import java.util.ArrayList;

public class FunctionDeclaration extends SymbolicExpression {
    
    String identifier;
    ArrayList<SymbolicExpression> args;
    Sequence seq;

    public FunctionDeclaration(String name) {
        super(name);
        this.identifier = name;
        this.args = new ArrayList<>();
    }

    public void addArg(SymbolicExpression arg) {
        this.args.add(arg);
    }

    public void addExpression(SymbolicExpression expression) {
        this.seq.add(expression);
    }

    public String getIdentifier() {
        return identifier;
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb
        .append("function ")
        .append(identifier)
        .append("(");
        for(SymbolicExpression s : args) {
            sb.append(s.toString());
            if(args.indexOf(s) != args.size()-1) {
                sb.append(", ");
            }
        }
        sb.append(")");
        return sb.toString();
    }


    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }

    

}
