package org.ioopm.calculator.ast;

import java.util.LinkedList;

public class Sequence extends SymbolicExpression {

    public LinkedList<SymbolicExpression> expressionsList;


    public Sequence(String name, Object[] subExpressions) {
        super(name, subExpressions);
        expressionsList = new LinkedList<>();
    }

    public void add(SymbolicExpression expression) {
        expressionsList.add(expression);
    }


    @Override
    public SymbolicExpression accept(Visitor v) {
        // TODO Auto-generated method stub
        return null;
    }
    
}
