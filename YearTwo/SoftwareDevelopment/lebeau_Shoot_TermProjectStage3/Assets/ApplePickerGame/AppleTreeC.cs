using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AppleTreeC : MonoBehaviour {

    public GameObject applePrefab;
    public float speed = 1f;
    public float movementBounds = 12f;
    public float changeDirectionChance = 0.1f;
    public float appleDropRate = 1f;

    // Use this for initialization
    void Start () {
        InvokeRepeating("AppleDrop", 2f, appleDropRate);
	}
	
    void AppleDrop() {
        GameObject apple = Instantiate(applePrefab) as GameObject;
        Vector3 APos = transform.position;
        APos.x -= 2.5f;
        apple.transform.position = APos;
        
    }

	// Update is called once per frame
	void Update () {
        Vector3 pos = transform.position;
        pos.x += speed * Time.deltaTime;
        transform.position = pos;
        
        //at right bounds begin movement left
        if(pos.x > movementBounds){
            speed = -Mathf.Abs(speed);
        }
        //at left bounds begin movement right
        else if(pos.x < -movementBounds){
            speed = Mathf.Abs(speed);
        }
 
	}

    // Update is called 50 times per second
    void FixedUpdate() {
        if (Random.value < changeDirectionChance) {
            speed *= -1;
        }
    }
}
