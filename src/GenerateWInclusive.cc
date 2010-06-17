int njets=0;
Bool_t fitCaloJets=kTRUE;

void SetNjets(int n) { 
  njets=n;
}

void SetJetFlavour(const char *jetflavour) {
  if(strcmp(jetflavour,"calojet")==0) fitCaloJets = kTRUE;
  else fitCaloJets = kFALSE;
}

// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("useMt",           "Use W Transverse Mass",  kFALSE);
  opts.addBoolOption("useTcMt",         "Use t.c. W Transverse Mass",  kFALSE);
  opts.addBoolOption("usePfMt",         "Use p.f. W Transverse Mass",  kTRUE);

  return opts;
}

void Generate(Int_t nexp = 1, UInt_t iseed = 65539, char* outfile= 0)
{

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  TDatime *now = new TDatime();
  int today = now->GetDate();
  int clock = now->GetTime();
  int seed = today+clock+iseed;
  // Set the random number seed...
  RooRandom::randomGenerator()->SetSeed(seed);

  // define the structure of the dataset
  // kinematic variables
  RooRealVar *met = new RooRealVar("met","E_{T}^{miss}",0.0,500.,"GeV");
  RooRealVar *tcmet = new RooRealVar("tcmet","t.c. E_{T}^{miss}",0.0,500.,"GeV");
  RooRealVar *pfmet = new RooRealVar("pfmet","p.f. E_{T}^{miss}",0.0,500.,"GeV");
  RooRealVar *mt = new RooRealVar("mt","m_{T}^{W}",0.0,500.,"GeV");
  RooRealVar *tcmt = new RooRealVar("tcmt","t.c. m_{T}^{W}",0.0,500.,"GeV");
  RooRealVar *pfmt = new RooRealVar("pfmt","p.f. m_{T}^{W}",20.0,150.,"GeV");

  MLFit theFit;

  theFit.AddFlatFileColumn(met);
  theFit.AddFlatFileColumn(tcmet);
  theFit.AddFlatFileColumn(pfmet);
  theFit.AddFlatFileColumn(mt);
  theFit.AddFlatFileColumn(tcmt);
  theFit.AddFlatFileColumn(pfmt);

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

    //    theFit.bind(MLStrList("sig_PfMt_mean1","sig_PfMt_mean2"),"sig_PfMt_mean","sig_PfMt_mean");
    theFit.bind(MLStrList("sig_PfMt_sigmaR1","sig_PfMt_sigmaR2"),"sig_PfMt_sigmaR","sig_PfMt_sigmaR");
    theFit.bind(MLStrList("sig_PfMt_alphaR1","sig_PfMt_alphaR2"),"sig_PfMt_alphaR","sig_PfMt_alphaR");
  }

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  char configfilename[200];
  sprintf(configfilename, "toyconfig/WInclusive/toyW.config");

  theFit.initialize(configfilename);
  MLGenerator theGenerator(theFit, "myFit");
  
  Int_t ngen =
    theFit.getRealPar("N_sig")->getVal()+
    theFit.getRealPar("N_qcd")->getVal()+
    theFit.getRealPar("N_other")->getVal();

  // Generate...
  RooArgSet genVars(theFit.getObsList(MLStrList("pfmt")));
  MLToyStudy theStudy(theGenerator, genVars, "E", "MTE", 0, theFit.getNoNormVars("myFit"));
  theStudy.addFit(*myPdf);

  theStudy.generateAndFit(nexp,ngen);
  
  char resultfilename[200];
  if (outfile==0) sprintf(resultfilename,"toys/output/resultsW.dat");
  else sprintf(resultfilename, outfile);
  theStudy._fitParData->write(resultfilename);

  char variablesfilename[200];
  sprintf(variablesfilename,"toys/variablesW.root");
  TFile varfile(variablesfilename,"RECREATE");

  RooArgSet *variables = theStudy._fitParData->get();
  variables->setName("variables");
  variables->Write();
  varfile.Close();
}
