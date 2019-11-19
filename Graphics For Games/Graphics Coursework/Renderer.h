#pragma once
#include "..\nclgl\OGLRenderer.h"
#include "..\nclgl\Camera.h"
#include "..\nclgl\OBJmesh.h"
#include "..\nclgl\heightmap.h"
#include "..\nclgl\SceneNode.h"
#include "..\nclgl\Frustum.h"
#include "../../nclgl/MD5Mesh.h"
#include "../../nclgl/MD5Node.h"
#include <algorithm>

#define LIGHTNUM 8
#define POST_PASSES 2
#define SHADOWSIZE 2048

class Renderer :
	public OGLRenderer
{
public:
	Renderer(Window& parent);
	virtual ~Renderer(void);

	virtual void RenderScene();
	virtual void UpdateScene(float msec);

	void ToggleBoundingVolume() { showBoundingVolume = !showBoundingVolume; }

	Window* GetWindow() { return window; }

protected:
	void FillBuffers(); //G- Buffer Fill Render Pass
	void DrawPointLights(); // Lighting Render Pass
	void CombineBuffers(); // Combination Render Pass
	// Make a new texture ...
	void GenerateScreenTexture(GLuint& into, bool depth = false);

	void BuildNodeLists(SceneNode* from);
	void SortNodeLists();
	void ClearNodeLists();
	void DrawNodes();
	void DrawNode(SceneNode* n);

	Shader* heightMapShader;
	Shader* boundingVolumeShader;
	Shader* sceneShader; // Shader to fill our GBuffers
	Shader* pointlightShader; // Shader to calculate lighting
	Shader* combineShader; // shader to stick it all together
	Shader* processShader;
	Shader* skeletonShader;
	Shader* textureShader;
	Shader* reflectShader;
	Shader* skyBoxShader;
	Shader* shadowShader;
	Shader* shadowSceneShader;


	SceneNode* heightMapNode;
	SceneNode* hellKnightNode;
	SceneNode* waterNode;
	
	SceneNode* oceanNode;

	size_t numberOfLight;
	Light** lights; // Array of lighting data
	Mesh* heightMap; // Terrain !
	OBJMesh* sphere; 
	Mesh* quad; // To draw a full - screen quad
	Mesh* skyBoxQuad;
	Camera* camera; // Our usual camera
	Camera* mapCamera;
	Mesh* ppQuad1;
	Mesh* ppQuad2;
	Mesh* waterQuad;
	float waterRotate;
	GLuint skyBox1;
	GLuint skyBox2;

	Matrix4 perspectiveMatrix = Matrix4::Perspective(1, 20000, (float)width / (float)height, 45);

	float rotation; // How much to increase rotation by
	GLuint processFBO;
	GLuint bufferFBO; // FBO for our G- Buffer pass
	GLuint bufferFBO0; 
	GLuint bufferColourTex[2]; // Albedo goes here
	GLuint bufferColourTex0[2];
	GLuint bufferNormalTex; // Normals go here
	GLuint bufferDepthTex; // Depth goes here
	GLuint bufferDepthTex0;

	GLuint pointLightFBO; // FBO for our lighting pass
	GLuint lightEmissiveTex; // Store emissive lighting
	GLuint lightSpecularTex; // Store specular lighting
	GLuint shadowTex;
	GLuint shadowFBO;

	SceneNode* root[2];
	
	Frustum frameFrustum;

	vector<SceneNode*> transparentNodeList;
	vector<SceneNode*> nodeList;

	bool showBoundingVolume;
	bool showPostProcessing;
	int sceneNum;

	Window* window;
private:
	inline void InitScene0();
	inline void InitScene1();
	inline SceneNode* LoadHeightMap();
	inline SceneNode* LoadOcean();
	inline SceneNode* LoadWater();
	inline SceneNode* LoadHellKnight();
	inline void LoadSkyBox();
	inline void LoadLights();
	inline void InitPostProcessing();
	inline void DrawPostProcess();
	inline void PresentScene();
	inline void DrawSkybox();
	inline void InitShadow();
	inline void DrawShadowScene();
	inline void DrawCombinedScene();
	inline void DrawOcean();
};


