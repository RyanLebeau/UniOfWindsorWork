using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotateIt : MonoBehaviour {
    Vector3 rot = new Vector3(30f, 60f, 90f);

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void FixedUpdate () {
        transform.Rotate(rot*Time.fixedDeltaTime);
	}
}
