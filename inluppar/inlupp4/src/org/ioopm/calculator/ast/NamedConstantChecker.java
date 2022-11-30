package org.ioopm.calculator.ast;

import java.util.ArrayList;
import java.util.HashMap;


public class NamedConstantChecker implements Visitor {
    public ArrayList<SymbolicExpression> checkList = new ArrayList<SymbolicExpression>();

    public boolean check(SymbolicExpression topLevel) {
        topLevel.accept(this);
        
        return this.checkList.size() == 0;
    }

    @Override
    public SymbolicExpression visit(Addition n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        return n; // mayhaps ????
    }

    @Override
    public SymbolicExpression visit(Assignment n) {
        SymbolicExpression left = n.lhs.accept(this);
        n.rhs.accept(this);
        if (n.rhs.isNamedConstant()) {
            this.checkList.add(n);
            return n;
        }
        else {
            return n;
        }
    }

    @Override
    public SymbolicExpression visit(Constant n) {
        return n;
    }

    @Override
    public SymbolicExpression visit(Cos n) {
        n.expression.accept(this);
        return n;
    }

    @Override
    public SymbolicExpression visit(Division n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        return n; // mayhaps ????
    }

    @Override
    public SymbolicExpression visit(Exp n) {
        n.expression.accept(this);
        return n;
    }

    @Override
    public SymbolicExpression visit(Log n) {
        n.expression.accept(this);
        return n;
    }

    @Override
    public SymbolicExpression visit(Multiplication n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        return n; // mayhaps ????
    }

    @Override
    public SymbolicExpression visit(Negation n) {
        n.expression.accept(this);
        return n;
    }

    @Override
    public SymbolicExpression visit(Quit n) {
        throw new RuntimeException("no");
    }

    @Override
    public SymbolicExpression visit(Sin n) {
        n.expression.accept(this);
        return n;
    }

    @Override
    public SymbolicExpression visit(Subtraction n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        return n; // mayhaps ????
    }

    @Override
    public SymbolicExpression visit(Variable n) {
        return n;
    }

    @Override
    public SymbolicExpression visit(Vars n) {
        throw new RuntimeException("no");
    }

    @Override
    public SymbolicExpression visit(Clear n) {
        throw new RuntimeException("no");
    }

    @Override
    public SymbolicExpression visit(Scope n) {
        n.expression.accept(this);
        return n;
    }

    @Override
    public SymbolicExpression visit(Equals n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        return n;
    }

    @Override
    public SymbolicExpression visit(GT n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        return n;
    }

    @Override
    public SymbolicExpression visit(GTE n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        return n;
    }

    @Override
    public SymbolicExpression visit(LT n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        return n;
    }

    @Override
    public SymbolicExpression visit(LTE n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        return n;
    }

}
