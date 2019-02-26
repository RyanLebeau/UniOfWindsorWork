using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class HUD : MonoBehaviour {
    public static int diamonds, coins, kills, deaths, powerUp;
    public static float powTime;
    public static bool endLevelBool, changeScenes = false, displayed = false;
    public Text diaText, coinText, killsText, deathsText, healthText, levelText, powTimerText, endLevelText, endGameText;
    public Color darkRed;
    public Image exitPrompt, pausePrompt, endLevelPrompt, endGamePrompt;
    public GameObject audioM;

	// Use this for initialization
	void Start () {
        //play game music
        audioM.GetComponent<Audio>().playMusic(audioM.GetComponent<Audio>().gameM);
        diamonds = 0; coins = 0;
        kills = 0; deaths = 0;
        darkRed = new Color(1.0f, 0.553f, 0.541f);
        diaText.color = Color.cyan;
        coinText.color = Color.yellow;
        healthText.color = darkRed;
        killsText.color = darkRed;
        deathsText.color = darkRed;
        levelText.color = Color.white;
        powTimerText.color = Color.white;
        powTime = 0;
        powerUp = 0;
    }
	
	// Update is called once per frame
	void Update () {
        diaText.text = "Diamonds: " + diamonds;
        coinText.text = "Coins: " + coins;
        killsText.text = "Kills: " + kills;
        healthText.text = "Health: " + Character.charHealth;
        deathsText.text = "Deaths: " + deaths;
        levelText.text = "Level " + ProcGen.levelNum + "." + ProcGen.sectionNum;
        if (endLevelBool && !displayed) {
            endLevel();
            displayed = true;
        }
        //only change scenes once ProcGen restart level coroutine is finsihed
        if (changeScenes) {
            changeScenes = false;
            SceneManager.LoadScene("MenuScreens");
        }
        if(powTime > 0) {
            if (powerUp == 1) {
                powTimerText.text = "PowerUp: " + powTime.ToString("F1") + " uses";
            }
            else {
                powTimerText.text = "PowerUp Time: " + powTime.ToString("F1") + "s";
                powTime -= Time.deltaTime;
            }
            
        }
        else {
            powTimerText.text = "";
            //reset moving vectors
            if(powerUp == 3) {
                Character.forward = new Vector3(0.1f, 0, 0);
                Character.backward = new Vector3(-0.1f, 0, 0);
                Character.forwardSprint = new Vector3(0.15f, 0, 0);
                Character.backwardSprint = new Vector3(-0.15f, 0, 0);
            }
            if (powerUp == 4) {
                Character.ifShoot = false;
            }
            if (powerUp == 1) {
                Character.ifTeleport = false;
            }
            if (powerUp == 2) {
                Character.ifLaser = false;
            }
        }
	}

    public void pauseButton() {
        //play button sound
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().clickS);
        Time.timeScale = 0;
        pausePrompt.gameObject.SetActive(true);
    }
    public void resumeButton() {
        //play button sound
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().clickS);
        Time.timeScale = 1;
        pausePrompt.gameObject.SetActive(false);
    }
    public void exitButton() {
        //play button sound
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().clickS);
        Time.timeScale = 0;
        exitPrompt.gameObject.SetActive(true);
    }
    public void confirmEButton() {
        //play button sound
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().clickS);
        Time.timeScale = 1;
        exitPrompt.gameObject.SetActive(false);
        endLevelPrompt.gameObject.SetActive(false);
        endGamePrompt.gameObject.SetActive(false);
        coins = 0;
        kills = 0;
        deaths = 0;
        //trigger end of level in ProcGen
        ProcGen.endLevelBool = true;
        ProcGen.endGameBool = true;
        endLevelBool = false;
        displayed = false;
    }
    public void denyEButton() {
        //play button sound
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().clickS);
        Time.timeScale = 1;
        exitPrompt.gameObject.SetActive(false);
    }

    //if end of level platform was reached
    public void endLevel() {
        //highscore
        setHighScore(ProcGen.levelNum);
        print("ran");
        Time.timeScale = 0;
        print("froze");
        //display prompt for user to continue or go to main menu
        if(ProcGen.levelNum != 3) {
            endLevelPrompt.gameObject.SetActive(true);
            endLevelText.text = "You have completed Level " + ProcGen.levelNum + "!\nContinue to next level?";
        }
        else {
            endGamePrompt.gameObject.SetActive(true);
            endGameText.text = "You have completed Level 3!";
        }
    }
    public void nextLevelBttn() {
        //play button sound
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().clickS);
        Time.timeScale = 1;
        //trigger level reset in ProcGen script
        ProcGen.endLevelBool = true;
        endLevelBool = false;
        endLevelPrompt.gameObject.SetActive(false);
        ProcGen.levelNum += 1;
        displayed = false;
    }
    public void setHighScore(int levelNum) {
        if(levelNum == 1) {
            //check or set highscore
            if (PlayerPrefs.HasKey("lOneHighC")) {
                //change back to coins
                if (PlayerPrefs.GetInt("lOneHighC") < coins) {
                    PlayerPrefs.SetInt("lOneHighC", coins);
                    PlayerPrefs.SetInt("lOneHighK", kills);
                    PlayerPrefs.SetInt("lOneHighD", deaths);
                }
            }
            else {
                //first highscore set
                PlayerPrefs.SetInt("lOneHighC", coins);
                PlayerPrefs.SetInt("lOneHighK", kills);
                PlayerPrefs.SetInt("lOneHighD", deaths);
            }
        }
        else if (levelNum == 2){
            //check or set highscore
            if (PlayerPrefs.HasKey("lTwoHighC")) {
                if (PlayerPrefs.GetInt("lTwoHighC") < coins) {
                    PlayerPrefs.SetInt("lTwoHighC", coins);
                    PlayerPrefs.SetInt("lTwoHighK", kills);
                    PlayerPrefs.SetInt("lTwoHighD", deaths);
                }
            }
            //first highscore set
            else {
                PlayerPrefs.SetInt("lTwoHighC", coins);
                PlayerPrefs.SetInt("lTwoHighK", kills);
                PlayerPrefs.SetInt("lTwoHighD", deaths);
            }
        }
        else if (levelNum == 3) {
            //check or set highscore
            if (PlayerPrefs.HasKey("lThreeHighC")) {
                if (PlayerPrefs.GetInt("lThreeHighC") < coins) {
                    PlayerPrefs.SetInt("lThreeHighC", coins);
                    PlayerPrefs.SetInt("lThreeHighK", kills);
                    PlayerPrefs.SetInt("lThreeHighD", deaths);
                }
            }
            //first highscore set
            else {
                PlayerPrefs.SetInt("lThreeHighC", coins);
                PlayerPrefs.SetInt("lThreeHighK", kills);
                PlayerPrefs.SetInt("lThreeHighD", deaths);
            }
        }
    }
}
