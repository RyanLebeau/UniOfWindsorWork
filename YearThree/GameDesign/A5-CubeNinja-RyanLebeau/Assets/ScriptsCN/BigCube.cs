using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BigCube : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}

    // FixedUpdate is called 0.02fps
    void FixedUpdate () {
        transform.Rotate(new Vector3(0.6f, 0.6f, 0.6f));
    }
}
