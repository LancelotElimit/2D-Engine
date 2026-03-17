cmake_minimum_required(VERSION 3.16)
project(SDLTest)

if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT
        "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,
        $<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,
        $<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL3 / SDL3_image
add_subdirectory(external/SDL)

set(SDLIMAGE_VENDORED OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(external/SDL_image)

# 头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 可执行程序
add_executable(SDLTest
    src/SDLTest.cpp
)

# 链接库
target_link_libraries(SDLTest PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
)

# 复制 asset 文件夹到 exe 目录
add_custom_command(TARGET SDLTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/asset
        $<TARGET_FILE_DIR:SDLTest>/asset
)

# 自动复制 SDL3.dll 到 exe 目录
add_custom_command(TARGET SDLTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE_DIR:SDLTest>
)

# 自动复制 SDL3_image.dll 到 exe 目录
add_custom_command(TARGET SDLTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3_image::SDL3_image>
        $<TARGET_FILE_DIR:SDLTest>
)