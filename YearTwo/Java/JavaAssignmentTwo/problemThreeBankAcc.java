/**
 * Modified By: Ryan Lebeau - 104535367
 * 60-212
 * 2017/10/15
 */


/**
 A bank account has a balance that can be changed by
 deposits and withdrawals.
 */
public class problemThreeBankAcc
{
    private double balance;
    private double fee = 0.03;
    private double monthlyTransactions;
    private double monthlyDeduction=0;
    /**
     Constructs a bank account with a zero balance.
     */
    public problemThreeBankAcc(){
        balance = 0;
    }

    /**
     Constructs a bank account with a given balance.
     @param initialBalance the initial balance
     */
    public problemThreeBankAcc(double initialBalance)
    {
        balance = initialBalance;
    }

    /**
     Deposits money into the bank account.
     @param amount the amount to deposit
     */
    public void deposit(double amount)
    {
        balance = balance + amount;
        //balance -= amount*fee;
        monthlyTransactions++;
        if(monthlyTransactions>5){
            monthlyDeduction+=amount*fee;
        }
    }

    /**
     Withdraws money from the bank account.
     @param amount the amount to withdraw
     */
    public void withdraw(double amount)
    {
        balance = balance - amount;
        //balance -= amount*fee;
        monthlyTransactions++;
        if(monthlyTransactions>5){
            monthlyDeduction+=amount*fee;
        }
    }

    /**
     Gets the current balance of the bank account.
     @return the current balance
     */
    public double getBalance()
    {
        return balance;
    }

    /**
     * If there were more than 5 transactions in the month
     * remove fees stored in 'monthlyDeduction'
     */
    public void deductMonthlyCharge(){
        if(monthlyTransactions > 5){
            balance -= monthlyDeduction;
        }
        monthlyDeduction = 0;
        monthlyTransactions = 0;
    }
}
