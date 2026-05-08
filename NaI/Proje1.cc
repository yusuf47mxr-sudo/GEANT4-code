#include <iostream>

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

// --- BÖLÜM 1: KÜTÜPHANELERİN ÇAĞRILMASI ---

#include "G4RunManagerFactory.hh" // Fabrika (Şefi yaratan yer)
#include "G4UImanager.hh"        // Arayüz Yöneticisi (Komutları anlayan)
#include "G4VisExecutive.hh"     // Görselleştirme Yöneticisi (Çizim yapan)
#include "G4UIExecutive.hh"      // Pencere Yöneticisi (GUI açan)

int main(int argc, char** argv)
{


    auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

    // 1. Şefe Dedektörü Tanıt (Geometriyi ver)
    runManager->SetUserInitialization(new DetectorConstruction());

    // 2. Şefe Fizik Listesini Tanıt (Yasaları ver)
    runManager->SetUserInitialization(new PhysicsList());

    // 3. Aksiyon (Tabanca) <--- YENİ!
    runManager->SetUserInitialization(new ActionInitialization());




    // --- BÖLÜM 3: RESSAM (VISUALIZATION MANAGER) ---

    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    // --- BÖLÜM 4: TERCÜMAN (UI MANAGER) ---

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // --- BÖLÜM 5: PENCERE MANTIĞI (IF-ELSE) ---

    
    if (argc == 1) { 
    
        
        G4UIExecutive* ui = new G4UIExecutive(argc, argv); // Pencereyi (Qt veya OpenGL) aç.
        

        
        ui->SessionStart(); // PENCEREYİ AÇIK TUT. Sen kapatana kadar bekle.
        delete ui;
    }
    else {

        
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    // --- BÖLÜM 6: TEMİZLİK (DESTRUCTOR) ---
//(Memory Leak olmasın diye).
    delete visManager;
    delete runManager;

    return 0;
}
