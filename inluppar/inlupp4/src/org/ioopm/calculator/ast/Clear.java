package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class Clear extends Command {
    private static final Clear theInstance = new Clear();
    private Clear() {}
    public static Clear instance() {
        return theInstance;
    }
 /// The rest of the code
}
