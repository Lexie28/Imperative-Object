import java.util.Scanner;

public class PairOfDice {

    private Die die1;
    private Die die2;

    public PairOfDice() {
        this.die1 = new Die();
        this.die2 = new Die();
    }

    public PairOfDice(int numberOfSides) {
        this.die1 = new Die(numberOfSides);
        this.die2 = new Die(numberOfSides);

    }

    public int roll() {
        die1.roll();
        die2.roll();
        return (die1.get() + die2.get());
      }

    public int getDie1() {
        return die1.get();
    }

    public int getDie2() {
        return die2.get();
    }

    public String toString() {
        return ("Die 1: " + this.getDie1() + "\nDie 2: " + this.getDie2());
        }
    
    public static void main(String [] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Number of sides: ");
        int sides = sc.nextInt();
        PairOfDice d = new PairOfDice(sides);
        System.out.println("Total: " + d.roll());
        System.out.println(d);

    }

}
