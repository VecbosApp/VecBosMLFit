int njets=0;

void SetNjets(int n) { 
  njets=n;
}

void Generate(Int_t nexp = 1, UInt_t iseed = 65539, char* outfile= 0)
{

  if (njets==0) { 
    cout << "njets not set. Exiting." << endl;
    return;
  }
  
  TDatime *now = new TDatime();
  int today = now->GetDate();
  int clock = now->GetTime();
  int seed = today+clock+iseed;
  // Set the random number seed...
  RooRandom::randomGenerator()->SetSeed(seed);

  // define the structure of the dataset
  RooRealVar* mass = new RooRealVar("invMass",  "Mass [GeV/c^{2}]" , 60., 110.);
  RooRealVar* sinMHTphiMET = new RooRealVar("sinMHTphiMET", "sin #phi_{MHT-MET}",-0.85,0.85);

  MLFit theFit;

  theFit.AddFlatFileColumn(mass);
  theFit.AddFlatFileColumn(sinMHTphiMET);

  // define a fit model
  theFit.addModel("myFit", "Ratio ZtoEE");
  
  // define species
  theFit.addSpecies("myFit", "sig", "Signal Component");
  theFit.addSpecies("myFit", "ttbarbkg", "Bkg   Component");
  
  // mLL PDF
  theFit.addPdfWName("myFit", "sig" , "invMass",  "Cruijff",  "sig_Mass");
  theFit.addPdfWName("myFit", "ttbarbkg" , "invMass",  "Poly2",  "ttbarbkg_Mass");
  
  // shape variable
  theFit.addPdfWName("myFit", "sig" , "sinMHTphiMET",  "DoubleGaussian", "sig_sinMHTphiMET");
  theFit.addPdfWName("myFit", "ttbarbkg" , "sinMHTphiMET",  "Poly2", "ttbarbkg_sinMHTphiMET");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  char configfilename[200];
  sprintf(configfilename, "toyconfig/toyZ-%djet.config",njets);

  theFit.initialize(configfilename);
  MLGenerator theGenerator(theFit, "myFit");
  
  Int_t ngen =
    theFit.getRealPar("N_ttbarbkg")->getVal()+
    theFit.getRealPar("N_sig")->getVal();

  // Generate...
  RooArgSet genVars(theFit.getObsList(MLStrList("invMass","sinMHTphiMET")));
  MLToyStudy theStudy(theGenerator, genVars, "E", "MTE", 0, theFit.getNoNormVars("myFit"));
  theStudy.addFit(*myPdf);

  theStudy.generateAndFit(nexp,ngen);
  
  char resultfilename[200];
  if (outfile==0) sprintf(resultfilename,"toys/output/resultsZ-%djet.dat",njets);
  else sprintf(resultfilename, outfile, njets);
  theStudy._fitParData->write(resultfilename);

  TFile varfile("toys/variablesZjets.root","RECREATE");

  RooArgSet *variables = theStudy._fitParData->get();
  variables->setName("variables");
  variables->Write();
  varfile.Close();
}
