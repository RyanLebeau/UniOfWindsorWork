using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class endScript : MonoBehaviour {
    public Text userScoreText;
    public Text winOrLose;
    public static int score, compScore;

	// Use this for initialization
	void Start () {
        score = mainScript.scoreUser;
        compScore = mainScript.scoreComp;
        GameWinner();
        TextUpdate();
    }
	
	// Update is called once per frame
	void Update () {
        
    }

    //updating text
    public void TextUpdate() {
        userScoreText.text = "Your Score: " + score.ToString();
    }

    //displaying if the use rwon or lost the game
    public void GameWinner() {
        if(score == compScore) {
            winOrLose.text = "Tie Game";
            winOrLose.color = Color.black;
        }
        else if (score > compScore) {
            winOrLose.text = "You Win!";
            winOrLose.color = Color.green;
        }
        else {
            winOrLose.text = "You Lose";
            winOrLose.color = Color.red;
        }
    }
}
