package inluppar.inlupp3.src.org.ioopm.calculator.ast;
import java.util.HashMap;

public class Variable extends Atom {
    private String identifier;

    public Variable(String identifier)
    {
        this.identifier = identifier;
    }

    public boolean isVariable() {
        return true;
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
        return this.identifier.equals(other.identifier);
    }

    @Override
    public int hashCode() {
        return this.identifier.hashCode();
    }
    
    public SymbolicExpression eval(Environment vars) {
        if (vars.containsKey(this)) //om vårt hashtable containar vår variable
        {
            return vars.get(this);
        }
        else
        {
            return this;
        }
    }
}
