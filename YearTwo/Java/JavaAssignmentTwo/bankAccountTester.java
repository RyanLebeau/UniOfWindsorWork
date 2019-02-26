/**
 * Ryan Lebeau - 104535367
 * 60-212
 * 2017/10/15
 */

public class bankAccountTester {
    /**
     Tests the methods of the BankAccount class.
     @param args not used
     */
    public static void main(String[] args)
    {
        problemThreeBankAcc testCheck = new problemThreeBankAcc();
        //8 transactions monthly limit set at 5
        testCheck.deposit(2000);
        testCheck.withdraw(500);
        testCheck.deposit(200);
        testCheck.withdraw(100);
        testCheck.deposit(200);
        testCheck.withdraw(100);
        testCheck.deposit(200);
        testCheck.withdraw(100);
        testCheck.deductMonthlyCharge();
        System.out.println(testCheck.getBalance());
        System.out.println("Expected: 1788");
    }
}
