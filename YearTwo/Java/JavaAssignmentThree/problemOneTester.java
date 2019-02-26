import java.util.Scanner;

public class problemOneTester {
    public static void main(String[] args) {
        problemOne CCVerify = new problemOne();
        Scanner input = new Scanner(System.in);
        CCVerify.verifyCreditCardNum(input.nextLine());
        CCVerify.verifyCreditCardNum(input.nextLine());
        CCVerify.verifyCreditCardNum(input.nextLine());
    }
}