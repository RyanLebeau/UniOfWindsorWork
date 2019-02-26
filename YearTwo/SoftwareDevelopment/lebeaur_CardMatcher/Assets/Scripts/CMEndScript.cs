using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class CMEndScript : MonoBehaviour {
    public Text win, time;
    public AudioSource sourceA;
    public AudioClip winSound, loseSound;
    public static int timerNumber=0;

	// Use this for initialization
	void Start () {
        timerNumber = CMMain.timerNum;
        //if user wins
        if (CMMain.winOrLose) {
            win.text = "YOU WIN!";
            sourceA.PlayOneShot(winSound);
        }
        //if user loses
        else {
            win.text = "YOU LOSE!";
            sourceA.PlayOneShot(loseSound);
        }
	}

    void Update() {
        time.text = "Time Elapsed: " + timerNumber + "s";
    }

    //loading start scene and resetting arrays
    public void restartButton() {
        SceneManager.LoadScene("CMStartScene");
        CMMain.scoreNum = 1000;
        CMMain.timerNum = 0;
        CMMain.countMatches = 0;
        for(int i = 0; i < CMMain.cardTagNum.Length; i++) {
            CMMain.cardTagNum[i] = 0;
        }
    }
}
