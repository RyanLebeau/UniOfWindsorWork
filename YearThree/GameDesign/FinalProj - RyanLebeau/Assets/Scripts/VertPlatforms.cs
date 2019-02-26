using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VertPlatforms : MonoBehaviour {
    public float currTime = 0.0f;
    public Vector3 move;

    // Use this for initialization
    void Start() {
        //rate of 4units/3 seconds
        move = new Vector3(0, -0.04f, 0);
    }

    // FixedUpdate is called once per 0.02s
    void FixedUpdate() {
        currTime += Time.fixedDeltaTime;
        if (currTime >= 2) {
            move.y *= -1;
            currTime = 0;
        }
        gameObject.transform.Translate(move);
        if(gameObject.transform.position.y <= -1) {
            move.y *= -1;
            currTime = 0;
        }
    }
}
