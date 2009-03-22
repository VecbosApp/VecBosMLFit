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
  opts.addBoolOption("fitCaloJets",       "Fit calojets, trackjets otherwise", fitCaloJets);
  opts.addBoolOption("useMt",             "Use W Transverse Mass",  kTRUE);
  opts.addBoolOption("useMHTphiJet",      "Use MHTphiJet",          kTRUE);
  opts.addBoolOption("worstCaseScenario", "Use the same Mt shape for W and ttbar", kFALSE);
  opts.addBoolOption("generateWith2DPdf", "Generate with 2D Mt-sin(MHTphiJet) PDF", kTRUE);

  return opts;
}

void Generate(Int_t nexp = 1, UInt_t iseed = 65539, char* outfile= 0)
{

  if (njets==0) { 
    cout << "njets not set. Exiting." << endl;
    return;
  }

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // Initialize the fit...
  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "trackjet");
  
  const char* e0 = "\033[44;37m";
  const char* en="\033[0m";
  
  if(opts.getBoolVal("fitCaloJets")) 
    cout << e0 << "Toy Monte Carlo generation for W + " << njets << " calojets " << en << endl;
  else cout << e0 << "Toy Monte Carlo generation for W + " << njets << " trackjets " << en << endl;

  TDatime *now = new TDatime();
  int today = now->GetDate();
  int clock = now->GetTime();
  int seed = today+clock+iseed;
  // Set the random number seed...
  RooRandom::randomGenerator()->SetSeed(seed);

  // define the structure of the dataset
  RooRealVar* Mt = new RooRealVar("Mt",  "Transverse W Mass [GeV/c^{2}]" , 30., 250.);
  RooRealVar *sinMHTphiJet = new RooRealVar("sinMHTphiJet","sinMHTphiJet", -0.85, 0.85);
  RooRealVar* bvetoCat = new RooRealVar("BVETO", "BVETO",-1,1);

  
  // define generation model, in case it is different from fit model
  MLFit theGenFit;

  theGenFit.AddFlatFileColumn(Mt);
  theGenFit.AddFlatFileColumn(sinMHTphiJet);
  theGenFit.AddFlatFileColumn(bvetoCat);

  // define a fit model
  theGenFit.addModel("myGenFit", "Ratio WtoENu");
  
  // define species accepted by b veto
  theGenFit.addSpecies("myGenFit", "sig_a",    "Accepted Signal Component");
  theGenFit.addSpecies("myGenFit", "ttbar_a",  "Accepted ttbar Component");
  theGenFit.addSpecies("myGenFit", "other_a",  "Accepted Other Bkgs Component");

  // define species rejected by b veto
  theGenFit.addSpecies("myGenFit", "sig_r",    "Rejected Signal Component");
  theGenFit.addSpecies("myGenFit", "ttbar_r",  "Rejected ttbar Component");
  theGenFit.addSpecies("myGenFit", "other_r",  "Rejected Other Bkgs Component");

  theGenFit.fitWithEff("sig_a", "sig_r", "sig");
  theGenFit.fitWithEff("ttbar_a", "ttbar_r", "ttbar");
  theGenFit.fitWithEff("other_a", "other_r", "other");

  // Mt - sinMHTphiJet PDF
  if(opts.getBoolVal("useMt") && opts.getBoolVal("useMHTphiJet")) {

    MLStrList obs("Mt","sinMHTphiJet");

    char dataset[200];
    sprintf(dataset,"datasets/wenu_21X-%d%s.root",njets,jetflavour);
    MLStrList WjArgs(dataset, "WjetsMADGRAPH");
    MLStrList ttjArgs(dataset, "ttjetsMADGRAPH");
    MLStrList otherArgs(dataset, "other");

    theGenFit.add2DPdfWName("myGenFit", "sig_a", obs, "Hist", WjArgs, "sig_a_MtSinMHTphiJet");
    
    theGenFit.add2DPdfWName("myGenFit", "ttbar_a", obs, "Hist", ttjArgs, "ttbar_a_MtSinMHTphiJet");
    
    theGenFit.add2DPdfWName("myGenFit", "other_a", obs, "Hist", otherArgs, "sig_a_MtSinMHTphiJet");
    
    theGenFit.add2DPdfWName("myGenFit", "sig_r", obs, "Hist", WjArgs, "sig_r_MtSinMHTphiJet");
    
    theGenFit.add2DPdfWName("myGenFit", "ttbar_r", obs, "Hist", ttjArgs, "ttbar_r_MtSinMHTphiJet");

    theGenFit.add2DPdfWName("myGenFit", "other_r", obs, "Hist", otherArgs, "sig_r_MtSinMHTphiJet");

  }

  // b veto category
  theGenFit.addPdfWName("myGenFit", "sig_a" ,   "BVETO",  "Poly2",  "bveto_acc");
  theGenFit.addPdfCopy("myGenFit",  "ttbar_a",  "BVETO",  "sig_a");
  theGenFit.addPdfCopy("myGenFit",  "other_a",  "BVETO",  "sig_a");

  theGenFit.addPdfWName("myGenFit", "sig_r" ,   "BVETO",  "Poly2",  "bveto_rej");
  theGenFit.addPdfCopy("myGenFit",  "ttbar_r",  "BVETO",  "sig_r");
  theGenFit.addPdfCopy("myGenFit",  "other_r",  "BVETO",  "sig_r");

  // build the fit likelihood
  RooAbsPdf *myGenPdf = theGenFit.buildModel("myGenFit");

  char configfilename[200];
  sprintf(configfilename, "toyconfig/toyW-%d%s.config",njets,jetflavour);

  theGenFit.initialize(configfilename);


  // define the fit model
  MLFit theFit;

  theFit.AddFlatFileColumn(Mt);
  theFit.AddFlatFileColumn(sinMHTphiJet);
  theFit.AddFlatFileColumn(bvetoCat);

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
    if(opts.getBoolVal("worstCaseScenario")) theFit.addPdfCopy("myFit", "ttbar_a", "Mt", "sig_a");
    else theFit.addPdfWName("myFit", "ttbar_a", "Mt", "CrystalCruijff", "ttbar_Mt");
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
  theFit.addPdfWName("myFit", "sig_a" ,   "BVETO",  "Poly2",  "bveto_acc");
  theFit.addPdfCopy("myFit",  "ttbar_a",  "BVETO",  "sig_a");
  theFit.addPdfCopy("myFit",  "other_a",  "BVETO",  "sig_a");

  theFit.addPdfWName("myFit", "sig_r" ,   "BVETO",  "Poly2",  "bveto_rej");
  theFit.addPdfCopy("myFit",  "ttbar_r",  "BVETO",  "sig_r");
  theFit.addPdfCopy("myFit",  "other_r",  "BVETO",  "sig_r");


  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "trackjet");

  char configfilename[200];
  sprintf(configfilename, "toyconfig/toyW-%d%s.config",njets,jetflavour);

  theFit.initialize(configfilename);


  MLWjetGenerator theGenerator(theGenFit, "myGenFit");

  Int_t ngen =
    theFit.getRealPar("N_sig")->getVal()+
    theFit.getRealPar("N_ttbar")->getVal()+
    theFit.getRealPar("N_other")->getVal();

  MLToyStudy *theStudy = 0;
  // Generate...
  if(opts.getBoolVal("generateWith2DPdf")) {
    RooArgSet genVars(theGenFit.getObsList(MLStrList("Mt","sinMHTphiJet")));
    theStudy = new MLToyStudy(theGenerator, genVars, "E", "MTE", 0, theGenFit.getNoNormVars("myGenFit"));
    theStudy->addFit(*myPdf);
    theStudy->generateAndFit(nexp,ngen);
  } else {
    RooArgSet genVars(theFit.getObsList(MLStrList("Mt","sinMHTphiJet")));
    theStudy = new MLToyStudy(theGenerator, genVars, "E", "MTE", 0, theFit.getNoNormVars("myGenFit"));
    theStudy->addFit(*myPdf);
    theStudy->generateAndFit(nexp,ngen);
  }

  char resultfilename[200];
  if (outfile==0) sprintf(resultfilename,"toys/output/resultsW-%d%s.dat",njets,jetflavour);
  else sprintf(resultfilename, outfile, njets);
  theStudy->_fitParData->write(resultfilename);

  char variablesfilename[200];
  sprintf(variablesfilename,"toys/variablesW-%d%s.root",njets,jetflavour);
  TFile varfile(variablesfilename,"RECREATE");

  RooArgSet *variables = theStudy->_fitParData->get();
  variables->setName("variables");
  variables->Write();
  varfile.Close();

}
