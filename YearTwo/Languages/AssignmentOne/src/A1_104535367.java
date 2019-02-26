/**
 * Ryan Lebeau - 104535367
 * 60-214
 * 2018/02/02
 */

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class A1_104535367 {
    public static void main(String[] args) throws IOException {
        A1_104535367 assignOne = new A1_104535367();
        //output file creation and naming
        String outputName = args[0].split("-")[0].concat("-output.txt");
        File outputFile = new File(outputName);
        PrintWriter outWriter = new PrintWriter(outputFile);
        //input file creation
        Scanner scan = new Scanner(args[0]);
        //array of nonIdentifiers in c
        ArrayList<String> nonIden = new ArrayList<>();
        nonIden.addAll(Arrays.asList("int","float","long","double","boolean","bool","char","public","private","static","main",
                "return","printf","signed","unsigned","while","for","if","elseif","else","do","break","switch","continue"));
        //writing to output file
        outWriter.println("number of unique/distinct identifiers: "
                +assignOne.checkIdentifiers(assignOne.txtToString(args[0]), nonIden));
        outWriter.close();
    }

    //creates and returns a string of input.txt
    public String txtToString(String inputName) throws IOException{
        //creating a scanner of the input file and scanning through the entire file
        String textFile = new Scanner(new File(inputName)).useDelimiter("\\Z").next();
        //replacing anything enveloped with quotations to an empty character
        textFile = textFile.replaceAll("\\\".*\\\"", "");
        //replacing all parenthesis with a space
        textFile = textFile.replaceAll("\\(|\\)", " ");
        return textFile;
    }

    //matches anything that is a possible identifier and compares it too nonIdentifiers
    public int checkIdentifiers(String input, ArrayList<String> nonIdentifiers){
        String regex = "\\b_*[a-zA-Z][_a-zA-z0-9]*\\b";
        //create a pattern and matcher to compare possible identifiers
        Pattern pat = Pattern.compile(regex);
        Matcher match = pat.matcher(input);
        int idenCount = 0;
        //if a match with the regex is found within the input
        while(match.find()){
            //check to see if the possible identifier is in the arrayList of defined c statements
            if(!nonIdentifiers.contains(match.group())){
                idenCount++;
                //add identifier to list of c statements to prevent duplicate matches
                nonIdentifiers.add(match.group());
            }
        }
        return idenCount;
    }
}
