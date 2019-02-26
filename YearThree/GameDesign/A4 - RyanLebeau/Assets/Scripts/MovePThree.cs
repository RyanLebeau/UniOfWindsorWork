using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovePThree : MonoBehaviour {
    public Vector3 move = new Vector3(0.0f, 0.0f, 0.075f); 
	// Use this for initialization
	void Start () {
		
	}

    // FixedUpdate is called once per 0.2s
    void FixedUpdate () {
        if (transform.position.z <= 12.5)
            move.z = (0.075f);
        else if (transform.position.z >= 18)
            move.z = (-0.075f);
        transform.Translate(move);
    }
}
