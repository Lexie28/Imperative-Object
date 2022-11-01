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
            store.doneTimes[store.doneLength-1] = store.doneTimes[store.doneLength-1] + time;
            System.out.println("Customer starting time: " + doneCustomers[i].bornTime);
        }
        time++;
    }

    public String toString() {
        String result = "";
        for (int i = 0; i < store.regAmount; i++) {

            if (store.registers[i].isOpen()){
                if (store.registers[i].queue.isEmpty()) {
                    result = result + "  [ ]\n";
                }
                else
                {
                    result = result + "[" + store.registers[i].queue.first.element.groceries + "]";
                    for (int j = 1; j < store.registers[i].queue.length; j++) {
                        result = result + "@";
                    }
                    result = result + "\n";
                }
                }
            else 
            {
                result = result + "X [ ]\n";
            }
        }
        return result;
    }


    public double averageTime() {
        double result = 0;
        if (store.doneLength == 0)
        {
            return 0;
        }
        for (int i = 0; i < store.doneLength; i++) {
            result += store.doneTimes[i];
        }
        return (result / store.doneLength);
    }
}