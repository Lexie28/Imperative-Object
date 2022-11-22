package src.org.ioopm.calculator.ast;

public class Multiplication extends Binary {

    public Multiplication(SymbolicExpression lhs, SymbolicExpression rhs){
        super(lhs, rhs);
    }
    
    /**
     * Used to get the name of the operation
     * @return the String representing this operation
     */
    public String getName(){
        return ("*");
    }

    /**
     * Used to get the priority of the operation
     * @return the int representing the priority of this operation
     */
    public int getPriority() {
        return 100;
    }

    /**
     * Used to evaluate an expression using a hash-table of variables
     * @param vars the environment vars to store the variables in
     * @return a symbolicexpression that has been evaluated
     */
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression lhs = this.lhs.eval(vars);
        SymbolicExpression rhs = this.rhs.eval(vars);

        if(lhs.isConstant() && rhs.isConstant())
        {  
            return(new Constant(lhs.getValue() * rhs.getValue()));
        }
        else
        {
            return new Multiplication(lhs, rhs);
        }
    }
}
