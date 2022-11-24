package org.ioopm.calculator.ast;

public class Quit extends Command {
    private static final Quit theInstance = new Quit();
    private Quit() {
        super("Quit");
    }
    public static Quit instance() {
        return theInstance;
    }
 /// The rest of the code

 @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
