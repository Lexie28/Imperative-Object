package org.ioopm.calculator.ast;

public class GTE extends Conditionals{

    public GTE(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
        //TODO Auto-generated constructor stub
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        // TODO Auto-generated method stub
        return null;
    }

    public static String getName() {
        return ">=";
    }
    
}
