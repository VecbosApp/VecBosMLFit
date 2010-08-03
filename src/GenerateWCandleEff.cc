// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("usePfMt",           "Use W Transverse Mass",  kTRUE);
  opts.addBoolOption("recoEff",           "Do the toys for electron reco efficiency",  kTRUE);

  return opts;
}

void Generate(Int_t nexp = 1, UInt_t iseed = 65539, char* outfile= 0)
{

  // Various fit options...
  MLOptions opts = GetDefaultOptions();
  
  const char* e0 = "\033[44;37m";
  const char* en="\033[0m";
  
  TDatime *now = new TDatime();
  int today = now->GetDate();
  int clock = now->GetTime();
  int seed = today+clock+iseed;
  // Set the random number seed...
  RooRandom::randomGenerator()->SetSeed(seed);

  // define the structure of the dataset
  RooRealVar* PfMt = new RooRealVar("pfmt",  "Transverse W Mass [GeV/c^{2}]" , 20., 150.);
  RooRealVar* isSel = new RooRealVar("isSel", "isSel",-1,1);

  MLFit theFit;

  theFit.AddFlatFileColumn(PfMt);
  theFit.AddFlatFileColumn(isSel);

  // define a fit model
  theFit.addModel("myFit", "Ratio WtoENu");
  
  // define species
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

  // PfMt PDF
  if(opts.getBoolVal("usePfMt")) {
    theFit.addPdfWName("myFit", "sig_a",   "pfmt", "DoubleCruijff", "sig_PfMt");
    theFit.addPdfWName("myFit", "qcd_a",   "pfmt", "Cruijff", "qcd_PfMt");
    theFit.addPdfWName("myFit", "other_a", "pfmt", "Cruijff", "other_PfMt");
    
    theFit.bind(MLStrList("sig_PfMt_sigmaR1","sig_PfMt_sigmaR2"),"sig_PfMt_sigmaR","sig_PfMt_sigmaR");
    theFit.bind(MLStrList("sig_PfMt_alphaR1","sig_PfMt_alphaR2"),"sig_PfMt_alphaR","sig_PfMt_alphaR");

    theFit.addPdfCopy("myFit", "sig_r",   "pfmt", "sig_a");
    theFit.addPdfCopy("myFit", "qcd_r",   "pfmt", "qcd_a");
    theFit.addPdfCopy("myFit", "other_r", "pfmt", "other_a");
  }

  theFit.addPdfWName("myFit", "sig_a" ,   "isSel",  "Poly2",  "veto_acc");
  theFit.addPdfCopy("myFit",  "qcd_a",    "isSel",  "sig_a");
  theFit.addPdfCopy("myFit",  "other_a",  "isSel",  "sig_a");
  
  theFit.addPdfWName("myFit", "sig_r" ,   "isSel",  "Poly2",  "veto_rej");
  theFit.addPdfCopy("myFit",  "qcd_r",    "isSel",  "sig_r");
  theFit.addPdfCopy("myFit",  "other_r",  "isSel",  "sig_r");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  char configfilename[200];
  if(opts.getBoolVal("recoEff")) sprintf(configfilename, "toyconfig/WInclusive/toyWCandleWithEffSC.config");
  else sprintf(configfilename, "toyconfig/WInclusive/toyWCandleWithEff.config");

  theFit.initialize(configfilename);
  MLEffGenerator theGenerator(theFit, "myFit");

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
  if (outfile==0) sprintf(resultfilename,"toys/output/resultsWCandleEff.dat");
  else sprintf(resultfilename, outfile);
  theStudy._fitParData->write(resultfilename);

  char variablesfilename[200];
  sprintf(variablesfilename,"toys/output/variablesWCandleEff.root");
  TFile varfile(variablesfilename,"RECREATE");

  RooArgSet *variables = theStudy._fitParData->get();
  variables->setName("variables");
  variables->Write();
  varfile.Close();
}
