#include "Util.hpp"
#include <boost\tokenizer.hpp>
#include <boost\algorithm\string.hpp>
#include <boost\algorithm\string\regex.hpp>

#include <OgreVertexIndexData.h>
#include <OgreHardwareBufferManager.h>
#include <OgreSubMesh.h>
#include <Physics.hpp>

namespace Util {

	std::vector<ObjObject> ParseSimpleVertexOnlyObj(Ogre::DataStreamPtr& fileHandle) {
		Ogre::String str;
		std::vector<ObjObject> ret;
		std::stringstream ss;
		while (!fileHandle->eof()) {
			str = fileHandle->getLine();
			size_t pos;
			if (pos = str.find("object") != Ogre::String::npos) {
				ret.push_back(ObjObject(str.substr(pos + 7)));
			}
			else if(str.length() > 1) {
				ss.clear();
				ss.str("");
				boost::char_separator<char> sep("# /");
				boost::tokenizer<boost::char_separator<char>> tokens(str, sep);
				
				
				boost::tokenizer<boost::char_separator<char>>::iterator itr = tokens.begin();
				Ogre::String temp = *itr;
				while (++itr != tokens.end()) {
					ss << " " << *itr;
				}
				if (temp == "v") { // vertex points
					Ogre::Real x, y, z;
					ss >> x >> y >> z;

					ret.back().bounds.merge(Ogre::Vector3(x, y, z));

					ret.back().vertices.push_back(x);
					ret.back().vertices.push_back(y);
					ret.back().vertices.push_back(z);
				}
				//else if (temp == "vn") { //vertex normals
				//	Ogre::Real x, y, z;
				//	ss >> x >> y >> z;
				//	ret.back().normals.push_back(x);
				//	ret.back().normals.push_back(y);
				//	ret.back().normals.push_back(z);
				//}
				//else if (temp == "vt") { //texture coords
				//	Ogre::Real x, y, z;
				//	ss >> x >> y >> z;
				//	ret.back().texcoords.push_back(x);
				//	ret.back().texcoords.push_back(y);
				//	ret.back().texcoords.push_back(z);
				//}
				else if (temp == "f") {  //faces
					unsigned short f;
					while (ss >> f){
						ret.back().faces.push_back(f - 1);
					}
				}
			}
		}

		return ret;
	}

	void CreateOgreMesh(Ogre::MeshPtr levelMesh, ObjObject& simpleObj) {

		levelMesh->sharedVertexData = new Ogre::VertexData;
		levelMesh->sharedVertexData->vertexCount = simpleObj.vertices.size() / 3;

		/// Create declaration (memory format) of vertex data
		Ogre::VertexDeclaration* decl = levelMesh->sharedVertexData->vertexDeclaration;

		// 1st buffer
		decl->addElement(0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
		
		/// Allocate vertex buffer of the requested number of vertices (vertexCount) 
		/// and bytes per vertex (offset)
		Ogre::HardwareVertexBufferSharedPtr vbuf =
			Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
			Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3), simpleObj.vertices.size() / 3, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
		/// Upload the vertex data to the card
		vbuf->writeData(0, vbuf->getSizeInBytes(), simpleObj.vertices.data(), true);

		/// Set vertex buffer binding so buffer 0 is bound to our vertex buffer
		levelMesh->sharedVertexData->vertexBufferBinding->setBinding(0, vbuf);


		//// 2nd buffer
		//decl->addElement(1, 0, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
		//vbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
		//	Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3), simpleObj.normals.size(), Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

		///// Upload the normal data to the card
		//vbuf->writeData(0, Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3)*simpleObj.normals.size() / 3, simpleObj.normals.data(), true);

		//levelMesh->sharedVertexData->vertexBufferBinding->setBinding(1, vbuf);


		//// 3nd buffer
		//decl->addElement(2, 0, Ogre::VET_FLOAT3, Ogre::VES_TEXTURE_COORDINATES);
		//vbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
		//	Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3), simpleObj.texcoords.size(), Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

		///// Upload the texture coordinate data to the card
		//vbuf->writeData(0, Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3)*simpleObj.texcoords.size() / 3, simpleObj.texcoords.data(), true);

		//levelMesh->sharedVertexData->vertexBufferBinding->setBinding(2, vbuf);


		/// Allocate index buffer of the requested number of vertices (ibufCount) 
		Ogre::HardwareIndexBufferSharedPtr ibuf = Ogre::HardwareBufferManager::getSingleton().
			createIndexBuffer(
			Ogre::HardwareIndexBuffer::IT_16BIT,
			simpleObj.faces.size(),
			Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
		/// Upload the index data to the card
		ibuf->writeData(0, ibuf->getSizeInBytes(), simpleObj.faces.data(), true);

		Ogre::SubMesh* sub = levelMesh->createSubMesh();
		/// Set parameters of the submesh
		sub->useSharedVertices = true;
		sub->indexData->indexBuffer = ibuf;
		sub->indexData->indexCount = simpleObj.faces.size();
		sub->indexData->indexStart = 0;

		/// Set bounding information (for culling)
		levelMesh->_setBounds(simpleObj.bounds);
		levelMesh->_setBoundingSphereRadius(simpleObj.bounds.getMaximum().length());

		levelMesh->load();
	}

	void CookTrimeshFromObj(char* dst, ObjObject& obj){
		std::vector<physx::PxVec3> physverts;
		for (unsigned int i = 0; i < obj.vertices.size(); i += 3) {
			physverts.push_back(physx::PxVec3(obj.vertices[i], obj.vertices[i + 1], obj.vertices[i + 2]));
		}

		std::vector<physx::PxU32> physfaces;
		for (unsigned int i = 0; i < obj.faces.size(); i++) {
			physfaces.push_back(obj.faces[i]);
		}

		gpe::Physics::getSingletonPtr()->CookTrimesh(dst, physverts, physfaces);
	}

	DebugLog::DebugLog() {

	}

	DebugLog::~DebugLog() {

	}

	DebugLog& DebugLog::operator<<(const char*& message) {
		OutputDebugStringA(message);
		return *this;
	}

	DebugLog& DebugLog::operator<<(const WCHAR*& message) {
		OutputDebugStringW(message);
		return *this;
	}

	DebugLog& DebugLog::operator<<(const std::string& message) {
		OutputDebugStringA(message.c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const std::wstring& message) {
		OutputDebugStringW(message.c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const int& val) {
		std::stringstream ss;
		ss << val;
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const float& val) {
		std::stringstream ss;
		ss << val;
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const double& val) {
		std::stringstream ss;
		ss << val;
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const short& val) {
		std::stringstream ss;
		ss << val;
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const unsigned int& val) {
		std::stringstream ss;
		ss << val;
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const unsigned short& val) {
		std::stringstream ss;
		ss << val;
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const physx::PxVec2& val) {
		std::stringstream ss;
		ss << "PxVec2(" << val.x << ", " << val.y << ")";
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const physx::PxVec3& val) {
		std::stringstream ss;
		ss << "PxVec3(" << val.x << ", " << val.y << ", " << val.z << ")";
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const physx::PxVec4& val) {
		std::stringstream ss;
		ss << "PxVec4(" << val.x << ", " << val.y << ", " << val.z << ", " << val.w << ")";
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const Ogre::Vector2& val) {
		std::stringstream ss;
		ss << "Vector2(" << val.x << ", " << val.y << ")";
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const Ogre::Vector3& val) {
		std::stringstream ss;
		ss << "Vector3(" << val.x << ", " << val.y << ", " << val.z << ")";
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const Ogre::Vector4& val) {
		std::stringstream ss;
		ss << "Vector4(" << val.x << ", " << val.y << ", " << val.z << ", " << val.w << ")";
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	// define an operator<< to take in std::endl
	DebugLog& DebugLog::operator<<(StandardEndLine manip) {
		OutputDebugStringA("\n");

		return *this;
	}


}