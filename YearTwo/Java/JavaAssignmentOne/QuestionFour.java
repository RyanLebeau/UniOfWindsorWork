/*
Ryan Lebeau
2017/10/01
QuestionFour.java 
*/

import java.net.URL;
import javax.swing.JOptionPane;
import javax.swing.ImageIcon;
public class QuestionFour {
	public static void main(String[] args) throws Exception {
		URL imageLocation = new URL ("http://horstmann.com/java4everyone/duke.gif");
		JOptionPane.showMessageDialog(null, "Hello", "Title", JOptionPane.PLAIN_MESSAGE, new ImageIcon(imageLocation));
	}

}
