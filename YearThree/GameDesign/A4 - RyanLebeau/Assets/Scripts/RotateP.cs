using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotateP : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}

    // FixedUpdate is called once per 0.2s
    void FixedUpdate () {
        transform.Rotate(0.0f, 0.6f, 0.0f);
	}
}
