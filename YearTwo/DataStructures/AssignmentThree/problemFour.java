/**
 * Ryan Lebeau - 104535367
 * 60-212
 * 2017/11/03
 * Flood Maps
 */

public class problemFour {
    private int[][] heights;
    private int sizeInt;
    //converts the input array into a square 2D array
    public problemFour(int[] inputValues){
        int counter=0;
        //find number of column and rows in square 2D array
        double sizeDoub = Math.sqrt(inputValues.length);
        sizeInt = (int)sizeDoub;
        heights = new int[sizeInt][sizeInt];
        //populating with values from 1D inputValues array
        for(int i=0; i<sizeInt; i++){
            for(int j=0; j<sizeInt; j++){
                heights[i][j] = inputValues[counter];
                counter++;
            }
        }

    }
    //returns the lowest height that was entered
    public int lowestHeight(){
        int lowest=heights[0][0];
        for(int i=0; i<sizeInt; i++){
            for(int j=0; j<sizeInt; j++){
                if(lowest>=heights[i][j])
                    lowest = heights[i][j];
            }
        }
        return lowest;
    }
    //returns the tallest height that was entered
    public int highestHeight(){
        int highest=heights[0][0];
        for(int i=0; i<sizeInt; i++){
            for(int j=0; j<sizeInt; j++){
                if(highest<=heights[i][j])
                    highest = heights[i][j];
            }
        }
        return highest;
    }
    //replaces flooded positions with '*' and dry with '-' from 2D heights array, water level is a parameter
    public void printFloodMap(int waterLevel){
        for(int i=0; i<sizeInt; i++){
            for(int j=0; j<sizeInt; j++){
                if(heights[i][j] >= waterLevel)
                    System.out.print("-");
                else
                    System.out.print("*");
            }
            System.out.print("\n");
        }
    }
}
