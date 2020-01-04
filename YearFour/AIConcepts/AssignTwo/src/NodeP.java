/*
Ryan Lebeau
COMP3710
Due 15/10/2019
NodeP.java - Designs the node class which is each state in the tree (puzzle)
 */

import java.util.*;

public class NodeP {
    public List<NodeP> children = new ArrayList<NodeP>();
    public NodeP parent;
    public int weight = 0;
    public char[][] puzzle;
    public char[][] goalPuzzle ={
            {'1', '2', '3', '4'},
            {'5', '6', '7', '8'},
            {'9', 'A', 'B', 'C'},
            {'D', 'E', 'F', ' '}
    };

    //constructor that sets current puzzle
    public NodeP(char[][] puz){
        puzzle = puz;
    }

    //MOVES
    //do all possible moves at once (makes life easier)
    public int MoveAll(){
        //count how many were expanded
        boolean[] success = new boolean[4];
        int expand=0;

        success[0] = MoveDown(puzzle);
        success[1] = MoveLeft(puzzle);
        success[2] = MoveRight(puzzle);
        success[3] = MoveUp(puzzle);
        for(int i=0;i<4;i++){
            if(success[i])
                expand++;
        }
        return expand;
    }
    //move to the left
    public boolean MoveLeft(char[][] puzF){
        //get where the space is in the puzzle
        int[] coords = SpaceLocater(puzF);
        //check if space can be moved left
        if(coords[1] == 0)
            return false;
        char[][] puz = new char[4][4];
        CopyPuzzle(puz, puzF);
        //swap space to left
        char temp = puz[coords[0]][coords[1]-1];
        puz[coords[0]][coords[1]-1] = puz[coords[0]][coords[1]];
        puz[coords[0]][coords[1]] = temp;
        //set this puzzle as new puzzle for child
        NodeP child = new NodeP(puz);
        child.parent = this;
        children.add(child);
        return true;
    }
    //move to the right
    public boolean MoveRight(char[][] puzF){
        //get where the space is in the puzzle
        int[] coords = SpaceLocater(puzF);
        //check if space can be moved right
        if(coords[1] == 3)
            return false;
        char[][] puz = new char[4][4];
        CopyPuzzle(puz, puzF);
        //swap space to right
        char temp = puz[coords[0]][coords[1]+1];
        puz[coords[0]][coords[1]+1] = puz[coords[0]][coords[1]];
        puz[coords[0]][coords[1]] = temp;
        //set this puzzle as new puzzle for child
        NodeP child = new NodeP(puz);
        child.parent = this;
        children.add(child);
        return true;
    }
    //move down
    public boolean MoveDown(char[][] puzF){
        //get where the space is in the puzzle
        int[] coords = SpaceLocater(puzF);
        //check if space can be moved down
        if(coords[0] == 3)
            return false;
        char[][] puz = new char[4][4];
        CopyPuzzle(puz, puzF);
        //swap space down
        char temp = puz[coords[0]+1][coords[1]];
        puz[coords[0]+1][coords[1]] = puz[coords[0]][coords[1]];
        puz[coords[0]][coords[1]] = temp;
        //set this puzzle as new puzzle for child
        NodeP child = new NodeP(puz);
        child.parent = this;
        children.add(child);
        return true;
    }
    //move up
    public boolean MoveUp(char[][] puzF){
        //get where the space is in the puzzle
        int[] coords = SpaceLocater(puzF);
        //check if space can be moved up
        if(coords[0] == 0)
            return false;
        char[][] puz = new char[4][4];
        CopyPuzzle(puz, puzF);
        //swap space up
        char temp = puz[coords[0]-1][coords[1]];
        puz[coords[0]-1][coords[1]] = puz[coords[0]][coords[1]];
        puz[coords[0]][coords[1]] = temp;
        //set this puzzle as new puzzle for child
        NodeP child = new NodeP(puz);
        child.parent = this;
        children.add(child);
        return true;
    }

    //copy puzzle a to puzzle b
    public void CopyPuzzle(char[][] a, char[][] b){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                a[i][j] = b[i][j];
            }
        }
    }

    //check if the puzzle is the same as an entered puzzle
    public boolean CheckDuplicate(char[][] puz){
        //iterate through entire puzzle
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                //if the puzzles are not identical then return false
                if(puz[i][j] != puzzle[i][j])
                    return false;
            }
        }
        return true;
    }

    //locate space in puzzle and return its x,y coords
    public int[] SpaceLocater(char[][] puz){
        int[] coords = new int[2];
        //iterate through entire puzzle
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                //when space is found
                if(puz[i][j] == ' '){
                    coords[0] = i;
                    coords[1] = j;
                }
            }
        }
        return coords;
    }

    //locate character in puzzle and return its coords
    public int[] CharLocater(char[][] puz, char term){
        int[] coords = new int[2];
        //iterate through entire puzzle
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                //when char is found
                if(puz[i][j] == term){
                    coords[0] = i;
                    coords[1] = j;
                }
            }
        }
        return coords;
    }

    //check if nodes puzzle is in its goal state
    public boolean GoalState(){
        //iterate through entire puzzle
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                //if the puzzles are not identical then return false
                if(puzzle[i][j] != goalPuzzle[i][j])
                    return false;
            }
        }
        return true;
    }

    //print the puzzle out to the system
    public void PrintPuzzle(){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(j==3)
                    System.out.print(puzzle[i][j]+"\n");
                else
                    System.out.print(puzzle[i][j]);
            }
        }
        System.out.print("\n");
    }
}
