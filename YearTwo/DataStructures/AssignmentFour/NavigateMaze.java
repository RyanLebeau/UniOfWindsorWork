/**
 * Ryan Lebeau - 104535367
 * 60-254
 * 2017/11/17
 */

import java.util.*;
import java.io.*;

public class NavigateMaze {
    public static void main(String[] args) throws FileNotFoundException{
        Graph maze = new Graph();
        Queue que = new Queue();
        ArrayList<Integer> SPath = new ArrayList<>();
        int size=0, start=0, end=0;

        File input = new File("input.txt");
        Scanner scan = new Scanner(input);
        //gathering first three input lines
        String StrSize = scan.nextLine();
        String StrStart = scan.nextLine();
        String StrEnd = scan.nextLine();
        size = Integer.parseInt(StrSize);
        start = Integer.parseInt(StrStart);
        end = Integer.parseInt(StrEnd);
        //adding all vertices for graph (rooms for maze)
        for(int i=0;i<size;i++){
            maze.addVertex(i);
        }
        //adding all edges for graph vertices (which rooms connect)
        for(int i=0;i<size;i++){
            String temp = scan.nextLine();
            String[] values = temp.split(",");
            for(int j=0;j<size;j++){
                //System.out.print(values[j]);
                if(values[j].equals("1"))
                    maze.addEdge(i, j);
            }
        }
        //creating array for past visits and populating with -1
        int[] past = new int[size];
        for(int i=0;i<size;i++){
            past[i] = -1;
        }
        //boolean array for if a vertex has been visited
        boolean[] visit = new boolean[size];
        int VertexID,FoundID,currPos=end;

        que.enqueue(maze.getVertex(start));
        //while the queue is not empty
        while(!que.ifEmpty()){
            Vertex curr = que.dequeue();
            VertexID = curr.getID();
            //if vertex has not been visited
            if(!visit[VertexID]) {
                visit[VertexID] = true;
                //for all edge connections in the current vertex
                for(Vertex found: curr.getEdges()) {
                    FoundID = found.getID();
                    //if found vertex not yet handled
                    if(!visit[FoundID]) {
                        que.enqueue(found);
                        //if this is first time getting to vertex set its past position to the current vertex
                        if (past[FoundID] == -1) {
                            past[FoundID] = VertexID;
                        }
                    }
                }
            }
        }
        //if the solution is the starting vertex
        if(start==end)
            System.out.println("Shortest Path: "+start);
        //if there is no solution
        else if(past[end]==-1)
            System.out.println("There is no solution to this maze");
        else{
            SPath.add(currPos);
            //add all vertices that were required to reach end to the SPath
            while(past[currPos]!=-1){
                SPath.add(past[currPos]);
                currPos = past[currPos];
            }
            //since SPath is populated from finish to end print in reverse
            System.out.println("Shortest Path: ");
            for(int i=SPath.size()-1;i>0;i--){
                System.out.print(SPath.get(i)+", ");
            }
            System.out.print(SPath.get(0));
        }
    }
}
