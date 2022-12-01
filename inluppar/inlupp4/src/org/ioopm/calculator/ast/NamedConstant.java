package org.ioopm.calculator.ast;

public class NamedConstant extends Atom {
    private String identifier;
    private double value;

    public NamedConstant(String identifier, double value) {
        super(identifier);
        this.identifier = identifier;
        if (Constants.namedConstants.containsKey(identifier)) {
            this.value = Constants.namedConstants.get(identifier);
        }
        else
        {
            throw new IllegalExpressionException(identifier + "is not a named constant");
        }
    }

    /**
     * Used to get the string version of the identifier used in this operation
     * @return the String representing this identifier
     */
    public String getIdentifier() {
        return identifier;
    }

    /**
     * Used to get the string version of this operation
     * @return the String representing this operation
     */
    public String toString() {
        return this.identifier;
    }

    /**
     * Used to determine if this is a constant
     * @return a boolean telling whether it is a contant or not
     */
    public boolean isNamedConstant() {
        return true;
    }


    /**
     * Accepts the visitor class to NamedConstant
     * @return the visited NamedConstant
     */
    @Override
    public SymbolicExpression accept(Visitor v) {
        return new Constant(value);
    }

}
