using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class FollowPlayer : MonoBehaviour {
    public Vector3 currSpherePos = new Vector3();
    public Text score, deaths;

	// Use this for initialization
	void Start () {
        Camera.main.transform.rotation = Quaternion.Euler(30.0f, 40.0f, 0.0f);
    }

    // Update is called once per frame
    void Update() {
        if (EndZone.end) {
            score.text = "";
            deaths.text = "";
        }
        else {
            score.text = "Cubes: " + Coins.score;
            deaths.text = "Deaths: " + DeathZone.death;
        }
        
    }

	// FixedUpdate is called once per 0.2s
	void FixedUpdate () {
        currSpherePos = MoveSphere.currentPos;
        currSpherePos.y += 5.0f;
        currSpherePos.x -= 5.2f;
        currSpherePos.z -= 5.5f;
        transform.position = currSpherePos;
	}
}
