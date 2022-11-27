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

    public String getIdentifier() {
        return identifier;
    }

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


    @Override
    public SymbolicExpression accept(Visitor v) {
        return new Constant(value);
    }

}
