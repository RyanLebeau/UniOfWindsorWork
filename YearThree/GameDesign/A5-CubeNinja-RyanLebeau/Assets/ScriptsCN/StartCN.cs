using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
//RyanLebeau_104535367_60-377

public class StartCN : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void startBttn() {
        SceneManager.LoadScene("MainSceneCN");
    }
}
