package org.ioopm.calculator.ast;

import java.util.Iterator;
import java.util.Set;

public class Stack extends Environment {
    
    java.util.Stack<Environment> envStack;

    public Stack() {
        envStack = new java.util.Stack<Environment>();
    }

    @Override
    public SymbolicExpression get(Object o) {
        Iterator<Environment> iter = envStack.iterator();
        while(iter.hasNext()) {
            Environment current = iter.next();
            if(current.containsKey(o)) {
                return current.get(o);
            } else {
                continue;
            }
        }
        return null;
    }

    @Override
    public SymbolicExpression put(Variable v, SymbolicExpression e) {
        return envStack.peek().put(v, e);
    }

    @Override
    public boolean containsKey(Object o) {
        return this.get(o) != null;
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
