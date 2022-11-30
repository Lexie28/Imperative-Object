package org.ioopm.calculator.ast;

public class Conditionals extends SymbolicExpression {
    public SymbolicExpression lhsexp;
    public SymbolicExpression rhsexp;
    public String op;
    public SymbolicExpression ifstate;
    public SymbolicExpression elsestate;

    public ArrayList<String> operationslist = 


    public String toString() {
        return ("if" + this.lhs + this.op + "{" + this.ifstate + "} else {" this.elsestate + "}");
    }

    
}
