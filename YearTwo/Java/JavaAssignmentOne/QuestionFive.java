/*
Ryan Lebeau
2017/10/01
QuestionOne.java 
*/
public class QuestionFive {

	public static void main(String[] args) {
		//declaring variables
		int s0=10, v0=5, t=12, a=6, p=4, m1=10, m2=2;
		double s, G, g=9.8, pi=3.14;
		//computing both problems
		s = s0+v0+ (1/2)*g*t*t;
		G = 4*pi*pi*((a*a*a)/(p*p*(m1+m2)));
		//returning the values
		System.out.println("s = "+s+"\nG = "+G);
	}

}
