using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class EndCN : MonoBehaviour {
    public Text finalScore;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        finalScore.text = "Score: " + PlayerPrefs.GetInt("CubeNinjaScore");
    }

    public void ExitButton() {
        //ENTER MAIN MENU SCENE NAME
        //SceneManager.LoadScene("");
        ScreenBounds.scoreNum = 0;
        ScreenBounds.dropsNum = 0;
    }
}
