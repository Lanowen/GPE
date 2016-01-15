#pragma once

#include <Ogre.h>
#include "buffer.hpp"

#include <PxPhysicsAPI.h>
#include <common/PxRenderBuffer.h>

class VisualDebugger : public Ogre::SimpleRenderable
{

public:

	enum VertexDeclaration
	{
		VertexDeclaration_Position = 0,
		VertexDeclaration_TextureCoordinates = 1,
		VertexDeclaration_Normal = 2,
		VertexDeclaration_Colour = 3,
	};

	struct RenderProfile
	{
		RenderProfile();
		// operation, normals, colour, indexes, texture-coords, 16bit indexes.
		RenderProfile(Ogre::RenderOperation::OperationType op, bool n, bool c, bool i, bool t, bool _16);
		bool usesNormals;
		bool usesColourVertices;
		bool usesIndexes;
		bool uses16BitIndexes;
		bool usesTextureCoordinates;
		Ogre::RenderOperation::OperationType mRenderOperation;
	};
     
	static RenderProfile OGRE_VISUALDEBUGGER;
	static RenderProfile OGRE_PHYSXMESH;
	static RenderProfile OGRE_PARTICLE_POINTS;
	static RenderProfile OGRE_PARTICLE_VELOCITIES;
	static RenderProfile OGRE_SOFTBODY;

	VisualDebugger(physx::PxScene* scene, Ogre::SceneManager* visualDebuggerScene_Mgr);
	virtual ~VisualDebugger();
	void update(const physx::PxRenderBuffer& debugRenderable);

	void DrawVector(physx::PxVec3 position, physx::PxVec3 direction, physx::PxReal length);

	void showAll();
	void hideAll();

protected:

	physx::PxPhysics*							physics_;
    inline void _initialise();
    inline void _resize(size_t vertexCount = 0, size_t indexCount = 0);

	Ogre::Real getBoundingRadius() const;
     
	/** \brief
	*/
	Ogre::Real getSquaredViewDepth(const Ogre::Camera* cam) const;

	RenderProfile mProfile;

	/** \brief Maximum capacity of the currently allocated vertex buffer.
*/
     size_t mVertexBufferCapacity;
     
     /** \brief Maximum capacity of the currently allocated index buffer.
*/
     size_t mIndexBufferCapacity;
     
     //
     Ogre::HardwareVertexBufferSharedPtr mVertexBuffer;
     
     //
     Ogre::HardwareVertexBufferSharedPtr mVertexColourBuffer;
     
     //
     Ogre::HardwareVertexBufferSharedPtr mNormalBuffer;
     
     //
     Ogre::HardwareVertexBufferSharedPtr mTextureCoordsBuffer;
     
     //
     Ogre::HardwareIndexBufferSharedPtr mIndexBuffer;

private:
	physx::PxScene*						visualDebuggerScene_;
	Ogre::SceneNode*				visualDebuggerNode_;
	void							drawVisualDebugger();
	unsigned int					nbLines_;
	buffer<float>					lines_;
	buffer<unsigned int>			colours_;
	std::vector<physx::PxVec3>		debug_vectors_;
};

#undef ABORT_IF_EMPTY