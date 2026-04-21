#include <iostream>

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

// --- BÖLÜM 1: KÜTÜPHANELERİN ÇAĞRILMASI ---
// Bu ".hh" dosyaları, Geant4'ün yönetici kadrosunun telefon numaralarıdır.
// Onları dahil etmezsek "RunManager kim?" diye hata alırız.
#include "G4RunManagerFactory.hh" // Fabrika (Şefi yaratan yer)
#include "G4UImanager.hh"        // Arayüz Yöneticisi (Komutları anlayan)
#include "G4VisExecutive.hh"     // Görselleştirme Yöneticisi (Çizim yapan)
#include "G4UIExecutive.hh"      // Pencere Yöneticisi (GUI açan)

int main(int argc, char** argv)
{

    // Burası simülasyonun kalbidir.
    // G4RunManagerFactory::CreateRunManager(...): Bu modern bir yöntemdir.
    // Bilgisayarının gücüne bakar; eğer çok çekirdekli ise "Multi-Threaded (MT)",
    // değilse "Serial (Tek çekirdek)" modunda bir şef yaratır.
    // Şefin görevi: Dedektörü, fiziği ve silahı koordine etmektir.
    auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

    // 1. Şefe Dedektörü Tanıt (Geometriyi ver)
    runManager->SetUserInitialization(new DetectorConstruction());

    // 2. Şefe Fizik Listesini Tanıt (Yasaları ver)
    runManager->SetUserInitialization(new PhysicsList());

    // 3. Aksiyon (Tabanca) <--- YENİ!
    runManager->SetUserInitialization(new ActionInitialization());




    // --- BÖLÜM 3: RESSAM (VISUALIZATION MANAGER) ---
    // Simülasyon kör çalışmasın diye bir "Ressam" tutuyoruz.
    // G4VisExecutive: Bu arkadaş, dedektörünü ve parçacık izlerini ekrana çizer.
    // Initialize(): Ressam fırçasını, boyasını hazırlar (OpenGL sürücülerini yükler).
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    // --- BÖLÜM 4: TERCÜMAN (UI MANAGER) ---
    // Sen klavyeden "/run/beamOn 100" yazdığında C++ bunu anlamaz.
    // UImanager, senin yazdığın metni C++ koduna çevirip çekirdeğe iletir.
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // --- BÖLÜM 5: PENCERE MANTIĞI (IF-ELSE) ---
    // Burası çok zekice bir ayrımdır.
    // argc: Programa girilen parametre sayısı.
    
    if (argc == 1) { 
        // DURUM A: Sen sadece "./Simulasyon" yazdın ve Enter'a bastın.
        // Bilgisayar anlar ki: "Hoca grafikleri görmek istiyor, pencere açayım."
        
        G4UIExecutive* ui = new G4UIExecutive(argc, argv); // Pencereyi (Qt veya OpenGL) aç.
        
        // Ekrana ilk görüntüyü getirmesi için "vis.mac" dosyasını okumasını söylüyoruz.
        // (Bu dosya henüz yok, o yüzden hata verebilir ama mantık budur).
        //UImanager->ApplyCommand("/control/execute vis.mac"); 
        
        ui->SessionStart(); // PENCEREYİ AÇIK TUT. Sen kapatana kadar bekle.
        delete ui;
    }
    else {
        // DURUM B: Sen "./Simulasyon run.mac" yazdın.
        // Bilgisayar anlar ki: "Hoca pencere istemiyor, arkada hızlıca hesap yapıp çıkacak."
        // Pencere açmaz, sadece verilen dosyayı okur ve kapanır.
        
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    // --- BÖLÜM 6: TEMİZLİK (DESTRUCTOR) ---
    // İşi biten yöneticileri hafızadan siliyoruz (Memory Leak olmasın diye).
    delete visManager;
    delete runManager;

    return 0;
}