public class Customer {
    public int bornTime;
    public int groceries;


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
