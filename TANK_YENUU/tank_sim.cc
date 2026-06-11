#include "G4MTRunManager.hh" // ARTIK MT (Multi-Thread) YÖNETİCİSİ KULLANIYORUZ
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "TankDetectorConstruction.hh"
#include "TankPhysicsList.hh"
#include "TankActionInitialization.hh" // YENİ EKLEDİĞİMİZ SINIF

int main(int argc, char** argv)
{
    // Arayüzü başlat
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    // 1. OYUN MOTORUNU BAŞLAT (Çoklu Çekirdek Motoru)
    G4MTRunManager* runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(12); // 12 ÇEKİRDEK BURADA BELİRLENİYOR!

    // 2. PARÇALARI MOTORLA BİRLEŞTİR 
    runManager->SetUserInitialization(new TankDetectorConstruction());
    runManager->SetUserInitialization(new TankPhysicsList());
    
    // YENİ YAPI: Action sınıflarını paketlediğimiz sınıfı motora veriyoruz
    runManager->SetUserInitialization(new TankActionInitialization());

    // Motoru başlat
    runManager->Initialize();

    // 3. GÖRSELLEŞTİRME YÖNETİCİSİ
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    // 4. EKRANI AÇ VE BEKLE
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    if (ui) {
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    } else {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    // İşimiz bitti hafızayı temizle
    delete visManager;
    delete runManager;

    return 0;
}