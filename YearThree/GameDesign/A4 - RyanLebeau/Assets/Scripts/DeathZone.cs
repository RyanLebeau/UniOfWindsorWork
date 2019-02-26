using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DeathZone : MonoBehaviour {
    public Vector3 startPos = new Vector3(0.0f, 2.0f, 0.0f);
    public static int death = 0;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    void OnTriggerStay(Collider col) {
        //if player is not in safe zone
        if (col.tag == "Play") {
            col.gameObject.transform.position = startPos;
            death++;
        }
    }
}
