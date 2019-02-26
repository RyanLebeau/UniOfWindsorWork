using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CMDifficultyScript : MonoBehaviour {
    //if user selects easy mode
	public void easyButton() {
        SceneManager.LoadScene("CMMainScene");
        CMMain.easyHard = 1;
    }
    //if user selects hard mode
    public void hardButton() {
        SceneManager.LoadScene("CMMainScene");
        CMMain.easyHard = 2;
    }
}
