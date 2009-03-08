// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("fitCaloJets",     "Fit calojets, trackjets otherwise", kFALSE);
  opts.addBoolOption("useMt",           "Use W Transverse Mass",  kTRUE);
  opts.addBoolOption("useMHTphiJet",    "Use MHTphiJet",          kTRUE);
  opts.addBoolOption("AllFit",          "Fit all species",        kFALSE);
  opts.addBoolOption("WOnlyFit",        "Fit W species only",     kTRUE);
  opts.addBoolOption("ttbarOnlyFit",    "Fit ttbar species only", kFALSE);
  opts.addBoolOption("otherOnlyFit",    "Fit other species only", kFALSE);

  return opts;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

MLFit theFit;

void myFit() {

  MLFit theFit;

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  opts.addBoolOption("useTightBVeto",   "Use Tight B Veto Rectangular Cut", kTRUE);
  opts.addBoolOption("useMediumBVeto",  "Use Tight B Veto Rectangular Cut", kFALSE);
  opts.addBoolOption("useLooseBVeto",   "Use Tight B Veto Rectangular Cut", kFALSE);
  
  // define the structure of the dataset
  RooRealVar* Mt = new RooRealVar("Mt",  "Transverse W Mass [GeV/c^{2}]" , 30., 250.);
  RooRealVar *sinMHTphiJet = new RooRealVar("sinMHTphiJet","sinMHTphiJet",0);
  RooRealVar* bvetoTightCat = new RooRealVar("BVetoTightCat", "BVetoTightCat",-1,1);
  RooRealVar* bvetoMediumCat = new RooRealVar("BVetoMediumCat", "BVetoMediumCat",-1,1);
  RooRealVar* bvetoLooseCat = new RooRealVar("BVetoLooseCat", "BVetoLooseCat",-1,1);

  theFit.AddFlatFileColumn(Mt);
  theFit.AddFlatFileColumn(sinMHTphiJet);
  theFit.AddFlatFileColumn(bvetoTightCat);
  theFit.AddFlatFileColumn(bvetoMediumCat);
  theFit.AddFlatFileColumn(bvetoLooseCat);

  // define a fit model
  theFit.addModel("myFit", "Ratio WtoENu");
  
  // define species accepted by b veto
  theFit.addSpecies("myFit", "other_a",  "Accepted Other Bkgs Component");
  theFit.addSpecies("myFit", "sig_a",    "Accepted Signal Component");
  theFit.addSpecies("myFit", "ttbar_a",  "Accepted ttbar Component");

  // define species rejected by b veto
  theFit.addSpecies("myFit", "sig_r",    "Rejected Signal Component");
  theFit.addSpecies("myFit", "ttbar_r",  "Rejected ttbar Component");
  theFit.addSpecies("myFit", "other_r",  "Rejected Other Bkgs Component");
  
  theFit.fitWithEff("sig_a", "sig_r", "sig");
  theFit.fitWithEff("ttbar_a", "ttbar_r", "ttbar");
  theFit.fitWithEff("other_a", "other_r", "other");

  // Mt PDF
  if(opts.getBoolVal("useMt")) {
    theFit.addPdfWName("myFit", "sig_a",   "Mt", "CrystalCruijff", "sig_Mt");
    theFit.addPdfWName("myFit", "ttbar_a", "Mt", "CrystalCruijff", "ttbar_Mt");
    theFit.addPdfWName("myFit", "other_a", "Mt", "CrystalCruijff", "other_Mt");

    theFit.addPdfCopy("myFit", "sig_r",   "Mt", "sig_a");
    theFit.addPdfCopy("myFit", "ttbar_r", "Mt", "ttbar_a");
    theFit.addPdfCopy("myFit", "other_r", "Mt", "other_a");
  }

  // sinMHTphiJet PDF
  if(opts.getBoolVal("useMHTphiJet")) {
    theFit.addPdfWName("myFit", "sig_a" ,   "sinMHTphiJet",  "Cruijff",  "sig_sinMHTphiJet");
    theFit.addPdfWName("myFit", "ttbar_a",  "sinMHTphiJet",  "Cruijff",  "ttbar_sinMHTphiJet");
    theFit.addPdfWName("myFit", "other_a",  "sinMHTphiJet",  "Cruijff",  "other_sinMHTphiJet");

    theFit.addPdfCopy("myFit", "sig_r" ,   "sinMHTphiJet",  "sig_a");
    theFit.addPdfCopy("myFit", "ttbar_r",  "sinMHTphiJet",  "ttbar_a");
    theFit.addPdfCopy("myFit", "other_r",  "sinMHTphiJet",  "other_a");
  }

  // b veto category
  TString catname = "BVetoTightCat";
  if(opts.getBoolVal("useMediumBVeto")) catname = "BVetoMediumCat";
  if(opts.getBoolVal("useLooseBVeto"))  catname = "BVetoLooseCat";

  theFit.addPdfWName("myFit", "sig_a" ,   catname,  "Poly2",  "bveto_acc");
  theFit.addPdfCopy("myFit",  "ttbar_a",  catname,  "sig_a");
  theFit.addPdfCopy("myFit",  "other_a",  catname,  "sig_a");

  theFit.addPdfWName("myFit", "sig_r" ,   catname,  "Poly2",  "bveto_rej");
  theFit.addPdfCopy("myFit",  "ttbar_r",  catname,  "sig_r");
  theFit.addPdfCopy("myFit",  "other_r",    catname,  "sig_r");

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fit a sample of Z events
void FitWElectrons(int njets) {
  
  myFit();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "trackjet");

  // Load the data
  char datasetname[200];
  sprintf(datasetname,"datasets/wenu_21X-%d%s.root",njets,jetflavour);
  char treename[100];
  if(opts.getBoolVal("WOnlyFit")) sprintf(treename,"WjetsMADGRAPH");
  if(opts.getBoolVal("ttbarOnlyFit")) sprintf(treename,"ttjetsMADGRAPH");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(treename,"other");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);
  if(opts.getBoolVal("WOnlyFit")) data = (RooDataSet*)data->reduce("WToENuDecay==1");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  if(opts.getBoolVal("WOnlyFit")) theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-Wonly.config");
  if(opts.getBoolVal("ttbarOnlyFit")) theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-TTbaronly.config");
  if(opts.getBoolVal("otherOnlyFit")) theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-otheronly.config");

  // Print Fit configuration 
  myPdf->getParameters(data)->selectByAttrib("Constant",kTRUE)->Print("V");  
  myPdf->getParameters(data)->selectByAttrib("Constant",kFALSE)->Print("V");
  
  RooFitResult *fitres =  myPdf->fitTo(*data,theFit.getNoNormVars("myFit"),"MHTER");
  fitres->Print("V");
  
  // write the config file corresponding to the fit minimum
  char configfilename[200];
  if(opts.getBoolVal("WOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-Wonly-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("ttbarOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-TTbaronly-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("otherOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-otheronly-%d%s.config",njets,jetflavour);
  theFit.writeConfigFile(configfilename);  

  // save the fit result in ROOT 
  char rootfilename[200];
  if(opts.getBoolVal("WOnlyFit")) sprintf(rootfilename,"shapesWenu/root/fitRes-Wonly-%d%s.root",njets,jetflavour);
  if(opts.getBoolVal("ttbarOnlyFit")) sprintf(rootfilename,"shapesWenu/root/fitRes-ttbaronly-%d%s.root",njets,jetflavour);
  if(opts.getBoolVal("otherOnlyFit")) sprintf(rootfilename,"shapesWenu/root/fitRes-otheronly-%d%s.root",njets,jetflavour);

  TFile *file = new TFile(rootfilename,"recreate");
  fitres->Write();
  file->Close();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotWElectrons(int njets, int nbins) {

  myFit();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "trackjet");

  // Load the data
  char datasetname[200];
  sprintf(datasetname,"datasets/wenu_21X-%d%s.root",njets,jetflavour);
  char treename[100];
  if(opts.getBoolVal("WOnlyFit")) sprintf(treename,"WjetsMADGRAPH");
  if(opts.getBoolVal("ttbarOnlyFit")) sprintf(treename,"ttjetsMADGRAPH");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(treename,"other");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);
  if(opts.getBoolVal("WOnlyFit")) data = (RooDataSet*)data->reduce("WToENuDecay==1"); // only for signal

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");

  // Initialize the fit...
  char configfilename[200];
  if(opts.getBoolVal("WOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-Wonly-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("ttbarOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-TTbaronly-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("otherOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-otheronly-%d%s.config",njets,jetflavour);
  theFit.initialize(configfilename);

  // draw normalized to the full yield, not N * bveto_eff
  theFit.getRealPar("eff_sig")->setVal(1.);  
  theFit.getRealPar("eff_ttbar")->setVal(1.);  
  theFit.getRealPar("eff_other")->setVal(1.);  

  if(opts.getBoolVal("useMt")) {
    TCanvas *c = new TCanvas("c","fitResult");
    RooPlot* MassPlot = MakePlot("Mt", &theFit, data, nbins);    
    
    MassPlot->SetAxisColor(1,"x");
    MassPlot->SetLabelColor(1, "X");
    MassPlot->SetLabelColor(1, "Y");
    MassPlot->SetXTitle("M_{T}[GeV/c^{2}]");

    MassPlot->SetYTitle("Events");
    MassPlot->Draw();

    char epsfilename[200];
    char Cfilename[200];

    if(opts.getBoolVal("WOnlyFit")) {
      sprintf(epsfilename,"shapesWenu/eps/Mt-Wonly-%d%s.eps",njets,jetflavour);
      sprintf(Cfilename,"shapesWenu/macro/Mt-Wonly-%d%s.C",njets,jetflavour);
    }
    if(opts.getBoolVal("ttbarOnlyFit")) {
      sprintf(epsfilename,"shapesWenu/eps/Mt-TTbaronly-%d%s.eps",njets,jetflavour);
      sprintf(Cfilename,"shapesWenu/macro/Mt-TTbaronly-%d%s.C",njets,jetflavour);
    }
    if(opts.getBoolVal("otherOnlyFit")) {
      sprintf(epsfilename,"shapesWenu/eps/Mt-otheronly-%d%s.eps",njets,jetflavour);
      sprintf(Cfilename,"shapesWenu/macro/Mt-otheronly-%d%s.C",njets,jetflavour);
    }
    c->SaveAs(epsfilename);
    c->SaveAs(Cfilename);
  }

  if(opts.getBoolVal("useMHTphiJet")) {
    TCanvas *c = new TCanvas("c","fitResult");
    RooPlot* AngularPlot = MakePlot("sinMHTphiJet", &theFit, data, nbins);    
    
    AngularPlot->SetAxisColor(1,"x");
    AngularPlot->SetLabelColor(1, "X");
    AngularPlot->SetLabelColor(1, "Y");
    AngularPlot->SetXTitle("sin(#phi_{MHT-Jet})");

    AngularPlot->SetYTitle("Events");
    AngularPlot->Draw();

    char epsfilename[200];
    char Cfilename[200];

    if(opts.getBoolVal("WOnlyFit")) {
      sprintf(epsfilename,"shapesWenu/eps/sinMHTphiJet-Wonly-%d%s.eps",njets,jetflavour);
      sprintf(Cfilename,"shapesWenu/macro/sinMHTphiJet-Wonly-%d%s.C",njets,jetflavour);
    }
    if(opts.getBoolVal("ttbarOnlyFit")) {
      sprintf(epsfilename,"shapesWenu/eps/sinMHTphiJet-TTbaronly-%d%s.eps",njets,jetflavour);
      sprintf(Cfilename,"shapesWenu/macro/sinMHTphiJet-TTbaronly-%d%s.C",njets,jetflavour);
    }
    if(opts.getBoolVal("otherOnlyFit")) {
      sprintf(epsfilename,"shapesWenu/eps/sinMHTphiJet-otheronly-%d%s.eps",njets,jetflavour);
      sprintf(Cfilename,"shapesWenu/macro/sinMHTphiJet-otheronly-%d%s.C",njets,jetflavour);
    }
    c->SaveAs(epsfilename);
    c->SaveAs(Cfilename);
  }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Make the plot for a given variable
RooPlot *MakePlot(TString VarName, MLFit* theFit, RooDataSet* theData, int nbins, bool poissonError=true)
{

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  RooRealVar* Var = theFit->RealObservable(VarName);
  double min=Var->getMin();
  double max=Var->getMax();
  RooPlot *plot = Var->frame(min,max,nbins);
  
  // plot the data
  if(poissonError)
    theData->plotOn(plot);
  else 
    theData->plotOn(plot, RooFit::DataError(RooAbsData::SumW2) );

  double Ns = theFit->getRealPar("N_sig")->getVal();
  double Nttbar = theFit->getRealPar("N_ttbar")->getVal();
  double Nother = theFit->getRealPar("N_other")->getVal();

  // plot the total likelihood
  RooAbsPdf *thePdf = theFit->getPdf("myFit");
  thePdf->plotOn(plot, RooFit::LineColor(kBlack) );

  // plot (dashed) the bkg component
  //theFit->getRealPar("N_sig")->setVal(0.);
  //  thePdf->plotOn(plot, RooFit::Normalization(Nb/(Ns+Nb)),RooFit::LineColor(kBlack),RooFit::LineStyle(kDashed));

  
  return plot;
}

