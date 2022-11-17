package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class Addition extends Binary {
    
    public Addition(SymbolicExpression lhs, SymbolicExpression rhs){
        super(lhs, rhs);
    }

    public String getName(){
        return ("+");
    }

    public int getPriority() {
        return 50;
    }

    public SymbolicExpression eval() {
        SymbolicExpression lhs = this.lhs;
        SymbolicExpression rhs = this.rhs;

        if(lhs.isConstant() && rhs.isConstant())
        {  
            return(new Constant(lhs.getValue() + rhs.getValue()));
        }
        else
        {
            return new Addition(lhs, rhs);
        }
    }

}