package org.ioopm.calculator.ast;

import java.util.Iterator;

public class EvaluationVisitor implements Visitor {

    private Stack env = new Stack();
    Environment funcs;

    public SymbolicExpression evaluate(SymbolicExpression topLevel, Environment env, Environment funcs) {
        this.env.pushEnvironment(env);
        this.funcs = funcs;
        return topLevel.accept(this);
        
    }


    // This method gets called from Addition.accept(Visitor v) -- you should
    // be able to see from the eval() methods how these should behave (i.e., 
    // compare this method with your Addition::eval() and Symbolic.addition) 

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the addition to be visited
     * @return the visited symbolicexpression
     */
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

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the assignment to be visited
     * @return the visited symbolicexpression
     */
    @Override
    public SymbolicExpression visit(Assignment n) {
        SymbolicExpression left = n.lhs.accept(this);
        n.rhs.accept(this);

        if(n.rhs.isVariable() && !env.containsKeyInCurrent(n.rhs)) {
            env.put((Variable) n.rhs, left);

            return left;
        } else {
            throw new RuntimeException("Cannot assign to a non-variable");
        }

    }

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the constant to be visited
     * @return the visited symbolicexpression
     */
    @Override
    public SymbolicExpression visit(Constant n) {
        return new Constant(n.getValue());
    }

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the cos to be visited
     * @return the visited symbolicexpression
     */
    @Override
    public SymbolicExpression visit(Cos n) {
        SymbolicExpression expression = n.expression.accept(this);
        if(expression.isConstant()) {
            return new Constant(Math.cos(expression.getValue()));
        } else {
            return new Cos(expression);
        }
    }

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the division to be visited
     * @return the visited symbolicexpression
     */
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

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the exp to be visited
     * @return the visited symbolicexpression
     */
    @Override
    public SymbolicExpression visit(Exp n) {
        SymbolicExpression expression = n.expression.accept(this);
        if(expression.isConstant()) {
            return new Constant(Math.exp(expression.getValue()));
        } else {
            return new Exp(expression);
        }
    }

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the log to be visited
     * @return the visited symbolicexpression
     */
    @Override
    public SymbolicExpression visit(Log n) {
        SymbolicExpression expression = n.expression.accept(this);
        if(expression.isConstant()) {
            return new Constant(Math.log(expression.getValue()));
        } else {
            return new Log(expression);
        }
    }

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the multiplication to be visited
     * @return the visited symbolicexpression
     */
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

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the negation to be visited
     * @return the visited symbolicexpression
     */
    @Override
    public SymbolicExpression visit(Negation n) {
        SymbolicExpression expression = n.expression.accept(this);
        if(expression.isConstant()) {
            return new Constant(-expression.getValue());
        } else {
            return new Negation(expression);
        }
    }

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the quit command to be visited
     * @return the visited symbolicexpression
     */
    @Override
    public SymbolicExpression visit(Quit n) {
        throw new RuntimeException("Cannot evaluate a command");
    }

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the Sin to be visited
     * @return the visited symbolicexpression
     */
    @Override
    public SymbolicExpression visit(Sin n) {
        SymbolicExpression expression = n.expression.accept(this);
        if(expression.isConstant()) {
            return new Constant(Math.sin(expression.getValue()));
        } else {
            return new Sin(expression);
        }
    }

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the subtraction to be visited
     * @return the visited symbolicexpression
     */
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

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the variable to be visited
     * @return the visited symbolicexpression
     */
    @Override
    public SymbolicExpression visit(Variable n) {
        if(env.containsKey(n)) {
            return env.get(n);
        } else {
            return new Variable(n.toString());
        }
    }

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the vars command to be visited
     * @return the visited symbolicexpression
     */
    @Override
    public SymbolicExpression visit(Vars n) {
        n.accept(this);
        return n;
    }

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the clear command to be visited
     * @return the visited symbolicexpression
     */
    @Override
    public SymbolicExpression visit(Clear n) {
        throw new RuntimeException("Cannot evaluate a command");
    }

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the scope to be visited
     * @return the visited symbolicexpression
     */
    @Override
    public SymbolicExpression visit(Scope n) {
        env.pushEnvironment(new Environment());
        SymbolicExpression exp = n.expression.accept(this);
        env.popEnvironment();
        return exp;
    }

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the equals to be visited
     * @return the visited symbolicexpression
     */
    @Override
    public SymbolicExpression visit(Equals n) {
        SymbolicExpression left = n.lhs.accept(this);
        SymbolicExpression right = n.rhs.accept(this);

        if (left.equals(right)) {
            return n.ifstate.accept(this);
        }
        else
        {
            return n.elsestate.accept(this);
        }
    }

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the greater than to be visited
     * @return the visited symbolicexpression
     */
    @Override
    public SymbolicExpression visit(GT n) {
        SymbolicExpression left = n.lhs.accept(this);
        SymbolicExpression right = n.rhs.accept(this);

        if (left.isConstant() && right.isConstant())
        {
            if (((Constant) left).getValue() > ((Constant) right).getValue()) {
                return n.ifstate.accept(this);
            }
            else
            {
                return n.elsestate.accept(this);
            }
    }
    else {
        throw new RuntimeException("Could not compare");
    }
    }

    /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the greater than or equals to, to be visited
     * @return the visited symbolicexpression
     */
    @Override
    public SymbolicExpression visit(GTE n) {
        SymbolicExpression left = n.lhs.accept(this);
        SymbolicExpression right = n.rhs.accept(this);

        if (left.isConstant() && right.isConstant())
        {
            if (((Constant) left).getValue() >= ((Constant) right).getValue()) {
                return n.ifstate.accept(this);
            }
            else
            {
                return n.elsestate.accept(this);
            }
        }
        else {
            throw new RuntimeException("Could not compare");
        }
        }

        /**
     * Used to visit (and therefore evaluate) an expression
     * @param n the less than to be visited
     * @return the visited symbolicexpression
     */
    @Override
    public SymbolicExpression visit(LT n) {
        SymbolicExpression left = n.lhs.accept(this);
        SymbolicExpression right = n.rhs.accept(this);

        if (left.isConstant() && right.isConstant())
        {
            if (((Constant) left).getValue() < ((Constant) right).getValue()) {
                return n.ifstate.accept(this);
            }
            else
            {
                return n.elsestate.accept(this);
            }
    }
        else {
            throw new RuntimeException("Could not compare");
        }
}

/**
     * Used to visit (and therefore evaluate) an expression
     * @param n the less than or equals to, to be visited
     * @return the visited symbolicexpression
     */
    @Override
    public SymbolicExpression visit(LTE n) {
        SymbolicExpression left = n.lhs.accept(this);
        SymbolicExpression right = n.rhs.accept(this);

        if (left.isConstant() && right.isConstant())
        {
            if (((Constant) left).getValue() <= ((Constant) right).getValue()) {
                return n.ifstate.accept(this);
            }
            else
            {
                return n.elsestate.accept(this);
            }
    }
        else {
            throw new RuntimeException("Could not compare");
        }
    }

    @Override
    public SymbolicExpression visit(End n) {
        throw new RuntimeException("Cannot evaluate a command");
    }

    @Override
    public SymbolicExpression visit(FunctionDeclaration n) {
        throw new RuntimeException("no ");


    }

    @Override
    public SymbolicExpression visit(FunctionCall n) {
        env.pushEnvironment(new Environment());
        
        FunctionDeclaration fd = (FunctionDeclaration) funcs.get(new Variable(n.identifier));

        if(fd == null) {
            throw new RuntimeException("Function does not exist");
        }

        if(fd.args.size() > n.args.size()) {
            throw new RuntimeException("Function called with too few arguments. Expected " + fd.args.size() + ", got " + n.args.size());
        } else if(fd.args.size() < n.args.size()) {
            throw new RuntimeException("Function called with too many arguments. Expected " + fd.args.size() + ", got " + n.args.size());
        } else {

            for(int i = 0; i< fd.args.size(); i++) {
                new Assignment(n.args.get(i), fd.args.get(i)).accept(this);
            }

        }

        SymbolicExpression expression = n.seq.accept(this);

        env.popEnvironment();
        return expression;
    }

    @Override
    public SymbolicExpression visit(Sequence n) {
        SymbolicExpression result = n.expression.accept(this);
        if(n.next != null) {
            result = n.next.accept(this);
        }
        return result;
     }

}
