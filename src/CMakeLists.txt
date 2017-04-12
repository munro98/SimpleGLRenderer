
#TODO Add header files
SET(headers
	"Shader.hpp"
	"SimpleGUI.hpp"
	"TriangleRenderer.hpp"
	"CoreRenderer.hpp"
	"ModelRenderer.hpp"
	"OBJLoader.hpp"
	"Mesh.hpp"
	"Model.hpp"
	"ModelShader.hpp"
	"Loader.hpp"
	"Camera.hpp"
	"Texture.hpp"
	"stb_image.h"
)


#TODO Add sources
SET(sources
	"main.cpp"
	"SimpleGUI.cpp"
	"Shader.cpp"
	"TriangleRenderer.cpp"
	"CoreRenderer.cpp"
	"ModelRenderer.cpp"
	"OBJLoader.cpp"
	"Mesh.cpp"
	"Model.cpp"
	"ModelShader.cpp"
	"Loader.cpp"
	"Camera.cpp"
	"Texture.cpp"
	"stb_image.c"
)

#Add executable target
add_executable(${SIMPLE_GL_RENDERER} ${headers} ${sources})
#Link libraries
target_link_libraries(${SIMPLE_GL_RENDERER} PRIVATE glew glfw ${GLFW_LIBRARIES})
target_link_libraries(${SIMPLE_GL_RENDERER} PRIVATE imgui)