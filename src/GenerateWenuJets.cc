// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("highJetThreshold", "Fit W+jets with ET>30 GeV", kTRUE);
  opts.addBoolOption("fitRatio",         "FitRatio directly",kFALSE);
  opts.addBoolOption("usePfMt",         "Use W Transverse Mass",  kTRUE);
  opts.addRealOption("njetmin",         "smallest jet number to consider", 1);
  opts.addRealOption("njetmax",         "largest jet number to consider", 4);

  return opts;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Generate(Int_t nexp = 1, UInt_t iseed = 65539, char* outfile= 0) {

  TDatime *now = new TDatime();
  int today = now->GetDate();
  int clock = now->GetTime();
  int seed = today+clock+iseed;
  // Set the random number seed...
  RooRandom::randomGenerator()->SetSeed(seed);

  MLFit theFit;

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // define the structure of the dataset
  RooRealVar* pfmt = new RooRealVar("pfmt",  "M_{T}" , 20., 150., "GeV/c^{2}");
  RooRealVar *njets = new RooRealVar("nJets", "nJets",0.5, 20.5);

  theFit.AddFlatFileColumn(pfmt);
  theFit.AddFlatFileColumn(njets);

  // define a fit model
  theFit.addModel("myFit", "Ratio WtoENu");

  // define species
  MLStrList speclist;
  for(int nj = opts.getRealVal("njetmin"); nj <=opts.getRealVal("njetmax"); nj++){
    //signal
    char speclabel[50],specdesc[200];
    sprintf(speclabel,"W%dj",nj);
    sprintf(specdesc,"Signal %dj Component",nj);
    theFit.addSpecies("myFit", speclabel, specdesc);
    speclist.Add(speclabel); // exclusive species list ot be transformed in inclusive.

    //QCD
    sprintf(speclabel,"qcd%dj",nj);
    sprintf(specdesc,"QCD background %dj Component",nj);
    theFit.addSpecies("myFit", speclabel, specdesc);
    //other
    sprintf(speclabel,"other%dj",nj);
    sprintf(specdesc,"Other background %dj Component",nj);
    theFit.addSpecies("myFit", speclabel, specdesc);    

  }
 
  if(opts.getBoolVal("fitRatio"))  theFit.fitInclusiveRatioPoly(speclist, "Wincl",3);
  else  theFit.fitInclusive( speclist, "Wincl",1);

  for(int nj = opts.getRealVal("njetmin"); nj <=opts.getRealVal("njetmax"); nj++){

    char speclabel[50],pdfname[200];

    // Mt PDF
    if(opts.getBoolVal("usePfMt")) {
      
      //signal
      sprintf(speclabel,"W%dj",nj);
      sprintf(pdfname,"sig_PfMt%dj",nj);   
      theFit.addPdfWName("myFit", speclabel , "pfmt",  "DoubleCruijff", pdfname );

      //QCD
      sprintf(speclabel,"qcd%dj",nj);
      sprintf(pdfname,"qcd_PfMt%dj",nj);   
      theFit.addPdfWName("myFit",speclabel  , "pfmt",  "Cruijff",   pdfname);

      //other
      sprintf(speclabel,"other%dj",nj);
      sprintf(pdfname,"other_PfMt%dj",nj);   
      if(nj<3) {// 1,2 j ==> ttbar veto

        // used only in the 1/2-jet bin
        const int nbins = 10;
        double limitarray[] = {20.,28.,36.,44.,52.,60.,70.,80.,90.,120.,150.};

        TAxis* limits = new TAxis(nbins,limitarray) ;
        TList args;
        args.Add(limits);
        theFit.addPdfWName("myFit",speclabel  , "pfmt",  "BinnedPdf", args,  pdfname);
      } else theFit.addPdfWName("myFit",speclabel  , "pfmt",  "Cruijff",   pdfname);
    }

    // jet category
    sprintf(pdfname,"%dj",nj);

    sprintf(speclabel,"W%dj",nj);
    theFit.addPdfWName("myFit",speclabel , "nJets", "ExclJet", pdfname);

    sprintf(speclabel,"qcd%dj",nj);
    theFit.addPdfWName("myFit",speclabel , "nJets", "ExclJet", pdfname);

    sprintf(speclabel,"other%dj",nj);
    theFit.addPdfWName("myFit",speclabel , "nJets", "ExclJet", pdfname);

  }

  cout << "stocase6" << endl;


  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");

  // Initialize the fit...
  char jetflavour[200];
  sprintf(jetflavour, "PFjet");
  
  int ithr;
  if(opts.getBoolVal("highJetThreshold")) ithr=0;
  else ithr=1;

  char initconfigfile[200];
  sprintf(initconfigfile,"toyconfig/toyW-New-%s-thr%d.config",jetflavour,ithr);
  theFit.initialize(initconfigfile);

  MLGenerator theGenerator(theFit, "myFit");


  Int_t ngen =
    theFit.getRealPar("N_Wincl1j")->getVal()+
    theFit.getRealPar("N_qcd1j")->getVal()+
    theFit.getRealPar("N_qcd2j")->getVal()+
    theFit.getRealPar("N_qcd3j")->getVal()+
    theFit.getRealPar("N_qcd4j")->getVal()+
    theFit.getRealPar("N_other1j")->getVal()+
    theFit.getRealPar("N_other2j")->getVal()+
    theFit.getRealPar("N_other3j")->getVal()+
    theFit.getRealPar("N_other4j")->getVal();

  // Generate...
  RooArgSet genVars(theFit.getObsList(MLStrList("pfmt","nJets")));
  MLToyStudy theStudy(theGenerator, genVars, "E", "MTE", 0, theFit.getNoNormVars("myFit"));
  theStudy.addFit(*myPdf);

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

