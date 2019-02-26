using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullets : MonoBehaviour {
    public float currTime;
    public GameObject audioM;

	// Use this for initialization
	void Start () {
        currTime = 0;
	}
	
	// Update is called once per frame
	void Update () {
        currTime += Time.deltaTime;
		if(gameObject.transform.position.y <= -1) {
            Destroy(gameObject);
        }
        if(currTime >= 4) {
            Destroy(gameObject);
        }

	}

    private void OnCollisionEnter(Collision cision) {
        if(cision.collider.tag == "Character" && gameObject.tag != "CharBllt") {
            Character.charHealth -= 1;
            //play damage sound and then destroy
            StartCoroutine(playDamageSound());
        }
        else if (cision.collider.tag == "BS" && gameObject.tag == "CharBllt") {
            HUD.kills += 1;
            Destroy(cision.gameObject);
            //play death sound and then destroy
            StartCoroutine(playDeathSound());
        }
        else if (cision.collider.tag == "SB" &&  !cision.gameObject.GetComponent<Enemies>().explode && gameObject.tag == "CharBllt") {
            HUD.kills += 1;
            Destroy(cision.gameObject);
            //play death sound and then destroy
            StartCoroutine(playDeathSound());
        }
        else if (cision.collider.tag == "Cubey" && gameObject.tag == "CharBllt") {
            HUD.kills += 1;
            Destroy(cision.gameObject);
            //play death sound and then destroy
            StartCoroutine(playDeathSound());
        }
        else if (cision.collider.tag == "Hover" && gameObject.tag == "CharBllt") {
            HUD.kills += 1;
            Destroy(cision.gameObject);
            //play death sound and then destroy
            StartCoroutine(playDeathSound());
        }
        else if (cision.collider.tag == "FCubey" && gameObject.tag == "CharBllt") {
            HUD.kills += 1;
            Destroy(cision.gameObject);
            //play death sound and then destroy
            StartCoroutine(playDeathSound());
        }
    }

    IEnumerator playDeathSound() {
        //play death sound
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().enDeathS);
        gameObject.GetComponent<Renderer>().enabled = false;
        gameObject.GetComponent<Collider>().enabled = false;
        yield return new WaitForSeconds(0.4f);
        Destroy(gameObject);
        yield return null;
    }

    IEnumerator playDamageSound() {
        //play damage sound
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().damageS);
        gameObject.GetComponent<Renderer>().enabled = false;
        gameObject.GetComponent<Collider>().enabled = false;
        yield return new WaitForSeconds(1);
        Destroy(gameObject);
        yield return null;
    }
}
