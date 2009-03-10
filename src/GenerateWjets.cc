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
  MLWjetGenerator theGenerator(theFit, "myFit");
  
  Int_t ngen =
    theFit.getRealPar("N_sig")->getVal()+
    theFit.getRealPar("N_ttbar")->getVal()+
    theFit.getRealPar("N_other")->getVal();

  // Generate...
  RooArgSet genVars(theFit.getObsList(MLStrList("Mt","sinMHTphiJet")));
  MLToyStudy theStudy(theGenerator, genVars, "E", "MTE", 0, theFit.getNoNormVars("myFit"));
  theStudy.addFit(*myPdf);

  theStudy.generateAndFit(nexp,ngen);
  
  char resultfilename[200];
  if (outfile==0) sprintf(resultfilename,"toys/output/resultsW-%d%s.dat",njets,jetflavour);
  else sprintf(resultfilename, outfile, njets);
  theStudy._fitParData->write(resultfilename);

  char variablesfilename[200];
  sprintf(variablesfilename,"toys/variablesW-%d%s.root",njets,jetflavour);
  TFile varfile(variablesfilename,"RECREATE");

  RooArgSet *variables = theStudy._fitParData->get();
  variables->setName("variables");
  variables->Write();
  varfile.Close();
}
