/*
Ryan Lebeau
COMP3710
Due 15/10/2019
MainProblem.java - handles user input to run each search algorithm
 */

import java.util.*;

public class MainProblem {
    public static void main(String[] args) {
        char[][] puzzle = {
            {'5', '1', '2', '4'},
            {'6', 'A', '3', '7'},
            {'9', ' ', 'C', '8'},
            {'D', 'E', 'B', 'F'}
        };
        //creating root node and search controller
        NodeP root = new NodeP(puzzle);
        Searches searchController = new Searches();
        //user input
        Scanner myScan = new Scanner(System.in);
        System.out.println("Please enter the search method (BFS, GBFSh1, GBFSh2, AStarh1, AStarh2, )");
        String search = myScan.nextLine();
        //calling each search function on root node then to their output handler
        switch (search.toLowerCase()){
            case "bfs":
                BFSOutput(searchController.BFS(root)); break;
            case "gbfsh1":
                GBFSOutput(searchController.GBFS(root, 1)); break;
            case "gbfsh2":
                GBFSOutput(searchController.GBFS(root, 2)); break;
            case "astarh1":
                AStarOutput(searchController.AStar(root, 1)); break;
            case "astarh2":
                AStarOutput(searchController.AStar(root, 2)); break;
            default:
                System.out.println("That was not an option. Options are BFS, GBFSh1, GBFSh2, AStarh1, AStarh2, ");
        }
    }

    //print out all required fields for BFS search
    public static void BFSOutput(Object[] solStuff){
        //cast objects from solution array to their type
        List<NodeP> solution = (List<NodeP>) solStuff[0];
        int nodesExp = (int) solStuff[1];
        int nodesAccs = (int) solStuff[2];
        System.out.println("--- Breadth First Search");
        if(solution.size() == 0)
            System.out.println("No path to goal state found.");
        else{
            //print out goal path
            for(int i=solution.size()-1; i>=0; i--){
                solution.get(i).PrintPuzzle();
            }
            //depth of the solution
            System.out.println("The depth of the solution was "+(solution.size()-1));
            //number of nodes expanded
            System.out.println("The number of nodes expanded was "+nodesExp+" (excluding root)");
            //number of nodes accessed
            System.out.println("The number of nodes accessed was "+nodesAccs+" (excluding root)\n");
        }
    }

    //print out all required fields for GBFS search
    public static void GBFSOutput(Object[] solStuff){
        //cast objects from solution array to their type
        List<NodeP> solution = (List<NodeP>) solStuff[0];
        int nodesExp = (int) solStuff[1];
        int nodesAccs = (int) solStuff[2];
        int hValue = (int) solStuff[3];

        System.out.println("--- Greedy Best First Search");
        //printing if h1 or h2 were used
        if(hValue == 1)
            System.out.println("--- Misplaced Tiles Heuristic");
        else
            System.out.println("--- Manhattan Distance Heuristic");

        if(solution.size() == 0)
            System.out.println("No path to goal state found. 1000 node cap");
        else{
            //print out goal path
            for(int i=solution.size()-1; i>=0; i--){
                solution.get(i).PrintPuzzle();
            }
            //depth of the solution
            System.out.println("The depth of the solution was "+(solution.size()-1));
            //number of nodes expanded
            System.out.println("The number of nodes expanded was "+nodesExp+" (excluding root)");
            //number of nodes accessed
            System.out.println("The number of nodes accessed was "+nodesAccs+" (excluding root)");
        }
    }

    //print out all required fields for AStar search
    public static void AStarOutput(Object[] solStuff){
        //cast objects from solution array to their type
        List<NodeP> solution = (List<NodeP>) solStuff[0];
        int nodesExp = (int) solStuff[1];
        int nodesAccs = (int) solStuff[2];
        int hValue = (int) solStuff[3];

        System.out.println("--- A* Search");
        //printing if h1 or h2 were used
        if(hValue == 1)
            System.out.println("--- Misplaced Tiles Heuristic");
        else
            System.out.println("--- Manhattan Distance Heuristic");

        if(solution.size() == 0)
            System.out.println("No path to goal state found. 1000 node cap");
        else{
            //print out goal path
            for(int i=solution.size()-1; i>=0; i--){
                solution.get(i).PrintPuzzle();
            }
            //depth of the solution
            System.out.println("The depth of the solution was "+(solution.size()-1));
            //number of nodes expanded
            System.out.println("The number of nodes expanded was "+nodesExp+" (excluding root)");
            //number of nodes accessed
            System.out.println("The number of nodes accessed was "+nodesAccs+" (excluding root)");
        }
    }
}
