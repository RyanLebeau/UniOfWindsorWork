using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Character : MonoBehaviour {
    public static Vector3 forward = new Vector3(0.1f, 0, 0);
    public static Vector3 backward = new Vector3(-0.1f, 0, 0);
    public static Vector3 forwardSprint = new Vector3(0.15f, 0, 0);
    public static Vector3 backwardSprint = new Vector3(-0.15f, 0, 0);
    public static Vector3 currentPos = new Vector3();
    public static Vector3 Pos = new Vector3();
    public static float currentTime = 0.01f, jumps = 0, jumpMax = 2, immunityTime = 0.01f;
    public static bool ifJump = false, ifShoot = false, ifTeleport = false, tele = false, ifLaser = false, laserSpawned = false;
    public static int charHealth, direction, tempHealth;
    public static string powerup;
    public GameObject charSide, charFront, bullet, laser, audioM;
    public static GameObject lBlock;

    // Use this for initialization
    void Start () {
        charHealth = 5;
        //make sure character facing screen when moving
        gameObject.GetComponent<Renderer>().enabled = false;
        charSide.SetActive(false);
        charFront.SetActive(true);
        powerup = "";
        gameObject.transform.position = new Vector3(gameObject.transform.position.x, gameObject.transform.position.y, 0);
    }

    void Update() {
        //jump 
        if (Input.GetKeyDown(KeyCode.Space) || Input.GetKeyDown(KeyCode.W) || Input.GetKeyDown(KeyCode.UpArrow)) {
            jumps++;
            if (jumps <= jumpMax) {
                ifJump = true;
                currentTime = 0.01f;
            }
        }
        //user falls off map they die
        if (gameObject.transform.position.y < -1 || charHealth == 0) {
            //play death sound
            if(HUD.deaths != -1)
                audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().deathS);
            ProcGen.charDeath = true;
            gameObject.transform.position = new Vector3(0, 3, 0);
        }
        //reset characters position if starting a new level
        else if (ProcGen.endLevelBool) {
            gameObject.transform.position = new Vector3(0, 3, 0);
        }
        //if player has gun powerup
        if((Input.GetKeyDown(KeyCode.LeftShift) || Input.GetKeyDown(KeyCode.RightShift)) && ifShoot) {
            shootBullet();
        }
        //if player has teleport power up
        if (ifTeleport && Input.GetMouseButtonDown(0)) {
            //pass mouse position to teleport
            teleportChar(Camera.main.ScreenToWorldPoint(new Vector3(Input.mousePosition.x, Input.mousePosition.y, 0)));
            tele = true;
            tempHealth = charHealth;
            HUD.powTime -= 1;
        }
        if (tele) {
            immunityTime += Time.deltaTime;
            charHealth = tempHealth;
            if (immunityTime >= 2) {
                immunityTime = 0;
                tele = false;
            }
        }
        //if player has laser powerup
        if (ifLaser && Input.GetMouseButtonDown(0)) {
            //play laser sound
            audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().laserS);
            laserSpawn(Camera.main.ScreenToWorldPoint(new Vector3(Input.mousePosition.x, Input.mousePosition.y, 0)));
            if (laserSpawned) {
                Destroy(lBlock);
                laserSpawned = false;
                immunityTime = 0;
            }
            laserSpawned = true;
        }
        
        if (laserSpawned) {
            immunityTime += Time.deltaTime;
            if(immunityTime >= 0.2f) {
                Destroy(lBlock);
                laserSpawned = false;
                immunityTime = 0;
            }
        }
        enemyCollision();
        Pos = gameObject.transform.position;
        
    }

    // FixedUpdate is called once per 0.02s
    void FixedUpdate () {
        //Moving with A,D or arrow keys
        if (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.LeftArrow)) {
            //sprinting with control
            if (Input.GetKey(KeyCode.LeftControl) || Input.GetKey(KeyCode.RightControl))
                transform.Translate(backwardSprint);
            else 
                transform.Translate(backward);
            //switch to side view
            switchToSide();
            direction = 2;
        }
        else {
            if(charSide.activeSelf)
                switchToFront();
        }

        if (Input.GetKey(KeyCode.D) || Input.GetKey(KeyCode.RightArrow)) {
            if (Input.GetKey(KeyCode.LeftControl) || Input.GetKey(KeyCode.RightControl))
                transform.Translate(forwardSprint);
            else
                transform.Translate(forward);
            //changing current position for camera only if player moves forward
            if (currentPos.x <= gameObject.transform.position.x) {
                currentPos = gameObject.transform.position;
            }
            switchToSide();
            direction = 1;
        }

        //jump for 0.4s at speed of 7units/s
        if (ifJump) {
            GetComponent<Rigidbody>().velocity = new Vector3(0, 10.0f, 0);
            currentTime += Time.fixedDeltaTime;
            if (currentTime >= 0.5f) {
                //reduces arc hang time
                GetComponent<Rigidbody>().velocity = new Vector3(0, -7.0f, 0);
                ifJump = false;
            }
        }
    }

    public void switchToSide() {
        charFront.SetActive(false);
        charSide.SetActive(true);
    }

    public void switchToFront() {
        charSide.SetActive(false);
        charFront.SetActive(true);
    }

    //if a collision with an enemy will occur
    public void enemyCollision() {
        RaycastHit RayHit;
        Ray distRay1, distRay2, distRay3, distRay4, distRay5;
        distRay1 = new Ray(gameObject.transform.position, Enemies.cPos - gameObject.transform.position);
        distRay2 = new Ray(gameObject.transform.position, Enemies.hPos - gameObject.transform.position);
        distRay3 = new Ray(gameObject.transform.position, Enemies.bsPos - gameObject.transform.position);
        distRay4 = new Ray(gameObject.transform.position, Enemies.fcPos - gameObject.transform.position);
        distRay5 = new Ray(gameObject.transform.position, Enemies.sbPos - gameObject.transform.position);
        //cubey being hit
        if (Physics.Raycast(distRay1, out RayHit)) {
            if (RayHit.collider.tag == "Cubey") {
                Vector3 myNormal = RayHit.normal;
                //changing it relative to local axis
                myNormal = RayHit.transform.TransformDirection(myNormal);
                enemySideHit(myNormal, RayHit);
            }
        }
        //hover being hit
        if (Physics.Raycast(distRay2, out RayHit)) {
            if (RayHit.collider.tag == "Hover") {
                Vector3 myNormal = RayHit.normal;
                //changing it relative to local axis
                myNormal = RayHit.transform.TransformDirection(myNormal);
                enemySideHit(myNormal, RayHit);
            }
        }
        //BS being hit
        if (Physics.Raycast(distRay3, out RayHit)) {
            if (RayHit.collider.tag == "BS") {
                Vector3 myNormal = RayHit.normal;
                //changing it relative to local axis
                myNormal = RayHit.transform.TransformDirection(myNormal);
                enemySideHit(myNormal, RayHit);
            }
        }
        //fcubey being hit
        if (Physics.Raycast(distRay4, out RayHit)) {
            if (RayHit.collider.tag == "FCubey") {
                Vector3 myNormal = RayHit.normal;
                //changing it relative to local axis
                myNormal = RayHit.transform.TransformDirection(myNormal);
                enemySideHit(myNormal, RayHit);
            }
        }
        //SB being hit
        if (Physics.Raycast(distRay5, out RayHit)) {
            if (RayHit.collider.tag == "SB") {
                Vector3 myNormal = RayHit.normal;
                //changing it relative to local axis
                myNormal = RayHit.transform.TransformDirection(myNormal);
                enemySideHit(myNormal, RayHit);
            }
        }
    }
    
    //checking which side character hit enemy on
    public void enemySideHit(Vector3 myNormal, RaycastHit rayHit) {
        //character is going to hit enemy on top
        if(myNormal == rayHit.transform.up) {
            Enemies.sideHit = "top";
        }
        //character is going to hit enemy on bottom
        if (myNormal == -rayHit.transform.up) {
            Enemies.sideHit = "bottom";
        }
        //character is going to hit enemy on right
        if (myNormal == rayHit.transform.right) {
            Enemies.sideHit = "right";
        }
        //character is going to hit enemy on left
        if (myNormal == -rayHit.transform.right) {
            Enemies.sideHit = "left";
        }
    }

    //powerup functions for the character
    public void shootBullet() {
        //play shoot sound
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().shootS);
        Vector3 spawnPos = gameObject.transform.position;
        //shoot direction player is facing
        if (direction == 2) {
            spawnPos.x -= 0.5f;
            GameObject newBllt = Instantiate(bullet, spawnPos, new Quaternion(0, 0, 0, 0));
            newBllt.gameObject.tag = "CharBllt";
            newBllt.GetComponent<Rigidbody>().AddForce(new Vector3(-2000, 20));
        }
        else {
            spawnPos.x += 0.5f;
            GameObject newBllt = Instantiate(bullet, spawnPos, new Quaternion(0, 0, 0, 0));
            newBllt.gameObject.tag = "CharBllt";
            newBllt.GetComponent<Rigidbody>().AddForce(new Vector3(2000, 20));
        }

    }
    //powerup function for teleporting player
    public void teleportChar(Vector3 telePos) {
        telePos.z = 0;
        gameObject.transform.position = telePos;
        //if player teleported to the right update camera
        if(currentPos.x < gameObject.transform.position.x)
            currentPos.x = gameObject.transform.position.x;
        jumps = 0;
    }
    //powerup function for laser
    public void laserSpawn(Vector3 endPos) {
        //vector for difference between click and player
        Vector3 distance, spawnPos = new Vector3();
        distance.x = Mathf.Abs(endPos.x - gameObject.transform.position.x);
        distance.y = Mathf.Abs(endPos.y - gameObject.transform.position.y);
        distance.z = 0;
        float angle = 0;
        //determine position of enemy
        //above right
        if (endPos.x - gameObject.transform.position.x >= 0 && endPos.y - gameObject.transform.position.y >= 0) {
            spawnPos = new Vector3(gameObject.transform.position.x + distance.x / 2, gameObject.transform.position.y - 1 + distance.y / 2, 0);
            //angle of click to character
            angle = Mathf.Atan2(endPos.y - gameObject.transform.position.y, endPos.x - gameObject.transform.position.x) * 180 / Mathf.PI;
        }
        //above left
        else if (endPos.x - gameObject.transform.position.x < 0 && endPos.y - gameObject.transform.position.y >= 0) {
            spawnPos = new Vector3(gameObject.transform.position.x - distance.x / 2, gameObject.transform.position.y-1 + distance.y / 2, 0);
            angle = Mathf.Atan2(endPos.y - gameObject.transform.position.y, endPos.x - gameObject.transform.position.x) * 180 / Mathf.PI;
        }
        
        //below right
        else if (endPos.x - gameObject.transform.position.x >= 0 && endPos.y - gameObject.transform.position.y <= 0) {
            spawnPos = new Vector3(gameObject.transform.position.x + distance.x / 2, gameObject.transform.position.y-1 - distance.y / 2, 0);
            angle = 180 + Mathf.Atan2(endPos.y - gameObject.transform.position.y, endPos.x - gameObject.transform.position.x) * 180 / Mathf.PI;
        }
        //below left
        else if (endPos.x - gameObject.transform.position.x < 0 && endPos.y - gameObject.transform.position.y <= 0) {
            spawnPos = new Vector3(gameObject.transform.position.x - distance.x / 2, gameObject.transform.position.y-1 - distance.y / 2, 0);
            angle = 180 + Mathf.Atan2(endPos.y - gameObject.transform.position.y, endPos.x - gameObject.transform.position.x) * 180 / Mathf.PI;
        }
        //spawn laser beam
        lBlock = Instantiate(laser, spawnPos, new Quaternion(0, 0, 0, 0));
        //setting size of beam
        if(distance.x >= distance.y)
            lBlock.transform.localScale = new Vector3(distance.x, 1, 1);
        else if (distance.y > distance.x)
            lBlock.transform.localScale = new Vector3(distance.y, 1, 1);
        //set angle of beam
        lBlock.transform.Rotate(new Vector3(0, 0, angle));
    }

    void OnCollisionEnter(Collision col) {
        string colTag = col.collider.tag;
        //if player is on a platform reset double jump
        if (colTag == "PlatformS" || colTag == "PlatformV" || colTag == "PlatformH") {
            jumps = 0;
            currentTime = 0.01f;
        }
        //if player finishes level
        else if(colTag == "EndPlatform") {
            //play end sound
            audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().endS);
            HUD.endLevelBool = true;
        }
    }

    
}
