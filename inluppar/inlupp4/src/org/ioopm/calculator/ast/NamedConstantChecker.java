package org.ioopm.calculator.ast;

import java.util.ArrayList;


public class NamedConstantChecker implements Visitor {
    public ArrayList<SymbolicExpression> checkList = new ArrayList<SymbolicExpression>();

    /**
     *  to check whether an expression contains a named constant
     * @param topLevel the SymbolicExpression to be checked for named constants
     * @return a boolean showing whether it contains a named constant or not
     */
    public boolean check(SymbolicExpression topLevel) {
        topLevel.accept(this);
        
        return this.checkList.size() == 0;
    }

    /**
     * Checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the addition to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Addition n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        return n; // mayhaps ????
    }

    /**
     * checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the assignment to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Assignment n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        if (n.rhs.isNamedConstant()) {
            this.checkList.add(n);
            return n;
        }
        else {
            return n;
        }
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the constant to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Constant n) {
        return n;
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the Cos to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Cos n) {
        n.expression.accept(this);
        return n;
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the division to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Division n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        return n; // mayhaps ????
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the exponential to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Exp n) {
        n.expression.accept(this);
        return n;
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the logarithm to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Log n) {
        n.expression.accept(this);
        return n;
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the multiplication to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Multiplication n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        return n; // mayhaps ????
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the negation to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Negation n) {
        n.expression.accept(this);
        return n;
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the quit command to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Quit n) {
        throw new RuntimeException("no");
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the Sin to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Sin n) {
        n.expression.accept(this);
        return n;
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the subtraction to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Subtraction n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        return n; // mayhaps ????
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the variable to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Variable n) {
        return n;
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the vars command to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Vars n) {
        throw new RuntimeException("no");
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the clear command to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Clear n) {
        throw new RuntimeException("no");
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the scope to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Scope n) {
        n.expression.accept(this);
        return n;
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the equals to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Equals n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        return n;
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the greater than to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(GT n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        return n;
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the greater than or equals to, to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(GTE n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        return n;
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the less than to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(LT n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        return n;
    }

    /**
     *  checks the expression and when it finds an assignment, it will check that the variable being assigned is not a named constant
     * @param n the less than or equals to, to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(LTE n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        return n;
    }

    @Override
    public SymbolicExpression visit(End n) {
        throw new RuntimeException("end");
    }

    @Override
    public SymbolicExpression visit(FunctionDeclaration n) {
        throw new RuntimeException("n fd");
    }

    @Override
    public SymbolicExpression visit(FunctionCall n) {
        return n.accept(this);
    }

    @Override
    public SymbolicExpression visit(Sequence n) {
        SymbolicExpression result = n.expression.accept(this);
        if(n.next != null) {
            n.next.accept(this);
        }
        return result;
    }

}
