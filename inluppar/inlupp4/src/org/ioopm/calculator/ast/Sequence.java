package org.ioopm.calculator.ast;

public class Sequence extends SymbolicExpression {

    public SymbolicExpression expression;
    public Sequence next;


    public Sequence(String name, SymbolicExpression expression) {
        super(name);
        this.expression = expression;
    }

    public void add(SymbolicExpression expression) {
        if(this.next == null) {
            next = new Sequence(name, expression);
        } else {
            next.add(expression);
        }
    }


    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
    
}
