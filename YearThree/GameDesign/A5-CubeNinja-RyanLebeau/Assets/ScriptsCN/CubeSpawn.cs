using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CubeSpawn : MonoBehaviour {
    public static List<GameObject> bCubes,mCubes,sCubes,ssCubes,inactiveObj;
    public static float xTraj, yTraj;
    public static int spawnsNum;
    public static bool ifCalcTraj;
    public static RaycastHit hitCube;
    public GameObject bCube, mCube, sCube, ssCube;
    public List<Vector3> spawns = new List<Vector3>();
    public List<Vector3> spawns2 = new List<Vector3>();
    public Material blue, green, red, yellow, chrome;
    public Vector3 medDir, medDir2, medStartPos, mSP2, smallDir, smallDir2, smallStartPos, sSP2,
                    smallerDir, smallerDir2, smallerStartPos, ssSP2;
    public float currTime, x, y, xT1, xT2, yT1, yT2;
    public bool swap = false;

	// Use this for initialization
	void Start () {
        bCubes = new List<GameObject>();
        mCubes = new List<GameObject>();
        sCubes = new List<GameObject>();
        ssCubes = new List<GameObject>();
        inactiveObj = new List<GameObject>();
        //spawn points
        spawns.Add(new Vector3(7.0f, -5.0f, 0.0f));
        spawns.Add(new Vector3(4.0f, -5.0f, 0.0f));
        spawns.Add(new Vector3(1.25f, -5.0f, 0.0f));
        spawns.Add(new Vector3(-1.25f, -5.0f, 0.0f));
        spawns.Add(new Vector3(-4.0f, -5.0f, 0.0f));
        spawns.Add(new Vector3(-7.0f, -5.0f, 0.0f));
        //spawn points for seperate z position to prevent collisions
        spawns2.Add(new Vector3(7.0f, -5.0f, 3.0f));
        spawns2.Add(new Vector3(4.0f, -5.0f, 3.0f));
        spawns2.Add(new Vector3(1.25f, -5.0f, 3.0f));
        spawns2.Add(new Vector3(-1.25f, -5.0f, 3.0f));
        spawns2.Add(new Vector3(-4.0f, -5.0f, 3.0f));
        spawns2.Add(new Vector3(-7.0f, -5.0f, 3.0f));
        ifCalcTraj = false;
        xT1 = 0; yT1 = 0;
    }
	
	// FixedUpdate is called 0.02fps
	void FixedUpdate () {
        currTime += Time.fixedDeltaTime;
        //spawn bCube every 2s at random spawn point
        if(currTime >= 2.0) {
            spawnsNum = Random.Range(0, 6);
            //1 in 25 chance to spawn a special cube with bonus points
            if (Random.Range(0, 25) == 1) {
                bCubes.Add(Instantiate(bCube, spawns[spawnsNum], new Quaternion(0, 0, 0, 0)));
                bCubes[bCubes.Count - 1].GetComponent<Renderer>().material = chrome;
                bCubes[bCubes.Count - 1].transform.tag = "BigCubeS";
            }
            //spawning a normal cube
            else {
                //offset z position of cubes to prevent constant collision easily
                if (swap) {
                    bCubes.Add(Instantiate(bCube, spawns[spawnsNum], new Quaternion(0, 0, 0, 0)));
                    swap = !swap;
                }
                else {
                    bCubes.Add(Instantiate(bCube, spawns2[spawnsNum], new Quaternion(0, 0, 0, 0)));
                    swap = !swap;
                }
                //bCubes.Add(Instantiate(bCube, spawns[spawnsNum], new Quaternion(0, 0, 0, 0)));
                bCubes[bCubes.Count - 1].GetComponent<Renderer>().material = blue;
            }
            MoveCube();
            currTime = 0;
        }
        if (ifCalcTraj == true) {
            CalcTraj();
        }
    }

    //set movement for cube randomly
    void MoveCube() {
        int x;
        while (true) {
            //if the cube spawned is a special cube
            if (bCubes[bCubes.Count - 1].transform.tag == "BigCubeS") {
                //if cube is spawning on edge of screen 'toss' towards middle
                if (spawnsNum == 0)
                    x = -6;
                else if (spawnsNum == 5)
                    x = 6;
                else
                    x = Random.Range(-1, 2)*6;
                if (x != 0)
                    break;
            }
            else {
                if (spawnsNum == 0)
                    x = Random.Range(-5, 0);
                else if (spawnsNum == 5)
                    x = Random.Range(1, 6);
                else
                    x = Random.Range(-5, 6);
                if (x != 0)
                    break;
            }
        }
        int y = Random.Range(10, 15);
        bCubes[bCubes.Count - 1].GetComponent<Rigidbody>().velocity = new Vector3(x, y, 0);
    }

    //calculate current velocity of cube being sliced for spawned in cubes
    void CalcTraj() {
        xT2 = xT1;
        xT1 = hitCube.collider.transform.position.x;
        yT2 = yT1;
        yT1 = hitCube.collider.transform.position.y;
        xTraj = Mathf.Abs(xT1 - xT2) / 0.02f;
        yTraj = Mathf.Abs(yT1 - yT2) / 0.02f;
        //in case slice was done too fast to calculate velocity (very rare)
        if (yTraj > 5.0f) { yTraj = 5.0f; }
        if (xTraj > 5.0f) { xTraj = 5.0f; }
    }

    //spawn in medium cubes
    public void MedSpawn() {
        ifCalcTraj = false;
        hitCube.rigidbody.isKinematic = true;
        //defining cubes velocity
        medDir = new Vector3(xTraj, yTraj+3, 0.0f);
        medDir2 = new Vector3(xTraj, yTraj+2.5f, 0.0f);
        medStartPos = new Vector3(hitCube.transform.position.x+0.3f, hitCube.transform.position.y, -2.0f);
        mSP2 = new Vector3(hitCube.transform.position.x, hitCube.transform.position.y, -2.0f);
        //spawning in cubes
        mCubes.Add(Instantiate(mCube, medStartPos, new Quaternion(0, 0, 0, 0)));
        mCubes[mCubes.Count - 1].GetComponent<Renderer>().material = green;
        mCubes.Add(Instantiate(mCube, mSP2, new Quaternion(0, 0, 0, 0)));
        mCubes[mCubes.Count - 1].GetComponent<Renderer>().material = green;
        //setting cubes veloctiy
        mCubes[mCubes.Count - 2].GetComponent<Rigidbody>().velocity = medDir;
        mCubes[mCubes.Count - 1].GetComponent<Rigidbody>().velocity = medDir2;
        //turning off objects without causing errors between box colliders
        inactiveObj.Add(hitCube.collider.gameObject);
        hitCube.collider.gameObject.SetActive(false);
    }

    //spawn in small cubes
    public void SmallSpawn() {
        ifCalcTraj = false;
        hitCube.rigidbody.isKinematic = true;
        //defining cubes velocity
        smallDir = new Vector3(xTraj, yTraj + 1.5f, 0.0f);
        smallDir2 = new Vector3(xTraj, yTraj + 1, 0.0f);
        smallStartPos = new Vector3(hitCube.transform.position.x + 0.3f, hitCube.transform.position.y, -4.0f);
        sSP2 = new Vector3(hitCube.transform.position.x, hitCube.transform.position.y, -4.0f);
        //spawning in cubes
        sCubes.Add(Instantiate(sCube, smallStartPos, new Quaternion(0, 0, 0, 0)));
        sCubes[sCubes.Count - 1].GetComponent<Renderer>().material = red;
        sCubes.Add(Instantiate(sCube, sSP2, new Quaternion(0, 0, 0, 0)));
        sCubes[sCubes.Count - 1].GetComponent<Renderer>().material = red;
        //setting cubes veloctiy
        sCubes[sCubes.Count - 2].GetComponent<Rigidbody>().velocity = smallDir;
        sCubes[sCubes.Count - 1].GetComponent<Rigidbody>().velocity = smallDir2;
        //turning off objects without causing errors between box colliders
        inactiveObj.Add(hitCube.collider.gameObject);
        hitCube.collider.gameObject.SetActive(false);
    }

    //spawn in smaller cubes
    public void SmallerSpawn() {
        ifCalcTraj = false;
        hitCube.rigidbody.isKinematic = true;
        //defining cubes velocity
        smallerDir = new Vector3(xTraj, yTraj + 1.5f, 0.0f);
        smallerDir2 = new Vector3(xTraj, yTraj + 1, 0.0f);
        smallerStartPos = new Vector3(hitCube.transform.position.x + 0.1f, hitCube.transform.position.y, -4.0f);
        ssSP2 = new Vector3(hitCube.transform.position.x, hitCube.transform.position.y, -4.0f);
        //spawning in cubes
        ssCubes.Add(Instantiate(ssCube, smallerStartPos, new Quaternion(0, 0, 0, 0)));
        ssCubes[ssCubes.Count - 1].GetComponent<Renderer>().material = yellow;
        ssCubes.Add(Instantiate(ssCube, ssSP2, new Quaternion(0, 0, 0, 0)));
        ssCubes[ssCubes.Count - 1].GetComponent<Renderer>().material = yellow;
        //setting cubes veloctiy
        ssCubes[ssCubes.Count - 2].GetComponent<Rigidbody>().velocity = smallerDir;
        ssCubes[ssCubes.Count - 1].GetComponent<Rigidbody>().velocity = smallerDir2;
        //turning off objects without causing errors between box colliders
        inactiveObj.Add(hitCube.collider.gameObject);
        hitCube.collider.gameObject.SetActive(false);
    }
}
