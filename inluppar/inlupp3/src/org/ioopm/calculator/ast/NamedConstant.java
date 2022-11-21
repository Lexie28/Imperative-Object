package inluppar.inlupp3.src.org.ioopm.calculator.ast;

import java.util.HashMap;

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

    public boolean isNamedConstant() {
        return true;
    }


}
