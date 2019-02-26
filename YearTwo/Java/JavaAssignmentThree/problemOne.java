/**
 * Ryan Lebeau - 104535367
 * 60-212
 * 2017/11/03
 * Credit Card Validator
 */

public class problemOne {

    //receives the cc numbers as a string and returns if it is valid or not
    public int verifyCreditCardNum(String inputStr){
        //creating a string of just cc numbers with no whitespaces
        String integers = removeSpace(inputStr);
        int result = addInput(integers);
        result += addSecondDigit(integers);
        result += addAboveFour(integers);
        //returning true if valid and false if invalid
        if(result%10 == 0){
            System.out.println("Verified.\n");
            return 1;
        }
        else {
            System.out.println("Not valid.\n");
            return 0;
        }
    }
    //remove all spaces from the string of cc numbers
    private String removeSpace(String inputStr) {
        return inputStr.replaceAll(" ", "");
    }
    //return the sum of all cc numbers
    private int addInput(String integers){
        int sum=0;
        for(int i=0; i<integers.length(); i++){
            sum += Character.getNumericValue(integers.charAt(i));
        }
        return sum;
    }
    //return the sum of all second digits in the string of cc numbers
    private int addSecondDigit(String integers){
        int sum=0;
        for(int i=integers.length()-2; i>=0; i=i-2){
            sum += Character.getNumericValue(integers.charAt(i));
        }
        return sum;
    }
    //return the number of cc numbers above value 4
    private int addAboveFour(String integers){
        int sum=0;
        for(int i=integers.length()-2; i>=0; i=i-2){
            if(Character.getNumericValue(integers.charAt(i)) > 4)
                sum += 1;
        }
        return sum;
    }
}
