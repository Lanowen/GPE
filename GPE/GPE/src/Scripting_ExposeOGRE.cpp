#include <Scripting_ExposeOGRE.hpp>
#include <Scripting_Helpers.hpp>

#include <Ogre.h>

//Persistent<FunctionTemplate> BaseV8TemplateObject<V8Vector3>::templ;
//Persistent<FunctionTemplate> BaseV8TemplateObject<V8Quaternion>::templ;
//Persistent<FunctionTemplate> BaseV8TemplateObject<V8Radian>::templ;
//Persistent<FunctionTemplate> BaseV8TemplateObject<V8Degree>::templ;
//Persistent<FunctionTemplate> BaseV8TemplateObject<V8Node>::templ;
//Persistent<FunctionTemplate> BaseV8TemplateObject<V8AnimationStateSet>::templ;
//Persistent<FunctionTemplate> BaseV8TemplateObject<V8AnimationState>::templ;
//Persistent<FunctionTemplate> BaseV8TemplateObject<V8Entity>::templ;
//Persistent<FunctionTemplate> BaseV8TemplateObject<V8Matrix3>::templ;
//Persistent<FunctionTemplate> BaseV8TemplateObject<V8SceneNode>::templ;

using namespace Ogre;

Local<FunctionTemplate> V8OGRE::NewFunctionTemplate(InvocationCallback callback, Handle<Value> data, Handle<Signature> signature)
	{
		Local<FunctionTemplate> GPEFuncTemplateBase = FunctionTemplate::New();
		Local<FunctionTemplate> GPEFuncTemplate = FunctionTemplate::New();
		Local<FunctionTemplate> temp;
		Local<FunctionTemplate> temp2;
		Local<ObjectTemplate> objTemp;

		GPEFuncTemplate->SetClassName(v8::String::New("GPE"));
		GPEFuncTemplateBase->PrototypeTemplate()->Set(v8::String::New("GPE"), GPEFuncTemplate->InstanceTemplate());


		//Types
			//Vector3
				V8Vector3::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8Vector3::Vector3Constructor));
				V8Vector3::getTemplate()->SetClassName(v8::String::New("Vector3"));
				GPEFuncTemplateBase->PrototypeTemplate()->Set(v8::String::New("Vector3"), V8Vector3::getTemplate());

				objTemp = V8Vector3::getTemplate()->InstanceTemplate();
				objTemp->SetInternalFieldCount(1);

				objTemp->SetAccessor(v8::String::New("x"), V8Vector3::getX, V8Vector3::setX);
				objTemp->SetAccessor(v8::String::New("y"), V8Vector3::getY, V8Vector3::setY);
				objTemp->SetAccessor(v8::String::New("z"), V8Vector3::getZ, V8Vector3::setZ);
				objTemp->SetIndexedPropertyHandler(V8Vector3::elementGet, V8Vector3::elementSet);

				objTemp->Set(v8::String::New("compare"), FunctionTemplate::New(InvocationCallback( V8Vector3::compare )));
				objTemp->Set(v8::String::New("acompare"), FunctionTemplate::New(InvocationCallback( V8Vector3::acompare )));
				objTemp->Set(v8::String::New("negate"), FunctionTemplate::New(InvocationCallback( V8Vector3::negate )));
				objTemp->Set(v8::String::New("add"), FunctionTemplate::New(InvocationCallback( V8Vector3::add )));
				objTemp->Set(v8::String::New("subtract"), FunctionTemplate::New(InvocationCallback( V8Vector3::subtract )));
				objTemp->Set(v8::String::New("multiply"), FunctionTemplate::New(InvocationCallback( V8Vector3::multiply )));
				objTemp->Set(v8::String::New("divide"), FunctionTemplate::New(InvocationCallback( V8Vector3::divide )));
				
				objTemp->Set(v8::String::New("assignment_add"), FunctionTemplate::New(InvocationCallback( V8Vector3::assignmentAdd)));
				objTemp->Set(v8::String::New("assignment_subtract"), FunctionTemplate::New(InvocationCallback( V8Vector3::assignmentSubtract )));
				objTemp->Set(v8::String::New("assignment_multiply"), FunctionTemplate::New(InvocationCallback( V8Vector3::assignmentMultiply )));
				objTemp->Set(v8::String::New("assignment_divide"), FunctionTemplate::New(InvocationCallback( V8Vector3::assignmentDivide )));

				objTemp->Set(v8::String::New("length"), FunctionTemplate::New(InvocationCallback( V8Vector3::length)));
				objTemp->Set(v8::String::New("squaredLength"), FunctionTemplate::New(InvocationCallback( V8Vector3::squaredLength )));
				objTemp->Set(v8::String::New("distance"), FunctionTemplate::New(InvocationCallback( V8Vector3::distance )));
				objTemp->Set(v8::String::New("squaredDistance"), FunctionTemplate::New(InvocationCallback( V8Vector3::squaredDistance )));

				objTemp->Set(v8::String::New("dotProduct"), FunctionTemplate::New(InvocationCallback( V8Vector3::dotProduct )));
				objTemp->Set(v8::String::New("absDotProduct"), FunctionTemplate::New(InvocationCallback( V8Vector3::absDotProduct )));
				objTemp->Set(v8::String::New("crossProduct"), FunctionTemplate::New(InvocationCallback( V8Vector3::crossProduct )));
				objTemp->Set(v8::String::New("normalize"), FunctionTemplate::New(InvocationCallback( V8Vector3::normalize )));
				objTemp->Set(v8::String::New("getNormalized"), FunctionTemplate::New(InvocationCallback( V8Vector3::getNormalized )));

				objTemp->Set(v8::String::New("lessThan"), FunctionTemplate::New(InvocationCallback( V8Vector3::lessThan )));
				objTemp->Set(v8::String::New("greaterThan"), FunctionTemplate::New(InvocationCallback( V8Vector3::greaterThan )));

				objTemp->Set(v8::String::New("makeFloor"), FunctionTemplate::New(InvocationCallback( V8Vector3::makeFloor )));
				objTemp->Set(v8::String::New("makeCeil"), FunctionTemplate::New(InvocationCallback( V8Vector3::makeCeil )));

				objTemp->Set(v8::String::New("perpendicular"), FunctionTemplate::New(InvocationCallback( V8Vector3::perpendicular )));
				objTemp->Set(v8::String::New("randomDeviant"), FunctionTemplate::New(InvocationCallback( V8Vector3::randomDeviant )));
				objTemp->Set(v8::String::New("angleBetween"), FunctionTemplate::New(InvocationCallback( V8Vector3::angleBetween )));
				objTemp->Set(v8::String::New("getRotationTo"), FunctionTemplate::New(InvocationCallback( V8Vector3::getRotationTo )));
				objTemp->Set(v8::String::New("isZeroLength"), FunctionTemplate::New(InvocationCallback( V8Vector3::isZeroLength )));
				objTemp->Set(v8::String::New("reflect"), FunctionTemplate::New(InvocationCallback( V8Vector3::reflect )));
				objTemp->Set(v8::String::New("positionEquals"), FunctionTemplate::New(InvocationCallback( V8Vector3::positionEquals )));
				objTemp->Set(v8::String::New("positionCloses"), FunctionTemplate::New(InvocationCallback( V8Vector3::positionCloses )));
				objTemp->Set(v8::String::New("directionEquals"), FunctionTemplate::New(InvocationCallback( V8Vector3::directionEquals )));
				objTemp->Set(v8::String::New("isNaN"), FunctionTemplate::New(InvocationCallback( V8Vector3::isNaN )));
				objTemp->Set(v8::String::New("primaryAxis"), FunctionTemplate::New(InvocationCallback( V8Vector3::primaryAxis )));

				//V8Vector3::getTemplate()->PrototypeTemplate()->Set(v8::String::New("ZERO"), FunctionTemplate::New(InvocationCallback( V8Quaternion::createIdentity )));

		//Quaternion
				V8Quaternion::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8Quaternion::QuaternionConstructor));
				V8Quaternion::getTemplate()->SetClassName(v8::String::New("Quaternion"));
				GPEFuncTemplateBase->PrototypeTemplate()->Set(v8::String::New("Quaternion"), V8Quaternion::getTemplate());

				objTemp = V8Quaternion::getTemplate()->InstanceTemplate();
				objTemp->SetInternalFieldCount(1);

				objTemp->SetAccessor(v8::String::New("x"), V8Quaternion::getX, V8Quaternion::setX);
				objTemp->SetAccessor(v8::String::New("y"), V8Quaternion::getY, V8Quaternion::setY);
				objTemp->SetAccessor(v8::String::New("z"), V8Quaternion::getZ, V8Quaternion::setZ);
				objTemp->SetAccessor(v8::String::New("w"), V8Quaternion::getW, V8Quaternion::setW);
				objTemp->SetIndexedPropertyHandler(V8Quaternion::elementGet, V8Quaternion::elementSet);

				objTemp->Set(v8::String::New("FromRotationMatrix"), FunctionTemplate::New(InvocationCallback( V8Quaternion::FromRotationMatrix )));
				objTemp->Set(v8::String::New("ToRotationMatrix"), FunctionTemplate::New(InvocationCallback( V8Quaternion::ToRotationMatrix )));
				objTemp->Set(v8::String::New("FromAngleAxis"), FunctionTemplate::New(InvocationCallback( V8Quaternion::FromAngleAxis )));
				objTemp->Set(v8::String::New("ToAngleAxis"), FunctionTemplate::New(InvocationCallback( V8Quaternion::ToAngleAxis )));
				objTemp->Set(v8::String::New("FromAxes"), FunctionTemplate::New(InvocationCallback( V8Quaternion::FromAxes )));
				objTemp->Set(v8::String::New("ToAxes"), FunctionTemplate::New(InvocationCallback( V8Quaternion::ToAxes )));
				objTemp->Set(v8::String::New("xAxis"), FunctionTemplate::New(InvocationCallback( V8Quaternion::xAxis )));
				objTemp->Set(v8::String::New("yAxis"), FunctionTemplate::New(InvocationCallback( V8Quaternion::yAxis )));
				objTemp->Set(v8::String::New("zAxis"), FunctionTemplate::New(InvocationCallback( V8Quaternion::zAxis )));

				objTemp->Set(v8::String::New("add"), FunctionTemplate::New(InvocationCallback( V8Quaternion::add )));
				objTemp->Set(v8::String::New("subtract"), FunctionTemplate::New(InvocationCallback( V8Quaternion::subtract )));
				objTemp->Set(v8::String::New("multiply"), FunctionTemplate::New(InvocationCallback( V8Quaternion::multiply )));
				objTemp->Set(v8::String::New("negate"), FunctionTemplate::New(InvocationCallback( V8Quaternion::negate )));
				objTemp->Set(v8::String::New("compare"), FunctionTemplate::New(InvocationCallback( V8Quaternion::compare )));
				objTemp->Set(v8::String::New("acompare"), FunctionTemplate::New(InvocationCallback( V8Quaternion::acompare )));

				objTemp->Set(v8::String::New("Dot"), FunctionTemplate::New(InvocationCallback( V8Quaternion::Dot )));
				objTemp->Set(v8::String::New("Norm"), FunctionTemplate::New(InvocationCallback( V8Quaternion::Norm )));
				objTemp->Set(v8::String::New("normalize"), FunctionTemplate::New(InvocationCallback( V8Quaternion::normalize )));
				objTemp->Set(v8::String::New("Inverse"), FunctionTemplate::New(InvocationCallback( V8Quaternion::Inverse )));
				objTemp->Set(v8::String::New("UnitInverse"), FunctionTemplate::New(InvocationCallback( V8Quaternion::UnitInverse )));
				objTemp->Set(v8::String::New("Exp"), FunctionTemplate::New(InvocationCallback( V8Quaternion::Exp )));
				objTemp->Set(v8::String::New("Log"), FunctionTemplate::New(InvocationCallback( V8Quaternion::Log )));
				objTemp->Set(v8::String::New("rotate"), FunctionTemplate::New(InvocationCallback( V8Quaternion::rotate )));

				objTemp->Set(v8::String::New("getRoll"), FunctionTemplate::New(InvocationCallback( V8Quaternion::getRoll )));
				objTemp->Set(v8::String::New("getPitch"), FunctionTemplate::New(InvocationCallback( V8Quaternion::getPitch )));
				objTemp->Set(v8::String::New("getYaw"), FunctionTemplate::New(InvocationCallback( V8Quaternion::getYaw )));
				objTemp->Set(v8::String::New("equals"), FunctionTemplate::New(InvocationCallback( V8Quaternion::equals )));
				objTemp->Set(v8::String::New("Slerp"), FunctionTemplate::New(InvocationCallback( V8Quaternion::Slerp )));
				objTemp->Set(v8::String::New("SlerpExtraSpins"), FunctionTemplate::New(InvocationCallback( V8Quaternion::SlerpExtraSpins )));
				objTemp->Set(v8::String::New("Intermediate"), FunctionTemplate::New(InvocationCallback( V8Quaternion::Intermediate )));
				objTemp->Set(v8::String::New("Squad"), FunctionTemplate::New(InvocationCallback( V8Quaternion::Squad )));
				objTemp->Set(v8::String::New("nlerp"), FunctionTemplate::New(InvocationCallback( V8Quaternion::nlerp )));
				objTemp->Set(v8::String::New("isNaN"), FunctionTemplate::New(InvocationCallback( V8Quaternion::isNaN )));

				V8Quaternion::getTemplate()->Set(v8::String::New("createIdentity"), FunctionTemplate::New(InvocationCallback( V8Quaternion::createIdentity )));

			//Radian
				V8Radian::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8Radian::RadianConstructor));
				V8Radian::getTemplate()->SetClassName(v8::String::New("Radian"));
				GPEFuncTemplateBase->PrototypeTemplate()->Set(v8::String::New("Radian"), V8Radian::getTemplate());

				objTemp = V8Radian::getTemplate()->InstanceTemplate();
				objTemp->SetInternalFieldCount(1);

				objTemp->Set(v8::String::New("valueDegrees"), FunctionTemplate::New(InvocationCallback( V8Radian::valueDegrees )));
				objTemp->Set(v8::String::New("valueRadians"), FunctionTemplate::New(InvocationCallback( V8Radian::valueRadians )));
				objTemp->Set(v8::String::New("valueAngleUnits"), FunctionTemplate::New(InvocationCallback( V8Radian::valueAngleUnits )));

				objTemp->Set(v8::String::New("negate"), FunctionTemplate::New(InvocationCallback( V8Radian::negate )));
				objTemp->Set(v8::String::New("add"), FunctionTemplate::New(InvocationCallback( V8Radian::add )));
				objTemp->Set(v8::String::New("subtract"), FunctionTemplate::New(InvocationCallback( V8Radian::subtract )));
				objTemp->Set(v8::String::New("multiply"), FunctionTemplate::New(InvocationCallback( V8Radian::multiply )));
				objTemp->Set(v8::String::New("divide"), FunctionTemplate::New(InvocationCallback( V8Radian::divide )));

				objTemp->Set(v8::String::New("assignmentAdd"), FunctionTemplate::New(InvocationCallback( V8Radian::assignmentAdd )));
				objTemp->Set(v8::String::New("assignmentSubtract"), FunctionTemplate::New(InvocationCallback( V8Radian::assignmentSubtract )));
				objTemp->Set(v8::String::New("assignmentMultiply"), FunctionTemplate::New(InvocationCallback( V8Radian::assignmentMultiply )));
				objTemp->Set(v8::String::New("assignmentDivide"), FunctionTemplate::New(InvocationCallback( V8Radian::assignmentDivide )));

				objTemp->Set(v8::String::New("compare"), FunctionTemplate::New(InvocationCallback( V8Radian::compare )));
				objTemp->Set(v8::String::New("acompare"), FunctionTemplate::New(InvocationCallback( V8Radian::acompare )));
				objTemp->Set(v8::String::New("lessThan"), FunctionTemplate::New(InvocationCallback( V8Radian::lessThan )));
				objTemp->Set(v8::String::New("LessThanEq"), FunctionTemplate::New(InvocationCallback( V8Radian::lessThanEq )));
				objTemp->Set(v8::String::New("greaterThan"), FunctionTemplate::New(InvocationCallback( V8Radian::greaterThan )));
				objTemp->Set(v8::String::New("greaterThanEq"), FunctionTemplate::New(InvocationCallback( V8Radian::greaterThanEq )));

			//Degree
				V8Degree::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8Degree::DegreeConstructor));
				V8Degree::getTemplate()->SetClassName(v8::String::New("Degree"));
				GPEFuncTemplateBase->PrototypeTemplate()->Set(v8::String::New("Degree"), V8Degree::getTemplate());

				objTemp = V8Degree::getTemplate()->InstanceTemplate();
				objTemp->SetInternalFieldCount(1);

				objTemp->Set(v8::String::New("valueDegrees"), FunctionTemplate::New(InvocationCallback( V8Degree::valueDegrees )));
				objTemp->Set(v8::String::New("valueRadians"), FunctionTemplate::New(InvocationCallback( V8Degree::valueRadians )));
				objTemp->Set(v8::String::New("valueAngleUnits"), FunctionTemplate::New(InvocationCallback( V8Degree::valueAngleUnits )));

				objTemp->Set(v8::String::New("negate"), FunctionTemplate::New(InvocationCallback( V8Degree::negate )));
				objTemp->Set(v8::String::New("add"), FunctionTemplate::New(InvocationCallback( V8Degree::add )));
				objTemp->Set(v8::String::New("subtract"), FunctionTemplate::New(InvocationCallback( V8Degree::subtract )));
				objTemp->Set(v8::String::New("multiply"), FunctionTemplate::New(InvocationCallback( V8Degree::multiply )));
				objTemp->Set(v8::String::New("divide"), FunctionTemplate::New(InvocationCallback( V8Degree::divide )));

				objTemp->Set(v8::String::New("assignmentAdd"), FunctionTemplate::New(InvocationCallback( V8Degree::assignmentAdd )));
				objTemp->Set(v8::String::New("assignmentSubtract"), FunctionTemplate::New(InvocationCallback( V8Degree::assignmentSubtract )));
				objTemp->Set(v8::String::New("assignmentMultiply"), FunctionTemplate::New(InvocationCallback( V8Degree::assignmentMultiply )));
				objTemp->Set(v8::String::New("assignmentDivide"), FunctionTemplate::New(InvocationCallback( V8Degree::assignmentDivide )));

				objTemp->Set(v8::String::New("compare"), FunctionTemplate::New(InvocationCallback( V8Degree::compare )));
				objTemp->Set(v8::String::New("acompare"), FunctionTemplate::New(InvocationCallback( V8Degree::acompare )));
				objTemp->Set(v8::String::New("lessThan"), FunctionTemplate::New(InvocationCallback( V8Degree::lessThan )));
				objTemp->Set(v8::String::New("LessThanEq"), FunctionTemplate::New(InvocationCallback( V8Degree::lessThanEq )));
				objTemp->Set(v8::String::New("greaterThan"), FunctionTemplate::New(InvocationCallback( V8Degree::greaterThan )));
				objTemp->Set(v8::String::New("greaterThanEq"), FunctionTemplate::New(InvocationCallback( V8Degree::greaterThanEq )));

			//Node
				V8Node::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8Node::getTemplate()->SetClassName(v8::String::New("Node"));
				GPEFuncTemplateBase->PrototypeTemplate()->Set(v8::String::New("Node"), V8Node::getTemplate());

				temp = FunctionTemplate::New();
				temp->SetClassName(v8::String::New("TransformSpace"));
				V8Node::getTemplate()->PrototypeTemplate()->Set("TransformSpace", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(v8::String::New("TS_LOCAL"), Uint32::New(Node::TransformSpace::TS_LOCAL));
				temp->PrototypeTemplate()->Set(v8::String::New("TS_PARENT"), Uint32::New(Node::TransformSpace::TS_PARENT));
				temp->PrototypeTemplate()->Set(v8::String::New("TS_WORLD"), Uint32::New(Node::TransformSpace::TS_WORLD));

				objTemp = V8Node::getTemplate()->InstanceTemplate();
				objTemp->SetInternalFieldCount(1);

				objTemp->Set(v8::String::New("getName"), FunctionTemplate::New(InvocationCallback( V8Node::getName )));
				objTemp->Set(v8::String::New("getParent"), FunctionTemplate::New(InvocationCallback( V8Node::getParent )));
				objTemp->Set(v8::String::New("getOrientation"), FunctionTemplate::New(InvocationCallback( V8Node::getOrientation )));
				objTemp->Set(v8::String::New("setOrientation"), FunctionTemplate::New(InvocationCallback( V8Node::setOrientation )));
				objTemp->Set(v8::String::New("resetOrientation"), FunctionTemplate::New(InvocationCallback( V8Node::resetOrientation )));
				objTemp->Set(v8::String::New("setPosition"), FunctionTemplate::New(InvocationCallback( V8Node::setPosition )));
				objTemp->Set(v8::String::New("getPosition"), FunctionTemplate::New(InvocationCallback( V8Node::getPosition )));
				objTemp->Set(v8::String::New("setScale"), FunctionTemplate::New(InvocationCallback( V8Node::setScale )));
				objTemp->Set(v8::String::New("getScale"), FunctionTemplate::New(InvocationCallback( V8Node::getScale )));
				objTemp->Set(v8::String::New("setInheritOrientation"), FunctionTemplate::New(InvocationCallback( V8Node::setInheritOrientation )));
				objTemp->Set(v8::String::New("getInheritOrientation"), FunctionTemplate::New(InvocationCallback( V8Node::getInheritOrientation )));
				objTemp->Set(v8::String::New("setInheritScale"), FunctionTemplate::New(InvocationCallback( V8Node::setInheritScale )));
				objTemp->Set(v8::String::New("scale"), FunctionTemplate::New(InvocationCallback( V8Node::scale )));
				objTemp->Set(v8::String::New("translate"), FunctionTemplate::New(InvocationCallback( V8Node::translate )));
				objTemp->Set(v8::String::New("roll"), FunctionTemplate::New(InvocationCallback( V8Node::roll )));
				objTemp->Set(v8::String::New("pitch"), FunctionTemplate::New(InvocationCallback( V8Node::pitch )));
				objTemp->Set(v8::String::New("yaw"), FunctionTemplate::New(InvocationCallback( V8Node::yaw )));
				objTemp->Set(v8::String::New("rotate"), FunctionTemplate::New(InvocationCallback( V8Node::rotate )));

				objTemp->Set(v8::String::New("createChild"), FunctionTemplate::New(InvocationCallback( V8Node::createChild )));
				objTemp->Set(v8::String::New("addChild"), FunctionTemplate::New(InvocationCallback( V8Node::addChild )));
				objTemp->Set(v8::String::New("numChildren"), FunctionTemplate::New(InvocationCallback( V8Node::numChildren )));
				objTemp->Set(v8::String::New("getChild"), FunctionTemplate::New(InvocationCallback( V8Node::getChild )));
				objTemp->Set(v8::String::New("removeChild"), FunctionTemplate::New(InvocationCallback( V8Node::removeChild )));
				objTemp->Set(v8::String::New("removeAllChildren"), FunctionTemplate::New(InvocationCallback( V8Node::removeAllChildren )));
				objTemp->Set(v8::String::New("_setDerivedPosition"), FunctionTemplate::New(InvocationCallback( V8Node::_setDerivedPosition )));
				objTemp->Set(v8::String::New("_setDerivedOrientation"), FunctionTemplate::New(InvocationCallback( V8Node::_setDerivedOrientation )));
				objTemp->Set(v8::String::New("_getDerivedOrientation"), FunctionTemplate::New(InvocationCallback( V8Node::_getDerivedOrientation )));
				objTemp->Set(v8::String::New("_getDerivedPosition"), FunctionTemplate::New(InvocationCallback( V8Node::_getDerivedPosition )));
				objTemp->Set(v8::String::New("_getDerivedScale"), FunctionTemplate::New(InvocationCallback( V8Node::_getDerivedScale )));
				objTemp->Set(v8::String::New("_update"), FunctionTemplate::New(InvocationCallback( V8Node::_update )));
				objTemp->Set(v8::String::New("setInitialState"), FunctionTemplate::New(InvocationCallback( V8Node::setInitialState )));
				objTemp->Set(v8::String::New("resetToInitialState"), FunctionTemplate::New(InvocationCallback( V8Node::resetToInitialState )));
				objTemp->Set(v8::String::New("getInitialPosition"), FunctionTemplate::New(InvocationCallback( V8Node::getInitialPosition )));

				objTemp->Set(v8::String::New("convertWorldToLocalPosition"), FunctionTemplate::New(InvocationCallback( V8Node::convertWorldToLocalPosition )));
				objTemp->Set(v8::String::New("convertLocalToWorldPosition"), FunctionTemplate::New(InvocationCallback( V8Node::convertLocalToWorldPosition )));
				objTemp->Set(v8::String::New("convertWorldToLocalOrientation"), FunctionTemplate::New(InvocationCallback( V8Node::convertWorldToLocalOrientation )));
				objTemp->Set(v8::String::New("convertLocalToWorldOrientation"), FunctionTemplate::New(InvocationCallback( V8Node::convertLocalToWorldOrientation )));
				objTemp->Set(v8::String::New("getInitialOrientation"), FunctionTemplate::New(InvocationCallback( V8Node::getInitialOrientation )));
				objTemp->Set(v8::String::New("getInitialScale"), FunctionTemplate::New(InvocationCallback( V8Node::getInitialScale )));
				//objTemp->Set(v8::String::New("getSquaredViewDepth"), FunctionTemplate::New(InvocationCallback( V8Node::getSquaredViewDepth )));
				objTemp->Set(v8::String::New("needUpdate"), FunctionTemplate::New(InvocationCallback( V8Node::needUpdate )));
				objTemp->Set(v8::String::New("requestUpdate"), FunctionTemplate::New(InvocationCallback( V8Node::requestUpdate )));
				objTemp->Set(v8::String::New("cancelUpdate"), FunctionTemplate::New(InvocationCallback( V8Node::cancelUpdate )));
				objTemp->Set(v8::String::New("queueNeedUpdate"), FunctionTemplate::New(InvocationCallback( V8Node::queueNeedUpdate )));
				objTemp->Set(v8::String::New("processQueuedUpdates"), FunctionTemplate::New(InvocationCallback( V8Node::processQueuedUpdates )));

			//AnimationStateSet
				V8AnimationStateSet::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8AnimationStateSet::getTemplate()->SetClassName(v8::String::New("AnimationStateSet"));
				GPEFuncTemplateBase->PrototypeTemplate()->Set(v8::String::New("AnimationStateSet"), V8AnimationStateSet::getTemplate());

				objTemp = V8AnimationStateSet::getTemplate()->InstanceTemplate();
				objTemp->SetInternalFieldCount(1);

				objTemp->Set(v8::String::New("createAnimationState"), FunctionTemplate::New(InvocationCallback( V8AnimationStateSet::createAnimationState )));
				objTemp->Set(v8::String::New("getAnimationState"), FunctionTemplate::New(InvocationCallback( V8AnimationStateSet::getAnimationState )));
				objTemp->Set(v8::String::New("hasAnimationState"), FunctionTemplate::New(InvocationCallback( V8AnimationStateSet::hasAnimationState )));
				objTemp->Set(v8::String::New("removeAnimationState"), FunctionTemplate::New(InvocationCallback( V8AnimationStateSet::removeAnimationState )));
				objTemp->Set(v8::String::New("removeAllAnimationStates"), FunctionTemplate::New(InvocationCallback( V8AnimationStateSet::removeAllAnimationStates )));
				objTemp->Set(v8::String::New("copyMatchingState"), FunctionTemplate::New(InvocationCallback( V8AnimationStateSet::copyMatchingState )));
				objTemp->Set(v8::String::New("_notifyDirty"), FunctionTemplate::New(InvocationCallback( V8AnimationStateSet::_notifyDirty )));
				objTemp->Set(v8::String::New("getDirtyFrameNumber"), FunctionTemplate::New(InvocationCallback( V8AnimationStateSet::getDirtyFrameNumber )));
				objTemp->Set(v8::String::New("_notifyAnimationStateEnabled"), FunctionTemplate::New(InvocationCallback( V8AnimationStateSet::_notifyAnimationStateEnabled )));
				objTemp->Set(v8::String::New("hasEnabledAnimationState"), FunctionTemplate::New(InvocationCallback( V8AnimationStateSet::hasEnabledAnimationState )));

			//AnimationState
				V8AnimationState::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8AnimationState::getTemplate()->SetClassName(v8::String::New("AnimationState"));
				GPEFuncTemplateBase->PrototypeTemplate()->Set(v8::String::New("AnimationState"), V8AnimationState::getTemplate());

				objTemp = V8AnimationState::getTemplate()->InstanceTemplate();
				objTemp->SetInternalFieldCount(1);

				objTemp->Set(v8::String::New("getAnimationName"), FunctionTemplate::New(InvocationCallback( V8AnimationState::getAnimationName )));
				objTemp->Set(v8::String::New("getTimePosition"), FunctionTemplate::New(InvocationCallback( V8AnimationState::getTimePosition )));
				objTemp->Set(v8::String::New("setTimePosition"), FunctionTemplate::New(InvocationCallback( V8AnimationState::setTimePosition )));
				objTemp->Set(v8::String::New("getLength"), FunctionTemplate::New(InvocationCallback( V8AnimationState::getLength )));
				objTemp->Set(v8::String::New("setLength"), FunctionTemplate::New(InvocationCallback( V8AnimationState::setLength )));
				objTemp->Set(v8::String::New("getWeight"), FunctionTemplate::New(InvocationCallback( V8AnimationState::getWeight )));
				objTemp->Set(v8::String::New("setWeight"), FunctionTemplate::New(InvocationCallback( V8AnimationState::setWeight )));
				objTemp->Set(v8::String::New("addTime"), FunctionTemplate::New(InvocationCallback( V8AnimationState::addTime )));
				objTemp->Set(v8::String::New("hasEnded"), FunctionTemplate::New(InvocationCallback( V8AnimationState::hasEnded )));
				objTemp->Set(v8::String::New("getEnabled"), FunctionTemplate::New(InvocationCallback( V8AnimationState::getEnabled )));
				objTemp->Set(v8::String::New("setEnabled"), FunctionTemplate::New(InvocationCallback( V8AnimationState::setEnabled )));
				objTemp->Set(v8::String::New("compare"), FunctionTemplate::New(InvocationCallback( V8AnimationState::compare )));
				objTemp->Set(v8::String::New("acompare"), FunctionTemplate::New(InvocationCallback( V8AnimationState::acompare )));
				objTemp->Set(v8::String::New("setLoop"), FunctionTemplate::New(InvocationCallback( V8AnimationState::setLoop )));
				objTemp->Set(v8::String::New("getLoop"), FunctionTemplate::New(InvocationCallback( V8AnimationState::getLoop )));
				objTemp->Set(v8::String::New("copyStateFrom"), FunctionTemplate::New(InvocationCallback( V8AnimationState::copyStateFrom )));
				objTemp->Set(v8::String::New("getParent"), FunctionTemplate::New(InvocationCallback( V8AnimationState::getParent )));
				objTemp->Set(v8::String::New("createBlendMask"), FunctionTemplate::New(InvocationCallback( V8AnimationState::createBlendMask )));
				objTemp->Set(v8::String::New("destroyBlendMask"), FunctionTemplate::New(InvocationCallback( V8AnimationState::destroyBlendMask )));
				objTemp->Set(v8::String::New("_setBlendMaskData"), FunctionTemplate::New(InvocationCallback( V8AnimationState::_setBlendMaskData )));
				objTemp->Set(v8::String::New("hasBlendMask"), FunctionTemplate::New(InvocationCallback( V8AnimationState::hasBlendMask )));
				objTemp->Set(v8::String::New("setBlendMaskEntry"), FunctionTemplate::New(InvocationCallback( V8AnimationState::setBlendMaskEntry )));
				objTemp->Set(v8::String::New("getBlendMaskEntry"), FunctionTemplate::New(InvocationCallback( V8AnimationState::getBlendMaskEntry )));

		//ENUMS

				//temp = FunctionTemplate::New();
				//temp->SetClassName(v8::String::New("PxDataAccessFlag"));
				//GPEFuncTemplate->PrototypeTemplate()->Set("PxDataAccessFlag", temp->InstanceTemplate());

				//temp->PrototypeTemplate()->Set(v8::String::New("eREADABLE"), Uint32::New(PxDataAccessFlag::Enum::eREADABLE));


		//Functions
			//Nothing
				//temp = FunctionTemplate::New();
				//temp->SetClassName(v8::String::New("PxMath"));
				//GPEFuncTemplate->PrototypeTemplate()->Set("PxMath", temp->InstanceTemplate());

				//temp->PrototypeTemplate()->Set(v8::String::New("Max"),			FunctionTemplate::New(func_math_max));
				

		return(GPEFuncTemplateBase);
	}

//Vector3
	Handle<Value>  V8Vector3::Vector3Constructor(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0){
			Vector3* vecObject = new Vector3();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
			self.MakeWeak(Isolate::GetCurrent(),vecObject, &CleanupDelete);
			self->SetInternalField(0, External::New( vecObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty()){
			Vector3* vecObject;
			if(args[0]->IsNumber()){
				vecObject = new Vector3( args[0]->NumberValue());
			}
			else if(args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])){
				vecObject = new Vector3(*unwrap<Vector3>(args[0]->ToObject()));
			}
			else {
				return ThrowException( v8::Exception::TypeError( v8::String::New("Vector3 constructor takes nothing, (Number), (Number, Number, Number), or (Vector3) as an argument.") ) );
			}
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
			self.MakeWeak(Isolate::GetCurrent(),vecObject, &CleanupDelete);
			self->SetInternalField(0, External::New( vecObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 3 && !args[0].IsEmpty() && !args[1].IsEmpty() && !args[2].IsEmpty() ){
			if(	args[0]->IsNumber() &&
				args[1]->IsNumber() &&
				args[2]->IsNumber()) 
			{
				Vector3* vecObject = new Vector3( args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue() );
				Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
				self.MakeWeak(Isolate::GetCurrent(),vecObject, &CleanupDelete);
				self->SetInternalField(0, External::New( vecObject ));

				return scope.Close( self );
			}
		}
        
		return ThrowException( v8::Exception::TypeError( v8::String::New("Vector3 constructor takes nothing, (Number), (Number, Number, Number), or (Vector3) as an argument.") ) );
	}

	Handle<Value> V8Vector3::getX( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		Vector3* thisVector3 = unwrap<Vector3>(info.Holder());
		//if(thisVector3 != NULL) 
		//{
			return scope.Close(Number::New( thisVector3->x ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8Vector3::setX( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			Vector3* thisVector3 = unwrap<Vector3>(info.Holder());
			//if(thisVector3 != NULL && value->IsNumber()) 
			//{
				thisVector3->x = value->NumberValue();
			//}
		}
	}

	Handle<Value> V8Vector3::getY( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		Vector3* thisVector3 = unwrap<Vector3>(info.Holder());
		//if(thisVector3 != NULL) 
		//{
			return scope.Close(Number::New( thisVector3->y ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8Vector3::setY( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			Vector3* thisVector3 = unwrap<Vector3>(info.Holder());
			//if(thisVector3 != NULL && value->IsNumber()) 
			//{
				thisVector3->y = value->NumberValue();
			//}
		}
	}

	Handle<Value> V8Vector3::getZ( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		Vector3* thisVector3 = unwrap<Vector3>(info.Holder());
		//if(thisVector3 != NULL) 
		//{
			return scope.Close(Number::New( thisVector3->z ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8Vector3::setZ( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			Vector3* thisVector3 = unwrap<Vector3>(info.Holder());
			//if(thisVector3 != NULL && value->IsNumber()) 
			//{
				thisVector3->z = value->NumberValue();
			//}
		}
	}

	Handle<Value> V8Vector3::elementGet(uint32_t index, const AccessorInfo& info){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(index >=0 && index <= 2){
			Vector3* thisVector3 = unwrap<Vector3>(info.Holder());
			//if(thisVector3 != NULL) 
			//{
				return scope.Close(Number::New( (*thisVector3)[index] ));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::elementSet(uint32_t index, Local<Value> value, const AccessorInfo& info){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber() && index >=0 && index <= 2){
			Vector3* thisVector3 = unwrap<Vector3>(info.Holder());
			//if(thisVector3 != NULL) 
			//{
				(*thisVector3)[index] = value->NumberValue();
				return scope.Close(value);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::compare(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
				return scope.Close( Boolean::New(*thisVector3 == *inVector3));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::acompare(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
				return scope.Close( Boolean::New(*thisVector3 != *inVector3));
			//}
		}

		return scope.Close( Undefined() );
	}	

	Handle<Value> V8Vector3::negate(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
			Vector3* obj = new Vector3(-*thisVector3);
			Persistent<Object> newVector3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newVector3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newVector3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newVector3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::add(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
			Vector3* obj = new Vector3(*thisVector3 + *inVector3);
			Persistent<Object> newVector3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newVector3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newVector3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newVector3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::subtract(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
			Vector3* obj = new Vector3(*thisVector3 - *inVector3);
			Persistent<Object> newVector3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newVector3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newVector3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newVector3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::multiply(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
			Vector3* obj = new Vector3(*thisVector3 * args[0]->NumberValue());
			Persistent<Object> newVector3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newVector3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newVector3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newVector3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::divide(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
			Vector3* obj = new Vector3(*thisVector3 / args[0]->NumberValue());
			Persistent<Object> newVector3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newVector3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newVector3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newVector3);
			//}
		}

		return scope.Close( Undefined() );
	}


	Handle<Value> V8Vector3::assignmentAdd(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
				*thisVector3 += *inVector3;
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::assignmentSubtract(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
				*thisVector3 -= *inVector3;
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::assignmentMultiply(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
				*thisVector3 *= args[0]->NumberValue();
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::assignmentDivide(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
				*thisVector3 /= args[0]->NumberValue();
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::length(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
			return scope.Close( Number::New(thisVector3->length()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::squaredLength(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
			return scope.Close( Number::New(thisVector3->squaredLength()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::distance(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0]))
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());

			Vector3*	vecObject = new Vector3(*unwrap<Vector3>(args[0]->ToObject()));
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
			return scope.Close( Number::New(thisVector3->distance(*vecObject)));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::squaredDistance(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0]))
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());

			Vector3*	vecObject = new Vector3(*unwrap<Vector3>(args[0]->ToObject()));
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
			return scope.Close( Number::New(thisVector3->squaredDistance(*vecObject)));
			//}
		}

		return scope.Close( Undefined() );
	}


	Handle<Value> V8Vector3::dotProduct(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{			
			return scope.Close(Number::New(thisVector3->dotProduct(*inVector3)));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::absDotProduct(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{			
			return scope.Close(Number::New(thisVector3->absDotProduct(*inVector3)));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::crossProduct(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
			Vector3* obj = new Vector3(thisVector3->crossProduct(*inVector3));
			Persistent<Object> newVector3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newVector3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newVector3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newVector3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::normalize(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
			
			return scope.Close(Number::New(thisVector3->normalise()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::midPoint(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
			Vector3* obj = new Vector3(thisVector3->midPoint(*inVector3));
			Persistent<Object> newVector3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newVector3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newVector3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newVector3);
			//}
		}

		return scope.Close( Undefined() );
	}
	

	Handle<Value> V8Vector3::lessThan(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
			return scope.Close(Boolean::New( (*thisVector3) < (*inVector3) ) );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::greaterThan(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
			return scope.Close(Boolean::New( (*thisVector3) > (*inVector3) ) );
			//}
		}

		return scope.Close( Undefined() );
	}
	
	Handle<Value> V8Vector3::makeFloor(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
			thisVector3->makeFloor(*inVector3);

			return scope.Close(  args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::makeCeil(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
			thisVector3->makeCeil(*inVector3);

			return scope.Close(  args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::perpendicular(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			//if(thisVector3 != NULL && inVector3 != NULL) 
			//{
			Vector3* obj = new Vector3(thisVector3->perpendicular());
			Persistent<Object> newVector3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newVector3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newVector3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newVector3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::randomDeviant(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Radian* inRadian = unwrap<Radian>(args[0]->ToObject());

			Vector3* obj = new Vector3(thisVector3->randomDeviant(*inRadian));
			Persistent<Object> newVector3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newVector3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newVector3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newVector3);
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0]) &&
									  !args[1].IsEmpty() && args[1]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[1])) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Radian* inRadian = unwrap<Radian>(args[0]->ToObject());
			Vector3* inVector3 = unwrap<Vector3>(args[1]->ToObject());

			Vector3* obj = new Vector3(thisVector3->randomDeviant(*inRadian, *inVector3));
			Persistent<Object> newVector3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newVector3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newVector3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newVector3);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::angleBetween(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0]))  
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());

			Radian* obj = new Radian(thisVector3->angleBetween(*inVector3));
			Persistent<Object> newRadian = Persistent<Object>::New(Isolate::GetCurrent(),V8Radian::getTemplate()->InstanceTemplate()->NewInstance());			
			newRadian.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newRadian->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newRadian);
		}
		
		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::getRotationTo(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0]))  
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());

			Quaternion* obj = new Quaternion(thisVector3->getRotationTo(*inVector3));
			Persistent<Object> newQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newQuat->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newQuat);
		}

		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0]) &&
									  !args[1].IsEmpty() && args[1]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[1])) 
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			Vector3* inVector3_2 = unwrap<Vector3>(args[1]->ToObject());

			Quaternion* obj = new Quaternion(thisVector3->getRotationTo(*inVector3, *inVector3_2));
			Persistent<Object> newQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newQuat->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newQuat);
		}
		
		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::isZeroLength(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0)  
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			
			return scope.Close(Boolean::New(thisVector3->isZeroLength()));
		}
		
		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::getNormalized(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0)  
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());

			Vector3* obj = new Vector3(thisVector3->normalisedCopy());
			Persistent<Object> newVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8Vector3::getTemplate()->InstanceTemplate()->NewInstance());			
			newVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newVec3);
		}
		
		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::reflect(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0]))  
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());

			Vector3* obj = new Vector3(thisVector3->reflect(*inVector3));
			Persistent<Object> newVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8Vector3::getTemplate()->InstanceTemplate()->NewInstance());			
			newVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newVec3);
		}
		
		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::positionEquals(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0]))  
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			
			return scope.Close(Boolean::New( thisVector3->positionEquals(*inVector3) ));
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0]) &&
			!args[1].IsEmpty() && args[1]->IsNumber())  
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			
			return scope.Close(Boolean::New( thisVector3->positionEquals(*inVector3, args[1]->ToNumber()->Value()) ));
		}
		
		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::positionCloses(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0]))  
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			
			return scope.Close(Boolean::New( thisVector3->positionCloses(*inVector3) ));
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0]) &&
			!args[1].IsEmpty() && args[1]->IsNumber())  
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			
			return scope.Close(Boolean::New( thisVector3->positionCloses(*inVector3, args[1]->ToNumber()->Value()) ));
		}
		
		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::directionEquals(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0]) &&
			!args[1].IsEmpty() && args[1]->IsObject() && V8Radian::getTemplate()->HasInstance(args[1]))  
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());
			Radian* inRad = unwrap<Radian>(args[1]->ToObject());
			
			return scope.Close(Boolean::New( thisVector3->directionEquals(*inVector3, *inRad) ));
		}
		
		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::isNaN(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0)  
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());
			
			return scope.Close(Boolean::New( thisVector3->isNaN() ));
		}
		
		return scope.Close( Undefined() );
	}

	Handle<Value> V8Vector3::primaryAxis(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0)  
        {
			Vector3* thisVector3 = unwrap<Vector3>(args.Holder());

			Vector3* obj = new Vector3(thisVector3->primaryAxis());
			Persistent<Object> newVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8Vector3::getTemplate()->InstanceTemplate()->NewInstance());			
			newVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newVec3);
		}
		
		return scope.Close( Undefined() );
	}


//Quaternion
	Handle<Value>  V8Quaternion::QuaternionConstructor(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0){
			Quaternion* quatObject = new Quaternion();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
			self.MakeWeak(Isolate::GetCurrent(),quatObject, &CleanupDelete);
			self->SetInternalField(0, External::New( quatObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty()){
			Quaternion* quatObject;
			if(args[0]->IsObject() && V8Matrix3::getTemplate()->HasInstance(args[0])){
				quatObject = new Quaternion(*unwrap<Matrix3>(args[0]->ToObject()));
			}
			else if(args[0]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[0])){
				quatObject = new Quaternion(*unwrap<Quaternion>(args[0]->ToObject()));
			}
			else {
				return ThrowException( v8::Exception::TypeError( v8::String::New("Quaternion constructor takes nothing, (Matrix3), (Number, Number, Number, Number), (Number,Vector3), (Vector3,Vector3,Vector3), or (Quaternion) as an argument.") ) );
			}
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
			self.MakeWeak(Isolate::GetCurrent(),quatObject, &CleanupDelete);
			self->SetInternalField(0, External::New( quatObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0]) &&
				!args[1].IsEmpty() && args[1]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[1])){
			Quaternion* quatObject = new Quaternion(*unwrap<Radian>(args[0]->ToObject()),*unwrap<Vector3>(args[1]->ToObject()));
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
			self.MakeWeak(Isolate::GetCurrent(),quatObject, &CleanupDelete);
			self->SetInternalField(0, External::New( quatObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0]) &&
				!args[1].IsEmpty() && args[1]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[1]) &&
				!args[2].IsEmpty() && args[2]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[2])){
			Quaternion* quatObject = new Quaternion(*unwrap<Vector3>(args[0]->ToObject()),*unwrap<Vector3>(args[1]->ToObject()), *unwrap<Vector3>(args[2]->ToObject()) );
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
			self.MakeWeak(Isolate::GetCurrent(),quatObject, &CleanupDelete);
			self->SetInternalField(0, External::New( quatObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 4){
			if(!args[0].IsEmpty() && args[0]->IsNumber() &&
				!args[1].IsEmpty() && args[1]->IsNumber() &&
				!args[2].IsEmpty() && args[2]->IsNumber() &&
				!args[3].IsEmpty() && args[3]->IsNumber()) 
			{
				Quaternion* quatObject = new Quaternion( args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue(), args[3]->NumberValue() );
				Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
				self.MakeWeak(Isolate::GetCurrent(),quatObject, &CleanupDelete);
				self->SetInternalField(0, External::New( quatObject ));

				return scope.Close( self );
			}
		}
        
		return ThrowException( v8::Exception::TypeError( v8::String::New("Quaternion constructor takes nothing, (Matrix3), (Number, Number, Number, Number), (Number,Vector3), (Vector3,Vector3,Vector3), or (Quaternion) as an argument.") ) );
	}

	Handle<Value> V8Quaternion::getX( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		Quaternion* thisQuat = unwrap<Quaternion>(info.Holder());
		//if(thisQuat != NULL) 
		//{
			Handle<Number> val = Number::New( thisQuat->x );
			return scope.Close(val);
		//}

		//return scope.Close( Undefined() );
	}

	void V8Quaternion::setX( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		Quaternion* thisQuat = unwrap<Quaternion>(info.Holder());
		if(thisQuat != NULL && value->IsNumber()) 
		{
			thisQuat->x = value->NumberValue();
		}
	}

	Handle<Value> V8Quaternion::getY( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		Quaternion* thisQuat = unwrap<Quaternion>(info.Holder());
		//if(thisQuat != NULL) 
		//{
			Handle<Number> val = Number::New( thisQuat->y );
			return scope.Close(val);
		//}

		//return scope.Close( Undefined() );
	}

	void V8Quaternion::setY( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		Quaternion* thisQuat = unwrap<Quaternion>(info.Holder());
		if(thisQuat != NULL && value->IsNumber()) 
		{
			thisQuat->y = value->NumberValue();
		}
	}

	Handle<Value> V8Quaternion::getZ( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		Quaternion* thisQuat = unwrap<Quaternion>(info.Holder());
		//if(thisQuat != NULL) 
		//{
			Handle<Number> val = Number::New( thisQuat->z );
			return scope.Close(val);
		//}

		//return scope.Close( Undefined() );
	}

	void V8Quaternion::setZ( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		Quaternion* thisQuat = unwrap<Quaternion>(info.Holder());
		if(thisQuat != NULL && value->IsNumber()) 
		{
			thisQuat->z = value->NumberValue();
		}
	}

	Handle<Value> V8Quaternion::getW( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		Quaternion* thisQuat = unwrap<Quaternion>(info.Holder());
		//if(thisQuat != NULL) 
		//{
			Handle<Number> val = Number::New( thisQuat->w );
			return scope.Close(val);
		//}

		//return scope.Close( Undefined() );
	}

	void V8Quaternion::setW( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		Quaternion* thisQuat = unwrap<Quaternion>(info.Holder());
		if(thisQuat != NULL && value->IsNumber()) 
		{
			thisQuat->w = value->NumberValue();
		}
	}

	Handle<Value> V8Quaternion::elementGet(uint32_t index, const AccessorInfo& info){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(true){
			Quaternion* thisQuat = unwrap<Quaternion>(info.Holder());
			//if(thisPxVec3 != NULL) 
			//{
				return scope.Close(Number::New( (*thisQuat)[index] ));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::elementSet(uint32_t index, Local<Value> value, const AccessorInfo& info){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			Quaternion* thisQuat = unwrap<Quaternion>(info.Holder());
			//if(thisPxVec3 != NULL) 
			//{
				(*thisQuat)[index] = value->NumberValue();
				return scope.Close(value);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::FromRotationMatrix(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Matrix3::getTemplate()->HasInstance(args[0])) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			thisQuat->FromRotationMatrix(*unwrap<Matrix3>(args[0]->ToObject()));

			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::ToRotationMatrix(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Matrix3::getTemplate()->HasInstance(args[0])) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			thisQuat->ToRotationMatrix(*unwrap<Matrix3>(args[0]->ToObject()));

			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::FromAngleAxis(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0]) && 
							!args[1].IsEmpty() && args[1]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[1])) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			thisQuat->FromAngleAxis(*unwrap<Radian>(args[0]->ToObject()), *unwrap<Vector3>(args[1]->ToObject()));

			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::ToAngleAxis(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0]) && 
							!args[1].IsEmpty() && args[1]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[1])) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			thisQuat->ToAngleAxis(*unwrap<Radian>(args[0]->ToObject()), *unwrap<Vector3>(args[1]->ToObject()));

			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::FromAxes(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0]) && 
							!args[1].IsEmpty() && args[1]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[1]) &&
							!args[2].IsEmpty() && args[2]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[2])) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			thisQuat->FromAxes(*unwrap<Vector3>(args[0]->ToObject()), *unwrap<Vector3>(args[1]->ToObject()), *unwrap<Vector3>(args[2]->ToObject()));

			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::ToAxes(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0]) && 
							!args[1].IsEmpty() && args[1]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[1]) &&
							!args[2].IsEmpty() && args[2]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[2])) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			thisQuat->ToAxes(*unwrap<Vector3>(args[0]->ToObject()), *unwrap<Vector3>(args[1]->ToObject()), *unwrap<Vector3>(args[2]->ToObject()));

			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::xAxis(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			Vector3* obj = new Vector3(thisQuat->xAxis());
			Persistent<Object> newVector3 = Persistent<Object>::New(Isolate::GetCurrent(),V8Vector3::getTemplate()->InstanceTemplate()->NewInstance());			
			newVector3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newVector3->SetInternalField(0, External::New(obj));

			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( newVector3 );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::yAxis(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			Vector3* obj = new Vector3(thisQuat->yAxis());
			Persistent<Object> newVector3 = Persistent<Object>::New(Isolate::GetCurrent(),V8Vector3::getTemplate()->InstanceTemplate()->NewInstance());			
			newVector3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newVector3->SetInternalField(0, External::New( obj ));

			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( newVector3 );
			//}
		}

		return scope.Close( Undefined() );
	}


	Handle<Value> V8Quaternion::zAxis(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			Vector3* obj = new Vector3(thisQuat->zAxis());
			Persistent<Object> newVector3 = Persistent<Object>::New(Isolate::GetCurrent(),V8Vector3::getTemplate()->InstanceTemplate()->NewInstance());			
			newVector3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newVector3->SetInternalField(0, External::New( obj ));

			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( newVector3 );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::add(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[0])) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());
			Quaternion* inPxQuat = unwrap<Quaternion>(args[0]->ToObject());
			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{

			Quaternion* obj = new Quaternion(*thisQuat + *inPxQuat);
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxQuat);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::subtract(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[0])) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());
			Quaternion* inPxQuat = unwrap<Quaternion>(args[0]->ToObject());
			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{

			Quaternion* obj = new Quaternion(*thisQuat - *inPxQuat);
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxQuat);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::multiply(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty())
        {
			if(args[0]->IsNumber()){
				Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());
				//if(thisQuat != NULL && inPxQuat != NULL) 
				//{

				Quaternion* obj = new Quaternion(*thisQuat * args[0]->NumberValue());
				Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
				newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxQuat->SetInternalField(0, External::New( obj ));
			
				return scope.Close(newPxQuat);
				//}
			}
			else if(args[0]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[0])){
				Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());
				Quaternion* inPxQuat = unwrap<Quaternion>(args[0]->ToObject());
				//if(thisQuat != NULL && inPxQuat != NULL) 
				//{

				Quaternion* obj = new Quaternion(*thisQuat * *inPxQuat);
				Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
				newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxQuat->SetInternalField(0, External::New( obj ));
			
				return scope.Close(newPxQuat);
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::negate(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());
			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{

			Quaternion* obj = new Quaternion(-*thisQuat);
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxQuat);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::compare(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[0])) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());
			Quaternion* otherQuat = unwrap<Quaternion>(args[0]->ToObject());
			
			return scope.Close( Boolean::New(thisQuat == otherQuat) );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::acompare(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[0])) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());
			Quaternion* otherQuat = unwrap<Quaternion>(args[0]->ToObject());
			
			return scope.Close( Boolean::New(thisQuat != otherQuat) );
			//}
		}

		return scope.Close( Undefined() );
	}
	
	Handle<Value> V8Quaternion::Dot(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[0])) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());
			Quaternion* inPxQuat = unwrap<Quaternion>(args[0]->ToObject());
			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{			
			return scope.Close(Number::New(thisQuat->Dot(*inPxQuat)));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::Norm(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());
			
			return scope.Close( Number::New(thisQuat->Norm()) );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::normalize(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());
			
			return scope.Close( Number::New(thisQuat->normalise()) );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::Inverse(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());
			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{
			Quaternion* obj = new Quaternion(thisQuat->Inverse());
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxQuat);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::UnitInverse(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());
			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{
			Quaternion* obj = new Quaternion(thisQuat->UnitInverse());
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxQuat);
			//}
		}

		return scope.Close( Undefined() );
	}	

	Handle<Value> V8Quaternion::Exp(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());
			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{
			Quaternion* obj = new Quaternion(thisQuat->Exp());
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxQuat);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::Log(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());
			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{
			Quaternion* obj = new Quaternion(thisQuat->Log());
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxQuat);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::rotate(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());
			Vector3* inVector3 = unwrap<Vector3>(args[0]->ToObject());

			Vector3* obj = new Vector3((*thisQuat) * (*inVector3));
			Persistent<Object> newVector3 = Persistent<Object>::New(Isolate::GetCurrent(),V8Vector3::getTemplate()->InstanceTemplate()->NewInstance());			
			newVector3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newVector3->SetInternalField(0, External::New( obj ));

			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( newVector3 );
			//}
		}

		return scope.Close( Undefined() );
	}


	Handle<Value> V8Quaternion::getRoll(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			Radian* obj = new Radian(thisQuat->getRoll());
			Persistent<Object> newRad = Persistent<Object>::New(Isolate::GetCurrent(),V8Radian::getTemplate()->InstanceTemplate()->NewInstance());			
			newRad.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newRad->SetInternalField(0, External::New( obj ));

			return scope.Close( newRad );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsBoolean()) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			Radian* obj = new Radian(thisQuat->getRoll(args[0]->BooleanValue()));
			Persistent<Object> newRad = Persistent<Object>::New(Isolate::GetCurrent(),V8Radian::getTemplate()->InstanceTemplate()->NewInstance());			
			newRad.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newRad->SetInternalField(0, External::New( obj ));

			return scope.Close( newRad );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::getPitch(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			Radian* obj = new Radian(thisQuat->getPitch());
			Persistent<Object> newRad = Persistent<Object>::New(Isolate::GetCurrent(),V8Radian::getTemplate()->InstanceTemplate()->NewInstance());			
			newRad.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newRad->SetInternalField(0, External::New( obj ));

			return scope.Close( newRad );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsBoolean()) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			Radian* obj = new Radian(thisQuat->getPitch(args[0]->BooleanValue()));
			Persistent<Object> newRad = Persistent<Object>::New(Isolate::GetCurrent(),V8Radian::getTemplate()->InstanceTemplate()->NewInstance());			
			newRad.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newRad->SetInternalField(0, External::New( obj ));

			return scope.Close( newRad );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::getYaw(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			Radian* obj = new Radian(thisQuat->getYaw());
			Persistent<Object> newRad = Persistent<Object>::New(Isolate::GetCurrent(),V8Radian::getTemplate()->InstanceTemplate()->NewInstance());			
			newRad.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newRad->SetInternalField(0, External::New( obj ));

			return scope.Close( newRad );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsBoolean()) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			Radian* obj = new Radian(thisQuat->getYaw(args[0]->BooleanValue()));
			Persistent<Object> newRad = Persistent<Object>::New(Isolate::GetCurrent(),V8Radian::getTemplate()->InstanceTemplate()->NewInstance());			
			newRad.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newRad->SetInternalField(0, External::New( obj ));

			return scope.Close( newRad );
		}

		return scope.Close( Undefined() );
	}

	
	Handle<Value> V8Quaternion::equals(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[0]) && 
				!args[1].IsEmpty() && args[1]->IsObject() && V8Radian::getTemplate()->HasInstance(args[1])) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			return scope.Close( Boolean::New( thisQuat->equals(*unwrap<Quaternion>(args[0]->ToObject()), *unwrap<Radian>(args[1]->ToObject())) ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::Slerp(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsNumber() && 
				!args[1].IsEmpty() && args[1]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[1]) && 
				!args[2].IsEmpty() && args[2]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[2])) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			Quaternion* obj = new Quaternion(thisQuat->Slerp(args[0]->NumberValue(),*unwrap<Quaternion>(args[1]->ToObject()), *unwrap<Quaternion>(args[2]->ToObject()) ) );
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));

			return scope.Close( newPxQuat );
		}
		else if(args.Length() == 4 && !args[0].IsEmpty() && args[0]->IsNumber() && 
				!args[1].IsEmpty() && args[1]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[1]) && 
				!args[2].IsEmpty() && args[2]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[2]) &&
				!args[3].IsEmpty() && args[3]->IsBoolean()) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			Quaternion* obj = new Quaternion(thisQuat->Slerp(args[0]->NumberValue(),*unwrap<Quaternion>(args[1]->ToObject()), *unwrap<Quaternion>(args[2]->ToObject()), args[3]->BooleanValue() ) );
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));

			return scope.Close( newPxQuat );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::SlerpExtraSpins(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 4 && !args[0].IsEmpty() && args[0]->IsNumber() && 
				!args[1].IsEmpty() && args[1]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[1]) && 
				!args[2].IsEmpty() && args[2]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[2]) &&
				!args[3].IsEmpty() && args[3]->IsNumber()) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			Quaternion* obj = new Quaternion(thisQuat->SlerpExtraSpins(args[0]->NumberValue(),*unwrap<Quaternion>(args[1]->ToObject()), *unwrap<Quaternion>(args[2]->ToObject()), args[3]->Int32Value() ) );
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));

			return scope.Close( newPxQuat );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::Intermediate(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		//TODO: finish this

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::Squad(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		//TODO: finish this

		return scope.Close( Undefined() );
	}


	Handle<Value> V8Quaternion::nlerp(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsNumber() && 
				!args[1].IsEmpty() && args[1]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[1]) && 
				!args[2].IsEmpty() && args[2]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[2])) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			Quaternion* obj = new Quaternion(thisQuat->nlerp(args[0]->NumberValue(),*unwrap<Quaternion>(args[1]->ToObject()), *unwrap<Quaternion>(args[2]->ToObject()) ) );
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));

			return scope.Close( newPxQuat );
		}
		if(args.Length() == 4 && !args[0].IsEmpty() && args[0]->IsNumber() && 
				!args[1].IsEmpty() && args[1]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[1]) && 
				!args[2].IsEmpty() && args[2]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[2]) &&
				!args[3].IsEmpty() && args[3]->IsBoolean()) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			Quaternion* obj = new Quaternion(thisQuat->nlerp(args[0]->NumberValue(),*unwrap<Quaternion>(args[1]->ToObject()), *unwrap<Quaternion>(args[2]->ToObject()), args[3]->BooleanValue() ) );
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));

			return scope.Close( newPxQuat );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::isNaN(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Quaternion* thisQuat = unwrap<Quaternion>(args.Holder());

			return scope.Close( Boolean::New( thisQuat->isNaN() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Quaternion::createIdentity(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			//if(thisQuat != NULL && inPxQuat != NULL) 
			//{

			Quaternion* obj = new Quaternion(Quaternion::IDENTITY);
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxQuat);
			//}
		}

		return scope.Close( Undefined() );
	}

//Radian
	Handle<Value>  V8Radian::RadianConstructor(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0){
			Radian* quatObject = new Radian();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
			self.MakeWeak(Isolate::GetCurrent(),quatObject, &CleanupDelete);
			self->SetInternalField(0, External::New( quatObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty()){
			Radian* rad;
			if(args[0]->IsNumber()){
				rad = new Radian(args[0]->NumberValue());
			}
			else if(args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])){
				rad = new Radian(*unwrap<Radian>(args[0]->ToObject()));
			}
			else if(args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])){
				rad = new Radian(*unwrap<Degree>(args[0]->ToObject()));
			}
			else {
				return ThrowException( v8::Exception::TypeError( v8::String::New("Radian constructor takes nothing, (Number), (Degree), or (Radian) as an argument.") ) );
			}
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
			self.MakeWeak(Isolate::GetCurrent(),rad, &CleanupDelete);
			self->SetInternalField(0, External::New( rad ));

			return scope.Close( self );
		}
		
        
		return ThrowException( v8::Exception::TypeError( v8::String::New("Radian constructor takes nothing, (Number), (Degree), or (Radian) as an argument.") ) );
	}

	Handle<Value> V8Radian::set(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());

			*thisRad = *unwrap<Radian>(args[0]->ToObject());
			
			return scope.Close(args.Holder());

		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());

			*thisRad = *unwrap<Degree>(args[0]->ToObject());
			
			return scope.Close(args.Holder());

		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());

			*thisRad = args[0]->NumberValue();
			
			return scope.Close(args.Holder());

		}


		return scope.Close( Undefined() );
	}

	Handle<Value> V8Radian::valueDegrees(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());
			
			return scope.Close( Number::New( thisRad->valueDegrees() ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Radian::valueRadians(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());
			
			return scope.Close( Number::New( thisRad->valueRadians() ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Radian::valueAngleUnits(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());
			
			return scope.Close( Number::New( thisRad->valueAngleUnits() ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Radian::negate(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());

			Radian* newRad = new Radian(-*thisRad);

			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),newRad, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( newRad ));
			
			return scope.Close(args.Holder());

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Radian::add(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());
			Radian* otherRad = unwrap<Radian>(args[0]->ToObject());

			Radian* newRad = new Radian(*thisRad + *otherRad);

			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),newRad, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( newRad ));
			
			return scope.Close(args.Holder());

		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());
			Degree* otherRad = unwrap<Degree>(args[0]->ToObject());

			Radian* newRad = new Radian(*thisRad + *otherRad);

			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),newRad, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( newRad ));
			
			return scope.Close(args.Holder());

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Radian::subtract(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());
			Radian* otherRad = unwrap<Radian>(args[0]->ToObject());

			Radian* newRad = new Radian(*thisRad - *otherRad);

			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),newRad, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( newRad ));
			
			return scope.Close(args.Holder());

		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());
			Degree* otherRad = unwrap<Degree>(args[0]->ToObject());

			Radian* newRad = new Radian(*thisRad - *otherRad);

			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),newRad, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( newRad ));
			
			return scope.Close(args.Holder());

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Radian::multiply(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());
			Radian* otherRad = unwrap<Radian>(args[0]->ToObject());

			Radian* newRad = new Radian(*thisRad * *otherRad);

			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),newRad, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( newRad ));
			
			return scope.Close(args.Holder());

		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());

			Radian* newRad = new Radian(*thisRad * args[0]->NumberValue());

			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),newRad, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( newRad ));
			
			return scope.Close(args.Holder());

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Radian::divide(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());

			Radian* newRad = new Radian(*thisRad / args[0]->NumberValue());

			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),newRad, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( newRad ));
			
			return scope.Close(args.Holder());

		}

		return scope.Close( Undefined() );
	}



	Handle<Value> V8Radian::assignmentAdd(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());
			Radian* otherRad = unwrap<Radian>(args[0]->ToObject());

			*thisRad += *otherRad;
			
			return scope.Close(args.Holder());

		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());
			Degree* otherRad = unwrap<Degree>(args[0]->ToObject());

			*thisRad += *otherRad;

			return scope.Close(args.Holder());

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Radian::assignmentSubtract(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());
			Radian* otherRad = unwrap<Radian>(args[0]->ToObject());

			*thisRad -= *otherRad;
			
			return scope.Close(args.Holder());

		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());
			Degree* otherRad = unwrap<Degree>(args[0]->ToObject());

			*thisRad -= *otherRad;
			
			return scope.Close(args.Holder());

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Radian::assignmentMultiply(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());

			*thisRad *= args[0]->NumberValue();
			
			return scope.Close(args.Holder());

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Radian::assignmentDivide(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());

			*thisRad /= args[0]->NumberValue();
			
			return scope.Close(args.Holder());

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Radian::compare(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());
			Radian* otherRad = unwrap<Radian>(args[0]->ToObject());

			return scope.Close( Boolean::New( *thisRad == *otherRad ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Radian::acompare(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());
			Radian* otherRad = unwrap<Radian>(args[0]->ToObject());

			return scope.Close( Boolean::New( *thisRad != *otherRad ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Radian::lessThan(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());
			Radian* otherRad = unwrap<Radian>(args[0]->ToObject());

			return scope.Close( Boolean::New( *thisRad < *otherRad ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Radian::lessThanEq(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());
			Radian* otherRad = unwrap<Radian>(args[0]->ToObject());

			return scope.Close( Boolean::New( *thisRad <= *otherRad ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Radian::greaterThan(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());
			Radian* otherRad = unwrap<Radian>(args[0]->ToObject());

			return scope.Close( Boolean::New( *thisRad > *otherRad ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Radian::greaterThanEq(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Radian* thisRad = unwrap<Radian>(args.Holder()->ToObject());
			Radian* otherRad = unwrap<Radian>(args[0]->ToObject());

			return scope.Close( Boolean::New( *thisRad >= *otherRad ) );

		}

		return scope.Close( Undefined() );
	}

//Degree
	Handle<Value>  V8Degree::DegreeConstructor(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0){
			Degree* quatObject = new Degree();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
			self.MakeWeak(Isolate::GetCurrent(),quatObject, &CleanupDelete);
			self->SetInternalField(0, External::New( quatObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty()){
			Degree* rad;
			if(args[0]->IsNumber()){
				rad = new Degree(args[0]->NumberValue());
			}
			else if(args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])){
				rad = new Degree(*unwrap<Degree>(args[0]->ToObject()));
			}
			else if(args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])){
				rad = new Degree(*unwrap<Radian>(args[0]->ToObject()));
			}
			else {
				return ThrowException( v8::Exception::TypeError( v8::String::New("Degree constructor takes nothing, (Number), (Radian), or (Degree) as an argument.") ) );
			}
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
			self.MakeWeak(Isolate::GetCurrent(),rad, &CleanupDelete);
			self->SetInternalField(0, External::New( rad ));

			return scope.Close( self );
		}
		
        
		return ThrowException( v8::Exception::TypeError( v8::String::New("Degree constructor takes nothing, (Number), (Radian), or (Degree) as an argument.") ) );
	}

	Handle<Value> V8Degree::set(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());

			*thisRad = *unwrap<Degree>(args[0]->ToObject());
			
			return scope.Close(args.Holder());

		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());

			*thisRad = *unwrap<Radian>(args[0]->ToObject());
			
			return scope.Close(args.Holder());

		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());

			*thisRad = args[0]->NumberValue();
			
			return scope.Close(args.Holder());

		}


		return scope.Close( Undefined() );
	}

	Handle<Value> V8Degree::valueRadians(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());
			
			return scope.Close( Number::New( thisRad->valueRadians() ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Degree::valueDegrees(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());
			
			return scope.Close( Number::New( thisRad->valueDegrees() ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Degree::valueAngleUnits(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());
			
			return scope.Close( Number::New( thisRad->valueAngleUnits() ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Degree::negate(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());

			Degree* newRad = new Degree(-*thisRad);

			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),newRad, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( newRad ));
			
			return scope.Close(args.Holder());

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Degree::add(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());
			Degree* otherRad = unwrap<Degree>(args[0]->ToObject());

			Degree* newRad = new Degree(*thisRad + *otherRad);

			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),newRad, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( newRad ));
			
			return scope.Close(args.Holder());

		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());
			Radian* otherRad = unwrap<Radian>(args[0]->ToObject());

			Degree* newRad = new Degree(*thisRad + *otherRad);

			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),newRad, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( newRad ));
			
			return scope.Close(args.Holder());

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Degree::subtract(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());
			Degree* otherRad = unwrap<Degree>(args[0]->ToObject());

			Degree* newRad = new Degree(*thisRad - *otherRad);

			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),newRad, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( newRad ));
			
			return scope.Close(args.Holder());

		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());
			Radian* otherRad = unwrap<Radian>(args[0]->ToObject());

			Degree* newRad = new Degree(*thisRad - *otherRad);

			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),newRad, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( newRad ));
			
			return scope.Close(args.Holder());

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Degree::multiply(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());
			Degree* otherRad = unwrap<Degree>(args[0]->ToObject());

			Degree* newRad = new Degree(*thisRad * *otherRad);

			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),newRad, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( newRad ));
			
			return scope.Close(args.Holder());

		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());

			Degree* newRad = new Degree(*thisRad * args[0]->NumberValue());

			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),newRad, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( newRad ));
			
			return scope.Close(args.Holder());

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Degree::divide(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());

			Degree* newRad = new Degree(*thisRad / args[0]->NumberValue());

			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			newPxQuat.MakeWeak(Isolate::GetCurrent(),newRad, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( newRad ));
			
			return scope.Close(args.Holder());

		}

		return scope.Close( Undefined() );
	}



	Handle<Value> V8Degree::assignmentAdd(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());
			Degree* otherRad = unwrap<Degree>(args[0]->ToObject());

			*thisRad += *otherRad;
			
			return scope.Close(args.Holder());

		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());
			Radian* otherRad = unwrap<Radian>(args[0]->ToObject());

			*thisRad += *otherRad;

			return scope.Close(args.Holder());

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Degree::assignmentSubtract(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());
			Degree* otherRad = unwrap<Degree>(args[0]->ToObject());

			*thisRad -= *otherRad;
			
			return scope.Close(args.Holder());

		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());
			Radian* otherRad = unwrap<Radian>(args[0]->ToObject());

			*thisRad -= *otherRad;
			
			return scope.Close(args.Holder());

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Degree::assignmentMultiply(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());

			*thisRad *= args[0]->NumberValue();
			
			return scope.Close(args.Holder());

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Degree::assignmentDivide(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());

			*thisRad /= args[0]->NumberValue();
			
			return scope.Close(args.Holder());

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Degree::compare(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());
			Degree* otherRad = unwrap<Degree>(args[0]->ToObject());

			return scope.Close( Boolean::New( *thisRad == *otherRad ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Degree::acompare(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());
			Degree* otherRad = unwrap<Degree>(args[0]->ToObject());

			return scope.Close( Boolean::New( *thisRad != *otherRad ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Degree::lessThan(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());
			Degree* otherRad = unwrap<Degree>(args[0]->ToObject());

			return scope.Close( Boolean::New( *thisRad < *otherRad ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Degree::lessThanEq(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());
			Degree* otherRad = unwrap<Degree>(args[0]->ToObject());

			return scope.Close( Boolean::New( *thisRad <= *otherRad ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Degree::greaterThan(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());
			Degree* otherRad = unwrap<Degree>(args[0]->ToObject());

			return scope.Close( Boolean::New( *thisRad > *otherRad ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Degree::greaterThanEq(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Degree::getTemplate()->HasInstance(args[0])) 
        {
			Degree* thisRad = unwrap<Degree>(args.Holder()->ToObject());
			Degree* otherRad = unwrap<Degree>(args[0]->ToObject());

			return scope.Close( Boolean::New( *thisRad >= *otherRad ) );

		}

		return scope.Close( Undefined() );
	}

//Node
	Handle<Value> V8Node::getName(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());
			
			return scope.Close( v8::String::New( thisNode->getName().c_str() ));

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::getParent(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Node* newNode = thisNode->getParent();

			Persistent<Object> nodeObj = Persistent<Object>::New(Isolate::GetCurrent(),V8Node::getTemplate()->InstanceTemplate()->NewInstance());			
			//nodeObj.MakeWeak(Isolate::GetCurrent(),newNode, &CleanupDelete);
			nodeObj->SetInternalField(0, External::New( newNode ));
			
			return scope.Close( nodeObj );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::getOrientation(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Quaternion* newQuat = new Quaternion(thisNode->getOrientation());

			Persistent<Object> quatObj = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			quatObj.MakeWeak(Isolate::GetCurrent(),newQuat, &CleanupDelete);
			quatObj->SetInternalField(0, External::New( newQuat ));
			
			return scope.Close( quatObj );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::setOrientation(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->setOrientation(*unwrap<Quaternion>(args[0]->ToObject()));
			
			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 4 && !args[0].IsEmpty() && args[0]->IsNumber() && 
			!args[1].IsEmpty() && args[1]->IsNumber() &&
			!args[2].IsEmpty() && args[2]->IsNumber() &&
			!args[3].IsEmpty() && args[3]->IsNumber()){
				
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->setOrientation(args[0]->NumberValue(),args[1]->NumberValue(),args[2]->NumberValue(),args[3]->NumberValue());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::resetOrientation(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->resetOrientation();
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::setPosition(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->setPosition(*unwrap<Vector3>(args[0]->ToObject()));
			
			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsNumber() && 
			!args[1].IsEmpty() && args[1]->IsNumber() &&
			!args[2].IsEmpty() && args[2]->IsNumber()){
				
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->setPosition(args[0]->NumberValue(),args[1]->NumberValue(),args[2]->NumberValue());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}
	
	
	Handle<Value> V8Node::getPosition(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Vector3* newVal = new Vector3(thisNode->getPosition());

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Vector3::getTemplate()->InstanceTemplate()->NewInstance());			
			obj.MakeWeak(Isolate::GetCurrent(),newVal, &CleanupDelete);
			obj->SetInternalField(0, External::New( newVal ));
			
			return scope.Close( obj );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::setScale(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->setScale(*unwrap<Vector3>(args[0]->ToObject()));
			
			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsNumber() && 
			!args[1].IsEmpty() && args[1]->IsNumber() &&
			!args[2].IsEmpty() && args[2]->IsNumber()){
				
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->setScale(args[0]->NumberValue(),args[1]->NumberValue(),args[2]->NumberValue());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::getScale(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Vector3* newVal = new Vector3(thisNode->getScale());

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Vector3::getTemplate()->InstanceTemplate()->NewInstance());			
			obj.MakeWeak(Isolate::GetCurrent(),newVal, &CleanupDelete);
			obj->SetInternalField(0, External::New( newVal ));
			
			return scope.Close( obj );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::setInheritOrientation(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsBoolean()) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());
			
			thisNode->setInheritOrientation(args[0]->BooleanValue());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::getInheritOrientation(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			
			return scope.Close( Boolean::New(thisNode->getInheritOrientation()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::setInheritScale(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsBoolean()) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());
			
			thisNode->setInheritScale(args[0]->BooleanValue());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::getInheritScale(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			
			return scope.Close( Boolean::New(thisNode->getInheritScale()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::scale(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->scale(*unwrap<Vector3>(args[0]->ToObject()));
			
			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsNumber() && 
			!args[1].IsEmpty() && args[1]->IsNumber() &&
			!args[2].IsEmpty() && args[2]->IsNumber()){
				
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->scale(args[0]->NumberValue(),args[1]->NumberValue(),args[2]->NumberValue());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::translate(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->translate(*unwrap<Vector3>(args[0]->ToObject()));
			
			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0]) && 
			!args[1].IsEmpty() && args[1]->IsUint32()){
				
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->translate(*unwrap<Vector3>(args[0]->ToObject()), (Node::TransformSpace)args[1]->Uint32Value());
			
			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsNumber() && 
			!args[1].IsEmpty() && args[1]->IsNumber() &&
			!args[2].IsEmpty() && args[2]->IsNumber()){
				
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->translate(args[0]->NumberValue(),args[1]->NumberValue(),args[2]->NumberValue());
			
			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 4 && !args[0].IsEmpty() && args[0]->IsNumber() && 
			!args[1].IsEmpty() && args[1]->IsNumber() &&
			!args[2].IsEmpty() && args[2]->IsNumber() &&
			!args[3].IsEmpty() && args[3]->IsUint32()){
				
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->translate(args[0]->NumberValue(),args[1]->NumberValue(),args[2]->NumberValue(), (Node::TransformSpace)args[3]->Uint32Value());
			
			return scope.Close( args.Holder() );
		}
		//TODO:Trasnlate with Matrix3

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::roll(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->roll(*unwrap<Radian>(args[0]->ToObject()));
			
			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0]) && 
			!args[1].IsEmpty() && args[1]->IsUint32()){
				
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->roll(*unwrap<Radian>(args[0]->ToObject()), (Node::TransformSpace)args[1]->Uint32Value());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::pitch(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->pitch(*unwrap<Radian>(args[0]->ToObject()));
			
			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0]) && 
			!args[1].IsEmpty() && args[1]->IsUint32()){
				
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->pitch(*unwrap<Radian>(args[0]->ToObject()), (Node::TransformSpace)args[1]->Uint32Value());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::yaw(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->yaw(*unwrap<Radian>(args[0]->ToObject()));
			
			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8Radian::getTemplate()->HasInstance(args[0]) && 
			!args[1].IsEmpty() && args[1]->IsUint32()){
				
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->yaw(*unwrap<Radian>(args[0]->ToObject()), (Node::TransformSpace)args[1]->Uint32Value());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::rotate(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0]) &&
			!args[1].IsEmpty() && args[1]->IsObject() && V8Radian::getTemplate()->HasInstance(args[1])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->rotate(*unwrap<Vector3>(args[0]->ToObject()), *unwrap<Radian>(args[1]->ToObject()));
			
			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0]) &&
			!args[1].IsEmpty() && args[1]->IsObject() && V8Radian::getTemplate()->HasInstance(args[1]) &&
			!args[2].IsEmpty() && args[2]->IsUint32()) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->rotate(*unwrap<Vector3>(args[0]->ToObject()), *unwrap<Radian>(args[1]->ToObject()),(Node::TransformSpace)args[2]->Uint32Value());
			
			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->rotate(*unwrap<Quaternion>(args[0]->ToObject()));
			
			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[0]) &&
			!args[1].IsEmpty() && args[1]->IsUint32()) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->rotate(*unwrap<Quaternion>(args[0]->ToObject()),(Node::TransformSpace)args[1]->Uint32Value());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::createChild(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Node* newNode = thisNode->createChild();

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Node::getTemplate()->InstanceTemplate()->NewInstance());			
			obj->SetInternalField(0, External::New( newNode ));
			
			return scope.Close( obj );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Node* newNode = thisNode->createChild(*unwrap<Vector3>(args[0]->ToObject()));

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Node::getTemplate()->InstanceTemplate()->NewInstance());			
			obj->SetInternalField(0, External::New( newNode ));
			
			return scope.Close( obj );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsString()) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Node* newNode = thisNode->createChild(*v8::String::Utf8Value(args[0]->ToString()));

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Node::getTemplate()->InstanceTemplate()->NewInstance());			
			obj->SetInternalField(0, External::New( newNode ));
			
			return scope.Close( obj );
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0]) &&
			 !args[1].IsEmpty() && args[1]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[1])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Node* newNode = thisNode->createChild(*unwrap<Vector3>(args[0]->ToObject()), *unwrap<Quaternion>(args[1]->ToObject()));

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Node::getTemplate()->InstanceTemplate()->NewInstance());			
			obj->SetInternalField(0, External::New( newNode ));
			
			return scope.Close( obj );
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsString() && 
			!args[1].IsEmpty() && args[1]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[1])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Node* newNode = thisNode->createChild(*v8::String::Utf8Value(args[0]->ToString()), *unwrap<Vector3>(args[1]->ToObject()));

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Node::getTemplate()->InstanceTemplate()->NewInstance());			
			obj->SetInternalField(0, External::New( newNode ));
			
			return scope.Close(obj );
		}
		else if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsString() && 
			!args[1].IsEmpty() && args[1]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[1]) && 
			!args[2].IsEmpty() && args[2]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[2])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Node* newNode = thisNode->createChild(*v8::String::Utf8Value(args[0]->ToString()), *unwrap<Vector3>(args[1]->ToObject()), *unwrap<Quaternion>(args[2]->ToObject()));

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Node::getTemplate()->InstanceTemplate()->NewInstance());			
			obj->SetInternalField(0, External::New( newNode ));
			
			return scope.Close( obj);
		}
		

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::addChild(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Node::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->addChild(unwrap<Node>(args[0]->ToObject()));
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::numChildren(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Node::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());
			
			return scope.Close( Uint32::New(thisNode->numChildren()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::getChild(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32()) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Node* newNode = thisNode->getChild(args[0]->Uint32Value());

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Node::getTemplate()->InstanceTemplate()->NewInstance());			
			obj->SetInternalField(0, External::New( newNode ));
			
			return scope.Close( obj );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsString()) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Node* newNode = thisNode->getChild(*v8::String::Utf8Value(args[0]->ToString()));

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Node::getTemplate()->InstanceTemplate()->NewInstance());			
			obj->SetInternalField(0, External::New( newNode ));
			
			return scope.Close( obj );
		}


		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::removeChild(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32()) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Node* newNode = thisNode->removeChild(args[0]->Uint32Value());

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Node::getTemplate()->InstanceTemplate()->NewInstance());			
			obj->SetInternalField(0, External::New( newNode ));
			
			return scope.Close( obj );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsString()) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Node* newNode = thisNode->removeChild(*v8::String::Utf8Value(args[0]->ToString()));

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Node::getTemplate()->InstanceTemplate()->NewInstance());			
			obj->SetInternalField(0, External::New( newNode ));
			
			return scope.Close( obj );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Node::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Node* newNode = thisNode->removeChild(unwrap<Node>(args[0]->ToObject()));

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Node::getTemplate()->InstanceTemplate()->NewInstance());			
			obj->SetInternalField(0, External::New( newNode ));
			
			return scope.Close( obj );
		}


		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::removeAllChildren(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->removeAllChildren();
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::_getDerivedOrientation(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Quaternion* newQuat = new Quaternion(thisNode->_getDerivedOrientation());

			Persistent<Object> quatObj = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			quatObj.MakeWeak(Isolate::GetCurrent(),newQuat, &CleanupDelete);
			quatObj->SetInternalField(0, External::New( newQuat ));
			
			return scope.Close( quatObj );
		}

		return scope.Close( Undefined() );
	}
	
	Handle<Value> V8Node::_getDerivedPosition(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Vector3* newVal = new Vector3(thisNode->_getDerivedPosition());

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Vector3::getTemplate()->InstanceTemplate()->NewInstance());			
			obj.MakeWeak(Isolate::GetCurrent(),newVal, &CleanupDelete);
			obj->SetInternalField(0, External::New( newVal ));
			
			return scope.Close( obj );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::_setDerivedOrientation(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->_setDerivedOrientation(*unwrap<Quaternion>(args[0]->ToObject()));
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::_setDerivedPosition(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->_setDerivedPosition(*unwrap<Vector3>(args[0]->ToObject()));
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::_getDerivedScale(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Vector3* newVal = new Vector3(thisNode->_getDerivedScale());

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Vector3::getTemplate()->InstanceTemplate()->NewInstance());			
			obj.MakeWeak(Isolate::GetCurrent(),newVal, &CleanupDelete);
			obj->SetInternalField(0, External::New( newVal ));
			
			return scope.Close( obj );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::_update(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsBoolean() &&
			!args[1].IsEmpty() && args[1]->IsBoolean()) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->_update(args[0]->BooleanValue(), args[1]->BooleanValue());

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::setInitialState(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->setInitialState();

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::resetToInitialState(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->resetToInitialState();

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::getInitialOrientation(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Quaternion* newQuat = new Quaternion(thisNode->getInitialOrientation());

			Persistent<Object> quatObj = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			quatObj.MakeWeak(Isolate::GetCurrent(),newQuat, &CleanupDelete);
			quatObj->SetInternalField(0, External::New( newQuat ));
			
			return scope.Close( quatObj );
		}

		return scope.Close( Undefined() );
	}
	
	Handle<Value> V8Node::getInitialPosition(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Vector3* newVal = new Vector3(thisNode->getInitialPosition());

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Vector3::getTemplate()->InstanceTemplate()->NewInstance());			
			obj.MakeWeak(Isolate::GetCurrent(),newVal, &CleanupDelete);
			obj->SetInternalField(0, External::New( newVal ));
			
			return scope.Close( obj );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::getInitialScale(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Vector3* newVal = new Vector3(thisNode->getInitialScale());

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Vector3::getTemplate()->InstanceTemplate()->NewInstance());			
			obj.MakeWeak(Isolate::GetCurrent(),newVal, &CleanupDelete);
			obj->SetInternalField(0, External::New( newVal ));
			
			return scope.Close( obj );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::convertWorldToLocalPosition(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Vector3* newVal = new Vector3(thisNode->convertWorldToLocalPosition(*unwrap<Vector3>(args[0]->ToObject())));

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Vector3::getTemplate()->InstanceTemplate()->NewInstance());			
			obj.MakeWeak(Isolate::GetCurrent(),newVal, &CleanupDelete);
			obj->SetInternalField(0, External::New( newVal ));
			
			return scope.Close( obj );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::convertLocalToWorldPosition(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Vector3::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Vector3* newVal = new Vector3(thisNode->convertLocalToWorldPosition(*unwrap<Vector3>(args[0]->ToObject())));

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Vector3::getTemplate()->InstanceTemplate()->NewInstance());			
			obj.MakeWeak(Isolate::GetCurrent(),newVal, &CleanupDelete);
			obj->SetInternalField(0, External::New( newVal ));
			
			return scope.Close( obj );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::convertWorldToLocalOrientation(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Quaternion* newVal = new Quaternion(thisNode->convertWorldToLocalOrientation(*unwrap<Quaternion>(args[0]->ToObject())));

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			obj.MakeWeak(Isolate::GetCurrent(),newVal, &CleanupDelete);
			obj->SetInternalField(0, External::New( newVal ));
			
			return scope.Close( obj );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::convertLocalToWorldOrientation(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Quaternion::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			Quaternion* newVal = new Quaternion(thisNode->convertLocalToWorldOrientation(*unwrap<Quaternion>(args[0]->ToObject())));

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8Quaternion::getTemplate()->InstanceTemplate()->NewInstance());			
			obj.MakeWeak(Isolate::GetCurrent(),newVal, &CleanupDelete);
			obj->SetInternalField(0, External::New( newVal ));
			
			return scope.Close( obj );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::needUpdate(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->needUpdate();

			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsBoolean()) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->needUpdate(args[0]->BooleanValue());

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::requestUpdate(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Node::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->requestUpdate(unwrap<Node>(args[0]->ToObject()));

			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8Node::getTemplate()->HasInstance(args[0]) &&
			!args[1].IsEmpty() && args[1]->IsBoolean()) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->requestUpdate(unwrap<Node>(args[0]->ToObject()), args[1]->BooleanValue());

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::cancelUpdate(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Node::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->cancelUpdate(unwrap<Node>(args[0]->ToObject()));

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::queueNeedUpdate(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8Node::getTemplate()->HasInstance(args[0])) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->queueNeedUpdate(unwrap<Node>(args[0]->ToObject()));

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8Node::processQueuedUpdates(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			Node* thisNode = unwrap<Node>(args.Holder()->ToObject());

			thisNode->processQueuedUpdates();

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

//AnimationStateSet
	Handle<Value> V8AnimationStateSet::createAnimationState(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsString() &&
			!args[1].IsEmpty() && args[1]->IsNumber() &&
			!args[2].IsEmpty() && args[2]->IsNumber()) 
        {
			AnimationStateSet* thisASSet = unwrap<AnimationStateSet>(args.Holder()->ToObject());

			AnimationState* newVal = thisASSet->createAnimationState(*v8::String::Utf8Value(args[0]->ToString()), args[1]->NumberValue(), args[2]->NumberValue());

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8AnimationState::getTemplate()->InstanceTemplate()->NewInstance());			
			obj->SetInternalField(0, External::New( newVal ));
			
			return scope.Close( obj );

		}
		else if(args.Length() == 4 && !args[0].IsEmpty() && args[0]->IsString() &&
			!args[1].IsEmpty() && args[1]->IsNumber() &&
			!args[2].IsEmpty() && args[2]->IsNumber() &&
			!args[3].IsEmpty() && args[3]->IsNumber()) 
        {
			AnimationStateSet* thisASSet = unwrap<AnimationStateSet>(args.Holder()->ToObject());

			AnimationState* newVal = thisASSet->createAnimationState(*v8::String::Utf8Value(args[0]->ToString()), args[1]->NumberValue(), args[2]->NumberValue(), args[3]->NumberValue());

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8AnimationState::getTemplate()->InstanceTemplate()->NewInstance());			
			obj->SetInternalField(0, External::New( newVal ));
			
			return scope.Close( obj );
		}
		else if(args.Length() == 5 && !args[0].IsEmpty() && args[0]->IsString() &&
			!args[1].IsEmpty() && args[1]->IsNumber() &&
			!args[2].IsEmpty() && args[2]->IsNumber() &&
			!args[3].IsEmpty() && args[3]->IsNumber() &&
			!args[4].IsEmpty() && args[4]->IsBoolean()) 
        {
			AnimationStateSet* thisASSet = unwrap<AnimationStateSet>(args.Holder()->ToObject());

			AnimationState* newVal = thisASSet->createAnimationState(*v8::String::Utf8Value(args[0]->ToString()), args[1]->NumberValue(), args[2]->NumberValue(), args[3]->NumberValue(), args[4]->BooleanValue());

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8AnimationState::getTemplate()->InstanceTemplate()->NewInstance());			
			obj->SetInternalField(0, External::New( newVal ));
			
			return scope.Close( obj );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationStateSet::getAnimationState(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsString())
        {
			AnimationStateSet* thisASSet = unwrap<AnimationStateSet>(args.Holder()->ToObject());

			AnimationState* newVal = thisASSet->getAnimationState(*v8::String::Utf8Value(args[0]->ToString()));

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8AnimationState::getTemplate()->InstanceTemplate()->NewInstance());			
			obj->SetInternalField(0, External::New( newVal ));
			
			return scope.Close( obj );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationStateSet::hasAnimationState(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsString())
        {
			AnimationStateSet* thisASSet = unwrap<AnimationStateSet>(args.Holder()->ToObject());
			
			return scope.Close( Boolean::New(thisASSet->hasAnimationState(*v8::String::Utf8Value(args[0]->ToString()))) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationStateSet::removeAnimationState(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsString())
        {
			AnimationStateSet* thisASSet = unwrap<AnimationStateSet>(args.Holder()->ToObject());
			thisASSet->removeAnimationState(*v8::String::Utf8Value(args[0]->ToString()));
			
			return scope.Close( args.Holder() );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationStateSet::removeAllAnimationStates(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0)
        {
			AnimationStateSet* thisASSet = unwrap<AnimationStateSet>(args.Holder()->ToObject());
			thisASSet->removeAllAnimationStates();
			
			return scope.Close( args.Holder() );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationStateSet::copyMatchingState(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8AnimationStateSet::getTemplate()->HasInstance(args[0]))
        {
			AnimationStateSet* thisASSet = unwrap<AnimationStateSet>(args.Holder()->ToObject());
			thisASSet->copyMatchingState(unwrap<AnimationStateSet>(args[0]->ToObject()));
			
			return scope.Close( args.Holder() );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationStateSet::_notifyDirty(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0)
        {
			AnimationStateSet* thisASSet = unwrap<AnimationStateSet>(args.Holder()->ToObject());
			thisASSet->_notifyDirty();
			
			return scope.Close( args.Holder() );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationStateSet::getDirtyFrameNumber(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0)
        {
			AnimationStateSet* thisASSet = unwrap<AnimationStateSet>(args.Holder()->ToObject());
			
			
			return scope.Close( Uint32::New(thisASSet->getDirtyFrameNumber()) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationStateSet::_notifyAnimationStateEnabled(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8AnimationState::getTemplate()->HasInstance(args[0]) &&
			!args[1].IsEmpty() && args[1]->IsBoolean())
        {
			AnimationStateSet* thisASSet = unwrap<AnimationStateSet>(args.Holder()->ToObject());
			thisASSet->_notifyAnimationStateEnabled(unwrap<AnimationState>(args[0]->ToObject()), args[1]->BooleanValue());
			
			return scope.Close( args.Holder() );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationStateSet::hasEnabledAnimationState(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0)
        {
			AnimationStateSet* thisASSet = unwrap<AnimationStateSet>(args.Holder()->ToObject());
			
			
			return scope.Close( Boolean::New(thisASSet->hasEnabledAnimationState()) );

		}

		return scope.Close( Undefined() );
	}

//AnimationState
	Handle<Value> V8AnimationState::getAnimationName(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());
			
			return scope.Close( v8::String::New( thisAS->getAnimationName().c_str() ));

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::getTimePosition(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());
			
			return scope.Close( Number::New( thisAS->getTimePosition() ));

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::setTimePosition(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());

			thisAS->setTimePosition(args[0]->NumberValue());
			
			return scope.Close( args.Holder() );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::getLength(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());
			
			return scope.Close( Number::New( thisAS->getLength() ));

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::setLength(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());

			thisAS->setLength(args[0]->NumberValue());
			
			return scope.Close( args.Holder() );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::getWeight(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());
			
			return scope.Close( Number::New( thisAS->getWeight() ));

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::setWeight(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());

			thisAS->setWeight(args[0]->NumberValue());
			
			return scope.Close( args.Holder() );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::addTime(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());

			thisAS->addTime(args[0]->NumberValue());
			
			return scope.Close( args.Holder() );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::hasEnded(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());
			
			return scope.Close( Boolean::New( thisAS->hasEnded() ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::getEnabled(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());
			
			return scope.Close( Boolean::New( thisAS->getEnabled() ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::setEnabled(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsBoolean()) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());

			thisAS->setEnabled(args[0]->BooleanValue());
			
			return scope.Close( args.Holder() );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::compare(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8AnimationState::getTemplate()->HasInstance(args[0])) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());
			
			return scope.Close( Boolean::New( *thisAS == *unwrap<AnimationState>(args[0]->ToObject()) ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::acompare(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8AnimationState::getTemplate()->HasInstance(args[0])) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());
			
			return scope.Close( Boolean::New( *thisAS != *unwrap<AnimationState>(args[0]->ToObject()) ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::getLoop(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());
			
			return scope.Close( Boolean::New( thisAS->getLoop() ) );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::setLoop(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsBoolean()) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());

			thisAS->setLoop(args[0]->BooleanValue());
			
			return scope.Close( args.Holder() );

		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::copyStateFrom(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8AnimationState::getTemplate()->HasInstance(args[0])) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());

			thisAS->copyStateFrom(*unwrap<AnimationState>(args[0]->ToObject()));
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::getParent(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());

			thisAS->copyStateFrom(*unwrap<AnimationState>(args[0]->ToObject()));

			AnimationStateSet* newVal = thisAS->getParent();

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8AnimationStateSet::getTemplate()->InstanceTemplate()->NewInstance());			
			obj->SetInternalField(0, External::New( newVal ));
			
			return scope.Close( obj );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::createBlendMask(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32()) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());

			thisAS->createBlendMask(args[0]->Uint32Value());
			
			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsUint32() &&
			!args[1].IsEmpty() && args[1]->IsNumber()) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());

			thisAS->createBlendMask(args[0]->Uint32Value(), args[1]->NumberValue());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::destroyBlendMask(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());

			thisAS->destroyBlendMask();
			
			return scope.Close( args.Holder() );
		}


		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::_setBlendMaskData(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		//TODO: Finish this

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::hasBlendMask(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());
			
			return scope.Close( Boolean::New(thisAS->hasBlendMask()));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::setBlendMaskEntry(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsUint32() &&
			!args[1].IsEmpty() && args[1]->IsNumber()) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());

			thisAS->setBlendMaskEntry(args[0]->Uint32Value(), args[1]->NumberValue());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8AnimationState::getBlendMaskEntry(const Arguments& args){
		//Locker lock;
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32()) 
        {
			AnimationState* thisAS = unwrap<AnimationState>(args.Holder()->ToObject());
			
			return scope.Close( Number::New(thisAS->getBlendMaskEntry(args[0]->Uint32Value())) );
		}

		return scope.Close( Undefined() );
	}