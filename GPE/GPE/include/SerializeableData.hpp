#pragma once

#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <iostream>

//namespace GPENet {

typedef unsigned int UINT32;

	class SerializableData{
	public:
		SerializableData(){}

		virtual ~SerializableData(){}

	private:
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version){
			//std::cout<< "BASE SERIALIZATION" << std::endl;
			//ar.register_type(static_cast<SerializableUINT32 *>(NULL));
		}
	};

	//

	class SerializableUINT32 : public SerializableData {
	public:

		SerializableUINT32(){}

		virtual ~SerializableUINT32(){}

		UINT32 val;

	private:
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version){
			//std::cout<< "Serialized this UINT32" << std::endl;
			ar & boost::serialization::base_object<SerializableData>(*this);
			ar & val;
		}
	};

	class SerializableVector3 : public SerializableData {
	public:

		SerializableVector3(){}

		virtual ~SerializableVector3(){}

		float x;
		float y;
		float z;

	private:
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version){
			//std::cout<< "Serialized this Vector3" << std::endl;
			ar & boost::serialization::base_object<SerializableData>(*this);
			ar & x;
			ar & y;
			ar & z;
		}
	};

	class SerializableCharacterData : public SerializableData {
	public:

		SerializableCharacterData(){}

		virtual ~SerializableCharacterData(){}

		float px, py, pz;
		float vx, vy, vz;
		float yaw;
		int baseAnim;
		int topAnim;
		//int what;

	private:
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version){
			//std::cout<< "Serialized this Vector3" << std::endl;
			ar & boost::serialization::base_object<SerializableData>(*this);
			ar & px;
			ar & py;
			ar & pz;
			ar & vx;
			ar & vy;
			ar & vz;
			ar & yaw;
			ar & baseAnim;
			ar & topAnim;
			//ar & what;
		}
	};

//}
