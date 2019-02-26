/**
 * Ryan Lebeau - 104535367
 * 60-212
 * 2017/11/03
 * Tic Tac Toe Game
 */

public class problemThree {
    public String[][] gameBoard = new String[3][3];
    //constructor that populates gameBoard with empty spaces for printing
    public problemThree(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                    gameBoard[i][j] = "";
            }
        }
    }

    //receives input position string and which user is playing then sets game piece at position
    public void addPositionCell(int user, String position){
        int posXY[] = {Character.getNumericValue(position.charAt(0)), Character.getNumericValue(position.charAt(2))};
        if(user==1){
            gameBoard[posXY[0]][posXY[1]] = "O";
        }
        else{
            gameBoard[posXY[0]][posXY[1]] = "X";
        }
    }
    //returns the number of player that has won, if no winner return 0
    public int checkWin(){
        //check for horizontal and vertical wins
        for(int i=0; i<3; i++){
            if(gameBoard[i][0].equals("O") && gameBoard[i][1].equals("O") && gameBoard[i][2].equals("O")){
                return 1;
            }
            else if(gameBoard[i][0].equals("X") && gameBoard[i][1].equals("X") && gameBoard[i][2].equals("X")){
                return 2;
            }
            else if(gameBoard[0][i].equals("O") && gameBoard[1][i].equals("O") && gameBoard[2][i].equals("O")){
                return 1;
            }
            else if(gameBoard[0][i].equals("X") && gameBoard[1][i].equals("X") && gameBoard[2][i].equals("X")){
                return 2;
            }
        }
        //check for both diagonal cases
        if(gameBoard[0][0].equals("O") && gameBoard[1][1].equals("O") && gameBoard[2][2].equals("O")){
            return 1;
        }
        else if(gameBoard[0][2].equals("O") && gameBoard[1][1].equals("O") && gameBoard[2][0].equals("O")){
            return 1;
        }
        else if(gameBoard[0][0].equals("X") && gameBoard[1][1].equals("X") && gameBoard[2][2].equals("X")){
            return 2;
        }
        else if(gameBoard[0][2].equals("X") && gameBoard[1][1].equals("X") && gameBoard[2][0].equals("X")){
            return 2;
        }
        return 0;
    }
    //check if board is full, returns true if full and false if not full
    public boolean isFull(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(!gameBoard[i][j].equals("O") && !gameBoard[i][j].equals("X")){
                    return false;
                }
            }
        }
        return true;
    }
    //prints the game board to users
    public void printBoard(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(gameBoard[i][j].equals("O") || gameBoard[i][j].equals("X")){
                    if(j<2)
                        System.out.print(gameBoard[i][j]+" | ");
                    else
                        System.out.print(gameBoard[i][j]);
                }
                else{
                    if(j<2)
                        System.out.print("- | ");
                    else
                        System.out.print("-");
                }

            }
            System.out.print("\n");
        }
    }
}
