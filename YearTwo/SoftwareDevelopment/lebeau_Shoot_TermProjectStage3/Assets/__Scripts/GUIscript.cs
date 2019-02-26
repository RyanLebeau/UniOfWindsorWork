using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GUIscript : MonoBehaviour {
    public static int screen, levelSelect, enNumB, enNumS, enNumG, scoreLimitB, scoreLimitS, scoreLimitG, musicSNum,
        winSNum, shootSNum, destroySNum, bImgNum, sImgNum, gImgNum, e0Pts, e1Pts, e2Pts, e3Pts, e4Pts, e0C, e1C, e2C, e3C, e4C;
    public static float xAxisScale, yAxisScale, volumeSetting;
    public Canvas c0, c1, c2, c3, c4, c5, c6, c7;
    public Text BSG, errorLvl;
    public Toggle e0, e1, e2, e3, e4;
    public Dropdown gameMusic, levelWin, shootSound, destruction, bImgDrop, sImgDrop, gImgDrop, e0D, e1D, e2D, e3D, e4D;
    public List<string> gameMusicStr, levelWinStr, shootSoundStr, destructionStr, ImgOption, colourOption;
    public Slider volSlider, xAxis, yAxis;
    public Image bImg, sImg, gImg;
    public Sprite imgOne, imgTwo, imgThree, imgFour, imgFive, imgSix, imgSeven;
    public static int[] enSpawnB, enSpawnS, enSpawnG;
    public bool spawnBChange, spawnSChange, spawnGChange;
    public static AudioSource source;
    public AudioClip w1, w2, w3, s1, s2, s3, d1, d2, d3, bClick, mM;


    // Use this for initialization
    void Start () {
        //setting default values if they are never changed
        //number of enemies
        enNumB = 100;
        enNumS = 225;
        enNumG = 375;
        //score
        scoreLimitB = 25;
        scoreLimitS = 100;
        scoreLimitG = 150;
        //backgrounds
        bImgNum = 0;
        sImgNum = 1;
        gImgNum = 2;
        //points
        e0Pts = 1; e1Pts = 5; e2Pts = 10; e3Pts = 20; e4Pts = 50;
        //colours
        e0C = 0; e1C = 1; e2C = 2; e3C = 3; e4C = 4;
        //scaling
        xAxisScale = 1.0f; yAxisScale = 1.0f;
        //sounds
        musicSNum = 0;
        winSNum = 1;
        destroySNum = 0;
        shootSNum = 0;
        //initializing variables
        errorLvl.text = "";
        //types of enemies spawning in each level
        enSpawnB = new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        enSpawnS = new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        enSpawnG = new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        //populating all dropdown menus with required options
        gameMusicStr = new List<string> { "Audio 1", "Audio 2", "Audio 3" };
        levelWinStr = new List<string> { "Win 1", "Win 2", "Win 3" };
        shootSoundStr = new List<string> { "Shoot 1", "Shoot 2", "Shoot 3" };
        destructionStr = new List<string> { "Destroy 1", "Destroy 2", "Destroy 3" };
        ImgOption = new List<string> { "Image 1", "Image 2", "Image 3", "Image 4", "Image 5", "Image 6", "Image 7" };
        colourOption = new List<string> { "Blue", "Green", "Yellow", "Cyan", "Magenta", "White" };
        gameMusic.AddOptions(gameMusicStr);
        levelWin.AddOptions(levelWinStr);
        shootSound.AddOptions(shootSoundStr);
        destruction.AddOptions(destructionStr);
        bImgDrop.AddOptions(ImgOption);
        sImgDrop.AddOptions(ImgOption);
        gImgDrop.AddOptions(ImgOption);
        e0D.AddOptions(colourOption);
        e1D.AddOptions(colourOption);
        e2D.AddOptions(colourOption);
        e3D.AddOptions(colourOption);
        e4D.AddOptions(colourOption);
        source = GetComponent<AudioSource>();
        //starting menu music
        source.PlayOneShot(mM);
        source.loop = true;
        screen = 0;
        //these control if the enemy spawns for a level have been changed through config, if not default is used
        spawnBChange = false; spawnSChange = false; spawnGChange = false;
        canvasOff();
        c0.gameObject.SetActive(true);
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    //disable all canvas layers
    public void canvasOff() {
        c0.gameObject.SetActive(false);
        c1.gameObject.SetActive(false);
        c2.gameObject.SetActive(false);
        c3.gameObject.SetActive(false);
        c4.gameObject.SetActive(false);
        c5.gameObject.SetActive(false);
        c6.gameObject.SetActive(false);
        c7.gameObject.SetActive(false);
    }

    //c0 - Start Game
    public void c0Start() {
        source.PlayOneShot(bClick);
        screen = 1;
        c0.gameObject.SetActive(false);
        c1.gameObject.SetActive(true);
    }
    public void c0Exit() {
        source.PlayOneShot(bClick);
        Application.Quit();
    }

    //c1 - Main Menu
    public void c1GameLevel() {
        source.PlayOneShot(bClick);
        screen = 2;
        c1.gameObject.SetActive(false);
        c2.gameObject.SetActive(true);
    }
    public void c1Configurations() {
        source.PlayOneShot(bClick);
        screen = 4;
        c1.gameObject.SetActive(false);
        c4.gameObject.SetActive(true);
    }
    public void c1PlayGame() {
        source.PlayOneShot(bClick);
        screen = 8;
        //if spawns werer never set use these default values
        if (!spawnBChange) { enSpawnB = new int[] { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 }; }
        if (!spawnSChange) { enSpawnS = new int[] { 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 }; }
        if (!spawnGChange) { enSpawnG = new int[] { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; }
        c1.gameObject.SetActive(false);
        c0.gameObject.SetActive(true);
        SceneManager.LoadScene("_Scene_0");
    }
    public void c1Exit() {
        source.PlayOneShot(bClick);
        screen = 0;
        c1.gameObject.SetActive(false);
        c0.gameObject.SetActive(true);
    }

    //c2 - Game Levels
    public void c2Bronze() {
        source.PlayOneShot(bClick);
        levelSelect = 0;
        screen = 3;
        BSG.text = "Bronze";
        c2.gameObject.SetActive(false);
        c3.gameObject.SetActive(true);
    }
    public void c2Silver() {
        source.PlayOneShot(bClick);
        levelSelect = 1;
        screen = 3;
        BSG.text = "Silver";
        c2.gameObject.SetActive(false);
        c3.gameObject.SetActive(true);
    }
    public void c2Gold() {
        source.PlayOneShot(bClick);
        levelSelect = 2;
        screen = 3;
        BSG.text = "Gold";
        c2.gameObject.SetActive(false);
        c3.gameObject.SetActive(true);
    }
    public void c2Exit() {
        source.PlayOneShot(bClick);
        screen = 1;
        c2.gameObject.SetActive(false);
        c1.gameObject.SetActive(true);
    }

    //c3 - Game Level
    //which enemies will spawn per level
    public void c3Toggle() {
        //bronze level
        if(levelSelect == 0) {
            if (e0.isOn) {
                //change variable since spawns have been selected
                spawnBChange = true;
                enSpawnB[0] = 1;
                enSpawnB[1] = 1;
                enSpawnB[2] = 1;
            }
            if (e1.isOn) {
                spawnBChange = true;
                enSpawnB[3] = 1;
                enSpawnB[4] = 1;
            }
            if (e2.isOn) {
                spawnBChange = true;
                enSpawnB[5] = 1;
                enSpawnB[6] = 1;
            }
            if (e3.isOn) {
                spawnBChange = true;
                enSpawnB[7] = 1;
                enSpawnB[8] = 1;
            }
            if (e4.isOn) {
                spawnBChange = true;
                enSpawnB[9] = 1;
            }
        }
        //silver level
        else if (levelSelect == 1) {
            if (e0.isOn) {
                spawnSChange = true;
                enSpawnS[0] = 1;
                enSpawnS[1] = 1;
                enSpawnS[2] = 1;
            }
            if (e1.isOn) {
                spawnSChange = true;
                enSpawnS[3] = 1;
                enSpawnS[4] = 1;
            }
            if (e2.isOn) {
                spawnSChange = true;
                enSpawnS[5] = 1;
                enSpawnS[6] = 1;
            }
            if (e3.isOn) {
                spawnSChange = true;
                enSpawnS[7] = 1;
                enSpawnS[8] = 1;
            }
            if (e4.isOn) {
                spawnSChange = true;
                enSpawnS[9] = 1;
            }
        }
        //gold level
        else if (levelSelect == 2) {
            if (e0.isOn) {
                spawnGChange = true;
                enSpawnG[0] = 1;
                enSpawnG[1] = 1;
                enSpawnG[2] = 1;
            }
            if (e1.isOn) {
                spawnGChange = true;
                enSpawnG[3] = 1;
                enSpawnG[4] = 1;
            }
            if (e2.isOn) {
                spawnGChange = true;
                enSpawnG[5] = 1;
                enSpawnG[6] = 1;
            }
            if (e3.isOn) {
                spawnGChange = true;
                enSpawnG[7] = 1;
                enSpawnG[8] = 1;
            }
            if (e4.isOn) {
                spawnGChange = true;
                enSpawnG[9] = 1;
            }
        }
    }
    //number of enemies to spawn per level
    public void c3NumEnemies(string numE) {
        if(levelSelect == 0) {
            enNumB = int.Parse(numE);
        }
        else if(levelSelect == 1) {
            enNumS = int.Parse(numE);
        }
        else if(levelSelect == 2) {
            enNumG = int.Parse(numE);
        }
    }
    //number of points required per level
    public void c3ScoreMax(string scoreStr) {
        if (levelSelect == 0) {
            scoreLimitB = int.Parse(scoreStr);
        }
        else if (levelSelect == 1) {
            scoreLimitS = int.Parse(scoreStr);
        }
        else if (levelSelect == 2) {
            scoreLimitG = int.Parse(scoreStr);
        }
    }
    public void c3Exit() {
        source.PlayOneShot(bClick);
        c3Toggle();
        //if the number of enemies is not higher than the previous setting
        if (levelSelect == 1 && enNumS < enNumB) {
            errorLvl.text = "Invalid number of enemies.";
        }
        else if(levelSelect == 2 && enNumG < enNumS) {
            errorLvl.text = "Invalid number of enemies.";
        }
        else {
            //resetting screen toggles and text so next level screen does not have options saved
            e0.isOn = false;
            e1.isOn = false;
            e2.isOn = false;
            e3.isOn = false;
            e4.isOn = false;
            errorLvl.text = "";
            screen = 2;
            c3.gameObject.SetActive(false);
            c2.gameObject.SetActive(true);
        }
    }

    //c4 - Configuration
    public void c4Enemies() {
        source.PlayOneShot(bClick);
        screen = 5;
        c4.gameObject.SetActive(false);
        c5.gameObject.SetActive(true);
    }
    public void c4Audio() {
        source.PlayOneShot(bClick);
        screen = 6;
        c4.gameObject.SetActive(false);
        c6.gameObject.SetActive(true);
    }
    public void c4Background() {
        source.PlayOneShot(bClick);
        screen = 7;
        c4.gameObject.SetActive(false);
        c7.gameObject.SetActive(true);
    }
    public void c4Exit() {
        source.PlayOneShot(bClick);
        screen = 1;
        c4.gameObject.SetActive(false);
        c1.gameObject.SetActive(true);
    }

    //c5 - Enemy Config
    //points
    public void c5PtsE0(string points) {
        e0Pts = int.Parse(points);
    }
    public void c5PtsE1(string points) {
        e1Pts = int.Parse(points);
    }
    public void c5PtsE2(string points) {
        e2Pts = int.Parse(points);
    }
    public void c5PtsE3(string points) {
        e3Pts = int.Parse(points);
    }
    public void c5PtsE4(string points) {
        e4Pts = int.Parse(points);
    }
    //colour
    public void c5ColourE0(int index) {
        e0C = index;
    }
    public void c5ColourE1(int index) {
        e1C = index;
    }
    public void c5ColourE2(int index) {
        e2C = index;
    }
    public void c5ColourE3(int index) {
        e3C = index;
    }
    public void c5ColourE4(int index) {
        e4C = index;
    }
    public void c5Exit() {
        source.PlayOneShot(bClick);
        screen = 4;
        c5.gameObject.SetActive(false);
        c4.gameObject.SetActive(true);
    }

    //c6 - Audio
    public void c6VolumeSlider() {
        source.volume = volSlider.value;
        volumeSetting = volSlider.value;
    }
    public void c6GameMusic(int index) {
        musicSNum = index;
    }
    public void c6LevelWin(int index) {
        winSNum = index;
        //play selected sound
        switch (index) {
            case 0: source.PlayOneShot(w1); break;
            case 1: source.PlayOneShot(w2); break;
            case 2: source.PlayOneShot(w3); break;
            default: break;
        }
    }
    public void c6ShootSound(int index) {
        shootSNum = index;
        //play selected sound
        switch (index) {
            case 0: source.PlayOneShot(s1); break;
            case 1: source.PlayOneShot(s2); break;
            case 2: source.PlayOneShot(s3); break;
            default: break;
        }
    }
    public void c6DestroySound(int index) {
        destroySNum = index;
        //play selected sound
        switch (index) {
            case 0: source.PlayOneShot(d1); break;
            case 1: source.PlayOneShot(d2); break;
            case 2: source.PlayOneShot(d3); break;
            default: break;
        }
    }
    public void c6Exit() {
        source.PlayOneShot(bClick);
        screen = 4;
        c6.gameObject.SetActive(false);
        c4.gameObject.SetActive(true);
    }

    //c7 - Background
    public void c7Bronze(int index) {
        bImgNum = index;
        //set preview image next to dropdown menu
        switch (index) {
            case 0: bImg.sprite = imgOne; break;
            case 1: bImg.sprite = imgTwo; break;
            case 2: bImg.sprite = imgThree; break;
            case 3: bImg.sprite = imgFour; break;
            case 4: bImg.sprite = imgFive; break;
            case 5: bImg.sprite = imgSix; break;
            case 6: bImg.sprite = imgSeven; break;
            default: break;
        }
    }
    public void c7Silver(int index) {
        sImgNum = index;
        switch (index) {
            case 0: sImg.sprite = imgOne; break;
            case 1: sImg.sprite = imgTwo; break;
            case 2: sImg.sprite = imgThree; break;
            case 3: sImg.sprite = imgFour; break;
            case 4: sImg.sprite = imgFive; break;
            case 5: sImg.sprite = imgSix; break;
            case 6: sImg.sprite = imgSeven; break;
            default: break;
        }
    }
    public void c7Gold(int index) {
        gImgNum = index;
        switch (index) {
            case 0: gImg.sprite = imgOne; break;
            case 1: gImg.sprite = imgTwo; break;
            case 2: gImg.sprite = imgThree; break;
            case 3: gImg.sprite = imgFour; break;
            case 4: gImg.sprite = imgFive; break;
            case 5: gImg.sprite = imgSix; break;
            case 6: gImg.sprite = imgSeven; break;
            default: break;
        }
    }
    //saving the x and y scale factor
    public void c7xAxis() {
        xAxisScale = xAxis.value;
    }
    public void c7yAxis() {
        yAxisScale = yAxis.value;
    }
    public void c7Exit() {
        source.PlayOneShot(bClick);
        screen = 4;
        c7.gameObject.SetActive(false);
        c4.gameObject.SetActive(true);
    }

}
