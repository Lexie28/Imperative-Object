package org.ioopm.calculator.ast;

import java.util.ArrayList;

public class FunctionDeclaration extends SymbolicExpression {
    
    String identifier;
    ArrayList<SymbolicExpression> args;
    public Sequence seq;

    public FunctionDeclaration(String name) {
        super(name);
        this.identifier = name;
        this.args = new ArrayList<>();
    }

    /**
     * Used to add arguments to the function declaration list
     * @param arg the argument to be added to this list
     */
    public void addArg(SymbolicExpression arg) {
        this.args.add(arg);
    }


    /**
     * Used to add an expression to the function declaration sequence
     * @param expression the expression to be added to the sequence
     */
    public void addExpression(SymbolicExpression expression) {
        if(this.seq == null) {
            this.seq = new Sequence(name, expression);
        } else {
            this.seq.add(expression);
        }
        
    }

    /**
     * Used get the identifier of the function declaration
     * @return a String representing the identifier of the function declaration
     */
    public String getIdentifier() {
        return identifier;
    }

    /**
     * Used to get the string version of this operation
     * @return the String representing this operation
     */
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


    /**
     * Accepts the visitor class to function declaration
     * @return the visited Function Declaration
     */
    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }

    

}
