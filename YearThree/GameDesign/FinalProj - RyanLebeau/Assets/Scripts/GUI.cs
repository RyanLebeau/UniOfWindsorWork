using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GUI : MonoBehaviour {
    public Canvas splash, menu, levels, instruct, highs, levelInfo;
    public Text lOneHighT, lTwoHighT, lThreeHighT, lvlInfoTitle, LOne, LTwo, LThree;
    public GameObject audioM;

	// Use this for initialization
	void Start () {
        //play menu music
        audioM.GetComponent<Audio>().playMusic(audioM.GetComponent<Audio>().menuM);
        splash.gameObject.SetActive(true);
        menu.gameObject.SetActive(false);
        levels.gameObject.SetActive(false);
        instruct.gameObject.SetActive(false);
        highs.gameObject.SetActive(false);
        levelInfo.gameObject.SetActive(false);
        //loading highscores
        if (PlayerPrefs.HasKey("lOneHighC")) {
            lOneHighT.text = "Level One: " + PlayerPrefs.GetInt("lOneHighC") + "coin(s) -- " +
                PlayerPrefs.GetInt("lOneHighK") + "kill(s) -- " + PlayerPrefs.GetInt("lOneHighD") + "death(s)";
        }
        else {
            lOneHighT.text = "Level One: No highscore data";
        }
        if (PlayerPrefs.HasKey("lTwoHighC")) {
            lTwoHighT.text = "Level Two: " + PlayerPrefs.GetInt("lTwoHighC") + "coin(s) -- " +
                PlayerPrefs.GetInt("lTwoHighK") + "kill(s) -- " + PlayerPrefs.GetInt("lTwoHighD") + "death(s)";
        }
        else {
            lTwoHighT.text = "Level Two: No highscore data";
        }
        if (PlayerPrefs.HasKey("lThreeHighC")) {
            lThreeHighT.text = "Level Three: " + PlayerPrefs.GetInt("lThreeHighC") + "coin(s) -- " +
                PlayerPrefs.GetInt("lThreeHighK") + "kill(s) -- " + PlayerPrefs.GetInt("lThreeHighD") + "death(s)";
        }
        else {
            lThreeHighT.text = "Level Three: No highscore data";
        }
    }
	
	// Update is called once per frame
	void Update () {
		
	}

    public void SplashStartBttn() {
        //play button sound
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().clickS);
        splash.gameObject.SetActive(false);
        menu.gameObject.SetActive(true);
    }

    public void MenuLevelsBttn() {
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().clickS);
        menu.gameObject.SetActive(false);
        levels.gameObject.SetActive(true);
    }
    public void LevelsOneBttn() {
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().clickS);
        levels.gameObject.SetActive(false);
        levelInfo.gameObject.SetActive(true);
        lvlInfoTitle.text = "Level 1 Info";
        LOne.gameObject.SetActive(true);
        LTwo.gameObject.SetActive(false);
        LThree.gameObject.SetActive(false);
        ProcGen.levelNum = 1;
    }
    public void LevelsTwoBttn() {
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().clickS);
        levels.gameObject.SetActive(false);
        levelInfo.gameObject.SetActive(true);
        lvlInfoTitle.text = "Level 2 Info";
        LOne.gameObject.SetActive(false);
        LTwo.gameObject.SetActive(true);
        LThree.gameObject.SetActive(false);
        ProcGen.levelNum = 2;
    }
    public void LevelsThreeBttn() {
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().clickS);
        levels.gameObject.SetActive(false);
        levelInfo.gameObject.SetActive(true);
        lvlInfoTitle.text = "Level 3 Info";
        LOne.gameObject.SetActive(false);
        LTwo.gameObject.SetActive(false);
        LThree.gameObject.SetActive(true);
        ProcGen.levelNum = 3;
    }
    public void LevelStartBttn() {
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().clickS);
        levelInfo.gameObject.SetActive(false);
        LOne.gameObject.SetActive(false);
        LTwo.gameObject.SetActive(false);
        LThree.gameObject.SetActive(false);
        SceneManager.LoadScene("Levels");
    }

    public void MenuInstructBttn() {
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().clickS);
        menu.gameObject.SetActive(false);
        instruct.gameObject.SetActive(true);
    }

    public void MenuHighsBttn() {
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().clickS);
        menu.gameObject.SetActive(false);
        highs.gameObject.SetActive(true);
    }

    public void BackToMenuBttn() {
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().clickS);
        splash.gameObject.SetActive(false);
        menu.gameObject.SetActive(true);
        highs.gameObject.SetActive(false);
        levels.gameObject.SetActive(false);
        instruct.gameObject.SetActive(false);
    }

    public void ExitGameBttn() {
        //audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().clickS);
        Application.Quit();
    }
}
