int njets=-1;
Bool_t fitCaloJets=kTRUE;

void SetNjets(int n) { 
  njets=n;
}

void SetJetFlavour(const char *jetflavour) {
  if(strcmp(jetflavour,"calojets")==0) fitCaloJets = kTRUE;
  else fitCaloJets = kFALSE;
}

// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("fitCaloJets",       "Fit calojets, trackjets otherwise", fitCaloJets);
  opts.addBoolOption("usePfMt",           "Use W Transverse Mass",  kTRUE);
  opts.addBoolOption("useMHTphiJet",      "Use MHTphiJet",          kFALSE);
  opts.addBoolOption("worstCaseScenario", "Use the same Mt shape for W and ttbar", kFALSE);

  opts.addBoolOption("alternativeSigMT",  "apply uniform variation of PDF among two bounding shapes", kTRUE);
  opts.addBoolOption("smearQCDMT",        "apply Gaussian smearing to all QCD fixed parameters", kFALSE);
  opts.addBoolOption("smearOtherMT",      "apply Gaussian smearing to all other fixed parameters", kFALSE);

  return opts;
}

MLFit theFit;
MLFit *theFit2[10000];

void Generate(Int_t nexp = 1, UInt_t iseed = 65539, char* outfile= 0)
{

  if (njets==-1) { 
    cout << "njets not set. Exiting." << endl;
    return;
  }

  // Various fit options...
  MLOptions opts = GetDefaultOptions();
  
  const char* e0 = "\033[44;37m";
  const char* en="\033[0m";
  
  if(opts.getBoolVal("fitCaloJets")) 
    cout << e0 << "Toy Monte Carlo generation for W + " << njets << " calojets " << en << endl;
  else cout << e0 << "Toy Monte Carlo generation for W + " << njets << " PFjets " << en << endl;

  TDatime *now = new TDatime();
  int today = now->GetDate();
  int clock = now->GetTime();
  int seed = today+clock+iseed;
  // Set the random number seed...
  RooRandom::randomGenerator()->SetSeed(seed);

  // define the structure of the dataset
  RooRealVar* PfMt = new RooRealVar("pfmt",  "Transverse W Mass [GeV/c^{2}]" , 20., 150.);
  //  RooRealVar *sinMHTphiJet = new RooRealVar("sinMHTphiJet","sinMHTphiJet", -1.0, 1.0);
  //  RooRealVar* bvetoCat = new RooRealVar("BVETO", "BVETO",-1,1);


  theFit.AddFlatFileColumn(PfMt);
//   theFit.AddFlatFileColumn(sinMHTphiJet);
//   theFit.AddFlatFileColumn(bvetoCat);

  // define a fit model
  theFit.addModel("myFit", "Ratio WtoENu");
  
  // define species
  theFit.addSpecies("myFit", "sig",   "Accepted Signal Component");
  theFit.addSpecies("myFit", "qcd",   "Accepted QCD Component");
  theFit.addSpecies("myFit", "other", "Accepted Other Bkgs Component");

  // PfMt PDF
  if(opts.getBoolVal("usePfMt")) {
    if(njets==0) {
      theFit.addPdfWName("myFit", "sig",   "pfmt", "DoubleCruijff", "sig_PfMt");
      theFit.addPdfWName("myFit", "qcd",   "pfmt", "Cruijff", "qcd_PfMt");
      if(opts.getBoolVal("worstCaseScenario")) theFit.addPdfCopy("myFit", "other", "pfmt", "sig");
      else theFit.addPdfWName("myFit", "other", "pfmt", "Cruijff", "other_PfMt");

      theFit.bind(MLStrList("sig_PfMt_sigmaR1","sig_PfMt_sigmaR2"),"sig_PfMt_sigmaR","sig_PfMt_sigmaR");
      theFit.bind(MLStrList("sig_PfMt_alphaR1","sig_PfMt_alphaR2"),"sig_PfMt_alphaR","sig_PfMt_alphaR");
    } else {
      theFit.addPdfWName("myFit", "sig",   "pfmt", "DoubleCruijff",  "sig_PfMt");
      theFit.addPdfWName("myFit", "qcd",   "pfmt", "DoubleGaussian", "qcd_PfMt");
      if(opts.getBoolVal("worstCaseScenario")) theFit.addPdfCopy("myFit", "other", "pfmt", "sig");
      else theFit.addPdfWName("myFit", "other", "pfmt", "DoubleCruijff", "other_PfMt");
    }
  }

  // sinMHTphiJet PDF
  if(opts.getBoolVal("useMHTphiJet")) {
    theFit.addPdfWName("myFit", "sig" ,   "sinMHTphiJet",  "Cruijff",  "sig_sinMHTphiJet");
    theFit.addPdfWName("myFit", "qcd",    "sinMHTphiJet",  "Cruijff",  "qcd_sinMHTphiJet");
    theFit.addPdfWName("myFit", "other",  "sinMHTphiJet",  "Cruijff",  "other_sinMHTphiJet");

  }
  
  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "PFjet");

  char configfilename[200];
  sprintf(configfilename, "toyconfig/toyW-%d%s.config",njets,jetflavour);

  theFit.initialize(configfilename);
  //  MLWjetGenerator theGenerator(theFit, "myFit");
  MLGenerator theGenerator(theFit, "myFit");

  Int_t ngen =
    theFit.getRealPar("N_sig")->getVal()+
    theFit.getRealPar("N_qcd")->getVal()+
    theFit.getRealPar("N_other")->getVal();

  // Generate...
  RooArgSet genVars(theFit.getObsList(MLStrList("pfmt")));
  MLToyStudy theStudy(theGenerator, genVars, "E", "MTE", 0, theFit.getNoNormVars("myFit"));
  theStudy.addFit(*myPdf);
  
  if(opts.getBoolVal("alternativeSigMT") || opts.getBoolVal("smearQCDMT") || opts.getBoolVal("smearOtherMT")) {
    
    for(int ifit=0; ifit<1000; ifit++) {
      
      RooAbsPdf *myPdf2 = 0;
      
      char fitname[200];
      sprintf(fitname,"myFit%d",ifit);
      
      getSecondFit(ifit,njets);
      myPdf2 = theFit2[ifit]->buildModel(fitname);
      
      //initialize the second fit...
      theFit2[ifit]->initialize(configfilename);

      
      // smear group of correlated parameters for systematics
      if(opts.getBoolVal("alternativeSigMT")) {
        MLStrList sig_PfMt_params_1("sig_PfMt_mean1","sig_PfMt_sigmaL1","sig_PfMt_sigmaR",
                                    "sig_PfMt_alphaL1","sig_PfMt_alphaR");
        MLStrList sig_PfMt_params_2("sig_PfMt_mean2","sig_PfMt_sigmaL2","sig_PfMt_alphaL2","sig_PfMt_f1");
        MLStrList sig_PfMt_params(sig_PfMt_params_1);
        sig_PfMt_params.Add(sig_PfMt_params_2);
        theFit2[ifit]->uniformVaryConstantParameters(sig_PfMt_params);
      }
      
      if(opts.getBoolVal("smearQCDMT")) {
        MLStrList qcd_PfMt_params("qcd_PfMt_mean","qcd_PfMt_sigmaL","qcd_PfMt_sigmaR",
                                  "qcd_PfMt_alphaL","qcd_PfMt_alphaR");
        
        theFit2[ifit]->uniformVaryConstantParameters(qcd_PfMt_params);
      }
      
      if(opts.getBoolVal("smearOtherMT")) {
        MLStrList other_PfMt_params("other_PfMt_mean","other_PfMt_sigmaL","other_PfMt_sigmaR",
                                    "other_PfMt_alphaL","other_PfMt_alphaR");
        theFit2[ifit]->uniformVaryConstantParameters(other_PfMt_params);
      }
      
      if( myPdf2 !=0 ) theStudy.addFit(*myPdf2);

    }
  }

  theStudy.generateAndFit(nexp,ngen);
  
  char resultfilename[200];
  if (outfile==0) sprintf(resultfilename,"toys/output/resultsW-%d%s.dat",njets,jetflavour);
  else sprintf(resultfilename, outfile, njets);
  theStudy._fitParData->write(resultfilename);

  char variablesfilename[200];
  sprintf(variablesfilename,"toys/output/variablesW-%d%s.root",njets,jetflavour);
  TFile varfile(variablesfilename,"RECREATE");

  RooArgSet *variables = theStudy._fitParData->get();
  variables->setName("variables");
  variables->Write();
  varfile.Close();
}

void getSecondFit(int ifit, int njets) {

  MLFit *theIFit = new MLFit();
  char fitname[200];
  sprintf(fitname,"myFit%d",ifit);

  // Various fit options...
  MLOptions opts = GetDefaultOptions();
  
  // define the structure of the dataset
  RooRealVar* PfMt = new RooRealVar("pfmt",  "Transverse W Mass [GeV/c^{2}]" , 20., 150.);

  theIFit->AddFlatFileColumn(PfMt);

  // define a fit model
  theIFit->addModel(fitname, "Ratio WtoENu");
  
  // define species
  theIFit->addSpecies(fitname, "sig",   "Accepted Signal Component");
  theIFit->addSpecies(fitname, "qcd",   "Accepted QCD Component");
  theIFit->addSpecies(fitname, "other", "Accepted Other Bkgs Component");

  // PfMt PDF
  if(opts.getBoolVal("usePfMt")) {
    if(njets==0) {
      theIFit->addPdfWName(fitname, "sig",   "pfmt", "DoubleCruijff", "sig_PfMt");
      theIFit->addPdfWName(fitname, "qcd",   "pfmt", "Cruijff", "qcd_PfMt");
      if(opts.getBoolVal("worstCaseScenario")) theIFit->addPdfCopy(fitname, "other", "pfmt", "sig");
      else theIFit->addPdfWName(fitname, "other", "pfmt", "Cruijff", "other_PfMt");

      theIFit->bind(MLStrList("sig_PfMt_sigmaR1","sig_PfMt_sigmaR2"),"sig_PfMt_sigmaR","sig_PfMt_sigmaR");
      theIFit->bind(MLStrList("sig_PfMt_alphaR1","sig_PfMt_alphaR2"),"sig_PfMt_alphaR","sig_PfMt_alphaR");
    } else {
      theIFit->addPdfWName(fitname, "sig",   "pfmt", "DoubleCruijff",  "sig_PfMt");
      theIFit->addPdfWName(fitname, "qcd",   "pfmt", "DoubleGaussian", "qcd_PfMt");
      if(opts.getBoolVal("worstCaseScenario")) theIFit->addPdfCopy(fitname, "other", "pfmt", "sig");
      else theIFit->addPdfWName(fitname, "other", "pfmt", "DoubleCruijff", "other_PfMt");
    }
  }

  theIFit->Print();
  theFit2[ifit] = theIFit;

}
