using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LaserBeam : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    private void OnTriggerEnter(Collider other) {
        if (other.tag == "Cubey" || other.tag == "FCubey" || other.tag == "SB") {
            HUD.kills += 1;
            Destroy(other.gameObject);
        }
    }
}
