public class problemFourTester {
    public static void main(String[] args) {
        int inputs[] = {1,2,8,4,5,6,7,2,3,420,1,1,3,6,7,5};
        int waterLevel = 5;
        problemFour test = new problemFour(inputs);
        System.out.println("Lowest point: "+test.lowestHeight());
        System.out.println("Highest point: "+test.highestHeight());
        test.printFloodMap(waterLevel);
    }
}
