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
  
  // define the structure of the dataset
  RooRealVar* mass = new RooRealVar("transvMass",  "Transverse W Mass [GeV/c^{2}]" , 30., 250.);
  RooRealVar* weight = new RooRealVar("CSA07weight", "CSA07weight", 0., 100.);
  
  theFit.AddFlatFileColumn(mass);
  theFit.AddFlatFileColumn(weight);
  
  // define a fit model
  theFit.addModel("myFit", "Ratio WtoENu");
  
  // define species
  theFit.addSpecies("myFit", "sig", "Signal Component");
  theFit.addSpecies("myFit", "zeeBkg", "Z to ee Bkg   Component");
  theFit.addSpecies("myFit", "ttbarBkg", "ttbar Bkg   Component");
  theFit.addSpecies("myFit", "qcdBkg", "QCD Bkg   Component");
  
  // mLL PDF
  if(opts.getBoolVal("usetransvMass")) {
    theFit.addPdfWName("myFit", "sig" , "transvMass",  "Totti", "sig_Mass");
    theFit.addPdfWName("myFit", "zeeBkg" , "transvMass",  "Totti", "zeeBkg_Mass");
    theFit.addPdfWName("myFit", "ttbarBkg" , "transvMass",  "Totti", "ttbarBkg_Mass");
    theFit.addPdfWName("myFit", "qcdBkg" , "transvMass",  "Poly2", "qcdBkg_Mass");
  }
  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fit a sample of Z events
void FitWElectrons(int njets) {
  
  myFit();

  // Load the data
  char datasetname[200];
  sprintf(datasetname,"datasets/merged-wenu-%djets.root",njets);
  theFit.addDataSetFromRootFile("data", "data", datasetname);
  RooDataSet *data = theFit.getDataSet("data");
  data->setWeightVar("CSA07weight");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  char fitconfig[200];
  sprintf(fitconfig,"fitconfig/fitW-%djet.config",njets);
  theFit.initialize(fitconfig);

  // Print Fit configuration 
  myPdf->getParameters(data)->selectByAttrib("Constant",kTRUE)->Print("V");  
  myPdf->getParameters(data)->selectByAttrib("Constant",kFALSE)->Print("V");
  
  RooFitResult *fitres =  myPdf->fitTo(*data,theFit.getNoNormVars("myFit"),"MHTER");
  fitres->Print("V");
  
  // write the config file corresponding to the fit minimum
  char configfilename[200];
  sprintf(configfilename,"fitres/fitResult-CSA07-w%djets.config",njets);

  theFit.writeConfigFile(configfilename);  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotWElectrons(int njets, int nbins) {

  myFit();

  // Load the data
  char datasetname[200];
  sprintf(datasetname,"datasets/merged-wenu-%djets.root",njets);
  theFit.addDataSetFromRootFile("data", "data", datasetname);
  RooDataSet *data = theFit.getDataSet("data");
  data->setWeightVar("CSA07weight");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");

  // Initialize the fit...
  char configfilename[200];
  sprintf(configfilename, "fitres/fitResult-CSA07-w%djets.config",njets);
  theFit.initialize(configfilename);

  TCanvas *c = new TCanvas("c","fitResult");
  char rootfilename[200];
  sprintf(rootfilename,"fitres/mtw-CSA07-%djet.root");
  TFile *output = new TFile(rootfilename,"RECREATE");

  RooPlot* MassPlot = MakePlot("transvMass", &theFit, data, nbins, false);    

  MassPlot->SetYTitle("Events");
  MassPlot->Draw();
  char epsfilename[200];
  sprintf(epsfilename,"fitres/mtw-CSA07-%djet.eps",njets);
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
  double Nb = theFit->getRealPar("N_zeeBkg")->getVal() +
    theFit->getRealPar("N_ttbarBkg")->getVal() +
    theFit->getRealPar("N_qcdBkg")->getVal();
  
  // plot (dashed) the bkg component
  theFit->getRealPar("N_sig")->setVal(0.);
  thePdf->plotOn(plot, RooFit::Normalization(Nb/(Ns+Nb)),RooFit::LineColor(kBlack),RooFit::LineStyle(kDashed));

  
  return plot;
}

