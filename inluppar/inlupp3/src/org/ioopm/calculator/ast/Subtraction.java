package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class Subtraction extends Binary {
 
    public Subtraction(SymbolicExpression lhs, SymbolicExpression rhs){
        super(lhs, rhs);
    }
    
    public String getName(){
        return ("-");
    }

    public int getPriority() {
        return 50;
    }

    public SymbolicExpression eval() {
        SymbolicExpression lhs = this.lhs;
        SymbolicExpression rhs = this.rhs;

        if(lhs.isConstant() && rhs.isConstant())
        {  
            return(new Constant(lhs.getValue() - rhs.getValue()));
        }
        else
        {
            return new Subtraction(lhs, rhs);
        }
    }
}
