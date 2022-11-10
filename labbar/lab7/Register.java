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
        if (queue.isEmpty() == true) //if queue is empty, return
        {
            throw new EmptyQueueException("Trying to step in an empty queue.");
            //return;
        }
        else if (currentCustomerIsDone())
        {
            queue.dequeue();
        }
        else
        {
            queue.first.element.serve();
        }
        
    }


    public boolean hasCustomers() {
        if (queue.isEmpty() == true)
        {
            return false;
        }
        else if (queue.first != null)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    public boolean currentCustomerIsDone() {
        if (queue.isEmpty())
        {
            return false;
        }
        return(queue.first.element.isDone()); //vi försöker accessa queue.first some inte finns
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
