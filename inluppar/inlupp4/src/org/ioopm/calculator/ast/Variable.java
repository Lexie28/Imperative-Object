package org.ioopm.calculator.ast;

public class Variable extends Atom implements Comparable<Variable> {
    private String identifier;


    /**
    * Used to display variable
    * @param identifier string representation of variable
    * @return string representation of variable
    */
    public Variable(String identifier)
    {
        super(identifier);
        this.identifier = identifier;
    }

    /**
    * Checks if it is a variable
    * @return true or false depending on whether it is a variable or not
    */
    public boolean isVariable() {
        return true;
    }

    /**
    * Converts the variable into a string representation
    * @return a string representation of the variable
    */
    public String toString() {
        return this.identifier;
    }

    /**
    * checks if two variables are equal or not
    * @param other object that vill be compared against
    * @return true or false depending on if veriables are equal or not
    */
    public boolean equals(Object other) {
        if (other instanceof Variable) {
            return this.equals((Variable) other);
        } 
        else {
            return false;
        }
        }
    

    /**
    * checks if two string representations of variables are equal
    * @param other object that vill be compared against
    * @return returns true or false depending on if string representations are equal
    */
    public boolean equals(Variable other) {
        /// access a private field of other!
        return this.identifier.equals(other.identifier);
    }

    /**
    * assignes a hashCode value to identifier
    * @return returns an integer representing the hash code value
    */
    @Override
    public int hashCode() {
        return this.identifier.hashCode();
    }


    /**
     * Accepts the visitor class to Variable
     * @return the visited Variable
     */
    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }

    /**
     * Compares two different variables
     * @param v the variable to be compared against
     * @return an int, if 0, the two strings are equal, otherwise they are not
     */
    @Override
    public int compareTo(Variable v) {
        return this.identifier.compareTo(v.identifier);
    }

    
}
