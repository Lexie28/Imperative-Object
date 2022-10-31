public class Store {
    Register registers[];
    int regAmount;

    public Store() {
        this.registers = new Register[15];
        this.regAmount = 1;
    }

    public double getAverageQueueLength() {
        int totalCustomers = 0;
        for (int i = 0; i < regAmount; i++)
        {
            totalCustomers += registers[i].getQueueLength();
        }
        return (totalCustomers / regAmount);
    }

    public void newCustomer(Customer c) {
        Queue shortest = registers[0].queue;
        for (int i = 0; i < regAmount; i++)
        {
            if (registers[i].getQueueLength() < shortest.length()) {
                shortest = registers[i].queue;
            }
        }
        shortest.enqueue(c);
    }  

    public void step(){
        for (int i = 0; i < regAmount; i++){
            registers[i].step();
        }
    }

    public void openNewRegister() {
        registers[regAmount] = new Register();
        regAmount++;
    }

    public Customer[] getDoneCustomers() {
        Customer doneCustomers[] = new Customer[15];
        int j = 0;
        for (int i = 0; i < regAmount; i++){
            Customer current = registers[i].queue.first.element;
            if (current.isDone())
            {
                doneCustomers[j] = current;
                j++;
            } 
        }
        return doneCustomers;
    }

    public int getDoneCustomerAmount() {
        int count = 0;
        for (int i = 0; i < regAmount; i++){
            Customer current = registers[i].queue.first.element;
            if (current.isDone())
            {
                count++;
            } 
        }
        return count;
    }

}
