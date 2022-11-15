package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public abstract class Binary {
    private SymbolicExpression lhs = null;
    private SymbolicExpression rhs = null;

    public Binary(SymbolicExpression lhs, SymbolicExpression rhs) {

        this.lhs = lhs;
        this.rhs = rhs;

    public SymbolicExpression getlhs(){
        return this.lhs;
    }
    public SymbolicExpression getrhs(){
        return this.rhs;
    }
}

