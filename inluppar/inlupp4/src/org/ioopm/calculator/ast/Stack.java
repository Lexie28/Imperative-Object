package org.ioopm.calculator.ast;

import java.util.ListIterator;
import java.util.Set;

public class Stack extends Environment {
    
    java.util.ArrayList<Environment> envStack;

    public Stack() {
        envStack = new java.util.ArrayList<Environment>();
    }

    /**
     * traverses the stack in a logically correct and relevant order to return the value associated with Object o
     * @param n the Object o to look for in the stack
     * @return the gotten SymbolicExpression from the stack
     */
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

    /**
     * Adds a new set (variable and associated SymbolicExpression) to our stack
     * @param v the Variable to now store in the stack
     * @param e the expression associated with the variable to be stored in the stack
     * @return the SymbolicExpression being put
     */
    @Override
    public SymbolicExpression put(Variable v, SymbolicExpression e) {
        return envStack.get(envStack.size()-1).put(v, e);
    }



    /**
     * Checks whether our stack contains a certain key
     * @param o the object that is being looked up in the stack
     * @return a boolean indicating whether this specific key exists in the stack
     */
    @Override
    public boolean containsKey(Object o) {
        return this.get(o) != null;
    }

    /**
     * Checks whether the specific stack environment we are currently in contains a certain key
     * @param o the object that is being looked up
     * @return a boolean indicating whether this specific key exists in this specific environment
     */
    public boolean containsKeyInCurrent(Object o) {
        return envStack.get(envStack.size()-1).get(o) != null;
    }


    /**
     * Pushes a new environment onto our stack
     * @param vars the new environment to be added onto the stack
     */
    public void pushEnvironment(Environment vars) {
        envStack.add(vars);
    }

    /**
     * Pops/Removes the latest environment from our stack
     */
    public void popEnvironment() {
        envStack.remove(envStack.size()-1);
    }

    /**
     * Creates a set of keys existing in our stack (the latest environment)
     * @return a set of variables representing the keys in this environment
     */
    @Override
    public Set<Variable> keySet() {
        return envStack.get(envStack.size()-1).keySet();
    }

    /**
     * Peeks on the latest environment added to our stack
     * @return said environment
     */
    public Environment peek() {
        return envStack.get(envStack.size()-1);
    }

}
