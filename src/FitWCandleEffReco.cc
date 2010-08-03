// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;

  // Fit configuration
  opts.addBoolOption("weightedDataset", "use event weight instead of 1", kFALSE);
  opts.addBoolOption("AllFit",          "Fit all species",        kTRUE);
  opts.addBoolOption("WOnlyFit",        "Fit W species only",     kFALSE);
  opts.addBoolOption("QCDOnlyFit",      "Fit QCD species only",   kFALSE);
  opts.addBoolOption("otherOnlyFit",    "Fit other species only", kFALSE);
  opts.addBoolOption("useCaloJet",      "Use calo jets",          kTRUE);
  opts.addBoolOption("usePFJet",        "Use PF jets",            kFALSE);

  // efficiency
  opts.addBoolOption("egOnlyEff",       "Fit for N and EG reconstruction eff", kFALSE);
  opts.addBoolOption("pfOnlyEff",       "Fit for N and PF reconstruction eff", kTRUE);

  opts.addBoolOption("barrel",          "Fit for barrel only",   kFALSE);
  opts.addBoolOption("endcap",          "Fit for endcap only",   kTRUE);
  opts.addBoolOption("endcapPlus",      "Fit for endcap + only", kFALSE);
  opts.addBoolOption("endcapMinus",     "Fit for endcap - only", kFALSE);


  return opts;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////

MLFit theFit;

void myFit() {

  MLFit theFit;

  // Various fit options...
  MLOptions opts = GetDefaultOptions();
  
  // define the structure of the dataset
  RooRealVar *mt        = new RooRealVar("mt","p.f. m_{T}^{W}",20.0,150.,"GeV");
  RooRealVar *matchedEG = new RooRealVar("matchedEG", "matchedEG",-1,1);
  RooRealVar *matchedPF = new RooRealVar("matchedPF", "matchedPF",-1,1);
  RooRealVar *eta       = new RooRealVar("eta","electron #eta",-2.5,2.5);
  RooRealVar *pt        = new RooRealVar("pt", "electron p_{T}",  0.0, 100000., "GeV/c");
  RooRealVar *covIeIe                   = new RooRealVar("covIeIe",                "cov ieta ieta",         0., 100000.); 
  RooRealVar *hoe                       = new RooRealVar("hoe",                       "H/E",            -1000., 100000.); 
  RooRealVar *ecalRecHitSumEtConeDR03SC = new RooRealVar("ecalRecHitSumEtConeDR03SC", "ecal isol",      -1000., 100000.);
  RooRealVar *hcalTowerSumEtConeDR03SC  = new RooRealVar("hcalTowerSumEtConeDR03SC",  "hcal isol",      -1000., 100000.);
  RooRealVar *trkSumPtSolidConeDR03SC   = new RooRealVar("trkSumPtSolidConeDR03SC",   "tracker isol",   -1000., 100000.);  
  RooRealVar *nCaloJets = new RooRealVar("nCaloJets","# calo jets",0.0, 500.);
  RooRealVar *nPFJets   = new RooRealVar("nPFJets","# PF jets",0.0, 500.);
  RooRealVar *weight    = new RooRealVar("weight","weight",0,10000); 

  theFit.AddFlatFileColumn(mt);
  theFit.AddFlatFileColumn(matchedEG);
  theFit.AddFlatFileColumn(matchedPF);
  theFit.AddFlatFileColumn(eta);
  theFit.AddFlatFileColumn(pt);
  theFit.AddFlatFileColumn(nCaloJets);
  theFit.AddFlatFileColumn(nPFJets);
  theFit.AddFlatFileColumn(covIeIe);
  theFit.AddFlatFileColumn(hoe);
  theFit.AddFlatFileColumn(ecalRecHitSumEtConeDR03SC);
  theFit.AddFlatFileColumn(hcalTowerSumEtConeDR03SC);
  theFit.AddFlatFileColumn(trkSumPtSolidConeDR03SC);
  //  theFit.AddFlatFileColumn(weight);   // chiara, da commentare per i dati

  // define a fit model
  theFit.addModel("myFit", "Inclusive WtoENu");
  
  // define species
  theFit.addSpecies("myFit", "sig_a",   "Accepted Signal Component");
  theFit.addSpecies("myFit", "qcd_a",   "Accepted QCD Component");
  theFit.addSpecies("myFit", "other_a", "Accepted Other Bkgs Component");
  
  theFit.addSpecies("myFit", "sig_r",   "Rejected Signal Component");
  theFit.addSpecies("myFit", "qcd_r",   "Rejected QCD Component");
  theFit.addSpecies("myFit", "other_r", "Rejected Other Bkgs Component");

  theFit.fitWithEff("sig_a",   "sig_r",   "sig");
  theFit.fitWithEff("qcd_a",   "qcd_r",   "qcd");
  theFit.fitWithEff("other_a", "other_r", "other");

  
  // P.F. Mt PDF
  theFit.addPdfWName("myFit", "sig_a",   "mt", "DoubleCruijff", "sig_PfMt");
  theFit.addPdfWName("myFit", "qcd_a",   "mt", "Cruijff",       "qcd_PfMt");
  theFit.addPdfWName("myFit", "other_a", "mt", "Cruijff",       "other_PfMt");
  
  theFit.bind(MLStrList("sig_PfMt_sigmaR1","sig_PfMt_sigmaR2"),"sig_PfMt_sigmaR","sig_PfMt_sigmaR");
  theFit.bind(MLStrList("sig_PfMt_alphaR1","sig_PfMt_alphaR2"),"sig_PfMt_alphaR","sig_PfMt_alphaR");
  
  theFit.addPdfCopy("myFit", "sig_r",   "mt", "sig_a");
  theFit.addPdfCopy("myFit", "qcd_r",   "mt", "qcd_a");
  theFit.addPdfCopy("myFit", "other_r", "mt", "other_a");

  // veto category
  if(opts.getBoolVal("egOnlyEff")) {  
    theFit.addPdfWName("myFit", "sig_a" ,   "matchedEG",  "Poly2",  "veto_acc");
    theFit.addPdfCopy ("myFit", "qcd_a",    "matchedEG",  "sig_a");
    theFit.addPdfCopy ("myFit", "other_a",  "matchedEG",  "sig_a");
    
    theFit.addPdfWName("myFit", "sig_r" ,   "matchedEG",  "Poly2",  "veto_rej");
    theFit.addPdfCopy ("myFit", "qcd_r",    "matchedEG",  "sig_r");
    theFit.addPdfCopy ("myFit", "other_r",  "matchedEG",  "sig_r");
  }

  if(opts.getBoolVal("pfOnlyEff")) {
    theFit.addPdfWName("myFit", "sig_a" ,   "matchedPF",  "Poly2",  "veto_acc");
    theFit.addPdfCopy ("myFit", "qcd_a",    "matchedPF",  "sig_a");
    theFit.addPdfCopy ("myFit", "other_a",  "matchedPF",  "sig_a");
    
    theFit.addPdfWName("myFit", "sig_r" ,   "matchedPF",  "Poly2",  "veto_rej");
    theFit.addPdfCopy ("myFit", "qcd_r",    "matchedPF",  "sig_r");
    theFit.addPdfCopy ("myFit", "other_r",  "matchedPF",  "sig_r");
  }
}

// Fit a sample of W events
void FitWElectrons() {
  
  myFit();
  
  // Various fit options...
  MLOptions opts = GetDefaultOptions();
  
  // Load the data
  char datasetname[200];
  char treename[100];
  if(opts.getBoolVal("AllFit")) {
    sprintf(datasetname,"results_data_reco/dataMerged_SCStudy.root");
    sprintf(treename,"T1");
  } else sprintf(treename,"T1");
  if(opts.getBoolVal("WOnlyFit"))     sprintf(datasetname,"results/datasets/WJetsMADGRAPH_SCStudy.root");   
  if(opts.getBoolVal("QCDOnlyFit"))   sprintf(datasetname,"results/datasets/QCD_SCStudy.root");           
  if(opts.getBoolVal("otherOnlyFit")) sprintf(datasetname,"results/datasets/other_SCStudy.root");       
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);

  // chiara, barrel only (sistema per PF jets)
  if (opts.getBoolVal("useCaloJet")) {
    // data = (RooDataSet*)data->reduce("(nCaloJets==0) && ( eta<-1.479 ) && (met/pt>0.3) && (matchedEG==1)");   // chiara

    /* 
    data = (RooDataSet*)data->reduce("nCaloJets==0 && met/pt>0.3");
    if(opts.getBoolVal("barrel"))
      data = (RooDataSet*)data->reduce("abs(eta)<1.479 && hoe<0.04 && sqrt(covIeIe)<0.01 && (ecalRecHitSumEtConeDR03SC/pt)<0.07 && (hcalTowerSumEtConeDR03SC/pt)<0.1 && (trkSumPtSolidConeDR03SC/pt)<0.09");
    else if(opts.getBoolVal("endcapPlus"))
      data = (RooDataSet*)data->reduce("eta>1.479 && hoe<0.025 && sqrt(covIeIe)<0.03 && (ecalRecHitSumEtConeDR03SC/pt)<0.05 && (hcalTowerSumEtConeDR03SC/pt)<0.025 && (trkSumPtSolidConeDR03SC/pt)<0.04");
    else if(opts.getBoolVal("endcapMinus"))
      data = (RooDataSet*)data->reduce("eta<-1.479 && hoe<0.025 && sqrt(covIeIe)<0.03 && (ecalRecHitSumEtConeDR03SC/pt)<0.05 && (hcalTowerSumEtConeDR03SC/pt)<0.025 && (trkSumPtSolidConeDR03SC/pt)<0.04");
    */

    // data = (RooDataSet*)data->reduce("runNumber>=138920");
    data = (RooDataSet*)data->reduce("nCaloJets==0 && met/pt>0.3");
    if(opts.getBoolVal("barrel"))
      data = (RooDataSet*)data->reduce("abs(eta)<1.479 && hoe<0.04 && sqrt(covIeIe)<0.01 && (ecalRecHitSumEtConeDR03SC/pt)<0.07 && (hcalTowerSumEtConeDR03SC/pt)<0.1 && (trkSumPtSolidConeDR03SC/pt)<0.09");
    else if(opts.getBoolVal("endcap"))
      data = (RooDataSet*)data->reduce("abs(eta)>1.479 && hoe<0.025 && sqrt(covIeIe)<0.03 && (ecalRecHitSumEtConeDR03SC/pt)<0.05 && (hcalTowerSumEtConeDR03SC/pt)<0.025 && (trkSumPtSolidConeDR03SC/pt)<0.04");
    else if(opts.getBoolVal("endcapPlus"))
      data = (RooDataSet*)data->reduce("eta>1.479 && hoe<0.025 && sqrt(covIeIe)<0.03 && (ecalRecHitSumEtConeDR03SC/pt)<0.05 && (hcalTowerSumEtConeDR03SC/pt)<0.025 && (trkSumPtSolidConeDR03SC/pt)<0.04");
    else if(opts.getBoolVal("endcapMinus"))
      data = (RooDataSet*)data->reduce("eta<-1.479 && hoe<0.025 && sqrt(covIeIe)<0.03 && (ecalRecHitSumEtConeDR03SC/pt)<0.05 && (hcalTowerSumEtConeDR03SC/pt)<0.025 && (trkSumPtSolidConeDR03SC/pt)<0.04");

  }

  // use event weights (the ones in the dataset are for 1/pb)
  if(opts.getBoolVal("weightedDataset")) data->setWeightVar("weight");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  if(opts.getBoolVal("AllFit")) theFit.initialize("fitconfig/WInclusive/fitW_withEffReco.config");   
  if(opts.getBoolVal("WOnlyFit")) theFit.initialize("shapes/WInclusive/config/fitW_Wonly_withEff.config"); 
  if(opts.getBoolVal("QCDOnlyFit")) theFit.initialize("shapes/WInclusive/config/fitW_QCDonly_withEff.config");   
  if(opts.getBoolVal("otherOnlyFit")) theFit.initialize("shapes/WInclusive/config/fitW_Otheronly_withEff.config"); 

  // Print Fit configuration 
  myPdf->getParameters(data)->selectByAttrib("Constant",kTRUE)->Print("V");  
  myPdf->getParameters(data)->selectByAttrib("Constant",kFALSE)->Print("V");
  
  RooArgSet *minosParameters = myPdf->getParameters(data)->selectByName("eff_sig");
  RooFitResult *fitres =  myPdf->fitTo(*data,RooFit::ConditionalObservables(theFit.getNoNormVars("myFit")),RooFit::Extended(kTRUE),RooFit::Hesse(kTRUE),RooFit::Minos(*minosParameters),RooFit::Save(kTRUE),RooFit::Timer(kTRUE));

  fitres->Print("V");
  
  // write the config file corresponding to the fit minimum
  char configfilename[200];
  if(opts.getBoolVal("AllFit")) sprintf(configfilename, "fitres/WInclusive/fitMinimum-data_withEffReco.config");
  if(opts.getBoolVal("WOnlyFit")) sprintf(configfilename,"shapes/WInclusive/config/fitMinimum-Wonly_withEff.config"); 
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(configfilename,"shapes/WInclusive/config/fitMinimum-QCDonly_withEff.config"); 
  if(opts.getBoolVal("otherOnlyFit")) sprintf(configfilename,"shapes/WInclusive/config/fitMinimum-otheronly_withEff.config");
  theFit.writeConfigFile(configfilename);

  // save the fit result in ROOT 
  char rootfilename[200];
  if(opts.getBoolVal("AllFit")) sprintf(rootfilename,"fitres/WInclusive/fitMinimum.root"); 
  if(opts.getBoolVal("WOnlyFit")) sprintf(rootfilename,"shapes/WInclusive/root/fitRes-Wonly.root");
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(rootfilename,"shapes/WInclusive/root/fitRes-QCDonly.root");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(rootfilename,"shapes/WInclusive/root/fitRes-otheronly.root");
  
  TFile *file = new TFile(rootfilename,"recreate");
  fitres->Write();
  file->Close();
}

void PlotWElectrons(int nbins) {
  
  myFit();
  
  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // Load the data
  char datasetname[200];
  char treename[100];
  if(opts.getBoolVal("AllFit")) {
    sprintf(datasetname,"results_data_reco/dataMerged_SCStudy.root");
    sprintf(treename,"T1");
  } else sprintf(treename,"T1"); 
  if(opts.getBoolVal("WOnlyFit")) sprintf(datasetname,"results/datasets/WJetsMADGRAPH_SCStudy.root");   
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(datasetname,"results/datasets/QCD_SCStudy.root");           
  if(opts.getBoolVal("otherOnlyFit")) sprintf(datasetname,"results/datasets/other_SCStudy.root");       
  
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);
  
  // chiara, barrel only   // chiara, sistema per PF jets
  /*
    if (opts.getBoolVal("useCaloJet")) {
    data = (RooDataSet*)data->reduce("nCaloJets==0 && met/pt>0.3");
    if(opts.getBoolVal("barrel"))
    data = (RooDataSet*)data->reduce("abs(eta)<1.479 && hoe<0.04 && sqrt(covIeIe)<0.01 && (ecalRecHitSumEtConeDR03SC/pt)<0.07 && (hcalTowerSumEtConeDR03SC/pt)<0.1 && (trkSumPtSolidConeDR03SC/pt)<0.09");
    else if(opts.getBoolVal("endcapPlus"))
    data = (RooDataSet*)data->reduce("eta>1.479 && hoe<0.025 && sqrt(covIeIe)<0.03 && (ecalRecHitSumEtConeDR03SC/pt)<0.05 && (hcalTowerSumEtConeDR03SC/pt)<0.025 && (trkSumPtSolidConeDR03SC/pt)<0.04");
    else if(opts.getBoolVal("endcapMinus"))
    data = (RooDataSet*)data->reduce("eta<-1.479 && hoe<0.025 && sqrt(covIeIe)<0.03 && (ecalRecHitSumEtConeDR03SC/pt)<0.05 && (hcalTowerSumEtConeDR03SC/pt)<0.025 && (trkSumPtSolidConeDR03SC/pt)<0.04");
    }
  */

  if (opts.getBoolVal("useCaloJet")) {
    data = (RooDataSet*)data->reduce("nCaloJets==0 && met/pt>0.3");
    if(opts.getBoolVal("barrel"))
      data = (RooDataSet*)data->reduce("abs(eta)<1.479 && hoe<0.04 && sqrt(covIeIe)<0.01 && (ecalRecHitSumEtConeDR03SC/pt)<0.07 && (hcalTowerSumEtConeDR03SC/pt)<0.1 && (trkSumPtSolidConeDR03SC/pt)<0.09");
    else if(opts.getBoolVal("endcap"))
      data = (RooDataSet*)data->reduce("abs(eta)>1.479 && hoe<0.025 && sqrt(covIeIe)<0.03 && (ecalRecHitSumEtConeDR03SC/pt)<0.05 && (hcalTowerSumEtConeDR03SC/pt)<0.025 && (trkSumPtSolidConeDR03SC/pt)<0.04");
    else if(opts.getBoolVal("endcapPlus"))
      data = (RooDataSet*)data->reduce("eta>1.479 && hoe<0.025 && sqrt(covIeIe)<0.03 && (ecalRecHitSumEtConeDR03SC/pt)<0.05 && (hcalTowerSumEtConeDR03SC/pt)<0.025 && (trkSumPtSolidConeDR03SC/pt)<0.04");
    else if(opts.getBoolVal("endcapMinus"))
      data = (RooDataSet*)data->reduce("eta<-1.479 && hoe<0.025 && sqrt(covIeIe)<0.03 && (ecalRecHitSumEtConeDR03SC/pt)<0.05 && (hcalTowerSumEtConeDR03SC/pt)<0.025 && (trkSumPtSolidConeDR03SC/pt)<0.04");
  }

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
  if(opts.getBoolVal("AllFit")) sprintf(configfilename,"fitres/WInclusive/fitMinimum-data_withEffReco.config");
  if(opts.getBoolVal("WOnlyFit")) sprintf(configfilename,"shapes/WInclusive/config/fitMinimum-Wonly_withEff.config");
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(configfilename,"shapes/WInclusive/config/fitMinimum-QCDonly_withEff.config");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(configfilename,"shapes/WInclusive/config/fitMinimum-otheronly_withEff.config");
  theFit.initialize(configfilename);
  
  TCanvas *c = new TCanvas("c","fitResult");
  c.SetLogy();

  RooPlot* MassPlot = MakePlot("mt", &theFit, data, configfilename, nbins, usePoissonError);    
  
  MassPlot->SetAxisColor(1,"x");
  MassPlot->SetLabelColor(1, "X");
  MassPlot->SetLabelColor(1, "Y");
  MassPlot->SetXTitle("M_{T}[GeV/c^{2}]");
  
  MassPlot->SetYTitle("Events");
  MassPlot->Draw();

  // TLatex* t2 = new TLatex(0.6,0.85,"#splitline{CMS Preliminary 2010}{L_{int}=12.37 nb^{-1}, #sqrt{s}=7 TeV}");
  // t2->SetNDC();
  // t2->SetTextSize(0.06);
  // t2->Draw();
  
  char epsfilename[200];
  char epsfilename[200];
  char Cfilename[200];
  
  if(opts.getBoolVal("AllFit")) {
    sprintf(epsfilename,"fit-plots/eps/PfMtWCandle-data.eps");
    sprintf(Cfilename,"fit-plots/macro/PfMtWCandle-data.C");
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
  thePdf->plotOn(plot, RooFit::LineColor(kBlue) );

  
  if(opts.getBoolVal("AllFit")) {
    // === plot (dashed) the qcd component ===
    MLFit theFit2;
    
    // define the structure of the dataset
    RooRealVar *mt = new RooRealVar("mt","p.f. m_{T}^{W}",20.0,150.,"GeV");
    
    // other variables
    RooRealVar *weight = new RooRealVar("weight","weight",0,10000);
    
    theFit2.AddFlatFileColumn(mt);
    //    theFit2.AddFlatFileColumn(weight);   // chiara: da commentare per i dati
    
    // define a fit model
    theFit2.addModel("qcdFit", "qcd Fit");
    theFit2.addSpecies("qcdFit", "qcd", "QCD Bkg Component");
    theFit2.addPdfWName("qcdFit", "qcd",  "mt",  "Cruijff",  "qcd_PfMt");
    
    RooAbsPdf *myPdf2 = theFit2.buildModel("qcdFit");
    theFit2.initialize(configfilename);
    
    myPdf2->plotOn(plot, RooFit::Normalization(Nqcd/(Ns+Nother+Nqcd)),RooFit::LineColor(kRed),RooFit::LineStyle(kDashed));
  }
    
  return plot;
}

