using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;

public class LoginScript : MonoBehaviour {
    public List<string> normalUsers, newUsers, blockedUsers, appleSaves, RPSsaves, MemSaves, ShmupSaves;
    public List<List<string>> timeHistory;
    public Text errMsg, permDenyMM, errMsgNewPass, errMsgDelete, errMsgBlock, userEntry, APuserEntry, RPSuserEntry, MemUserEntry, ShmupUserEntry;
    public List<Text> userLogs, appleLogs, RPSLogs, MemLogs, ShmupLogs;
    public Canvas login, firstLogin, mainMenu, fileCanvas, userAccCanvas,
        createUserCanvas, deleteUserCanvas, changePassCanvas, blockedCanvas, configCanvas, audioCanvas,
        bgChoiceCanvas, historyCanvas, APCanvas, APhistoryCanvas, RPSCanvas, RPSHistoryCanvas, MemoryCanvas,
        MemHistoryCanvas, ShmupCanvas, ShmupConfigCanvas, ShmupHistoryCanvas;
    public AudioSource aSource;
    public AudioClip bgMusicOne, bgMusicTwo, bgMusicThree, buttonClick;
    public Slider volSlider;
    public Image background, bgGrey, overlay, display;
    public Sprite bgOne, bgGreyOne, bgOlOne, bgTwo, bgGreyTwo, bgOlTwo, bgThree, bgGreyThree, bgOlThree;
    public GameObject historyEmpty, APhistoryEmpty, RPShistoryEmpty, MemHistoryEmpty, ShmupHistoryEmpty;
    //public History userData;
    public bool adminUser;

    public static string currUser, currPass, newUser, newPass, userSearch, currScreen, logString;
    public static int passAttempts = 0, bgChoiceNum = 0;
    public static float logTime;



    // Use this for initialization
    void Start () {
        //set admin and lists to empty
        normalUsers = new List<string>();
        normalUsers.Add("admin");
        PlayerPrefs.SetString("admin", "admin");
        adminUser = false;
        newUsers = new List<string>();
        blockedUsers = new List<string>();
        //-user history order
        //log in date
        //username
        //log in time
        //load user lists values
        //time in game
        timeHistory = new List<List<string>>();
        userLogs = new List<Text>();
        loadUsers();
        //set bgImage
        switch (bgChoiceNum) {
            case 0:
                background.sprite = bgOne;
                bgGrey.sprite = bgGreyOne;
                overlay.sprite = bgOlOne;
                break;
            case 1:
                background.sprite = bgTwo;
                bgGrey.sprite = bgGreyTwo;
                overlay.sprite = bgOlTwo;
                break;
            case 2:
                background.sprite = bgThree;
                bgGrey.sprite = bgGreyThree;
                overlay.sprite = bgOlThree;
                break;
            default: break;
        }
        //start music
        aSource = GetComponent<AudioSource>();
        aSource.PlayOneShot(bgMusicOne);
        //set canvas layers
        login.gameObject.SetActive(true);
        firstLogin.gameObject.SetActive(false);
        mainMenu.gameObject.SetActive(false);
        //disabling subscreen and button menus for main menu
        canvasOff();
	}
	
	// Update is called once per frame
	void Update () {
        logTime = Time.time;
	}

    private void OnDisable() {
        int temp = (int)logTime - int.Parse(timeHistory[timeHistory.Count - 1][2]);
        timeHistory[timeHistory.Count - 1].Add(temp.ToString());
        saveUsers();
    }

    //username input field
    public void usernameIn(string user) {
        if(currUser != user) { passAttempts = 0; }
        currUser = user;
    }
    //password input field
    public void passwordIn(string password) {
        currPass = password;
    }
    //login button
    public void loginButton() {
        aSource.PlayOneShot(buttonClick);
        if (normalUsers.Contains(currUser) || newUsers.Contains(currUser)) {
            //password matches
            if(currPass == PlayerPrefs.GetString(currUser)) {
                //new user
                if (newUsers.Contains(currUser)) {
                    login.gameObject.SetActive(false);
                    firstLogin.gameObject.SetActive(true);
                    //since user logged in first time set as normal user
                    normalUsers.Add(currUser);
                    newUsers.Remove(currUser);
                    //history log
                    timeHistory.Add(new List<string>());
                    //list of lists -> list of strings -> history data 0 1 2 3 4
                    timeHistory[timeHistory.Count - 1].Add(System.DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss"));
                    timeHistory[timeHistory.Count - 1].Add(currUser);
                    int temp = (int)logTime;
                    timeHistory[timeHistory.Count - 1].Add(temp.ToString());
                    timeHistory[timeHistory.Count - 1].Add("NEW");
                    saveUsers();
                }
                //normal user
                else {
                    if(currUser == "admin") { adminUser = true; }
                    login.gameObject.SetActive(false);
                    mainMenu.gameObject.SetActive(true);
                    //history log
                    timeHistory.Add(new List<string>());
                    //list of lists -> list of strings -> history data 0 1 2 3 4
                    timeHistory[timeHistory.Count - 1].Add(System.DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss"));
                    timeHistory[timeHistory.Count - 1].Add(currUser);
                    int temp = (int)logTime;
                    timeHistory[timeHistory.Count - 1].Add(temp.ToString());
                    timeHistory[timeHistory.Count - 1].Add("NORMAL");
                    saveUsers();
                }
            }
            //password does not match
            else {
                errMsg.text = "Incorrect Password";
                passAttempts++;
                if(passAttempts == 3 && currUser != "admin") {
                    errMsg.text = "3 failed attempts user blocked";
                    blockedUsers.Add(currUser);
                    if (normalUsers.Contains(currUser)) { normalUsers.Remove(currUser); }
                    else if (newUsers.Contains(currUser)) { newUsers.Remove(currUser); }
                    saveUsers();
                }
            }
        }
        else {
            if (blockedUsers.Contains(currUser)) { errMsg.text = "User has been blocked contact admin"; }
            else { errMsg.text = "Username does not exist"; }
        }
    }
    //exit login button
    public void exitButton() {
        aSource.PlayOneShot(buttonClick);
        Application.Quit();
    }

    //First Login
    public void firstLoginNewPass(string password) {
        currPass = password;
    }
    public void firstLoginPassButton() {
        aSource.PlayOneShot(buttonClick);
        PlayerPrefs.DeleteKey(currUser);
        PlayerPrefs.SetString(currUser, currPass);
        firstLogin.gameObject.SetActive(false);
        mainMenu.gameObject.SetActive(true);
    }

    //Main Menu
    //-file button options
    public void fileButton() {
        aSource.PlayOneShot(buttonClick);
        //if in a submenu
        if (overlay.gameObject.activeSelf) {
            canvasOff();
        }
        //if file open already
        if (fileCanvas.gameObject.activeSelf) {
            fileCanvas.gameObject.SetActive(false);
        }
        else {
            fileCanvas.gameObject.SetActive(true);
        }
        
        //disable other main button canvas's
        userAccCanvas.gameObject.SetActive(false);
        configCanvas.gameObject.SetActive(false);
        APCanvas.gameObject.SetActive(false);
        RPSCanvas.gameObject.SetActive(false);
        MemoryCanvas.gameObject.SetActive(false);
        ShmupCanvas.gameObject.SetActive(false);
        ShmupConfigCanvas.gameObject.SetActive(false);
    }
    public void userAccButton() {
        aSource.PlayOneShot(buttonClick);
        userAccCanvas.gameObject.SetActive(true);
        //disable other file button canvas's
        configCanvas.gameObject.SetActive(false);
    }
    public void configButton() {
        aSource.PlayOneShot(buttonClick);
        configCanvas.gameObject.SetActive(true);
        //disable other file button canvas's
        userAccCanvas.gameObject.SetActive(false);
    }
    public void historyButton() {
        aSource.PlayOneShot(buttonClick);
        overlay.gameObject.SetActive(true);
        historyCanvas.gameObject.SetActive(true);
        currScreen = "UserHistory";
        populateUserHistory();
        //disable other main button canvas's
        fileCanvas.gameObject.SetActive(false);
        userAccCanvas.gameObject.SetActive(false);
        configCanvas.gameObject.SetActive(false);
    }
    public void historyBackBttn() {
        aSource.PlayOneShot(buttonClick);
        overlay.gameObject.SetActive(false);
        historyCanvas.gameObject.SetActive(false);
        userEntry.gameObject.SetActive(false);
        disableUserHistory();
    }
    //--user accounts button options
    public void createUserButton() {
        aSource.PlayOneShot(buttonClick);
        if (adminUser) {
            fileCanvas.gameObject.SetActive(false);
            userAccCanvas.gameObject.SetActive(false);
            //enable canvas for create user
            overlay.gameObject.SetActive(true);
            createUserCanvas.gameObject.SetActive(true);
            currScreen = "CreateUser";
        }
        else { StartCoroutine(PermDenied()); }
    }
    public void deleteUserButton() {
        aSource.PlayOneShot(buttonClick);
        if (adminUser) {
            fileCanvas.gameObject.SetActive(false);
            userAccCanvas.gameObject.SetActive(false);
            overlay.gameObject.SetActive(true);
            deleteUserCanvas.gameObject.SetActive(true);
            currScreen = "DeleteUser";
        }
        else { StartCoroutine(PermDenied()); }
    }
    public void changePasswordButton() {
        aSource.PlayOneShot(buttonClick);
        fileCanvas.gameObject.SetActive(false);
        userAccCanvas.gameObject.SetActive(false);
        overlay.gameObject.SetActive(true);
        changePassCanvas.gameObject.SetActive(true);
        currScreen = "ChangePassword";
    }
    public void blockedUserButton() {
        aSource.PlayOneShot(buttonClick);
        if (adminUser) {
            fileCanvas.gameObject.SetActive(false);
            userAccCanvas.gameObject.SetActive(false);
            overlay.gameObject.SetActive(true);
            blockedCanvas.gameObject.SetActive(true);
            currScreen = "BlockedUsers";
        }
        else { StartCoroutine(PermDenied()); }
    }
    //---creating a user
    public void createUserInput(string username) {
        newUser = username;
    }
    public void confirmCreateButton() {
        aSource.PlayOneShot(buttonClick);
        newUsers.Add(newUser);
        PlayerPrefs.SetString(newUser, newUser);
        overlay.gameObject.SetActive(false);
        createUserCanvas.gameObject.SetActive(false);
        //save lists
        saveUsers();
    }
    public void createUserBackBttn() {
        aSource.PlayOneShot(buttonClick);
        overlay.gameObject.SetActive(false);
        createUserCanvas.gameObject.SetActive(false);
    }
    //---deleting a user
    public void deleteUserIn(string username) {
        userSearch = username;
    }
    public void deleteUserConfirmBttn() {
        aSource.PlayOneShot(buttonClick);
        if(userSearch == "admin") {
            errMsgDelete.text = "admin account can not be deleted";
            errMsgDelete.gameObject.SetActive(true);
        }
        else if (normalUsers.Contains(userSearch)) {
            normalUsers.Remove(userSearch);
            overlay.gameObject.SetActive(false);
            deleteUserCanvas.gameObject.SetActive(false);
            errMsgDelete.gameObject.SetActive(false);
        }
        else if (newUsers.Contains(userSearch)) {
            newUsers.Remove(userSearch);
            overlay.gameObject.SetActive(false);
            deleteUserCanvas.gameObject.SetActive(false);
            errMsgDelete.gameObject.SetActive(false);
        }
        else if (blockedUsers.Contains(userSearch)) {
            blockedUsers.Remove(userSearch);
            overlay.gameObject.SetActive(false);
            deleteUserCanvas.gameObject.SetActive(false);
            errMsgDelete.gameObject.SetActive(false);
        }
        else {
            errMsgDelete.text = "User does not exist";
            errMsgDelete.gameObject.SetActive(true);
        }
        saveUsers();
    }
    public void deleteUserBackBttn() {
        aSource.PlayOneShot(buttonClick);
        overlay.gameObject.SetActive(false);
        deleteUserCanvas.gameObject.SetActive(false);
        errMsgDelete.gameObject.SetActive(false);
    }
    //---changing password
    public void changePassInput(string password) {
        newPass = password;
    }
    public void confirmPassChangeButton() {
        aSource.PlayOneShot(buttonClick);
        if (newPass == PlayerPrefs.GetString(currUser)) {
            errMsgNewPass.gameObject.SetActive(true);
        }
        else {
            errMsgNewPass.gameObject.SetActive(false);
            PlayerPrefs.DeleteKey(currUser);
            PlayerPrefs.SetString(currUser, newPass);
            overlay.gameObject.SetActive(false);
            changePassCanvas.gameObject.SetActive(false);
            mainMenu.gameObject.SetActive(true);
        }
    }
    public void changePassBackBttn() {
        aSource.PlayOneShot(buttonClick);
        overlay.gameObject.SetActive(false);
        changePassCanvas.gameObject.SetActive(false);
        errMsgNewPass.gameObject.SetActive(false);
    }
    //---blocked users
    public void blockedUserInput(string username) {
        userSearch = username;
    }
    public void blockedUserBttn() {
        aSource.PlayOneShot(buttonClick);
        if (blockedUsers.Contains(userSearch)) {
            errMsgBlock.text = "User unblocked!";
            blockedUsers.Remove(userSearch);
            normalUsers.Add(userSearch);
            saveUsers();
        }
        else {
            errMsgBlock.text = "User is not currently blocked";
        }
    }
    public void blockedUserBackBttn() {
        aSource.PlayOneShot(buttonClick);
        overlay.gameObject.SetActive(false);
        blockedCanvas.gameObject.SetActive(false);
        errMsgBlock.text = "";
    }
    //--config button options
    public void audioButton() {
        aSource.PlayOneShot(buttonClick);
        fileCanvas.gameObject.SetActive(false);
        configCanvas.gameObject.SetActive(false);
        overlay.gameObject.SetActive(true);
        audioCanvas.gameObject.SetActive(true);
        currScreen = "AudioMenu";
    }
    public void bgChoiceButton() {
        aSource.PlayOneShot(buttonClick);
        fileCanvas.gameObject.SetActive(false);
        configCanvas.gameObject.SetActive(false);
        overlay.gameObject.SetActive(true);
        bgChoiceCanvas.gameObject.SetActive(true);
        currScreen = "BgChoice";
    }
    //---audio menu
    public void volumeSlider() {
        aSource.volume = volSlider.value;
    }
    public void musicDropdown(int index) {
        switch (index) {
            case 0:
                aSource.Stop();
                aSource.PlayOneShot(bgMusicOne);
                break;
            case 1:
                aSource.Stop();
                aSource.PlayOneShot(bgMusicTwo);
                break;
            case 2:
                aSource.Stop();
                aSource.PlayOneShot(bgMusicThree);
                break;
            default:
                break;
        }
    }
    public void audioBackBttn() {
        aSource.PlayOneShot(buttonClick);
        overlay.gameObject.SetActive(false);
        audioCanvas.gameObject.SetActive(false);
    }
    //---bg choice
    public void bgChoiceDropdown(int index) {
        bgChoiceNum = index;
        switch (index) {
            case 0:
                display.sprite = bgOne;
                break;
            case 1:
                display.sprite = bgTwo;
                break;
            case 2:
                display.sprite = bgThree;
                break;
            default: break;
        }
    }
    public void bgChoiceConfirmBttn() {
        aSource.PlayOneShot(buttonClick);
        switch (bgChoiceNum) {
            case 0:
                background.sprite = bgOne;
                bgGrey.sprite = bgGreyOne;
                overlay.sprite = bgOlOne;
                break;
            case 1:
                background.sprite = bgTwo;
                bgGrey.sprite = bgGreyTwo;
                overlay.sprite = bgOlTwo;
                break;
            case 2:
                background.sprite = bgThree;
                bgGrey.sprite = bgGreyThree;
                overlay.sprite = bgOlThree;
                break;
            default: break;
        }
        saveUsers();
    }
    public void bgChoiceBackBttn() {
        aSource.PlayOneShot(buttonClick);
        overlay.gameObject.SetActive(false);
        bgChoiceCanvas.gameObject.SetActive(false);
    }
    public void exitPackageButton() {
        aSource.PlayOneShot(buttonClick);
        Application.Quit();
    }
    //-Apple Picker Options
    public void AppleButton() {
        aSource.PlayOneShot(buttonClick);
        //if in a submenu
        if (overlay.gameObject.activeSelf) {
            canvasOff();
        }
        //if file open already
        if (APCanvas.gameObject.activeSelf) {
            APCanvas.gameObject.SetActive(false);
        }
        else {
            APCanvas.gameObject.SetActive(true);
        }
        //disable other main button canvas's
        fileCanvas.gameObject.SetActive(false);
        userAccCanvas.gameObject.SetActive(false);
        configCanvas.gameObject.SetActive(false);
        //APCanvas.gameObject.SetActive(false);
        RPSCanvas.gameObject.SetActive(false);
        MemoryCanvas.gameObject.SetActive(false);
        ShmupCanvas.gameObject.SetActive(false);
        ShmupConfigCanvas.gameObject.SetActive(false);
    }
    //--history button
    public void AppleHistoryBttn() {
        aSource.PlayOneShot(buttonClick);
        overlay.gameObject.SetActive(true);
        APhistoryCanvas.gameObject.SetActive(true);
        currScreen = "AppleHistory";
        populateAppleHistory();
        //disable other main button canvas's
        APCanvas.gameObject.SetActive(false);
    }
    public void APhistoryBackBttn() {
        aSource.PlayOneShot(buttonClick);
        overlay.gameObject.SetActive(false);
        APhistoryCanvas.gameObject.SetActive(false);
        APuserEntry.gameObject.SetActive(false);
        disableAppleHistory();
    }
    //--start game
    public void AppleStartBttn() {
        aSource.PlayOneShot(buttonClick);
        SceneManager.LoadScene("APstartScene");
    }
    //--exit
    public void AppleExitBttn() {
        aSource.PlayOneShot(buttonClick);
        canvasOff();
    }
    //-Rock Paper Scissors Button
    public void RPSButton() {
        aSource.PlayOneShot(buttonClick);
        //if in a submenu
        if (overlay.gameObject.activeSelf) {
            canvasOff();
        }
        //if file open already
        if (RPSCanvas.gameObject.activeSelf) {
            RPSCanvas.gameObject.SetActive(false);
        }
        else {
            RPSCanvas.gameObject.SetActive(true);
        }
        //disable other main button canvas's
        fileCanvas.gameObject.SetActive(false);
        userAccCanvas.gameObject.SetActive(false);
        configCanvas.gameObject.SetActive(false);
        APCanvas.gameObject.SetActive(false);
        //RPSCanvas.gameObject.SetActive(false);
        MemoryCanvas.gameObject.SetActive(false);
        ShmupCanvas.gameObject.SetActive(false);
        ShmupConfigCanvas.gameObject.SetActive(false);
    }
    //--history button
    public void RPSHistoryBttn() {
        aSource.PlayOneShot(buttonClick);
        overlay.gameObject.SetActive(true);
        RPSHistoryCanvas.gameObject.SetActive(true);
        currScreen = "RPSHistory";
        populateRPSHistory();
        //disable other main button canvas's
        RPSCanvas.gameObject.SetActive(false);
    }
    public void RPShistoryBackBttn() {
        aSource.PlayOneShot(buttonClick);
        overlay.gameObject.SetActive(false);
        RPSHistoryCanvas.gameObject.SetActive(false);
        RPSuserEntry.gameObject.SetActive(false);
        disableRPSHistory();
    }
    //--start game
    public void RPSStartBttn() {
        aSource.PlayOneShot(buttonClick);
        SceneManager.LoadScene("RPSMainScene");
    }
    //--exit
    public void RPSExitBttn() {
        aSource.PlayOneShot(buttonClick);
        canvasOff();
    }
    //-Memory Button
    public void MemoryButton() {
        aSource.PlayOneShot(buttonClick);
        //if in a submenu
        if (overlay.gameObject.activeSelf) {
            canvasOff();
        }
        //if file open already
        if (MemoryCanvas.gameObject.activeSelf) {
            MemoryCanvas.gameObject.SetActive(false);
        }
        else {
            MemoryCanvas.gameObject.SetActive(true);
        }
        //disable other main button canvas's
        fileCanvas.gameObject.SetActive(false);
        userAccCanvas.gameObject.SetActive(false);
        configCanvas.gameObject.SetActive(false);
        APCanvas.gameObject.SetActive(false);
        RPSCanvas.gameObject.SetActive(false);
        //MemoryCanvas.gameObject.SetActive(false);
        ShmupCanvas.gameObject.SetActive(false);
        ShmupConfigCanvas.gameObject.SetActive(false);
    }
    //--history button
    public void MemoryHistoryBttn() {
        aSource.PlayOneShot(buttonClick);
        overlay.gameObject.SetActive(true);
        MemHistoryCanvas.gameObject.SetActive(true);
        currScreen = "MemHistory";
        populateMemHistory();
        //disable other main button canvas's
        MemoryCanvas.gameObject.SetActive(false);
    }
    public void MemhistoryBackBttn() {
        aSource.PlayOneShot(buttonClick);
        overlay.gameObject.SetActive(false);
        MemHistoryCanvas.gameObject.SetActive(false);
        MemUserEntry.gameObject.SetActive(false);
        disableMemHistory();
    }
    //--start game
    public void MemoryStartBttn() {
        aSource.PlayOneShot(buttonClick);
        SceneManager.LoadScene("CMStartScene");
    }
    //--exit
    public void MemoryExitBttn() {
        aSource.PlayOneShot(buttonClick);
        canvasOff();
    }
    //-Shmup Button
    public void ShmupButton() {
        aSource.PlayOneShot(buttonClick);
        //if in a submenu
        if (overlay.gameObject.activeSelf) {
            canvasOff();
        }
        //if file open already
        if (ShmupCanvas.gameObject.activeSelf) {
            ShmupCanvas.gameObject.SetActive(false);
        }
        else {
            ShmupCanvas.gameObject.SetActive(true);
        }
        //disable other main button canvas's
        fileCanvas.gameObject.SetActive(false);
        userAccCanvas.gameObject.SetActive(false);
        configCanvas.gameObject.SetActive(false);
        APCanvas.gameObject.SetActive(false);
        RPSCanvas.gameObject.SetActive(false);
        MemoryCanvas.gameObject.SetActive(false);
        //ShmupCanvas.gameObject.SetActive(false);
        ShmupConfigCanvas.gameObject.SetActive(false);
    }
    //--game levels button
    public void ShmupGameLevelBttn() {

    }
    //--config button
    public void ShmupConfigBttn() {
        aSource.PlayOneShot(buttonClick);
        ShmupConfigCanvas.gameObject.SetActive(true);
    }
    //--history button
    public void ShmupHistoryBttn() {
        aSource.PlayOneShot(buttonClick);
        overlay.gameObject.SetActive(true);
        ShmupHistoryCanvas.gameObject.SetActive(true);
        currScreen = "ShmupHistory";
        populateShmupHistory();
        //disable other main button canvas's
        ShmupCanvas.gameObject.SetActive(false);
    }
    public void ShmupHistoryBackBttn() {
        aSource.PlayOneShot(buttonClick);
        overlay.gameObject.SetActive(false);
        ShmupHistoryCanvas.gameObject.SetActive(false);
        ShmupUserEntry.gameObject.SetActive(false);
        disableShmupHistory();
    }

    //--start game
    public void ShmupStartBttn() {
        aSource.PlayOneShot(buttonClick);
        SceneManager.LoadScene("SceneMenu");
    }
    //--exit
    public void ShmupExitBttn() {
        aSource.PlayOneShot(buttonClick);
        canvasOff();
    }

    //populaing user history
    public void populateUserHistory() {
        userEntry.gameObject.SetActive(true);
        int j = 0;
        Vector3 ypos = new Vector3();
        ypos.x = 10;
        ypos.y = 85;
        ypos.z = 0;
        //admin history
        if (adminUser) {
            for (int i = timeHistory.Count - 2; i >= 0; i--, j++) {
                if (j == 7) { break; }
                Text temp = Instantiate(userEntry);
                temp.transform.SetParent(historyEmpty.transform, true);
                temp.text = timeHistory[i][1] + "     " + timeHistory[i][3] + "     " + timeHistory[i][0] + "     " + timeHistory[i][4] + "s";
                temp.transform.localPosition = ypos;
                temp.transform.localScale = new Vector3(1, 1, 1);
                userLogs.Add(temp);
                ypos.y -= 45;
            }
        }
        //user history
        else {
            for (int i = timeHistory.Count - 2; i >= 0; i--) {
                if (j == 7) { break; }
                if (currUser == timeHistory[i][1]) {
                    j++;
                    Text temp = Instantiate(userEntry);
                    temp.transform.SetParent(historyCanvas.transform);
                    temp.text = timeHistory[i][0] + "     " + timeHistory[i][4] + "s";
                    temp.transform.localPosition = ypos;
                    temp.transform.localScale = new Vector3(1, 1, 1);
                    userLogs.Add(temp);
                    ypos.y -= 45;
                }
            }
        }
    }
    //turn off history logs
    public void disableUserHistory() {
        for (int i = 0; i < userLogs.Count; i++) {
            userLogs[i].gameObject.SetActive(false);
        }
        userLogs.Clear();
    }
    //populating apple history saves
    public void populateAppleHistory() {
        if (File.Exists(Application.persistentDataPath + "/appleSave.dat")) {
            BinaryFormatter binF = new BinaryFormatter();
            FileStream file = File.Open(Application.persistentDataPath + "/appleSave.dat", FileMode.Open);
            AppleSaves asave = (AppleSaves)binF.Deserialize(file);
            file.Close();
            //loading in apple saves
            appleSaves = asave.appleHistory;
            int j = 0;
            APuserEntry.gameObject.SetActive(true);
            Vector3 ypos = new Vector3();
            ypos.x = 10;
            ypos.y = 85;
            ypos.z = 0;
            for (int i = appleSaves.Count - 1; i >= 0; i--, j++) {
                if (j == 7) { break; }
                Text temp = Instantiate(APuserEntry);
                temp.transform.SetParent(APhistoryEmpty.transform, true);
                temp.text = appleSaves[i];
                temp.transform.localPosition = ypos;
                temp.transform.localScale = new Vector3(1, 1, 1);
                appleLogs.Add(temp);
                ypos.y -= 45;
            }
        }
    }
    //turn off apple history logs
    public void disableAppleHistory() {
        for (int i = 0; i < appleLogs.Count; i++) {
            appleLogs[i].gameObject.SetActive(false);
        }
        appleLogs.Clear();
    }
    //populating rps history saves
    public void populateRPSHistory() {
        if (File.Exists(Application.persistentDataPath + "/rpsSave.dat")) {
            BinaryFormatter binF = new BinaryFormatter();
            FileStream file = File.Open(Application.persistentDataPath + "/rpsSave.dat", FileMode.Open);
            RpsSaves rpssave = (RpsSaves)binF.Deserialize(file);
            file.Close();
            //loading in apple saves
            RPSsaves = rpssave.rpsHistory;
            int j = 0;
            RPSuserEntry.gameObject.SetActive(true);
            Vector3 ypos = new Vector3();
            ypos.x = 10;
            ypos.y = 85;
            ypos.z = 0;
            for (int i = RPSsaves.Count - 1; i >= 0; i--, j++) {
                if (j == 7) { break; }
                Text temp = Instantiate(RPSuserEntry);
                temp.transform.SetParent(RPShistoryEmpty.transform, true);
                temp.text = RPSsaves[i];
                temp.transform.localPosition = ypos;
                temp.transform.localScale = new Vector3(1, 1, 1);
                RPSLogs.Add(temp);
                ypos.y -= 45;
            }
        }
    }
    //turn off rps history logs
    public void disableRPSHistory() {
        for (int i = 0; i < RPSLogs.Count; i++) {
            RPSLogs[i].gameObject.SetActive(false);
        }
        RPSLogs.Clear();
    }
    //populating memory history saves
    public void populateMemHistory() {
        if (File.Exists(Application.persistentDataPath + "/memSave.dat")) {
            BinaryFormatter binF = new BinaryFormatter();
            FileStream file = File.Open(Application.persistentDataPath + "/memSave.dat", FileMode.Open);
            MemorySaves memsave = (MemorySaves)binF.Deserialize(file);
            file.Close();
            //loading in apple saves
            MemSaves = memsave.memHistory;
            int j = 0;
            MemUserEntry.gameObject.SetActive(true);
            Vector3 ypos = new Vector3();
            ypos.x = 10;
            ypos.y = 85;
            ypos.z = 0;
            for (int i = MemSaves.Count - 1; i >= 0; i--, j++) {
                if (j == 7) { break; }
                Text temp = Instantiate(MemUserEntry);
                temp.transform.SetParent(MemHistoryEmpty.transform, true);
                temp.text = MemSaves[i];
                temp.transform.localPosition = ypos;
                temp.transform.localScale = new Vector3(1, 1, 1);
                MemLogs.Add(temp);
                ypos.y -= 45;
            }
        }
    }
    //turn off memory history logs
    public void disableMemHistory() {
        for (int i = 0; i < MemLogs.Count; i++) {
            MemLogs[i].gameObject.SetActive(false);
        }
        MemLogs.Clear();
    }
    //populating memory history saves
    public void populateShmupHistory() {
        if (File.Exists(Application.persistentDataPath + "/shmupSave.dat")) {
            BinaryFormatter binF = new BinaryFormatter();
            FileStream file = File.Open(Application.persistentDataPath + "/shmupSave.dat", FileMode.Open);
            ShmupSaves shmupsave = (ShmupSaves)binF.Deserialize(file);
            file.Close();
            //loading in apple saves
            ShmupSaves = shmupsave.shmupHistory;
            int j = 0;
            ShmupUserEntry.gameObject.SetActive(true);
            Vector3 ypos = new Vector3();
            ypos.x = 10;
            ypos.y = 85;
            ypos.z = 0;
            for (int i = ShmupSaves.Count - 1; i >= 0; i--, j++) {
                if (j == 7) { break; }
                Text temp = Instantiate(ShmupUserEntry);
                temp.transform.SetParent(ShmupHistoryEmpty.transform, true);
                temp.text = ShmupSaves[i];
                temp.transform.localPosition = ypos;
                temp.transform.localScale = new Vector3(1, 1, 1);
                ShmupLogs.Add(temp);
                ypos.y -= 45;
            }
        }
    }
    //turn off shmup history logs
    public void disableShmupHistory() {
        for (int i = 0; i < ShmupLogs.Count; i++) {
            ShmupLogs[i].gameObject.SetActive(false);
        }
        ShmupLogs.Clear();
    }

    //quick off for all canvas layers once in main menu
    public void canvasOff() {
        fileCanvas.gameObject.SetActive(false);
        userAccCanvas.gameObject.SetActive(false);
        createUserCanvas.gameObject.SetActive(false);
        deleteUserCanvas.gameObject.SetActive(false);
        changePassCanvas.gameObject.SetActive(false);
        blockedCanvas.gameObject.SetActive(false);
        configCanvas.gameObject.SetActive(false);
        audioCanvas.gameObject.SetActive(false);
        bgChoiceCanvas.gameObject.SetActive(false);
        historyCanvas.gameObject.SetActive(false);
        APCanvas.gameObject.SetActive(false);
        RPSCanvas.gameObject.SetActive(false);
        MemoryCanvas.gameObject.SetActive(false);
        ShmupCanvas.gameObject.SetActive(false);
        ShmupConfigCanvas.gameObject.SetActive(false);
        APhistoryCanvas.gameObject.SetActive(false);
        RPSHistoryCanvas.gameObject.SetActive(false);
        MemHistoryCanvas.gameObject.SetActive(false);
        ShmupHistoryCanvas.gameObject.SetActive(false);
        overlay.gameObject.SetActive(false);
        errMsg.text = "";
        errMsgBlock.text = "";
        permDenyMM.gameObject.SetActive(false);
        errMsgNewPass.gameObject.SetActive(false);
        errMsgDelete.gameObject.SetActive(false);
        errMsgBlock.gameObject.SetActive(true);
        userEntry.gameObject.SetActive(false);
        disableUserHistory();
        disableAppleHistory();
        disableRPSHistory();
        disableMemHistory();
        disableShmupHistory();
    }
    //main menu "permission denied" coroutine
    IEnumerator PermDenied() {
        permDenyMM.gameObject.SetActive(true);
        yield return new WaitForSeconds(2.0f);
        permDenyMM.gameObject.SetActive(false);
    }
    //saving user lists between launches
    public void saveUsers() {
        BinaryFormatter binF = new BinaryFormatter();
        FileStream file = File.Create(Application.persistentDataPath + "/userLists.dat");
        //setting data in container
        UserLists ulist = new UserLists();
        ulist.newUsers = newUsers;
        ulist.normalUsers = normalUsers;
        ulist.blockedUsers = blockedUsers;
        ulist.bgChoiceNum = bgChoiceNum;
        ulist.timeHistory = timeHistory;
        //writing data to file
        binF.Serialize(file, ulist);
        file.Close();
    }
    //loading saved user list data
    public void loadUsers() {
        if(File.Exists(Application.persistentDataPath + "/userLists.dat")) {
            BinaryFormatter binF = new BinaryFormatter();
            FileStream file = File.Open(Application.persistentDataPath + "/userLists.dat", FileMode.Open);
            UserLists ulist = (UserLists)binF.Deserialize(file);
            file.Close();
            //loading in lists
            normalUsers = ulist.normalUsers;
            newUsers = ulist.newUsers;
            blockedUsers = ulist.blockedUsers;
            bgChoiceNum = ulist.bgChoiceNum;
            timeHistory = ulist.timeHistory;
        }
    }
}

//container class to easily write needed data
[System.Serializable]
class UserLists {
    public List<string> normalUsers, newUsers, blockedUsers;
    public List<List<string>> timeHistory;
    public int bgChoiceNum;
}