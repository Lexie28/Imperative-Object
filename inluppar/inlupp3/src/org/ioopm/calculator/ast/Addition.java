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

    //kolla vad som händer om du addar en constant o en variable, kolla om den finns i ht'en och isf dra ut det valuet
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression lhs = this.lhs.eval(vars);
        SymbolicExpression rhs = this.rhs.eval(vars);

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