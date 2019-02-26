using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Card : MonoBehaviour {
    public GameObject card, cardFront, toBeTurned;
    public static List<GameObject> cardsSelected;
    public Material oneM,twoM,threeM,fourM,fiveM,sixM,sevenM,eightM,nineM;
    public MeshRenderer render;
    public Vector3 cardPos;
    public AudioSource source;
    public AudioClip turnSound,matchSound,nonMatchSound;

	// Use this for initialization
	void Start () {
        //easy mode
        if(CMMain.easyHard == 1) {
            //setting material of cards
            for (int j = 0; j < 6; j++) {
                FindTags(CMMain.cardTag[j]);
            }
        }
        //hard mode
        else if(CMMain.easyHard == 2) {
            for (int j = 0; j < 9; j++) {
                FindTags(CMMain.cardTag[j]);
            }
        }
        Physics.queriesHitTriggers = true;
        cardsSelected = new List<GameObject>();
        source = GetComponent<AudioSource>();
    }

    //when mouse clicks a card
    void OnMouseDown() {
        cardsSelected.Add(this.gameObject);
        source.PlayOneShot(turnSound);
        //flip selected card
        cardsSelected[cardsSelected.Count - 1].transform.Rotate(0.0f, 0.0f, 180.0f);
        //if there are 2 cards turned over
        if(cardsSelected.Count == 2) { StartCoroutine(FlipWait()); }

    }

    //handling time delay for cards
    private IEnumerator FlipWait() {
        //locking cursor position
        Cursor.visible = false;
        Cursor.lockState = CursorLockMode.Locked;
        //if cards match or not start sound effects
        if (cardsSelected[0].CompareTag(cardsSelected[1].tag)) { source.PlayOneShot(matchSound); }
        else { source.PlayOneShot(nonMatchSound); }
        //pause for one second
        yield return new WaitForSeconds(1);
        RotateBack();
    }

    //handle if both cards flipped match or not
    public void RotateBack() {
        //if cards match
        if (cardsSelected[0].CompareTag(cardsSelected[1].tag)) {
            CMMain.countMatches++;
            Destroy(cardsSelected[0]);
            Destroy(cardsSelected[1]);
            cardsSelected.Clear();
        }
        //if cards do not match
        else {
            cardsSelected[0].transform.Rotate(0.0f, 0.0f, 180.0f);
            cardsSelected[1].transform.Rotate(0.0f, 0.0f, 180.0f);
            CMMain.scoreNum -= 40;
            cardsSelected.Clear();
        }
        //unlocking cursor position
        Cursor.visible = true;
        Cursor.lockState = CursorLockMode.None;  
    }

    //finds cards on designated tag and passes the card gameobject to 'ChangeMaterial'
    public void FindTags(string tag) {
        //easy mode
        if(CMMain.easyHard == 1) {
            for (int i = 0; i < 12; i++) {
                if (CMMain.cards[i].CompareTag(tag)) {
                    ChangeMaterial(CMMain.cards[i].gameObject);
                }
            }
        }
        //hard mode
        else if(CMMain.easyHard == 2) {
            for (int i = 0; i < 18; i++) {
                if (CMMain.cards[i].CompareTag(tag)) {
                    ChangeMaterial(CMMain.cards[i].gameObject);
                }
            }
        }
        
    }

    //change a game objects material
    public void ChangeMaterial(GameObject tempCard) {
        //gets mesh renderer of child(front) of parameter card
        cardFront = tempCard.gameObject.transform.GetChild(0).gameObject;
        render = cardFront.GetComponent<MeshRenderer>();
        //each layer has a different material
        switch (tempCard.tag) {
            case "One":
                render.material = oneM; break;
            case "Two":
                render.material = twoM; break;
            case "Three":
                render.material = threeM; break;
            case "Four":
                render.material = fourM; break;
            case "Five":
                render.material = fiveM; break;
            case "Six":
                render.material = sixM; break;
            case "Seven":
                render.material = sevenM; break;
            case "Eight":
                render.material = eightM; break;
            case "Nine":
                render.material = nineM; break;
            default:
                break;
        }
    }
}
