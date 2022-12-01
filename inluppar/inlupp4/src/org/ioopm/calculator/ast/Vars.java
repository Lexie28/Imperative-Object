package org.ioopm.calculator.ast;



public class Vars extends Command {
        private static final Vars theInstance = new Vars();
        private Vars() {
            super("Vars");
        }
        public static Vars instance() {
            return theInstance;
        }
     /// The rest of the code

     /**
     * Accepts the visitor class to Vars
     * @return the visited Vars
     */
     @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
