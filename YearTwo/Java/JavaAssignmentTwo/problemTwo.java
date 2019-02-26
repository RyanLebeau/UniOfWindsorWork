/**
 * Ryan Lebeau - 104535367
 * 60-212
 * 2017/10/15
 */


public class problemTwo {
    private int time;
    private int power;
    //displays the time and power of microwave
    public void start(){
        System.out.println("Cooking for "+this.time+" seconds at power "+this.power);
    }
    //set the power level of microwave
    public void powerLvl(int p){
        this.power = p;
    }
    //set the timer of the microwave
    public void timer(int t){
        this.time = t;
    }
    //reset the timer and power on the microwave
    public void reset(){
        this.time = 0;
        this.power = 0;
    }
}
