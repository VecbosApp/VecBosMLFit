// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("usetransvMass", "Use transverse mass", kTRUE);        
  return opts;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

MLFit theFit;

void myFit() {

  MLFit theFit;

  // Various fit options...
  MLOptions opts = GetDefaultOptions();
  opts.addBoolOption("usetransvMass", "Use W Transverse Mass", kFALSE);
  opts.addBoolOption("useMHTphiJet", "Use MHTphiJet", kTRUE);
  
  // define the structure of the dataset
  RooRealVar* mass = new RooRealVar("transvMass",  "Transverse W Mass [GeV/c^{2}]" , 30., 250.);
  RooRealVar* sinMHTphiJet = new RooRealVar("sinMHTphiJet", "sin #phi_{MHT-Jets}",-0.85,0.85);
  
  theFit.AddFlatFileColumn(mass);
  theFit.AddFlatFileColumn(sinMHTphiJet);

  // define a fit model
  theFit.addModel("myFit", "Ratio WtoENu");
  
  // define species
  theFit.addSpecies("myFit", "sig", "Signal Component");
  theFit.addSpecies("myFit", "zeeBkg", "Z to ee Bkg   Component");
  theFit.addSpecies("myFit", "ttbarBkg", "ttbar Bkg   Component");
  theFit.addSpecies("myFit", "qcdBkg", "QCD Bkg   Component");
  
  // mLL PDF
//   if(opts.getBoolVal("usetransvMass")) {
//     theFit.addPdfWName("myFit", "sig" , "transvMass",  "Totti", "sig_Mass");
//     theFit.addPdfWName("myFit", "zeeBkg" , "transvMass",  "Totti", "zeeBkg_Mass");
//     theFit.addPdfWName("myFit", "ttbarBkg" , "transvMass",  "Totti", "ttbarBkg_Mass");
//     theFit.addPdfWName("myFit", "qcdBkg" , "transvMass",  "Totti", "qcdBkg_Mass");
//   }
  // shape variable
  if(opts.getBoolVal("useMHTphiJet")) {
    theFit.addPdfWName("myFit", "sig" , "sinMHTphiJet",  "DoubleGaussian", "sig_MHTphiJet");
    theFit.addPdfWName("myFit", "zeeBkg" , "sinMHTphiJet",  "DoubleGaussian", "zeeBkg_MHTphiJet");
    theFit.addPdfWName("myFit", "ttbarBkg" , "sinMHTphiJet",  "DoubleGaussian", "ttbarBkg_MHTphiJet");
    theFit.addPdfWName("myFit", "qcdBkg" , "sinMHTphiJet",  "Poly2", "qcdBkg_MHTphiJet");
  }
  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fit a sample of Z events
void FitWElectrons(int njets) {
  
  myFit();

  // Load the data
  char datasetname[200];
  sprintf(datasetname,"datasets/wenu_21X-%djets.root",njets);
  const char *treename = "QCD";
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);
  // data = (RooDataSet*)data->reduce("WToENuDecay==1"); // only for signal

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-QCDonly.config");
  
  // Print Fit configuration 
  myPdf->getParameters(data)->selectByAttrib("Constant",kTRUE)->Print("V");  
  myPdf->getParameters(data)->selectByAttrib("Constant",kFALSE)->Print("V");
  
  RooFitResult *fitres =  myPdf->fitTo(*data,theFit.getNoNormVars("myFit"),"MHTER");
  fitres->Print("V");
  
  // write the config file corresponding to the fit minimum
  char configfilename[200];
  sprintf(configfilename, "shapesWenu/config/fitMinimumQCDonly-sinMHTphiJet-%djet.config",njets);
  theFit.writeConfigFile(configfilename);  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotWElectrons(int njets, int nbins) {

  myFit();

  // Load the data
  char datasetname[200];
  sprintf(datasetname,"datasets/wenu_21X-%djets.root",njets);
  const char *treename = "QCD";
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);
  // data = (RooDataSet*)data->reduce("WToENuDecay==1"); // only for signal

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");

  // Initialize the fit...
  char configfilename[200];
  sprintf(configfilename, "shapesWenu/config/fitMinimumQCDonly-sinMHTphiJet-%djet.config",njets);
  theFit.initialize(configfilename);

  TCanvas *c = new TCanvas("c","fitResult");
  char rootfilename[200];
  sprintf(rootfilename,"shapesWenu/root/sinMHTphiJet-QCDonly-%djet.root",njets);
  TFile *output = new TFile(rootfilename,"RECREATE");

  RooPlot* MassPlot = MakePlot("sinMHTphiJet", &theFit, data, nbins);    

  MassPlot->SetYTitle("Events");
  MassPlot->Draw();
  char epsfilename[200];
  sprintf(epsfilename,"shapesWenu/eps/sinMHTphiJet-QCDonly-%djet.eps",njets);
  c->SaveAs(epsfilename);
  MassPlot->Write();
  //  output->Close();

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
  //  double Nb = theFit->getRealPar("N_bkg")->getVal();

  // plot (dashed) the bkg component
  //theFit->getRealPar("N_sig")->setVal(0.);
  //  thePdf->plotOn(plot, RooFit::Normalization(Nb/(Ns+Nb)),RooFit::LineColor(kBlack),RooFit::LineStyle(kDashed));

  
  return plot;
}

