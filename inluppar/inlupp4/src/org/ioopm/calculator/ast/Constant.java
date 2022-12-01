package org.ioopm.calculator.ast;

public class Constant extends Atom {
    private double value;

    public Constant(double value)
    {
        super("Constant");
        this.value = value;
    }



    /**
     * Used to determine if this is a constant
     * @return a boolean telling whether it is a contant or not
     */
    public boolean isConstant() {
        return true;
    }

    /**
     * Used to get the value of this constant
     * @return a double representing the value of this constant
     */
    public double getValue() {
        return this.value;
    }

    /**
     * Used to get the string version of this operation
     * @return the String representing this operation
     */
    public String toString() {
        return String.valueOf(this.value);
    }


    /**
     * Used to determine if two objects are equal
     * @param other an Object to be compared to the current (this) one
     * @return a boolean telling if it is equal or not
     */
   public boolean equals(Object other) {
    if (other instanceof Constant) {
        return this.equals((Constant) other);
    } 
    else {
        return false;
    }
    }

    /**
     * Used to determine if two objects are equal
     * @param other a Constant to be compared to the current (this) one
     * @return a boolean telling if it is equal or not
     */
    public boolean equals(Constant other) {
        /// access a private field of other!
        return this.value == other.value;
    }

    /**
     * Accepts the visitor class to Constant
     * @return the visited Constant
     */
    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }


}
