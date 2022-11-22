package org.ioopm.calculator.ast;

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

    /**
     * Used to evaluate an expression using a hash-table of variables
     * @param vars the environment vars to store the variables in
     * @return a symbolicexpression that has been evaluated
     */
    public SymbolicExpression eval(Environment vars) {
        return new Constant(value);
    }
}
