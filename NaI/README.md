# NaI

Geant4 tabanlı bir simülasyon: silindirik bir NaI(Tl) sintilasyon kristaline
gönderilen Co-60 kaynaklı gama fotonlarının kristal içinde biriktirdiği
enerjinin ölçülmesi. Amaç, bir NaI(Tl) dedektörünün Co-60 kalibrasyon
kaynağına tepkisini (foto-pik ve Compton sürekli bölgesi) enerji biriktirme
seviyesinde modellemektir.

## Fiziksel Motivasyon

- Kristalin altından, +z yönünde tek yönlü bir gama demeti gönderilir
  (`PrimaryGeneratorAction`).
- Her foton, %50 olasılıkla 1.1732 MeV, %50 olasılıkla 1.3325 MeV enerjiyle
  üretilir — Co-60 kaynağının iki karakteristik gama hattı.
- Kristal, ağırlıkça %15.3 Na, %84.6 I, %0.1 Tl bileşiminde, 3.67 g/cm³
  yoğunluğunda özel tanımlı "NaITl" malzemesinden oluşur (`DetectorConstruction`).
- Fizik listesi standart elektromanyetik etkileşimler ve bozunum süreçlerini
  içerir; optik foton taşınımı (ışık toplama, PMT yanıtı) modellenmez —
  simülasyon ham enerji depozisyonu seviyesinde çalışır.
- Kristalde biriken toplam enerji, olay başına `SteppingAction`/`EventAction`
  tarafından toplanır ve bir ROOT ntuple'ına yazılır.

## Proje Yapısı

```
NaI/
├── include/    # Sınıf başlıkları (.hh)
├── src/        # Sınıf implementasyonları (.cc)
├── Proje1.cc   # main() - programın giriş noktası
└── CMakeLists.txt # Derleme yapılandırması
```

## Gereksinimler

- Geant4 (11.x önerilir), CMake >= 3.16
- C++ derleyici (GCC/Clang)

## Derleme

```bash
mkdir -p build && cd build
cmake ..
make -j$(nproc)
```

Derleme sonucunda `Simulasyon` çalıştırılabilir dosyası üretilir.

## Çalıştırma

Görsel (interaktif) mod:

```bash
./Simulasyon
```

Toplu (batch) mod, bir makro dosyası ile:

```bash
./Simulasyon run.mac
```

Çıktı, çalışma dizininde `Veri.root` dosyasına yazılır. Ntuple: `Olaylar`,
tek sütun `Enerji_MeV` — olay başına kristalde biriken toplam enerji.

## Bilinen Sınırlamalar / Yapılacaklar

- Enerji biriktirme, kristale özel bir hassas hacim (sensitive detector)
  yerine world içindeki tüm adımlar üzerinden toplanmaktadır.
- Optik foton üretimi/toplama fiziği aktif değildir; gerçek bir NaI(Tl)
  dedektörünün enerji çözünürlüğü (ışık verimi, PMT gürültüsü) bu
  simülasyonda temsil edilmez.
