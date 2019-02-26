import java.util.ArrayList;
import java.util.*;
import java.util.stream.Collectors;

public class AssignTwoStack {
    List<String> stackArr = new ArrayList<>();
    //ArrayList stackArr = new ArrayList();
    private int beginCtr = -1;

    public void push(String inputPush){
        beginCtr++;
        stackArr.add(inputPush);
        printStack();
        System.out.println(inputPush+" was successfully pushed to the stack");
        printStack();
    }

    public String pop(){
        if (beginCtr >= 0){
            printStack();
            int size = stackArr.size() -1;
            String temp = stackArr.get(size);
            beginCtr--;
            stackArr.remove(size);
            System.out.println("Element popped.");
            printStack();
            return temp;
        }
        else{
            System.out.println("Stack is empty can not pop.");
            return null;
        }
    }

    public String peek(){
        int size = stackArr.size()-1;
        return stackArr.get(size);
    }

    public boolean emptyCheck(){
        if (beginCtr == -1)
            return true;
        else
            return false;
    }

    public void printStack(){
        if (beginCtr >= 0){
            System.out.println("Stack: "+stackArr);
        }
    }
}
