
//PxVec3
moveDir = new PxVec3(1,0,0);
castDir = new PxVec3(0,-1,0);

//PxQuad
rotLeft = new PxQuat(Math.PI/2, new PxVec3(0,0,1));
rotRight = new PxQuat(-Math.PI / 2, new PxVec3(0, 0, 1));

MOVESPEED = 2;
HALFEXTENT = 0.4;

hit1 = new PxSceneQueryHit();
hit2 = new PxSceneQueryHit();

disp = new PxVec3(0);
pxExt = new PxExtendedVec3();

exit = false;

function onContact() {
    print("Recieved Projectile_Hit event\n");
}

registerEventCallback("Projectile_Hit", onContact);

function onShapeHit(hit) {
    if(hit.getDirection().dot(moveDir) > .95){
        moveDir = rotLeft.rotate(moveDir);
        castDir = rotLeft.rotate(castDir);
    }
}

registerEventCallback("onShapeHit", onShapeHit);

function AdvancePhysics(deltaTime) {

    if (exit)
        return;

    disp.x = 0;
    disp.y = 0;
    disp.z = 0;

    if (!Enemy.physScene.raycastSingle(PhysX.toVec3(Enemy.CCT.getPosition()).subtract(moveDir.multiply(HALFEXTENT)), castDir, 1 + HALFEXTENT, hit1, new PxSceneQueryFilterData(PhysX.PxSceneQueryFilterFlag.eSTATIC)) && !Enemy.physScene.raycastSingle(PhysX.toVec3(Enemy.CCT.getPosition()).add(moveDir.multiply(HALFEXTENT)), castDir, 1 + HALFEXTENT, hit2, new PxSceneQueryFilterData(PhysX.PxSceneQueryFilterFlag.eSTATIC))) {
        moveDir = rotRight.rotate(moveDir);
        castDir = rotRight.rotate(castDir);
        Enemy.CCT.move(moveDir.multiply(0.05), 0, deltaTime, PhysX.PxSceneQueryHitType.eBLOCK);
    }

    disp.assignment_add(moveDir.multiply(MOVESPEED));

    disp = disp.multiply(deltaTime);

    Enemy.CCT.move(disp, 0, deltaTime, PhysX.PxSceneQueryHitType.eBLOCK);

    tempPos = Enemy.CCT.getPosition();

    Enemy.node.setPosition(new Vector3(tempPos.x, tempPos.y, tempPos.z));
}

registerEventCallback("AdvancePhysics", AdvancePhysics);

//print(test);
//print(new PxVec3());
//print(PxSceneQueryHit);
//print(new PxSceneQueryHit());
//hit1 = new PxSceneQueryHit();
//print(hit1);

