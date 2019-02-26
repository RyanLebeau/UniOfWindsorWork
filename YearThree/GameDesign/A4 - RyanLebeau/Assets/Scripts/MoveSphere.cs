using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveSphere : MonoBehaviour {
    public Vector3 forward = new Vector3(0.0f, 0.0f, 0.1f);
    public Vector3 backward = new Vector3(0.0f, 0.0f, -0.1f);
    public Vector3 left = new Vector3(-0.1f, 0.0f, 0.0f);
    public Vector3 right = new Vector3(0.1f, 0.0f, 0.0f);
    public Vector3 jump = new Vector3(0.0f, 4.0f, 0.0f);
    public static Vector3 currentPos = new Vector3();
    public static Vector3 startPos = new Vector3();
    public static float currentTime = 0.01f;
    public static bool ifJump = false;

    // Use this for initialization
    void Start () {
		
	}

    // Update is called once per frame
    void Update () {
        //jump 
        if (Input.GetKeyDown(KeyCode.Space)) {
            ifJump = true;
            currentTime = 0.01f;
            print(startPos.y);
        }
    }

    // FixedUpdate is called once per 0.2s
    void FixedUpdate () {
        //Moving with WASD or arrow keys
        if (Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.UpArrow)) {
            transform.Translate(forward);
        }
        if (Input.GetKey(KeyCode.S) || Input.GetKey(KeyCode.DownArrow)) {
            transform.Translate(backward);
        }
        if (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.LeftArrow)) {
            transform.Translate(left);
        }
        if (Input.GetKey(KeyCode.D) || Input.GetKey(KeyCode.RightArrow)) {
            transform.Translate(right);
        }
        
        //get current position
        currentPos = transform.position;
        //jump for 0.4s at speed of 7.5units/s
        if (ifJump) {
            GetComponent<Rigidbody>().velocity = new Vector3(0, 7.5f, 0);
            currentTime += Time.fixedDeltaTime;
            if(currentTime >= 0.4f) {
                //reduces arc hang time
                GetComponent<Rigidbody>().velocity = new Vector3(0, -0.01f, 0);
                ifJump = false;
                currentTime = 0.01f;
                print(currentPos.y);
            }
        }
    }
}
