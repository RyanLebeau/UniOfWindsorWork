//test one
/*
class First{
    xOne:number;
    constructor(test:number){
        this.xOne = test;
    }
    fOne(textOne:string){
        if(textOne == "hello world"){ console.log(textOne.toUpperCase());}
        else{ console.log("Did not work dumbass");}
    }
    fTwo(limit:number){
        for(var i:number=limit;i>0;i--){
            console.log(i);
            if(i%2==0){console.log("-"+i);}
        }
    }
}

class Second extends First{
    disp():void{
        console.log(this.xOne);
    }
}

var object = new Second(69); 
object.fOne("hello world");
object.fTwo(10);
object.disp();*/

var apiKey = "25138e2d328844e9983723f06ce2664a";
//var XMLHttpRequest = require("xmlhttprequest").XMLHttpRequest;

var xhr = new XMLHttpRequest();
xhr.open("GET", "https://www.bungie.net/platform/Destiny/Manifest/InventoryItem/1274330687/", true);
xhr.setRequestHeader("X-API-Key", apiKey);

xhr.onreadystatechange = function(){
    if(this.readyState === 4 && this.status === 200){
        var json = JSON.parse(this.responseText);
        console.log(json.Response.data.inventoryItem.itemName); //Gjallarhorn
    }
}

xhr.send();
