/**
 * Ryan Lebeau - 104535367
 * 60-212
 * 2017/10/15
 */

import java.awt.*;
import java.awt.geom.Ellipse2D;
import javax.swing.*;

public class trafficLightsDraw extends JComponent {
    //size variables that provide basis for all positioning
    public int rectWidth = 200;
    public int rectHeight = 400;
    //required paint method
    public void paintComponent(Graphics g){
        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D) g;
        g2.setColor(Color.BLACK);
        //creating and positioning the three traffic light boxes
        Rectangle lightBoxes = new Rectangle(rectWidth/2, rectHeight/4, rectWidth, rectHeight);
        g2.draw(lightBoxes);
        lightBoxes.translate(rectWidth+rectWidth/2, 0);
        g2.draw(lightBoxes);
        lightBoxes.translate(rectWidth+rectWidth/2, 0);
        g2.draw(lightBoxes);
        //drawing the three traffic light methods
        redLight(g2);
        yellowLight(g2);
        greenLight(g2);
    }

    private void redLight(Graphics2D g2){
        g2.setPaint(Color.RED);
        g2.fill(new Ellipse2D.Double(rectWidth-rectWidth/8, rectHeight/3, rectWidth/4, rectWidth/4));
        g2.setPaint(Color.BLACK);
        g2.fill(new Ellipse2D.Double(rectWidth-rectWidth/8, (rectHeight/3)*2, rectWidth/4, rectWidth/4));
        g2.fill(new Ellipse2D.Double(rectWidth-rectWidth/8, (rectHeight/3)*3, rectWidth/4, rectWidth/4));
    }
    private void yellowLight(Graphics2D g2){
        g2.setPaint(Color.BLACK);
        g2.fill(new Ellipse2D.Double(rectWidth*2+rectWidth/2-rectWidth/8, rectHeight/3, rectWidth/4, rectWidth/4));
        g2.setPaint(Color.YELLOW);
        g2.fill(new Ellipse2D.Double(rectWidth*2+rectWidth/2-rectWidth/8, (rectHeight/3)*2, rectWidth/4, rectWidth/4));
        g2.setPaint(Color.BLACK);
        g2.fill(new Ellipse2D.Double(rectWidth*2+rectWidth/2-rectWidth/8, (rectHeight/3)*3, rectWidth/4, rectWidth/4));
    }
    private void greenLight(Graphics2D g2){
        g2.setPaint(Color.BLACK);
        g2.fill(new Ellipse2D.Double(rectWidth*4-rectWidth/8, rectHeight/3, rectWidth/4, rectWidth/4));
        g2.fill(new Ellipse2D.Double(rectWidth*4-rectWidth/8, (rectHeight/3)*2, rectWidth/4, rectWidth/4));
        g2.setPaint(Color.GREEN);
        g2.fill(new Ellipse2D.Double(rectWidth*4-rectWidth/8, (rectHeight/3)*3, rectWidth/4, rectWidth/4));
    }
}
