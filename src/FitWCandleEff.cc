// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("weightedDataset", "use event weight instead of 1",     kFALSE);
  opts.addBoolOption("usePfMt",         "Use p.f. W Transverse Mass",  kTRUE);
  opts.addBoolOption("AllFit",          "Fit all species",        kTRUE);
  opts.addBoolOption("WOnlyFit",        "Fit W species only",     kFALSE);
  opts.addBoolOption("QCDOnlyFit",      "Fit QCD species only",   kFALSE);
  opts.addBoolOption("otherOnlyFit",    "Fit other species only", kFALSE);

  // efficiency
  opts.addBoolOption("idWP80",           "Fit for N and Identification eff", kTRUE);
  opts.addBoolOption("isoOnlyEff",       "Fit for N and Isolation eff", kFALSE);
  opts.addBoolOption("idAndIsoEff",      "Fit for N and ID+ISO eff", kFALSE);

  return opts;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

MLFit theFit;

void myFit(const char* flagId="isIdWP80", const char* flagIso="") {

  MLFit theFit;

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // define the structure of the dataset
  // kinematic variables
  RooRealVar *pfmt = new RooRealVar("pfmt","p.f. m_{T}^{W}",20.0,150.,"GeV");

  RooRealVar *isIdWP70 = new RooRealVar("isIdWP70","isIdWP70",-1,1);
  RooRealVar *isIdWP80 = new RooRealVar("isIdWP80","isIdWP80",-1,1);
  RooRealVar *isIdWP80modEE = new RooRealVar("isIdWP80modEE","isIdWP80modEE",-1,1);
  RooRealVar *isIdWP85 = new RooRealVar("isIdWP85","isIdWP85",-1,1);
  RooRealVar *isIdWP95 = new RooRealVar("isIdWP95","isIdWP95",-1,1);

  RooRealVar *isIsoWP70 = new RooRealVar("isIsoWP70","isIsoWP70",-1,1);
  RooRealVar *isIsoWP80 = new RooRealVar("isIsoWP80","isIsoWP80",-1,1);
  RooRealVar *isIsoWP80modEE = new RooRealVar("isIsoWP80modEE","isIsoWP80modEE",-1,1);
  RooRealVar *isIsoWP85 = new RooRealVar("isIsoWP85","isIsoWP85",-1,1);
  RooRealVar *isIsoWP95 = new RooRealVar("isIsoWP95","isIsoWP95",-1,1);

  RooRealVar *eta = new RooRealVar("eta","electron #eta",-2.5,2.5);

  theFit.AddFlatFileColumn(pfmt);
  theFit.AddFlatFileColumn(isIdWP70);
  theFit.AddFlatFileColumn(isIdWP80);
  theFit.AddFlatFileColumn(isIdWP80modEE);
  theFit.AddFlatFileColumn(isIdWP85);
  theFit.AddFlatFileColumn(isIdWP95);
  theFit.AddFlatFileColumn(isIsoWP70);
  theFit.AddFlatFileColumn(isIsoWP80);
  theFit.AddFlatFileColumn(isIsoWP80modEE);
  theFit.AddFlatFileColumn(isIsoWP85);
  theFit.AddFlatFileColumn(isIsoWP95);
  theFit.AddFlatFileColumn(eta);

  // define a fit model
  theFit.addModel("myFit", "Inclusive WtoENu");
  
  // define species
  theFit.addSpecies("myFit", "sig_a",   "Accepted Signal Component");
  theFit.addSpecies("myFit", "qcd_a",   "Accepted QCD Component");
  theFit.addSpecies("myFit", "other_a", "Accepted Other Bkgs Component");

  theFit.addSpecies("myFit", "sig_r",   "Rejected Signal Component");
  theFit.addSpecies("myFit", "qcd_r",   "Rejected QCD Component");
  theFit.addSpecies("myFit", "other_r", "Rejected Other Bkgs Component");

  theFit.fitWithEff("sig_a", "sig_r", "sig");
  theFit.fitWithEff("qcd_a", "qcd_r", "qcd");
  theFit.fitWithEff("other_a", "other_r", "other");

  // P.F. Mt PDF
  if(opts.getBoolVal("usePfMt")) {
    theFit.addPdfWName("myFit", "sig_a",   "pfmt", "DoubleCruijff", "sig_PfMt");
    theFit.addPdfWName("myFit", "qcd_a",   "pfmt", "Cruijff", "qcd_PfMt");
    theFit.addPdfWName("myFit", "other_a", "pfmt", "Cruijff", "other_PfMt");

    //    theFit.bind(MLStrList("sig_PfMt_mean1","sig_PfMt_mean2"),"sig_PfMt_mean","sig_PfMt_mean");
    theFit.bind(MLStrList("sig_PfMt_sigmaR1","sig_PfMt_sigmaR2"),"sig_PfMt_sigmaR","sig_PfMt_sigmaR");
    theFit.bind(MLStrList("sig_PfMt_alphaR1","sig_PfMt_alphaR2"),"sig_PfMt_alphaR","sig_PfMt_alphaR");

    theFit.addPdfCopy("myFit", "sig_r",   "pfmt", "sig_a");

//     theFit.addPdfWName("myFit", "qcd_r",   "pfmt", "Cruijff", "qcd_r_PfMt");
//     theFit.bind(MLStrList("qcd_r_PfMt_mean","qcd_r_PfMt_mean"),"qcd_PfMt_mean","qcd_PfMt_mean");
//     theFit.bind(MLStrList("qcd_r_PfMt_alphaL","qcd_r_PfMt_alphaL"),"qcd_PfMt_alphaL","qcd_PfMt_alphaL");
//     theFit.bind(MLStrList("qcd_r_PfMt_sigmaL","qcd_r_PfMt_sigmaL"),"qcd_PfMt_sigmaL","qcd_PfMt_sigmaL");

    theFit.addPdfCopy("myFit", "qcd_r",   "pfmt", "qcd_a");

    theFit.addPdfCopy("myFit", "other_r", "pfmt", "other_a");

  }

  TString FlagId(flagId);
  // veto category
  if(FlagId == TString("isIdWP70")) {

    cout << ">>>>>>>>>>>>>>>>>>>>>   WP70 >>>>>>>>>>>>>>>>>>" << endl;

    theFit.addPdfWName("myFit", "sig_a" ,   "isIdWP70",  "Poly2",  "veto_acc");
    theFit.addPdfCopy("myFit",  "qcd_a",    "isIdWP70",  "sig_a");
    theFit.addPdfCopy("myFit",  "other_a",  "isIdWP70",  "sig_a");
    
    theFit.addPdfWName("myFit", "sig_r" ,   "isIdWP70",  "Poly2",  "veto_rej");
    theFit.addPdfCopy("myFit",  "qcd_r",    "isIdWP70",  "sig_r");
    theFit.addPdfCopy("myFit",  "other_r",  "isIdWP70",  "sig_r");
  } else if(FlagId == TString("isIdWP80modEE")) {

    cout << ">>>>>>>>>>>>>>>>>>>>>   WP80 mod EE >>>>>>>>>>>>>>>>>>" << endl;

    theFit.addPdfWName("myFit", "sig_a" ,   "isIdWP80modEE",  "Poly2",  "veto_acc");
    theFit.addPdfCopy("myFit",  "qcd_a",    "isIdWP80modEE",  "sig_a");
    theFit.addPdfCopy("myFit",  "other_a",  "isIdWP80modEE",  "sig_a");

    theFit.addPdfWName("myFit", "sig_r" ,   "isIdWP80modEE",  "Poly2",  "veto_rej");
    theFit.addPdfCopy("myFit",  "qcd_r",    "isIdWP80modEE",  "sig_r");
    theFit.addPdfCopy("myFit",  "other_r",  "isIdWP80modEE",  "sig_r");
  } else if(FlagId == TString("isIdWP80")) {

    cout << ">>>>>>>>>>>>>>>>>>>>>   WP80 >>>>>>>>>>>>>>>>>>" << endl;

    theFit.addPdfWName("myFit", "sig_a" ,   "isIdWP80",  "Poly2",  "veto_acc");
    theFit.addPdfCopy("myFit",  "qcd_a",    "isIdWP80",  "sig_a");
    theFit.addPdfCopy("myFit",  "other_a",  "isIdWP80",  "sig_a");
    
    theFit.addPdfWName("myFit", "sig_r" ,   "isIdWP80",  "Poly2",  "veto_rej");
    theFit.addPdfCopy("myFit",  "qcd_r",    "isIdWP80",  "sig_r");
    theFit.addPdfCopy("myFit",  "other_r",  "isIdWP80",  "sig_r");
  } else if(FlagId == TString("isIdWP85")) {


    cout << ">>>>>>>>>>>>>>>>>>>>>   WP85 >>>>>>>>>>>>>>>>>>" << endl;

    theFit.addPdfWName("myFit", "sig_a" ,   "isIdWP85",  "Poly2",  "veto_acc");
    theFit.addPdfCopy("myFit",  "qcd_a",    "isIdWP85",  "sig_a");
    theFit.addPdfCopy("myFit",  "other_a",  "isIdWP85",  "sig_a");
    
    theFit.addPdfWName("myFit", "sig_r" ,   "isIdWP85",  "Poly2",  "veto_rej");
    theFit.addPdfCopy("myFit",  "qcd_r",    "isIdWP85",  "sig_r");
    theFit.addPdfCopy("myFit",  "other_r",  "isIdWP85",  "sig_r");
  } else if(FlagId == TString("isIdWP95")) {

    cout << ">>>>>>>>>>>>>>>>>>>>>   WP95 >>>>>>>>>>>>>>>>>>" << endl;

    theFit.addPdfWName("myFit", "sig_a" ,   "isIdWP95",  "Poly2",  "veto_acc");
    theFit.addPdfCopy("myFit",  "qcd_a",    "isIdWP95",  "sig_a");
    theFit.addPdfCopy("myFit",  "other_a",  "isIdWP95",  "sig_a");
    
    theFit.addPdfWName("myFit", "sig_r" ,   "isIdWP95",  "Poly2",  "veto_rej");
    theFit.addPdfCopy("myFit",  "qcd_r",    "isIdWP95",  "sig_r");
    theFit.addPdfCopy("myFit",  "other_r",  "isIdWP95",  "sig_r");
  } 

  TString FlagIso(flagIso);
  if(FlagIso == TString("isIsoWP70")) {

    cout << ">>>>>>>>>>>>>>>>>>>>>   Iso WP70 >>>>>>>>>>>>>>>>>>" << endl;

    theFit.addPdfWName("myFit", "sig_a" ,   "isIsoWP70",  "Poly2",  "veto_acc");
    theFit.addPdfCopy("myFit",  "qcd_a",    "isIsoWP70",  "sig_a");
    theFit.addPdfCopy("myFit",  "other_a",  "isIsoWP70",  "sig_a");
    
    theFit.addPdfWName("myFit", "sig_r" ,   "isIsoWP70",  "Poly2",  "veto_rej");
    theFit.addPdfCopy("myFit",  "qcd_r",    "isIsoWP70",  "sig_r");
    theFit.addPdfCopy("myFit",  "other_r",  "isIsoWP70",  "sig_r");
  } else if(FlagIso == TString("isIsoWP80")) {

    cout << ">>>>>>>>>>>>>>>>>>>>>   Iso WP80 >>>>>>>>>>>>>>>>>>" << endl;

    theFit.addPdfWName("myFit", "sig_a" ,   "isIsoWP80",  "Poly2",  "veto_acc");
    theFit.addPdfCopy("myFit",  "qcd_a",    "isIsoWP80",  "sig_a");
    theFit.addPdfCopy("myFit",  "other_a",  "isIsoWP80",  "sig_a");
    
    theFit.addPdfWName("myFit", "sig_r" ,   "isIsoWP80",  "Poly2",  "veto_rej");
    theFit.addPdfCopy("myFit",  "qcd_r",    "isIsoWP80",  "sig_r");
    theFit.addPdfCopy("myFit",  "other_r",  "isIsoWP80",  "sig_r");
  } else if(FlagIso == TString("isIsoWP80modEE")) {

    cout << ">>>>>>>>>>>>>>>>>>>>>   Iso WP80modEE >>>>>>>>>>>>>>>>>>" << endl;

    theFit.addPdfWName("myFit", "sig_a" ,   "isIsoWP80modEE",  "Poly2",  "veto_acc");
    theFit.addPdfCopy("myFit",  "qcd_a",    "isIsoWP80modEE",  "sig_a");
    theFit.addPdfCopy("myFit",  "other_a",  "isIsoWP80modEE",  "sig_a");
    
    theFit.addPdfWName("myFit", "sig_r" ,   "isIsoWP80modEE",  "Poly2",  "veto_rej");
    theFit.addPdfCopy("myFit",  "qcd_r",    "isIsoWP80modEE",  "sig_r");
    theFit.addPdfCopy("myFit",  "other_r",  "isIsoWP80modEE",  "sig_r");
  } else if(FlagIso == TString("isIsoWP85")) {

    cout << ">>>>>>>>>>>>>>>>>>>>>   Iso WP85 >>>>>>>>>>>>>>>>>>" << endl;

    theFit.addPdfWName("myFit", "sig_a" ,   "isIsoWP85",  "Poly2",  "veto_acc");
    theFit.addPdfCopy("myFit",  "qcd_a",    "isIsoWP85",  "sig_a");
    theFit.addPdfCopy("myFit",  "other_a",  "isIsoWP85",  "sig_a");
    
    theFit.addPdfWName("myFit", "sig_r" ,   "isIsoWP85",  "Poly2",  "veto_rej");
    theFit.addPdfCopy("myFit",  "qcd_r",    "isIsoWP85",  "sig_r");
    theFit.addPdfCopy("myFit",  "other_r",  "isIsoWP85",  "sig_r");
  } else if(FlagIso == TString("isIsoWP95")) {

    cout << ">>>>>>>>>>>>>>>>>>>>>   Iso WP95 >>>>>>>>>>>>>>>>>>" << endl;

    theFit.addPdfWName("myFit", "sig_a" ,   "isIsoWP95",  "Poly2",  "veto_acc");
    theFit.addPdfCopy("myFit",  "qcd_a",    "isIsoWP95",  "sig_a");
    theFit.addPdfCopy("myFit",  "other_a",  "isIsoWP95",  "sig_a");
    
    theFit.addPdfWName("myFit", "sig_r" ,   "isIsoWP95",  "Poly2",  "veto_rej");
    theFit.addPdfCopy("myFit",  "qcd_r",    "isIsoWP95",  "sig_r");
    theFit.addPdfCopy("myFit",  "other_r",  "isIsoWP95",  "sig_r");
  } 

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fit a sample of Z events
void FitWElectrons(const char *cut="nJets==0 && pfmet/pt>0.3",const char* flagId="isIdWP80", const char* flagIso="") {
  
  myFit(flagId,flagIso);

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // Load the data
  char datasetname[200];
  char treename[100];
  if(opts.getBoolVal("AllFit")) {
//     sprintf(datasetname,"toys/gensample.root");
//     sprintf(treename,"theData");
    sprintf(datasetname,"results_data/datasets/dataset_eg_Wenu_WithFlags.root");
    sprintf(treename,"T1");
  } else sprintf(treename,"T1");
  if(opts.getBoolVal("WOnlyFit")) sprintf(datasetname,"results/datasets_unweighted_x5/WJetsMADGRAPH_out-Wenu.root");
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(datasetname,"results/datasets_unweighted_x5/QCD_out-Wenu.root");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(datasetname,"results/datasets_unweighted_x5/other_out-Wenu.root");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);
  data = (RooDataSet*)data->reduce(cut);
  

  //  if(opts.getBoolVal("WOnlyFit")) data = (RooDataSet*)data->reduce("promptDecay==1");

  // use event weights (the ones in the dataset are for 1/pb)
  if(opts.getBoolVal("weightedDataset")) data->setWeightVar("weight");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");

  // Initialize the fit...
  if(opts.getBoolVal("AllFit")) theFit.initialize("fitconfig/WInclusive/fitWCandleWithEff.config");
  if(opts.getBoolVal("WOnlyFit")) theFit.initialize("shapes/WInclusive/config/WFit-WonlyWithEff.config");
  if(opts.getBoolVal("QCDOnlyFit")) theFit.initialize("shapes/WInclusive/config/WFit-QCDonlyWithEff.config");
  if(opts.getBoolVal("otherOnlyFit")) theFit.initialize("shapes/WInclusive/config/WFit-otheronlyWithEff.config");

  // Print Fit configuration 
  myPdf->getParameters(data)->selectByAttrib("Constant",kTRUE)->Print("V");  
  myPdf->getParameters(data)->selectByAttrib("Constant",kFALSE)->Print("V");
  
  RooFitResult *fitres =  myPdf->fitTo(*data,RooFit::ConditionalObservables(theFit.getNoNormVars("myFit")),RooFit::FitOptions("MHTER"));
  //  RooFitResult *fitres =  myPdf->fitTo(*data,RooFit::ConditionalObservables(theFit.getNoNormVars("myFit")),RooFit::Extended(kTRUE),RooFit::Hesse(kTRUE),RooFit::Minos(kTRUE));
  fitres->Print("V");
  
  // write the config file corresponding to the fit minimum
  char configfilename[200];
  if(opts.getBoolVal("AllFit")) sprintf(configfilename, "fitres/WInclusive/fitMinimumWCandleWithEff-data.config");
  if(opts.getBoolVal("WOnlyFit")) sprintf(configfilename, "shapes/WInclusive/config/fitMinimumWCandleWithEff-Wonly.config");
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(configfilename, "shapes/WInclusive/config/fitMinimumWCandleWithEff-QCDonly.config");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(configfilename, "shapes/WInclusive/config/fitMinimumWCandleWithEff-otheronly.config");
  theFit.writeConfigFile(configfilename);

  // save the fit result in ROOT 
  char rootfilename[200];

  TString cutPrefix(cut);
  cout << "cut string = " << cutPrefix.Data() << endl;
  cutPrefix.ReplaceAll("==","EQ");
  cutPrefix.ReplaceAll("&&","AND");
  cutPrefix.ReplaceAll("/","OVER");
  cutPrefix.ReplaceAll(">=","GEQ");
  cutPrefix.ReplaceAll(">","GT");
  cutPrefix.ReplaceAll("<=","LEQ");
  cutPrefix.ReplaceAll("<","LT");
  cutPrefix.ReplaceAll("(","OPPAR");
  cutPrefix.ReplaceAll(")","CLPAR");
  cutPrefix.ReplaceAll(" ","_");
  
  TString flagIdPrefix(flagId);
  TString flagIsoPrefix(flagIso);

  TString rootfilenameAllFit(TString("fitres/WInclusive/fitMinimumWCandleWithEff")+cutPrefix+flagIdPrefix+flagIsoPrefix+".root");

  cout << "Writing results in: " << rootfilenameAllFit.Data() << endl;

  if(opts.getBoolVal("AllFit")) sprintf(rootfilename, "%s",rootfilenameAllFit.Data());
  if(opts.getBoolVal("WOnlyFit")) sprintf(rootfilename,"shapes/WInclusive/root/fitResWCandleWithEff-Wonly.root");
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(rootfilename,"shapes/WInclusive/root/fitResWCandleWithEff-QCDonly.root");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(rootfilename,"shapes/WInclusive/root/fitResWCandleWithEff-otheronly.root");

  TFile *file = new TFile(rootfilename,"recreate");
  fitres->Write();
  file->Close();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotWElectrons(int nbins, const char* cut="nJets==0 && pfmet/pt>0.3") {

  myFit();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // Load the data
  char datasetname[200];
  char treename[100];
  if(opts.getBoolVal("AllFit")) { 
    //    sprintf(datasetname,"toys/gensample.root");
    //    sprintf(treename,"theData");
    //    sprintf(datasetname,"results/datasets_unweighted_x2/mockData_out-Wenu.root");
    sprintf(datasetname,"results_data/datasets/dataset_eg_Wenu_WithFlags.root");
    sprintf(treename,"T1");
  } else sprintf(treename,"T1");
  if(opts.getBoolVal("WOnlyFit")) sprintf(datasetname,"results/datasets_unweighted_x5/WJetsMADGRAPH_out-Wenu.root");
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(datasetname,"results/datasets_unweighted_x5/QCD_out-Wenu.root");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(datasetname,"results/datasets_unweighted_x5/other_out-Wenu.root");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);
  data = (RooDataSet*)data->reduce(cut);

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
  if(opts.getBoolVal("AllFit")) sprintf(configfilename,"fitres/WInclusive/fitMinimumWCandleWithEff-data.config");
  if(opts.getBoolVal("WOnlyFit")) sprintf(configfilename, "shapes/WInclusive/config/fitMinimumWCandleWithEff-Wonly.config");
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(configfilename, "shapes/WInclusive/config/fitMinimumWCandleWithEff-QCDonly.config");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(configfilename, "shapes/WInclusive/config/fitMinimumWCandleWithEff-otheronly.config");
  theFit.initialize(configfilename);

  if(opts.getBoolVal("usePfMt")) {
    TCanvas *c = new TCanvas("c","fitResult");
    RooPlot* MassPlot = MakePlot("pfmt", &theFit, data, configfilename, nbins, usePoissonError);    
    
    MassPlot->SetAxisColor(1,"x");
    MassPlot->SetLabelColor(1, "X");
    MassPlot->SetLabelColor(1, "Y");
    MassPlot->SetXTitle("M_{T}[GeV/c^{2}]");

    MassPlot->SetYTitle("Events");
    MassPlot->Draw();

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
    RooRealVar *pfmt = new RooRealVar("pfmt","p.f. m_{T}^{W}",20.0,150.,"GeV");

    // other variables
    RooRealVar *weight = new RooRealVar("weight","weight",0,10000);
    
    theFit2.AddFlatFileColumn(pfmt);
    //    theFit2.AddFlatFileColumn(weight);

    // define a fit model
    theFit2.addModel("qcdFit", "qcd Fit");
    theFit2.addSpecies("qcdFit", "qcd", "QCD Bkg Component");
    if(opts.getBoolVal("usePfMt")) theFit2.addPdfWName("qcdFit", "qcd",  "pfmt",  "Cruijff",  "qcd_PfMt");

    RooAbsPdf *myPdf2 = theFit2.buildModel("qcdFit");
    theFit2.initialize(configfilename);

    myPdf2->plotOn(plot, RooFit::Normalization(Nqcd/(Ns+Nother+Nqcd)),RooFit::LineColor(kRed),RooFit::LineStyle(kDashed));

//     // === plot (red) the signal component ===
//     MLFit theFit3;

//     theFit3.AddFlatFileColumn(met);
//     theFit3.AddFlatFileColumn(tcmet);
//     theFit3.AddFlatFileColumn(pfmet);
//     theFit3.AddFlatFileColumn(mt);
//     theFit3.AddFlatFileColumn(tcmt);
//     theFit3.AddFlatFileColumn(pfmt);
//     theFit3.AddFlatFileColumn(weight);

//     // define a fit model
//     theFit3.addModel("sigFit", "signal Fit");
//     theFit3.addSpecies("sigFit", "sig", "Signal Component");
//     if(opts.getBoolVal("usePfMt")) {
//       theFit3.addPdfWName("sigFit", "sig",  "pfmt",  "DoubleCruijff",  "sig_PfMt");
//       theFit.bind(MLStrList("sig_PfMt_sigmaR1","sig_PfMt_sigmaR2"),"sig_PfMt_sigmaR","sig_PfMt_sigmaR");
//       theFit.bind(MLStrList("sig_PfMt_alphaR1","sig_PfMt_alphaR2"),"sig_PfMt_alphaR","sig_PfMt_alphaR");
//     }

//     RooAbsPdf *myPdf3 = theFit3.buildModel("sigFit");
//     theFit3.initialize(configfilename);

//     myPdf3->plotOn(plot, RooFit::Normalization(Ns/(Ns+Nother+Nqcd)),RooFit::LineColor(kBlack), RooFit::LineStyle(3));
  
  }

  return plot;
}

