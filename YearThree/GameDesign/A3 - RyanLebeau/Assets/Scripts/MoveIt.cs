using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveIt : MonoBehaviour {
    Vector3 pos = new Vector3(1.0f, 0.0f, 0.0f);

    // Use this for initialization
    void Start () {
        
    }
    
    void FixedUpdate() {
        transform.Translate(pos * Time.fixedDeltaTime);
        if (transform.position.x >= 2.0f) { pos.x = -1.0f; }
        else if (transform.position.x <= -2.0f) { pos.x = 1.0f; }
    }
}
