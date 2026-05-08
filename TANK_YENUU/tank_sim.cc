#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

// dosyaların başlıkları 
#include "TankDetectorConstruction.hh"
#include "TankPhysicsList.hh"
#include "TankPrimaryGeneratorAction.hh"

int main(int argc, char** argv)
{
    // Arayüzü başlat (Terminalden mi yoksa pencereyle mi açıldığını anlar)
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    // 1. OYUN MOTORUNU BAŞLAT (RunManager)
    G4RunManager* runManager = new G4RunManager;

    // 2. PARÇALARI MOTORLA BİRLEŞTİR 
    // Dedektör (Tank)
    runManager->SetUserInitialization(new TankDetectorConstruction());
    // Fizik (Optik ve EM)
    runManager->SetUserInitialization(new TankPhysicsList());
    // Mermi (Müon)
    runManager->SetUserAction(new TankPrimaryGeneratorAction());

    // Motoru başlat
    runManager->Initialize();

    // 3. GÖRSELLEŞTİRME YÖNETİCİSİ (Ekranı ve grafikleri çizmesi için)
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    // 4. EKRANI AÇ VE BEKLE
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    if (ui) {
       
        UImanager->ApplyCommand("/control/execute vis.mac"); // vis.mac dosyasını okuyacak
        ui->SessionStart();
        delete ui;
    } else {
        // Eğer terminalden bir mac dosyası verilirse arka planda çalışır
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    // İşimiz biti hafızayı temizle
    delete visManager;
    delete runManager;

    return 0;
}