using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;

public class ApplePickerC : MonoBehaviour {

    public GameObject basketPrefab;
    public int numBaskets = 3;
    public float basketBottom = -1.5f;
    public float basketSpacing = 1f;
    public int scoreCur = 0;
    public int hScoreCur = 5;
    public Text playerScore;
    public Text highScore;
    public List<GameObject> basketList;
    public List<string> appleHistory;

    private void Awake() {
        //storing highscore
        if (PlayerPrefs.HasKey("ApplePickerHiScore")) {
            hScoreCur = PlayerPrefs.GetInt("ApplePickerHiScore");
        }
        PlayerPrefs.SetInt("ApplePickerHiScore", hScoreCur);
        //storing player score
        Scene currentScene = SceneManager.GetActiveScene();
        string sceneName = currentScene.name;
        if (PlayerPrefs.HasKey("ApplePickerCurScore") && sceneName == "AP_Scene_0") {
            PlayerPrefs.DeleteKey("ApplePickerCurScore");
            PlayerPrefs.SetInt("ApplePickerCurScore", scoreCur);
        }
        else {
            scoreCur = PlayerPrefs.GetInt("ApplePickerCurScore");
        }
        appleHistory = new List<string>();
        loadScore();
    }

    // Use this for initialization
    void Start() {
        basketList = new List<GameObject>();
        for (int i = 0; i < numBaskets; i++) {
            GameObject topBasket = Instantiate(basketPrefab) as GameObject;
            Vector3 pos = Vector3.zero;
            pos.y = basketBottom + (basketSpacing * i);
            topBasket.transform.position = pos;
            basketList.Add(topBasket);
        }
    }

    // Update is called once per frame
    void Update() {
        playerScore.text = "Score: " + scoreCur.ToString();
        highScore.text = "HighScore: " + hScoreCur.ToString();
        if (hScoreCur > PlayerPrefs.GetInt("ApplePickerHiScore")) {
            PlayerPrefs.SetInt("ApplePickerHiScore", hScoreCur);
        }
        if (scoreCur > PlayerPrefs.GetInt("ApplePickerCurScore")) {
            PlayerPrefs.SetInt("ApplePickerCurScore", scoreCur);
        }
    }

    public void OnDisable() {
        if (scoreCur > 0) {
            saveScore();
        }
    }

    //If an apple has fallen past the basket
    public void AppleDestroyed() {
        //destroying all apples on screen
        GameObject[] appleArr = GameObject.FindGameObjectsWithTag("Apple");
        foreach (GameObject appleGO in appleArr) {
            Destroy(appleGO);
        }
        //removing a basket
        int basketIndex = basketList.Count - 1;
        GameObject basketCur = basketList[basketIndex];
        basketList.RemoveAt(basketIndex);
        Destroy(basketCur);
        //ending game
        if (basketList.Count == 0) {
            appleHistory.Add(LoginScript.currUser + "     " + System.DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss") + "     " + scoreCur.ToString()+"pts");
            SceneManager.LoadScene("APdeathScene");
        }
    }

    //exit button
    public void exitBttn() {
        saveScore();
        Application.Quit();
    }
    
    public void loadScore() {
        if (File.Exists(Application.persistentDataPath + "/appleSave.dat")) {
            BinaryFormatter binF = new BinaryFormatter();
            FileStream file = File.Open(Application.persistentDataPath + "/appleSave.dat", FileMode.Open);
            AppleSaves asave = (AppleSaves)binF.Deserialize(file);
            file.Close();
            appleHistory = asave.appleHistory;
        }
    }

    //saving user lists between launches
    public void saveScore() {
        BinaryFormatter binF = new BinaryFormatter();
        FileStream file = File.Create(Application.persistentDataPath + "/appleSave.dat");
        //setting data in container
        AppleSaves asave = new AppleSaves();
        asave.appleHistory = appleHistory;
        //writing data to file
        binF.Serialize(file, asave);
        file.Close();
    }
}

//container class to easily write needed data
[System.Serializable]
class AppleSaves {
    public List<string> appleHistory;
}

