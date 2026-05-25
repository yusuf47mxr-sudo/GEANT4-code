#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

// Kendi yazdığımız sınıfları dahil ediyoruz
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

int main(int argc, char** argv)
{
    // 1. Arayüz (UI) Yöneticisini Başlat
    // Eğer terminalden bir makro dosyası girilmemişse (argc == 1), görsel arayüzü aç.
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    // 2. Geant4 Ana Motorunu (RunManager) Yarat
    G4RunManager* runManager = new G4RunManager;

    // 3. ZORUNLU ATAMALAR (Kendi yazdığımız sınıfları motora bağlıyoruz)
    runManager->SetUserInitialization(new DetectorConstruction()); // Geometri
    runManager->SetUserInitialization(new PhysicsList());          // Kuantum Fizik Kuralları
    runManager->SetUserInitialization(new ActionInitialization());   // Jeneratör ve Veri Kaydı

    // 4. Görselleştirme (VisManager) Yöneticisini Başlat
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    // 5. Kullanıcı Komut Yöneticisini Al
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (ui) {
        // Etkileşimli Mod: Görsel arayüz açılır
        // Arayüz açıldığında çalıştırılacak varsayılan görselleştirme komutları
        UImanager->ApplyCommand("/control/execute vis.mac"); 
        ui->SessionStart();
        delete ui;
    } else {
        // Toplu (Batch) Mod: Terminalden " ./QuantumGhost run.mac " yazılırsa çalışır
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    // 6. Hafızayı Temizle ve Çık
    delete visManager;
    delete runManager;
    
    return 0;
}