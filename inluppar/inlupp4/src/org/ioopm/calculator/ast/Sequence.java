package org.ioopm.calculator.ast;

public class Sequence extends SymbolicExpression {

    public SymbolicExpression expression;
    public Sequence next;


    public Sequence(String name, SymbolicExpression expression) {
        super(name);
        this.expression = expression;
    }

    /**
     * Used to add an expression to the sequence
     * @param expression the expression to be added to the sequence
     */
    public void add(SymbolicExpression expression) {
        if(this.next == null) {
            next = new Sequence(name, expression);
        } else {
            next.add(expression);
        }
    }


    /**
     * Accepts the visitor class to sequence
     * @return the visited sequence
     */
    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
    
}
