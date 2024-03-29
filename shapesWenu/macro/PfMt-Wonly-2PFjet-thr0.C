{
//=========Macro generated from canvas: c/fitResult
//=========  (Sun Dec  5 14:55:51 2010) by ROOT version5.22/00d
   TCanvas *c = new TCanvas("c", "fitResult",0,22,600,600);
   gStyle->SetOptStat(0);
   c->Range(1.204819,-37.19414,157.8313,195.2692);
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
   
   TH1 *frame_1877186304 = new TH1D("frame_1877186304","A RooPlot of "M_{T}"",25,20,150);
   frame_1877186304->SetMaximum(183.6461);
   frame_1877186304->SetDirectory(0);
   frame_1877186304->SetStats(0);
   frame_1877186304->SetMarkerStyle(8);
   frame_1877186304->GetXaxis()->SetTitle("M_{T}[GeV/c^{2}]");
   frame_1877186304->GetXaxis()->SetLabelFont(132);
   frame_1877186304->GetXaxis()->SetLabelSize(0.05);
   frame_1877186304->GetXaxis()->SetTitleSize(0.06);
   frame_1877186304->GetXaxis()->SetTitleFont(132);
   frame_1877186304->GetYaxis()->SetTitle("Events / ( 5 GeV/c^{2})");
   frame_1877186304->GetYaxis()->SetLabelFont(132);
   frame_1877186304->GetYaxis()->SetLabelSize(0.05);
   frame_1877186304->GetYaxis()->SetTitleSize(0.06);
   frame_1877186304->GetYaxis()->SetTitleFont(132);
   frame_1877186304->GetZaxis()->SetLabelFont(132);
   frame_1877186304->GetZaxis()->SetLabelSize(0.05);
   frame_1877186304->GetZaxis()->SetTitleSize(0.06);
   frame_1877186304->GetZaxis()->SetTitleFont(132);
   frame_1877186304->Draw("");
   
   TGraph *graph = new TGraph(63);
   graph->SetName("myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]");
   graph->SetTitle("Projection of Ratio WtoENu");

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#ffcc00");
   graph->SetFillColor(ci);

   ci = TColor::GetColor("#993300");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,14.8,0);
   graph->SetPoint(1,14.8,38.5087);
   graph->SetPoint(2,20,38.5087);
   graph->SetPoint(3,25.2,41.71086);
   graph->SetPoint(4,30.4,45.90623);
   graph->SetPoint(5,33,48.49378);
   graph->SetPoint(6,35.6,51.48903);
   graph->SetPoint(7,38.2,54.96659);
   graph->SetPoint(8,40.8,59.01284);
   graph->SetPoint(9,43.4,63.72517);
   graph->SetPoint(10,46,69.20879);
   graph->SetPoint(11,48.6,75.56918);
   graph->SetPoint(12,51.2,82.89782);
   graph->SetPoint(13,53.8,91.24817);
   graph->SetPoint(14,56.4,100.5995);
   graph->SetPoint(15,59,110.8085);
   graph->SetPoint(16,61.6,121.5558);
   graph->SetPoint(17,64.2,132.3032);
   graph->SetPoint(18,66.8,142.2898);
   graph->SetPoint(19,68.1,146.7138);
   graph->SetPoint(20,69.4,150.5985);
   graph->SetPoint(21,70.7,153.8298);
   graph->SetPoint(22,72,156.3062);
   graph->SetPoint(23,73.3,157.9457);
   graph->SetPoint(24,74.6,158.6924);
   graph->SetPoint(25,75.25,158.695);
   graph->SetPoint(26,75.9,158.1628);
   graph->SetPoint(27,76.55,157.0295);
   graph->SetPoint(28,77.2,155.3125);
   graph->SetPoint(29,77.85,153.0376);
   graph->SetPoint(30,78.5,150.2385);
   graph->SetPoint(31,79.15,146.9554);
   graph->SetPoint(32,79.8,143.2346);
   graph->SetPoint(33,80.45,139.1263);
   graph->SetPoint(34,81.1,134.6841);
   graph->SetPoint(35,82.4,125.0184);
   graph->SetPoint(36,87.6,83.40698);
   graph->SetPoint(37,88.9,73.85166);
   graph->SetPoint(38,90.2,65.02304);
   graph->SetPoint(39,91.5,56.99758);
   graph->SetPoint(40,92.8,49.8004);
   graph->SetPoint(41,94.1,43.4177);
   graph->SetPoint(42,95.4,37.80846);
   graph->SetPoint(43,96.7,32.91453);
   graph->SetPoint(44,98,28.66868);
   graph->SetPoint(45,99.3,25.00057);
   graph->SetPoint(46,100.6,21.84105);
   graph->SetPoint(47,101.9,19.12482);
   graph->SetPoint(48,103.2,16.79201);
   graph->SetPoint(49,105.8,13.06816);
   graph->SetPoint(50,108.4,10.31408);
   graph->SetPoint(51,111,8.263798);
   graph->SetPoint(52,113.6,6.723476);
   graph->SetPoint(53,118.8,4.655282);
   graph->SetPoint(54,124,3.407151);
   graph->SetPoint(55,129.2,2.617522);
   graph->SetPoint(56,134.4,2.095423);
   graph->SetPoint(57,139.6,1.736242);
   graph->SetPoint(58,144.8,1.480354);
   graph->SetPoint(59,150,1.292411);
   graph->SetPoint(60,150,1.292411);
   graph->SetPoint(61,155.2,1.292411);
   graph->SetPoint(62,155.2,0);
   
   TH1 *myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3 = new TH1F("myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3","Projection of Ratio WtoENu",100,0.76,169.24);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3->SetMinimum(0);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3->SetMaximum(174.5645);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3->SetDirectory(0);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3->SetStats(0);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3->SetMarkerStyle(8);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3->GetXaxis()->SetLabelFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3->GetXaxis()->SetLabelSize(0.05);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3->GetXaxis()->SetTitleSize(0.06);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3->GetXaxis()->SetTitleFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3->GetYaxis()->SetLabelFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3->GetYaxis()->SetLabelSize(0.05);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3->GetYaxis()->SetTitleSize(0.06);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3->GetYaxis()->SetTitleFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3->GetZaxis()->SetLabelFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3->GetZaxis()->SetLabelSize(0.05);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3->GetZaxis()->SetTitleSize(0.06);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]3);
   
   graph->Draw("f");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(25);
   grae->SetName("h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]");
   grae->SetTitle("Histogram of WJets_plot__pfmt");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,22.6,37.35522);
   grae->SetPointError(0,2.6,2.6,6.084278,7.166303);
   grae->SetPoint(1,27.8,42.68206);
   grae->SetPointError(1,2.6,2.6,6.507352,7.584084);
   grae->SetPoint(2,33,53.20258);
   grae->SetPointError(2,2.6,2.6,7.270957,8.339678);
   grae->SetPoint(3,38.2,54.9338);
   grae->SetPointError(3,2.6,2.6,7.389082,8.45671);
   grae->SetPoint(4,43.4,64.98827);
   grae->SetPointError(4,2.6,2.6,8.040731,9.102902);
   grae->SetPoint(5,48.6,77.90661);
   grae->SetPointError(5,2.6,2.6,8.807472,9.864249);
   grae->SetPoint(6,53.8,90.22564);
   grae->SetPointError(6,2.6,2.6,9.481059,10.53381);
   grae->SetPoint(7,59,108.5377);
   grae->SetPointError(7,2.6,2.6,9.930107,10.93011);
   grae->SetPoint(8,64.2,126.1173);
   grae->SetPointError(8,2.6,2.6,10.74131,11.74131);
   grae->SetPoint(9,69.4,151.8208);
   grae->SetPointError(9,2.6,2.6,11.83169,12.83169);
   grae->SetPoint(10,74.6,161.676);
   grae->SetPointError(10,2.6,2.6,12.225,13.225);
   grae->SetPoint(11,79.8,144.2962);
   grae->SetPointError(11,2.6,2.6,11.52272,12.52272);
   grae->SetPoint(12,85,104.0096);
   grae->SetPointError(12,2.6,2.6,9.71076,10.71076);
   grae->SetPoint(13,90.2,61.72553);
   grae->SetPointError(13,2.6,2.6,7.835165,8.89896);
   grae->SetPoint(14,95.4,37.42181);
   grae->SetPointError(14,2.6,2.6,6.089739,7.171691);
   grae->SetPoint(15,100.6,22.3732);
   grae->SetPointError(15,2.6,2.6,4.694141,5.80013);
   grae->SetPoint(16,105.8,15.04859);
   grae->SetPointError(16,2.6,2.6,3.835621,4.96478);
   grae->SetPoint(17,111,8.65629);
   grae->SetPointError(17,2.6,2.6,2.883286,4.05347);
   grae->SetPoint(18,116.2,6.12599);
   grae->SetPointError(18,2.6,2.6,2.405323,3.607156);
   grae->SetPoint(19,121.4,4.727664);
   grae->SetPointError(19,2.6,2.6,2.092873,3.322635);
   grae->SetPoint(20,126.6,3.462513);
   grae->SetPointError(20,2.6,2.6,1.762964,3.031301);
   grae->SetPoint(21,131.8,2.330539);
   grae->SetPointError(21,2.6,2.6,1.404492,2.730518);
   grae->SetPoint(22,137,1.265149);
   grae->SetPointError(22,2.6,2.6,0.9504262,2.389235);
   grae->SetPoint(23,142.2,1.398323);
   grae->SetPointError(23,2.6,2.6,1.012295,2.434292);
   grae->SetPoint(24,147.4,0.7990416);
   grae->SetPointError(24,2.6,2.6,0.6610041,2.068092);
   
   TH1 *h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2 = new TH1F("h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2","Histogram of WJets_plot__pfmt",100,7,163);
   h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2->SetMinimum(0);
   h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2->SetMaximum(192.3773);
   h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2->SetDirectory(0);
   h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2->SetStats(0);
   h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2->SetMarkerStyle(8);
   h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2->GetXaxis()->SetLabelFont(132);
   h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2->GetXaxis()->SetLabelSize(0.05);
   h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2->GetXaxis()->SetTitleSize(0.06);
   h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2->GetXaxis()->SetTitleFont(132);
   h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2->GetYaxis()->SetLabelFont(132);
   h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2->GetYaxis()->SetLabelSize(0.05);
   h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2->GetYaxis()->SetTitleSize(0.06);
   h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2->GetYaxis()->SetTitleFont(132);
   h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2->GetZaxis()->SetLabelFont(132);
   h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2->GetZaxis()->SetLabelSize(0.05);
   h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2->GetZaxis()->SetTitleSize(0.06);
   h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2->GetZaxis()->SetTitleFont(132);
   grae->SetHistogram(h_WJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]2);
   
   grae->Draw("p");
   
   graph = new TGraph(63);
   graph->SetName("myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]");
   graph->SetTitle("Projection of Ratio WtoENu");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#ff6600");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,14.8,0);
   graph->SetPoint(1,14.8,38.5087);
   graph->SetPoint(2,20,38.5087);
   graph->SetPoint(3,25.2,41.71086);
   graph->SetPoint(4,30.4,45.90623);
   graph->SetPoint(5,33,48.49378);
   graph->SetPoint(6,35.6,51.48903);
   graph->SetPoint(7,38.2,54.96659);
   graph->SetPoint(8,40.8,59.01284);
   graph->SetPoint(9,43.4,63.72517);
   graph->SetPoint(10,46,69.20879);
   graph->SetPoint(11,48.6,75.56918);
   graph->SetPoint(12,51.2,82.89782);
   graph->SetPoint(13,53.8,91.24817);
   graph->SetPoint(14,56.4,100.5995);
   graph->SetPoint(15,59,110.8085);
   graph->SetPoint(16,61.6,121.5558);
   graph->SetPoint(17,64.2,132.3032);
   graph->SetPoint(18,66.8,142.2898);
   graph->SetPoint(19,68.1,146.7138);
   graph->SetPoint(20,69.4,150.5985);
   graph->SetPoint(21,70.7,153.8298);
   graph->SetPoint(22,72,156.3062);
   graph->SetPoint(23,73.3,157.9457);
   graph->SetPoint(24,74.6,158.6924);
   graph->SetPoint(25,75.25,158.695);
   graph->SetPoint(26,75.9,158.1628);
   graph->SetPoint(27,76.55,157.0295);
   graph->SetPoint(28,77.2,155.3125);
   graph->SetPoint(29,77.85,153.0376);
   graph->SetPoint(30,78.5,150.2385);
   graph->SetPoint(31,79.15,146.9554);
   graph->SetPoint(32,79.8,143.2346);
   graph->SetPoint(33,80.45,139.1263);
   graph->SetPoint(34,81.1,134.6841);
   graph->SetPoint(35,82.4,125.0184);
   graph->SetPoint(36,87.6,83.40698);
   graph->SetPoint(37,88.9,73.85166);
   graph->SetPoint(38,90.2,65.02304);
   graph->SetPoint(39,91.5,56.99758);
   graph->SetPoint(40,92.8,49.8004);
   graph->SetPoint(41,94.1,43.4177);
   graph->SetPoint(42,95.4,37.80846);
   graph->SetPoint(43,96.7,32.91453);
   graph->SetPoint(44,98,28.66868);
   graph->SetPoint(45,99.3,25.00057);
   graph->SetPoint(46,100.6,21.84105);
   graph->SetPoint(47,101.9,19.12482);
   graph->SetPoint(48,103.2,16.79201);
   graph->SetPoint(49,105.8,13.06816);
   graph->SetPoint(50,108.4,10.31408);
   graph->SetPoint(51,111,8.263798);
   graph->SetPoint(52,113.6,6.723476);
   graph->SetPoint(53,118.8,4.655282);
   graph->SetPoint(54,124,3.407151);
   graph->SetPoint(55,129.2,2.617522);
   graph->SetPoint(56,134.4,2.095423);
   graph->SetPoint(57,139.6,1.736242);
   graph->SetPoint(58,144.8,1.480354);
   graph->SetPoint(59,150,1.292411);
   graph->SetPoint(60,150,1.292411);
   graph->SetPoint(61,155.2,1.292411);
   graph->SetPoint(62,155.2,0);
   
   TH1 *myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4 = new TH1F("myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4","Projection of Ratio WtoENu",100,0.76,169.24);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4->SetMinimum(0);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4->SetMaximum(174.5645);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4->SetDirectory(0);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4->SetStats(0);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4->SetMarkerStyle(8);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4->GetXaxis()->SetLabelFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4->GetXaxis()->SetLabelSize(0.05);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4->GetXaxis()->SetTitleSize(0.06);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4->GetXaxis()->SetTitleFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4->GetYaxis()->SetLabelFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4->GetYaxis()->SetLabelSize(0.05);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4->GetYaxis()->SetTitleSize(0.06);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4->GetYaxis()->SetTitleFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4->GetZaxis()->SetLabelFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4->GetZaxis()->SetLabelSize(0.05);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4->GetZaxis()->SetTitleSize(0.06);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]4);
   
   graph->Draw("l");
   
   TH1 *frame_1877186304 = new TH1D("frame_1877186304","A RooPlot of "M_{T}"",25,20,150);
   frame_1877186304->SetMaximum(183.6461);
   frame_1877186304->SetDirectory(0);
   frame_1877186304->SetStats(0);
   frame_1877186304->SetMarkerStyle(8);
   frame_1877186304->GetXaxis()->SetTitle("M_{T}[GeV/c^{2}]");
   frame_1877186304->GetXaxis()->SetLabelFont(132);
   frame_1877186304->GetXaxis()->SetLabelSize(0.05);
   frame_1877186304->GetXaxis()->SetTitleSize(0.06);
   frame_1877186304->GetXaxis()->SetTitleFont(132);
   frame_1877186304->GetYaxis()->SetTitle("Events / ( 5 GeV/c^{2})");
   frame_1877186304->GetYaxis()->SetLabelFont(132);
   frame_1877186304->GetYaxis()->SetLabelSize(0.05);
   frame_1877186304->GetYaxis()->SetTitleSize(0.06);
   frame_1877186304->GetYaxis()->SetTitleFont(132);
   frame_1877186304->GetZaxis()->SetLabelFont(132);
   frame_1877186304->GetZaxis()->SetLabelSize(0.05);
   frame_1877186304->GetZaxis()->SetTitleSize(0.06);
   frame_1877186304->GetZaxis()->SetTitleFont(132);
   frame_1877186304->Draw("AXISSAME");
   
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
