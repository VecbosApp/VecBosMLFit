{
//=========Macro generated from canvas: c/fitResult
//=========  (Wed Feb 23 19:39:00 2011) by ROOT version5.22/00d
   TCanvas *c = new TCanvas("c", "fitResult",104,25,600,600);
   gStyle->SetOptStat(0);
   c->Range(51.3253,-51.47743,123.6145,270.2565);
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
   
   TH1 *frame_a9a7e48 = new TH1D("frame_a9a7e48","A RooPlot of "Mass [GeV/c^{2}]"",40,60,120);
   frame_a9a7e48->SetMaximum(254.1698);
   frame_a9a7e48->SetDirectory(0);
   frame_a9a7e48->SetStats(0);
   frame_a9a7e48->SetMarkerStyle(8);
   frame_a9a7e48->GetXaxis()->SetTitle("M_{ee}[GeV/c^{2}]");
   frame_a9a7e48->GetXaxis()->SetLabelFont(132);
   frame_a9a7e48->GetXaxis()->SetLabelSize(0.05);
   frame_a9a7e48->GetXaxis()->SetTitleSize(0.06);
   frame_a9a7e48->GetXaxis()->SetTitleFont(132);
   frame_a9a7e48->GetYaxis()->SetTitle("Events / ( 2 GeV/c^{2})");
   frame_a9a7e48->GetYaxis()->SetLabelFont(132);
   frame_a9a7e48->GetYaxis()->SetLabelSize(0.05);
   frame_a9a7e48->GetYaxis()->SetTitleSize(0.06);
   frame_a9a7e48->GetYaxis()->SetTitleFont(132);
   frame_a9a7e48->GetZaxis()->SetLabelFont(132);
   frame_a9a7e48->GetZaxis()->SetLabelSize(0.05);
   frame_a9a7e48->GetZaxis()->SetTitleSize(0.06);
   frame_a9a7e48->GetZaxis()->SetTitleFont(132);
   frame_a9a7e48->Draw("");
   
   TGraph *graph = new TGraph(91);
   graph->SetName("myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]");
   graph->SetTitle("Projection of Ratio ZtoEE");

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#ffcc00");
   graph->SetFillColor(ci);

   ci = TColor::GetColor("#993300");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,58.5,0);
   graph->SetPoint(1,58.5,4.819017);
   graph->SetPoint(2,60,4.819017);
   graph->SetPoint(3,61.5,4.982553);
   graph->SetPoint(4,63,5.175955);
   graph->SetPoint(5,64.5,5.407026);
   graph->SetPoint(6,66,5.686287);
   graph->SetPoint(7,67.5,6.028187);
   graph->SetPoint(8,69,6.452963);
   graph->SetPoint(9,70.5,6.989602);
   graph->SetPoint(10,72,7.680644);
   graph->SetPoint(11,73.5,8.590226);
   graph->SetPoint(12,75,9.817914);
   graph->SetPoint(13,76.5,11.52319);
   graph->SetPoint(14,78,13.96988);
   graph->SetPoint(15,79.5,17.60814);
   graph->SetPoint(16,80.25,20.10076);
   graph->SetPoint(17,81,23.22545);
   graph->SetPoint(18,81.75,27.17683);
   graph->SetPoint(19,82.5,32.21165);
   graph->SetPoint(20,83.25,38.66342);
   graph->SetPoint(21,83.625,42.54868);
   graph->SetPoint(22,84,46.95291);
   graph->SetPoint(23,84.375,51.9418);
   graph->SetPoint(24,84.75,57.58447);
   graph->SetPoint(25,85.125,63.95111);
   graph->SetPoint(26,85.5,71.10942);
   graph->SetPoint(27,85.875,79.11955);
   graph->SetPoint(28,86.25,88.02711);
   graph->SetPoint(29,86.625,97.8544);
   graph->SetPoint(30,87,108.5897);
   graph->SetPoint(31,87.375,120.1751);
   graph->SetPoint(32,87.75,132.4944);
   graph->SetPoint(33,88.5,158.5134);
   graph->SetPoint(34,88.875,171.6076);
   graph->SetPoint(35,89.25,184.2303);
   graph->SetPoint(36,89.625,195.9133);
   graph->SetPoint(37,90,206.1637);
   graph->SetPoint(38,90.1875,210.6);
   graph->SetPoint(39,90.375,214.5018);
   graph->SetPoint(40,90.5625,217.8182);
   graph->SetPoint(41,90.75,220.5051);
   graph->SetPoint(42,90.9375,222.5256);
   graph->SetPoint(43,91.125,223.8517);
   graph->SetPoint(44,91.3125,224.4646);
   graph->SetPoint(45,91.5,224.1319);
   graph->SetPoint(46,91.6875,222.0987);
   graph->SetPoint(47,91.875,218.3664);
   graph->SetPoint(48,92.0625,213.054);
   graph->SetPoint(49,92.25,206.3254);
   graph->SetPoint(50,92.4375,198.3796);
   graph->SetPoint(51,92.625,189.439);
   graph->SetPoint(52,92.8125,179.7368);
   graph->SetPoint(53,93,169.506);
   graph->SetPoint(54,93.75,127.4435);
   graph->SetPoint(55,93.9375,117.4695);
   graph->SetPoint(56,94.125,107.9449);
   graph->SetPoint(57,94.3125,98.93799);
   graph->SetPoint(58,94.5,90.4928);
   graph->SetPoint(59,94.6875,82.63281);
   graph->SetPoint(60,94.875,75.36421);
   graph->SetPoint(61,95.0625,68.67946);
   graph->SetPoint(62,95.25,62.56046);
   graph->SetPoint(63,95.4375,56.98147);
   graph->SetPoint(64,95.625,51.91155);
   graph->SetPoint(65,96,43.16113);
   graph->SetPoint(66,96.375,36.026);
   graph->SetPoint(67,96.75,30.23235);
   graph->SetPoint(68,97.125,25.53453);
   graph->SetPoint(69,97.5,21.72227);
   graph->SetPoint(70,97.875,18.62098);
   graph->SetPoint(71,98.25,16.08866);
   graph->SetPoint(72,99,12.29817);
   graph->SetPoint(73,99.75,9.691906);
   graph->SetPoint(74,100.5,7.85669);
   graph->SetPoint(75,102,5.556015);
   graph->SetPoint(76,103.5,4.252361);
   graph->SetPoint(77,105,3.454913);
   graph->SetPoint(78,106.5,2.935489);
   graph->SetPoint(79,108,2.579444);
   graph->SetPoint(80,109.5,2.325033);
   graph->SetPoint(81,111,2.136939);
   graph->SetPoint(82,112.5,1.993889);
   graph->SetPoint(83,114,1.88249);
   graph->SetPoint(84,115.5,1.793982);
   graph->SetPoint(85,117,1.722447);
   graph->SetPoint(86,118.5,1.663767);
   graph->SetPoint(87,120,1.615008);
   graph->SetPoint(88,120,1.615008);
   graph->SetPoint(89,121.5,1.615008);
   graph->SetPoint(90,121.5,0);
   
   TH1 *myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1 = new TH1F("myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1","Projection of Ratio ZtoEE",100,52.2,127.8);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->SetMinimum(0);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->SetMaximum(246.9111);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->SetDirectory(0);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->SetStats(0);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->SetMarkerStyle(8);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetXaxis()->SetLabelFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetXaxis()->SetLabelSize(0.05);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetXaxis()->SetTitleSize(0.06);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetXaxis()->SetTitleFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetYaxis()->SetLabelFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetYaxis()->SetLabelSize(0.05);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetYaxis()->SetTitleSize(0.06);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetYaxis()->SetTitleFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetZaxis()->SetLabelFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetZaxis()->SetLabelSize(0.05);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetZaxis()->SetTitleSize(0.06);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]1);
   
   graph->Draw("f");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(40);
   grae->SetName("h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]");
   grae->SetTitle("Histogram of Data_plot__mee");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,60.75,2);
   grae->SetPointError(0,0.75,0.75,1.414214,1.414214);
   grae->SetPoint(1,62.25,4);
   grae->SetPointError(1,0.75,0.75,2,2);
   grae->SetPoint(2,63.75,3);
   grae->SetPointError(2,0.75,0.75,1.732051,1.732051);
   grae->SetPoint(3,65.25,8);
   grae->SetPointError(3,0.75,0.75,2.828427,2.828427);
   grae->SetPoint(4,66.75,7);
   grae->SetPointError(4,0.75,0.75,2.645751,2.645751);
   grae->SetPoint(5,68.25,2);
   grae->SetPointError(5,0.75,0.75,1.414214,1.414214);
   grae->SetPoint(6,69.75,7);
   grae->SetPointError(6,0.75,0.75,2.645751,2.645751);
   grae->SetPoint(7,71.25,13);
   grae->SetPointError(7,0.75,0.75,3.605551,3.605551);
   grae->SetPoint(8,72.75,9);
   grae->SetPointError(8,0.75,0.75,3,3);
   grae->SetPoint(9,74.25,10);
   grae->SetPointError(9,0.75,0.75,3.162278,3.162278);
   grae->SetPoint(10,75.75,17);
   grae->SetPointError(10,0.75,0.75,4.123106,4.123106);
   grae->SetPoint(11,77.25,12);
   grae->SetPointError(11,0.75,0.75,3.464102,3.464102);
   grae->SetPoint(12,78.75,16);
   grae->SetPointError(12,0.75,0.75,4,4);
   grae->SetPoint(13,80.25,21);
   grae->SetPointError(13,0.75,0.75,4.582576,4.582576);
   grae->SetPoint(14,81.75,26);
   grae->SetPointError(14,0.75,0.75,5.09902,5.09902);
   grae->SetPoint(15,83.25,36);
   grae->SetPointError(15,0.75,0.75,6,6);
   grae->SetPoint(16,84.75,59);
   grae->SetPointError(16,0.75,0.75,7.681146,7.681146);
   grae->SetPoint(17,86.25,106);
   grae->SetPointError(17,0.75,0.75,10.29563,10.29563);
   grae->SetPoint(18,87.75,120);
   grae->SetPointError(18,0.75,0.75,10.95445,10.95445);
   grae->SetPoint(19,89.25,173);
   grae->SetPointError(19,0.75,0.75,13.15295,13.15295);
   grae->SetPoint(20,90.75,227);
   grae->SetPointError(20,0.75,0.75,15.06652,15.06652);
   grae->SetPoint(21,92.25,194);
   grae->SetPointError(21,0.75,0.75,13.92839,13.92839);
   grae->SetPoint(22,93.75,127);
   grae->SetPointError(22,0.75,0.75,11.26943,11.26943);
   grae->SetPoint(23,95.25,66);
   grae->SetPointError(23,0.75,0.75,8.124038,8.124038);
   grae->SetPoint(24,96.75,28);
   grae->SetPointError(24,0.75,0.75,5.291503,5.291503);
   grae->SetPoint(25,98.25,19);
   grae->SetPointError(25,0.75,0.75,4.358899,4.358899);
   grae->SetPoint(26,99.75,13);
   grae->SetPointError(26,0.75,0.75,3.605551,3.605551);
   grae->SetPoint(27,101.25,6);
   grae->SetPointError(27,0.75,0.75,2.44949,2.44949);
   grae->SetPoint(28,102.75,5);
   grae->SetPointError(28,0.75,0.75,2.236068,2.236068);
   grae->SetPoint(29,104.25,5);
   grae->SetPointError(29,0.75,0.75,2.236068,2.236068);
   grae->SetPoint(30,105.75,3);
   grae->SetPointError(30,0.75,0.75,1.732051,1.732051);
   grae->SetPoint(31,107.25,4);
   grae->SetPointError(31,0.75,0.75,2,2);
   grae->SetPoint(32,108.75,3);
   grae->SetPointError(32,0.75,0.75,1.732051,1.732051);
   grae->SetPoint(33,110.25,0);
   grae->SetPointError(33,0.75,0.75,0,0);
   grae->SetPoint(34,111.75,2);
   grae->SetPointError(34,0.75,0.75,1.414214,1.414214);
   grae->SetPoint(35,113.25,2);
   grae->SetPointError(35,0.75,0.75,1.414214,1.414214);
   grae->SetPoint(36,114.75,4);
   grae->SetPointError(36,0.75,0.75,2,2);
   grae->SetPoint(37,116.25,1);
   grae->SetPointError(37,0.75,0.75,1,1);
   grae->SetPoint(38,117.75,1);
   grae->SetPointError(38,0.75,0.75,1,1);
   grae->SetPoint(39,119.25,0);
   grae->SetPointError(39,0.75,0.75,0,0);
   
   TH1 *h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1 = new TH1F("h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1","Histogram of Data_plot__mee",100,54,126);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->SetMinimum(0);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->SetMaximum(266.2732);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->SetDirectory(0);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->SetStats(0);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->SetMarkerStyle(8);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetXaxis()->SetLabelFont(132);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetXaxis()->SetLabelSize(0.05);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetXaxis()->SetTitleSize(0.06);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetXaxis()->SetTitleFont(132);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetYaxis()->SetLabelFont(132);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetYaxis()->SetLabelSize(0.05);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetYaxis()->SetTitleSize(0.06);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetYaxis()->SetTitleFont(132);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetZaxis()->SetLabelFont(132);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetZaxis()->SetLabelSize(0.05);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetZaxis()->SetTitleSize(0.06);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1->GetZaxis()->SetTitleFont(132);
   grae->SetHistogram(h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]1);
   
   grae->Draw("p");
   
   graph = new TGraph(91);
   graph->SetName("myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]");
   graph->SetTitle("Projection of Ratio ZtoEE");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#ff6600");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,58.5,0);
   graph->SetPoint(1,58.5,4.819017);
   graph->SetPoint(2,60,4.819017);
   graph->SetPoint(3,61.5,4.982553);
   graph->SetPoint(4,63,5.175955);
   graph->SetPoint(5,64.5,5.407026);
   graph->SetPoint(6,66,5.686287);
   graph->SetPoint(7,67.5,6.028187);
   graph->SetPoint(8,69,6.452963);
   graph->SetPoint(9,70.5,6.989602);
   graph->SetPoint(10,72,7.680644);
   graph->SetPoint(11,73.5,8.590226);
   graph->SetPoint(12,75,9.817914);
   graph->SetPoint(13,76.5,11.52319);
   graph->SetPoint(14,78,13.96988);
   graph->SetPoint(15,79.5,17.60814);
   graph->SetPoint(16,80.25,20.10076);
   graph->SetPoint(17,81,23.22545);
   graph->SetPoint(18,81.75,27.17683);
   graph->SetPoint(19,82.5,32.21165);
   graph->SetPoint(20,83.25,38.66342);
   graph->SetPoint(21,83.625,42.54868);
   graph->SetPoint(22,84,46.95291);
   graph->SetPoint(23,84.375,51.9418);
   graph->SetPoint(24,84.75,57.58447);
   graph->SetPoint(25,85.125,63.95111);
   graph->SetPoint(26,85.5,71.10942);
   graph->SetPoint(27,85.875,79.11955);
   graph->SetPoint(28,86.25,88.02711);
   graph->SetPoint(29,86.625,97.8544);
   graph->SetPoint(30,87,108.5897);
   graph->SetPoint(31,87.375,120.1751);
   graph->SetPoint(32,87.75,132.4944);
   graph->SetPoint(33,88.5,158.5134);
   graph->SetPoint(34,88.875,171.6076);
   graph->SetPoint(35,89.25,184.2303);
   graph->SetPoint(36,89.625,195.9133);
   graph->SetPoint(37,90,206.1637);
   graph->SetPoint(38,90.1875,210.6);
   graph->SetPoint(39,90.375,214.5018);
   graph->SetPoint(40,90.5625,217.8182);
   graph->SetPoint(41,90.75,220.5051);
   graph->SetPoint(42,90.9375,222.5256);
   graph->SetPoint(43,91.125,223.8517);
   graph->SetPoint(44,91.3125,224.4646);
   graph->SetPoint(45,91.5,224.1319);
   graph->SetPoint(46,91.6875,222.0987);
   graph->SetPoint(47,91.875,218.3664);
   graph->SetPoint(48,92.0625,213.054);
   graph->SetPoint(49,92.25,206.3254);
   graph->SetPoint(50,92.4375,198.3796);
   graph->SetPoint(51,92.625,189.439);
   graph->SetPoint(52,92.8125,179.7368);
   graph->SetPoint(53,93,169.506);
   graph->SetPoint(54,93.75,127.4435);
   graph->SetPoint(55,93.9375,117.4695);
   graph->SetPoint(56,94.125,107.9449);
   graph->SetPoint(57,94.3125,98.93799);
   graph->SetPoint(58,94.5,90.4928);
   graph->SetPoint(59,94.6875,82.63281);
   graph->SetPoint(60,94.875,75.36421);
   graph->SetPoint(61,95.0625,68.67946);
   graph->SetPoint(62,95.25,62.56046);
   graph->SetPoint(63,95.4375,56.98147);
   graph->SetPoint(64,95.625,51.91155);
   graph->SetPoint(65,96,43.16113);
   graph->SetPoint(66,96.375,36.026);
   graph->SetPoint(67,96.75,30.23235);
   graph->SetPoint(68,97.125,25.53453);
   graph->SetPoint(69,97.5,21.72227);
   graph->SetPoint(70,97.875,18.62098);
   graph->SetPoint(71,98.25,16.08866);
   graph->SetPoint(72,99,12.29817);
   graph->SetPoint(73,99.75,9.691906);
   graph->SetPoint(74,100.5,7.85669);
   graph->SetPoint(75,102,5.556015);
   graph->SetPoint(76,103.5,4.252361);
   graph->SetPoint(77,105,3.454913);
   graph->SetPoint(78,106.5,2.935489);
   graph->SetPoint(79,108,2.579444);
   graph->SetPoint(80,109.5,2.325033);
   graph->SetPoint(81,111,2.136939);
   graph->SetPoint(82,112.5,1.993889);
   graph->SetPoint(83,114,1.88249);
   graph->SetPoint(84,115.5,1.793982);
   graph->SetPoint(85,117,1.722447);
   graph->SetPoint(86,118.5,1.663767);
   graph->SetPoint(87,120,1.615008);
   graph->SetPoint(88,120,1.615008);
   graph->SetPoint(89,121.5,1.615008);
   graph->SetPoint(90,121.5,0);
   
   TH1 *myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2 = new TH1F("myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2","Projection of Ratio ZtoEE",100,52.2,127.8);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->SetMinimum(0);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->SetMaximum(246.9111);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->SetDirectory(0);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->SetStats(0);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->SetMarkerStyle(8);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetXaxis()->SetLabelFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetXaxis()->SetLabelSize(0.05);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetXaxis()->SetTitleSize(0.06);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetXaxis()->SetTitleFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetYaxis()->SetLabelFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetYaxis()->SetLabelSize(0.05);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetYaxis()->SetTitleSize(0.06);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetYaxis()->SetTitleFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetZaxis()->SetLabelFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetZaxis()->SetLabelSize(0.05);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetZaxis()->SetTitleSize(0.06);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]2);
   
   graph->Draw("l");
   
   graph = new TGraph(46);
   graph->SetName("myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]");
   graph->SetTitle("Projection of Ratio ZtoEE");

   ci = TColor::GetColor("#cc00ff");
   graph->SetFillColor(ci);

   ci = TColor::GetColor("#0000ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,58.5,0);
   graph->SetPoint(1,58.5,7.768373e-06);
   graph->SetPoint(2,60,7.768373e-06);
   graph->SetPoint(3,61.5,7.768373e-06);
   graph->SetPoint(4,63,7.768373e-06);
   graph->SetPoint(5,64.5,7.768373e-06);
   graph->SetPoint(6,66,7.768373e-06);
   graph->SetPoint(7,67.5,7.768373e-06);
   graph->SetPoint(8,69,7.768373e-06);
   graph->SetPoint(9,70.5,7.768373e-06);
   graph->SetPoint(10,72,7.768373e-06);
   graph->SetPoint(11,73.5,7.768373e-06);
   graph->SetPoint(12,75,7.768373e-06);
   graph->SetPoint(13,76.5,7.768373e-06);
   graph->SetPoint(14,78,7.768373e-06);
   graph->SetPoint(15,79.5,7.768373e-06);
   graph->SetPoint(16,81,7.768373e-06);
   graph->SetPoint(17,82.5,7.768373e-06);
   graph->SetPoint(18,84,7.768373e-06);
   graph->SetPoint(19,85.5,7.768373e-06);
   graph->SetPoint(20,87,7.768373e-06);
   graph->SetPoint(21,88.5,7.768373e-06);
   graph->SetPoint(22,90,7.768373e-06);
   graph->SetPoint(23,91.5,7.768373e-06);
   graph->SetPoint(24,93,7.768373e-06);
   graph->SetPoint(25,94.5,7.768373e-06);
   graph->SetPoint(26,96,7.768373e-06);
   graph->SetPoint(27,97.5,7.768373e-06);
   graph->SetPoint(28,99,7.768373e-06);
   graph->SetPoint(29,100.5,7.768373e-06);
   graph->SetPoint(30,102,7.768373e-06);
   graph->SetPoint(31,103.5,7.768373e-06);
   graph->SetPoint(32,105,7.768373e-06);
   graph->SetPoint(33,106.5,7.768373e-06);
   graph->SetPoint(34,108,7.768373e-06);
   graph->SetPoint(35,109.5,7.768373e-06);
   graph->SetPoint(36,111,7.768373e-06);
   graph->SetPoint(37,112.5,7.768373e-06);
   graph->SetPoint(38,114,7.768373e-06);
   graph->SetPoint(39,115.5,7.768373e-06);
   graph->SetPoint(40,117,7.768373e-06);
   graph->SetPoint(41,118.5,7.768373e-06);
   graph->SetPoint(42,120,7.768373e-06);
   graph->SetPoint(43,120,7.768373e-06);
   graph->SetPoint(44,121.5,7.768373e-06);
   graph->SetPoint(45,121.5,0);
   
   TH1 *myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3 = new TH1F("myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3","Projection of Ratio ZtoEE",100,52.2,127.8);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3->SetMinimum(0);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3->SetMaximum(8.54521e-06);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3->SetDirectory(0);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3->SetStats(0);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3->SetMarkerStyle(8);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3->GetXaxis()->SetLabelFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3->GetXaxis()->SetLabelSize(0.05);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3->GetXaxis()->SetTitleSize(0.06);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3->GetXaxis()->SetTitleFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3->GetYaxis()->SetLabelFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3->GetYaxis()->SetLabelSize(0.05);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3->GetYaxis()->SetTitleSize(0.06);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3->GetYaxis()->SetTitleFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3->GetZaxis()->SetLabelFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3->GetZaxis()->SetLabelSize(0.05);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3->GetZaxis()->SetTitleSize(0.06);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]3);
   
   graph->Draw("f");
   
   graph = new TGraph(46);
   graph->SetName("myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]");
   graph->SetTitle("Projection of Ratio ZtoEE");
   graph->SetFillColor(1);

   ci = TColor::GetColor("#330066");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,58.5,0);
   graph->SetPoint(1,58.5,7.768373e-06);
   graph->SetPoint(2,60,7.768373e-06);
   graph->SetPoint(3,61.5,7.768373e-06);
   graph->SetPoint(4,63,7.768373e-06);
   graph->SetPoint(5,64.5,7.768373e-06);
   graph->SetPoint(6,66,7.768373e-06);
   graph->SetPoint(7,67.5,7.768373e-06);
   graph->SetPoint(8,69,7.768373e-06);
   graph->SetPoint(9,70.5,7.768373e-06);
   graph->SetPoint(10,72,7.768373e-06);
   graph->SetPoint(11,73.5,7.768373e-06);
   graph->SetPoint(12,75,7.768373e-06);
   graph->SetPoint(13,76.5,7.768373e-06);
   graph->SetPoint(14,78,7.768373e-06);
   graph->SetPoint(15,79.5,7.768373e-06);
   graph->SetPoint(16,81,7.768373e-06);
   graph->SetPoint(17,82.5,7.768373e-06);
   graph->SetPoint(18,84,7.768373e-06);
   graph->SetPoint(19,85.5,7.768373e-06);
   graph->SetPoint(20,87,7.768373e-06);
   graph->SetPoint(21,88.5,7.768373e-06);
   graph->SetPoint(22,90,7.768373e-06);
   graph->SetPoint(23,91.5,7.768373e-06);
   graph->SetPoint(24,93,7.768373e-06);
   graph->SetPoint(25,94.5,7.768373e-06);
   graph->SetPoint(26,96,7.768373e-06);
   graph->SetPoint(27,97.5,7.768373e-06);
   graph->SetPoint(28,99,7.768373e-06);
   graph->SetPoint(29,100.5,7.768373e-06);
   graph->SetPoint(30,102,7.768373e-06);
   graph->SetPoint(31,103.5,7.768373e-06);
   graph->SetPoint(32,105,7.768373e-06);
   graph->SetPoint(33,106.5,7.768373e-06);
   graph->SetPoint(34,108,7.768373e-06);
   graph->SetPoint(35,109.5,7.768373e-06);
   graph->SetPoint(36,111,7.768373e-06);
   graph->SetPoint(37,112.5,7.768373e-06);
   graph->SetPoint(38,114,7.768373e-06);
   graph->SetPoint(39,115.5,7.768373e-06);
   graph->SetPoint(40,117,7.768373e-06);
   graph->SetPoint(41,118.5,7.768373e-06);
   graph->SetPoint(42,120,7.768373e-06);
   graph->SetPoint(43,120,7.768373e-06);
   graph->SetPoint(44,121.5,7.768373e-06);
   graph->SetPoint(45,121.5,0);
   
   TH1 *myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4 = new TH1F("myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4","Projection of Ratio ZtoEE",100,52.2,127.8);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4->SetMinimum(0);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4->SetMaximum(8.54521e-06);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4->SetDirectory(0);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4->SetStats(0);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4->SetMarkerStyle(8);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4->GetXaxis()->SetLabelFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4->GetXaxis()->SetLabelSize(0.05);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4->GetXaxis()->SetTitleSize(0.06);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4->GetXaxis()->SetTitleFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4->GetYaxis()->SetLabelFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4->GetYaxis()->SetLabelSize(0.05);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4->GetYaxis()->SetTitleSize(0.06);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4->GetYaxis()->SetTitleFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4->GetZaxis()->SetLabelFont(132);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4->GetZaxis()->SetLabelSize(0.05);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4->GetZaxis()->SetTitleSize(0.06);
   myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(myFit_Norm[mee,nExclPFJetsHi]_Slice[nExclPFJetsHi]_Comp[myFit_B1j]4);
   
   graph->Draw("l");
   
   grae = new TGraphAsymmErrors(40);
   grae->SetName("h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]");
   grae->SetTitle("Histogram of Data_plot__mee");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,60.75,2);
   grae->SetPointError(0,0.75,0.75,1.414214,1.414214);
   grae->SetPoint(1,62.25,4);
   grae->SetPointError(1,0.75,0.75,2,2);
   grae->SetPoint(2,63.75,3);
   grae->SetPointError(2,0.75,0.75,1.732051,1.732051);
   grae->SetPoint(3,65.25,8);
   grae->SetPointError(3,0.75,0.75,2.828427,2.828427);
   grae->SetPoint(4,66.75,7);
   grae->SetPointError(4,0.75,0.75,2.645751,2.645751);
   grae->SetPoint(5,68.25,2);
   grae->SetPointError(5,0.75,0.75,1.414214,1.414214);
   grae->SetPoint(6,69.75,7);
   grae->SetPointError(6,0.75,0.75,2.645751,2.645751);
   grae->SetPoint(7,71.25,13);
   grae->SetPointError(7,0.75,0.75,3.605551,3.605551);
   grae->SetPoint(8,72.75,9);
   grae->SetPointError(8,0.75,0.75,3,3);
   grae->SetPoint(9,74.25,10);
   grae->SetPointError(9,0.75,0.75,3.162278,3.162278);
   grae->SetPoint(10,75.75,17);
   grae->SetPointError(10,0.75,0.75,4.123106,4.123106);
   grae->SetPoint(11,77.25,12);
   grae->SetPointError(11,0.75,0.75,3.464102,3.464102);
   grae->SetPoint(12,78.75,16);
   grae->SetPointError(12,0.75,0.75,4,4);
   grae->SetPoint(13,80.25,21);
   grae->SetPointError(13,0.75,0.75,4.582576,4.582576);
   grae->SetPoint(14,81.75,26);
   grae->SetPointError(14,0.75,0.75,5.09902,5.09902);
   grae->SetPoint(15,83.25,36);
   grae->SetPointError(15,0.75,0.75,6,6);
   grae->SetPoint(16,84.75,59);
   grae->SetPointError(16,0.75,0.75,7.681146,7.681146);
   grae->SetPoint(17,86.25,106);
   grae->SetPointError(17,0.75,0.75,10.29563,10.29563);
   grae->SetPoint(18,87.75,120);
   grae->SetPointError(18,0.75,0.75,10.95445,10.95445);
   grae->SetPoint(19,89.25,173);
   grae->SetPointError(19,0.75,0.75,13.15295,13.15295);
   grae->SetPoint(20,90.75,227);
   grae->SetPointError(20,0.75,0.75,15.06652,15.06652);
   grae->SetPoint(21,92.25,194);
   grae->SetPointError(21,0.75,0.75,13.92839,13.92839);
   grae->SetPoint(22,93.75,127);
   grae->SetPointError(22,0.75,0.75,11.26943,11.26943);
   grae->SetPoint(23,95.25,66);
   grae->SetPointError(23,0.75,0.75,8.124038,8.124038);
   grae->SetPoint(24,96.75,28);
   grae->SetPointError(24,0.75,0.75,5.291503,5.291503);
   grae->SetPoint(25,98.25,19);
   grae->SetPointError(25,0.75,0.75,4.358899,4.358899);
   grae->SetPoint(26,99.75,13);
   grae->SetPointError(26,0.75,0.75,3.605551,3.605551);
   grae->SetPoint(27,101.25,6);
   grae->SetPointError(27,0.75,0.75,2.44949,2.44949);
   grae->SetPoint(28,102.75,5);
   grae->SetPointError(28,0.75,0.75,2.236068,2.236068);
   grae->SetPoint(29,104.25,5);
   grae->SetPointError(29,0.75,0.75,2.236068,2.236068);
   grae->SetPoint(30,105.75,3);
   grae->SetPointError(30,0.75,0.75,1.732051,1.732051);
   grae->SetPoint(31,107.25,4);
   grae->SetPointError(31,0.75,0.75,2,2);
   grae->SetPoint(32,108.75,3);
   grae->SetPointError(32,0.75,0.75,1.732051,1.732051);
   grae->SetPoint(33,110.25,0);
   grae->SetPointError(33,0.75,0.75,0,0);
   grae->SetPoint(34,111.75,2);
   grae->SetPointError(34,0.75,0.75,1.414214,1.414214);
   grae->SetPoint(35,113.25,2);
   grae->SetPointError(35,0.75,0.75,1.414214,1.414214);
   grae->SetPoint(36,114.75,4);
   grae->SetPointError(36,0.75,0.75,2,2);
   grae->SetPoint(37,116.25,1);
   grae->SetPointError(37,0.75,0.75,1,1);
   grae->SetPoint(38,117.75,1);
   grae->SetPointError(38,0.75,0.75,1,1);
   grae->SetPoint(39,119.25,0);
   grae->SetPointError(39,0.75,0.75,0,0);
   
   TH1 *h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2 = new TH1F("h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2","Histogram of Data_plot__mee",100,54,126);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2->SetMinimum(0);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2->SetMaximum(266.2732);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2->SetDirectory(0);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2->SetStats(0);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2->SetMarkerStyle(8);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2->GetXaxis()->SetLabelFont(132);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2->GetXaxis()->SetLabelSize(0.05);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2->GetXaxis()->SetTitleSize(0.06);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2->GetXaxis()->SetTitleFont(132);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2->GetYaxis()->SetLabelFont(132);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2->GetYaxis()->SetLabelSize(0.05);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2->GetYaxis()->SetTitleSize(0.06);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2->GetYaxis()->SetTitleFont(132);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2->GetZaxis()->SetLabelFont(132);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2->GetZaxis()->SetLabelSize(0.05);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2->GetZaxis()->SetTitleSize(0.06);
   h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2->GetZaxis()->SetTitleFont(132);
   grae->SetHistogram(h_Data_Cut[(nExclPFJetsHi > (1-0.5) )&& (nExclPFJetsHi < (1 + 0.5) )]2);
   
   grae->Draw("p");
   
   TH1 *frame_a9a7e48 = new TH1D("frame_a9a7e48","A RooPlot of "Mass [GeV/c^{2}]"",40,60,120);
   frame_a9a7e48->SetMaximum(254.1698);
   frame_a9a7e48->SetDirectory(0);
   frame_a9a7e48->SetStats(0);
   frame_a9a7e48->SetMarkerStyle(8);
   frame_a9a7e48->GetXaxis()->SetTitle("M_{ee}[GeV/c^{2}]");
   frame_a9a7e48->GetXaxis()->SetLabelFont(132);
   frame_a9a7e48->GetXaxis()->SetLabelSize(0.05);
   frame_a9a7e48->GetXaxis()->SetTitleSize(0.06);
   frame_a9a7e48->GetXaxis()->SetTitleFont(132);
   frame_a9a7e48->GetYaxis()->SetTitle("Events / ( 2 GeV/c^{2})");
   frame_a9a7e48->GetYaxis()->SetLabelFont(132);
   frame_a9a7e48->GetYaxis()->SetLabelSize(0.05);
   frame_a9a7e48->GetYaxis()->SetTitleSize(0.06);
   frame_a9a7e48->GetYaxis()->SetTitleFont(132);
   frame_a9a7e48->GetZaxis()->SetLabelFont(132);
   frame_a9a7e48->GetZaxis()->SetLabelSize(0.05);
   frame_a9a7e48->GetZaxis()->SetTitleSize(0.06);
   frame_a9a7e48->GetZaxis()->SetTitleFont(132);
   frame_a9a7e48->Draw("AXISSAME");
   
   TPaveText *pt = new TPaveText(0.1,0.96,0.8,0.98,"brNDC");
   pt->SetBorderSize(0);
   pt->SetTextAlign(12);
   pt->SetTextFont(72);
   pt->SetTextSize(0.03);
   TText *text = pt->AddText("CMS Preliminary 2011, #sqrt{s}=7 TeV, L_{int}=36 pb^{-1}");
   pt->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
