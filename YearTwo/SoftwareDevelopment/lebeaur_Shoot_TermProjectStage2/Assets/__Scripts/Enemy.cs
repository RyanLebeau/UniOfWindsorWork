using System.Collections; // Required for Arrays & other Collections
using System.Collections.Generic; // Required for Lists and Dictionaries
using UnityEngine; // Required for Unity

public class Enemy : MonoBehaviour {
    [Header("Set in Inspector: Enemy")]
    public float speed = 10f; // The speed in m/s
    public float fireRate = 0.3f; // Seconds/shot (Unused)
    public float health = 10;
    public int score = 100; // Points earned for destroying this
    public float showDamageDuration = 0.1f;
    public float powerUpDropChance = 1f;
    [Header("Set Dynamically: Enemy")]
    public Color[] originalColors;
    public Material[] materials;// All the Materials of this & its children
    public bool showingDamage = false;
    public float damageDoneTime; // Time to stop showing damage
    public bool notifiedOfDestruction = false;
    protected BoundsCheck bndCheck;
    public static bool destroySound;
    //public Color colourEnemy;

    void Awake() {
        destroySound = false;
        bndCheck = GetComponent<BoundsCheck>();
        materials = Utils.GetAllMaterials(gameObject);
        originalColors = new Color[materials.Length];
        for (int i = 0; i < materials.Length; i++) {
            //materials[i].color = Color.blue;
            if(this.gameObject.tag == "Enemy0") {
                switch (GUIscript.e0C) {
                    case 0: materials[i].color = Color.blue; break;
                    case 1: materials[i].color = Color.green; break;
                    case 2: materials[i].color = Color.yellow; break;
                    case 3: materials[i].color = Color.cyan; break;
                    case 4: materials[i].color = Color.magenta; break;
                    case 5: materials[i].color = Color.white; break;
                    default: break;
                }
            }
            else if (this.gameObject.tag == "Enemy1") {
                switch (GUIscript.e1C) {
                    case 0: materials[i].color = Color.blue; break;
                    case 1: materials[i].color = Color.green; break;
                    case 2: materials[i].color = Color.yellow; break;
                    case 3: materials[i].color = Color.cyan; break;
                    case 4: materials[i].color = Color.magenta; break;
                    case 5: materials[i].color = Color.white; break;
                    default: break;
                }
            }
            if (this.gameObject.tag == "Enemy2") {
                switch (GUIscript.e2C) {
                    case 0: materials[i].color = Color.blue; break;
                    case 1: materials[i].color = Color.green; break;
                    case 2: materials[i].color = Color.yellow; break;
                    case 3: materials[i].color = Color.cyan; break;
                    case 4: materials[i].color = Color.magenta; break;
                    case 5: materials[i].color = Color.white; break;
                    default: break;
                }
            }
            if (this.gameObject.tag == "Enemy3") {
                switch (GUIscript.e3C) {
                    case 0: materials[i].color = Color.blue; break;
                    case 1: materials[i].color = Color.green; break;
                    case 2: materials[i].color = Color.yellow; break;
                    case 3: materials[i].color = Color.cyan; break;
                    case 4: materials[i].color = Color.magenta; break;
                    case 5: materials[i].color = Color.white; break;
                    default: break;
                }
            }
            if (this.gameObject.tag == "Enemy4") {
                switch (GUIscript.e4C) {
                    case 0: materials[i].color = Color.blue; break;
                    case 1: materials[i].color = Color.green; break;
                    case 2: materials[i].color = Color.yellow; break;
                    case 3: materials[i].color = Color.cyan; break;
                    case 4: materials[i].color = Color.magenta; break;
                    case 5: materials[i].color = Color.white; break;
                    default: break;
                }
            }
            originalColors[i] = materials[i].color;
        }
    }
    // This is a Property: A method that acts like a field
    public Vector3 pos { // a
        get {
            return (this.transform.position);
        }
        set {
            this.transform.position = value;
        }
    }
    void Update() {
        Move();
        if (showingDamage && Time.time > damageDoneTime) {
            UnShowDamage();
        }
        if (bndCheck != null && bndCheck.offDown) {
            Destroy(gameObject);
        }
    }
    public virtual void Move() { // b
        Vector3 tempPos = pos;
        tempPos.y -= speed * Time.deltaTime;
        pos = tempPos;
    }
    void OnCollisionEnter(Collision coll) {
        GameObject otherGO = coll.gameObject;
        switch (otherGO.tag) {
            case "ProjectilePlayer":
                Projectile p = otherGO.GetComponent<Projectile>();
                // If this Enemy is off screen, don't damage it.
                if (!bndCheck.isOnScreen) {
                    Destroy(otherGO);
                    break;
                }
                // Hurt this Enemy
                ShowDamage();
                // Get the damage amount from the Main WEAP_DICT.
                health -= Main.GetWeaponDefinition(p.type).damageOnHit;
                if (health <= 0) {
                    if (!notifiedOfDestruction) {
                        Main.S.shipDestroyed(this);
                    }
                    notifiedOfDestruction = true;
                    //score
                    if(this.gameObject.tag == "Enemy0") { Main.currentScore += GUIscript.e0Pts; Main.e0Kills += 1; }
                    else if(this.gameObject.tag == "Enemy1") { Main.currentScore += GUIscript.e1Pts; Main.e1Kills += 1; }
                    else if(this.gameObject.tag == "Enemy2") { Main.currentScore += GUIscript.e2Pts; Main.e2Kills += 1; }
                    else if(this.gameObject.tag == "Enemy3") { Main.currentScore += GUIscript.e3Pts; Main.e3Kills += 1; }
                    destroySound = true;
                    // Destroy this Enemy
                    Destroy(this.gameObject);
                }
                Destroy(otherGO);
                break;
            default:
                print("Enemy hit by non-ProjectilePlayer: " +
                otherGO.name);
                break;
        }
    }
    void ShowDamage() {
        foreach (Material m in materials) {
            m.color = Color.red;
        }
        showingDamage = true;
        damageDoneTime = Time.time + showDamageDuration;
    }
    void UnShowDamage() {
        for (int i = 0; i < materials.Length; i++) {
            materials[i].color = originalColors[i];
        }
        showingDamage = false;
    }
}
