using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BasketC : MonoBehaviour {

    public ApplePickerC scoreScript;

	// Use this for initialization
	void Start () {
        scoreScript = Camera.main.GetComponent<ApplePickerC>();
    }
	
	// Update is called once per frame
	void Update () {
        //mouse screen position
        Vector3 mousePos2D = Input.mousePosition;
        //using camera z position to base mouse position
        mousePos2D.z = -Camera.main.transform.position.z;
        //convert from 2D to 3D game position
        Vector3 mousePos3D = Camera.main.ScreenToWorldPoint(mousePos2D);
        //match mouse and basket x positions
        Vector3 pos = this.transform.position;
        pos.x = mousePos3D.x;
        this.transform.position = pos;
        //scoreScript.scoreCur = 20;
	}

    //If basket catches apple
    void OnCollisionEnter(Collision coll) {
        GameObject collided = coll.gameObject;
        if (collided.tag == "Apple") {
            Destroy(collided);
            scoreScript.scoreCur += 1;
            if (scoreScript.scoreCur > scoreScript.hScoreCur) {
                scoreScript.hScoreCur += 1;
            }
        }
    }
}
