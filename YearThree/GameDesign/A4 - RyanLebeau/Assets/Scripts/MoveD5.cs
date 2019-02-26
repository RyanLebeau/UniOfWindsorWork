using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveD5 : MonoBehaviour {
    public Vector3 move = new Vector3();
    public float currTime = 0;
    public int direction = 1;
	// Use this for initialization
	void Start () {
		
	}

    // FixedUpdate is called once per 0.2s
    void FixedUpdate () {
        //move death zone for 2 seconds then change direction
        if(currTime >= 2.0) {
            direction *= -1;
            currTime = 0;
        }
        currTime += Time.fixedDeltaTime;
        move.z = 0.03f;
        transform.Translate(move*direction);
	}
}
