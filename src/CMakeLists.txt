cmake_minimum_required(VERSION 3.17.0)

project(Promyczek)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})


set(SOURCES Main.cpp Image.cpp Viewer/Viewer.cpp Math/Vec3.cpp Model/World.cpp Model/Sphere.cpp Rendering/Raytracer.cpp)
  
add_executable(PromyczekRenderer ${SOURCES}) 
target_compile_features(PromyczekRenderer PUBLIC cxx_std_20)
target_link_libraries(PromyczekRenderer 
    PRIVATE
        stb 
        ${GTK3_LIBRARIES} 
        ${GTKMM_LIBRARIES})