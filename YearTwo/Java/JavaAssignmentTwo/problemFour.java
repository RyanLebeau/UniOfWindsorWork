/**
 * Ryan Lebeau - 104535367
 * 60-212
 * 2017/10/15
 */

public class problemFour {
    private int amountRec;
    private int amountOwed;
    private int q=0,d=0,n=0;
    //constructor that receives the amount received and amount owed
    public problemFour(int r, int o){
        amountRec = r;
        amountOwed = o;
    }

    public void changeCalculation(){
        boolean flag=true;
        while(flag) {
            //handles the number of quarters
            if (amountOwed-25 >= 0) {
                amountOwed -= 25;
                q++;
            }
            //handles the number of dimes
            else if (amountOwed-10 >= 0){
                amountOwed -= 10;
                d++;
            }
            //handles the number of nickels
            else if (amountOwed-5 >= 0){
                amountOwed -= 5;
                n++;
            }
            //when only change left is pennies
            else
                flag=false;
        }
    }
    //prints the change required
    public void getChange(){
        System.out.println("Quarter(s): "+q+"\nDime(s): "+d+"\nNickel(s): "+n+"\nPennie(s): "+amountOwed);
    }
}
