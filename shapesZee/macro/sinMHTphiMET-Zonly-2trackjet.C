{
//=========Macro generated from canvas: c/fitResult
//=========  (Sun Mar  8 19:51:42 2009) by ROOT version5.18/00a
   TCanvas *c = new TCanvas("c", "fitResult",4,21,600,300);
   gStyle->SetOptStat(0);
   c->Range(-1.095783,-90.73183,0.9524096,476.3421);
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
   
   TH1 *frame_0a10e408 = new TH1D("frame_0a10e408","A RooPlot of "sin #phi_{MHT-MET}"",20,-0.85,0.85);
   frame_0a10e408->SetMaximum(447.9884);
   frame_0a10e408->SetDirectory(0);
   frame_0a10e408->SetStats(0);
   frame_0a10e408->SetMarkerStyle(8);
   frame_0a10e408->GetXaxis()->SetTitle("sin(#phi_{MHT,MET})");
   frame_0a10e408->GetXaxis()->SetLabelFont(132);
   frame_0a10e408->GetXaxis()->SetLabelSize(0.05);
   frame_0a10e408->GetXaxis()->SetTitleSize(0.06);
   frame_0a10e408->GetXaxis()->SetTitleFont(132);
   frame_0a10e408->GetYaxis()->SetTitle("Events");
   frame_0a10e408->GetYaxis()->SetLabelFont(132);
   frame_0a10e408->GetYaxis()->SetLabelSize(0.05);
   frame_0a10e408->GetYaxis()->SetTitleSize(0.06);
   frame_0a10e408->GetYaxis()->SetTitleFont(132);
   frame_0a10e408->GetZaxis()->SetLabelFont(132);
   frame_0a10e408->GetZaxis()->SetLabelSize(0.05);
   frame_0a10e408->GetZaxis()->SetTitleSize(0.06);
   frame_0a10e408->GetZaxis()->SetTitleFont(132);
   frame_0a10e408->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(20);
   grae->SetName("ZjetsMADGRAPH_plot__sinMHTphiMET");
   grae->SetTitle("Histogram of ZjetsMADGRAPH_plot__sinMHTphiMET");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,-0.8075,28);
   grae->SetPointError(0,0.0425,0.0425,5.259711,6.354446);
   grae->SetPoint(1,-0.7225,37);
   grae->SetPointError(1,0.0425,0.0425,6.055142,7.137555);
   grae->SetPoint(2,-0.6375,44);
   grae->SetPointError(2,0.0425,0.0425,6.60794,7.68351);
   grae->SetPoint(3,-0.5525,54);
   grae->SetPointError(3,0.0425,0.0425,7.32564,8.39385);
   grae->SetPoint(4,-0.4675,59);
   grae->SetPointError(4,0.0425,0.0425,7.659312,8.724565);
   grae->SetPoint(5,-0.3825,84);
   grae->SetPointError(5,0.0425,0.0425,9.146872,10.20155);
   grae->SetPoint(6,-0.2975,146);
   grae->SetPointError(6,0.0425,0.0425,11.59339,12.59339);
   grae->SetPoint(7,-0.2125,170);
   grae->SetPointError(7,0.0425,0.0425,12.54799,13.54799);
   grae->SetPoint(8,-0.1275,286);
   grae->SetPointError(8,0.0425,0.0425,16.41892,17.41892);
   grae->SetPoint(9,-0.0425,357);
   grae->SetPointError(9,0.0425,0.0425,18.40106,19.40106);
   grae->SetPoint(10,0.0425,406);
   grae->SetPointError(10,0.0425,0.0425,19.65564,20.65564);
   grae->SetPoint(11,0.1275,275);
   grae->SetPointError(11,0.0425,0.0425,16.09066,17.09066);
   grae->SetPoint(12,0.2125,191);
   grae->SetPointError(12,0.0425,0.0425,13.32932,14.32932);
   grae->SetPoint(13,0.2975,129);
   grae->SetPointError(13,0.0425,0.0425,10.86882,11.86882);
   grae->SetPoint(14,0.3825,91);
   grae->SetPointError(14,0.0425,0.0425,9.521834,10.57436);
   grae->SetPoint(15,0.4675,70);
   grae->SetPointError(15,0.0425,0.0425,8.346566,9.406467);
   grae->SetPoint(16,0.5525,54);
   grae->SetPointError(16,0.0425,0.0425,7.32564,8.39385);
   grae->SetPoint(17,0.6375,45);
   grae->SetPointError(17,0.0425,0.0425,6.683179,7.757904);
   grae->SetPoint(18,0.7225,28);
   grae->SetPointError(18,0.0425,0.0425,5.259711,6.354446);
   grae->SetPoint(19,0.8075,37);
   grae->SetPointError(19,0.0425,0.0425,6.055142,7.137555);
   grae->Draw("p");
   
   TGraph *graph = new TGraph(67);
   graph->SetName("curve_myFitProjected");
   graph->SetTitle("Projection of Ratio ZtoEE");
   graph->SetFillColor(1);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,-0.935,0);
   graph->SetPoint(1,-0.935,30.42857);
   graph->SetPoint(2,-0.85,30.42857);
   graph->SetPoint(3,-0.765,33.73149);
   graph->SetPoint(4,-0.68,38.43348);
   graph->SetPoint(5,-0.6375,41.55812);
   graph->SetPoint(6,-0.595,45.40154);
   graph->SetPoint(7,-0.5525,50.18465);
   graph->SetPoint(8,-0.51,56.2097);
   graph->SetPoint(9,-0.4675,63.8919);
   graph->SetPoint(10,-0.425,73.80065);
   graph->SetPoint(11,-0.40375,79.82197);
   graph->SetPoint(12,-0.3825,86.70784);
   graph->SetPoint(13,-0.36125,94.59349);
   graph->SetPoint(14,-0.34,103.6304);
   graph->SetPoint(15,-0.31875,113.9842);
   graph->SetPoint(16,-0.2975,125.8301);
   graph->SetPoint(17,-0.27625,139.3441);
   graph->SetPoint(18,-0.255,154.6881);
   graph->SetPoint(19,-0.23375,171.9881);
   graph->SetPoint(20,-0.2125,191.3032);
   graph->SetPoint(21,-0.19125,212.5849);
   graph->SetPoint(22,-0.17,235.6302);
   graph->SetPoint(23,-0.1275,285.1355);
   graph->SetPoint(24,-0.10625,310.0248);
   graph->SetPoint(25,-0.085,333.5388);
   graph->SetPoint(26,-0.074375,344.368);
   graph->SetPoint(27,-0.06375,354.3482);
   graph->SetPoint(28,-0.053125,363.3086);
   graph->SetPoint(29,-0.0425,371.0867);
   graph->SetPoint(30,-0.031875,377.5347);
   graph->SetPoint(31,-0.02125,382.5251);
   graph->SetPoint(32,-0.010625,385.9562);
   graph->SetPoint(33,-5.551115e-17,387.7566);
   graph->SetPoint(34,0.010625,387.8721);
   graph->SetPoint(35,0.02125,386.1654);
   graph->SetPoint(36,0.031875,382.6467);
   graph->SetPoint(37,0.0425,377.3988);
   graph->SetPoint(38,0.053125,370.5421);
   graph->SetPoint(39,0.06375,362.2291);
   graph->SetPoint(40,0.074375,352.6368);
   graph->SetPoint(41,0.085,341.959);
   graph->SetPoint(42,0.10625,318.1572);
   graph->SetPoint(43,0.1275,292.4168);
   graph->SetPoint(44,0.17,240.5211);
   graph->SetPoint(45,0.19125,216.3062);
   graph->SetPoint(46,0.2125,194.0125);
   graph->SetPoint(47,0.23375,173.8816);
   graph->SetPoint(48,0.255,155.9643);
   graph->SetPoint(49,0.27625,140.1834);
   graph->SetPoint(50,0.2975,126.3844);
   graph->SetPoint(51,0.31875,114.3746);
   graph->SetPoint(52,0.34,103.9491);
   graph->SetPoint(53,0.36125,94.90802);
   graph->SetPoint(54,0.3825,87.06538);
   graph->SetPoint(55,0.40375,80.25401);
   graph->SetPoint(56,0.425,74.32678);
   graph->SetPoint(57,0.4675,64.63272);
   graph->SetPoint(58,0.51,57.16828);
   graph->SetPoint(59,0.5525,51.34461);
   graph->SetPoint(60,0.595,46.73955);
   graph->SetPoint(61,0.68,40.05685);
   graph->SetPoint(62,0.765,35.56188);
   graph->SetPoint(63,0.85,32.40938);
   graph->SetPoint(64,0.85,32.40938);
   graph->SetPoint(65,0.935,32.40938);
   graph->SetPoint(66,0.935,0);
   graph->Draw("l");
   
   TH1 *frame_0a10e408 = new TH1D("frame_0a10e408","A RooPlot of "sin #phi_{MHT-MET}"",20,-0.85,0.85);
   frame_0a10e408->SetMaximum(447.9884);
   frame_0a10e408->SetDirectory(0);
   frame_0a10e408->SetStats(0);
   frame_0a10e408->SetMarkerStyle(8);
   frame_0a10e408->GetXaxis()->SetTitle("sin(#phi_{MHT,MET})");
   frame_0a10e408->GetXaxis()->SetLabelFont(132);
   frame_0a10e408->GetXaxis()->SetLabelSize(0.05);
   frame_0a10e408->GetXaxis()->SetTitleSize(0.06);
   frame_0a10e408->GetXaxis()->SetTitleFont(132);
   frame_0a10e408->GetYaxis()->SetTitle("Events");
   frame_0a10e408->GetYaxis()->SetLabelFont(132);
   frame_0a10e408->GetYaxis()->SetLabelSize(0.05);
   frame_0a10e408->GetYaxis()->SetTitleSize(0.06);
   frame_0a10e408->GetYaxis()->SetTitleFont(132);
   frame_0a10e408->GetZaxis()->SetLabelFont(132);
   frame_0a10e408->GetZaxis()->SetLabelSize(0.05);
   frame_0a10e408->GetZaxis()->SetTitleSize(0.06);
   frame_0a10e408->GetZaxis()->SetTitleFont(132);
   frame_0a10e408->Draw("axissame");
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
