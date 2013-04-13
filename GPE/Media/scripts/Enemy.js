
function onContact() {
    print("Recieved Projectile_Hit event\n");
}

registerEventCallback("Projectile_Hit", onContact);
removeEventCallback("Projectile_Hit", onContact);
