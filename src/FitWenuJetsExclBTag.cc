// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("fitGenJets",      "Fit genjets", kFALSE);
  opts.addBoolOption("fitCaloJets",     "Fit calojets, PFjets otherwise", kFALSE);
  opts.addBoolOption("highJetThreshold", "Fit W+jets with ET>30 GeV", kTRUE);
  opts.addBoolOption("weightedDataset", "use event weight instead of 1",     kFALSE);
  opts.addBoolOption("fitRatio",        "FitRatio directly", kTRUE);
  opts.addBoolOption("unfold",          "use unfolding step",               kTRUE);
  opts.addBoolOption("effcorr",         "use njets efficiency corrections", kTRUE);
  opts.addBoolOption("fitInclusive",    "Fit inclusive W+jets multiplicity", kTRUE);
  opts.addBoolOption("usePfMt",         "Use W Transverse Mass",  kTRUE);
  opts.addBoolOption("useBTag",         "Use B Tag",  kTRUE);
  opts.addBoolOption("AllFit",          "Fit all species",        kTRUE);
  opts.addBoolOption("WOnlyFit",        "Fit W species only",     kFALSE);
  opts.addBoolOption("TopOnlyFit",      "Fit Top species only",   kFALSE);
  opts.addBoolOption("OtherOnlyFit",    "Fit other species only", kFALSE);
  opts.addBoolOption("TopControlFit",   "Fit the top cntrol sample", kFALSE);
  opts.addRealOption("njetmin",         "smallest jet number to consider", 0);
  opts.addRealOption("njetmax",         "largest jet number to consider", 4);
  opts.addRealOption("nb",              "number of MC truth b's in the event (-1 means no requirement)", -1);
  opts.addBoolOption("barrelOnly",      "barrel only", kFALSE);
  opts.addBoolOption("endcapOnly",      "endcap only", kFALSE);
  opts.addBoolOption("preliminaryLabel", "Add the label with CMS preliminary", kTRUE);

  return opts;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

MLFit theFit;

void myFit() {

  MLFit theFit;

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // define the structure of the dataset
  RooRealVar* pfmt = new RooRealVar("pfmt",  "M_{T}" , 20., 150., "GeV/c^{2}");
  RooRealVar* nbj = new RooRealVar("nBTagJets", "n_{b-tag jets}", 0.0, 3.0);
  RooRealVar* weight = new RooRealVar("weight", "weight",1);
  RooRealVar *njets;
  if(opts.getBoolVal("fitGenJets")) {
    if(opts.getBoolVal("highJetThreshold")) njets = new RooRealVar("nExclGenJetsHi", "nExclGenJetsHi",0.5, 20.5);
    else njets = new RooRealVar("nExclGenJetsLo", "nExclGenJetsLo",0.5, 20.5);
  } else if(opts.getBoolVal("fitCaloJets")) {
    if(opts.getBoolVal("highJetThreshold")) njets = new RooRealVar("nExclJetsHi", "nExclJetsHi",0.5, 20.5);
    else njets = new RooRealVar("nExclJetsLo", "nExclJetsLo",0.5, 20.5);
  } else {
    if(opts.getBoolVal("highJetThreshold")) njets = new RooRealVar("nExclPFJetsHi", "nExclPFJetsHi",0.5, 20.5);
    else njets = new RooRealVar("nExclPFJetsLo", "nExclPFJetsLo",0.5, 20.5);
  }

  theFit.AddFlatFileColumn(pfmt);
  theFit.AddFlatFileColumn(nbj);
  theFit.AddFlatFileColumn(njets);
  theFit.AddFlatFileColumn(weight);

  // define a fit model
  theFit.addModel("myFit", "Ratio WtoENu");

  // define species
  MLStrList speclist;
  TString firstlabel("");
  for(int nj = opts.getRealVal("njetmin"); nj <=opts.getRealVal("njetmax"); nj++){
    //signal (assumption is W is all 0 bjets in the acceptance)
    char speclabel[50], specdesc[200];
    sprintf(speclabel,"W_%dj",nj);
    sprintf(specdesc,"Signal %dj Component",nj);
    theFit.addSpecies("myFit", speclabel, specdesc);
    if(opts.getBoolVal("unfold")) { 
      if(nj!=0) speclist.Add(speclabel); // exclusive species list ot be transformed in inclusive.
      else firstlabel = speclabel;
    } else {
      speclist.Add(speclabel);
    }

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

  // 30GeV PFjet, no PU, Madgraph Z2, W->enu smearing matrix
  float unf[25] = { 0.984035,       0.0862901,      0.00550043,     0.000332631,    0,
                    0.0157636,      0.884884,       0.119709,       0.0127509,      0,
                    0.000199209,    0.028361,       0.842643,       0.168977,       0.0156174,
                    2.30744e-06,    0.000464765,    0.0316275,      0.778135,       0.183992,
                    0,      0,      0.000520311,    0.0398049,      0.80039 };

  double eff[5] = { 0.718, 0.661, 0.614, 0.555, 0.485 };

  TMatrix foldingmatrix(5,5,unf);
  TArrayD efficiency(5,eff);

  if(opts.getBoolVal("fitRatio"))  {
    cout << "===> FITTING BERENDS-GIELE SCALING <===" << endl;
    if(opts.getBoolVal("unfold")) {
      cout << "===> FITTING AT GEN LEVEL <===" << endl;
      if(opts.getBoolVal("effcorr")) theFit.fitInclusiveRatioPolyUnfold(speclist, "Wincl", foldingmatrix , firstlabel, efficiency);
      else theFit.fitInclusiveRatioPolyUnfold(speclist, "Wincl", foldingmatrix , firstlabel);
    } else {
      cout << "===> FITTING AT DET LEVEL <===" << endl;
      if(opts.getBoolVal("effcorr")) theFit.fitInclusiveRatioPoly(speclist, "Wincl", opts.getRealVal("njetmin"), efficiency);
      else theFit.fitInclusiveRatioPoly(speclist, "Wincl", opts.getRealVal("njetmin"));
    }
  } else if(opts.getBoolVal("fitInclusive")) { 
    cout << "===> FITTING INCLUSIVE W+JETS MULTIPLICITIES <===" << endl;
    theFit.fitInclusive( speclist, "Wincl_",opts.getRealVal("njetmin"));
  } else {
    cout << "===> FITTING EXCLUSIVE W+JETS MULTIPLICITIES <===" << endl;
  }

  char jetlabel[200];
  if(opts.getBoolVal("fitGenJets")) {
    if(opts.getBoolVal("highJetThreshold")) sprintf(jetlabel,"nExclGenJetsHi");
    else sprintf(jetlabel,"nExclGenJetsLo");
  } else if(opts.getBoolVal("fitCaloJets")) {
    if(opts.getBoolVal("highJetThreshold")) sprintf(jetlabel,"nExclJetsHi");
    else sprintf(jetlabel,"nExclJetsLo");
  } else {
    if(opts.getBoolVal("highJetThreshold")) sprintf(jetlabel,"nExclPFJetsHi");
    else sprintf(jetlabel,"nExclPFJetsLo");
  }

  char speclabel[50],pdfname[200],speclabelToCopy[200];
  for(int nj = opts.getRealVal("njetmin"); nj <=opts.getRealVal("njetmax"); nj++){
    
    // Mt PDF
    if(opts.getBoolVal("usePfMt")) {
      
      //signal
      sprintf(speclabel,"W_%dj",nj);
      sprintf(pdfname,"sig_PfMt%dj",nj);   
      theFit.addPdfWName("myFit", speclabel , "pfmt",  "DoubleCruijff", pdfname );
      // theFit.addPdfWName("myFit", speclabel , "pfmt",  "CrystalCruijff", pdfname );

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
    theFit.addPdfWName("myFit",speclabel , jetlabel, "ExclJet", pdfname);

    sprintf(speclabel,"other_%dj",nj);
    theFit.addPdfWName("myFit",speclabel , jetlabel, "ExclJet", pdfname);

    sprintf(speclabel,"top0b_%dj",nj);
    theFit.addPdfWName("myFit",speclabel , jetlabel, "ExclJet", pdfname);

    sprintf(speclabel,"top1b_%dj",nj);
    theFit.addPdfWName("myFit",speclabel , jetlabel, "ExclJet", pdfname);

    sprintf(speclabel,"top2b_%dj",nj);
    theFit.addPdfWName("myFit",speclabel , jetlabel, "ExclJet", pdfname);

  }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fit a sample of Z events
void FitWElectrons() {
  
  myFit();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  char jetflavour[200];
  if(opts.getBoolVal("fitGenJets")) sprintf(jetflavour, "genjet");
  else if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "PFjet");
  
  int ithr;
  if(opts.getBoolVal("highJetThreshold")) ithr=0;
  else ithr=1;

  // Load the data
  char datasetname[200];
  if(opts.getBoolVal("AllFit")) sprintf(datasetname,"results_data/datasets/data_Wenu.root");
  else sprintf(datasetname,"results/datasets/wenu.root");
  // only for the top control sample
  if(opts.getBoolVal("TopControlFit"))  sprintf(datasetname,"results_data_top/datasets/dataset_ll.root");
  char treename[100];
  if(opts.getBoolVal("AllFit")) sprintf(treename,"Data");
  if(opts.getBoolVal("WOnlyFit")) sprintf(treename,"WJets");
  if(opts.getBoolVal("OtherOnlyFit")) sprintf(treename,"OtherJets");
  if(opts.getBoolVal("TopOnlyFit")) sprintf(treename,"TopJets");
  if(opts.getBoolVal("TopControlFit")) sprintf(treename,"T1");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *totdata = theFit.getDataSet(treename);
   char cutstring[100];
   if(opts.getBoolVal("fitGenJets")) {
     if(opts.getBoolVal("highJetThreshold")) sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )","nExclGenJetsHi",
                                                     opts.getRealVal("njetmin") , "nExclGenJetsHi" , opts.getRealVal("njetmax"));
     else sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )","nExclGenJetsLo",
                  opts.getRealVal("njetmin") , "nExclGenJetsLo" , opts.getRealVal("njetmax"));
   } else {
     if(opts.getBoolVal("highJetThreshold")) sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsHi":"nExclPFJetsHi",
                                                     opts.getRealVal("njetmin") ,opts.getBoolVal("fitCaloJets")?"nExclJetsHi":"nExclPFJetsHi" , opts.getRealVal("njetmax"));
     else sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsLo":"nExclPFJetsLo",
                  opts.getRealVal("njetmin") ,opts.getBoolVal("fitCaloJets")?"nExclJetsLo":"nExclPFJetsLo" , opts.getRealVal("njetmax"));
   }
   std::cout << "===> Reducing data with cut: " << cutstring << " <===" << std::endl;
   RooDataSet *data = (RooDataSet *)totdata->reduce(cutstring);

   // if requested, on MC, require a number of b-quarks (to validate the nBTagJets PDF)
   if(opts.getRealVal("nb")!=-1) {
     char bcutstring[50];
     sprintf(bcutstring,"nB==%d",opts.getRealVal("nb"));
     std::cout << "Reducing with MC truth cut: " << bcutstring << std::endl;
     data = (RooDataSet*) data->reduce(bcutstring);
   }

   if(opts.getBoolVal("barrelOnly")) data = (RooDataSet*) data->reduce("ecalsubdet==0");
   if(opts.getBoolVal("endcapOnly")) data = (RooDataSet*) data->reduce("ecalsubdet==1");

   // use event weights
   if(opts.getBoolVal("weightedDataset")) data->setWeightVar("weight");

   data->Print("V");

   // build the fit likelihood
   RooAbsPdf *myPdf = theFit.buildModel("myFit");

   // Initialize the fit...
   char initconfigfile[200];
   if(opts.getBoolVal("AllFit")) {
     sprintf(initconfigfile,"fitconfig/fitW-NewBJet-%s-thr%d.config",jetflavour,ithr);
     cout << "Using " << initconfigfile << endl;
     theFit.initialize(initconfigfile);
   }
   if(opts.getBoolVal("WOnlyFit")) theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-Wonly-NewBJet.config");
   if(opts.getBoolVal("OtherOnlyFit")) theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-otheronly-NewBJet.config");
   if(opts.getBoolVal("TopOnlyFit")) theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-toponly-NewBJet.config");
   if(opts.getBoolVal("TopControlFit")) {
     sprintf(initconfigfile,"fitconfig/fitTopControl-NewBJet-%s-thr%d.config",jetflavour,ithr);
     theFit.initialize(initconfigfile);
   }

   // Print Fit configuration 
   myPdf->getParameters(data)->selectByAttrib("Constant",kTRUE)->Print("V");  
   myPdf->getParameters(data)->selectByAttrib("Constant",kFALSE)->Print("V");

   RooFitResult *fitres;
   if(opts.getBoolVal("weightedDataset")) fitres =  myPdf->fitTo(*data,RooFit::ConditionalObservables(theFit.getNoNormVars("myFit")),RooFit::FitOptions("MHTER"),RooFit::SumW2Error(kTRUE),RooFit::NumCPU(4),RooFit::Timer(kTRUE));
   else fitres =  myPdf->fitTo(*data,RooFit::ConditionalObservables(theFit.getNoNormVars("myFit")),RooFit::FitOptions("MHTER"),RooFit::NumCPU(4),RooFit::Timer(kTRUE));
   fitres->Print("V");

   // write the config file corresponding to the fit minimum
   char configfilename[200];
   if(opts.getBoolVal("AllFit")) sprintf(configfilename, "fitres/fitMinimumW-NewBJet-%s-thr%d.config",jetflavour,ithr);
   if(opts.getBoolVal("WOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-Wonly-NewBJet-%s-thr%d.config",jetflavour,ithr);
   if(opts.getBoolVal("OtherOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-otheronly-NewBJet-%s-thr%d.config",jetflavour,ithr);
   if(opts.getBoolVal("TopOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-toponly-NewBJet-%s-thr%d.config",jetflavour,ithr);
   if(opts.getBoolVal("TopControlFit")) sprintf(configfilename, "fitres/fitMinimumTopControl-NewBJet-%s-thr%d.config",jetflavour,ithr);
   theFit.writeConfigFile(configfilename);  

   // save the fit result in ROOT 
   char rootfilename[200];
   if(opts.getBoolVal("AllFit")) sprintf(rootfilename, "fitres/fitMinimumW-NewBJet-%s-thr%d.root",jetflavour,ithr);
   if(opts.getBoolVal("WOnlyFit")) sprintf(rootfilename,"shapesWenu/root/fitRes-Wonly-NewBJet-%s-thr%d.root",jetflavour,ithr);
   if(opts.getBoolVal("OtherOnlyFit")) sprintf(rootfilename,"shapesWenu/root/fitRes-otheronly-NewBJet-%s-thr%d.root",jetflavour,ithr);
   if(opts.getBoolVal("TopOnlyFit")) sprintf(rootfilename,"shapesWenu/root/fitRes-toponly-NewBJet-%s-thr%d.root",jetflavour,ithr);
   if(opts.getBoolVal("TopControlFit")) sprintf(rootfilename, "fitres/fitMinimumTopControl-NewBJet-%s-thr%d.root",jetflavour,ithr);

   TFile *file = new TFile(rootfilename,"recreate");
   fitres->Write();
   file->Close();

 }

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////

 void PlotWElectrons(int njets, int ithr, int nbins) {

   myFit();

   // Various fit options...
   MLOptions opts = GetDefaultOptions();

   char jetflavour[200];
   if(opts.getBoolVal("fitGenJets")) sprintf(jetflavour, "genjet");
   else if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
   else sprintf(jetflavour, "PFjet");

   // Load the data
   char datasetname[200];
   if(opts.getBoolVal("AllFit")) sprintf(datasetname,"results_data/datasets/data_Wenu.root");
   else sprintf(datasetname,"results/datasets/wenu.root");
   // only for the top control sample
   if(opts.getBoolVal("TopControlFit"))  sprintf(datasetname,"results_data_top/datasets/dataset_ll.root");
   char treename[100];
   if(opts.getBoolVal("AllFit")) sprintf(treename,"Data");
   if(opts.getBoolVal("WOnlyFit")) sprintf(treename,"WJets");
   if(opts.getBoolVal("OtherOnlyFit")) sprintf(treename,"OtherJets");
   if(opts.getBoolVal("TopOnlyFit")) sprintf(treename,"TopJets");
   if(opts.getBoolVal("TopControlFit")) sprintf(treename,"T1");
   theFit.addDataSetFromRootFile(treename, treename, datasetname);
   RooDataSet *data = theFit.getDataSet(treename);
   char cutstring[100];
   if(opts.getBoolVal("fitGenJets")) {
     if(opts.getBoolVal("highJetThreshold")) sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )","nExclGenJetsHi",
                                                     opts.getRealVal("njetmin") , "nExclGenJetsHi" , opts.getRealVal("njetmax"));
     else sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )","nExclGenJetsLo",
                  opts.getRealVal("njetmin") , "nExclGenJetsLo" , opts.getRealVal("njetmax"));
   } else {
     if(opts.getBoolVal("highJetThreshold")) sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsHi":"nExclPFJetsHi",
                                                     opts.getRealVal("njetmin") ,opts.getBoolVal("fitCaloJets")?"nExclJetsHi":"nExclPFJetsHi" , opts.getRealVal("njetmax"));
     else sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsLo":"nExclPFJetsLo",
                  opts.getRealVal("njetmin") ,opts.getBoolVal("fitCaloJets")?"nExclJetsLo":"nExclPFJetsLo" , opts.getRealVal("njetmax"));
   }
   std::cout << "===> Reducing data with cut: " << cutstring << " <===" << std::endl;
   data = (RooDataSet *)data->reduce(cutstring);

   // if requested, on MC, require a number of b-quarks (to validate the nBTagJets PDF)
   if(opts.getRealVal("nb")!=-1) {
     char bcutstring[50];
     sprintf(bcutstring,"nB==%d",opts.getRealVal("nb"));
     std::cout << "Reducing with MC truth cut: " << bcutstring << std::endl;
     data = (RooDataSet*) data->reduce(bcutstring);
   }

   if(opts.getBoolVal("barrelOnly")) data = (RooDataSet*) data->reduce("ecalsubdet==0");
   if(opts.getBoolVal("endcapOnly")) data = (RooDataSet*) data->reduce("ecalsubdet==1");

   // use event weights
   if(opts.getBoolVal("weightedDataset")) data->setWeightVar("weight");

   data->Print("V");

   // build the fit likelihood
   RooAbsPdf *myPdf = theFit.buildModel("myFit");

   // Initialize the fit...
   char configfilename[200];
   if(opts.getBoolVal("AllFit")) sprintf(configfilename,"fitres/fitMinimumW-NewBJet-%s-thr%d.config",jetflavour,ithr);
   if(opts.getBoolVal("WOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-Wonly-NewBJet-%s-thr%d.config",jetflavour,ithr);
   if(opts.getBoolVal("OtherOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-otheronly-NewBJet-%s-thr%d.config",jetflavour,ithr);
   if(opts.getBoolVal("TopOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-toponly-NewBJet-%s-thr%d.config",jetflavour,ithr);
   if(opts.getBoolVal("TopControlFit")) sprintf(configfilename,"fitres/fitMinimumTopControl-NewBJet-%s-thr%d.config",jetflavour,ithr);
   theFit.initialize(configfilename);

   if(opts.getBoolVal("usePfMt")) {
     TCanvas *c = new TCanvas("c","fitResult");
     RooPlot* MassPlot = MakePlot("pfmt", njets, &theFit, data, configfilename, nbins);    

     MassPlot->SetAxisColor(1,"x");
     MassPlot->SetLabelColor(1, "X");
     MassPlot->SetLabelColor(1, "Y");
     MassPlot->SetXTitle("M_{T}[GeV/c^{2}]");

     char binsize[50];
     Double_t binW = MassPlot->getFitRangeBinW();
     sprintf(binsize,"%2.0f",binW);

     MassPlot->SetYTitle(TString("Events / (")+TString(binsize)+TString(" GeV/c^{2})"));
     MassPlot->Draw();

     makeLegend();

     if(opts.getBoolVal("preliminaryLabel")) {
       TPaveText pt1(0.1,0.96,0.8,0.98,"NDC");
       pt1.SetTextFont(72);
       pt1.SetTextSize(0.03);
       pt1.SetTextAlign(12);
       pt1.SetFillColor(0);
       pt1.SetBorderSize(0);
       pt1.AddText("CMS Preliminary 2010, #sqrt{s}=7 TeV, L_{int}=35 pb^{-1}");
       pt1.Draw();
     }

     char epsfilename[200];
     char Cfilename[200];

     if(opts.getBoolVal("AllFit")) {
       sprintf(epsfilename,"fit-plots/eps/PfMt-data-%d%s-thr%d.eps",njets,jetflavour,ithr);
       sprintf(Cfilename,"fit-plots/macro/PfMt-data-%d%s-thr%d.C",njets,jetflavour,ithr);
     }
     if(opts.getBoolVal("WOnlyFit")) {
       sprintf(epsfilename,"shapesWenu/eps/PfMt-Wonly-%d%s-thr%d.eps",njets,jetflavour,ithr);
       sprintf(Cfilename,"shapesWenu/macro/PfMt-Wonly-%d%s-thr%d.C",njets,jetflavour,ithr);
     }
     if(opts.getBoolVal("OtherOnlyFit")) {
       sprintf(epsfilename,"shapesWenu/eps/PfMt-Otheronly-%d%s-thr%d.eps",njets,jetflavour,ithr);
       sprintf(Cfilename,"shapesWenu/macro/PfMt-Otheronly-%d%s-thr%d.C",njets,jetflavour,ithr);
     }
     if(opts.getBoolVal("TopOnlyFit")) {
       sprintf(epsfilename,"shapesWenu/eps/PfMt-toponly-%d%s-thr%d.eps",njets,jetflavour,ithr);
       sprintf(Cfilename,"shapesWenu/macro/PfMt-toponly-%d%s-thr%d.C",njets,jetflavour,ithr);
     }
     c->SaveAs(epsfilename);
     c->SaveAs(Cfilename);
   }

   if(opts.getBoolVal("useBTag")) {
     TCanvas *c = new TCanvas("c","fitResult");
     RooPlot* BTagPlot = MakePlot("nBTagJets", njets, &theFit, data, configfilename, 3);    

     BTagPlot->SetAxisColor(1,"x");
     BTagPlot->SetLabelColor(1, "X");
     BTagPlot->SetLabelColor(1, "Y");
     BTagPlot->SetXTitle("N_{b-tag jets}");

     char binsize[50];
     Double_t binW = BTagPlot->getFitRangeBinW();
     sprintf(binsize,"%1.2f",binW);

     BTagPlot->SetYTitle(TString("Events / (")+TString(binsize)+TString(" )"));
     BTagPlot->Draw();

     makeLegend();

     if(opts.getBoolVal("preliminaryLabel")) {
       TPaveText pt1(0.1,0.96,0.8,0.98,"NDC");
       pt1.SetTextFont(72);
       pt1.SetTextSize(0.03);
       pt1.SetTextAlign(12);
       pt1.SetFillColor(0);
       pt1.SetBorderSize(0);
       pt1.AddText("CMS Preliminary 2010, #sqrt{s}=7 TeV, L_{int}=35 pb^{-1}");
       pt1.Draw();
     }

     char epsfilename[200];
     char Cfilename[200];

     if(opts.getBoolVal("AllFit")) {
       sprintf(epsfilename,"fit-plots/eps/BTag-data-%d%s-thr%d.eps",njets,jetflavour,ithr);
       sprintf(Cfilename,"fit-plots/macro/BTag-data-%d%s-thr%d.C",njets,jetflavour,ithr);
     }
     if(opts.getBoolVal("WOnlyFit")) {
       if(opts.getRealVal("nb")!=-1) {
         sprintf(epsfilename,"shapesWenu/eps/BTag-Wonly-%dbquarks-%d%s-thr%d.eps",opts.getRealVal("nb"),njets,jetflavour,ithr);
         sprintf(Cfilename,"shapesWenu/macro/BTag-Wonly-%dbquarks-%d%s-thr%d.C",opts.getRealVal("nb"),njets,jetflavour,ithr);        
       } else {
         sprintf(epsfilename,"shapesWenu/eps/BTag-Wonly-%d%s-thr%d.eps",njets,jetflavour,ithr);
         sprintf(Cfilename,"shapesWenu/macro/BTag-Wonly-%d%s-thr%d.C",njets,jetflavour,ithr);
       }
     }
     if(opts.getBoolVal("OtherOnlyFit")) {
       sprintf(epsfilename,"shapesWenu/eps/BTag-Otheronly-%d%s-thr%d.eps",njets,jetflavour,ithr);
       sprintf(Cfilename,"shapesWenu/macro/BTag-Otheronly-%d%s-thr%d.C",njets,jetflavour,ithr);
     }
     if(opts.getBoolVal("TopOnlyFit")) {
       if(opts.getRealVal("nb")!=-1) {
         sprintf(epsfilename,"shapesWenu/eps/BTag-toponly-%dbquarks-%d%s-thr%d.eps",opts.getRealVal("nb"),njets,jetflavour,ithr);
         sprintf(Cfilename,"shapesWenu/macro/BTag-toponly-%dbquarks-%d%s-thr%d.C",opts.getRealVal("nb"),njets,jetflavour,ithr);
       } else {
         sprintf(epsfilename,"shapesWenu/eps/BTag-toponly-%d%s-thr%d.eps",njets,jetflavour,ithr);
         sprintf(Cfilename,"shapesWenu/macro/BTag-toponly-%d%s-thr%d.C",njets,jetflavour,ithr);
       }
     }
     if(opts.getBoolVal("TopControlFit")) {
       sprintf(epsfilename,"fit-plots/eps/BTag-dataTopControl-%d%s-thr%d.eps",njets,jetflavour,ithr);
       sprintf(Cfilename,"fit-plots/macro/BTag-dataTopControl-%d%s-thr%d.C",njets,jetflavour,ithr);
     }
     c->SaveAs(epsfilename);
     c->SaveAs(Cfilename);
   }

 }

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////

 // Make the plot for a given variable
 RooPlot *MakePlot(TString VarName, int njets, MLFit* theFit, RooDataSet* theData, const char *configfilename, int nbins)
 {

   // Various fit options...
   MLOptions opts = GetDefaultOptions();

   RooRealVar* Var = theFit->RealObservable(VarName);
   RooRealVar* jets;
   if(opts.getBoolVal("highJetThreshold")) {
     if(opts.getBoolVal("fitCaloJets")) jets = theFit->RealObservable("nExclJetsHi");
     else jets = theFit->RealObservable("nExclPFJetsHi");
   } else{
     if(opts.getBoolVal("fitCaloJets")) jets = theFit->RealObservable("nExclJetsLo");
     else jets = theFit->RealObservable("nExclPFJetsLo");
   }
   jets->setVal(njets);

   double min=Var->getMin();
   double max=Var->getMax();
   RooPlot *plot = Var->frame(min,max,nbins);

   char cutstring[100];
   if(opts.getBoolVal("highJetThreshold")) sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsHi":"nExclPFJetsHi",
                                                   opts.getRealVal("njetmin") ,opts.getBoolVal("fitCaloJets")?"nExclJetsHi":"nExclPFJetsHi" , opts.getRealVal("njetmax"));
   else sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsLo":"nExclPFJetsLo",
                opts.getRealVal("njetmin") ,opts.getBoolVal("fitCaloJets")?"nExclJetsLo":"nExclPFJetsLo" , opts.getRealVal("njetmax"));
   std::cout << "===> Reducing data with cut: " << cutstring << " <===" << std::endl;

   // plot the data
   if(opts.getBoolVal("weightedDataset"))
     theData->plotOn(plot, RooFit::DataError(RooAbsData::SumW2), RooFit::Cut(cutstring));
   else 
     theData->plotOn(plot, RooFit::DataError(RooAbsData::Poisson), RooFit::Cut(cutstring));

   // plot the total likelihood
   RooAbsPdf *thePdf = theFit->getPdf("myFit");
   thePdf->plotOn(plot, RooFit::DrawOption("F"), RooFit::LineColor(kOrange+4), RooFit::FillColor(kOrange), RooFit::LineWidth(2), RooFit::MoveToBack(), RooFit::Slice(*jets) );
   thePdf->plotOn(plot, RooFit::DrawOption("L"), RooFit::LineColor(kOrange+7), RooFit::LineWidth(2), RooFit::Slice(*jets) );

   //   thePdf->plotOn(plot, RooFit::DrawOption("F"), RooFit::FillColor(kOrange+8), RooFit::LineWidth(2), RooFit::MoveToBack(), RooFit::Slice(*jets) );
   //   thePdf->plotOn(plot, RooFit::DrawOption("L"), RooFit::LineColor(kOrange+4), RooFit::LineWidth(2), RooFit::Slice(*jets) );
   //   thePdf->plotOn(plot, RooFit::DrawOption("F"), RooFit::FillColor(kViolet), RooFit::LineWidth(2), RooFit::MoveToBack(), RooFit::Slice(*jets) );
   //   thePdf->plotOn(plot, RooFit::DrawOption("L"), RooFit::LineColor(kViolet+3), RooFit::LineWidth(2), RooFit::Slice(*jets) );

    char speclabel[1000];
    sprintf(speclabel,"myFit_other_%dj,myFit_top0b_%dj,myFit_top1b_%dj,myFit_top2b_%dj",njets,njets,njets,njets);
    thePdf->plotOn(plot, RooFit::Components(speclabel), RooFit::DrawOption("F"), RooFit::FillColor(kViolet), RooFit::Slice(*jets) );
    thePdf->plotOn(plot, RooFit::Components(speclabel), RooFit::LineColor(kViolet+3), RooFit::LineWidth(2), RooFit::Slice(*jets) );       

    sprintf(speclabel,"myFit_top0b_%dj,myFit_top1b_%dj,myFit_top2b_%dj",njets,njets,njets);
    thePdf->plotOn(plot, RooFit::Components(speclabel), RooFit::DrawOption("F"), RooFit::FillColor(kOrange+8), RooFit::Slice(*jets));
    thePdf->plotOn(plot, RooFit::Components(speclabel), RooFit::LineColor(kOrange+4), RooFit::LineWidth(2), RooFit::Slice(*jets));

   if(opts.getBoolVal("weightedDataset"))
     theData->plotOn(plot, RooFit::DataError(RooAbsData::SumW2), RooFit::Cut(cutstring));
   else 
     theData->plotOn(plot, RooFit::DataError(RooAbsData::Poisson), RooFit::Cut(cutstring));

  return plot;
}

void makeLegend() {
  // Legend
  TH1F *dataH = new TH1F("dataH","dataH",50,0,150);
  TH1F *totalH = new TH1F("totalH","totalH",50,0,150);
  TH1F *topPlusOtherH = new TH1F("topPlusOtherH","topPlusOtherH",50,0,150);
  TH1F *otherH = new TH1F("otherH","otherH",50,0,150);

  dataH->SetMarkerColor(kBlack);
  totalH->SetFillColor(kOrange);
  topPlusOtherH->SetFillColor(kViolet);
  otherH->SetFillColor(kOrange+8);

  TLegendEntry *legge;
  TLegend *leg;
  leg = new TLegend(0.6,0.65,0.93,0.8);
  leg->SetFillStyle(0); leg->SetBorderSize(0.); leg->SetTextSize(0.025);
  leg->SetFillColor(0);
  legge = leg->AddEntry(dataH,"Data", "lpe");
  legge = leg->AddEntry(totalH,"total","f");
  legge = leg->AddEntry(topPlusOtherH,"Top+Other","f");
  legge = leg->AddEntry(otherH,"Top","f");
  leg->Draw();
  gPad->Update();
}
