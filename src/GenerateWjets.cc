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
  RooRealVar* mass = new RooRealVar("transvMass",  "Transverse W Mass [GeV/c^{2}]" , 30., 250.);

  MLFit theFit;

  theFit.AddFlatFileColumn(mass);
  
  // define a fit model
  theFit.addModel("myFit", "Ratio WtoENu");
  
  // define species
  theFit.addSpecies("myFit", "sig", "Signal Component");
  theFit.addSpecies("myFit", "zeeBkg", "Z to ee Bkg   Component");
  theFit.addSpecies("myFit", "ttbarBkg", "ttbar Bkg   Component");
  theFit.addSpecies("myFit", "qcdBkg", "QCD Bkg   Component");
  
  // mLL PDF
  theFit.addPdfWName("myFit", "sig" , "transvMass",  "Totti", "sig_Mass");
  theFit.addPdfWName("myFit", "zeeBkg" , "transvMass",  "Totti", "zeeBkg_Mass");
  theFit.addPdfWName("myFit", "ttbarBkg" , "transvMass",  "Totti", "ttbarBkg_Mass");
  theFit.addPdfWName("myFit", "qcdBkg" , "transvMass",  "Poly2", "qcdBkg_Mass");
  
  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  char configfilename[200];
  sprintf(configfilename, "toyconfig/toyW-%djet.config",njets);

  theFit.initialize(configfilename);
  MLGenerator theGenerator(theFit, "myFit");
  
  Int_t ngen =
    theFit.getRealPar("N_zeeBkg")->getVal()+
    theFit.getRealPar("N_ttbarBkg")->getVal()+
    theFit.getRealPar("N_qcdBkg")->getVal()+
    theFit.getRealPar("N_sig")->getVal();

  // Generate...
  RooArgSet genVars(theFit.getObsList(MLStrList("transvMass")));
  MLToyStudy theStudy(theGenerator, genVars, "E", "MTE", 0, theFit.getNoNormVars("myFit"));
  theStudy.addFit(*myPdf);

  theStudy.generateAndFit(nexp,ngen);
  
  char resultfilename[200];
  if (outfile==0) sprintf(resultfilename,"toys/output/resultsW-%djet.dat",njets);
  else sprintf(resultfilename, outfile, njets);
  theStudy._fitParData->write(resultfilename);

  TFile varfile("toys/variablesWjets.root","RECREATE");

  RooArgSet *variables = theStudy._fitParData->get();
  variables->setName("variables");
  variables->Write();
  varfile.Close();
}
