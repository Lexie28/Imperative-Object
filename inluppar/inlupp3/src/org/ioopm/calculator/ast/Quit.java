package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class Quit extends Command {
    private static final Quit theInstance = new Quit();
    private Quit() {}
    public static Quit instance() {
        return theInstance;
    }
 /// The rest of the code
}
