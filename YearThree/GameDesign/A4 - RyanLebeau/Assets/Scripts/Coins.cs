using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Coins : MonoBehaviour {
    public GameObject coin;
    public List<GameObject> coinsArray;
    public List<Vector3> positions;
    public static int score = 0;

	// Use this for initialization
	void Start () {
        coinsArray = new List<GameObject>();
        positions = new List<Vector3>();
        //set positions of coins
        SetPostionCoins();
        //creating 15 collectable coins
        for (int i = 0; i < 15; i++) {
            coinsArray.Add(Instantiate(coin, positions[i], new Quaternion(0,0,0,0)));
        }
        
	}

    // FixedUpdate is called once per 0.2s
    void FixedUpdate () {
        foreach (GameObject c in coinsArray) {
            c.transform.Rotate(30.0f * Time.fixedDeltaTime, 15.0f * Time.fixedDeltaTime, 45.0f * Time.fixedDeltaTime);
        }
    }

    void SetPostionCoins() {
        positions.Add(new Vector3(3, 3.5f, 4));
        positions.Add(new Vector3(-3, 6f, 7));
        positions.Add(new Vector3(-4, 6.75f, 12.5f));
        positions.Add(new Vector3(-4, 6.75f, 10.5f));
        positions.Add(new Vector3(-2, 7.75f, 25));
        positions.Add(new Vector3(-2, 7.75f, 29.5f));
        positions.Add(new Vector3(9, 9, 37));
        positions.Add(new Vector3(15f, 9.75f, 41f));
        positions.Add(new Vector3(18.5f, 9.75f, 43f));
        positions.Add(new Vector3(26f, 11.75f, 42f));
        positions.Add(new Vector3(23f, 10.5f, 43.75f));
        positions.Add(new Vector3(28f, 12.5f, 40.75f));
        positions.Add(new Vector3(36f, 14.7f, 42f));
        positions.Add(new Vector3(33f, 14.7f, 38.5f));
        positions.Add(new Vector3(39.5f, 14.7f, 46f));
    }
}
