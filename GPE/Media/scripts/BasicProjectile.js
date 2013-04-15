power = 1;

arr = new Array();
arr[0] = power;

function onContact(otherGO) {
    
    otherGO.dispatchEvent("OnDamage", arr);
}

registerEventCallback("Projectile_Hit", onContact);
