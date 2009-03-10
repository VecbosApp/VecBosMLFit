void errorBVeto() {

  const Int_t n = 7;
  //  const Int_t n = 4;
  double x[n], y[n];

//   //////////////////////////////////
//   // electron W + 3 trackjets
//   //////////////////////////////////

//   x[0]=60;
//   x[1]=80;
//   x[2]=100;
//   x[3]=120;
//   x[4]=140;
  
//   y[0]=109;
//   y[1]=91;
//   y[2]=105;
//   y[3]=105;
//   y[4]=108;

//   //////////////////////////////////
//   // electron W + 3 calojets
//   //////////////////////////////////

  x[0]=80;
  x[1]=100;
  x[2]=120;
  x[3]=140;
  x[4]=160;
  x[5]=180;
  x[6]=200;
  
  y[0]=65;
  y[1]=62;
  y[2]=61;
  y[3]=60;
  y[4]=59;
  y[5]=58;
  y[6]=60.5;

  
  TCanvas* c1 = new TCanvas("c1","c1");
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);
  c1->Range(0.3651566,-0.7055599,4.355518,4.060589);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetGridx();
  c1->SetGridy();
  c1->SetTickx();
  c1->SetTicky();
  c1->SetLeftMargin(0.12);
  c1->SetRightMargin(0.05);
  c1->SetTopMargin(0.05);
  c1->SetBottomMargin(0.16);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);

  TGraph * gr1 = new TGraph(n,x,y);
  gr1->GetXaxis()->SetTitle("square (D_{xy} ; D_{sz}) cut [#mum]");
  gr1->GetYaxis()->SetTitle("Error on W + 3 jets yield");
  gr1->GetYaxis()->SetRangeUser(56,66);
  gr1->SetMarkerStyle(21);
  gr1->SetLineWidth(1);
  gr1->SetMarkerStyle(21);
  gr1->Draw("ap");

}
