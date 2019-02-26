/*
Ryan Lebeau
2017/10/01
QuestionOne.java 
*/

public class QuestionOne {
	public static void main(String[] args) {
		//tracks current balance 
		int balance=1000;
		//calculates balance after interest for first three years
		for (int i=1;i<4;i++) {
			//prints the balance for each year
			System.out.println("Year "+i+" - "+balance);
			//adding interest to previous balance
			balance *= 1.05;
		}
	}
}
