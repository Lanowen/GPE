#include "VisualDebugger.hpp"

//VisualDebugger::RenderProfile  OGRE_VISUALDEBUGGER = VisualDebugger::RenderProfile(Ogre::RenderOperation::OT_LINE_LIST, false, true, false, false, false);
//
//VisualDebugger::RenderProfile  OGRE_PHYSXMESH = VisualDebugger::RenderProfile(Ogre::RenderOperation::OT_TRIANGLE_LIST, true, false, true, true, false);
//
//VisualDebugger::RenderProfile  OGRE_PARTICLE_POINTS = VisualDebugger::RenderProfile(Ogre::RenderOperation::OT_POINT_LIST, false, false, false, false, false);
//
//VisualDebugger::RenderProfile  OGRE_PARTICLE_VELOCITIES = VisualDebugger::RenderProfile(Ogre::RenderOperation::OT_LINE_LIST, false, false, false, false, false);
//
//VisualDebugger::RenderProfile  OGRE_SOFTBODY = VisualDebugger::RenderProfile(Ogre::RenderOperation::OT_TRIANGLE_LIST, false, false, true, false, false);

#define ABORT_IF_EMPTY if (renderable->vertices.count() < 3) { mBox.setExtents(Ogre::Vector3::ZERO, Ogre::Vector3::ZERO); return; }


VisualDebugger::RenderProfile::RenderProfile()
: mRenderOperation(Ogre::RenderOperation::OT_POINT_LIST),
  usesNormals(false),
  usesColourVertices(false),
  usesIndexes(false),
  uses16BitIndexes(false),
  usesTextureCoordinates(false)
{
}

VisualDebugger::RenderProfile::RenderProfile(Ogre::RenderOperation::OperationType op, bool n, bool c, bool i, bool t, bool _16)
: mRenderOperation(op),
  usesNormals(n),
  usesColourVertices(c),
  usesIndexes(i),
  uses16BitIndexes(_16),
  usesTextureCoordinates(t)
{
}

VisualDebugger::VisualDebugger(physx::PxScene* scene, Ogre::SceneManager* visualDebuggerScene_Mgr) {
	visualDebuggerScene_ = scene;
	nbLines_ = 0;
	mProfile = RenderProfile(Ogre::RenderOperation::OT_LINE_LIST, false, true, false, false, false);
	_initialise();

	if (Ogre::MaterialManager::getSingletonPtr()->resourceExists("VisualDebuggerMaterial") == false)
	{
		Ogre::MaterialPtr material = Ogre::MaterialManager::getSingletonPtr()->create("VisualDebuggerMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		material->getTechnique(0)->getPass(0)->setDepthBias(1);
		material->getTechnique(0)->getPass(0)->setAmbient(1,1,1);
		material->getTechnique(0)->getPass(0)->setSelfIllumination(1,1,1);
		material->getTechnique(0)->getPass(0)->setDiffuse(1,1,1,1);
		material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	}

	visualDebuggerNode_ = visualDebuggerScene_Mgr->getRootSceneNode()->createChildSceneNode("VisualDebuggerNode");

	visualDebuggerNode_->attachObject(this);

	visualDebuggerNode_->setVisible(true);
}

VisualDebugger::~VisualDebugger(){
}

void VisualDebugger::_initialise()
{
 // Op.
 mRenderOp.operationType = mProfile.mRenderOperation;

 // Vertices and other vertex bits.
 mRenderOp.vertexData  = new Ogre::VertexData;

 // Main vertex declartion. It is assumed that a Renderable has vertices.
 Ogre::VertexDeclaration* vDecl = mRenderOp.vertexData->vertexDeclaration;
 vDecl->addElement(VertexDeclaration_Position, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
 
 // Normals.
 if (mProfile.usesNormals)
  vDecl->addElement(VertexDeclaration_Normal, 0, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
 
 // Vertex Colours.
 if (mProfile.usesColourVertices)
  vDecl->addElement(VertexDeclaration_Colour, 0, Ogre::VET_COLOUR, Ogre::VES_DIFFUSE);
 
 if (mProfile.usesTextureCoordinates)
  vDecl->addElement(VertexDeclaration_TextureCoordinates, 0, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES);

 // Vertex buffer capacity is zero.
 mVertexBufferCapacity = 0;


 // Do the indexes. If it has one.
 if (mRenderOp.useIndexes = mProfile.usesIndexes)
 {
  mRenderOp.indexData = new Ogre::IndexData;
 }

 mIndexBufferCapacity = 0;
}

void VisualDebugger::DrawVector(physx::PxVec3 position, physx::PxVec3 direction, physx::PxReal length) {
	debug_vectors_.push_back(position);
	direction.normalize();
	debug_vectors_.push_back(position + direction*length);
}

void VisualDebugger::update(const physx::PxRenderBuffer& debugRenderable)
{
	lines_.remove_all();
	colours_.remove_all();
	nbLines_ = 0;

	if(debugRenderable.getNbLines() == 0 && debug_vectors_.size() == 0){
		return;
	}
  
	unsigned int nbLines = debugRenderable.getNbLines();
	const physx::PxDebugLine* lines = debugRenderable.getLines();

	while(nbLines--)
	{
		lines_.push_back(lines->pos0.x);
		lines_.push_back(lines->pos0.y);
		lines_.push_back(lines->pos0.z);
		lines_.push_back(lines->pos1.x);
		lines_.push_back(lines->pos1.y);
		lines_.push_back(lines->pos1.z);
		colours_.push_back(lines->color0);
		colours_.push_back(lines->color1);
		lines++;
	}

	for (unsigned int i = 0; i < debug_vectors_.size(); i += 2) {
		lines_.push_back(debug_vectors_[i].x);
		lines_.push_back(debug_vectors_[i].y);
		lines_.push_back(debug_vectors_[i].z);
		lines_.push_back(debug_vectors_[i+1].x);
		lines_.push_back(debug_vectors_[i + 1].y);
		lines_.push_back(debug_vectors_[i + 1].z);
		colours_.push_back(0xFF0000);
		colours_.push_back(0xFF0000);
	}

	nbLines_ += debugRenderable.getNbLines();
	nbLines_ += debug_vectors_.size() *3;
 
	drawVisualDebugger();
	visualDebuggerNode_->needUpdate();

	debug_vectors_.clear();
}

void VisualDebugger::_resize(size_t vertexCount, size_t indexCount)
{
  // Prepare vertex buffer
  size_t newVertCapacity = mVertexBufferCapacity;
  if ((vertexCount > mVertexBufferCapacity) ||
      (!mVertexBufferCapacity))
  {
    // vertexCount exceeds current capacity!
    // It is necessary to reallocate the buffer.

    // Check if this is the first call
    if (!newVertCapacity)
      newVertCapacity = 1;

    // Make capacity the next power of two
    while (newVertCapacity < vertexCount)
      newVertCapacity <<= 1;
  }
  else if (vertexCount < mVertexBufferCapacity>>1) {
    // Make capacity the previous power of two
    while (vertexCount < newVertCapacity>>1)
      newVertCapacity >>= 1;
  }
  
  if (newVertCapacity != mVertexBufferCapacity) 
  {
    mVertexBufferCapacity = newVertCapacity;
    
    // Create new vertex buffer
    mVertexBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
        mRenderOp.vertexData->vertexDeclaration->getVertexSize(VertexDeclaration_Position),
        mVertexBufferCapacity,
        Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY); // TODO: Custom HBU_?
    
    // Bind buffer
    mRenderOp.vertexData->vertexBufferBinding->setBinding(VertexDeclaration_Position, mVertexBuffer);
    
    // Colour vertices.
    if (this->mProfile.usesColourVertices)
    {
     // Create new vertexColour buffer
     mVertexColourBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
         mRenderOp.vertexData->vertexDeclaration->getVertexSize(VertexDeclaration_Colour),
         mVertexBufferCapacity,
         Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY); // TODO: Custom HBU_?
     
     // Bind buffer
     mRenderOp.vertexData->vertexBufferBinding->setBinding(VertexDeclaration_Colour, mVertexColourBuffer);
    }

    // Normals.
    if (this->mProfile.usesNormals)
    {
     // Create new vertexColour buffer
     mNormalBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
         mRenderOp.vertexData->vertexDeclaration->getVertexSize(VertexDeclaration_Normal),
         mVertexBufferCapacity,
         Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY); // TODO: Custom HBU_?
     
     // Bind buffer
     mRenderOp.vertexData->vertexBufferBinding->setBinding(VertexDeclaration_Normal, mNormalBuffer);
    }

    // Texture coords.
    if (this->mProfile.usesTextureCoordinates)
    {
     // Create new vertexColour buffer
     mTextureCoordsBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
         mRenderOp.vertexData->vertexDeclaration->getVertexSize(VertexDeclaration_TextureCoordinates),
         mVertexBufferCapacity,
         Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY); // TODO: Custom HBU_?
     
     // Bind buffer
     mRenderOp.vertexData->vertexBufferBinding->setBinding(VertexDeclaration_TextureCoordinates, mTextureCoordsBuffer);
    }

  }
  // Update vertex count in the render operation
  mRenderOp.vertexData->vertexCount = vertexCount;
  
  if (mProfile.usesIndexes)
  {
    OgreAssert(indexCount <= std::numeric_limits<unsigned short>::max(), "indexCount exceeds 16 bit");

    size_t newIndexCapacity = mIndexBufferCapacity;
    // Prepare index buffer
    if ((indexCount > newIndexCapacity) || (!newIndexCapacity))
    {
      // indexCount exceeds current capacity!
      // It is necessary to reallocate the buffer.
      // Check if this is the first call
      if (!newIndexCapacity)
        newIndexCapacity = 1;
      // Make capacity the next power of two
      while (newIndexCapacity < indexCount)
        newIndexCapacity <<= 1;
    }
    else if (indexCount < newIndexCapacity>>1) 
    {
      // Make capacity the previous power of two
      while (indexCount < newIndexCapacity>>1)
        newIndexCapacity >>= 1;
    }
    
    if (newIndexCapacity != mIndexBufferCapacity)
    {
      mIndexBufferCapacity = newIndexCapacity;
      // Create new index buffer
      mIndexBuffer = mRenderOp.indexData->indexBuffer =
        Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(
          Ogre::HardwareIndexBuffer::IT_32BIT, //Ogre::HardwareIndexBuffer::IndexType(!mProfile.uses16BitIndexes),
          mIndexBufferCapacity,
          Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY); // TODO: Custom HBU_?
    }
    
    // Update index count in the render operation
    mRenderOp.indexData->indexCount = indexCount;
  }
}

void VisualDebugger::drawVisualDebugger()
{
	_resize(lines_.size() / 3, 0);

	// Write the vertices.
	mVertexBuffer->writeData(0, lines_.size() * sizeof(float), lines_.first());

	mVertexColourBuffer->writeData(0, colours_.size() * sizeof(unsigned int), colours_.first());

	mBox.setInfinite();
}

float VisualDebugger::getBoundingRadius() const
{
 return Ogre::Math::Sqrt(std::max(mBox.getMaximum().squaredLength(), mBox.getMinimum().squaredLength()));
}

float VisualDebugger::getSquaredViewDepth(const Ogre::Camera* cam) const
{
 Ogre::Vector3 vMin, vMax, vMid, vDist;
 vMin = mBox.getMinimum();
 vMax = mBox.getMaximum();
 vMid = ((vMax - vMin) * 0.5) + vMin;
 vDist = cam->getDerivedPosition() - vMid;
 return vDist.squaredLength();
}

void VisualDebugger::showAll(){

	/*for(int i = 0; i < physx::PxVisualizationParameter::eNUM_VALUES; i++){
		visualDebuggerScene_->setVisualizationParameter((physx::PxVisualizationParameter::Enum)i, 1.0f);
	}*/

	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eSCALE, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eWORLD_AXES, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eBODY_AXES, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eBODY_MASS_AXES, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eBODY_LIN_VELOCITY, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eBODY_ANG_VELOCITY, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eBODY_JOINT_GROUPS, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eCONTACT_POINT, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eCONTACT_NORMAL, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eCONTACT_ERROR, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eCONTACT_FORCE, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eACTOR_AXES, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eCOLLISION_AABBS, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eCOLLISION_AXES, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eCOLLISION_FNORMALS, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eCOLLISION_EDGES, 1.0f);
	
		//visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eCOLLISION_STATIC, 1.0f);
		//visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eCOLLISION_DYNAMIC, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eCOLLISION_PAIRS, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::ePARTICLE_SYSTEM_POSITION, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::ePARTICLE_SYSTEM_VELOCITY, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::ePARTICLE_SYSTEM_COLLISION_NORMAL, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::ePARTICLE_SYSTEM_BOUNDS, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::ePARTICLE_SYSTEM_GRID, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::ePARTICLE_SYSTEM_BROADPHASE_BOUNDS, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::ePARTICLE_SYSTEM_MAX_MOTION_DISTANCE, 1.0f);
	//visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::ePARTICLE_SYSTEM_DRAINS, 1.0f);
	/*visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eDEFORMABLE_MESH, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eDEFORMABLE_ATTACHMENTS, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eDEFORMABLE_COLLISIONS, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eDEFORMABLE_SELFCOLLISIONS, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eDEFORMABLE_SLEEP, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eDEFORMABLE_TEARING, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eDEFORMABLE_VALIDBOUNDS, 1.0f);
	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eDEFORMABLE_SHAPES, 1.0f);*/

	visualDebuggerScene_->setVisualizationParameter(physx::PxVisualizationParameter::eCULL_BOX, 1.0f);

	visualDebuggerNode_->setVisible(true);
}

void VisualDebugger::hideAll(){
	for(int i = 0; i < physx::PxVisualizationParameter::eNUM_VALUES ; i++){
		visualDebuggerScene_->setVisualizationParameter((physx::PxVisualizationParameter::Enum)i, 0.0f);
	}

	visualDebuggerNode_->setVisible(false);
}