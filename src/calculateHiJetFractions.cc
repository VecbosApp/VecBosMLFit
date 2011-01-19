#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include <iostream>

void calc(const char* filename) {

  TFile *file = TFile::Open(filename);
  TTree *tree = (TTree*)file->Get("T1");
  
  TH1F *numH = new TH1F("numH","numH",5,0,5);
  TH1F *denomH = new TH1F("denomH","denomH",5,0,5);

  char normalizationStr[200];
  char numeratorStr[200];
  for(int njLo=1; njLo<=4; ++njLo) {
    cout << "=== Sample: " << filename << "\t nJ(15 GeV) = " << njLo << " ===" << endl;
    sprintf(normalizationStr,"(nExclPFJetsLo==%d && nB==2)*weight",njLo);
    for(int njHi=0; njHi<=njLo; ++njHi) {
      sprintf(numeratorStr,"(nExclPFJetsLo==%d && nExclPFJetsHi==%d && nB==2)*weight",njLo,njHi);
      tree->Project("denomH","nExclPFJetsHi",normalizationStr);
      tree->Project("numH","nExclPFJetsHi",numeratorStr);
      float num = numH->Integral();
      float denom = denomH->Integral();
      cout << "nj Hi = " << njHi << "\tfrac = " << num/denom << endl;
    }
  }

}
