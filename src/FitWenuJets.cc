// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("fitCaloJets",     "Fit calojets, PFjets otherwise", kFALSE);
  opts.addBoolOption("highJetThreshold", "Fit W+jets with ET>30 GeV", kTRUE);
  opts.addBoolOption("weightedDataset", "use event weight instead of 1",     kTRUE);
  opts.addBoolOption("fitRatio",         "FitRatio directly",kFALSE);
  opts.addBoolOption("usePfMt",         "Use W Transverse Mass",  kTRUE);
  opts.addBoolOption("AllFit",          "Fit all species",        kFALSE);
  opts.addBoolOption("WOnlyFit",        "Fit W species only",     kTRUE);
  opts.addBoolOption("QCDOnlyFit",      "Fit QCD species only",   kFALSE);
  opts.addBoolOption("otherOnlyFit",    "Fit other species only", kFALSE);
  opts.addRealOption("njetmin",         "smallest jet number to consider", 1);
  opts.addRealOption("njetmax",         "largest jet number to consider", 1);
  opts.addBoolOption("preliminaryLabel", "Add the label with CMS preliminary", kFALSE);

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
  RooRealVar* weight = new RooRealVar("weight", "weight",1);
  RooRealVar *njets;
  if(opts.getBoolVal("fitCaloJets")) {
    if(opts.getBoolVal("highJetThreshold")) njets = new RooRealVar("nExclJetsHi", "nExclJetsHi",0.5, 20.5);
    else njets = new RooRealVar("nExclJetsLo", "nExclJetsLo",0.5, 20.5);
  } else {
    if(opts.getBoolVal("highJetThreshold")) njets = new RooRealVar("nExclPFJetsHi", "nExclPFJetsHi",0.5, 20.5);
    else njets = new RooRealVar("nExclPFJetsLo", "nExclPFJetsLo",0.5, 20.5);
  }

  theFit.AddFlatFileColumn(pfmt);
  theFit.AddFlatFileColumn(njets);
  theFit.AddFlatFileColumn(weight);

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
  
  char jetlabel[200];
  if(opts.getBoolVal("fitCaloJets")) {
    if(opts.getBoolVal("highJetThreshold")) sprintf(jetlabel,"nExclJetsHi");
    else sprintf(jetlabel,"nExclJetsLo");
  } else {
    if(opts.getBoolVal("highJetThreshold")) sprintf(jetlabel,"nExclPFJetsHi");
    else sprintf(jetlabel,"nExclPFJetsLo");
  }

  char speclabel[50],pdfname[200];
  for(int nj = opts.getRealVal("njetmin"); nj <=opts.getRealVal("njetmax"); nj++){
    
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

      // used only in the 1/2-jet bin
      const int nbins = 10;
      double limitarray[] = {20.,28.,36.,44.,52.,60.,70.,80.,90.,120.,150.};

      TAxis* limits = new TAxis(nbins,limitarray) ;
      TList args;
      args.Add(limits);

      //other
      sprintf(speclabel,"other%dj",nj);
      sprintf(pdfname,"other_PfMt%dj",nj);   
      if(nj<3) // 1,2 j ==> ttbar veto
        theFit.addPdfWName("myFit",speclabel  , "pfmt",  "BinnedPdf", args,  pdfname);
      else theFit.addPdfWName("myFit",speclabel  , "pfmt",  "Cruijff",   pdfname);

    }

    // jet category
    sprintf(pdfname,"%dj",nj);

    sprintf(speclabel,"W%dj",nj);
    theFit.addPdfWName("myFit",speclabel , jetlabel, "ExclJet", pdfname);

    sprintf(speclabel,"qcd%dj",nj);
    theFit.addPdfWName("myFit",speclabel , jetlabel, "ExclJet", pdfname);

    sprintf(speclabel,"other%dj",nj);
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
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "PFjet");
  
  int ithr;
  if(opts.getBoolVal("highJetThreshold")) ithr=0;
  else ithr=1;

  // Load the data
  char datasetname[200];
  if(opts.getBoolVal("AllFit")) sprintf(datasetname,"results_data/datasetsJets/wenu_36X_0calojet_thr0.root");
  else sprintf(datasetname,"results/datasetsJets/wenu_36X_0calojet_thr0.root");
  char treename[100];
  if(opts.getBoolVal("AllFit")) sprintf(treename,"Data");
  if(opts.getBoolVal("WOnlyFit")) sprintf(treename,"WJets");
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(treename,"QCDJets");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(treename,"OtherJets");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *totdata = theFit.getDataSet(treename);
  char cutstring[100];
  if(opts.getBoolVal("highJetThreshold")) sprintf(cutstring,"(pfmt>20) && (%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsHi":"nExclPFJetsHi",
                                                  opts.getRealVal("njetmin") ,opts.getBoolVal("fitCaloJets")?"nExclJetsHi":"nExclPFJetsHi" , opts.getRealVal("njetmax"));
  else sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsLo":"nExclPFJetsLo",
               opts.getRealVal("njetmin") ,opts.getBoolVal("fitCaloJets")?"nExclJetsLo":"nExclPFJetsLo" , opts.getRealVal("njetmax"));
  std::cout << "===> Reducing data with cut: " << cutstring << " <===" << std::endl;
  RooDataSet *data = (RooDataSet *)totdata->reduce(cutstring);

  // use event weights
  if(opts.getBoolVal("weightedDataset")) data->setWeightVar("weight");

  data->Print("V");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  if(opts.getBoolVal("AllFit")) {
    char initconfigfile[200];
    sprintf(initconfigfile,"fitconfig/fitW-New-%s-thr%d.config",jetflavour,ithr);
    theFit.initialize(initconfigfile);
  }
  if(opts.getBoolVal("WOnlyFit")) theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-Wonly-New.config");
  if(opts.getBoolVal("QCDOnlyFit")) theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-QCDonly-New.config");
  if(opts.getBoolVal("otherOnlyFit")) theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-otheronly-New.config");

  // Print Fit configuration 
  myPdf->getParameters(data)->selectByAttrib("Constant",kTRUE)->Print("V");  
  myPdf->getParameters(data)->selectByAttrib("Constant",kFALSE)->Print("V");
  
  RooFitResult *fitres;
  if(opts.getBoolVal("weightedDataset")) fitres =  myPdf->fitTo(*data,RooFit::ConditionalObservables(theFit.getNoNormVars("myFit")),RooFit::FitOptions("MHTER"),RooFit::SumW2Error(kTRUE),RooFit::NumCPU(4),RooFit::Timer(kTRUE));
  else fitres =  myPdf->fitTo(*data,RooFit::ConditionalObservabLes(theFit.getNoNormVars("myFit")),RooFit::FitOptions("MHTER"),RooFit::NumCPU(4),RooFit::Timer(kTRUE));
  fitres->Print("V");
  
  // write the config file corresponding to the fit minimum
  char configfilename[200];
  if(opts.getBoolVal("AllFit")) sprintf(configfilename, "fitres/fitMinimumW-New-%s-thr%d.config",jetflavour,ithr);
  if(opts.getBoolVal("WOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-Wonly-New-%s-thr%d.config",jetflavour,ithr);
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-QCDonly-New-%s-thr%d.config",jetflavour,ithr);
  if(opts.getBoolVal("otherOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-otheronly-New-%s-thr%d.config",jetflavour,ithr);
  theFit.writeConfigFile(configfilename);  

  // save the fit result in ROOT 
  char rootfilename[200];
  if(opts.getBoolVal("AllFit")) sprintf(rootfilename, "fitres/fitMinimumW-New-%s-thr%d.root",jetflavour,ithr);
  if(opts.getBoolVal("WOnlyFit")) sprintf(rootfilename,"shapesWenu/root/fitRes-Wonly-New-%s-thr%d.root",jetflavour,ithr);
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(rootfilename,"shapesWenu/root/fitRes-QCDonly-New-%s-thr%d.root",jetflavour,ithr);
  if(opts.getBoolVal("otherOnlyFit")) sprintf(rootfilename,"shapesWenu/root/fitRes-otheronly-New-%s-thr%d.root",jetflavour,ithr);

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
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "PFjet");

  // Load the data
  char datasetname[200];
  if(opts.getBoolVal("AllFit")) sprintf(datasetname,"results_data/datasetsJets/wenu_36X_0calojet_thr0.root");
  else sprintf(datasetname,"results/datasetsJets/wenu_36X_0calojet_thr0.root");
  char treename[100];
  if(opts.getBoolVal("AllFit")) sprintf(treename,"Data");
  if(opts.getBoolVal("WOnlyFit")) sprintf(treename,"WJets");
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(treename,"QCDJets");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(treename,"OtherJets");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);
  char cutstring[100];
  if(opts.getBoolVal("highJetThreshold")) sprintf(cutstring,"(pfmt>20) && (%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsHi":"nExclPFJetsHi",
                                                  njets, opts.getBoolVal("fitCaloJets")?"nExclJetsHi":"nExclPFJetsHi", njets);
  else sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsLo":"nExclPFJetsLo",
               njets, opts.getBoolVal("fitCaloJets")?"nExclJetsLo":"nExclPFJetsLo", njets);
  
  std::cout << "===> Reducing data with cut: " << cutstring << " <===" << std::endl;
  data = (RooDataSet *)data->reduce(cutstring);

  // use event weights
  if(opts.getBoolVal("weightedDataset")) data->setWeightVar("weight");

  data->Print("V");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");

  // Initialize the fit...
  char configfilename[200];
  if(opts.getBoolVal("AllFit")) sprintf(configfilename,"fitres/fitMinimumW-New-%s-thr%d.config",jetflavour,ithr);
  if(opts.getBoolVal("WOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-Wonly-New-%s-thr%d.config",jetflavour,ithr);
  if(opts.getBoolVal("QCDOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-QCDonly-New-%s-thr%d.config",jetflavour,ithr);
  if(opts.getBoolVal("otherOnlyFit")) sprintf(configfilename, "shapesWenu/config/fitMinimum-otheronly-New-%s-thr%d.config",jetflavour,ithr);
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
      pt1.AddText("CMS Preliminary 2010, #sqrt{s}=7 TeV, L_{int}=2.88 pb^{-1}");
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
    if(opts.getBoolVal("QCDOnlyFit")) {
      sprintf(epsfilename,"shapesWenu/eps/PfMt-QCDonly-%d%s-thr%d.eps",njets,jetflavour,ithr);
      sprintf(Cfilename,"shapesWenu/macro/PfMt-QCDonly-%d%s-thr%d.C",njets,jetflavour,ithr);
    }
    if(opts.getBoolVal("otherOnlyFit")) {
      sprintf(epsfilename,"shapesWenu/eps/PfMt-otheronly-%d%s-thr%d.eps",njets,jetflavour,ithr);
      sprintf(Cfilename,"shapesWenu/macro/PfMt-otheronly-%d%s-thr%d.C",njets,jetflavour,ithr);
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
  theData->plotOn(plot, RooFit::DataError(RooAbsData::SumW2), RooFit::Cut(cutstring));

//   if(opts.getBoolVal("AllFit")) {
//     // === plot (dashed) the qcd component ===
//     MLFit theFit2;

//     // define the structure of the dataset
//     RooRealVar* PfMt = new RooRealVar("pfmt",  "M_{T}" , 0., 150., "GeV/c^{2}");
//     //    RooRealVar *sinMHTphiJet = new RooRealVar("sinMHTphiJet","sinMHTphiJet",-0.80, 0.80);

//     theFit2.AddFlatFileColumn(PfMt);
//     //    theFit2.AddFlatFileColumn(sinMHTphiJet);

//     // define a fit model
//     theFit2.addModel("qcdFit", "qcd Fit");
//     theFit2.addSpecies("qcdFit", "qcd", "qcd Bkg Component");
//     theFit2.addSpecies("qcdFit", "other", "other Bkg Component");
//     if(njets==0) {
//       theFit2.addPdfWName("qcdFit", "qcd",   "pfmt", "Cruijff", "qcd_PfMt");
//       theFit2.addPdfWName("qcdFit", "other", "pfmt", "Cruijff",  "other_PfMt");
//     } else {
//       theFit2.addPdfWName("qcdFit", "qcd",  "pfmt", "DoubleGaussian",  "qcd_PfMt");
//       theFit2.addPdfWName("qcdFit", "other", "pfmt", "DoubleCruijff", "other_PfMt");
//     }

//     RooAbsPdf *myPdf2 = theFit2.buildModel("qcdFit");
//     theFit2.initialize(configfilename);

//     myPdf2->plotOn(plot, RooFit::Normalization((Nqcd+Nother)/fabs(Ns+Nother+Nqcd)), RooFit::DrawOption("F"), RooFit::FillColor(kViolet), RooFit::MoveToBack(), RooFit::Slice(*jets) );
//     myPdf2->plotOn(plot, RooFit::Normalization((Nqcd+Nother)/fabs(Ns+Nother+Nqcd)), RooFit::LineColor(kViolet+3), RooFit::LineWidth(2), RooFit::Slice(*jets) );

//     // === plot (dashed) the bkg component ===
//     MLFit theFit3;

//     theFit3.AddFlatFileColumn(PfMt);
//     //    theFit3.AddFlatFileColumn(sinMHTphiJet);

//     // define a fit model
//     theFit3.addModel("otherFit", "other Fit");
//     theFit3.addSpecies("otherFit", "other", "other Bkg Component");
//     if(njets==0) {
//       theFit3.addPdfWName("otherFit", "other", "pfmt", "Cruijff",  "other_PfMt");
//     } else {
//       theFit3.addPdfWName("otherFit", "other", "pfmt", "DoubleCruijff", "other_PfMt");
//     }
//     //    theFit3.addPdfWName("otherFit", "other", "sinMHTphiJet",  "Cruijff",         "other_sinMHTphiJet");

//     RooAbsPdf *myPdf3 = theFit3.buildModel("otherFit");
//     theFit3.initialize(configfilename);

//     myPdf3->plotOn(plot, RooFit::Normalization(Nother/fabs(Ns+Nother+Nqcd)), RooFit::DrawOption("F"), RooFit::FillColor(kOrange+8), RooFit::LineWidth(2), RooFit::Slice(*jets));
//     myPdf3->plotOn(plot, RooFit::Normalization(Nother/fabs(Ns+Nother+Nqcd)), RooFit::LineColor(kOrange+4), RooFit::LineWidth(2), RooFit::Slice(*jets));
  
//   }

  // plot the total likelihood
  RooAbsPdf *thePdf = theFit->getPdf("myFit");
  thePdf->plotOn(plot, RooFit::DrawOption("F"), RooFit::LineColor(kOrange+4), RooFit::FillColor(kOrange), RooFit::LineWidth(2), RooFit::MoveToBack(), RooFit::Slice(*jets) );
  thePdf->plotOn(plot, RooFit::DrawOption("L"), RooFit::LineColor(kOrange+7), RooFit::LineWidth(2), RooFit::Slice(*jets) );

//   char speclabel[50];
//   sprintf(speclabel,"myFit_qcd%dj,myFit_other%dj",njets);
//   thePdf->plotOn(plot, RooFit::Components(speclabel), RooFit::DrawOption("F"), RooFit::FillColor(kViolet), RooFit::MoveToBack(), RooFit::Slice(*jets) );
//   thePdf->plotOn(plot, RooFit::Components(speclabel), RooFit::LineColor(kViolet+3), RooFit::LineWidth(2), RooFit::Slice(*jets) );       

//   sprintf(speclabel,"myFit_other%dj",njets);
//   thePdf->plotOn(plot, RooFit::Components(speclabel), RooFit::DrawOption("F"), RooFit::FillColor(kOrange+8), RooFit::LineWidth(2), RooFit::Slice(*jets));
//   thePdf->plotOn(plot, RooFit::Components(speclabel), RooFit::LineColor(kOrange+4), RooFit::LineWidth(2), RooFit::Slice(*jets));

  return plot;
}

void makeLegend() {
  // Legend
  TH1F *dataH = new TH1F("dataH","dataH",50,0,150);
  TH1F *totalH = new TH1F("totalH","totalH",50,0,150);
  TH1F *otherPlusQCDH = new TH1F("otherPlusQcdH","otherPlusQcdH",50,0,150);
  TH1F *qcdH = new TH1F("qcdH","qcdH",50,0,150);

  dataH->SetMarkerColor(kBlack);
  totalH->SetFillColor(kOrange);
  otherPlusQcdH->SetFillColor(kViolet);
  qcdH->SetFillColor(kOrange+8);

  TLegendEntry *legge;
  TLegend *leg;
  leg = new TLegend(0.6,0.65,0.93,0.8);
  leg->SetFillStyle(0); leg->SetBorderSize(0.); leg->SetTextSize(0.025);
  leg->SetFillColor(0);
  legge = leg->AddEntry(dataH,"Data", "lpe");
  legge = leg->AddEntry(totalH,"total","f");
  legge = leg->AddEntry(otherPlusQcdH,"EWK+QCD","f");
  legge = leg->AddEntry(qcdH,"EWK","f");
  leg->Draw();
  gPad->Update();
}
