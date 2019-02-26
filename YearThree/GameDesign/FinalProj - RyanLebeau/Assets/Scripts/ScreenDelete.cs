using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScreenDelete : MonoBehaviour {
    //public static float posX;
    //public static bool deleteHori = false;
    //public Collider hori;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        /*
        //horizontal platforms must be deleted differently since they can exit 
        //the trigger back onto the game screen
        if (deleteHori) {
            if(posX+18 < Character.currentPos.x) {
                //hori.gameObject.SetActive(false);
                deleteHori = false;
                Destroy(hori.gameObject);
                print(ProcGen.platformList[0].tag);
                ProcGen.platformList.RemoveAt(0);
            }
        }*/
	}

    //removing platform that moves off screen on the left
    private void OnTriggerExit(Collider col) {
        if (col.tag == "Cubey" || col.tag == "Hover" || col.tag == "BS" || col.tag == "FCubey" || col.tag == "SB") {
            //col.gameObject.SetActive(false);
            Destroy(col.gameObject);
        }/*
        else if (col.tag != "PlatformH" && col.tag != "Character" && col.tag != "lBlock") {
            //col.gameObject.SetActive(false);
            
            Destroy(col.gameObject);
            ProcGen.platformList.RemoveAt(0);
        }
        else if(col.tag == "PlatformH"){
            deleteHori = true;
            posX = Character.currentPos.x;
            hori = col;
            Destroy(col.gameObject);
        }*/

    }
}
