using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SafeZone : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
    void OnTriggerEnter(Collider col) {
        //if player enters safe zone
        if(col.name == "Player")
            col.gameObject.tag = "Safe";
    }
    void OnTriggerStay(Collider col) {
        //if player stays in safe zone
        if (col.name == "Player")
            col.gameObject.tag = "Safe";
    }
    void OnTriggerExit(Collider col) {
        //if player exits safe zone
        if (col.name == "Player")
            col.gameObject.tag = "Play";
    }
}
