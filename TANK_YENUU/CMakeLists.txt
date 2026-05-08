cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(TankSim)

# Geant4'ü ve görselleştirme araçlarını bul
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

# Başlık (.hh) dosyalarımızın nerede olduğunu söylüyor
include_directories(${PROJECT_SOURCE_DIR}/include)

# src ve include içindeki tüm dosyaları otomatik topla
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Ana programı derle
add_executable(Okey_DOKEY tank_sim.cc ${sources} ${headers})
target_link_libraries(Okey_DOKEY ${Geant4_LIBRARIES})