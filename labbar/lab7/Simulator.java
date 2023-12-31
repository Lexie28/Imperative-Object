public class Simulator{

    public static void main(String[] args) throws InterruptedException{
        int steps = 100;
        int intensity = 50;
        int maxGroceries = 10;
        int thresholdForNewRegister = 2;
        int amountOfRegisters = 2; 
        Simulation s = new Simulation(intensity, maxGroceries, thresholdForNewRegister, amountOfRegisters);
        for(int i = 0; i < steps; i++){
            System.out.print("\033[2J\033[;H");
            s.step();
            System.out.println(s);
            System.out.println("Current time:         " + s.time);
            System.out.println("Average queue length: " + s.store.getAverageQueueLength());
            System.out.println("Average wait time:    " + s.averageTime());

            Thread.sleep(500);
        }
        System.out.println("");
        System.out.println("Simulation finished!");
    }
}