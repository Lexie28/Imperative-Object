package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public abstract class Binary extends SymbolicExpression {
    private SymbolicExpression lhs;
    private SymbolicExpression rhs;

    public Binary(SymbolicExpression lhs, SymbolicExpression rhs) {
        this.lhs = lhs;
        this.rhs = rhs;
    }
}

