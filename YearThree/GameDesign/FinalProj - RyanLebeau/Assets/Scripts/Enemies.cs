using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemies : MonoBehaviour {
    public static Vector3 cPos, hPos, bsPos, fcPos, sbPos;
    public static string sideHit;
    public GameObject bullet, audioM, explosion, indOne, indTwo, indicator1, indicator2;
    public Vector3 cMove, hMove, fcMove;
    public float currTime, boomTime;
    public bool medium, shootLeft, explode;
    //public static GameObject indicator;

	// Use this for initialization
	void Start () {
        cMove = new Vector3(0.06f, 0, 0);
        cPos = new Vector3(0, 0, 0);
        hMove = new Vector3(-0.04f, 0, 0);
        hPos = new Vector3(0, 0, 0);
        bsPos = new Vector3(-1.5f, 0, 0);
        fcMove = new Vector3(-0.08f, 0, 0);
        fcPos = new Vector3(0, 0, 0);
        sbPos = new Vector3(0, 0, 0);
        currTime = 0;
        medium = false;
        shootLeft = false;
        explode = false;
        boomTime = 0;
        if(gameObject.tag == "SB") {
            indicator1 = Instantiate(indOne, Character.Pos, new Quaternion(0, 0, 0, 0));
            indicator2 = Instantiate(indTwo, Character.Pos, new Quaternion(0, 0, 0, 0));
            indicator1.SetActive(false);
            indicator2.SetActive(false);
        }
        
        //indOne.SetActive(false);
        //indTwo.SetActive(false);
    }
	
	// Update is called once per frame
	void Update () {
		
	}

    // FixedUpdate is called once per 0.02s
    void FixedUpdate() {
        //if enemy falls off map
        if(gameObject.transform.position.y < -5) {
            Destroy(gameObject);
        }
        //if enemies, primarily hover, are spawned off map kill them
        else if(gameObject.transform.position.y >= 15) {
            Destroy(gameObject);
        }
        //if enemy spawned in is 'Cubey'
        if(gameObject.tag == "Cubey") {
            currTime += Time.fixedDeltaTime;
            if (currTime >= 3) {
                cMove.x *= -1;
                currTime = 0;
            }
            gameObject.transform.Translate(cMove);
            cPos = gameObject.transform.position;
        }
        //if enemy spawned in is 'Hover'
        else if (gameObject.tag == "Hover") {
            currTime += Time.fixedDeltaTime;
            if (currTime >= 3.5f) {
                hMove.x *= -1;
                currTime = 0;
            }
            gameObject.transform.Translate(hMove);
            hPos = gameObject.transform.position;
        }
        //if enemy spawned in is 'BS-Bouncy Shooter'
        else if (gameObject.tag == "BS") {
            bsPos = gameObject.transform.position;
            currTime += Time.fixedDeltaTime;
            if (currTime >= 2) {
                Shoot();
                currTime = 0;
            }
        }
        //if enemy spawned in is 'FastCubey'
        else if (gameObject.tag == "FCubey") {
            currTime += Time.fixedDeltaTime;
            if (currTime >= 1.2f) {
                fcMove.x *= -1;
                Shoot();
                currTime = 0;
            }
            gameObject.transform.Translate(fcMove);
            fcPos = gameObject.transform.position;
        }
        //if enemy spawned in is 'SB-Suicide Bomber'
        else if (gameObject.tag == "SB") {
            Vector3 spawnPos = Character.Pos;
            spawnPos.y += 1;
            if (explode)
                boomTime += Time.fixedDeltaTime;
            else
                currTime += Time.fixedDeltaTime;
            Vector3 temp = Character.Pos;
            temp.x += 3;
            temp.y += 0;
            if (currTime >= 7) {
                gameObject.transform.position = temp;
                explode = true;
                currTime = 0;
            }
            if (boomTime >= 2.5f) {
                Explode();
                boomTime = 0;
            }
            //setting indicator 2
            if (Mathf.Abs(Character.Pos.x - sbPos.x) <= 3) {
                indicator1.SetActive(false);
                indicator2.SetActive(true);
                indicator2.transform.position = spawnPos;
            }
            else if (Mathf.Abs(Character.Pos.x - sbPos.x) <= 6) {
                indicator1.SetActive(true);
                indicator2.SetActive(false);
                indicator1.transform.position = spawnPos;
            }
            else {
                indicator2.SetActive(false);
                indicator1.SetActive(false);
            }
            sbPos = gameObject.transform.position;
        }

    }

    //basic enemy shooting
    public void Shoot() {
        if(gameObject.tag == "BS") {
            Vector3 spawnPos = bsPos;
            spawnPos.y += 1.5f;
            //shoot in direction of player
            if(Character.Pos.x <= bsPos.x) {
                spawnPos.x -= 0.5f;
                GameObject newBllt = Instantiate(bullet, spawnPos, new Quaternion(0, 0, 0, 0));
                newBllt.GetComponent<Rigidbody>().AddForce(new Vector3(-800, 400));
            }
            else {
                spawnPos.x += 0.5f;
                GameObject newBllt = Instantiate(bullet, spawnPos, new Quaternion(0, 0, 0, 0));
                newBllt.GetComponent<Rigidbody>().AddForce(new Vector3(800, 400));
            } 
        }
        //FCubey shoots a bullet in every other direction
        if (gameObject.tag == "FCubey") {
            Vector3 spawnPos = fcPos;
            spawnPos.y += 1;
            //shoot in direction of player
            if (shootLeft) {
                spawnPos.x -= 0.5f;
                GameObject newBllt = Instantiate(bullet, spawnPos, new Quaternion(0, 0, 0, 0));
                newBllt.GetComponent<Rigidbody>().AddForce(new Vector3(-800, 400));
                shootLeft = false;
            }
            else {
                spawnPos.x += 0.5f;
                GameObject newBllt = Instantiate(bullet, spawnPos, new Quaternion(0, 0, 0, 0));
                newBllt.GetComponent<Rigidbody>().AddForce(new Vector3(800, 400));
                shootLeft = true;
            }
        }
    }

    //explosion for SB
    public void Explode() {
        //play explode sound
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().expS);
        GameObject temp = Instantiate(explosion, sbPos, new Quaternion(0,0,0,0));
        Destroy(temp, 3.0f);
        Destroy(indicator1);
        Destroy(indicator2);
        //remove indOne or IndTwo
        if (Mathf.Abs(Character.Pos.x - sbPos.x) <= 3) {
            //play damage sound and then destroys
            StartCoroutine(playDamageSound());
            Character.charHealth -= 2;
        }
        else if (Mathf.Abs(Character.Pos.x - sbPos.x) <= 6) {
            //play damage sound and then destroy
            StartCoroutine(playDamageSound());
            Character.charHealth -= 1;
        }
        Destroy(gameObject);
    }

    public void OnCollisionEnter(Collision cision) {
        if (gameObject.tag == "Cubey" && cision.collider.tag == "Character") {
            if (sideHit == "top") {
                //play death sound and then destroy
                StartCoroutine(playDeathSound());
                HUD.kills += 1;
            }
            else if (sideHit == "bottom" || sideHit == "right" || sideHit == "left") {
                //play damage sound and then destroy
                StartCoroutine(playDamageSound());
                Character.charHealth -= 1;
            }
        }
        else if (gameObject.tag == "Hover" && cision.collider.tag == "Character") {
            if (sideHit == "top") {
                //play death sound and then destroy
                StartCoroutine(playDeathSound());
                HUD.kills += 1;
            }
            else if (sideHit == "bottom" || sideHit == "right" || sideHit == "left") {
                //play damage sound and then destroy
                StartCoroutine(playDamageSound());
                Character.charHealth -= 1;
            }
        }
        else if (gameObject.tag == "BS" && cision.collider.tag == "Character") {
            if (sideHit == "top") {
                //play death sound and then destroy
                StartCoroutine(playDeathSound());
                HUD.kills += 1;
            }
            else if (sideHit == "bottom" || sideHit == "right" || sideHit == "left") {
                //play damage sound and then destroy
                StartCoroutine(playDamageSound());
                Character.charHealth -= 1;
            }
        }
        else if (gameObject.tag == "FCubey" && cision.collider.tag == "Character") {
            if (sideHit == "top") {
                //play death sound and then destroy
                StartCoroutine(playDeathSound());
                HUD.kills += 1;
            }
            else if (sideHit == "bottom" || sideHit == "right" || sideHit == "left") {
                //play damage sound and then destroy
                StartCoroutine(playDamageSound());
                Character.charHealth -= 1;
            }
        }
        else if (gameObject.tag == "SB" && cision.collider.tag == "Character") {
            if (sideHit == "top" && !explode) {
                //play death sound and then destroy
                StartCoroutine(playDeathSound());
                HUD.kills += 1;
            }
        }
        else if ((gameObject.tag == "Cubey" || gameObject.tag == "Hover" || gameObject.tag == "BS" || gameObject.tag == "FCubey" || gameObject.tag == "SB") && cision.collider.tag == "LBound") {
            gameObject.GetComponent<Rigidbody>().isKinematic = true;
        }
    }

    IEnumerator playDeathSound() {
        //play death sound
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().enDeathS);
        foreach (Renderer temp in gameObject.GetComponentsInChildren<Renderer>())
            temp.enabled = false;
        gameObject.GetComponent<Renderer>().enabled = false;
        gameObject.GetComponent<Collider>().enabled = false;
        yield return new WaitForSeconds(0.4f);
        Destroy(gameObject);
        yield return null;
    }

    IEnumerator playDamageSound() {
        //play damage sound
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().damageS);
        foreach (Renderer temp in gameObject.GetComponentsInChildren<Renderer>())
            temp.enabled = false;
        gameObject.GetComponent<Renderer>().enabled = false;
        gameObject.GetComponent<Collider>().enabled = false;
        yield return new WaitForSeconds(1);
        Destroy(gameObject);
        yield return null;
    }
}
