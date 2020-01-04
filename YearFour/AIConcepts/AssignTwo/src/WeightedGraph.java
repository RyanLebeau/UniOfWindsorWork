/*
Ryan Lebeau
COMP3710
Due 15/10/2019
WeightedGraph.java - class that defines a wieghted graph in java with 3 specific needed functions I implemented
I did not design this graph class from scratch
some credit has to go to https://algorithms.tutorialhorizon.com/weighted-graph-implementation-java/
since I have never made a weighted graph in java before
 */

import java.util.*;

public class WeightedGraph {
    static class Edge {
        NodeP source;
        NodeP destination;
        int weight;

        public Edge(NodeP source, NodeP destination, int weight) {
            this.source = source;
            this.destination = destination;
            this.weight = weight;
        }
    }

    static class Graph {
        int vertices;
        LinkedList<Edge>[] adjacencylist;

        Graph(int vertices) {
            this.vertices = vertices;
            adjacencylist = new LinkedList[vertices];
            //initialize adjacency lists for all the vertices
            for (int i = 0; i < vertices; i++) {
                adjacencylist[i] = new LinkedList<>();
            }
        }

        public void addEdge(NodeP source, NodeP destination, int weight, int nodeNum) {
            Edge edge = new Edge(source, destination, weight);
            adjacencylist[nodeNum].addFirst(edge); //for directed graph
        }

        public void printGraph() {
            for (int i = 0; i < vertices; i++) {
                LinkedList<Edge> list = adjacencylist[i];
                for (int j = 0; j < list.size(); j++) {
                    System.out.println("vertex-" + i + " is connected to " +
                            list.get(j).destination + " with weight " + list.get(j).weight);
                }
            }
        }

        //will find the smallest edge weight node that hasnt been visited
        public NodeP FindSmallest(List<NodeP> visited){
            int smallestWeight=1000;
            NodeP dest = visited.get(0);
            //go through entire graph
            for (int i = 0; i < vertices; i++) {
                LinkedList<Edge> list = adjacencylist[i];
                for (int j = 0; j < list.size(); j++) {
                    //if this is the current largest weight and is not parent
                    if(list.get(j).weight <= smallestWeight && !CheckParent(list.get(j).source, list.get(j).destination)
                            && !CheckVisited(visited, list.get(j).destination)){
                        smallestWeight = list.get(j).weight;
                        dest = list.get(j).destination;
                    }
                }
            }
            return dest;
        }

        //will return true if source node is destinations parent
        public boolean CheckParent(NodeP source, NodeP dest){
            if(source.CheckDuplicate(dest.puzzle))
                return true;
            else
                return false;
        }

        //will return true if source node is destinations parent
        public boolean CheckVisited(List<NodeP> visited, NodeP dest){
            for(int i=0;i<visited.size();i++){
                if(visited.get(i).CheckDuplicate(dest.puzzle))
                    return true;
            }
            return false;
        }
    }
}