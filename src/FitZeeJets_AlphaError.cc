// Set Fit Options
MLOptions GetDefaultOptions() {

  MLOptions opts;

  opts.addBoolOption("fitCaloJets",      "Fit calojets, PF jets otherwise", kFALSE);
  opts.addBoolOption("highThreshold",    "Use high threshold jets",         kTRUE);  
  opts.addBoolOption("weightedDataset",  "Use event weight instead of 1",   kFALSE);
  opts.addBoolOption("fitRatio",         "FitRatio directly",               kFALSE);
  opts.addBoolOption("fitInclusive",     "Fit inclusive W+jets multiplicity", kTRUE);
  opts.addBoolOption("AllFit",           "Fit all species",                 kTRUE);
  opts.addBoolOption("ZOnlyFit",         "Fit Z species only",              kFALSE);
  opts.addBoolOption("bkgOnlyFit",       "Fit bkg species only",            kFALSE);
  opts.addRealOption("njetmin",          "Smallest jet number to consider", 1);
  opts.addRealOption("njetmax",          "Largest jet number to consider",  4);
  
  return opts;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

MLFit theFit;

void myFit() {

  MLFit theFit;

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // define the structure of the dataset
  RooRealVar* mass   = new RooRealVar("mee",    "Mass [GeV/c^{2}]" , 60., 110.);//XXX cahnge back!
  RooRealVar* weight = new RooRealVar("weight", "weight",1);
  RooRealVar* njets;
  if(opts.getBoolVal("fitCaloJets")){ 
    if(opts.getBoolVal("highThreshold")) njets = new RooRealVar("nExclJetsHi", "nExclJetsHi",0.5, 20.5); 
    else njets = new RooRealVar("nExclJetsLo", "nExclJetsLo",0.5, 20.5);
  }
  else {
    if(opts.getBoolVal("highThreshold")) njets = new RooRealVar("nExclPFJetsHi", "nExclPFJetsHi",0.5, 20.5);
    else njets = new RooRealVar("nExclPFJetsLo", "nExclPFJetsLo",0.5, 20.5);
  }
  theFit.AddFlatFileColumn(mass);
  theFit.AddFlatFileColumn(weight);
  theFit.AddFlatFileColumn(njets);

  // define a fit model
  theFit.addModel("myFit", "Ratio ZtoEE");

  // define species
  MLStrList speclist;
  for(int nj = opts.getRealVal("njetmin"); nj <=opts.getRealVal("njetmax"); nj++){

    // signal
    char speclabel[50],specdesc[200];
    sprintf(speclabel,"Z%dj",nj);
    sprintf(specdesc,"Signal %dj Component",nj);
    theFit.addSpecies("myFit", speclabel, specdesc);
    speclist.Add(speclabel);

    // background
    sprintf(speclabel,"B%dj",nj);
    sprintf(specdesc,"Background %dj Component",nj);
    theFit.addSpecies("myFit", speclabel, specdesc);
  }
  
  if(opts.getBoolVal("fitRatio")) {
    cout << "===> FITTING BERENDS-GIELE SCALING <===" << endl;
    theFit.fitInclusiveRatio(speclist, "Zincl", opts.getRealVal("njetmin"));
  } else if(opts.getBoolVal("fitInclusive")) {
    cout << "===> FITTING INCLUSIVE Z+JETS MULTIPLICITIES <===" << endl;
    theFit.fitInclusive(speclist,"Zincl",opts.getRealVal("njetmin")); 
  } else {
    cout << "===> FITTING EXCLUSIVE Z+JETS MULTIPLICITIES <===" << endl;
  }

  char jetlabel[200];
  if(opts.getBoolVal("fitCaloJets")){ 
    if(opts.getBoolVal("highThreshold")) sprintf(jetlabel,"nExclJetsHi");
    else sprintf(jetlabel,"nExclJetsLo");
  }
  else {
    if(opts.getBoolVal("highThreshold")) sprintf(jetlabel,"nExclPFJetsHi");
    else sprintf(jetlabel,"nExclPFJetsLo");
  }
  
    
  // PDFs
  char speclabel[50],pdfname[200],specfirst[50];
  bool first=true;
  for(int nj = opts.getRealVal("njetmin"); nj <=opts.getRealVal("njetmax"); nj++){

    // signal mll 
    sprintf(speclabel,"Z%dj",nj);
    if(first){
      theFit.addPdfWName("myFit", speclabel , "mee",  "Cruijff", "sig_Mass");
      first = false;
      strcpy(specfirst,speclabel);
    }
    else{
      theFit.addPdfCopy("myFit",speclabel , "mee", specfirst);
    }

    // background mll
    sprintf(speclabel,"B%dj",nj);
    sprintf(pdfname,"bkg_Mass%dj",nj);   
    theFit.addPdfWName("myFit",speclabel  , "mee",  "Poly2",   pdfname);

    // jet category   
    sprintf(speclabel,"Z%dj",nj);
    sprintf(pdfname,"%dj",nj);
    theFit.addPdfWName("myFit",speclabel , jetlabel, "ExclJet", pdfname);

    sprintf(speclabel,"B%dj",nj);
    sprintf(pdfname,"%dj",nj);
    theFit.addPdfWName("myFit",speclabel , jetlabel, "ExclJet", pdfname);
  }
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fit a sample of Z events
void FitZElectrons() {
  
  myFit();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "PFjet");

  int ithr;
  if(opts.getBoolVal("highThreshold")) ithr=0;
  else ithr=1;

  // load the data
  char datasetname[200];
  if(opts.getBoolVal("AllFit")) sprintf(datasetname,"results_data/datasets/zee.root");
  else sprintf(datasetname,"results/datasets/zee.root");

  char treename[100];
  if(opts.getBoolVal("AllFit"))     sprintf(treename,"T1");
  if(opts.getBoolVal("ZOnlyFit"))   sprintf(treename,"ZJets");
  if(opts.getBoolVal("bkgOnlyFit")) sprintf(treename,"BkgJets");  

  char cutstring[100];

  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *totdata = theFit.getDataSet(treename);
  char cutstring[100];
  if(opts.getBoolVal("highThreshold")) sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsHi":"nExclPFJetsHi",opts.getRealVal("njetmin") ,opts.getBoolVal("fitCaloJets")?"nExclJetsHi":"nExclPFJetsHi" , opts.getRealVal("njetmax"));
  else sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsLo":"nExclPFJetsLo",opts.getRealVal("njetmin") ,opts.getBoolVal("fitCaloJets")?"nExclJetsLo":"nExclPFJetsLo" , opts.getRealVal("njetmax"));
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
    sprintf(initconfigfile,"fitconfig/fitZ-AlphaErr-%s-thr%d.config",jetflavour,ithr);
    theFit.initialize(initconfigfile);
  }
  if(opts.getBoolVal("ZOnlyFit"))   theFit.initialize("shapesZee/config/RatioElectrons-ZjetsFit-Zonly-New.config");
  if(opts.getBoolVal("bkgOnlyFit")) theFit.initialize("shapesZee/config/RatioElectrons-ZjetsFit-bkgonly-New.config");

  
  // Print Fit configuration 
  myPdf->getParameters(data)->selectByAttrib("Constant",kTRUE)->Print("V");  
  myPdf->getParameters(data)->selectByAttrib("Constant",kFALSE)->Print("V");

  //Gaussian constraint PDFs for alphaL
  RooRealVar alphaLMean("alphaLMean"," mean alpha L ",theFit.getRealPar("sig_Mass_alphaL")->getVal());
  RooRealVar alphaLSigma("alphaLSigma"," sigma alpha L ",theFit.getRealPar("sig_Mass_alphaL")->getError());
  RooGaussian* alphaLDist = new RooGaussian("alphaLDist","alphaLDist",*(theFit.getRealPar("sig_Mass_alphaL")),alphaLMean,alphaLSigma);
  
  RooFitResult *fitres;
  if(opts.getBoolVal("weightedDataset")) fitres =  myPdf->fitTo(*data,RooFit::ConditionalObservables(theFit.getNoNormVars("myFit")),RooFit::FitOptions("MHTER"),RooFit::SumW2Error(kTRUE),RooFit::NumCPU(4),RooFit::Timer(kTRUE),RooFit::ExternalConstraints(RooArgSet(*alphaRDist,*alphaLDist)));
  else fitres =  myPdf->fitTo(*data,RooFit::ConditionalObservables(theFit.getNoNormVars("myFit")),RooFit::FitOptions("MHTER"),RooFit::NumCPU(4),RooFit::Timer(kTRUE),RooFit::ExternalConstraints(RooArgSet(*alphaLDist)));
  fitres->Print("V");
  
  
  // write the config file corresponding to the fit minimum
  char configfilename[200];
  if(opts.getBoolVal("AllFit"))   sprintf(configfilename, "fitres/fitMinimumZ-New-%s-thr%d.config",jetflavour,ithr);
  if(opts.getBoolVal("ZOnlyFit")) sprintf(configfilename, "shapesZee/config/fitMinimum-Zonly-New-%s-thr%d.config",jetflavour,ithr);
  if(opts.getBoolVal("bkgOnlyFit")) sprintf(configfilename, "shapesZee/config/fitMinimum-bkgonly-New-%s-thr%d.config",jetflavour,ithr);
  theFit.writeConfigFile(configfilename);  

  // save the fit result in ROOT 
  char rootfilename[200];
  if(opts.getBoolVal("AllFit"))     sprintf(rootfilename,"fitres/fitMinimumZ-New-%s-thr%d.root",jetflavour,ithr);
  if(opts.getBoolVal("ZOnlyFit"))   sprintf(rootfilename,"shapesZee/root/fitRes-Zonly-New-%s-thr%d.root",jetflavour,ithr);
  if(opts.getBoolVal("bkgOnlyFit")) sprintf(rootfilename,"shapesZee/root/fitRes-bkgonly-New-%s-thr%d.root",jetflavour,ithr);

  TFile *file = new TFile(rootfilename,"recreate");
  fitres->Write();
  file->Close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotZElectrons(int njets, int ithr, int nbins) {

  myFit();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "PFjet");

  // Load the data
  char datasetname[200];
  if(opts.getBoolVal("AllFit")) sprintf(datasetname,"results_data/datasets/zee.root");
  else sprintf(datasetname,"results/datasets/zee.root");  

  char treename[100];
  if(opts.getBoolVal("AllFit"))     sprintf(treename,"T1");
  if(opts.getBoolVal("ZOnlyFit"))   sprintf(treename,"ZJets");
  if(opts.getBoolVal("bkgOnlyFit")) sprintf(treename,"BkgJets");  

  char cutstring[100];
  theFit.addDataSetFromRootFile(treename, treename, datasetname);

  RooDataSet *data = theFit.getDataSet(treename);
  char cutstring[100];

//   if(opts.getBoolVal("highThreshold")) sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsHi":"nExclPFJetsHi",njets, opts.getBoolVal("fitCaloJets")?"nExclJetsHi":"nExclPFJetsHi", njets);
//   else sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsLo":"nExclPFJetsLo",njets, opts.getBoolVal("fitCaloJets")?"nExclJetsLo":"nExclPFJetsLo", njets);
  if(opts.getBoolVal("highThreshold")) sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsHi":"nExclPFJetsHi",opts.getRealVal("njetmin"), opts.getBoolVal("fitCaloJets")?"nExclJetsHi":"nExclPFJetsHi", opts.getRealVal("njetmax"));
  else sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsLo":"nExclPFJetsLo",opts.getRealVal("njetmin"), opts.getBoolVal("fitCaloJets")?"nExclJetsLo":"nExclPFJetsLo", opts.getRealVal("njetmax"));
  
  std::cout << "===> Reducing data with cut: " << cutstring << " <===" << std::endl;
  data = (RooDataSet *)data->reduce(cutstring);
  
  // use event weights
  if(opts.getBoolVal("weightedDataset")) data->setWeightVar("weight");
  
  data->Print("V");
  
  
  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");

  // Initialize the fit...
  char configfilename[200];
  if(opts.getBoolVal("AllFit"))     sprintf(configfilename, "fitres/fitMinimumZ-New-%s-thr%d.config",jetflavour,ithr);
  if(opts.getBoolVal("ZOnlyFit"))   sprintf(configfilename, "shapesZee/config/fitMinimum-Zonly-New-%s-thr%d.config",jetflavour,ithr);
  if(opts.getBoolVal("bkgOnlyFit")) sprintf(configfilename, "shapesZee/config/fitMinimum-bkgonly-New-%s-thr%d.config",jetflavour,ithr);
  theFit.initialize(configfilename);

  TCanvas *c = new TCanvas("c","fitResult");
  RooPlot* MassPlot = MakePlot("mee", njets, &theFit, data, configfilename, nbins);    
  
  MassPlot->SetAxisColor(1,"x");
  MassPlot->SetLabelColor(1, "X");
  MassPlot->SetLabelColor(1, "Y");
  MassPlot->SetXTitle("M_{ee}[GeV/c^{2}]");

  char binsize[50];
  Double_t binW = MassPlot->getFitRangeBinW();
  sprintf(binsize,"%2.0f",binW);

  MassPlot->SetYTitle(TString("Events / (")+TString(binsize)+TString(" GeV/c^{2})"));
  MassPlot->Draw();
  
  makeLegend();
  
  TPaveText pt1(0.1,0.96,0.8,0.98,"NDC");
  pt1.SetTextFont(72);
  pt1.SetTextSize(0.03);
  pt1.SetTextAlign(12);
  pt1.SetFillColor(0);
  pt1.SetBorderSize(0);
  pt1.AddText("CMS Preliminary 2010, #sqrt{s}=7 TeV, L_{int}=35. pb^{-1}");
  pt1.Draw();
 
  char epsfilename[200];
  char Cfilename[200];

  if(opts.getBoolVal("AllFit")) {
    sprintf(epsfilename,"fit-plots/eps/Mass-data-%d%s-thr%d.eps",njets,jetflavour,ithr);
    sprintf(Cfilename,"fit-plots/macro/Mass-data-%d%s-thr%d.C",njets,jetflavour,ithr);
  }
  if(opts.getBoolVal("ZOnlyFit")) {
    sprintf(epsfilename,"shapesZee/eps/Mass-Zonly-%d%s-thr%d.eps",njets,jetflavour,ithr);
    sprintf(Cfilename,"shapesZee/macro/Mass-Zonly-%d%s-thr%d.C",njets,jetflavour,ithr);
  }
  if(opts.getBoolVal("bkgOnlyFit")) {
    sprintf(epsfilename,"shapesZee/eps/Mass-bkgonly-%d%s-thr%d.eps",njets,jetflavour,ithr);
    sprintf(Cfilename,"shapesZee/macro/Mass-bkgonly-%d%s-thr%d.C",njets,jetflavour,ithr);
  }
  c->SaveAs(epsfilename);
  c->SaveAs(Cfilename);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Make the plot for a given variable
RooPlot *MakePlot(TString VarName, int njets, MLFit* theFit, RooDataSet* theData, const char *configfilename, int nbins)
{
  // Various fit options...
  MLOptions opts = GetDefaultOptions();
  
  RooRealVar* Var = theFit->RealObservable(VarName);
  RooRealVar* jets;
  if(opts.getBoolVal("highThreshold")) {
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
//   if(opts.getBoolVal("highThreshold")) sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsHi":"nExclPFJetsHi",opts.getRealVal("njetmin") ,opts.getBoolVal("fitCaloJets")?"nExclJetsHi":"nExclPFJetsHi" , opts.getRealVal("njetmax"));
//   else sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsLo":"nExclPFJetsLo",opts.getRealVal("njetmin") ,opts.getBoolVal("fitCaloJets")?"nExclJetsLo":"nExclPFJetsLo" , opts.getRealVal("njetmax"));
  if(opts.getBoolVal("highThreshold")) sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsHi":"nExclPFJetsHi",njets,opts.getBoolVal("fitCaloJets")?"nExclJetsHi":"nExclPFJetsHi" , njets);
  else sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nExlcJetsLo":"nExclPFJetsLo",njets ,opts.getBoolVal("fitCaloJets")?"nExclJetsLo":"nExclPFJetsLo" ,njets);
  std::cout << "===> Reducing data with cut: " << cutstring << " <===" << std::endl;
  
  // plot the data
  theData->plotOn(plot, RooFit::DataError(RooAbsData::SumW2), RooFit::Cut(cutstring));
  
  jets->Print("v");
  jets->setValueDirty();

  // plot the total likelihood
  RooAbsPdf *thePdf = theFit->getPdf("myFit");


  // to make the plot to data
  thePdf->plotOn(plot, RooFit::DrawOption("F"), RooFit::LineColor(kOrange+4), RooFit::FillColor(kOrange), RooFit::LineWidth(2), RooFit::MoveToBack(), RooFit::Slice(*jets), RooFit::MoveToBack() );
  thePdf->plotOn(plot, RooFit::DrawOption("L"), RooFit::LineColor(kOrange+7), RooFit::LineWidth(2), RooFit::Slice(*jets) );
  char speclabel[50];
  sprintf(speclabel,"myFit_B%dj",njets);
  thePdf->plotOn(plot, RooFit::Components(speclabel), RooFit::DrawOption("F"), RooFit::FillColor(kViolet), RooFit::Slice(*jets) );
  thePdf->plotOn(plot, RooFit::Components(speclabel), RooFit::LineColor(kViolet+3), RooFit::LineWidth(2), RooFit::Slice(*jets) );       

  // to plot pdfs
  // thePdf->plotOn(plot, RooFit::DrawOption("F"), RooFit::FillColor(kViolet), RooFit::LineWidth(2), RooFit::MoveToBack(), RooFit::Slice(*jets) );
  // thePdf->plotOn(plot, RooFit::DrawOption("L"), RooFit::LineColor(kViolet+3), RooFit::LineWidth(2), RooFit::Slice(*jets) );
  theData->plotOn(plot, RooFit::DataError(RooAbsData::SumW2), RooFit::Cut(cutstring));
  return plot;
}


void makeLegend() {
  // Legend
  TH1F *dataH  = new TH1F("dataH","dataH",50,0,150);
  TH1F *totalH = new TH1F("totalH","totalH",50,0,150);
  TH1F *qcdH   = new TH1F("qcdH","qcdH",50,0,150);

  dataH ->SetMarkerColor(kBlack);
  totalH->SetFillColor(kOrange);
  qcdH  ->SetFillColor(kViolet);

  TLegendEntry *legge;
  TLegend *leg;
  leg = new TLegend(0.2,0.65,0.53,0.8);
  leg->SetFillStyle(0); leg->SetBorderSize(0.); leg->SetTextSize(0.025);
  leg->SetFillColor(0);
  legge = leg->AddEntry(dataH, "Data", "lpe");
  legge = leg->AddEntry(totalH,"total","f");
  legge = leg->AddEntry(qcdH,  "bkg only","f");
  // leg->Draw();
  gPad->Update();
}
