package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class Assignment extends Binary {
    public Assignment(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    public String getName(){
        return ("=");
    }

    
}
