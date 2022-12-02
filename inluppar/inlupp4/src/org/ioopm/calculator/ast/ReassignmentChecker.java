package org.ioopm.calculator.ast;

import java.util.ArrayList;

public class ReassignmentChecker implements Visitor {

    public Stack stack = new Stack();
    public ArrayList<Variable> reassignmentList = new ArrayList<Variable>();

    public ReassignmentChecker() {
        stack.pushEnvironment(new Environment());
    }

    /**
     * Used to check so that a variable is not reassigned
     * @param topLevel the SymbolicExpression to be checked
     * @return a boolean showing whether a reassignment is in risk of occuring
     */
    public boolean check(SymbolicExpression topLevel) {
        topLevel.accept(this);
        
        return this.reassignmentList.size() == 0;
    }

    /**
     * Visits the expression to search for reassignments
     * @param n the assignment to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Assignment n) {
        SymbolicExpression left = n.lhs.accept(this);
        SymbolicExpression right = n.rhs.accept(this);
        if (n.rhs.isVariable() )  {
            if(this.stack.peek().containsKey((Variable) right)) {
                this.reassignmentList.add((Variable) right);
            } else {
                this.stack.put((Variable) right, left);
            }
        }

        return n;
    }

    /**
     * Visits the expression to search for reassignments
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
     * Visits the expression to search for reassignments
     * @param n the constant to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Constant n) {
        return n;
    }

    /**
     * Visits the expression to search for reassignments
     * @param n the Cos to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Cos n) {
        n.expression.accept(this);
        return n;
    }

    /**
     * Visits the expression to search for reassignments
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
     * Visits the expression to search for reassignments
     * @param n the exponential to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Exp n) {
        n.expression.accept(this);
        return n;
    }

    /**
     * Visits the expression to search for reassignments
     * @param n the logarithm to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Log n) {
        n.expression.accept(this);
        return n;
    }

    /**
     * Visits the expression to search for reassignments
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
     * Visits the expression to search for reassignments
     * @param n the negation to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Negation n) {
        n.expression.accept(this);
        return n;
    }

    /**
     * Visits the expression to search for reassignments
     * @param n the quit command to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Quit n) {
        throw new RuntimeException("no");
    }

    /**
     * Visits the expression to search for reassignments
     * @param n the Sin to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Sin n) {
        n.expression.accept(this);
        return n;
    }

    /**
     * Visits the expression to search for reassignments
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
     * Visits the expression to search for reassignments
     * @param n the variable to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Variable n) {
        return n;
    }

    /**
     * Visits the expression to search for reassignments
     * @param n the vars command to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Vars n) {
        throw new RuntimeException("no");
    }

    /**
     * Visits the expression to search for reassignments
     * @param n the clear command to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Clear n) {
        throw new RuntimeException("no");
    }

    /**
     * Visits the expression to search for reassignments
     * @param n the scope to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Scope n) {
        stack.pushEnvironment(new Environment());
        n.expression.accept(this);
        stack.popEnvironment();
        return n;
    }

    /**
     * Visits the expression to search for reassignments
     * @param n the GT to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(GT n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        n.ifstate.accept(this);
        n.elsestate.accept(this);
        return null;
    }

    /**
     * Visits the expression to search for reassignments
     * @param n the GTE to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(GTE n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        n.ifstate.accept(this);
        n.elsestate.accept(this);
        return null;
    }

    /**
     * Visits the expression to search for reassignments
     * @param n the LT to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(LT n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        n.ifstate.accept(this);
        n.elsestate.accept(this);
        return null;
    }

    /**
     * Visits the expression to search for reassignments
     * @param n the LTE to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(LTE n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        n.ifstate.accept(this);
        n.elsestate.accept(this);
        return null;
    }

    /**
     * Visits the expression to search for reassignments
     * @param n the equals to be visited in this capacity
     * @return the visited expression
     */
    @Override
    public SymbolicExpression visit(Equals n) {
        n.lhs.accept(this);
        n.rhs.accept(this);
        n.ifstate.accept(this);
        n.elsestate.accept(this);
        return null;
    }

    @Override
    public SymbolicExpression visit(End n) {
        throw new RuntimeException("Reassignment not defined for Commands");
    }

    @Override
    public SymbolicExpression visit(FunctionDeclaration n) {
        throw new RuntimeException("Reassignment not defined for FunctionDeclerations");
    }

    @Override
    public SymbolicExpression visit(FunctionCall n) {
        return n;
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
