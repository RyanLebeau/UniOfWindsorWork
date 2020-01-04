/*
Ryan Lebeau
COMP3710
Due 15/10/2019
Searches.java - class containing all the specific search algorithms and their related functions
 */

import java.util.*;

public class Searches {
    public Searches(){

    }

    public Object[] BFS(NodeP root){
        System.out.println("Processing...");
        List<NodeP> solution = new ArrayList<NodeP>();
        List<NodeP> unVisited = new ArrayList<NodeP>();
        List<NodeP> visited = new ArrayList<NodeP>();
        Object[] neededSolutions = new Object[3];
        int nodesExp = 0; int nodesAccs = 0;
        //add root node to the unvisited list
        unVisited.add(root);
        boolean goalFound = false;
        //loop to go trhough each node
        while(unVisited.size() > 0 && !goalFound){
            //add current node to visited
            NodeP currentNode = unVisited.get(0);
            visited.add(currentNode);
            unVisited.remove(0);
            //if our current state is goal, exit loop
            if(currentNode.GoalState()) {
                goalFound = true;
                solution.add(currentNode);
                break;
            }
            //create all children of current node and track how many were expanded
            nodesExp += currentNode.MoveAll();
            //add to the number of nodes expanded
            //nodesExp++;
            //loop through each child created
            for(int i=0;i<currentNode.children.size();i++){
                NodeP childNode = currentNode.children.get(i);
                //childNode.PrintPuzzle();
                //check if child is the goal state
                if(childNode.GoalState()) {
                    goalFound = true;
                    solution = TraceSolution(childNode);
                    break;
                }
                //check if child node has already been visited (if a path can not be found to solution)
                if(!PrevVisited(visited, childNode) && !PrevVisited(unVisited, childNode))
                    unVisited.add(childNode);

                //add to the number of nodes accessed
                nodesAccs++;
            }

            //if a solution was found when going through children
            if(goalFound){
                neededSolutions[0] = solution;
                neededSolutions[1] = nodesExp;
                neededSolutions[2] = nodesAccs;
                break;
            }
        }
        return neededSolutions;
    }

    public Object[] GBFS(NodeP root, int h){
        System.out.println("Processing...");
        List<NodeP> solution = new ArrayList<NodeP>();
        List<NodeP> visited = new ArrayList<NodeP>();
        List<NodeP> unVisited = new ArrayList<NodeP>();
        WeightedGraph.Graph tree = new WeightedGraph.Graph(1000);
        int nodesExp = 0; int nodesAccs = 0;
        Object[] neededSolutions = new Object[4];
        //add root node to the unvisited list
        boolean goalFound = false;
        unVisited.add(root);

        //loop to go through each node
        while(unVisited.size() > 0){
            NodeP currentNode;
            //set current node to root
            if(nodesExp == 0){
                currentNode = unVisited.get(0);
                visited.add(currentNode);
                unVisited.remove(0);
            }
            //check back from root through to each node for lowest edge weight as long as node
            //is not in visited list, unvisited is pointless since this will decide which node to use now
            else{
                currentNode = tree.FindSmallest(visited);
                visited.add(currentNode);
                System.out.println("Node selected with weight "+currentNode.weight);
            }

            //check if node is solution
            if(currentNode.GoalState()) {
                solution = TraceSolution(currentNode);
                //store variables needed to output to user
                neededSolutions[0] = solution;
                neededSolutions[1] = nodesExp;
                neededSolutions[2] = nodesAccs;
                neededSolutions[3] = h;
                break;
            }
            nodesExp++;

            //create all children of current node and track how many were expanded
            nodesAccs += currentNode.MoveAll();
            //enter them into tree and assign their weights
            for(int i =0;i<currentNode.children.size();i++){
                NodeP childNode = currentNode.children.get(i);
                int weight=0;

                //calculating misplaced tiles value of node
                if(h == 1)
                    weight = MisplacedTiles(childNode);
                //calculating manhattan distance
                else if(h==2){
                    weight = ManhattanDistance(childNode);
                }
                childNode.weight = weight;
                //limits searches to 1000 nodes
                if(nodesAccs-i >= 1000){
                    neededSolutions[0] = solution;
                    neededSolutions[1] = nodesExp;
                    neededSolutions[2] = nodesAccs;
                    neededSolutions[3] = h;
                    break;
                }
                //add edge from parent to child with its weight
                tree.addEdge(currentNode, childNode, weight, nodesAccs-i);

                //check if child node has already been visited (if a path can not be found to solution)
                if(!PrevVisited(visited, childNode) && !PrevVisited(unVisited, childNode))
                   unVisited.add(childNode);
            }
        }
        return neededSolutions;
    }

    public Object[] AStar(NodeP root, int h){
        System.out.println("Processing...");
        List<NodeP> solution = new ArrayList<NodeP>();
        List<NodeP> visited = new ArrayList<NodeP>();
        List<NodeP> unVisited = new ArrayList<NodeP>();
        WeightedGraph.Graph tree = new WeightedGraph.Graph(1000);
        int nodesExp = 0; int nodesAccs = 0;
        Object[] neededSolutions = new Object[4];
        //add root node to the unvisited list
        boolean goalFound = false;
        unVisited.add(root);

        //loop to go through each node
        while(unVisited.size() > 0){
            NodeP currentNode;
            //set current node to root
            if(nodesExp == 0){
                currentNode = unVisited.get(0);
                visited.add(currentNode);
                unVisited.remove(0);
            }
            //check back from root through to each node for lowest edge weight as long as node
            //is not in visited list, unvisited is pointless since this will decide which node to use now
            else{
                currentNode = tree.FindSmallest(visited);
                visited.add(currentNode);
                System.out.println("Node selected with weight "+currentNode.weight);
            }

            //check if node is solution
            if(currentNode.GoalState()) {
                solution = TraceSolution(currentNode);
                //store variables needed to output to user
                neededSolutions[0] = solution;
                neededSolutions[1] = nodesExp;
                neededSolutions[2] = nodesAccs;
                neededSolutions[3] = h;
                break;
            }
            nodesExp++;

            //create all children of current node and track how many were expanded
            nodesAccs += currentNode.MoveAll();
            //enter them into tree and assign their weights
            for(int i =0;i<currentNode.children.size();i++){
                NodeP childNode = currentNode.children.get(i);
                int weight=0;

                //calculating the total weight f(n)=g(n)+h(n)
                if(h == 1){
                    //calculating h(n) cost for misplaced tiles + g(n) cost
                    weight = MisplacedTiles(childNode) + GNCost(childNode);
                }
                else if(h==2){
                    //calculating h(n) cost for manhattan distance  + g(n) cost
                    weight = ManhattanDistance(childNode) + GNCost(childNode);
                }
                childNode.weight = weight;
                //limits searches to 1000 nodes
                if(nodesAccs-i >= 1000){
                    neededSolutions[0] = solution;
                    neededSolutions[1] = nodesExp;
                    neededSolutions[2] = nodesAccs;
                    neededSolutions[3] = h;
                    return neededSolutions;
                }
                //add edge from parent to child with its weight
                tree.addEdge(currentNode, childNode, weight, nodesAccs-i);

                //check if child node has already been visited (if a path can not be found to solution)
                if(!PrevVisited(visited, childNode) && !PrevVisited(unVisited, childNode))
                    unVisited.add(childNode);
            }
        }
        return neededSolutions;
    }

    //will calculate the cost of weights from current node to root
    public int GNCost(NodeP node){
        int cost = 0;
        NodeP parNode = node.parent;
        //add this nodes parents weight
        cost += parNode.weight;
        //add all parent nodes weights to total cost
        while(true){
            parNode = parNode.parent;
            if(parNode != null)
                cost += parNode.weight;
            else
                break;
        }
        //System.out.println(cost);
        return cost;
    }

    //will calculate the manhattan distance of current node
    public int ManhattanDistance(NodeP node){
        int distance=0;
        //loop through full puzzle
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                //x and y of current piece
                int[] coordsNode = node.CharLocater(node.puzzle, node.goalPuzzle[i][j]);
                //add the manhattan distance of this piece to total distance of node
                distance += Math.abs(coordsNode[0] - i) + Math.abs(coordsNode[1] - j);
            }
        }
        return distance;
    }

    //will calculate the misplace tiles value of current node
    public int MisplacedTiles(NodeP node){
        int correctTiles=0;
        //loop through each value in puzzle
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                //check if tile is the same as goal puzzles tile excluding empty tile
                if(node.puzzle[i][j] == node.goalPuzzle[i][j] && node.puzzle[i][j] != ' ')
                    correctTiles++;
            }
        }
        return (16-correctTiles);
    }

    //will check if node curr is in list of entered nodes
    public boolean PrevVisited(List<NodeP> nodes, NodeP curr){
        //if the current nodes puzzle is found in list of puzzles return true
        for(int i=0;i<nodes.size();i++){
            if(curr.CheckDuplicate(nodes.get(i).puzzle)){
                return true;
            }
        }
        //if current nodes puzzle is not found in list of puzzles
        return false;
    }

    //trace back the path of the goal state
    public List<NodeP> TraceSolution(NodeP goal){
        List<NodeP> solution = new ArrayList<>();
        //add final goal state
        solution.add(goal);
        NodeP parNode = goal.parent;
        //add final goal states parent
        solution.add(parNode);
        //add all parent nodes until root to solution list
        while(true){
            parNode = parNode.parent;
            if(parNode != null)
                solution.add(parNode);
            else
                break;
        }
        //return the solution
        return solution;
    }
}
