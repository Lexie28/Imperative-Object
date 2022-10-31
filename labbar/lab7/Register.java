public class Register {
    boolean open;
    Queue queue;

    public Register() {
        this.open = true;
        this.queue = new Queue();
    }

    public void open() {
        open = true;
    }

    public void close() {
        open = false;
    }

    public boolean isOpen() {
        return (open);
    }

    public void step() {
        if (currentCustomerIsDone())
        {
            queue.dequeue();
        }
        else
        {
            queue.first.serve();
        }
    }

    public boolean hasCustomers() {
        return (queue.first != NULL);
    }

    public boolean currentCustomerIsDone() {
        return(queue.first.isDone());
    }

    public void addToQueue(Customer c) {
        queue.enqueue(c);
    }

    public Customer removeCurrentCustomer() {
        return queue.dequeue();
    }

    public int getQueueLength() {
        return queue.length;
    }

}
