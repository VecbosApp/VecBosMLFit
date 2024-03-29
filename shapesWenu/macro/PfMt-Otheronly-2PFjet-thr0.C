{
//=========Macro generated from canvas: c/fitResult
//=========  (Sun Dec  5 16:19:42 2010) by ROOT version5.22/00d
   TCanvas *c = new TCanvas("c", "fitResult",0,22,600,600);
   gStyle->SetOptStat(0);
   c->Range(1.204819,-72.15569,157.8313,378.8174);
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
   
   TH1 *frame_248129048 = new TH1D("frame_248129048","A RooPlot of "M_{T}"",50,20,150);
   frame_248129048->SetMaximum(356.2687);
   frame_248129048->SetDirectory(0);
   frame_248129048->SetStats(0);
   frame_248129048->SetMarkerStyle(8);
   frame_248129048->GetXaxis()->SetTitle("M_{T}[GeV/c^{2}]");
   frame_248129048->GetXaxis()->SetLabelFont(132);
   frame_248129048->GetXaxis()->SetLabelSize(0.05);
   frame_248129048->GetXaxis()->SetTitleSize(0.06);
   frame_248129048->GetXaxis()->SetTitleFont(132);
   frame_248129048->GetYaxis()->SetTitle("Events / ( 3 GeV/c^{2})");
   frame_248129048->GetYaxis()->SetLabelFont(132);
   frame_248129048->GetYaxis()->SetLabelSize(0.05);
   frame_248129048->GetYaxis()->SetTitleSize(0.06);
   frame_248129048->GetYaxis()->SetTitleFont(132);
   frame_248129048->GetZaxis()->SetLabelFont(132);
   frame_248129048->GetZaxis()->SetLabelSize(0.05);
   frame_248129048->GetZaxis()->SetTitleSize(0.06);
   frame_248129048->GetZaxis()->SetTitleFont(132);
   frame_248129048->Draw("");
   
   TGraph *graph = new TGraph(59);
   graph->SetName("myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]");
   graph->SetTitle("Projection of Ratio WtoENu");

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#cc00ff");
   graph->SetFillColor(ci);

   ci = TColor::GetColor("#0000ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,17.4,0);
   graph->SetPoint(1,17.4,339.3035);
   graph->SetPoint(2,20,339.3035);
   graph->SetPoint(3,21.3,334.5071);
   graph->SetPoint(4,22.6,328.1725);
   graph->SetPoint(5,23.9,320.4102);
   graph->SetPoint(6,25.2,311.3519);
   graph->SetPoint(7,26.5,301.1464);
   graph->SetPoint(8,27.8,289.9554);
   graph->SetPoint(9,30.4,265.297);
   graph->SetPoint(10,33,238.7426);
   graph->SetPoint(11,35.6,211.577);
   graph->SetPoint(12,38.2,184.9044);
   graph->SetPoint(13,40.8,159.5894);
   graph->SetPoint(14,43.4,136.2386);
   graph->SetPoint(15,46,115.2138);
   graph->SetPoint(16,48.6,96.66775);
   graph->SetPoint(17,51.2,80.58948);
   graph->SetPoint(18,53.8,66.8521);
   graph->SetPoint(19,56.4,55.25571);
   graph->SetPoint(20,59,45.56269);
   graph->SetPoint(21,61.6,37.5242);
   graph->SetPoint(22,64.2,30.89839);
   graph->SetPoint(23,66.8,25.46169);
   graph->SetPoint(24,69.4,21.01463);
   graph->SetPoint(25,72,17.38399);
   graph->SetPoint(26,74.6,14.42236);
   graph->SetPoint(27,77.2,12.00621);
   graph->SetPoint(28,79.8,10.0333);
   graph->SetPoint(29,82.4,8.419755);
   graph->SetPoint(30,85,7.097271);
   graph->SetPoint(31,87.6,6.010473);
   graph->SetPoint(32,90.2,5.114645);
   graph->SetPoint(33,92.8,4.373745);
   graph->SetPoint(34,95.4,3.758767);
   graph->SetPoint(35,98,3.246363);
   graph->SetPoint(36,100.6,2.817736);
   graph->SetPoint(37,103.2,2.457737);
   graph->SetPoint(38,105.8,2.154131);
   graph->SetPoint(39,108.4,1.897024);
   graph->SetPoint(40,111,1.67839);
   graph->SetPoint(41,113.6,1.491705);
   graph->SetPoint(42,116.2,1.331648);
   graph->SetPoint(43,118.8,1.193867);
   graph->SetPoint(44,121.4,1.074791);
   graph->SetPoint(45,124,0.9714808);
   graph->SetPoint(46,126.6,0.8815072);
   graph->SetPoint(47,129.2,0.8028579);
   graph->SetPoint(48,131.8,0.7338589);
   graph->SetPoint(49,134.4,0.6731132);
   graph->SetPoint(50,137,0.6194508);
   graph->SetPoint(51,139.6,0.5718888);
   graph->SetPoint(52,142.2,0.5295983);
   graph->SetPoint(53,144.8,0.491878);
   graph->SetPoint(54,147.4,0.458133);
   graph->SetPoint(55,150,0.4278564);
   graph->SetPoint(56,150,0.4278564);
   graph->SetPoint(57,152.6,0.4278564);
   graph->SetPoint(58,152.6,0);
   
   TH1 *myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1 = new TH1F("myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1","Projection of Ratio WtoENu",100,3.88,166.12);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1->SetMinimum(0);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1->SetMaximum(373.2339);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1->SetDirectory(0);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1->SetStats(0);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1->SetMarkerStyle(8);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1->GetXaxis()->SetLabelFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1->GetXaxis()->SetLabelSize(0.05);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1->GetXaxis()->SetTitleSize(0.06);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1->GetXaxis()->SetTitleFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1->GetYaxis()->SetLabelFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1->GetYaxis()->SetLabelSize(0.05);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1->GetYaxis()->SetTitleSize(0.06);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1->GetYaxis()->SetTitleFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1->GetZaxis()->SetLabelFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1->GetZaxis()->SetLabelSize(0.05);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1->GetZaxis()->SetTitleSize(0.06);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]1);
   
   graph->Draw("f");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(50);
   grae->SetName("h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]");
   grae->SetTitle("Histogram of OtherJets_plot__pfmt");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,21.3,316.822);
   grae->SetPointError(0,1.3,1.3,17.30651,18.30651);
   grae->SetPoint(1,23.9,317.5382);
   grae->SetPointError(1,1.3,1.3,17.32661,18.32661);
   grae->SetPoint(2,26.5,313.5809);
   grae->SetPointError(2,1.3,1.3,17.21527,18.21527);
   grae->SetPoint(3,29.1,295.3044);
   grae->SetPointError(3,1.3,1.3,16.69169,17.69169);
   grae->SetPoint(4,31.7,235.4578);
   grae->SetPointError(4,1.3,1.3,14.85277,15.85277);
   grae->SetPoint(5,34.3,230.9034);
   grae->SetPointError(5,1.3,1.3,14.70373,15.70373);
   grae->SetPoint(6,36.9,221.7458);
   grae->SetPointError(6,1.3,1.3,14.39952,15.39952);
   grae->SetPoint(7,39.5,182.7295);
   grae->SetPointError(7,1.3,1.3,13.02698,14.02698);
   grae->SetPoint(8,42.1,119.9224);
   grae->SetPointError(8,1.3,1.3,10.46231,11.46231);
   grae->SetPoint(9,44.7,115.1881);
   grae->SetPointError(9,1.3,1.3,10.2442,11.2442);
   grae->SetPoint(10,47.3,119.4623);
   grae->SetPointError(10,1.3,1.3,10.44129,11.44129);
   grae->SetPoint(11,49.9,79.93546);
   grae->SetPointError(11,1.3,1.3,8.921912,9.977963);
   grae->SetPoint(12,52.5,74.55054);
   grae->SetPointError(12,1.3,1.3,8.614808,9.672851);
   grae->SetPoint(13,55.1,59.95387);
   grae->SetPointError(13,1.3,1.3,7.721319,8.78605);
   grae->SetPoint(14,57.7,55.46576);
   grae->SetPointError(14,1.3,1.3,7.424935,8.492238);
   grae->SetPoint(15,60.3,29.92949);
   grae->SetPointError(15,1.3,1.3,5.439994,6.531628);
   grae->SetPoint(16,62.9,31.71589);
   grae->SetPointError(16,1.3,1.3,5.601688,6.690709);
   grae->SetPoint(17,65.5,20.22525);
   grae->SetPointError(17,1.3,1.3,4.459531,5.570995);
   grae->SetPoint(18,68.1,30.03735);
   grae->SetPointError(18,1.3,1.3,5.449923,6.541391);
   grae->SetPoint(19,70.7,15.63673);
   grae->SetPointError(19,1.3,1.3,3.91115,5.037902);
   grae->SetPoint(20,73.3,21.78202);
   grae->SetPointError(20,1.3,1.3,4.630809,5.73822);
   grae->SetPoint(21,75.9,16.75348);
   grae->SetPointError(21,1.3,1.3,4.051521,5.173976);
   grae->SetPoint(22,78.5,9.496222);
   grae->SetPointError(22,1.3,1.3,3.025454,4.187985);
   grae->SetPoint(23,81.1,9.525121);
   grae->SetPointError(23,1.3,1.3,3.030229,4.192515);
   grae->SetPoint(24,83.7,12.64737);
   grae->SetPointError(24,1.3,1.3,3.508096,4.648997);
   grae->SetPoint(25,86.3,5.694679);
   grae->SetPointError(25,1.3,1.3,2.312687,3.52222);
   grae->SetPoint(26,88.9,6.764676);
   grae->SetPointError(26,1.3,1.3,2.534043,3.72636);
   grae->SetPoint(27,91.5,4.403299);
   grae->SetPointError(27,1.3,1.3,2.013289,3.251366);
   grae->SetPoint(28,94.1,5.07868);
   grae->SetPointError(28,1.3,1.3,2.17702,3.398301);
   grae->SetPoint(29,96.7,1.786854);
   grae->SetPointError(29,1.3,1.3,1.192794,2.565745);
   grae->SetPoint(30,99.3,6.466027);
   grae->SetPointError(30,1.3,1.3,2.473854,3.67062);
   grae->SetPoint(31,101.9,3.20066);
   grae->SetPointError(31,1.3,1.3,1.689218,2.967261);
   grae->SetPoint(32,104.5,3.804223);
   grae->SetPointError(32,1.3,1.3,1.859202,3.114873);
   grae->SetPoint(33,107.1,1.309956);
   grae->SetPointError(33,1.3,1.3,0.9712419,2.404395);
   grae->SetPoint(34,109.7,1.178417);
   grae->SetPointError(34,1.3,1.3,0.9101332,2.359891);
   grae->SetPoint(35,112.3,1.049986);
   grae->SetPointError(35,1.3,1.3,0.8504679,2.316438);
   grae->SetPoint(36,114.9,1.004732);
   grae->SetPointError(36,1.3,1.3,0.8294444,2.301127);
   grae->SetPoint(37,117.5,1.714476);
   grae->SetPointError(37,1.3,1.3,1.159169,2.541257);
   grae->SetPoint(38,120.1,0.8401047);
   grae->SetPointError(38,1.3,1.3,0.6949734,2.115383);
   grae->SetPoint(39,122.7,0.427286);
   grae->SetPointError(39,1.3,1.3,0.3534707,1.639959);
   grae->SetPoint(40,125.3,0.2399231);
   grae->SetPointError(40,1.3,1.3,0.1984755,1.424182);
   grae->SetPoint(41,127.9,0.2769577);
   grae->SetPointError(41,1.3,1.3,0.2291122,1.466833);
   grae->SetPoint(42,130.5,0.9347242);
   grae->SetPointError(42,1.3,1.3,0.7732471,2.224352);
   grae->SetPoint(43,133.1,0.7787697);
   grae->SetPointError(43,1.3,1.3,0.6442343,2.044746);
   grae->SetPoint(44,135.7,0.08189476);
   grae->SetPointError(44,1.3,1.3,0.06774713,1.242189);
   grae->SetPoint(45,138.3,1.008977);
   grae->SetPointError(45,1.3,1.3,0.8314165,2.302564);
   grae->SetPoint(46,140.9,0.1672035);
   grae->SetPointError(46,1.3,1.3,0.1383184,1.340435);
   grae->SetPoint(47,143.5,0.06460646);
   grae->SetPointError(47,1.3,1.3,0.05344545,1.222279);
   grae->SetPoint(48,146.1,0.07818068);
   grae->SetPointError(48,1.3,1.3,0.06467467,1.237911);
   grae->SetPoint(49,148.7,0.1191484);
   grae->SetPointError(49,1.3,1.3,0.0985651,1.285092);
   
   TH1 *h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1 = new TH1F("h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1","Histogram of OtherJets_plot__pfmt",100,7,163);
   h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1->SetMinimum(0);
   h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1->SetMaximum(369.4502);
   h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1->SetDirectory(0);
   h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1->SetStats(0);
   h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1->SetMarkerStyle(8);
   h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1->GetXaxis()->SetLabelFont(132);
   h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1->GetXaxis()->SetLabelSize(0.05);
   h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1->GetXaxis()->SetTitleSize(0.06);
   h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1->GetXaxis()->SetTitleFont(132);
   h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1->GetYaxis()->SetLabelFont(132);
   h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1->GetYaxis()->SetLabelSize(0.05);
   h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1->GetYaxis()->SetTitleSize(0.06);
   h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1->GetYaxis()->SetTitleFont(132);
   h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1->GetZaxis()->SetLabelFont(132);
   h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1->GetZaxis()->SetLabelSize(0.05);
   h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1->GetZaxis()->SetTitleSize(0.06);
   h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1->GetZaxis()->SetTitleFont(132);
   grae->SetHistogram(h_OtherJets_Cut[(nExclPFJetsHi > (2-0.5) )&& (nExclPFJetsHi < (2 + 0.5) )]1);
   
   grae->Draw("p");
   
   graph = new TGraph(59);
   graph->SetName("myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]");
   graph->SetTitle("Projection of Ratio WtoENu");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#330066");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,17.4,0);
   graph->SetPoint(1,17.4,339.3035);
   graph->SetPoint(2,20,339.3035);
   graph->SetPoint(3,21.3,334.5071);
   graph->SetPoint(4,22.6,328.1725);
   graph->SetPoint(5,23.9,320.4102);
   graph->SetPoint(6,25.2,311.3519);
   graph->SetPoint(7,26.5,301.1464);
   graph->SetPoint(8,27.8,289.9554);
   graph->SetPoint(9,30.4,265.297);
   graph->SetPoint(10,33,238.7426);
   graph->SetPoint(11,35.6,211.577);
   graph->SetPoint(12,38.2,184.9044);
   graph->SetPoint(13,40.8,159.5894);
   graph->SetPoint(14,43.4,136.2386);
   graph->SetPoint(15,46,115.2138);
   graph->SetPoint(16,48.6,96.66775);
   graph->SetPoint(17,51.2,80.58948);
   graph->SetPoint(18,53.8,66.8521);
   graph->SetPoint(19,56.4,55.25571);
   graph->SetPoint(20,59,45.56269);
   graph->SetPoint(21,61.6,37.5242);
   graph->SetPoint(22,64.2,30.89839);
   graph->SetPoint(23,66.8,25.46169);
   graph->SetPoint(24,69.4,21.01463);
   graph->SetPoint(25,72,17.38399);
   graph->SetPoint(26,74.6,14.42236);
   graph->SetPoint(27,77.2,12.00621);
   graph->SetPoint(28,79.8,10.0333);
   graph->SetPoint(29,82.4,8.419755);
   graph->SetPoint(30,85,7.097271);
   graph->SetPoint(31,87.6,6.010473);
   graph->SetPoint(32,90.2,5.114645);
   graph->SetPoint(33,92.8,4.373745);
   graph->SetPoint(34,95.4,3.758767);
   graph->SetPoint(35,98,3.246363);
   graph->SetPoint(36,100.6,2.817736);
   graph->SetPoint(37,103.2,2.457737);
   graph->SetPoint(38,105.8,2.154131);
   graph->SetPoint(39,108.4,1.897024);
   graph->SetPoint(40,111,1.67839);
   graph->SetPoint(41,113.6,1.491705);
   graph->SetPoint(42,116.2,1.331648);
   graph->SetPoint(43,118.8,1.193867);
   graph->SetPoint(44,121.4,1.074791);
   graph->SetPoint(45,124,0.9714808);
   graph->SetPoint(46,126.6,0.8815072);
   graph->SetPoint(47,129.2,0.8028579);
   graph->SetPoint(48,131.8,0.7338589);
   graph->SetPoint(49,134.4,0.6731132);
   graph->SetPoint(50,137,0.6194508);
   graph->SetPoint(51,139.6,0.5718888);
   graph->SetPoint(52,142.2,0.5295983);
   graph->SetPoint(53,144.8,0.491878);
   graph->SetPoint(54,147.4,0.458133);
   graph->SetPoint(55,150,0.4278564);
   graph->SetPoint(56,150,0.4278564);
   graph->SetPoint(57,152.6,0.4278564);
   graph->SetPoint(58,152.6,0);
   
   TH1 *myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2 = new TH1F("myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2","Projection of Ratio WtoENu",100,3.88,166.12);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2->SetMinimum(0);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2->SetMaximum(373.2339);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2->SetDirectory(0);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2->SetStats(0);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2->SetMarkerStyle(8);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2->GetXaxis()->SetLabelFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2->GetXaxis()->SetLabelSize(0.05);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2->GetXaxis()->SetTitleSize(0.06);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2->GetXaxis()->SetTitleFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2->GetYaxis()->SetLabelFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2->GetYaxis()->SetLabelSize(0.05);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2->GetYaxis()->SetTitleSize(0.06);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2->GetYaxis()->SetTitleFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2->GetZaxis()->SetLabelFont(132);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2->GetZaxis()->SetLabelSize(0.05);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2->GetZaxis()->SetTitleSize(0.06);
   myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(myFit_Norm[nExclPFJetsHi,pfmt]_Slice[nExclPFJetsHi]2);
   
   graph->Draw("l");
   
   TH1 *frame_248129048 = new TH1D("frame_248129048","A RooPlot of "M_{T}"",50,20,150);
   frame_248129048->SetMaximum(356.2687);
   frame_248129048->SetDirectory(0);
   frame_248129048->SetStats(0);
   frame_248129048->SetMarkerStyle(8);
   frame_248129048->GetXaxis()->SetTitle("M_{T}[GeV/c^{2}]");
   frame_248129048->GetXaxis()->SetLabelFont(132);
   frame_248129048->GetXaxis()->SetLabelSize(0.05);
   frame_248129048->GetXaxis()->SetTitleSize(0.06);
   frame_248129048->GetXaxis()->SetTitleFont(132);
   frame_248129048->GetYaxis()->SetTitle("Events / ( 3 GeV/c^{2})");
   frame_248129048->GetYaxis()->SetLabelFont(132);
   frame_248129048->GetYaxis()->SetLabelSize(0.05);
   frame_248129048->GetYaxis()->SetTitleSize(0.06);
   frame_248129048->GetYaxis()->SetTitleFont(132);
   frame_248129048->GetZaxis()->SetLabelFont(132);
   frame_248129048->GetZaxis()->SetLabelSize(0.05);
   frame_248129048->GetZaxis()->SetTitleSize(0.06);
   frame_248129048->GetZaxis()->SetTitleFont(132);
   frame_248129048->Draw("AXISSAME");
   
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
