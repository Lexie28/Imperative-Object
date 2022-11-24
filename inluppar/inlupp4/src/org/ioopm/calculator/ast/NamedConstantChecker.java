package org.ioopm.calculator.ast;

import java.util.HashMap;

import org.junit.jupiter.api.Named;

public class NamedConstantChecker implements Visitor {

    private HashMap<String, SymbolicExpression> illegalNamedConstantReassignments;

    public NamedConstantChecker() {
        illegalNamedConstantReassignments = new HashMap<String, SymbolicExpression>();
    }

    public boolean check(SymbolicExpression topLevel) {
        topLevel.accept(this);
        if(illegalNamedConstantReassignments.isEmpty()) {
            return true;
        } else {
            return false;
        }
    }

    public String getCheckFlags() {
        String result = "Error, assignments to named constants:";
        for(String str : illegalNamedConstantReassignments.keySet()) {
            result += "\n" + illegalNamedConstantReassignments.get(str) + " = " + str;
        }
        return result;
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
}
