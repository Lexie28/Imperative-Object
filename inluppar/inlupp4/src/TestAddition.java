import org.ioopm.calculator.ast.*;

public class TestAddition {
    @BeforeAll
    public void testSetup() {
        Constant c1 = new Constant(2.0);
        Constant c2 = new Constant(2.0);
        Addition a = new Addition(c1, c2);
    }

    public void testGetValue() {
        
    }
}
