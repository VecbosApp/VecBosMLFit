{
//=========Macro generated from canvas: c/fitResult
//=========  (Sun Mar 15 11:28:17 2009) by ROOT version5.18/00a
   TCanvas *c = new TCanvas("c", "fitResult",4,21,600,300);
   gStyle->SetOptStat(0);
   c->Range(-1.031325,-514.4596,0.8963855,2700.913);
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
   
   TH1 *frame_0adaaac0 = new TH1D("frame_0adaaac0","A RooPlot of "sinMHTphiJet"",17,-0.8,0.8);
   frame_0adaaac0->SetMaximum(2540.144);
   frame_0adaaac0->SetDirectory(0);
   frame_0adaaac0->SetStats(0);
   frame_0adaaac0->SetMarkerStyle(8);
   frame_0adaaac0->GetXaxis()->SetTitle("sin(#phi_{MHT-Jet})");
   frame_0adaaac0->GetXaxis()->SetLabelFont(132);
   frame_0adaaac0->GetXaxis()->SetLabelSize(0.05);
   frame_0adaaac0->GetXaxis()->SetTitleSize(0.06);
   frame_0adaaac0->GetXaxis()->SetTitleFont(132);
   frame_0adaaac0->GetYaxis()->SetTitle("Events");
   frame_0adaaac0->GetYaxis()->SetLabelFont(132);
   frame_0adaaac0->GetYaxis()->SetLabelSize(0.05);
   frame_0adaaac0->GetYaxis()->SetTitleSize(0.06);
   frame_0adaaac0->GetYaxis()->SetTitleFont(132);
   frame_0adaaac0->GetZaxis()->SetLabelFont(132);
   frame_0adaaac0->GetZaxis()->SetLabelSize(0.05);
   frame_0adaaac0->GetZaxis()->SetTitleSize(0.06);
   frame_0adaaac0->GetZaxis()->SetTitleFont(132);
   frame_0adaaac0->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(17);
   grae->SetName("ttjetsMADGRAPH_plot__sinMHTphiJet");
   grae->SetTitle("Histogram of ttjetsMADGRAPH_plot__sinMHTphiJet");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,-0.7529412,1036);
   grae->SetPointError(0,0.04705882,0.04705882,31.69084,32.69084);
   grae->SetPoint(1,-0.6588235,1077);
   grae->SetPointError(1,0.04705882,0.04705882,32.32149,33.32149);
   grae->SetPoint(2,-0.5647059,1206);
   grae->SetPointError(2,0.04705882,0.04705882,34.23111,35.23111);
   grae->SetPoint(3,-0.4705882,1386);
   grae->SetPointError(3,0.04705882,0.04705882,36.73238,37.73238);
   grae->SetPoint(4,-0.3764706,1544);
   grae->SetPointError(4,0.04705882,0.04705882,38.79695,39.79695);
   grae->SetPoint(5,-0.2823529,1683);
   grae->SetPointError(5,0.04705882,0.04705882,40.52743,41.52743);
   grae->SetPoint(6,-0.1882353,1888);
   grae->SetPointError(6,0.04705882,0.04705882,42.954,43.954);
   grae->SetPoint(7,-0.09411765,2069);
   grae->SetPointError(7,0.04705882,0.04705882,44.98901,45.98901);
   grae->SetPoint(8,-5.551115e-17,2370);
   grae->SetPointError(8,0.04705882,0.04705882,48.18521,49.18521);
   grae->SetPoint(9,0.09411765,2125);
   grae->SetPointError(9,0.04705882,0.04705882,45.60043,46.60043);
   grae->SetPoint(10,0.1882353,1866);
   grae->SetPointError(10,0.04705882,0.04705882,42.70012,43.70012);
   grae->SetPoint(11,0.2823529,1661);
   grae->SetPointError(11,0.04705882,0.04705882,40.25843,41.25843);
   grae->SetPoint(12,0.3764706,1508);
   grae->SetPointError(12,0.04705882,0.04705882,38.33619,39.33619);
   grae->SetPoint(13,0.4705882,1386);
   grae->SetPointError(13,0.04705882,0.04705882,36.73238,37.73238);
   grae->SetPoint(14,0.5647059,1169);
   grae->SetPointError(14,0.04705882,0.04705882,33.6943,34.6943);
   grae->SetPoint(15,0.6588235,1112);
   grae->SetPointError(15,0.04705882,0.04705882,32.85041,33.85041);
   grae->SetPoint(16,0.7529412,1101);
   grae->SetPointError(16,0.04705882,0.04705882,32.68509,33.68509);
   grae->Draw("p");
   
   TGraph *graph = new TGraph(60);
   graph->SetName("curve_myFitProjected");
   graph->SetTitle("Projection of Ratio WtoENu");
   graph->SetFillColor(1);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,-0.8941176,0);
   graph->SetPoint(1,-0.8941176,999.0661);
   graph->SetPoint(2,-0.8,999.0661);
   graph->SetPoint(3,-0.7529412,1030.227);
   graph->SetPoint(4,-0.7058824,1065.794);
   graph->SetPoint(5,-0.6588235,1106.482);
   graph->SetPoint(6,-0.6117647,1153.106);
   graph->SetPoint(7,-0.5647059,1206.562);
   graph->SetPoint(8,-0.5176471,1267.795);
   graph->SetPoint(9,-0.4705882,1337.731);
   graph->SetPoint(10,-0.4470588,1376.214);
   graph->SetPoint(11,-0.4235294,1417.139);
   graph->SetPoint(12,-0.4,1460.544);
   graph->SetPoint(13,-0.3764706,1506.422);
   graph->SetPoint(14,-0.3294118,1605.291);
   graph->SetPoint(15,-0.2823529,1712.335);
   graph->SetPoint(16,-0.2352941,1824.522);
   graph->SetPoint(17,-0.1882353,1936.769);
   graph->SetPoint(18,-0.1647059,1990.727);
   graph->SetPoint(19,-0.1411765,2041.828);
   graph->SetPoint(20,-0.1176471,2088.911);
   graph->SetPoint(21,-0.09411765,2130.786);
   graph->SetPoint(22,-0.07058824,2166.296);
   graph->SetPoint(23,-0.04705882,2194.385);
   graph->SetPoint(24,-0.02352941,2214.169);
   graph->SetPoint(25,-5.551115e-17,2225);
   graph->SetPoint(26,0.01176471,2226.931);
   graph->SetPoint(27,0.02352941,2226.246);
   graph->SetPoint(28,0.03529412,2222.125);
   graph->SetPoint(29,0.04705882,2214.572);
   graph->SetPoint(30,0.05882353,2203.694);
   graph->SetPoint(31,0.07058824,2189.648);
   graph->SetPoint(32,0.08235294,2172.63);
   graph->SetPoint(33,0.09411765,2152.868);
   graph->SetPoint(34,0.1176471,2106.156);
   graph->SetPoint(35,0.1411765,2051.746);
   graph->SetPoint(36,0.1647059,1991.948);
   graph->SetPoint(37,0.1882353,1928.953);
   graph->SetPoint(38,0.2352941,1800.774);
   graph->SetPoint(39,0.2588235,1738.437);
   graph->SetPoint(40,0.2823529,1678.585);
   graph->SetPoint(41,0.3058824,1621.826);
   graph->SetPoint(42,0.3294118,1568.516);
   graph->SetPoint(43,0.3529412,1518.818);
   graph->SetPoint(44,0.3764706,1472.751);
   graph->SetPoint(45,0.4,1430.232);
   graph->SetPoint(46,0.4235294,1391.109);
   graph->SetPoint(47,0.4470588,1355.186);
   graph->SetPoint(48,0.4705882,1322.247);
   graph->SetPoint(49,0.4941176,1292.067);
   graph->SetPoint(50,0.5176471,1264.422);
   graph->SetPoint(51,0.5647059,1215.879);
   graph->SetPoint(52,0.6117647,1175.038);
   graph->SetPoint(53,0.6588235,1140.545);
   graph->SetPoint(54,0.7058824,1111.276);
   graph->SetPoint(55,0.7529412,1086.309);
   graph->SetPoint(56,0.8,1064.896);
   graph->SetPoint(57,0.8,1064.896);
   graph->SetPoint(58,0.8941176,1064.896);
   graph->SetPoint(59,0.8941176,0);
   graph->Draw("l");
   
   TH1 *frame_0adaaac0 = new TH1D("frame_0adaaac0","A RooPlot of "sinMHTphiJet"",17,-0.8,0.8);
   frame_0adaaac0->SetMaximum(2540.144);
   frame_0adaaac0->SetDirectory(0);
   frame_0adaaac0->SetStats(0);
   frame_0adaaac0->SetMarkerStyle(8);
   frame_0adaaac0->GetXaxis()->SetTitle("sin(#phi_{MHT-Jet})");
   frame_0adaaac0->GetXaxis()->SetLabelFont(132);
   frame_0adaaac0->GetXaxis()->SetLabelSize(0.05);
   frame_0adaaac0->GetXaxis()->SetTitleSize(0.06);
   frame_0adaaac0->GetXaxis()->SetTitleFont(132);
   frame_0adaaac0->GetYaxis()->SetTitle("Events");
   frame_0adaaac0->GetYaxis()->SetLabelFont(132);
   frame_0adaaac0->GetYaxis()->SetLabelSize(0.05);
   frame_0adaaac0->GetYaxis()->SetTitleSize(0.06);
   frame_0adaaac0->GetYaxis()->SetTitleFont(132);
   frame_0adaaac0->GetZaxis()->SetLabelFont(132);
   frame_0adaaac0->GetZaxis()->SetLabelSize(0.05);
   frame_0adaaac0->GetZaxis()->SetTitleSize(0.06);
   frame_0adaaac0->GetZaxis()->SetTitleFont(132);
   frame_0adaaac0->Draw("axissame");
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
