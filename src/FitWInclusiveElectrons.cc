// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("weightedDataset", "use event weight instead of 1",     kTRUE);
  opts.addBoolOption("useMt",           "Use W Transverse Mass",  kFALSE);
  opts.addBoolOption("useTcMt",         "Use t.c. W Transverse Mass",  kFALSE);
  opts.addBoolOption("usePfMt",         "Use p.f. W Transverse Mass",  kTRUE);
  opts.addBoolOption("AllFit",          "Fit all species",        kFALSE);
  opts.addBoolOption("WOnlyFit",        "Fit W species only",     kFALSE);
  opts.addBoolOption("QCDOnlyFit",      "Fit QCD species only",   kTRUE);
  opts.addBoolOption("otherOnlyFit",    "Fit other species only", kFALSE);

  return opts;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

MLFit theFit;

void myFit() {

  MLFit theFit;

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // define the structure of the dataset
  // kinematic variables
  RooRealVar *met = new RooRealVar("met","E_{T}^{miss}",0.0,500.,"GeV");
  RooRealVar *tcmet = new RooRealVar("tcmet","t.c. E_{T}^{miss}",0.0,500.,"GeV");
  RooRealVar *pfmet = new RooRealVar("pfmet","p.f. E_{T}^{miss}",0.0,500.,"GeV");
  RooRealVar *mt = new RooRealVar("mt","m_{T}^{W}",0.0,500.,"GeV");
  RooRealVar *tcmt = new RooRealVar("tcmt","t.c. m_{T}^{W}",0.0,500.,"GeV");
  RooRealVar *pfmt = new RooRealVar("pfmt","p.f. m_{T}^{W}",10.0,150.,"GeV");

  // other variables
  RooRealVar *weight = new RooRealVar("weight","weight",0,10000);

  theFit.AddFlatFileColumn(met);
  theFit.AddFlatFileColumn(tcmet);
  theFit.AddFlatFileColumn(pfmet);
  theFit.AddFlatFileColumn(mt);
  theFit.AddFlatFileColumn(tcmt);
  theFit.AddFlatFileColumn(pfmt);
  theFit.AddFlatFileColumn(weight);

  // define a fit model
  theFit.addModel("myFit", "Inclusive WtoENu");
  
  // define species
  theFit.addSpecies("myFit", "sig",   "Signal Component");
  theFit.addSpecies("myFit", "qcd",   "QCD Component");
  theFit.addSpecies("myFit", "other", "Other Bkgs Component");

  // Mt PDF
  if(opts.getBoolVal("useMt")) {
    theFit.addPdfWName("myFit", "sig",   "mt", "Cruijff", "sig_Mt");
    theFit.addPdfWName("myFit", "qcd",   "mt", "Cruijff", "qcd_Mt");
    theFit.addPdfWName("myFit", "other", "mt", "Cruijff", "other_Mt");
  }

  // T.C. Mt PDF
  if(opts.getBoolVal("useTcMt")) {
    theFit.addPdfWName("myFit", "sig",   "tcmt", "Cruijff", "sig_TcMt");
    theFit.addPdfWName("myFit", "qcd",   "tcmt", "Cruijff", "qcd_TcMt");
    theFit.addPdfWName("myFit", "other", "tcmt", "Cruijff", "other_TcMt");
  }

  // P.F. Mt PDF
  if(opts.getBoolVal("usePfMt")) {
    theFit.addPdfWName("myFit", "sig",   "pfmt", "DoubleCruijff", "sig_PfMt");
    theFit.addPdfWName("myFit", "qcd",   "pfmt", "Cruijff", "qcd_PfMt");
    theFit.addPdfWName("myFit", "other", "pfmt", "Cruijff", "other_PfMt");

    theFit.bind(MLStrList("sig_PfMt_mean1","sig_PfMt_mean2"),"sig_PfMt_mean","sig_PfMt_mean");
    theFit.bind(MLStrList("sig_PfMt_sigmaR1","sig_PfMt_sigmaR2"),"sig_PfMt_sigmaR","sig_PfMt_sigmaR");
    theFit.bind(MLStrList("sig_PfMt_alphaR1","sig_PfMt_alphaR2"),"sig_PfMt_alphaR","sig_PfMt_alphaR");
  }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fit a sample of Z events
void FitWElectrons() {
  
  myFit();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // Load the data
  char datasetname[200];
  if(opts.getBoolVal("AllFit")) sprintf(datasetname,"results/datasets/data_IsolVtx.root");
  if(opts.getBoolVal("WOnlyFit")) sprintf(datasetname,"results/datasets/WJetsMADGRAPH_IsolVtx.root");
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(datasetname,"results/datasets/QCD_IsolVtx.root");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(datasetname,"results/datasets/other_IsolVtx.root");
  theFit.addDataSetFromRootFile("T1", "T1", datasetname);
  RooDataSet *data = theFit.getDataSet("T1");

  //  if(opts.getBoolVal("WOnlyFit")) data = (RooDataSet*)data->reduce("promptDecay==1");

  // use event weights
  if(opts.getBoolVal("weightedDataset")) data->setWeightVar("weight");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  if(opts.getBoolVal("AllFit")) {
    char initconfigfile[200];
    sprintf(initconfigfile,"fitconfig/WInclusive/fit.config");
    theFit.initialize(initconfigfile);
  }
  if(opts.getBoolVal("WOnlyFit")) theFit.initialize("shapes/WInclusive/config/WFit-Wonly.config");
  if(opts.getBoolVal("QCDOnlyFit")) theFit.initialize("shapes/WInclusive/config/WFit-QCDonly.config");
  if(opts.getBoolVal("otherOnlyFit")) theFit.initialize("shapes/WInclusive/config/WFit-otheronly.config");

  // Print Fit configuration 
  myPdf->getParameters(data)->selectByAttrib("Constant",kTRUE)->Print("V");  
  myPdf->getParameters(data)->selectByAttrib("Constant",kFALSE)->Print("V");
  
  RooFitResult *fitres =  myPdf->fitTo(*data,theFit.getNoNormVars("myFit"),"MHTER");
  fitres->Print("V");
  
  // write the config file corresponding to the fit minimum
  char configfilename[200];
  if(opts.getBoolVal("AllFit")) sprintf(configfilename, "fitres/WInclusive/fitMinimum-data.config");
  if(opts.getBoolVal("WOnlyFit")) sprintf(configfilename, "shapes/WInclusive/config/fitMinimum-Wonly.config");
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(configfilename, "shapes/WInclusive/config/fitMinimum-QCDonly.config");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(configfilename, "shapes/WInclusive/config/fitMinimum-otheronly.config");
  theFit.writeConfigFile(configfilename);

  // save the fit result in ROOT 
  char rootfilename[200];
  if(opts.getBoolVal("AllFit")) sprintf(rootfilename, "fitres/WInclusive/fitMinimum.root");
  if(opts.getBoolVal("WOnlyFit")) sprintf(rootfilename,"shapes/WInclusive/root/fitRes-Wonly.root");
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(rootfilename,"shapes/WInclusive/root/fitRes-QCDonly.root");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(rootfilename,"shapes/WInclusive/root/fitRes-otheronly.root");

  TFile *file = new TFile(rootfilename,"recreate");
  fitres->Write();
  file->Close();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotWElectrons(int nbins) {

  myFit();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // Load the data
  char datasetname[200];
  if(opts.getBoolVal("AllFit")) sprintf(datasetname,"results/datasets/data_IsolVtx.root");
  if(opts.getBoolVal("WOnlyFit")) sprintf(datasetname,"results/datasets/WJetsMADGRAPH_IsolVtx.root");
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(datasetname,"results/datasets/QCD_IsolVtx.root");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(datasetname,"results/datasets/other_IsolVtx.root");
  theFit.addDataSetFromRootFile("T1", "T1", datasetname);
  RooDataSet *data = theFit.getDataSet("T1");

  //  if(opts.getBoolVal("WOnlyFit")) data = (RooDataSet*)data->reduce("promptDecay==1");

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
  if(opts.getBoolVal("AllFit")) sprintf(configfilename,"fitres/fitMinimum.config");
  if(opts.getBoolVal("WOnlyFit")) sprintf(configfilename, "shapes/WInclusive/config/fitMinimum-Wonly.config");
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(configfilename, "shapes/WInclusive/config/fitMinimum-QCDonly.config");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(configfilename, "shapes/WInclusive/config/fitMinimum-otheronly.config");
  theFit.initialize(configfilename);

  if(opts.getBoolVal("useMt")) {
    TCanvas *c = new TCanvas("c","fitResult");
    RooPlot* MassPlot = MakePlot("mt", &theFit, data, configfilename, nbins, usePoissonError);    
    
    MassPlot->SetAxisColor(1,"x");
    MassPlot->SetLabelColor(1, "X");
    MassPlot->SetLabelColor(1, "Y");
    MassPlot->SetXTitle("M_{T}[GeV/c^{2}]");

    MassPlot->SetYTitle("Events");
    MassPlot->Draw();

    char epsfilename[200];
    char Cfilename[200];

    if(opts.getBoolVal("AllFit")) {
      sprintf(epsfilename,"fit-plots/eps/Mt-data.eps");
      sprintf(Cfilename,"fit-plots/macro/Mt-data.C");
    }
    if(opts.getBoolVal("WOnlyFit")) {
      sprintf(epsfilename,"shapes/WInclusive/eps/Mt-Wonly.eps");
      sprintf(Cfilename,"shapes/WInclusive/macro/Mt-Wonly.C");
    }
    if(opts.getBoolVal("QCDOnlyFit")) {
      sprintf(epsfilename,"shapes/WInclusive/eps/Mt-QCDonly.eps");
      sprintf(Cfilename,"shapes/WInclusive/macro/Mt-QCDonly.C");
    }
    if(opts.getBoolVal("otherOnlyFit")) {
      sprintf(epsfilename,"shapes/WInclusive/eps/Mt-otheronly.eps");
      sprintf(Cfilename,"shapes/WInclusive/macro/Mt-otheronly.C");
    }
    c->SaveAs(epsfilename);
    c->SaveAs(Cfilename);
  }

  if(opts.getBoolVal("useTcMt")) {
    TCanvas *c = new TCanvas("c","fitResult");
    RooPlot* MassPlot = MakePlot("tcmt", &theFit, data, configfilename, nbins, usePoissonError);    
    
    MassPlot->SetAxisColor(1,"x");
    MassPlot->SetLabelColor(1, "X");
    MassPlot->SetLabelColor(1, "Y");
    MassPlot->SetXTitle("t.c. M_{T}[GeV/c^{2}]");

    MassPlot->SetYTitle("Events");
    MassPlot->Draw();

    char epsfilename[200];
    char Cfilename[200];

    if(opts.getBoolVal("AllFit")) {
      sprintf(epsfilename,"fit-plots/eps/TcMt-data.eps");
      sprintf(Cfilename,"fit-plots/macro/TcMt-data.C");
    }
    if(opts.getBoolVal("WOnlyFit")) {
      sprintf(epsfilename,"shapes/WInclusive/eps/TcMt-Wonly.eps");
      sprintf(Cfilename,"shapes/WInclusive/macro/TcMt-Wonly.C");
    }
    if(opts.getBoolVal("QCDOnlyFit")) {
      sprintf(epsfilename,"shapes/WInclusive/eps/TcMt-QCDonly.eps");
      sprintf(Cfilename,"shapes/WInclusive/macro/TcMt-QCDonly.C");
    }
    if(opts.getBoolVal("otherOnlyFit")) {
      sprintf(epsfilename,"shapes/WInclusive/eps/TcMt-otheronly.eps");
      sprintf(Cfilename,"shapes/WInclusive/macro/TcMt-otheronly.C");
    }
    c->SaveAs(epsfilename);
    c->SaveAs(Cfilename);
  }

  if(opts.getBoolVal("usePfMt")) {
    TCanvas *c = new TCanvas("c","fitResult");
    RooPlot* MassPlot = MakePlot("pfmt", &theFit, data, configfilename, nbins, usePoissonError);    
    
    MassPlot->SetAxisColor(1,"x");
    MassPlot->SetLabelColor(1, "X");
    MassPlot->SetLabelColor(1, "Y");
    MassPlot->SetXTitle("p.f. M_{T}[GeV/c^{2}]");

    MassPlot->SetYTitle("Events");
    MassPlot->Draw();

    char epsfilename[200];
    char Cfilename[200];

    if(opts.getBoolVal("AllFit")) {
      sprintf(epsfilename,"fit-plots/eps/PfMt-data.eps");
      sprintf(Cfilename,"fit-plots/macro/PfMt-data.C");
    }
    if(opts.getBoolVal("WOnlyFit")) {
      sprintf(epsfilename,"shapes/WInclusive/eps/PfMt-Wonly.eps");
      sprintf(Cfilename,"shapes/WInclusive/macro/PfMt-Wonly.C");
    }
    if(opts.getBoolVal("QCDOnlyFit")) {
      sprintf(epsfilename,"shapes/WInclusive/eps/PfMt-QCDonly.eps");
      sprintf(Cfilename,"shapes/WInclusive/macro/PfMt-QCDonly.C");
    }
    if(opts.getBoolVal("otherOnlyFit")) {
      sprintf(epsfilename,"shapes/WInclusive/eps/PfMt-otheronly.eps");
      sprintf(Cfilename,"shapes/WInclusive/macro/PfMt-otheronly.C");
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
    RooRealVar *met = new RooRealVar("met","E_{T}^{miss}",0.0,500.,"GeV");
    RooRealVar *tcmet = new RooRealVar("tcmet","t.c. E_{T}^{miss}",0.0,500.,"GeV");
    RooRealVar *pfmet = new RooRealVar("pfmet","p.f. E_{T}^{miss}",0.0,500.,"GeV");
    RooRealVar *mt = new RooRealVar("mt","m_{T}^{W}",0.0,500.,"GeV");
    RooRealVar *tcmt = new RooRealVar("tcmt","t.c. m_{T}^{W}",0.0,500.,"GeV");
    RooRealVar *pfmt = new RooRealVar("pfmt","p.f. m_{T}^{W}",10.0,150.,"GeV");

    // other variables
    RooRealVar *weight = new RooRealVar("weight","weight",0,10000);
    
    theFit2.AddFlatFileColumn(met);
    theFit2.AddFlatFileColumn(tcmet);
    theFit2.AddFlatFileColumn(pfmet);
    theFit2.AddFlatFileColumn(mt);
    theFit2.AddFlatFileColumn(tcmt);
    theFit2.AddFlatFileColumn(pfmt);
    theFit2.AddFlatFileColumn(weight);

    // define a fit model
    theFit2.addModel("qcdFit", "qcd Fit");
    theFit2.addSpecies("qcdFit", "qcd", "QCD Bkg Component");
    if(opts.getBoolVal("useMt"))   theFit2.addPdfWName("qcdFit", "qcd",  "Mt",    "Cruijff",  "qcd_Mt");
    if(opts.getBoolVal("useTcMt")) theFit2.addPdfWName("qcdFit", "qcd",  "TcMt",  "Cruijff",  "qcd_TcMt");
    if(opts.getBoolVal("usePfMt")) theFit2.addPdfWName("qcdFit", "qcd",  "PfMt",  "Cruijff",  "qcd_PfMt");

    RooAbsPdf *myPdf2 = theFit2.buildModel("qcdFit");
    theFit2.initialize(configfilename);

    myPdf2->plotOn(plot, RooFit::Normalization(Nqcd/(Ns+Nother+Nqcd)),RooFit::LineColor(kBlack),RooFit::LineStyle(kDashed));

    // === plot (dashed) the other component ===
    MLFit theFit3;

    theFit3.AddFlatFileColumn(met);
    theFit3.AddFlatFileColumn(tcmet);
    theFit3.AddFlatFileColumn(pfmet);
    theFit3.AddFlatFileColumn(mt);
    theFit3.AddFlatFileColumn(tcmt);
    theFit3.AddFlatFileColumn(pfmt);
    theFit3.AddFlatFileColumn(weight);

    // define a fit model
    theFit3.addModel("otherFit", "other Fit");
    theFit3.addSpecies("otherFit", "other", "other Bkg Component");
    if(opts.getBoolVal("useMt"))   theFit3.addPdfWName("qcdFit", "other",  "Mt",    "Cruijff",  "qcd_Mt");
    if(opts.getBoolVal("useTcMt")) theFit3.addPdfWName("qcdFit", "other",  "TcMt",  "Cruijff",  "qcd_TcMt");
    if(opts.getBoolVal("usePfMt")) theFit3.addPdfWName("qcdFit", "other",  "PfMt",  "Cruijff",  "qcd_PfMt");

    RooAbsPdf *myPdf3 = theFit3.buildModel("otherFit");
    theFit3.initialize(configfilename);

    myPdf3->plotOn(plot, RooFit::Normalization(Nother/(Ns+Nother+Nqcd)),RooFit::LineColor(kBlack), RooFit::LineStyle(3));
  
  }

  return plot;
}

