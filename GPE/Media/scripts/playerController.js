//function onShapeHit(hit) {
//    print(PlayerCharacter().velocity.y);
//    print(hit);
//    actor = hit.getShape().getActor().isRigidDynamic();
//    if(actor)
//    {
//        if(actor.getRigidDynamicFlags() & PxRigidDynamicFlag.eKINEMATIC)
//            return;

//        // We only allow horizontal pushes. Vertical pushes when we stand on dynamic objects creates
//        // useless stress on the solver. It would be possible to enable/disable vertical pushes on
//        // particular objects, if the gameplay requires it.
//        //upVector = hit.controller.getUpDirection();
//        upVector = new PxVec3(0, 1, 0);
//		dp = hit.dir.dot(upVector);
//        //		printf("%f\n", fabsf(dp));
//		if (PxMath.Abs(dp) < 1e-3)
//        //		if(hit.dir.y==0.0f)
//        {
//			globalPose = actor.getGlobalPose();
//			localPos = globalPose.transformInv(toVec3(hit.worldPos));
//			PlayerCharacter.addForceAtLocalPos(actor, hit.dir * hit.length * 1000.0, localPos, PxForceMode.eACCELERATION);
//        }
//    }
	
//    //if (hit.dir.dot(PlayerCharacter.CCT.getUpDirection()) < -0.95) {
//    if (hit.dir.dot(new PxVec3(0,1,0)) < -0.95) {
//        PlayerCharacter.grounded = true;
//        PlayerCharacter.flipping = false;
//        PlayerCharacter.velocity.x = 0;
//        PlayerCharacter.velocity.y = 0;
//    }
//}

//registerEventCallback("onShapeHit", onShapeHit);
////print(testing);
////print(testFunc());
////print(testVect);
////print(PxVec3);
////print("testing2:", PxVec3(4, 5, 6));
//print(testVect.x, testVect.y, testVect.z);
//print(PlayerCharacter());

print(new PxVec3().dot);
print(new PxActor().isRigidDynamic);
print(new PxRigidActor().isRigidDynamic);