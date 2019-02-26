/**
 * Ryan Lebeau - 104535367
 * Languages Assignment 5
 * 03/04/2018
 */

import java.io.*;
import java_cup.runtime.Symbol;
class Main {
  public static void main(String[] args) throws Exception {
       File fileIn = new File (args[0]);
       A5_104535367_Parser parser= new A5_104535367_Parser(new A5_104535367_Scanner(new FileReader(fileIn)));
       String output = (String)parser.debug_parse().value;
       String outFile = "A5_output.java";
       FileWriter fileW = new FileWriter(new File(outFile));
       fileW.write(output);
       fileW.close();
  }
}