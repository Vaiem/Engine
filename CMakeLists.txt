cmake_minimum_required(VERSION 3.23.2 FATAL_ERROR)


project(Engine)

add_executable(Engine 
   src/main.cpp
   src/Render/ShaderCreate.cpp
   src/Render/ShaderCreate.h
   src/ResourseManager/ResourseManager.cpp
   src/ResourseManager/ResourseManager.h
   src/ResourseManager/stb_image.h
   src/Render/TextureCreate.cpp
   src/Render/TextureCreate.h
   src/Render/Sprite.h
   src/Render/Sprite.cpp
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries (Engine glfw)


add_subdirectory(external/glad)
target_link_libraries (Engine glad)

include_directories(external/glm)
   
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET Engine POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:Engine>/res)