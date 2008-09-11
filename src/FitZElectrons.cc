// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("useinvMass", "Use invMass", kTRUE);        
  return opts;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

MLFit theFit;

void myFit() {

  MLFit theFit;

  // Various fit options...
  MLOptions opts = GetDefaultOptions();
  
  // define the structure of the dataset
  RooRealVar* mass = new RooRealVar("invMass",  "Mass [GeV/c^{2}]" , 70., 110.);
  RooRealVar* weight = new RooRealVar("CSA07weight", "CSA07weight", 0., 100.);
  
  theFit.AddFlatFileColumn(mass);
  theFit.AddFlatFileColumn(weight);
  
  // define a fit model
  theFit.addModel("myFit", "Ratio ZtoEE");
  
  // define species
  theFit.addSpecies("myFit", "sig", "Signal Component");
  theFit.addSpecies("myFit", "ttbarbkg", "Bkg   Component");
  
  // mLL PDF
  if(opts.getBoolVal("useinvMass")) {
    theFit.addPdfWName("myFit", "sig" , "invMass",  "Cruijff", "sig_Mass");
    theFit.addPdfWName("myFit", "ttbarbkg" , "invMass",  "Poly2",  "ttbarbkg_Mass");
  }
  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fit a sample of Z events
void FitZElectrons() {
  
  myFit();

  // Load the data
  theFit.addDataSetFromRootFile("theData", "zjets", "datasets/zee-1jets.root");
  RooDataSet *data = theFit.getDataSet("theData");
  data->setWeightVar("CSA07weight");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  theFit.initialize("shapesZee/config/RatioElectrons-ZjetsFit-Zonly.config");
  
  // Print Fit configuration 
  myPdf->getParameters(data)->selectByAttrib("Constant",kTRUE)->Print("V");  
  myPdf->getParameters(data)->selectByAttrib("Constant",kFALSE)->Print("V");
  
  RooFitResult *fitres =  myPdf->fitTo(*data,theFit.getNoNormVars("myFit"),"MHTER");
  fitres->Print("V");
  
  // write the config file corresponding to the fit minimum
  theFit.writeConfigFile("shapesZee/config/fitMinimumZonlyWeight-1jet.config");  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotZElectrons(int nbins=19) {

  myFit();

  // Load the data
  theFit.addDataSetFromRootFile("theData", "zjets", "datasets/zee-1jets.root");
  RooDataSet *data = theFit.getDataSet("theData");
  data->setWeightVar("CSA07weight");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");

  // Initialize the fit...
  theFit.initialize("shapesZee/config/fitMinimumZonlyWeight-1jet.config");

  TCanvas *c = new TCanvas("c","fitResult");
  TFile *output = new TFile("shapesZee/root/mll-ZonlyWeight-1jet.root","RECREATE");

  RooPlot* MassPlot = MakePlot("invMass", &theFit, data, nbins, false);    

  MassPlot->SetYTitle("Events");
  MassPlot->Draw();
  c->SaveAs("shapesZee/eps/mll-ZonlyWeight-1jet.eps");
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
  double Nb = theFit->getRealPar("N_ttbarbkg")->getVal();

  // plot (dashed) the bkg component
  //  theFit->getRealPar("N_sig")->setVal(0.);
  //  thePdf->plotOn(plot, RooFit::Normalization(Nb/(Ns+Nb)),RooFit::LineColor(kBlack),RooFit::LineStyle(kDashed));

  
  return plot;
}

