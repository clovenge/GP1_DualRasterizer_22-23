#pragma once
#include <cstdint>
#include <vector>
#include "Camera.h"
#include "DataTypes.h"
#include <memory>
#include "BaseRenderer.h"


struct SDL_Window;
struct SDL_Surface;

namespace dae
{
	class Texture;
	struct Mesh;
	struct Vertex;
	class Timer;
	class Scene;

	class SoftwareRenderer : virtual public BaseRenderer
	{
	public:
		SoftwareRenderer(SDL_Window* pWindow);
		~SoftwareRenderer();

		void Update(Timer* pTimer);
		void Render();

		bool SaveBufferToImage() const;

		void ToggleDepthBuffer();
		void ToggleRenderOutput();
		void ToggleNormalMap();
		void ToggleBoundingBox();
		void ToggleUniformColor();
		void SWToggleCullMode();
		void Initialize(std::vector<Texture*>& mainTextures, Camera* pCamera, Mesh& vehicleMesh);

	private:

		SDL_Surface* m_pFrontBuffer{ nullptr };
		SDL_Surface* m_pBackBuffer{ nullptr };
		uint32_t* m_pBackBufferPixels{};

		Texture* m_pDiffuseTexture{ nullptr };
		Texture* m_pNormalTexture{ nullptr };
		Texture* m_pGlossTexture{ nullptr };
		Texture* m_pSpecularTexture{ nullptr };
		

		float* m_pDepthBufferPixels{};

		Camera* m_pCamera{};

		std::vector<Vector3> m_Veritces_ScreenSpace;
		float m_AspectRatio;
		bool m_DepthBuffer{false};
		bool m_NormalMapToggle{true};
		bool m_RotationToggle{true};

		
		Mesh* m_pMesh;

		bool m_IsMeshLoadedIn;
		bool m_BoundingBoxVisualization;
		

		//Function that transforms the vertices from the mesh from World space to Screen space
		void VertexTransformationFunction(Mesh& mesh) const;

		bool IsInTriangle(const std::vector<Vector2>& verticesScreenspace, const Vector2& pixelPos);
		
		void render_W4_Part1();

		float Remap(float value, float minValue, float maxValue);
		bool FustrumCulling(const Vector3 v0, const Vector3 v1, const Vector3 v2);
		void ToScreenSpace(Vector4& v0, Vector4& v1, Vector4& v2);

		void BoundingBox(Vector2& topLeft, Vector2& bottomRight, std::vector<Vector2> v);
		

		ColorRGB PixelShading(const Vertex_Out& v);

		enum class RenderState
		{
			observedArea, lambert, phong, combined
		};

		RenderState m_CurrentRenderState;

		bool m_IsUniform;

		enum class CullMode
		{
			backFace, frontFace, none,  size = 3
		};

		CullMode m_CullMode;
		
	};
}
