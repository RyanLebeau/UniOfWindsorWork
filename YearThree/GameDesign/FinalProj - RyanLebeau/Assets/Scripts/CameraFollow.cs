using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraFollow : MonoBehaviour {
    public Vector3 cameraPos = new Vector3();
    public Vector3 leftBoundPos = new Vector3();
    public Vector3 leftBoundTrigPos = new Vector3();
    public GameObject leftBound, leftBoundTrig, leftBoundIns, leftBoundTrigIns;

	// Use this for initialization
	void Start () {
        Camera.main.transform.rotation = Quaternion.Euler(8.0f, 0.0f, 0.0f);
        leftBoundIns = Instantiate(leftBound, new Vector3(-13, 7.5f, 0), new Quaternion(0, 0, 0, 0));
        leftBoundTrigIns = Instantiate(leftBoundTrig, new Vector3(-14.1f, 7.5f, 0), new Quaternion(0, 0, 0, 0));
    }
	
	// Update is called once per frame
	void Update () {
        cameraPos = Character.currentPos;
        cameraPos.y = 8.25f;
        cameraPos.z = -12.0f;
        transform.position = cameraPos;
        leftBoundPos = Character.currentPos;
        leftBoundPos.x -= 13.0f;
        leftBoundPos.y = 7.5f;
        leftBoundPos.z = 0;
        leftBoundIns.transform.position = leftBoundPos;
        leftBoundTrigPos = Character.currentPos;
        leftBoundTrigPos.x -= 14.5f;
        leftBoundTrigPos.y = 7.5f;
        leftBoundTrigPos.z = 0;
        leftBoundTrigIns.transform.position = leftBoundTrigPos;
    }
}
