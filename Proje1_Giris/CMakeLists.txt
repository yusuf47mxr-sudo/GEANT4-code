# 1. CMake Versiyon Kontrolü
cmake_minimum_required(VERSION 3.16)

# 2. Proje İsmi
project(Proje1_Giris)

# 3. Geant4 Paketini Bul (EN ÖNEMLİ SATIR)
# Bu satır, bilgisayarındaki Geant4 kütüphanelerini (Physics, Geometry vs.) arar.
# "ui_all" ve "vis_all" -> Görselleştirme araçlarını da getir demektir.
find_package(Geant4 REQUIRED ui_all vis_all)

# 4. Geant4 Kütüphanelerini Dahil Et
include(${Geant4_USE_FILE})

# 5. Başlık Dosyalarının (.hh) Yerini Göster
include_directories(${PROJECT_SOURCE_DIR}/include)

# 6. Kaynak Dosyaları (.cc) Topla
# "file(GLOB ...)" komutu src klasöründeki tüm .cc dosyalarını bulur ve listeye ekler.
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# 7. Çalıştırılabilir Dosyayı (Executable) Oluştur
# Proje1.cc (main dosyamız) ve diğer kaynakları birleştir.
add_executable(Simulasyon 
Proje1.cc 
${sources} ${headers})

# 8. Linkleme (Bağlama)
# Bizim kodumuzu Geant4 kütüphanelerine bağla.
target_link_libraries(Simulasyon ${Geant4_LIBRARIES})

# 9. Veri Setlerini Kopyala (Opsiyonel ama iyi alışkanlık)
# Simülasyon çalışınca macro dosyalarını build klasörüne kopyalar.
# geant4_setup_macro_init()


