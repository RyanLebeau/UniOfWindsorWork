/**
 * Ryan Lebeau - 104535367
 * 60-254
 * 2017/11/17
 */

import java.util.*;

public class Vertex {
    private ArrayList<Vertex> edges = new ArrayList<>();
    public int id;
    //constructor to set the id of vertex
    public Vertex(int con){
        id = con;
    }
    //addign an edge to the current vertex
    public void addEdge(Vertex e){
        edges.add(e);
    }
    //return arraylist of edges for current vertex
    public ArrayList<Vertex> getEdges(){
        return edges;
    }
    public int getID(){
        return id;
    }

    @Override
    public String toString(){
        String temp = id +" -> ";
        for(Vertex v:edges){
            temp = temp + v.id +" ";
        }
        return temp;
    }

}


