using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class ScreenBounds : MonoBehaviour {
    public static int scoreNum, dropsNum;
    public float currTime;
    public Text score, drops;

	// Use this for initialization
	void Start () {
        scoreNum = 0;
        dropsNum = 0;
	}

    // Update is called once per frame
    void Update () {
        score.text = "Score: " + scoreNum;
        drops.text = "Drops: " + dropsNum;
        if (dropsNum >= 5) {
            if (PlayerPrefs.HasKey("CubeNinjaScore")) {
                PlayerPrefs.DeleteKey("CubeNinjaScore");
            }
            PlayerPrefs.SetInt("CubeNinjaScore", scoreNum);
            scoreNum = 0;
            SceneManager.LoadScene("EndSceneCN");
        }
    }

    // FixedUpdate is called 0.02fps
    void FixedUpdate () {
        currTime += Time.fixedDeltaTime;
        //destroy all gameobjects that were disabled
        if (currTime > 20) {
            for(int i=CubeSpawn.inactiveObj.Count-2; i >= 0; i--) {
                Destroy(CubeSpawn.inactiveObj[i]);
                CubeSpawn.inactiveObj.RemoveAt(i);
            }
            currTime = 0;
        }
	}

    //remove all game objects that move out of screen
    void OnTriggerExit(Collider col) {
        if(col.tag == "BigCube" || col.tag == "MedCube" || col.tag == "SmallCube" || col.tag == "SmallerCube") {
            if(col.tag == "BigCube") {
                dropsNum += 1; 
            }
            CubeSpawn.inactiveObj.Add(col.gameObject);
            col.gameObject.SetActive(false);
        }
    }
}
