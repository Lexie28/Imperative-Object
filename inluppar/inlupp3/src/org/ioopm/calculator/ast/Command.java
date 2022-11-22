package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public abstract class Command extends SymbolicExpression {
    
    /**
     * Used to determine if this is a command
     * @return a boolean telling whether it is a command or not
     */
    public boolean isCommand() {
        return true;
    }
}
