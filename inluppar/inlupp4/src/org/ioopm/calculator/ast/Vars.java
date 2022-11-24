package org.ioopm.calculator.ast;



public class Vars extends Command {
        private static final Vars theInstance = new Vars();
        private Vars() {}
        public static Vars instance() {
            return theInstance;
        }
     /// The rest of the code

     @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
