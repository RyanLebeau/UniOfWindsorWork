using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class RPSmainScript : MonoBehaviour {
    public GameObject rockPrefab, paperPrefab, scissorPrefab;
    public static GameObject Display, DisplayC;
    public Text userScoreText, compScoreText, playerText, compText, gameText;
    public static int gamesPlayed = 0, scoreUser = 0, scoreComp = 0, userChoice;
    public static float compChoice;
    public bool displayChoice;
    public static bool compSelection;


    // Use this for initialization
    void Start () {
        //define prefab references
        rockPrefab = GameObject.FindGameObjectWithTag("Rock");
        paperPrefab = GameObject.FindGameObjectWithTag("Paper");
        scissorPrefab = GameObject.FindGameObjectWithTag("Scissor");
        //define text references
        userScoreText.text = "Score: ";
        compScoreText.text = "Score: ";
        gameText.text = "Game: ";
    }
	
	// Update is called once per frame
	void Update (){
        //rotating selection options
        rockPrefab.transform.Rotate(1, 0, 0);
        paperPrefab.transform.Rotate(0, 1, 0);
        scissorPrefab.transform.Rotate(1, 0, 0);
        //updating scores
        userScoreText.text = "Score: " + scoreUser.ToString();
        compScoreText.text = "Score: " + scoreComp.ToString();
        gameText.text = "Game: " + gamesPlayed.ToString();
        //if game has finished
        if (gamesPlayed >= 10) {
            ChangeScene();
        }
    }

    //if rock is selected
    public void RockClick() {
        //user selection
        if (!compSelection) {
            //if a rock is already displayed destroy it
            if (displayChoice == true) { Destroy(Display); }
            else { displayChoice = true; }
            //create a rock and display
            Display = Instantiate(rockPrefab) as GameObject;
            Vector3 posPlayer = Vector3.zero;
            posPlayer.x = 4;
            posPlayer.y = 3;
            Display.transform.position = posPlayer;
            userChoice = 1;
            //have computer select choice
            ComPick();
        }
        //computer selection
        else {
            if (displayChoice == true) { Destroy(DisplayC); }
            else { displayChoice = true; }
            DisplayC = Instantiate(rockPrefab) as GameObject;
            Vector3 posPlayer = Vector3.zero;
            posPlayer.x = 4;
            posPlayer.y = -2;
            DisplayC.transform.position = posPlayer;
            compSelection = false;
            compChoice = 1;
        }
    }
    //if paper is selected
    public void PaperClick() {
        //user selection
        if (!compSelection) {
            if (displayChoice == true) { Destroy(Display); }
            else { displayChoice = true; }
            Display = Instantiate(paperPrefab) as GameObject;
            Vector3 posPlayer = Vector3.zero;
            posPlayer.x = 4;
            posPlayer.y = 3;
            Display.transform.position = posPlayer;
            userChoice = 2;
            ComPick();
        }
        //computer selection
        else {
            if (displayChoice == true) { Destroy(DisplayC); }
            else { displayChoice = true; }
            DisplayC = Instantiate(paperPrefab) as GameObject;
            Vector3 posPlayer = Vector3.zero;
            posPlayer.x = 4;
            posPlayer.y = -2;
            DisplayC.transform.position = posPlayer;
            compSelection = false;
            compChoice = 2;
        }
    }
    //if scissors are selected
    public void ScissorClick() {
        //user selection
        if (!compSelection) {
            if (displayChoice == true) { Destroy(Display); }
            else { displayChoice = true; }
            Display = Instantiate(scissorPrefab) as GameObject;
            Vector3 posPlayer = Vector3.zero;
            posPlayer.x = 4;
            posPlayer.y = 3;
            Display.transform.position = posPlayer;
            userChoice = 3;
            ComPick();
        }
        //computer selection
        else {
            if (displayChoice == true) { Destroy(DisplayC); }
            else { displayChoice = true; }
            DisplayC = Instantiate(scissorPrefab) as GameObject;
            Vector3 posPlayer = Vector3.zero;
            posPlayer.x = 4;
            posPlayer.y = -2;
            DisplayC.transform.position = posPlayer;
            compSelection = false;
            compChoice = 3;
        }
    }

    //random selection for computer
    public void ComPick() {
        //set boolean handling if computer is making choice to true
        compSelection = true;
        compChoice = Random.value;
        //each option has 30%chance
        if(compChoice < 0.3) { RockClick(); }
        else if(compChoice>0.3 && compChoice <= 0.6) { PaperClick(); }
        else if(compChoice>0.6 && compChoice <= 0.9) { ScissorClick(); }
        Winner();
    }

    //deciding a winner
    public void Winner() {
        //if tie
        if (userChoice == compChoice) {
            gamesPlayed++;
        }
        //if user wins
        else if(userChoice==1 && compChoice==3 || userChoice==2 && compChoice==1 || userChoice==3 && compChoice == 2) {
            scoreUser++;
            gamesPlayed++;
        }
        //if computer wins
        else {
            scoreComp++;
            gamesPlayed++;
        }
    }

    //next scene
    public void ChangeScene() {
        SceneManager.LoadScene("RPSEndScene");
    }
}
