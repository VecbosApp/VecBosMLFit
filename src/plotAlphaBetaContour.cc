#include "RooRealVar.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TPad.h"
#include "TH1F.h"

void plotAlphaBetaContour() {

  gROOT->SetStyle("Plain");

  TFile fileGenJets("fitsScaling/fitRes-Wonly-NewBJet-genjet-thr0.root");
  TFile filePFJets("fitsScaling/fitRes-Wonly-NewBJet-PFjet-thr0.root");
  TFile filePFJets_Data("fitsScaling/fitMinimumW-NewBJet-PFjet-thr0.root");

  RooFitResult *fitResGenJets = (RooFitResult*)fileGenJets.Get("nll_myFit_WJets");
  RooFitResult *fitResPFJets = (RooFitResult*)filePFJets.Get("nll_myFit_WJets");
  RooFitResult *fitResPFJets_Data = (RooFitResult*)filePFJets_Data.Get("nll_myFit_Data");

  fitResGenJets->Print();
  fitResPFJets->Print();
  fitResPFJets_Data->Print();

  RooRealVar* alpha_0 = (RooRealVar*)(fitResGenJets->floatParsFinal().find("alphaR_Wincl"));
  RooRealVar* beta_0 = (RooRealVar*)(fitResGenJets->floatParsFinal().find("betaR_Wincl"));

  RooRealVar* alpha_1 = (RooRealVar*)(fitResPFJets->floatParsFinal().find("alphaR_Wincl"));
  RooRealVar* beta_1 = (RooRealVar*)(fitResPFJets->floatParsFinal().find("betaR_Wincl"));

  RooRealVar* alpha_2 = (RooRealVar*)(fitResPFJets_Data->floatParsFinal().find("alphaR_Wincl"));
  RooRealVar* beta_2 = (RooRealVar*)(fitResPFJets_Data->floatParsFinal().find("betaR_Wincl"));

  TCanvas *c1 = new TCanvas("c1", "c1",526,283,599,599);
  gStyle->SetOptStat(0);
  c1->Range(0.5767711,3.676376,3.237012,6.279685);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetTickx();
  c1->SetTicky();
  c1->SetLeftMargin(0.1290323);
  c1->SetRightMargin(0.05429072);
  c1->SetTopMargin(0.02701948);
  c1->SetBottomMargin(0.08646233);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);

  RooPlot *plot = new RooPlot(*alpha_0,*beta_0,4.0,7.0,0,1);

  alpha_0->Print();
  beta_0->Print();

  fitResGenJets->plotOn(plot,*alpha_0,*beta_0,"ME12");
  plot->getAttLine("contour")->SetLineStyle(kDashed);
  plot->getAttLine("contour")->SetLineColor(kRed);
  fitResPFJets->plotOn(plot,*alpha_1,*beta_1,"ME12");
  plot->getAttLine("contour")->SetLineColor(kRed);
  fitResPFJets_Data->plotOn(plot,*alpha_2,*beta_2,"ME12");
  plot->getAttLine("contour")->SetLineColor(kBlack);

  plot->Print();

  plot->SetTitle("");
  plot->SetAxisColor(1,"x");
  plot->SetLabelColor(1, "X");
  plot->SetLabelColor(1, "Y");
  plot->SetXTitle("#alpha");
  plot->SetYTitle("#beta");

  plot->Draw();

  TH1F *h_0 = new TH1F("h_0","h_0",1,0,1);
  h_0->SetLineStyle(kDashed);
  h_0->SetLineColor(kRed);
  TH1F *h_1 = new TH1F("h_1","h_1",1,0,1);
  h_1->SetLineColor(kRed);
  TH1F *h_2 = new TH1F("h_2","h_2",1,0,1);
  h_2->SetLineColor(kBlack);

  TLegendEntry *legge;
  TLegend *leg;
  leg = new TLegend(0.3,0.85,0.93,0.95);
  leg->SetFillStyle(0); leg->SetBorderSize(0.); leg->SetTextSize(0.025);
  leg->SetFillColor(0);
  legge = leg->AddEntry(h_0,"Generator Jets E_{T}>30 GeV (Madgraph)", "lp");
  legge = leg->AddEntry(h_1,"Reconstructed Jets E_{T}>30 GeV (Madgraph)", "lp");
  legge = leg->AddEntry(h_2,"Reconstructed Jets E_{T}>30 GeV (Data)", "lp");
  leg->Draw();
  gPad->Update();

  c1->SaveAs("alphabeta.eps");

}
