print("testing, This is a projectile script\n");

var n = new PxVec3(2,1,0);

function onContact() {
    //print("Recieved Projectile_Hit event\n");
    print(n.x, n.y, n.z);
}

registerEventCallback("Projectile_Hit", onContact);
//removeEventCallback("Projectile_Hit", onContact);


function derp() {
    print("lol");
    removeEventCallback("Event_onFrameQueued", derp);
}

function derp2() {
    //print("lol");
}

//registerEventCallback("Event_onFrameQueued", derp);
//registerEventCallback("Event_onFrameQueued", derp2);
//removeEventCallback("Event_onFrameQueued", onContact);

//print(testing);
print(mGrounded);