package org.ioopm.calculator.ast;
import java.util.HashMap;
import java.util.Iterator;
import java.util.TreeSet;
     
public class Environment extends HashMap<Variable, SymbolicExpression> {

    /**
     * Used to get the string version of this operation
     * @return the String representing this operation
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Variables: ");
        TreeSet<Variable> vars = new TreeSet<>(this.keySet());
        Iterator<Variable> it = vars.iterator();
            while(it.hasNext()) {
                Variable v = it.next();
                sb.append(v.toString());
                sb.append(" = ");
                sb.append(this.get(v));
                if(it.hasNext())
                {
                    sb.append(", ");
                }
            }
        return sb.toString();
    }
}
