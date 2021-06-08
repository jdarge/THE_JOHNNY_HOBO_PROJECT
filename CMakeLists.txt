# PROJ
cmake_minimum_required(VERSION 3.19)
project(music_player C)

# BASE
set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES main.c)
set(THIS ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(resources)

# LOCATION OF HEADER FILES
set(FMOD_DIR "${THIS}/fmod/api/lowlevel/lib/")# could use files in project
#set(FMOD_DIR "C:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/core/lib/x64")# could use files in project
include_directories(${FMOD_DIR} ${RAYLIB_DIREC})

# RAYLIB SPECIFIC
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

# EXECUTABLE
add_executable(music_player ${SOURCE_FILES})


add_subdirectory(libs/raylib)
target_link_libraries(music_player raylib)


include_directories(${FMOD_DIR})
target_link_libraries(music_player "${FMOD_DIR}/fmod_vc.lib" "${FMOD_DIR}/fmodL_vc.lib")


# BUILDING
#target_compile_definitions(music_player PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(raylib_template PUBLIC ASSETS_PATH="relative-path-to-assets-in-the-game-package") # Set the asset path macro in release more

