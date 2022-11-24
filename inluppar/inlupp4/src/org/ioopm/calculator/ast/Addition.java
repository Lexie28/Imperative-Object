package org.ioopm.calculator.ast;

public class Addition extends Binary {
    
    public Addition(SymbolicExpression lhs, SymbolicExpression rhs){
        super(getName(), lhs, rhs);
    }

    /**
     * Used to get the name of the operation
     * @return the String representing this operation
     */
    public static String getName(){
        return ("+");
    }

    /**
     * Used to get the priority of the operation
     * @return the int representing the priority of this operation
     */
    public int getPriority() {
        return 50;
    }


    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
