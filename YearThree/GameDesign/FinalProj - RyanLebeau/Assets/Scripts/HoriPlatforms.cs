using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HoriPlatforms : MonoBehaviour {
    public float currTime = 0.0f;
    public Vector3 move;

	// Use this for initialization
	void Start () {
        //rate of 12units/3s
        move = new Vector3(0.08f, 0, 0);
    }
	
	// FixedUpdate is called once per 0.02s
	void FixedUpdate () {
        currTime += Time.fixedDeltaTime;
        if (currTime >= 3) {
            move.x *= -1;
            currTime = 0;
        }
        gameObject.transform.Translate(move);
	}
}
