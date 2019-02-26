/*
Ryan Lebeau
2017/10/01
QuestionSix.java 
*/

public class QuestionSix {

	public static void main(String[] args) {
		double x=2.5, y=-1.5;
		int n=17, m=18;
		System.out.println("x+n*y-(x+n)*y = "+(x+n*y-(x+n)*y));
		System.out.println("m/n+m%n = "+(m/n+m%n));
		System.out.println("n%2+m%2 = "+(n%2+m%2));
		System.out.println("(m+n)/2 = "+((m+n)/2));
		System.out.println("(m+n)/2.0 = "+((m+n)/2.0));
		double xi=(int) Math.round(x);
		xi=(int) Math.round(0.5*(m+n));
		System.out.println("0.5*(m+n) = "+xi);
		System.out.println("1-(1-(1-n)) = "+(1-(1-(1-n))));
		System.out.println("n%10+(n-(n%10)) = "+(n%10+(n-(n%10))));
	}

}
