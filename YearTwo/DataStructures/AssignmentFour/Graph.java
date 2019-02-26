/**
 * Ryan Lebeau - 104535367
 * 60-254
 * 2017/11/17
 */

import java.util.*;

public class Graph {
    private ArrayList<Vertex> vertices = new ArrayList<>();
    private int size=0;
    //to add a vertex to graph
    public void addVertex(int id){
        vertices.add(new Vertex(id));
        size++;
    }
    //adding edges to the vertex
    public void addEdge(int start, int end){
        vertices.get(start).addEdge(vertices.get(end));
    }
    //return the vertex at certain position
    public Vertex getVertex(int position){
        return vertices.get(position);
    }
    @Override
    public String toString(){
        String temp = "";
        for(Vertex v: vertices){
            temp = temp + v.toString()+"\n";
        }
        return temp;
    }
}
