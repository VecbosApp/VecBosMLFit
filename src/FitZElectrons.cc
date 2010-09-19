// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("fitCaloJets",     "Fit calojets, PFjets otherwise", kFALSE);
  opts.addBoolOption("weightedDataset", "use event weight instead of 1",     kFALSE);
  opts.addBoolOption("useMass",         "Use Invariant Mass",     kTRUE);        
  opts.addBoolOption("useMHTphiMET",    "Use sin(MHTphiMET)",     kFALSE);
  opts.addBoolOption("AllFit",          "Fit all species",        kTRUE);
  opts.addBoolOption("ZOnlyFit",        "Fit Z species only",     kFALSE);
  opts.addBoolOption("bkgOnlyFit",      "Fit bkg species only",   kFALSE);
  opts.addBoolOption("preliminaryLabel", "Add the label with CMS preliminary", kTRUE);

  return opts;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

MLFit theFit;

void myFit() {

  MLFit theFit;

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // define the structure of the dataset
  RooRealVar* mee = new RooRealVar("mee",  "Mass [GeV/c^{2}]" , 60., 110.);
  RooRealVar* sinMHTphiMET = new RooRealVar("sinMHTphiMET", "sin #phi_{MHT-MET}",-0.85,0.85);
  RooRealVar* weight = new RooRealVar("evtWeight", "evtWeight",1);

  theFit.AddFlatFileColumn(mee);
  theFit.AddFlatFileColumn(sinMHTphiMET);
  theFit.AddFlatFileColumn(weight);

  // define a fit model
  theFit.addModel("myFit", "Ratio ZtoEE");
  
  // define species
  theFit.addSpecies("myFit", "sig", "Signal Component");
  theFit.addSpecies("myFit", "bkg", "Bkg Component");
  
  // mLL PDF
  if(opts.getBoolVal("useMass")) {
    theFit.addPdfWName("myFit", "sig" , "mee",  "Cruijff", "sig_Mass");
    theFit.addPdfWName("myFit", "bkg" , "mee",  "Poly2",   "bkg_Mass");
  }
  // shape variable
  if(opts.getBoolVal("useMHTphiMET")) {
    theFit.addPdfWName("myFit", "sig" , "sinMHTphiMET",  "Cruijff", "sig_sinMHTphiMET");
    theFit.addPdfWName("myFit", "bkg" , "sinMHTphiMET",  "Poly2",   "bkg_sinMHTphiMET");
  }
  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fit a sample of Z events
void FitZElectrons(int njets, int ithr) {
  
  myFit();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "PFjet");

  // Load the data
  char datasetname[200];
  if(opts.getBoolVal("AllFit")) sprintf(datasetname,"results_data/datasetsJets/zee_36X_%d%s_thr%d.root",njets,jetflavour,ithr);
  else sprintf(datasetname,"results/datasetsJets/zee_36X_%d%s_thr%d.root",njets,jetflavour,ithr);
  char treename[100];
  if(opts.getBoolVal("AllFit")) sprintf(treename,"DataJets");
  if(opts.getBoolVal("ZOnlyFit")) sprintf(treename,"ZJets");
  if(opts.getBoolVal("bkgOnlyFit")) sprintf(treename,"BkgJets");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);
  if(opts.getBoolVal("ZOnlyFit")) data = (RooDataSet*)data->reduce("ZToEEDecay==1");

  // use event weights
  if(opts.getBoolVal("weightedDataset")) data->setWeightVar("evtWeight");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  if(opts.getBoolVal("AllFit")) {
    char initconfigfile[200];
    sprintf(initconfigfile,"fitconfig/fitZ-%d%s-thr%d.config",njets,jetflavour,ithr);
    theFit.initialize(initconfigfile);
  }
  if(opts.getBoolVal("ZOnlyFit")) theFit.initialize("shapesZee/config/RatioElectrons-ZjetsFit-Zonly.config");
  if(opts.getBoolVal("bkgOnlyFit")) theFit.initialize("shapesZee/config/RatioElectrons-ZjetsFit-bkgonly.config");
  
  // Print Fit configuration 
  myPdf->getParameters(data)->selectByAttrib("Constant",kTRUE)->Print("V");  
  myPdf->getParameters(data)->selectByAttrib("Constant",kFALSE)->Print("V");
  
  RooFitResult *fitres =  myPdf->fitTo(*data,RooFit::ConditionalObservables(theFit.getNoNormVars("myFit")),RooFit::FitOptions("MHTER"));
  fitres->Print("V");
  
  // write the config file corresponding to the fit minimum
  char configfilename[200];
  if(opts.getBoolVal("AllFit")) sprintf(configfilename, "fitres/fitMinimumZ-%d%s-thr%d.config",njets,jetflavour,ithr);
  if(opts.getBoolVal("ZOnlyFit")) sprintf(configfilename, "shapesZee/config/fitMinimum-Zonly-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("bkgOnlyFit")) sprintf(configfilename, "shapesZee/config/fitMinimum-bkgonly-%d%s.config",njets,jetflavour);
  theFit.writeConfigFile(configfilename);  
  
  // save the fit result in ROOT 
  char rootfilename[200];
  if(opts.getBoolVal("AllFit")) sprintf(rootfilename, "fitres/fitMinimumZ-%d%s-thr%d.root",njets,jetflavour,ithr);
  if(opts.getBoolVal("ZOnlyFit")) sprintf(rootfilename,"shapesZee/root/fitRes-Zonly-%d%s.root",njets,jetflavour);
  if(opts.getBoolVal("bkgOnlyFit")) sprintf(rootfilename,"shapesZee/root/fitRes-bkgonly-%d%s.root",njets,jetflavour);

  TFile *file = new TFile(rootfilename,"recreate");
  fitres->Write();
  file->Close();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotZElectrons(int njets, int ithr, int nbins) {

  myFit();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "PFjet");

  // Load the data
  char datasetname[200];
  if(opts.getBoolVal("AllFit")) sprintf(datasetname,"results_data/datasetsJets/zee_36X_%d%s_thr%d.root",njets,jetflavour,ithr);
  else sprintf(datasetname,"results/datasetsJets/zee_36X_%d%s_thr%d.root",njets,jetflavour,ithr);
  char treename[100];
  if(opts.getBoolVal("AllFit")) sprintf(treename,"DataJets");
  if(opts.getBoolVal("ZOnlyFit")) sprintf(treename,"ZJets");
  if(opts.getBoolVal("bkgOnlyFit")) sprintf(treename,"BkgJets");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);
  if(opts.getBoolVal("ZOnlyFit")) data = (RooDataSet*)data->reduce("ZToEEDecay==1");

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
  if(opts.getBoolVal("AllFit")) sprintf(configfilename,"fitres/fitMinimumZ-%d%s-thr%d.config",njets,jetflavour,ithr);
  if(opts.getBoolVal("ZOnlyFit")) sprintf(configfilename, "shapesZee/config/fitMinimum-Zonly-%d%s.config",njets,jetflavour);
  if(opts.getBoolVal("bkgOnlyFit")) sprintf(configfilename, "shapesZee/config/fitMinimum-bkgonly-%d%s.config",njets,jetflavour);
  theFit.initialize(configfilename);

  if(opts.getBoolVal("useMass")) {
    TCanvas *c = new TCanvas("c","fitResult");
    RooPlot* MassPlot = MakePlot("mee", &theFit, data, nbins,usePoissonError);    
    
    MassPlot->SetAxisColor(1,"x");
    MassPlot->SetLabelColor(1, "X");
    MassPlot->SetLabelColor(1, "Y");
    MassPlot->SetXTitle("m_{e^{+}e^{-}}[GeV/c^{2}]");

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
      sprintf(epsfilename,"fit-plots/eps/Mass-data-%d%s-thr%d.eps",njets,jetflavour,ithr);
      sprintf(Cfilename,"fit-plots/macro/Mass-data-%d%s-thr%d.C",njets,jetflavour,ithr);
    }
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
    RooPlot* AngularPlot = MakePlot("sinMHTphiMET", &theFit, data, nbins,usePoissonError);    
    
    AngularPlot->SetAxisColor(1,"x");
    AngularPlot->SetLabelColor(1, "X");
    AngularPlot->SetLabelColor(1, "Y");
    AngularPlot->SetXTitle("sin(#phi_{MHT,MET})");

    AngularPlot->SetYTitle("Events");
    AngularPlot->Draw();

    char epsfilename[200];
    char Cfilename[200];

    if(opts.getBoolVal("AllFit")) {
      sprintf(epsfilename,"fit-plots/eps/sinMHTphiMET-data-%d%s.eps",njets,jetflavour);
      sprintf(Cfilename,"fit-plots/macro/sinMHTphiMET-data-%d%s.C",njets,jetflavour);
    }
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

  double Ns = theFit->getRealPar("N_sig")->getVal();
  double Nb = theFit->getRealPar("N_bkg")->getVal();

  RooAbsPdf *thePdf = theFit->getPdf("myFit");
  // plot the total likelihood
  theFit->getRealPar("N_sig")->setVal(Ns);
  thePdf->plotOn(plot, RooFit::DrawOption("F"), RooFit::LineColor(kOrange+4), RooFit::FillColor(kOrange), RooFit::LineWidth(2), RooFit::MoveToBack() );

  // plot the bkg component
  theFit->getRealPar("N_sig")->setVal(0.);
  thePdf->plotOn(plot, RooFit::Normalization(Nb/(Ns+Nb)), RooFit::DrawOption("F"), RooFit::FillColor(kViolet) );
  thePdf->plotOn(plot, RooFit::Normalization(Nb/(Ns+Nb)), RooFit::LineColor(kViolet+3), RooFit::LineWidth(2) );
  
  return plot;
}

void makeLegend() {
  // Legend
  TH1F *dataH = new TH1F("dataH","dataH",50,0,150);
  TH1F *totalH = new TH1F("totalH","totalH",50,0,150);
  TH1F *qcdH = new TH1F("qcdH","qcdH",50,0,150);

  dataH->SetMarkerColor(kBlack);
  totalH->SetFillColor(kOrange);
  qcdH->SetFillColor(kViolet);

  TLegendEntry *legge;
  TLegend *leg;
  leg = new TLegend(0.2,0.65,0.53,0.8);
  leg->SetFillStyle(0); leg->SetBorderSize(0.); leg->SetTextSize(0.025);
  leg->SetFillColor(0);
  legge = leg->AddEntry(dataH,"Data", "lpe");
  legge = leg->AddEntry(totalH,"total","f");
  legge = leg->AddEntry(qcdH,"bkg only","f");
  leg->Draw();
  gPad->Update();
}
