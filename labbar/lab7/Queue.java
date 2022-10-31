public class Queue {
    Node first;
    Node last;
    int length;
    
    public Queue() {
        this.first = null;
        this.last = null;
        this.length = 0;
    }

    public int length() {
        return length;
    }

    public void enqueue(Customer c) {
        Node newLast = new Node(c, null);
        last.next = newLast;
        last = newLast;
        if (length == 0)
        {
            first = newLast;
        }
        length++;
    }

    public Customer dequeue() {
        Customer result = first.element;
        first = first.next;
        length--;
        if (length == 0)
        {
            last = null;
        }
        return result;
    }

    public Customer first() {
        return first.element;
    }
}

class Node {
    Customer element;
    Node next;

    public Node(Customer c, Node next) {
        this.element = c;
        this.next = next;
    }

    public Customer getCustomer() {
        return element;
    }

    public Node getNode() {
        return next;
    }

    public void setNode(Node newNext) {
        next = newNext;
    }
}