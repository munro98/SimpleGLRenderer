add_library(stb_image
	stb_image.c

)

target_include_directories(stb_image PUBLIC "${PROJECT_SOURCE_DIR}/ext/stb_image")