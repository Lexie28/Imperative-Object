package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class Addition extends Binary {
    public Addition(SymbolicExpression lhs, SymbolicExpression rhs){
        super(lhs, rhs);
    }
    public String getName(){
        return ("+");

    }

}
