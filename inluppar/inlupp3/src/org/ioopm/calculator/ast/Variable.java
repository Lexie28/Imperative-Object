package inluppar.inlupp3.src.org.ioopm.calculator.ast;
import java.util.HashMap;

public class Variable extends Atom {
    private String identifier;

    public Variable(String identifier)
    {
        this.identifier = identifier;
    }

    public String toString() {
        return this.identifier;
    }

    public boolean equals(Object other) {
        if (other instanceof Variable) {
            return this.equals((Variable) other);
        } 
        else {
            return false;
        }
        }
    
    public boolean equals(Variable other) {
        /// access a private field of other!
        return this.identifier == other.identifier;
    }
    
    public SymbolicExpression eval(HashMap<Variable, SymbolicExpression> vars) {
        Variable key = new Variable(this.identifier);

        if (vars.containsKey(key)) //om vårt hashtable containar vår variable
        {
            return vars.get(key);
        }
        else
        {
        return new Variable(identifier);
        }
    }
}
