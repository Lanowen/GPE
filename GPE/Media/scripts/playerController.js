
function onShapeHit(hit) {
    actor = hit.getShape().getActor().isRigidDynamic();
    if(actor)
    {
        if(actor.getRigidDynamicFlags() & PhysX.PxRigidDynamicFlag.eKINEMATIC)
            return;

        // We only allow horizontal pushes. Vertical pushes when we stand on dynamic objects creates
        // useless stress on the solver. It would be possible to enable/disable vertical pushes on
        // particular objects, if the gameplay requires it.
        //upVector = hit.controller.getUpDirection();
        upVector = new PxVec3(0, 1, 0);
        dp = hit.getDirection().dot(upVector);
        //		printf("%f\n", fabsf(dp));
		if (PhysX.PxMath.Abs(dp) < 1e-3)
        //		if(hit.dir.y==0.0f)
        {
		    globalPose = actor.getGlobalPose();
		    localPos = globalPose.transformInv(PhysX.toVec3(hit.getWorldPose()));
		    Player.addForceAtLocalPos(actor, hit.getDirection().multiply(hit.getLength() * 1000.0), localPos, PhysX.PxForceMode.eACCELERATION);
        }
    }
	
    //if (hit.dir.dot(pChar.CCT.getUpDirection()) < -0.95) {

    if (hit.getDirection().dot(new PxVec3(0, 1, 0)) < -0.95) {
        Player.grounded = true;
        Player.flipping = false;
        Player.velocity.x = 0;
        Player.velocity.y = 0;
    }
}

registerEventCallback("onShapeHit", onShapeHit);
//print(1 & 1, 1 & 2, 1 & 3);
//print(PlayerCharacter());
//print(PhysX.PxRigidDynamicFlag.eKINEMATIC);

//print(new PxVec3(1,0,0).dot(new PxVec3(1,0,0)));

//print(new PxVec3().dot);
//print(new PxActor().isRigidDynamic);
//print(PxRigidActor().getShapes());