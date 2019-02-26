using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EndZone : MonoBehaviour {
    Renderer mat;
    public Material green;
    public static bool end = false;
    public Text exit, score, death;
    public float time = 0;

	// Use this for initialization
	void Start () {
		mat = gameObject.GetComponent<Renderer>();
    }
	
	// Update is called once per frame
	void Update () {
        if (end) {
            exit.text = "You Win!";
            score.text = "Cubes Collected: " + Coins.score;
            death.text = "Deaths: " + DeathZone.death;
            time += Time.deltaTime;
            if (time >= 5) {
                end = false;
                Application.Quit();
            }
                
        }
        
	}

    void OnTriggerEnter(Collider col) {
        //if player enters safe zone
        if (col.name == "Player") {
            mat.material = green;
            end = true;
        }
    }
}
