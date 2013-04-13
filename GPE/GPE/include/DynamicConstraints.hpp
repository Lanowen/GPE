#pragma once

#include <PxPhysicsAPI.h>
#include <PxConstraintDesc.h>
#include <extensions/PxConstraintExt.h>
#include <Util.hpp>

class DynamicConstraints : public physx::PxConstraintConnector
{
public:

	DynamicConstraints(){
		mData.rotZ = mData.rotY = mData.rotX = mData.posZ = mData.posY = mData.posX = false;
	};

	virtual void			onComShift(physx::PxU32 actor)	{ 
	}

	virtual void*			prepareData()	
	{
		return &mData;
	}

	virtual bool			updatePvdProperties(PVD::PvdDataStream& pvdConnection,
		const physx::PxConstraint* c,
		physx::PxPvdUpdateType::Enum updateType) const	 {return true;}

	virtual void			onConstraintRelease()	{}
	virtual void*			getExternalReference(physx::PxU32& typeID) { typeID = physx::PxConstraintExtIDs::eNEXT_FREE_ID; return this; }

	static physx::PxU32 solverPrep(
		physx::Px1DConstraint* constraints,
		physx::PxVec3& body0WorldOffset,
		physx::PxU32 maxConstraints,
		const void* constantBlock,
		const physx::PxTransform& bodyAToWorld,
		const physx::PxTransform& bodyBToWorld
		)
	{
		freeze *data = (freeze *)constantBlock;

		(constraints + 0)->linear0 = physx::PxVec3(data->posX ? 1 : 0,0,0);
		(constraints + 0)->angular0 = physx::PxVec3(data->rotX ? 1 : 0,0,0);
		(constraints + 0)->minImpulse = -FLT_MAX;
		(constraints + 0)->maxImpulse = FLT_MAX;

		(constraints + 1)->linear0 = physx::PxVec3(0,data->posY ? 1 : 0,0);
		(constraints + 1)->angular0 = physx::PxVec3(0,data->rotY ? 1 : 0,0);
		(constraints + 1)->minImpulse = -FLT_MAX;
		(constraints + 1)->maxImpulse = FLT_MAX;

		(constraints + 2)->linear0 = physx::PxVec3(0,0,data->posZ ? 1 : 0);
		(constraints + 2)->angular0 = physx::PxVec3(0,0,data->rotZ ? 1 : 0);
		(constraints + 2)->minImpulse = -FLT_MAX;
		(constraints + 2)->maxImpulse = FLT_MAX;

		return 3;
	}


	static void constraintProj(const void* constantBlock,
						physx::PxTransform& bodyAToWorld,
						physx::PxTransform& bodyBToWorld,
						bool projectToA)
	{
		freeze *data = (freeze *)constantBlock;

		if(data->posX){
			bodyAToWorld.p.x = data->pos.x;
		}
		if(data->posY){
			bodyAToWorld.p.y = data->pos.y;
		}
		if(data->posZ){
			bodyAToWorld.p.z = data->pos.z;
		}

		/*if(data->rotX && data->rotY && data->rotZ){
			bodyAToWorld.q = physx::PxQuat(data->rot);
		}
		else */

		//TODO: Fix later
		//if(data->rotX || data->rotY || data->rotZ) {
		//	physx::PxVec3 axis;
		//	physx::PxReal dot;

		//	if(data->rotX){
		//		/*axis = physx::PxVec3(1,0,0);

		//		physx::PxReal angle1, angle2;
		//		data->rot.toRadiansAndUnitAxis(angle1, axis);
		//		bodyAToWorld.q.toRadiansAndUnitAxis(angle2, axis);

		//		if(angle1 != angle2){
		//			bodyAToWorld.q *= physx::PxQuat(angle1-angle2, axis);
		//		}*/
		//		
		//		physx::PxVec3 erp = bodyAToWorld.q.getBasisVector0();
		//		Util::dout << erp.x << " " << erp.y << " " << erp.z << std::endl;
		//		/*dot = data->basisX.dot(bodyAToWorld.q.getBasisVector0());
		//		Util::dout << "X:" << physx::PxAcos(dot)  << std::endl;
		//		if(dot < 0.99){
		//			bodyAToWorld.q *= physx::PxQuat(physx::PxAcos(dot), physx::PxVec3(1,0,0));
		//		}*/
		//	}

		//	if(data->rotY){
		//		/*axis = physx::PxVec3(0,1,0);

		//		physx::PxReal angle1, angle2;
		//		data->rot.toRadiansAndUnitAxis(angle1, axis);
		//		bodyAToWorld.q.toRadiansAndUnitAxis(angle2, axis);

		//		if(angle1 != angle2){
		//			bodyAToWorld.q *= physx::PxQuat(angle1-angle2, axis);
		//		}*/
		//		
		//		//dot = data->basisY.dot(bodyAToWorld.q.getBasisVector1());
		//		//Util::dout << "Y:" << physx::PxAcos(dot)  << std::endl;
		//		//if(dot < 0.99){
		//		//	//atan2(norm(cross(a,b)),dot(a,b));
		//		//	//bodyAToWorld.q *= physx::PxQuat(physx::PxAtan2(data->basisY.cross(bodyAToWorld.q.getBasisVector1()),dot), physx::PxVec3(0,1,0));
		//		//}
		//	}

		//	if(data->rotZ){
		//		/*axis = physx::PxVec3(0,0,1);

		//		physx::PxReal angle1, angle2;
		//		data->rot.toRadiansAndUnitAxis(angle1, axis);
		//		bodyAToWorld.q.toRadiansAndUnitAxis(angle2, axis);

		//		if(angle1 != angle2){
		//			bodyAToWorld.q *= physx::PxQuat(angle1-angle2, axis);
		//		}*/

		//		dot = data->basisZ.dot(bodyAToWorld.q.getBasisVector2());
		//		if(dot < 0.99){
		//			bodyAToWorld.q *= physx::PxQuat(physx::PxAcos(dot), physx::PxVec3(0,0,1));
		//		}
		//	}
		//}
	}

	static void vis( physx::PxConstraintVisualizer& visualizer,
		const void* constantBlock,
		const physx::PxTransform& body0Transform,
		const physx::PxTransform& body1Transform,
		PxU32 flags )
	{

	}

	void freezeXPos(bool frz = true){
		mData.posX = frz;

		physx::PxRigidActor *obj0, *obj1;

		this->mConstraint->getActors(obj0,obj1);

		if(frz && obj0){
			mData.pos.x = obj0->getGlobalPose().p.x;
		}
	}

	void freezeYPos(bool frz = true){
		mData.posY = frz;

		physx::PxRigidActor *obj0, *obj1;

		this->mConstraint->getActors(obj0,obj1);

		if(frz && obj0){
			mData.pos.y = obj0->getGlobalPose().p.y;
		}
	}

	void freezeZPos(bool frz = true){
		mData.posZ = frz;

		physx::PxRigidActor *obj0, *obj1;

		this->mConstraint->getActors(obj0,obj1);

		if(frz && obj0){
			mData.pos.z = obj0->getGlobalPose().p.z;
		}
	}

	void freezeXRot(bool frz = true){
		mData.rotX = frz;

		physx::PxRigidActor *obj0, *obj1;

		this->mConstraint->getActors(obj0,obj1);

		if(frz && obj0){
			//mData.rot = physx::PxQuat(obj0->getGlobalPose().q);
			mData.basisX = obj0->getGlobalPose().q.getBasisVector0();
		}
	}

	void freezeYRot(bool frz = true){
		mData.rotY = frz;

		physx::PxRigidActor *obj0, *obj1;

		this->mConstraint->getActors(obj0,obj1);

		if(frz && obj0){
			//mData.rot = physx::PxQuat(obj0->getGlobalPose().q);
			mData.basisY = obj0->getGlobalPose().q.getBasisVector1();
		}
	}

	void freezeZRot(bool frz = true){
		mData.rotZ = frz;

		physx::PxRigidActor *obj0, *obj1;

		this->mConstraint->getActors(obj0,obj1);

		if(frz && obj0){
			//mData.rot = physx::PxQuat(obj0->getGlobalPose().q);
			mData.basisZ = obj0->getGlobalPose().q.getBasisVector2();
		}
	}

public:
	struct freeze{
		bool posX;
		bool posY, posZ, rotX, rotY, rotZ;
		physx::PxVec3 pos;
		//physx::PxQuat rot;
		physx::PxVec3 basisX, basisY, basisZ;
	};

	freeze mData;

	physx::PxConstraint* mConstraint;
};