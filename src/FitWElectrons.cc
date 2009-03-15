// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("fitCaloJets",     "Fit calojets, trackjets otherwise", kTRUE);
  opts.addBoolOption("weightedDataset", "use event weight instead of 1",     kTRUE);
  opts.addBoolOption("useMt",           "Use W Transverse Mass",  kTRUE);
  opts.addBoolOption("useMHTphiJet",    "Use MHTphiJet",          kTRUE);
  opts.addBoolOption("AllFit",          "Fit all species",        kTRUE);
  opts.addBoolOption("WOnlyFit",        "Fit W species only",     kFALSE);
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

  opts.addBoolOption("useBVeto",   "Use Optimized B Veto Rectangular Cut", kTRUE);
  
  // define the structure of the dataset
  RooRealVar* Mt = new RooRealVar("Mt",  "Transverse W Mass [GeV/c^{2}]" , 30., 250.);
  RooRealVar *sinMHTphiJet = new RooRealVar("sinMHTphiJet","sinMHTphiJet",-0.80, 0.8);
  RooRealVar* bvetoCat = new RooRealVar("BVetoCat", "BVetoCat",-1,1);
  RooRealVar* weight = new RooRealVar("weight", "weight",1);

  theFit.AddFlatFileColumn(Mt);
  theFit.AddFlatFileColumn(sinMHTphiJet);
  theFit.AddFlatFileColumn(bvetoCat);
  theFit.AddFlatFileColumn(weight);

  // define a fit model
  theFit.addModel("myFit", "Ratio WtoENu");
  
  // define species accepted by b veto
  theFit.addSpecies("myFit", "sig_a",    "Accepted Signal Component");
  theFit.addSpecies("myFit", "ttbar_a",  "Accepted ttbar Component");
  theFit.addSpecies("myFit", "other_a",  "Accepted Other Bkgs Component");

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
  theFit.addPdfWName("myFit", "sig_a" ,   "BVetoCat",  "Poly2",  "bveto_acc");
  theFit.addPdfCopy("myFit",  "ttbar_a",  "BVetoCat",  "sig_a");
  theFit.addPdfCopy("myFit",  "other_a",  "BVetoCat",  "sig_a");

  theFit.addPdfWName("myFit", "sig_r" ,   "BVetoCat",  "Poly2",  "bveto_rej");
  theFit.addPdfCopy("myFit",  "ttbar_r",  "BVetoCat",  "sig_r");
  theFit.addPdfCopy("myFit",  "other_r",  "BVetoCat",  "sig_r");

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
  if(opts.getBoolVal("AllFit")) sprintf(datasetname,"datasets/wenu_data_21X-%d%s.root",njets,jetflavour);
  else sprintf(datasetname,"datasets/wenu_21X-%d%s.root",njets,jetflavour);
  char treename[100];
  if(opts.getBoolVal("AllFit")) sprintf(treename,"data");
  if(opts.getBoolVal("WOnlyFit")) sprintf(treename,"WjetsMADGRAPH");
  if(opts.getBoolVal("ttbarOnlyFit")) sprintf(treename,"ttjetsMADGRAPH");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(treename,"other");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);
  if(opts.getBoolVal("WOnlyFit")) data = (RooDataSet*)data->reduce("WToENuDecay==1");

  // use event weights
  if(opts.getBoolVal("weightedDataset")) data->setWeightVar("evtWeight");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  if(opts.getBoolVal("AllFit")) {
    char initconfigfile[200];
    sprintf(initconfigfile,"fitconfig/fitW-%d%s.config",njets,jetflavour);
    theFit.initialize(initconfigfile);
  }
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
  if(opts.getBoolVal("AllFit")) sprintf(configfilename, "fitres/fitMinimumW-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("WOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-Wonly-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("ttbarOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-TTbaronly-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("otherOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-otheronly-%d%s.config",njets,jetflavour);
  theFit.writeConfigFile(configfilename);  

  // save the fit result in ROOT 
  char rootfilename[200];
  if(opts.getBoolVal("AllFit")) sprintf(rootfilename, "fitres/fitMinimumW-%d%s.root",njets,jetflavour);
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
  if(opts.getBoolVal("AllFit")) sprintf(datasetname,"datasets/wenu_data_21X-%d%s.root",njets,jetflavour);
  else sprintf(datasetname,"datasets/wenu_21X-%d%s.root",njets,jetflavour);
  char treename[100];
  if(opts.getBoolVal("AllFit")) sprintf(treename,"data");
  if(opts.getBoolVal("WOnlyFit")) sprintf(treename,"WjetsMADGRAPH");
  if(opts.getBoolVal("ttbarOnlyFit")) sprintf(treename,"ttjetsMADGRAPH");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(treename,"other");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);
  if(opts.getBoolVal("WOnlyFit")) data = (RooDataSet*)data->reduce("WToENuDecay==1"); // only for signal

  bool usePoissonError=true;
  // use event weights
  if(opts.getBoolVal("weightedDataset")) {
    data->setWeightVar("evtWeight");
    usePoissonError=false;
  }

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");

  // Initialize the fit...
  char configfilename[200];
  if(opts.getBoolVal("AllFit")) sprintf(configfilename,"fitres/fitMinimumW-%d%s.config",njets,jetflavour);
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
    RooPlot* MassPlot = MakePlot("Mt", &theFit, data, configfilename, nbins, usePoissonError);    
    
    MassPlot->SetAxisColor(1,"x");
    MassPlot->SetLabelColor(1, "X");
    MassPlot->SetLabelColor(1, "Y");
    MassPlot->SetXTitle("M_{T}[GeV/c^{2}]");

    MassPlot->SetYTitle("Events");
    MassPlot->Draw();

    char epsfilename[200];
    char Cfilename[200];

    if(opts.getBoolVal("AllFit")) {
      sprintf(epsfilename,"fit-plots/eps/Mt-data-%d%s.eps",njets,jetflavour);
      sprintf(Cfilename,"fit-plots/macro/Mt-data-%d%s.C",njets,jetflavour);
    }
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
    RooPlot* AngularPlot = MakePlot("sinMHTphiJet", &theFit, data, configfilename, nbins, usePoissonError);    
    
    AngularPlot->SetAxisColor(1,"x");
    AngularPlot->SetLabelColor(1, "X");
    AngularPlot->SetLabelColor(1, "Y");
    AngularPlot->SetXTitle("sin(#phi_{MHT-Jet})");

    AngularPlot->SetYTitle("Events");
    AngularPlot->Draw();

    char epsfilename[200];
    char Cfilename[200];

    if(opts.getBoolVal("AllFit")) {
      sprintf(epsfilename,"fit-plots/eps/sinMHTphiJet-data-%d%s.eps",njets,jetflavour);
      sprintf(Cfilename,"fit-plots/macro/sinMHTphiJet-data-%d%s.C",njets,jetflavour);
    }
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
RooPlot *MakePlot(TString VarName, MLFit* theFit, RooDataSet* theData, const char *configfilename, int nbins, bool poissonError=true)
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

  cout << "Ns = " << Ns << endl; 
  cout << "Nttbar = " << Nttbar << endl;
  cout << "Nother = " << Nother << endl;
  
  cout << (Nother+Nttbar)/(Nother+Nttbar+Ns) << endl;

  // plot the total likelihood
  RooAbsPdf *thePdf = theFit->getPdf("myFit");
  thePdf->plotOn(plot, RooFit::LineColor(kBlack) );


  if(opts.getBoolVal("AllFit")) {
    // === plot (dashed) the ttbar component ===
    MLFit theFit2;

    // define the structure of the dataset
    RooRealVar* Mt = new RooRealVar("Mt",  "Transverse W Mass [GeV/c^{2}]" , 30., 250.);
    RooRealVar *sinMHTphiJet = new RooRealVar("sinMHTphiJet","sinMHTphiJet",-0.85, 0.85);

    theFit2.AddFlatFileColumn(Mt);
    theFit2.AddFlatFileColumn(sinMHTphiJet);

    // define a fit model
    theFit2.addModel("ttbarFit", "ttbar Fit");
    theFit2.addSpecies("ttbarFit", "ttbar", "ttbar Bkg Component");
    theFit2.addPdfWName("ttbarFit", "ttbar",  "Mt",           "CrystalCruijff",  "ttbar_Mt");
    theFit2.addPdfWName("ttbarFit", "ttbar",  "sinMHTphiJet", "Cruijff",         "ttbar_sinMHTphiJet");

    RooAbsPdf *myPdf2 = theFit2.buildModel("ttbarFit");
    theFit2.initialize(configfilename);

    myPdf2->plotOn(plot, RooFit::Normalization(Nttbar/(Ns+Nother+Nttbar)),RooFit::LineColor(kBlack),RooFit::LineStyle(kDashed));

    // === plot (dashed) the bkg component ===
    MLFit theFit3;

    theFit3.AddFlatFileColumn(Mt);
    theFit3.AddFlatFileColumn(sinMHTphiJet);

    // define a fit model
    theFit3.addModel("otherFit", "other Fit");
    theFit3.addSpecies("otherFit", "other", "other Bkg Component");
    theFit3.addPdfWName("otherFit", "other", "Mt",            "CrystalCruijff",  "other_Mt");
    theFit3.addPdfWName("otherFit", "other", "sinMHTphiJet",  "Cruijff",         "other_sinMHTphiJet");

    RooAbsPdf *myPdf3 = theFit3.buildModel("otherFit");
    theFit3.initialize(configfilename);

    myPdf3->plotOn(plot, RooFit::Normalization(Nother/(Ns+Nother+Nttbar)),RooFit::LineColor(kBlack), RooFit::LineStyle(3));
  
  }

  return plot;
}

