/**
 * Ryan Lebeau - 104535367
 * 60-254
 * 2017/11/17
 */

import java.util.*;

public class Queue {
    private ArrayList<Vertex> vertices = new ArrayList<>();
    //add vertex to the back of queue
    public void enqueue(Vertex v){
        vertices.add(v);
    }
    //removes element from front of queue and returns it
    public Vertex dequeue(){
        Vertex temp = vertices.get(0);
        vertices.remove(0);
        return temp;
    }
    //if the queue is empty return true
    public boolean ifEmpty(){
        if(vertices.size() == 0)
            return true;
        else
            return false;
    }
}
