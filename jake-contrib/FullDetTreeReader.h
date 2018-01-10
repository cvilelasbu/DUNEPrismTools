#include "TChain.h"

#include <iostream>
#include <string>

struct FullDetTreeReader {
  FullDetTreeReader(std::string treeName, std::string inputFiles) {
    tree = new TChain(treeName.c_str());

    NFiles = tree->Add(inputFiles.c_str());
    NEntries = tree->GetEntries();

    SetBranchAddresses();
    std::cout << "[FullDetTreeReader]: Loaded TChain: " << NFiles
              << " files and " << NEntries << " entries." << std::endl;
    GetEntry(0);
  }

  static const Int_t kNXBins = 400;
  static const Int_t kNYBins = 3;
  static const Int_t kNZBins = 3;

  Double_t Enu;
  Int_t nuPDG;
  Double_t vtx_X;
  Double_t vtx_Y;
  Double_t vtx_Z;
  Int_t eventNum;
  Int_t lepPDG;
  Int_t nLep;
  Double_t Q2True;
  Double_t yTrue;
  Double_t W_rest;
  Int_t nPi0;
  Int_t nPiC;
  Int_t nProton;
  Int_t nNeutron;
  Int_t nGamma;

  Double_t eLepTrue;
  Double_t ePi0True;
  Double_t ePiCTrue;
  Double_t eProtonTrue;
  Double_t eNeutronTrue;
  Double_t eGammaTrue;

  Double_t eLepPrimaryDep[kNXBins][kNYBins][kNZBins];
  Double_t eHadPrimaryDep[kNXBins][kNYBins][kNZBins];
  Double_t eProtonPrimaryDep[kNXBins][kNYBins][kNZBins];
  Double_t eNeutronPrimaryDep[kNXBins][kNYBins][kNZBins];
  Double_t ePiCPrimaryDep[kNXBins][kNYBins][kNZBins];
  Double_t ePi0PrimaryDep[kNXBins][kNYBins][kNZBins];
  Double_t eOtherPrimaryDep[kNXBins][kNYBins][kNZBins];

  Double_t eLepSecondaryDep[kNXBins][kNYBins][kNZBins];
  Double_t eHadSecondaryDep[kNXBins][kNYBins][kNZBins];
  Double_t eProtonSecondaryDep[kNXBins][kNYBins][kNZBins];
  Double_t eNeutronSecondaryDep[kNXBins][kNYBins][kNZBins];
  Double_t ePiCSecondaryDep[kNXBins][kNYBins][kNZBins];
  Double_t ePi0SecondaryDep[kNXBins][kNYBins][kNZBins];
  Double_t eOtherSecondaryDep[kNXBins][kNYBins][kNZBins];

  TChain *tree;
  UInt_t NFiles;
  UInt_t NEntries;
  UInt_t CEnt;

  void SetBranchAddresses() {
    tree->SetBranchAddress("Enu", &Enu);
    tree->SetBranchAddress("nuPDG", &nuPDG);
    tree->SetBranchAddress("vtx_X", &vtx_X);
    tree->SetBranchAddress("vtx_Y", &vtx_Y);
    tree->SetBranchAddress("vtx_Z", &vtx_Z);
    tree->SetBranchAddress("eventNum", &eventNum);
    tree->SetBranchAddress("lepPDG", &lepPDG);
    tree->SetBranchAddress("nLep", &nLep);
    tree->SetBranchAddress("Q2True", &Q2True);
    tree->SetBranchAddress("yTrue", &yTrue);
    tree->SetBranchAddress("W_rest", &W_rest);
    tree->SetBranchAddress("nPi0", &nPi0);
    tree->SetBranchAddress("nPiC", &nPiC);
    tree->SetBranchAddress("nProton", &nProton);
    tree->SetBranchAddress("nNeutron", &nNeutron);
    tree->SetBranchAddress("nGamma", &nGamma);

    tree->SetBranchAddress("eLepTrue", & eLepTrue);
    tree->SetBranchAddress("ePi0True", & ePi0True);
    tree->SetBranchAddress("ePiCTrue", & ePiCTrue);
    tree->SetBranchAddress("eProtonTrue", & eProtonTrue);
    tree->SetBranchAddress("eNeutronTrue", & eNeutronTrue);
    tree->SetBranchAddress("eGammaTrue", & eGammaTrue);

    tree->SetBranchAddress("eLepPrimaryDepFull", &eLepPrimaryDep);
    tree->SetBranchAddress("eHadPrimaryDep", &eHadPrimaryDep);
    tree->SetBranchAddress("eProtonPrimaryDep", &eProtonPrimaryDep);
    tree->SetBranchAddress("eNeutronPrimaryDep", &eNeutronPrimaryDep);
    tree->SetBranchAddress("ePiCPrimaryDep", &ePiCPrimaryDep);
    tree->SetBranchAddress("ePi0PrimaryDep", &ePi0PrimaryDep);
    tree->SetBranchAddress("eOtherPrimaryDep", &eOtherPrimaryDep);

    tree->SetBranchAddress("eLepSecondaryDepFull", &eLepSecondaryDep);
    tree->SetBranchAddress("eHadSecondaryDep", &eHadSecondaryDep);
    tree->SetBranchAddress("eProtonSecondaryDep", &eProtonSecondaryDep);
    tree->SetBranchAddress("eNeutronSecondaryDep", &eNeutronSecondaryDep);
    tree->SetBranchAddress("ePiCSecondaryDep", &ePiCSecondaryDep);
    tree->SetBranchAddress("ePi0SecondaryDep", &ePi0SecondaryDep);
    tree->SetBranchAddress("eOtherSecondaryDep", &eOtherSecondaryDep);
  }

  void GetEntry(UInt_t e) {
    CEnt = e;
    tree->GetEntry(CEnt);
  }

  UInt_t GetEntry() { return CEnt; }
  UInt_t GetEntries() { return NEntries; }

  ~FullDetTreeReader() { delete tree; };
};