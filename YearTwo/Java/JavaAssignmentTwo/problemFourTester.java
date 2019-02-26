/**
 * Ryan Lebeau - 104535367
 * 60-212
 * 2017/10/15
 */

public class problemFourTester {
    public static void main(String[] args) {
        //test case 1
        problemFour testOne = new problemFour(400, 218);
        testOne.changeCalculation();
        testOne.getChange();
        //test case 2
        problemFour testTwo = new problemFour(100, 84);
        testTwo.changeCalculation();
        testTwo.getChange();
        //test case 3
        problemFour testThree = new problemFour(200, 99);
        testThree.changeCalculation();
        testThree.getChange();
    }
}
