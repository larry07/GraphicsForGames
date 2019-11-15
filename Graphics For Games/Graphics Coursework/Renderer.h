#pragma once
#include "..\nclgl\OGLRenderer.h"
#include "..\nclgl\Camera.h"
#include "..\nclgl\OBJmesh.h"
#include "..\nclgl\heightmap.h"
#include "..\nclgl\SceneNode.h"
#include "..\nclgl\Frustum.h"
#include <algorithm>

#define LIGHTNUM 8

class Renderer :
	public OGLRenderer
{
public:
	Renderer(Window& parent);
	virtual ~Renderer(void);

	virtual void RenderScene();
	virtual void UpdateScene(float msec);

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

	Light* pointLights; // Array of lighting data
	Mesh* heightMap; // Terrain !
	OBJMesh* sphere; // Light volume
	Mesh* quad; // To draw a full - screen quad
	Camera* camera; // Our usual camera

	float rotation; // How much to increase rotation by

	GLuint bufferFBO; // FBO for our G- Buffer pass
	GLuint bufferColourTex; // Albedo goes here
	GLuint bufferNormalTex; // Normals go here
	GLuint bufferDepthTex; // Depth goes here

	GLuint pointLightFBO; // FBO for our lighting pass
	GLuint lightEmissiveTex; // Store emissive lighting
	GLuint lightSpecularTex; // Store specular lighting

	SceneNode* root;

	Frustum frameFrustum;

	vector<SceneNode*> transparentNodeList;
	vector<SceneNode*> nodeList;

	Window* window;
};


