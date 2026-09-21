# TANK_YENUU

Geant4 tabanlı bir su-Cherenkov dedektör simülasyonu: silindirik bir su
tankının merkezinden geçirilen yüklü parçacıkların (müon, pion, elektron)
ürettiği Cherenkov ışığının ve enerji biriktirmesinin, parçacık türüne ve
enerjisine bağlı olarak incelenmesi.

## Fiziksel Motivasyon

- Tank, 52.5 cm yarıçapında ve 120 cm yüksekliğinde, suyla dolu silindirik
  bir hacimdir (`TankDetectorConstruction`). Duvarlarına tamamen ışık yutucu
  ("zifiri karanlık") bir optik yüzey tanımlanmıştır; böylece yalnızca tek
  geçişte üretilen Cherenkov fotonları gözlemlenir, çoklu yansıma/toplama
  modellenmez.
- Suya RINDEX = 1.33 sabit kırılma indisiyle bir malzeme özellik tablosu
  tanımlanmıştır, bu da Cherenkov ışığı üretimi için gereklidir.
- Parçacıklar tankın üstünden, merkez eksen boyunca (-z yönünde) tek yönlü
  olarak gönderilir (`TankPrimaryGeneratorAction`).
- Fizik listesi standart elektromanyetik süreçlerin yanında
  `G4OpticalPhysics` içerir, böylece Cherenkov ışığı üretimi ve taşınımı
  aktif olarak simüle edilir.
- Her adımda üretilen ikincil optik fotonlar arasından Cherenkov sürecinden
  gelenler ayıklanır; bu fotonların ana parçacığın hareket yönüyle yaptığı
  açı (Cherenkov açısı) hesaplanır (`TankSteppingAction`).
- Olay başına toplam enerji biriktirme ve üretilen foton sayısı, her
  Cherenkov fotonu için de saçılma açısı, iki ayrı ROOT ntuple'ına yazılır
  (`TankRunAction`).

## Proje Yapısı

```
TANK_YENUU/
├── include/     # Sınıf başlıkları (.hh)
├── src/         # Sınıf implementasyonları (.cc)
├── tank_sim.cc  # main() - programın giriş noktası
├── CMakeLists.txt # Derleme yapılandırması
├── muyon.mac    # mu- için 100 MeV - 1.5 GeV arası enerji taraması
├── pion.mac     # pi- için 100 MeV - 1.5 GeV arası enerji taraması
├── electron.mac # e- için 100 MeV - 1.5 GeV arası enerji taraması
└── vis.mac      # Görselleştirme (interaktif mod) makrosu
```

## Gereksinimler

- Geant4 (11.x önerilir, Optik fizik desteğiyle derlenmiş), CMake >= 3.16
- C++ derleyici (GCC/Clang)

## Derleme

```bash
mkdir -p build && cd build
cmake ..
make -j$(nproc)
```

Derleme sonucunda `Okey_DOKEY` çalıştırılabilir dosyası üretilir. Simülasyon,
çoklu iş parçacığı (multi-threading) desteğiyle 12 thread üzerinde çalışacak
şekilde yapılandırılmıştır.

## Çalıştırma

Görsel (interaktif) mod, `vis.mac` otomatik olarak çalıştırılır:

```bash
./Okey_DOKEY
```

Toplu (batch) mod, örneğin müon taraması için:

```bash
./Okey_DOKEY muyon.mac
```

Her enerji noktası için ayrı bir ROOT dosyası üretilir (örn.
`muyon_100MeV.root`, `pion_1GeV.root`, `electron_1.5GeV.root`).

Ntuple'lar:
- `TankData`: `Edep` (double, MeV), `Photons` (int) — olay başına.
- `PhotonData`: `CherenkovAngle` (double, derece) — üretilen her Cherenkov
  fotonu için ayrı satır.

## Bilinen Sınırlamalar / Yapılacaklar

- Hadronik fizik süreçleri kayıtlı değildir; pion gibi hadronlar için nükleer
  etkileşim/absorpsiyon modellenmez, yalnızca elektromanyetik enerji kaybı
  hesaplanır.
- Enerji ve foton sayımı, tanka özel bir hassas hacim yerine world içindeki
  tüm adımlar üzerinden toplanmaktadır.
