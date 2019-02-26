using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ResizeIt : MonoBehaviour {
    Vector3 scale = new Vector3(1.0f, 1.0f, 1.0f);

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void FixedUpdate () {
        transform.localScale += scale * Time.fixedDeltaTime;
        if (transform.localScale.x >= 4.0f) { scale = new Vector3(-1.0f, -1.0f, -1.0f); }
        else if (transform.localScale.x <= 1.0f) { scale = new Vector3(1.0f, 1.0f, 1.0f); }
    }
}
