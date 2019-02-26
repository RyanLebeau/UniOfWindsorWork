using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AppleC : MonoBehaviour {
    public float bottomBound = -7f;
    public ApplePickerC apScript;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		if(transform.position.y < bottomBound) { 
            Destroy(this.gameObject);
            //signalling to 'ApplePicker' that apple was dropped past basket
            apScript = Camera.main.GetComponent<ApplePickerC>();
            apScript.AppleDestroyed();
        }
	}
}
