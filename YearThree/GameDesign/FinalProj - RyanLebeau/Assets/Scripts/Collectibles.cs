using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Collectibles : MonoBehaviour {
    public GameObject audioM;

	// Use this for initialization
	void Start () {
		
	}
	
	// FixedUpdate is called once per 0.02s
	void FixedUpdate () {
        if(gameObject.tag == "Coin")
            gameObject.transform.Rotate(new Vector3(0, 0, 1.5f));
        else if (gameObject.tag == "Teleport")
            gameObject.transform.Rotate(new Vector3(1.5f, 0, 0));
        else if(gameObject.tag == "Diamond" || gameObject.tag == "OneUp" || gameObject.tag == "Gun" || gameObject.tag == "Speed" || gameObject.tag == "Laser" || gameObject.tag == "Teleport")
            gameObject.transform.Rotate(new Vector3(0, 1.5f, 0));
    }

    //if the character walks through a coin or diamond
    private void OnTriggerEnter(Collider col) {
        if (gameObject.tag == "Coin" && col.tag == "Character") {
            //play coin sound
            audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().coinS);
            Destroy(gameObject);
            HUD.coins += 1;
        }
        else if (gameObject.tag == "Diamond" && col.tag == "Character") {
            //play diamond sound
            audioM.GetComponent<Audio>().playFX(audioM.GetComponent<Audio>().diaS);
            Destroy(gameObject);
            HUD.diamonds += 1;
        }
        
    }
}
