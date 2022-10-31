import java.util.Scanner;

public class MyDieTest {

  public static void main(String [] args) {
      Scanner sc = new Scanner(System.in);
      System.out.print("Number of sides: ");
      int sides = sc.nextInt();
      Die d = new Die(sides);

      int acc = 0;
      for (int i = 0; i < 10; i++) {
        acc += d.roll();
      }
      System.out.println("Total count: " + acc);
      System.out.println(d);
  }
}