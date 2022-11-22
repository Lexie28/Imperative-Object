package src.org.ioopm.calculator.ast;

public abstract class Unary extends SymbolicExpression {
    public SymbolicExpression expression;

    /**
    * Used to display variable
    * @param expression string representation of variable
    * @return string representation of variable
    */
    public Unary(SymbolicExpression expression)
    {
        this.expression = expression;
    }

    /**
     * Used to get the priority of the operation
     * @return the int representing the priority of this operation
     */
    public int getPriority() {
        return 150;
    }

    /**
    * string representation of expression
    * @return string representation of expression
    */
    public String toString() {
        /// Note how the call to toString() is not necessary

        return this.getName() + " " + this.expression.toString();
    }

    /**
    * checks if two unary expressions are equal or not
    * @param other object that vill be compared against
    * @return true or false depending on if equal or not
    */
    public boolean equals(Object other) {
        if (other instanceof Unary) {
            return this.equals((Unary) other);
        } else {
            return false;
        }
    }

    /**
    * checks if two unary expressions are equal or not
    * @param other object that vill be compared against
    * @return true or false depending on if equal or not
    */
    public boolean equals(Unary other) {
        boolean a = this.getName() == other.getName();
        boolean b = this.expression == other.expression;
        if(a == true && b == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
