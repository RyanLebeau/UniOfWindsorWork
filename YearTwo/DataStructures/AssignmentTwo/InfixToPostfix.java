/**
 * Ryan Lebeau - 104535367
 * 60-254
 * 2017/10/18
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class InfixToPostfix {
    // public String[] inArr = null;
    Map<String, Integer> preced = new HashMap<>();
    private List<String> outputList = new ArrayList<>();
    AssignTwoStack stack = new AssignTwoStack();
    AssignTwoStack stackPost = new AssignTwoStack();

    public static void main(String[] args) {
        //File inputFile = new File("inputText.txt");
        List<String> inArr = new ArrayList<>();
        try {
            Scanner scan = new Scanner(new File("inputText.txt"));
            while (scan.hasNextLine()) {
                String infix = scan.nextLine();
                inArr.add(infix);
            }

        } catch (FileNotFoundException e) {
            System.out.println("Input file not found.");
        }
        InfixToPostfix test = new InfixToPostfix();
        test.setPreced();
        for (String infixString : inArr) {
            test.convertPost(infixString.split(" "));
            System.out.println("Final value is: "+test.evaluatePostfix());
            test.clearStacks();
        }

    }

    private void convertPost(String[] infix) {
        boolean flag = false;
        for (String tempWord : infix) {
            if (checkDigit(tempWord)) {
                outputList.add(tempWord);
            } else if (tempWord.equals("(")) {
                stack.push(tempWord);
            } else if (tempWord.equals(")")) {
                while (!flag) {
                    String topStack = stack.pop();
                    if (topStack.equals("("))
                        flag = true;
                    else if (checkOperator(topStack))
                        outputList.add(topStack);
                }
            } else if (checkOperator(tempWord)) {
                if (stack.emptyCheck())
                    stack.push(tempWord);
                else {
                    while (preced.get(stack.peek()) >= preced.get(tempWord)) {
                        outputList.add(stack.pop());
                        if (stack.emptyCheck())
                            break;
                    }
                    stack.push(tempWord);
                }
            }
        }
        while (!stack.emptyCheck()) {
            outputList.add(stack.pop());
        }
        System.out.println("\n\n" + outputList);
    }

    private int evaluatePostfix() {
        String finalVal;
        int finalValI;
        for (String currElement: outputList){
            if (checkDigit(currElement)){
                //int currDigit = atoi(currElement);
                stackPost.push(currElement);
            }
            else if (checkOperator(currElement)) {
                if (!stackPost.emptyCheck()) {
                    String secondDigit = stackPost.pop();
                    String firstDigit = stackPost.pop();
                    int fDigit = atoi(firstDigit);
                    int sDigit = atoi(secondDigit);
                    double result = postfixMath(fDigit, sDigit, currElement);
                    String sResult = String.valueOf(result);
                    stackPost.push(sResult);
                }
            }
        }
        finalVal = stackPost.pop();
        finalValI = atoi(finalVal);
        return finalValI;
    }


    private void clearStacks() {
        outputList.clear();
        stack = new AssignTwoStack();
        stackPost = new AssignTwoStack();
    }

    private double postfixMath(double first, double second, String operator){
        double result;
        switch(operator){
            case "^":
                result = Math.pow(first, second);
                return result;
            case "*":
                result = first*second;
                return result;
            case "/":
                result = first/second;
                return result;
            case "+":
                result = first+second;
                return result;
            case "-":
                result = first-second;
                return result;
            default:
                System.out.println("Not an operator\n");
        }
        return 0;
    }

    private boolean checkDigit(String check) {
        try {
            Integer.parseInt(check);
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    private boolean checkOperator(String check) {
        switch (check) {
            case "+":
                return true;
            case "-":
                return true;
            case "*":
                return true;
            case "/":
                return true;
            case "^":
                return true;
            case "~":
                return true;
            default:
                return false;
        }
    }

    private void setPreced() {
        preced.put("^", 5);
        preced.put("~", 4);
        preced.put("/", 3);
        preced.put("*", 3);
        preced.put("+", 2);
        preced.put("-", 2);
        //Integer.parseInt("45")
        preced.put("(", 1);
    }

    public int atoi(String str) {
        if (str == null || str.length() < 1)
            return 0;

        // trim white spaces
        str = str.trim();

        char flag = '+';

        // check negative or positive
        int i = 0;
        if (str.charAt(0) == '-') {
            flag = '-';
            i++;
        } else if (str.charAt(0) == '+') {
            i++;
        }
        // use double to store result
        double result = 0;

        // calculate value
        while (str.length() > i && str.charAt(i) >= '0' && str.charAt(i) <= '9') {
            result = result * 10 + (str.charAt(i) - '0');
            i++;
        }

        if (flag == '-')
            result = -result;

        // handle max and min
        if (result > Integer.MAX_VALUE)
            return Integer.MAX_VALUE;

        if (result < Integer.MIN_VALUE)
            return Integer.MIN_VALUE;

        return (int) result;
    }
}