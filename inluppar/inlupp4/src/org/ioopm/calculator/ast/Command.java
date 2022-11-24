package org.ioopm.calculator.ast;

public abstract class Command extends SymbolicExpression {
    
    public Command(String name) {
        super(name);
    }
    
    /**
     * Used to determine if this is a command
     * @return a boolean telling whether it is a command or not
     */
    public boolean isCommand() {
        return true;
    }
}
