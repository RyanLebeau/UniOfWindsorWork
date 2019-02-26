using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;


public class CMMain : MonoBehaviour {
    public GameObject card, cardFront, temp;
    public static GameObject[] cards;
    public Quaternion rotation;
    public Text score, timer;
    public int random, randNum;
    public static int scoreNum, easyHard, timerNum = 0, countMatches;
    public static int[] cardLayers, cardTagNum;
    public static bool winOrLose; 
    public static string[] cardTag;


    // Use this for initialization
    void Start () {
        //initializing variables
        scoreNum = 1000;
        winOrLose = false;
        Vector3 pos = new Vector3();
        rotation = Quaternion.Euler(90, 90, 90);
        switch (easyHard) {
            //easy mode
            case 1:
                //initial position
                pos.x = -3;
                pos.y = 7;
                pos.z = -5;
                //array definitions
                cards = new GameObject[12];
                cardTag = new string[]{ "One", "Two", "Three", "Four", "Five", "Six" };
                cardTagNum = new int[] { 0, 0, 0, 0, 0, 0 };
                //first card
                card.gameObject.tag = randCard();
                cards[0] = card;
                //populating each row
                for (int i = 0; i < 11; i++) {
                    if (i <= 2) {
                        temp = Instantiate(card, pos, rotation);
                        
                        //setting tag for card
                        temp.tag = randCard();
                        //adding instantiate card to array
                        cards[i + 1] = temp;
                        pos.x += 6;
                    }
                    else if (i > 2 && i <= 6) {
                        temp = Instantiate(card, pos, rotation);
                        temp.tag = randCard();
                        cards[i + 1] = temp;
                        pos.x += 6;
                    }
                    else {
                        temp = Instantiate(card, pos, rotation);
                        temp.tag = randCard();
                        cards[i + 1] = temp;
                        pos.x += 6;
                    }
                    //setting initial position for each row
                    if (i == 2) {
                        pos.x = -9;
                        pos.y -= 6;
                    }
                    else if (i == 6) {
                        pos.x = -9;
                        pos.y -= 6;
                    }
                }
                break;
            //hard mode
            case 2:
                //initial position
                pos.x = -5;
                pos.y = 7;
                pos.z = -5;
                //array definitions
                cards = new GameObject[18];
                cardTag = new string[] { "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
                cardTagNum = new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0};
                //first card
                card.gameObject.tag = randCard();
                card.transform.localScale = new Vector3(3f, 0.01f, 4f);
                cards[0] = card;
                //populating each row
                for (int i = 0; i < 17; i++) {
                    if (i == 0) {
                        temp = Instantiate(card, pos, rotation);
                        temp.transform.localScale = new Vector3(3f, 0.01f, 4f);
                        //setting random tag to card
                        temp.tag = randCard();
                        //adding instantiate card object to array
                        cards[i + 1] = temp;
                    }
                    else if (i == 1) {
                        pos.x = -1;
                        temp = Instantiate(card, pos, rotation);
                        temp.transform.localScale = new Vector3(3f, 0.01f, 4f);
                        temp.tag = randCard();
                        cards[i + 1] = temp;
                        pos.x += 4;
                    }
                    else if (i > 1 && i <= 4) {
                        temp = Instantiate(card, pos, rotation);
                        temp.transform.localScale = new Vector3(3f, 0.01f, 4f);
                        temp.tag = randCard();
                        cards[i + 1] = temp;
                        pos.x += 4;
                    }
                    else if (i > 4 && i <= 10) {
                        temp = Instantiate(card, pos, rotation);
                        temp.transform.localScale = new Vector3(3f, 0.01f, 4f);
                        temp.tag = randCard();
                        cards[i + 1] = temp;
                        pos.x += 4;
                    }
                    else {
                        temp = Instantiate(card, pos, rotation);
                        temp.transform.localScale = new Vector3(3f, 0.01f, 4f);
                        temp.tag = randCard();
                        cards[i + 1] = temp;
                        pos.x += 4;
                    }
                    //setting initial position for each row
                    if (i == 4) {
                        pos.x = -9;
                        pos.y -= 6;
                    }
                    else if (i == 10) {
                        pos.x = -9;
                        pos.y -= 6;
                    }
                }
                break;
            default: break;
        }
        
	}
	
	// Update is called once per frame
	void Update () {
        score.text = "Score: " + scoreNum;
        timer.text = "Time: " + timerNum + "s";
        timerNum = (int)Time.timeSinceLevelLoad;
        //if user loses and reaches 0 score
        if (scoreNum <= 0) {
            winOrLose = false;
            SceneManager.LoadScene("CMEndScene");
        }
        //if number of matches corresponds with difficulty mode user wins
        else if (easyHard == 1 && countMatches == 6 || easyHard == 2 && countMatches == 9) {
            winOrLose = true;
            SceneManager.LoadScene("CMEndScene");
        }
    }

    //function to randomly assign card to type(if a pair of the type does not exist)
    public string randCard() {
        string cTag;
        while (true) {
            //easy mode(12 cards)
            if(easyHard == 1) {
                random = Random.Range(0, 6);
                if (cardTagNum[random] < 2) {
                    cardTagNum[random] += 1;
                    cTag = cardTag[random];
                    return cTag;
                }
            }
            //hard mode(18 cards)
            else if(easyHard == 2) {
                random = Random.Range(0, 9);
                if (cardTagNum[random] < 2) {
                    cardTagNum[random] += 1;
                    cTag = cardTag[random];
                    return cTag;
                }
            }
            
        }
    }
}
