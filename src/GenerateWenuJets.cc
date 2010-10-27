// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("highJetThreshold", "Fit W+jets with ET>30 GeV", kTRUE);
  opts.addBoolOption("fitRatio",         "FitRatio directly",kFALSE);
  opts.addBoolOption("usePfMt",         "Use W Transverse Mass",  kTRUE);
  opts.addBoolOption("useBTag",         "Use B Tag",  kTRUE);
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
  RooRealVar* btag = new RooRealVar("combinedSecondaryVertexBJetTags", "EVT b-tag", 0., 1.);
  RooRealVar *njets = new RooRealVar("nJets", "nJets",0.5, 20.5);

  theFit.AddFlatFileColumn(pfmt);
  theFit.AddFlatFileColumn(btag);
  theFit.AddFlatFileColumn(njets);

  // define a fit model
  theFit.addModel("myFit", "Ratio WtoENu");

  // define species
  MLStrList speclistLF, speclistHF;
  for(int nj = opts.getRealVal("njetmin"); nj <=opts.getRealVal("njetmax"); nj++){
    //signal LF
    char speclabel[50],specdesc[200];
    sprintf(speclabel,"W_LF%dj",nj);
    sprintf(specdesc,"Signal LF %dj Component",nj);
    theFit.addSpecies("myFit", speclabel, specdesc);
    speclistLF.Add(speclabel); // exclusive species list ot be transformed in inclusive.

    //signal HF
    char speclabel[50],specdesc[200];
    sprintf(speclabel,"W_HF%dj",nj);
    sprintf(specdesc,"Signal HF %dj Component",nj);
    theFit.addSpecies("myFit", speclabel, specdesc);
    speclistHF.Add(speclabel); // exclusive species list ot be transformed in inclusive.

    // QCD LF
    sprintf(speclabel,"qcd_LF%dj",nj);
    sprintf(specdesc,"QCD LF background %dj Component",nj);
    theFit.addSpecies("myFit", speclabel, specdesc);

    // QCD HF
    sprintf(speclabel,"qcd_HF%dj",nj);
    sprintf(specdesc,"QCD HF background %dj Component",nj);
    theFit.addSpecies("myFit", speclabel, specdesc);

    //other
    sprintf(speclabel,"other%dj",nj);
    sprintf(specdesc,"Other background %dj Component",nj);
    theFit.addSpecies("myFit", speclabel, specdesc);    

  }
 
  if(opts.getBoolVal("fitRatio")) {
    theFit.fitInclusiveRatioPoly(speclistLF, "WinclLF",1);
    theFit.fitInclusiveRatioPoly(speclistHF, "WinclHF",1);
  }
  else {
    theFit.fitInclusive( speclistLF, "WinclLF",1);
    theFit.fitInclusive( speclistHF, "WinclHF",1);
  }

  for(int nj = opts.getRealVal("njetmin"); nj <=opts.getRealVal("njetmax"); nj++){

    char speclabel[50],pdfname[200],specnameToCopy[200];

    // Mt PDF
    if(opts.getBoolVal("usePfMt")) {
      
      //signal LF
      sprintf(speclabel,"W_LF%dj",nj);
      sprintf(pdfname,"sigLF_PfMt%dj",nj);
      theFit.addPdfWName("myFit", speclabel , "pfmt",  "DoubleCruijff", pdfname );

      //signal HF
      sprintf(speclabel,"W_HF%dj",nj);
      sprintf(pdfname,"sigHF_PfMt%dj",nj);
      sprintf(specnameToCopy,"W_LF%dj",nj);
      theFit.addPdfCopy("myFit", speclabel , "pfmt",  specnameToCopy ); // same as W+LF

      //QCD LF
      sprintf(speclabel,"qcd_LF%dj",nj);
      sprintf(pdfname,"qcdLF_PfMt%dj",nj);   
      theFit.addPdfWName("myFit",speclabel  , "pfmt",  "Cruijff",   pdfname);

      //QCD HF
      sprintf(speclabel,"qcd_HF%dj",nj);
      sprintf(pdfname,"qcdHF_PfMt%dj",nj);   
      sprintf(specnameToCopy,"qcd_LF%dj",nj);
      theFit.addPdfCopy("myFit", speclabel , "pfmt",  specnameToCopy ); // same as QCD+LF

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

    // EVT b-tag 
    if(opts.getBoolVal("useBTag")) {

      // used only in the 1/2-jet bin
      const int nbins = 10;
      double limitarray[] = {0.0, 0.1, 0.2, 0.3, 0.6, 0.7, 0.8, 0.85, 0.9, 0.95, 1.0 };
      double limitarrayOther[] = {0.0, 0.15, 0.25, 0.45, 0.80, 0.84, 0.86, 0.90, 0.93, 0.96, 1.0001 };

      TAxis* limits = new TAxis(nbins,limitarray) ;
      TList args;
      args.Add(limits);

      TAxis* limitsOther = new TAxis(nbins,limitarrayOther) ;
      TList argsOther;
      argsOther.Add(limitsOther);

      //other
      sprintf(speclabel,"other%dj",nj);
      sprintf(pdfname,"other_btag%dj",nj);   
      theFit.addPdfWName("myFit", speclabel , "combinedSecondaryVertexBJetTags",  "BinnedPdf", argsOther, pdfname );
      
      // signal LF
      sprintf(speclabel,"W_LF%dj",nj);
      sprintf(pdfname,"sigLF_btag%dj",nj);   
      theFit.addPdfWName("myFit", speclabel , "combinedSecondaryVertexBJetTags",  "BinnedPdf", args, pdfname );

      // signal HF
      sprintf(speclabel,"W_HF%dj",nj);
      sprintf(pdfname,"sigHF_btag%dj",nj);   
      sprintf(specnameToCopy,"other%dj",nj); 
      theFit.addPdfCopy("myFit", speclabel, "combinedSecondaryVertexBJetTags", specnameToCopy );

      //QCD LF
      sprintf(speclabel,"qcd_LF%dj",nj);
      sprintf(pdfname,"qcdLF_btag%dj",nj);   
      theFit.addPdfWName("myFit", speclabel , "combinedSecondaryVertexBJetTags",  "BinnedPdf", args, pdfname );

      // QCD HF
      sprintf(speclabel,"qcd_HF%dj",nj);
      sprintf(pdfname,"qcdHF_btag%dj",nj);   
      sprintf(specnameToCopy,"other%dj",nj); 
      theFit.addPdfCopy("myFit", speclabel, "combinedSecondaryVertexBJetTags", specnameToCopy ); // same as other

    }

    // jet category
    sprintf(pdfname,"%dj",nj);

    sprintf(speclabel,"W_LF%dj",nj);
    theFit.addPdfWName("myFit",speclabel , "nJets", "ExclJet", pdfname);

    sprintf(speclabel,"W_HF%dj",nj);
    theFit.addPdfWName("myFit",speclabel , "nJets", "ExclJet", pdfname);

    sprintf(speclabel,"qcd_LF%dj",nj);
    theFit.addPdfWName("myFit",speclabel , "nJets", "ExclJet", pdfname);

    sprintf(speclabel,"qcd_HF%dj",nj);
    theFit.addPdfWName("myFit",speclabel , "nJets", "ExclJet", pdfname);

    sprintf(speclabel,"other%dj",nj);
    theFit.addPdfWName("myFit",speclabel , "nJets", "ExclJet", pdfname);

  }


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
    theFit.getRealPar("N_WinclLF1j")->getVal()+
    theFit.getRealPar("N_WinclHF1j")->getVal()+
    theFit.getRealPar("N_qcd_LF1j")->getVal()+theFit.getRealPar("N_qcd_HF1j")->getVal()+
    theFit.getRealPar("N_qcd_LF2j")->getVal()+theFit.getRealPar("N_qcd_HF2j")->getVal()+
    theFit.getRealPar("N_qcd_LF3j")->getVal()+theFit.getRealPar("N_qcd_HF3j")->getVal()+
    theFit.getRealPar("N_qcd_LF4j")->getVal()+theFit.getRealPar("N_qcd_HF4j")->getVal()+
    theFit.getRealPar("N_other1j")->getVal()+
    theFit.getRealPar("N_other2j")->getVal()+
    theFit.getRealPar("N_other3j")->getVal()+
    theFit.getRealPar("N_other4j")->getVal();

  // Generate...
  RooArgSet genVars(theFit.getObsList(MLStrList("pfmt","combinedSecondaryVertexBJetTags","nJets")));
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

