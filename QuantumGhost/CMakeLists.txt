cmake_minimum_required(VERSION 3.16...3.27)
project(QuantumGhost)

# Geant4'ü sistemde bul ve arayüz/görselleştirme modüllerini aktif et
find_package(Geant4 REQUIRED ui_all vis_all)

# Geant4'ün standart ayarlarını projeye dahil et
include(${Geant4_USE_FILE})

# Kendi başlık (header) dosyalarımızın nerede olduğunu göster
include_directories(${PROJECT_SOURCE_DIR}/include)

# Tüm kaynak (.cc) dosyalarını topla
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# QuantumGhost adında bir çalıştırılabilir dosya (executable) üret
add_executable(QuantumGhost QuantumGhost.cc ${sources} ${headers})

# Üretilen programa Geant4 kütüphanelerini bağla
target_link_libraries(QuantumGhost ${Geant4_LIBRARIES})