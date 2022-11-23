package org.ioopm.calculator.ast; /// could place this in parser *for now*

public abstract class SymbolicExpression {
    
    /**
     * Used to determine if this is a constant
     * @return a boolean telling whether it is a constant or not
     */
    public boolean isConstant() {
        return false;
    }

    /**
     * Used to determine if this is a variable
     * @return a boolean telling whether it is a variable or not
     */
    public boolean isVariable() {
        return false;
    }

    /**
     * Used to determine if this is a command
     * @return a boolean telling whether it is a command or not
     */
    public boolean isCommand() {
        return false;
    }
    
    /**
     * Used to determine if this is a named constant
     * @return a boolean telling whether it is a named constant or not
     */
    public boolean isNamedConstant() {
        return false;
    }

    /**
     * Used to get the name of the operation
     * @return the String representing this operation
     */
    public String getName() {
        throw new RuntimeException("getName() called on expression with no operator");
    }

    /**
     * Used to get the priority of the operation
     * @return the int representing the priority of this operation
     */
    public int getPriority() {
        return 0;
    }

    /**
     * Used to get the value of the operation
     * @return the double representing the priority of this operation
     */
    public double getValue() {
        throw new RuntimeException("getValue() called on expression with no value");
    }

    /**
     * Used to get the string version of this operation
     * @return the String representing this operation
     */
    public String toString() {
        throw new RuntimeException("toString() called on expression with no value");
    }

    public abstract SymbolicExpression accept(Visitor v);
    
}