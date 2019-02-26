using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Audio : MonoBehaviour {
    public AudioSource fxSource, musicSource;
    public AudioClip menuM, gameM, shootS, deathS, puS, expS, coinS, diaS, clickS,
            enDeathS, damageS, endS, laserS;

	// Use this for initialization
	void Awake () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    //play a single sound effect
    public void playFX(AudioClip clip) {
        //adjusting volume levels
        if(clip == shootS || clip == puS) {
            fxSource.volume = 0.4f;
        }
        else if (clip == coinS) {
            fxSource.volume = 0.6f;
        }
        else
            fxSource.volume = 1;
        fxSource.clip = clip;
        fxSource.Play();
    }

    //play music that loops in the background
    public void playMusic(AudioClip clip) {
        musicSource.Stop();
        musicSource.clip = clip;
        musicSource.loop = true;
        musicSource.volume = 0.75f;
        musicSource.Play();
    }
}
