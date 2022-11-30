package org.ioopm.calculator.ast;

import java.util.Collections;
import java.util.Iterator;
import java.util.ListIterator;
import java.util.Set;

public class Stack extends Environment {
    
    java.util.ArrayList<Environment> envStack;

    public Stack() {
        envStack = new java.util.ArrayList<Environment>();
    }

    @Override
    public SymbolicExpression get(Object o) {
        ListIterator<Environment> iter = envStack.listIterator(envStack.size());
        while(iter.hasPrevious()) {
            Environment current = iter.previous();
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
        return envStack.get(envStack.size()-1).put(v, e);
    }

    @Override
    public boolean containsKey(Object o) {
        return this.get(o) != null;
    }

    public boolean containsKeyInCurrent(Object o) {
        return envStack.get(envStack.size()-1).get(o) != null;
    }


    public void pushEnvironment(Environment vars) {
        envStack.add(vars);
    }

    public void popEnvironment() {
        envStack.remove(envStack.size()-1);
    }

    @Override
    public Set<Variable> keySet() {
        return envStack.get(envStack.size()-1).keySet();
    }

    public Environment peek() {
        return envStack.get(envStack.size()-1);
    }

}
