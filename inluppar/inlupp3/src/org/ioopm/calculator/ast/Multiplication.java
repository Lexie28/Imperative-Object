package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class Multiplication extends Binary {

    public Multiplication(SymbolicExpression lhs, SymbolicExpression rhs){
        super(lhs, rhs);
    }
    
    public String getName(){
        return ("*");
    }

    public int getPriority() {
        return 100;
    }

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
