
void calcSWeight_mT() {

  MLFit theFit;
  
  // define the structure of the dataset
  RooRealVar *pfmt = new RooRealVar("pfmt","p.f. m_{T}^{W}",20.0,150.,"GeV");

  theFit.AddFlatFileColumn(pfmt);
  
  // define a fit model
  theFit.addModel("myFit", "Inclusive WtoENu");
  
  // define species
  theFit.addSpecies("myFit", "sig",   "Signal Component");
  theFit.addSpecies("myFit", "qcd",   "QCD Component");
  theFit.addSpecies("myFit", "other", "Other Bkgs Component");

  // P.F. Mt PDF
  theFit.addPdfWName("myFit", "sig",   "pfmt", "DoubleCruijff", "sig_PfMt");
  theFit.addPdfWName("myFit", "qcd",   "pfmt", "Cruijff", "qcd_PfMt");
  theFit.addPdfWName("myFit", "other", "pfmt", "Cruijff", "other_PfMt");
  
  theFit.bind(MLStrList("sig_PfMt_sigmaR1","sig_PfMt_sigmaR2"),"sig_PfMt_sigmaR","sig_PfMt_sigmaR");
  theFit.bind(MLStrList("sig_PfMt_alphaR1","sig_PfMt_alphaR2"),"sig_PfMt_alphaR","sig_PfMt_alphaR");

  theFit.addDataSetFromRootFile("T1", "T1", "results_data/datasets/dataset_eg_Wenu_WithFlags.root");

  RooDataSet *data = theFit.getDataSet("T1");
  data = (RooDataSet*)data->reduce("nJets==0 && pfmet/pt>0.3 && isIsoWP80>0");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  theFit.initialize("fitres/WInclusive/fitMinimumWCandle-data.config");
  
  // fix all parameters, float the yields and fit
  theFit._parameterSet.selectByName("*")->setAttribAll("Constant",kTRUE);
  (static_cast<RooRealVar*>(theFit._parameterSet.find("N_sig")))->setConstant(kFALSE) ;
  (static_cast<RooRealVar*>(theFit._parameterSet.find("N_qcd")))->setConstant(kFALSE) ;
  
  RooFitResult *fitres =  myPdf->fitTo(*data,RooFit::ConditionalObservables(theFit.getNoNormVars("myFit")),RooFit::FitOptions("MHTER"));
  fitres->Print("V");

  // add appropriate column to dataset
  RooArgList yieldsList;
  yieldsList.add(*theFit._fracList.find("N_sig"));
  yieldsList.add(*theFit._fracList.find("N_qcd"));
  cout << "number of entries in set to write: " << data->numEntries() << endl ;
  RooArgSet nonormvars;
  RooDataSet* dsnew = MLSPlot::addSWeightToData((RooSimultaneous*)(myPdf), yieldsList, *data, nonormvars) ;

  TFile sPlots("results_data/sPlots/Wenu.root","recreate");
  cout << "number of entries in set to write: " << dsnew->numEntries() << endl ;
  dsnew->Write();
  sPlots.Close();
  
  TFile sPlotsTree("results_data/sPlots/Wenu_tree.root","recreate");
  TTree *tree = (TTree*)dsnew->tree();
  tree->Write();
  sPlotsTree.Close();

}
