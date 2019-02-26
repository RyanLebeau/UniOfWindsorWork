using System.Collections; // Required for Arrays & other Collections
using System.Collections.Generic; // Required to use Lists or Dictionaries
using UnityEngine; // Required for Unity
using UnityEngine.UI;
using UnityEngine.SceneManagement; // For loading & reloading of scenes
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

public class Main : MonoBehaviour {
    static public Main S; // A singleton for Main
    static Dictionary<WeaponType, WeaponDefinition> WEAP_DICT;
    [Header("Set in Inspector")]
    public GameObject[] prefabEnemies; // Array of Enemy prefabs
    public float enemySpawnPerSecond = 0.5f; // # Enemies/second
    public float enemyDefaultPadding = 1.5f; //Padding for position
    public WeaponDefinition[] weaponDefinitions;
    public GameObject prefabPowerUp, backgroundGO, e0, e1, e2, e3, e4;
    public WeaponType[] powerUpFrequency = new WeaponType[] {WeaponType.blaster,WeaponType.blaster,WeaponType.spread, WeaponType.shield};
    private BoundsCheck bndCheck;
    public static int currentScore, currentLvl, randNum, spawnCount, e0Kills, e1Kills, e2Kills, e3Kills, e4Kills;
    public static float currentTime;
    public Text scoreTxt, e0KillsTxt, e1KillsTxt, e2KillsTxt, e3KillsTxt, e4KillsTxt, bSGTxt, timerTxt;
    public Canvas pauseMenu;
    public Button pauseB;
    public Image bgImage;
    public Texture imgOne, imgTwo, imgThree, imgFour, imgFive, imgSix, imgSeven;
    public Material backgroundMat, e0Mat;
    //, e1Mat, e2Mat, e3Mat, e4Mat
    public Vector3 scaleBg;
    public static AudioSource sourceM;
    public AudioClip m1, m2, m3, s1, s2, s3, w1, w2, w3, d1, d2, d3, bClick;
    public List<string> shmupHistory;

    public void shipDestroyed(Enemy e) {
        // Potentially generate a PowerUp
        if (Random.value <= e.powerUpDropChance) {
            // Choose which PowerUp to pick
            // Pick one from the possibilities in powerUpFrequency
            int ndx = Random.Range(0, powerUpFrequency.Length);
            WeaponType puType = powerUpFrequency[ndx];
            // Spawn a PowerUp
            GameObject go = Instantiate(prefabPowerUp) as GameObject;
            PowerUp pu = go.GetComponent<PowerUp>();
            // Set it to the proper WeaponType
            pu.SetType(puType);
            // Set it to the position of the destroyed ship
            pu.transform.position = e.transform.position;
        }
    }

    void Awake() {
        //initializing variables
        currentLvl = 0;
        scaleBg = new Vector3(GUIscript.xAxisScale, GUIscript.yAxisScale, 0.0f);
        spawnCount = 0;
        currentScore = 0;
        e0Kills = 0; e1Kills = 0; e2Kills = 0; e3Kills = 0; e4Kills = 0;
        currentTime = 0.0f;
        pauseMenu.gameObject.SetActive(false);
        sourceM = GetComponent<AudioSource>();
        //music
        //sourceM.volume = GUIscript.volumeSetting;
        if(GUIscript.musicSNum == 0) { sourceM.PlayOneShot(m1); }
        else if(GUIscript.musicSNum == 1) { sourceM.PlayOneShot(m2); }
        else if (GUIscript.musicSNum == 2) { sourceM.PlayOneShot(m3); }
        sourceM.loop = true;
        //typeEnemySpawns = 0;
        S = this;
        // Set bndCheck to reference the BoundsCheck component on this GameObject
        bndCheck = GetComponent<BoundsCheck>();
        spawnCount++;
        // Invoke SpawnEnemy() once (in 2 seconds, based on default values)
        Invoke("SpawnEnemy", 1f / enemySpawnPerSecond);
        WEAP_DICT = new Dictionary<WeaponType, WeaponDefinition>();
        foreach (WeaponDefinition def in weaponDefinitions) {
            WEAP_DICT[def.type] = def;
        }
        shmupHistory = new List<string>();
        loadScore();
    }

    //use update() to check if score limit is reached
    private void Update() {
        //update text
        scoreTxt.text = "Score: " + currentScore;
        e0KillsTxt.text = "E0 Kills: " + e0Kills;
        e1KillsTxt.text = "E1 Kills: " + e1Kills;
        e2KillsTxt.text = "E2 Kills: " + e2Kills;
        e3KillsTxt.text = "E3 Kills: " + e3Kills;
        e4KillsTxt.text = "E4 Kills: " + e4Kills;
        //counting time
        currentTime += Time.deltaTime;
        timerTxt.text = ""+Mathf.Round(currentTime*100f)/100f;
        //destroy audio
        if (Enemy.destroySound) {
            if(GUIscript.destroySNum == 0) { sourceM.PlayOneShot(d1); }
            else if(GUIscript.destroySNum == 1) { sourceM.PlayOneShot(d2); }
            else if(GUIscript.destroySNum == 2) { sourceM.PlayOneShot(d3); }
            Enemy.destroySound = false;
        }
        //shoot audio
        if (Weapon.shootSound) {
            if(GUIscript.shootSNum == 0) { sourceM.PlayOneShot(s1); }
            else if(GUIscript.shootSNum == 1) { sourceM.PlayOneShot(s2); }
            else if(GUIscript.shootSNum == 2) { sourceM.PlayOneShot(s3); }
            Weapon.shootSound = false;
        }
        //level text
        if(currentLvl == 0) { bSGTxt.text = "Bronze"; setBg(); }
        else if(currentLvl == 1) { bSGTxt.text = "Silver"; }
        else if(currentLvl == 2) { bSGTxt.text = "Gold"; }
        //changing level
        if(currentLvl == 0 && currentScore >= GUIscript.scoreLimitB) {
            currentLvl = 1;
            spawnCount = 0;
            setBg();
            playWin();
        }
        else if(currentLvl == 1 && currentScore >= GUIscript.scoreLimitS) {
            currentLvl = 2;
            spawnCount = 0;
            setBg();
            playWin();
        }
    }

    //set background image
    public void setBg() {
        if(currentLvl == 0) {
            //changing image based off value from dropdown menu
            switch (GUIscript.bImgNum) {
                case 0: backgroundMat.mainTexture = imgOne; break;
                case 1: backgroundMat.mainTexture = imgTwo; break;
                case 2: backgroundMat.mainTexture = imgThree; break;
                case 3: backgroundMat.mainTexture = imgFour; break;
                case 4: backgroundMat.mainTexture = imgFive; break;
                case 5: backgroundMat.mainTexture = imgSix; break;
                case 6: backgroundMat.mainTexture = imgSeven; break;
                default: break;
            }
        }
        else if(currentLvl == 1) {
            switch (GUIscript.sImgNum) {
                case 0: backgroundMat.mainTexture = imgOne; break;
                case 1: backgroundMat.mainTexture = imgTwo; break;
                case 2: backgroundMat.mainTexture = imgThree; break;
                case 3: backgroundMat.mainTexture = imgFour; break;
                case 4: backgroundMat.mainTexture = imgFive; break;
                case 5: backgroundMat.mainTexture = imgSix; break;
                case 6: backgroundMat.mainTexture = imgSeven; break;
                default: break;
            }
        }
        else if(currentLvl == 2) {
            switch (GUIscript.gImgNum) {
                case 0: backgroundMat.mainTexture = imgOne; break;
                case 1: backgroundMat.mainTexture = imgTwo; break;
                case 2: backgroundMat.mainTexture = imgThree; break;
                case 3: backgroundMat.mainTexture = imgFour; break;
                case 4: backgroundMat.mainTexture = imgFive; break;
                case 5: backgroundMat.mainTexture = imgSix; break;
                case 6: backgroundMat.mainTexture = imgSeven; break;
                default: break;
            }
        }
        backgroundGO.transform.localScale = scaleBg*100;
    }

    //play proper win sound
    public void playWin() {
        if(GUIscript.winSNum == 0) { sourceM.PlayOneShot(w1); }
        else if(GUIscript.winSNum == 1) { sourceM.PlayOneShot(w2); }
        else if(GUIscript.winSNum == 2) { sourceM.PlayOneShot(w3); }
    }

    //pause button and menu
    public void pauseButton() {
        sourceM.PlayOneShot(bClick);
        //pause everything and enable canvas
        Time.timeScale = 0.0f;
        pauseMenu.gameObject.SetActive(true);
        pauseB.gameObject.SetActive(false);
    }
    //resuming game
    public void resume() {
        sourceM.PlayOneShot(bClick);
        pauseMenu.gameObject.SetActive(false);
        pauseB.gameObject.SetActive(true);
        Time.timeScale = 1.0f;
    }
    //restart game
    public void restartB() {
        sourceM.PlayOneShot(bClick);
        pauseMenu.gameObject.SetActive(false);
        pauseB.gameObject.SetActive(true);
        Time.timeScale = 1.0f;
        Restart();
    }
    //go back to main menu
    public void mainMenuB() {
        pauseMenu.gameObject.SetActive(false);
        pauseB.gameObject.SetActive(true);
        Time.timeScale = 1.0f;
        shmupHistory.Add(LoginScript.currUser + "     " + System.DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss") + "     " + currentScore.ToString() + "pts");
        saveScore();
        SceneManager.LoadScene("SceneMenu");
    }

    public void SpawnEnemy() {
        //if the enemy spawn limit has been reached
        if (spawnCount >= GUIscript.enNumB && currentLvl == 0) { return; }
        else if (spawnCount >= GUIscript.enNumS && currentLvl == 1) { return; }
        else if (spawnCount >= GUIscript.enNumG && currentLvl == 2) { return; }
        //spawns enemies selected in game levels configuration
        while(true) {
            randNum = Random.Range(0, 10);
            //if enemy is selected to spawn for bronze
            if(currentLvl == 0 && GUIscript.enSpawnB[randNum] == 1) {
                break;
            }
            //silver
            else if (currentLvl == 1 && GUIscript.enSpawnS[randNum] == 1) {
                break;
            }
            //gold
            else if (currentLvl == 2 && GUIscript.enSpawnG[randNum] == 1) {
                break;
            }
        }
        GameObject go = Instantiate<GameObject>(prefabEnemies[randNum]);
        spawnCount++;
        // Pick a random Enemy prefab to instantiate
        //int ndx = Random.Range(0, prefabEnemies.Length); // b
        //GameObject go = Instantiate<GameObject>(prefabEnemies[ndx]); // c
        // Position the Enemy above the screen with a random x position
        float enemyPadding = enemyDefaultPadding; // d
        if (go.GetComponent<BoundsCheck>() != null) { // e
            enemyPadding = Mathf.Abs(go.GetComponent<BoundsCheck>().radius);
        }
        // Set the initial position for the spawnedEnemy
        Vector3 pos = Vector3.zero;
        float xMin = -bndCheck.camWidth + enemyPadding;
        float xMax = bndCheck.camWidth - enemyPadding;
        pos.x = Random.Range(xMin, xMax);
        pos.y = bndCheck.camHeight + enemyPadding;
        go.transform.position = pos;
        // Invoke SpawnEnemy() again
        if(currentLvl == 0 && spawnCount < GUIscript.enNumB) {
            spawnCount++;
            Invoke("SpawnEnemy", 1f / enemySpawnPerSecond);
        }
        else if (currentLvl == 1 && spawnCount < GUIscript.enNumS) {
            spawnCount++;
            Invoke("SpawnEnemy", 1f / enemySpawnPerSecond);
        }
        else if (currentLvl == 2 && spawnCount < GUIscript.enNumG) {
            spawnCount++;
            Invoke("SpawnEnemy", 1f / enemySpawnPerSecond);
        }
    }

    public void DelayedRestart(float delay) {
        // Invoke the Restart() method in delay seconds
        Invoke("Restart", delay);
    }

    public void Restart() {
        shmupHistory.Add(LoginScript.currUser + "     " + System.DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss") + "     " + currentScore.ToString() + "pts");
        saveScore();
        // Reload _Scene_0 to restart the game
        SceneManager.LoadScene("_Scene_0");
    }

    /// <summary>
    /// Static function that gets a WeaponDefinition from the WEAP_DICT static
    /// protected field of the Main class.
    /// </summary>
    /// <returns>The WeaponDefinition or, if there is no WeaponDefinition with
    /// the WeaponType passed in, returns a new WeaponDefinition with a
    /// WeaponType of none..</returns>
    /// <param name="wt">The WeaponType of the desired WeaponDefinition</param>
    static public WeaponDefinition GetWeaponDefinition(WeaponType wt) { // a
        // Check to make sure that the key exists in the Dictionary
        // Attempting to retrieve a key that didn't exist, would throw an error,
        // so the following if statement is important.
        if (WEAP_DICT.ContainsKey(wt)) {
            return (WEAP_DICT[wt]);
        }
        // This returns a new WeaponDefinition with a type of WeaponType.none,
        // which means it has failed to find the right WeaponDefinition
        return (new WeaponDefinition());
    }

    public void loadScore() {
        if (File.Exists(Application.persistentDataPath + "/shmupSave.dat")) {
            BinaryFormatter binF = new BinaryFormatter();
            FileStream file = File.Open(Application.persistentDataPath + "/shmupSave.dat", FileMode.Open);
            ShmupSaves shmupsave = (ShmupSaves)binF.Deserialize(file);
            file.Close();
            shmupHistory = shmupsave.shmupHistory;
        }
    }

    //saving user lists between launches
    public void saveScore() {
        BinaryFormatter binF = new BinaryFormatter();
        FileStream file = File.Create(Application.persistentDataPath + "/shmupSave.dat");
        //setting data in container
        ShmupSaves shmupsave = new ShmupSaves();
        shmupsave.shmupHistory = shmupHistory;
        //writing data to file
        binF.Serialize(file, shmupsave);
        file.Close();
    }
}

//container class to easily write needed data
[System.Serializable]
class ShmupSaves {
    public List<string> shmupHistory;
}