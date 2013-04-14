
function onShapeHit(hit) {
    actor = hit.getShape().getActor().isRigidDynamic();
    if(actor)
    {
        if(actor.getRigidDynamicFlags() & PhysX.PxRigidDynamicFlag.eKINEMATIC)
            return;

        // We only allow horizontal pushes. Vertical pushes when we stand on dynamic objects creates
        // useless stress on the solver. It would be possible to enable/disable vertical pushes on
        // particular objects, if the gameplay requires it.
        upVector = hit.getController().getUpDirection();
        //upVector = new PxVec3(0, 1, 0);
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
	
    if (hit.getDirection().dot(hit.getController().getUpDirection()) < -0.95) {
    //if (hit.getDirection().dot(new PxVec3(0, 1, 0)) < -0.95) {
        Player.grounded = true;
        Player.flipping = false;
        Player.velocity.x = 0;
        Player.velocity.y = 0;
    }
}

registerEventCallback("onShapeHit", onShapeHit);

function UpdateAnimation(deltaTime) {
    if(!Player.flipping){
        if(Player.gunDirection == UPANGLED){
            Player.animationStateSet.getAnimationState("Run_full_upper").setEnabled(false);
            Player.animationStateSet.getAnimationState("Walk_full_upper").setEnabled(false);
            Player.animationStateSet.getAnimationState("Run_step_upper").setEnabled(false);
            Player.animationStateSet.getAnimationState("Walk_step_upper").setEnabled(false);
            Player.animationStateSet.getAnimationState("Run_full_upper_shoot").setEnabled(false);
            Player.animationStateSet.getAnimationState("Walk_full_upper_shoot").setEnabled(false);
            Player.animationStateSet.getAnimationState("Run_step_upper_shoot").setEnabled(false);
            Player.animationStateSet.getAnimationState("Walk_step_upper_shoot").setEnabled(false);
            Player.animationStateSet.getAnimationState("Jump_up").setEnabled(false);
            Player.animationStateSet.getAnimationState("Jump_peaking").setEnabled(false);

            Player.animationStateSet.getAnimationState("Aim_up_angled").setEnabled(true);
            Player.animationStateSet.getAnimationState("Aim_down_angled").setEnabled(false);
        }
        else if(Player.gunDirection == DOWNANGLED){
            Player.animationStateSet.getAnimationState("Run_full_upper").setEnabled(false);
            Player.animationStateSet.getAnimationState("Walk_full_upper").setEnabled(false);
            Player.animationStateSet.getAnimationState("Run_step_upper").setEnabled(false);
            Player.animationStateSet.getAnimationState("Walk_step_upper").setEnabled(false);
            Player.animationStateSet.getAnimationState("Run_full_upper_shoot").setEnabled(false);
            Player.animationStateSet.getAnimationState("Walk_full_upper_shoot").setEnabled(false);
            Player.animationStateSet.getAnimationState("Run_step_upper_shoot").setEnabled(false);
            Player.animationStateSet.getAnimationState("Walk_step_upper_shoot").setEnabled(false);
            Player.animationStateSet.getAnimationState("Jump_up").setEnabled(false);
            Player.animationStateSet.getAnimationState("Jump_peaking").setEnabled(false);

            Player.animationStateSet.getAnimationState("Aim_up_angled").setEnabled(false);
            Player.animationStateSet.getAnimationState("Aim_down_angled").setEnabled(true);
        }
        else {
            Player.animationStateSet.getAnimationState("Aim_up_angled").setEnabled(false);
            Player.animationStateSet.getAnimationState("Aim_down_angled").setEnabled(false);
        }
    }


    if(!Player.grounded){
        Player.animationStateSet.getAnimationState("Run_full").setEnabled(false);
        Player.animationStateSet.getAnimationState("Walk_full").setEnabled(false);
        Player.animationStateSet.getAnimationState("Run_full_upper").setEnabled(false);
        Player.animationStateSet.getAnimationState("Walk_full_upper").setEnabled(false);

        if(Player.flipping){
            Player.animationStateSet.getAnimationState("Run_full_upper_shoot").setEnabled(false);
            Player.animationStateSet.getAnimationState("Walk_full_upper_shoot").setEnabled(false);
            Player.animationStateSet.getAnimationState("Run_step_upper_shoot").setEnabled(false);
            Player.animationStateSet.getAnimationState("Walk_step_upper_shoot").setEnabled(false);
        }

        if(!Player.animationStateSet.getAnimationState("Flipping").getEnabled()){
            if(Player.velocity.y < -1){
                if(!Player.animationStateSet.getAnimationState("Falling").getEnabled()){
                    Player.animationStateSet.getAnimationState("Falling").setEnabled(true);
                    Player.animationStateSet.getAnimationState("Falling").setTimePosition(0);
                }
                Player.animationStateSet.getAnimationState("Jump_peaking").setEnabled(false);
                Player.animationStateSet.getAnimationState("Jump_up").setEnabled(false);
            }
            else if(Player.velocity.y < 6 && !Player.animationStateSet.getAnimationState("Jump_peaking").getEnabled() && !Player.animationStateSet.getAnimationState("Falling").getEnabled()){
                Player.animationStateSet.getAnimationState("Jump_peaking").setTimePosition(0);
                Player.animationStateSet.getAnimationState("Jump_peaking").setEnabled(true);
				
                Player.animationStateSet.getAnimationState("Jump_up").setEnabled(false);
            }
            //Util::dout << Player.animationStateSet.getAnimationState("Jump_peaking").getEnabled() << " " << Player.animationStateSet.getAnimationState("Jump_peaking").getTimePosition() << " " << Player.animationStateSet.getAnimationState("Jump_peaking").getLength() << std::endl;
        }
    }
    else {
        Player.animationStateSet.getAnimationState("Flipping").setEnabled(false);
        Player.animationStateSet.getAnimationState("Falling").setEnabled(false);
        if(Player.inputVel.isZero()){
            Player.animationStateSet.getAnimationState("Run_full").setEnabled(false);
            Player.animationStateSet.getAnimationState("Walk_full").setEnabled(false);
            Player.animationStateSet.getAnimationState("Run_step").setEnabled(false);
            Player.animationStateSet.getAnimationState("Walk_step").setEnabled(false);

			
            Player.animationStateSet.getAnimationState("Run_full_upper").setEnabled(false);
            Player.animationStateSet.getAnimationState("Walk_full_upper").setEnabled(false);
            Player.animationStateSet.getAnimationState("Run_step_upper").setEnabled(false);
            Player.animationStateSet.getAnimationState("Walk_step_upper").setEnabled(false);

            if(Player.gunDirection == UPANGLED){
                Player.animationStateSet.getAnimationState("Aim_up_angled").setEnabled(true);
                Player.animationStateSet.getAnimationState("Aim_down_angled").setEnabled(false);
            }
            else if(Player.gunDirection == DOWNANGLED){
                Player.animationStateSet.getAnimationState("Aim_up_angled").setEnabled(false);
                Player.animationStateSet.getAnimationState("Aim_down_angled").setEnabled(true);
            }
            else {
                Player.animationStateSet.getAnimationState("Aim_up_angled").setEnabled(false);
                Player.animationStateSet.getAnimationState("Aim_down_angled").setEnabled(false);
            }
        }
        else {
            if(Player.isTurning){
                //turning animation
                Player.animationStateSet.getAnimationState("Run_full").setEnabled(false);
                Player.animationStateSet.getAnimationState("Walk_full").setEnabled(false);
                Player.animationStateSet.getAnimationState("Run_step").setEnabled(false);
                Player.animationStateSet.getAnimationState("Walk_step").setEnabled(false);

                Player.animationStateSet.getAnimationState("Run_full_upper").setEnabled(false);
                Player.animationStateSet.getAnimationState("Walk_full_upper").setEnabled(false);
                Player.animationStateSet.getAnimationState("Run_step_upper").setEnabled(false);
                Player.animationStateSet.getAnimationState("Walk_step_upper").setEnabled(false);
                Player.animationStateSet.getAnimationState("Run_full_upper_shoot").setEnabled(false);
                Player.animationStateSet.getAnimationState("Walk_full_upper_shoot").setEnabled(false);
                Player.animationStateSet.getAnimationState("Run_step_upper_shoot").setEnabled(false);
                Player.animationStateSet.getAnimationState("Walk_step_upper_shoot").setEnabled(false);
            }
            else if(Player.shiftPressed){
                if(!Player.animationStateSet.getAnimationState("Run_full").getEnabled() && !Player.animationStateSet.getAnimationState("Run_step").getEnabled() ){
                    Player.animationStateSet.getAnimationState("Run_step").setEnabled(true);
                    Player.animationStateSet.getAnimationState("Run_step").setTimePosition(0);

                    if(Player.timeSinceLastShot > SHOOT_ANIMATION_LENGTH && Player.gunDirection == FORWARD){
                        Player.animationStateSet.getAnimationState("Run_step_upper").setEnabled(true);
                        Player.animationStateSet.getAnimationState("Run_step_upper").setTimePosition(Player.animationStateSet.getAnimationState("Run_step").getTimePosition());
                    }
                }
                if(Player.animationStateSet.getAnimationState("Run_step").getEnabled() && Player.animationStateSet.getAnimationState("Run_step").hasEnded()){
                    Player.animationStateSet.getAnimationState("Run_full").setEnabled(true);
                    Player.animationStateSet.getAnimationState("Run_full").setTimePosition(0);

                    Player.animationStateSet.getAnimationState("Run_step").setEnabled(false);
                    Player.animationStateSet.getAnimationState("Run_step_upper").setEnabled(false);

                    if(Player.timeSinceLastShot > SHOOT_ANIMATION_LENGTH && Player.gunDirection == FORWARD){
                        Player.animationStateSet.getAnimationState("Run_full_upper").setEnabled(true);
                        Player.animationStateSet.getAnimationState("Run_full_upper").setTimePosition(Player.animationStateSet.getAnimationState("Run_full").getTimePosition());
                    }
                }
                Player.animationStateSet.getAnimationState("Walk_full").setEnabled(false);
                Player.animationStateSet.getAnimationState("Walk_step").setEnabled(false);

                Player.animationStateSet.getAnimationState("Walk_step_upper").setEnabled(false);
                Player.animationStateSet.getAnimationState("Walk_full_upper").setEnabled(false);
            }
            else{
                if(!Player.animationStateSet.getAnimationState("Walk_full").getEnabled() && !Player.animationStateSet.getAnimationState("Walk_step").getEnabled() ){
                    Player.animationStateSet.getAnimationState("Walk_step").setEnabled(true);
                    Player.animationStateSet.getAnimationState("Walk_step").setTimePosition(0);

                    if(Player.timeSinceLastShot > SHOOT_ANIMATION_LENGTH && Player.gunDirection == FORWARD){
                        Player.animationStateSet.getAnimationState("Walk_step_upper").setEnabled(true);
                        Player.animationStateSet.getAnimationState("Walk_step_upper").setTimePosition(Player.animationStateSet.getAnimationState("Walk_step").getTimePosition());
                    }
                }
                if(Player.animationStateSet.getAnimationState("Walk_step").getEnabled() && Player.animationStateSet.getAnimationState("Walk_step").hasEnded() ){
                    Player.animationStateSet.getAnimationState("Walk_step").setEnabled(false);
                    Player.animationStateSet.getAnimationState("Walk_full").setEnabled(true);
                    Player.animationStateSet.getAnimationState("Walk_full").setTimePosition(0);

                    Player.animationStateSet.getAnimationState("Walk_step_upper").setEnabled(false);

                    if(Player.timeSinceLastShot > SHOOT_ANIMATION_LENGTH && Player.gunDirection == FORWARD){
                        Player.animationStateSet.getAnimationState("Walk_full_upper").setEnabled(true);
                        Player.animationStateSet.getAnimationState("Walk_full_upper").setTimePosition(Player.animationStateSet.getAnimationState("Walk_full").getTimePosition());
                    }
                }
                Player.animationStateSet.getAnimationState("Run_full").setEnabled(false);
                Player.animationStateSet.getAnimationState("Run_step").setEnabled(false);

                Player.animationStateSet.getAnimationState("Run_full_upper").setEnabled(false);
                Player.animationStateSet.getAnimationState("Run_step_upper").setEnabled(false);				
            }
        }
    }
    if(Player.isTurning){
        yaw = Player.node._getDerivedOrientation().getYaw();
        temp = Math.abs(Player.yawTarget.subtract(yaw).valueRadians());
        if(temp < TURN_SPEED * deltaTime){
            yaw = new Radian(temp);
            Player.isTurning = false;
        }
        else {
            yaw = new Radian(TURN_SPEED * deltaTime);
        }
        Player.node.yaw(yaw.multiply((Player.direction == LEFT ? -1 : 1)));
    }

    if(Player.flipping){
        Player.childNode.pitch(new Radian(FLIP_SPEED * deltaTime));
    }
    else {
        deltaAngle = Player.childNode.getOrientation().getPitch();
        Player.childNode.pitch(deltaAngle.negate());		
    }

    
}

registerEventCallback("UpdateAnimation", UpdateAnimation);