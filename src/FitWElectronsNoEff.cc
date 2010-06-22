// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("fitCaloJets",     "Fit calojets, PFjets otherwise", kTRUE);
  opts.addBoolOption("weightedDataset", "use event weight instead of 1",     kTRUE);
  opts.addBoolOption("usePfMt",         "Use W Transverse Mass",  kTRUE);
  opts.addBoolOption("AllFit",          "Fit all species",        kFALSE);
  opts.addBoolOption("WOnlyFit",        "Fit W species only",     kFALSE);
  opts.addBoolOption("QCDOnlyFit",      "Fit QCD species only",   kTRUE);
  opts.addBoolOption("otherOnlyFit",    "Fit other species only", kFALSE);

  return opts;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

MLFit theFit;

void myFit(int njets) {

  MLFit theFit;

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // define the structure of the dataset
  RooRealVar* pfmt = new RooRealVar("pfmt",  "M_{T}" , 20., 150., "GeV/c^{2}");
  RooRealVar* weight = new RooRealVar("weight", "weight",1);

  theFit.AddFlatFileColumn(pfmt);
  theFit.AddFlatFileColumn(weight);

  // define a fit model
  theFit.addModel("myFit", "Ratio WtoENu");
  
  // define species
  theFit.addSpecies("myFit", "sig",    "Signal Component");
  theFit.addSpecies("myFit", "qcd",    "qcd Component");
  theFit.addSpecies("myFit", "other",  "Other Bkgs Component");

  // PfMt PDF
  if(opts.getBoolVal("usePfMt")) {

    if(njets==0) {
      theFit.addPdfWName("myFit", "sig",   "pfmt", "DoubleCruijff", "sig_PfMt");
      theFit.addPdfWName("myFit", "qcd",   "pfmt", "Cruijff", "qcd_PfMt");
      theFit.addPdfWName("myFit", "other", "pfmt", "Cruijff", "other_PfMt");

      theFit.bind(MLStrList("sig_PfMt_sigmaR1","sig_PfMt_sigmaR2"),"sig_PfMt_sigmaR","sig_PfMt_sigmaR");
      theFit.bind(MLStrList("sig_PfMt_alphaR1","sig_PfMt_alphaR2"),"sig_PfMt_alphaR","sig_PfMt_alphaR");
    } else {
      theFit.addPdfWName("myFit", "sig",   "pfmt", "DoubleCruijff", "sig_PfMt");
      theFit.addPdfWName("myFit", "qcd",   "pfmt", "DoubleGaussian", "qcd_PfMt");
      theFit.addPdfWName("myFit", "other", "pfmt", "DoubleCruijff", "other_PfMt");
    }

  }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fit a sample of Z events
void FitWElectrons(int njets) {
  
  myFit(njets);

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "PFjet");

  // Load the data
  char datasetname[200];
  if(opts.getBoolVal("AllFit")) sprintf(datasetname,"results_data/datasetsJets/wenu_35X_%d%s.root",njets,jetflavour);
  else sprintf(datasetname,"results/datasetsJets/wenu_33X_%d%s.root",njets,jetflavour);
  char treename[100];
  if(opts.getBoolVal("AllFit")) sprintf(treename,"Data");
  if(opts.getBoolVal("WOnlyFit")) sprintf(treename,"WJets");
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(treename,"QCDJets");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(treename,"OtherJets");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *dataTot = theFit.getDataSet(treename);
  RooDataSet *data = (RooDataSet*)dataTot->reduce("event<10000");

  // use event weights
  if(opts.getBoolVal("weightedDataset")) data->setWeightVar("weight");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  if(opts.getBoolVal("AllFit")) {
    char initconfigfile[200];
    sprintf(initconfigfile,"fitconfig/fitW-%d%s.config",njets,jetflavour);
    theFit.initialize(initconfigfile);
  }
  if(opts.getBoolVal("WOnlyFit")) theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-Wonly.config");
  if(opts.getBoolVal("QCDOnlyFit")) theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-QCDonly.config");
  if(opts.getBoolVal("otherOnlyFit")) theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-otheronly.config");

  // Print Fit configuration 
  myPdf->getParameters(data)->selectByAttrib("Constant",kTRUE)->Print("V");  
  myPdf->getParameters(data)->selectByAttrib("Constant",kFALSE)->Print("V");
  
  RooFitResult *fitres =  myPdf->fitTo(*data,RooFit::ConditionalObservables(theFit.getNoNormVars("myFit")),RooFit::FitOptions("MHTER"));
  fitres->Print("V");
  
  // write the config file corresponding to the fit minimum
  char configfilename[200];
  if(opts.getBoolVal("AllFit")) sprintf(configfilename, "fitres/fitMinimumW-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("WOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-Wonly-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-QCDonly-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("otherOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-otheronly-%d%s.config",njets,jetflavour);
  theFit.writeConfigFile(configfilename);  

  // save the fit result in ROOT 
  char rootfilename[200];
  if(opts.getBoolVal("AllFit")) sprintf(rootfilename, "fitres/fitMinimumW-%d%s.root",njets,jetflavour);
  if(opts.getBoolVal("WOnlyFit")) sprintf(rootfilename,"shapesWenu/root/fitRes-Wonly-%d%s.root",njets,jetflavour);
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(rootfilename,"shapesWenu/root/fitRes-QCDonly-%d%s.root",njets,jetflavour);
  if(opts.getBoolVal("otherOnlyFit")) sprintf(rootfilename,"shapesWenu/root/fitRes-otheronly-%d%s.root",njets,jetflavour);

  TFile *file = new TFile(rootfilename,"recreate");
  fitres->Write();
  file->Close();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotWElectrons(int njets, int nbins) {

  myFit(njets);

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "PFjet");

  // Load the data
  char datasetname[200];
  if(opts.getBoolVal("AllFit")) sprintf(datasetname,"results_data/datasetsJets/wenu_35X_%d%s.root",njets,jetflavour);
  else sprintf(datasetname,"results/datasetsJets/wenu_33X_%d%s.root",njets,jetflavour);
  char treename[100];
  if(opts.getBoolVal("AllFit")) sprintf(treename,"Data");
  if(opts.getBoolVal("WOnlyFit")) sprintf(treename,"WJets");
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(treename,"QCDJets");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(treename,"OtherJets");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *dataTot = theFit.getDataSet(treename);
  RooDataSet *data = (RooDataSet*)dataTot->reduce("event<10000");

  bool usePoissonError=true;
  // use event weights
  if(opts.getBoolVal("weightedDataset")) {
    data->setWeightVar("weight");
    usePoissonError=false;
  }

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");

  // Initialize the fit...
  char configfilename[200];
  if(opts.getBoolVal("AllFit")) sprintf(configfilename,"fitres/fitMinimumW-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("WOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-Wonly-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-QCDonly-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("otherOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-otheronly-%d%s.config",njets,jetflavour);
  theFit.initialize(configfilename);

  if(opts.getBoolVal("usePfMt")) {
    TCanvas *c = new TCanvas("c","fitResult");
    RooPlot* MassPlot = MakePlot("pfmt", njets, &theFit, data, configfilename, nbins, usePoissonError);    
    
    MassPlot->SetAxisColor(1,"x");
    MassPlot->SetLabelColor(1, "X");
    MassPlot->SetLabelColor(1, "Y");
    MassPlot->SetXTitle("M_{T}[GeV/c^{2}]");

    MassPlot->SetYTitle("Events");
    MassPlot->Draw();

//     TLatex* t2 = new TLatex(0.6,0.62,"#splitline{CMS Preliminary 2010}{#sqrt{s}=7 TeV, L_{int}=12 nb^{-1}}");
//     t2->SetNDC();
//     t2->SetTextSize(0.05);
//     t2->Draw();
 
    char epsfilename[200];
    char Cfilename[200];

    if(opts.getBoolVal("AllFit")) {
      sprintf(epsfilename,"fit-plots/eps/PfMt-data-%d%s.eps",njets,jetflavour);
      sprintf(Cfilename,"fit-plots/macro/PfMt-data-%d%s.C",njets,jetflavour);
    }
    if(opts.getBoolVal("WOnlyFit")) {
      sprintf(epsfilename,"shapesWenu/eps/PfMt-Wonly-%d%s.eps",njets,jetflavour);
      sprintf(Cfilename,"shapesWenu/macro/PfMt-Wonly-%d%s.C",njets,jetflavour);
    }
    if(opts.getBoolVal("QCDOnlyFit")) {
      sprintf(epsfilename,"shapesWenu/eps/PfMt-QCDonly-%d%s.eps",njets,jetflavour);
      sprintf(Cfilename,"shapesWenu/macro/PfMt-QCDonly-%d%s.C",njets,jetflavour);
    }
    if(opts.getBoolVal("otherOnlyFit")) {
      sprintf(epsfilename,"shapesWenu/eps/PfMt-otheronly-%d%s.eps",njets,jetflavour);
      sprintf(Cfilename,"shapesWenu/macro/PfMt-otheronly-%d%s.C",njets,jetflavour);
    }
    c->SaveAs(epsfilename);
    c->SaveAs(Cfilename);
  }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Make the plot for a given variable
RooPlot *MakePlot(TString VarName, int njets, MLFit* theFit, RooDataSet* theData, const char *configfilename, int nbins, bool poissonError=true)
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
  double Nqcd = theFit->getRealPar("N_qcd")->getVal();
  double Nother = theFit->getRealPar("N_other")->getVal();

  cout << "Ns = " << Ns << endl; 
  cout << "Nqcd = " << Nqcd << endl;
  cout << "Nother = " << Nother << endl;
  
  cout << (Nother+Nqcd)/(Nother+Nqcd+Ns) << endl;

  // plot the total likelihood
  RooAbsPdf *thePdf = theFit->getPdf("myFit");
  thePdf->plotOn(plot, RooFit::LineColor(kBlack) );


  if(opts.getBoolVal("AllFit")) {
    // === plot (dashed) the qcd component ===
    MLFit theFit2;

    // define the structure of the dataset
    RooRealVar* PfMt = new RooRealVar("pfmt",  "M_{T}" , 20., 150., "GeV/c^{2}");
    //    RooRealVar *sinMHTphiJet = new RooRealVar("sinMHTphiJet","sinMHTphiJet",-0.80, 0.80);

    theFit2.AddFlatFileColumn(PfMt);
    //    theFit2.AddFlatFileColumn(sinMHTphiJet);

    // define a fit model
    theFit2.addModel("qcdFit", "qcd Fit");
    theFit2.addSpecies("qcdFit", "qcd", "qcd Bkg Component");
    if(njets==0) {
      theFit2.addPdfWName("qcdFit", "qcd",   "pfmt", "Cruijff", "qcd_PfMt");
    } else {
      theFit2.addPdfWName("qcdFit", "qcd",  "pfmt", "DoubleGaussian",  "qcd_PfMt");
    }

    RooAbsPdf *myPdf2 = theFit2.buildModel("qcdFit");
    theFit2.initialize(configfilename);

    myPdf2->plotOn(plot, RooFit::Normalization(Nqcd/(Ns+Nother+Nqcd)),RooFit::LineColor(kBlack),RooFit::LineStyle(kDashed));

    // === plot (dashed) the bkg component ===
    MLFit theFit3;

    theFit3.AddFlatFileColumn(PfMt);
    //    theFit3.AddFlatFileColumn(sinMHTphiJet);

    // define a fit model
    theFit3.addModel("otherFit", "other Fit");
    theFit3.addSpecies("otherFit", "other", "other Bkg Component");
    if(njets==0) {
      theFit3.addPdfWName("otherFit", "other", "pfmt", "Cruijff",  "other_PfMt");
    } else {
      theFit3.addPdfWName("otherFit", "other", "pfmt", "DoubleCruijff", "other_PfMt");
    }
    //    theFit3.addPdfWName("otherFit", "other", "sinMHTphiJet",  "Cruijff",         "other_sinMHTphiJet");

    RooAbsPdf *myPdf3 = theFit3.buildModel("otherFit");
    theFit3.initialize(configfilename);

    myPdf3->plotOn(plot, RooFit::Normalization(Nother/(Ns+Nother+Nqcd)),RooFit::LineColor(kRed), RooFit::LineStyle(kDashed));
  
  }

  return plot;
}

