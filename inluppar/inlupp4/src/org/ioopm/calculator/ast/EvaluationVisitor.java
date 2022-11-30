package org.ioopm.calculator.ast;

public class EvaluationVisitor implements Visitor {

    private Stack env = new Stack();

    public SymbolicExpression evaluate(SymbolicExpression topLevel, Environment env) {
        this.env.pushEnvironment(env);
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
        SymbolicExpression left = n.lhs.accept(this);
        SymbolicExpression right = n.rhs.accept(this);
        /* if(right.isNamedConstant()) {
            throw new RuntimeException("Cannot redefine a named constant");
        } else */ 
        if(right.isVariable() && !env.containsKey(right)) {
            env.put((Variable) right, left);

            return left;
        } else {
            throw new RuntimeException("Cannot assign to a non-variable");
        }
        /* else if(right.isVariable() && env.containsKey((Variable) right)) { // May have to remove this case
            throw new RuntimeException("Cannot redefine a variable");
        } else {
            throw new RuntimeException("Cannot assign to a non-variable");
        } */

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
        throw new RuntimeException("Cannot evaluate a command");
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
    public SymbolicExpression visit(Variable n) {
        if(env.containsKey(n)) {
            return env.get(n);
        } else {
            return new Variable(n.toString());
        }
    }

    @Override
    public SymbolicExpression visit(Vars n) {
        n.accept(this);
        return n;
    }

    @Override
    public SymbolicExpression visit(Clear n) {
        throw new RuntimeException("Cannot evaluate a command");
    }

    @Override
    public SymbolicExpression visit(Scope n) {
        env.pushEnvironment(new Environment());
        SymbolicExpression exp = n.expression.accept(this);
        env.popEnvironment();
        return exp;
    }

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

}
