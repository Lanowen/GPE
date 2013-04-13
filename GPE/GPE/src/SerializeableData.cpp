#include <SerializeableData.hpp>

//#include <boost\archive\text_iarchive.hpp>
//#include <boost\archive\text_oarchive.hpp>

//template<class Archive>
//void SerializableData::serialize(Archive & ar, const unsigned int version){}
//
//template<class Archive>
//void SerializableUINT32::serialize(Archive & ar, const unsigned int version){
//	std::cout<< "Serialized this UINT32" << std::endl;
//	ar & boost::serialization::base_object<SerializableData>(*this);
//	ar & val;
//}
//
//template<class Archive>
//void SerializableVector3::serialize(Archive & ar, const unsigned int version){
//	ar & boost::serialization::base_object<SerializableData>(*this);
//	ar & x;
//	ar & y;
//	ar & z;
//}
