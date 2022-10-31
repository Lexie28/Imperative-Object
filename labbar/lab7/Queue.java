public class Queue {
    Node first;
    Node last;
    int length;
    
    public Queue() {
        this.first = NULL;
        this.last = NULL;
        this.length = 0;
    }

    public int length() {
        return length;
    }

    public void enqueue(Customer c) {
        Node newLast = new Node(c, NULL);
        last.setNode = newLast;
        last = newLast;
        if (length == 0)
        {
            first = newLast;
        }
        length++;
    }

    public Customer dequeue() {
        Customer result = first;
        first = first.next;
        length--;
        if (length == 0)
        {
            last = NULL;
        }
        return result;
    }

    public Customer first() {
        return first;
    }
}

private class Node {
    Customer element;
    Node next;

    private Node(Customer c, Node next) {
        this.element = c;
        this.next = next;
    }

    private Customer getCustomer() {
        return element;
    }

    private Node getNode() {
        return next;
    }

    private void setNode(Node newNext) {
        next = newNext;
    }
}