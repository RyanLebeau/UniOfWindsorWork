import java.util.Scanner;

public class problemThreeTester {
    public static void main(String[] args) {
        problemThree ticTacToe = new problemThree();
        Scanner input = new Scanner(System.in);
        ticTacToe.printBoard();
        //loop that runs until board is full or a player wins
        while(!ticTacToe.isFull()){
            //player 1 turn
            System.out.println("Enter co-ordinates player 1(x,y): ");
            ticTacToe.addPositionCell(1, input.next());
            ticTacToe.printBoard();
            if(ticTacToe.checkWin()==1){
                System.out.println("Player 1 Wins!");
                break;
            }
            //player 2 turn
            System.out.println("Enter co-ordinates player 2(x,y): ");
            ticTacToe.addPositionCell(2, input.next());
            ticTacToe.printBoard();
            if(ticTacToe.checkWin()==2) {
                System.out.println("Player 2 Wins!");
                break;
            }
        }
        //if the game board is full and neither player has won
        if(ticTacToe.isFull() && ticTacToe.checkWin()==0){
            System.out.println("There is no winner please play again...");
        }
    }
}
