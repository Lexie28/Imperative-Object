package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class NamedConstant extends Atom {
    private String identifier;
    private double value;

    public NamedConstant(String identifier, double value) {
        this.identifier = identifier;
        this.value = value;
    }


}
