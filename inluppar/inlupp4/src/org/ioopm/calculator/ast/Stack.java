package org.ioopm.calculator.ast;

import java.util.Set;

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

    @Override
    public Set<Variable> keySet() {
        return envStack.peek().keySet();
    }

    public Environment peek() {
        return envStack.peek();
    }

}
