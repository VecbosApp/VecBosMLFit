{
//=========Macro generated from canvas: c/fitResult
//=========  (Sun Mar  8 18:50:44 2009) by ROOT version5.18/00a
   TCanvas *c = new TCanvas("c", "fitResult",4,21,600,300);
   gStyle->SetOptStat(0);
   c->Range(-1.095783,-8.464343,0.9524096,44.4378);
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
   
   TH1 *frame_0ab04c48 = new TH1D("frame_0ab04c48","A RooPlot of "sin #phi_{MHT-MET}"",12,-0.85,0.85);
   frame_0ab04c48->SetMaximum(41.79269);
   frame_0ab04c48->SetDirectory(0);
   frame_0ab04c48->SetStats(0);
   frame_0ab04c48->SetMarkerStyle(8);
   frame_0ab04c48->GetXaxis()->SetTitle("sin(#phi_{MHT,MET})");
   frame_0ab04c48->GetXaxis()->SetLabelFont(132);
   frame_0ab04c48->GetXaxis()->SetLabelSize(0.05);
   frame_0ab04c48->GetXaxis()->SetTitleSize(0.06);
   frame_0ab04c48->GetXaxis()->SetTitleFont(132);
   frame_0ab04c48->GetYaxis()->SetTitle("Events");
   frame_0ab04c48->GetYaxis()->SetLabelFont(132);
   frame_0ab04c48->GetYaxis()->SetLabelSize(0.05);
   frame_0ab04c48->GetYaxis()->SetTitleSize(0.06);
   frame_0ab04c48->GetYaxis()->SetTitleFont(132);
   frame_0ab04c48->GetZaxis()->SetLabelFont(132);
   frame_0ab04c48->GetZaxis()->SetLabelSize(0.05);
   frame_0ab04c48->GetZaxis()->SetTitleSize(0.06);
   frame_0ab04c48->GetZaxis()->SetTitleFont(132);
   frame_0ab04c48->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(12);
   grae->SetName("ZjetsMADGRAPH_plot__sinMHTphiMET");
   grae->SetTitle("Histogram of ZjetsMADGRAPH_plot__sinMHTphiMET");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,-0.7791667,4);
   grae->SetPointError(0,0.07083333,0.07083333,1.914339,3.162753);
   grae->SetPoint(1,-0.6375,3);
   grae->SetPointError(1,0.07083333,0.07083333,1.632705,2.918186);
   grae->SetPoint(2,-0.4958333,2);
   grae->SetPointError(2,0.07083333,0.07083333,1.291815,2.63786);
   grae->SetPoint(3,-0.3541667,7);
   grae->SetPointError(3,0.07083333,0.07083333,2.58147,3.770281);
   grae->SetPoint(4,-0.2125,15);
   grae->SetPointError(4,0.07083333,0.07083333,3.82938,4.958738);
   grae->SetPoint(5,-0.07083333,23);
   grae->SetPointError(5,0.07083333,0.07083333,4.760716,5.865235);
   grae->SetPoint(6,0.07083333,33);
   grae->SetPointError(6,0.07083333,0.07083333,5.715302,6.802567);
   grae->SetPoint(7,0.2125,22);
   grae->SetPointError(7,0.07083333,0.07083333,4.654502,5.761366);
   grae->SetPoint(8,0.3541667,6);
   grae->SetPointError(8,0.07083333,0.07083333,2.379931,3.583641);
   grae->SetPoint(9,0.4958333,3);
   grae->SetPointError(9,0.07083333,0.07083333,1.632705,2.918186);
   grae->SetPoint(10,0.6375,1);
   grae->SetPointError(10,0.07083333,0.07083333,0.8272462,2.299526);
   grae->SetPoint(11,0.7791667,2);
   grae->SetPointError(11,0.07083333,0.07083333,1.291815,2.63786);
   grae->Draw("p");
   
   TGraph *graph = new TGraph(72);
   graph->SetName("curve_myFitProjected");
   graph->SetTitle("Projection of Ratio ZtoEE");
   graph->SetFillColor(1);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,-0.9916667,0);
   graph->SetPoint(1,-0.9916667,2.263457);
   graph->SetPoint(2,-0.85,2.263457);
   graph->SetPoint(3,-0.7083333,2.632932);
   graph->SetPoint(4,-0.6375,2.920298);
   graph->SetPoint(5,-0.5666667,3.325161);
   graph->SetPoint(6,-0.4958333,3.917377);
   graph->SetPoint(7,-0.4604167,4.319324);
   graph->SetPoint(8,-0.425,4.821129);
   graph->SetPoint(9,-0.3895833,5.454715);
   graph->SetPoint(10,-0.3541667,6.263401);
   graph->SetPoint(11,-0.3364583,6.750933);
   graph->SetPoint(12,-0.31875,7.305464);
   graph->SetPoint(13,-0.3010417,7.937187);
   graph->SetPoint(14,-0.2833333,8.657571);
   graph->SetPoint(15,-0.265625,9.4793);
   graph->SetPoint(16,-0.2479167,10.41605);
   graph->SetPoint(17,-0.2302083,11.48206);
   graph->SetPoint(18,-0.2125,12.69132);
   graph->SetPoint(19,-0.1947917,14.05638);
   graph->SetPoint(20,-0.1770833,15.58654);
   graph->SetPoint(21,-0.159375,17.28542);
   graph->SetPoint(22,-0.1416667,19.14789);
   graph->SetPoint(23,-0.1239583,21.15651);
   graph->SetPoint(24,-0.10625,23.27787);
   graph->SetPoint(25,-0.07083333,27.62919);
   graph->SetPoint(26,-0.053125,29.69499);
   graph->SetPoint(27,-0.03541667,31.55181);
   graph->SetPoint(28,-0.0265625,32.3674);
   graph->SetPoint(29,-0.01770833,33.08989);
   graph->SetPoint(30,-0.008854167,33.70688);
   graph->SetPoint(31,0,34.20737);
   graph->SetPoint(32,0.008854167,34.58213);
   graph->SetPoint(33,0.01770833,34.82406);
   graph->SetPoint(34,0.0265625,34.92851);
   graph->SetPoint(35,0.03541667,34.89904);
   graph->SetPoint(36,0.04427083,34.74964);
   graph->SetPoint(37,0.053125,34.48307);
   graph->SetPoint(38,0.06197917,34.10316);
   graph->SetPoint(39,0.07083333,33.61525);
   graph->SetPoint(40,0.0796875,33.02608);
   graph->SetPoint(41,0.08854167,32.34359);
   graph->SetPoint(42,0.09739583,31.5767);
   graph->SetPoint(43,0.10625,30.73506);
   graph->SetPoint(44,0.1239583,28.86849);
   graph->SetPoint(45,0.1416667,26.82707);
   graph->SetPoint(46,0.1770833,22.53408);
   graph->SetPoint(47,0.1947917,20.41608);
   graph->SetPoint(48,0.2125,18.38503);
   graph->SetPoint(49,0.2302083,16.47508);
   graph->SetPoint(50,0.2479167,14.70803);
   graph->SetPoint(51,0.265625,13.09511);
   graph->SetPoint(52,0.2833333,11.63914);
   graph->SetPoint(53,0.3010417,10.33664);
   graph->SetPoint(54,0.31875,9.179815);
   graph->SetPoint(55,0.3364583,8.158122);
   graph->SetPoint(56,0.3541667,7.259601);
   graph->SetPoint(57,0.371875,6.471812);
   graph->SetPoint(58,0.3895833,5.782507);
   graph->SetPoint(59,0.4072917,5.180065);
   graph->SetPoint(60,0.425,4.653752);
   graph->SetPoint(61,0.4604167,3.791649);
   graph->SetPoint(62,0.4958333,3.130725);
   graph->SetPoint(63,0.53125,2.62064);
   graph->SetPoint(64,0.5666667,2.223588);
   graph->SetPoint(65,0.6375,1.663748);
   graph->SetPoint(66,0.7083333,1.303858);
   graph->SetPoint(67,0.7791667,1.062995);
   graph->SetPoint(68,0.85,0.895683);
   graph->SetPoint(69,0.85,0.895683);
   graph->SetPoint(70,0.9916667,0.895683);
   graph->SetPoint(71,0.9916667,0);
   graph->Draw("l");
   
   TH1 *frame_0ab04c48 = new TH1D("frame_0ab04c48","A RooPlot of "sin #phi_{MHT-MET}"",12,-0.85,0.85);
   frame_0ab04c48->SetMaximum(41.79269);
   frame_0ab04c48->SetDirectory(0);
   frame_0ab04c48->SetStats(0);
   frame_0ab04c48->SetMarkerStyle(8);
   frame_0ab04c48->GetXaxis()->SetTitle("sin(#phi_{MHT,MET})");
   frame_0ab04c48->GetXaxis()->SetLabelFont(132);
   frame_0ab04c48->GetXaxis()->SetLabelSize(0.05);
   frame_0ab04c48->GetXaxis()->SetTitleSize(0.06);
   frame_0ab04c48->GetXaxis()->SetTitleFont(132);
   frame_0ab04c48->GetYaxis()->SetTitle("Events");
   frame_0ab04c48->GetYaxis()->SetLabelFont(132);
   frame_0ab04c48->GetYaxis()->SetLabelSize(0.05);
   frame_0ab04c48->GetYaxis()->SetTitleSize(0.06);
   frame_0ab04c48->GetYaxis()->SetTitleFont(132);
   frame_0ab04c48->GetZaxis()->SetLabelFont(132);
   frame_0ab04c48->GetZaxis()->SetLabelSize(0.05);
   frame_0ab04c48->GetZaxis()->SetTitleSize(0.06);
   frame_0ab04c48->GetZaxis()->SetTitleFont(132);
   frame_0ab04c48->Draw("axissame");
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
