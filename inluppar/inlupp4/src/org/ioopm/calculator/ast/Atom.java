package org.ioopm.calculator.ast;

public abstract class Atom extends SymbolicExpression {
    
    public Atom(String name) {
        super(name);
    }

    /**
     * Used to get the priority of the operation
     * @return the int representing the priority of this operation
     */
    public int getPriority() {
        return 200;
    }
}
//den här behövs egentligen inte
