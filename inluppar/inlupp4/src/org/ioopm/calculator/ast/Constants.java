package src.org.ioopm.calculator.ast;

import java.util.HashMap;

public class Constants {
    public static final HashMap<String, Double> namedConstants = new HashMap<>();

    static {
        Constants.namedConstants.put("pi", Math.PI);
        Constants.namedConstants.put("e",  Math.E);
        Constants.namedConstants.put("L", (6.022140857 * (10^23)));
        Constants.namedConstants.put("Answer" , 42.0);
    }

    /**
     * Used to determine if this is a command
     * @return a boolean telling whether it is a command or not
     */
    public boolean isNamedConstant() {
        return true;
    }
}

