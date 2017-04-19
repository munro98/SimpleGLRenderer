
#TODO Add header files
SET(headers
	"Shader.hpp"
	"SimpleGUI.hpp"
	"TriangleRenderer.hpp"
	"CoreRenderer.hpp"
	"ModelRenderer.hpp"
	"PBRModelRenderer.hpp"
	"OBJLoader.hpp"
	"Mesh.hpp"
	"Model.hpp"
	"ModelShader.hpp"
	"PBRModelShader.hpp"
	"Loader.hpp"
	"Camera.hpp"
	"Texture.hpp"
	"SkyboxShader.hpp"
	"SkyboxRenderer.hpp"
	"Terrain.hpp"
	"TerrainRenderer.hpp"
	"HeightGenerator.hpp"

)


#TODO Add sources
SET(sources
	"main.cpp"
	"SimpleGUI.cpp"
	"Shader.cpp"
	"TriangleRenderer.cpp"
	"CoreRenderer.cpp"
	"ModelRenderer.cpp"
	"PBRModelRenderer.cpp"
	"OBJLoader.cpp"
	"Mesh.cpp"
	"Model.cpp"
	"ModelShader.cpp"
	"PBRModelShader.cpp"
	"Loader.cpp"
	"Camera.cpp"
	"Texture.cpp"
	"SkyboxShader.cpp"
	"SkyboxRenderer.cpp"
	"Terrain.cpp"
	"TerrainRenderer.cpp"
	"HeightGenerator.cpp"
)

#Add executable target
add_executable(${SIMPLE_GL_RENDERER} ${headers} ${sources})
#Link libraries
target_link_libraries(${SIMPLE_GL_RENDERER} PRIVATE glew glfw ${GLFW_LIBRARIES})
target_link_libraries(${SIMPLE_GL_RENDERER} PRIVATE imgui)
target_link_libraries(${SIMPLE_GL_RENDERER} PRIVATE stb_image)