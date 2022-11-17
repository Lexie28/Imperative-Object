package inluppar.inlupp3.src.org.ioopm.calculator.ast;
import java.util.HashMap;

public class Assignment extends Binary {
    public Assignment(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    public String getName(){
        return ("=");
    }

    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression lhs = this.lhs;
        SymbolicExpression rhs = this.lhs;
        if(lhs.isConstant())
        {
            //rhs måste bli en variable. TODO är detta rätt sätt?
            Variable rhsvar = new Variable(rhs.toString());
            vars.put(rhsvar, lhs);
            return(new Constant(lhs.getValue()));
        }
        else
        {
            return new Assignment(lhs, rhs);
        }
    }
    
}
