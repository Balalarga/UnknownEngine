cmake_minimum_required(VERSION 3.15)

project(OpenglWrapper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(THIRDPARTY_DIR ThirdParty)
# Windows libs only
set(LIBS mingw32 opengl32 glu32 Imm32)


# GLEW setup
set(GLEW_DIR ${THIRDPARTY_DIR}/GLEW)
link_directories(${GLEW_DIR}/lib/x64)
include_directories(${GLEW_DIR}/include)
set(BINARIES ${GLEW_DIR}/bin/x64)
set(LIBS ${LIBS} glew32)


# GLM includes
include_directories(${THIRDPARTY_DIR}/glm)


# SDL2 setup
set(SDL2_DIR ${THIRDPARTY_DIR}/SDL2_mingw/x64)
link_directories(${SDL2_DIR}/lib)
include_directories(${SDL2_DIR}/include/SDL2)
set(LIBS ${LIBS} SDL2main SDL2 SDL2_image SDL2_ttf)
set(BINARIES ${BINARIES} ${SDL2_DIR}/bin)


set(USE_IMGUI OFF)
if (${USE_IMGUI})
# ImGui setup
    add_compile_definitions(USE_IMGUI=1)
    add_library(ImGui
            # Main Imgui files
            ${THIRDPARTY_DIR}/ImGui/imgui.cpp
            ${THIRDPARTY_DIR}/ImGui/imgui_draw.cpp
            ${THIRDPARTY_DIR}/ImGui/imgui_tables.cpp
            ${THIRDPARTY_DIR}/ImGui/imgui_widgets.cpp
            # SDL2+OpenGL-specific files
            ${THIRDPARTY_DIR}/ImGui/backends/imgui_impl_sdl.cpp
            ${THIRDPARTY_DIR}/ImGui/backends/imgui_impl_opengl3.cpp)
    target_include_directories(ImGui PUBLIC ${THIRDPARTY_DIR}/ImGui/ ${THIRDPARTY_DIR}/ImGui/backends/)
    target_link_libraries(ImGui ${LIBS})
    set(LIBS ${LIBS} ImGui)
else()
    add_compile_definitions(USE_IMGUI=0)
endif()


# Find all source files
file(GLOB_RECURSE PROJECT_SOURCES Sources/*.cpp Sources/*.h Sources/*.hpp)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} ${LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE Sources)


if (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json)
    #configure_file(${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json COPYONLY)
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/compile_commands.json $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()


# Copy dll files
foreach(BINARY ${BINARIES})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/${BINARY} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endforeach()
