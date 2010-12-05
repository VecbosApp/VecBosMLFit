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
  RooRealVar* nbj = new RooRealVar("nBTagJets", "n_{b-tag jets}", 0.0, 3.0);
  RooRealVar *njets = new RooRealVar("nJets", "nJets",0.5, 20.5);

  theFit.AddFlatFileColumn(pfmt);
  theFit.AddFlatFileColumn(nbj);
  theFit.AddFlatFileColumn(njets);

  // define a fit model
  theFit.addModel("myFit", "Ratio WtoENu");

  // define species
  cout << "min = " << opts.getRealVal("njetmin") << " max = " << opts.getRealVal("njetmax") << endl;
  MLStrList speclist;
  for(int nj = opts.getRealVal("njetmin"); nj <=opts.getRealVal("njetmax"); nj++){
    //signal (assumption is W is all 0 bjets in the acceptance)
    char speclabel[50], specdesc[200];
    sprintf(speclabel,"W_%dj",nj);
    sprintf(specdesc,"Signal %dj Component",nj);
    theFit.addSpecies("myFit", speclabel, specdesc);
    speclist.Add(speclabel); // exclusive species list ot be transformed in inclusive.

    // top (ttbar + single t)
    sprintf(speclabel,"top0b_%dj",nj); // 0 bjet
    sprintf(specdesc,"Top background 0bjet %dj Component",nj);
    theFit.addSpecies("myFit", speclabel, specdesc);    

    sprintf(speclabel,"top1b_%dj",nj); // 1 bjet
    sprintf(specdesc,"Top background 1bjet %dj Component",nj);
    theFit.addSpecies("myFit", speclabel, specdesc);    

    sprintf(speclabel,"top2b_%dj",nj); // 2 bjet
    sprintf(specdesc,"Top background 2bjet %dj Component",nj);
    theFit.addSpecies("myFit", speclabel, specdesc);    

    // Other
    sprintf(speclabel,"other_%dj",nj);
    sprintf(specdesc,"Other background %dj Component",nj);
    theFit.addSpecies("myFit", speclabel, specdesc);

  }
 
  if(opts.getBoolVal("fitRatio"))  {
    theFit.fitInclusiveRatioPoly(speclist, "Wincl_",opts.getRealVal("njetmin"));
  }
  else { 
    theFit.fitInclusive( speclist, "Wincl_",opts.getRealVal("njetmin"));
  }

  char speclabel[50],pdfname[200],speclabelToCopy[200];
  for(int nj = opts.getRealVal("njetmin"); nj <=opts.getRealVal("njetmax"); nj++){
    
    // Mt PDF
    if(opts.getBoolVal("usePfMt")) {
      
      //signal
      sprintf(speclabel,"W_%dj",nj);
      sprintf(pdfname,"sig_PfMt%dj",nj);   
      theFit.addPdfWName("myFit", speclabel , "pfmt",  "DoubleCruijff", pdfname );

      //Other
      sprintf(speclabel,"other_%dj",nj);
      sprintf(pdfname,"other_PfMt%dj",nj);   
      theFit.addPdfWName("myFit",speclabel  , "pfmt",  "Cruijff",   pdfname);

      //top
      sprintf(speclabel,"top0b_%dj",nj);
      sprintf(pdfname,"top_PfMt%dj",nj);   
      theFit.addPdfWName("myFit",speclabel  , "pfmt",  "Cruijff",   pdfname);
      
      sprintf(speclabel,"top1b_%dj",nj);
      sprintf(speclabelToCopy,"top0b_%dj",nj);
      theFit.addPdfCopy("myFit", speclabel, "pfmt", speclabelToCopy);

      sprintf(speclabel,"top2b_%dj",nj);
      theFit.addPdfCopy("myFit", speclabel, "pfmt", speclabelToCopy);
    }

    // b-tagged jet multiplicity
    char effb0[50], effnob0[50], effb1[50], effnob1[50], effb2[50], effnob2[50];
    if(opts.getBoolVal("useBTag")) {

      // signal
      sprintf(speclabel,"W_%dj",nj);
      sprintf(pdfname,"b0_btag_%dj",nj);   // call W+0 bjets the signal (by definition)
      theFit.addPdfWName("myFit", speclabel , "nBTagJets",  "BtagPdf", pdfname );
      
      // Other
      // floated on data. No need of measuring on control sample
      const int nbins = 3;
      double limitarray[] = {0.0, 1.0, 2.0, 3.0 };

      TAxis* limits = new TAxis(nbins,limitarray) ;
      TList args;
      args.Add(limits);

      sprintf(speclabel,"other_%dj",nj);
      sprintf(pdfname,"other_btag_%dj",nj);
      theFit.addPdfWName("myFit", speclabel , "nBTagJets",  "BinnedPdf", args, pdfname );

      // top
      sprintf(speclabel,"top0b_%dj",nj);
      sprintf(pdfname,"b0_btag_%dj",nj);
      theFit.addPdfWName("myFit", speclabel , "nBTagJets",  "BtagPdf", pdfname );

      sprintf(speclabel,"top1b_%dj",nj);
      sprintf(pdfname,"b1_btag_%dj",nj);
      theFit.addPdfWName("myFit", speclabel , "nBTagJets",  "BtagPdf", pdfname );

      sprintf(speclabel,"top2b_%dj",nj);
      sprintf(pdfname,"b2_btag_%dj",nj);
      theFit.addPdfWName("myFit", speclabel , "nBTagJets",  "BtagPdf", pdfname );

      // tagging and mistag rate are jet properties: unique over jet multiplicities
      sprintf(effb0,"b0_btag_%dj_eb",nj);
      sprintf(effb1,"b1_btag_%dj_eb",nj);
      sprintf(effb2,"b2_btag_%dj_eb",nj);
      sprintf(effnob0,"b0_btag_%dj_enob",nj);
      sprintf(effnob1,"b1_btag_%dj_enob",nj);
      sprintf(effnob2,"b2_btag_%dj_enob",nj);

      theFit.bind(MLStrList(effb0,effb1,effb2),"btag_eb","btag_eb");
      theFit.bind(MLStrList(effnob0,effnob1,effnob2),"btag_enob","btag_enob");

    }
    
  
    // jet category
    sprintf(pdfname,"%dj",nj);

    sprintf(speclabel,"W_%dj",nj);
    theFit.addPdfWName("myFit",speclabel , "nJets", "ExclJet", pdfname);

    sprintf(speclabel,"other_%dj",nj);
    theFit.addPdfWName("myFit",speclabel , "nJets", "ExclJet", pdfname);

    sprintf(speclabel,"top0b_%dj",nj);
    theFit.addPdfWName("myFit",speclabel , "nJets", "ExclJet", pdfname);

    sprintf(speclabel,"top1b_%dj",nj);
    theFit.addPdfWName("myFit",speclabel , "nJets", "ExclJet", pdfname);

    sprintf(speclabel,"top2b_%dj",nj);
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
  sprintf(initconfigfile,"toyconfig/toyW-NewBJet-%s-thr%d.config",jetflavour,ithr);
  theFit.initialize(initconfigfile);

  MLGenerator theGenerator(theFit, "myFit");

  Int_t ngen = 
    theFit.getRealPar("N_Wincl_1j")->getVal()+
    theFit.getRealPar("N_other_1j")->getVal()+theFit.getRealPar("N_other_2j")->getVal()+theFit.getRealPar("N_other_3j")->getVal()+theFit.getRealPar("N_other_4j")->getVal()+
    theFit.getRealPar("N_top0b_1j")->getVal()+theFit.getRealPar("N_top0b_2j")->getVal()+theFit.getRealPar("N_top0b_3j")->getVal()+theFit.getRealPar("N_top0b_4j")->getVal()+
    theFit.getRealPar("N_top1b_1j")->getVal()+theFit.getRealPar("N_top1b_2j")->getVal()+theFit.getRealPar("N_top1b_3j")->getVal()+theFit.getRealPar("N_top1b_4j")->getVal()+
    theFit.getRealPar("N_top2b_1j")->getVal()+theFit.getRealPar("N_top2b_2j")->getVal()+theFit.getRealPar("N_top2b_3j")->getVal()+theFit.getRealPar("N_top2b_4j")->getVal();
  
  // Generate...
  RooArgSet genVars(theFit.getObsList(MLStrList("pfmt","nBTagJets","nJets")));
  MLToyStudy theStudy(theGenerator, genVars, "E", "MTE", 0, theFit.getNoNormVars("myFit"));
  theStudy.addFit(*myPdf);

  theStudy.generateAndFit(nexp,ngen);
  
  char resultfilename[200];
  if (outfile==0) sprintf(resultfilename,"toys/output/resultsW-%s.dat",jetflavour);
  else sprintf(resultfilename, outfile, njets);
  theStudy._fitParData->write(resultfilename);

  char variablesfilename[200];
  sprintf(variablesfilename,"toys/output/variablesW-%s.root",jetflavour);
  TFile varfile(variablesfilename,"RECREATE");

  RooArgSet *variables = theStudy._fitParData->get();
  variables->setName("variables");
  variables->Write();
  varfile.Close();

}

