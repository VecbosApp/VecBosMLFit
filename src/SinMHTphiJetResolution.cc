// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("fitCaloJets",     "Fit calojets, trackjets otherwise", kTRUE);
  opts.addBoolOption("weightedDataset", "use event weight instead of 1",     kFALSE);
  opts.addBoolOption("useMt",           "Use W Transverse Mass",  kFALSE);
  opts.addBoolOption("useMHTphiJet",    "Use MHTphiJet",          kTRUE);
  opts.addBoolOption("AllFit",          "Fit all species",        kFALSE);
  opts.addBoolOption("WOnlyFit",        "Fit W species only",     kTRUE);
  opts.addBoolOption("ttbarOnlyFit",    "Fit ttbar species only", kFALSE);
  opts.addBoolOption("otherOnlyFit",    "Fit other species only", kFALSE);

  return opts;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

MLFit theFit;

void myFit() {

  MLFit theFit;

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  opts.addBoolOption("useBVeto",   "Use Optimized B Veto Rectangular Cut", kTRUE);
  
  // define the structure of the dataset
  RooRealVar* Mt = new RooRealVar("Mt",  "Transverse W Mass [GeV/c^{2}]" , 30., 250.);
  RooRealVar *sinMHTphiJet = new RooRealVar("sinMHTphiJet","sinMHTphiJet",-0.80, 0.80);
  RooRealVar* bvetoCat = new RooRealVar("BVetoCat", "BVetoCat",-1,1);
  RooRealVar* weight = new RooRealVar("weight", "weight",1);

  theFit.AddFlatFileColumn(Mt);
  theFit.AddFlatFileColumn(sinMHTphiJet);
  theFit.AddFlatFileColumn(bvetoCat);
  theFit.AddFlatFileColumn(weight);

  // define a fit model
  theFit.addModel("myFit", "Ratio WtoENu");
  
  // define species accepted by b veto
  theFit.addSpecies("myFit", "sig_a",    "Accepted Signal Component");
  theFit.addSpecies("myFit", "ttbar_a",  "Accepted ttbar Component");
  theFit.addSpecies("myFit", "other_a",  "Accepted Other Bkgs Component");

  // define species rejected by b veto
  theFit.addSpecies("myFit", "sig_r",    "Rejected Signal Component");
  theFit.addSpecies("myFit", "ttbar_r",  "Rejected ttbar Component");
  theFit.addSpecies("myFit", "other_r",  "Rejected Other Bkgs Component");
  
  theFit.fitWithEff("sig_a", "sig_r", "sig");
  theFit.fitWithEff("ttbar_a", "ttbar_r", "ttbar");
  theFit.fitWithEff("other_a", "other_r", "other");

  // Mt PDF
  if(opts.getBoolVal("useMt")) {
    theFit.addPdfWName("myFit", "sig_a",   "Mt", "CrystalCruijff", "sig_Mt");
    theFit.addPdfWName("myFit", "ttbar_a", "Mt", "CrystalCruijff", "ttbar_Mt");
    theFit.addPdfWName("myFit", "other_a", "Mt", "CrystalCruijff", "other_Mt");

    theFit.addPdfCopy("myFit", "sig_r",   "Mt", "sig_a");
    theFit.addPdfCopy("myFit", "ttbar_r", "Mt", "ttbar_a");
    theFit.addPdfCopy("myFit", "other_r", "Mt", "other_a");
  }

  // sinMHTphiJet PDF
  if(opts.getBoolVal("useMHTphiJet")) {
    theFit.addPdfWName("myFit", "sig_a" ,   "sinMHTphiJet",  "Cruijff",  "sig_sinMHTphiJet");
    theFit.addPdfWName("myFit", "ttbar_a",  "sinMHTphiJet",  "Cruijff",  "ttbar_sinMHTphiJet");
    theFit.addPdfWName("myFit", "other_a",  "sinMHTphiJet",  "Cruijff",  "other_sinMHTphiJet");

    theFit.addPdfCopy("myFit", "sig_r" ,   "sinMHTphiJet",  "sig_a");
    theFit.addPdfCopy("myFit", "ttbar_r",  "sinMHTphiJet",  "ttbar_a");
    theFit.addPdfCopy("myFit", "other_r",  "sinMHTphiJet",  "other_a");
  }

  // b veto category
  theFit.addPdfWName("myFit", "sig_a" ,   "BVetoCat",  "Poly2",  "bveto_acc");
  theFit.addPdfCopy("myFit",  "ttbar_a",  "BVetoCat",  "sig_a");
  theFit.addPdfCopy("myFit",  "other_a",  "BVetoCat",  "sig_a");

  theFit.addPdfWName("myFit", "sig_r" ,   "BVetoCat",  "Poly2",  "bveto_rej");
  theFit.addPdfCopy("myFit",  "ttbar_r",  "BVetoCat",  "sig_r");
  theFit.addPdfCopy("myFit",  "other_r",  "BVetoCat",  "sig_r");

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fit a sample of Z events
void FitWElectrons(int njets) {
  
  myFit();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "trackjet");

  // Load the data
  char datasetname[200];
  if(opts.getBoolVal("AllFit")) sprintf(datasetname,"datasets/wenu_21X_data_%d%s.root",njets,jetflavour);
  else sprintf(datasetname,"datasets/wenu_21X-%d%s.root",njets,jetflavour);
  char treename[100];
  if(opts.getBoolVal("AllFit")) sprintf(treename,"data");
  if(opts.getBoolVal("WOnlyFit")) sprintf(treename,"WjetsMADGRAPH");
  if(opts.getBoolVal("ttbarOnlyFit")) sprintf(treename,"ttjetsMADGRAPH");
  if(opts.getBoolVal("otherOnlyFit")) sprintf(treename,"other");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);
  if(opts.getBoolVal("WOnlyFit")) data = (RooDataSet*)data->reduce("WToENuDecay==1");

  // use event weights
  if(opts.getBoolVal("weightedDataset")) data->setWeightVar("weight");

  // do one fit for each Mt bin
  float xbins[10];
  xbins[0] = 30;
  xbins[1] = 60;
  xbins[2] = 90;
  xbins[3] = 140;
  xbins[4] = 250;

  TGraphErrors *gr_sinMHTphiJetSigmaL = new TGraphErrors(4);
  TGraphErrors *gr_sinMHTphiJetSigmaR = new TGraphErrors(4);
  TGraphErrors *gr_sinMHTphiJetMean = new TGraphErrors(4);

  for(int bin=1; bin<5; bin++) {

    float xmin=xbins[bin-1];
    float xmax=xbins[bin];

    cout << "FITTING SIN PHI (MHT-JET) IN THE RANGE: " << xmin << " < Mt < " << xmax << endl;

    char cut[200];
    sprintf(cut,"Mt>%f && Mt<%f",xmin,xmax);
    RooDataSet *slicedata = (RooDataSet*)data->reduce(cut);

    // build the fit likelihood
    RooAbsPdf *myPdf = theFit.buildModel("myFit");
    
    // Initialize the fit...
    if(opts.getBoolVal("AllFit")) {
      char initconfigfile[200];
      sprintf(initconfigfile,"fitconfig/fitW-%d%s.config",njets,jetflavour);
      theFit.initialize(initconfigfile);
    }
    if(opts.getBoolVal("WOnlyFit")) theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-Wonly.config");
    if(opts.getBoolVal("ttbarOnlyFit")) theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-TTbaronly.config");
    if(opts.getBoolVal("otherOnlyFit")) theFit.initialize("shapesWenu/config/RatioElectrons-WjetsFit-otheronly.config");
    
    // Print Fit configuration 
    myPdf->getParameters(data)->selectByAttrib("Constant",kTRUE)->Print("V");  
    myPdf->getParameters(data)->selectByAttrib("Constant",kFALSE)->Print("V");
    
    RooFitResult *fitres =  myPdf->fitTo(*slicedata,theFit.getNoNormVars("myFit"),"MHTER");
    fitres->Print("V");

    float xmed = (xmax+xmin)/2.;
    float ex = (xmax-xmin)/2.;

    RooArgList floatingList = fitres->floatParsFinal();
    RooRealVar *sigmaL = (RooRealVar*)floatingList.find("sig_sinMHTphiJet_sigmaL");
    RooRealVar *sigmaR = (RooRealVar*)floatingList.find("sig_sinMHTphiJet_sigmaR");
    RooRealVar *mean = (RooRealVar*)floatingList.find("sig_sinMHTphiJet_mean");

    float sigmaL_val = sigmaL->getVal();
    float sigmaL_err = sigmaL->getError();
    float sigmaR_val = sigmaR->getVal();
    float sigmaR_err = sigmaR->getError();
    float mean_val = mean->getVal();
    float mean_err = mean->getError();

    gr_sinMHTphiJetSigmaL->SetPoint(bin-1,xmed,sigmaL_val);
    gr_sinMHTphiJetSigmaL->SetPointError(bin-1,ex,sigmaL_err);

    gr_sinMHTphiJetSigmaR->SetPoint(bin-1,xmed,sigmaR_val);
    gr_sinMHTphiJetSigmaR->SetPointError(bin-1,ex,sigmaR_err);
    
    gr_sinMHTphiJetMean->SetPoint(bin-1,xmed,mean_val);
    gr_sinMHTphiJetMean->SetPointError(bin-1,ex,mean_err);

  }


  TCanvas *cmean = new TCanvas("cmean","sin(MHTphiJet) mean");
  gr_sinMHTphiJetMean->GetXaxis()->SetTitle("M_{T} [GeV/c^{2}]");  
  gr_sinMHTphiJetMean->GetYaxis()->SetTitle("mean of sin(#phi_{MHT-Jet})");  
  gr_sinMHTphiJetMean->Draw("ap");

  char mea[200];
  sprintf(mea,"sinMHTphiJet_mean_%d%s.C",njets,jetflavour);
  cmean->SaveAs(mea);
  
  TCanvas *cres = new TCanvas("cres","sin(MHTphiJet) resolution");
  gr_sinMHTphiJetSigmaL->SetMarkerColor(2);
  gr_sinMHTphiJetSigmaL->SetLineColor(2);
  gr_sinMHTphiJetSigmaR->SetMarkerColor(4);
  gr_sinMHTphiJetSigmaR->SetLineColor(4);
  gr_sinMHTphiJetSigmaL->GetXaxis()->SetTitle("M_{T} [GeV/c^{2}]");
  gr_sinMHTphiJetSigmaL->GetYaxis()->SetTitle("resolution of sin(#phi_{MHT-Jet})");

  gr_sinMHTphiJetSigmaL->Draw("ap");
  gr_sinMHTphiJetSigmaR->Draw("p");

  TLegend *leg = new TLegend(0.11,0.65,0.45,0.89);
  leg->SetBorderSize(0);
  leg->SetLineColor(0);
  leg->SetFillColor(0);
  leg->AddEntry(gr_sinMHTphiJetSigmaL,"#sigma_{L}","p");
  leg->AddEntry(gr_sinMHTphiJetSigmaR,"#sigma_{R}","p");
  leg->Draw();

  char res[200];
  sprintf(res,"sinMHTphiJet_sigma_%d%s.C",njets,jetflavour);
  cres->SaveAs(res);


}
