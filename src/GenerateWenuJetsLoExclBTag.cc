// #include "TDatime.h"
// #include "TAxis.h"
// #include "TFile.h"

// #include "RooRandom.h"
// #include "RooRealVar.h"
// #include "RooCategory.h"
// #include "RooArgSet.h"
// #include "RooAbsPdf.h"

// #include "MLOptions.hh"
// #include "MLFit.hh"
// #include "MLStrList.hh"
// #include "MLToyStudy.hh"
// #include "MLGenerator.hh"
// #include "MLPdfRecipe.hh"

// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("highJetThreshold", "Fit W+jets with ET>30 GeV", kFALSE);
  opts.addBoolOption("fitRatio",         "FitRatio directly",kFALSE);
  opts.addBoolOption("usePfMt",          "Use W Transverse Mass",  kTRUE);
  opts.addBoolOption("useBTag",          "Use B Tag",  kTRUE);
  opts.addRealOption("njetmin",          "smallest jet number to consider", 1);
  opts.addRealOption("njetmax",          "largest jet number to consider", 4);
  opts.addBoolOption("MCT",              "do an embedded toy", kFALSE);
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
  RooRealVar *njets = new RooRealVar("nExclPFJetsLo", "nExclPFJetsLo",0.5, 20.5);
  RooCategory *HiJetsClass = new RooCategory("HiJetsClass", "HiJetsClass");

  HiJetsClass->defineType("HiJets0",   0);
  HiJetsClass->defineType("HiJets1",   1);
  HiJetsClass->defineType("HiJets2",   2);
  HiJetsClass->defineType("HiJets3",   3);
  HiJetsClass->defineType("HiJets4",   4);

  theFit.AddFlatFileColumn(pfmt);
  theFit.AddFlatFileColumn(nbj);
  theFit.AddFlatFileColumn(njets);
  theFit.AddFlatFileColumn(HiJetsClass);

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
    theFit.fitInclusiveRatio(speclist, "Wincl",opts.getRealVal("njetmin"));
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
    char njetsstr[50], nbstr[50];
    char njetsstrb0[50], njetsstrb1[50], njetsstrb2[50], nbstrb0[50], nbstrb1[50], nbstrb2[50];
    if(opts.getBoolVal("useBTag")) {

      // signal
      sprintf(speclabel,"W_%dj",nj);
      sprintf(pdfname,"b0_btag_%dj",nj);   // call W+0 bjets the signal (by definition)
      //      theFit.addPdfWName("myFit", speclabel , "nBTagJets",  "BtagPdf", pdfname );
      theFit.addSimPdf("myFit",speclabel,"nBTagJets","HiJetsClass",pdfname);
      for(int njHi=0; njHi<=opts.getRealVal("njetmax"); njHi++) {
        char catLabel[20];
        sprintf(catLabel,"HiJets%d",njHi);
        char fullSimPdfName[100];
        sprintf(fullSimPdfName,"%s_HiJets%d",pdfname,njHi);
        theFit.addPdfToSimPdf("myFit",speclabel,"nBTagJets",MLStrList("nBTagJets"),
                              catLabel,"BtagPdf",TList(),fullSimPdfName);
      }

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
      theFit.addSimPdf("myFit",speclabel,"nBTagJets","HiJetsClass",pdfname);
      for(int njHi=0; njHi<=opts.getRealVal("njetmax"); njHi++) {
        char catLabel[20];
        sprintf(catLabel,"HiJets%d",njHi);
        char fullSimPdfName[100];
        sprintf(fullSimPdfName,"%s_HiJets%d",pdfname,njHi);
        theFit.addPdfToSimPdf("myFit",speclabel,"nBTagJets",MLStrList("nBTagJets"),
                              catLabel,"BtagPdf",TList(),fullSimPdfName);
      }


      sprintf(speclabel,"top1b_%dj",nj);
      sprintf(pdfname,"b1_btag_%dj",nj);
      theFit.addSimPdf("myFit",speclabel,"nBTagJets","HiJetsClass",pdfname);
      for(int njHi=0; njHi<=opts.getRealVal("njetmax"); njHi++) {
        char catLabel[20];
        sprintf(catLabel,"HiJets%d",njHi);
        char fullSimPdfName[100];
        sprintf(fullSimPdfName,"%s_HiJets%d",pdfname,njHi);
        theFit.addPdfToSimPdf("myFit",speclabel,"nBTagJets",MLStrList("nBTagJets"),
                              catLabel,"BtagPdf",TList(),fullSimPdfName);
      }

      sprintf(speclabel,"top2b_%dj",nj);
      sprintf(pdfname,"b2_btag_%dj",nj);
      theFit.addSimPdf("myFit",speclabel,"nBTagJets","HiJetsClass",pdfname);
      for(int njHi=0; njHi<=opts.getRealVal("njetmax"); njHi++) {
        char catLabel[20];
        sprintf(catLabel,"HiJets%d",njHi);
        char fullSimPdfName[100];
        sprintf(fullSimPdfName,"%s_HiJets%d",pdfname,njHi);
        theFit.addPdfToSimPdf("myFit",speclabel,"nBTagJets",MLStrList("nBTagJets"),
                              catLabel,"BtagPdf",TList(),fullSimPdfName);
      }

      sprintf(njetsstr,"b0_btag_%dj_njets",nj);
      sprintf(nbstr,"b0_btag_%dj_nb",nj);

      // tagging and mistag rate are jet properties: unique over jet multiplicities
      for(int njHi=0; njHi<=opts.getRealVal("njetmax"); njHi++) {
        sprintf(effb0,"b0_btag_%dj_HiJets%d_eb",nj,njHi);
        sprintf(effb1,"b1_btag_%dj_HiJets%d_eb",nj,njHi);
        sprintf(effb2,"b2_btag_%dj_HiJets%d_eb",nj,njHi);
        sprintf(effnob0,"b0_btag_%dj_HiJets%d_enob",nj,njHi);
        sprintf(effnob1,"b1_btag_%dj_HiJets%d_enob",nj,njHi);
        sprintf(effnob2,"b2_btag_%dj_HiJets%d_enob",nj,njHi);
        
        theFit.bind(MLStrList(effb0,effb1,effb2),"btag_eb","btag_eb");
        theFit.bind(MLStrList(effnob0,effnob1,effnob2),"btag_enob","btag_enob");

        // bind also the nb and nj multiplicities
        sprintf(njetsstrb0,"b0_btag_%dj_HiJets%d_njets",nj,njHi);
        sprintf(njetsstrb1,"b1_btag_%dj_HiJets%d_njets",nj,njHi);
        sprintf(njetsstrb2,"b2_btag_%dj_HiJets%d_njets",nj,njHi);
        sprintf(nbstrb0,"b0_btag_%dj_HiJets%d_nb",nj,njHi);
        sprintf(nbstrb1,"b1_btag_%dj_HiJets%d_nb",nj,njHi);
        sprintf(nbstrb2,"b2_btag_%dj_HiJets%d_nb",nj,njHi);
        
        theFit.bind(MLStrList(njetsstrb0,njetsstrb1,njetsstrb2),njetsstr,njetsstr);
        theFit.bind(MLStrList(nbstrb0,nbstrb1,nbstrb2),nbstr,nbstr);
      }
      
 
    }
    
  
    // jet category
    sprintf(pdfname,"%dj",nj);

    sprintf(speclabel,"W_%dj",nj);
    theFit.addPdfWName("myFit",speclabel , "nExclPFJetsLo", "ExclJet", pdfname);

    sprintf(speclabel,"other_%dj",nj);
    theFit.addPdfWName("myFit",speclabel , "nExclPFJetsLo", "ExclJet", pdfname);

    sprintf(speclabel,"top0b_%dj",nj);
    theFit.addPdfWName("myFit",speclabel , "nExclPFJetsLo", "ExclJet", pdfname);

    sprintf(speclabel,"top1b_%dj",nj);
    theFit.addPdfWName("myFit",speclabel , "nExclPFJetsLo", "ExclJet", pdfname);

    sprintf(speclabel,"top2b_%dj",nj);
    theFit.addPdfWName("myFit",speclabel , "nExclPFJetsLo", "ExclJet", pdfname);

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

  Int_t ngen = 0;
  if(opts.getBoolVal("fitRatio")) 
    ngen = theFit.getRealPar("N_Wincl_total")->getVal();
  else
    ngen = theFit.getRealPar("N_Wincl_1j")->getVal();

  ngen += theFit.getRealPar("N_other_1j")->getVal()+theFit.getRealPar("N_other_2j")->getVal()+theFit.getRealPar("N_other_3j")->getVal()+theFit.getRealPar("N_other_4j")->getVal()+
    theFit.getRealPar("N_top0b_1j")->getVal()+theFit.getRealPar("N_top0b_2j")->getVal()+theFit.getRealPar("N_top0b_3j")->getVal()+theFit.getRealPar("N_top0b_4j")->getVal()+
    theFit.getRealPar("N_top1b_1j")->getVal()+theFit.getRealPar("N_top1b_2j")->getVal()+theFit.getRealPar("N_top1b_3j")->getVal()+theFit.getRealPar("N_top1b_4j")->getVal()+
    theFit.getRealPar("N_top2b_1j")->getVal()+theFit.getRealPar("N_top2b_2j")->getVal()+theFit.getRealPar("N_top2b_3j")->getVal()+theFit.getRealPar("N_top2b_4j")->getVal();

  // Generate...
  RooArgSet genVars(theFit.getObsList(MLStrList("pfmt","nBTagJets","nExclPFJetsLo")));
  MLToyStudy theStudy(theGenerator, genVars, "E", "MTE", 0, theFit.getNoNormVars("myFit"));
  if(opts.getBoolVal("MCT")) {
    char speclabel[50];
    for(int nj = opts.getRealVal("njetmin"); nj <=opts.getRealVal("njetmax"); nj++) {
      for(int nb=0; nb<3; nb++) {
        sprintf(speclabel,"top%db_%dj",nb,nj);
        theStudy.addMockSpecies(speclabel,"mockFinal.root",speclabel);
      }
    }
  }
  theStudy.addFit(*myPdf);

  theStudy.generateAndFit(nexp,ngen);
  
  char resultfilename[200];
  if (outfile==0) sprintf(resultfilename,"toys/output/resultsW-%s.dat",jetflavour);
  else sprintf(resultfilename, outfile, njets);
  theStudy._fitParData->write(resultfilename);

  char variablesfilename[200];
  sprintf(variablesfilename,"toys/output/variablesW-%s.root",jetflavour);
  TFile varfile(variablesfilename,"RECREATE");

  const RooArgSet *variables = theStudy._fitParData->get();
  variables->setName("variables");
  variables->Write();
  varfile.Close();

}

