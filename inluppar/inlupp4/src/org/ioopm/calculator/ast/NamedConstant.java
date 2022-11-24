package org.ioopm.calculator.ast;

import javax.management.RuntimeErrorException;

public class NamedConstant extends Atom {
    private String identifier;
    private double value;

    public NamedConstant(String identifier, double value) {
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
