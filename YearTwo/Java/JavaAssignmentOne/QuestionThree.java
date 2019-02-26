/*
Ryan Lebeau
2017/10/01
QuestionThree.java 
*/

public class QuestionThree {
	public static void main(String[] args) {
		//variables to store current sum and product
		int sum=0,product=1;
		//calculates sum and product of the first 5 negative integers
		for(int i=-1; i>-6;i--) {
			sum += i;
			product *= i;
		}
		//print results to the user0
		System.out.println("Sum = "+sum+"\nProduct = "+product);
	}
}
