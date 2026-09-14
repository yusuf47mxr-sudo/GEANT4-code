# QuantumGhost

Geant4 tabanlı bir simülasyon: merkezden zıt yönlere (+Z ve -Z) gönderilen,
polarizasyonları birbirine dik (dolanık/entangled) iki foton çiftinin, iki
kolda yer alan saçıcı-soğurucu dedektör çiftleriyle Compton saçılması yoluyla
incelenmesi. Fikri temel, Wu-Shaknov (1950) deneyinin bir dijital/simülasyon
versiyonudur: foton polarizasyon korelasyonunun Compton saçılma açısı
dağılımı üzerinden gözlemlenmesi.

## Fiziksel Motivasyon

- Kaynaktan 511 keV enerjili iki gamma fotonu, zıt yönlerde (+Z / -Z) ve
  birbirine dik polarizasyon vektörleriyle üretilir (`PrimaryGeneratorAction`).
- Her foton, kendi kolundaki saçıcı (polystyrene) hacimde Compton saçılmasına
  girer, ardından soğurucu (BGO) halka tarafından yutulur.
- Polarizasyona duyarlı Compton saçılması için standart EM fizik listesi
  yerine `G4EmLivermorePolarizedPhysics` kullanılır (`PhysicsList`).
- Her etkileşim (EventID, hacim, enerji, pozisyon) `PolarimeterSD` tarafından
  bir ROOT ntuple'ına kaydedilir; korelasyon analizi bu veriler üzerinden
  ayrı bir Python/Uproot betiğinde yapılır.

## Proje Yapısı

```
QuantumGhost/
├── include/        # Sınıf başlıkları (.hh)
├── src/            # Sınıf implementasyonları (.cc)
├── QuantumGhost.cc # main() - programın giriş noktası
├── CMakeLists.txt  # Derleme yapılandırması
├── run.mac         # Toplu (batch) mod çalıştırma makrosu
├── run2.mac        # Alternatif çalıştırma makrosu
└── vis.mac         # Görselleştirme (interaktif mod) makrosu
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

## Çalıştırma

Görsel (interaktif) mod:

```bash
./QuantumGhost
```

Toplu (batch) mod, örneğin 10.000 olay için:

```bash
./QuantumGhost run.mac
```

Çıktı, çalışma dizininde `QuantumPolarimeterData.root` dosyasına yazılır.
Sütunlar: `EventID`, `VolumeID` (1: Saçıcı, 2: Soğurucu), `Energy_keV`,
`PosX_mm`, `PosY_mm`, `PosZ_mm`.

## Bilinen Sınırlamalar / Yapılacaklar

- Geometri ve enerji parametreleri şu an kod içinde sabit; bir
  `G4UImessenger` ile makro üzerinden değiştirilebilir hale getirilebilir.
- Korelasyon (Bell-tipi eşitsizlik) analizi bu depoda değil, ayrı bir analiz
  betiğinde yapılmaktadır.
