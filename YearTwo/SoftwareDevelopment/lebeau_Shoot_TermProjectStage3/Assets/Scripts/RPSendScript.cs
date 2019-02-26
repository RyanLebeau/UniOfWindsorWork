using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using UnityEngine;
using UnityEngine.UI;

public class RPSendScript : MonoBehaviour {
    public Text userScoreText;
    public Text winOrLose;
    public static int score, compScore;
    public List<string> rpsHistory;

	// Use this for initialization
	void Start () {
        score = RPSmainScript.scoreUser;
        compScore = RPSmainScript.scoreComp;
        GameWinner();
        TextUpdate();
        rpsHistory = new List<string>();
        loadScore();
        rpsHistory.Add(LoginScript.currUser + "     " + System.DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss") + "     " + score.ToString() + "pts");
    }
	
	// Update is called once per frame
	void Update () {
        
    }

    private void OnDisable() {
        saveScore();
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

    public void ExitBttn() {
        saveScore();
        Application.Quit();
    }

    public void loadScore() {
        if (File.Exists(Application.persistentDataPath + "/rpsSave.dat")) {
            BinaryFormatter binF = new BinaryFormatter();
            FileStream file = File.Open(Application.persistentDataPath + "/rpsSave.dat", FileMode.Open);
            RpsSaves rpssave = (RpsSaves)binF.Deserialize(file);
            file.Close();
            rpsHistory = rpssave.rpsHistory;
        }
    }

    //saving user lists between launches
    public void saveScore() {
        BinaryFormatter binF = new BinaryFormatter();
        FileStream file = File.Create(Application.persistentDataPath + "/rpsSave.dat");
        //setting data in container
        RpsSaves rpssave = new RpsSaves();
        rpssave.rpsHistory = rpsHistory;
        //writing data to file
        binF.Serialize(file, rpssave);
        file.Close();
    }
}

//container class to easily write needed data
[System.Serializable]
class RpsSaves {
    public List<string> rpsHistory;
}
