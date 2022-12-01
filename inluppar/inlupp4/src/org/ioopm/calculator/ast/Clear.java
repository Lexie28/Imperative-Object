package org.ioopm.calculator.ast;

public class Clear extends Command {
    private static final Clear theInstance = new Clear();
    private Clear() {
        super("Clear");
    }
    public static Clear instance() {
        return theInstance;
    }
 /// The rest of the code

 /**
     * Accepts the visitor class to Clear
     * @return the visited Clear
     */
 @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
