using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PowerUps : MonoBehaviour {
    public GameObject audioM;

	// Use this for initialization
	void Start () {

    }
	
	// Update is called once per frame
	void Update () {

    }

    private void OnTriggerEnter(Collider col) {
        if (gameObject.tag == "Teleport" && col.tag == "Character") {
            ResetPU();
            //teleport to mouse click 5 times
            HUD.powTime = 5;
            HUD.powerUp = 1;
            Character.ifTeleport = true;
            //play powerup sound and then destroy
            StartCoroutine(playSound());
        }
        else if (gameObject.tag == "Laser" && col.tag == "Character") {
            ResetPU();
            //laser that is from character to click killing all in its way
            HUD.powTime = 15;
            HUD.powerUp = 2;
            Character.ifLaser = true;
            //play powerup sound and then destroy
            StartCoroutine(playSound());
        }
        else if (gameObject.tag == "Speed" && col.tag == "Character") {
            ResetPU();
            //increase speed
            HUD.powTime = 7;
            HUD.powerUp = 3;
            //set movement vectors
            Character.forward = new Vector3(0.15f, 0, 0);
            Character.backward = new Vector3(-0.15f, 0, 0);
            Character.forwardSprint = new Vector3(0.22f, 0, 0);
            Character.backwardSprint = new Vector3(-0.22f, 0, 0);
            //play powerup sound and then destroy
            StartCoroutine(playSound());
        }
        else if (gameObject.tag == "Gun" && col.tag == "Character") {
            ResetPU();
            //provides basic shooting to the character
            Character.ifShoot = true;
            HUD.powTime = 10;
            HUD.powerUp = 4;
            //play powerup sound and then destroy
            StartCoroutine(playSound());
        }
        else if (gameObject.tag == "OneUp" && col.tag == "Character") {
            //adds 1-3 health to user
            Character.charHealth += 1;
            //play powerup sound and then destroy
            StartCoroutine(playSound());
        }
    }

    public void ResetPU() {
        Character.ifShoot = false;
        Character.ifTeleport = false;
        Character.ifLaser = false;
        Character.forward = new Vector3(0.1f, 0, 0);
        Character.backward = new Vector3(-0.1f, 0, 0);
        Character.forwardSprint = new Vector3(0.15f, 0, 0);
        Character.backwardSprint = new Vector3(-0.15f, 0, 0);
    }

    IEnumerator playSound() {
        //play powerup sound
        audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().puS);
        foreach (Renderer temp in gameObject.GetComponentsInChildren<Renderer>())
            temp.enabled = false;
        gameObject.GetComponent<Renderer>().enabled = false;
        gameObject.GetComponent<Collider>().enabled = false;
        yield return new WaitForSeconds(1.2f);
        Destroy(gameObject);
        yield return null;
    }
}
