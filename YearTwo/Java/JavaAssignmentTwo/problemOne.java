/**
 * Ryan Lebeau - 104535367
 * 60-212
 * 2017/10/15
 */

import javax.swing.*;
import java.awt.*;

public class problemOne {
    public static void main(String[] args) {
        trafficLightsDraw test = new trafficLightsDraw();
        //window initialize
        JFrame window = new JFrame();
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setSize(test.rectWidth*5,test.rectHeight+(test.rectHeight/2));
        window.setTitle("Traffic Lights");
        window.add(test);
        window.setVisible(true);
    }
}
