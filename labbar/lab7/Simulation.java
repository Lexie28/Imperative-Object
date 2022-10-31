public class Simulation {
    Store store;
    int time;
    int intensity;
    int maxGroceries;
    int thresholdForNewRegister;

    public Simulation(int intensity, int maxGroceries, int thresholdForNewRegister) {
        this.store = new Store();
        this.time = 0;
        this.intensity = intensity;
        this.maxGroceries = maxGroceries;
        this.thresholdForNewRegister = thresholdForNewRegister;
    }

    public void step()
    {
        store.step();
        int r = (int) (Math.random() * (100 - 0)) + 0;
        if (r < intensity) {
            store.newCustomer(new Customer(time, (int) (Math.random() * (maxGroceries - 1)) + 1));
        }
        if (store.getAverageQueueLength() > (double) thresholdForNewRegister) {
            store.openNewRegister();
        }

        Customer[] doneCustomers = store.getDoneCustomers();
        for (int i = 0; i < store.getDoneCustomerAmount(); i++)
        {
            System.out.println("Customer starting time: " + doneCustomers[i].bornTime);
        }
        time++;
    }
}