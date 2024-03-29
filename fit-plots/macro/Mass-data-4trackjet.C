{
//=========Macro generated from canvas: c/fitResult
//=========  (Wed Mar 11 12:20:54 2009) by ROOT version5.18/00a
   TCanvas *c = new TCanvas("c", "fitResult",4,21,600,300);
   gStyle->SetOptStat(0);
   c->Range(52.77108,-2.719704,113.012,14.27845);
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
   
   TH1 *frame_0b20fe70 = new TH1D("frame_0b20fe70","A RooPlot of "Mass [GeV/c^{2}]"",12,60,110);
   frame_0b20fe70->SetMaximum(13.42854);
   frame_0b20fe70->SetDirectory(0);
   frame_0b20fe70->SetStats(0);
   frame_0b20fe70->SetMarkerStyle(8);
   frame_0b20fe70->GetXaxis()->SetTitle("m_{ee}[GeV/c^{2}]");
   frame_0b20fe70->GetXaxis()->SetLabelFont(132);
   frame_0b20fe70->GetXaxis()->SetLabelSize(0.05);
   frame_0b20fe70->GetXaxis()->SetTitleSize(0.06);
   frame_0b20fe70->GetXaxis()->SetTitleFont(132);
   frame_0b20fe70->GetYaxis()->SetTitle("Events");
   frame_0b20fe70->GetYaxis()->SetLabelFont(132);
   frame_0b20fe70->GetYaxis()->SetLabelSize(0.05);
   frame_0b20fe70->GetYaxis()->SetTitleSize(0.06);
   frame_0b20fe70->GetYaxis()->SetTitleFont(132);
   frame_0b20fe70->GetZaxis()->SetLabelFont(132);
   frame_0b20fe70->GetZaxis()->SetLabelSize(0.05);
   frame_0b20fe70->GetZaxis()->SetTitleSize(0.06);
   frame_0b20fe70->GetZaxis()->SetTitleFont(132);
   frame_0b20fe70->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(12);
   grae->SetName("data_plot__mass");
   grae->SetTitle("Histogram of data_plot__mass");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,62.08333,0.3650521);
   grae->SetPointError(0,2.083333,2.083333,0.1100674,0.1100674);
   grae->SetPoint(1,66.25,0.298679);
   grae->SetPointError(1,2.083333,2.083333,0.09955968,0.09955968);
   grae->SetPoint(2,70.41667,0.5869748);
   grae->SetPointError(2,2.083333,2.083333,0.3050026,0.3050026);
   grae->SetPoint(3,74.58333,0.8088975);
   grae->SetPointError(3,2.083333,2.083333,0.4170592,0.4170592);
   grae->SetPoint(4,78.75,0.5206017);
   grae->SetPointError(4,2.083333,2.083333,0.30137,0.30137);
   grae->SetPoint(5,82.91667,2.605046);
   grae->SetPointError(5,2.083333,2.083333,0.8214791,0.8214791);
   grae->SetPoint(6,87.08333,6.442066);
   grae->SetPointError(6,2.083333,2.083333,1.353448,1.353448);
   grae->SetPoint(7,91.25,11.032);
   grae->SetPointError(7,2.083333,2.083333,1.757086,1.757086);
   grae->SetPoint(8,95.41667,4.112897);
   grae->SetPointError(8,2.083333,2.083333,1.045276,1.045276);
   grae->SetPoint(9,99.58333,1.872904);
   grae->SetPointError(9,2.083333,2.083333,0.6556599,0.6556599);
   grae->SetPoint(10,103.75,0.7757109);
   grae->SetPointError(10,2.083333,2.083333,0.4157367,0.4157367);
   grae->SetPoint(11,107.9167,0.2654925);
   grae->SetPointError(11,2.083333,2.083333,0.09386576,0.09386576);
   grae->Draw("p");
   
   TGraph *graph = new TGraph(80);
   graph->SetName("curve_myFitProjected");
   graph->SetTitle("Projection of Ratio ZtoEE");
   graph->SetFillColor(1);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,55.83333,0);
   graph->SetPoint(1,55.83333,0.4902916);
   graph->SetPoint(2,60,0.4902916);
   graph->SetPoint(3,64.16667,0.518081);
   graph->SetPoint(4,68.33333,0.5571961);
   graph->SetPoint(5,72.5,0.6247443);
   graph->SetPoint(6,74.58333,0.6829494);
   graph->SetPoint(7,76.66667,0.775999);
   graph->SetPoint(8,77.70833,0.8449975);
   graph->SetPoint(9,78.75,0.937978);
   graph->SetPoint(10,79.79167,1.066304);
   graph->SetPoint(11,80.83333,1.247732);
   graph->SetPoint(12,81.35417,1.366547);
   graph->SetPoint(13,81.875,1.51018);
   graph->SetPoint(14,82.39583,1.684615);
   graph->SetPoint(15,82.91667,1.897249);
   graph->SetPoint(16,83.4375,2.157094);
   graph->SetPoint(17,83.95833,2.474903);
   graph->SetPoint(18,84.47917,2.863102);
   graph->SetPoint(19,84.73958,3.087843);
   graph->SetPoint(20,85,3.335361);
   graph->SetPoint(21,85.26042,3.607389);
   graph->SetPoint(22,85.52083,3.905564);
   graph->SetPoint(23,85.78125,4.23134);
   graph->SetPoint(24,86.04167,4.585881);
   graph->SetPoint(25,86.30208,4.969932);
   graph->SetPoint(26,86.5625,5.383677);
   graph->SetPoint(27,86.82292,5.826569);
   graph->SetPoint(28,87.08333,6.297164);
   graph->SetPoint(29,89.16667,10.47799);
   graph->SetPoint(30,89.42708,10.92614);
   graph->SetPoint(31,89.6875,11.32112);
   graph->SetPoint(32,89.94792,11.65184);
   graph->SetPoint(33,90.20833,11.90853);
   graph->SetPoint(34,90.33854,12.00655);
   graph->SetPoint(35,90.46875,12.08327);
   graph->SetPoint(36,90.59896,12.13807);
   graph->SetPoint(37,90.72917,12.1705);
   graph->SetPoint(38,90.85938,12.18029);
   graph->SetPoint(39,90.98958,12.16163);
   graph->SetPoint(40,91.11979,12.11029);
   graph->SetPoint(41,91.25,12.02688);
   graph->SetPoint(42,91.38021,11.9124);
   graph->SetPoint(43,91.51042,11.76818);
   graph->SetPoint(44,91.64062,11.5959);
   graph->SetPoint(45,91.77083,11.3975);
   graph->SetPoint(46,91.90104,11.17515);
   graph->SetPoint(47,92.03125,10.93122);
   graph->SetPoint(48,92.29167,10.38867);
   graph->SetPoint(49,92.55208,9.79058);
   graph->SetPoint(50,92.8125,9.157503);
   graph->SetPoint(51,93.33333,7.860722);
   graph->SetPoint(52,93.59375,7.227809);
   graph->SetPoint(53,93.85417,6.620733);
   graph->SetPoint(54,94.11458,6.047347);
   graph->SetPoint(55,94.375,5.512759);
   graph->SetPoint(56,94.63542,5.019732);
   graph->SetPoint(57,94.89583,4.569123);
   graph->SetPoint(58,95.15625,4.160331);
   graph->SetPoint(59,95.41667,3.791702);
   graph->SetPoint(60,95.67708,3.460877);
   graph->SetPoint(61,95.9375,3.165074);
   graph->SetPoint(62,96.19792,2.901312);
   graph->SetPoint(63,96.45833,2.666573);
   graph->SetPoint(64,96.71875,2.457917);
   graph->SetPoint(65,96.97917,2.272555);
   graph->SetPoint(66,97.5,1.961582);
   graph->SetPoint(67,98.02083,1.715622);
   graph->SetPoint(68,98.54167,1.520161);
   graph->SetPoint(69,99.0625,1.36382);
   graph->SetPoint(70,99.58333,1.237814);
   graph->SetPoint(71,100.625,1.05147);
   graph->SetPoint(72,101.6667,0.9241625);
   graph->SetPoint(73,102.7083,0.8341526);
   graph->SetPoint(74,103.75,0.7684142);
   graph->SetPoint(75,105.8333,0.6806637);
   graph->SetPoint(76,110,0.587899);
   graph->SetPoint(77,110,0.587899);
   graph->SetPoint(78,114.1667,0.587899);
   graph->SetPoint(79,114.1667,0);
   graph->Draw("l");
   
   graph = new TGraph(54);
   graph->SetName("curve_myFitProjected");
   graph->SetTitle("Projection of Ratio ZtoEE");
   graph->SetFillColor(1);
   graph->SetLineStyle(2);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,55.83333,0);
   graph->SetPoint(1,55.83333,0.348486);
   graph->SetPoint(2,60,0.348486);
   graph->SetPoint(3,61.04167,0.351145);
   graph->SetPoint(4,62.08333,0.3536886);
   graph->SetPoint(5,63.125,0.3561171);
   graph->SetPoint(6,64.16667,0.3584303);
   graph->SetPoint(7,65.20833,0.3606283);
   graph->SetPoint(8,66.25,0.362711);
   graph->SetPoint(9,67.29167,0.3646785);
   graph->SetPoint(10,68.33333,0.3665307);
   graph->SetPoint(11,69.375,0.3682678);
   graph->SetPoint(12,70.41667,0.3698895);
   graph->SetPoint(13,71.45833,0.3713961);
   graph->SetPoint(14,72.5,0.3727874);
   graph->SetPoint(15,73.54167,0.3740634);
   graph->SetPoint(16,74.58333,0.3752242);
   graph->SetPoint(17,75.625,0.3762698);
   graph->SetPoint(18,76.66667,0.3772001);
   graph->SetPoint(19,77.70833,0.3780152);
   graph->SetPoint(20,78.75,0.3787151);
   graph->SetPoint(21,79.79167,0.3792997);
   graph->SetPoint(22,80.83333,0.3797691);
   graph->SetPoint(23,81.875,0.3801232);
   graph->SetPoint(24,82.91667,0.3803621);
   graph->SetPoint(25,83.95833,0.3804857);
   graph->SetPoint(26,85,0.3804942);
   graph->SetPoint(27,86.04167,0.3803873);
   graph->SetPoint(28,87.08333,0.3801653);
   graph->SetPoint(29,88.125,0.379828);
   graph->SetPoint(30,89.16667,0.3793754);
   graph->SetPoint(31,90.20833,0.3788076);
   graph->SetPoint(32,91.25,0.3781246);
   graph->SetPoint(33,92.29167,0.3773263);
   graph->SetPoint(34,93.33333,0.3764128);
   graph->SetPoint(35,94.375,0.3753841);
   graph->SetPoint(36,95.41667,0.3742401);
   graph->SetPoint(37,96.45833,0.3729809);
   graph->SetPoint(38,97.5,0.3716064);
   graph->SetPoint(39,98.54167,0.3701167);
   graph->SetPoint(40,99.58333,0.3685118);
   graph->SetPoint(41,100.625,0.3667916);
   graph->SetPoint(42,101.6667,0.3649562);
   graph->SetPoint(43,102.7083,0.3630055);
   graph->SetPoint(44,103.75,0.3609396);
   graph->SetPoint(45,104.7917,0.3587585);
   graph->SetPoint(46,105.8333,0.3564621);
   graph->SetPoint(47,106.875,0.3540505);
   graph->SetPoint(48,107.9167,0.3515236);
   graph->SetPoint(49,108.9583,0.3488815);
   graph->SetPoint(50,110,0.3461242);
   graph->SetPoint(51,110,0.3461242);
   graph->SetPoint(52,114.1667,0.3461242);
   graph->SetPoint(53,114.1667,0);
   graph->Draw("l");
   
   TH1 *frame_0b20fe70 = new TH1D("frame_0b20fe70","A RooPlot of "Mass [GeV/c^{2}]"",12,60,110);
   frame_0b20fe70->SetMaximum(13.42854);
   frame_0b20fe70->SetDirectory(0);
   frame_0b20fe70->SetStats(0);
   frame_0b20fe70->SetMarkerStyle(8);
   frame_0b20fe70->GetXaxis()->SetTitle("m_{ee}[GeV/c^{2}]");
   frame_0b20fe70->GetXaxis()->SetLabelFont(132);
   frame_0b20fe70->GetXaxis()->SetLabelSize(0.05);
   frame_0b20fe70->GetXaxis()->SetTitleSize(0.06);
   frame_0b20fe70->GetXaxis()->SetTitleFont(132);
   frame_0b20fe70->GetYaxis()->SetTitle("Events");
   frame_0b20fe70->GetYaxis()->SetLabelFont(132);
   frame_0b20fe70->GetYaxis()->SetLabelSize(0.05);
   frame_0b20fe70->GetYaxis()->SetTitleSize(0.06);
   frame_0b20fe70->GetYaxis()->SetTitleFont(132);
   frame_0b20fe70->GetZaxis()->SetLabelFont(132);
   frame_0b20fe70->GetZaxis()->SetLabelSize(0.05);
   frame_0b20fe70->GetZaxis()->SetTitleSize(0.06);
   frame_0b20fe70->GetZaxis()->SetTitleFont(132);
   frame_0b20fe70->Draw("axissame");
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
