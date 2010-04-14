void calcSWeight_mT() {

  MLFit theFit;
  
  // define the structure of the dataset
  RooRealVar *pfmt = new RooRealVar("pfmt","p.f. m_{T}^{W}",10.0,150.,"GeV");
  RooRealVar *weight = new RooRealVar("weight","weight",0,10000);

  theFit.AddFlatFileColumn(pfmt);
  theFit.AddFlatFileColumn(weight);
  
  // define a fit model
  theFit.addModel("myFit", "Inclusive WtoENu");
  
  // define species
  theFit.addSpecies("myFit", "sig",   "Signal Component");
  theFit.addSpecies("myFit", "qcd",   "QCD Component");
  theFit.addSpecies("myFit", "other", "Other Bkgs Component");

  // mLL PDF
  theFit.addPdfWName("myFit", "sig",   "pfmt", "DoubleCruijff", "sig_PfMt");
  theFit.addPdfWName("myFit", "qcd",   "pfmt", "Cruijff", "qcd_PfMt");
  theFit.addPdfWName("myFit", "other", "pfmt", "Cruijff", "other_PfMt");
  
  //theFit.bind(MLStrList("sig_PfMt_mean1","sig_PfMt_mean2"),"sig_PfMt_mean","sig_PfMt_mean");
  theFit.bind(MLStrList("sig_PfMt_sigmaR1","sig_PfMt_sigmaR2"),"sig_PfMt_sigmaR","sig_PfMt_sigmaR");
  theFit.bind(MLStrList("sig_PfMt_alphaR1","sig_PfMt_alphaR2"),"sig_PfMt_alphaR","sig_PfMt_alphaR");

  theFit.addDataSetFromRootFile("T1", "T1", "results/datasets/mockData_out-Wenu.root");

  RooDataSet *data = theFit.getDataSet("T1");
  data->setWeightVar("weight");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  theFit.initialize("fitres/WInclusive/fitMinimum-data.config");
  
  // fix all parameters, float the yields and fit
  theFit._parameterSet.selectByName("*")->setAttribAll("Constant",kTRUE);
  (static_cast<RooRealVar*>(theFit._parameterSet.find("N_sig")))->setConstant(kFALSE) ;
  (static_cast<RooRealVar*>(theFit._parameterSet.find("N_qcd")))->setConstant(kFALSE) ;
  //  (static_cast<RooRealVar*>(theFit._parameterSet.find("N_other")))->setConstant(kFALSE) ;
  
  RooFitResult *fitres =  myPdf->fitTo(*data,theFit.getNoNormVars("myFit"),"MHTER");
  fitres->Print("V");

  // add appropriate column to dataset
  RooArgList yieldsList;
  yieldsList.add(*theFit._fracList.find("N_sig"));
  yieldsList.add(*theFit._fracList.find("N_qcd"));
  //  yieldsList.add(*theFit._fracList.find("N_other"));
  cout << "number of entries in set to write: " << data->numEntries() << endl ;
  RooArgSet nonormvars;
  RooDataSet* dsnew = MLSPlot::addSWeightToData((RooSimultaneous*)(myPdf), yieldsList, *data, nonormvars) ;

  TFile sPlots("results/sPlots/Wenu.root","recreate");
  cout << "number of entries in set to write: " << dsnew->numEntries() << endl ;
  dsnew->Write();
  sPlots.Close();
}
