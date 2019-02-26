using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Slicing : MonoBehaviour {
    public static RaycastHit hit, mouse;
    public static Ray sliceRay;
    public static int layMask;
    public static bool beingHit;
    public CubeSpawn cspawn;
    public ParticleSystem cutLine;

	// Use this for initialization
	void Start () {
        cspawn = FindObjectOfType(typeof(CubeSpawn)) as CubeSpawn;
        layMask = 1 << 8;
        layMask = ~layMask;
        beingHit = false;
	}
	
	// Update is called once per frame
	void Update () {
        if (Input.GetMouseButton(0)) {
            //get ray to mouse from camera
            sliceRay = Camera.main.ScreenPointToRay(Input.mousePosition);
            //mouse slice particle effect
            if (Physics.Raycast(sliceRay, out mouse)) {
                cutLine.transform.position = mouse.point;
                cutLine.Play();
            }
            //if ray hits cube set hit to true and save which cube
            if (Physics.Raycast(sliceRay, out hit, 100.0f, layMask, QueryTriggerInteraction.Ignore)){
                beingHit = true;
                CubeSpawn.hitCube = hit;
                CubeSpawn.ifCalcTraj = true;
            }
            //if ray has been hitting cube and no longer does (sliced)
            else if(!Physics.Raycast(sliceRay, out hit, 100.0f, layMask, QueryTriggerInteraction.Ignore) && beingHit) {
                //use tag to distinguish which cube was sliced
                if (CubeSpawn.hitCube.collider.tag == "BigCube" || CubeSpawn.hitCube.collider.tag == "BigCubeS")
                    SliceBig();
                if (CubeSpawn.hitCube.collider.tag == "MedCube")
                    SliceMed();
                if (CubeSpawn.hitCube.collider.tag == "SmallCube")
                    SliceSmall();
                beingHit = false;
            }
        }
        //if cube was just clicked
        else {
            CubeSpawn.ifCalcTraj = false;
            cutLine.Pause();
            cutLine.Clear();
        }
	}

    //when a big cube is sliced
    public void SliceBig() {
        //paricle effect
        cspawn.MedSpawn();
        if(CubeSpawn.hitCube.collider.tag == "BigCubeS") {
            ScreenBounds.scoreNum += 5;
        }
        else {
            ScreenBounds.scoreNum += 1;
        } 
    }

    //when a medium cube is sliced
    public void SliceMed() {
        cspawn.SmallSpawn();
        ScreenBounds.scoreNum += 2;
    }

    //when a small cube is sliced
    public void SliceSmall() {
        cspawn.SmallerSpawn();
        ScreenBounds.scoreNum += 3;
    }
}
