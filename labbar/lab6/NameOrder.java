import java.util.Scanner;

public class NameOrder {

    public static void main(String[] args) {
        String name1;
        String name2;
        Scanner sc = new Scanner(System.in);
        System.out.print("Write a name: ");
        name1 = sc.nextLine();
        System.out.print("Write a name: ");
        name2 = sc.nextLine();
        if (name1.compareTo(name2) < 0)
        {
            System.out.println("First name: " + name1 + " Second name: " + name2);
        }
        else
        {
            System.out.println("First name: " + name2 + " Second name: " + name1);
        }
    }

}
