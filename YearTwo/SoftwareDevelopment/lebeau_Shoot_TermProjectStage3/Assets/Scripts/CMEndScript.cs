using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

public class CMEndScript : MonoBehaviour {
    public Text win, time;
    public AudioSource sourceA;
    public AudioClip winSound, loseSound;
    public static int timerNumber=0;
    public List<string> memHistory;

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
        memHistory = new List<string>();
        loadScore();
        memHistory.Add(LoginScript.currUser + "     " + System.DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss") + "     " + CMMain.scoreNum.ToString() + "pts left");
    }

    void Update() {
        time.text = "Time Elapsed: " + timerNumber + "s";
    }

    private void OnDisable() {
        saveScore();
    }

    //loading start scene and resetting arrays
    public void exitButton() {
        saveScore();
        Application.Quit();
    }

    public void loadScore() {
        if (File.Exists(Application.persistentDataPath + "/memSave.dat")) {
            BinaryFormatter binF = new BinaryFormatter();
            FileStream file = File.Open(Application.persistentDataPath + "/memSave.dat", FileMode.Open);
            MemorySaves memsave = (MemorySaves)binF.Deserialize(file);
            file.Close();
            memHistory = memsave.memHistory;
        }
    }

    //saving user lists between launches
    public void saveScore() {
        BinaryFormatter binF = new BinaryFormatter();
        FileStream file = File.Create(Application.persistentDataPath + "/memSave.dat");
        //setting data in container
        MemorySaves memsave = new MemorySaves();
        memsave.memHistory = memHistory;
        //writing data to file
        binF.Serialize(file, memsave);
        file.Close();
    }
}

//container class to easily write needed data
[System.Serializable]
class MemorySaves {
    public List<string> memHistory;
}
