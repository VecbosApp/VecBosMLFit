#include <TChain.h>
#include <TMath.h>
#include <TFile.h>
#include <TSystem.h>

#include <RooDataSet.h>
#include <RooRealVar.h>
#include <RooCategory.h>

#include <iostream>

using namespace std;


void createDataset(const char *treefile, const char *roofitfile) {

  cout << "roofitting file " << treefile << " in " << roofitfile << endl;

  // kinematic variables
  RooRealVar *pfmt = new RooRealVar("pfmt","m_{T}^{W}",20.0,150,"GeV");
  RooRealVar *nExclPFJetsHi = new RooRealVar("nExclPFJetsHi","n. of Hi Thr PF jets",0.0,5.0);
  RooRealVar *nBTagJets = new RooRealVar("nBTagJets","n. of b-tagged jets",0.0,3.0);
  RooRealVar *nB = new RooRealVar("nB","n. of MC truth B-Had matching jets",0.0,3.0);

  RooArgSet totalSet(*pfmt,*nBTagJets,*nB,*nExclPFJetsHi);

  TFile *file = TFile::Open(treefile);
  TTree *tree = (TTree*)file->Get("T1");
  RooDataSet *data = new RooDataSet("TopJets","dataset",tree,totalSet);

  TFile *roofitFile = TFile::Open(roofitfile,"recreate");
  for(int jet=1; jet<5; jet++) {
    std::cout << "\tN JETS = " << jet << std::endl;
    for(int nb=0; nb<3; nb++) {

      char cut[200];
      sprintf(cut,"nExclPFJetsHi==%d && nB==%d",jet,nb);

      char specname[200];
      sprintf(specname,"top%db_%dj",nb,jet);

      RooDataSet *reducedDS = (RooDataSet*)data->reduce(cut);
      reducedDS->SetName(specname);
      cout << "\tdataset with nJets = " << jet << " and nB = " << nb << " has " << reducedDS->numEntries() << " entries." << endl;
      reducedDS->Write();
    }
  }

  roofitFile->Close();

  int event;
  RooRealVar *eventVar = new RooRealVar("event","event",0,100000);
  RooArgSet eventSet(*eventVar);

  TFile *outFile = TFile::Open("mockFinal.root","recreate");

  // adding event to the datasets
  for(int jet=1; jet<5; jet++) {
    std::cout << "\tN JETS = " << jet << std::endl;
    for(int nb=0; nb<3; nb++) {
      TFile *origFile = TFile::Open(roofitfile);
      char specname[200];
      sprintf(specname,"top%db_%dj",nb,jet);
      RooDataSet *dataset = (RooDataSet*)origFile->Get(specname);
      int nentries = dataset->numEntries();

      // create and fill a tree (one column with the consecutive number of event)
      outFile->cd();
      TTree *eventTree = new TTree("eventTree","eventTree");
      eventTree->Branch("event", &event);
      for(int i=0; i<nentries; i++) {
        event=i;
        eventTree->Fill();
      }
      RooDataSet *eventData = new RooDataSet("eventTree","eventTree",eventTree,eventSet);

      // now merge the dataset with the event column
      outFile->cd();
      dataset->merge(eventData);
      dataset->Write();
    }
  }

  outFile->Close();

}

