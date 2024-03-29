{
//=========Macro generated from canvas: c/fitResult
//=========  (Sun Mar  8 19:12:35 2009) by ROOT version5.18/00a
   TCanvas *c = new TCanvas("c", "fitResult",4,21,600,300);
   gStyle->SetOptStat(0);
   c->Range(-1.095783,-32.39693,0.9524096,170.0839);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetTickx();
   c->SetTicky();
   c->SetLeftMargin(0.12);
   c->SetRightMargin(0.05);
   c->SetTopMargin(0.05);
   c->SetBottomMargin(0.16);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   
   TH1 *frame_09b1f9a0 = new TH1D("frame_09b1f9a0","A RooPlot of "sin #phi_{MHT-MET}"",8,-0.85,0.85);
   frame_09b1f9a0->SetMaximum(159.9599);
   frame_09b1f9a0->SetDirectory(0);
   frame_09b1f9a0->SetStats(0);
   frame_09b1f9a0->SetMarkerStyle(8);
   frame_09b1f9a0->GetXaxis()->SetTitle("sin(#phi_{MHT,MET})");
   frame_09b1f9a0->GetXaxis()->SetLabelFont(132);
   frame_09b1f9a0->GetXaxis()->SetLabelSize(0.05);
   frame_09b1f9a0->GetXaxis()->SetTitleSize(0.06);
   frame_09b1f9a0->GetXaxis()->SetTitleFont(132);
   frame_09b1f9a0->GetYaxis()->SetTitle("Events");
   frame_09b1f9a0->GetYaxis()->SetLabelFont(132);
   frame_09b1f9a0->GetYaxis()->SetLabelSize(0.05);
   frame_09b1f9a0->GetYaxis()->SetTitleSize(0.06);
   frame_09b1f9a0->GetYaxis()->SetTitleFont(132);
   frame_09b1f9a0->GetZaxis()->SetLabelFont(132);
   frame_09b1f9a0->GetZaxis()->SetLabelSize(0.05);
   frame_09b1f9a0->GetZaxis()->SetTitleSize(0.06);
   frame_09b1f9a0->GetZaxis()->SetTitleFont(132);
   frame_09b1f9a0->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(8);
   grae->SetName("other_plot__sinMHTphiMET");
   grae->SetTitle("Histogram of other_plot__sinMHTphiMET");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,-0.74375,129);
   grae->SetPointError(0,0.10625,0.10625,10.86882,11.86882);
   grae->SetPoint(1,-0.53125,117);
   grae->SetPointError(1,0.10625,0.10625,10.3282,11.3282);
   grae->SetPoint(2,-0.31875,140);
   grae->SetPointError(2,0.10625,0.10625,11.34272,12.34272);
   grae->SetPoint(3,-0.10625,129);
   grae->SetPointError(3,0.10625,0.10625,10.86882,11.86882);
   grae->SetPoint(4,0.10625,134);
   grae->SetPointError(4,0.10625,0.10625,11.08663,12.08663);
   grae->SetPoint(5,0.31875,131);
   grae->SetPointError(5,0.10625,0.10625,10.95644,11.95644);
   grae->SetPoint(6,0.53125,134);
   grae->SetPointError(6,0.10625,0.10625,11.08663,12.08663);
   grae->SetPoint(7,0.74375,113);
   grae->SetPointError(7,0.10625,0.10625,10.1419,11.1419);
   grae->Draw("p");
   
   TGraph *graph = new TGraph(14);
   graph->SetName("curve_myFitProjected");
   graph->SetTitle("Projection of Ratio ZtoEE");
   graph->SetFillColor(1);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,-1.0625,0);
   graph->SetPoint(1,-1.0625,130.3387);
   graph->SetPoint(2,-0.85,130.3387);
   graph->SetPoint(3,-0.6375,129.8478);
   graph->SetPoint(4,-0.425,129.3568);
   graph->SetPoint(5,-0.2125,128.8659);
   graph->SetPoint(6,0,128.375);
   graph->SetPoint(7,0.2125,127.8841);
   graph->SetPoint(8,0.425,127.3932);
   graph->SetPoint(9,0.6375,126.9022);
   graph->SetPoint(10,0.85,126.4113);
   graph->SetPoint(11,0.85,126.4113);
   graph->SetPoint(12,1.0625,126.4113);
   graph->SetPoint(13,1.0625,0);
   graph->Draw("l");
   
   TH1 *frame_09b1f9a0 = new TH1D("frame_09b1f9a0","A RooPlot of "sin #phi_{MHT-MET}"",8,-0.85,0.85);
   frame_09b1f9a0->SetMaximum(159.9599);
   frame_09b1f9a0->SetDirectory(0);
   frame_09b1f9a0->SetStats(0);
   frame_09b1f9a0->SetMarkerStyle(8);
   frame_09b1f9a0->GetXaxis()->SetTitle("sin(#phi_{MHT,MET})");
   frame_09b1f9a0->GetXaxis()->SetLabelFont(132);
   frame_09b1f9a0->GetXaxis()->SetLabelSize(0.05);
   frame_09b1f9a0->GetXaxis()->SetTitleSize(0.06);
   frame_09b1f9a0->GetXaxis()->SetTitleFont(132);
   frame_09b1f9a0->GetYaxis()->SetTitle("Events");
   frame_09b1f9a0->GetYaxis()->SetLabelFont(132);
   frame_09b1f9a0->GetYaxis()->SetLabelSize(0.05);
   frame_09b1f9a0->GetYaxis()->SetTitleSize(0.06);
   frame_09b1f9a0->GetYaxis()->SetTitleFont(132);
   frame_09b1f9a0->GetZaxis()->SetLabelFont(132);
   frame_09b1f9a0->GetZaxis()->SetLabelSize(0.05);
   frame_09b1f9a0->GetZaxis()->SetTitleSize(0.06);
   frame_09b1f9a0->GetZaxis()->SetTitleFont(132);
   frame_09b1f9a0->Draw("axissame");
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
