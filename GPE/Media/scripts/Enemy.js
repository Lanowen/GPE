
//PxVec3
moveDir = new PxVec3(1,0,0);
castDir = new PxVec3(0,-1,0);

//PxQuad
rotLeft = new PxQuat(Math.PI/2, new PxVec3(0,0,1));
rotRight = new PxQuat(-Math.PI / 2, new PxVec3(0, 0, 1));

MOVESPEED = 2;
HALFEXTENT = 0.4;

hit1 = new PxRaycastHit();
hit2 = new PxRaycastHit();

disp = new PxVec3(0);
pxExt = new PxExtendedVec3();

rotCount = 0;
falling = false;

time = 0;

life = 3;

function onContact() {
    print("Recieved Projectile_Hit event\n");
}

registerEventCallback("Projectile_Hit", onContact);

function onShapeHit(hit) {
    if(hit.getDirection().dot(moveDir) > .95){
        moveDir = rotLeft.rotate(moveDir);
        castDir = rotLeft.rotate(castDir);
    }

    if (falling) {
        falling = false;
        rotCount = 0;
    }
}

registerEventCallback("onShapeHit", onShapeHit);

function AdvancePhysics(deltaTime) {

    if (deltaTime > 0.2)
        return;

    time += deltaTime;
    disp.x = 0;
    disp.y = 0;
    disp.z = 0;

    if (falling) {

        disp.y = -9.81;
        disp = disp.multiply(deltaTime);

        Enemy.CCT.move(disp, 0, deltaTime, PhysX.PxSceneQueryHitType.eBLOCK);

        tempPos = Enemy.CCT.getPosition();

        Enemy.node.setPosition(new Vector3(tempPos.x, tempPos.y, tempPos.z));
        return;
    }

    if (!Enemy.physScene.raycastSingle(PhysX.toVec3(Enemy.CCT.getPosition()).subtract(moveDir.multiply(HALFEXTENT)), castDir, 1 + HALFEXTENT, PhysX.PxSceneQueryFlag.eBLOCKING_HIT, hit1, new PxSceneQueryFilterData(PhysX.PxSceneQueryFilterFlag.eSTATIC)) &&
        !Enemy.physScene.raycastSingle(PhysX.toVec3(Enemy.CCT.getPosition()).add(moveDir.multiply(HALFEXTENT)), castDir, 1 + HALFEXTENT, PhysX.PxSceneQueryFlag.eBLOCKING_HIT, hit1, new PxSceneQueryFilterData(PhysX.PxSceneQueryFilterFlag.eSTATIC))) {
        moveDir = rotRight.rotate(moveDir);
        castDir = rotRight.rotate(castDir);

        Enemy.CCT.move(moveDir.multiply(0.05), 0, deltaTime, PhysX.PxSceneQueryHitType.eBLOCK);
        //print("lol off edge,", time);
        rotCount++;
        if (rotCount > 4) {
            falling = true;
            moveDir.x = 1;
            moveDir.y = 0;
            castDir.x = 0;
            castDir.y = -1;
        }

    }
    else {
        rotCount = 0;
    }

    disp.assignment_add(moveDir.multiply(MOVESPEED));

    disp = disp.multiply(deltaTime);

    // Enemy.CCT.move(disp, 0, deltaTime, PhysX.PxSceneQueryHitType.eBLOCK);

    tempPos = Enemy.CCT.getPosition();

    Enemy.node.setPosition(new Vector3(tempPos.x, tempPos.y, tempPos.z));
}

registerEventCallback("AdvancePhysics", AdvancePhysics);

function OnDamage(power) {
    life -= power;

    if (life <= 0)
        Enemy.release();
}

registerEventCallback("OnDamage", OnDamage);