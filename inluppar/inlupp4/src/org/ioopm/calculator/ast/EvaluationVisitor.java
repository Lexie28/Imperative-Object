package org.ioopm.calculator.ast;

public class EvaluationVisitor implements Visitor {

    private Environment env = null;

    public SymbolicExpression evaluate(SymbolicExpression topLevel, Environment env) {
        this.env = env;
        return topLevel.accept(this);
    }


    // This method gets called from Addition.accept(Visitor v) -- you should
    // be able to see from the eval() methods how these should behave (i.e., 
    // compare this method with your Addition::eval() and Symbolic.addition) 
    @Override
    public SymbolicExpression visit(Addition n) {
        // Visit the left hand side and right hand side subexpressions
        SymbolicExpression left = n.lhs.accept(this);
        SymbolicExpression right = n.rhs.accept(this);
        // When we come back here, the visitor has visited all subexpressions, 
        // meaning left and right point to newly created trees reduced to 
        // the extent possible (best case -- both are constants)

        // If subexpressions are fully evaluated, replace them in
        // the tree with a constant whose value is the sub of the
        // subexpressions, if not, simply construct a new addition
        // node from the new subexpressions
        if (left.isConstant() && right.isConstant()) {
            return new Constant(left.getValue() + right.getValue());
        } else {
            return new Addition(left, right);
        }
    }

    @Override
    public SymbolicExpression visit(Assignment n) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public SymbolicExpression visit(Constant n) {
        return new Constant(n.getValue());
    }

    @Override
    public SymbolicExpression visit(Cos n) {
        SymbolicExpression expression = n.expression.accept(this);
        if(expression.isConstant()) {
            return new Constant(Math.cos(expression.getValue()));
        } else {
            return new Cos(expression);
        }
    }

    @Override
    public SymbolicExpression visit(Division n) {
        SymbolicExpression left = n.lhs.accept(this);
        SymbolicExpression right = n.rhs.accept(this);

        if (left.isConstant() && right.isConstant()) {
            return new Constant(left.getValue() / right.getValue());
        } else {
            return new Division(left, right);
        }
    }

    @Override
    public SymbolicExpression visit(Exp n) {
        SymbolicExpression expression = n.expression.accept(this);
        if(expression.isConstant()) {
            return new Constant(Math.exp(expression.getValue()));
        } else {
            return new Exp(expression);
        }
    }

    @Override
    public SymbolicExpression visit(Log n) {
        SymbolicExpression expression = n.expression.accept(this);
        if(expression.isConstant()) {
            return new Constant(Math.log(expression.getValue()));
        } else {
            return new Log(expression);
        }
    }

    @Override
    public SymbolicExpression visit(Multiplication n) {
        SymbolicExpression left = n.lhs.accept(this);
        SymbolicExpression right = n.rhs.accept(this);

        if (left.isConstant() && right.isConstant()) {
            return new Constant(left.getValue() * right.getValue());
        } else {
            return new Multiplication(left, right);
        }
    }

    @Override
    public SymbolicExpression visit(Negation n) {
        SymbolicExpression expression = n.expression.accept(this);
        if(expression.isConstant()) {
            return new Constant(-expression.getValue());
        } else {
            return new Negation(expression);
        }
    }

    @Override
    public SymbolicExpression visit(Quit n) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public SymbolicExpression visit(Sin n) {
        SymbolicExpression expression = n.expression.accept(this);
        if(expression.isConstant()) {
            return new Constant(Math.sin(expression.getValue()));
        } else {
            return new Sin(expression);
        }
    }

    @Override
    public SymbolicExpression visit(Subtraction n) {
        SymbolicExpression left = n.lhs.accept(this);
        SymbolicExpression right = n.rhs.accept(this);

        if (left.isConstant() && right.isConstant()) {
            return new Constant(left.getValue() - right.getValue());
        } else {
            return new Subtraction(left, right);
        }
    }

    @Override
    public SymbolicExpression visit(Variable n) { // ????????????????????
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public SymbolicExpression visit(Vars n) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public SymbolicExpression visit(Clear n) {
        // TODO Auto-generated method stub
        return null;
    }
    
}
