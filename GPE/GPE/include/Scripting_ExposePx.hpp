#pragma once

//#define _USE_MATH_DEFINES

#include <v8.h>
#include <PxPhysics.h>
//#include <PxVec2.h>
#include <characterkinematic/PxController.h>
#include <characterkinematic/PxBoxController.h>
#include <characterkinematic/PxCapsuleController.h>
#include <PxPhysicsAPI.h>

#include <string>

#include <Scripting_Helpers.hpp>

using namespace v8;

class V8PxSerializable : public BaseV8TemplateObject<V8PxSerializable>{
public:
	//Functions
	static Handle<Value> getOrder(const Arguments& args);
	static Handle<Value> collectForExport(const Arguments& args);
	static Handle<Value> getFields(const Arguments& args);
	static Handle<Value> getFieldDescriptor(const Arguments& args);
	static Handle<Value> getObjectSize(const Arguments& args);
	static Handle<Value> exportExtraData(const Arguments& args);
	static Handle<Value> importExtraData(const Arguments& args);
	static Handle<Value> resolvePointers(const Arguments& args);
	//static Handle<Value> getClassName(const Arguments& args);
	//static Handle<Value> isKindOf(const Arguments& args);
	static Handle<Value> registerNameForExport(const Arguments& args);
	/*static Handle<Value> enableInScene(const Arguments& args);
	static Handle<Value> disableInScene(const Arguments& args);
	static Handle<Value> isInScene(const Arguments& args);
	static Handle<Value> disableAutoResolve(const Arguments& args);
	static Handle<Value> enableAutoResolve(const Arguments& args);
	static Handle<Value> isAutoResolveDisabled(const Arguments& args);
	static Handle<Value> disableFields(const Arguments& args);
	static Handle<Value> enableFields(const Arguments& args);
	static Handle<Value> areFieldsDisabled(const Arguments& args);*/
	//static Handle<Value> setOwnsMemory(const Arguments& args);
	//static Handle<Value> clearOwnsMemory(const Arguments& args);
	//static Handle<Value> ownsMemory(const Arguments& args);
	//static Handle<Value> getAddress(const Arguments& args);
	//static Handle<Value> getSerialType(const Arguments& args);
	//static Handle<Value> getMetaData(const Arguments& args);
};

class V8PxRefResolver : public BaseV8TemplateObject<V8PxRefResolver>{
public:
	//Functions
	static Handle<Value> newAddress(const Arguments& args);
	static Handle<Value> setNewAddress(const Arguments& args);
};

class V8PxUserReferences : public BaseV8TemplateObject<V8PxUserReferences>{
public:
	//Functions
	static Handle<Value> getObjectFromID(const Arguments& args);
	static Handle<Value> setUserData(const Arguments& args);
};

class V8PxCollection : public BaseV8TemplateObject<V8PxCollection>{
public:
	//Functions
	static Handle<Value> serialize(const Arguments& args);
	static Handle<Value> deserialize(const Arguments& args);
	static Handle<Value> setUserData(const Arguments& args);
	static Handle<Value> addExternalRef(const Arguments& args);
	static Handle<Value> getNbObjects(const Arguments& args);
	static Handle<Value> getObject(const Arguments& args);
};


class V8PxVec2 : public BaseV8TemplateObject<V8PxVec2>{
public:
	//boost::any Class(PxVec2);

	static Handle<Value> PxVec2Constructor(const Arguments& args);

	//Accessors
	static Handle<Value> getX( Local<v8::String> property, const AccessorInfo& info );
	static void setX( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getY( Local<v8::String> property, const AccessorInfo& info );
	static void setY( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Interceptors
	static Handle<Value> elementGet(uint32_t index, const AccessorInfo& info);
	static Handle<Value> elementSet(uint32_t index, Local<Value> value, const AccessorInfo& info);

	//Functions
	static Handle<Value> compare(const Arguments& args);
	static Handle<Value> acompare(const Arguments& args);
	static Handle<Value> isZero(const Arguments& args);
	static Handle<Value> isFinite(const Arguments& args);
	static Handle<Value> isNormalized(const Arguments& args);
	static Handle<Value> magnitudeSquared(const Arguments& args);
	static Handle<Value> magnitude(const Arguments& args);
	static Handle<Value> negate(const Arguments& args);
	static Handle<Value> add(const Arguments& args);
	static Handle<Value> subtract(const Arguments& args);
	static Handle<Value> multiply(const Arguments& args);
	static Handle<Value> divide(const Arguments& args);

	static Handle<Value> assignmentAdd(const Arguments& args);
	static Handle<Value> assignmentSubtract(const Arguments& args);
	static Handle<Value> assignmentMultiply(const Arguments& args);
	static Handle<Value> assignmentDivide(const Arguments& args);

	static Handle<Value> dot(const Arguments& args);
	static Handle<Value> getNormalized(const Arguments& args);
	static Handle<Value> normalize(const Arguments& args);
	static Handle<Value> min(const Arguments& args);
	static Handle<Value> max(const Arguments& args);

	static Handle<Value> elementwiseMultiply(const Arguments& args);
	static Handle<Value> elementwiseMin(const Arguments& args);
	static Handle<Value> elementwiseMax(const Arguments& args);	
};

class V8PxVec3 : public BaseV8TemplateObject<V8PxVec3>{
public:
	static Handle<Value> PxVec3Constructor(const Arguments& args);

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
	static Handle<Value> isZero(const Arguments& args);
	static Handle<Value> isFinite(const Arguments& args);
	static Handle<Value> isNormalized(const Arguments& args);
	static Handle<Value> magnitudeSquared(const Arguments& args);
	static Handle<Value> magnitude(const Arguments& args);
	static Handle<Value> negate(const Arguments& args);
	static Handle<Value> add(const Arguments& args);
	static Handle<Value> subtract(const Arguments& args);
	static Handle<Value> multiply(const Arguments& args);
	static Handle<Value> divide(const Arguments& args);

	static Handle<Value> assignmentAdd(const Arguments& args);
	static Handle<Value> assignmentSubtract(const Arguments& args);
	static Handle<Value> assignmentMultiply(const Arguments& args);
	static Handle<Value> assignmentDivide(const Arguments& args);

	static Handle<Value> dot(const Arguments& args);
	static Handle<Value> cross(const Arguments& args);
	static Handle<Value> getNormalized(const Arguments& args);
	static Handle<Value> normalize(const Arguments& args);
	static Handle<Value> min(const Arguments& args);
	static Handle<Value> max(const Arguments& args);

	static Handle<Value> elementwiseMultiply(const Arguments& args);
	static Handle<Value> elementwiseMin(const Arguments& args);
	static Handle<Value> elementwiseMax(const Arguments& args);	
};

class V8PxExtendedVec3 : public BaseV8TemplateObject<V8PxExtendedVec3>{
public:
	static Handle<Value> PxExtendedVec3Constructor(const Arguments& args);

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
	static Handle<Value> isZero(const Arguments& args);
	static Handle<Value> isFinite(const Arguments& args);
	static Handle<Value> magnitudeSquared(const Arguments& args);
	static Handle<Value> magnitude(const Arguments& args);
	static Handle<Value> negate(const Arguments& args);
	static Handle<Value> add(const Arguments& args);
	static Handle<Value> subtract(const Arguments& args);

	static Handle<Value> assignmentAdd(const Arguments& args);
	static Handle<Value> assignmentSubtract(const Arguments& args);
	static Handle<Value> assignmentMultiply(const Arguments& args);

	static Handle<Value> dot(const Arguments& args);
	static Handle<Value> cross(const Arguments& args);
	static Handle<Value> normalize(const Arguments& args);
	static Handle<Value> min(const Arguments& args);
	static Handle<Value> max(const Arguments& args);

	static Handle<Value> set(const Arguments& args);
	static Handle<Value> setPlusInfinity(const Arguments& args);
	static Handle<Value> setMinusInfinity(const Arguments& args);

};

class V8PxVec4 : public BaseV8TemplateObject<V8PxVec4>{
public:
	static Handle<Value> PxVec4Constructor(const Arguments& args);

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
	static Handle<Value> compare(const Arguments& args);
	static Handle<Value> acompare(const Arguments& args);
	static Handle<Value> isZero(const Arguments& args);
	static Handle<Value> isFinite(const Arguments& args);
	static Handle<Value> isNormalized(const Arguments& args);
	static Handle<Value> magnitudeSquared(const Arguments& args);
	static Handle<Value> magnitude(const Arguments& args);
	static Handle<Value> negate(const Arguments& args);
	static Handle<Value> add(const Arguments& args);
	static Handle<Value> subtract(const Arguments& args);
	static Handle<Value> multiply(const Arguments& args);
	static Handle<Value> divide(const Arguments& args);

	static Handle<Value> assignmentAdd(const Arguments& args);
	static Handle<Value> assignmentSubtract(const Arguments& args);
	static Handle<Value> assignmentMultiply(const Arguments& args);
	static Handle<Value> assignmentDivide(const Arguments& args);

	static Handle<Value> dot(const Arguments& args);
	static Handle<Value> getNormalized(const Arguments& args);
	static Handle<Value> normalize(const Arguments& args);

	static Handle<Value> elementwiseMultiply(const Arguments& args);
	static Handle<Value> elementwiseMin(const Arguments& args);
	static Handle<Value> elementwiseMax(const Arguments& args);	

	static Handle<Value> getXYZ(const Arguments& args);
	static Handle<Value> setZero(const Arguments& args);
};

class V8PxQuat : public BaseV8TemplateObject<V8PxQuat>{
public:
	static Handle<Value> PxQuatConstructor(const Arguments& args);

	//Accessors
	static Handle<Value> getX( Local<v8::String> property, const AccessorInfo& info );
	static void setX( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getY( Local<v8::String> property, const AccessorInfo& info );
	static void setY( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getZ( Local<v8::String> property, const AccessorInfo& info );
	static void setZ( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getW( Local<v8::String> property, const AccessorInfo& info );
	static void setW( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Functions
	static Handle<Value> isFinite(const Arguments& args);
	//static Handle<Value> isValid(const Arguments& args);
	static Handle<Value> isSane(const Arguments& args);
	static Handle<Value> toRadiansAndUnitAxis(const Arguments& args);
	static Handle<Value> getAngle(const Arguments& args);
	static Handle<Value> magnitudeSquared(const Arguments& args);
	
	static Handle<Value> dot(const Arguments& args);
	static Handle<Value> getNormalized(const Arguments& args);
	static Handle<Value> magnitude(const Arguments& args);
	static Handle<Value> normalize(const Arguments& args);
	static Handle<Value> getConjugate(const Arguments& args);
	static Handle<Value> getImaginaryPart(const Arguments& args);
	static Handle<Value> getBasisVector0(const Arguments& args);
	static Handle<Value> getBasisVector1(const Arguments& args);
	static Handle<Value> getBasisVector2(const Arguments& args);
	static Handle<Value> rotate(const Arguments& args);
	static Handle<Value> rotateInv(const Arguments& args);

	static Handle<Value> assignmentAdd(const Arguments& args);
	static Handle<Value> assignmentSubtract(const Arguments& args);
	static Handle<Value> assignmentMultiply(const Arguments& args);
	static Handle<Value> add(const Arguments& args);
	static Handle<Value> subtract(const Arguments& args);
	static Handle<Value> multiply(const Arguments& args);
	static Handle<Value> negate(const Arguments& args);

	static Handle<Value> createIdentity(const Arguments& args);
};

class V8PxMat33 : public BaseV8TemplateObject<V8PxMat33>{
public:
	static Handle<Value> PxMat33Constructor(const Arguments& args);

	//Interceptors
	static Handle<Value> elementGet(uint32_t index, const AccessorInfo& info);
	static Handle<Value> elementSet(uint32_t index, Local<Value> value, const AccessorInfo& info);

	//Functions
	static Handle<Value> createIdentity(const Arguments& args);
	static Handle<Value> createZero(const Arguments& args);
	static Handle<Value> createDiagonal(const Arguments& args);

	static Handle<Value> getTranspose(const Arguments& args);
	static Handle<Value> getInverse(const Arguments& args);
	static Handle<Value> getDeterminant(const Arguments& args);
	static Handle<Value> transform(const Arguments& args);
	static Handle<Value> transformTranspose(const Arguments& args);

	static Handle<Value> assignmentAdd(const Arguments& args);
	static Handle<Value> assignmentSubtract(const Arguments& args);
	static Handle<Value> assignmentMultiply(const Arguments& args);
	static Handle<Value> add(const Arguments& args);
	static Handle<Value> subtract(const Arguments& args);
	static Handle<Value> multiply(const Arguments& args);
	static Handle<Value> negate(const Arguments& args);
};

class V8PxMat44 : public BaseV8TemplateObject<V8PxMat44>{
public:
	static Handle<Value> PxMat44Constructor(const Arguments& args);

	//Interceptors
	static Handle<Value> elementGet(uint32_t index, const AccessorInfo& info);
	static Handle<Value> elementSet(uint32_t index, Local<Value> value, const AccessorInfo& info);

	//Functions
	static Handle<Value> createIdentity(const Arguments& args);
	static Handle<Value> createZero(const Arguments& args);

	static Handle<Value> getTranspose(const Arguments& args);
	static Handle<Value> transform(const Arguments& args);
	static Handle<Value> rotate(const Arguments& args);
	static Handle<Value> getBasis(const Arguments& args);
	static Handle<Value> getPosition(const Arguments& args);
	static Handle<Value> setPosition(const Arguments& args);
	static Handle<Value> scale(const Arguments& args);
	static Handle<Value> inverseRT(const Arguments& args);
	static Handle<Value> isFinite(const Arguments& args);

	static Handle<Value> assignmentAdd(const Arguments& args);
	static Handle<Value> assignmentSubtract(const Arguments& args);
	static Handle<Value> assignmentMultiply(const Arguments& args);
	static Handle<Value> add(const Arguments& args);
	static Handle<Value> subtract(const Arguments& args);
	static Handle<Value> multiply(const Arguments& args);
	static Handle<Value> negate(const Arguments& args);
};

class V8PxTransform : public BaseV8TemplateObject<V8PxTransform>{
public:
	static Handle<Value> PxTransformConstructor(const Arguments& args);

	//Accessors
	static Handle<Value> getQ( Local<v8::String> property, const AccessorInfo& info );
	static void setQ( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getP( Local<v8::String> property, const AccessorInfo& info );
	static void setP( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Functions
	static Handle<Value> createIdentity(const Arguments& args);

	static Handle<Value> getInverse(const Arguments& args);
	static Handle<Value> transform(const Arguments& args);
	static Handle<Value> transformInv(const Arguments& args);
	static Handle<Value> rotate(const Arguments& args);
	static Handle<Value> rotateInv(const Arguments& args);

	static Handle<Value> isValid(const Arguments& args);
	static Handle<Value> isSane(const Arguments& args);
	static Handle<Value> isFinite(const Arguments& args);

	static Handle<Value> multiply(const Arguments& args);

};
class V8PxBounds3 : public BaseV8TemplateObject<V8PxBounds3>{
public:
	static Handle<Value> PxBounds3Constructor(const Arguments& args);

	//Accessors
	static Handle<Value> getMin( Local<v8::String> property, const AccessorInfo& info );
	static void setMin( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getMax( Local<v8::String> property, const AccessorInfo& info );
	static void setMax( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Static
	static Handle<Value> empty(const Arguments& args);
	static Handle<Value> boundsOfPoints(const Arguments& args);
	static Handle<Value> centerExtents(const Arguments& args);
	static Handle<Value> basisExtent(const Arguments& args);
	static Handle<Value> poseExtent(const Arguments& args);
	static Handle<Value> transform(const Arguments& args);

	//Functions
	static Handle<Value> setEmpty(const Arguments& args);
	static Handle<Value> setInfinite(const Arguments& args);
	static Handle<Value> include(const Arguments& args);
	static Handle<Value> isEmpty(const Arguments& args);
	static Handle<Value> intersects(const Arguments& args);
	static Handle<Value> intersects1D(const Arguments& args);
	static Handle<Value> contains(const Arguments& args);
	static Handle<Value> isInside(const Arguments& args);
	static Handle<Value> getCenter(const Arguments& args);
	static Handle<Value> getExtents(const Arguments& args);
	static Handle<Value> getDimensions(const Arguments& args);
	static Handle<Value> scale(const Arguments& args);
	static Handle<Value> fatten(const Arguments& args);
	static Handle<Value> isFinite(const Arguments& args);
};

class V8PxShape : public BaseV8TemplateObject<V8PxShape>{
public:
	//Accessors
	static Handle<Value> getUserData( Local<v8::String> property, const AccessorInfo& info );
	static void setUserData( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Functions
	static Handle<Value> release( const Arguments& args );
	static Handle<Value> getGeometryType( const Arguments& args );
	static Handle<Value> setGeometry( const Arguments& args );
	static Handle<Value> getBoxGeometry( const Arguments& args );
	static Handle<Value> getSphereGeometry( const Arguments& args );
	static Handle<Value> getCapsuleGeometry( const Arguments& args );
	static Handle<Value> getPlaneGeometry( const Arguments& args );
	static Handle<Value> getConvexMeshGeometry( const Arguments& args );
	static Handle<Value> getTriangleMeshGeometry( const Arguments& args );
	static Handle<Value> getHeightFieldGeometry( const Arguments& args );
	static Handle<Value> getActor( const Arguments& args );
	static Handle<Value> getWorldBounds( const Arguments& args );
	static Handle<Value> setLocalPose( const Arguments& args );
	static Handle<Value> getLocalPose( const Arguments& args );
	static Handle<Value> setSimulationFilterData( const Arguments& args );
	static Handle<Value> getSimulationFilterData( const Arguments& args );
	static Handle<Value> resetFiltering( const Arguments& args );
	static Handle<Value> setQueryFilterData( const Arguments& args );
	static Handle<Value> getQueryFilterData( const Arguments& args );
	static Handle<Value> setMaterials( const Arguments& args );
	static Handle<Value> getNbMaterials( const Arguments& args );
	static Handle<Value> getMaterials( const Arguments& args );
	static Handle<Value> getMaterialFromInternalFaceIndex( const Arguments& args );
	static Handle<Value> setContactOffset( const Arguments& args );
	static Handle<Value> getContactOffset( const Arguments& args );
	static Handle<Value> setRestOffset( const Arguments& args );
	static Handle<Value> getRestOffset( const Arguments& args );
	static Handle<Value> setFlag( const Arguments& args );
	static Handle<Value> setFlags( const Arguments& args );
	static Handle<Value> getFlags( const Arguments& args );
	static Handle<Value> setName( const Arguments& args );
	static Handle<Value> getName( const Arguments& args );
};

class V8PxControllerShapeHit : public BaseV8TemplateObject<V8PxControllerShapeHit>{
public:
	//Functions
	static Handle<Value> getController( const Arguments& args );
	static Handle<Value> getShape( const Arguments& args );
	static Handle<Value> getWorldPose( const Arguments& args );
	static Handle<Value> getWorldNormal( const Arguments& args );
	static Handle<Value> getDirection( const Arguments& args );
	static Handle<Value> getLength( const Arguments& args );
};

class V8PxControllersHit : public BaseV8TemplateObject<V8PxControllersHit>{
public:
	//Functions
	static Handle<Value> getController( const Arguments& args );
	static Handle<Value> getOther( const Arguments& args );
};

template <int SIZE>
class V8PxPadding : public BaseV8TemplateObject<V8PxPadding<SIZE>>{
public:
	static Handle<Value> PxPaddingConstructor(const Arguments& args);

	//Accessors
	static Handle<Value> getSize( Local<v8::String> property, const AccessorInfo& info );

	//Interceptors
	static Handle<Value> elementGet(uint32_t index, const AccessorInfo& info);
	static Handle<Value> elementSet(uint32_t index, Local<Value> value, const AccessorInfo& info);
//private:
	//int size;
};

class V8PxGeometry : public BaseV8TemplateObject<V8PxGeometry>{
public:
	//Functions
	static Handle<Value> getType( const Arguments& args );
};

class V8PxBoxGeometry : public BaseV8TemplateObject<V8PxBoxGeometry>{
public:
	static Handle<Value> PxBoxGeometryConstructor(const Arguments& args);

	//Accessors
	static Handle<Value> getHalfExtents( Local<v8::String> property, const AccessorInfo& info );
	static void setHalfExtents( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Functions
	static Handle<Value> isValid( const Arguments& args );
};

class V8PxCapsuleGeometry : public BaseV8TemplateObject<V8PxCapsuleGeometry>{
public:
	static Handle<Value> PxCapsuleGeometryConstructor(const Arguments& args);

	//Accessors
	static Handle<Value> getRadius( Local<v8::String> property, const AccessorInfo& info );
	static void setRadius( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getHalfHeight( Local<v8::String> property, const AccessorInfo& info );
	static void setHalfHeight( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Functions
	static Handle<Value> isValid( const Arguments& args );
};

class V8PxConvexMeshGeometry : public BaseV8TemplateObject<V8PxConvexMeshGeometry>{
public:
	static Handle<Value> PxConvexMeshGeometryConstructor(const Arguments& args);

	//Accessors
	static Handle<Value> getScale( Local<v8::String> property, const AccessorInfo& info );
	static void setScale( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getConvexMesh( Local<v8::String> property, const AccessorInfo& info );
	static void setConvexMesh( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Functions
	static Handle<Value> isValid( const Arguments& args );
};

class V8PxHeightFieldGeometry : public BaseV8TemplateObject<V8PxHeightFieldGeometry>{
public:
	static Handle<Value> PxHeightFieldGeometryConstructor(const Arguments& args);

	//Accessors
	static Handle<Value> getHeightField( Local<v8::String> property, const AccessorInfo& info );
	static void setHeightField( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getHeightScale( Local<v8::String> property, const AccessorInfo& info );
	static void setHeightScale( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getRowScale( Local<v8::String> property, const AccessorInfo& info );
	static void setRowScale( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getColumnScale( Local<v8::String> property, const AccessorInfo& info );
	static void setColumnScale( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getHeightFeildFlags( Local<v8::String> property, const AccessorInfo& info );
	static void setHeightFieldFlags( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getPaddingFromFlags( Local<v8::String> property, const AccessorInfo& info );
	static void setPaddingFromFlags( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Functions
	static Handle<Value> isValid( const Arguments& args );
};

class V8PxSphereGeometry : public BaseV8TemplateObject<V8PxSphereGeometry>{
public:
	static Handle<Value> PxSphereGeometryConstructor(const Arguments& args);

	//Accessors
	static Handle<Value> getRadius( Local<v8::String> property, const AccessorInfo& info );
	static void setRadius( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Functions
	static Handle<Value> isValid( const Arguments& args );
};

class V8PxPlaneGeometry : public BaseV8TemplateObject<V8PxPlaneGeometry>{
public:
	static Handle<Value> PxPlaneGeometryConstructor(const Arguments& args);

	//Functions
	static Handle<Value> isValid( const Arguments& args );
};

class V8PxTriangleMeshGeometry : public BaseV8TemplateObject<V8PxTriangleMeshGeometry>{
public:
	static Handle<Value> PxTriangleMeshGeometryConstructor(const Arguments& args);

	//Accessors
	static Handle<Value> getScale( Local<v8::String> property, const AccessorInfo& info );
	static void setScale( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getMeshFlags( Local<v8::String> property, const AccessorInfo& info );
	static void setMeshFlags( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getPaddingFromFlags( Local<v8::String> property, const AccessorInfo& info );
	static void setPaddingFromFlags( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getTriangleMesh( Local<v8::String> property, const AccessorInfo& info );
	static void setTriangleMesh( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Functions
	static Handle<Value> isValid( const Arguments& args );
};

class V8PxTriangleMesh : public BaseV8TemplateObject<V8PxTriangleMesh>{
public:
	//Functions
	static Handle<Value> getNbVertices( const Arguments& args );
	static Handle<Value> getVertices( const Arguments& args );
	static Handle<Value> getNbTriangles( const Arguments& args );
	static Handle<Value> getTriangles( const Arguments& args );
	static Handle<Value> has16BitTriangleIndices( const Arguments& args );
	static Handle<Value> getTrianglesRemap( const Arguments& args );
	static Handle<Value> release( const Arguments& args );
	static Handle<Value> getTriangleMaterialIndex( const Arguments& args );
	static Handle<Value> getReferenceCount( const Arguments& args );
};

class V8PxFieldDescriptor : public BaseV8TemplateObject<V8PxFieldDescriptor>{
public:
	//Accessors
	static Handle<Value> getType( Local<v8::String> property, const AccessorInfo& info );
	static void setType( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getName( Local<v8::String> property, const AccessorInfo& info );
	//static void setName( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getOffset( Local<v8::String> property, const AccessorInfo& info );
	static void setOffset( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getSize( Local<v8::String> property, const AccessorInfo& info );
	static void setSize( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getCount( Local<v8::String> property, const AccessorInfo& info );
	static void setCount( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getOffsetSize( Local<v8::String> property, const AccessorInfo& info );
	static void setOffsetSize( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getFlags( Local<v8::String> property, const AccessorInfo& info );
	static void setFlags( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Functions
	//static Handle<Value> FieldSize( const Arguments& args );
	static Handle<Value> Address( const Arguments& args );
	static Handle<Value> GetArrayAddress( const Arguments& args );
	static Handle<Value> IsStaticArray( const Arguments& args );
	static Handle<Value> GetStaticArraySize( const Arguments& args );
	static Handle<Value> IsDynamicArray( const Arguments& args );
	static Handle<Value> GetDynamicArraySize( const Arguments& args );
};

class V8PxSerialStream : public BaseV8TemplateObject<V8PxSerialStream>{
public:
	//Functions
	//static Handle<Value> storeBuffer( const Arguments& args );
	//static Handle<Value> getTotalStoredSize( const Arguments& args );
};

class V8PxMeshScale : public BaseV8TemplateObject<V8PxMeshScale>{
public:
	static Handle<Value> PxMeshScaleConstructor(const Arguments& args);

	//Accessors
	static Handle<Value> getScale( Local<v8::String> property, const AccessorInfo& info );
	static void setScale( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getRotation( Local<v8::String> property, const AccessorInfo& info );
	static void setRotation( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Functions
	static Handle<Value> createIdentity( const Arguments& args );

	static Handle<Value> isIdentity( const Arguments& args );
	static Handle<Value> getInverse( const Arguments& args );
	static Handle<Value> toMat33( const Arguments& args );
};

class V8PxConvexMesh : public BaseV8TemplateObject<V8PxConvexMesh>{
public:
	//Functions
	static Handle<Value> getNbVertices( const Arguments& args );
	static Handle<Value> getVertices( const Arguments& args );
	static Handle<Value> getIndexBuffer( const Arguments& args );
	static Handle<Value> getNbPolygons( const Arguments& args );
	static Handle<Value> getPolygonData( const Arguments& args );
	static Handle<Value> release( const Arguments& args );
	static Handle<Value> getReferenceCount( const Arguments& args );
	static Handle<Value> getMassInformation( const Arguments& args );
};

class V8PxHeightField : public BaseV8TemplateObject<V8PxHeightField>{
public:
	//Functions
	static Handle<Value> release( const Arguments& args );
	static Handle<Value> saveCells( const Arguments& args );
	static Handle<Value> getNbRows( const Arguments& args );
	static Handle<Value> getNbColumns( const Arguments& args );
	static Handle<Value> getFormat( const Arguments& args );
	static Handle<Value> getSampleStride( const Arguments& args );
	static Handle<Value> getThickness( const Arguments& args );
	static Handle<Value> getConvexEdgeThreshold( const Arguments& args );
	static Handle<Value> getFlags( const Arguments& args );
	static Handle<Value> getHeight( const Arguments& args );
	static Handle<Value> getReferenceCount( const Arguments& args );
	static Handle<Value> getTriangleMaterialIndex( const Arguments& args );
};

class V8PxFilterData : public BaseV8TemplateObject<V8PxFilterData>{
public:
	static Handle<Value> PxFilterDataConstructor(const Arguments& args);

	//Accessors
	static Handle<Value> getword0( Local<v8::String> property, const AccessorInfo& info );
	static void setword0( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getword1( Local<v8::String> property, const AccessorInfo& info );
	static void setword1( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getword2( Local<v8::String> property, const AccessorInfo& info );
	static void setword2( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getword3( Local<v8::String> property, const AccessorInfo& info );
	static void setword3( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Functions
	static Handle<Value> setToDefault( const Arguments& args );

};

class V8PxHullPolygon : public BaseV8TemplateObject<V8PxHullPolygon>{
public:
	static Handle<Value> PxHullPolygonConstructor(const Arguments& args);

	//Accessors
	static Handle<Value> getmPlane( Local<v8::String> property, const AccessorInfo& info );
	//static void setmPlane( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getmNbVerts( Local<v8::String> property, const AccessorInfo& info );
	static void setmNbVerts( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getmIndexBase( Local<v8::String> property, const AccessorInfo& info );
	static void setmIndexBase( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
};

class V8PxMaterial : public BaseV8TemplateObject<V8PxMaterial>{
public:
	//Accessors
	static Handle<Value> getUserData( Local<v8::String> property, const AccessorInfo& info );
	static void setUserData( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Functions
	static Handle<Value> release( const Arguments& args );
	static Handle<Value> setDynamicFriction( const Arguments& args );
	static Handle<Value> getDynamicFriction( const Arguments& args );
	static Handle<Value> setStaticFriction( const Arguments& args );
	static Handle<Value> getStaticFriction( const Arguments& args );
	static Handle<Value> setRestitution( const Arguments& args );
	static Handle<Value> getRestitution( const Arguments& args );
	/*static Handle<Value> setDynamicFrictionV( const Arguments& args );
	static Handle<Value> getDynamicFrictionV( const Arguments& args );
	static Handle<Value> setStaticFrictionV( const Arguments& args );
	static Handle<Value> getStaticFrictionV( const Arguments& args );
	static Handle<Value> setDirOfAnisotropy( const Arguments& args );
	static Handle<Value> getDirOfAnisotropy( const Arguments& args );*/
	static Handle<Value> setFlag( const Arguments& args );
	static Handle<Value> setFlags( const Arguments& args );
	static Handle<Value> getFlags( const Arguments& args );
	static Handle<Value> setFrictionCombineMode( const Arguments& args );
	static Handle<Value> getFrictionCombineMode( const Arguments& args );
	static Handle<Value> setRestitutionCombineMode( const Arguments& args );
	static Handle<Value> getRestitutionCombineMode( const Arguments& args );
};

class V8PxObserver : public BaseV8TemplateObject<V8PxObserver>{
public:
	//Functions
	static Handle<Value> onRelease( const Arguments& args );
};

class V8PxObservable : public BaseV8TemplateObject<V8PxObservable>{
public:
	//Functions
	static Handle<Value> getObservableType( const Arguments& args );
	static Handle<Value> registerObserver( const Arguments& args );
	static Handle<Value> unregisterObserver( const Arguments& args );
	static Handle<Value> getNbObservers( const Arguments& args );
	static Handle<Value> getObservers( const Arguments& args );
};

class V8PxActor : public BaseV8TemplateObject<V8PxActor>{
public:
	//Accessors
	static Handle<Value> getUserData( Local<v8::String> property, const AccessorInfo& info );
	static void setUserData( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Functions
	static Handle<Value> release( const Arguments& args );
	static Handle<Value> getType( const Arguments& args );
	//static Handle<Value> is( const Arguments& args );
	static Handle<Value> isRigidStatic( const Arguments& args );
	static Handle<Value> isRigidDynamic( const Arguments& args );
	static Handle<Value> isParticleSystem( const Arguments& args );
	static Handle<Value> isParticleFluid( const Arguments& args );
	//static Handle<Value> isDeformable( const Arguments& args );
	static Handle<Value> isArticulationLink( const Arguments& args );
	static Handle<Value> isRigidActor( const Arguments& args );
	static Handle<Value> isRigidBody( const Arguments& args );
	static Handle<Value> isParticleBase( const Arguments& args );
	static Handle<Value> getScene( const Arguments& args );
	static Handle<Value> setName( const Arguments& args );
	static Handle<Value> getName( const Arguments& args );
	static Handle<Value> getWorldBounds( const Arguments& args );
	static Handle<Value> setActorFlag( const Arguments& args );
	static Handle<Value> setActorFlags( const Arguments& args );
	static Handle<Value> getActorFlags( const Arguments& args );
	static Handle<Value> setDominanceGroup( const Arguments& args );
	static Handle<Value> getDominanceGroup( const Arguments& args );
	static Handle<Value> setOwnerClient( const Arguments& args );
	static Handle<Value> getOwnerClient( const Arguments& args );
	static Handle<Value> setClientBehaviorBits( const Arguments& args );
	static Handle<Value> getClientBehaviorBits( const Arguments& args );
	static Handle<Value> getAggregate( const Arguments& args );
};

class V8PxRigidActor : public BaseV8TemplateObject<V8PxRigidActor>{
public:
	//Functions
	static Handle<Value> release( const Arguments& args );
	static Handle<Value> getGlobalPose( const Arguments& args );
	static Handle<Value> setGlobalPose( const Arguments& args );
	static Handle<Value> createShape( const Arguments& args );
	static Handle<Value> getNbShapes( const Arguments& args );
	static Handle<Value> getShapes( const Arguments& args );
	static Handle<Value> getNbConstraints( const Arguments& args );
	static Handle<Value> getConstraints( const Arguments& args );
	static Handle<Value> isRigidActor( const Arguments& args );
};

class V8PxRigidBody : public BaseV8TemplateObject<V8PxRigidBody>{
public:
	//Functions
	static Handle<Value> setCMassLocalPose( const Arguments& args );
	static Handle<Value> getCMassLocalPose( const Arguments& args );
	static Handle<Value> setMass( const Arguments& args );
	static Handle<Value> getMass( const Arguments& args );
	static Handle<Value> setMassSpaceInertiaTensor( const Arguments& args );
	static Handle<Value> getMassSpaceInertiaTensor( const Arguments& args );
	static Handle<Value> getLinearVelocity( const Arguments& args );
	static Handle<Value> setLinearVelocity( const Arguments& args );
	static Handle<Value> getAngularVelocity( const Arguments& args );
	static Handle<Value> setAngularVelocity( const Arguments& args );
	static Handle<Value> addForce( const Arguments& args );
	static Handle<Value> addTorque( const Arguments& args );
	static Handle<Value> clearForce( const Arguments& args );
	static Handle<Value> clearTorque( const Arguments& args );
	static Handle<Value> isRigidBody( const Arguments& args );
};

class V8PxParticleBase : public BaseV8TemplateObject<V8PxParticleBase>{
public:
	//Functions
	static Handle<Value> lockParticleReadData( const Arguments& args );
	static Handle<Value> createParticles( const Arguments& args );
	static Handle<Value> releaseParticles( const Arguments& args );
	static Handle<Value> setPositions( const Arguments& args );
	static Handle<Value> setVelocities( const Arguments& args );
	static Handle<Value> setRestOffsets( const Arguments& args );
	static Handle<Value> addForces( const Arguments& args );
	static Handle<Value> getDamping( const Arguments& args );
	static Handle<Value> setDamping( const Arguments& args );
	static Handle<Value> getExternalAcceleration( const Arguments& args );
	static Handle<Value> setExternalAcceleration( const Arguments& args );
	static Handle<Value> getProjectionPlane( const Arguments& args );
	static Handle<Value> setProjectionPlane( const Arguments& args );
	static Handle<Value> getParticleMass( const Arguments& args );
	static Handle<Value> setParticleMass( const Arguments& args );
	static Handle<Value> getRestitution( const Arguments& args );
	static Handle<Value> setRestitution( const Arguments& args );
	static Handle<Value> getDynamicFriction( const Arguments& args );
	static Handle<Value> setDynamicFriction( const Arguments& args );
	static Handle<Value> getStaticFriction( const Arguments& args );
	static Handle<Value> setStaticFriction( const Arguments& args );
	static Handle<Value> setSimulationFilterData( const Arguments& args );
	static Handle<Value> getSimulationFilterData( const Arguments& args );
	static Handle<Value> resetFiltering( const Arguments& args );
	static Handle<Value> setParticleBaseFlag( const Arguments& args );
	static Handle<Value> getParticleBaseFlags( const Arguments& args );
	static Handle<Value> getMaxParticles( const Arguments& args );
	static Handle<Value> getMaxMotionDistance( const Arguments& args );
	static Handle<Value> getRestOffset( const Arguments& args );
	static Handle<Value> getContactOffset( const Arguments& args );
	static Handle<Value> getGridSize( const Arguments& args );
	static Handle<Value> getParticleReadDataFlags( const Arguments& args );
	static Handle<Value> isParticleBase( const Arguments& args );
};

class V8PxLockedData : public BaseV8TemplateObject<V8PxLockedData>{
public:
	//Functions
	static Handle<Value> getDataAccessFlags( const Arguments& args );
	static Handle<Value> unlock( const Arguments& args );
};

template <class T>
class V8PxStrideIterator : public BaseV8TemplateObject<V8PxStrideIterator<T>>{
public:

	static void initTemplate(std::string className, Handle<FunctionTemplate>& base){
		HandleScope scope;
		Local<ObjectTemplate> objTemp;

		className = "PxStrideIterator<" + className + ">";

		getTemplate() = Persistent<FunctionTemplate>::New(FunctionTemplate::New());
		getTemplate()->SetClassName(String::New(className.c_str()));
		base->PrototypeTemplate()->Set(String::New(className.c_str()), getTemplate());

		getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);
	}

	static void initObject(Handle<Object> &obj, Handle<Object> &data){
		obj->Set(v8::String::New("handle"), FunctionTemplate::New(InvocationCallback(V8PxStrideIterator<T>::handle), data)->GetFunction());
		obj->Set(v8::String::New("unique"), FunctionTemplate::New(InvocationCallback(V8PxStrideIterator<T>::unique), data)->GetFunction());
		obj->Set(v8::String::New("stride"), FunctionTemplate::New(InvocationCallback(V8PxStrideIterator<T>::stride), data)->GetFunction());
		obj->Set(v8::String::New("next"), FunctionTemplate::New(InvocationCallback(V8PxStrideIterator<T>::next), data)->GetFunction());
		obj->Set(v8::String::New("prev"), FunctionTemplate::New(InvocationCallback(V8PxStrideIterator<T>::prev), data)->GetFunction());
		obj->Set(v8::String::New("jump"), FunctionTemplate::New(InvocationCallback(V8PxStrideIterator<T>::jump), data)->GetFunction());
	}

	//Functions
	//template<typename T>
	static Handle<Value> handle( const Arguments& args );

	//template<typename T>
	static Handle<Value> unique( const Arguments& args );

	static Handle<Value> stride( const Arguments& args );
	static Handle<Value> next( const Arguments& args );
	static Handle<Value> prev( const Arguments& args );
	static Handle<Value> jump( const Arguments& args );
};

class V8PxParticleReadData : public BaseV8TemplateObject<V8PxParticleReadData>{
public:
	//Accessors
	static Handle<Value> getNumValidParticles( Local<v8::String> property, const AccessorInfo& info );
	static void setNumValidParticles( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	static Handle<Value> getValidParticleRange( Local<v8::String> property, const AccessorInfo& info );
	static void setValidParticleRange( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	static Handle<Value> getValidParticleBitmap( Local<v8::String> property, const AccessorInfo& info );
	//static void setValidParticleBitmap( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	static Handle<Value> getPositionBuffer( Local<v8::String> property, const AccessorInfo& info );
	//static void setPositionBuffer( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	static Handle<Value> getVelocityBuffer( Local<v8::String> property, const AccessorInfo& info );
	//static void setVelocityBuffer( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	static Handle<Value> getRestOffsetBuffer( Local<v8::String> property, const AccessorInfo& info );
	//static void setRestOffsetBuffer( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	static Handle<Value> getFlagsBuffer( Local<v8::String> property, const AccessorInfo& info );
	//static void setFlagsBuffer( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	static Handle<Value> getCollisionNormalBuffer( Local<v8::String> property, const AccessorInfo& info );
	//static void setCollisionNormalBuffer( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );

	//Functions
	static Handle<Value> getDataAccessFlags( const Arguments& args );
	static Handle<Value> unlock( const Arguments& args );
};

class V8PxRigidDynamic : public BaseV8TemplateObject<V8PxRigidDynamic> {
public:
	//Functions
	static Handle<Value> setKinematicTarget( const Arguments& args );
	static Handle<Value> getKinematicTarget( const Arguments& args );
	static Handle<Value> setLinearDamping( const Arguments& args );
	static Handle<Value> getLinearDamping( const Arguments& args );
	static Handle<Value> setAngularDamping( const Arguments& args );
	static Handle<Value> getAngularDamping( const Arguments& args );
	static Handle<Value> setMaxAngularVelocity( const Arguments& args );
	static Handle<Value> getMaxAngularVelocity( const Arguments& args );
	static Handle<Value> isSleeping( const Arguments& args );
	static Handle<Value> setSleepThreshold( const Arguments& args );
	static Handle<Value> getSleepThreshold( const Arguments& args );
	static Handle<Value> wakeUp( const Arguments& args );
	static Handle<Value> putToSleep( const Arguments& args );
	static Handle<Value> setSolverIterationCounts( const Arguments& args );
	static Handle<Value> getSolverIterationCounts( const Arguments& args );
	static Handle<Value> getContactReportThreshold( const Arguments& args );
	static Handle<Value> setContactReportThreshold( const Arguments& args );
	static Handle<Value> setRigidDynamicFlag( const Arguments& args );
	static Handle<Value> setRigidDynamicFlags( const Arguments& args );
	static Handle<Value> getRigidDynamicFlags( const Arguments& args );
	static Handle<Value> getConcreteTypeName( const Arguments& args );
};

class V8PxRigidStatic : public BaseV8TemplateObject<V8PxRigidStatic> {
public:
	//Functions
	static Handle<Value> getConcreteTypeName( const Arguments& args );
};


//TODO: Finish this
class V8PxScene : public BaseV8TemplateObject<V8PxScene> {
public:
	//Functions
	static Handle<Value> release( const Arguments& args );
	//static Handle<Value> saveToDesc( const Arguments& args );
	static Handle<Value> setFlag( const Arguments& args );
	static Handle<Value> getFlags( const Arguments& args );
	static Handle<Value> setGravity( const Arguments& args );
	static Handle<Value> getGravity( const Arguments& args );
	//static Handle<Value> getPhysics( const Arguments& args );
	static Handle<Value> getTimestamp( const Arguments& args );
	static Handle<Value> getSceneQueryStaticTimestamp( const Arguments& args );
	static Handle<Value> setBounceThresholdVelocity( const Arguments& args );
	static Handle<Value> getBounceThresholdVelocity( const Arguments& args );
	//TODO: Userdata
	//static Handle<Value> simulate( const Arguments& args );
	//static Handle<Value> checkResults( const Arguments& args );
	//static Handle<Value> fetchResults( const Arguments& args );
	//static Handle<Value> flush( const Arguments& args );
	/*static Handle<Value> getTaskManager( const Arguments& args );
	static Handle<Value> setSolverBatchSize( const Arguments& args );
	static Handle<Value> getSolverBatchSize( const Arguments& args );
	static Handle<Value> setNbContactDataBlocks( const Arguments& args );
	static Handle<Value> getNbContactDataBlocksUsed( const Arguments& args );
	static Handle<Value> getMaxNbContactDataBlocksUsed( const Arguments& args );
	static Handle<Value> addArticulation( const Arguments& args );
	static Handle<Value> removeArticulation( const Arguments& args );*/
	static Handle<Value> addActor( const Arguments& args );
	//static Handle<Value> addActors( const Arguments& args );
	static Handle<Value> removeActor( const Arguments& args );
	//static Handle<Value> addAggregate( const Arguments& args );
	//static Handle<Value> removeAggregate( const Arguments& args );
	//static Handle<Value> getNbAggregates( const Arguments& args );
	//static Handle<Value> getAggregates( const Arguments& args );
	//static Handle<Value> setDominanceGroupPair( const Arguments& args );
	//static Handle<Value> getNbActors( const Arguments& args );
	//static Handle<Value> getActors( const Arguments& args );
	//static Handle<Value> getActiveTransforms( const Arguments& args );
	//static Handle<Value> getNbArticulations( const Arguments& args );
	//static Handle<Value> getArticulations( const Arguments& args );
	/*static Handle<Value> getNbConstraints( const Arguments& args );
	static Handle<Value> getConstraints( const Arguments& args );
	static Handle<Value> createClient( const Arguments& args );
	static Handle<Value> setClientBehaviorBits( const Arguments& args );
	static Handle<Value> getClientBehaviorBits( const Arguments& args );
	static Handle<Value> setSimulationEventCallback( const Arguments& args );
	static Handle<Value> getSimulationEventCallback( const Arguments& args );
	static Handle<Value> setContactModifyCallback( const Arguments& args );
	static Handle<Value> getContactModifyCallback( const Arguments& args );
	static Handle<Value> getFilterShaderData( const Arguments& args );
	static Handle<Value> getFilterShaderDataSize( const Arguments& args );
	static Handle<Value> getFilterShader( const Arguments& args );
	static Handle<Value> getFilterCallback( const Arguments& args );
	static Handle<Value> createBatchQuery( const Arguments& args );
	static Handle<Value> createSweepCache( const Arguments& args );
	static Handle<Value> setDynamicTreeRebuildRateHint( const Arguments& args );
	static Handle<Value> getDynamicTreeRebuildRateHint( const Arguments& args );*/

	static Handle<Value> raycastAny( const Arguments& args );
	static Handle<Value> raycastSingle( const Arguments& args );
	static Handle<Value> raycastMultiple( const Arguments& args );
	static Handle<Value> sweepAny( const Arguments& args );
	static Handle<Value> sweepSingle( const Arguments& args );
	static Handle<Value> sweepMultiple( const Arguments& args );
	static Handle<Value> overlapMultiple( const Arguments& args );
	static Handle<Value> overlapAny( const Arguments& args );

	/*static Handle<Value> setVisualizationParameter( const Arguments& args );
	static Handle<Value> getVisualizationParameter( const Arguments& args );
	static Handle<Value> setVisualizationCullingBox( const Arguments& args );
	static Handle<Value> getVisualizationCullingBox( const Arguments& args );
	static Handle<Value> getRenderBuffer( const Arguments& args );
	static Handle<Value> getSimulationStatistics( const Arguments& args );
	static Handle<Value> lockRead( const Arguments& args );
	static Handle<Value> unlockRead( const Arguments& args );
	static Handle<Value> lockWrite( const Arguments& args );
	static Handle<Value> unlockWrite( const Arguments& args );*/
};

class V8PxSceneQueryImpactHit : public BaseV8TemplateObject<V8PxSceneQueryImpactHit>{
public:
	//Functions
	static Handle<Value> getImpact( const Arguments& args );
	static Handle<Value> getNormal( const Arguments& args );
	static Handle<Value> getDistance( const Arguments& args );

};

class V8PxSceneQueryHit : public BaseV8TemplateObject<V8PxSceneQueryHit>{
public:
	//Functions
	static Handle<Value> getShape( const Arguments& args );
	static Handle<Value> getFaceIndex( const Arguments& args );
	static Handle<Value> getFlags( const Arguments& args );

};

class V8PxRaycastHit : public BaseV8TemplateObject<V8PxRaycastHit>{
public:
	//Functions
	static Handle<Value> getU( const Arguments& args );
	static Handle<Value> getV( const Arguments& args );
};

class V8PxControllerDesc : public BaseV8TemplateObject<V8PxControllerDesc>{
//public:
//	//static Handle<Value> PxControllerDescConstructor(const Arguments& args);
//
//	//Accessors
//	static Handle<Value> getPosition( Local<v8::String> property, const AccessorInfo& info );
//	static void setPosition( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
//
//	static Handle<Value> getUpDirection( Local<v8::String> property, const AccessorInfo& info );
//	static void setUpDirection( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
//
//	static Handle<Value> getSlopeLimit( Local<v8::String> property, const AccessorInfo& info );
//	static void setSlopeLimit( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
//
//	static Handle<Value> getContactOffset( Local<v8::String> property, const AccessorInfo& info );
//	static void setContactOffset( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
//
//	static Handle<Value> getStepOffset( Local<v8::String> property, const AccessorInfo& info );
//	static void setStepOffset( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
//
//	static Handle<Value> getCallback( Local<v8::String> property, const AccessorInfo& info );
//	static void setCallback( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
//
//	static Handle<Value> getInteractionMode( Local<v8::String> property, const AccessorInfo& info );
//	static void setInteractionMode( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
//
//	static Handle<Value> getMaterial( Local<v8::String> property, const AccessorInfo& info );
//	static void setMaterial( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
//
//	static Handle<Value> getUserData( Local<v8::String> property, const AccessorInfo& info );
//	static void setUserData( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
//
//	//Functions
//	//static Handle<Value> isValid(const Arguments& args);
//	static Handle<Value> getType(const Arguments& args);
};

class V8PxNameManager : public BaseV8TemplateObject<V8PxNameManager>{
};
class V8PxParticleCreationData : public BaseV8TemplateObject<V8PxParticleCreationData>{
};
class V8PxParticleSystem : public BaseV8TemplateObject<V8PxParticleSystem>{
};
class V8PxParticleFluid : public BaseV8TemplateObject<V8PxParticleFluid>{
};
class V8PxDeformable : public BaseV8TemplateObject<V8PxDeformable>{
};
class V8PxArticulationLink : public BaseV8TemplateObject<V8PxArticulationLink>{
};
class V8PxConstraint : public BaseV8TemplateObject<V8PxConstraint>{
};
class V8PxShapeDesc : public BaseV8TemplateObject<V8PxShapeDesc>{
};
class V8PxAggregate : public BaseV8TemplateObject<V8PxAggregate>{
};
class V8PxController : public BaseV8TemplateObject<V8PxController>{
};

class V8PhysX {
public:
	//V8PhysX();
	//virtual ~V8PhysX();

	static Local<FunctionTemplate> NewFunctionTemplate(InvocationCallback callback = 0, Handle<Value> data = Handle<Value>(), Handle<Signature> signature = Handle<Signature>());

	static Handle<Value> func_toVec3(const Arguments& args);

	static Handle<Value> func_math_max(const Arguments& args);
	static Handle<Value> func_math_min(const Arguments& args);
	static Handle<Value> func_math_abs(const Arguments& args);
	static Handle<Value> func_math_equals(const Arguments& args);
	static Handle<Value> func_math_clamp(const Arguments& args);
	static Handle<Value> func_math_sqrt(const Arguments& args);
	static Handle<Value> func_math_recipSqrt(const Arguments& args);
	static Handle<Value> func_math_sin(const Arguments& args);
	static Handle<Value> func_math_cos(const Arguments& args);
	static Handle<Value> func_math_tan(const Arguments& args);
	static Handle<Value> func_math_asin(const Arguments& args);
	static Handle<Value> func_math_acos(const Arguments& args);
	static Handle<Value> func_math_atan(const Arguments& args);
	static Handle<Value> func_math_atan2(const Arguments& args);
	static Handle<Value> func_math_isFinite(const Arguments& args);
	static Handle<Value> func_math_floor(const Arguments& args);
	static Handle<Value> func_math_exp(const Arguments& args);
	static Handle<Value> func_math_ceil(const Arguments& args);
	static Handle<Value> func_math_sign(const Arguments& args);
	static Handle<Value> func_math_pow(const Arguments& args);
	static Handle<Value> func_math_log(const Arguments& args);			

private:

};