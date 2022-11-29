package org.ioopm.calculator.ast;

public class Stack extends Environment {
    
    java.util.Stack<Environment> envStack;

    public Stack() {
        envStack = new java.util.Stack<Environment>();
    }

    @Override
    public SymbolicExpression get(Object o) {
        return envStack.peek().get(o);
    }

    @Override
    public SymbolicExpression put(Variable v, SymbolicExpression e) {
        return envStack.peek().put(v, e);
    }

    public void pushEnvironment(Environment vars) {
        envStack.push(vars);
    }

    public void popEnvironment() {
        envStack.pop();
    }
}
