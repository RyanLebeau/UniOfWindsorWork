using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ProcGen : MonoBehaviour {
    public static int levelNum, sectionNum, sectionHalf, platPosX, platPosY, platChoice, enemySpawned, powerupSpawned;
    public static bool charDeath, endLevelBool, spawnedEnd, endGameBool, started;
    public static List<GameObject> platformList = new List<GameObject>();
    public GameObject SLong, SMed, SShort, HLong, HMed, HSpec, VLong, VShort, VSpec, EndPlat,
                Cubey, Hover, BS, FCubey, SB, Laser, Teleport, Speed, Gun, OneUp;
    public int randSpawn;

	// Use this for initialization
	void Start () {
        endLevelBool = false;
        endGameBool = false;
        charDeath = false;
        started = false;
        //starting platform is always the same
        platformList.Add(Instantiate(SShort, new Vector3(0, 0, 0), new Quaternion(0, 0, 0, 0)));
        //tracks most recent platform edge 
        platPosX = 5; platPosY = 0;
        //spawn the first section
        spawnSection();
        sectionNum = 1;
	}
	
	// Update is called once per frame
	void Update () {
        if(Character.currentPos.x >= sectionHalf && sectionNum < 10) {
            spawnSection();
            sectionNum++;
            if(sectionNum > 2)
                deleteSection();
        }
        if ((charDeath || endLevelBool) && !started) {
            started = true;
            restartLevel();
        }
        if(Character.currentPos.x >= sectionHalf && sectionNum == 10 && !spawnedEnd) {
            //so end is not spawned on every frame
            spawnedEnd = true;
            spawnEnd();
        }
	}

    //spawns in everything for the section
    public void spawnSection() {
        int tempX = platPosX;
        //3 random platforms
        for (int i = 0; i < 3; i++) {
            //randSpawn = Random.Range(1, 85);
            randSpawn = Random.Range(1, 101);
            if (levelNum == 1) {
                platformList.Add(Instantiate(spawnPlatform(randSpawn), findPosition(), new Quaternion(0, 0, 0, 0)));
                if (platChoice == 0 || platChoice == 1 || platChoice == 3 || platChoice == 6) {
                    spawnEnemy();
                    spawnPowerUp();
                }
            }
            else if (levelNum == 2) {
                platformList.Add(Instantiate(spawnPlatform(randSpawn), findPosition(), new Quaternion(0, 0, 0, 0)));
                if (platChoice == 0 || platChoice == 1 || platChoice == 3 || platChoice == 6) {
                    spawnEnemy();
                    spawnPowerUp();
                }
            }
            else if (levelNum == 3) {
                platformList.Add(Instantiate(spawnPlatform(randSpawn), findPosition(), new Quaternion(0, 0, 0, 0)));
                if (platChoice == 0 || platChoice == 1 || platChoice == 3 || platChoice == 6) {
                    spawnEnemy();
                    spawnPowerUp();
                }
            }
        }
        //where half of the section lies
        sectionHalf = (platPosX - tempX) / 2;
        sectionHalf += tempX;
    }

    //finds proper position to spawn platforms
    public Vector3 findPosition() {
        Vector3 spawnPos = new Vector3();
        //x position
        findPositionX(true);
        platPosX += Random.Range(4, 9);
        spawnPos.x = platPosX;
        findPositionX(false);
        //y position
        findPositionY();
        spawnPos.y = platPosY;
        spawnPos.z = 0;
        return spawnPos;
    }
    //solves for x position of plaform
    public void findPositionX(bool firstHalf) {
        //adding half the length of platform to current X pos 
        switch (platChoice) {
            //solid platforms
            case 0:
                platPosX += 13; break;
            case 1:
                platPosX += 9; break;
            case 2:
                platPosX += 5; break;
            //horizontally moving platforms
            case 3:
                //since platform moves from spawn 12 then back 12
                //a bool is required to give enough movement space for second half
                if (firstHalf)
                    platPosX += 13;
                else
                    platPosX += 25;
                break;
            case 4:
                if (firstHalf)
                    platPosX += 9;
                else
                    platPosX += 21;
                break;
            case 5:
                if (firstHalf)
                    platPosX += 5;
                else
                    platPosX += 17;
                break;
            //vertically moving platforms
            case 6:
                platPosX += 13; break;
            case 7:
                platPosX += 5; break;
        }
    }
    //solves for y position of platform
    public void findPositionY() {
        //adding or subtracting from previous y position
        switch (platChoice) {
            //solid long,med,short
            case 0:
            case 1:
            case 2:
                if (platPosY >= 4 && platPosY < 6)
                    platPosY += Random.Range(-4, 7);
                else if (platPosY >= 6)
                    platPosY += Random.Range(-6, 1);
                else
                    platPosY += Random.Range(0, 7);
                break;
            //horizontally moving long, medium, special
            case 3:
            case 4:
            case 5:
                if (platPosY >= 11)
                    platPosY += Random.Range(-1, 0);
                else if(platPosY == 0)
                    platPosY += Random.Range(0, 2);
                else
                    platPosY += Random.Range(-1, 2);
                break;
            //vertically moving long
            case 6:
                if (platPosY >= 11)
                    platPosY += Random.Range(-1, 0);
                else if (platPosY <= 3)
                    platPosY += Random.Range(3, 5);
                else
                    platPosY += Random.Range(-1, 3);
                break;
            //vertically moving short, special
            case 7:
                if (platPosY >= 11)
                    platPosY += Random.Range(-1, 0);
                else if (platPosY == 0)
                    platPosY += Random.Range(0, 3);
                else
                    platPosY += Random.Range(-1, 2);
                break;
        }
    }

    //selects weighted random for which platform to spawn in
    public GameObject spawnPlatform(int rand) {
        if (rand <= 21) {
            platChoice = 0;
            return SLong;
        }
        else if (rand > 21 && rand <= 42) {
            platChoice = 1;
            return SMed;
        }
        else if (rand > 42 && rand <= 62) {
            platChoice = 2;
            return SShort;
        }
        else if (rand > 62 && rand <= 69) {
            platChoice = 3;
            return HLong;
        }
        else if (rand > 69 && rand <= 76) {
            platChoice = 4;
            return HMed;
        }
        else if (rand > 76 && rand <= 78) {
            platChoice = 5;
            return HSpec;
        }
        else if (rand > 78 && rand <= 88) {
            platChoice = 6;
            return VLong;
        }
        else if (rand > 88 && rand <= 98) {
            platChoice = 7;
            return VShort;
        }
        else if (rand > 98 && rand <= 100) {
            platChoice = 7;
            return VSpec;
        }
        return (null);
    }

    //deleting past section that is completely off screen (when third spawns delete first, etc)
    public void deleteSection() {
        //4 platforms must be deleted from first section
        if(sectionNum == 3) {
            for(int i = 0; i < 4; i++) {
                Destroy(platformList[0].gameObject);
                platformList.RemoveAt(0);
            }
        }
        else {
            for (int i = 0; i < 3; i++) {
                Destroy(platformList[0].gameObject);
                platformList.RemoveAt(0);
            }
        }
    }

    //spawn in enemy randomly based off of levelNum
    //enemySpawned num 1-cubey 2-hover 3-BS 4-fcubey 5-SB
    public void spawnEnemy() {
        int randNum = Random.Range(0, 3);
        GameObject enemy;
        Vector3 spawnPos = platformList[platformList.Count - 1].transform.position;
        //level one spawns in cubey, hover, or BS
        if (levelNum == 1) {
            switch (randNum) {
                case 0:
                    enemySpawned = 1;
                    spawnPos.y += 2;
                    enemy = Instantiate(Cubey, spawnPos, new Quaternion(0, 0, 0, 0));
                    //set enemy as a child of the platform
                    enemy.transform.parent = platformList[platformList.Count - 1].transform;
                    break;
                case 1:
                    enemySpawned = 2;
                    spawnPos.y += 4;
                    enemy = Instantiate(Hover, spawnPos, new Quaternion(0, 0, 0, 0));
                    //set enemy as a child of the platform
                    enemy.transform.parent = platformList[platformList.Count - 1].transform;
                    break;
                case 2:
                    enemySpawned = 3;
                    spawnPos.y += 0.5f;
                    enemy = Instantiate(BS, spawnPos, new Quaternion(0, 0, 0, 0));
                    //set enemy as a child of the platform
                    enemy.transform.parent = platformList[platformList.Count - 1].transform;
                    break;
            }
        }
        //level two spawns in cubey, fastcubey, or SB
        else if (levelNum == 2) {
            switch (randNum) {
                case 0:
                    enemySpawned = 1;
                    spawnPos.y += 2;
                    enemy = Instantiate(Cubey, spawnPos, new Quaternion(0, 0, 0, 0));
                    //set enemy as a child of the platform
                    enemy.transform.parent = platformList[platformList.Count - 1].transform;
                    break;
                case 1:
                    enemySpawned = 4;
                    spawnPos.y += 2;
                    enemy = Instantiate(FCubey, spawnPos, new Quaternion(0, 0, 0, 0));
                    //set enemy as a child of the platform
                    enemy.transform.parent = platformList[platformList.Count - 1].transform;
                    break;
                case 2:
                    enemySpawned = 5;
                    spawnPos.y += 2;
                    enemy = Instantiate(SB, spawnPos, new Quaternion(0, 0, 0, 0));
                    //set enemy as a child of the platform
                    enemy.transform.parent = platformList[platformList.Count - 1].transform;
                    break;
            }
        }
        //level three spawns in cubey, fastcubey, or hover
        else if (levelNum == 3) {
            switch (randNum) {
                case 0:
                    enemySpawned = 1;
                    spawnPos.y += 2;
                    enemy = Instantiate(Cubey, spawnPos, new Quaternion(0, 0, 0, 0));
                    //set enemy as a child of the platform
                    enemy.transform.parent = platformList[platformList.Count - 1].transform;
                    break;
                case 1:
                    enemySpawned = 4;
                    spawnPos.y += 2;
                    enemy = Instantiate(FCubey, spawnPos, new Quaternion(0, 0, 0, 0));
                    //set enemy as a child of the platform
                    enemy.transform.parent = platformList[platformList.Count - 1].transform;
                    break;
                case 2:
                    enemySpawned = 2;
                    spawnPos.y += 4;
                    enemy = Instantiate(Hover, spawnPos, new Quaternion(0, 0, 0, 0));
                    //set enemy as a child of the platform
                    enemy.transform.parent = platformList[platformList.Count - 1].transform;
                    break;
            }
        }
    }

    //spawn powerup randomly based off of levelNum
    //powerupSpawned num 1-teleport 2-laser 3-speed 4-gun 5-oneup
    public void spawnPowerUp() {
        int randNum = Random.Range(0, 3);
        GameObject powerup;
        Vector3 spawnPos = platformList[platformList.Count - 1].transform.position;
        spawnPos.x -= 6.7f;
        spawnPos.y += 1.25f;
        //level one spawns teleport, gun, oneup
        if (levelNum == 1) {
            switch (randNum) {
                case 0:
                    powerupSpawned = 1;
                    powerup = Instantiate(Teleport, spawnPos, new Quaternion(0, 0, 0, 0));
                    //set powerup as a child of the platform
                    powerup.transform.parent = platformList[platformList.Count - 1].transform;
                    break;
                case 1:
                    powerupSpawned = 4;
                    powerup = Instantiate(Gun, spawnPos, new Quaternion(0, 0, 0, 0));
                    //set powerup as a child of the platform
                    powerup.transform.parent = platformList[platformList.Count - 1].transform;
                    powerup.gameObject.transform.localScale = new Vector3(0.05f, 0.25f, 0.01f);
                    break;
                case 2:
                    powerupSpawned = 5;
                    powerup = Instantiate(OneUp, spawnPos, new Quaternion(0, 0, 0, 0));
                    //set powerup as a child of the platform
                    powerup.transform.parent = platformList[platformList.Count - 1].transform;
                    powerup.gameObject.transform.localScale = new Vector3(0.05f, 0.25f, 0.01f);
                    break;
                //reducing the chance of a power up to spawn
                case 3:
                    break;
            }
        }
        //level one spawns laser, gun, oneup
        if (levelNum == 2) {
            switch (randNum) {
                case 0:
                    powerupSpawned = 2;
                    powerup = Instantiate(Laser, spawnPos, new Quaternion(0, 0, 0, 0));
                    //set powerup as a child of the platform
                    powerup.transform.parent = platformList[platformList.Count - 1].transform;
                    powerup.gameObject.transform.localScale = new Vector3(0.05f, 0.25f, 0.01f);
                    break;
                case 1:
                    powerupSpawned = 4;
                    powerup = Instantiate(Gun, spawnPos, new Quaternion(0, 0, 0, 0));
                    //set powerup as a child of the platform
                    powerup.transform.parent = platformList[platformList.Count - 1].transform;
                    powerup.gameObject.transform.localScale = new Vector3(0.05f, 0.25f, 0.01f);
                    break;
                case 2:
                    powerupSpawned = 5;
                    powerup = Instantiate(OneUp, spawnPos, new Quaternion(0, 0, 0, 0));
                    //set powerup as a child of the platform
                    powerup.transform.parent = platformList[platformList.Count - 1].transform;
                    powerup.gameObject.transform.localScale = new Vector3(0.05f, 0.25f, 0.01f);
                    break;
                case 3:
                    break;
            }
        }
        //level one spawns speed, gun, oneup
        if (levelNum == 3) {
            switch (randNum) {
                case 0:
                    powerupSpawned = 3;
                    powerup = Instantiate(Speed, spawnPos, new Quaternion(0, 0, 0, 0));
                    //set powerup as a child of the platform
                    powerup.transform.parent = platformList[platformList.Count - 1].transform;
                    powerup.gameObject.transform.localScale = new Vector3(0.05f, 0.25f, 0.01f);
                    break;
                case 1:
                    powerupSpawned = 4;
                    powerup = Instantiate(Gun, spawnPos, new Quaternion(0, 0, 0, 0));
                    //set powerup as a child of the platform
                    powerup.transform.parent = platformList[platformList.Count - 1].transform;
                    powerup.gameObject.transform.localScale = new Vector3(0.05f, 0.25f, 0.01f);
                    break;
                case 2:
                    powerupSpawned = 5;
                    powerup = Instantiate(OneUp, spawnPos, new Quaternion(0, 0, 0, 0));
                    //set powerup as a child of the platform
                    powerup.transform.parent = platformList[platformList.Count - 1].transform;
                    powerup.gameObject.transform.localScale = new Vector3(0.05f, 0.25f, 0.01f);
                    break;
                case 3:
                    break;
            }
        }
    }

    //spawn the end zone
    public void spawnEnd() {
        platPosX += 10;
        platPosY = 0;
        platformList.Add(Instantiate(EndPlat, new Vector3(platPosX, platPosY, 0), new Quaternion(0, 0, 0, 0)));
    }

    //restart current level by emptying platforms annd resetting data
    public void restartLevel() {
        while(platformList.Count > 0) {
            Destroy(platformList[0].gameObject);
            platformList.RemoveAt(0);
        }
        //StartCoroutine(Reset());
        ResetL();
    }

    //reset all necessary data to start level over again from death/exit/next level
    public void ResetL() {
        //resetting camera
        Character.currentPos = new Vector3(0, 3, 0);
        //starting platform is always the same
        platformList.Add(Instantiate(SShort, new Vector3(0, 0, 0), new Quaternion(0, 0, 0, 0)));
        //tracks most recent platform edge 
        platPosX = 5; platPosY = 0;
        //spawn the first section
        spawnSection();
        sectionNum = 1;
        HUD.coins = 0;
        HUD.kills = 0;
        HUD.powTime = 0;
        Character.charHealth = 5;
        spawnedEnd = false;
        charDeath = false;
        //reset boolean that prevent multiple restartlevel calls
        started = false;
        //reset stats if player died
        if (!endLevelBool)
            HUD.deaths += 1;
        //allow HUD to change scenes only if end of game
        if (endGameBool) {
            endGameBool = false;
            endLevelBool = false;
            HUD.deaths = 0;
            HUD.changeScenes = true;
        }
        //if end of level reset and not death reset
        else if (endLevelBool) {
            HUD.deaths = -1;
            endLevelBool = false;
        }
    }

}
