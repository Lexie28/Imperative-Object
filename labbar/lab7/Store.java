public class Store {
    Register registers[];
    int regAmount;
    int doneTimes[];
    int doneLength;

    public Store(int amountOfRegisters) {
        this.registers = new Register[amountOfRegisters];
        for (int i = 0; i < amountOfRegisters; i++)
        {
            this.registers[i] = new Register();
        }
        this.regAmount = 1;
        this.doneTimes = new int[100];
        this.doneLength = 0;
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

    public void step() throws Exception {
        for (int i = 0; i < regAmount; i++){
            try {
                registers[i].step();
                }
                catch (Exception e) {
                    e.printStackTrace();
                }
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
            if (registers[i].queue.isEmpty()) {

            }
            else
            {
                Customer current = registers[i].queue.first.element;
                if (current.isDone())
                {
                    doneCustomers[j] = current;
                    doneTimes[doneLength] = -current.bornTime;
                    doneLength++;
                    j++;
                } 
            }
        }
        return doneCustomers;
    }

    public int getDoneCustomerAmount() {
        int count = 0;
        for (int i = 0; i < regAmount; i++){
            if (!(registers[i].queue.isEmpty())){
                Customer current = registers[i].queue.first.element;
                if (current.isDone())
                {
                    count++;
                }
            } 
        }
        return count;
    }

}
