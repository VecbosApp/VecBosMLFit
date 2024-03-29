{
//=========Macro generated from canvas: c/fitResult
//=========  (Sat Dec  4 21:14:52 2010) by ROOT version5.22/00d
   TCanvas *c = new TCanvas("c", "fitResult",0,22,600,600);
   gStyle->SetOptStat(0);
   c->Range(-0.4337349,-2.009039,3.180723,10.54745);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetTickx(1);
   c->SetTicky(1);
   c->SetLeftMargin(0.12);
   c->SetRightMargin(0.05);
   c->SetTopMargin(0.05);
   c->SetBottomMargin(0.16);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   
   TH1 *frame_1379391016 = new TH1D("frame_1379391016","A RooPlot of "n_{b-tag jets}"",3,0,3);
   frame_1379391016->SetMaximum(9.919629);
   frame_1379391016->SetDirectory(0);
   frame_1379391016->SetStats(0);
   frame_1379391016->SetMarkerStyle(8);
   frame_1379391016->GetXaxis()->SetTitle("N_{b-tag jets}");
   frame_1379391016->GetXaxis()->SetLabelFont(132);
   frame_1379391016->GetXaxis()->SetLabelSize(0.05);
   frame_1379391016->GetXaxis()->SetTitleSize(0.06);
   frame_1379391016->GetXaxis()->SetTitleFont(132);
   frame_1379391016->GetYaxis()->SetTitle("Events / (1.00 )");
   frame_1379391016->GetYaxis()->SetLabelFont(132);
   frame_1379391016->GetYaxis()->SetLabelSize(0.05);
   frame_1379391016->GetYaxis()->SetTitleSize(0.06);
   frame_1379391016->GetYaxis()->SetTitleFont(132);
   frame_1379391016->GetZaxis()->SetLabelFont(132);
   frame_1379391016->GetZaxis()->SetLabelSize(0.05);
   frame_1379391016->GetZaxis()->SetTitleSize(0.06);
   frame_1379391016->GetZaxis()->SetTitleFont(132);
   frame_1379391016->Draw("");
   
   TGraph *graph = new TGraph(25);
   graph->SetName("myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]");
   graph->SetTitle("Projection of Ratio WtoENu");

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#ffcc00");
   graph->SetFillColor(ci);

   ci = TColor::GetColor("#993300");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,-1,0);
   graph->SetPoint(1,-1,6.17221);
   graph->SetPoint(2,0,6.17221);
   graph->SetPoint(3,0.5,6.17221);
   graph->SetPoint(4,0.75,6.17221);
   graph->SetPoint(5,0.875,6.17221);
   graph->SetPoint(6,0.9375,6.17221);
   graph->SetPoint(7,0.96875,6.17221);
   graph->SetPoint(8,0.984375,6.17221);
   graph->SetPoint(9,0.9921875,6.17221);
   graph->SetPoint(10,0.9960938,6.17221);
   graph->SetPoint(11,1,0.2638797);
   graph->SetPoint(12,1.5,0.2638797);
   graph->SetPoint(13,1.75,0.2638797);
   graph->SetPoint(14,1.875,0.2638797);
   graph->SetPoint(15,1.9375,0.2638797);
   graph->SetPoint(16,1.96875,0.2638797);
   graph->SetPoint(17,1.984375,0.2638797);
   graph->SetPoint(18,1.992188,0.2638797);
   graph->SetPoint(19,1.996094,0.2638797);
   graph->SetPoint(20,2,2.232967e-16);
   graph->SetPoint(21,3,2.232967e-16);
   graph->SetPoint(22,3,2.232967e-16);
   graph->SetPoint(23,4,2.232967e-16);
   graph->SetPoint(24,4,0);
   
   TH1 *myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1 = new TH1F("myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1","Projection of Ratio WtoENu",100,-1.5,4.5);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->SetMinimum(0);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->SetMaximum(6.789431);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->SetDirectory(0);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->SetStats(0);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->SetMarkerStyle(8);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetXaxis()->SetLabelFont(132);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetXaxis()->SetLabelSize(0.05);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetXaxis()->SetTitleSize(0.06);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetXaxis()->SetTitleFont(132);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetYaxis()->SetLabelFont(132);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetYaxis()->SetLabelSize(0.05);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetYaxis()->SetTitleSize(0.06);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetYaxis()->SetTitleFont(132);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetZaxis()->SetLabelFont(132);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetZaxis()->SetLabelSize(0.05);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetZaxis()->SetTitleSize(0.06);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]1);
   
   graph->Draw("f");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(3);
   grae->SetName("h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]");
   grae->SetTitle("Histogram of WJets_plot__nBTagJets");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,0.5,5.886464);
   grae->SetPointError(0,0.5,0.5,2.354926,3.560802);
   grae->SetPoint(1,1.5,0.5498175);
   grae->SetPointError(1,0.5,0.5,0.4548345,1.781073);
   grae->SetPoint(2,2.5,0);
   grae->SetPointError(2,0.5,0.5,0,1.147874);
   
   TH1 *h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1 = new TH1F("h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1","Histogram of WJets_plot__nBTagJets",100,0,3.3);
   h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->SetMinimum(0);
   h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->SetMaximum(10.39199);
   h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->SetDirectory(0);
   h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->SetStats(0);
   h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->SetMarkerStyle(8);
   h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetXaxis()->SetLabelFont(132);
   h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetXaxis()->SetLabelSize(0.05);
   h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetXaxis()->SetTitleSize(0.06);
   h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetXaxis()->SetTitleFont(132);
   h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetYaxis()->SetLabelFont(132);
   h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetYaxis()->SetLabelSize(0.05);
   h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetYaxis()->SetTitleSize(0.06);
   h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetYaxis()->SetTitleFont(132);
   h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetZaxis()->SetLabelFont(132);
   h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetZaxis()->SetLabelSize(0.05);
   h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetZaxis()->SetTitleSize(0.06);
   h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetZaxis()->SetTitleFont(132);
   grae->SetHistogram(h_WJets_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1);
   
   grae->Draw("p");
   
   graph = new TGraph(25);
   graph->SetName("myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]");
   graph->SetTitle("Projection of Ratio WtoENu");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#ff6600");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,-1,0);
   graph->SetPoint(1,-1,6.17221);
   graph->SetPoint(2,0,6.17221);
   graph->SetPoint(3,0.5,6.17221);
   graph->SetPoint(4,0.75,6.17221);
   graph->SetPoint(5,0.875,6.17221);
   graph->SetPoint(6,0.9375,6.17221);
   graph->SetPoint(7,0.96875,6.17221);
   graph->SetPoint(8,0.984375,6.17221);
   graph->SetPoint(9,0.9921875,6.17221);
   graph->SetPoint(10,0.9960938,6.17221);
   graph->SetPoint(11,1,0.2638797);
   graph->SetPoint(12,1.5,0.2638797);
   graph->SetPoint(13,1.75,0.2638797);
   graph->SetPoint(14,1.875,0.2638797);
   graph->SetPoint(15,1.9375,0.2638797);
   graph->SetPoint(16,1.96875,0.2638797);
   graph->SetPoint(17,1.984375,0.2638797);
   graph->SetPoint(18,1.992188,0.2638797);
   graph->SetPoint(19,1.996094,0.2638797);
   graph->SetPoint(20,2,2.232967e-16);
   graph->SetPoint(21,3,2.232967e-16);
   graph->SetPoint(22,3,2.232967e-16);
   graph->SetPoint(23,4,2.232967e-16);
   graph->SetPoint(24,4,0);
   
   TH1 *myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2 = new TH1F("myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2","Projection of Ratio WtoENu",100,-1.5,4.5);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->SetMinimum(0);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->SetMaximum(6.789431);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->SetDirectory(0);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->SetStats(0);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->SetMarkerStyle(8);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetXaxis()->SetLabelFont(132);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetXaxis()->SetLabelSize(0.05);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetXaxis()->SetTitleSize(0.06);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetXaxis()->SetTitleFont(132);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetYaxis()->SetLabelFont(132);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetYaxis()->SetLabelSize(0.05);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetYaxis()->SetTitleSize(0.06);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetYaxis()->SetTitleFont(132);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetZaxis()->SetLabelFont(132);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetZaxis()->SetLabelSize(0.05);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetZaxis()->SetTitleSize(0.06);
   myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(myFit_Norm[nBTagJets,nExclPFJetsHi]_Slice[nExclPFJetsHi]2);
   
   graph->Draw("l");
   
   TH1 *frame_1379391016 = new TH1D("frame_1379391016","A RooPlot of "n_{b-tag jets}"",3,0,3);
   frame_1379391016->SetMaximum(9.919629);
   frame_1379391016->SetDirectory(0);
   frame_1379391016->SetStats(0);
   frame_1379391016->SetMarkerStyle(8);
   frame_1379391016->GetXaxis()->SetTitle("N_{b-tag jets}");
   frame_1379391016->GetXaxis()->SetLabelFont(132);
   frame_1379391016->GetXaxis()->SetLabelSize(0.05);
   frame_1379391016->GetXaxis()->SetTitleSize(0.06);
   frame_1379391016->GetXaxis()->SetTitleFont(132);
   frame_1379391016->GetYaxis()->SetTitle("Events / (1.00 )");
   frame_1379391016->GetYaxis()->SetLabelFont(132);
   frame_1379391016->GetYaxis()->SetLabelSize(0.05);
   frame_1379391016->GetYaxis()->SetTitleSize(0.06);
   frame_1379391016->GetYaxis()->SetTitleFont(132);
   frame_1379391016->GetZaxis()->SetLabelFont(132);
   frame_1379391016->GetZaxis()->SetLabelSize(0.05);
   frame_1379391016->GetZaxis()->SetTitleSize(0.06);
   frame_1379391016->GetZaxis()->SetTitleFont(132);
   frame_1379391016->Draw("AXISSAME");
   
   TLegend *leg = new TLegend(0.6,0.65,0.93,0.8,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(132);
   leg->SetTextSize(0.025);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("dataH","Data","lpe");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(8);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("totalH","total","f");

   ci = TColor::GetColor("#ffcc00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("topPlusOtherH","Top+Other","f");

   ci = TColor::GetColor("#cc00ff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("otherH","Other","f");

   ci = TColor::GetColor("#ff6633");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
