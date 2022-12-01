package org.ioopm.calculator.ast;

public class Scope extends Unary {
    SymbolicExpression expression; 
    public Scope(SymbolicExpression expression) {
        super(getName(), expression);
        this.expression = expression;
    }

    /**
     * Used to get the name of the operation
     * @return the String representing this operation
     */
    public static String getName() {
        return "scope";
    }

    /**
     * Accepts the visitor class to Scope
     * @return the visited Scope
     */
    @Override
    public SymbolicExpression accept(Visitor v) {
        
        return v.visit(this);
    }

    /**
     * Used to get the string version of this operation
     * @return the String representing this operation
     */
    public String toString() {
        return "{" + expression.toString() + "}";
    }

    
}
