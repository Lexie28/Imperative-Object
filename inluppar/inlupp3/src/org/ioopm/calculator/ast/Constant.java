package inluppar.inlupp3.src.org.ioopm.calculator.ast;

public class Constant extends Atom {
    private double value;

    public Constant(double value)
    {
        this.value = value;
    }

    public boolean isConstant() {
        return true;
    }

    public double getValue() {
        return this.value;
    }
    
    public String toString() {
        return String.valueOf(this.value);
    }
}
