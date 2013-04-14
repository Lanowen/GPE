#include <Scripting_ExposePx.hpp>

#include <iostream>

#include <Scripting_Helpers.hpp>
#include <V8Scripting.hpp>
//#include <Util.hpp>

//TODO: Change mallocs into new[]

using namespace physx;

Local<FunctionTemplate> V8PhysX::NewFunctionTemplate(InvocationCallback callback, Handle<Value> data, Handle<Signature> signature)
	{
		//HandleScope scope(Isolate::GetCurrent());

		Local<FunctionTemplate> physXFuncTemplateBase = FunctionTemplate::New();
		Local<FunctionTemplate> physXFuncTemplate = FunctionTemplate::New(); //used for enums
		Local<FunctionTemplate> temp;
		Local<FunctionTemplate> temp2;
		Local<ObjectTemplate> objTemp;

		physXFuncTemplate->SetClassName(String::New("PhysX"));
		physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PhysX"), physXFuncTemplate->InstanceTemplate());

		
		//Types
			//PxSerializable
				V8PxSerializable::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxSerializable::getTemplate()->SetClassName(String::New("PxSerializable"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxSerializable"), V8PxSerializable::getTemplate());

				objTemp = V8PxSerializable::getTemplate()->PrototypeTemplate();
				objTemp->SetInternalFieldCount(1);

				objTemp->Set(String::New("getOrder"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::getOrder )));
				objTemp->Set(String::New("collectForExport"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::collectForExport )));
				objTemp->Set(String::New("getFields"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::getFields )));
				objTemp->Set(String::New("getFieldDescriptor"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::getFieldDescriptor )));
				objTemp->Set(String::New("getObjectSize"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::getObjectSize )));
				objTemp->Set(String::New("exportExtraData"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::exportExtraData )));
				objTemp->Set(String::New("importExtraData"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::importExtraData )));
				objTemp->Set(String::New("resolvePointers"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::resolvePointers )));
				//objTemp->Set(String::New("getClassName"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::getClassName )));
				//objTemp->Set(String::New("isKindOf"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::isKindOf )));
				objTemp->Set(String::New("registerNameForExport"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::registerNameForExport )));
				/*objTemp->Set(String::New("enableInScene"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::enableInScene )));
				objTemp->Set(String::New("disableInScene"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::disableInScene )));
				objTemp->Set(String::New("isInScene"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::isInScene )));
				objTemp->Set(String::New("disableAutoResolve"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::disableAutoResolve )));
				objTemp->Set(String::New("enableAutoResolve"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::enableAutoResolve )));
				objTemp->Set(String::New("isAutoResolveDisabled"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::isAutoResolveDisabled )));
				objTemp->Set(String::New("disableFields"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::disableFields )));
				objTemp->Set(String::New("enableFields"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::enableFields )));
				objTemp->Set(String::New("areFieldsDisabled"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::areFieldsDisabled )));
				objTemp->Set(String::New("setOwnsMemory"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::setOwnsMemory )));
				objTemp->Set(String::New("clearOwnsMemory"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::clearOwnsMemory )));
				objTemp->Set(String::New("ownsMemory"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::ownsMemory )));*/
				//objTemp->Set(String::New("getAddress"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::getAddress )));
				//objTemp->Set(String::New("getSerialType"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::getSerialType )));

				//V8PxSerializable::getTemplate()->Set(String::New("getMetaData"), FunctionTemplate::New(InvocationCallback( V8PxSerializable::getMetaData )));

			//PxRefResolver
				V8PxRefResolver::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxRefResolver::getTemplate()->SetClassName(String::New("PxRefResolver"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxRefResolver"), V8PxRefResolver::getTemplate());

				objTemp = V8PxRefResolver::getTemplate()->PrototypeTemplate();
				V8PxRefResolver::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("newAddress"), FunctionTemplate::New(InvocationCallback( V8PxRefResolver::newAddress )));
				objTemp->Set(String::New("setNewAddress"), FunctionTemplate::New(InvocationCallback( V8PxRefResolver::setNewAddress )));

			//PxUserReferences
				V8PxUserReferences::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxUserReferences::getTemplate()->SetClassName(String::New("PxUserReferences"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxUserReferences"), V8PxUserReferences::getTemplate());

				objTemp = V8PxUserReferences::getTemplate()->PrototypeTemplate();
				V8PxUserReferences::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("getObjectFromID"), FunctionTemplate::New(InvocationCallback( V8PxUserReferences::getObjectFromID )));
				objTemp->Set(String::New("setUserData"), FunctionTemplate::New(InvocationCallback( V8PxUserReferences::setUserData )));

			//PxCollection
				V8PxCollection::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxCollection::getTemplate()->SetClassName(String::New("PxCollection"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxCollection"), V8PxCollection::getTemplate());

				objTemp = V8PxCollection::getTemplate()->PrototypeTemplate();
				V8PxCollection::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("serialize"), FunctionTemplate::New(InvocationCallback( V8PxCollection::serialize )));
				objTemp->Set(String::New("deserialize"), FunctionTemplate::New(InvocationCallback( V8PxCollection::deserialize )));
				objTemp->Set(String::New("setUserData"), FunctionTemplate::New(InvocationCallback( V8PxCollection::setUserData )));
				objTemp->Set(String::New("addExternalRef"), FunctionTemplate::New(InvocationCallback( V8PxCollection::addExternalRef )));
				objTemp->Set(String::New("getNbObjects"), FunctionTemplate::New(InvocationCallback( V8PxCollection::getNbObjects )));
				objTemp->Set(String::New("getObject"), FunctionTemplate::New(InvocationCallback( V8PxCollection::getObject )));

			//PxVec2
				V8PxVec2::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxVec2::PxVec2Constructor));
				V8PxVec2::getTemplate()->SetClassName(String::New("PxVec2"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxVec2"), V8PxVec2::getTemplate());

				objTemp = V8PxVec2::getTemplate()->PrototypeTemplate();
				V8PxVec2::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxVec2::getTemplate()->Set(String::New("createArray"), FunctionTemplate::New(InvocationCallback( createArray<PxVec2>::makeArray )));

				V8PxVec2::getTemplate()->InstanceTemplate()->SetAccessor(String::New("x"), V8PxVec2::getX, V8PxVec2::setX);
				V8PxVec2::getTemplate()->InstanceTemplate()->SetAccessor(String::New("y"), V8PxVec2::getY, V8PxVec2::setY);
				V8PxVec2::getTemplate()->InstanceTemplate()->SetIndexedPropertyHandler(V8PxVec2::elementGet, V8PxVec2::elementSet);

				objTemp->Set(String::New("compare"), FunctionTemplate::New(InvocationCallback( V8PxVec2::compare )));
				objTemp->Set(String::New("acompare"), FunctionTemplate::New(InvocationCallback( V8PxVec2::acompare )));
				objTemp->Set(String::New("isZero"), FunctionTemplate::New(InvocationCallback( V8PxVec2::isZero )));
				objTemp->Set(String::New("isFinite"), FunctionTemplate::New(InvocationCallback( V8PxVec2::isFinite )));
				objTemp->Set(String::New("isNormalized"), FunctionTemplate::New(InvocationCallback( V8PxVec2::isNormalized )));
				objTemp->Set(String::New("magnitudeSquared"), FunctionTemplate::New(InvocationCallback( V8PxVec2::magnitudeSquared )));
				objTemp->Set(String::New("magnitude"), FunctionTemplate::New(InvocationCallback( V8PxVec2::magnitude )));
				objTemp->Set(String::New("negate"), FunctionTemplate::New(InvocationCallback( V8PxVec2::negate )));
				objTemp->Set(String::New("add"), FunctionTemplate::New(InvocationCallback( V8PxVec2::add )));
				objTemp->Set(String::New("subtract"), FunctionTemplate::New(InvocationCallback( V8PxVec2::subtract )));
				objTemp->Set(String::New("multiply"), FunctionTemplate::New(InvocationCallback( V8PxVec2::multiply )));
				objTemp->Set(String::New("divide"), FunctionTemplate::New(InvocationCallback( V8PxVec2::divide )));
				
				objTemp->Set(String::New("assignment_add"), FunctionTemplate::New(InvocationCallback( V8PxVec2::assignmentAdd)));
				objTemp->Set(String::New("assignment_subtract"), FunctionTemplate::New(InvocationCallback( V8PxVec2::assignmentSubtract )));
				objTemp->Set(String::New("assignment_multiply"), FunctionTemplate::New(InvocationCallback( V8PxVec2::assignmentMultiply )));
				objTemp->Set(String::New("assignment_divide"), FunctionTemplate::New(InvocationCallback( V8PxVec2::assignmentDivide )));

				objTemp->Set(String::New("dot"), FunctionTemplate::New(InvocationCallback( V8PxVec2::dot )));
				objTemp->Set(String::New("getNormalized"), FunctionTemplate::New(InvocationCallback( V8PxVec2::getNormalized )));
				objTemp->Set(String::New("normalize"), FunctionTemplate::New(InvocationCallback( V8PxVec2::normalize )));
				objTemp->Set(String::New("min"), FunctionTemplate::New(InvocationCallback( V8PxVec2::min )));
				objTemp->Set(String::New("max"), FunctionTemplate::New(InvocationCallback( V8PxVec2::max )));

				objTemp->Set(String::New("elementwise_multiply"), FunctionTemplate::New(InvocationCallback( V8PxVec2::elementwiseMultiply )));
				objTemp->Set(String::New("elementwise_min"), FunctionTemplate::New(InvocationCallback( V8PxVec2::elementwiseMin )));
				objTemp->Set(String::New("elementwise_max"), FunctionTemplate::New(InvocationCallback( V8PxVec2::elementwiseMax )));

			//PxVec3
				V8PxVec3::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxVec3::PxVec3Constructor));
				V8PxVec3::getTemplate()->SetClassName(String::New("PxVec3"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxVec3"), V8PxVec3::getTemplate());

				objTemp = V8PxVec3::getTemplate()->PrototypeTemplate();
				V8PxVec3::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxVec3::getTemplate()->InstanceTemplate()->SetAccessor(String::New("x"), V8PxVec3::getX, V8PxVec3::setX);
				V8PxVec3::getTemplate()->InstanceTemplate()->SetAccessor(String::New("y"), V8PxVec3::getY, V8PxVec3::setY);
				V8PxVec3::getTemplate()->InstanceTemplate()->SetAccessor(String::New("z"), V8PxVec3::getZ, V8PxVec3::setZ);
				V8PxVec3::getTemplate()->InstanceTemplate()->SetIndexedPropertyHandler(V8PxVec3::elementGet, V8PxVec3::elementSet);

				objTemp->Set(String::New("compare"), FunctionTemplate::New(InvocationCallback( V8PxVec3::compare )));
				objTemp->Set(String::New("acompare"), FunctionTemplate::New(InvocationCallback( V8PxVec3::acompare )));
				objTemp->Set(String::New("isZero"), FunctionTemplate::New(InvocationCallback( V8PxVec3::isZero )));
				objTemp->Set(String::New("isFinite"), FunctionTemplate::New(InvocationCallback( V8PxVec3::isFinite )));
				objTemp->Set(String::New("isNormalized"), FunctionTemplate::New(InvocationCallback( V8PxVec3::isNormalized )));
				objTemp->Set(String::New("magnitudeSquared"), FunctionTemplate::New(InvocationCallback( V8PxVec3::magnitudeSquared )));
				objTemp->Set(String::New("magnitude"), FunctionTemplate::New(InvocationCallback( V8PxVec3::magnitude )));
				objTemp->Set(String::New("negate"), FunctionTemplate::New(InvocationCallback( V8PxVec3::negate )));
				objTemp->Set(String::New("add"), FunctionTemplate::New(InvocationCallback( V8PxVec3::add )));
				objTemp->Set(String::New("subtract"), FunctionTemplate::New(InvocationCallback( V8PxVec3::subtract )));
				objTemp->Set(String::New("multiply"), FunctionTemplate::New(InvocationCallback( V8PxVec3::multiply )));
				objTemp->Set(String::New("divide"), FunctionTemplate::New(InvocationCallback( V8PxVec3::divide )));
				
				objTemp->Set(String::New("assignment_add"), FunctionTemplate::New(InvocationCallback( V8PxVec3::assignmentAdd)));
				objTemp->Set(String::New("assignment_subtract"), FunctionTemplate::New(InvocationCallback( V8PxVec3::assignmentSubtract )));
				objTemp->Set(String::New("assignment_multiply"), FunctionTemplate::New(InvocationCallback( V8PxVec3::assignmentMultiply )));
				objTemp->Set(String::New("assignment_divide"), FunctionTemplate::New(InvocationCallback( V8PxVec3::assignmentDivide )));

				objTemp->Set(String::New("dot"), FunctionTemplate::New(InvocationCallback( V8PxVec3::dot )));
				objTemp->Set(String::New("cross"), FunctionTemplate::New(InvocationCallback( V8PxVec3::cross )));
				objTemp->Set(String::New("getNormalized"), FunctionTemplate::New(InvocationCallback( V8PxVec3::getNormalized )));
				objTemp->Set(String::New("normalize"), FunctionTemplate::New(InvocationCallback( V8PxVec3::normalize )));
				objTemp->Set(String::New("min"), FunctionTemplate::New(InvocationCallback( V8PxVec3::min )));
				objTemp->Set(String::New("max"), FunctionTemplate::New(InvocationCallback( V8PxVec3::max )));

				objTemp->Set(String::New("elementwise_multiply"), FunctionTemplate::New(InvocationCallback( V8PxVec3::elementwiseMultiply )));
				objTemp->Set(String::New("elementwise_min"), FunctionTemplate::New(InvocationCallback( V8PxVec3::elementwiseMin )));
				objTemp->Set(String::New("elementwise_max"), FunctionTemplate::New(InvocationCallback( V8PxVec3::elementwiseMax )));

			//PxExtendedVec3
				V8PxExtendedVec3::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxExtendedVec3::PxExtendedVec3Constructor));
				V8PxExtendedVec3::getTemplate()->SetClassName(String::New("PxExtendedVec3"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxExtendedVec3"), V8PxExtendedVec3::getTemplate());

				objTemp = V8PxExtendedVec3::getTemplate()->PrototypeTemplate();
				V8PxExtendedVec3::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxExtendedVec3::getTemplate()->InstanceTemplate()->SetAccessor(String::New("x"), V8PxExtendedVec3::getX, V8PxExtendedVec3::setX);
				V8PxExtendedVec3::getTemplate()->InstanceTemplate()->SetAccessor(String::New("y"), V8PxExtendedVec3::getY, V8PxExtendedVec3::setY);
				V8PxExtendedVec3::getTemplate()->InstanceTemplate()->SetAccessor(String::New("z"), V8PxExtendedVec3::getZ, V8PxExtendedVec3::setZ);
				V8PxExtendedVec3::getTemplate()->InstanceTemplate()->SetIndexedPropertyHandler(V8PxExtendedVec3::elementGet, V8PxExtendedVec3::elementSet);

				objTemp->Set(String::New("isZero"), FunctionTemplate::New(InvocationCallback( V8PxExtendedVec3::isZero )));
				objTemp->Set(String::New("isFinite"), FunctionTemplate::New(InvocationCallback( V8PxExtendedVec3::isFinite )));
				objTemp->Set(String::New("magnitudeSquared"), FunctionTemplate::New(InvocationCallback( V8PxExtendedVec3::magnitudeSquared )));
				objTemp->Set(String::New("magnitude"), FunctionTemplate::New(InvocationCallback( V8PxExtendedVec3::magnitude )));
				objTemp->Set(String::New("negate"), FunctionTemplate::New(InvocationCallback( V8PxExtendedVec3::negate )));
				objTemp->Set(String::New("add"), FunctionTemplate::New(InvocationCallback( V8PxExtendedVec3::add )));
				objTemp->Set(String::New("subtract"), FunctionTemplate::New(InvocationCallback( V8PxExtendedVec3::subtract )));
				
				objTemp->Set(String::New("assignment_add"), FunctionTemplate::New(InvocationCallback( V8PxExtendedVec3::assignmentAdd)));
				objTemp->Set(String::New("assignment_subtract"), FunctionTemplate::New(InvocationCallback( V8PxExtendedVec3::assignmentSubtract )));
				objTemp->Set(String::New("assignment_multiply"), FunctionTemplate::New(InvocationCallback( V8PxExtendedVec3::assignmentMultiply )));

				objTemp->Set(String::New("dot"), FunctionTemplate::New(InvocationCallback( V8PxExtendedVec3::dot )));
				objTemp->Set(String::New("cross"), FunctionTemplate::New(InvocationCallback( V8PxExtendedVec3::cross )));
				objTemp->Set(String::New("normalize"), FunctionTemplate::New(InvocationCallback( V8PxExtendedVec3::normalize )));
				objTemp->Set(String::New("min"), FunctionTemplate::New(InvocationCallback( V8PxExtendedVec3::min )));
				objTemp->Set(String::New("max"), FunctionTemplate::New(InvocationCallback( V8PxExtendedVec3::max )));

				objTemp->Set(String::New("set"), FunctionTemplate::New(InvocationCallback( V8PxExtendedVec3::set )));
				objTemp->Set(String::New("setPlusInfinity"), FunctionTemplate::New(InvocationCallback( V8PxExtendedVec3::setPlusInfinity )));
				objTemp->Set(String::New("setMinusInfinity"), FunctionTemplate::New(InvocationCallback( V8PxExtendedVec3::setMinusInfinity )));

			//PxVec4
				V8PxVec4::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxVec4::PxVec4Constructor));
				V8PxVec4::getTemplate()->SetClassName(String::New("PxVec4"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxVec4"), V8PxVec4::getTemplate());

				objTemp = V8PxVec4::getTemplate()->PrototypeTemplate();
				V8PxVec4::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxVec4::getTemplate()->InstanceTemplate()->SetAccessor(String::New("x"), V8PxVec4::getX, V8PxVec4::setX);
				V8PxVec4::getTemplate()->InstanceTemplate()->SetAccessor(String::New("y"), V8PxVec4::getY, V8PxVec4::setY);
				V8PxVec4::getTemplate()->InstanceTemplate()->SetAccessor(String::New("z"), V8PxVec4::getZ, V8PxVec4::setZ);
				V8PxVec4::getTemplate()->InstanceTemplate()->SetAccessor(String::New("w"), V8PxVec4::getW, V8PxVec4::setW);
				V8PxVec4::getTemplate()->InstanceTemplate()->SetIndexedPropertyHandler(V8PxVec4::elementGet, V8PxVec4::elementSet);

				objTemp->Set(String::New("compare"), FunctionTemplate::New(InvocationCallback( V8PxVec4::compare )));
				objTemp->Set(String::New("acompare"), FunctionTemplate::New(InvocationCallback( V8PxVec4::acompare )));
				objTemp->Set(String::New("isZero"), FunctionTemplate::New(InvocationCallback( V8PxVec4::isZero )));
				objTemp->Set(String::New("isFinite"), FunctionTemplate::New(InvocationCallback( V8PxVec4::isFinite )));
				objTemp->Set(String::New("isNormalized"), FunctionTemplate::New(InvocationCallback( V8PxVec4::isNormalized )));
				objTemp->Set(String::New("magnitudeSquared"), FunctionTemplate::New(InvocationCallback( V8PxVec4::magnitudeSquared )));
				objTemp->Set(String::New("magnitude"), FunctionTemplate::New(InvocationCallback( V8PxVec4::magnitude )));
				objTemp->Set(String::New("negate"), FunctionTemplate::New(InvocationCallback( V8PxVec4::negate )));
				objTemp->Set(String::New("add"), FunctionTemplate::New(InvocationCallback( V8PxVec4::add )));
				objTemp->Set(String::New("subtract"), FunctionTemplate::New(InvocationCallback( V8PxVec4::subtract )));
				objTemp->Set(String::New("multiply"), FunctionTemplate::New(InvocationCallback( V8PxVec4::multiply )));
				objTemp->Set(String::New("divide"), FunctionTemplate::New(InvocationCallback( V8PxVec4::divide )));
				
				objTemp->Set(String::New("assignment_add"), FunctionTemplate::New(InvocationCallback( V8PxVec4::assignmentAdd)));
				objTemp->Set(String::New("assignment_subtract"), FunctionTemplate::New(InvocationCallback( V8PxVec4::assignmentSubtract )));
				objTemp->Set(String::New("assignment_multiply"), FunctionTemplate::New(InvocationCallback( V8PxVec4::assignmentMultiply )));
				objTemp->Set(String::New("assignment_divide"), FunctionTemplate::New(InvocationCallback( V8PxVec4::assignmentDivide )));

				objTemp->Set(String::New("dot"), FunctionTemplate::New(InvocationCallback( V8PxVec4::dot )));
				objTemp->Set(String::New("getNormalized"), FunctionTemplate::New(InvocationCallback( V8PxVec4::getNormalized )));
				objTemp->Set(String::New("normalize"), FunctionTemplate::New(InvocationCallback( V8PxVec4::normalize )));

				objTemp->Set(String::New("elementwise_multiply"), FunctionTemplate::New(InvocationCallback( V8PxVec4::elementwiseMultiply )));
				objTemp->Set(String::New("elementwise_min"), FunctionTemplate::New(InvocationCallback( V8PxVec4::elementwiseMin )));
				objTemp->Set(String::New("elementwise_max"), FunctionTemplate::New(InvocationCallback( V8PxVec4::elementwiseMax )));

				objTemp->Set(String::New("getXYZ"), FunctionTemplate::New(InvocationCallback( V8PxVec4::getXYZ )));
				objTemp->Set(String::New("setZero"), FunctionTemplate::New(InvocationCallback( V8PxVec4::setZero )));

			//PxQuat
				V8PxQuat::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxQuat::PxQuatConstructor));
				V8PxQuat::getTemplate()->SetClassName(String::New("PxQuat"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxQuat"), V8PxQuat::getTemplate());

				objTemp = V8PxQuat::getTemplate()->PrototypeTemplate();
				V8PxQuat::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxQuat::getTemplate()->InstanceTemplate()->SetAccessor(String::New("x"), V8PxQuat::getX, V8PxQuat::setX);
				V8PxQuat::getTemplate()->InstanceTemplate()->SetAccessor(String::New("y"), V8PxQuat::getY, V8PxQuat::setY);
				V8PxQuat::getTemplate()->InstanceTemplate()->SetAccessor(String::New("z"), V8PxQuat::getZ, V8PxQuat::setZ);
				V8PxQuat::getTemplate()->InstanceTemplate()->SetAccessor(String::New("w"), V8PxQuat::getW, V8PxQuat::setW);
				objTemp->Set(String::New("isFinite"), FunctionTemplate::New(InvocationCallback( V8PxQuat::isFinite )));
				//objTemp->Set(String::New("isValid"), FunctionTemplate::New(InvocationCallback( V8PxQuat::isValid )));
				objTemp->Set(String::New("isSane"), FunctionTemplate::New(InvocationCallback( V8PxQuat::isSane )));
				objTemp->Set(String::New("toRadiansAndUnitAxis"), FunctionTemplate::New(InvocationCallback( V8PxQuat::toRadiansAndUnitAxis )));
				objTemp->Set(String::New("getAngle"), FunctionTemplate::New(InvocationCallback( V8PxQuat::getAngle )));
				objTemp->Set(String::New("magnitudeSquared"), FunctionTemplate::New(InvocationCallback( V8PxQuat::magnitudeSquared )));

				objTemp->Set(String::New("dot"), FunctionTemplate::New(InvocationCallback( V8PxQuat::dot )));
				objTemp->Set(String::New("getNormalized"), FunctionTemplate::New(InvocationCallback( V8PxQuat::getNormalized )));
				objTemp->Set(String::New("magnitude"), FunctionTemplate::New(InvocationCallback( V8PxQuat::magnitude )));
				objTemp->Set(String::New("normalize"), FunctionTemplate::New(InvocationCallback( V8PxQuat::normalize )));
				objTemp->Set(String::New("getConjugate"), FunctionTemplate::New(InvocationCallback( V8PxQuat::getConjugate )));
				objTemp->Set(String::New("getImaginaryPart"), FunctionTemplate::New(InvocationCallback( V8PxQuat::getImaginaryPart )));
				objTemp->Set(String::New("getBasisVector0"), FunctionTemplate::New(InvocationCallback( V8PxQuat::getBasisVector0 )));
				objTemp->Set(String::New("getBasisVector1"), FunctionTemplate::New(InvocationCallback( V8PxQuat::getBasisVector1 )));
				objTemp->Set(String::New("getBasisVector2"), FunctionTemplate::New(InvocationCallback( V8PxQuat::getBasisVector2 )));
				objTemp->Set(String::New("rotate"), FunctionTemplate::New(InvocationCallback( V8PxQuat::rotate )));
				objTemp->Set(String::New("rotateInv"), FunctionTemplate::New(InvocationCallback( V8PxQuat::rotateInv )));

				objTemp->Set(String::New("assignment_add"), FunctionTemplate::New(InvocationCallback( V8PxQuat::assignmentAdd)));
				objTemp->Set(String::New("assignment_subtract"), FunctionTemplate::New(InvocationCallback( V8PxQuat::assignmentSubtract )));
				objTemp->Set(String::New("assignment_multiply"), FunctionTemplate::New(InvocationCallback( V8PxQuat::assignmentMultiply )));
				objTemp->Set(String::New("add"), FunctionTemplate::New(InvocationCallback( V8PxQuat::add )));
				objTemp->Set(String::New("subtract"), FunctionTemplate::New(InvocationCallback( V8PxQuat::subtract )));
				objTemp->Set(String::New("multiply"), FunctionTemplate::New(InvocationCallback( V8PxQuat::multiply )));
				objTemp->Set(String::New("negate"), FunctionTemplate::New(InvocationCallback( V8PxQuat::negate )));

				V8PxQuat::getTemplate()->Set(String::New("createIdentity"), FunctionTemplate::New(InvocationCallback( V8PxQuat::createIdentity )));

			//PxMat33
				V8PxMat33::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxMat33::PxMat33Constructor));
				V8PxMat33::getTemplate()->SetClassName(String::New("PxMat33"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxMat33"), V8PxMat33::getTemplate());

				objTemp = V8PxMat33::getTemplate()->PrototypeTemplate();
				V8PxMat33::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->SetIndexedPropertyHandler(V8PxMat33::elementGet, V8PxMat33::elementSet);

				V8PxMat33::getTemplate()->Set(String::New("createIdentity"), FunctionTemplate::New(InvocationCallback( V8PxMat33::createIdentity )));
				V8PxMat33::getTemplate()->Set(String::New("createZero"), FunctionTemplate::New(InvocationCallback( V8PxMat33::createZero )));
				V8PxMat33::getTemplate()->Set(String::New("createDiagonal"), FunctionTemplate::New(InvocationCallback( V8PxMat33::createDiagonal )));

				objTemp->Set(String::New("getTranspose"), FunctionTemplate::New(InvocationCallback( V8PxMat33::getTranspose)));
				objTemp->Set(String::New("getInverse"), FunctionTemplate::New(InvocationCallback( V8PxMat33::getInverse)));
				objTemp->Set(String::New("getDeterminant"), FunctionTemplate::New(InvocationCallback( V8PxMat33::getDeterminant)));
				objTemp->Set(String::New("transform"), FunctionTemplate::New(InvocationCallback( V8PxMat33::transform)));
				objTemp->Set(String::New("transformTranspose"), FunctionTemplate::New(InvocationCallback( V8PxMat33::transformTranspose)));

				objTemp->Set(String::New("assignment_add"), FunctionTemplate::New(InvocationCallback( V8PxMat33::assignmentAdd)));
				objTemp->Set(String::New("assignment_subtract"), FunctionTemplate::New(InvocationCallback( V8PxMat33::assignmentSubtract )));
				objTemp->Set(String::New("assignment_multiply"), FunctionTemplate::New(InvocationCallback( V8PxMat33::assignmentMultiply )));
				objTemp->Set(String::New("add"), FunctionTemplate::New(InvocationCallback( V8PxMat33::add )));
				objTemp->Set(String::New("subtract"), FunctionTemplate::New(InvocationCallback( V8PxMat33::subtract )));
				objTemp->Set(String::New("multiply"), FunctionTemplate::New(InvocationCallback( V8PxMat33::multiply )));
				objTemp->Set(String::New("negate"), FunctionTemplate::New(InvocationCallback( V8PxMat33::negate )));

			//PxMat44
				V8PxMat44::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxMat44::PxMat44Constructor));
				V8PxMat44::getTemplate()->SetClassName(String::New("PxMat44"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxMat44"), V8PxMat44::getTemplate());

				objTemp = V8PxMat44::getTemplate()->PrototypeTemplate();
				V8PxMat44::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->SetIndexedPropertyHandler(V8PxMat44::elementGet, V8PxMat44::elementSet);

				V8PxMat44::getTemplate()->Set(String::New("createIdentity"), FunctionTemplate::New(InvocationCallback( V8PxMat44::createIdentity )));
				V8PxMat44::getTemplate()->Set(String::New("createZero"), FunctionTemplate::New(InvocationCallback( V8PxMat44::createZero )));

				objTemp->Set(String::New("getTranspose"), FunctionTemplate::New(InvocationCallback( V8PxMat44::getTranspose)));
				objTemp->Set(String::New("transform"), FunctionTemplate::New(InvocationCallback( V8PxMat44::transform)));
				objTemp->Set(String::New("rotate"), FunctionTemplate::New(InvocationCallback( V8PxMat44::rotate)));
				objTemp->Set(String::New("getBasis"), FunctionTemplate::New(InvocationCallback( V8PxMat44::getBasis)));
				objTemp->Set(String::New("getPosition"), FunctionTemplate::New(InvocationCallback( V8PxMat44::getPosition)));
				objTemp->Set(String::New("setPosition"), FunctionTemplate::New(InvocationCallback( V8PxMat44::setPosition)));
				objTemp->Set(String::New("scale"), FunctionTemplate::New(InvocationCallback( V8PxMat44::scale)));
				objTemp->Set(String::New("inverseRT"), FunctionTemplate::New(InvocationCallback( V8PxMat44::inverseRT)));
				objTemp->Set(String::New("isFinite"), FunctionTemplate::New(InvocationCallback( V8PxMat44::isFinite)));

				objTemp->Set(String::New("assignment_add"), FunctionTemplate::New(InvocationCallback( V8PxMat44::assignmentAdd)));
				objTemp->Set(String::New("assignment_subtract"), FunctionTemplate::New(InvocationCallback( V8PxMat44::assignmentSubtract )));
				objTemp->Set(String::New("assignment_multiply"), FunctionTemplate::New(InvocationCallback( V8PxMat44::assignmentMultiply )));
				objTemp->Set(String::New("add"), FunctionTemplate::New(InvocationCallback( V8PxMat44::add )));
				objTemp->Set(String::New("subtract"), FunctionTemplate::New(InvocationCallback( V8PxMat44::subtract )));
				objTemp->Set(String::New("multiply"), FunctionTemplate::New(InvocationCallback( V8PxMat44::multiply )));
				objTemp->Set(String::New("negate"), FunctionTemplate::New(InvocationCallback( V8PxMat44::negate )));

			//PxTransform
				V8PxTransform::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxTransform::PxTransformConstructor));
				V8PxTransform::getTemplate()->SetClassName(String::New("PxTransform"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxTransform"), V8PxTransform::getTemplate());

				objTemp = V8PxTransform::getTemplate()->PrototypeTemplate();
				V8PxTransform::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxTransform::getTemplate()->InstanceTemplate()->SetAccessor(String::New("q"), V8PxTransform::getQ, V8PxTransform::setQ);
				V8PxTransform::getTemplate()->InstanceTemplate()->SetAccessor(String::New("p"), V8PxTransform::getP, V8PxTransform::setP);

				V8PxTransform::getTemplate()->Set(String::New("createIdentity"), FunctionTemplate::New(InvocationCallback( V8PxTransform::createIdentity )));

				objTemp->Set(String::New("getInverse"), FunctionTemplate::New(InvocationCallback( V8PxTransform::getInverse)));
				objTemp->Set(String::New("transform"), FunctionTemplate::New(InvocationCallback( V8PxTransform::transform)));
				objTemp->Set(String::New("transformInv"), FunctionTemplate::New(InvocationCallback( V8PxTransform::transformInv)));
				objTemp->Set(String::New("rotate"), FunctionTemplate::New(InvocationCallback( V8PxTransform::rotate)));
				objTemp->Set(String::New("rotateInv"), FunctionTemplate::New(InvocationCallback( V8PxTransform::rotateInv)));
				objTemp->Set(String::New("isValid"), FunctionTemplate::New(InvocationCallback( V8PxTransform::isValid)));
				objTemp->Set(String::New("isSane"), FunctionTemplate::New(InvocationCallback( V8PxTransform::isSane)));
				objTemp->Set(String::New("isFinite"), FunctionTemplate::New(InvocationCallback( V8PxTransform::isFinite)));

				objTemp->Set(String::New("multiply"), FunctionTemplate::New(InvocationCallback( V8PxTransform::multiply)));

			//PxBounds3
				V8PxBounds3::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxBounds3::PxBounds3Constructor));
				V8PxBounds3::getTemplate()->SetClassName(String::New("PxBounds3"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxBounds3"), V8PxBounds3::getTemplate());

				objTemp = V8PxBounds3::getTemplate()->PrototypeTemplate();
				V8PxBounds3::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxBounds3::getTemplate()->InstanceTemplate()->SetAccessor(String::New("minimum"), V8PxBounds3::getMin, V8PxBounds3::setMin);
				V8PxBounds3::getTemplate()->InstanceTemplate()->SetAccessor(String::New("maximum"), V8PxBounds3::getMax, V8PxBounds3::setMax);

				V8PxBounds3::getTemplate()->Set(String::New("empty"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::empty )));
				V8PxBounds3::getTemplate()->Set(String::New("boundsOfPoints"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::boundsOfPoints )));
				V8PxBounds3::getTemplate()->Set(String::New("centerExtents"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::centerExtents )));
				V8PxBounds3::getTemplate()->Set(String::New("basisExtent"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::basisExtent )));
				V8PxBounds3::getTemplate()->Set(String::New("poseExtent"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::poseExtent )));
				V8PxBounds3::getTemplate()->Set(String::New("transform"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::transform )));

				objTemp->Set(String::New("setEmpty"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::setEmpty)));
				objTemp->Set(String::New("setInfinite"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::setInfinite)));
				objTemp->Set(String::New("include"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::include)));
				objTemp->Set(String::New("isEmpty"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::isEmpty)));
				objTemp->Set(String::New("intersects"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::intersects)));
				objTemp->Set(String::New("intersects1D"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::intersects1D)));
				objTemp->Set(String::New("contains"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::contains)));
				objTemp->Set(String::New("isInside"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::contains)));
				objTemp->Set(String::New("getCenter"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::getCenter)));
				objTemp->Set(String::New("getExtents"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::getExtents)));
				objTemp->Set(String::New("getDimensions"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::getDimensions)));
				objTemp->Set(String::New("scale"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::scale)));
				objTemp->Set(String::New("fatten"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::fatten)));
				objTemp->Set(String::New("isFinite"), FunctionTemplate::New(InvocationCallback( V8PxBounds3::isFinite)));

			//PxShape
				V8PxShape::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxShape::getTemplate()->SetClassName(String::New("PxShape"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxShape"), V8PxShape::getTemplate());

				objTemp = V8PxShape::getTemplate()->PrototypeTemplate();
				V8PxShape::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxShape::getTemplate()->InstanceTemplate()->SetAccessor(String::New("userData"), V8PxShape::getUserData, V8PxShape::setUserData);

				objTemp->Set(String::New("release"), FunctionTemplate::New(InvocationCallback( V8PxShape::release)));
				objTemp->Set(String::New("getGeometryType"), FunctionTemplate::New(InvocationCallback( V8PxShape::getGeometryType)));
				objTemp->Set(String::New("setGeometry"), FunctionTemplate::New(InvocationCallback( V8PxShape::setGeometry)));
				objTemp->Set(String::New("getBoxGeometry"), FunctionTemplate::New(InvocationCallback( V8PxShape::getBoxGeometry)));
				objTemp->Set(String::New("getSphereGeometry"), FunctionTemplate::New(InvocationCallback( V8PxShape::getSphereGeometry)));
				objTemp->Set(String::New("getCapsuleGeometry"), FunctionTemplate::New(InvocationCallback( V8PxShape::getCapsuleGeometry)));
				objTemp->Set(String::New("getPlaneGeometry"), FunctionTemplate::New(InvocationCallback( V8PxShape::getPlaneGeometry)));
				objTemp->Set(String::New("getConvexMeshGeometry"), FunctionTemplate::New(InvocationCallback( V8PxShape::getConvexMeshGeometry)));
				objTemp->Set(String::New("getTriangleMeshGeometry"), FunctionTemplate::New(InvocationCallback( V8PxShape::getTriangleMeshGeometry)));
				objTemp->Set(String::New("getHeightFieldGeometry"), FunctionTemplate::New(InvocationCallback( V8PxShape::getHeightFieldGeometry)));
				objTemp->Set(String::New("getActor"), FunctionTemplate::New(InvocationCallback( V8PxShape::getActor)));
				objTemp->Set(String::New("getWorldBounds"), FunctionTemplate::New(InvocationCallback( V8PxShape::getWorldBounds)));
				objTemp->Set(String::New("setLocalPose"), FunctionTemplate::New(InvocationCallback( V8PxShape::setLocalPose)));
				objTemp->Set(String::New("getLocalPose"), FunctionTemplate::New(InvocationCallback( V8PxShape::getLocalPose)));
				objTemp->Set(String::New("setSimulationFilterData"), FunctionTemplate::New(InvocationCallback( V8PxShape::setSimulationFilterData)));
				objTemp->Set(String::New("getSimulationFilterData"), FunctionTemplate::New(InvocationCallback( V8PxShape::getSimulationFilterData)));
				objTemp->Set(String::New("resetFiltering"), FunctionTemplate::New(InvocationCallback( V8PxShape::resetFiltering)));
				objTemp->Set(String::New("setQueryFilterData"), FunctionTemplate::New(InvocationCallback( V8PxShape::setQueryFilterData)));
				objTemp->Set(String::New("getQueryFilterData"), FunctionTemplate::New(InvocationCallback( V8PxShape::getQueryFilterData)));
				objTemp->Set(String::New("setMaterials"), FunctionTemplate::New(InvocationCallback( V8PxShape::setMaterials)));
				objTemp->Set(String::New("getNbMaterials"), FunctionTemplate::New(InvocationCallback( V8PxShape::getNbMaterials)));
				objTemp->Set(String::New("getMaterials"), FunctionTemplate::New(InvocationCallback( V8PxShape::getMaterials)));
				objTemp->Set(String::New("getMaterialFromInternalFaceIndex"), FunctionTemplate::New(InvocationCallback( V8PxShape::getMaterialFromInternalFaceIndex)));
				objTemp->Set(String::New("setContactOffset"), FunctionTemplate::New(InvocationCallback( V8PxShape::setContactOffset)));
				objTemp->Set(String::New("getContactOffset"), FunctionTemplate::New(InvocationCallback( V8PxShape::getContactOffset)));
				objTemp->Set(String::New("setRestOffset"), FunctionTemplate::New(InvocationCallback( V8PxShape::setRestOffset)));
				objTemp->Set(String::New("getRestOffset"), FunctionTemplate::New(InvocationCallback( V8PxShape::getRestOffset)));
				objTemp->Set(String::New("setFlag"), FunctionTemplate::New(InvocationCallback( V8PxShape::setFlag)));
				objTemp->Set(String::New("setFlags"), FunctionTemplate::New(InvocationCallback( V8PxShape::setFlags)));
				objTemp->Set(String::New("getFlags"), FunctionTemplate::New(InvocationCallback( V8PxShape::getFlags)));
				objTemp->Set(String::New("setName"), FunctionTemplate::New(InvocationCallback( V8PxShape::setName)));
				objTemp->Set(String::New("getName"), FunctionTemplate::New(InvocationCallback( V8PxShape::getName)));

			//PxControllerShapeHit
				V8PxControllerShapeHit::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxControllerShapeHit::getTemplate()->SetClassName(String::New("PxControllerShapeHit"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxControllerShapeHit"), V8PxControllerShapeHit::getTemplate());

				objTemp = V8PxControllerShapeHit::getTemplate()->PrototypeTemplate();
				V8PxControllerShapeHit::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("getController"), FunctionTemplate::New(InvocationCallback(V8PxControllerShapeHit::getController)), ReadOnly);
				objTemp->Set(String::New("getShape"), FunctionTemplate::New(InvocationCallback(V8PxControllerShapeHit::getShape)), ReadOnly);
				objTemp->Set(String::New("getWorldPose"), FunctionTemplate::New(InvocationCallback(V8PxControllerShapeHit::getWorldPose)), ReadOnly);
				objTemp->Set(String::New("getWorldNormal"), FunctionTemplate::New(InvocationCallback(V8PxControllerShapeHit::getWorldNormal)), ReadOnly);
				objTemp->Set(String::New("getDirection"), FunctionTemplate::New(InvocationCallback(V8PxControllerShapeHit::getDirection)), ReadOnly);
				objTemp->Set(String::New("getLength"), FunctionTemplate::New(InvocationCallback(V8PxControllerShapeHit::getLength)), ReadOnly);

			//PxControllersHit
				V8PxControllersHit::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxControllersHit::getTemplate()->SetClassName(String::New("PxControllersHit"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxControllersHit"), V8PxControllersHit::getTemplate());

				objTemp = V8PxControllersHit::getTemplate()->PrototypeTemplate();
				V8PxControllersHit::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("controller"), FunctionTemplate::New(InvocationCallback(V8PxControllersHit::getController)), ReadOnly);
				objTemp->Set(String::New("other"), FunctionTemplate::New(InvocationCallback(V8PxControllersHit::getOther)), ReadOnly);

			//PxPadding1
				V8PxPadding<0>::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxPadding<1>::PxPaddingConstructor));
				V8PxPadding<0>::getTemplate()->SetClassName(String::New("PxPadding1"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxPadding1"), V8PxPadding<0>::getTemplate());

				objTemp = V8PxPadding<0>::getTemplate()->PrototypeTemplate();
				V8PxPadding<0>::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxPadding<0>::getTemplate()->InstanceTemplate()->SetAccessor(String::New("size"), V8PxPadding<1>::getSize);
				V8PxPadding<0>::getTemplate()->InstanceTemplate()->SetIndexedPropertyHandler(V8PxPadding<1>::elementGet, V8PxPadding<1>::elementSet);

			//PxPadding2
				V8PxPadding<1>::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxPadding<2>::PxPaddingConstructor));
				V8PxPadding<1>::getTemplate()->SetClassName(String::New("PxPadding2"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxPadding2"), V8PxPadding<1>::getTemplate());

				objTemp = V8PxPadding<1>::getTemplate()->PrototypeTemplate();
				V8PxPadding<1>::getTemplate()->InstanceTemplate()->SetInternalFieldCount(2);

				V8PxPadding<1>::getTemplate()->InstanceTemplate()->SetAccessor(String::New("size"), V8PxPadding<2>::getSize);
				V8PxPadding<1>::getTemplate()->InstanceTemplate()->SetIndexedPropertyHandler(V8PxPadding<2>::elementGet, V8PxPadding<2>::elementSet);

			//PxPadding3
				V8PxPadding<2>::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxPadding<3>::PxPaddingConstructor));
				V8PxPadding<2>::getTemplate()->SetClassName(String::New("PxPadding3"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxPadding3"), V8PxPadding<2>::getTemplate());

				objTemp = V8PxPadding<2>::getTemplate()->PrototypeTemplate();
				V8PxPadding<2>::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxPadding<2>::getTemplate()->InstanceTemplate()->SetAccessor(String::New("size"), V8PxPadding<3>::getSize);
				V8PxPadding<2>::getTemplate()->InstanceTemplate()->SetIndexedPropertyHandler(V8PxPadding<3>::elementGet, V8PxPadding<3>::elementSet);

			//PxPadding4
				V8PxPadding<3>::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxPadding<4>::PxPaddingConstructor));
				V8PxPadding<3>::getTemplate()->SetClassName(String::New("PxPadding4"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxPadding4"), V8PxPadding<3>::getTemplate());

				objTemp = V8PxPadding<3>::getTemplate()->PrototypeTemplate();
				V8PxPadding<3>::getTemplate()->InstanceTemplate()->SetInternalFieldCount(4);

				V8PxPadding<3>::getTemplate()->InstanceTemplate()->SetAccessor(String::New("size"), V8PxPadding<4>::getSize);
				V8PxPadding<3>::getTemplate()->InstanceTemplate()->SetIndexedPropertyHandler(V8PxPadding<4>::elementGet, V8PxPadding<4>::elementSet);

			//PxGeometry
				V8PxGeometry::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxGeometry::getTemplate()->SetClassName(String::New("PxGeometry"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxGeometry"), V8PxGeometry::getTemplate());

				objTemp = V8PxGeometry::getTemplate()->PrototypeTemplate();
				V8PxGeometry::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("getType"), FunctionTemplate::New(InvocationCallback( V8PxGeometry::getType)));

			//PxBoxGeometry
				V8PxBoxGeometry::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxBoxGeometry::PxBoxGeometryConstructor));
				V8PxBoxGeometry::getTemplate()->SetClassName(String::New("PxBoxGeometry"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxBoxGeometry"), V8PxBoxGeometry::getTemplate());

				V8PxBoxGeometry::getTemplate()->Inherit(V8PxGeometry::getTemplate());

				objTemp = V8PxBoxGeometry::getTemplate()->PrototypeTemplate();
				V8PxBoxGeometry::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->SetAccessor(String::New("halfExtents"), V8PxBoxGeometry::getHalfExtents, V8PxBoxGeometry::setHalfExtents);

				objTemp->Set(String::New("isValid"), FunctionTemplate::New(InvocationCallback(V8PxBoxGeometry::isValid)));

			//PxCapsuleGeometry
				V8PxCapsuleGeometry::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxCapsuleGeometry::PxCapsuleGeometryConstructor));
				V8PxCapsuleGeometry::getTemplate()->SetClassName(String::New("PxCapsuleGeometry"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxCapsuleGeometry"), V8PxCapsuleGeometry::getTemplate());

				V8PxCapsuleGeometry::getTemplate()->Inherit(V8PxGeometry::getTemplate());

				objTemp = V8PxCapsuleGeometry::getTemplate()->PrototypeTemplate();
				V8PxCapsuleGeometry::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxCapsuleGeometry::getTemplate()->InstanceTemplate()->SetAccessor(String::New("radius"), V8PxCapsuleGeometry::getRadius, V8PxCapsuleGeometry::setRadius);
				V8PxCapsuleGeometry::getTemplate()->InstanceTemplate()->SetAccessor(String::New("halfHeight"), V8PxCapsuleGeometry::getHalfHeight, V8PxCapsuleGeometry::setHalfHeight);

				objTemp->Set(String::New("isValid"), FunctionTemplate::New(InvocationCallback(V8PxCapsuleGeometry::isValid)));

			//PxConvexMeshGeometry
				V8PxConvexMeshGeometry::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxConvexMeshGeometry::PxConvexMeshGeometryConstructor));
				V8PxConvexMeshGeometry::getTemplate()->SetClassName(String::New("PxConvexMeshGeometry"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxConvexMeshGeometry"), V8PxConvexMeshGeometry::getTemplate());

				V8PxConvexMeshGeometry::getTemplate()->Inherit(V8PxGeometry::getTemplate());

				objTemp = V8PxConvexMeshGeometry::getTemplate()->PrototypeTemplate();
				V8PxConvexMeshGeometry::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxConvexMeshGeometry::getTemplate()->InstanceTemplate()->SetAccessor(String::New("scale"), V8PxConvexMeshGeometry::getScale, V8PxConvexMeshGeometry::setScale);
				V8PxConvexMeshGeometry::getTemplate()->InstanceTemplate()->SetAccessor(String::New("convexMesh"), V8PxConvexMeshGeometry::getConvexMesh, V8PxConvexMeshGeometry::setConvexMesh);

				objTemp->Set(String::New("isValid"), FunctionTemplate::New(InvocationCallback(V8PxConvexMeshGeometry::isValid)));

			//PxHeightFieldGeometry
				V8PxHeightFieldGeometry::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxHeightFieldGeometry::PxHeightFieldGeometryConstructor));
				V8PxHeightFieldGeometry::getTemplate()->SetClassName(String::New("PxHeightFieldGeometry"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxHeightFieldGeometry"), V8PxHeightFieldGeometry::getTemplate());

				V8PxHeightFieldGeometry::getTemplate()->Inherit(V8PxGeometry::getTemplate());

				objTemp = V8PxHeightFieldGeometry::getTemplate()->PrototypeTemplate();
				V8PxHeightFieldGeometry::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxHeightFieldGeometry::getTemplate()->InstanceTemplate()->SetAccessor(String::New("heightField"), V8PxHeightFieldGeometry::getHeightField, V8PxHeightFieldGeometry::setHeightField);
				V8PxHeightFieldGeometry::getTemplate()->InstanceTemplate()->SetAccessor(String::New("heightScale"), V8PxHeightFieldGeometry::getHeightScale, V8PxHeightFieldGeometry::setHeightScale);
				V8PxHeightFieldGeometry::getTemplate()->InstanceTemplate()->SetAccessor(String::New("rowScale"), V8PxHeightFieldGeometry::getHeightField, V8PxHeightFieldGeometry::setHeightField);
				V8PxHeightFieldGeometry::getTemplate()->InstanceTemplate()->SetAccessor(String::New("columnScale"), V8PxHeightFieldGeometry::getColumnScale, V8PxHeightFieldGeometry::setColumnScale);
				V8PxHeightFieldGeometry::getTemplate()->InstanceTemplate()->SetAccessor(String::New("heightFieldFlags"), V8PxHeightFieldGeometry::getHeightFeildFlags, V8PxHeightFieldGeometry::setHeightFieldFlags);
				V8PxHeightFieldGeometry::getTemplate()->InstanceTemplate()->SetAccessor(String::New("paddingFromFlags"), V8PxHeightFieldGeometry::getPaddingFromFlags, V8PxHeightFieldGeometry::setPaddingFromFlags);

				objTemp->Set(String::New("isValid"), FunctionTemplate::New(InvocationCallback(V8PxHeightFieldGeometry::isValid)));
			
			//PxSphereGeometry
				V8PxSphereGeometry::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxSphereGeometry::PxSphereGeometryConstructor));
				V8PxSphereGeometry::getTemplate()->SetClassName(String::New("PxSphereGeometry"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxSphereGeometry"), V8PxSphereGeometry::getTemplate());

				V8PxSphereGeometry::getTemplate()->Inherit(V8PxGeometry::getTemplate());

				objTemp = V8PxSphereGeometry::getTemplate()->PrototypeTemplate();
				V8PxSphereGeometry::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxSphereGeometry::getTemplate()->InstanceTemplate()->SetAccessor(String::New("radius"), V8PxSphereGeometry::getRadius, V8PxSphereGeometry::setRadius);

				objTemp->Set(String::New("isValid"), FunctionTemplate::New(InvocationCallback(V8PxSphereGeometry::isValid)));

			//PxPlaneGeometry
				V8PxPlaneGeometry::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxPlaneGeometry::PxPlaneGeometryConstructor));
				V8PxPlaneGeometry::getTemplate()->SetClassName(String::New("PxPlaneGeometry"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxPlaneGeometry"), V8PxPlaneGeometry::getTemplate());

				V8PxPlaneGeometry::getTemplate()->Inherit(V8PxGeometry::getTemplate());

				objTemp = V8PxPlaneGeometry::getTemplate()->PrototypeTemplate();
				V8PxPlaneGeometry::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("isValid"), FunctionTemplate::New(InvocationCallback(V8PxPlaneGeometry::isValid)));

			//PxTriangleMeshGeometry
				V8PxTriangleMeshGeometry::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxTriangleMeshGeometry::PxTriangleMeshGeometryConstructor));
				V8PxTriangleMeshGeometry::getTemplate()->SetClassName(String::New("PxTriangleMeshGeometry"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxTriangleMeshGeometry"), V8PxTriangleMeshGeometry::getTemplate());

				V8PxTriangleMeshGeometry::getTemplate()->Inherit(V8PxGeometry::getTemplate());

				objTemp = V8PxTriangleMeshGeometry::getTemplate()->PrototypeTemplate();
				V8PxTriangleMeshGeometry::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxTriangleMeshGeometry::getTemplate()->InstanceTemplate()->SetAccessor(String::New("scale"), V8PxTriangleMeshGeometry::getScale, V8PxTriangleMeshGeometry::setScale);
				V8PxTriangleMeshGeometry::getTemplate()->InstanceTemplate()->SetAccessor(String::New("meshFlags"), V8PxTriangleMeshGeometry::getMeshFlags, V8PxTriangleMeshGeometry::setMeshFlags);
				V8PxTriangleMeshGeometry::getTemplate()->InstanceTemplate()->SetAccessor(String::New("paddingFromFlags"), V8PxTriangleMeshGeometry::getPaddingFromFlags, V8PxTriangleMeshGeometry::setPaddingFromFlags);
				V8PxTriangleMeshGeometry::getTemplate()->InstanceTemplate()->SetAccessor(String::New("triangleMesh"), V8PxTriangleMeshGeometry::getTriangleMesh, V8PxTriangleMeshGeometry::setTriangleMesh);

				objTemp->Set(String::New("isValid"), FunctionTemplate::New(InvocationCallback(V8PxTriangleMeshGeometry::isValid)));

			//PxTriangleMesh
				V8PxTriangleMesh::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxTriangleMesh::getTemplate()->SetClassName(String::New("PxTriangleMesh"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxTriangleMesh"), V8PxTriangleMesh::getTemplate());

				V8PxTriangleMesh::getTemplate()->Inherit(V8PxSerializable::getTemplate());

				objTemp = V8PxTriangleMesh::getTemplate()->PrototypeTemplate();
				V8PxTriangleMesh::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("getNbVertices"), FunctionTemplate::New(InvocationCallback(V8PxTriangleMesh::getNbVertices)));
				objTemp->Set(String::New("getVertices"), FunctionTemplate::New(InvocationCallback(V8PxTriangleMesh::getVertices)));
				objTemp->Set(String::New("getNbTriangles"), FunctionTemplate::New(InvocationCallback(V8PxTriangleMesh::getNbTriangles)));
				objTemp->Set(String::New("getTriangles"), FunctionTemplate::New(InvocationCallback(V8PxTriangleMesh::getTriangles)));
				objTemp->Set(String::New("has16BitTriangleIndices"), FunctionTemplate::New(InvocationCallback(V8PxTriangleMesh::has16BitTriangleIndices)));
				objTemp->Set(String::New("getTrianglesRemap"), FunctionTemplate::New(InvocationCallback(V8PxTriangleMesh::getTrianglesRemap)));
				objTemp->Set(String::New("release"), FunctionTemplate::New(InvocationCallback(V8PxTriangleMesh::release)));
				objTemp->Set(String::New("getTriangleMaterialIndex"), FunctionTemplate::New(InvocationCallback(V8PxTriangleMesh::getTriangleMaterialIndex)));
				objTemp->Set(String::New("getReferenceCount"), FunctionTemplate::New(InvocationCallback(V8PxTriangleMesh::getReferenceCount)));

			//PxFieldDescriptor
				V8PxFieldDescriptor::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxFieldDescriptor::getTemplate()->SetClassName(String::New("PxFieldDescriptor"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxFieldDescriptor"), V8PxFieldDescriptor::getTemplate());

				objTemp = V8PxFieldDescriptor::getTemplate()->PrototypeTemplate();
				V8PxFieldDescriptor::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxFieldDescriptor::getTemplate()->InstanceTemplate()->SetAccessor(String::New("type"), V8PxFieldDescriptor::getType, V8PxFieldDescriptor::setType);
				V8PxFieldDescriptor::getTemplate()->InstanceTemplate()->SetAccessor(String::New("name"), V8PxFieldDescriptor::getName);
				V8PxFieldDescriptor::getTemplate()->InstanceTemplate()->SetAccessor(String::New("offset"), V8PxFieldDescriptor::getOffset, V8PxFieldDescriptor::setOffset);
				V8PxFieldDescriptor::getTemplate()->InstanceTemplate()->SetAccessor(String::New("size"), V8PxFieldDescriptor::getSize, V8PxFieldDescriptor::setSize);
				V8PxFieldDescriptor::getTemplate()->InstanceTemplate()->SetAccessor(String::New("count"), V8PxFieldDescriptor::getCount, V8PxFieldDescriptor::setCount);
				V8PxFieldDescriptor::getTemplate()->InstanceTemplate()->SetAccessor(String::New("offsetSize"), V8PxFieldDescriptor::getOffsetSize, V8PxFieldDescriptor::setOffsetSize);
				V8PxFieldDescriptor::getTemplate()->InstanceTemplate()->SetAccessor(String::New("flags"), V8PxFieldDescriptor::getFlags, V8PxFieldDescriptor::setFlags);

				//objTemp->Set(String::New("fieldSize"), FunctionTemplate::New(InvocationCallback(V8PxFieldDescriptor::FieldSize)));
				objTemp->Set(String::New("address"), FunctionTemplate::New(InvocationCallback(V8PxFieldDescriptor::Address)));
				objTemp->Set(String::New("getArrayAddress"), FunctionTemplate::New(InvocationCallback(V8PxFieldDescriptor::GetArrayAddress)));
				objTemp->Set(String::New("isStaticArray"), FunctionTemplate::New(InvocationCallback(V8PxFieldDescriptor::IsStaticArray)));
				objTemp->Set(String::New("getStaticArraySize"), FunctionTemplate::New(InvocationCallback(V8PxFieldDescriptor::GetStaticArraySize)));
				objTemp->Set(String::New("isDynamicArray"), FunctionTemplate::New(InvocationCallback(V8PxFieldDescriptor::IsDynamicArray)));
				objTemp->Set(String::New("getDynamicArraySize"), FunctionTemplate::New(InvocationCallback(V8PxFieldDescriptor::GetDynamicArraySize)));

			//PxSerialStream
				V8PxSerialStream::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxSerialStream::getTemplate()->SetClassName(String::New("PxSerialStream"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxSerialStream"), V8PxSerialStream::getTemplate());

				objTemp = V8PxSerialStream::getTemplate()->PrototypeTemplate();
				V8PxSerialStream::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				//objTemp->Set(String::New("storeBuffer"), FunctionTemplate::New(InvocationCallback(V8PxSerialStream::storeBuffer)));
				//objTemp->Set(String::New("getTotalStoredSize"), FunctionTemplate::New(InvocationCallback(V8PxSerialStream::getTotalStoredSize)));

			//PxMeshScale
				V8PxMeshScale::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxMeshScale::PxMeshScaleConstructor));
				V8PxMeshScale::getTemplate()->SetClassName(String::New("PxMeshScale"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxMeshScale"), V8PxMeshScale::getTemplate());

				objTemp = V8PxMeshScale::getTemplate()->PrototypeTemplate();
				V8PxMeshScale::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxMeshScale::getTemplate()->Set(String::New("createIdentity"), FunctionTemplate::New(InvocationCallback( V8PxMeshScale::createIdentity )));

				V8PxMeshScale::getTemplate()->InstanceTemplate()->SetAccessor(String::New("scale"), V8PxMeshScale::getScale, V8PxMeshScale::setScale);
				V8PxMeshScale::getTemplate()->InstanceTemplate()->SetAccessor(String::New("rotation"), V8PxMeshScale::getRotation, V8PxMeshScale::setRotation);

				objTemp->Set(String::New("isIdentity"), FunctionTemplate::New(InvocationCallback(V8PxMeshScale::isIdentity)));
				objTemp->Set(String::New("getInverse"), FunctionTemplate::New(InvocationCallback(V8PxMeshScale::getInverse)));
				objTemp->Set(String::New("createIdentity"), FunctionTemplate::New(InvocationCallback(V8PxMeshScale::createIdentity)));
				objTemp->Set(String::New("toMat33"), FunctionTemplate::New(InvocationCallback(V8PxMeshScale::toMat33)));

			//PxConvexMesh
				V8PxConvexMesh::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxConvexMesh::getTemplate()->SetClassName(String::New("PxConvexMesh"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxConvexMesh"), V8PxConvexMesh::getTemplate());

				V8PxConvexMesh::getTemplate()->Inherit(V8PxSerializable::getTemplate());

				objTemp = V8PxConvexMesh::getTemplate()->PrototypeTemplate();
				V8PxConvexMesh::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("getNbVertices"), FunctionTemplate::New(InvocationCallback(V8PxConvexMesh::getNbVertices)));
				objTemp->Set(String::New("getVertices"), FunctionTemplate::New(InvocationCallback(V8PxConvexMesh::getVertices)));
				objTemp->Set(String::New("getIndexBuffer"), FunctionTemplate::New(InvocationCallback(V8PxConvexMesh::getIndexBuffer)));
				objTemp->Set(String::New("getNbPolygons"), FunctionTemplate::New(InvocationCallback(V8PxConvexMesh::getNbPolygons)));
				objTemp->Set(String::New("getPolygonData"), FunctionTemplate::New(InvocationCallback(V8PxConvexMesh::getPolygonData)));
				objTemp->Set(String::New("release"), FunctionTemplate::New(InvocationCallback(V8PxConvexMesh::release)));
				objTemp->Set(String::New("getReferenceCount"), FunctionTemplate::New(InvocationCallback(V8PxConvexMesh::getReferenceCount)));
				objTemp->Set(String::New("getMassInformation"), FunctionTemplate::New(InvocationCallback(V8PxConvexMesh::getMassInformation)));
			
			//PxHeightField
				V8PxHeightField::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxHeightField::getTemplate()->SetClassName(String::New("PxHeightField"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxHeightField"), V8PxHeightField::getTemplate());

				V8PxHeightField::getTemplate()->Inherit(V8PxSerializable::getTemplate());

				objTemp = V8PxHeightField::getTemplate()->PrototypeTemplate();
				V8PxHeightField::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("release"), FunctionTemplate::New(InvocationCallback(V8PxHeightField::release)));
				objTemp->Set(String::New("saveCells"), FunctionTemplate::New(InvocationCallback(V8PxHeightField::release)));
				objTemp->Set(String::New("getNbRows"), FunctionTemplate::New(InvocationCallback(V8PxHeightField::release)));
				objTemp->Set(String::New("getNbColumns"), FunctionTemplate::New(InvocationCallback(V8PxHeightField::release)));
				objTemp->Set(String::New("getFormat"), FunctionTemplate::New(InvocationCallback(V8PxHeightField::release)));
				objTemp->Set(String::New("getSampleStride"), FunctionTemplate::New(InvocationCallback(V8PxHeightField::release)));
				objTemp->Set(String::New("getThickness"), FunctionTemplate::New(InvocationCallback(V8PxHeightField::release)));
				objTemp->Set(String::New("getConvexEdgeThreshold"), FunctionTemplate::New(InvocationCallback(V8PxHeightField::release)));
				objTemp->Set(String::New("getFlags"), FunctionTemplate::New(InvocationCallback(V8PxHeightField::release)));
				objTemp->Set(String::New("getHeight"), FunctionTemplate::New(InvocationCallback(V8PxHeightField::release)));
				objTemp->Set(String::New("getReferenceCount"), FunctionTemplate::New(InvocationCallback(V8PxHeightField::getReferenceCount)));
				objTemp->Set(String::New("getMassInformation"), FunctionTemplate::New(InvocationCallback(V8PxHeightField::getTriangleMaterialIndex)));

			//PxFilterData
				V8PxFilterData::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxFilterData::PxFilterDataConstructor));
				V8PxFilterData::getTemplate()->SetClassName(String::New("PxFilterData"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxFilterData"), V8PxFilterData::getTemplate());

				objTemp = V8PxFilterData::getTemplate()->PrototypeTemplate();
				V8PxFilterData::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxFilterData::getTemplate()->InstanceTemplate()->SetAccessor(String::New("word0"), V8PxFilterData::getword0, V8PxFilterData::setword0);
				V8PxFilterData::getTemplate()->InstanceTemplate()->SetAccessor(String::New("word1"), V8PxFilterData::getword1, V8PxFilterData::setword1);
				V8PxFilterData::getTemplate()->InstanceTemplate()->SetAccessor(String::New("word2"), V8PxFilterData::getword2, V8PxFilterData::setword2);
				V8PxFilterData::getTemplate()->InstanceTemplate()->SetAccessor(String::New("word3"), V8PxFilterData::getword3, V8PxFilterData::setword3);

				objTemp->Set(String::New("setToDefault"), FunctionTemplate::New(InvocationCallback(V8PxFilterData::setToDefault)));

			//PxHullPolygon
				V8PxHullPolygon::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxHullPolygon::PxHullPolygonConstructor));
				V8PxHullPolygon::getTemplate()->SetClassName(String::New("PxHullPolygon"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxHullPolygon"), V8PxHullPolygon::getTemplate());

				objTemp = V8PxHullPolygon::getTemplate()->PrototypeTemplate();
				V8PxHullPolygon::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				//objTemp->SetAccessor(String::New("mPlane"), V8PxHullPolygon::getmPlane); //set in constructor
				V8PxHullPolygon::getTemplate()->InstanceTemplate()->SetAccessor(String::New("mNbVerts"), V8PxHullPolygon::getmNbVerts, V8PxHullPolygon::setmNbVerts);
				V8PxHullPolygon::getTemplate()->InstanceTemplate()->SetAccessor(String::New("mIndexBase"), V8PxHullPolygon::getmIndexBase, V8PxHullPolygon::setmIndexBase);

			//PxMaterial
				V8PxMaterial::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxMaterial::getTemplate()->SetClassName(String::New("PxMaterial"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxMaterial"), V8PxMaterial::getTemplate());

				V8PxMaterial::getTemplate()->Inherit(V8PxSerializable::getTemplate());

				objTemp = V8PxMaterial::getTemplate()->PrototypeTemplate();
				V8PxMaterial::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxMaterial::getTemplate()->InstanceTemplate()->SetAccessor(String::New("userData"), V8PxMaterial::getUserData, V8PxMaterial::setUserData);

				objTemp->Set(String::New("release"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::release)));
				objTemp->Set(String::New("setDynamicFriction"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::setDynamicFriction)));
				objTemp->Set(String::New("getDynamicFriction"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::getDynamicFriction)));
				objTemp->Set(String::New("setStaticFriction"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::setStaticFriction)));
				objTemp->Set(String::New("getStaticFriction"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::getStaticFriction)));
				objTemp->Set(String::New("setRestitution"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::setRestitution)));
				objTemp->Set(String::New("getRestitution"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::getRestitution)));
				/*objTemp->Set(String::New("setDynamicFrictionV"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::setDynamicFrictionV)));
				objTemp->Set(String::New("getDynamicFrictionV"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::getDynamicFrictionV)));
				objTemp->Set(String::New("setStaticFrictionV"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::setStaticFrictionV)));
				objTemp->Set(String::New("getStaticFrictionV"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::getStaticFrictionV)));
				objTemp->Set(String::New("setDirOfAnisotropy"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::setDirOfAnisotropy)));
				objTemp->Set(String::New("getDirOfAnisotropy"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::getDirOfAnisotropy)));*/
				objTemp->Set(String::New("setFlag"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::setFlag)));
				objTemp->Set(String::New("setFlags"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::setFlags)));
				objTemp->Set(String::New("getFlags"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::getFlags)));
				objTemp->Set(String::New("setFrictionCombineMode"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::setFrictionCombineMode)));
				objTemp->Set(String::New("getFrictionCombineMode"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::getFrictionCombineMode)));
				objTemp->Set(String::New("setRestitutionCombineMode"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::setRestitutionCombineMode)));
				objTemp->Set(String::New("getRestitutionCombineMode"), FunctionTemplate::New(InvocationCallback(V8PxMaterial::getRestitutionCombineMode)));

			//PxObserver
				V8PxObserver::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxObserver::getTemplate()->SetClassName(String::New("PxObserver"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxObserver"), V8PxObserver::getTemplate());

				V8PxObserver::getTemplate()->Inherit(V8PxSerializable::getTemplate());

				objTemp = V8PxObserver::getTemplate()->PrototypeTemplate();
				V8PxObserver::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("onRelease"), FunctionTemplate::New(InvocationCallback(V8PxObserver::onRelease)));
			
			//PxObservable
				V8PxObservable::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxObservable::getTemplate()->SetClassName(String::New("PxObservable"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxObservable"), V8PxObservable::getTemplate());

				objTemp = V8PxObservable::getTemplate()->PrototypeTemplate();
				objTemp->SetInternalFieldCount(1);

				objTemp->Set(String::New("getObservableType"), FunctionTemplate::New(InvocationCallback(V8PxObservable::getObservableType)));
				objTemp->Set(String::New("registerObserver"), FunctionTemplate::New(InvocationCallback(V8PxObservable::registerObserver)));
				objTemp->Set(String::New("unregisterObserver"), FunctionTemplate::New(InvocationCallback(V8PxObservable::unregisterObserver)));
				objTemp->Set(String::New("getNbObservers"), FunctionTemplate::New(InvocationCallback(V8PxObservable::getNbObservers)));
				objTemp->Set(String::New("getObservers"), FunctionTemplate::New(InvocationCallback(V8PxObservable::getObservers)));

			//PxActor
				V8PxActor::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxActor::getTemplate()->SetClassName(String::New("PxActor"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxActor"), V8PxActor::getTemplate());

				//FIXME:I don't think I can do 2 at once
				V8PxActor::getTemplate()->Inherit(V8PxSerializable::getTemplate());
				V8PxActor::getTemplate()->Inherit(V8PxObservable::getTemplate());

				objTemp = V8PxActor::getTemplate()->PrototypeTemplate();
				V8PxActor::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxActor::getTemplate()->InstanceTemplate()->SetAccessor(String::New("userData"), V8PxActor::getUserData, V8PxActor::setUserData);

				objTemp->Set(String::New("release"), FunctionTemplate::New(InvocationCallback(V8PxActor::release)));
				objTemp->Set(String::New("getType"), FunctionTemplate::New(InvocationCallback(V8PxActor::getType)));
				//objTemp->Set(String::New("is"), FunctionTemplate::New(InvocationCallback(V8PxActor::is)));
				objTemp->Set(String::New("isRigidStatic"), FunctionTemplate::New(InvocationCallback(V8PxActor::isRigidStatic)));
				objTemp->Set(String::New("isRigidDynamic"), FunctionTemplate::New(InvocationCallback(V8PxActor::isRigidDynamic)));
				objTemp->Set(String::New("isParticleSystem"), FunctionTemplate::New(InvocationCallback(V8PxActor::isParticleSystem)));
				objTemp->Set(String::New("isParticleFluid"), FunctionTemplate::New(InvocationCallback(V8PxActor::isParticleFluid)));
				//objTemp->Set(String::New("isDeformable"), FunctionTemplate::New(InvocationCallback(V8PxActor::isDeformable)));
				objTemp->Set(String::New("isArticulationLink"), FunctionTemplate::New(InvocationCallback(V8PxActor::isArticulationLink)));
				objTemp->Set(String::New("isRigidActor"), FunctionTemplate::New(InvocationCallback(V8PxActor::isRigidActor)));
				objTemp->Set(String::New("isRigidBody"), FunctionTemplate::New(InvocationCallback(V8PxActor::isRigidBody)));
				objTemp->Set(String::New("isParticleBase"), FunctionTemplate::New(InvocationCallback(V8PxActor::isParticleBase)));
				objTemp->Set(String::New("getScene"), FunctionTemplate::New(InvocationCallback(V8PxActor::getScene)));
				objTemp->Set(String::New("setName"), FunctionTemplate::New(InvocationCallback(V8PxActor::setName)));
				objTemp->Set(String::New("getName"), FunctionTemplate::New(InvocationCallback(V8PxActor::getName)));
				objTemp->Set(String::New("getWorldBounds"), FunctionTemplate::New(InvocationCallback(V8PxActor::getWorldBounds)));
				objTemp->Set(String::New("setActorFlag"), FunctionTemplate::New(InvocationCallback(V8PxActor::setActorFlag)));
				objTemp->Set(String::New("setActorFlags"), FunctionTemplate::New(InvocationCallback(V8PxActor::setActorFlags)));
				objTemp->Set(String::New("getActorFlags"), FunctionTemplate::New(InvocationCallback(V8PxActor::getActorFlags)));
				objTemp->Set(String::New("setDominanceGroup"), FunctionTemplate::New(InvocationCallback(V8PxActor::setDominanceGroup)));
				objTemp->Set(String::New("getDominanceGroup"), FunctionTemplate::New(InvocationCallback(V8PxActor::getDominanceGroup)));
				objTemp->Set(String::New("setOwnerClient"), FunctionTemplate::New(InvocationCallback(V8PxActor::setOwnerClient)));
				objTemp->Set(String::New("getOwnerClient"), FunctionTemplate::New(InvocationCallback(V8PxActor::getOwnerClient)));
				objTemp->Set(String::New("setClientBehaviorBits"), FunctionTemplate::New(InvocationCallback(V8PxActor::setClientBehaviorBits)));
				objTemp->Set(String::New("getClientBehaviorBits"), FunctionTemplate::New(InvocationCallback(V8PxActor::getClientBehaviorBits)));
				objTemp->Set(String::New("getAggregate"), FunctionTemplate::New(InvocationCallback(V8PxActor::getAggregate)));

			//PxRigidActor
				V8PxRigidActor::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());

				V8PxRigidActor::getTemplate()->Inherit(V8PxActor::getTemplate());

				V8PxRigidActor::getTemplate()->SetClassName(String::New("PxRigidActor"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxRigidActor"), V8PxRigidActor::getTemplate());

				

				objTemp = V8PxRigidActor::getTemplate()->PrototypeTemplate();
				V8PxRigidActor::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("release"), FunctionTemplate::New(InvocationCallback(V8PxRigidActor::release)));
				objTemp->Set(String::New("getGlobalPose"), FunctionTemplate::New(InvocationCallback(V8PxRigidActor::getGlobalPose)));
				objTemp->Set(String::New("setGlobalPose"), FunctionTemplate::New(InvocationCallback(V8PxRigidActor::setGlobalPose)));
				objTemp->Set(String::New("createShape"), FunctionTemplate::New(InvocationCallback(V8PxRigidActor::createShape)));
				objTemp->Set(String::New("getNbShapes"), FunctionTemplate::New(InvocationCallback(V8PxRigidActor::getNbShapes)));
				objTemp->Set(String::New("getShapes"), FunctionTemplate::New(InvocationCallback(V8PxRigidActor::getShapes)));
				objTemp->Set(String::New("getNbConstraints"), FunctionTemplate::New(InvocationCallback(V8PxRigidActor::getNbConstraints)));
				objTemp->Set(String::New("getConstraints"), FunctionTemplate::New(InvocationCallback(V8PxRigidActor::getConstraints)));
				objTemp->Set(String::New("isRigidActor"), FunctionTemplate::New(InvocationCallback(V8PxRigidActor::isRigidActor)));

			//PxRigidBody
				V8PxRigidBody::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxRigidBody::getTemplate()->SetClassName(String::New("PxRigidBody"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxRigidBody"), V8PxRigidBody::getTemplate());

				V8PxRigidBody::getTemplate()->Inherit(V8PxRigidActor::getTemplate());

				objTemp = V8PxRigidBody::getTemplate()->PrototypeTemplate();
				V8PxRigidBody::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("setCMassLocalPose"), FunctionTemplate::New(InvocationCallback(V8PxRigidBody::setCMassLocalPose)));
				objTemp->Set(String::New("getCMassLocalPose"), FunctionTemplate::New(InvocationCallback(V8PxRigidBody::getCMassLocalPose)));
				objTemp->Set(String::New("setMass"), FunctionTemplate::New(InvocationCallback(V8PxRigidBody::setMass)));
				objTemp->Set(String::New("getMass"), FunctionTemplate::New(InvocationCallback(V8PxRigidBody::getMass)));
				objTemp->Set(String::New("setMassSpaceInertiaTensor"), FunctionTemplate::New(InvocationCallback(V8PxRigidBody::setMassSpaceInertiaTensor)));
				objTemp->Set(String::New("getMassSpaceInertiaTensor"), FunctionTemplate::New(InvocationCallback(V8PxRigidBody::getMassSpaceInertiaTensor)));
				objTemp->Set(String::New("getLinearVelocity"), FunctionTemplate::New(InvocationCallback(V8PxRigidBody::getLinearVelocity)));
				objTemp->Set(String::New("setLinearVelocity"), FunctionTemplate::New(InvocationCallback(V8PxRigidBody::setLinearVelocity)));
				objTemp->Set(String::New("getAngularVelocity"), FunctionTemplate::New(InvocationCallback(V8PxRigidBody::getAngularVelocity)));
				objTemp->Set(String::New("setAngularVelocity"), FunctionTemplate::New(InvocationCallback(V8PxRigidBody::setAngularVelocity)));
				objTemp->Set(String::New("addForce"), FunctionTemplate::New(InvocationCallback(V8PxRigidBody::addForce)));
				objTemp->Set(String::New("addTorque"), FunctionTemplate::New(InvocationCallback(V8PxRigidBody::addTorque)));
				objTemp->Set(String::New("clearForce"), FunctionTemplate::New(InvocationCallback(V8PxRigidBody::clearForce)));
				objTemp->Set(String::New("clearTorque"), FunctionTemplate::New(InvocationCallback(V8PxRigidBody::clearTorque)));
				objTemp->Set(String::New("isRigidBody"), FunctionTemplate::New(InvocationCallback(V8PxRigidBody::isRigidBody)));

			//PxParticleBase
				V8PxParticleBase::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxParticleBase::getTemplate()->SetClassName(String::New("PxParticleBase"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxParticleBase"), V8PxParticleBase::getTemplate());

				V8PxParticleBase::getTemplate()->Inherit(V8PxActor::getTemplate());

				objTemp = V8PxParticleBase::getTemplate()->PrototypeTemplate();
				V8PxParticleBase::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("lockParticleReadData"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::lockParticleReadData)));
				objTemp->Set(String::New("createParticles"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::createParticles)));
				objTemp->Set(String::New("releaseParticles"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::releaseParticles)));
				objTemp->Set(String::New("setPositions"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::setPositions)));
				objTemp->Set(String::New("setVelocities"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::setVelocities)));
				objTemp->Set(String::New("setRestOffsets"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::setRestOffsets)));
				objTemp->Set(String::New("addForces"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::addForces)));
				objTemp->Set(String::New("getDamping"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::getDamping)));
				objTemp->Set(String::New("setDamping"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::setDamping)));
				objTemp->Set(String::New("getExternalAcceleration"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::getExternalAcceleration)));
				objTemp->Set(String::New("setExternalAcceleration"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::setExternalAcceleration)));
				objTemp->Set(String::New("getProjectionPlane"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::getProjectionPlane)));
				objTemp->Set(String::New("setProjectionPlane"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::setProjectionPlane)));
				objTemp->Set(String::New("getParticleMass"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::getParticleMass)));
				objTemp->Set(String::New("setParticleMass"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::setParticleMass)));
				objTemp->Set(String::New("getRestitution"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::getRestitution)));
				objTemp->Set(String::New("setRestitution"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::setRestitution)));
				objTemp->Set(String::New("getDynamicFriction"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::getDynamicFriction)));
				objTemp->Set(String::New("setDynamicFriction"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::setDynamicFriction)));
				objTemp->Set(String::New("getStaticFriction"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::getStaticFriction)));
				objTemp->Set(String::New("setStaticFriction"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::setStaticFriction)));
				objTemp->Set(String::New("setSimulationFilterData"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::setSimulationFilterData)));
				objTemp->Set(String::New("getSimulationFilterData"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::getSimulationFilterData)));
				objTemp->Set(String::New("resetFiltering"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::resetFiltering)));
				objTemp->Set(String::New("setParticleBaseFlag"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::setParticleBaseFlag)));
				objTemp->Set(String::New("getParticleBaseFlags"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::getParticleBaseFlags)));
				objTemp->Set(String::New("getMaxParticles"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::getMaxParticles)));
				objTemp->Set(String::New("getMaxMotionDistance"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::getMaxMotionDistance)));
				objTemp->Set(String::New("getRestOffset"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::getRestOffset)));
				objTemp->Set(String::New("getContactOffset"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::getContactOffset)));
				objTemp->Set(String::New("getGridSize"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::getGridSize)));
				objTemp->Set(String::New("getParticleReadDataFlags"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::getParticleReadDataFlags)));
				objTemp->Set(String::New("isParticleBase"), FunctionTemplate::New(InvocationCallback(V8PxParticleBase::isParticleBase)));

			//PxLockedData
				V8PxLockedData::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxLockedData::getTemplate()->SetClassName(String::New("PxLockedData"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxLockedData"), V8PxLockedData::getTemplate());

				objTemp = V8PxLockedData::getTemplate()->PrototypeTemplate();
				V8PxLockedData::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("getDataAccessFlags"), FunctionTemplate::New(InvocationCallback(V8PxLockedData::getDataAccessFlags)));
				objTemp->Set(String::New("unlock"), FunctionTemplate::New(InvocationCallback(V8PxLockedData::unlock)));

			//PxStrideIterator
				V8PxStrideIterator<PxVec3>::initTemplate("PxVec3", physXFuncTemplateBase);
				V8PxStrideIterator<PxF32>::initTemplate("PxF32", physXFuncTemplateBase);
				V8PxStrideIterator<PxParticleFlags>::initTemplate("PxParticleFlags", physXFuncTemplateBase);

			//PxParticleReadData
				V8PxParticleReadData::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxParticleReadData::getTemplate()->SetClassName(String::New("PxParticleReadData"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxParticleReadData"), V8PxParticleReadData::getTemplate());

				V8PxParticleReadData::getTemplate()->Inherit(V8PxLockedData::getTemplate());

				objTemp = V8PxParticleReadData::getTemplate()->PrototypeTemplate();
				V8PxParticleReadData::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				V8PxParticleReadData::getTemplate()->InstanceTemplate()->SetAccessor(String::New("numValidParticles"), V8PxParticleReadData::getNumValidParticles, V8PxParticleReadData::setNumValidParticles);
				V8PxParticleReadData::getTemplate()->InstanceTemplate()->SetAccessor(String::New("validParticleRange"), V8PxParticleReadData::getValidParticleRange, V8PxParticleReadData::setValidParticleRange);
				//V8PxParticleReadData::getTemplate()->InstanceTemplate()->SetAccessor(String::New("validParticleBitmap"), V8PxParticleReadData::getValidParticleBitmap, V8PxParticleReadData::setValidParticleBitmap);
				V8PxParticleReadData::getTemplate()->InstanceTemplate()->SetAccessor(String::New("validParticleBitmap"), V8PxParticleReadData::getValidParticleBitmap, NULL);
				V8PxParticleReadData::getTemplate()->InstanceTemplate()->SetAccessor(String::New("positionBuffer"), V8PxParticleReadData::getPositionBuffer, NULL);
				V8PxParticleReadData::getTemplate()->InstanceTemplate()->SetAccessor(String::New("velocityBuffer"), V8PxParticleReadData::getVelocityBuffer, NULL);
				V8PxParticleReadData::getTemplate()->InstanceTemplate()->SetAccessor(String::New("restOffsetBuffer"), V8PxParticleReadData::getRestOffsetBuffer, NULL);
				V8PxParticleReadData::getTemplate()->InstanceTemplate()->SetAccessor(String::New("flagsBuffer"), V8PxParticleReadData::getFlagsBuffer, NULL);
				V8PxParticleReadData::getTemplate()->InstanceTemplate()->SetAccessor(String::New("collisionNormalBuffer"), V8PxParticleReadData::getCollisionNormalBuffer, NULL);

				objTemp->Set(String::New("getDataAccessFlags"), FunctionTemplate::New(InvocationCallback(V8PxParticleReadData::getDataAccessFlags)));
				objTemp->Set(String::New("unlock"), FunctionTemplate::New(InvocationCallback(V8PxParticleReadData::unlock)));

			//PxRigidDynamic
				V8PxRigidDynamic::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxRigidDynamic::getTemplate()->SetClassName(String::New("PxRigidDynamic"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxRigidDynamic"), V8PxRigidDynamic::getTemplate());

				V8PxRigidDynamic::getTemplate()->Inherit(V8PxRigidBody::getTemplate());

				objTemp = V8PxRigidDynamic::getTemplate()->PrototypeTemplate();
				V8PxRigidDynamic::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("setKinematicTarget"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::setKinematicTarget)));
				objTemp->Set(String::New("getKinematicTarget"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::getKinematicTarget)));
				objTemp->Set(String::New("setLinearDamping"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::setLinearDamping)));
				objTemp->Set(String::New("getLinearDamping"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::getLinearDamping)));
				objTemp->Set(String::New("setAngularDamping"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::setAngularDamping)));
				objTemp->Set(String::New("getAngularDamping"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::getAngularDamping)));
				objTemp->Set(String::New("setMaxAngularVelocity"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::setMaxAngularVelocity)));
				objTemp->Set(String::New("getMaxAngularVelocity"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::getMaxAngularVelocity)));
				objTemp->Set(String::New("isSleeping"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::isSleeping)));
				objTemp->Set(String::New("setSleepThreshold"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::setSleepThreshold)));
				objTemp->Set(String::New("getSleepThreshold"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::getSleepThreshold)));
				objTemp->Set(String::New("wakeUp"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::wakeUp)));
				objTemp->Set(String::New("putToSleep"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::putToSleep)));
				objTemp->Set(String::New("setSolverIterationCounts"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::setSolverIterationCounts)));
				objTemp->Set(String::New("getSolverIterationCounts"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::getSolverIterationCounts)));
				objTemp->Set(String::New("getContactReportThreshold"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::getContactReportThreshold)));
				objTemp->Set(String::New("setContactReportThreshold"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::setContactReportThreshold)));
				objTemp->Set(String::New("setRigidDynamicFlag"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::setRigidDynamicFlag)));
				objTemp->Set(String::New("setRigidDynamicFlags"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::setRigidDynamicFlags)));
				objTemp->Set(String::New("getRigidDynamicFlags"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::getRigidDynamicFlags)));
				objTemp->Set(String::New("getConcreteTypeName"), FunctionTemplate::New(InvocationCallback(V8PxRigidDynamic::getConcreteTypeName)));

			//PxRigidStatic
				V8PxRigidStatic::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxRigidStatic::getTemplate()->SetClassName(String::New("PxRigidStatic"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxRigidStatic"), V8PxRigidStatic::getTemplate());

				V8PxRigidStatic::getTemplate()->Inherit(V8PxRigidActor::getTemplate());

				objTemp = V8PxRigidStatic::getTemplate()->PrototypeTemplate();
				V8PxRigidStatic::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("getConcreteTypeName"), FunctionTemplate::New(InvocationCallback(V8PxRigidStatic::getConcreteTypeName)));

			//PxScene
				V8PxScene::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxScene::getTemplate()->SetClassName(String::New("PxScene"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxScene"), V8PxScene::getTemplate());

				objTemp = V8PxScene::getTemplate()->PrototypeTemplate();
				V8PxScene::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("release"), FunctionTemplate::New(InvocationCallback(V8PxScene::release)));
				objTemp->Set(String::New("setFlag"), FunctionTemplate::New(InvocationCallback(V8PxScene::setFlag)));
				objTemp->Set(String::New("getFlags"), FunctionTemplate::New(InvocationCallback(V8PxScene::getFlags)));
				objTemp->Set(String::New("setGravity"), FunctionTemplate::New(InvocationCallback(V8PxScene::setGravity)));
				objTemp->Set(String::New("getGravity"), FunctionTemplate::New(InvocationCallback(V8PxScene::getGravity)));
				//objTemp->Set(String::New("getPhysics"), FunctionTemplate::New(InvocationCallback(V8PxScene::getPhysics)));
				objTemp->Set(String::New("getTimestamp"), FunctionTemplate::New(InvocationCallback(V8PxScene::getTimestamp)));
				objTemp->Set(String::New("getSceneQueryStaticTimestamp"), FunctionTemplate::New(InvocationCallback(V8PxScene::getSceneQueryStaticTimestamp)));
				objTemp->Set(String::New("setBounceThresholdVelocity"), FunctionTemplate::New(InvocationCallback(V8PxScene::setBounceThresholdVelocity)));
				objTemp->Set(String::New("getBounceThresholdVelocity"), FunctionTemplate::New(InvocationCallback(V8PxScene::getBounceThresholdVelocity)));

				objTemp->Set(String::New("addActor"), FunctionTemplate::New(InvocationCallback(V8PxScene::addActor)));
				//objTemp->Set(String::New("addActors"), FunctionTemplate::New(InvocationCallback(V8PxScene::addActors)));
				objTemp->Set(String::New("removeActor"), FunctionTemplate::New(InvocationCallback(V8PxScene::removeActor)));
				//objTemp->Set(String::New("getNbActors"), FunctionTemplate::New(InvocationCallback(V8PxScene::getNbActors)));
				//objTemp->Set(String::New("getActors"), FunctionTemplate::New(InvocationCallback(V8PxScene::getActors)));

				objTemp->Set(String::New("raycastAny"), FunctionTemplate::New(InvocationCallback(V8PxScene::raycastAny)));
				objTemp->Set(String::New("raycastSingle"), FunctionTemplate::New(InvocationCallback(V8PxScene::raycastSingle)));
				objTemp->Set(String::New("raycastMultiple"), FunctionTemplate::New(InvocationCallback(V8PxScene::raycastMultiple)));
				objTemp->Set(String::New("sweepAny"), FunctionTemplate::New(InvocationCallback(V8PxScene::sweepAny)));
				objTemp->Set(String::New("sweepSingle"), FunctionTemplate::New(InvocationCallback(V8PxScene::sweepSingle)));
				objTemp->Set(String::New("sweepMultiple"), FunctionTemplate::New(InvocationCallback(V8PxScene::sweepMultiple)));
				objTemp->Set(String::New("overlapMultiple"), FunctionTemplate::New(InvocationCallback(V8PxScene::overlapMultiple)));
				objTemp->Set(String::New("overlapAny"), FunctionTemplate::New(InvocationCallback(V8PxScene::overlapAny)));

			//PxSceneQueryHit
				V8PxSceneQueryHit::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxSceneQueryHit::V8PxSceneQueryHitConstructor));
				V8PxSceneQueryHit::getTemplate()->SetClassName(String::New("PxSceneQueryHit"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxSceneQueryHit"), V8PxSceneQueryHit::getTemplate());

				objTemp = V8PxSceneQueryHit::getTemplate()->PrototypeTemplate();
				V8PxSceneQueryHit::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("getShape"), FunctionTemplate::New(InvocationCallback(V8PxSceneQueryHit::getShape)));
				objTemp->Set(String::New("getFaceIndex"), FunctionTemplate::New(InvocationCallback(V8PxSceneQueryHit::getFaceIndex)));
				objTemp->Set(String::New("getFlags"), FunctionTemplate::New(InvocationCallback(V8PxSceneQueryHit::getFlags)));

			//PxSceneQueryImpactHit
				V8PxSceneQueryImpactHit::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxSceneQueryImpactHit::V8PxSceneQueryImpactHitConstructor));
				V8PxSceneQueryImpactHit::getTemplate()->SetClassName(String::New("PxSceneQueryImpactHit"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxSceneQueryImpactHit"), V8PxSceneQueryImpactHit::getTemplate());

				V8PxSceneQueryImpactHit::getTemplate()->Inherit(V8PxSceneQueryHit::getTemplate());

				objTemp = V8PxSceneQueryImpactHit::getTemplate()->PrototypeTemplate();
				V8PxSceneQueryImpactHit::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("getImpact"), FunctionTemplate::New(InvocationCallback(V8PxSceneQueryImpactHit::getImpact)));
				objTemp->Set(String::New("getNormal"), FunctionTemplate::New(InvocationCallback(V8PxSceneQueryImpactHit::getNormal)));
				objTemp->Set(String::New("getDistance"), FunctionTemplate::New(InvocationCallback(V8PxSceneQueryImpactHit::getDistance)));

			//PxRaycastHit
				V8PxRaycastHit::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxRaycastHit::V8PxRaycastHitConstructor));
				V8PxRaycastHit::getTemplate()->SetClassName(String::New("PxRaycastHit"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxRaycastHit"), V8PxRaycastHit::getTemplate());

				V8PxRaycastHit::getTemplate()->Inherit(V8PxSceneQueryImpactHit::getTemplate());

				objTemp = V8PxRaycastHit::getTemplate()->PrototypeTemplate();
				V8PxRaycastHit::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("getU"), FunctionTemplate::New(InvocationCallback(V8PxRaycastHit::getU)));
				objTemp->Set(String::New("getV"), FunctionTemplate::New(InvocationCallback(V8PxRaycastHit::getV)));

			//PxControllerState
				V8PxControllerState::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxControllerState::V8PxControllerStateConstructor));
				V8PxControllerState::getTemplate()->SetClassName(String::New("PxControllerState"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxControllerState"), V8PxControllerState::getTemplate());

				objTemp = V8PxControllerState::getTemplate()->InstanceTemplate();
				objTemp->SetInternalFieldCount(1);

				objTemp->SetAccessor(v8::String::New("deltaXP"), V8PxControllerState::getDeltaXP, V8PxControllerState::setDeltaXP);
				objTemp->SetAccessor(v8::String::New("touchedShape"), V8PxControllerState::getTouchedShape, V8PxControllerState::setTouchedShape);
				objTemp->SetAccessor(v8::String::New("touchedObstacle"), V8PxControllerState::getTouchedObstacle, V8PxControllerState::setTouchedObstacle);
				objTemp->SetAccessor(v8::String::New("collisionFlags"), V8PxControllerState::getCollisionFlags, V8PxControllerState::setCollisionFlags);
				objTemp->SetAccessor(v8::String::New("standOnAnotherCCT"), V8PxControllerState::getStandOnAnotherCCT, V8PxControllerState::setStandOnAnotherCCT);
				objTemp->SetAccessor(v8::String::New("standOnObstacle"), V8PxControllerState::getStandOnObstacle, V8PxControllerState::setStandOnObstacle);
				objTemp->SetAccessor(v8::String::New("isMovingUp"), V8PxControllerState::getIsMovingUp, V8PxControllerState::setIsMovingUp);

			//PxControllerStats
				V8PxControllerStats::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxControllerStats::V8PxControllerStatsConstructor));
				V8PxControllerStats::getTemplate()->SetClassName(String::New("PxControllerStats"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxControllerStats"), V8PxControllerStats::getTemplate());

				objTemp = V8PxControllerStats::getTemplate()->InstanceTemplate();
				objTemp->SetInternalFieldCount(1);

				objTemp->SetAccessor(v8::String::New("nbIterations"), V8PxControllerStats::getNbIterations, V8PxControllerStats::setNbIterations);
				objTemp->SetAccessor(v8::String::New("nbFullUpdates"), V8PxControllerStats::getNbFullUpdates, V8PxControllerStats::setNbFullUpdates);
				objTemp->SetAccessor(v8::String::New("nbPartialUpdates"), V8PxControllerStats::getNbPartialUpdates, V8PxControllerStats::setNbPartialUpdates);

			//PxController
				V8PxController::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PxController::getTemplate()->SetClassName(String::New("PxController"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxController"), V8PxController::getTemplate());

				objTemp = V8PxController::getTemplate()->PrototypeTemplate();
				V8PxController::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(String::New("getType"), FunctionTemplate::New(InvocationCallback(V8PxController::getType)));
				objTemp->Set(String::New("release"), FunctionTemplate::New(InvocationCallback(V8PxController::release)));
				objTemp->Set(String::New("move"), FunctionTemplate::New(InvocationCallback(V8PxController::move)));
				objTemp->Set(String::New("setPosition"), FunctionTemplate::New(InvocationCallback(V8PxController::setPosition)));
				objTemp->Set(String::New("getPosition"), FunctionTemplate::New(InvocationCallback(V8PxController::getPosition)));
				objTemp->Set(String::New("setFootPosition"), FunctionTemplate::New(InvocationCallback(V8PxController::setFootPosition)));
				objTemp->Set(String::New("getFootPosition"), FunctionTemplate::New(InvocationCallback(V8PxController::getFootPosition)));
				objTemp->Set(String::New("getActor"), FunctionTemplate::New(InvocationCallback(V8PxController::getActor)));
				objTemp->Set(String::New("setStepOffset"), FunctionTemplate::New(InvocationCallback(V8PxController::setStepOffset)));
				objTemp->Set(String::New("getStepOffset"), FunctionTemplate::New(InvocationCallback(V8PxController::getStepOffset)));
				objTemp->Set(String::New("setInteraction"), FunctionTemplate::New(InvocationCallback(V8PxController::setInteraction)));
				objTemp->Set(String::New("getInteraction"), FunctionTemplate::New(InvocationCallback(V8PxController::getInteraction)));
				objTemp->Set(String::New("setNonWalkableMode"), FunctionTemplate::New(InvocationCallback(V8PxController::setNonWalkableMode)));
				objTemp->Set(String::New("getNonWalkableMode"), FunctionTemplate::New(InvocationCallback(V8PxController::getNonWalkableMode)));
				objTemp->Set(String::New("setGroupsBitmask"), FunctionTemplate::New(InvocationCallback(V8PxController::setGroupsBitmask)));
				objTemp->Set(String::New("getGroupsBitmask"), FunctionTemplate::New(InvocationCallback(V8PxController::getGroupsBitmask)));
				objTemp->Set(String::New("getContactOffset"), FunctionTemplate::New(InvocationCallback(V8PxController::getContactOffset)));
				objTemp->Set(String::New("getUpDirection"), FunctionTemplate::New(InvocationCallback(V8PxController::getUpDirection)));
				objTemp->Set(String::New("setUpDirection"), FunctionTemplate::New(InvocationCallback(V8PxController::setUpDirection)));
				objTemp->Set(String::New("getSlopeLimit"), FunctionTemplate::New(InvocationCallback(V8PxController::getSlopeLimit)));
				objTemp->Set(String::New("invalidateCache"), FunctionTemplate::New(InvocationCallback(V8PxController::invalidateCache)));
				objTemp->Set(String::New("getScene"), FunctionTemplate::New(InvocationCallback(V8PxController::getScene)));
				objTemp->Set(String::New("getState"), FunctionTemplate::New(InvocationCallback(V8PxController::getState)));
				objTemp->Set(String::New("getStats"), FunctionTemplate::New(InvocationCallback(V8PxController::getStats)));
				objTemp->Set(String::New("resize"), FunctionTemplate::New(InvocationCallback(V8PxController::resize)));

			//PxControllerFilters
				V8PxControllerFilters::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxControllerFilters::V8PxControllerFiltersConstructor));
				V8PxControllerFilters::getTemplate()->SetClassName(String::New("PxControllerFilters"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxControllerFilters"), V8PxControllerFilters::getTemplate());

				objTemp = V8PxControllerFilters::getTemplate()->InstanceTemplate();
				objTemp->SetInternalFieldCount(1);

				objTemp->SetAccessor(v8::String::New("activeGroups"), V8PxControllerFilters::getActiveGroups, V8PxControllerFilters::setActiveGroups);
				objTemp->SetAccessor(v8::String::New("filterData"), V8PxControllerFilters::getFilterData, V8PxControllerFilters::setFilterData);
				//objTemp->SetAccessor(v8::String::New("filterCallback"), V8PxControllerFilters::getFilterCallback, V8PxControllerFilters::setFilterCallback);
				objTemp->SetAccessor(v8::String::New("filterFlags"), V8PxControllerFilters::getFilterFlags, V8PxControllerFilters::setFilterFlags);

			//PxSceneQueryFilterData
				V8PxSceneQueryFilterData::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxSceneQueryFilterData::V8PxSceneQueryFilterDataConstructor));
				V8PxSceneQueryFilterData::getTemplate()->SetClassName(String::New("PxSceneQueryFilterData"));
				physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxSceneQueryFilterData"), V8PxSceneQueryFilterData::getTemplate());

				objTemp = V8PxSceneQueryFilterData::getTemplate()->InstanceTemplate();
				objTemp->SetInternalFieldCount(1);

				objTemp->SetAccessor(v8::String::New("data"), V8PxSceneQueryFilterData::getData, V8PxSceneQueryFilterData::setData);
				objTemp->SetAccessor(v8::String::New("flags"), V8PxSceneQueryFilterData::getFlags, V8PxSceneQueryFilterData::setFlags);

			//PxControllerDesc
				//V8PxControllerDesc::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New(V8PxControllerDesc::PxControllerDescConstructor));
				//V8PxControllerDesc::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				//V8PxControllerDesc::getTemplate()->SetClassName(String::New("PxControllerDesc"));
				//physXFuncTemplateBase->PrototypeTemplate()->Set(String::New("PxControllerDesc"), V8PxControllerDesc::getTemplate());

				//objTemp = V8PxControllerDesc::getTemplate()->PrototypeTemplate();
				//V8PxControllerDesc::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				//V8PxControllerDesc::getTemplate()->InstanceTemplate()->SetAccessor(String::New("position"), V8PxControllerDesc::getPosition, V8PxControllerDesc::setPosition);
				//V8PxControllerDesc::getTemplate()->InstanceTemplate()->SetAccessor(String::New("upDirection"), V8PxControllerDesc::getUpDirection, V8PxControllerDesc::setUpDirection);
				//V8PxControllerDesc::getTemplate()->InstanceTemplate()->SetAccessor(String::New("slopeLimit"), V8PxControllerDesc::getSlopeLimit, V8PxControllerDesc::setSlopeLimit);
				//V8PxControllerDesc::getTemplate()->InstanceTemplate()->SetAccessor(String::New("contactOffset"), V8PxControllerDesc::getContactOffset, V8PxControllerDesc::setContactOffset);
				//V8PxControllerDesc::getTemplate()->InstanceTemplate()->SetAccessor(String::New("stepOffset"), V8PxControllerDesc::getStepOffset, V8PxControllerDesc::setStepOffset);
				//V8PxControllerDesc::getTemplate()->InstanceTemplate()->SetAccessor(String::New("callback"), V8PxControllerDesc::getCallback, V8PxControllerDesc::setCallback);
				//V8PxControllerDesc::getTemplate()->InstanceTemplate()->SetAccessor(String::New("interactionMode"), V8PxControllerDesc::getInteractionMode, V8PxControllerDesc::setInteractionMode);
				//V8PxControllerDesc::getTemplate()->InstanceTemplate()->SetAccessor(String::New("material"), V8PxControllerDesc::getMaterial, V8PxControllerDesc::setMaterial);
				//V8PxControllerDesc::getTemplate()->InstanceTemplate()->SetAccessor(String::New("userData"), V8PxControllerDesc::getUserData, V8PxControllerDesc::setUserData);

				////objTemp->Set(String::New("isValid"), FunctionTemplate::New(InvocationCallback( V8PxControllerDesc::isValid)));
				//objTemp->Set(String::New("getType"), FunctionTemplate::New(InvocationCallback( V8PxControllerDesc::getType)));

		//ENUMS
				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxSerialOrder"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxSerialOrder", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eCONVEX"), Int32::New(PxSerialOrder::eCONVEX));
				temp->PrototypeTemplate()->Set(String::New("eTRIMESH"), Int32::New(PxSerialOrder::eTRIMESH));
				temp->PrototypeTemplate()->Set(String::New("eHEIGHTFIELD"), Int32::New(PxSerialOrder::eHEIGHTFIELD));
				temp->PrototypeTemplate()->Set(String::New("eDEFMESH"), Int32::New(PxSerialOrder::eDEFMESH));
				temp->PrototypeTemplate()->Set(String::New("eMATERIAL"), Int32::New(PxSerialOrder::eMATERIAL));
				temp->PrototypeTemplate()->Set(String::New("eSHAPE"), Int32::New(PxSerialOrder::eSHAPE));
				temp->PrototypeTemplate()->Set(String::New("eSTATIC"), Int32::New(PxSerialOrder::eSTATIC));
				temp->PrototypeTemplate()->Set(String::New("eDYNAMIC"), Int32::New(PxSerialOrder::eDYNAMIC));
				temp->PrototypeTemplate()->Set(String::New("eDEFAULT"), Int32::New(PxSerialOrder::eDEFAULT));
				temp->PrototypeTemplate()->Set(String::New("eARTICULATION"), Int32::New(PxSerialOrder::eARTICULATION));
				temp->PrototypeTemplate()->Set(String::New("eJOINT"), Int32::New(PxSerialOrder::eJOINT));
				temp->PrototypeTemplate()->Set(String::New("eCONSTRAINT"), Int32::New(PxSerialOrder::eCONSTRAINT));

				//-----------------------------------------------------------------------------------------------------------------------

				/*temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxSerialType"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxSerialType", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eUNDEFINED"), Int32::New(PxSerialType::eUNDEFINED));

				temp->PrototypeTemplate()->Set(String::New("eHEIGHTFIELD"), Int32::New(PxSerialType::eHEIGHTFIELD));
				temp->PrototypeTemplate()->Set(String::New("eCONVEX_MESH"), Int32::New(PxSerialType::eCONVEX_MESH));
				temp->PrototypeTemplate()->Set(String::New("eTRIANGLE_MESH"), Int32::New(PxSerialType::eTRIANGLE_MESH));
				temp->PrototypeTemplate()->Set(String::New("eDEFORMABLE_MESH"), Int32::New(PxSerialType::eDEFORMABLE_MESH));

				temp->PrototypeTemplate()->Set(String::New("eRIGID_DYNAMIC"), Int32::New(PxSerialType::eRIGID_DYNAMIC));
				temp->PrototypeTemplate()->Set(String::New("eRIGID_STATIC"), Int32::New(PxSerialType::eRIGID_STATIC));
				temp->PrototypeTemplate()->Set(String::New("eSHAPE"), Int32::New(PxSerialType::eSHAPE));
				temp->PrototypeTemplate()->Set(String::New("eMATERIAL"), Int32::New(PxSerialType::eMATERIAL));
				temp->PrototypeTemplate()->Set(String::New("eCONSTRAINT"), Int32::New(PxSerialType::eCONSTRAINT));
				temp->PrototypeTemplate()->Set(String::New("eDEFORMABLE"), Int32::New(PxSerialType::eDEFORMABLE));
				temp->PrototypeTemplate()->Set(String::New("ePARTICLE_SYSTEM"), Int32::New(PxSerialType::ePARTICLE_SYSTEM));
				temp->PrototypeTemplate()->Set(String::New("ePARTICLE_FLUID"), Int32::New(PxSerialType::ePARTICLE_FLUID));
				temp->PrototypeTemplate()->Set(String::New("eATTACHMENT"), Int32::New(PxSerialType::eATTACHMENT));
				temp->PrototypeTemplate()->Set(String::New("eAGGREGATE"), Int32::New(PxSerialType::eAGGREGATE));
				temp->PrototypeTemplate()->Set(String::New("eARTICULATION"), Int32::New(PxSerialType::eARTICULATION));
				temp->PrototypeTemplate()->Set(String::New("eARTICULATION_LINK"), Int32::New(PxSerialType::eARTICULATION_LINK));
				temp->PrototypeTemplate()->Set(String::New("eARTICULATION_JOINT"), Int32::New(PxSerialType::eARTICULATION_JOINT));

				temp->PrototypeTemplate()->Set(String::New("eDEFORMABLE_CORE"), Int32::New(PxSerialType::eDEFORMABLE_CORE));

				temp->PrototypeTemplate()->Set(String::New("eUSER_SPHERICAL_JOINT"), Int32::New(PxSerialType::eUSER_SPHERICAL_JOINT));
				temp->PrototypeTemplate()->Set(String::New("eUSER_REVOLUTE_JOINT"), Int32::New(PxSerialType::eUSER_REVOLUTE_JOINT));
				temp->PrototypeTemplate()->Set(String::New("eUSER_PRISMATIC_JOINT"), Int32::New(PxSerialType::eUSER_PRISMATIC_JOINT));
				temp->PrototypeTemplate()->Set(String::New("eUSER_FIXED_JOINT"), Int32::New(PxSerialType::eUSER_FIXED_JOINT));
				temp->PrototypeTemplate()->Set(String::New("eUSER_DISTANCE_JOINT"), Int32::New(PxSerialType::eUSER_DISTANCE_JOINT));
				temp->PrototypeTemplate()->Set(String::New("eUSER_D6_JOINT"), Int32::New(PxSerialType::eUSER_D6_JOINT));

				temp->PrototypeTemplate()->Set(String::New("eUSER_OBSERVER"), Int32::New(PxSerialType::eUSER_OBSERVER));

				temp->PrototypeTemplate()->Set(String::New("eLAST"), Int32::New(PxSerialType::eLAST));*/

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxSerialFlag"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxSerialFlag", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eOWNS_MEMORY"), Int32::New(PxSerialFlag::eOWNS_MEMORY));
				temp->PrototypeTemplate()->Set(String::New("eDISABLE_AUTO_RESOLVE"), Int32::New(PxSerialFlag::eDISABLE_AUTO_RESOLVE));
				temp->PrototypeTemplate()->Set(String::New("eDISABLE_FIELDS"), Int32::New(PxSerialFlag::eDISABLE_FIELDS));
				temp->PrototypeTemplate()->Set(String::New("eIN_SCENE"), Int32::New(PxSerialFlag::eIN_SCENE));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxController"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxController", temp->InstanceTemplate());
				
				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxShapeFlag"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxShapeFlag", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eSIMULATION_SHAPE"), Int32::New(PxShapeFlag::eSIMULATION_SHAPE));
				temp->PrototypeTemplate()->Set(String::New("eSCENE_QUERY_SHAPE"), Int32::New(PxShapeFlag::eSCENE_QUERY_SHAPE));
				temp->PrototypeTemplate()->Set(String::New("eTRIGGER_SHAPE"), Int32::New(PxShapeFlag::eTRIGGER_SHAPE));
				temp->PrototypeTemplate()->Set(String::New("eVISUALIZATION"), Int32::New(PxShapeFlag::eVISUALIZATION));
				temp->PrototypeTemplate()->Set(String::New("ePARTICLE_DRAIN"), Int32::New(PxShapeFlag::ePARTICLE_DRAIN));
				//temp->PrototypeTemplate()->Set(String::New("eDEFORMABLE_DRAIN"), Int32::New(PxShapeFlag::eDEFORMABLE_DRAIN));
				temp->PrototypeTemplate()->Set(String::New("eUSE_SWEPT_BOUNDS"), Int32::New(PxShapeFlag::eUSE_SWEPT_BOUNDS));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxGeometryType"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxGeometryType", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eSPHERE"), Int32::New(PxGeometryType::eSPHERE));
				temp->PrototypeTemplate()->Set(String::New("ePLANE"), Int32::New(PxGeometryType::ePLANE));
				temp->PrototypeTemplate()->Set(String::New("eCAPSULE"), Int32::New(PxGeometryType::eCAPSULE));
				temp->PrototypeTemplate()->Set(String::New("eBOX"), Int32::New(PxGeometryType::eBOX));
				temp->PrototypeTemplate()->Set(String::New("eCONVEXMESH"), Int32::New(PxGeometryType::eCONVEXMESH));
				temp->PrototypeTemplate()->Set(String::New("eTRIANGLEMESH"), Int32::New(PxGeometryType::eTRIANGLEMESH));
				temp->PrototypeTemplate()->Set(String::New("eHEIGHTFIELD"), Int32::New(PxGeometryType::eHEIGHTFIELD));
				temp->PrototypeTemplate()->Set(String::New("eGEOMETRY_COUNT"), Int32::New(PxGeometryType::eGEOMETRY_COUNT));
				temp->PrototypeTemplate()->Set(String::New("eINVALID"), Int32::New(PxGeometryType::eINVALID));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxField"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxField", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eUNDEFINED"), Int32::New(PxField::Enum::eUNDEFINED));
				temp->PrototypeTemplate()->Set(String::New("eBYTE"), Int32::New(PxField::Enum::eBYTE));
				temp->PrototypeTemplate()->Set(String::New("eWORD"), Int32::New(PxField::Enum::eWORD));
				temp->PrototypeTemplate()->Set(String::New("eDWORD"), Int32::New(PxField::Enum::eDWORD));
				temp->PrototypeTemplate()->Set(String::New("eFLOAT"), Int32::New(PxField::Enum::eFLOAT));
				temp->PrototypeTemplate()->Set(String::New("eVEC3"), Int32::New(PxField::Enum::eVEC3));
				temp->PrototypeTemplate()->Set(String::New("eSTRING"), Int32::New(PxField::Enum::eSTRING));
				temp->PrototypeTemplate()->Set(String::New("eSERIAL_PTR"), Int32::New(PxField::Enum::eSERIAL_PTR));
				temp->PrototypeTemplate()->Set(String::New("eSERIAL_EMBEDDED"), Int32::New(PxField::Enum::eSERIAL_EMBEDDED));
				temp->PrototypeTemplate()->Set(String::New("ePX_ARRAY"), Int32::New(PxField::Enum::ePX_ARRAY));
				temp->PrototypeTemplate()->Set(String::New("eLAST"), Int32::New(PxField::Enum::eLAST));
				temp->PrototypeTemplate()->Set(String::New("eFORCE_DWORD"), Int32::New(PxField::Enum::eFORCE_DWORD));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxHeightFieldFormat"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxHeightFieldFormat", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eS16_TM"), Int32::New(PxHeightFieldFormat::Enum::eS16_TM));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxHeightFieldTessFlag"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxHeightFieldTessFlag", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("e0TH_VERTEX_SHARED"), Int32::New(PxHeightFieldTessFlag::Enum::e0TH_VERTEX_SHARED));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxHeightFieldFlag"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxHeightFieldFlag", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eNO_BOUNDARY_EDGES"), Int32::New(PxHeightFieldFlag::Enum::eNO_BOUNDARY_EDGES));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxPairFlag"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxPairFlag", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eRESOLVE_CONTACTS"), Uint32::New(PxPairFlag::Enum::eRESOLVE_CONTACTS));
				temp->PrototypeTemplate()->Set(String::New("eMODIFY_CONTACTS"), Uint32::New(PxPairFlag::Enum::eMODIFY_CONTACTS));
				temp->PrototypeTemplate()->Set(String::New("eNOTIFY_TOUCH_FOUND"), Uint32::New(PxPairFlag::Enum::eNOTIFY_TOUCH_FOUND));
				temp->PrototypeTemplate()->Set(String::New("eNOTIFY_TOUCH_PERSISTS"), Uint32::New(PxPairFlag::Enum::eNOTIFY_TOUCH_PERSISTS));
				temp->PrototypeTemplate()->Set(String::New("eNOTIFY_TOUCH_LOST"), Uint32::New(PxPairFlag::Enum::eNOTIFY_TOUCH_LOST));
				temp->PrototypeTemplate()->Set(String::New("eNOTIFY_THRESHOLD_FORCE_FOUND"), Uint32::New(PxPairFlag::Enum::eNOTIFY_THRESHOLD_FORCE_FOUND));
				temp->PrototypeTemplate()->Set(String::New("eNOTIFY_THRESHOLD_FORCE_PERSISTS"), Uint32::New(PxPairFlag::Enum::eNOTIFY_THRESHOLD_FORCE_PERSISTS));
				temp->PrototypeTemplate()->Set(String::New("eNOTIFY_THRESHOLD_FORCE_LOST"), Uint32::New(PxPairFlag::Enum::eNOTIFY_THRESHOLD_FORCE_LOST));
				temp->PrototypeTemplate()->Set(String::New("eNOTIFY_CONTACT_POINTS"), Uint32::New(PxPairFlag::Enum::eNOTIFY_CONTACT_POINTS));
				//temp->PrototypeTemplate()->Set(String::New("eNOTIFY_CONTACT_FORCES"), Uint32::New(PxPairFlag::Enum::eNOTIFY_CONTACT_FORCES));
				//temp->PrototypeTemplate()->Set(String::New("eNOTIFY_CONTACT_FORCE_PER_POINT"), Uint32::New(PxPairFlag::Enum::eNOTIFY_CONTACT_FORCE_PER_POINT));
				//temp->PrototypeTemplate()->Set(String::New("eNOTIFY_CONTACT_FEATURE_INDICES_PER_POINT"), Uint32::New(PxPairFlag::Enum::eNOTIFY_CONTACT_FEATURE_INDICES_PER_POINT));
				//temp->PrototypeTemplate()->Set(String::New("eSWEPT_CONTACT_GENERATION"), Uint32::New(PxPairFlag::Enum::eSWEPT_CONTACT_GENERATION));
				temp->PrototypeTemplate()->Set(String::New("eSWEPT_INTEGRATION_LINEAR"), Uint32::New(PxPairFlag::Enum::eSWEPT_INTEGRATION_LINEAR));
				//temp->PrototypeTemplate()->Set(String::New("eSWEPT_INTEGRATION_FULL"), Uint32::New(PxPairFlag::Enum::eSWEPT_INTEGRATION_FULL));
				temp->PrototypeTemplate()->Set(String::New("eCONTACT_DEFAULT"), Uint32::New(PxPairFlag::Enum::eCONTACT_DEFAULT));
				temp->PrototypeTemplate()->Set(String::New("eTRIGGER_DEFAULT"), Uint32::New(PxPairFlag::Enum::eTRIGGER_DEFAULT));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxFilterFlag"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxFilterFlag", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eKILL"), Uint32::New(PxFilterFlag::Enum::eKILL));
				temp->PrototypeTemplate()->Set(String::New("eSUPPRESS"), Uint32::New(PxFilterFlag::Enum::eSUPPRESS));
				temp->PrototypeTemplate()->Set(String::New("eCALLBACK"), Uint32::New(PxFilterFlag::Enum::eCALLBACK));
				temp->PrototypeTemplate()->Set(String::New("eNOTIFY"), Uint32::New(PxFilterFlag::Enum::eNOTIFY));
				temp->PrototypeTemplate()->Set(String::New("eDEFAULT"), Uint32::New(PxFilterFlag::Enum::eDEFAULT));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxFilterObjectType"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxFilterObjectType", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eRIGID_STATIC"), Uint32::New(PxFilterObjectType::Enum::eRIGID_STATIC));
				temp->PrototypeTemplate()->Set(String::New("eRIGID_DYNAMIC"), Uint32::New(PxFilterObjectType::Enum::eRIGID_DYNAMIC));
				temp->PrototypeTemplate()->Set(String::New("ePARTICLE_SYSTEM"), Uint32::New(PxFilterObjectType::Enum::ePARTICLE_SYSTEM));
				temp->PrototypeTemplate()->Set(String::New("ePARTICLE_FLUID"), Uint32::New(PxFilterObjectType::Enum::ePARTICLE_FLUID));
				//temp->PrototypeTemplate()->Set(String::New("eDEFORMABLE"), Uint32::New(PxFilterObjectType::Enum::eDEFORMABLE));
				temp->PrototypeTemplate()->Set(String::New("eARTICULATION"), Uint32::New(PxFilterObjectType::Enum::eARTICULATION));
				temp->PrototypeTemplate()->Set(String::New("eMAX_TYPE_COUNT"), Uint32::New(PxFilterObjectType::Enum::eMAX_TYPE_COUNT));
				temp->PrototypeTemplate()->Set(String::New("eUNDEFINED"), Uint32::New(PxFilterObjectType::Enum::eMAX_TYPE_COUNT));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxMaterialFlag"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxMaterialFlag", temp->InstanceTemplate());

				//temp->PrototypeTemplate()->Set(String::New("eANISOTROPIC"), Uint32::New(PxMaterialFlag::Enum::eANISOTROPIC));
				temp->PrototypeTemplate()->Set(String::New("eDISABLE_FRICTION"), Uint32::New(PxMaterialFlag::Enum::eDISABLE_FRICTION));
				temp->PrototypeTemplate()->Set(String::New("eDISABLE_STRONG_FRICTION"), Uint32::New(PxMaterialFlag::Enum::eDISABLE_STRONG_FRICTION));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxCombineMode"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxCombineMode", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eAVERAGE"), Uint32::New(PxCombineMode::Enum::eAVERAGE));
				temp->PrototypeTemplate()->Set(String::New("eMIN"), Uint32::New(PxCombineMode::Enum::eMIN));
				temp->PrototypeTemplate()->Set(String::New("eMULTIPLY"), Uint32::New(PxCombineMode::Enum::eMULTIPLY));
				temp->PrototypeTemplate()->Set(String::New("eMAX"), Uint32::New(PxCombineMode::Enum::eMAX));
				temp->PrototypeTemplate()->Set(String::New("eN_VALUES"), Uint32::New(PxCombineMode::Enum::eN_VALUES));
				temp->PrototypeTemplate()->Set(String::New("ePAD_32"), Uint32::New(PxCombineMode::Enum::ePAD_32));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxObservableType"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxObservableType", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eActor"), Uint32::New(PxObservableType::Enum::eActor));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxForceMode"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxForceMode", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eFORCE"), Int32::New(PxForceMode::Enum::eFORCE));
				temp->PrototypeTemplate()->Set(String::New("eIMPULSE"), Int32::New(PxForceMode::Enum::eIMPULSE));
				temp->PrototypeTemplate()->Set(String::New("eVELOCITY_CHANGE"), Int32::New(PxForceMode::Enum::eVELOCITY_CHANGE));
				temp->PrototypeTemplate()->Set(String::New("eACCELERATION"), Int32::New(PxForceMode::Enum::eACCELERATION));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxParticleBaseFlag"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxParticleBaseFlag", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eCOLLISION_TWOWAY"), Int32::New(PxParticleBaseFlag::Enum::eCOLLISION_TWOWAY));
				temp->PrototypeTemplate()->Set(String::New("eCOLLISION_WITH_DYNAMIC_ACTORS"), Int32::New(PxParticleBaseFlag::Enum::eCOLLISION_WITH_DYNAMIC_ACTORS));
				temp->PrototypeTemplate()->Set(String::New("eENABLED"), Int32::New(PxParticleBaseFlag::Enum::eENABLED));
				temp->PrototypeTemplate()->Set(String::New("ePROJECT_TO_PLANE"), Int32::New(PxParticleBaseFlag::Enum::ePROJECT_TO_PLANE));
				temp->PrototypeTemplate()->Set(String::New("ePER_PARTICLE_REST_OFFSET"), Int32::New(PxParticleBaseFlag::Enum::ePER_PARTICLE_REST_OFFSET));
				temp->PrototypeTemplate()->Set(String::New("ePER_PARTICLE_COLLISION_CACHE_HINT"), Int32::New(PxParticleBaseFlag::Enum::ePER_PARTICLE_COLLISION_CACHE_HINT));
				temp->PrototypeTemplate()->Set(String::New("eGPU"), Int32::New(PxParticleBaseFlag::Enum::eGPU));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxParticleReadDataFlag"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxParticleReadDataFlag", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("ePOSITION_BUFFER"), Int32::New(PxParticleReadDataFlag::Enum::ePOSITION_BUFFER));
				temp->PrototypeTemplate()->Set(String::New("eVELOCITY_BUFFER"), Int32::New(PxParticleReadDataFlag::Enum::eVELOCITY_BUFFER));
				temp->PrototypeTemplate()->Set(String::New("eREST_OFFSET_BUFFER"), Int32::New(PxParticleReadDataFlag::Enum::eREST_OFFSET_BUFFER));
				temp->PrototypeTemplate()->Set(String::New("eFLAGS_BUFFER"), Int32::New(PxParticleReadDataFlag::Enum::eFLAGS_BUFFER));
				temp->PrototypeTemplate()->Set(String::New("eCOLLISION_NORMAL_BUFFER"), Int32::New(PxParticleReadDataFlag::Enum::eCOLLISION_NORMAL_BUFFER));
				temp->PrototypeTemplate()->Set(String::New("eDENSITY_BUFFER"), Int32::New(PxParticleReadDataFlag::Enum::eDENSITY_BUFFER));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxDataAccessFlag"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxDataAccessFlag", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eREADABLE"), Uint32::New(PxDataAccessFlag::Enum::eREADABLE));
				temp->PrototypeTemplate()->Set(String::New("eWRITABLE"), Uint32::New(PxDataAccessFlag::Enum::eWRITABLE));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxRigidDynamicFlag"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxRigidDynamicFlag", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eKINEMATIC"), Uint32::New(PxRigidDynamicFlag::Enum::eKINEMATIC));
				temp->PrototypeTemplate()->Set(String::New("eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES"), Uint32::New(PxRigidDynamicFlag::Enum::eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxSceneQueryFlag"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxSceneQueryFlag", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eIMPACT"), Uint32::New(PxSceneQueryFlag::Enum::eIMPACT));
				temp->PrototypeTemplate()->Set(String::New("eNORMAL"), Uint32::New(PxSceneQueryFlag::Enum::eNORMAL));
				temp->PrototypeTemplate()->Set(String::New("eDISTANCE"), Uint32::New(PxSceneQueryFlag::Enum::eDISTANCE));
				temp->PrototypeTemplate()->Set(String::New("eUV"), Uint32::New(PxSceneQueryFlag::Enum::eUV));
				temp->PrototypeTemplate()->Set(String::New("eINITIAL_OVERLAP"), Uint32::New(PxSceneQueryFlag::Enum::eINITIAL_OVERLAP));
				temp->PrototypeTemplate()->Set(String::New("eINITIAL_OVERLAP_KEEP"), Uint32::New(PxSceneQueryFlag::Enum::eINITIAL_OVERLAP_KEEP));
				temp->PrototypeTemplate()->Set(String::New("eTOUCHING_HIT"), Uint32::New(PxSceneQueryFlag::Enum::eTOUCHING_HIT));
				temp->PrototypeTemplate()->Set(String::New("eBLOCKING_HIT"), Uint32::New(PxSceneQueryFlag::Enum::eBLOCKING_HIT));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxCCTNonWalkableMode"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxCCTNonWalkableMode", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("ePREVENT_CLIMBING"), Uint32::New(PxCCTNonWalkableMode::Enum::ePREVENT_CLIMBING));
				temp->PrototypeTemplate()->Set(String::New("eFORCE_SLIDING"), Uint32::New(PxCCTNonWalkableMode::Enum::eFORCE_SLIDING));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxControllerFlag"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxControllerFlag", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eCOLLISION_SIDES"), Uint32::New(PxControllerFlag::Enum::eCOLLISION_SIDES));
				temp->PrototypeTemplate()->Set(String::New("eCOLLISION_UP"), Uint32::New(PxControllerFlag::Enum::eCOLLISION_UP));
				temp->PrototypeTemplate()->Set(String::New("eCOLLISION_DOWN"), Uint32::New(PxControllerFlag::Enum::eCOLLISION_DOWN));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxControllerShapeType"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxControllerShapeType", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eBOX"), Int32::New(PxControllerShapeType::eBOX));
				temp->PrototypeTemplate()->Set(String::New("eCAPSULE"), Int32::New(PxControllerShapeType::eCAPSULE));
				temp->PrototypeTemplate()->Set(String::New("eFORCE_DWORD"), Int32::New(PxControllerShapeType::eFORCE_DWORD));

				//-----------------------------------------------------------------------------------------------------------------------

				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxCCTInteractionMode"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxCCTInteractionMode", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eINCLUDE"), Int32::New(PxCCTInteractionMode::eINCLUDE));
				temp->PrototypeTemplate()->Set(String::New("eEXCLUDE"), Int32::New(PxCCTInteractionMode::eEXCLUDE));
				temp->PrototypeTemplate()->Set(String::New("eUSE_FILTER"), Int32::New(PxCCTInteractionMode::eUSE_FILTER));

				//-----------------------------------------------------------------------------------------------------------------------
				
				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxSceneQueryFilterFlag"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxSceneQueryFilterFlag", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eSTATIC"), Int32::New(PxSceneQueryFilterFlag::eSTATIC));
				temp->PrototypeTemplate()->Set(String::New("eDYNAMIC"), Int32::New(PxSceneQueryFilterFlag::eDYNAMIC));
				temp->PrototypeTemplate()->Set(String::New("ePREFILTER"), Int32::New(PxSceneQueryFilterFlag::ePREFILTER));
				temp->PrototypeTemplate()->Set(String::New("ePOSTFILTER"), Int32::New(PxSceneQueryFilterFlag::ePOSTFILTER));
				temp->PrototypeTemplate()->Set(String::New("eMESH_MULTIPLE"), Int32::New(PxSceneQueryFilterFlag::eMESH_MULTIPLE));
				temp->PrototypeTemplate()->Set(String::New("eBACKFACE"), Int32::New(PxSceneQueryFilterFlag::eBACKFACE));

				//-----------------------------------------------------------------------------------------------------------------------
				
				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxSceneQueryHitType"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxSceneQueryHitType", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("eNONE"), Int32::New(PxSceneQueryHitType::eNONE));
				temp->PrototypeTemplate()->Set(String::New("eTOUCH"), Int32::New(PxSceneQueryHitType::eTOUCH));
				temp->PrototypeTemplate()->Set(String::New("eBLOCK"), Int32::New(PxSceneQueryHitType::eBLOCK));


		//Functions
				physXFuncTemplate->PrototypeTemplate()->Set(String::New("toVec3"),			FunctionTemplate::New(func_toVec3));
			//Math
				temp = FunctionTemplate::New();
				temp->SetClassName(String::New("PxMath"));
				physXFuncTemplate->PrototypeTemplate()->Set("PxMath", temp->InstanceTemplate());

				temp->PrototypeTemplate()->Set(String::New("Max"),			FunctionTemplate::New(func_math_max));
				temp->PrototypeTemplate()->Set(String::New("Min"),			FunctionTemplate::New(func_math_min));
				temp->PrototypeTemplate()->Set(String::New("Abs"),			FunctionTemplate::New(func_math_abs));
				temp->PrototypeTemplate()->Set(String::New("Equals"),		FunctionTemplate::New(func_math_equals));
				temp->PrototypeTemplate()->Set(String::New("Clamp"),		FunctionTemplate::New(func_math_clamp));
				temp->PrototypeTemplate()->Set(String::New("Sqrt"),			FunctionTemplate::New(func_math_sqrt));
				temp->PrototypeTemplate()->Set(String::New("RecipSqrt"),	FunctionTemplate::New(func_math_recipSqrt));
				temp->PrototypeTemplate()->Set(String::New("Sin"),			FunctionTemplate::New(func_math_sin));
				temp->PrototypeTemplate()->Set(String::New("Cos"),			FunctionTemplate::New(func_math_cos));
				temp->PrototypeTemplate()->Set(String::New("Tan"),			FunctionTemplate::New(func_math_tan));
				temp->PrototypeTemplate()->Set(String::New("Asin"),			FunctionTemplate::New(func_math_asin));
				temp->PrototypeTemplate()->Set(String::New("Acos"),			FunctionTemplate::New(func_math_acos));
				temp->PrototypeTemplate()->Set(String::New("Atan"),			FunctionTemplate::New(func_math_atan));
				temp->PrototypeTemplate()->Set(String::New("Atan2"),		FunctionTemplate::New(func_math_atan2));
				temp->PrototypeTemplate()->Set(String::New("IsFinite"),		FunctionTemplate::New(func_math_isFinite));
				temp->PrototypeTemplate()->Set(String::New("Floor"),		FunctionTemplate::New(func_math_floor));
				temp->PrototypeTemplate()->Set(String::New("Exp"),			FunctionTemplate::New(func_math_exp));
				temp->PrototypeTemplate()->Set(String::New("Ceil"),			FunctionTemplate::New(func_math_ceil));
				temp->PrototypeTemplate()->Set(String::New("Sign"),			FunctionTemplate::New(func_math_sign));
				temp->PrototypeTemplate()->Set(String::New("Pow"),			FunctionTemplate::New(func_math_pow));
				temp->PrototypeTemplate()->Set(String::New("Log"),			FunctionTemplate::New(func_math_log));

		return physXFuncTemplateBase;
	}

Handle<Value> V8PhysX::func_toVec3(const Arguments& args){
	//Locker lock(Isolate::GetCurrent());
    HandleScope scope(Isolate::GetCurrent());

    if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxExtendedVec3::getTemplate()->HasInstance(args[0])) 
    {
		return scope.Close( wrap<PxVec3, V8PxVec3>(toVec3(*unwrap<PxExtendedVec3>(args[0]->ToObject()))));
	}

	//ThrowException(Exception::SyntaxError(String::New("PhysX.Max takes 2 Number arguments")));

	return scope.Close( Undefined() );
}

Handle<Value> V8PhysX::func_math_max(const Arguments& args){
	//Locker lock(Isolate::GetCurrent());
    HandleScope scope(Isolate::GetCurrent());

    if(args.Length() == 2 ) 
    {
		return Number::New(PxMax(args[0]->NumberValue(), args[1]->NumberValue()));
	}

	//ThrowException(Exception::SyntaxError(String::New("PhysX.Max takes 2 Number arguments")));

	return scope.Close( Undefined() );
}

Handle<Value> V8PhysX::func_math_min(const Arguments& args){
	//Locker lock(Isolate::GetCurrent());
    HandleScope scope(Isolate::GetCurrent());

    if(args.Length() == 2 ) 
    {
		return Number::New(PxMin(args[0]->NumberValue(), args[1]->NumberValue()));
	}

	return scope.Close( Undefined() );
}

Handle<Value> V8PhysX::func_math_abs(const Arguments& args){
	//Locker lock(Isolate::GetCurrent());
    HandleScope scope(Isolate::GetCurrent());

    if(args.Length() == 1 ) 
    {
		return Number::New(PxAbs(args[0]->NumberValue()));
	}

	return scope.Close( Undefined() );
}

Handle<Value> V8PhysX::func_math_equals(const Arguments& args){return Undefined();}
Handle<Value> V8PhysX::func_math_clamp(const Arguments& args){return Undefined();}
Handle<Value> V8PhysX::func_math_sqrt(const Arguments& args){return Undefined();}
Handle<Value> V8PhysX::func_math_recipSqrt(const Arguments& args){return Undefined();}
Handle<Value> V8PhysX::func_math_sin(const Arguments& args){return Undefined();}
Handle<Value> V8PhysX::func_math_cos(const Arguments& args){return Undefined();}
Handle<Value> V8PhysX::func_math_tan(const Arguments& args){return Undefined();}
Handle<Value> V8PhysX::func_math_asin(const Arguments& args){return Undefined();}
Handle<Value> V8PhysX::func_math_acos(const Arguments& args){return Undefined();}
Handle<Value> V8PhysX::func_math_atan(const Arguments& args){return Undefined();}
Handle<Value> V8PhysX::func_math_atan2(const Arguments& args){return Undefined();}
Handle<Value> V8PhysX::func_math_isFinite(const Arguments& args){return Undefined();}
Handle<Value> V8PhysX::func_math_floor(const Arguments& args){return Undefined();}
Handle<Value> V8PhysX::func_math_exp(const Arguments& args){return Undefined();}
Handle<Value> V8PhysX::func_math_ceil(const Arguments& args){return Undefined();}
Handle<Value> V8PhysX::func_math_sign(const Arguments& args){return Undefined();}
Handle<Value> V8PhysX::func_math_pow(const Arguments& args){return Undefined();}
Handle<Value> V8PhysX::func_math_log(const Arguments& args){return Undefined();}

//PxSerializable
	Handle<Value> V8PxSerializable::getOrder(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());
			
			return scope.Close( Uint32::New( thisPxSerializable->getOrder() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxSerializable::collectForExport(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxCollection::getTemplate()->HasInstance(args[0])) 
        {
			PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());
			
			thisPxSerializable->collectForExport( *unwrap<PxCollection>( args[0]->ToObject() ) );

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxSerializable::getFields(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() >= 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxSerialStream::getTemplate()->HasInstance(args[0])) 
        {
			if(args.Length() == 1){
				PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());
				return scope.Close( Boolean::New( thisPxSerializable->getFields( *unwrap<PxSerialStream>(args[0]->ToObject()) ) ) );
			}
			else if(args.Length() == 2 && !args[1].IsEmpty() && (args[1]->IsInt32() || args[1]->IsUint32()) ){
				PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());
				return scope.Close( Boolean::New( thisPxSerializable->getFields( *unwrap<PxSerialStream>(args[0]->ToObject()), args[1]->Int32Value() ) ) );
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxSerializable::getFieldDescriptor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsString()) 
        {
			PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());
			
			Persistent<Object> newPxFieldDescriptor = Persistent<Object>::New(Isolate::GetCurrent(),V8PxFieldDescriptor::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxFieldDescriptor.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);

			//Don't know if this will work...
			const PxFieldDescriptor* temp = thisPxSerializable->getFieldDescriptor( *String::Utf8Value(args[0]->ToString()) );

			newPxFieldDescriptor->SetInternalField(0, External::New( &temp ) );

			return scope.Close( newPxFieldDescriptor );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxSerializable::getObjectSize(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

			return scope.Close( Uint32::New( thisPxSerializable->getObjectSize() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxSerializable::exportExtraData(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxSerialStream::getTemplate()->HasInstance(args[0])) 
        {
			PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());
			
			thisPxSerializable->exportExtraData( *unwrap<PxSerialStream>( args[0]->ToObject() ));

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxSerializable::importExtraData(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsString() &&
								!args[1].IsEmpty() && args[1]->IsInt32())
        {
			PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

			PxU32 temp = args[1]->Uint32Value();

			return scope.Close( String::New( thisPxSerializable->importExtraData( *String::Utf8Value(args[0]->ToString()) , temp ) ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxSerializable::resolvePointers(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxRefResolver::getTemplate()->HasInstance(args[0]) &&
								!args[1].IsEmpty() && args[1]->IsExternal())
        {
			PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

			return scope.Close( Boolean::New( thisPxSerializable->resolvePointers(  *unwrap<PxRefResolver>(args[0]->ToObject()), Local<External>::Cast(args[1])->Value() ) ) );
		}

		return scope.Close( Undefined() );
	}

	//Handle<Value> V8PxSerializable::getClassName(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0)
 //       {
	//		PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

	//		return scope.Close( String::New( thisPxSerializable->getClassName() ) );
	//	}

	//	return scope.Close( Undefined() );
	//}

	//Handle<Value> V8PxSerializable::isKindOf(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsString())
 //       {
	//		PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

	//		return scope.Close( Boolean::New( thisPxSerializable->isKindOf( *String::Utf8Value(args[0]->ToString()) ) ) );
	//	}

	//	return scope.Close( Undefined() );
	//}

	Handle<Value> V8PxSerializable::registerNameForExport(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxNameManager::getTemplate()->HasInstance(args[0]))
        {
			PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

			PxNameManager* inPxNameManager = unwrap<PxNameManager>(args[0]->ToObject());

			thisPxSerializable->registerNameForExport(*inPxNameManager);

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	//Handle<Value> V8PxSerializable::enableInScene(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0)
 //       {
	//		PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

	//		thisPxSerializable->enableInScene();

	//		return scope.Close( args.Holder() );
	//	}

	//	return scope.Close( Undefined() );
	//}

	//Handle<Value> V8PxSerializable::disableInScene(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0)
 //       {
	//		PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

	//		thisPxSerializable->disableInScene();

	//		return scope.Close( args.Holder() );
	//	}

	//	return scope.Close( Undefined() );
	//}

	//Handle<Value> V8PxSerializable::isInScene(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0)
 //       {
	//		PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

	//		return scope.Close( Uint32::New( thisPxSerializable->isInScene() ) );
	//	}

	//	return scope.Close( Undefined() );
	//}

	//Handle<Value> V8PxSerializable::disableAutoResolve(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0)
 //       {
	//		PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

	//		thisPxSerializable->disableAutoResolve();

	//		return scope.Close( args.Holder() );
	//	}

	//	return scope.Close( Undefined() );
	//}

	//Handle<Value> V8PxSerializable::enableAutoResolve(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0)
 //       {
	//		PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

	//		thisPxSerializable->enableAutoResolve();

	//		return scope.Close( args.Holder() );
	//	}

	//	return scope.Close( Undefined() );
	//}

	//Handle<Value> V8PxSerializable::isAutoResolveDisabled(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0)
 //       {
	//		PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

	//		return scope.Close( Uint32::New( thisPxSerializable->isAutoResolveDisabled() ) );
	//	}

	//	return scope.Close( Undefined() );
	//}

	//Handle<Value> V8PxSerializable::disableFields(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0)
 //       {
	//		PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

	//		thisPxSerializable->disableFields();

	//		return scope.Close( args.Holder() );
	//	}

	//	return scope.Close( Undefined() );
	//}

	//Handle<Value> V8PxSerializable::enableFields(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0)
 //       {
	//		PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

	//		thisPxSerializable->enableFields();

	//		return scope.Close( args.Holder() );
	//	}

	//	return scope.Close( Undefined() );
	//}

	//Handle<Value> V8PxSerializable::areFieldsDisabled(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0)
 //       {
	//		PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

	//		return scope.Close( Uint32::New( thisPxSerializable->areFieldsDisabled() ) );
	//	}

	//	return scope.Close( Undefined() );
	//}

	//Handle<Value> V8PxSerializable::setOwnsMemory(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0)
 //       {
	//		PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

	//		thisPxSerializable->setOwnsMemory();

	//		return scope.Close( args.Holder() );
	//	}

	//	return scope.Close( Undefined() );
	//}

	//Handle<Value> V8PxSerializable::clearOwnsMemory(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0)
 //       {
	//		PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

	//		thisPxSerializable->clearOwnsMemory();

	//		return scope.Close( args.Holder() );
	//	}

	//	return scope.Close( Undefined() );
	//}

	//Handle<Value> V8PxSerializable::ownsMemory(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0)
 //       {
	//		PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

	//		return scope.Close( Uint32::New( thisPxSerializable->ownsMemory() ) );
	//	}

	//	return scope.Close( Undefined() );
	//}

	/*Handle<Value> V8PxSerializable::getAddress(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0)
        {
			PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

			Persistent<Object> newPxSerializable = Persistent<Object>::New(Isolate::GetCurrent(),V8PxSerializable::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxSerializable.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxSerializable->SetInternalField(0, External::New( thisPxSerializable->getAddress() ));

			return scope.Close( newPxSerializable );
		}

		return scope.Close( Undefined() );
	}*/

	//Handle<Value> V8PxSerializable::getSerialType(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0)
 //       {
	//		PxSerializable* thisPxSerializable = unwrap<PxSerializable>(args.Holder());

	//		return scope.Close( Uint32::New( thisPxSerializable->getSerialType() ) );
	//	}

	//	return scope.Close( Undefined() );
	//}

	//Handle<Value> V8PxSerializable::getMetaData(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxSerialStream::getTemplate()->HasInstance(args[0]))
 //       {
	//		PxSerializable::getMetaData( *unwrap<PxSerialStream>( args[0]->ToObject() ) );
	//	}

	//	return scope.Close( Undefined() );
	//}

//PxRefResolver
	Handle<Value> V8PxRefResolver::newAddress(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxSerializable::getTemplate()->HasInstance(args[0])) 
        {
			PxRefResolver* thisPxRefResolver = unwrap<PxRefResolver>(args.Holder());

			Persistent<Object> newPxSerializable = Persistent<Object>::New(Isolate::GetCurrent(),V8PxSerializable::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxSerializable.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxSerializable->SetInternalField(0, External::New( thisPxRefResolver->newAddress(  unwrap<PxSerializable>(args[0]->ToObject() ) ) ));

			return scope.Close( newPxSerializable );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRefResolver::setNewAddress(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxSerializable::getTemplate()->HasInstance(args[0])
			&& !args[1].IsEmpty() && args[1]->IsObject() && V8PxSerializable::getTemplate()->HasInstance(args[1])) 
        {
			PxRefResolver* thisPxRefResolver = unwrap<PxRefResolver>(args.Holder());
			
			thisPxRefResolver->setNewAddress( unwrap<PxSerializable>( args[0]->ToObject() ), unwrap<PxSerializable>( args[1]->ToObject() ) );

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

//PxUserReferences
	Handle<Value> V8PxUserReferences::getObjectFromID(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		//FIXME
		/*if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsExternal()) 
        {
			PxUserReferences* thisPxUserReferences = unwrap<PxUserReferences>(args.Holder());

			Persistent<Object> newPxSerializable = Persistent<Object>::New(Isolate::GetCurrent(),V8PxSerializable::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxSerializable.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxSerializable->SetInternalField(0, External::New( thisPxUserReferences->getObjectFromID(  Local<External>::Cast(args[0])->Value() ) ) );

			return scope.Close( newPxSerializable );
		}*/

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxUserReferences::setUserData(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		//FIXME
		/*if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxSerializable::getTemplate()->HasInstance(args[0])
			&& !args[1].IsEmpty() && args[1]->IsExternal()) 
        {
			PxUserReferences* thisPxUserReferences = unwrap<PxUserReferences>(args.Holder());
			
			thisPxUserReferences->setUserData( unwrap<PxSerializable>( args[0]->ToObject() ),  Local<External>::Cast(args[1])->Value() );

			return scope.Close( args.Holder() );
		}*/

		return scope.Close( Undefined() );
	}

//PxCollection
	Handle<Value> V8PxCollection::serialize(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		//FIXME
		/*if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxSerialStream::getTemplate()->HasInstance(args[0])) 
        {
			PxCollection* thisPxCollection = unwrap<PxCollection>(args.Holder());

			thisPxCollection->serialize( *unwrap<PxSerialStream>(args[0]->ToObject()) );

			return scope.Close( args.Holder() );
		}*/

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxCollection::deserialize(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsExternal() &&
			!args[1].IsEmpty() && args[1]->IsObject() && V8PxUserReferences::getTemplate()->HasInstance(args[1]) &&
			!args[2].IsEmpty() && args[2]->IsObject() && V8PxUserReferences::getTemplate()->HasInstance(args[2])) 
        {
			PxCollection* thisPxCollection = unwrap<PxCollection>(args.Holder());

			return scope.Close( Boolean::New( thisPxCollection->deserialize( Local<External>::Cast(args[0])->Value(), unwrap<PxUserReferences>(args[1]->ToObject()),  unwrap<PxUserReferences>(args[2]->ToObject()) ) ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxCollection::setUserData(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		//FIXME
		/*if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxSerializable::getTemplate()->HasInstance(args[0]) && 
			!args[1].IsEmpty() && args[1]->IsExternal()) 
        {
			PxCollection* thisPxCollection = unwrap<PxCollection>(args.Holder());

			thisPxCollection->setUserData( unwrap<PxSerializable>(args[0]->ToObject()), Local<External>::Cast(args[1])->Value() );

			return scope.Close( args.Holder() );
		}*/

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxCollection::addExternalRef(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		//FIXME
		/*if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxSerializable::getTemplate()->HasInstance(args[0]) && 
			!args[1].IsEmpty() && args[1]->IsExternal()) 
        {
			PxCollection* thisPxCollection = unwrap<PxCollection>(args.Holder());

			thisPxCollection->addExternalRef( unwrap<PxSerializable>(args[0]->ToObject()), Local<External>::Cast(args[1])->Value() );

			return scope.Close( args.Holder() );
		}*/

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxCollection::getNbObjects(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxCollection* thisPxCollection = unwrap<PxCollection>(args.Holder());

			return scope.Close( Uint32::New(thisPxCollection->getNbObjects()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxCollection::getObject(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32()) 
        {
			PxCollection* thisPxCollection = unwrap<PxCollection>(args.Holder());

			Persistent<Object> newPxSerializable = Persistent<Object>::New(Isolate::GetCurrent(),V8PxSerializable::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxSerializable.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxSerializable->SetInternalField(0, External::New( thisPxCollection->getObject( args[0]->Uint32Value() ) ));

			return scope.Close( newPxSerializable );
		}

		return scope.Close( Undefined() );
	}

//PxVec2
	Handle<Value>  V8PxVec2::PxVec2Constructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){
			PxVec2* vecObject = new PxVec2();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),vecObject, &CleanupDelete);
			self->SetInternalField(0, External::New( vecObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty()){
			PxVec2* vecObject;
			if(args[0]->IsNumber()){
				vecObject = new PxVec2( args[0]->NumberValue());
			}
			else if(args[0]->IsObject() && V8PxVec2::getTemplate()->HasInstance(args[0])){
				vecObject = new PxVec2(*unwrap<PxVec2>(args[0]->ToObject()));
			}
			else {
				return ThrowException( Exception::TypeError( String::New("PxVec2 constructor takes nothing, (Number), (Number, Number), or (PxVec2) as an argument.") ) );
			}
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),vecObject, &CleanupDelete);
			self->SetInternalField(0, External::New( vecObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 2 && args[0].IsEmpty() && !args[1].IsEmpty()){
			if(	args[0]->IsNumber() &&
				args[1]->IsNumber()) 
			{
				PxVec2* vecObject = new PxVec2( args[0]->NumberValue(), args[1]->NumberValue());
				Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//				self.MakeWeak(Isolate::GetCurrent(),vecObject, &CleanupDelete);
				self->SetInternalField(0, External::New( vecObject ));

				return scope.Close( self );
			}
		}
        
		return ThrowException( Exception::TypeError( String::New("PxVec2 constructor takes nothing, (Number), (Number, Number), or (PxVec2) as an argument.") ) );
	}

	Handle<Value> V8PxVec2::getX( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxVec2* thisPxVec2 = unwrap<PxVec2>(info.Holder());
		//if(thisPxVec2 != NULL) 
		//{
			return scope.Close(Number::New( thisPxVec2->x ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxVec2::setX( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PxVec2* thisPxVec2 = unwrap<PxVec2>(info.Holder());
			//if(thisPxVec2 != NULL && value->IsNumber()) 
			//{
				thisPxVec2->x = value->NumberValue();
			//}
		}
	}

	Handle<Value> V8PxVec2::getY( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxVec2* thisPxVec2 = unwrap<PxVec2>(info.Holder());
		//if(thisPxVec2 != NULL) 
		//{
			return scope.Close(Number::New( thisPxVec2->y ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxVec2::setY( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PxVec2* thisPxVec2 = unwrap<PxVec2>(info.Holder());
			//if(thisPxVec2 != NULL && value->IsNumber()) 
			//{
				thisPxVec2->y = value->NumberValue();
			//}
		}
	}

	Handle<Value> V8PxVec2::elementGet(uint32_t index, const AccessorInfo& info){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(index >=0 && index<= 1){
			PxVec2* thisPxVec2 = unwrap<PxVec2>(info.Holder());
			//if(thisPxVec2 != NULL) 
			//{
				return scope.Close(Number::New( (*thisPxVec2)[index] ));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::elementSet(uint32_t index, Local<Value> value, const AccessorInfo& info){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber() && index >=0 && index<= 1){
			PxVec2* thisPxVec2 = unwrap<PxVec2>(info.Holder());
			//if(thisPxVec2 != NULL) 
			//{
				(*thisPxVec2)[index] = value->NumberValue();
				return scope.Close(value);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::compare(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec2::getTemplate()->HasInstance(args[0])) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			PxVec2* inPxVec2 = unwrap<PxVec2>(args[0]->ToObject());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
				return scope.Close( Boolean::New(*thisPxVec2 == *inPxVec2));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::acompare(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec2::getTemplate()->HasInstance(args[0])) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			PxVec2* inPxVec2 = unwrap<PxVec2>(args[0]->ToObject());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
				return scope.Close( Boolean::New(*thisPxVec2 != *inPxVec2));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::isZero(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
			return scope.Close( Boolean::New(thisPxVec2->isZero()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::isFinite(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
			return scope.Close( Boolean::New(thisPxVec2->isFinite()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::isNormalized(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
			return scope.Close( Boolean::New(thisPxVec2->isNormalized()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::magnitudeSquared(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
			return scope.Close( Number::New(thisPxVec2->magnitudeSquared()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::magnitude(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
			return scope.Close( Number::New(thisPxVec2->magnitude()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::negate(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
			PxVec2* obj = new PxVec2(-*thisPxVec2);
			Persistent<Object> newPxVec2 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec2.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec2->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec2);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::add(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec2::getTemplate()->HasInstance(args[0])) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			PxVec2* inPxVec2 = unwrap<PxVec2>(args[0]->ToObject());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
			PxVec2* obj = new PxVec2(*thisPxVec2 + *inPxVec2);
			Persistent<Object> newPxVec2 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec2.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec2->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec2);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::subtract(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec2::getTemplate()->HasInstance(args[0])) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			PxVec2* inPxVec2 = unwrap<PxVec2>(args[0]->ToObject());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
			PxVec2* obj = new PxVec2(*thisPxVec2 - *inPxVec2);
			Persistent<Object> newPxVec2 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec2.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec2->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec2);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::multiply(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
			PxVec2* obj = new PxVec2(*thisPxVec2 * args[0]->NumberValue());
			Persistent<Object> newPxVec2 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec2.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec2->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec2);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::divide(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
			PxVec2* obj = new PxVec2(*thisPxVec2 / args[0]->NumberValue());
			Persistent<Object> newPxVec2 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec2.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec2->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec2);
			//}
		}

		return scope.Close( Undefined() );
	}


	Handle<Value> V8PxVec2::assignmentAdd(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec2::getTemplate()->HasInstance(args[0])) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			PxVec2* inPxVec2 = unwrap<PxVec2>(args[0]->ToObject());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
				*thisPxVec2 += *inPxVec2;
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::assignmentSubtract(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec2::getTemplate()->HasInstance(args[0])) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			PxVec2* inPxVec2 = unwrap<PxVec2>(args[0]->ToObject());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
				*thisPxVec2 -= *inPxVec2;
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::assignmentMultiply(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
				*thisPxVec2 *= args[0]->NumberValue();
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::assignmentDivide(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
				*thisPxVec2 /= args[0]->NumberValue();
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}


	Handle<Value> V8PxVec2::dot(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec2::getTemplate()->HasInstance(args[0])) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			PxVec2* inPxVec2 = unwrap<PxVec2>(args[0]->ToObject());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{			
			return scope.Close(Number::New(thisPxVec2->dot(*inPxVec2)));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::getNormalized(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
			PxVec2* obj = new PxVec2(thisPxVec2->getNormalized());
			Persistent<Object> newPxVec2 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec2.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec2->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec2);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::normalize(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
			
			return scope.Close(Number::New(thisPxVec2->normalize()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::min(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			//PxVec2* inPxVec2 = unwrap<PxVec2>(args[0]->ToObject());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{			
			return scope.Close(Number::New(thisPxVec2->minElement()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::max(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			//PxVec2* inPxVec2 = unwrap<PxVec2>(args[0]->ToObject());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{			
			return scope.Close(Number::New(thisPxVec2->maxElement()));
			//}
		}

		return scope.Close( Undefined() );
	}


	Handle<Value> V8PxVec2::elementwiseMultiply(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec2::getTemplate()->HasInstance(args[0])) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			PxVec2* inPxVec2 = unwrap<PxVec2>(args[0]->ToObject());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
			PxVec2* obj = new PxVec2(thisPxVec2->multiply(*inPxVec2));
			Persistent<Object> newPxVec2 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec2.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec2->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec2);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::elementwiseMin(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec2::getTemplate()->HasInstance(args[0])) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			PxVec2* inPxVec2 = unwrap<PxVec2>(args[0]->ToObject());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
			PxVec2* obj = new PxVec2(thisPxVec2->minimum(*inPxVec2));
			Persistent<Object> newPxVec2 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec2.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec2->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec2);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec2::elementwiseMax(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec2::getTemplate()->HasInstance(args[0])) 
        {
			PxVec2* thisPxVec2 = unwrap<PxVec2>(args.Holder());
			PxVec2* inPxVec2 = unwrap<PxVec2>(args[0]->ToObject());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
			PxVec2* obj = new PxVec2(thisPxVec2->maximum(*inPxVec2));
			Persistent<Object> newPxVec2 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec2.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec2->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec2);
			//}
		}

		return scope.Close( Undefined() );
	}


//PxVec3
	Handle<Value>  V8PxVec3::PxVec3Constructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){
			PxVec3* vecObject = new PxVec3();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),vecObject, &CleanupDelete);
			self->SetInternalField(0, External::New( vecObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty()){
			PxVec3* vecObject;
			if(args[0]->IsNumber()){
				vecObject = new PxVec3( args[0]->NumberValue());
			}
			else if(args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])){
				vecObject = new PxVec3(*unwrap<PxVec3>(args[0]->ToObject()));
			}
			else {
				return ThrowException( Exception::TypeError( String::New("PxVec3 constructor takes nothing, (Number), (Number, Number, Number), or (PxVec3) as an argument.") ) );
			}
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),vecObject, &CleanupDelete);
			self->SetInternalField(0, External::New( vecObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 3 && !args[0].IsEmpty() && !args[1].IsEmpty() && !args[2].IsEmpty() ){
			if(	args[0]->IsNumber() &&
				args[1]->IsNumber() &&
				args[2]->IsNumber()) 
			{
				PxVec3* vecObject = new PxVec3( args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue() );
				Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//				self.MakeWeak(Isolate::GetCurrent(),vecObject, &CleanupDelete);
				self->SetInternalField(0, External::New( vecObject ));

				return scope.Close( self );
			}
		}
        
		return ThrowException( Exception::TypeError( String::New("PxVec3 constructor takes nothing, (Number), (Number, Number, Number), or (PxVec3) as an argument.") ) );
	}

	Handle<Value> V8PxVec3::getX( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxVec3* thisPxVec3 = unwrap<PxVec3>(info.Holder());
		//if(thisPxVec3 != NULL) 
		//{
			return scope.Close(Number::New( thisPxVec3->x ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxVec3::setX( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PxVec3* thisPxVec3 = unwrap<PxVec3>(info.Holder());
			//if(thisPxVec3 != NULL && value->IsNumber()) 
			//{
				thisPxVec3->x = value->NumberValue();
			//}
		}
	}

	Handle<Value> V8PxVec3::getY( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxVec3* thisPxVec3 = unwrap<PxVec3>(info.Holder());
		//if(thisPxVec3 != NULL) 
		//{
			return scope.Close(Number::New( thisPxVec3->y ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxVec3::setY( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PxVec3* thisPxVec3 = unwrap<PxVec3>(info.Holder());
			//if(thisPxVec3 != NULL && value->IsNumber()) 
			//{
				thisPxVec3->y = value->NumberValue();
			//}
		}
	}

	Handle<Value> V8PxVec3::getZ( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxVec3* thisPxVec3 = unwrap<PxVec3>(info.Holder());
		//if(thisPxVec3 != NULL) 
		//{
			return scope.Close(Number::New( thisPxVec3->z ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxVec3::setZ( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PxVec3* thisPxVec3 = unwrap<PxVec3>(info.Holder());
			//if(thisPxVec3 != NULL && value->IsNumber()) 
			//{
				thisPxVec3->z = value->NumberValue();
			//}
		}
	}

	Handle<Value> V8PxVec3::elementGet(uint32_t index, const AccessorInfo& info){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(index >=0 && index <= 2){
			PxVec3* thisPxVec3 = unwrap<PxVec3>(info.Holder());
			//if(thisPxVec3 != NULL) 
			//{
				return scope.Close(Number::New( (*thisPxVec3)[index] ));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::elementSet(uint32_t index, Local<Value> value, const AccessorInfo& info){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber() && index >=0 && index <= 2){
			PxVec3* thisPxVec3 = unwrap<PxVec3>(info.Holder());
			//if(thisPxVec3 != NULL) 
			//{
				(*thisPxVec3)[index] = value->NumberValue();
				return scope.Close(value);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::compare(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
				return scope.Close( Boolean::New(*thisPxVec3 == *inPxVec3));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::acompare(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
				return scope.Close( Boolean::New(*thisPxVec3 != *inPxVec3));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::isZero(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
			return scope.Close( Boolean::New(thisPxVec3->isZero()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::isFinite(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
			return scope.Close( Boolean::New(thisPxVec3->isFinite()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::isNormalized(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
			return scope.Close( Boolean::New(thisPxVec3->isNormalized()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::magnitudeSquared(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
			return scope.Close( Number::New(thisPxVec3->magnitudeSquared()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::magnitude(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
			return scope.Close( Number::New(thisPxVec3->magnitude()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::negate(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
			PxVec3* obj = new PxVec3(-*thisPxVec3);
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::add(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
			PxVec3* obj = new PxVec3(*thisPxVec3 + *inPxVec3);
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::subtract(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
			PxVec3* obj = new PxVec3(*thisPxVec3 - *inPxVec3);
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::multiply(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
			PxVec3* obj = new PxVec3(*thisPxVec3 * args[0]->NumberValue());
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::divide(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
			PxVec3* obj = new PxVec3(*thisPxVec3 / args[0]->NumberValue());
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}


	Handle<Value> V8PxVec3::assignmentAdd(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
				*thisPxVec3 += *inPxVec3;
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::assignmentSubtract(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
				*thisPxVec3 -= *inPxVec3;
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::assignmentMultiply(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
				*thisPxVec3 *= args[0]->NumberValue();
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::assignmentDivide(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
				*thisPxVec3 /= args[0]->NumberValue();
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}


	Handle<Value> V8PxVec3::dot(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{			
			return scope.Close(Number::New(thisPxVec3->dot(*inPxVec3)));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::cross(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
			PxVec3* obj = new PxVec3(thisPxVec3->cross(*inPxVec3));
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::getNormalized(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
			PxVec3* obj = new PxVec3(thisPxVec3->getNormalized());
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::normalize(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
			
			return scope.Close(Number::New(thisPxVec3->normalize()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::min(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			//PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{			
			return scope.Close(Number::New(thisPxVec3->minElement()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::max(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			//PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{			
			return scope.Close(Number::New(thisPxVec3->maxElement()));
			//}
		}

		return scope.Close( Undefined() );
	}


	Handle<Value> V8PxVec3::elementwiseMultiply(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
			PxVec3* obj = new PxVec3(thisPxVec3->multiply(*inPxVec3));
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::elementwiseMin(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
			PxVec3* obj = new PxVec3(thisPxVec3->minimum(*inPxVec3));
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec3::elementwiseMax(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxVec3* thisPxVec3 = unwrap<PxVec3>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxVec3 != NULL && inPxVec3 != NULL) 
			//{
			PxVec3* obj = new PxVec3(thisPxVec3->maximum(*inPxVec3));
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

//PxExtendedVec3
	Handle<Value>  V8PxExtendedVec3::PxExtendedVec3Constructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){
			PxExtendedVec3* vecObject = new PxExtendedVec3();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),vecObject, &CleanupDelete);
			self->SetInternalField(0, External::New( vecObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxExtendedVec3::getTemplate()->HasInstance(args[0])){
			PxExtendedVec3*	vecObject = new PxExtendedVec3(*unwrap<PxExtendedVec3>(args[0]->ToObject()));

			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),vecObject, &CleanupDelete);
			self->SetInternalField(0, External::New( vecObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 3 && !args[0].IsEmpty() && !args[1].IsEmpty() && !args[2].IsEmpty() ){
			if(	args[0]->IsNumber() &&
				args[1]->IsNumber() &&
				args[2]->IsNumber()) 
			{
				PxExtendedVec3* vecObject = new PxExtendedVec3( args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue() );
				Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//				self.MakeWeak(Isolate::GetCurrent(),vecObject, &CleanupDelete);
				self->SetInternalField(0, External::New( vecObject ));

				return scope.Close( self );
			}
		}
        
		return ThrowException( Exception::TypeError( String::New("PxExtendedVec3 constructor takes nothing, (Number), or (PxExtendedVec3) as an argument.") ) );
	}

	Handle<Value> V8PxExtendedVec3::getX( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(info.Holder());
		//if(thisPxExtendedVec3 != NULL) 
		//{
			return scope.Close(Number::New( thisPxExtendedVec3->x ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxExtendedVec3::setX( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(info.Holder());
			//if(thisPxExtendedVec3 != NULL && value->IsNumber()) 
			//{
				thisPxExtendedVec3->x = value->NumberValue();
			//}
		}
	}

	Handle<Value> V8PxExtendedVec3::getY( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(info.Holder());
		//if(thisPxExtendedVec3 != NULL) 
		//{
			return scope.Close(Number::New( thisPxExtendedVec3->y ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxExtendedVec3::setY( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(info.Holder());
			//if(thisPxExtendedVec3 != NULL && value->IsNumber()) 
			//{
				thisPxExtendedVec3->y = value->NumberValue();
			//}
		}
	}

	Handle<Value> V8PxExtendedVec3::getZ( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(info.Holder());
		//if(thisPxExtendedVec3 != NULL) 
		//{
			return scope.Close(Number::New( thisPxExtendedVec3->z ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxExtendedVec3::setZ( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(info.Holder());
			//if(thisPxExtendedVec3 != NULL && value->IsNumber()) 
			//{
				thisPxExtendedVec3->z = value->NumberValue();
			//}
		}
	}

	Handle<Value> V8PxExtendedVec3::elementGet(uint32_t index, const AccessorInfo& info){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(index >=0 && index <= 2){
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(info.Holder());
			//if(thisPxExtendedVec3 != NULL) 
			//{
				return scope.Close(Number::New( (*thisPxExtendedVec3)[index] ));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::elementSet(uint32_t index, Local<Value> value, const AccessorInfo& info){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber() && index >=0 && index <= 2){
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(info.Holder());
			//if(thisPxExtendedVec3 != NULL) 
			//{
				(*thisPxExtendedVec3)[index] = value->NumberValue();
				return scope.Close(value);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::isZero(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			//if(thisPxExtendedVec3 != NULL && inPxExtendedVec3 != NULL) 
			//{
			return scope.Close( Boolean::New(thisPxExtendedVec3->isZero()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::isFinite(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			//if(thisPxExtendedVec3 != NULL && inPxExtendedVec3 != NULL) 
			//{
			return scope.Close( Boolean::New(thisPxExtendedVec3->isFinite()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::magnitudeSquared(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			//if(thisPxExtendedVec3 != NULL && inPxExtendedVec3 != NULL) 
			//{
			return scope.Close( Number::New(thisPxExtendedVec3->magnitudeSquared()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::magnitude(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			//if(thisPxExtendedVec3 != NULL && inPxExtendedVec3 != NULL) 
			//{
			return scope.Close( Number::New(thisPxExtendedVec3->magnitude()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::negate(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			//if(thisPxExtendedVec3 != NULL && inPxExtendedVec3 != NULL) 
			//{
			PxExtendedVec3* obj = new PxExtendedVec3(-*thisPxExtendedVec3);
			Persistent<Object> newPxExtendedVec3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxExtendedVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxExtendedVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxExtendedVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::add(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxExtendedVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			PxExtendedVec3* inPxExtendedVec3 = unwrap<PxExtendedVec3>(args[0]->ToObject());
			//if(thisPxExtendedVec3 != NULL && inPxExtendedVec3 != NULL) 
			//{
			PxExtendedVec3* obj = new PxExtendedVec3(*thisPxExtendedVec3 + *inPxExtendedVec3);
			Persistent<Object> newPxExtendedVec3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxExtendedVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxExtendedVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxExtendedVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::subtract(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxExtendedVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			PxExtendedVec3* inPxExtendedVec3 = unwrap<PxExtendedVec3>(args[0]->ToObject());
			//if(thisPxExtendedVec3 != NULL && inPxExtendedVec3 != NULL) 
			//{
			PxVec3* obj = new PxVec3(*thisPxExtendedVec3 - *inPxExtendedVec3);
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::assignmentAdd(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxExtendedVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			PxExtendedVec3* inPxExtendedVec3 = unwrap<PxExtendedVec3>(args[0]->ToObject());
			//if(thisPxExtendedVec3 != NULL && inPxExtendedVec3 != NULL) 
			//{
				*thisPxExtendedVec3 += *inPxExtendedVec3;
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::assignmentSubtract(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxExtendedVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			PxExtendedVec3* inPxExtendedVec3 = unwrap<PxExtendedVec3>(args[0]->ToObject());
			//if(thisPxExtendedVec3 != NULL && inPxExtendedVec3 != NULL) 
			//{
				*thisPxExtendedVec3 -= *inPxExtendedVec3;
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::assignmentMultiply(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			//if(thisPxExtendedVec3 != NULL && inPxExtendedVec3 != NULL) 
			//{
				*thisPxExtendedVec3 *= args[0]->NumberValue();
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::dot(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxExtendedVec3 != NULL && inPxExtendedVec3 != NULL) 
			//{			
			return scope.Close(Number::New(thisPxExtendedVec3->dot(*inPxVec3)));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::cross(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxExtendedVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			PxExtendedVec3* inPxExtendedVec3 = unwrap<PxExtendedVec3>(args[0]->ToObject());
			//if(thisPxExtendedVec3 != NULL && inPxExtendedVec3 != NULL) 
			//{
			PxExtendedVec3* obj = new PxExtendedVec3(thisPxExtendedVec3->cross(*inPxExtendedVec3));
			Persistent<Object> newPxExtendedVec3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxExtendedVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxExtendedVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxExtendedVec3);
			//}
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxExtendedVec3::getTemplate()->HasInstance(args[0]) && !args[1].IsEmpty() && args[1]->IsObject()){
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			PxExtendedVec3* leftPxExtendedVec3 = unwrap<PxExtendedVec3>(args[0]->ToObject());

			if(V8PxExtendedVec3::getTemplate()->HasInstance(args[1])){
				PxExtendedVec3* rightPxExtendedVec3 = unwrap<PxExtendedVec3>(args[1]->ToObject());
				thisPxExtendedVec3->cross(*leftPxExtendedVec3, *rightPxExtendedVec3);

				return scope.Close(args.Holder());
			}
			else if(V8PxVec3::getTemplate()->HasInstance(args[1])) {
				PxVec3* rightPxVec3 = unwrap<PxVec3>(args[1]->ToObject());
				thisPxExtendedVec3->cross(*leftPxExtendedVec3, *rightPxVec3);

				return scope.Close(args.Holder());
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::normalize(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			//if(thisPxExtendedVec3 != NULL && inPxExtendedVec3 != NULL) 
			//{
			
			return scope.Close(Number::New(thisPxExtendedVec3->normalize()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::min(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxExtendedVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			PxExtendedVec3* inPxExtendedVec3 = unwrap<PxExtendedVec3>(args[0]->ToObject());

			thisPxExtendedVec3->minimum(*inPxExtendedVec3);
			//if(thisPxExtendedVec3 != NULL && inPxExtendedVec3 != NULL) 
			//{			
			return scope.Close(args.Holder());
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::max(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxExtendedVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			PxExtendedVec3* inPxExtendedVec3 = unwrap<PxExtendedVec3>(args[0]->ToObject());

			thisPxExtendedVec3->maximum(*inPxExtendedVec3);
			//if(thisPxExtendedVec3 != NULL && inPxExtendedVec3 != NULL) 
			//{			
			return scope.Close(args.Holder());
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::set(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsNumber() && !args[1].IsEmpty() && args[1]->IsNumber() && !args[2].IsEmpty() && args[2]->IsNumber()) 
        {
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			thisPxExtendedVec3->set(args[0]->ToNumber()->Value(), args[1]->ToNumber()->Value(), args[2]->ToNumber()->Value());
			//if(thisPxExtendedVec3 != NULL && inPxExtendedVec3 != NULL) 
			//{			
			return scope.Close(args.Holder());
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::setPlusInfinity(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			thisPxExtendedVec3->setPlusInfinity();
			//if(thisPxExtendedVec3 != NULL && inPxExtendedVec3 != NULL) 
			//{			
			return scope.Close(args.Holder());
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxExtendedVec3::setMinusInfinity(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxExtendedVec3* thisPxExtendedVec3 = unwrap<PxExtendedVec3>(args.Holder());
			thisPxExtendedVec3->setMinusInfinity();
			//if(thisPxExtendedVec3 != NULL && inPxExtendedVec3 != NULL) 
			//{			
			return scope.Close(args.Holder());
			//}
		}

		return scope.Close( Undefined() );
	}

//PxVec4
	Handle<Value>  V8PxVec4::PxVec4Constructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));


		if(args.Length() == 0){
			PxVec4* vecObject = new PxVec4();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),vecObject, &CleanupDelete);
			self->SetInternalField(0, External::New( vecObject ));

			return scope.Close( self );
		}
		if(args.Length() == 1 && !args[0].IsEmpty()){
			PxVec4* vecObject;
			if(args[0]->IsNumber()){
				vecObject = new PxVec4( args[0]->NumberValue());
			}
			else if(args[0]->IsObject() && V8PxVec4::getTemplate()->HasInstance(args[0])){
				vecObject = new PxVec4(*unwrap<PxVec4>(args[0]->ToObject()));
			}
			else if(args[0]->IsArray()){
				Local<Array> arr = Local<Array>::Cast(args[0]);
				if(arr->Length() == 4){
					PxReal vals[4];

					for(int i = 0; i < 4; i++){
						Local<Value> element = arr->GetInternalField(i);
						if(element->IsNumber()){
							vals[i] = element->NumberValue();
						}
						else {
							return ThrowException( Exception::TypeError( v8stringCreate(4, "PxVec4 constuctor must take an Array of Numbers ONLY. Element at Index: ", i, " is ", *String::Utf8Value(element->ToObject()->GetConstructorName())) ) );
						}
					}

					vecObject = new PxVec4(vals);
				}
				else {
					return ThrowException( Exception::TypeError( v8stringCreate(2, "PxVec4 constuctor must take an Array of Length 4 ONLY. Array Length is: ", arr->Length()) ) );
				}
			}
			else {
				return ThrowException( Exception::TypeError( String::New("PxVec4 constructor takes nothing, (Number), (Number, Number, Number, Number), (Array[4](Number)), (PxVec3, Number), or (PxVec4) as an argument.") ) );
			}
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),vecObject, &CleanupDelete);
			self->SetInternalField(0, External::New( vecObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0]) &&
				!args[1].IsEmpty() && args[1]->IsNumber()){
			PxVec4* vecObject = new PxVec4(*unwrap<PxVec3>(args[0]->ToObject()), args[1]->NumberValue());
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),vecObject, &CleanupDelete);
			self->SetInternalField(0, External::New( vecObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 4){
			if(!args[0].IsEmpty() && args[0]->IsNumber() &&
				!args[1].IsEmpty() && args[1]->IsNumber() &&
				!args[2].IsEmpty() && args[2]->IsNumber() &&
				!args[3].IsEmpty() && args[3]->IsNumber()) 
			{
				PxVec4* vecObject = new PxVec4( args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue(), args[3]->NumberValue() );
				Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//				self.MakeWeak(Isolate::GetCurrent(),vecObject, &CleanupDelete);
				self->SetInternalField(0, External::New( vecObject ));

				return scope.Close( self );
			}
		}
        
		return ThrowException( Exception::TypeError( String::New("PxVec4 constructor takes nothing, (Number), (Number, Number, Number, Number), (Array[4](Number)), (PxVec3, Number), or (PxVec4) as an argument.") ) );
	}

	Handle<Value> V8PxVec4::getX( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxVec4* thisPxVec4 = unwrap<PxVec4>(info.Holder());
		//if(thisPxVec4 != NULL) 
		//{
			return scope.Close(Number::New( thisPxVec4->x ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxVec4::setX( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PxVec4* thisPxVec4 = unwrap<PxVec4>(info.Holder());
			//if(thisPxVec4 != NULL && value->IsNumber()) 
			//{
				thisPxVec4->x = value->NumberValue();
			//}
		}
	}

	Handle<Value> V8PxVec4::getY( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxVec4* thisPxVec4 = unwrap<PxVec4>(info.Holder());
		//if(thisPxVec4 != NULL) 
		//{
			return scope.Close(Number::New( thisPxVec4->y ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxVec4::setY( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PxVec4* thisPxVec4 = unwrap<PxVec4>(info.Holder());
			//if(thisPxVec4 != NULL && value->IsNumber()) 
			//{
				thisPxVec4->y = value->NumberValue();
			//}
		}
	}

	Handle<Value> V8PxVec4::getZ( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxVec4* thisPxVec4 = unwrap<PxVec4>(info.Holder());
		//if(thisPxVec4 != NULL) 
		//{
			return scope.Close(Number::New( thisPxVec4->z ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxVec4::setZ( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PxVec4* thisPxVec4 = unwrap<PxVec4>(info.Holder());
			//if(thisPxVec4 != NULL && value->IsNumber()) 
			//{
				thisPxVec4->z = value->NumberValue();
			//}
		}
	}

	Handle<Value> V8PxVec4::getW( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxVec4* thisPxVec4 = unwrap<PxVec4>(info.Holder());
		//if(thisPxVec4 != NULL) 
		//{
			return scope.Close(Number::New( thisPxVec4->w ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxVec4::setW( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PxVec4* thisPxVec4 = unwrap<PxVec4>(info.Holder());
			//if(thisPxVec4 != NULL && value->IsNumber()) 
			//{
				thisPxVec4->w = value->NumberValue();
			//}
		}
	}

	Handle<Value> V8PxVec4::elementGet(uint32_t index, const AccessorInfo& info){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(index >=0 && index<= 3){
			PxVec4* thisPxVec4 = unwrap<PxVec4>(info.Holder());
			//if(thisPxVec4 != NULL) 
			//{
				return scope.Close(Number::New( (*thisPxVec4)[index] ));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::elementSet(uint32_t index, Local<Value> value, const AccessorInfo& info){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber() && index >=0 && index<= 3){
			PxVec4* thisPxVec4 = unwrap<PxVec4>(info.Holder());
			//if(thisPxVec4 != NULL) 
			//{
				(*thisPxVec4)[index] = value->NumberValue();
				return scope.Close(value);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::compare(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec4::getTemplate()->HasInstance(args[0])) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			PxVec4* inPxVec4 = unwrap<PxVec4>(args[0]->ToObject());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
				return scope.Close( Boolean::New(*thisPxVec4 == *inPxVec4));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::acompare(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec4::getTemplate()->HasInstance(args[0])) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			PxVec4* inPxVec4 = unwrap<PxVec4>(args[0]->ToObject());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
				return scope.Close( Boolean::New(*thisPxVec4 != *inPxVec4));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::isZero(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
			return scope.Close( Boolean::New(thisPxVec4->isZero()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::isFinite(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
			return scope.Close( Boolean::New(thisPxVec4->isFinite()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::isNormalized(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
			return scope.Close( Boolean::New(thisPxVec4->isNormalized()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::magnitudeSquared(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
			return scope.Close( Number::New(thisPxVec4->magnitudeSquared()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::magnitude(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
			return scope.Close( Number::New(thisPxVec4->magnitude()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::negate(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
			PxVec4* obj = new PxVec4(-*thisPxVec4);
			Persistent<Object> newPxVec4 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec4.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec4->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec4);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::add(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec4::getTemplate()->HasInstance(args[0])) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			PxVec4* inPxVec4 = unwrap<PxVec4>(args[0]->ToObject());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
			PxVec4* obj = new PxVec4(*thisPxVec4 + *inPxVec4);
			Persistent<Object> newPxVec4 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec4.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec4->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec4);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::subtract(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec4::getTemplate()->HasInstance(args[0])) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			PxVec4* inPxVec4 = unwrap<PxVec4>(args[0]->ToObject());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
			PxVec4* obj = new PxVec4(*thisPxVec4 - *inPxVec4);
			Persistent<Object> newPxVec4 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec4.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec4->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec4);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::multiply(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
			PxVec4* obj = new PxVec4(*thisPxVec4 * args[0]->NumberValue());
			Persistent<Object> newPxVec4 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec4.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec4->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec4);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::divide(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
			PxVec4* obj = new PxVec4(*thisPxVec4 / args[0]->NumberValue());
			Persistent<Object> newPxVec4 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec4.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec4->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec4);
			//}
		}

		return scope.Close( Undefined() );
	}


	Handle<Value> V8PxVec4::assignmentAdd(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec4::getTemplate()->HasInstance(args[0])) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			PxVec4* inPxVec4 = unwrap<PxVec4>(args[0]->ToObject());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
				*thisPxVec4 += *inPxVec4;
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::assignmentSubtract(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec4::getTemplate()->HasInstance(args[0])) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			PxVec4* inPxVec4 = unwrap<PxVec4>(args[0]->ToObject());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
				*thisPxVec4 -= *inPxVec4;
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::assignmentMultiply(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
				*thisPxVec4 *= args[0]->NumberValue();
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::assignmentDivide(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
				*thisPxVec4 /= args[0]->NumberValue();
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}


	Handle<Value> V8PxVec4::dot(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec4::getTemplate()->HasInstance(args[0])) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			PxVec4* inPxVec4 = unwrap<PxVec4>(args[0]->ToObject());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{			
			return scope.Close(Number::New(thisPxVec4->dot(*inPxVec4)));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::getNormalized(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
			PxVec4* obj = new PxVec4(thisPxVec4->getNormalized());
			Persistent<Object> newPxVec4 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec4.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec4->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec4);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::normalize(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
			
			return scope.Close(Number::New(thisPxVec4->normalize()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::elementwiseMultiply(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec4::getTemplate()->HasInstance(args[0])) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			PxVec4* inPxVec4 = unwrap<PxVec4>(args[0]->ToObject());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
			PxVec4* obj = new PxVec4(thisPxVec4->multiply(*inPxVec4));
			Persistent<Object> newPxVec4 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec4.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec4->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec4);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::elementwiseMin(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec4::getTemplate()->HasInstance(args[0])) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			PxVec4* inPxVec4 = unwrap<PxVec4>(args[0]->ToObject());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
			PxVec4* obj = new PxVec4(thisPxVec4->minimum(*inPxVec4));
			Persistent<Object> newPxVec4 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec4.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec4->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec4);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::elementwiseMax(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec4::getTemplate()->HasInstance(args[0])) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			PxVec4* inPxVec4 = unwrap<PxVec4>(args[0]->ToObject());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
			PxVec4* obj = new PxVec4(thisPxVec4->maximum(*inPxVec4));
			Persistent<Object> newPxVec4 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxVec4.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec4->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec4);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::getXYZ(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{
			PxVec3* obj = new PxVec3(thisPxVec4->getXYZ());
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxVec4::setZero(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxVec4* thisPxVec4 = unwrap<PxVec4>(args.Holder());
			//if(thisPxVec4 != NULL && inPxVec4 != NULL) 
			//{

			thisPxVec4->setZero();
			
			return scope.Close(args.Holder());
			//}
		}

		return scope.Close( Undefined() );
	}

//PxQuat
	Handle<Value>  V8PxQuat::PxQuatConstructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){
			PxQuat* quatObject = new PxQuat();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),quatObject, &CleanupDelete);
			self->SetInternalField(0, External::New( quatObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty()){
			PxQuat* quatObject;
			if(args[0]->IsObject() && V8PxMat33::getTemplate()->HasInstance(args[0])){
				quatObject = new PxQuat(*unwrap<PxMat33>(args[0]->ToObject()));
			}
			else if(args[0]->IsObject() && V8PxQuat::getTemplate()->HasInstance(args[0])){
				quatObject = new PxQuat(*unwrap<PxQuat>(args[0]->ToObject()));
			}
			else {
				return ThrowException( Exception::TypeError( String::New("PxQuat constructor takes nothing, (PxMat33), (Number, Number, Number, Number), (Number, PxVec3), or (PxQuat) as an argument.") ) );
			}
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),quatObject, &CleanupDelete);
			self->SetInternalField(0, External::New( quatObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsNumber() && 
			!args[1].IsEmpty() && args[1]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[1])){
			PxQuat* quatObject = new PxQuat(args[0]->NumberValue(),*unwrap<PxVec3>(args[1]->ToObject()));
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),quatObject, &CleanupDelete);
			self->SetInternalField(0, External::New( quatObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 4){
			if(!args[0].IsEmpty() && args[0]->IsNumber() &&
				!args[1].IsEmpty() && args[1]->IsNumber() &&
				!args[2].IsEmpty() && args[2]->IsNumber() &&
				!args[3].IsEmpty() && args[3]->IsNumber()) 
			{
				PxQuat* quatObject = new PxQuat( args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue(), args[3]->NumberValue() );
				Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//				self.MakeWeak(Isolate::GetCurrent(),quatObject, &CleanupDelete);
				self->SetInternalField(0, External::New( quatObject ));

				return scope.Close( self );
			}
		}
        
		return ThrowException( Exception::TypeError( String::New("PxQuat constructor takes nothing, (PxMat33), (Number, Number, Number, Number), (Number, PxVec3), or (PxQuat) as an argument.") ) );
	}

	Handle<Value> V8PxQuat::getX( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxQuat* thisPxQuat = unwrap<PxQuat>(info.Holder());
		//if(thisPxQuat != NULL) 
		//{
			Handle<Number> val = Number::New( thisPxQuat->x );
			return scope.Close(val);
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxQuat::setX( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxQuat* thisPxQuat = unwrap<PxQuat>(info.Holder());
		if(thisPxQuat != NULL && value->IsNumber()) 
		{
			thisPxQuat->x = value->NumberValue();
		}
	}

	Handle<Value> V8PxQuat::getY( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxQuat* thisPxQuat = unwrap<PxQuat>(info.Holder());
		//if(thisPxQuat != NULL) 
		//{
			Handle<Number> val = Number::New( thisPxQuat->y );
			return scope.Close(val);
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxQuat::setY( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxQuat* thisPxQuat = unwrap<PxQuat>(info.Holder());
		if(thisPxQuat != NULL && value->IsNumber()) 
		{
			thisPxQuat->y = value->NumberValue();
		}
	}

	Handle<Value> V8PxQuat::getZ( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxQuat* thisPxQuat = unwrap<PxQuat>(info.Holder());
		//if(thisPxQuat != NULL) 
		//{
			Handle<Number> val = Number::New( thisPxQuat->z );
			return scope.Close(val);
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxQuat::setZ( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxQuat* thisPxQuat = unwrap<PxQuat>(info.Holder());
		if(thisPxQuat != NULL && value->IsNumber()) 
		{
			thisPxQuat->z = value->NumberValue();
		}
	}

	Handle<Value> V8PxQuat::getW( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxQuat* thisPxQuat = unwrap<PxQuat>(info.Holder());
		//if(thisPxQuat != NULL) 
		//{
			Handle<Number> val = Number::New( thisPxQuat->w );
			return scope.Close(val);
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxQuat::setW( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxQuat* thisPxQuat = unwrap<PxQuat>(info.Holder());
		if(thisPxQuat != NULL && value->IsNumber()) 
		{
			thisPxQuat->w = value->NumberValue();
		}
	}


	Handle<Value> V8PxQuat::isFinite(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( Boolean::New(thisPxQuat->isFinite()));
			//}
		}

		return scope.Close( Undefined() );
	}

	//Handle<Value> V8PxQuat::isValid(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0) 
 //       {
	//		PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
	//		//if(thisPxQuat != NULL && inPxQuat != NULL) 
	//		//{
	//		return scope.Close( Boolean::New(thisPxQuat->isValid()));
	//		//}
	//	}

	//	return scope.Close( Undefined() );
	//}

	Handle<Value> V8PxQuat::isSane(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( Boolean::New(thisPxQuat->isSane()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::toRadiansAndUnitAxis(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
			PxReal angle;
			PxVec3 axis;
			thisPxQuat->toRadiansAndUnitAxis(angle, axis);
			Local<Array> returnArray = Array::New(2);

			returnArray->Set(0, Number::New(angle));

			PxVec3* obj = new PxVec3(axis);
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));

			returnArray->Set(1, newPxVec3);

			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( returnArray );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::getAngle(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( Number::New(thisPxQuat->getAngle()));
			//}
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxQuat::getTemplate()->HasInstance(args[0])) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
			PxQuat* inPxQuat = unwrap<PxQuat>(args[0]->ToObject());
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( Number::New(thisPxQuat->getAngle(*inPxQuat)));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::magnitudeSquared(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( Number::New(thisPxQuat->magnitudeSquared()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::dot(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxQuat::getTemplate()->HasInstance(args[0])) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
			PxQuat* inPxQuat = unwrap<PxQuat>(args[0]->ToObject());
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{			
			return scope.Close(Number::New(thisPxQuat->dot(*inPxQuat)));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::getNormalized(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			PxQuat* obj = new PxQuat(thisPxQuat->getNormalized());
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxQuat);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::magnitude(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( Number::New(thisPxQuat->magnitude()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::normalize(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			
			return scope.Close(Number::New(thisPxQuat->normalize()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::getConjugate(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			PxQuat* obj = new PxQuat(thisPxQuat->getConjugate());
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxQuat);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::getImaginaryPart(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());

			PxVec3* imaginary = &thisPxQuat->getImaginaryPart();

			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxVec3->SetInternalField(0, External::New(imaginary));

			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( newPxVec3 );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::getBasisVector0(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());

			PxVec3* obj = new PxVec3(thisPxQuat->getBasisVector0());
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));

			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( newPxVec3 );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::getBasisVector1(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());

			PxVec3* obj = new PxVec3(thisPxQuat->getBasisVector1());
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New(obj));

			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( newPxVec3 );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::getBasisVector2(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());

			PxVec3* obj = new PxVec3(thisPxQuat->getBasisVector2());
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));

			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( newPxVec3 );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::rotate(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());

			PxVec3* obj = new PxVec3(thisPxQuat->rotate(*inPxVec3));
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));

			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( newPxVec3 );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::rotateInv(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());

			PxVec3* obj = new PxVec3(thisPxQuat->rotateInv(*inPxVec3));
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));

			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( newPxVec3 );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::assignmentAdd(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxQuat::getTemplate()->HasInstance(args[0])) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
			PxQuat* inPxQuat = unwrap<PxQuat>(args[0]->ToObject());
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
				*thisPxQuat += *inPxQuat;
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::assignmentSubtract(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxQuat::getTemplate()->HasInstance(args[0])) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
			PxQuat* inPxQuat = unwrap<PxQuat>(args[0]->ToObject());
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
				*thisPxQuat -= *inPxQuat;
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::assignmentMultiply(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty())
        {
			if(args[0]->IsNumber()){
				PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
				//if(thisPxQuat != NULL && inPxQuat != NULL) 
				//{

				*thisPxQuat *= args[0]->NumberValue();
			
				return scope.Close(args.Holder());
				//}
			}
			else if(args[0]->IsObject() && V8PxQuat::getTemplate()->HasInstance(args[0])){
				PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
				PxQuat* inPxQuat = unwrap<PxQuat>(args[0]->ToObject());
				//if(thisPxQuat != NULL && inPxQuat != NULL) 
				//{

				*thisPxQuat *= *inPxQuat;
			
				return scope.Close(args.Holder());
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::add(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxQuat::getTemplate()->HasInstance(args[0])) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
			PxQuat* inPxQuat = unwrap<PxQuat>(args[0]->ToObject());
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{

			PxQuat* obj = new PxQuat(*thisPxQuat + *inPxQuat);
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxQuat);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::subtract(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxQuat::getTemplate()->HasInstance(args[0])) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
			PxQuat* inPxQuat = unwrap<PxQuat>(args[0]->ToObject());
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{

			PxQuat* obj = new PxQuat(*thisPxQuat - *inPxQuat);
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxQuat);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::multiply(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty())
        {
			if(args[0]->IsNumber()){
				PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
				//if(thisPxQuat != NULL && inPxQuat != NULL) 
				//{

				PxQuat* obj = new PxQuat(*thisPxQuat * args[0]->NumberValue());
				Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//				newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxQuat->SetInternalField(0, External::New( obj ));
			
				return scope.Close(newPxQuat);
				//}
			}
			else if(args[0]->IsObject() && V8PxQuat::getTemplate()->HasInstance(args[0])){
				PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
				PxQuat* inPxQuat = unwrap<PxQuat>(args[0]->ToObject());
				//if(thisPxQuat != NULL && inPxQuat != NULL) 
				//{

				PxQuat* obj = new PxQuat(*thisPxQuat * *inPxQuat);
				Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//				newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxQuat->SetInternalField(0, External::New( obj ));
			
				return scope.Close(newPxQuat);
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::negate(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxQuat* thisPxQuat = unwrap<PxQuat>(args.Holder());
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{

			PxQuat* obj = new PxQuat(-*thisPxQuat);
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxQuat);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxQuat::createIdentity(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{

			PxQuat* obj = new PxQuat(PxQuat::createIdentity());
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8PxQuat::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxQuat.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxQuat->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxQuat);
			//}
		}

		return scope.Close( Undefined() );
	}

//PxMat33
	Handle<Value>  V8PxMat33::PxMat33Constructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){
			PxMat33* matObject = new PxMat33();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),matObject, &CleanupDelete);
			self->SetInternalField(0, External::New( matObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() ){
			PxMat33* matObject;
			if(args[0]->IsObject() && V8PxMat33::getTemplate()->HasInstance(args[0])){
				matObject = new PxMat33(*unwrap<PxMat33>(args[0]->ToObject()));
			}
			else if(args[0]->IsObject() && V8PxQuat::getTemplate()->HasInstance(args[0])){
				matObject = new PxMat33(*unwrap<PxQuat>(args[0]->ToObject()));
			}
			else if(args[0]->IsArray()){
				Local<Array> arr = Local<Array>::Cast(args[0]);
				if(arr->Length() == 9){
					PxReal vals[9];

					for(int i = 0; i < 9; i++){
						Local<Value> element = arr->GetInternalField(i);
						if(element->IsNumber()){
							vals[i] = element->NumberValue();
						}
						else {
							return ThrowException( Exception::TypeError( v8stringCreate(4, "PxMat33 constuctor must take an Array of Numbers ONLY. Element at Index: ", i, " is ", *String::Utf8Value(element->ToObject()->GetConstructorName())) ) );
						}
					}

					matObject = new PxMat33(vals);

					Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//					self.MakeWeak(Isolate::GetCurrent(),matObject, &CleanupDelete);
					self->SetInternalField(0, External::New( matObject ));

					return scope.Close( self );
				}
				else {
					return ThrowException( Exception::TypeError( v8stringCreate(2, "PxMat33 constuctor must take an Array of length 9 ONLY. Not length: ", arr->Length()) ) );
				}
			}
			else {
				return ThrowException( Exception::TypeError( String::New("PxMat33 constructor takes nothing, (PxQuat), (Array[9](Number)), (PxVec3, PxVec3, PxVec3), or (PxMat33) as an argument.") ) );
			}
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),matObject, &CleanupDelete);
			self->SetInternalField(0, External::New( matObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0]) &&
				!args[1].IsEmpty() && args[1]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[1]) &&
				!args[2].IsEmpty() && args[2]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[2])){

			PxMat33* matObject = new PxMat33(*unwrap<PxVec3>(args[0]->ToObject()),*unwrap<PxVec3>(args[1]->ToObject()),*unwrap<PxVec3>(args[2]->ToObject()));
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),matObject, &CleanupDelete);
			self->SetInternalField(0, External::New( matObject ));

			return scope.Close( self );
		}
        
		return ThrowException( Exception::TypeError( String::New("PxMat33 constructor takes nothing, (PxQuat), (Array[9](Number)), (PxVec3, PxVec3, PxVec3), or (PxMat33) as an argument.") ) );
	}

	Handle<Value> V8PxMat33::elementGet(uint32_t index, const AccessorInfo& info){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(index >=0 && index <= 2){
			PxMat33* thisPxMat33 = unwrap<PxMat33>(info.Holder());
			//if(thisPxMat33 != NULL) 
			//{
				Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxVec3.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
				newPxVec3->SetInternalField(0, External::New(&(*thisPxMat33)[index]));

				return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat33::elementSet(uint32_t index, Local<Value> value, const AccessorInfo& info){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(index >=0 && index <= 2 && !value.IsEmpty() && value->IsObject() && V8PxVec3::getTemplate()->HasInstance(value)){
			PxMat33* thisPxMat33 = unwrap<PxMat33>(info.Holder());
			PxVec3* thisPxVec3 = unwrap<PxVec3>(Local<Object>::Cast(value));
			//if(thisPxMat33 != NULL) 
			//{

				(*thisPxMat33)[index] = *thisPxVec3;

				return scope.Close(value);
			//}
		}

		return scope.Close( Undefined() );
	}
		
	Handle<Value> V8PxMat33::createIdentity(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			//if(thisPxMat33 != NULL && inPxMat33 != NULL) 
			//{
			PxMat33* obj = new PxMat33(PxMat33::createIdentity());
			Persistent<Object> newPxMat33 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxMat33::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxMat33.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxMat33->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxMat33);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat33::createZero(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			//if(thisPxMat33 != NULL && inPxMat33 != NULL) 
			//{
			PxMat33* obj = new PxMat33(PxMat33::createZero());
			Persistent<Object> newPxMat33 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxMat33::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxMat33.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxMat33->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxMat33);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat33::createDiagonal(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			//if(thisPxMat33 != NULL && inPxMat33 != NULL) 
			//{
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());

			PxMat33* obj = new PxMat33(PxMat33::createDiagonal(*inPxVec3));
			Persistent<Object> newPxMat33 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxMat33::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxMat33.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxMat33->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxMat33);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat33::getTranspose(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxMat33* thisPxMat33 = unwrap<PxMat33>(args.Holder());
			//if(thisPxMat33 != NULL && inPxMat33 != NULL) 
			//{
			PxMat33* obj = new PxMat33(thisPxMat33->getTranspose());
			Persistent<Object> newPxMat33 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxMat33::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxMat33.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxMat33->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxMat33);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat33::getInverse(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxMat33* thisPxMat33 = unwrap<PxMat33>(args.Holder());
			//if(thisPxMat33 != NULL && inPxMat33 != NULL) 
			//{
			PxMat33* obj = new PxMat33(thisPxMat33->getInverse());
			Persistent<Object> newPxMat33 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxMat33::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxMat33.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxMat33->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxMat33);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat33::getDeterminant(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxMat33* thisPxMat33 = unwrap<PxMat33>(args.Holder());
			//if(thisPxMat33 != NULL && inPxMat33 != NULL) 
			//{			
			return scope.Close( Number::New(thisPxMat33->getDeterminant()) );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat33::transform(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxMat33* thisPxMat33 = unwrap<PxMat33>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxMat33 != NULL && inPxMat33 != NULL) 
			//{
			PxVec3* obj = new PxVec3(thisPxMat33->transform(*inPxVec3));
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat33::transformTranspose(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxMat33* thisPxMat33 = unwrap<PxMat33>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxMat33 != NULL && inPxMat33 != NULL) 
			//{
			PxVec3* obj = new PxVec3(thisPxMat33->transformTranspose(*inPxVec3));
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat33::assignmentAdd(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxMat33::getTemplate()->HasInstance(args[0])) 
        {
			PxMat33* thisPxMat33 = unwrap<PxMat33>(args.Holder());
			PxMat33* inPxMat33 = unwrap<PxMat33>(args[0]->ToObject());
			//if(thisPxMat33 != NULL && inPxMat33 != NULL) 
			//{
				*thisPxMat33 += *inPxMat33;
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat33::assignmentSubtract(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxMat33::getTemplate()->HasInstance(args[0])) 
        {
			PxMat33* thisPxMat33 = unwrap<PxMat33>(args.Holder());
			PxMat33* inPxMat33 = unwrap<PxMat33>(args[0]->ToObject());
			//if(thisPxMat33 != NULL && inPxMat33 != NULL) 
			//{
				*thisPxMat33 -= *inPxMat33;
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat33::assignmentMultiply(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && !args[0].IsEmpty() && args[0]->IsNumber())
        {
			PxMat33* thisPxMat33 = unwrap<PxMat33>(args.Holder());
			//if(thisPxMat33 != NULL && inPxMat33 != NULL) 
			//{

			*thisPxMat33 *= args[0]->NumberValue();
			
			return scope.Close(args.Holder());
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat33::add(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxMat33::getTemplate()->HasInstance(args[0])) 
        {
			PxMat33* thisPxMat33 = unwrap<PxMat33>(args.Holder());
			PxMat33* inPxMat33 = unwrap<PxMat33>(args[0]->ToObject());
			//if(thisPxMat33 != NULL && inPxMat33 != NULL) 
			//{
			PxMat33* obj = new PxMat33(*thisPxMat33 + *inPxMat33);
			Persistent<Object> newPxMat33 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxMat33.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxMat33->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxMat33);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat33::subtract(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxMat33::getTemplate()->HasInstance(args[0])) 
        {
			PxMat33* thisPxMat33 = unwrap<PxMat33>(args.Holder());
			PxMat33* inPxMat33 = unwrap<PxMat33>(args[0]->ToObject());
			//if(thisPxMat33 != NULL && inPxMat33 != NULL) 
			//{
			PxMat33* obj = new PxMat33(*thisPxMat33 - *inPxMat33);
			Persistent<Object> newPxMat33 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxMat33.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxMat33->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxMat33);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat33::multiply(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty())
        {
			if(args[0]->IsNumber()){
				PxMat33* thisPxMat33 = unwrap<PxMat33>(args.Holder());
				//if(thisPxMat33 != NULL && inPxMat33 != NULL) 
				//{
				PxMat33* obj = new PxMat33(*thisPxMat33 * args[0]->NumberValue());
				Persistent<Object> newPxMat33 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//				newPxMat33.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxMat33->SetInternalField(0, External::New( obj ));
			
				return scope.Close(newPxMat33);
				//}
			}
			else if(args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])){
				PxMat33* thisPxMat33 = unwrap<PxMat33>(args.Holder());
				PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
				//if(thisPxMat33 != NULL && inPxMat33 != NULL) 
				//{
				PxVec3* obj = new PxVec3(*thisPxMat33 * *inPxVec3);
				Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//				newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxVec3->SetInternalField(0, External::New( obj ));
			
				return scope.Close(newPxVec3);
			}
			else if(args[0]->IsObject() && V8PxMat33::getTemplate()->HasInstance(args[0])){
				PxMat33* thisPxMat33 = unwrap<PxMat33>(args.Holder());
				PxMat33* inPxMat33 = unwrap<PxMat33>(args[0]->ToObject());
				//if(thisPxMat33 != NULL && inPxMat33 != NULL) 
				//{
				PxMat33* obj = new PxMat33(*thisPxMat33 * *inPxMat33);
				Persistent<Object> newPxMat33 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//				newPxMat33.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxMat33->SetInternalField(0, External::New( obj ));
			
				return scope.Close(newPxMat33);
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat33::negate(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxMat33* thisPxMat33 = unwrap<PxMat33>(args.Holder());
			//if(thisPxMat33 != NULL && inPxMat33 != NULL) 
			//{
			PxMat33* obj = new PxMat33(-*thisPxMat33);
			Persistent<Object> newPxMat33 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxMat33.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxMat33->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxMat33);
			//}
		}

		return scope.Close( Undefined() );
	}

//PxMat44
	Handle<Value>  V8PxMat44::PxMat44Constructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){
			PxMat44* matObject = new PxMat44();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),matObject, &CleanupDelete);
			self->SetInternalField(0, External::New( matObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty()){
			PxMat44* matObject;
			if(args[0]->IsObject() && V8PxMat44::getTemplate()->HasInstance(args[0])){ //Mat44
				matObject = new PxMat44(*unwrap<PxMat44>(args[0]->ToObject()));
			}
			else if(args[0]->IsObject() && V8PxQuat::getTemplate()->HasInstance(args[0])){ //Quat
				matObject = new PxMat44(*unwrap<PxQuat>(args[0]->ToObject()));
			}
			else if(args[0]->IsObject() && V8PxVec4::getTemplate()->HasInstance(args[0])){ //Vec4 diagonal
				matObject = new PxMat44(*unwrap<PxVec4>(args[0]->ToObject()));
			}
			else if(args[0]->IsArray()){ //Number Array
				Local<Array> arr = Local<Array>::Cast(args[0]);
				if(arr->Length() == 16){
					PxReal vals[16];

					for(int i = 0; i < 16; i++){
						Local<Value> element = arr->GetInternalField(i);

						if(element->IsNumber()){
							vals[i] = element->NumberValue();
						}
						else {
							return ThrowException( Exception::TypeError( v8stringCreate(4, "PxMat44 constuctor must take an Array of Numbers ONLY. Element at Index: ", i, " is ", *String::Utf8Value(element->ToObject()->GetConstructorName())) ) );
						}
					}

					matObject = new PxMat44(vals);

					Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//					self.MakeWeak(Isolate::GetCurrent(),matObject, &CleanupDelete);
					self->SetInternalField(0, External::New( matObject ));

					return scope.Close( self );
				}
				else {
					return ThrowException( Exception::TypeError( v8stringCreate(2, "PxMat44 constuctor must take an Array of length 16 ONLY. Not length: ", arr->Length()) ) );
				}
			}
			else {
				return ThrowException( Exception::TypeError( String::New("PxMat44 constructor takes nothing, (PxQuat), (PxVec4), (Array[16](Number)), (Mat33, PxVec3), (PxVec4, PxVec4, PxVec4, PxVec4), (PxVec3, PxVec3, PxVec3, PxVec3), or (PxMat44) as an argument.") ) );
			}
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),matObject, &CleanupDelete);
			self->SetInternalField(0, External::New( matObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxMat33::getTemplate()->HasInstance(args[0]) &&
				!args[1].IsEmpty() && args[1]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[1])){ //Mat33 orientation and Vec3 Position

			PxMat44* matObject = new PxMat44(*unwrap<PxMat33>(args[0]->ToObject()),*unwrap<PxVec3>(args[1]->ToObject()));
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),matObject, &CleanupDelete);
			self->SetInternalField(0, External::New( matObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 4 && !args[0].IsEmpty() && !args[1].IsEmpty() && !args[2].IsEmpty() && !args[3].IsEmpty()){
			PxMat44* matObject;

			if(	args[0]->IsObject() && V8PxVec4::getTemplate()->HasInstance(args[0]) &&
				args[1]->IsObject() && V8PxVec4::getTemplate()->HasInstance(args[1]) &&
				args[2]->IsObject() && V8PxVec4::getTemplate()->HasInstance(args[2]) &&
				args[3]->IsObject() && V8PxVec4::getTemplate()->HasInstance(args[3])){

				matObject = new PxMat44(*unwrap<PxVec4>(args[0]->ToObject()),*unwrap<PxVec4>(args[1]->ToObject()),
										*unwrap<PxVec4>(args[2]->ToObject()), *unwrap<PxVec4>(args[3]->ToObject()));
			}
			else if(args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0]) &&
					args[1]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[1]) &&
					args[2]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[2]) &&
					args[3]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[3])){

				matObject = new PxMat44(*unwrap<PxVec3>(args[0]->ToObject()),*unwrap<PxVec3>(args[1]->ToObject()),
										*unwrap<PxVec3>(args[2]->ToObject()), *unwrap<PxVec3>(args[3]->ToObject()));
			}
			else {
				return ThrowException( Exception::TypeError( String::New("PxMat44 constructor takes nothing, (PxQuat), (PxVec4), (Array[16](Number)), (Mat33, PxVec3), (PxVec4, PxVec4, PxVec4, PxVec4), (PxVec3, PxVec3, PxVec3, PxVec3), or (PxMat44) as an argument.") ) );
			}

			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),matObject, &CleanupDelete);
			self->SetInternalField(0, External::New( matObject ));

			return scope.Close( self );
		}
        
		return ThrowException( Exception::TypeError( String::New("PxMat44 constructor takes nothing, (PxQuat), (PxVec4), (Array[16](Number)), (Mat33, PxVec3), (PxVec4, PxVec4, PxVec4, PxVec4), (PxVec3, PxVec3, PxVec3, PxVec3), or (PxMat44) as an argument.") ) );
	}

	Handle<Value> V8PxMat44::elementGet(uint32_t index, const AccessorInfo& info){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(index >=0 && index <= 3){
			PxMat44* thisPxMat44 = unwrap<PxMat44>(info.Holder());
			//if(thisPxMat44 != NULL) 
			//{
				Persistent<Object> newPxVec4 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec4::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxVec4.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
				newPxVec4->SetInternalField(0, External::New(&(*thisPxMat44)[index]));

				return scope.Close(newPxVec4);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat44::elementSet(uint32_t index, Local<Value> value, const AccessorInfo& info){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(index >=0 && index <= 3 && !value.IsEmpty() && value->IsObject() && V8PxVec4::getTemplate()->HasInstance(value)){
			PxMat44* thisPxMat44 = unwrap<PxMat44>(info.Holder());
			PxVec4* thisPxVec4 = unwrap<PxVec4>(Local<Object>::Cast(value));
			//if(thisPxMat44 != NULL) 
			//{

				(*thisPxMat44)[index] = *thisPxVec4;

				return scope.Close(value);
			//}
		}

		return scope.Close( Undefined() );
	}
		
	Handle<Value> V8PxMat44::createIdentity(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
			//{
			PxMat44* obj = new PxMat44(PxMat44::createIdentity());
			Persistent<Object> newPxMat44 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxMat44::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxMat44.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxMat44->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxMat44);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat44::createZero(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
			//{
			PxMat44* obj = new PxMat44(PxMat44::createZero());
			Persistent<Object> newPxMat44 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxMat44::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxMat44.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxMat44->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxMat44);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat44::getTranspose(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
			//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
			//{
			PxMat44* obj = new PxMat44(thisPxMat44->getTranspose());
			Persistent<Object> newPxMat44 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxMat44::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxMat44.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxMat44->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxMat44);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat44::transform(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject())
		{
			if(V8PxVec3::getTemplate()->HasInstance(args[0])){

				PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
				PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
				//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
				//{
				PxVec3* obj = new PxVec3(thisPxMat44->transform(*inPxVec3));
				Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxVec3->SetInternalField(0, External::New( obj ));
			
				return scope.Close(newPxVec3);
				//}
			}
			else if(V8PxVec4::getTemplate()->HasInstance(args[0])){

				PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
				PxVec4* inPxVec4 = unwrap<PxVec4>(args[0]->ToObject());
				//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
				//{
				PxVec4* obj = new PxVec4(thisPxMat44->transform(*inPxVec4));
				Persistent<Object> newPxVec4 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec4::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxVec4.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxVec4->SetInternalField(0, External::New( obj ));
			
				return scope.Close(newPxVec4);
				//}
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat44::rotate(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject())
		{
			if(V8PxVec3::getTemplate()->HasInstance(args[0])){

				PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
				PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
				//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
				//{
				PxVec3* obj = new PxVec3(thisPxMat44->rotate(*inPxVec3));
				Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxVec3->SetInternalField(0, External::New( obj ));
			
				return scope.Close(newPxVec3);
				//}
			}
			else if(V8PxVec4::getTemplate()->HasInstance(args[0])){

				PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
				PxVec4* inPxVec4 = unwrap<PxVec4>(args[0]->ToObject());
				//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
				//{
				PxVec4* obj = new PxVec4(thisPxMat44->rotate(*inPxVec4));
				Persistent<Object> newPxVec4 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec4::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxVec4.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxVec4->SetInternalField(0, External::New( obj ));
			
				return scope.Close(newPxVec4);
				//}
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat44::getBasis(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsInt32())
		{
				PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
				//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
				//{
				PxVec3* obj = new PxVec3(thisPxMat44->getBasis(args[0]->Int32Value()));
				Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxVec3->SetInternalField(0, External::New( obj ));
			
				return scope.Close(newPxVec3);
				//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat44::getPosition(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0)
		{
				PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
				//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
				//{
				PxVec3* obj = new PxVec3(thisPxMat44->getPosition());
				Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxVec3->SetInternalField(0, External::New( obj ));
			
				return scope.Close(newPxVec3);
				//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat44::setPosition(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0]))
		{
				PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
				PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
				//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
				//{
				thisPxMat44->setPosition(*inPxVec3);
			
				return scope.Close(args.Holder());
				//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat44::scale(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec4::getTemplate()->HasInstance(args[0]))
		{
				PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
				PxVec4* inPxVec4 = unwrap<PxVec4>(args[0]->ToObject());
				//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
				//{
				thisPxMat44->scale(*inPxVec4);
			
				return scope.Close(args.Holder());
				//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat44::inverseRT(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0)
		{
				PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
				//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
				//{
				PxMat44* obj = new PxMat44(thisPxMat44->inverseRT());
				Persistent<Object> newPxMat44 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxMat44::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxMat44.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxMat44->SetInternalField(0, External::New( obj ));
			
				return scope.Close(newPxMat44);
				//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat44::isFinite(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0)
		{
				PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
				//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
				//{			
				return scope.Close( Boolean::New(thisPxMat44->isFinite()) );
				//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat44::assignmentAdd(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && args[0]->IsObject() && V8PxMat44::getTemplate()->HasInstance(args[0])) 
        {
			PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
			PxMat44* inPxMat44 = unwrap<PxMat44>(args[0]->ToObject());
			//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
			//{
				*thisPxMat44 += *inPxMat44;
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat44::assignmentSubtract(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && args[0]->IsObject() && V8PxMat44::getTemplate()->HasInstance(args[0])) 
        {
			PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
			PxMat44* inPxMat44 = unwrap<PxMat44>(args[0]->ToObject());
			//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
			//{
				*thisPxMat44 -= *inPxMat44;
				return scope.Close( args.Holder() );
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat44::assignmentMultiply(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber())
        {
			PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
			//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
			//{

			*thisPxMat44 *= args[0]->NumberValue();
			
			return scope.Close(args.Holder());
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat44::add(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && args[0]->IsObject() && V8PxMat44::getTemplate()->HasInstance(args[0])) 
        {
			PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
			PxMat44* inPxMat44 = unwrap<PxMat44>(args[0]->ToObject());
			//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
			//{
			PxMat44* obj = new PxMat44(*thisPxMat44 + *inPxMat44);
			Persistent<Object> newPxMat44 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxMat44.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxMat44->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxMat44);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat44::subtract(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && args[0]->IsObject() && V8PxMat44::getTemplate()->HasInstance(args[0])) 
        {
			PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
			PxMat44* inPxMat44 = unwrap<PxMat44>(args[0]->ToObject());
			//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
			//{
			PxMat44* obj = new PxMat44(*thisPxMat44 - *inPxMat44);
			Persistent<Object> newPxMat44 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxMat44.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxMat44->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxMat44);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat44::multiply(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty())
        {
			if(args[0]->IsNumber()){
				PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
				//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
				//{
				PxMat44* obj = new PxMat44(*thisPxMat44 * args[0]->NumberValue());
				Persistent<Object> newPxMat44 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//				newPxMat44.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxMat44->SetInternalField(0, External::New( obj ));
			
				return scope.Close(newPxMat44);
				//}
			}
			else if(args[0]->IsObject() && V8PxMat44::getTemplate()->HasInstance(args[0])){
				PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
				PxMat44* inPxMat44 = unwrap<PxMat44>(args[0]->ToObject());
				//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
				//{
				PxMat44* obj = new PxMat44(*thisPxMat44 * *inPxMat44);
				Persistent<Object> newPxMat44 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//				newPxMat44.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxMat44->SetInternalField(0, External::New( obj ));
			
				return scope.Close(newPxMat44);
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMat44::negate(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxMat44* thisPxMat44 = unwrap<PxMat44>(args.Holder());
			//if(thisPxMat44 != NULL && inPxMat44 != NULL) 
			//{
			PxMat44* obj = new PxMat44(-*thisPxMat44);
			Persistent<Object> newPxMat44 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxMat44.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxMat44->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxMat44);
			//}
		}

		return scope.Close( Undefined() );
	}

//PxTransform

	Handle<Value>  V8PxTransform::PxTransformConstructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){
			PxTransform* transfObject = new PxTransform();

			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),transfObject, &CleanupDelete);
			self->SetInternalField(0, External::New( transfObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty()){
			PxTransform* transfObject;
			if(args[0]->IsObject() && V8PxTransform::getTemplate()->HasInstance(args[0])){ //Transform
				transfObject = new PxTransform(*unwrap<PxTransform>(args[0]->ToObject()));
			}
			else if(args[0]->IsObject() && V8PxQuat::getTemplate()->HasInstance(args[0])){ //Quat
				transfObject = new PxTransform(*unwrap<PxQuat>(args[0]->ToObject()));
			}
			else if(args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])){ //Vec3
				transfObject = new PxTransform(*unwrap<PxVec3>(args[0]->ToObject()));
			}
			else {
				return ThrowException( Exception::TypeError( String::New("PxTransform constructor takes nothing, (PxQuat), (PxVec3), (PxVec3, PxQuat), or (PxTransform) as an argument.") ) );
			}
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),transfObject, &CleanupDelete);
			self->SetInternalField(0, External::New( transfObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0]) &&
				!args[1].IsEmpty() && args[1]->IsObject() && V8PxQuat::getTemplate()->HasInstance(args[1])){ //Vec3 Position and Quat orientation

			PxTransform* transfObject = new PxTransform(*unwrap<PxVec3>(args[0]->ToObject()),*unwrap<PxQuat>(args[1]->ToObject()));
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),transfObject, &CleanupDelete);
			self->SetInternalField(0, External::New( transfObject ));

			return scope.Close( self );
		}
        
		return ThrowException( Exception::TypeError( String::New("PxTransform constructor takes nothing, (PxQuat), (PxVec3), (PxVec3, PxQuat), or (PxTransform) as an argument.") ) );
	}

	Handle<Value> V8PxTransform::getQ( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxTransform* thisPxTransform = unwrap<PxTransform>(info.Holder());
		//if(thisPxVec2 != NULL) 
		//{
			Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8PxQuat::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxQuat.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxQuat->SetInternalField(0, External::New(&thisPxTransform->q));

			return scope.Close(newPxQuat);
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxTransform::setQ( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8PxQuat::getTemplate()->HasInstance(value)){
			PxTransform* thisTransform = unwrap<PxTransform>(info.Holder());
			PxQuat* inQuat = unwrap<PxQuat>(value->ToObject());
			//if(thisPxVec2 != NULL && value->IsNumber()) 
			//{
				thisTransform->q = *inQuat;
			//}
		}
	}

	Handle<Value> V8PxTransform::getP( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxTransform* thisPxTransform = unwrap<PxTransform>(info.Holder());
		//if(thisPxVec2 != NULL) 
		//{
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxVec3->SetInternalField(0, External::New(&thisPxTransform->p));

			return scope.Close(newPxVec3);
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxTransform::setP( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8PxVec3::getTemplate()->HasInstance(value)){
			PxTransform* thisTransform = unwrap<PxTransform>(info.Holder());
			PxVec3* inVec3 = unwrap<PxVec3>(value->ToObject());
			//if(thisPxVec2 != NULL && value->IsNumber()) 
			//{
				thisTransform->p = *inVec3;
			//}
		}
	}

	Handle<Value> V8PxTransform::createIdentity(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			//if(thisPxTransform != NULL && inPxTransform != NULL) 
			//{
			PxTransform* obj = new PxTransform(PxTransform::createIdentity());
			Persistent<Object> newPxTransform = Persistent<Object>::New(Isolate::GetCurrent(),V8PxTransform::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxTransform.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxTransform->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxTransform);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxTransform::getInverse(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxTransform* thisPxTransform = unwrap<PxTransform>(args.Holder());
			//if(thisPxTransform != NULL && inPxTransform != NULL) 
			//{
			PxTransform* obj = new PxTransform(thisPxTransform->getInverse());
			Persistent<Object> newPxTransform = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxTransform.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxTransform->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxTransform);
			//}
		}

		return scope.Close( Undefined() );
	}
	
	Handle<Value> V8PxTransform::transform(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxTransform* thisPxTransform = unwrap<PxTransform>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxTransform != NULL && inPxTransform != NULL) 
			//{
			PxVec3* obj = new PxVec3(thisPxTransform->transform(*inPxVec3));
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxTransform::transformInv(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxTransform* thisPxTransform = unwrap<PxTransform>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxTransform != NULL && inPxTransform != NULL) 
			//{
			PxVec3* obj = new PxVec3(thisPxTransform->transformInv(*inPxVec3));
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxTransform::rotate(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxTransform* thisPxTransform = unwrap<PxTransform>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxTransform != NULL && inPxTransform != NULL) 
			//{
			PxVec3* obj = new PxVec3(thisPxTransform->rotate(*inPxVec3));
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxTransform::rotateInv(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxTransform* thisPxTransform = unwrap<PxTransform>(args.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());
			//if(thisPxTransform != NULL && inPxTransform != NULL) 
			//{
			PxVec3* obj = new PxVec3(thisPxTransform->rotateInv(*inPxVec3));
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxTransform::isValid(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxTransform* thisPxTransform = unwrap<PxTransform>(args.Holder());
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( Boolean::New(thisPxTransform->isValid()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxTransform::isSane(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxTransform* thisPxTransform = unwrap<PxTransform>(args.Holder());
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( Boolean::New(thisPxTransform->isSane()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxTransform::isFinite(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxTransform* thisPxTransform = unwrap<PxTransform>(args.Holder());
			//if(thisPxQuat != NULL && inPxQuat != NULL) 
			//{
			return scope.Close( Boolean::New(thisPxTransform->isFinite()));
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxTransform::multiply(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxTransform::getTemplate()->HasInstance(args[0])) 
        {
			PxTransform* thisPxTransform = unwrap<PxTransform>(args.Holder());
			PxTransform* inPxTransform = unwrap<PxTransform>(args[0]->ToObject());
			//if(thisPxVec2 != NULL && inPxVec2 != NULL) 
			//{
			PxTransform* obj = new PxTransform(*thisPxTransform * *inPxTransform);
			Persistent<Object> newPxTransform = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//			newPxTransform.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxTransform->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxTransform);
			//}
		}

		return scope.Close( Undefined() );
	}

//PxBounds3

	Handle<Value>  V8PxBounds3::PxBounds3Constructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){
			PxBounds3* obj = new PxBounds3();

			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxBounds3::getTemplate()->HasInstance(args[0])){
			PxBounds3* obj = new PxBounds3(*unwrap<PxBounds3>(args[0]->ToObject()));
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0]) &&
				!args[1].IsEmpty() && args[1]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[1])){
			
			PxBounds3* obj = new PxBounds3(*unwrap<PxVec3>(args[0]->ToObject()),*unwrap<PxVec3>(args[1]->ToObject()));
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
        
		return ThrowException( Exception::TypeError( String::New("PxBounds3 constructor takes nothing, (PxVec3, PxVec3), or (PxBounds3) as an argument.") ) );
	}

	Handle<Value> V8PxBounds3::getMin( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(info.Holder());
		//if(thisPxVec2 != NULL) 
		//{
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxVec3->SetInternalField(0, External::New(&thisPxBounds3->minimum));

			return scope.Close(newPxVec3);
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxBounds3::setMin( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8PxVec3::getTemplate()->HasInstance(value)){
			PxBounds3* thisBounds3 = unwrap<PxBounds3>(info.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(value->ToObject());
			//if(thisPxVec2 != NULL && value->IsNumber()) 
			//{
			thisBounds3->minimum = *inPxVec3;
			//}
		}
	}

	Handle<Value> V8PxBounds3::getMax( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(info.Holder());
		//if(thisPxVec2 != NULL) 
		//{
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxVec3->SetInternalField(0, External::New(&thisPxBounds3->maximum));

			return scope.Close(newPxVec3);
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxBounds3::setMax( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8PxVec3::getTemplate()->HasInstance(value)){
			PxBounds3* thisBounds3 = unwrap<PxBounds3>(info.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(value->ToObject());
			//if(thisPxVec2 != NULL && value->IsNumber()) 
			//{
			thisBounds3->maximum = *inPxVec3;
			//}
		}
	}

	Handle<Value> V8PxBounds3::empty(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			//if(thisPxBounds3 != NULL && inPxBounds3 != NULL) 
			//{
			PxBounds3* obj = new PxBounds3(PxBounds3::empty());
			Persistent<Object> newPxBounds3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxBounds3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxBounds3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxBounds3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxBounds3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxBounds3::boundsOfPoints(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0]) &&
				!args[1].IsEmpty() && args[1]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[1])) 
        {
			//if(thisPxBounds3 != NULL && inPxBounds3 != NULL) 
			//{
			PxBounds3* obj = new PxBounds3(PxBounds3::boundsOfPoints(*unwrap<PxVec3>(args[0]->ToObject()),*unwrap<PxVec3>(args[1]->ToObject())));
			Persistent<Object> newPxBounds3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxBounds3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxBounds3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxBounds3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxBounds3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxBounds3::centerExtents(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0]) &&
				!args[1].IsEmpty() && args[1]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[1])) 
        {
			//if(thisPxBounds3 != NULL && inPxBounds3 != NULL) 
			//{
			PxBounds3* obj = new PxBounds3(PxBounds3::centerExtents(*unwrap<PxVec3>(args[0]->ToObject()),*unwrap<PxVec3>(args[1]->ToObject())));
			Persistent<Object> newPxBounds3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxBounds3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxBounds3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxBounds3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxBounds3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxBounds3::basisExtent(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0]) &&
				!args[1].IsEmpty() && args[1]->IsObject() && V8PxMat33::getTemplate()->HasInstance(args[1]) &&
				!args[2].IsEmpty() && args[2]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[2])) 
        {
			//if(thisPxBounds3 != NULL && inPxBounds3 != NULL) 
			//{
			PxBounds3* obj = new PxBounds3(PxBounds3::basisExtent(*unwrap<PxVec3>(args[0]->ToObject()),*unwrap<PxMat33>(args[0]->ToObject()),*unwrap<PxVec3>(args[2]->ToObject())));
			Persistent<Object> newPxBounds3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxBounds3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxBounds3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxBounds3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxBounds3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxBounds3::poseExtent(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxTransform::getTemplate()->HasInstance(args[0]) &&
				!args[1].IsEmpty() && args[1]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[1])) 
        {
			//if(thisPxBounds3 != NULL && inPxBounds3 != NULL) 
			//{
			PxBounds3* obj = new PxBounds3(PxBounds3::poseExtent(*unwrap<PxTransform>(args[0]->ToObject()),*unwrap<PxVec3>(args[0]->ToObject())));
			Persistent<Object> newPxBounds3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxBounds3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxBounds3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxBounds3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxBounds3);
			//}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxBounds3::transform(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() &&
				!args[1].IsEmpty() && args[1]->IsObject() && V8PxBounds3::getTemplate()->HasInstance(args[1])) 
        {
			
			if(V8PxMat33::getTemplate()->HasInstance(args[0])){
				PxBounds3* obj = new PxBounds3(PxBounds3::transform(*unwrap<PxMat33>(args[0]->ToObject()),*unwrap<PxBounds3>(args[0]->ToObject())));
				Persistent<Object> newPxBounds3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxBounds3::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxBounds3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxBounds3->SetInternalField(0, External::New( obj ));
			
				return scope.Close(newPxBounds3);
			}
			else if(V8PxTransform::getTemplate()->HasInstance(args[0])){
				PxBounds3* obj = new PxBounds3(PxBounds3::transform(*unwrap<PxTransform>(args[0]->ToObject()),*unwrap<PxBounds3>(args[0]->ToObject())));
				Persistent<Object> newPxBounds3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxBounds3::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxBounds3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxBounds3->SetInternalField(0, External::New( obj ));
			
				return scope.Close(newPxBounds3);
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxBounds3::setEmpty(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(args.Holder());

			thisPxBounds3->setEmpty();
			
			return scope.Close(args.Holder());
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxBounds3::setInfinite(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(args.Holder());

			thisPxBounds3->setInfinite();
			
			return scope.Close(args.Holder());
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxBounds3::include(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject()){
			
			if(V8PxVec3::getTemplate()->HasInstance(args[0])) {
				PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(args.Holder());

				thisPxBounds3->include(*unwrap<PxVec3>(args[0]->ToObject()));
			
				return scope.Close(args.Holder());
			}
			else if(V8PxBounds3::getTemplate()->HasInstance(args[0])){
				PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(args.Holder());

				thisPxBounds3->include(*unwrap<PxBounds3>(args[0]->ToObject()));
			
				return scope.Close(args.Holder());
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxBounds3::isEmpty(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(args.Holder());
			
			return scope.Close(Boolean::New(thisPxBounds3->isEmpty()));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxBounds3::intersects(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxBounds3::getTemplate()->HasInstance(args[0])) 
        {
			PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(args.Holder());
			
			return scope.Close(Boolean::New(thisPxBounds3->intersects(*unwrap<PxBounds3>(args[0]->ToObject()))));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxBounds3::intersects1D(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxBounds3::getTemplate()->HasInstance(args[0]) &&
			!args[1].IsEmpty() && args[1]->IsUint32()) 
        {
			PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(args.Holder());
			
			return scope.Close(Boolean::New(thisPxBounds3->intersects1D(*unwrap<PxBounds3>(args[0]->ToObject()), args[1]->Uint32Value())));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxBounds3::contains(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(args.Holder());
			
			return scope.Close(Boolean::New(thisPxBounds3->contains(*unwrap<PxVec3>(args[0]->ToObject()))));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxBounds3::isInside(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxBounds3::getTemplate()->HasInstance(args[0])) 
        {
			PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(args.Holder());
			
			return scope.Close(Boolean::New(thisPxBounds3->isInside(*unwrap<PxBounds3>(args[0]->ToObject()))));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxBounds3::getCenter(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(args.Holder());

			PxVec3* obj = new PxVec3(thisPxBounds3->getCenter());
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxBounds3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32()){
			PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(args.Holder());

			return scope.Close(Number::New(thisPxBounds3->getCenter(args[0]->Uint32Value())));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxBounds3::getExtents(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(args.Holder());

			PxVec3* obj = new PxVec3(thisPxBounds3->getExtents());
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxBounds3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32()){
			PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(args.Holder());

			return scope.Close(Number::New(thisPxBounds3->getExtents(args[0]->Uint32Value())));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxBounds3::getDimensions(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(args.Holder());

			PxVec3* obj = new PxVec3(thisPxBounds3->getDimensions());
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxBounds3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxVec3);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxBounds3::scale(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(args.Holder());

			thisPxBounds3->scale(args[0]->NumberValue());
			
			return scope.Close(args.Holder());
		}

		return scope.Close( Undefined() );
	}

	
	Handle<Value> V8PxBounds3::fatten(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(args.Holder());

			thisPxBounds3->fatten(args[0]->NumberValue());
			
			return scope.Close(args.Holder());
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxBounds3::isFinite(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxBounds3* thisPxBounds3 = unwrap<PxBounds3>(args.Holder());
			
			return scope.Close(Boolean::New(thisPxBounds3->isFinite()));
		}

		return scope.Close( Undefined() );
	}

//PxShape

	//Handle<Value> V8PxShape::getUserData( Local<String> property , const AccessorInfo& info ){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	PxShape* thisPxShape = unwrap<PxShape>(info.Holder());
	//	//if(thisPxVec2 != NULL) 
	//	//{
	//		//Persistent<Object> newPxQuat = Persistent<Object>::New(Isolate::GetCurrent(),V8PxQuat::getTemplate()->InstanceTemplate()->NewInstance());			
//	//		//newPxQuat.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
	//		//newPxQuat->SetInternalField(0, External::New(&thisPxShape->q));
	//	Persistent<External> newExternal = Persistent<External>::New(Isolate::GetCurrent(),External::New(thisPxShape->userData));
//	//	newExternal.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);

	//	return scope.Close(newExternal);
	//	//}

	//	//return scope.Close( Undefined() );
	//}

	//void V8PxShape::setUserData( Local<String> property, Local<Value> value, const AccessorInfo& info ){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(!value.IsEmpty()){
	//		if(value->IsObject()){
	//			PxShape* thisPxShape = unwrap<PxShape>(info.Holder());

	//			thisPxShape->userData = &value;
	//		}
	//		else if(value->IsExternal()){
	//			PxShape* thisPxShape = unwrap<PxShape>(info.Holder());

	//			thisPxShape->userData = Local<External>::Cast(value)->Value();
	//		}
	//	}
	//}

	Handle<Value> V8PxShape::getUserData( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());


		if(info.Data().IsEmpty()){
			PxShape* thisPxShape = unwrap<PxShape>(info.Holder());

			if(thisPxShape->userData){
				return( Local<Value>::New(External::New(thisPxShape->userData)) );
			}
			else {
				return( Undefined() );
			}
		}
		else {
			return scope.Close(info.Data());
		}

	}

	void V8PxShape::setUserData( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty()){
			PxShape* thisPxShape = unwrap<PxShape>(info.Holder());
			thisPxShape->userData = Local<External>::Cast(value)->Value();

			info.Holder()->SetAccessor(String::New("userData"), getUserData, setUserData, value);
		}
	}

	Handle<Value> V8PxShape::release(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());
			thisPxShape->release();
			
			return scope.Close(Handle<Object>());
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getGeometryType(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());

			
			return scope.Close(Number::New(thisPxShape->getGeometryType()));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::setGeometry(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxGeometry::getTemplate()->HasInstance(args[0])) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());
			PxGeometry* inPxGeometry = unwrap<PxGeometry>(args[0]->ToObject());

			thisPxShape->setGeometry(*inPxGeometry);
			
			return scope.Close(args.Holder());
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getBoxGeometry(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxBoxGeometry::getTemplate()->HasInstance(args[0])) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());
			PxBoxGeometry* inPxBoxGeometry = unwrap<PxBoxGeometry>(args[0]->ToObject());
			
			return scope.Close(Boolean::New(thisPxShape->getBoxGeometry(*inPxBoxGeometry)));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getSphereGeometry(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxSphereGeometry::getTemplate()->HasInstance(args[0])) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());
			PxSphereGeometry* inPxSphereGeometry = unwrap<PxSphereGeometry>(args[0]->ToObject());
			
			return scope.Close(Boolean::New(thisPxShape->getSphereGeometry(*inPxSphereGeometry)));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getCapsuleGeometry(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxSphereGeometry::getTemplate()->HasInstance(args[0])) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());
			PxCapsuleGeometry* inPxCapsuleGeometry = unwrap<PxCapsuleGeometry>(args[0]->ToObject());
			
			return scope.Close(Boolean::New(thisPxShape->getCapsuleGeometry(*inPxCapsuleGeometry)));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getPlaneGeometry(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxSphereGeometry::getTemplate()->HasInstance(args[0])) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());
			PxPlaneGeometry* inPxPlaneGeometry = unwrap<PxPlaneGeometry>(args[0]->ToObject());
			
			return scope.Close(Boolean::New(thisPxShape->getPlaneGeometry(*inPxPlaneGeometry)));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getConvexMeshGeometry(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxSphereGeometry::getTemplate()->HasInstance(args[0])) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());
			PxConvexMeshGeometry* inPxConvexMeshGeometry = unwrap<PxConvexMeshGeometry>(args[0]->ToObject());
			
			return scope.Close(Boolean::New(thisPxShape->getConvexMeshGeometry(*inPxConvexMeshGeometry)));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getTriangleMeshGeometry(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxSphereGeometry::getTemplate()->HasInstance(args[0])) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());
			PxTriangleMeshGeometry* inPxTriangleMeshGeometry = unwrap<PxTriangleMeshGeometry>(args[0]->ToObject());
			
			return scope.Close(Boolean::New(thisPxShape->getTriangleMeshGeometry(*inPxTriangleMeshGeometry)));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getHeightFieldGeometry(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxSphereGeometry::getTemplate()->HasInstance(args[0])) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());
			PxHeightFieldGeometry* inPxHeightFieldGeometry = unwrap<PxHeightFieldGeometry>(args[0]->ToObject());
			
			return scope.Close(Boolean::New(thisPxShape->getHeightFieldGeometry(*inPxHeightFieldGeometry)));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getActor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());

			Persistent<Object> newPxRigidActor = Persistent<Object>::New(Isolate::GetCurrent(),V8PxRigidActor::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxRigidActor.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxRigidActor->SetInternalField(0, External::New(&thisPxShape->getActor()));
			
			return scope.Close(newPxRigidActor);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getWorldBounds(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());

			PxBounds3* obj = new PxBounds3(thisPxShape->getWorldBounds());
			Persistent<Object> newPxBounds3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxBounds3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxBounds3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxBounds3->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxBounds3);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::setLocalPose(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxTransform::getTemplate()->HasInstance(args[0])) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());
			PxTransform* inPxTransform = unwrap<PxTransform>(args[0]->ToObject());

			thisPxShape->setLocalPose(*inPxTransform);
			
			return scope.Close(args.Holder());
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getLocalPose(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());

			PxTransform* obj = new PxTransform(thisPxShape->getLocalPose());
			Persistent<Object> newPxTransform = Persistent<Object>::New(Isolate::GetCurrent(),V8PxTransform::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxTransform.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxTransform->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxTransform);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::setSimulationFilterData(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxFilterData::getTemplate()->HasInstance(args[0])) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());
			PxFilterData* inPxFilterData = unwrap<PxFilterData>(args[0]->ToObject());

			thisPxShape->setSimulationFilterData(*inPxFilterData);
			
			return scope.Close(args.Holder());
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getSimulationFilterData(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());

			PxFilterData* obj = new PxFilterData(thisPxShape->getSimulationFilterData());
			Persistent<Object> newPxFilterData = Persistent<Object>::New(Isolate::GetCurrent(),V8PxFilterData::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxFilterData.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxFilterData->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxFilterData);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::resetFiltering(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());

			thisPxShape->resetFiltering();
			
			return scope.Close(args.Holder());
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::setQueryFilterData(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxFilterData::getTemplate()->HasInstance(args[0])) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());
			PxFilterData* inPxFilterData = unwrap<PxFilterData>(args[0]->ToObject());

			thisPxShape->setQueryFilterData(*inPxFilterData);
			
			return scope.Close(args.Holder());
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getQueryFilterData(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());

			PxFilterData* obj = new PxFilterData(thisPxShape->getQueryFilterData());
			Persistent<Object> newPxFilterData = Persistent<Object>::New(Isolate::GetCurrent(),V8PxFilterData::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxFilterData.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			newPxFilterData->SetInternalField(0, External::New( obj ));
			
			return scope.Close(newPxFilterData);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::setMaterials(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsArray() && V8PxFilterData::getTemplate()->HasInstance(args[0])) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());
			Local<Array> inArray = Local<Array>::Cast(args[0]);

			PxMaterial* newMats = (PxMaterial*)malloc(sizeof(PxMaterial)*inArray->Length());

			for(int i = 0; i < inArray->Length(); i++){
				newMats[i] = *unwrap<PxMaterial>(inArray->GetInternalField(i)->ToObject());
			}

			PxMaterial*const* newMats2 = &newMats; 

			thisPxShape->setMaterials(newMats2, inArray->Length());

			free(newMats);
			
			return scope.Close(args.Holder());
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getNbMaterials(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());
			
			return scope.Close(Number::New(thisPxShape->getNbMaterials()));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getMaterials(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());

			PxMaterial** newMats = (PxMaterial**)malloc(sizeof(PxMaterial*)*thisPxShape->getNbMaterials());

			int numMats = thisPxShape->getMaterials(newMats, thisPxShape->getNbMaterials());

			Persistent<Array> newArray = Persistent<Array>::New(Isolate::GetCurrent(),Array::New(numMats));
//			newArray.MakeWeak(Isolate::GetCurrent(),newMats, &CleanupFree);
			
			for(int i = 0; i < numMats; i++){
				Persistent<Object> newPxMaterial = Persistent<Object>::New(Isolate::GetCurrent(),V8PxMaterial::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxMaterial.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
				newPxMaterial->SetInternalField(0, External::New( newMats[i] ));

				newArray->SetInternalField(i, newPxMaterial); 
			}

			
			return scope.Close(newArray);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getMaterialFromInternalFaceIndex(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsInt32()) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());

			Persistent<Object> newPxMaterial = Persistent<Object>::New(Isolate::GetCurrent(),V8PxMaterial::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxMaterial.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxMaterial->SetInternalField(0, External::New(thisPxShape->getMaterialFromInternalFaceIndex(args[0]->Int32Value()) ) );

			return scope.Close(newPxMaterial);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::setContactOffset(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());

			thisPxShape->setContactOffset(args[0]->NumberValue());
			
			return scope.Close(args.Holder());
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getContactOffset(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());
			
			return scope.Close(Number::New(thisPxShape->getContactOffset()));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::setRestOffset(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());

			thisPxShape->setRestOffset(args[0]->NumberValue());
			
			return scope.Close(args.Holder());
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getRestOffset(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());
			
			return scope.Close(Number::New(thisPxShape->getRestOffset()));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::setFlag(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsInt32() && !args[1].IsEmpty() && args[1]->IsBoolean()) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());

			thisPxShape->setFlag(PxShapeFlag::Enum(args[0]->Int32Value()), args[0]->BooleanValue());
			
			return scope.Close(args.Holder());
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::setFlags(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsInt32()) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());

			thisPxShape->setFlags(PxShapeFlags(args[0]->Int32Value()));
			
			return scope.Close(args.Holder());
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getFlags(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());
			
			return scope.Close(Integer::New(PxU32(thisPxShape->getFlags())));
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::setName(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsString()) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());

			thisPxShape->setName(*String::Utf8Value(args[0]->ToString()));
			
			return scope.Close(args.Holder());
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxShape::getName(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxShape* thisPxShape = unwrap<PxShape>(args.Holder());
			
			return scope.Close(String::New(thisPxShape->getName()));
		}

		return scope.Close( Undefined() );
	}

//PxControllerShapeHit

	Handle<Value> V8PxControllerShapeHit::getController(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxControllerShapeHit* thisPxControllerShapeHit = unwrap<PxControllerShapeHit>(args.Holder());

			Persistent<Object> newPxController = Persistent<Object>::New(Isolate::GetCurrent(),V8PxController::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxController.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxController->SetInternalField(0, External::New(&*thisPxControllerShapeHit->controller));
			
			return scope.Close(newPxController);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxControllerShapeHit::getShape(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxControllerShapeHit* thisPxControllerShapeHit = unwrap<PxControllerShapeHit>(args.Holder());

			Persistent<Object> newPxShape = Persistent<Object>::New(Isolate::GetCurrent(),V8PxShape::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxShape.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxShape->SetInternalField(0, External::New(&*thisPxControllerShapeHit->shape));
			
			return scope.Close(newPxShape);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxControllerShapeHit::getWorldPose(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxControllerShapeHit* thisPxControllerShapeHit = unwrap<PxControllerShapeHit>(args.Holder());

			Persistent<Object> newPxExtendedVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxExtendedVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxExtendedVec3.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxExtendedVec3->SetInternalField(0, External::New(&thisPxControllerShapeHit->worldPos));
			
			return scope.Close(newPxExtendedVec3);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxControllerShapeHit::getWorldNormal(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxControllerShapeHit* thisPxControllerShapeHit = unwrap<PxControllerShapeHit>(args.Holder());

			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxVec3->SetInternalField(0, External::New(&thisPxControllerShapeHit->worldNormal));
			
			return scope.Close(newPxVec3);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxControllerShapeHit::getDirection(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxControllerShapeHit* thisPxControllerShapeHit = unwrap<PxControllerShapeHit>(args.Holder());

			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxVec3->SetInternalField(0, External::New(&thisPxControllerShapeHit->dir));
			
			return scope.Close(newPxVec3);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxControllerShapeHit::getLength(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxControllerShapeHit* thisPxControllerShapeHit = unwrap<PxControllerShapeHit>(args.Holder());

			return scope.Close(Number::New(thisPxControllerShapeHit->length));
		}

		return scope.Close( Undefined() );
	}

//PxControllersHit

	Handle<Value> V8PxControllersHit::getController(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxControllersHit* thisPxControllersHit = unwrap<PxControllersHit>(args.Holder());

			Persistent<Object> newPxController = Persistent<Object>::New(Isolate::GetCurrent(),V8PxController::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxController.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxController->SetInternalField(0, External::New(&*thisPxControllersHit->controller));
			
			return scope.Close(newPxController);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxControllersHit::getOther(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxControllersHit* thisPxControllersHit = unwrap<PxControllersHit>(args.Holder());

			Persistent<Object> newPxController = Persistent<Object>::New(Isolate::GetCurrent(),V8PxController::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxController.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxController->SetInternalField(0, External::New(&*thisPxControllersHit->other));
			
			return scope.Close(newPxController);
		}

		return scope.Close( Undefined() );
	}

//PxPadding

	template<int SIZE>
	Handle<Value> V8PxPadding<SIZE>::PxPaddingConstructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){

			PxPadding<SIZE>* obj = new PxPadding<SIZE>();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxPadding<SIZE>::getTemplate()->HasInstance(args[0])){

			PxPadding<SIZE>* obj = new PxPadding<SIZE>(*unwrap<PxPadding<SIZE>>(args[0]->ToObject()));
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));
			return scope.Close( self );
		}
        
		return ThrowException( Exception::TypeError( String::New("PxPadding constructor takes nothing or (PxPadding) as an argument.") ) );
	}

	template<int SIZE>
	Handle<Value> V8PxPadding<SIZE>::getSize( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		return scope.Close(Uint32::New(SIZE));
	}

	template<int SIZE>
	Handle<Value> V8PxPadding<SIZE>::elementGet(uint32_t index, const AccessorInfo& info){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(index >=0 && index < SIZE){
			PxPadding<SIZE>* thisPxPadding = unwrap<PxPadding<SIZE>>(info.Holder());

			return scope.Close(Uint32::New( thisPxPadding->mPadding[index] ));
		}

		return scope.Close( Undefined() );
	}

	template<int SIZE>
	Handle<Value> V8PxPadding<SIZE>::elementSet(uint32_t index, Local<Value> value, const AccessorInfo& info){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsUint32() && index >=0 && index < SIZE){
			PxPadding<SIZE>* thisPxPadding = unwrap<PxPadding<SIZE>>(info.Holder());

			thisPxPadding->mPadding[index] = PxU8(value->Uint32Value());
			return scope.Close(value);
		}

		return scope.Close( Undefined() );
	}

//PxGeometry

	Handle<Value> V8PxGeometry::getType(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxGeometry* thisPxGeometry = unwrap<PxGeometry>(args.Holder());
			
			return scope.Close(Integer::New(thisPxGeometry->getType()));
		}

		return scope.Close( Undefined() );
	}

//PxBoxGeometry

	Handle<Value>  V8PxBoxGeometry::PxBoxGeometryConstructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){
			PxBoxGeometry* obj = new PxBoxGeometry();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject()){

			if(V8PxBoxGeometry::getTemplate()->HasInstance(args[0])){
				PxBoxGeometry* obj = new PxBoxGeometry(*unwrap<PxBoxGeometry>(args[0]->ToObject()));
				Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//				self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				self->SetInternalField(0, External::New( obj ));

				return scope.Close( self );
			}
			else if(V8PxVec3::getTemplate()->HasInstance(args[0])){
				PxBoxGeometry* obj = new PxBoxGeometry(*unwrap<PxVec3>(args[0]->ToObject()));
				Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//				self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				self->SetInternalField(0, External::New( obj ));

				return scope.Close( self );
			}
		}
		else if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsNumber() &&
				!args[1].IsEmpty() && args[1]->IsNumber() &&
				!args[2].IsEmpty() && args[2]->IsNumber()){

			PxBoxGeometry* obj = new PxBoxGeometry(args[0]->NumberValue(), args[1]->NumberValue(),args[2]->NumberValue());
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
        
		return ThrowException( Exception::TypeError( String::New("PxBoxGeometry constructor takes nothing, (PxVec3), (Number, Number, Number), or (PxBoxGeometry) as an argument.") ) );
	}

	Handle<Value> V8PxBoxGeometry::getHalfExtents( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxBoxGeometry* thisPxBoxGeometry = unwrap<PxBoxGeometry>(info.Holder());
		//if(thisPxVec2 != NULL) 
		//{
			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxVec3->SetInternalField(0, External::New(&thisPxBoxGeometry->halfExtents));

			return scope.Close(newPxVec3);
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxBoxGeometry::setHalfExtents( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8PxVec3::getTemplate()->HasInstance(value)){
			PxBoxGeometry* thisPxBoxGeometry = unwrap<PxBoxGeometry>(info.Holder());
			PxVec3* inPxVec3 = unwrap<PxVec3>(value->ToObject());
			//if(thisPxVec2 != NULL && value->IsNumber()) 
			//{
			thisPxBoxGeometry->halfExtents = *inPxVec3;
			//}
		}
	}

	Handle<Value> V8PxBoxGeometry::isValid(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxBoxGeometry* thisPxBoxGeometry = unwrap<PxBoxGeometry>(args.Holder());
			
			return scope.Close(Boolean::New(thisPxBoxGeometry->isValid()));
		}

		return scope.Close( Undefined() );
	}

//PxCapsuleGeometry

	Handle<Value>  V8PxCapsuleGeometry::PxCapsuleGeometryConstructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){
			PxCapsuleGeometry* obj = new PxCapsuleGeometry();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxCapsuleGeometry::getTemplate()->HasInstance(args[0])){
			PxCapsuleGeometry* obj = new PxCapsuleGeometry(*unwrap<PxCapsuleGeometry>(args[0]->ToObject()));
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsNumber() &&
				!args[1].IsEmpty() && args[1]->IsNumber()){

			PxCapsuleGeometry* obj = new PxCapsuleGeometry(args[0]->NumberValue(), args[1]->NumberValue());
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
        
		return ThrowException( Exception::TypeError( String::New("PxCapsuleGeometry constructor takes nothing, (Number, Number), or (PxCapsuleGeometry) as an argument.") ) );
	}

	Handle<Value> V8PxCapsuleGeometry::getRadius( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxCapsuleGeometry* thisPxCapsuleGeometry = unwrap<PxCapsuleGeometry>(info.Holder());
		//if(thisPxVec2 != NULL) 
		//{
		return scope.Close(Number::New(thisPxCapsuleGeometry->radius));
		//}
	}

	void V8PxCapsuleGeometry::setRadius( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PxCapsuleGeometry* thisPxCapsuleGeometry = unwrap<PxCapsuleGeometry>(info.Holder());

			thisPxCapsuleGeometry->radius = value->NumberValue();
		}
	}

	Handle<Value> V8PxCapsuleGeometry::getHalfHeight( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxCapsuleGeometry* thisPxCapsuleGeometry = unwrap<PxCapsuleGeometry>(info.Holder());
		//if(thisPxVec2 != NULL) 
		//{
		return scope.Close(Number::New(thisPxCapsuleGeometry->halfHeight));
		//}
	}

	void V8PxCapsuleGeometry::setHalfHeight( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PxCapsuleGeometry* thisPxCapsuleGeometry = unwrap<PxCapsuleGeometry>(info.Holder());

			thisPxCapsuleGeometry->halfHeight = value->NumberValue();
		}
	}

	Handle<Value> V8PxCapsuleGeometry::isValid(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxCapsuleGeometry* thisPxCapsuleGeometry = unwrap<PxCapsuleGeometry>(args.Holder());
			
			return scope.Close(Boolean::New(thisPxCapsuleGeometry->isValid()));
		}

		return scope.Close( Undefined() );
	}

//PxConvexMeshGeometry

	Handle<Value>  V8PxConvexMeshGeometry::PxConvexMeshGeometryConstructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){
			PxConvexMeshGeometry* obj = new PxConvexMeshGeometry();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject()){

			if(V8PxConvexMeshGeometry::getTemplate()->HasInstance(args[0])){
				PxConvexMeshGeometry* obj = new PxConvexMeshGeometry(*unwrap<PxConvexMeshGeometry>(args[0]->ToObject()));
				Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//				self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				self->SetInternalField(0, External::New( obj ));

				return scope.Close( self );
			}
			else if(V8PxConvexMesh::getTemplate()->HasInstance(args[0])){
				PxConvexMeshGeometry* obj = new PxConvexMeshGeometry(&*unwrap<PxConvexMesh>(args[0]->ToObject()));
				Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//				self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				self->SetInternalField(0, External::New( obj ));

				return scope.Close( self );
			}
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxConvexMesh::getTemplate()->HasInstance(args[0]) &&
				!args[1].IsEmpty() && args[1]->IsObject() && V8PxMeshScale::getTemplate()->HasInstance(args[1])){

			PxConvexMeshGeometry* obj = new PxConvexMeshGeometry(&*unwrap<PxConvexMesh>(args[0]->ToObject()), *unwrap<PxMeshScale>(args[1]->ToObject()));
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
        
		return ThrowException( Exception::TypeError( String::New("PxConvexMeshGeometry constructor takes nothing, (PxConvexMesh), (PxConvexMesh, PxMeshScale),  or (PxConvexMeshGeometry) as an argument.") ) );
	}

	Handle<Value> V8PxConvexMeshGeometry::getScale( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxConvexMeshGeometry* thisPxConvexMeshGeometry = unwrap<PxConvexMeshGeometry>(info.Holder());

		Persistent<Object> newPxMeshScale = Persistent<Object>::New(Isolate::GetCurrent(),V8PxMeshScale::getTemplate()->InstanceTemplate()->NewInstance());			
//		newPxMeshScale.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
		newPxMeshScale->SetInternalField(0, External::New(&thisPxConvexMeshGeometry->scale));

		return scope.Close(newPxMeshScale);
	}

	void V8PxConvexMeshGeometry::setScale( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8PxMeshScale::getTemplate()->HasInstance(value)){
			PxConvexMeshGeometry* thisPxConvexMeshGeometry = unwrap<PxConvexMeshGeometry>(info.Holder());

			thisPxConvexMeshGeometry->scale = *unwrap<PxMeshScale>(value->ToObject());
		}
	}

	Handle<Value> V8PxConvexMeshGeometry::getConvexMesh( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxConvexMeshGeometry* thisPxConvexMeshGeometry = unwrap<PxConvexMeshGeometry>(info.Holder());

		Persistent<Object> newPxConvexMesh = Persistent<Object>::New(Isolate::GetCurrent(),V8PxConvexMesh::getTemplate()->InstanceTemplate()->NewInstance());			
//		newPxConvexMesh.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
		newPxConvexMesh->SetInternalField(0, External::New(&thisPxConvexMeshGeometry->convexMesh));

		return scope.Close(newPxConvexMesh);
	}

	void V8PxConvexMeshGeometry::setConvexMesh( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8PxConvexMesh::getTemplate()->HasInstance(value)){
			PxConvexMeshGeometry* thisPxConvexMeshGeometry = unwrap<PxConvexMeshGeometry>(info.Holder());

			thisPxConvexMeshGeometry->convexMesh = &*unwrap<PxConvexMesh>(value->ToObject());
		}
	}

	Handle<Value> V8PxConvexMeshGeometry::isValid(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxConvexMeshGeometry* thisPxConvexMeshGeometry = unwrap<PxConvexMeshGeometry>(args.Holder());
			
			return scope.Close(Boolean::New(thisPxConvexMeshGeometry->isValid()));
		}

		return scope.Close( Undefined() );
	}

//PxHeightFieldGeometry

	Handle<Value>  V8PxHeightFieldGeometry::PxHeightFieldGeometryConstructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){
			PxHeightFieldGeometry* obj = new PxHeightFieldGeometry();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxHeightFieldGeometry::getTemplate()->HasInstance(args[0])){
			PxHeightFieldGeometry* obj = new PxHeightFieldGeometry(*unwrap<PxHeightFieldGeometry>(args[0]->ToObject()));
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
		else if(args.Length() == 5 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxHeightField::getTemplate()->HasInstance(args[0]) &&
			!args[1].IsEmpty() && (args[1]->IsInt32() || args[1]->IsUint32()) &&
			!args[2].IsEmpty() && args[2]->IsNumber() &&
			!args[3].IsEmpty() && args[3]->IsNumber() &&
			!args[4].IsEmpty() && args[4]->IsNumber()){

			PxHeightFieldGeometry* obj = new PxHeightFieldGeometry(&*unwrap<PxHeightField>(args[0]->ToObject()), PxMeshGeometryFlags(args[1]->Int32Value()),args[2]->NumberValue(),args[3]->NumberValue(),args[4]->NumberValue());
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
        
		return ThrowException( Exception::TypeError( String::New("PxHeightFieldGeometry constructor takes nothing, (PxHeightField, PxMeshGeometryFlags, Number, Number, Number),  or (PxHeightFieldGeometry) as an argument.") ) );
	}

	Handle<Value> V8PxHeightFieldGeometry::getHeightField( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxHeightFieldGeometry* thisPxHeightFieldGeometry = unwrap<PxHeightFieldGeometry>(info.Holder());

		Persistent<Object> newPxHeightField = Persistent<Object>::New(Isolate::GetCurrent(),V8PxHeightField::getTemplate()->InstanceTemplate()->NewInstance());			
//		newPxHeightField.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
		newPxHeightField->SetInternalField(0, External::New(&thisPxHeightFieldGeometry->heightField));

		return scope.Close(newPxHeightField);
	}

	void V8PxHeightFieldGeometry::setHeightField( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8PxHeightField::getTemplate()->HasInstance(value)){
			PxHeightFieldGeometry* thisPxHeightFieldGeometry = unwrap<PxHeightFieldGeometry>(info.Holder());

			thisPxHeightFieldGeometry->heightField = &*unwrap<PxHeightField>(value->ToObject());
		}
	}

	Handle<Value> V8PxHeightFieldGeometry::getHeightScale( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxHeightFieldGeometry* thisPxHeightFieldGeometry = unwrap<PxHeightFieldGeometry>(info.Holder());

		return scope.Close(Number::New(thisPxHeightFieldGeometry->heightScale));
	}

	void V8PxHeightFieldGeometry::setHeightScale( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PxHeightFieldGeometry* thisPxHeightFieldGeometry = unwrap<PxHeightFieldGeometry>(info.Holder());

			thisPxHeightFieldGeometry->heightScale = value->NumberValue();
		}
	}

	Handle<Value> V8PxHeightFieldGeometry::getRowScale( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxHeightFieldGeometry* thisPxHeightFieldGeometry = unwrap<PxHeightFieldGeometry>(info.Holder());

		return scope.Close(Number::New(thisPxHeightFieldGeometry->rowScale));
	}

	void V8PxHeightFieldGeometry::setRowScale( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PxHeightFieldGeometry* thisPxHeightFieldGeometry = unwrap<PxHeightFieldGeometry>(info.Holder());

			thisPxHeightFieldGeometry->rowScale = value->NumberValue();
		}
	}

	Handle<Value> V8PxHeightFieldGeometry::getColumnScale( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxHeightFieldGeometry* thisPxHeightFieldGeometry = unwrap<PxHeightFieldGeometry>(info.Holder());

		return scope.Close(Number::New(thisPxHeightFieldGeometry->columnScale));
	}

	void V8PxHeightFieldGeometry::setColumnScale( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PxHeightFieldGeometry* thisPxHeightFieldGeometry = unwrap<PxHeightFieldGeometry>(info.Holder());

			thisPxHeightFieldGeometry->columnScale = value->NumberValue();
		}
	}

	Handle<Value> V8PxHeightFieldGeometry::getHeightFeildFlags( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxHeightFieldGeometry* thisPxHeightFieldGeometry = unwrap<PxHeightFieldGeometry>(info.Holder());

		return scope.Close(Uint32::New(PxU32(thisPxHeightFieldGeometry->heightFieldFlags)));
	}

	void V8PxHeightFieldGeometry::setHeightFieldFlags( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && (value->IsInt32() || value->IsUint32())){
			PxHeightFieldGeometry* thisPxHeightFieldGeometry = unwrap<PxHeightFieldGeometry>(info.Holder());

			thisPxHeightFieldGeometry->heightFieldFlags = PxMeshGeometryFlags(value->Int32Value());
		}
	}

	Handle<Value> V8PxHeightFieldGeometry::getPaddingFromFlags( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxHeightFieldGeometry* thisPxHeightFieldGeometry = unwrap<PxHeightFieldGeometry>(info.Holder());

		PxPadding<3>* obj = new PxPadding<3>(thisPxHeightFieldGeometry->paddingFromFlags);
		Persistent<Object> newPxPadding3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxPadding<2>::getTemplate()->InstanceTemplate()->NewInstance());			
//		newPxPadding3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
		newPxPadding3->SetInternalField(0, External::New( obj ));

		return scope.Close(newPxPadding3);
	}

	void V8PxHeightFieldGeometry::setPaddingFromFlags( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8PxPadding<2>::getTemplate()->HasInstance(value)){
			PxHeightFieldGeometry* thisPxHeightFieldGeometry = unwrap<PxHeightFieldGeometry>(info.Holder());

			PxPadding<3>* thisPxPadding3 = unwrap<PxPadding<3>>(value->ToObject());

			thisPxHeightFieldGeometry->paddingFromFlags = *thisPxPadding3;
		}
	}

	Handle<Value> V8PxHeightFieldGeometry::isValid(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxHeightFieldGeometry* thisPxHeightFieldGeometry = unwrap<PxHeightFieldGeometry>(args.Holder());
			
			return scope.Close(Boolean::New(thisPxHeightFieldGeometry->isValid()));
		}

		return scope.Close( Undefined() );
	}

//PxSphereGeometry

	Handle<Value>  V8PxSphereGeometry::PxSphereGeometryConstructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){
			PxSphereGeometry* obj = new PxSphereGeometry();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty()){
			if(args[0]->IsObject() && V8PxSphereGeometry::getTemplate()->HasInstance(args[0])){
				PxSphereGeometry* obj = new PxSphereGeometry(*unwrap<PxSphereGeometry>(args[0]->ToObject()));
				Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//				self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				self->SetInternalField(0, External::New( obj ));

				return scope.Close( self );
			}
			else if(args[0]->IsNumber()){
				PxSphereGeometry* obj = new PxSphereGeometry(args[0]->NumberValue());
				Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//				self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				self->SetInternalField(0, External::New( obj ));

				return scope.Close( self );
			}
		}
        
		return ThrowException( Exception::TypeError( String::New("PxSphereGeometry constructor takes nothing, (Number),  or (PxSphereGeometry) as an argument.") ) );
	}

	Handle<Value> V8PxSphereGeometry::getRadius( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxSphereGeometry* thisPxSphereGeometry = unwrap<PxSphereGeometry>(info.Holder());

		return scope.Close(Number::New(thisPxSphereGeometry->radius));
	}

	void V8PxSphereGeometry::setRadius( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PxSphereGeometry* thisPxSphereGeometry = unwrap<PxSphereGeometry>(info.Holder());

			thisPxSphereGeometry->radius = value->NumberValue();
		}
	}

	Handle<Value> V8PxSphereGeometry::isValid(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxSphereGeometry* thisPxSphereGeometry = unwrap<PxSphereGeometry>(args.Holder());
			
			return scope.Close(Boolean::New(thisPxSphereGeometry->isValid()));
		}

		return scope.Close( Undefined() );
	}

//PxPlaneGeometry

	Handle<Value>  V8PxPlaneGeometry::PxPlaneGeometryConstructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){
			PxPlaneGeometry* obj = new PxPlaneGeometry();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxPlaneGeometry::getTemplate()->HasInstance(args[0])){
			PxPlaneGeometry* obj = new PxPlaneGeometry(*unwrap<PxPlaneGeometry>(args[0]->ToObject()));
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
        
		return ThrowException( Exception::TypeError( String::New("PxPlaneGeometry constructor takes nothing, or (PxPlaneGeometry) as an argument.") ) );
	}

	Handle<Value> V8PxPlaneGeometry::isValid(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxPlaneGeometry* thisPxPlaneGeometry = unwrap<PxPlaneGeometry>(args.Holder());
			
			return scope.Close(Boolean::New(thisPxPlaneGeometry->isValid()));
		}

		return scope.Close( Undefined() );
	}

//PxTriangleMeshGeometry

	Handle<Value>  V8PxTriangleMeshGeometry::PxTriangleMeshGeometryConstructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){
			PxTriangleMeshGeometry* obj = new PxTriangleMeshGeometry();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject()){
			
			if(V8PxTriangleMeshGeometry::getTemplate()->HasInstance(args[0])){
				PxTriangleMeshGeometry* obj = new PxTriangleMeshGeometry(*unwrap<PxTriangleMeshGeometry>(args[0]->ToObject()));
				Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//				self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				self->SetInternalField(0, External::New( obj ));

				return scope.Close( self );
			}
			else if(V8PxTriangleMesh::getTemplate()->HasInstance(args[0])){
				PxTriangleMeshGeometry* obj = new PxTriangleMeshGeometry(unwrap<PxTriangleMesh>(args[0]->ToObject()));
				Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//				self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				self->SetInternalField(0, External::New( obj ));

				return scope.Close( self );
			}
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxTriangleMesh::getTemplate()->HasInstance(args[0]) &&
			!args[1].IsEmpty() && args[1]->IsObject() && V8PxMeshScale::getTemplate()->HasInstance(args[1])){
			
			PxTriangleMeshGeometry* obj = new PxTriangleMeshGeometry( unwrap<PxTriangleMesh>(args[0]->ToObject()), *unwrap<PxMeshScale>(args[1]->ToObject()) );
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
		else if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxTriangleMesh::getTemplate()->HasInstance(args[0]) &&
			!args[1].IsEmpty() && args[1]->IsObject() && V8PxMeshScale::getTemplate()->HasInstance(args[1]) &&
			!args[2].IsEmpty() && (args[2]->IsInt32() || args[2]->IsUint32())){

			PxTriangleMeshGeometry* obj = new PxTriangleMeshGeometry( unwrap<PxTriangleMesh>(args[0]->ToObject()), *unwrap<PxMeshScale>(args[1]->ToObject()), PxMeshGeometryFlags(args[2]->Int32Value()) );
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
			self->SetInternalField(0, External::New( obj ));

			return scope.Close( self );
		}
        
		return ThrowException( Exception::TypeError( String::New("PxTriangleMeshGeometry constructor takes nothing, (PxTriangleMesh), (PxTriangleMesh, PxMeshScale), (PxTriangleMesh, PxMeshScale, PxMeshGeometryFlags),  or (PxTriangleMeshGeometry) as an argument.") ) );
	}

	Handle<Value> V8PxTriangleMeshGeometry::getScale( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxTriangleMeshGeometry* thisPxTriangleMeshGeometry = unwrap<PxTriangleMeshGeometry>(info.Holder());

		PxMeshScale* obj = new PxMeshScale(thisPxTriangleMeshGeometry->scale);
		Persistent<Object> newPxMeshScale = Persistent<Object>::New(Isolate::GetCurrent(),V8PxMeshScale::getTemplate()->InstanceTemplate()->NewInstance());			
//		newPxMeshScale.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
		newPxMeshScale->SetInternalField(0, External::New( obj ));

		return scope.Close(newPxMeshScale);
	}

	void V8PxTriangleMeshGeometry::setScale( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8PxMeshScale::getTemplate()->HasInstance(value)){
			PxTriangleMeshGeometry* thisPxTriangleMeshGeometry = unwrap<PxTriangleMeshGeometry>(info.Holder());

			PxMeshScale* inPxMeshScale = unwrap<PxMeshScale>(value->ToObject());

			thisPxTriangleMeshGeometry->scale = *inPxMeshScale;
		}
	}

	Handle<Value> V8PxTriangleMeshGeometry::getMeshFlags( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxTriangleMeshGeometry* thisPxTriangleMeshGeometry = unwrap<PxTriangleMeshGeometry>(info.Holder());

		return scope.Close(Uint32::New(PxU32(thisPxTriangleMeshGeometry->meshFlags)));
	}

	void V8PxTriangleMeshGeometry::setMeshFlags( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && (value->IsInt32() || value->IsUint32())){
			PxTriangleMeshGeometry* thisPxTriangleMeshGeometry = unwrap<PxTriangleMeshGeometry>(info.Holder());

			thisPxTriangleMeshGeometry->meshFlags = PxMeshGeometryFlags(value->Int32Value());
		}
	}
	
	Handle<Value> V8PxTriangleMeshGeometry::getPaddingFromFlags( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxTriangleMeshGeometry* thisPxTriangleMeshGeometry = unwrap<PxTriangleMeshGeometry>(info.Holder());

		PxPadding<3>* obj = new PxPadding<3>(thisPxTriangleMeshGeometry->paddingFromFlags);
		Persistent<Object> newPxPadding3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxPadding<2>::getTemplate()->InstanceTemplate()->NewInstance());			
//		newPxPadding3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
		newPxPadding3->SetInternalField(0, External::New( obj ));

		return scope.Close(newPxPadding3);
	}

	void V8PxTriangleMeshGeometry::setPaddingFromFlags( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8PxPadding<2>::getTemplate()->HasInstance(value)){
			PxTriangleMeshGeometry* thisPxTriangleMeshGeometry = unwrap<PxTriangleMeshGeometry>(info.Holder());

			PxPadding<3>* thisPxPadding3 = unwrap<PxPadding<3>>(value->ToObject());

			thisPxTriangleMeshGeometry->paddingFromFlags = *thisPxPadding3;
		}
	}

	Handle<Value> V8PxTriangleMeshGeometry::getTriangleMesh( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxTriangleMeshGeometry* thisPxTriangleMeshGeometry = unwrap<PxTriangleMeshGeometry>(info.Holder());

		Persistent<Object> newPxTriangleMesh = Persistent<Object>::New(Isolate::GetCurrent(),V8PxTriangleMesh::getTemplate()->InstanceTemplate()->NewInstance());			
//		newPxTriangleMesh.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
		newPxTriangleMesh->SetInternalField(0, External::New( thisPxTriangleMeshGeometry->triangleMesh ));

		return scope.Close(newPxTriangleMesh);
	}

	void V8PxTriangleMeshGeometry::setTriangleMesh( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8PxTriangleMesh::getTemplate()->HasInstance(value)){
			PxTriangleMeshGeometry* thisPxTriangleMeshGeometry = unwrap<PxTriangleMeshGeometry>(info.Holder());

			PxTriangleMesh* inPxTriangleMesh = unwrap<PxTriangleMesh>(value->ToObject());

			thisPxTriangleMeshGeometry->triangleMesh->release();

			thisPxTriangleMeshGeometry->triangleMesh = inPxTriangleMesh;
		}
	}

	Handle<Value> V8PxTriangleMeshGeometry::isValid(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxTriangleMeshGeometry* thisPxTriangleMeshGeometry = unwrap<PxTriangleMeshGeometry>(args.Holder());
			
			return scope.Close(Boolean::New(thisPxTriangleMeshGeometry->isValid()));
		}

		return scope.Close( Undefined() );
	}

//PxTriangleMesh

	Handle<Value> V8PxTriangleMesh::getNbVertices(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxTriangleMesh* thisPxTriangleMesh = unwrap<PxTriangleMesh>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxTriangleMesh->getNbVertices()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxTriangleMesh::getVertices(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxTriangleMesh* thisPxTriangleMesh = unwrap<PxTriangleMesh>(args.Holder());

			int numVerts = thisPxTriangleMesh->getNbVertices();

			Persistent<Array> newArray = Persistent<Array>::New(Isolate::GetCurrent(),Array::New(numVerts));
//			newArray.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);

			const PxVec3* verts = thisPxTriangleMesh->getVertices();
			
			for(int i = 0; i < numVerts; i++){
				PxVec3* obj = new PxVec3(verts[i]);
				Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxVec3->SetInternalField(0, External::New( obj ));

				newArray->SetInternalField(i, newPxVec3); 
			}
			
			return scope.Close(newArray);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxTriangleMesh::getNbTriangles(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxTriangleMesh* thisPxTriangleMesh = unwrap<PxTriangleMesh>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxTriangleMesh->getNbTriangles()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxTriangleMesh::getTriangles(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxTriangleMesh* thisPxTriangleMesh = unwrap<PxTriangleMesh>(args.Holder());

			int numTris = thisPxTriangleMesh->getNbTriangles() * 3;

			Persistent<Array> newArray = Persistent<Array>::New(Isolate::GetCurrent(),Array::New(numTris));
//			newArray.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);

			const void* indicies = thisPxTriangleMesh->getTriangles();
			bool bit16 = thisPxTriangleMesh->has16BitTriangleIndices();
			const PxU16* tris16;
			const PxU32* tris32;

			if(bit16){
				tris16 = static_cast<const PxU16*>(indicies);
			}
			else {
				tris32 = static_cast<const PxU32*>(indicies);
			}

			for(int i = 0; i < numTris; i++){
				if(bit16){
					newArray->SetInternalField(i, Uint32::New(tris16[i])); 
				}
				else {
					newArray->SetInternalField(i, Uint32::New(tris32[i])); 
				}
			}
			
			return scope.Close(newArray);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxTriangleMesh::has16BitTriangleIndices(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxTriangleMesh* thisPxTriangleMesh = unwrap<PxTriangleMesh>(args.Holder());
			
			return scope.Close( Boolean::New(thisPxTriangleMesh->has16BitTriangleIndices()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxTriangleMesh::getTrianglesRemap(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxTriangleMesh* thisPxTriangleMesh = unwrap<PxTriangleMesh>(args.Holder());

			int numTris = thisPxTriangleMesh->getNbTriangles() * 3;

			Persistent<Array> newArray = Persistent<Array>::New(Isolate::GetCurrent(),Array::New(numTris));
//			newArray.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);

			const void* indicies = thisPxTriangleMesh->getTrianglesRemap();
			bool bit16 = thisPxTriangleMesh->has16BitTriangleIndices();
			const PxU16* tris16;
			const PxU32* tris32;

			if(bit16){
				tris16 = static_cast<const PxU16*>(indicies);
			}
			else {
				tris32 = static_cast<const PxU32*>(indicies);
			}

			for(int i = 0; i < numTris; i++){
				if(bit16){
					newArray->SetInternalField(i, Uint32::New(tris16[i])); 
				}
				else {
					newArray->SetInternalField(i, Uint32::New(tris32[i])); 
				}
			}
			
			return scope.Close(newArray);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxTriangleMesh::release(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxTriangleMesh* thisPxTriangleMesh = unwrap<PxTriangleMesh>(args.Holder());

			thisPxTriangleMesh->release();
			
			return scope.Close( Undefined() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxTriangleMesh::getTriangleMaterialIndex(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32()) 
        {
			PxTriangleMesh* thisPxTriangleMesh = unwrap<PxTriangleMesh>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxTriangleMesh->getTriangleMaterialIndex(args[0]->Uint32Value())) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxTriangleMesh::getReferenceCount(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxTriangleMesh* thisPxTriangleMesh = unwrap<PxTriangleMesh>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxTriangleMesh->getReferenceCount()) );
		}

		return scope.Close( Undefined() );
	}

//PxFieldDescriptor
	Handle<Value> V8PxFieldDescriptor::getType( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(info.Holder());
		//if(thisPxFieldDescriptor != NULL) 
		//{
			return scope.Close(Int32::New( thisPxFieldDescriptor->mType ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxFieldDescriptor::setType( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsInt32()){
			PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(info.Holder());
			//if(thisPxFieldDescriptor != NULL && value->IsNumber()) 
			//{
			thisPxFieldDescriptor->mType = PxField::Enum(value->Int32Value());
			//}
		}
	}

	Handle<Value> V8PxFieldDescriptor::getName( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(info.Holder());
		//if(thisPxFieldDescriptor != NULL) 
		//{
			return scope.Close( String::New( thisPxFieldDescriptor->mName ));
		//}

		//return scope.Close( Undefined() );
	}

	//void V8PxFieldDescriptor::setName( Local<String> property, Local<Value> value, const AccessorInfo& info ){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(!value.IsEmpty() && value->IsString()){
	//		PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(info.Holder());
	//		//if(thisPxFieldDescriptor != NULL && value->IsNumber()) 
	//		//{
	//		thisPxFieldDescriptor->mName = *String::Utf8Value(value->ToString());
	//		//}
	//	}
	//}

	Handle<Value> V8PxFieldDescriptor::getOffset( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(info.Holder());
		//if(thisPxFieldDescriptor != NULL) 
		//{
			return scope.Close(Uint32::New( thisPxFieldDescriptor->mOffset ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxFieldDescriptor::setOffset( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsUint32()){
			PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(info.Holder());
			//if(thisPxFieldDescriptor != NULL && value->IsNumber()) 
			//{
			thisPxFieldDescriptor->mOffset = value->Uint32Value();
			//}
		}
	}

	Handle<Value> V8PxFieldDescriptor::getSize( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(info.Holder());
		//if(thisPxFieldDescriptor != NULL) 
		//{
			return scope.Close(Uint32::New( thisPxFieldDescriptor->mSize ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxFieldDescriptor::setSize( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsUint32()){
			PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(info.Holder());
			//if(thisPxFieldDescriptor != NULL && value->IsNumber()) 
			//{
			thisPxFieldDescriptor->mSize = value->Uint32Value();
			//}
		}
	}

	Handle<Value> V8PxFieldDescriptor::getCount( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(info.Holder());
		//if(thisPxFieldDescriptor != NULL) 
		//{
			return scope.Close(Uint32::New( thisPxFieldDescriptor->mCount ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxFieldDescriptor::setCount( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsUint32()){
			PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(info.Holder());
			//if(thisPxFieldDescriptor != NULL && value->IsNumber()) 
			//{
			thisPxFieldDescriptor->mCount = value->Uint32Value();
			//}
		}
	}

	Handle<Value> V8PxFieldDescriptor::getOffsetSize( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(info.Holder());
		//if(thisPxFieldDescriptor != NULL) 
		//{
			return scope.Close(Uint32::New( thisPxFieldDescriptor->mOffsetSize ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxFieldDescriptor::setOffsetSize( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsUint32()){
			PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(info.Holder());
			//if(thisPxFieldDescriptor != NULL && value->IsNumber()) 
			//{
			thisPxFieldDescriptor->mOffsetSize = value->Uint32Value();
			//}
		}
	}

	Handle<Value> V8PxFieldDescriptor::getFlags( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(info.Holder());
		//if(thisPxFieldDescriptor != NULL) 
		//{
			return scope.Close(Uint32::New( thisPxFieldDescriptor->mFlags ));
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxFieldDescriptor::setFlags( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsUint32()){
			PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(info.Holder());
			//if(thisPxFieldDescriptor != NULL && value->IsNumber()) 
			//{
			thisPxFieldDescriptor->mFlags = value->Uint32Value();
			//}
		}
	}


	//Handle<Value> V8PxFieldDescriptor::FieldSize(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0) 
	//	{
	//		PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(args.Holder());
	//		
	//		return scope.Close( Uint32::New(thisPxFieldDescriptor->FieldSize()) );
	//	}

	//	return scope.Close( Undefined() );
	//}

	Handle<Value> V8PxFieldDescriptor::Address(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsExternal()) 
		{
			PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(args.Holder());

			Persistent<External> newExternal = Persistent<External>::New(Isolate::GetCurrent(), External::New( thisPxFieldDescriptor->Address( Handle<External>::Cast(args[0])->Value() ) ) );
//			newExternal.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			
			return scope.Close( newExternal );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxFieldDescriptor::GetArrayAddress(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsExternal()) 
		{
			PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(args.Holder());

			Persistent<External> newExternal = Persistent<External>::New(Isolate::GetCurrent(), External::New( thisPxFieldDescriptor->GetArrayAddress( Handle<External>::Cast(args[0])->Value() ) ) );
//			newExternal.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			
			return scope.Close( newExternal );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxFieldDescriptor::IsStaticArray(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0 ) 
		{
			PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxFieldDescriptor->IsStaticArray()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxFieldDescriptor::GetStaticArraySize(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0 ) 
		{
			PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxFieldDescriptor->GetStaticArraySize()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxFieldDescriptor::IsDynamicArray(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0 ) 
		{
			PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxFieldDescriptor->IsDynamicArray()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxFieldDescriptor::GetDynamicArraySize(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsExternal()) 
		{
			PxFieldDescriptor* thisPxFieldDescriptor = unwrap<PxFieldDescriptor>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxFieldDescriptor->GetDynamicArraySize( Handle<External>::Cast(args[0])->Value() )) );
		}

		return scope.Close( Undefined() );
	}

//PxSerialStream

	//Handle<Value> V8PxSerialStream::storeBuffer(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsExternal() &&
	//		!args[1].IsEmpty() && args[1]->IsUint32()) 
	//	{
	//		PxSerialStream* thisPxSerialStream = unwrap<PxSerialStream>(args.Holder());

	//		thisPxSerialStream->storeBuffer( Handle<External>::Cast(args[0])->Value(), args[1]->Uint32Value() );
	//		
	//		return scope.Close( args.Holder() );
	//	}

	//	return scope.Close( Undefined() );
	//}
	//
	//Handle<Value> V8PxSerialStream::getTotalStoredSize(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsExternal() &&
	//		!args[1].IsEmpty() && args[1]->IsUint32()) 
	//	{
	//		PxSerialStream* thisPxSerialStream = unwrap<PxSerialStream>(args.Holder());
	//		
	//		return scope.Close( Uint32::New(thisPxSerialStream->getTotalStoredSize()) );
	//	}

	//	return scope.Close( Undefined() );
	//}

//PxMeshScale
	Handle<Value>  V8PxMeshScale::PxMeshScaleConstructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){
			PxMeshScale* meshScaleObj = new PxMeshScale();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),meshScaleObj, &CleanupDelete);
			self->SetInternalField(0, External::New( meshScaleObj ));

			return scope.Close( self );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxMat33::getTemplate()->HasInstance(args[0]) ){

			PxMeshScale* meshScaleObj = new PxMeshScale(*unwrap<PxMeshScale>(args[0]->ToObject()));
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),meshScaleObj, &CleanupDelete);
			self->SetInternalField(0, External::New( meshScaleObj ));

			return scope.Close( self );

		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0]) &&
				!args[1].IsEmpty() && args[1]->IsObject() && V8PxQuat::getTemplate()->HasInstance(args[1])){ //Mat33 orientation and Vec3 Position

			PxMeshScale* meshScaleObj = new PxMeshScale(*unwrap<PxVec3>(args[0]->ToObject()), *unwrap<PxQuat>(args[1]->ToObject()));
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),meshScaleObj, &CleanupDelete);
			self->SetInternalField(0, External::New( meshScaleObj ));

			return scope.Close( self );
		}

        
		return ThrowException( Exception::TypeError( String::New("PxMeshScale constructor takes nothing or (PxVec3, PxQuat) as an argument.") ) );
	}

	Handle<Value> V8PxMeshScale::createIdentity(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
		{
			PxMeshScale* meshScaleObj = new PxMeshScale(PxMeshScale::createIdentity());

			Persistent<Object> newMeshScale = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			newMeshScale.MakeWeak(Isolate::GetCurrent(),meshScaleObj, &CleanupDelete);
			newMeshScale->SetInternalField(0, External::New( meshScaleObj ));

			return scope.Close( newMeshScale );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMeshScale::getScale( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxMeshScale* thisPxMeshScale = unwrap<PxMeshScale>(info.Holder());

		Persistent<Object> newMeshScale = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//		newMeshScale.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
		newMeshScale->SetInternalField(0, External::New( &thisPxMeshScale->scale ) );

		return scope.Close( newMeshScale );
	}

	void V8PxMeshScale::setScale( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8PxVec3::getTemplate()->HasInstance(value)){
			PxMeshScale* thisPxMeshScale = unwrap<PxMeshScale>(info.Holder());

			PxVec3* inPxVec3 = unwrap<PxVec3>(value->ToObject());

			thisPxMeshScale->scale = *inPxVec3;
		}
	}

	Handle<Value> V8PxMeshScale::getRotation( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxMeshScale* thisPxMeshScale = unwrap<PxMeshScale>(info.Holder());

		Persistent<Object> newMeshScale = Persistent<Object>::New(Isolate::GetCurrent(),V8PxQuat::getTemplate()->InstanceTemplate()->NewInstance());			
//		newMeshScale.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
		newMeshScale->SetInternalField(0, External::New( &thisPxMeshScale->rotation ) );

		return scope.Close( newMeshScale );
	}

	void V8PxMeshScale::setRotation( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8PxQuat::getTemplate()->HasInstance(value)){
			PxMeshScale* thisPxMeshScale = unwrap<PxMeshScale>(info.Holder());

			PxQuat* inPxQuat = unwrap<PxQuat>(value->ToObject());

			thisPxMeshScale->rotation = *inPxQuat;
		}
	}

	Handle<Value> V8PxMeshScale::isIdentity(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
		{
			PxMeshScale* thisMeshScale = unwrap<PxMeshScale>( args.Holder() );

			return scope.Close( Boolean::New(thisMeshScale->isIdentity()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMeshScale::getInverse(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
		{
			PxMeshScale* thisMeshScale = unwrap<PxMeshScale>( args.Holder() );

			PxMeshScale* meshScaleObj = new PxMeshScale(thisMeshScale->getInverse());

			Persistent<Object> newMeshScale = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			newMeshScale.MakeWeak(Isolate::GetCurrent(),meshScaleObj, &CleanupDelete);
			newMeshScale->SetInternalField(0, External::New( meshScaleObj ));

			return scope.Close( newMeshScale );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMeshScale::toMat33(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
		{
			PxMeshScale* thisMeshScale = unwrap<PxMeshScale>( args.Holder() );

			PxMat33* mat33Obj = new PxMat33( thisMeshScale->toMat33() );

			Persistent<Object> newMat33 = Persistent<Object>::New(Isolate::GetCurrent(), V8PxMat33::getTemplate()->InstanceTemplate()->NewInstance() );
//			newMat33.MakeWeak(Isolate::GetCurrent(),mat33Obj, &CleanupDelete);
			newMat33->SetInternalField(0, External::New( mat33Obj ));

			return scope.Close( newMat33 );
		}

		return scope.Close( Undefined() );
	}

//PxConvexMesh

	Handle<Value> V8PxConvexMesh::getNbVertices(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxConvexMesh* thisPxConvexMesh = unwrap<PxConvexMesh>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxConvexMesh->getNbVertices()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxConvexMesh::getVertices(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxConvexMesh* thisPxConvexMesh = unwrap<PxConvexMesh>(args.Holder());

			int numVerts = thisPxConvexMesh->getNbVertices();

			Persistent<Array> newArray = Persistent<Array>::New(Isolate::GetCurrent(),Array::New(numVerts));
//			newArray.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);

			const PxVec3* verts = thisPxConvexMesh->getVertices();
			
			for(int i = 0; i < numVerts; i++){
				PxVec3* obj = new PxVec3(verts[i]);
				Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
				newPxVec3->SetInternalField(0, External::New( obj ));

				newArray->SetInternalField(i, newPxVec3); 
			}
			
			return scope.Close(newArray);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxConvexMesh::getIndexBuffer(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxConvexMesh* thisPxConvexMesh = unwrap<PxConvexMesh>(args.Holder());

			int numPoly = thisPxConvexMesh->getNbPolygons();

			Persistent<Array> newArray = Persistent<Array>::New(Isolate::GetCurrent(),Array::New(numPoly));
//			newArray.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);

			const PxU8* indicies = thisPxConvexMesh->getIndexBuffer();
			
			for(int i = 0; i < numPoly; i++){
				newArray->SetInternalField(i, Uint32::New(indicies[i])); 
			}
			
			return scope.Close(newArray);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxConvexMesh::getNbPolygons(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxConvexMesh* thisPxConvexMesh = unwrap<PxConvexMesh>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxConvexMesh->getNbPolygons()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxConvexMesh::getPolygonData(const Arguments& args){ //NEED TO TEST THIS BADLY, DATA MIGHT GO OUT OF SCOPE AND DIE
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32()) 
        {
			PxConvexMesh* thisPxConvexMesh = unwrap<PxConvexMesh>(args.Holder());

			PxHullPolygon* data = NULL;

			if(thisPxConvexMesh->getPolygonData(args[0]->Uint32Value(), *data)){
				Persistent<Object> newPxHullPolygon = Persistent<Object>::New(Isolate::GetCurrent(),V8PxHullPolygon::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxHullPolygon.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
				newPxHullPolygon->SetInternalField(0, External::New( data ));
			
				return scope.Close( newPxHullPolygon );
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxConvexMesh::release(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxConvexMesh* thisPxConvexMesh = unwrap<PxConvexMesh>(args.Holder());

			thisPxConvexMesh->release();
			
			return scope.Close( Undefined() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxConvexMesh::getReferenceCount(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxConvexMesh* thisPxConvexMesh = unwrap<PxConvexMesh>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxConvexMesh->getReferenceCount()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxConvexMesh::getMassInformation(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxConvexMesh* thisPxConvexMesh = unwrap<PxConvexMesh>(args.Holder());
			
			Persistent<Array> newArray = Persistent<Array>::New(Isolate::GetCurrent(),Array::New(3));
//			newArray.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);

			PxReal* mass = NULL;
			PxMat33* localInertia = NULL;
			PxVec3* localCenterOfMass = NULL;

			thisPxConvexMesh->getMassInformation(*mass, *localInertia, *localCenterOfMass);

			Persistent<Object> newPxMat33 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxMat33::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxMat33.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxMat33->SetInternalField(0, External::New( localInertia ));

			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxVec3->SetInternalField(0, External::New( localCenterOfMass ));

			newArray->SetInternalField(0, Number::New(*mass));
			newArray->SetInternalField(1, newPxMat33);
			newArray->SetInternalField(2, newPxVec3);
			
			return scope.Close(newArray);
		}

		return scope.Close( Undefined() );
	}

//PxHeightField

	Handle<Value> V8PxHeightField::release(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxHeightField* thisPxHeightField = unwrap<PxHeightField>(args.Holder());

			thisPxHeightField->release();
			
			return scope.Close( Undefined() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxHeightField::saveCells(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == !args[0].IsEmpty() && args[0]->IsExternal() && !args[1].IsEmpty() && args[1]->IsUint32()) 
        {
			PxHeightField* thisPxHeightField = unwrap<PxHeightField>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxHeightField->saveCells( Local<External>::Cast(args[1])->Value() , args[1]->Uint32Value())) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxHeightField::getNbRows(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxHeightField* thisPxHeightField = unwrap<PxHeightField>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxHeightField->getNbRows()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxHeightField::getNbColumns(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxHeightField* thisPxHeightField = unwrap<PxHeightField>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxHeightField->getNbColumns()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxHeightField::getFormat(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxHeightField* thisPxHeightField = unwrap<PxHeightField>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxHeightField->getFormat()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxHeightField::getSampleStride(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxHeightField* thisPxHeightField = unwrap<PxHeightField>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxHeightField->getSampleStride()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxHeightField::getThickness(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxHeightField* thisPxHeightField = unwrap<PxHeightField>(args.Holder());
			
			return scope.Close( Number::New(thisPxHeightField->getThickness()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxHeightField::getConvexEdgeThreshold(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxHeightField* thisPxHeightField = unwrap<PxHeightField>(args.Holder());
			
			return scope.Close( Number::New(thisPxHeightField->getConvexEdgeThreshold()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxHeightField::getFlags(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxHeightField* thisPxHeightField = unwrap<PxHeightField>(args.Holder());
			
			return scope.Close( Uint32::New((PxU32)thisPxHeightField->getFlags()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxHeightField::getHeight(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsNumber() && !args[1].IsEmpty() && args[1]->IsNumber()) 
        {
			PxHeightField* thisPxHeightField = unwrap<PxHeightField>(args.Holder());
			
			return scope.Close( Number::New(thisPxHeightField->getHeight(args[0]->NumberValue() , args[1]->NumberValue())) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxHeightField::getReferenceCount(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxHeightField* thisPxHeightField = unwrap<PxHeightField>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxHeightField->getReferenceCount()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxHeightField::getTriangleMaterialIndex(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32()) 
        {
			PxHeightField* thisPxHeightField = unwrap<PxHeightField>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxHeightField->getTriangleMaterialIndex(args[0]->Uint32Value())) );
		}

		return scope.Close( Undefined() );
	}

//PxFilterData
	Handle<Value>  V8PxFilterData::PxFilterDataConstructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){
			PxFilterData* filtDataObject = new PxFilterData();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),filtDataObject, &CleanupDelete);
			self->SetInternalField(0, External::New( filtDataObject ));

			return scope.Close( self );
		}
		else if(args.Length() == 4 && !args[0].IsEmpty() && args[0]->IsUint32() &&
									  !args[1].IsEmpty() && args[1]->IsUint32() &&
									  !args[2].IsEmpty() && args[2]->IsUint32() &&
									  !args[3].IsEmpty() && args[3]->IsUint32()){
			
			PxFilterData* filtDataObject = new PxFilterData(args[0]->Uint32Value(), args[1]->Uint32Value(), args[2]->Uint32Value(), args[3]->Uint32Value());
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),filtDataObject, &CleanupDelete);
			self->SetInternalField(0, External::New( filtDataObject ));

			return scope.Close( self );
		}
        
		return ThrowException( Exception::TypeError( String::New("PxFilterData constructor takes nothing, (UInt, UInt, UInt, UInt) as an argument.") ) );
	}

	Handle<Value> V8PxFilterData::getword0( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxFilterData* thisPxFilterData = unwrap<PxFilterData>(info.Holder());
		//if(thisPxFilterData != NULL) 
		//{
			return scope.Close( Uint32::New( thisPxFilterData->word0 ) );
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxFilterData::setword0( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxFilterData* thisPxFilterData = unwrap<PxFilterData>(info.Holder());
		if(thisPxFilterData != NULL && value->IsUint32()) 
		{
			thisPxFilterData->word0 = value->Uint32Value();
		}
	}

	Handle<Value> V8PxFilterData::getword1( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxFilterData* thisPxFilterData = unwrap<PxFilterData>(info.Holder());
		//if(thisPxFilterData != NULL) 
		//{
			return scope.Close( Uint32::New( thisPxFilterData->word1 ) );
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxFilterData::setword1( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxFilterData* thisPxFilterData = unwrap<PxFilterData>(info.Holder());
		if(thisPxFilterData != NULL && value->IsUint32()) 
		{
			thisPxFilterData->word1 = value->Uint32Value();
		}
	}

	Handle<Value> V8PxFilterData::getword2( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxFilterData* thisPxFilterData = unwrap<PxFilterData>(info.Holder());
		//if(thisPxFilterData != NULL) 
		//{
			return scope.Close( Uint32::New( thisPxFilterData->word2 ) );
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxFilterData::setword2( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxFilterData* thisPxFilterData = unwrap<PxFilterData>(info.Holder());
		if(thisPxFilterData != NULL && value->IsUint32()) 
		{
			thisPxFilterData->word2 = value->Uint32Value();
		}
	}

	Handle<Value> V8PxFilterData::getword3( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxFilterData* thisPxFilterData = unwrap<PxFilterData>(info.Holder());
		//if(thisPxFilterData != NULL) 
		//{
			return scope.Close( Uint32::New( thisPxFilterData->word3 ) );
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxFilterData::setword3( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxFilterData* thisPxFilterData = unwrap<PxFilterData>(info.Holder());
		if(thisPxFilterData != NULL && value->IsUint32()) 
		{
			thisPxFilterData->word3 = value->Uint32Value();
		}
	}

	Handle<Value> V8PxFilterData::setToDefault(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxFilterData* thisPxFilterData = unwrap<PxFilterData>(args.Holder());

			thisPxFilterData->setToDefault();
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

//PxHullPolygon
	Handle<Value>  V8PxHullPolygon::PxHullPolygonConstructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0){
			PxHullPolygon* filtDataObject = new PxHullPolygon();
			Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			self.MakeWeak(Isolate::GetCurrent(),filtDataObject, &CleanupDelete);
			self->SetInternalField(0, External::New( filtDataObject ));

			Persistent<Object> planeEqn = Persistent<Object>::New(Isolate::GetCurrent(),Object::New());
//			planeEqn.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			planeEqn->SetIndexedPropertiesToExternalArrayData(filtDataObject->mPlane, v8::kExternalFloatArray, 4);

			self->SetAccessor(String::New("mPlane"), getmPlane, NULL, planeEqn);

			return scope.Close( self );
		}
        
		return ThrowException( Exception::TypeError( String::New("PxHullPolygon constructor takes nothing as an argument.") ) );
	}

	Handle<Value> V8PxHullPolygon::getmPlane( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		//PxHullPolygon* thisPxHullPolygon = unwrap<PxHullPolygon>(info.Holder());
		//if(thisPxHullPolygon != NULL) 
		//{

			return scope.Close( info.Data() );
		//}

		//return scope.Close( Undefined() );
	}

	Handle<Value> V8PxHullPolygon::getmNbVerts( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxHullPolygon* thisPxHullPolygon = unwrap<PxHullPolygon>(info.Holder());
		//if(thisPxHullPolygon != NULL) 
		//{

		return scope.Close( Uint32::New(thisPxHullPolygon->mNbVerts) );
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxHullPolygon::setmNbVerts( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxHullPolygon* thisPxHullPolygon = unwrap<PxHullPolygon>(info.Holder());
		if(thisPxHullPolygon != NULL && value->IsUint32()) 
		{
			thisPxHullPolygon->mNbVerts = value->Uint32Value();
		}
	}

	Handle<Value> V8PxHullPolygon::getmIndexBase( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxHullPolygon* thisPxHullPolygon = unwrap<PxHullPolygon>(info.Holder());
		//if(thisPxHullPolygon != NULL) 
		//{

		return scope.Close( Uint32::New(thisPxHullPolygon->mIndexBase) );
		//}

		//return scope.Close( Undefined() );
	}

	void V8PxHullPolygon::setmIndexBase( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxHullPolygon* thisPxHullPolygon = unwrap<PxHullPolygon>(info.Holder());
		if(thisPxHullPolygon != NULL && value->IsUint32()) 
		{
			thisPxHullPolygon->mIndexBase = value->Uint32Value();
		}
	}

//PxMaterial

	Handle<Value> V8PxMaterial::getUserData( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());


		if(info.Data().IsEmpty()){
			PxMaterial* thisPxMaterial = unwrap<PxMaterial>(info.Holder());

			if(thisPxMaterial->userData){
				return( Local<Value>::New(External::New(thisPxMaterial->userData)) );
			}
			else {
				return( Undefined() );
			}
		}
		else {
			return scope.Close(info.Data());
		}

	}

	void V8PxMaterial::setUserData( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty()){
			PxMaterial* thisPxMaterial = unwrap<PxMaterial>(info.Holder());
			thisPxMaterial->userData = Local<External>::Cast(value)->Value();

			info.Holder()->SetAccessor(String::New("userData"), getUserData, setUserData, value);
		}
	}

	Handle<Value> V8PxMaterial::release(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());

			thisPxMaterial->release();
			
			return scope.Close( Undefined() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMaterial::setDynamicFriction(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());

			thisPxMaterial->setDynamicFriction(args[0]->NumberValue());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMaterial::getDynamicFriction(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());
			
			return scope.Close( Number::New(thisPxMaterial->getDynamicFriction()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMaterial::setStaticFriction(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());

			thisPxMaterial->setStaticFriction(args[0]->NumberValue());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMaterial::getStaticFriction(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());
			
			return scope.Close( Number::New(thisPxMaterial->getStaticFriction()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMaterial::setRestitution(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());

			thisPxMaterial->setRestitution(args[0]->NumberValue());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMaterial::getRestitution(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());
			
			return scope.Close( Number::New(thisPxMaterial->getRestitution()) );
		}

		return scope.Close( Undefined() );
	}

	//Handle<Value> V8PxMaterial::setDynamicFrictionV(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
 //       {
	//		PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());

	//		thisPxMaterial->setDynamicFrictionV(args[0]->NumberValue());
	//		
	//		return scope.Close( args.Holder() );
	//	}

	//	return scope.Close( Undefined() );
	//}

	//Handle<Value> V8PxMaterial::getDynamicFrictionV(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0) 
 //       {
	//		PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());
	//		
	//		return scope.Close( Number::New(thisPxMaterial->getDynamicFrictionV()) );
	//	}

	//	return scope.Close( Undefined() );
	//}

	//Handle<Value> V8PxMaterial::setStaticFrictionV(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
 //       {
	//		PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());

	//		thisPxMaterial->setStaticFrictionV(args[0]->NumberValue());
	//		
	//		return scope.Close( args.Holder() );
	//	}

	//	return scope.Close( Undefined() );
	//}

	//Handle<Value> V8PxMaterial::getStaticFrictionV(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0) 
 //       {
	//		PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());
	//		
	//		return scope.Close( Number::New(thisPxMaterial->getStaticFrictionV()) );
	//	}

	//	return scope.Close( Undefined() );
	//}

	//Handle<Value> V8PxMaterial::setDirOfAnisotropy(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
 //       {
	//		PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());

	//		PxVec3* inPxVec3 = unwrap<PxVec3>(args[0]->ToObject());

	//		thisPxMaterial->setDirOfAnisotropy(*inPxVec3);
	//		
	//		return scope.Close( args.Holder() );
	//	}

	//	return scope.Close( Undefined() );
	//}

	//Handle<Value> V8PxMaterial::getDirOfAnisotropy(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0) 
 //       {
	//		PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());

	//		PxVec3* obj = new PxVec3(thisPxMaterial->getDirOfAnisotropy());
	//		Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),args.Holder()->Clone());			
//	//		newPxVec3.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
	//		newPxVec3->SetInternalField(0, External::New( obj ));
	//		
	//		return scope.Close(newPxVec3);
	//	}

	//	return scope.Close( Undefined() );
	//}

	Handle<Value> V8PxMaterial::setFlag(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsUint32() &&
								 !args[1].IsEmpty() && args[1]->IsBoolean()) 
        {
			PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());

			thisPxMaterial->setFlag((PxMaterialFlag::Enum)args[0]->Uint32Value(), args[1]->BooleanValue());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMaterial::setFlags(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32()) 
        {
			PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());

			thisPxMaterial->setFlags((PxMaterialFlags)args[0]->Uint32Value());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMaterial::getFlags(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());
			
			return scope.Close( Uint32::New((PxU32)thisPxMaterial->getFlags()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMaterial::setFrictionCombineMode(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());

			thisPxMaterial->setFrictionCombineMode((PxCombineMode::Enum)args[0]->Uint32Value());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMaterial::getFrictionCombineMode(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxMaterial->getFrictionCombineMode()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMaterial::setRestitutionCombineMode(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());

			thisPxMaterial->setRestitutionCombineMode((PxCombineMode::Enum)args[0]->Uint32Value());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxMaterial::getRestitutionCombineMode(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxMaterial* thisPxMaterial = unwrap<PxMaterial>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxMaterial->getRestitutionCombineMode()) );
		}

		return scope.Close( Undefined() );
	}

//PxObserver

	Handle<Value> V8PxObserver::onRelease(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxObserver* thisPxObserver = unwrap<PxObserver>(args.Holder());			

			PxObservable* observable = NULL;

			thisPxObserver->onRelease(*observable);

			Persistent<Object> newPxObservable = Persistent<Object>::New(Isolate::GetCurrent(),V8PxObservable::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxObservable.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxObservable->SetInternalField(0, External::New( observable ));
			
			return scope.Close( newPxObservable );
		}

		return scope.Close( Undefined() );
	}

//PxObservable

	Handle<Value> V8PxObservable::getObservableType(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxObservable* thisPxObservable = unwrap<PxObservable>(args.Holder());			
			
			return scope.Close( Uint32::New( thisPxObservable->getObservableType() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxObservable::registerObserver(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxObserver::getTemplate()->HasInstance(args[0])) 
        {
			PxObservable* thisPxObservable = unwrap<PxObservable>(args.Holder());

			PxObserver* inPxObserver = unwrap<PxObserver>(args[0]->ToObject());

			thisPxObservable->registerObserver(*inPxObserver);
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxObservable::unregisterObserver(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxObserver::getTemplate()->HasInstance(args[0])) 
        {
			PxObservable* thisPxObservable = unwrap<PxObservable>(args.Holder());

			PxObserver* inPxObserver = unwrap<PxObserver>(args[0]->ToObject());

			thisPxObservable->unregisterObserver(*inPxObserver);
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxObservable::getNbObservers(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxObservable* thisPxObservable = unwrap<PxObservable>(args.Holder());			
			
			return scope.Close( Uint32::New( thisPxObservable->getNbObservers() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxObservable::getObservers(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxObservable* thisPxObservable = unwrap<PxObservable>(args.Holder());

			PxObserver** newObs = (PxObserver**)malloc(sizeof(PxObserver*)*thisPxObservable->getNbObservers());

			int numObs = thisPxObservable->getObservers(newObs, thisPxObservable->getNbObservers());

			Persistent<Array> newArray = Persistent<Array>::New(Isolate::GetCurrent(),Array::New(numObs));
//			newArray.MakeWeak(Isolate::GetCurrent(),newObs, &CleanupFree);
			
			for(int i = 0; i < numObs; i++){
				Persistent<Object> newPxObserver = Persistent<Object>::New(Isolate::GetCurrent(),V8PxObserver::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxObserver.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
				newPxObserver->SetInternalField(0, External::New( newObs[i] ));

				newArray->SetInternalField(i, newPxObserver); 
			}

			
			return scope.Close(newArray);
		}

		return scope.Close( Undefined() );
	}

//PxActor

	Handle<Value> V8PxActor::getUserData( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());


		if(info.Data().IsEmpty()){
			PxActor* thisPxActor = unwrap<PxActor>(info.Holder());

			if(thisPxActor->userData){
				return( Local<Value>::New(External::New(thisPxActor->userData)) );
			}
			else {
				return( Undefined() );
			}
		}
		else {
			return scope.Close(info.Data());
		}

	}

	void V8PxActor::setUserData( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty()){
			PxActor* thisPxActor = unwrap<PxActor>(info.Holder());
			thisPxActor->userData = Local<External>::Cast(value)->Value();

			info.Holder()->SetAccessor(String::New("userData"), getUserData, setUserData, value);
		}
	}

	Handle<Value> V8PxActor::release(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			thisPxActor->release();
			
			return scope.Close( Undefined() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::getType(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());
			
			return scope.Close( Uint32::New( thisPxActor->getType() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::isRigidStatic(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			PxRigidStatic* newObj = thisPxActor->isRigidStatic();

			if(newObj){
				Persistent<Object> newPxRigidStatic = Persistent<Object>::New(Isolate::GetCurrent(),V8PxRigidStatic::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxRigidStatic.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
				newPxRigidStatic->SetInternalField(0, External::New( newObj ));

				return scope.Close( newPxRigidStatic );
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::isRigidDynamic(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			PxRigidDynamic* newObj = thisPxActor->isRigidDynamic();

			if(newObj){
				Persistent<Object> newPxRigidDynamic = Persistent<Object>::New(Isolate::GetCurrent(),V8PxRigidDynamic::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxRigidDynamic.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
				newPxRigidDynamic->SetInternalField(0, External::New( newObj ));

				return scope.Close( newPxRigidDynamic );
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::isParticleSystem(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			PxParticleSystem* newObj = thisPxActor->isParticleSystem();

			if(newObj){
				Persistent<Object> newPxParticleSystem = Persistent<Object>::New(Isolate::GetCurrent(),V8PxParticleSystem::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxParticleSystem.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
				newPxParticleSystem->SetInternalField(0, External::New( newObj ));

				return scope.Close( newPxParticleSystem );
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::isParticleFluid(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			PxParticleFluid* newObj = thisPxActor->isParticleFluid();

			if(newObj){
				Persistent<Object> newPxParticleFluid = Persistent<Object>::New(Isolate::GetCurrent(),V8PxParticleFluid::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxParticleFluid.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
				newPxParticleFluid->SetInternalField(0, External::New( newObj ));

				return scope.Close( newPxParticleFluid );
			}
		}

		return scope.Close( Undefined() );
	}

	//Handle<Value> V8PxActor::isDeformable(const Arguments& args){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(args.Length() == 0) 
 //       {
	//		PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

	//		PxDeformable* newObj = thisPxActor->isDeformable();

	//		if(newObj){
	//			Persistent<Object> newPxDeformable = Persistent<Object>::New(Isolate::GetCurrent(),V8PxDeformable::getTemplate()->InstanceTemplate()->NewInstance());			
//	//			newPxDeformable.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
	//			newPxDeformable->SetInternalField(0, External::New( newObj ));

	//			return scope.Close( newPxDeformable );
	//		}
	//	}

	//	return scope.Close( Undefined() );
	//}

	Handle<Value> V8PxActor::isArticulationLink(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			PxArticulationLink* newObj = thisPxActor->isArticulationLink();

			if(newObj){
				Persistent<Object> newPxArticulationLink = Persistent<Object>::New(Isolate::GetCurrent(),V8PxArticulationLink::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxArticulationLink.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
				newPxArticulationLink->SetInternalField(0, External::New( newObj ));

				return scope.Close( newPxArticulationLink );
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::isRigidActor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			PxRigidActor* newObj = thisPxActor->isRigidActor();

			if(newObj){
				Persistent<Object> newPxRigidActor = Persistent<Object>::New(Isolate::GetCurrent(),V8PxRigidActor::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxRigidActor.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
				newPxRigidActor->SetInternalField(0, External::New( newObj ));

				return scope.Close( newPxRigidActor );
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::isRigidBody(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			PxRigidBody* newObj = thisPxActor->isRigidBody();

			if(newObj){
				Persistent<Object> newPxRigidBody = Persistent<Object>::New(Isolate::GetCurrent(),V8PxRigidBody::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxRigidBody.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
				newPxRigidBody->SetInternalField(0, External::New( newObj ));

				return scope.Close( newPxRigidBody );
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::isParticleBase(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			PxParticleBase* newObj = thisPxActor->isParticleBase();

			if(newObj){
				Persistent<Object> newPxParticleBase = Persistent<Object>::New(Isolate::GetCurrent(),V8PxParticleBase::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxParticleBase.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
				newPxParticleBase->SetInternalField(0, External::New( newObj ));

				return scope.Close( newPxParticleBase );
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::getScene(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			PxScene* scene = thisPxActor->getScene();

			Persistent<Object> newPxScene = Persistent<Object>::New(Isolate::GetCurrent(),V8PxScene::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxScene.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxScene->SetInternalField(0, External::New( scene ));

			return scope.Close( newPxScene );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::setName(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsString()) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			thisPxActor->setName( *String::Utf8Value(args[0]->ToString()) );

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::getName(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsString()) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			return scope.Close( String::New(thisPxActor->getName()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::getWorldBounds(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			PxBounds3* bounds = new PxBounds3(thisPxActor->getWorldBounds());

			Persistent<Object> newPxBounds3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxBounds3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxBounds3.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupDelete);
			newPxBounds3->SetInternalField(0, External::New( bounds ));

			return scope.Close( newPxBounds3 );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::setActorFlag(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsUint32() &&
								 !args[1].IsEmpty() && args[1]->IsBoolean()) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			thisPxActor->setActorFlag((PxActorFlag::Enum)args[0]->Uint32Value(), args[1]->BooleanValue());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::setActorFlags(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32()) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			thisPxActor->setActorFlags((PxActorFlags)args[0]->Uint32Value());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::getActorFlags(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());
			
			return scope.Close( Uint32::New((PxU32)thisPxActor->getActorFlags()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::setDominanceGroup(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32()) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			thisPxActor->setDominanceGroup((PxDominanceGroup)args[0]->Uint32Value());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::getDominanceGroup(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());
			
			return scope.Close( Uint32::New((PxU32)thisPxActor->getDominanceGroup()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::setOwnerClient(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32()) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			thisPxActor->setOwnerClient((PxClientID)args[0]->Uint32Value());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::getOwnerClient(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());
			
			return scope.Close( Uint32::New((PxU32)thisPxActor->getOwnerClient()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::setClientBehaviorBits(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32()) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			thisPxActor->setClientBehaviorBits((PxU32)args[0]->Uint32Value());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::getClientBehaviorBits(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());
			
			return scope.Close( Uint32::New((PxU32)thisPxActor->getClientBehaviorBits()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxActor::getAggregate(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxActor* thisPxActor = unwrap<PxActor>(args.Holder());

			PxAggregate* aggregate = thisPxActor->getAggregate();

			Persistent<Object> newPxAggregate = Persistent<Object>::New(Isolate::GetCurrent(),V8PxAggregate::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxAggregate.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupDelete);
			newPxAggregate->SetInternalField(0, External::New( aggregate ));

			return scope.Close( newPxAggregate );
		}

		return scope.Close( Undefined() );
	}

//PxRigidActor

	Handle<Value> V8PxRigidActor::release(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxRigidActor* thisPxRigidActor = unwrap<PxRigidActor>(args.Holder());

			thisPxRigidActor->release();
			
			return scope.Close( Undefined() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidActor::getGlobalPose(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxRigidActor* thisPxRigidActor = unwrap<PxRigidActor>(args.Holder());

			PxTransform* transf = new PxTransform(thisPxRigidActor->getGlobalPose());

			Persistent<Object> newPxTransform = Persistent<Object>::New(Isolate::GetCurrent(),V8PxTransform::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxTransform.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupDelete);
			newPxTransform->SetInternalField(0, External::New( transf ));
			
			return scope.Close( newPxTransform );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidActor::setGlobalPose(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!args[0].IsEmpty() && args[0]->IsObject() && V8PxTransform::getTemplate()->HasInstance(args[0])) 
        {

			PxTransform* inPose = unwrap<PxTransform>(args[0]->ToObject());
			PxRigidActor* thisPxRigidActor = unwrap<PxRigidActor>(args.Holder());

			if(args.Length() == 1) {
				thisPxRigidActor->setGlobalPose(*inPose);
				return scope.Close(args.Holder() );
			}
			else if(args.Length() == 2 && !args[1].IsEmpty() && args[1]->IsBoolean()){
				thisPxRigidActor->setGlobalPose(*inPose, args[1]->BooleanValue());
				return scope.Close(args.Holder() );
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidActor::createShape(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxRigidActor* thisPxRigidActor = unwrap<PxRigidActor>(args.Holder());

		/*if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxShapeDesc::getTemplate()->HasInstance(args[0])) 
        {
			PxShapeDesc* inPxShapeDesc = unwrap<PxShapeDesc>(args[0]->ToObject());

			PxShape* shape = thisPxRigidActor->createShape(*inPxShapeDesc);

			Persistent<Object> newPxShape = Persistent<Object>::New(Isolate::GetCurrent(),V8PxShape::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxShape.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupDelete);
			newPxShape->SetInternalField(0, External::New( shape ));

			return scope.Close( newPxShape );
		}
		else */if(args.Length() > 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxGeometry::getTemplate()->HasInstance(args[0])){

			PxGeometry* inPxGeometry = unwrap<PxGeometry>(args[0]->ToObject());

			if(!args[1].IsEmpty() && args[1]->IsObject() && V8PxMaterial::getTemplate()->HasInstance(args[1])){

				PxMaterial* inPxMaterial = unwrap<PxMaterial>(args[1]->ToObject());

				if(!args[2].IsEmpty() && args[2]->IsObject() && V8PxTransform::getTemplate()->HasInstance(args[2])){

					PxTransform* inPxTransform = unwrap<PxTransform>(args[2]->ToObject());

					PxShape* shape = thisPxRigidActor->createShape(*inPxGeometry, *inPxMaterial, *inPxTransform);

					Persistent<Object> newPxShape = Persistent<Object>::New(Isolate::GetCurrent(),V8PxShape::getTemplate()->InstanceTemplate()->NewInstance());			
//					newPxShape.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupDelete);
					newPxShape->SetInternalField(0, External::New( shape ));

					return scope.Close( newPxShape );

				}
				else if(args[2].IsEmpty()) {
					PxShape* shape = thisPxRigidActor->createShape(*inPxGeometry, *inPxMaterial);

					Persistent<Object> newPxShape = Persistent<Object>::New(Isolate::GetCurrent(),V8PxShape::getTemplate()->InstanceTemplate()->NewInstance());			
//					newPxShape.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupDelete);
					newPxShape->SetInternalField(0, External::New( shape ));

					return scope.Close( newPxShape );
				}
			}
			else if(!args[1].IsEmpty() && args[1]->IsArray()){
				Local<Array> arr = Local<Array>::Cast(args[1]);
				int length = arr->Length();
				PxMaterial** matBuffer = (PxMaterial**)malloc(sizeof(PxMaterial*)*length);
				for(int i = 0; i < length; i++){
					Local<Value> obj = arr->Get(i);
					if(V8PxMaterial::getTemplate()->HasInstance(obj)){
						matBuffer[i] = unwrap<PxMaterial>(obj->ToObject());
					}
					else {
						free(matBuffer);
						return scope.Close( Undefined() );
					}
				}

				if(!args[2].IsEmpty() && args[2]->IsObject() && V8PxTransform::getTemplate()->HasInstance(args[2])){
					PxTransform* inPxTransform = unwrap<PxTransform>(args[2]->ToObject());

					PxShape* shape = thisPxRigidActor->createShape(*inPxGeometry, matBuffer, length, *inPxTransform);

					Persistent<Object> newPxShape = Persistent<Object>::New(Isolate::GetCurrent(),V8PxShape::getTemplate()->InstanceTemplate()->NewInstance());			
//					newPxShape.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupDelete);
					newPxShape->SetInternalField(0, External::New( shape ));

					free(matBuffer);

					return scope.Close( newPxShape );
				}
				else if(args[2].IsEmpty()) {
					PxShape* shape = thisPxRigidActor->createShape(*inPxGeometry, matBuffer, length);

					Persistent<Object> newPxShape = Persistent<Object>::New(Isolate::GetCurrent(),V8PxShape::getTemplate()->InstanceTemplate()->NewInstance());			
//					newPxShape.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupDelete);
					newPxShape->SetInternalField(0, External::New( shape ));

					free(matBuffer);

					return scope.Close( newPxShape );
				}
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidActor::getNbShapes(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxRigidActor* thisPxRigidActor = unwrap<PxRigidActor>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxRigidActor->getNbShapes()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidActor::getShapes(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxRigidActor* thisPxRigidActor = unwrap<PxRigidActor>(args.Holder());
			
			PxShape** newShapes = (PxShape**)malloc(sizeof(PxShape*)*thisPxRigidActor->getNbShapes());

			int numShapes = thisPxRigidActor->getShapes(newShapes, thisPxRigidActor->getNbShapes());

			Persistent<Array> newArray = Persistent<Array>::New(Isolate::GetCurrent(),Array::New(numShapes));
//			newArray.MakeWeak(Isolate::GetCurrent(),newShapes, &CleanupFree);
			
			for(int i = 0; i < numShapes; i++){
				Persistent<Object> newPxShape = Persistent<Object>::New(Isolate::GetCurrent(),V8PxShape::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxShape.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
				newPxShape->SetInternalField(0, External::New( newShapes[i] ));

				newArray->SetInternalField(i, newPxShape); 
			}

			return scope.Close(newArray);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidActor::getNbConstraints(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxRigidActor* thisPxRigidActor = unwrap<PxRigidActor>(args.Holder());
			
			return scope.Close( Uint32::New(thisPxRigidActor->getNbConstraints()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidActor::getConstraints(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxRigidActor* thisPxRigidActor = unwrap<PxRigidActor>(args.Holder());
			
			PxConstraint** newConstraints = (PxConstraint**)malloc(sizeof(PxConstraint*)*thisPxRigidActor->getNbConstraints());

			int numContraints = thisPxRigidActor->getConstraints(newConstraints, thisPxRigidActor->getNbConstraints());

			Persistent<Array> newArray = Persistent<Array>::New(Isolate::GetCurrent(),Array::New(numContraints));
//			newArray.MakeWeak(Isolate::GetCurrent(),newConstraints, &CleanupFree);
			
			for(int i = 0; i < numContraints; i++){
				Persistent<Object> newPxConstraint = Persistent<Object>::New(Isolate::GetCurrent(),V8PxConstraint::getTemplate()->InstanceTemplate()->NewInstance());			
//				newPxConstraint.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
				newPxConstraint->SetInternalField(0, External::New( newConstraints[i] ));

				newArray->SetInternalField(i, newPxConstraint); 
			}

			return scope.Close(newArray);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidActor::isRigidActor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

//PxRigidBody

	Handle<Value> V8PxRigidBody::setCMassLocalPose(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxTransform::getTemplate()->HasInstance(args[0])) 
        {
			PxRigidBody* thisPxRigidBody = unwrap<PxRigidBody>(args.Holder());
			PxTransform* inPose = unwrap<PxTransform>(args[0]->ToObject());

			thisPxRigidBody->setCMassLocalPose(*inPose);
			
			return scope.Close(args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidBody::getCMassLocalPose(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxRigidBody* thisPxRigidBody = unwrap<PxRigidBody>(args.Holder());
			PxTransform* transf = new PxTransform(thisPxRigidBody->getCMassLocalPose());

			Persistent<Object> newPxTransform = Persistent<Object>::New(Isolate::GetCurrent(),V8PxTransform::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxTransform.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupDelete);
			newPxTransform->SetInternalField(0, External::New( transf ));
			
			return scope.Close( newPxTransform );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidBody::setMass(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxRigidBody* thisPxRigidBody = unwrap<PxRigidBody>(args.Holder());

			thisPxRigidBody->setMass(args[0]->NumberValue());
			
			return scope.Close(args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidBody::getMass(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxRigidBody* thisPxRigidBody = unwrap<PxRigidBody>(args.Holder());
			
			return scope.Close( Number::New(thisPxRigidBody->getMass()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidBody::setMassSpaceInertiaTensor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxRigidBody* thisPxRigidBody = unwrap<PxRigidBody>(args.Holder());
			PxVec3* inVec3 = unwrap<PxVec3>(args[0]->ToObject());

			thisPxRigidBody->setMassSpaceInertiaTensor(*inVec3);
			
			return scope.Close(args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidBody::getMassSpaceInertiaTensor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxRigidBody* thisPxRigidBody = unwrap<PxRigidBody>(args.Holder());

			PxVec3* vec3 = new PxVec3(thisPxRigidBody->getMassSpaceInertiaTensor());

			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( vec3 ));
			
			return scope.Close( newPxVec3 );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidBody::getLinearVelocity(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxRigidBody* thisPxRigidBody = unwrap<PxRigidBody>(args.Holder());

			PxVec3* vec3 = new PxVec3(thisPxRigidBody->getLinearVelocity());

			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( vec3 ));
			
			return scope.Close( newPxVec3 );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidBody::setLinearVelocity(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxRigidBody* thisPxRigidBody = unwrap<PxRigidBody>(args.Holder());
			PxVec3* inVec3 = unwrap<PxVec3>(args[0]->ToObject());

			if(args.Length() == 1){
				thisPxRigidBody->setLinearVelocity(*inVec3);
				return scope.Close(args.Holder() );
			}
			else if(args.Length() == 2 && !args[1].IsEmpty() && args[1]->IsBoolean()){
				thisPxRigidBody->setLinearVelocity(*inVec3, args[1]->BooleanValue());
				return scope.Close(args.Holder() );
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidBody::getAngularVelocity(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxRigidBody* thisPxRigidBody = unwrap<PxRigidBody>(args.Holder());

			PxVec3* vec3 = new PxVec3(thisPxRigidBody->getAngularVelocity());

			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( vec3 ));
			
			return scope.Close( newPxVec3 );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidBody::setAngularVelocity(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxRigidBody* thisPxRigidBody = unwrap<PxRigidBody>(args.Holder());
			PxVec3* inVec3 = unwrap<PxVec3>(args[0]->ToObject());

			if(args.Length() == 1){
				thisPxRigidBody->setAngularVelocity(*inVec3);
				return scope.Close(args.Holder() );
			}
			else if(args.Length() == 2 && !args[1].IsEmpty() && args[1]->IsBoolean()){
				thisPxRigidBody->setAngularVelocity(*inVec3, args[1]->BooleanValue());
				return scope.Close(args.Holder() );
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidBody::addForce(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxRigidBody* thisPxRigidBody = unwrap<PxRigidBody>(args.Holder());
			PxVec3* inVec3 = unwrap<PxVec3>(args[0]->ToObject());

			if(args.Length() == 1){
				thisPxRigidBody->addForce(*inVec3);
				return scope.Close(args.Holder() );
			}
			else if(!args[1].IsEmpty() && args[1]->IsInt32()){
				if(args.Length() == 2){
					thisPxRigidBody->addForce(*inVec3, (PxForceMode::Enum)args[1]->Int32Value());
					return scope.Close(args.Holder() );
				}
				else if(args.Length() == 3 && !args[2].IsEmpty() && args[2]->IsBoolean()){
					thisPxRigidBody->addForce(*inVec3, (PxForceMode::Enum)args[1]->Int32Value(), args[2]->BooleanValue());
					return scope.Close(args.Holder() );
				}
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidBody::addTorque(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxRigidBody* thisPxRigidBody = unwrap<PxRigidBody>(args.Holder());
			PxVec3* inVec3 = unwrap<PxVec3>(args[0]->ToObject());

			if(args.Length() == 1){
				thisPxRigidBody->addTorque(*inVec3);
				return scope.Close(args.Holder() );
			}
			else if(!args[1].IsEmpty() && args[1]->IsInt32()){
				if(args.Length() == 2){
					thisPxRigidBody->addTorque(*inVec3, (PxForceMode::Enum)args[1]->Int32Value());
					return scope.Close(args.Holder() );
				}
				else if(args.Length() == 3 && !args[2].IsEmpty() && args[2]->IsBoolean()){
					thisPxRigidBody->addTorque(*inVec3, (PxForceMode::Enum)args[1]->Int32Value(), args[2]->BooleanValue());
					return scope.Close(args.Holder() );
				}
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidBody::clearForce(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0){
			PxRigidBody* thisPxRigidBody = unwrap<PxRigidBody>(args.Holder());
			thisPxRigidBody->clearForce();
			return scope.Close(args.Holder() );
		}
		else if(!args[0].IsEmpty() && args[0]->IsInt32()) {
			PxRigidBody* thisPxRigidBody = unwrap<PxRigidBody>(args.Holder());

			if(args.Length() == 1){
				thisPxRigidBody->clearForce((PxForceMode::Enum)args[0]->Int32Value());
				return scope.Close(args.Holder() );
			}
			else if(args.Length() == 2 && !args[1].IsEmpty() && args[1]->IsBoolean()){
				thisPxRigidBody->clearForce((PxForceMode::Enum)args[0]->Int32Value(), args[1]->BooleanValue());
				return scope.Close(args.Holder() );
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidBody::clearTorque(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0){
			PxRigidBody* thisPxRigidBody = unwrap<PxRigidBody>(args.Holder());
			thisPxRigidBody->clearTorque();

			return scope.Close(args.Holder() );
		}
		else if(!args[0].IsEmpty() && args[0]->IsInt32()) {
			PxRigidBody* thisPxRigidBody = unwrap<PxRigidBody>(args.Holder());

			if(args.Length() == 1){
				thisPxRigidBody->clearTorque((PxForceMode::Enum)args[0]->Int32Value());

				return scope.Close(args.Holder() );
			}
			else if(args.Length() == 2 && !args[1].IsEmpty() && args[1]->IsBoolean()){
				thisPxRigidBody->clearTorque((PxForceMode::Enum)args[0]->Int32Value(), args[1]->BooleanValue());

				return scope.Close(args.Holder() );
			}
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidBody::isRigidBody(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

//PxParticleBase

	Handle<Value> V8PxParticleBase::lockParticleReadData(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());
			PxParticleReadData* pReadData = thisPxParticleBase->lockParticleReadData();

			Persistent<Object> newPxParticleReadData = Persistent<Object>::New(Isolate::GetCurrent(),V8PxParticleReadData::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxParticleReadData.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupDelete);
			newPxParticleReadData->SetInternalField(0, External::New( pReadData ));
			
			return scope.Close( newPxParticleReadData );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::createParticles(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxParticleCreationData::getTemplate()->HasInstance(args[0])) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());
			PxParticleCreationData* cData = unwrap<PxParticleCreationData>(args[0]->ToObject());

			return scope.Close( Uint32::New(thisPxParticleBase->createParticles(*cData)) );
		}
		//else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxParticleCreationData::getTemplate()->HasInstance(args[0]) &&
		//						 !args[1].IsEmpty() && args[1]->IsArray()) 
		//{
		//	PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());
		//	PxParticleCreationData* cData = unwrap<PxParticleCreationData>(args[0]->ToObject());

		//	PxStrideIterator<PxU32> indexBuffer;

		//	PxU32 numWritten = thisPxParticleBase->createParticles(*cData, &indexBuffer);

		//	Local<Array> arr = Local<Array>::Cast(args[1]);

		//	arr->SetInternalField(0, Array::New(numWritten)); //hope this works

		//	for(int i = 0; i < numWritten; i++){
		//		//arr->SetInternalField(i, Uint32::New(indexBuffer[i]) );
		//		arr->Set(i, Uint32::New(indexBuffer[i]) );
		//	}

		//	return scope.Close( Uint32::New(numWritten) );
		//}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::releaseParticles(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsUint32() && !args[1].IsEmpty() && args[1]->IsArray()) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());

			Local<Array> arr = Local<Array>::Cast(args[0]);

			int len = arr->Length();

			PxU32* buff = (PxU32*)malloc(sizeof(PxU32)*len);

			Local<Value> temp;

			for(int i = 0; i < len; i++){
				temp = arr->Get(i);
				if(!arr->IsUint32()){
					free(buff);
					return ThrowException( Exception::TypeError( String::New("Array needs to be all type of Uint32.") ) );
				}
				buff[i] = temp->Uint32Value();
			}

			PxStrideIterator<PxU32> indexBuffer(buff);

			thisPxParticleBase->releaseParticles(args[0]->Uint32Value(), indexBuffer);

			free(buff);

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::setPositions(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsUint32() &&
								 !args[1].IsEmpty() && args[1]->IsArray() &&
								 !args[2].IsEmpty() && args[2]->IsArray()) 
		{
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());

			Local<Value> temp;

			Local<Array> arr = Local<Array>::Cast(args[1]);
			int len = arr->Length();
			PxU32* buff = (PxU32*)malloc(sizeof(PxU32)*len);
			for(int i = 0; i < len; i++){
				temp = arr->Get(i);
				if(!arr->IsUint32()){
					free(buff);
					return ThrowException( Exception::TypeError( String::New("Array needs to be all type of Uint32.") ) );
				}
				buff[i] = temp->Uint32Value();
			}
			PxStrideIterator<PxU32> indexBuffer(buff);

			arr = Local<Array>::Cast(args[2]);
			len = arr->Length();
			PxVec3* vecBuff = (PxVec3*)malloc(sizeof(PxVec3)*len);
			for(int i = 0; i < len; i++){
				temp = arr->Get(i);
				if(!arr->IsUint32()){
					free(buff);
					free(vecBuff);
					return ThrowException( Exception::TypeError( String::New("Array needs to be all type of PxVec3.") ) );
				}
				vecBuff[i] = *unwrap<PxVec3>(temp->ToObject());
			}
			PxStrideIterator<PxVec3> positionBuffer(vecBuff);

			thisPxParticleBase->setPositions(args[0]->Uint32Value(), indexBuffer, positionBuffer);

			free(buff);
			free(vecBuff);

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::setVelocities(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsUint32() &&
								 !args[1].IsEmpty() && args[1]->IsArray() &&
								 !args[2].IsEmpty() && args[2]->IsArray()) 
		{
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());

			Local<Value> temp;

			Local<Array> arr = Local<Array>::Cast(args[1]);
			int len = arr->Length();
			PxU32* buff = (PxU32*)malloc(sizeof(PxU32)*len);
			for(int i = 0; i < len; i++){
				temp = arr->Get(i);
				if(!arr->IsUint32()){
					free(buff);
					return ThrowException( Exception::TypeError( String::New("Array needs to be all type of Uint32.") ) );
				}
				buff[i] = temp->Uint32Value();
			}
			PxStrideIterator<PxU32> indexBuffer(buff);

			arr = Local<Array>::Cast(args[2]);
			len = arr->Length();
			PxVec3* vecBuff = (PxVec3*)malloc(sizeof(PxVec3)*len);
			for(int i = 0; i < len; i++){
				temp = arr->Get(i);
				if(!arr->IsUint32()){
					free(buff);
					free(vecBuff);
					return ThrowException( Exception::TypeError( String::New("Array needs to be all type of PxVec3.") ) );
				}
				vecBuff[i] = *unwrap<PxVec3>(temp->ToObject());
			}
			PxStrideIterator<PxVec3> velocityBuffer(vecBuff);

			thisPxParticleBase->setVelocities(args[0]->Uint32Value(), indexBuffer, velocityBuffer);

			free(buff);
			free(vecBuff);

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::setRestOffsets(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 3 && !args[0].IsEmpty() && args[0]->IsUint32() &&
								 !args[1].IsEmpty() && args[1]->IsArray() &&
								 !args[2].IsEmpty() && args[2]->IsArray()) 
		{
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());

			Local<Value> temp;

			Local<Array> arr = Local<Array>::Cast(args[1]);
			int len = arr->Length();
			PxU32* buff = (PxU32*)malloc(sizeof(PxU32)*len);
			for(int i = 0; i < len; i++){
				temp = arr->Get(i);
				if(!arr->IsUint32()){
					free(buff);
					return ThrowException( Exception::TypeError( String::New("Array needs to be all type of Uint32.") ) );
				}
				buff[i] = temp->Uint32Value();
			}
			PxStrideIterator<PxU32> indexBuffer(buff);

			arr = Local<Array>::Cast(args[2]);
			len = arr->Length();
			PxF32* fBuff = (PxF32*)malloc(sizeof(PxF32)*len);
			for(int i = 0; i < len; i++){
				temp = arr->Get(i);
				if(!arr->IsUint32()){
					free(buff);
					free(fBuff);
					return ThrowException( Exception::TypeError( String::New("Array needs to be all type of Number.") ) );
				}
				fBuff[i] = temp->NumberValue();
			}
			PxStrideIterator<PxF32> restOffsetBuffer(fBuff);

			thisPxParticleBase->setRestOffsets(args[0]->Uint32Value(), indexBuffer, restOffsetBuffer);

			free(buff);
			free(fBuff);

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::addForces(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 4 && !args[0].IsEmpty() && args[0]->IsUint32() &&
								 !args[1].IsEmpty() && args[1]->IsArray() &&
								 !args[2].IsEmpty() && args[2]->IsArray() &&
								 !args[2].IsEmpty() && args[3]->IsInt32()) 
		{
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());

			Local<Value> temp;

			Local<Array> arr = Local<Array>::Cast(args[1]);
			int len = arr->Length();
			PxU32* buff = (PxU32*)malloc(sizeof(PxU32)*len);
			for(int i = 0; i < len; i++){
				temp = arr->Get(i);
				if(!arr->IsUint32()){
					free(buff);
					return ThrowException( Exception::TypeError( String::New("Array needs to be all type of Uint32.") ) );
				}
				buff[i] = temp->Uint32Value();
			}
			PxStrideIterator<PxU32> indexBuffer(buff);

			arr = Local<Array>::Cast(args[2]);
			len = arr->Length();
			PxVec3* vecBuff = (PxVec3*)malloc(sizeof(PxVec3)*len);
			for(int i = 0; i < len; i++){
				temp = arr->Get(i);
				if(!arr->IsUint32()){
					free(buff);
					free(vecBuff);
					return ThrowException( Exception::TypeError( String::New("Array needs to be all type of PxVec3.") ) );
				}
				vecBuff[i] = *unwrap<PxVec3>(temp->ToObject());
			}
			PxStrideIterator<PxVec3> forceBuffer(vecBuff);

			thisPxParticleBase->addForces(args[0]->Uint32Value(), indexBuffer, forceBuffer, (PxForceMode::Enum)args[3]->Int32Value());

			free(buff);
			free(vecBuff);

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::getDamping(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());
			
			return scope.Close( Number::New(thisPxParticleBase->getDamping()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::setDamping(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());

			thisPxParticleBase->setDamping( args[0]->NumberValue() );
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::getExternalAcceleration(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());

			PxVec3* vecObj = new PxVec3(thisPxParticleBase->getExternalAcceleration());

			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( vecObj ));
			
			return scope.Close( newPxVec3 );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::setExternalAcceleration(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());

			PxVec3* acceleration = unwrap<PxVec3>(args[0]->ToObject());

			thisPxParticleBase->setExternalAcceleration( *acceleration );
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::getProjectionPlane(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());

			PxVec3 normal;
			PxReal distance;

			thisPxParticleBase->getProjectionPlane(normal, distance);


			Persistent<Object> newPxVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxVec3.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupDelete);
			newPxVec3->SetInternalField(0, External::New( new PxVec3(normal) ));

			Local<Array> returnArray = Array::New(2);

			returnArray->Set(0, newPxVec3);
			returnArray->Set(1, Number::New(distance));
			
			return scope.Close( returnArray );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::setProjectionPlane(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0]) && !args[1].IsEmpty() && args[1]->IsNumber()) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());

			PxVec3* normal = unwrap<PxVec3>(args[0]->ToObject());

			thisPxParticleBase->setProjectionPlane( *normal, args[1]->NumberValue() );
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::getParticleMass(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());
			
			return scope.Close( Number::New(thisPxParticleBase->getParticleMass()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::setParticleMass(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());

			thisPxParticleBase->setParticleMass( args[0]->NumberValue() );
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::getRestitution(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());
			
			return scope.Close( Number::New(thisPxParticleBase->getRestitution()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::setRestitution(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());

			thisPxParticleBase->setRestitution( args[0]->NumberValue() );
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::getDynamicFriction(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());
			
			return scope.Close( Number::New(thisPxParticleBase->getDynamicFriction()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::setDynamicFriction(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());

			thisPxParticleBase->setDynamicFriction( args[0]->NumberValue() );
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::getStaticFriction(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());
			
			return scope.Close( Number::New(thisPxParticleBase->getStaticFriction()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::setStaticFriction(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());

			thisPxParticleBase->setStaticFriction( args[0]->NumberValue() );
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::setSimulationFilterData(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxFilterData::getTemplate()->HasInstance(args[0])) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());
			PxFilterData* inFData = unwrap<PxFilterData>(args[0]->ToObject());

			thisPxParticleBase->setSimulationFilterData( *inFData );
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::getSimulationFilterData(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());

			PxFilterData dataObj = thisPxParticleBase->getSimulationFilterData();

			Persistent<Object> newPxFilterData = Persistent<Object>::New(Isolate::GetCurrent(),V8PxFilterData::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxFilterData.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxFilterData->SetInternalField(0, External::New( &dataObj ));
			
			return scope.Close( newPxFilterData );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::resetFiltering(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());

			thisPxParticleBase->resetFiltering();
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::setParticleBaseFlag(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsUint32() && !args[1].IsEmpty() && args[1]->IsBoolean()) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());

			thisPxParticleBase->setParticleBaseFlag( (PxParticleBaseFlag::Enum)args[0]->Uint32Value(), args[1]->BooleanValue() );
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::getParticleBaseFlags(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());
			
			return scope.Close( Uint32::New( (PxU32)thisPxParticleBase->getParticleBaseFlags() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::getMaxParticles(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());
			
			return scope.Close( Uint32::New( thisPxParticleBase->getMaxParticles() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::getMaxMotionDistance(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());
			
			return scope.Close( Number::New( thisPxParticleBase->getMaxMotionDistance() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::getRestOffset(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());
			
			return scope.Close( Number::New( thisPxParticleBase->getRestOffset() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::getContactOffset(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());
			
			return scope.Close( Number::New( thisPxParticleBase->getContactOffset() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::getGridSize(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());
			
			return scope.Close( Number::New( thisPxParticleBase->getGridSize() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::getParticleReadDataFlags(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleBase* thisPxParticleBase = unwrap<PxParticleBase>(args.Holder());
			
			return scope.Close( Uint32::New( (PxU32)thisPxParticleBase->getParticleReadDataFlags() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleBase::isParticleBase(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

//PxLockedData

	Handle<Value> V8PxLockedData::getDataAccessFlags(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxLockedData* thisPxLockedData = unwrap<PxLockedData>(args.Holder());
			
			return scope.Close( Uint32::New((PxU32)thisPxLockedData->getDataAccessFlags()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxLockedData::unlock(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxLockedData* thisPxLockedData = unwrap<PxLockedData>(args.Holder());
			
			thisPxLockedData->unlock();

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

//PxStrideIterator

	template<class T>
	Handle<Value> V8PxStrideIterator<T>::handle(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxStrideIterator<T>* thisPxStrideIterator = unwrap<PxStrideIterator<T>>(args.Holder());
			args.Data()->ToObject()->SetInternalField(0, External::New( &(**thisPxStrideIterator) ));

			return scope.Close( args.Data() );
		}

		return scope.Close( Undefined() );
	}

	template<class T>
	Handle<Value> V8PxStrideIterator<T>::unique(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxStrideIterator<T>* thisPxStrideIterator = unwrap<PxStrideIterator<T>>(args.Holder());
			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),args.Data()->ToObject()->Clone());
//			obj.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			obj->SetInternalField(0, External::New( &(**thisPxStrideIterator) ));

			return scope.Close( obj );
		}

		return scope.Close( Undefined() );
	}

	template<class T>
	Handle<Value> V8PxStrideIterator<T>::stride(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxStrideIterator<T>* thisPxStrideIterator = unwrap<PxStrideIterator<T>>(args.Holder());

			return scope.Close( Uint32::New( thisPxStrideIterator->stride() )  );
		}

		return scope.Close( Undefined() );
	}

	template<class T>
	Handle<Value> V8PxStrideIterator<T>::next(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsInt32()) {
			PxStrideIterator<T>* thisPxStrideIterator = unwrap<PxStrideIterator<T>>(args.Holder());
			(*thisPxStrideIterator)++;
			args.Data()->ToObject()->SetInternalField(0, External::New( &(**thisPxStrideIterator) ));

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	template<class T>
	Handle<Value> V8PxStrideIterator<T>::prev(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsInt32()) {
			PxStrideIterator<T>* thisPxStrideIterator = unwrap<PxStrideIterator<T>>(args.Holder());
			(*thisPxStrideIterator)--;
			args.Data()->ToObject()->SetInternalField(0, External::New( &(**thisPxStrideIterator) ));

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	template<class T>
	Handle<Value> V8PxStrideIterator<T>::jump(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsInt32()) {
			PxStrideIterator<T>* thisPxStrideIterator = unwrap<PxStrideIterator<T>>(args.Holder());
			(*thisPxStrideIterator) += args[0]->Int32Value();
			args.Data()->ToObject()->SetInternalField(0, External::New( &(**thisPxStrideIterator) ));

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

//PxParticleReadData

	Handle<Value> V8PxParticleReadData::getNumValidParticles( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxParticleReadData* thisPxParticleReadData = unwrap<PxParticleReadData>(info.Holder());
		return scope.Close( Uint32::New( thisPxParticleReadData->numValidParticles ));
	}

	void V8PxParticleReadData::setNumValidParticles( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsUint32()){
			PxParticleReadData* thisPxParticleReadData = unwrap<PxParticleReadData>(info.Holder());

			thisPxParticleReadData->numValidParticles = value->Uint32Value();
		}
	}

	Handle<Value> V8PxParticleReadData::getValidParticleRange( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxParticleReadData* thisPxParticleReadData = unwrap<PxParticleReadData>(info.Holder());
		return scope.Close( Uint32::New( thisPxParticleReadData->validParticleRange ));
	}

	void V8PxParticleReadData::setValidParticleRange( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsUint32()){
			PxParticleReadData* thisPxParticleReadData = unwrap<PxParticleReadData>(info.Holder());

			thisPxParticleReadData->validParticleRange = value->Uint32Value();
		}
	}

	Handle<Value> V8PxParticleReadData::getValidParticleBitmap( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxParticleReadData* thisPxParticleReadData = unwrap<PxParticleReadData>(info.Holder());
		return scope.Close( Uint32::New( *(thisPxParticleReadData->validParticleBitmap) ));
	}

	/*void V8PxParticleReadData::setValidParticleBitmap( Local<String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsUint32()){
			PxParticleReadData* thisPxParticleReadData = unwrap<PxParticleReadData>(info.Holder());

			thisPxParticleReadData->validParticleRange = value->Uint32Value();
		}
	}*/

	Handle<Value> V8PxParticleReadData::getPositionBuffer( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(info.Data().IsEmpty()){
			PxParticleReadData* thisPxParticleReadData = unwrap<PxParticleReadData>(info.Holder());

			Persistent<Object> newPxStrideIterator = Persistent<Object>::New(Isolate::GetCurrent(),V8PxStrideIterator<PxVec3>::getTemplate()->InstanceTemplate()->NewInstance());
//			newPxStrideIterator.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxStrideIterator->SetInternalField(0, External::New( &(thisPxParticleReadData->positionBuffer) ));

			Persistent<Object> newDataObj = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());
//			newDataObj.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newDataObj->SetInternalField(0, External::New( &(PxVec3)(*(thisPxParticleReadData->positionBuffer)) ));

			V8PxStrideIterator<PxVec3>::initObject(newPxStrideIterator, newDataObj);

			info.Holder()->SetAccessor(String::New("positionBuffer"), V8PxParticleReadData::getPositionBuffer, NULL, newPxStrideIterator);

			return scope.Close( newPxStrideIterator );
		}
		else {
			return scope.Close( info.Data() );
		}
	}

	Handle<Value> V8PxParticleReadData::getVelocityBuffer( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(info.Data().IsEmpty()){
			PxParticleReadData* thisPxParticleReadData = unwrap<PxParticleReadData>(info.Holder());

			Persistent<Object> newPxStrideIterator = Persistent<Object>::New(Isolate::GetCurrent(),V8PxStrideIterator<PxVec3>::getTemplate()->InstanceTemplate()->NewInstance());
//			newPxStrideIterator.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxStrideIterator->SetInternalField(0, External::New( &(thisPxParticleReadData->velocityBuffer) ));

			Persistent<Object> newDataObj = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());
//			newDataObj.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newDataObj->SetInternalField(0, External::New( &(PxVec3)(*(thisPxParticleReadData->velocityBuffer)) ));

			V8PxStrideIterator<PxVec3>::initObject(newPxStrideIterator, newDataObj);

			info.Holder()->SetAccessor(String::New("velocityBuffer"), V8PxParticleReadData::getVelocityBuffer, NULL, newPxStrideIterator);

			return scope.Close( newPxStrideIterator );
		}
		else {
			return scope.Close( info.Data() );
		}
	}

	Handle<Value> V8PxParticleReadData::getRestOffsetBuffer( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(info.Data().IsEmpty()){
			PxParticleReadData* thisPxParticleReadData = unwrap<PxParticleReadData>(info.Holder());

			Persistent<Object> newPxStrideIterator = Persistent<Object>::New(Isolate::GetCurrent(),V8PxStrideIterator<PxF32>::getTemplate()->InstanceTemplate()->NewInstance());
//			newPxStrideIterator.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxStrideIterator->SetInternalField(0, External::New( &(thisPxParticleReadData->restOffsetBuffer) ));

			Handle<Number> newDataObj = Number::New( (*(thisPxParticleReadData->restOffsetBuffer)) ); //wonder how long this will live, it should live persistently...

			V8PxStrideIterator<PxF32>::initObject(newPxStrideIterator, newDataObj->ToObject());

			info.Holder()->SetAccessor(String::New("restOffsetBuffer"), V8PxParticleReadData::getRestOffsetBuffer, NULL, newPxStrideIterator);

			return scope.Close( newPxStrideIterator );
		}
		else {
			return scope.Close( info.Data() );
		}
	}

	Handle<Value> V8PxParticleReadData::getFlagsBuffer( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(info.Data().IsEmpty()){
			PxParticleReadData* thisPxParticleReadData = unwrap<PxParticleReadData>(info.Holder());

			Persistent<Object> newPxStrideIterator = Persistent<Object>::New(Isolate::GetCurrent(),V8PxStrideIterator<PxParticleFlags>::getTemplate()->InstanceTemplate()->NewInstance());
//			newPxStrideIterator.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxStrideIterator->SetInternalField(0, External::New( &(thisPxParticleReadData->flagsBuffer) ));

			Handle<Integer> newDataObj = Uint32::New( (PxU32)(*(thisPxParticleReadData->flagsBuffer)) );

			V8PxStrideIterator<PxParticleFlags>::initObject(newPxStrideIterator, newDataObj->ToObject());

			info.Holder()->SetAccessor(String::New("flagsBuffer"), V8PxParticleReadData::getFlagsBuffer, NULL, newPxStrideIterator);

			return scope.Close( newPxStrideIterator );
		}
		else {
			return scope.Close( info.Data() );
		}
	}

	Handle<Value> V8PxParticleReadData::getCollisionNormalBuffer( Local<String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(info.Data().IsEmpty()){
			PxParticleReadData* thisPxParticleReadData = unwrap<PxParticleReadData>(info.Holder());

			if(thisPxParticleReadData->collisionNormalBuffer.ptr() != NULL){
				Persistent<Object> newPxStrideIterator = Persistent<Object>::New(Isolate::GetCurrent(),V8PxStrideIterator<PxVec3>::getTemplate()->InstanceTemplate()->NewInstance());
//				newPxStrideIterator.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
				newPxStrideIterator->SetInternalField(0, External::New( &(thisPxParticleReadData->collisionNormalBuffer) ));

				Persistent<Object> newDataObj = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());
//				newDataObj.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
				newDataObj->SetInternalField(0, External::New( &(PxVec3)(*(thisPxParticleReadData->collisionNormalBuffer)) ));

				V8PxStrideIterator<PxVec3>::initObject(newPxStrideIterator, newDataObj);

				info.Holder()->SetAccessor(String::New("collisionNormalBuffer"), V8PxParticleReadData::getCollisionNormalBuffer, NULL, newPxStrideIterator);

				return scope.Close( newPxStrideIterator );
			}
			else {
				return scope.Close( Undefined() );
			}
		}
		else {
			return scope.Close( info.Data() );
		}
	}

	Handle<Value> V8PxParticleReadData::getDataAccessFlags(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleReadData* thisPxParticleReadData = unwrap<PxParticleReadData>(args.Holder());
			
			return scope.Close( Uint32::New((PxU32)thisPxParticleReadData->getDataAccessFlags()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxParticleReadData::unlock(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxParticleReadData* thisPxParticleReadData = unwrap<PxParticleReadData>(args.Holder());
			
			thisPxParticleReadData->unlock();

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

//PxRigidDynamic
	Handle<Value> V8PxRigidDynamic::setKinematicTarget(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxTransform::getTemplate()->HasInstance(args[0])) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());
			
			thisrigid->setKinematicTarget(*unwrap<PxTransform>(args[0]->ToObject()));

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidDynamic::getKinematicTarget(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxTransform::getTemplate()->HasInstance(args[0])) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());

			return scope.Close( Boolean::New( thisrigid->getKinematicTarget(*unwrap<PxTransform>(args[0]->ToObject())) ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidDynamic::setLinearDamping(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());
			
			thisrigid->setLinearDamping(args[0]->NumberValue());

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidDynamic::getLinearDamping(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());

			return scope.Close( Number::New( thisrigid->getLinearDamping() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidDynamic::setAngularDamping(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());
			
			thisrigid->setAngularDamping(args[0]->NumberValue());

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidDynamic::getAngularDamping(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());

			return scope.Close( Number::New( thisrigid->getAngularDamping() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidDynamic::setMaxAngularVelocity(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());
			
			thisrigid->setMaxAngularVelocity(args[0]->NumberValue());

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidDynamic::getMaxAngularVelocity(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());

			return scope.Close( Number::New( thisrigid->getMaxAngularVelocity() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidDynamic::isSleeping(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());

			return scope.Close( Boolean::New( thisrigid->isSleeping() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidDynamic::setSleepThreshold(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());
			
			thisrigid->setSleepThreshold(args[0]->NumberValue());

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidDynamic::getSleepThreshold(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());

			return scope.Close( Number::New( thisrigid->getSleepThreshold() ) );
		}

		return scope.Close( Undefined() );
	}


	Handle<Value> V8PxRigidDynamic::wakeUp(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());


		if(args.Length() == 0) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());
			
			thisrigid->wakeUp();

			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());
			
			thisrigid->wakeUp(args[0]->NumberValue());

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidDynamic::putToSleep(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());
			
			thisrigid->putToSleep();

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}
	
	Handle<Value> V8PxRigidDynamic::setSolverIterationCounts(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());
		
		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32()) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());
			
			thisrigid->setSolverIterationCounts(args[0]->Uint32Value());

			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsUint32()
			&& !args[1].IsEmpty() && args[1]->IsUint32()) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());
			
			thisrigid->setSolverIterationCounts(args[0]->Uint32Value(), args[1]->Uint32Value());

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidDynamic::getSolverIterationCounts(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());
		
		//TODO: Fix this
		/*if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsUint32()
			&& !args[1].IsEmpty() && args[1]->IsUint32()) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());

			PxU32 first, second;
			
			thisrigid->getSolverIterationCounts(first, second);

			return scope.Close( args.Holder() );
		}*/

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidDynamic::getContactReportThreshold(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());

			return scope.Close( Number::New( thisrigid->getContactReportThreshold() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidDynamic::setContactReportThreshold(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());
			
			thisrigid->setContactReportThreshold(args[0]->NumberValue());

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidDynamic::setRigidDynamicFlag(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsUint32() &&
			!args[1].IsEmpty() && args[1]->IsBoolean()) 
        {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());

			thisrigid->setRigidDynamicFlag((PxRigidDynamicFlag::Enum )args[0]->Uint32Value(), args[1]->BooleanValue());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidDynamic::setRigidDynamicFlags(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsInt32()) 
        {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());

			thisrigid->setRigidDynamicFlags(PxRigidDynamicFlags(args[0]->Int32Value()));
			
			return scope.Close(args.Holder());
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidDynamic::getRigidDynamicFlags(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());
			
			return scope.Close( Uint32::New((PxU32)thisrigid->getRigidDynamicFlags()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRigidDynamic::getConcreteTypeName(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxRigidDynamic* thisrigid = unwrap<PxRigidDynamic>(args.Holder());
			
			return scope.Close( v8::String::New(thisrigid->getConcreteTypeName()) );
		}

		return scope.Close( Undefined() );
	}

//PxRigidStatic
	Handle<Value> V8PxRigidStatic::getConcreteTypeName(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxRigidStatic* thisrigid = unwrap<PxRigidStatic>(args.Holder());
			
			return scope.Close( v8::String::New(thisrigid->getConcreteTypeName()) );
		}

		return scope.Close( Undefined() );
	}

//PxScene
	Handle<Value> V8PxScene::release(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxScene* thisScene = unwrap<PxScene>(args.Holder());

			thisScene->release();
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxScene::setFlag(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsUint32() &&
			!args[1].IsEmpty() && args[1]->IsBoolean()) 
        {
			PxScene* thisScene = unwrap<PxScene>(args.Holder());

			thisScene->setFlag((PxSceneFlag::Enum )args[0]->Uint32Value(), args[1]->BooleanValue());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxScene::getFlags(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxScene* thisScene = unwrap<PxScene>(args.Holder());
			
			return scope.Close( Uint32::New((PxU32)thisScene->getFlags()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxScene::setGravity(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxScene* thisScene = unwrap<PxScene>(args.Holder());

			thisScene->setGravity(*unwrap<PxVec3>(args[0]->ToObject()));
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxScene::getGravity(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxScene* thisScene = unwrap<PxScene>(args.Holder());

			PxVec3* newVal = new PxVec3( thisScene->getGravity() );

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder() );
//			obj.MakeWeak(Isolate::GetCurrent(),newVal, &CleanupDelete);
			obj->SetInternalField(0, External::New( newVal ));
			
			return scope.Close( obj );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxScene::getTimestamp(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxScene* thisScene = unwrap<PxScene>(args.Holder());

			
			return scope.Close( Uint32::New( thisScene->getTimestamp() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxScene::getSceneQueryStaticTimestamp(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxScene* thisScene = unwrap<PxScene>(args.Holder());

			
			return scope.Close( Uint32::New( thisScene->getSceneQueryStaticTimestamp() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxScene::setBounceThresholdVelocity(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxScene* thisScene = unwrap<PxScene>(args.Holder());

			thisScene->setBounceThresholdVelocity(args[0]->NumberValue());
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxScene::getBounceThresholdVelocity(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxScene* thisScene = unwrap<PxScene>(args.Holder());
			
			return scope.Close( Number::New(thisScene->getBounceThresholdVelocity()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxScene::addActor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxActor::getTemplate()->HasInstance(args[0])) 
        {
			PxScene* thisScene = unwrap<PxScene>(args.Holder());

			thisScene->addActor(*unwrap<PxActor>(args[0]->ToObject()));
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxScene::removeActor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxActor::getTemplate()->HasInstance(args[0])) 
        {
			PxScene* thisScene = unwrap<PxScene>(args.Holder());

			thisScene->removeActor(*unwrap<PxActor>(args[0]->ToObject()));
			
			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxScene::raycastAny(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 4 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])
			&& !args[1].IsEmpty() && args[1]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[1])
			&& !args[2].IsEmpty() && args[2]->IsNumber()
			&& !args[3].IsEmpty() && args[3]->IsObject() && V8PxSceneQueryHit::getTemplate()->HasInstance(args[3])) 
        {
			PxScene* thisScene = unwrap<PxScene>(args.Holder());
			
			return scope.Close( Boolean::New( thisScene->raycastAny(	*unwrap<PxVec3>(args[0]->ToObject()),
									*unwrap<PxVec3>(args[1]->ToObject()),
									args[2]->NumberValue(),
									*unwrap<PxSceneQueryHit>(args[3]->ToObject())
									) ));
		}
		else if(args.Length() == 5 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])
			&& !args[1].IsEmpty() && args[1]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[1])
			&& !args[2].IsEmpty() && args[2]->IsNumber()
			&& !args[3].IsEmpty() && args[3]->IsObject() && V8PxSceneQueryHit::getTemplate()->HasInstance(args[3])
			&& !args[4].IsEmpty() && args[4]->IsObject() && V8PxSceneQueryFilterData::getTemplate()->HasInstance(args[4])) 
        {
			PxScene* thisScene = unwrap<PxScene>(args.Holder());
			
			return scope.Close( Boolean::New( thisScene->raycastAny(	*unwrap<PxVec3>(args[0]->ToObject()),
									*unwrap<PxVec3>(args[1]->ToObject()),
									args[2]->NumberValue(),
									*unwrap<PxSceneQueryHit>(args[3]->ToObject()),
									*unwrap<PxSceneQueryFilterData>(args[4]->ToObject())
									) ));
		}

		//TODO: Add other types

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxScene::raycastSingle(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 5 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])
			&& !args[1].IsEmpty() && args[1]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[1])
			&& !args[2].IsEmpty() && args[2]->IsNumber()
			&& !args[3].IsEmpty() && args[3]->IsUint32()
			&& !args[4].IsEmpty() && args[4]->IsObject() && V8PxRaycastHit::getTemplate()->HasInstance(args[4])
			&& !args[5].IsEmpty() && args[5]->IsObject() && V8PxSceneQueryFilterData::getTemplate()->HasInstance(args[5]))
        {
			PxScene* thisScene = unwrap<PxScene>(args.Holder());
			
			return scope.Close( Boolean::New( thisScene->raycastSingle(	*unwrap<PxVec3>(args[0]->ToObject()),
									*unwrap<PxVec3>(args[1]->ToObject()),
									args[2]->NumberValue(),
									(PxSceneQueryFlags)args[3]->Uint32Value(),
									*unwrap<PxRaycastHit>(args[4]->ToObject())
									) ));
		}
		else if(args.Length() == 6 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])
			&& !args[1].IsEmpty() && args[1]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[1])
			&& !args[2].IsEmpty() && args[2]->IsNumber()
			&& !args[3].IsEmpty() && args[3]->IsUint32()
			&& !args[4].IsEmpty() && args[4]->IsObject() && V8PxRaycastHit::getTemplate()->HasInstance(args[4])) 
        {
			PxScene* thisScene = unwrap<PxScene>(args.Holder());
			
			return scope.Close( Boolean::New( thisScene->raycastSingle(	*unwrap<PxVec3>(args[0]->ToObject()),
									*unwrap<PxVec3>(args[1]->ToObject()),
									args[2]->NumberValue(),
									(PxSceneQueryFlags)args[3]->Uint32Value(),
									*unwrap<PxRaycastHit>(args[4]->ToObject()),
									*unwrap<PxSceneQueryFilterData>(args[5]->ToObject())
									) ));
		}

		//TODO: Add other types

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxScene::raycastMultiple(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		//TODO: Finish this
		//if(args.Length() == 4 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0])
		//	&& !args[1].IsEmpty() && args[1]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[1])
		//	&& !args[2].IsEmpty() && args[2]->IsNumber()
		//	&& !args[3].IsEmpty() && args[3]->IsUint32())
  //      {
		//	PxScene* thisScene = unwrap<PxScene>(args.Holder());

		//	//Handle<Array> arr = Handle<Array>::New();

		//	PxI32 num = thisScene->raycastMultiple(	*unwrap<PxVec3>(args[0]->ToObject()),
		//							*unwrap<PxVec3>(args[1]->ToObject()),
		//							args[2]->NumberValue(),
		//							(PxSceneQueryFlags)args[3]->Uint32Value(),
		//							*unwrap<PxRaycastHit>(args[4]->ToObject())
		//							);
		//	
		//	return scope.Close( );
		//}

		//TODO: Add other types

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxScene::sweepAny(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		//TODO: Finish this

		//TODO: Add other typesv8stringCreate

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxScene::sweepSingle(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		//TODO: Finish this

		//TODO: Add other types

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxScene::sweepMultiple(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		//TODO: Finish this

		//TODO: Add other types

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxScene::overlapMultiple(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		//TODO: Finish this

		//TODO: Add other types

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxScene::overlapAny(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		//TODO: Finish this

		//TODO: Add other types

		return scope.Close( Undefined() );
	}

//PxSceneQueryHit

	Handle<Value> V8PxSceneQueryHit::V8PxSceneQueryHitConstructor(const Arguments& args){
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0) 
        {
			PxSceneQueryHit* val = new PxSceneQueryHit();

			Persistent<Object> newObj = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder());			
//			newObj.MakeWeak(Isolate::GetCurrent(),val, &CleanupDelete);
			newObj->SetInternalField(0, External::New(val));
			
			return scope.Close(newObj);
		}
		else if( args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && templ->HasInstance(args[0])){
			PxSceneQueryHit* val = new PxSceneQueryHit(*unwrap<PxSceneQueryHit>(args[0]->ToObject()));

			Persistent<Object> newObj = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder());			
//			newObj.MakeWeak(Isolate::GetCurrent(),val, &CleanupDelete);
			newObj->SetInternalField(0, External::New(val));
			
			return scope.Close(newObj);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxSceneQueryHit::getShape(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxSceneQueryHit* thisHit = unwrap<PxSceneQueryHit>(args.Holder());

			Persistent<Object> newPxShape = Persistent<Object>::New(Isolate::GetCurrent(),V8PxShape::getTemplate()->InstanceTemplate()->NewInstance());			
//			newPxShape.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
			newPxShape->SetInternalField(0, External::New(&*thisHit->shape));
			
			return scope.Close(newPxShape);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxSceneQueryHit::getFaceIndex(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxSceneQueryHit* thisHit = unwrap<PxSceneQueryHit>(args.Holder());
			
			return scope.Close( Uint32::New( thisHit->faceIndex ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxSceneQueryHit::getFlags(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxSceneQueryHit* thisHit = unwrap<PxSceneQueryHit>(args.Holder());
			
			return scope.Close( Integer::New( PxU32(thisHit->flags) ) );
		}

		return scope.Close( Undefined() );
	}

//PxSceneQueryImpactHit

	Handle<Value> V8PxSceneQueryImpactHit::V8PxSceneQueryImpactHitConstructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0) 
        {
			PxSceneQueryImpactHit* val = new PxSceneQueryImpactHit();

			Persistent<Object> newObj = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder());			
//			newObj.MakeWeak(Isolate::GetCurrent(),val, &CleanupDelete);
			newObj->SetInternalField(0, External::New(val));
			
			return scope.Close(newObj);
		}
		else if( args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && templ->HasInstance(args[0])){
			PxSceneQueryImpactHit* val = new PxSceneQueryImpactHit(*unwrap<PxSceneQueryImpactHit>(args[0]->ToObject()));

			Persistent<Object> newObj = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder());			
//			newObj.MakeWeak(Isolate::GetCurrent(),val, &CleanupDelete);
			newObj->SetInternalField(0, External::New(val));
			
			return scope.Close(newObj);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxSceneQueryImpactHit::getImpact(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxSceneQueryImpactHit* thisHit = unwrap<PxSceneQueryImpactHit>(args.Holder());

			PxVec3* newVal = new PxVec3(thisHit->impact);

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			obj.MakeWeak(Isolate::GetCurrent(),newVal, &CleanupDelete);
			obj->SetInternalField(0, External::New(newVal));
			
			return scope.Close(obj);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxSceneQueryImpactHit::getNormal(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxSceneQueryImpactHit* thisHit = unwrap<PxSceneQueryImpactHit>(args.Holder());

			PxVec3* newVal = new PxVec3(thisHit->normal);

			Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),V8PxVec3::getTemplate()->InstanceTemplate()->NewInstance());			
//			obj.MakeWeak(Isolate::GetCurrent(),newVal, &CleanupDelete);
			obj->SetInternalField(0, External::New(newVal));
			
			return scope.Close(obj);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxSceneQueryImpactHit::getDistance(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxSceneQueryImpactHit* thisHit = unwrap<PxSceneQueryImpactHit>(args.Holder());
			
			return scope.Close( Number::New( thisHit->distance ) );
		}

		return scope.Close( Undefined() );
	}

//PxRaycastHit

	Handle<Value> V8PxRaycastHit::V8PxRaycastHitConstructor(const Arguments& args){
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0) 
        {
			PxRaycastHit* val = new PxRaycastHit();

			Persistent<Object> newObj = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder());			
//			newObj.MakeWeak(Isolate::GetCurrent(),val, &CleanupDelete);
			newObj->SetInternalField(0, External::New(val));
			
			return scope.Close(newObj);
		}
		else if( args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && templ->HasInstance(args[0])){
			PxRaycastHit* val = new PxRaycastHit(*unwrap<PxRaycastHit>(args[0]->ToObject()));

			Persistent<Object> newObj = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder());			
//			newObj.MakeWeak(Isolate::GetCurrent(),val, &CleanupDelete);
			newObj->SetInternalField(0, External::New(val));
			
			return scope.Close(newObj);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRaycastHit::getU(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxRaycastHit* thisHit = unwrap<PxRaycastHit>(args.Holder());
			
			return scope.Close( Number::New( thisHit->u ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxRaycastHit::getV(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxRaycastHit* thisHit = unwrap<PxRaycastHit>(args.Holder());
			
			return scope.Close( Number::New( thisHit->v ) );
		}

		return scope.Close( Undefined() );
	}

//PxControllerState

	Handle<Value> V8PxControllerState::V8PxControllerStateConstructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0) 
        {
			PxControllerState* val = new PxControllerState();

			Persistent<Object> newObj = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder());			
//			newObj.MakeWeak(Isolate::GetCurrent(),val, &CleanupDelete);
			newObj->SetInternalField(0, External::New(val));
			
			return scope.Close(newObj);
		}
		else if( args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && templ->HasInstance(args[0])){
			PxControllerState* val = new PxControllerState(*unwrap<PxControllerState>(args[0]->ToObject()));

			Persistent<Object> newObj = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder());			
//			newObj.MakeWeak(Isolate::GetCurrent(),val, &CleanupDelete);
			newObj->SetInternalField(0, External::New(val));
			
			return scope.Close(newObj);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxControllerState::getDeltaXP( Local<v8::String> property, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxControllerState* thisObj = unwrap<PxControllerState>(info.Holder());
			
		return scope.Close( wrap<PxVec3, V8PxVec3>(thisObj->deltaXP) );
	}

	void V8PxControllerState::setDeltaXP( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8PxVec3::getTemplate()->HasInstance(value)){
			PxControllerState* thisObj = unwrap<PxControllerState>(info.Holder());

			thisObj->deltaXP = *unwrap<PxVec3>(value->ToObject());
		}
	}

	Handle<Value> V8PxControllerState::getTouchedShape( Local<v8::String> property, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxControllerState* thisObj = unwrap<PxControllerState>(info.Holder());
			
		return scope.Close( wrapPtr<PxShape, V8PxShape>(thisObj->touchedShape) );
	}

	void V8PxControllerState::setTouchedShape( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8PxShape::getTemplate()->HasInstance(value)){
			PxControllerState* thisObj = unwrap<PxControllerState>(info.Holder());

			thisObj->touchedShape = unwrap<PxShape>(value->ToObject());
		}
	}


	//TODO: Finish this
	Handle<Value> V8PxControllerState::getTouchedObstacle( Local<v8::String> property, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxControllerState* thisObj = unwrap<PxControllerState>(info.Holder());
			
		//return scope.Close( wrapPtr<PxObstacle, V8PxObstacle>(thisObj->touchedObstacle) );
		return scope.Close( Undefined() );
	}
	//TODO: Finish this
	void V8PxControllerState::setTouchedObstacle( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		/*if(!value.IsEmpty() && value->IsObject() && V8PxObstacle::getTemplate()->HasInstance(value)){
			PxControllerState* thisObj = unwrap<PxControllerState>(info.Holder());

			thisObj->touchedObstacle = unwrap<PxObstacle>(value->ToObject());
		}*/
	}

	Handle<Value> V8PxControllerState::getCollisionFlags( Local<v8::String> property, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxControllerState* thisObj = unwrap<PxControllerState>(info.Holder());
			
		return scope.Close( Uint32::New(thisObj->collisionFlags) );
	}

	void V8PxControllerState::setCollisionFlags( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsUint32()){
			PxControllerState* thisObj = unwrap<PxControllerState>(info.Holder());

			thisObj->collisionFlags = value->Uint32Value();
		}
	}

	Handle<Value> V8PxControllerState::getStandOnAnotherCCT( Local<v8::String> property, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxControllerState* thisObj = unwrap<PxControllerState>(info.Holder());
			
		return scope.Close( Boolean::New(thisObj->standOnAnotherCCT) );
	}

	void V8PxControllerState::setStandOnAnotherCCT( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsBoolean()){
			PxControllerState* thisObj = unwrap<PxControllerState>(info.Holder());

			thisObj->standOnAnotherCCT = value->BooleanValue();
		}
	}

	Handle<Value> V8PxControllerState::getStandOnObstacle( Local<v8::String> property, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxControllerState* thisObj = unwrap<PxControllerState>(info.Holder());
			
		return scope.Close( Boolean::New(thisObj->standOnObstacle) );
	}

	void V8PxControllerState::setStandOnObstacle( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsBoolean()){
			PxControllerState* thisObj = unwrap<PxControllerState>(info.Holder());

			thisObj->standOnObstacle = value->BooleanValue();
		}
	}

	Handle<Value> V8PxControllerState::getIsMovingUp( Local<v8::String> property, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxControllerState* thisObj = unwrap<PxControllerState>(info.Holder());
			
		return scope.Close( Boolean::New(thisObj->isMovingUp) );
	}

	void V8PxControllerState::setIsMovingUp( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsBoolean()){
			PxControllerState* thisObj = unwrap<PxControllerState>(info.Holder());

			thisObj->isMovingUp = value->BooleanValue();
		}
	}

//PxControllerStats

	Handle<Value> V8PxControllerStats::V8PxControllerStatsConstructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0) 
        {
			PxControllerStats* val = new PxControllerStats();

			Persistent<Object> newObj = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder());			
//			newObj.MakeWeak(Isolate::GetCurrent(),val, &CleanupDelete);
			newObj->SetInternalField(0, External::New(val));
			
			return scope.Close(newObj);
		}
		else if( args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && templ->HasInstance(args[0])){
			PxControllerStats* val = new PxControllerStats(*unwrap<PxControllerStats>(args[0]->ToObject()));

			Persistent<Object> newObj = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder());			
//			newObj.MakeWeak(Isolate::GetCurrent(),val, &CleanupDelete);
			newObj->SetInternalField(0, External::New(val));
			
			return scope.Close(newObj);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxControllerStats::getNbIterations( Local<v8::String> property, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxControllerStats* thisObj = unwrap<PxControllerStats>(info.Holder());
			
		return scope.Close( Uint32::New(thisObj->nbIterations) );
	}

	void V8PxControllerStats::setNbIterations( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsUint32()){
			PxControllerStats* thisObj = unwrap<PxControllerStats>(info.Holder());

			thisObj->nbIterations = value->Uint32Value();
		}
	}

	Handle<Value> V8PxControllerStats::getNbFullUpdates( Local<v8::String> property, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxControllerStats* thisObj = unwrap<PxControllerStats>(info.Holder());
			
		return scope.Close( Uint32::New(thisObj->nbFullUpdates) );
	}

	void V8PxControllerStats::setNbFullUpdates( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsUint32()){
			PxControllerStats* thisObj = unwrap<PxControllerStats>(info.Holder());

			thisObj->nbFullUpdates = value->Uint32Value();
		}
	}

	Handle<Value> V8PxControllerStats::getNbPartialUpdates( Local<v8::String> property, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxControllerStats* thisObj = unwrap<PxControllerStats>(info.Holder());
			
		return scope.Close( Uint32::New(thisObj->nbPartialUpdates) );
	}

	void V8PxControllerStats::setNbPartialUpdates( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsUint32()){
			PxControllerStats* thisObj = unwrap<PxControllerStats>(info.Holder());

			thisObj->nbPartialUpdates = value->Uint32Value();
		}
	}

//PxControllerFilters

	Handle<Value> V8PxControllerFilters::V8PxControllerFiltersConstructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0) 
        {
			PxControllerFilters* val = new PxControllerFilters();

			Persistent<Object> newObj = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder());			
//			newObj.MakeWeak(Isolate::GetCurrent(),val, &CleanupDelete);
			newObj->SetInternalField(0, External::New(val));
			
			return scope.Close(newObj);
		}
		else if( args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && templ->HasInstance(args[0])){
			PxControllerFilters* val = new PxControllerFilters(*unwrap<PxControllerFilters>(args[0]->ToObject()));

			Persistent<Object> newObj = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder());			
//			newObj.MakeWeak(Isolate::GetCurrent(),val, &CleanupDelete);
			newObj->SetInternalField(0, External::New(val));
			
			return scope.Close(newObj);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxControllerFilters::getActiveGroups( Local<v8::String> property, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxControllerFilters* thisObj = unwrap<PxControllerFilters>(info.Holder());
			
		return scope.Close( Uint32::New(thisObj->mActiveGroups) );
	}

	void V8PxControllerFilters::setActiveGroups( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsUint32()){
			PxControllerFilters* thisObj = unwrap<PxControllerFilters>(info.Holder());

			thisObj->mActiveGroups = value->Uint32Value();
		}
	}

	Handle<Value> V8PxControllerFilters::getFilterData( Local<v8::String> property, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxControllerFilters* thisObj = unwrap<PxControllerFilters>(info.Holder());
			
		return scope.Close( wrap<PxFilterData, V8PxFilterData>(*const_cast<PxFilterData*>(thisObj->mFilterData)) );
	}

	void V8PxControllerFilters::setFilterData( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8PxFilterData::getTemplate()->HasInstance(value)){
			PxControllerFilters* thisObj = unwrap<PxControllerFilters>(info.Holder());

			thisObj->mFilterData = unwrap<PxFilterData>(value->ToObject());
		}
	}

	//Handle<Value> V8PxControllerFilters::getFilterCallback( Local<v8::String> property, const AccessorInfo& info ){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	PxControllerFilters* thisObj = unwrap<PxControllerFilters>(info.Holder());
	//		
	//	return scope.Close( wrap<PxSceneQueryFilterCallback, V8PxSceneQueryFilterCallback>(*thisObj->mFilterCallback) );
	//}

	//void V8PxControllerFilters::setFilterCallback( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	if(!value.IsEmpty() && value->IsObject() && V8PxFilterData::getTemplate()->HasInstance(value)){
	//		PxControllerFilters* thisObj = unwrap<PxControllerFilters>(info.Holder());

	//		thisObj->mFilterCallback = unwrap<PxSceneQueryFilterCallback>(value->ToObject());
	//	}
	//}

	Handle<Value> V8PxControllerFilters::getFilterFlags( Local<v8::String> property, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxControllerFilters* thisObj = unwrap<PxControllerFilters>(info.Holder());
			
		return scope.Close( Uint32::New( (PxU32)thisObj->mFilterFlags) );
	}

	void V8PxControllerFilters::setFilterFlags( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsUint32() ){
			PxControllerFilters* thisObj = unwrap<PxControllerFilters>(info.Holder());

			thisObj->mFilterFlags = (PxSceneQueryFilterFlags)value->Uint32Value();
		}
	}

//PxController
	Handle<Value> V8PxController::getType(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());
			
			return scope.Close( Uint32::New( thisObj->getType() ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::release(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());

			thisObj->release();

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::move(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 4 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0]) &&
			!args[1].IsEmpty() && args[1]->IsNumber() &&
			!args[2].IsEmpty() && args[2]->IsNumber() &&
			!args[3].IsEmpty() && args[3]->IsObject() && V8PxControllerFilters::getTemplate()->HasInstance(args[3])) 
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());

			thisObj->move(*unwrap<PxVec3>(args[0]->ToObject()), args[1]->NumberValue(), args[2]->NumberValue(), *unwrap<PxControllerFilters>(args[3]->ToObject()));
			
			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 4 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[0]) &&
			!args[1].IsEmpty() && args[1]->IsNumber() &&
			!args[2].IsEmpty() && args[2]->IsNumber() &&
			!args[3].IsEmpty() && args[3]->IsUint32()) 
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());

			thisObj->move(*unwrap<PxVec3>(args[0]->ToObject()), args[1]->NumberValue(), args[2]->NumberValue(),args[3]->Uint32Value(), 0);
			
			return scope.Close( args.Holder() );
		}
		//TODO: Finish this

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::setPosition(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxExtendedVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());

			return scope.Close( Boolean::New( thisObj->setPosition(*unwrap<PxExtendedVec3>(args[0]->ToObject())) ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::getPosition(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());

			return scope.Close( wrap<PxExtendedVec3, V8PxExtendedVec3>(const_cast<PxExtendedVec3&>(thisObj->getPosition())) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::setFootPosition(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxExtendedVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());

			return scope.Close( Boolean::New( thisObj->setFootPosition(*unwrap<PxExtendedVec3>(args[0]->ToObject())) ) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::getFootPosition(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());

			return scope.Close( wrap<PxExtendedVec3, V8PxExtendedVec3>(thisObj->getFootPosition()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::getActor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());

			return scope.Close( wrapPtr<PxRigidDynamic, V8PxRigidDynamic>(thisObj->getActor()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::setStepOffset(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber())
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());
			thisObj->setStepOffset(args[0]->NumberValue());

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::getStepOffset(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0)
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());
			

			return scope.Close( Number::New(thisObj->getStepOffset()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::setInteraction(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32())
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());
			thisObj->setInteraction((PxCCTInteractionMode::Enum)args[0]->Uint32Value());

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::getInteraction(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0)
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());
			

			return scope.Close( Uint32::New(thisObj->getInteraction()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::setNonWalkableMode(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32())
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());
			thisObj->setNonWalkableMode((PxCCTNonWalkableMode::Enum)args[0]->Uint32Value());

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::getNonWalkableMode(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0)
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());
			

			return scope.Close( Uint32::New(thisObj->getNonWalkableMode()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::setGroupsBitmask(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32())
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());
			thisObj->setGroupsBitmask(args[0]->Uint32Value());

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::getGroupsBitmask(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0)
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());
			

			return scope.Close( Uint32::New(thisObj->getGroupsBitmask()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::getContactOffset(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0)
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());
			

			return scope.Close( Number::New(thisObj->getContactOffset()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::setUpDirection(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxExtendedVec3::getTemplate()->HasInstance(args[0])) 
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());

			thisObj->setUpDirection(*unwrap<PxVec3>(args[0]->ToObject()));

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::getUpDirection(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());

			return scope.Close( wrap<PxVec3, V8PxVec3>(thisObj->getUpDirection()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::getSlopeLimit(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());

			return scope.Close( Number::New(thisObj->getSlopeLimit()) );
		}

		return scope.Close( Undefined() );
	}

	
	Handle<Value> V8PxController::invalidateCache(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());

			thisObj->invalidateCache();

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::getScene(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());

			return scope.Close( wrapPtr<PxScene, V8PxScene>(thisObj->getScene()) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::getState(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());

			PxControllerState* state = new PxControllerState();

			thisObj->getState(*state);

			return scope.Close( wrapPtrCleanup<PxControllerState, V8PxControllerState>(state) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::getStats(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 0) 
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());

			PxControllerStats* stat = new PxControllerStats();

			thisObj->getStats(*stat);

			return scope.Close( wrapPtrCleanup<PxControllerStats, V8PxControllerStats>(stat) );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxController::resize(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsNumber()) 
        {
			PxController* thisObj = unwrap<PxController>(args.Holder());

			thisObj->resize(args[0]->NumberValue());

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

//PxSceneQueryFilterData
	Handle<Value> V8PxSceneQueryFilterData::V8PxSceneQueryFilterDataConstructor(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!getTemplate()->HasInstance(args.Holder()))
			return ThrowException( Exception::Error(String::New("This must be an instance of an object, create it using the new keyword")));

		if(args.Length() == 0) 
        {
			PxSceneQueryFilterData* val = new PxSceneQueryFilterData();

			Persistent<Object> newObj = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder());			
//			newObj.MakeWeak(Isolate::GetCurrent(),val, &CleanupDelete);
			newObj->SetInternalField(0, External::New(val));
			
			return scope.Close(newObj);
		}
		else if( args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsObject() && templ->HasInstance(args[0])){

			PxSceneQueryFilterData* val = new PxSceneQueryFilterData(*unwrap<PxSceneQueryFilterData>(args[0]->ToObject()));

			Persistent<Object> newObj = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder());			
//			newObj.MakeWeak(Isolate::GetCurrent(),val, &CleanupDelete);
			newObj->SetInternalField(0, External::New(val));
			
			return scope.Close(newObj);
		}
		else if( args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32()){

			PxSceneQueryFilterData* val = new PxSceneQueryFilterData((PxSceneQueryFilterFlags)args[0]->Uint32Value());

			Persistent<Object> newObj = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder());			
//			newObj.MakeWeak(Isolate::GetCurrent(),val, &CleanupDelete);
			newObj->SetInternalField(0, External::New(val));
			
			return scope.Close(newObj);
		}
		else if( args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsObject() && templ->HasInstance(args[0]) &&
			!args[1].IsEmpty() && args[1]->IsUint32()){

			PxSceneQueryFilterData* val = new PxSceneQueryFilterData(*unwrap<PxFilterData>(args[0]->ToObject()), (PxSceneQueryFilterFlags)args[1]->Uint32Value());

			Persistent<Object> newObj = Persistent<Object>::New(Isolate::GetCurrent(), args.Holder());			
//			newObj.MakeWeak(Isolate::GetCurrent(),val, &CleanupDelete);
			newObj->SetInternalField(0, External::New(val));
			
			return scope.Close(newObj);
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PxSceneQueryFilterData::getData( Local<v8::String> property, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxSceneQueryFilterData* thisObj = unwrap<PxSceneQueryFilterData>(info.Holder());
			
		return scope.Close( wrap<PxFilterData, V8PxFilterData>(thisObj->data) );
	}

	void V8PxSceneQueryFilterData::setData( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8PxFilterData::getTemplate()->HasInstance(value)){
			PxSceneQueryFilterData* thisObj = unwrap<PxSceneQueryFilterData>(info.Holder());

			thisObj->data = *unwrap<PxFilterData>(value->ToObject());
		}
	}

	Handle<Value> V8PxSceneQueryFilterData::getFlags( Local<v8::String> property, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PxSceneQueryFilterData* thisObj = unwrap<PxSceneQueryFilterData>(info.Holder());
			
		return scope.Close( Uint32::New( (PxU16)thisObj->flags) );
	}

	void V8PxSceneQueryFilterData::setFlags( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsUint32()){
			PxSceneQueryFilterData* thisObj = unwrap<PxSceneQueryFilterData>(info.Holder());

			thisObj->flags = (PxSceneQueryFilterFlags)value->Uint32Value();
		}
	}



////PxControllerDesc
//
//	Handle<Value> V8PxControllerDesc::getPosition( Local<String> property , const AccessorInfo& info ){
//		//Locker lock(Isolate::GetCurrent());
//		HandleScope scope(Isolate::GetCurrent());
//
//		PxControllerDesc* thisPxControllerDesc = unwrap<PxControllerDesc>(info.Holder());
//		//if(thisPxVec2 != NULL) 
//		//{
//			Persistent<Object> newPxExtendedVec3 = Persistent<Object>::New(Isolate::GetCurrent(),V8PxExtendedVec3::getTemplate()->InstanceTemplate()->NewInstance());			
////			newPxExtendedVec3.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
//			newPxExtendedVec3->SetInternalField(0, External::New(&thisPxControllerDesc->position));
//
//			return scope.Close(newPxExtendedVec3);
//		//}
//
//		//return scope.Close( Undefined() );
//	}
//
//	void V8PxControllerDesc::setPosition( Local<String> property, Local<Value> value, const AccessorInfo& info ){
//		//Locker lock(Isolate::GetCurrent());
//		HandleScope scope(Isolate::GetCurrent());
//
//		if(!value.IsEmpty() && value->IsObject() && V8PxExtendedVec3::getTemplate()->HasInstance(value)){
//			PxControllerDesc* thisControllerDesc = unwrap<PxControllerDesc>(info.Holder());
//			PxExtendedVec3* inPxExtendedVec3 = unwrap<PxExtendedVec3>(value->ToObject());
//			//if(thisPxVec2 != NULL && value->IsNumber()) 
//			//{
//				thisControllerDesc->position = *inPxExtendedVec3;
//			//}
//		}
//	}