cmake_minimum_required (VERSION 3.8)
project(ML_Numbers VERSION 1.0)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ML_Numbers)
set (CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE SOURCE "Source/*.*")

include_directories(${PROJECT_SOURCE_DIR}/Library/SDL2-2.0.12/include)
set(SDL2_LIBRARIES "${PROJECT_SOURCE_DIR}/Library/SDL2-2.0.12/lib/x64/SDL2.lib")

file(GLOB DLLS "DLLs/x64/*.dll")
file(COPY ${DLLS} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/Release)
file(COPY ${DLLS} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/Debug)
file(COPY ${DLLS} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/MinSizeRel)
file(COPY ${DLLS} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/RelWithDebInfo)

add_executable(ML_Numbers ${SOURCE})

target_link_libraries(ML_Numbers ${SDL2_LIBRARIES})


