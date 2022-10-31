public class Customer {
    private int bornTime;
    private int groceries;


    public Customer(int bornTime, int groceries) {
        this.bornTime = bornTime;
        this.groceries = groceries;
    }

    public void serve() {
        if (groceries >= 1)
        {
            groceries = groceries - 1;
        }
    }

    public boolean isDone() {
        return (groceries == 0);
    }
    
}
