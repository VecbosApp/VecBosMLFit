// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("fitCaloJets",     "Fit calojets, trackjets otherwise", kTRUE);
  opts.addBoolOption("weightedDataset", "use event weight instead of 1",     kTRUE);
  opts.addBoolOption("useMass",         "Use Invariant Mass",     kFALSE);        
  opts.addBoolOption("useMHTphiMET",    "Use sin(MHTphiMET)",     kTRUE);
  opts.addBoolOption("AllFit",          "Fit all species",        kFALSE);
  opts.addBoolOption("ZOnlyFit",        "Fit Z species only",     kTRUE);
  opts.addBoolOption("bkgOnlyFit",      "Fit bkg species only",   kFALSE);

  return opts;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

MLFit theFit;

void myFit() {

  MLFit theFit;

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // define the structure of the dataset
  RooRealVar* mass = new RooRealVar("mass",  "Mass [GeV/c^{2}]" , 60., 110.);
  RooRealVar* sinMHTphiMET = new RooRealVar("sinMHTphiMET", "sin #phi_{MHT-MET}",-0.85,0.85);
  RooRealVar* weight = new RooRealVar("weight", "weight",1);

  theFit.AddFlatFileColumn(mass);
  theFit.AddFlatFileColumn(sinMHTphiMET);
  theFit.AddFlatFileColumn(weight);

  // define a fit model
  theFit.addModel("myFit", "Ratio ZtoEE");
  
  // define species
  theFit.addSpecies("myFit", "sig", "Signal Component");
  theFit.addSpecies("myFit", "bkg", "Bkg Component");
  
  // mLL PDF
  if(opts.getBoolVal("useMass")) {
    theFit.addPdfWName("myFit", "sig" , "mass",  "Cruijff", "sig_Mass");
    theFit.addPdfWName("myFit", "bkg" , "mass",  "Poly2",   "bkg_Mass");
  }
  // shape variable
  if(opts.getBoolVal("useMHTphiMET")) {
    theFit.addPdfWName("myFit", "sig" , "sinMHTphiMET",  "Cruijff", "sig_sinMHTphiMET");
    theFit.addPdfWName("myFit", "bkg" , "sinMHTphiMET",  "Poly2",   "bkg_sinMHTphiMET");
  }
  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fit a sample of Z events
void FitZElectrons(int njets) {
  
  myFit();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojet");
  else sprintf(jetflavour, "trackjet");

  // Load the data
  char datasetname[200];
  if(opts.getBoolVal("AllFit")) sprintf(datasetname,"datasets/zee_21X_data_%d%s.root",njets,jetflavour);
  else sprintf(datasetname,"datasets/zee_21X-%d%s.root",njets,jetflavour);
  char treename[100];
  if(opts.getBoolVal("AllFit")) sprintf(treename,"data");
  if(opts.getBoolVal("ZOnlyFit")) sprintf(treename,"ZjetsMADGRAPH");
  if(opts.getBoolVal("bkgOnlyFit")) sprintf(treename,"other");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);
  if(opts.getBoolVal("ZOnlyFit")) data = (RooDataSet*)data->reduce("ZToEEDecay==1");

  // use event weights
  if(opts.getBoolVal("weightedDataset")) data->setWeightVar("weight");

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  
  // Initialize the fit...
  if(opts.getBoolVal("AllFit")) {
    char initconfigfile[200];
    sprintf(initconfigfile,"fitconfig/fitZ-%d%s.config",njets,jetflavour);
    theFit.initialize(initconfigfile);
  }
  if(opts.getBoolVal("ZOnlyFit")) theFit.initialize("shapesZee/config/RatioElectrons-ZjetsFit-Zonly.config");
  if(opts.getBoolVal("bkgOnlyFit")) theFit.initialize("shapesZee/config/RatioElectrons-ZjetsFit-bkgonly.config");
  
  // Print Fit configuration 
  myPdf->getParameters(data)->selectByAttrib("Constant",kTRUE)->Print("V");  
  myPdf->getParameters(data)->selectByAttrib("Constant",kFALSE)->Print("V");

  // do one fit for each Mt bin
  float xbins[10];
  xbins[0] = 60;
  xbins[1] = 80;
  xbins[2] = 88;
  xbins[3] = 92;
  xbins[4] = 110;

  TGraphErrors *gr_sinMHTphiMETSigmaL = new TGraphErrors(4);
  TGraphErrors *gr_sinMHTphiMETSigmaR = new TGraphErrors(4);
  TGraphErrors *gr_sinMHTphiMETMean = new TGraphErrors(4);

  for(int bin=1; bin<5; bin++) {

    float xmin=xbins[bin-1];
    float xmax=xbins[bin];

    cout << "FITTING SIN PHI (MHT-MET) IN THE RANGE: " << xmin << " < Mass < " << xmax << endl;

    char cut[200];
    sprintf(cut,"mass>%f && mass<%f",xmin,xmax);
    RooDataSet *slicedata = (RooDataSet*)data->reduce(cut);
  
    RooFitResult *fitres =  myPdf->fitTo(*slicedata,theFit.getNoNormVars("myFit"),"MHTER");
    fitres->Print("V");
  
    float xmed = (xmax+xmin)/2.;
    float ex = (xmax-xmin)/2.;

    RooArgList floatingList = fitres->floatParsFinal();
    RooRealVar *sigmaL = (RooRealVar*)floatingList.find("sig_sinMHTphiMET_sigmaL");
    RooRealVar *sigmaR = (RooRealVar*)floatingList.find("sig_sinMHTphiMET_sigmaR");
    RooRealVar *mean = (RooRealVar*)floatingList.find("sig_sinMHTphiMET_mean");

    float sigmaL_val = sigmaL->getVal();
    float sigmaL_err = sigmaL->getError();
    float sigmaR_val = sigmaR->getVal();
    float sigmaR_err = sigmaR->getError();
    float mean_val = mean->getVal();
    float mean_err = mean->getError();

    gr_sinMHTphiMETSigmaL->SetPoint(bin-1,xmed,sigmaL_val);
    gr_sinMHTphiMETSigmaL->SetPointError(bin-1,ex,sigmaL_err);

    gr_sinMHTphiMETSigmaR->SetPoint(bin-1,xmed,sigmaR_val);
    gr_sinMHTphiMETSigmaR->SetPointError(bin-1,ex,sigmaR_err);
    
    gr_sinMHTphiMETMean->SetPoint(bin-1,xmed,mean_val);
    gr_sinMHTphiMETMean->SetPointError(bin-1,ex,mean_err);

  }

  TCanvas *cmean = new TCanvas("cmean","sin(MHTphiMET) mean");
  gr_sinMHTphiMETMean->GetXaxis()->SetTitle("M_{T} [GeV/c^{2}]");  
  gr_sinMHTphiMETMean->GetYaxis()->SetTitle("mean of sin(#phi_{MHT-Jet})");  
  gr_sinMHTphiMETMean->Draw("ap");

  char mea[200];
  sprintf(mea,"sinMHTphiMET_mean_%d%s.C",njets,jetflavour);
  cmean->SaveAs(mea);
  
  TCanvas *cres = new TCanvas("cres","sin(MHTphiMET) resolution");
  gr_sinMHTphiMETSigmaL->SetMarkerColor(2);
  gr_sinMHTphiMETSigmaL->SetLineColor(2);
  gr_sinMHTphiMETSigmaR->SetMarkerColor(4);
  gr_sinMHTphiMETSigmaR->SetLineColor(4);
  gr_sinMHTphiMETSigmaL->GetXaxis()->SetTitle("M_{T} [GeV/c^{2}]");
  gr_sinMHTphiMETSigmaL->GetYaxis()->SetTitle("resolution of sin(#phi_{MHT-Jet})");

  gr_sinMHTphiMETSigmaL->Draw("ap");
  gr_sinMHTphiMETSigmaR->Draw("p");

  TLegend *leg = new TLegend(0.11,0.65,0.45,0.89);
  leg->SetBorderSize(0);
  leg->SetLineColor(0);
  leg->SetFillColor(0);
  leg->AddEntry(gr_sinMHTphiMETSigmaL,"#sigma_{L}","p");
  leg->AddEntry(gr_sinMHTphiMETSigmaR,"#sigma_{R}","p");
  leg->Draw();

  char res[200];
  sprintf(res,"sinMHTphiMET_sigma_%d%s.C",njets,jetflavour);
  cres->SaveAs(res);

}
