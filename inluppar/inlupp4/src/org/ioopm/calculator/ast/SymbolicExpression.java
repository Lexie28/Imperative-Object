package org.ioopm.calculator.ast; /// could place this in parser *for now*

public abstract class SymbolicExpression {

    private String name; 
    private String[] subExpressions;
    /// The second argument allows us to pass in 0 or more arguments
    public SymbolicExpression(String name, Object... subExpressions) {
        this.name = name;
        this.subExpressions = new String[subExpressions.length];
        for (int i = 0; i < subExpressions.length; ++i) {
            this.subExpressions[i] = subExpressions[i].toString();
        }
    }

    /// Returns e.g., "Constant(42)" if name is "Constant" and subExpressions is ["42"]
    public String toString(String msg) {
        StringBuilder sb = new StringBuilder();
        sb.append(this.name);
        sb.append("(");
        for (int i = 1; i < this.subExpressions.length; ++i) {
            sb.append(this.subExpressions[i]);
            if (i + 1 < subExpressions.length) {
                sb.append(", ");
            }
        }
        sb.append(")");
        return sb.toString(); 
    }
    
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
    public static String getName() {
        try {
            throw new RuntimeException("getName() called on expression with no operator");

        } catch(Throwable e) {
            e.printStackTrace();
            return null;
        }
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

    public abstract SymbolicExpression accept(Visitor v);
    
}