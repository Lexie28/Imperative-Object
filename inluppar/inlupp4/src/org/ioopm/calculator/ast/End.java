package org.ioopm.calculator.ast;

public class End extends Command{
    private static final End theInstance = new End();
    private End() {
        super("End");
    }
    public static End instance() {
        return theInstance;
    }
    /// The rest of the code

    /**
     * Accepts the visitor class to Quit
     * @return the visited Quit
     */
    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
