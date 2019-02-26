using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CMStartScript : MonoBehaviour {
    //start button
    public void startButton() {
        SceneManager.LoadScene("CMDifficultyScene");
    }

    //exit button
    public void exitButton() {
        Application.Quit();
    }

}
