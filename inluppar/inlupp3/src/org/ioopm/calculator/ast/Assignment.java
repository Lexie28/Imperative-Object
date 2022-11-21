package inluppar.inlupp3.src.org.ioopm.calculator.ast;
import java.util.HashMap;

public class Assignment extends Binary {
    public Assignment(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    public String getName(){
        return ("=");
    }

    public SymbolicExpression eval(Environment vars)  {
        SymbolicExpression lhs = this.lhs.eval(vars);
        SymbolicExpression rhs = this.rhs;

        if (rhs.isNamedConstant())
        {
            throw new IllegalExpressionException("Error: cannot redefine named constant");
        }
        else{
            
            if(rhs.isVariable())
        {
            //rhs måste bli en variable. TODO är detta rätt sätt?
            vars.put((Variable) rhs, lhs);
            return lhs;
        }
        else
        {
            return new Assignment(lhs, rhs);
        }
        }
    }
    
}
