{
//=========Macro generated from canvas: c/fitResult
//=========  (Sun Mar  8 15:15:01 2009) by ROOT version5.18/00a
   TCanvas *c = new TCanvas("c", "fitResult",4,21,600,300);
   gStyle->SetOptStat(0);
   c->Range(-1.095783,-1544.018,0.9524096,8106.092);
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
   
   TH1 *frame_0a8fe7d8 = new TH1D("frame_0a8fe7d8","A RooPlot of "sinMHTphiJet"",20,-0.85,0.85);
   frame_0a8fe7d8->SetMaximum(7623.587);
   frame_0a8fe7d8->SetDirectory(0);
   frame_0a8fe7d8->SetStats(0);
   frame_0a8fe7d8->SetMarkerStyle(8);
   frame_0a8fe7d8->GetXaxis()->SetTitle("sin(#phi_{MHT-Jet})");
   frame_0a8fe7d8->GetXaxis()->SetLabelFont(132);
   frame_0a8fe7d8->GetXaxis()->SetLabelSize(0.05);
   frame_0a8fe7d8->GetXaxis()->SetTitleSize(0.06);
   frame_0a8fe7d8->GetXaxis()->SetTitleFont(132);
   frame_0a8fe7d8->GetYaxis()->SetTitle("Events");
   frame_0a8fe7d8->GetYaxis()->SetLabelFont(132);
   frame_0a8fe7d8->GetYaxis()->SetLabelSize(0.05);
   frame_0a8fe7d8->GetYaxis()->SetTitleSize(0.06);
   frame_0a8fe7d8->GetYaxis()->SetTitleFont(132);
   frame_0a8fe7d8->GetZaxis()->SetLabelFont(132);
   frame_0a8fe7d8->GetZaxis()->SetLabelSize(0.05);
   frame_0a8fe7d8->GetZaxis()->SetTitleSize(0.06);
   frame_0a8fe7d8->GetZaxis()->SetTitleFont(132);
   frame_0a8fe7d8->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(20);
   grae->SetName("WjetsMADGRAPH_plot__sinMHTphiJet");
   grae->SetTitle("Histogram of WjetsMADGRAPH_plot__sinMHTphiJet");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,-0.8075,472);
   grae->SetPointError(0,0.0425,0.0425,21.23131,22.23131);
   grae->SetPoint(1,-0.7225,561);
   grae->SetPointError(1,0.0425,0.0425,23.19072,24.19072);
   grae->SetPoint(2,-0.6375,622);
   grae->SetPointError(2,0.0425,0.0425,24.44494,25.44494);
   grae->SetPoint(3,-0.5525,814);
   grae->SetPointError(3,0.0425,0.0425,28.03507,29.03507);
   grae->SetPoint(4,-0.4675,1248);
   grae->SetPointError(4,0.0425,0.0425,34.83058,35.83058);
   grae->SetPoint(5,-0.3825,1646);
   grae->SetPointError(5,0.0425,0.0425,40.07401,41.07401);
   grae->SetPoint(6,-0.2975,2497);
   grae->SetPointError(6,0.0425,0.0425,49.47249,50.47249);
   grae->SetPoint(7,-0.2125,3891);
   grae->SetPointError(7,0.0425,0.0425,61.87988,62.87988);
   grae->SetPoint(8,-0.1275,5540);
   grae->SetPointError(8,0.0425,0.0425,73.93286,74.93286);
   grae->SetPoint(9,-0.0425,7013);
   grae->SetPointError(9,0.0425,0.0425,83.24515,84.24515);
   grae->SetPoint(10,0.0425,7084);
   grae->SetPointError(10,0.0425,0.0425,83.66799,84.66799);
   grae->SetPoint(11,0.1275,5462);
   grae->SetPointError(11,0.0425,0.0425,73.40704,74.40704);
   grae->SetPoint(12,0.2125,3703);
   grae->SetPointError(12,0.0425,0.0425,60.35433,61.35433);
   grae->SetPoint(13,0.2975,2476);
   grae->SetPointError(13,0.0425,0.0425,49.26193,50.26193);
   grae->SetPoint(14,0.3825,1671);
   grae->SetPointError(14,0.0425,0.0425,40.38092,41.38092);
   grae->SetPoint(15,0.4675,1233);
   grae->SetPointError(15,0.0425,0.0425,34.61766,35.61766);
   grae->SetPoint(16,0.5525,886);
   grae->SetPointError(16,0.0425,0.0425,29.26995,30.26995);
   grae->SetPoint(17,0.6375,682);
   grae->SetPointError(17,0.0425,0.0425,25.61992,26.61992);
   grae->SetPoint(18,0.7225,538);
   grae->SetPointError(18,0.0425,0.0425,22.70022,23.70022);
   grae->SetPoint(19,0.8075,442);
   grae->SetPointError(19,0.0425,0.0425,20.52974,21.52974);
   grae->Draw("p");
   
   TGraph *graph = new TGraph(70);
   graph->SetName("curve_myFitProjected");
   graph->SetTitle("Projection of Ratio WtoENu");
   graph->SetFillColor(1);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,-0.935,0);
   graph->SetPoint(1,-0.935,438.0216);
   graph->SetPoint(2,-0.85,438.0216);
   graph->SetPoint(3,-0.765,503.7854);
   graph->SetPoint(4,-0.68,599.5197);
   graph->SetPoint(5,-0.6375,664.2436);
   graph->SetPoint(6,-0.595,744.8218);
   graph->SetPoint(7,-0.5525,846.2899);
   graph->SetPoint(8,-0.51,975.5157);
   graph->SetPoint(9,-0.4675,1141.844);
   graph->SetPoint(10,-0.44625,1242.706);
   graph->SetPoint(11,-0.425,1357.854);
   graph->SetPoint(12,-0.40375,1489.485);
   graph->SetPoint(13,-0.3825,1640.059);
   graph->SetPoint(14,-0.36125,1812.292);
   graph->SetPoint(15,-0.34,2009.096);
   graph->SetPoint(16,-0.31875,2233.482);
   graph->SetPoint(17,-0.2975,2488.388);
   graph->SetPoint(18,-0.27625,2776.419);
   graph->SetPoint(19,-0.255,3099.47);
   graph->SetPoint(20,-0.23375,3458.229);
   graph->SetPoint(21,-0.2125,3851.557);
   graph->SetPoint(22,-0.19125,4275.784);
   graph->SetPoint(23,-0.17,4724.012);
   graph->SetPoint(24,-0.1275,5645.668);
   graph->SetPoint(25,-0.10625,6085.901);
   graph->SetPoint(26,-0.085,6485.017);
   graph->SetPoint(27,-0.074375,6662.181);
   graph->SetPoint(28,-0.06375,6820.763);
   graph->SetPoint(29,-0.053125,6958.208);
   graph->SetPoint(30,-0.0425,7072.207);
   graph->SetPoint(31,-0.031875,7160.782);
   graph->SetPoint(32,-0.02125,7222.352);
   graph->SetPoint(33,-0.010625,7255.801);
   graph->SetPoint(34,-5.551115e-17,7260.559);
   graph->SetPoint(35,0.010625,7237.133);
   graph->SetPoint(36,0.02125,7186.126);
   graph->SetPoint(37,0.031875,7108.444);
   graph->SetPoint(38,0.0425,7005.445);
   graph->SetPoint(39,0.053125,6878.89);
   graph->SetPoint(40,0.06375,6730.877);
   graph->SetPoint(41,0.074375,6563.77);
   graph->SetPoint(42,0.085,6380.119);
   graph->SetPoint(43,0.10625,5973.856);
   graph->SetPoint(44,0.1275,5533.353);
   graph->SetPoint(45,0.17,4625.85);
   graph->SetPoint(46,0.19125,4188.917);
   graph->SetPoint(47,0.2125,3777);
   graph->SetPoint(48,0.23375,3396.011);
   graph->SetPoint(49,0.255,3048.936);
   graph->SetPoint(50,0.27625,2736.505);
   graph->SetPoint(51,0.2975,2457.827);
   graph->SetPoint(52,0.31875,2210.959);
   graph->SetPoint(53,0.34,1993.346);
   graph->SetPoint(54,0.36125,1802.156);
   graph->SetPoint(55,0.3825,1634.514);
   graph->SetPoint(56,0.40375,1487.65);
   graph->SetPoint(57,0.425,1358.987);
   graph->SetPoint(58,0.44625,1246.188);
   graph->SetPoint(59,0.4675,1147.169);
   graph->SetPoint(60,0.51,983.3614);
   graph->SetPoint(61,0.5525,855.5708);
   graph->SetPoint(62,0.595,754.8466);
   graph->SetPoint(63,0.6375,674.5805);
   graph->SetPoint(64,0.68,609.9043);
   graph->SetPoint(65,0.765,513.86);
   graph->SetPoint(66,0.85,447.5801);
   graph->SetPoint(67,0.85,447.5801);
   graph->SetPoint(68,0.935,447.5801);
   graph->SetPoint(69,0.935,0);
   graph->Draw("l");
   
   TH1 *frame_0a8fe7d8 = new TH1D("frame_0a8fe7d8","A RooPlot of "sinMHTphiJet"",20,-0.85,0.85);
   frame_0a8fe7d8->SetMaximum(7623.587);
   frame_0a8fe7d8->SetDirectory(0);
   frame_0a8fe7d8->SetStats(0);
   frame_0a8fe7d8->SetMarkerStyle(8);
   frame_0a8fe7d8->GetXaxis()->SetTitle("sin(#phi_{MHT-Jet})");
   frame_0a8fe7d8->GetXaxis()->SetLabelFont(132);
   frame_0a8fe7d8->GetXaxis()->SetLabelSize(0.05);
   frame_0a8fe7d8->GetXaxis()->SetTitleSize(0.06);
   frame_0a8fe7d8->GetXaxis()->SetTitleFont(132);
   frame_0a8fe7d8->GetYaxis()->SetTitle("Events");
   frame_0a8fe7d8->GetYaxis()->SetLabelFont(132);
   frame_0a8fe7d8->GetYaxis()->SetLabelSize(0.05);
   frame_0a8fe7d8->GetYaxis()->SetTitleSize(0.06);
   frame_0a8fe7d8->GetYaxis()->SetTitleFont(132);
   frame_0a8fe7d8->GetZaxis()->SetLabelFont(132);
   frame_0a8fe7d8->GetZaxis()->SetLabelSize(0.05);
   frame_0a8fe7d8->GetZaxis()->SetTitleSize(0.06);
   frame_0a8fe7d8->GetZaxis()->SetTitleFont(132);
   frame_0a8fe7d8->Draw("axissame");
   c->Modified();
   c->cd();
   c->SetSelected(c);
}