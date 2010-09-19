// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("fitCaloJets",     "Fit calojets, PFjets otherwise", kFALSE);
  opts.addBoolOption("weightedDataset", "use event weight instead of 1",     kFALSE);
  opts.addBoolOption("usePfMt",         "Use W Transverse Mass",  kTRUE);
  opts.addBoolOption("AllFit",          "Fit all species",        kTRUE);
  opts.addBoolOption("WOnlyFit",        "Fit W species only",     kFALSE);
  opts.addBoolOption("QCDOnlyFit",      "Fit QCD species only",   kFALSE);
  opts.addBoolOption("otherOnlyFit",    "Fit other species only", kFALSE);
  opts.addBoolOption("preliminaryLabel", "Add the label with CMS preliminary", kTRUE);

  return opts;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

MLFit theFit;

void myFit(int njets) {

  MLFit theFit;

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // define the structure of the dataset
  RooRealVar* pfmt = new RooRealVar("pfmt",  "M_{T}" , 0., 150., "GeV/c^{2}");
  RooRealVar* weight = new RooRealVar("weight", "weight",1);

  theFit.AddFlatFileColumn(pfmt);
  theFit.AddFlatFileColumn(weight);

  // define a fit model
  theFit.addModel("myFit", "Ratio WtoENu");
  
  // define species
  theFit.addSpecies("myFit", "sig",    "Signal Component");
  theFit.addSpecies("myFit", "qcd",    "qcd Component");
  theFit.addSpecies("myFit", "other",  "Other Bkgs Component");

  // Mt PDF
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
void FitWElectrons(int njets, int ithr) {
  
  myFit(njets);

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "PFjet");

  // Load the data
  char datasetname[200];
  if(opts.getBoolVal("AllFit")) sprintf(datasetname,"results_data/datasetsJets/wenu_36X_%d%s_thr%d.root",njets,jetflavour,ithr);
  else sprintf(datasetname,"results/datasetsJets/wenu_36X_%d%s_thr%d.root",njets,jetflavour,ithr);
  // else sprintf(datasetname,"Toys_WPfMt/Syst_100nb/sigMT/pfmtHigh.root");
  char treename[100];
  if(opts.getBoolVal("AllFit")) sprintf(treename,"Data");
  if(opts.getBoolVal("WOnlyFit")) sprintf(treename,"T1");
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(treename,"QCDJets");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(treename,"OtherJets");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *dataTot = theFit.getDataSet(treename);
  RooDataSet *data = (RooDataSet*)dataTot->reduce("1==1");


  // use event weights
  if(opts.getBoolVal("weightedDataset")) data->setWeightVar("weight");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  if(opts.getBoolVal("AllFit")) {
    char initconfigfile[200];
    sprintf(initconfigfile,"fitconfig/fitW-%d%s-thr%d.config",njets,jetflavour,ithr);
    theFit.initialize(initconfigfile);
  }
  if(njets==0) {
    if(opts.getBoolVal("WOnlyFit")) theFit.initialize("shapes/WInclusive/config/WFit-Wonly.config");
    if(opts.getBoolVal("QCDOnlyFit")) theFit.initialize("shapes/WInclusive/config/WFit-QCDonly.config");
    if(opts.getBoolVal("otherOnlyFit")) theFit.initialize("shapes/WInclusive/config/WFit-otheronly.config");
  } else {
    if(opts.getBoolVal("WOnlyFit")) theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-Wonly.config");
    if(opts.getBoolVal("QCDOnlyFit")) theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-QCDonly.config");
    if(opts.getBoolVal("otherOnlyFit")) theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-otheronly.config");
  }

  // Print Fit configuration 
  myPdf->getParameters(data)->selectByAttrib("Constant",kTRUE)->Print("V");  
  myPdf->getParameters(data)->selectByAttrib("Constant",kFALSE)->Print("V");
  
  RooFitResult *fitres =  myPdf->fitTo(*data,RooFit::ConditionalObservables(theFit.getNoNormVars("myFit")),RooFit::FitOptions("MHTER"));
  fitres->Print("V");
  
  // write the config file corresponding to the fit minimum
  char configfilename[200];
  if(opts.getBoolVal("AllFit")) sprintf(configfilename, "fitres/fitMinimumW-%d%s-thr%d.config",njets,jetflavour,ithr);
  if(opts.getBoolVal("WOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-Wonly-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-QCDonly-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("otherOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-otheronly-%d%s.config",njets,jetflavour);
  theFit.writeConfigFile(configfilename);  

  // save the fit result in ROOT 
  char rootfilename[200];
  if(opts.getBoolVal("AllFit")) sprintf(rootfilename, "fitres/fitMinimumW-%d%s-thr%d.root",njets,jetflavour,ithr);
  if(opts.getBoolVal("WOnlyFit")) sprintf(rootfilename,"shapesWenu/root/fitRes-Wonly-%d%s.root",njets,jetflavour);
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(rootfilename,"shapesWenu/root/fitRes-QCDonly-%d%s.root",njets,jetflavour);
  if(opts.getBoolVal("otherOnlyFit")) sprintf(rootfilename,"shapesWenu/root/fitRes-otheronly-%d%s.root",njets,jetflavour);

  TFile *file = new TFile(rootfilename,"recreate");
  fitres->Write();
  file->Close();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotWElectrons(int njets, int ithr, int nbins) {

  myFit(njets);

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "PFjet");

  // Load the data
  char datasetname[200];
  if(opts.getBoolVal("AllFit")) sprintf(datasetname,"results_data/datasetsJets/wenu_36X_%d%s_thr%d.root",njets,jetflavour,ithr);
  else sprintf(datasetname,"results/datasetsJets/wenu_36X_%d%s_thr%d.root",njets,jetflavour,ithr);
  // else sprintf(datasetname,"Toys_WPfMt/Syst_100nb/sigMT/pfmtHigh.root");
  char treename[100];
  if(opts.getBoolVal("AllFit")) sprintf(treename,"Data");
  if(opts.getBoolVal("WOnlyFit")) sprintf(treename,"T1");
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(treename,"QCDJets");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(treename,"OtherJets");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *dataTot = theFit.getDataSet(treename);
  RooDataSet *data = (RooDataSet*)dataTot->reduce("1==1");

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
  if(opts.getBoolVal("AllFit")) sprintf(configfilename,"fitres/fitMinimumW-%d%s-thr%d.config",njets,jetflavour,ithr);
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

    char binsize[50];
    Double_t binW = MassPlot->getFitRangeBinW();
    sprintf(binsize,"%2.0f",binW);

    MassPlot->SetYTitle(TString("Events / (")+TString(binsize)+TString(" GeV/c^{2})"));
    MassPlot->Draw();

    makeLegend();

    if(opts.getBoolVal("preliminaryLabel")) {
      TPaveText pt1(0.1,0.96,0.8,0.98,"NDC");
      pt1.SetTextFont(72);
      pt1.SetTextSize(0.03);
      pt1.SetTextAlign(12);
      pt1.SetFillColor(0);
      pt1.SetBorderSize(0);
      pt1.AddText("CMS Preliminary 2010, #sqrt{s}=7 TeV, L_{int}=2.88 pb^{-1}");
      pt1.Draw();
    }
 
    char epsfilename[200];
    char Cfilename[200];

    if(opts.getBoolVal("AllFit")) {
      sprintf(epsfilename,"fit-plots/eps/PfMt-data-%d%s-thr%d.eps",njets,jetflavour,ithr);
      sprintf(Cfilename,"fit-plots/macro/PfMt-data-%d%s-thr%d.C",njets,jetflavour,ithr);
    }
    if(opts.getBoolVal("WOnlyFit")) {
      sprintf(epsfilename,"shapesWenu/eps/PfMt-Wonly-%d%s-thr%d.eps",njets,jetflavour,ithr);
      sprintf(Cfilename,"shapesWenu/macro/PfMt-Wonly-%d%s-thr%d.C",njets,jetflavour,ithr);
    }
    if(opts.getBoolVal("QCDOnlyFit")) {
      sprintf(epsfilename,"shapesWenu/eps/PfMt-QCDonly-%d%s-thr%d.eps",njets,jetflavour,ithr);
      sprintf(Cfilename,"shapesWenu/macro/PfMt-QCDonly-%d%s-thr%d.C",njets,jetflavour,ithr);
    }
    if(opts.getBoolVal("otherOnlyFit")) {
      sprintf(epsfilename,"shapesWenu/eps/PfMt-otheronly-%d%s-thr%d.eps",njets,jetflavour,ithr);
      sprintf(Cfilename,"shapesWenu/macro/PfMt-otheronly-%d%s-thr%d.C",njets,jetflavour,ithr);
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

  if(opts.getBoolVal("AllFit")) {
    // === plot (dashed) the qcd component ===
    MLFit theFit2;

    // define the structure of the dataset
    RooRealVar* PfMt = new RooRealVar("pfmt",  "M_{T}" , 0., 150., "GeV/c^{2}");
    //    RooRealVar *sinMHTphiJet = new RooRealVar("sinMHTphiJet","sinMHTphiJet",-0.80, 0.80);

    theFit2.AddFlatFileColumn(PfMt);
    //    theFit2.AddFlatFileColumn(sinMHTphiJet);

    // define a fit model
    theFit2.addModel("qcdFit", "qcd Fit");
    theFit2.addSpecies("qcdFit", "qcd", "qcd Bkg Component");
    theFit2.addSpecies("qcdFit", "other", "other Bkg Component");
    if(njets==0) {
      theFit2.addPdfWName("qcdFit", "qcd",   "pfmt", "Cruijff", "qcd_PfMt");
      theFit2.addPdfWName("qcdFit", "other", "pfmt", "Cruijff",  "other_PfMt");
    } else {
      theFit2.addPdfWName("qcdFit", "qcd",  "pfmt", "DoubleGaussian",  "qcd_PfMt");
      theFit2.addPdfWName("qcdFit", "other", "pfmt", "DoubleCruijff", "other_PfMt");
    }

    RooAbsPdf *myPdf2 = theFit2.buildModel("qcdFit");
    theFit2.initialize(configfilename);

    myPdf2->plotOn(plot, RooFit::Normalization((Nqcd+Nother)/fabs(Ns+Nother+Nqcd)), RooFit::DrawOption("F"), RooFit::FillColor(kViolet), RooFit::MoveToBack() );
    myPdf2->plotOn(plot, RooFit::Normalization((Nqcd+Nother)/fabs(Ns+Nother+Nqcd)), RooFit::LineColor(kViolet+3), RooFit::LineWidth(2) );

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

    myPdf3->plotOn(plot, RooFit::Normalization(Nother/fabs(Ns+Nother+Nqcd)), RooFit::DrawOption("F"), RooFit::FillColor(kOrange+8), RooFit::LineWidth(2));
    myPdf3->plotOn(plot, RooFit::Normalization(Nother/fabs(Ns+Nother+Nqcd)), RooFit::LineColor(kOrange+4), RooFit::LineWidth(2));
  
  }

  // plot the total likelihood
  RooAbsPdf *thePdf = theFit->getPdf("myFit");
  thePdf->plotOn(plot, RooFit::DrawOption("F"), RooFit::LineColor(kOrange+4), RooFit::FillColor(kOrange), RooFit::LineWidth(2), RooFit::MoveToBack() );
  //  thePdf->plotOn(plot, RooFit::DrawOption("L"), RooFit::LineColor(kOrange+7), RooFit::LineWidth(2) );

  return plot;
}

void makeLegend() {
  // Legend
  TH1F *dataH = new TH1F("dataH","dataH",50,0,150);
  TH1F *totalH = new TH1F("totalH","totalH",50,0,150);
  TH1F *otherPlusQCDH = new TH1F("otherPlusQcdH","otherPlusQcdH",50,0,150);
  TH1F *qcdH = new TH1F("qcdH","qcdH",50,0,150);

  dataH->SetMarkerColor(kBlack);
  totalH->SetFillColor(kOrange);
  otherPlusQcdH->SetFillColor(kViolet);
  qcdH->SetFillColor(kOrange+8);

  TLegendEntry *legge;
  TLegend *leg;
  leg = new TLegend(0.6,0.65,0.93,0.8);
  leg->SetFillStyle(0); leg->SetBorderSize(0.); leg->SetTextSize(0.025);
  leg->SetFillColor(0);
  legge = leg->AddEntry(dataH,"Data", "lpe");
  legge = leg->AddEntry(totalH,"total","f");
  legge = leg->AddEntry(otherPlusQcdH,"EWK+QCD","f");
  legge = leg->AddEntry(qcdH,"EWK","f");
  leg->Draw();
  gPad->Update();
}
