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

    public int getdie1() {
        return die1.get();
    }

    public int getdie2() {
        return die2.get();
    }

    public String toString() {
        return "Die(" + value + ")";
        }

}
