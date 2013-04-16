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
		}
	};

	class SerializableUINT32 : public SerializableData {
	public:

		SerializableUINT32(){}

		virtual ~SerializableUINT32(){}

		UINT32 val;

	private:
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version){
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
			ar & boost::serialization::base_object<SerializableData>(*this);
			ar & x;
			ar & y;
			ar & z;
		}
	};

	class CreateEnemy : public SerializableData {
	public:

		CreateEnemy(){}

		virtual ~CreateEnemy(){}

		int id;
		float px, py, pz;

	private:
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version){
			ar & boost::serialization::base_object<SerializableData>(*this);
			ar & px;
			ar & py;
			ar & pz;
		}
	};

	class CreatePlayer : public SerializableData {
	public:

		CreatePlayer(){}

		virtual ~CreatePlayer(){}

		int id;
		float px, py, pz;

	private:
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version){
			ar & boost::serialization::base_object<SerializableData>(*this);
			ar & id;
			ar & px;
			ar & py;
			ar & pz;
		}
	};

	class CreateBullet : public SerializableData {
	public:

		CreateBullet(){}

		virtual ~CreateBullet(){}

		int id, parentid;
		float px, py, pz;
		float dx, dy, dz;

	private:
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version){
			ar & boost::serialization::base_object<SerializableData>(*this);
			ar & id;
			ar & parentid;
			ar & px;
			ar & py;
			ar & pz;
			ar & dx;
			ar & dy;
			ar & dz;
		}
	};

	class NetEvent : public SerializableData {
	public:

		NetEvent(){}

		virtual ~NetEvent(){}

		int targetid, parentid;
		std::string eventName;

	private:
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version){
			ar & boost::serialization::base_object<SerializableData>(*this);
			ar & id;
			ar & parentid;
			ar & eventName;
		}
	};
