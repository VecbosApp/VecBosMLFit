// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("fitCaloJets",     "Fit calojets, trackjets otherwise", kTRUE);
  opts.addBoolOption("useMass",         "Use Invariant Mass",     kTRUE);        
  opts.addBoolOption("useMHTphiMET",    "Use sin(MHTphiMET)",     kTRUE);
  opts.addBoolOption("AllFit",          "Fit all species",        kFALSE);
  opts.addBoolOption("ZOnlyFit",        "Fit Z species only",     kTRUE);
  opts.addBoolOption("bkgOnlyFit",      "Fit bkg species only",   kFALSE);

  return opts;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

MLFit theFit;

void myFit() {

  MLFit theFit;

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // define the structure of the dataset
  RooRealVar* mass = new RooRealVar("mass",  "Mass [GeV/c^{2}]" , 60., 110.);
  RooRealVar* sinMHTphiMET = new RooRealVar("sinMHTphiMET", "sin #phi_{MHT-MET}",-0.85,0.85);
  
  theFit.AddFlatFileColumn(mass);
  theFit.AddFlatFileColumn(sinMHTphiMET);

  // define a fit model
  theFit.addModel("myFit", "Ratio ZtoEE");
  
  // define species
  theFit.addSpecies("myFit", "sig", "Signal Component");
  theFit.addSpecies("myFit", "bkg", "Bkg Component");
  
  // mLL PDF
  if(opts.getBoolVal("useMass")) {
    theFit.addPdfWName("myFit", "sig" , "mass",  "Cruijff", "sig_Mass");
    theFit.addPdfWName("myFit", "bkg" , "mass",  "Poly2",   "bkg_Mass");
  }
  // shape variable
  if(opts.getBoolVal("useMHTphiMET")) {
    theFit.addPdfWName("myFit", "sig" , "sinMHTphiMET",  "Cruijff", "sig_sinMHTphiMET");
    theFit.addPdfWName("myFit", "bkg" , "sinMHTphiMET",  "Poly2",   "bkg_sinMHTphiMET");
  }
  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fit a sample of Z events
void FitZElectrons(int njets) {
  
  myFit();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "trackjet");

  // Load the data
  char datasetname[200];
  sprintf(datasetname,"datasets/zee_21X-%d%s.root",njets,jetflavour);
  char treename[100];
  if(opts.getBoolVal("ZOnlyFit")) sprintf(treename,"ZjetsMADGRAPH");
  if(opts.getBoolVal("bkgOnlyFit")) sprintf(treename,"other");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);
  if(opts.getBoolVal("ZOnlyFit")) data = (RooDataSet*)data->reduce("ZToEEDecay==1");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  if(opts.getBoolVal("ZOnlyFit")) theFit.initialize("shapesZee/config/RatioElectrons-ZjetsFit-Zonly.config");
  if(opts.getBoolVal("bkgOnlyFit")) theFit.initialize("shapesZee/config/RatioElectrons-ZjetsFit-bkgonly.config");
  
  // Print Fit configuration 
  myPdf->getParameters(data)->selectByAttrib("Constant",kTRUE)->Print("V");  
  myPdf->getParameters(data)->selectByAttrib("Constant",kFALSE)->Print("V");
  
  RooFitResult *fitres =  myPdf->fitTo(*data,theFit.getNoNormVars("myFit"),"MHTER");
  fitres->Print("V");
  
  // write the config file corresponding to the fit minimum
  char configfilename[200];
  if(opts.getBoolVal("ZOnlyFit")) sprintf(configfilename, "shapesZee/config/fitMinimum-Zonly-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("bkgOnlyFit")) sprintf(configfilename, "shapesZee/config/fitMinimum-bkgonly-%d%s.config",njets,jetflavour);
  theFit.writeConfigFile(configfilename);  
  
  // save the fit result in ROOT 
  char rootfilename[200];
  if(opts.getBoolVal("ZOnlyFit")) sprintf(rootfilename,"shapesZee/root/fitRes-Zonly-%d%s.root",njets,jetflavour);
  if(opts.getBoolVal("bkgOnlyFit")) sprintf(rootfilename,"shapesZee/root/fitRes-bkgonly-%d%s.root",njets,jetflavour);

  TFile *file = new TFile(rootfilename,"recreate");
  fitres->Write();
  file->Close();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotZElectrons(int njets, int nbins=19) {

  myFit();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "trackjet");

  // Load the data
  char datasetname[200];
  sprintf(datasetname,"datasets/zee_21X-%d%s.root",njets,jetflavour);
  char treename[100];
  if(opts.getBoolVal("ZOnlyFit")) sprintf(treename,"ZjetsMADGRAPH");
  if(opts.getBoolVal("bkgOnlyFit")) sprintf(treename,"other");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);
  if(opts.getBoolVal("ZOnlyFit")) data = (RooDataSet*)data->reduce("ZToEEDecay==1");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");

  // Initialize the fit...
  char configfilename[200];
  if(opts.getBoolVal("ZOnlyFit")) sprintf(configfilename, "shapesZee/config/fitMinimum-Zonly-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("bkgOnlyFit")) sprintf(configfilename, "shapesZee/config/fitMinimum-bkgonly-%d%s.config",njets,jetflavour);
  theFit.initialize(configfilename);

  if(opts.getBoolVal("useMass")) {
    TCanvas *c = new TCanvas("c","fitResult");
    RooPlot* MassPlot = MakePlot("mass", &theFit, data, nbins);    
    
    MassPlot->SetAxisColor(1,"x");
    MassPlot->SetLabelColor(1, "X");
    MassPlot->SetLabelColor(1, "Y");
    MassPlot->SetXTitle("m_{ee}[GeV/c^{2}]");

    MassPlot->SetYTitle("Events");
    MassPlot->Draw();

    char epsfilename[200];
    char Cfilename[200];

    if(opts.getBoolVal("ZOnlyFit")) {
      sprintf(epsfilename,"shapesZee/eps/Mass-Zonly-%d%s.eps",njets,jetflavour);
      sprintf(Cfilename,"shapesZee/macro/Mass-Zonly-%d%s.C",njets,jetflavour);
    }
    if(opts.getBoolVal("bkgOnlyFit")) {
      sprintf(epsfilename,"shapesZee/eps/Mass-bkgonly-%d%s.eps",njets,jetflavour);
      sprintf(Cfilename,"shapesZee/macro/Mass-bkgonly-%d%s.C",njets,jetflavour);
    }
    c->SaveAs(epsfilename);
    c->SaveAs(Cfilename);
  }

  if(opts.getBoolVal("useMHTphiMET")) {
    TCanvas *c = new TCanvas("c","fitResult");
    RooPlot* AngularPlot = MakePlot("sinMHTphiMET", &theFit, data, nbins);    
    
    AngularPlot->SetAxisColor(1,"x");
    AngularPlot->SetLabelColor(1, "X");
    AngularPlot->SetLabelColor(1, "Y");
    AngularPlot->SetXTitle("sin(#phi_{MHT,MET})");

    AngularPlot->SetYTitle("Events");
    AngularPlot->Draw();

    char epsfilename[200];
    char Cfilename[200];

    if(opts.getBoolVal("ZOnlyFit")) {
      sprintf(epsfilename,"shapesZee/eps/sinMHTphiMET-Zonly-%d%s.eps",njets,jetflavour);
      sprintf(Cfilename,"shapesZee/macro/sinMHTphiMET-Zonly-%d%s.C",njets,jetflavour);
    }
    if(opts.getBoolVal("bkgOnlyFit")) {
      sprintf(epsfilename,"shapesZee/eps/sinMHTphiMET-bkgonly-%d%s.eps",njets,jetflavour);
      sprintf(Cfilename,"shapesZee/macro/sinMHTphiMET-bkgonly-%d%s.C",njets,jetflavour);
    }
    c->SaveAs(epsfilename);
    c->SaveAs(Cfilename);
  }


}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Make the plot for a given variable
RooPlot *MakePlot(TString VarName, MLFit* theFit, RooDataSet* theData, int nbins, bool poissonError=true)
{
  RooRealVar* Var = theFit->RealObservable(VarName);
  double min=Var->getMin();
  double max=Var->getMax();
  RooPlot *plot = Var->frame(min,max,nbins);
  
  // plot the data
  if(poissonError)
    theData->plotOn(plot);
  else 
    theData->plotOn(plot, RooFit::DataError(RooAbsData::SumW2) );

  // plot the total likelihood
  RooAbsPdf *thePdf = theFit->getPdf("myFit");
  thePdf->plotOn(plot, RooFit::LineColor(kBlack));

  double Ns = theFit->getRealPar("N_sig")->getVal();
  double Nb = theFit->getRealPar("N_bkg")->getVal();

  // plot (dashed) the bkg component
  //  theFit->getRealPar("N_sig")->setVal(0.);
  //  thePdf->plotOn(plot, RooFit::Normalization(Nb/(Ns+Nb)),RooFit::LineColor(kBlack),RooFit::LineStyle(kDashed));

  
  return plot;
}
