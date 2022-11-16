package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public abstract class Atom extends SymbolicExpression {
    public int getPriority() {
        return 200;
    }
}
//den här behövs egentligen inte
