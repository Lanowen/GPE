#pragma once

#include <v8.h>

#include <Scripting_Helpers.hpp>

using namespace v8;

class V8Vector3 : public BaseV8TemplateObject<V8Vector3>{
public:
	static Handle<Value> Vector3Constructor(const Arguments& args);

	//Accessors
	static Handle<Value> getX( Local<v8::String> property, const AccessorInfo& info );
	static void setX( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getY( Local<v8::String> property, const AccessorInfo& info );
	static void setY( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getZ( Local<v8::String> property, const AccessorInfo& info );
	static void setZ( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Interceptors
	static Handle<Value> elementGet(uint32_t index, const AccessorInfo& info);
	static Handle<Value> elementSet(uint32_t index, Local<Value> value, const AccessorInfo& info);

	//Functions
	static Handle<Value> compare(const Arguments& args);
	static Handle<Value> acompare(const Arguments& args);
	static Handle<Value> negate(const Arguments& args);
	static Handle<Value> add(const Arguments& args);
	static Handle<Value> subtract(const Arguments& args);
	static Handle<Value> multiply(const Arguments& args);
	static Handle<Value> divide(const Arguments& args);

	static Handle<Value> assignmentAdd(const Arguments& args);
	static Handle<Value> assignmentSubtract(const Arguments& args);
	static Handle<Value> assignmentMultiply(const Arguments& args);
	static Handle<Value> assignmentDivide(const Arguments& args);

	static Handle<Value> length(const Arguments& args);
	static Handle<Value> squaredLength(const Arguments& args);
	static Handle<Value> distance(const Arguments& args);
	static Handle<Value> squaredDistance(const Arguments& args);

	static Handle<Value> dotProduct(const Arguments& args);
	static Handle<Value> absDotProduct(const Arguments& args);
	static Handle<Value> crossProduct(const Arguments& args);
	static Handle<Value> normalize(const Arguments& args);
	static Handle<Value> getNormalized(const Arguments& args);
	static Handle<Value> midPoint(const Arguments& args);

	static Handle<Value> lessThan(const Arguments& args);
	static Handle<Value> greaterThan(const Arguments& args);

	static Handle<Value> makeFloor(const Arguments& args);
	static Handle<Value> makeCeil(const Arguments& args);	

	static Handle<Value> perpendicular(const Arguments& args);
	static Handle<Value> randomDeviant(const Arguments& args);
	static Handle<Value> angleBetween(const Arguments& args);
	static Handle<Value> getRotationTo(const Arguments& args);
	static Handle<Value> isZeroLength(const Arguments& args);
	static Handle<Value> reflect(const Arguments& args);
	static Handle<Value> positionEquals(const Arguments& args);
	static Handle<Value> positionCloses(const Arguments& args);
	static Handle<Value> directionEquals(const Arguments& args);
	static Handle<Value> isNaN(const Arguments& args);
	static Handle<Value> primaryAxis(const Arguments& args);
};


class V8Quaternion : public BaseV8TemplateObject<V8Quaternion>{
public:
	static Handle<Value> QuaternionConstructor(const Arguments& args);

	//Accessors
	static Handle<Value> getX( Local<v8::String> property, const AccessorInfo& info );
	static void setX( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getY( Local<v8::String> property, const AccessorInfo& info );
	static void setY( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getZ( Local<v8::String> property, const AccessorInfo& info );
	static void setZ( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getW( Local<v8::String> property, const AccessorInfo& info );
	static void setW( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Interceptors
	static Handle<Value> elementGet(uint32_t index, const AccessorInfo& info);
	static Handle<Value> elementSet(uint32_t index, Local<Value> value, const AccessorInfo& info);

	//Functions
	static Handle<Value> FromRotationMatrix(const Arguments& args);
	static Handle<Value> ToRotationMatrix(const Arguments& args);
	static Handle<Value> FromAngleAxis(const Arguments& args);
	static Handle<Value> ToAngleAxis(const Arguments& args);
	static Handle<Value> FromAxes(const Arguments& args);
	static Handle<Value> ToAxes(const Arguments& args);
	static Handle<Value> xAxis(const Arguments& args);
	static Handle<Value> yAxis(const Arguments& args);
	static Handle<Value> zAxis(const Arguments& args);

	static Handle<Value> add(const Arguments& args);
	static Handle<Value> subtract(const Arguments& args);
	static Handle<Value> multiply(const Arguments& args);
	static Handle<Value> negate(const Arguments& args);
	static Handle<Value> compare(const Arguments& args);
	static Handle<Value> acompare(const Arguments& args);

	static Handle<Value> Dot(const Arguments& args);
	static Handle<Value> Norm(const Arguments& args);
	static Handle<Value> normalize(const Arguments& args);
	static Handle<Value> Inverse(const Arguments& args);
	static Handle<Value> UnitInverse(const Arguments& args);
	static Handle<Value> Exp(const Arguments& args);
	static Handle<Value> Log(const Arguments& args);
	static Handle<Value> rotate(const Arguments& args);

	static Handle<Value> getRoll(const Arguments& args);
	static Handle<Value> getPitch(const Arguments& args);
	static Handle<Value> getYaw(const Arguments& args);
	static Handle<Value> equals(const Arguments& args);
	static Handle<Value> Slerp(const Arguments& args);
	static Handle<Value> SlerpExtraSpins(const Arguments& args);
	static Handle<Value> Intermediate(const Arguments& args);
	static Handle<Value> Squad(const Arguments& args);
	static Handle<Value> nlerp(const Arguments& args);
	static Handle<Value> isNaN(const Arguments& args);	

	static Handle<Value> createIdentity(const Arguments& args);
};

class V8Radian : public BaseV8TemplateObject<V8Radian>{
public:
	static Handle<Value> RadianConstructor(const Arguments& args);

	//Functions
	static Handle<Value> set(const Arguments& args);

	static Handle<Value> valueDegrees(const Arguments& args);
	static Handle<Value> valueRadians(const Arguments& args);
	static Handle<Value> valueAngleUnits(const Arguments& args);
	
	static Handle<Value> negate(const Arguments& args);
	static Handle<Value> add(const Arguments& args);
	static Handle<Value> subtract(const Arguments& args);
	static Handle<Value> multiply(const Arguments& args);
	static Handle<Value> divide(const Arguments& args);

	static Handle<Value> assignmentAdd(const Arguments& args);
	static Handle<Value> assignmentSubtract(const Arguments& args);
	static Handle<Value> assignmentMultiply(const Arguments& args);
	static Handle<Value> assignmentDivide(const Arguments& args);

	static Handle<Value> compare(const Arguments& args);
	static Handle<Value> acompare(const Arguments& args);
	static Handle<Value> lessThan(const Arguments& args);
	static Handle<Value> lessThanEq(const Arguments& args);
	static Handle<Value> greaterThan(const Arguments& args);
	static Handle<Value> greaterThanEq(const Arguments& args);
};

class V8Degree : public BaseV8TemplateObject<V8Degree>{
public:
	static Handle<Value> DegreeConstructor(const Arguments& args);

	//Functions
	static Handle<Value> set(const Arguments& args);

	static Handle<Value> valueDegrees(const Arguments& args);
	static Handle<Value> valueRadians(const Arguments& args);
	static Handle<Value> valueAngleUnits(const Arguments& args);
	
	static Handle<Value> negate(const Arguments& args);
	static Handle<Value> add(const Arguments& args);
	static Handle<Value> subtract(const Arguments& args);
	static Handle<Value> multiply(const Arguments& args);
	static Handle<Value> divide(const Arguments& args);

	static Handle<Value> assignmentAdd(const Arguments& args);
	static Handle<Value> assignmentSubtract(const Arguments& args);
	static Handle<Value> assignmentMultiply(const Arguments& args);
	static Handle<Value> assignmentDivide(const Arguments& args);

	static Handle<Value> compare(const Arguments& args);
	static Handle<Value> acompare(const Arguments& args);
	static Handle<Value> lessThan(const Arguments& args);
	static Handle<Value> lessThanEq(const Arguments& args);
	static Handle<Value> greaterThan(const Arguments& args);
	static Handle<Value> greaterThanEq(const Arguments& args);
};

class V8Node : public BaseV8TemplateObject<V8Node>{
public:

	//Functions
	static Handle<Value> getName(const Arguments& args);
	static Handle<Value> getParent(const Arguments& args);

	static Handle<Value> getOrientation(const Arguments& args);
	static Handle<Value> setOrientation(const Arguments& args);
	static Handle<Value> resetOrientation(const Arguments& args);
	static Handle<Value> setPosition(const Arguments& args);
	static Handle<Value> getPosition(const Arguments& args);
	static Handle<Value> setScale(const Arguments& args);
	static Handle<Value> getScale(const Arguments& args);
	static Handle<Value> setInheritOrientation(const Arguments& args);
	static Handle<Value> getInheritOrientation(const Arguments& args);
	static Handle<Value> setInheritScale(const Arguments& args);
	static Handle<Value> getInheritScale(const Arguments& args);
	static Handle<Value> scale(const Arguments& args);
	static Handle<Value> translate(const Arguments& args);
	static Handle<Value> roll(const Arguments& args);
	static Handle<Value> pitch(const Arguments& args);
	static Handle<Value> yaw(const Arguments& args);
	static Handle<Value> rotate(const Arguments& args);
	//static Handle<Value> getLocalAxes(const Arguments& args);

	static Handle<Value> createChild(const Arguments& args);
	static Handle<Value> addChild(const Arguments& args);
	static Handle<Value> numChildren(const Arguments& args);
	static Handle<Value> getChild(const Arguments& args);
	//static Handle<Value> getChildIterator(const Arguments& args);
	static Handle<Value> removeChild(const Arguments& args);
	static Handle<Value> removeAllChildren(const Arguments& args);
	static Handle<Value> _setDerivedPosition(const Arguments& args);
	static Handle<Value> _setDerivedOrientation(const Arguments& args);
	static Handle<Value> _getDerivedOrientation(const Arguments& args);
	static Handle<Value> _getDerivedPosition(const Arguments& args);
	static Handle<Value> _getDerivedScale(const Arguments& args);
	//static Handle<Value> _getFullTransform(const Arguments& args);
	static Handle<Value> _update(const Arguments& args);
	//static Handle<Value> setListener(const Arguments& args);
	//static Handle<Value> getListener(const Arguments& args);
	static Handle<Value> setInitialState(const Arguments& args);
	static Handle<Value> resetToInitialState(const Arguments& args);
	static Handle<Value> getInitialPosition(const Arguments& args);

	static Handle<Value> convertWorldToLocalPosition(const Arguments& args);
	static Handle<Value> convertLocalToWorldPosition(const Arguments& args);
	static Handle<Value> convertWorldToLocalOrientation(const Arguments& args);
	static Handle<Value> convertLocalToWorldOrientation(const Arguments& args);
	static Handle<Value> getInitialOrientation(const Arguments& args);
	static Handle<Value> getInitialScale(const Arguments& args);
	//static Handle<Value> getSquaredViewDepth(const Arguments& args);
	static Handle<Value> needUpdate(const Arguments& args);
	static Handle<Value> requestUpdate(const Arguments& args);
	static Handle<Value> cancelUpdate(const Arguments& args);
	//static Handle<Value> getDebugRenderable(const Arguments& args);
	static Handle<Value> queueNeedUpdate(const Arguments& args);
	static Handle<Value> processQueuedUpdates(const Arguments& args);
	//static Handle<Value> setUserAny(const Arguments& args);
	//static Handle<Value> getUserAny(const Arguments& args);
	//static Handle<Value> getUserObjectBindings(const Arguments& args);
	//static Handle<Value> getUserObjectBindings(const Arguments& args);

};


class V8AnimationStateSet : public BaseV8TemplateObject<V8AnimationStateSet>{
public:

	//Functions
	static Handle<Value> createAnimationState(const Arguments& args);
	static Handle<Value> getAnimationState(const Arguments& args);
	static Handle<Value> hasAnimationState(const Arguments& args);
	static Handle<Value> removeAnimationState(const Arguments& args);
	static Handle<Value> removeAllAnimationStates(const Arguments& args);
	//static Handle<Value> getAnimationStateIterator(const Arguments& args);
	static Handle<Value> copyMatchingState(const Arguments& args);
	static Handle<Value> _notifyDirty(const Arguments& args);
	static Handle<Value> getDirtyFrameNumber(const Arguments& args);
	static Handle<Value> _notifyAnimationStateEnabled(const Arguments& args);
	static Handle<Value> hasEnabledAnimationState(const Arguments& args);
	//static Handle<Value> getEnabledAnimationStateIterator(const Arguments& args);
};

class V8AnimationState : public BaseV8TemplateObject<V8AnimationState>{
public:

	//Functions
	static Handle<Value> getAnimationName(const Arguments& args);
	static Handle<Value> getTimePosition(const Arguments& args);
	static Handle<Value> setTimePosition(const Arguments& args);
	static Handle<Value> getLength(const Arguments& args);
	static Handle<Value> setLength(const Arguments& args);
	static Handle<Value> getWeight(const Arguments& args);
	static Handle<Value> setWeight(const Arguments& args);
	static Handle<Value> addTime(const Arguments& args);
	static Handle<Value> hasEnded(const Arguments& args);
	static Handle<Value> getEnabled(const Arguments& args);
	static Handle<Value> setEnabled(const Arguments& args);
	static Handle<Value> compare(const Arguments& args);
	static Handle<Value> acompare(const Arguments& args);
	static Handle<Value> setLoop(const Arguments& args);
	static Handle<Value> getLoop(const Arguments& args);
	static Handle<Value> copyStateFrom(const Arguments& args);
	static Handle<Value> getParent(const Arguments& args);
	static Handle<Value> createBlendMask(const Arguments& args);
	static Handle<Value> destroyBlendMask(const Arguments& args);
	static Handle<Value> _setBlendMaskData(const Arguments& args);
	//static Handle<Value> _setBlendMask(const Arguments& args);
	//static Handle<Value> getBlendMask(const Arguments& args);
	static Handle<Value> hasBlendMask(const Arguments& args);
	static Handle<Value> setBlendMaskEntry(const Arguments& args);
	static Handle<Value> getBlendMaskEntry(const Arguments& args);
};

class V8Entity : public BaseV8TemplateObject<V8Entity>{
};
class V8Matrix3 : public BaseV8TemplateObject<V8Matrix3>{
};
class V8SceneNode : public BaseV8TemplateObject<V8SceneNode>{
};


class V8OGRE {
public:
	static Local<FunctionTemplate> NewFunctionTemplate(InvocationCallback callback = 0, Handle<Value> data = Handle<Value>(), Handle<Signature> signature = Handle<Signature>());			

private:

};