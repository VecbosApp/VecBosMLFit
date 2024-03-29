{
//=========Macro generated from canvas: c/fitResult
//=========  (Mon Mar 16 15:03:55 2009) by ROOT version5.18/00a
   TCanvas *c = new TCanvas("c", "fitResult",4,21,599,299);
   gStyle->SetOptStat(0);
   c->Range(-1.031325,-99.15992,0.8963855,520.5896);
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
   
   TH1 *frame_0b5d2db0 = new TH1D("frame_0b5d2db0","A RooPlot of "sinMHTphiJet"",19,-0.8,0.8);
   frame_0b5d2db0->SetMaximum(489.6021);
   frame_0b5d2db0->SetDirectory(0);
   frame_0b5d2db0->SetStats(0);
   frame_0b5d2db0->SetMarkerStyle(8);
   frame_0b5d2db0->GetXaxis()->SetTitle("sin(#phi_{MHT-Jet})");
   frame_0b5d2db0->GetXaxis()->SetLabelFont(132);
   frame_0b5d2db0->GetXaxis()->SetLabelSize(0.05);
   frame_0b5d2db0->GetXaxis()->SetTitleSize(0.06);
   frame_0b5d2db0->GetXaxis()->SetTitleFont(132);
   frame_0b5d2db0->GetYaxis()->SetTitle("Events");
   frame_0b5d2db0->GetYaxis()->SetLabelFont(132);
   frame_0b5d2db0->GetYaxis()->SetLabelSize(0.05);
   frame_0b5d2db0->GetYaxis()->SetTitleSize(0.06);
   frame_0b5d2db0->GetYaxis()->SetTitleFont(132);
   frame_0b5d2db0->GetZaxis()->SetLabelFont(132);
   frame_0b5d2db0->GetZaxis()->SetLabelSize(0.05);
   frame_0b5d2db0->GetZaxis()->SetTitleSize(0.06);
   frame_0b5d2db0->GetZaxis()->SetTitleFont(132);
   frame_0b5d2db0->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(19);
   grae->SetName("data_plot__sinMHTphiJet");
   grae->SetTitle("Histogram of data_plot__sinMHTphiJet");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,-0.7578947,96.4458);
   grae->SetPointError(0,0.04210526,0.04210526,5.113465,5.113465);
   grae->SetPoint(1,-0.6736842,100.5939);
   grae->SetPointError(1,0.04210526,0.04210526,5.240414,5.240414);
   grae->SetPoint(2,-0.5894737,118.3235);
   grae->SetPointError(2,0.04210526,0.04210526,5.758895,5.758895);
   grae->SetPoint(3,-0.5052632,145.0329);
   grae->SetPointError(3,0.04210526,0.04210526,6.47745,6.47745);
   grae->SetPoint(4,-0.4210526,151.4159);
   grae->SetPointError(4,0.04210526,0.04210526,6.560346,6.560346);
   grae->SetPoint(5,-0.3368421,190.3301);
   grae->SetPointError(5,0.04210526,0.04210526,7.488604,7.488604);
   grae->SetPoint(6,-0.2526316,252.0991);
   grae->SetPointError(6,0.04210526,0.04210526,8.807826,8.807826);
   grae->SetPoint(7,-0.1684211,337.2415);
   grae->SetPointError(7,0.04210526,0.04210526,10.46042,10.46042);
   grae->SetPoint(8,-0.08421053,390.7719);
   grae->SetPointError(8,0.04210526,0.04210526,11.36392,11.36392);
   grae->SetPoint(9,-6.245005e-17,452.0283);
   grae->SetPointError(9,0.04210526,0.04210526,12.28821,12.28821);
   grae->SetPoint(10,0.08421053,420.6941);
   grae->SetPointError(10,0.04210526,0.04210526,11.79841,11.79841);
   grae->SetPoint(11,0.1684211,308.9044);
   grae->SetPointError(11,0.04210526,0.04210526,9.949008,9.949008);
   grae->SetPoint(12,0.2526316,246.5045);
   grae->SetPointError(12,0.04210526,0.04210526,8.702766,8.702766);
   grae->SetPoint(13,0.3368421,202.2467);
   grae->SetPointError(13,0.04210526,0.04210526,7.755458,7.755458);
   grae->SetPoint(14,0.4210526,162.3224);
   grae->SetPointError(14,0.04210526,0.04210526,6.930902,6.930902);
   grae->SetPoint(15,0.5052632,131.1831);
   grae->SetPointError(15,0.04210526,0.04210526,6.065218,6.065218);
   grae->SetPoint(16,0.5894737,112.0041);
   grae->SetPointError(16,0.04210526,0.04210526,5.578361,5.578361);
   grae->SetPoint(17,0.6736842,108.4156);
   grae->SetPointError(17,0.04210526,0.04210526,5.504942,5.504942);
   grae->SetPoint(18,0.7578947,96.91406);
   grae->SetPointError(18,0.04210526,0.04210526,5.186223,5.186223);
   grae->Draw("p");
   
   TGraph *graph = new TGraph(68);
   graph->SetName("curve_myFitProjected");
   graph->SetTitle("Projection of Ratio WtoENu");
   graph->SetFillColor(1);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,-0.8842105,0);
   graph->SetPoint(1,-0.8842105,89.03545);
   graph->SetPoint(2,-0.8,89.03545);
   graph->SetPoint(3,-0.7157895,96.2488);
   graph->SetPoint(4,-0.6736842,100.7885);
   graph->SetPoint(5,-0.6315789,106.1416);
   graph->SetPoint(6,-0.5894737,112.5022);
   graph->SetPoint(7,-0.5473684,120.1204);
   graph->SetPoint(8,-0.5052632,129.3192);
   graph->SetPoint(9,-0.4631579,140.516);
   graph->SetPoint(10,-0.4210526,154.2453);
   graph->SetPoint(11,-0.4,162.2641);
   graph->SetPoint(12,-0.3789474,171.1795);
   graph->SetPoint(13,-0.3578947,181.0976);
   graph->SetPoint(14,-0.3368421,192.1311);
   graph->SetPoint(15,-0.3157895,204.3957);
   graph->SetPoint(16,-0.2947368,218.0048);
   graph->SetPoint(17,-0.2736842,233.0598);
   graph->SetPoint(18,-0.2526316,249.6374);
   graph->SetPoint(19,-0.2315789,267.7711);
   graph->SetPoint(20,-0.2105263,287.4274);
   graph->SetPoint(21,-0.1894737,308.4762);
   graph->SetPoint(22,-0.1684211,330.659);
   graph->SetPoint(23,-0.1263158,376.5704);
   graph->SetPoint(24,-0.1052632,398.9106);
   graph->SetPoint(25,-0.08421053,419.6299);
   graph->SetPoint(26,-0.07368421,429.056);
   graph->SetPoint(27,-0.06315789,437.6818);
   graph->SetPoint(28,-0.05263158,445.3779);
   graph->SetPoint(29,-0.04210526,452.0227);
   graph->SetPoint(30,-0.03157895,457.5071);
   graph->SetPoint(31,-0.02105263,461.7383);
   graph->SetPoint(32,-0.01052632,464.6435);
   graph->SetPoint(33,-6.245005e-17,466.173);
   graph->SetPoint(34,0.01052632,466.2878);
   graph->SetPoint(35,0.02105263,464.9474);
   graph->SetPoint(36,0.03157895,462.0579);
   graph->SetPoint(37,0.04210526,457.6442);
   graph->SetPoint(38,0.05263158,451.7857);
   graph->SetPoint(39,0.06315789,444.5762);
   graph->SetPoint(40,0.07368421,436.1556);
   graph->SetPoint(41,0.08421053,426.6804);
   graph->SetPoint(42,0.1052632,405.232);
   graph->SetPoint(43,0.1263158,381.5642);
   graph->SetPoint(44,0.1684211,332.2884);
   graph->SetPoint(45,0.1894737,308.4797);
   graph->SetPoint(46,0.2105263,286.0091);
   graph->SetPoint(47,0.2315789,265.1887);
   graph->SetPoint(48,0.2526316,246.1617);
   graph->SetPoint(49,0.2736842,228.9487);
   graph->SetPoint(50,0.2947368,213.4884);
   graph->SetPoint(51,0.3157895,199.67);
   graph->SetPoint(52,0.3368421,187.3571);
   graph->SetPoint(53,0.3578947,176.4036);
   graph->SetPoint(54,0.3789474,166.6649);
   graph->SetPoint(55,0.4,158.0035);
   graph->SetPoint(56,0.4210526,150.2931);
   graph->SetPoint(57,0.4631579,137.281);
   graph->SetPoint(58,0.5052632,126.8615);
   graph->SetPoint(59,0.5473684,118.4431);
   graph->SetPoint(60,0.5894737,111.5764);
   graph->SetPoint(61,0.6315789,105.9217);
   graph->SetPoint(62,0.6736842,101.2218);
   graph->SetPoint(63,0.7157895,97.28072);
   graph->SetPoint(64,0.8,91.10878);
   graph->SetPoint(65,0.8,91.10878);
   graph->SetPoint(66,0.8842105,91.10878);
   graph->SetPoint(67,0.8842105,0);
   graph->Draw("l");
   
   graph = new TGraph(59);
   graph->SetName("curve_ttbarFitProjected");
   graph->SetTitle("Projection of ttbar Fit");
   graph->SetFillColor(1);
   graph->SetLineStyle(2);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,-0.8842105,0);
   graph->SetPoint(1,-0.8842105,19.21898);
   graph->SetPoint(2,-0.8,19.21898);
   graph->SetPoint(3,-0.7578947,19.88446);
   graph->SetPoint(4,-0.7157895,20.62932);
   graph->SetPoint(5,-0.6736842,21.46419);
   graph->SetPoint(6,-0.6315789,22.40076);
   graph->SetPoint(7,-0.5894737,23.45164);
   graph->SetPoint(8,-0.5473684,24.62998);
   graph->SetPoint(9,-0.5052632,25.94877);
   graph->SetPoint(10,-0.4631579,27.41971);
   graph->SetPoint(11,-0.4210526,29.05148);
   graph->SetPoint(12,-0.3789474,30.84727);
   graph->SetPoint(13,-0.3368421,32.8014);
   graph->SetPoint(14,-0.2947368,34.89514);
   graph->SetPoint(15,-0.2105263,39.33436);
   graph->SetPoint(16,-0.1684211,41.53932);
   graph->SetPoint(17,-0.1263158,43.60172);
   graph->SetPoint(18,-0.1052632,44.54175);
   graph->SetPoint(19,-0.08421053,45.39986);
   graph->SetPoint(20,-0.06315789,46.16039);
   graph->SetPoint(21,-0.04210526,46.80857);
   graph->SetPoint(22,-0.02105263,47.33111);
   graph->SetPoint(23,-6.245005e-17,47.71687);
   graph->SetPoint(24,0.02105263,47.95735);
   graph->SetPoint(25,0.04210526,48.04712);
   graph->SetPoint(26,0.05263158,48.02138);
   graph->SetPoint(27,0.06315789,47.91912);
   graph->SetPoint(28,0.07368421,47.74108);
   graph->SetPoint(29,0.08421053,47.48959);
   graph->SetPoint(30,0.09473684,47.16788);
   graph->SetPoint(31,0.1052632,46.77998);
   graph->SetPoint(32,0.1263158,45.82504);
   graph->SetPoint(33,0.1473684,44.6684);
   graph->SetPoint(34,0.1684211,43.35807);
   graph->SetPoint(35,0.1894737,41.94234);
   graph->SetPoint(36,0.2105263,40.46633);
   graph->SetPoint(37,0.2526316,37.48495);
   graph->SetPoint(38,0.2947368,34.64754);
   graph->SetPoint(39,0.3157895,33.32641);
   graph->SetPoint(40,0.3368421,32.08235);
   graph->SetPoint(41,0.3578947,30.9191);
   graph->SetPoint(42,0.3789474,29.83736);
   graph->SetPoint(43,0.4,28.8356);
   graph->SetPoint(44,0.4210526,27.91078);
   graph->SetPoint(45,0.4421053,27.05887);
   graph->SetPoint(46,0.4631579,26.27528);
   graph->SetPoint(47,0.4842105,25.55517);
   graph->SetPoint(48,0.5052632,24.89367);
   graph->SetPoint(49,0.5473684,23.72767);
   graph->SetPoint(50,0.5894737,22.74205);
   graph->SetPoint(51,0.6315789,21.90622);
   graph->SetPoint(52,0.6736842,21.19442);
   graph->SetPoint(53,0.7157895,20.58535);
   graph->SetPoint(54,0.7578947,20.06155);
   graph->SetPoint(55,0.8,19.60879);
   graph->SetPoint(56,0.8,19.60879);
   graph->SetPoint(57,0.8842105,19.60879);
   graph->SetPoint(58,0.8842105,0);
   graph->Draw("l");
   
   graph = new TGraph(68);
   graph->SetName("curve_otherFitProjected");
   graph->SetTitle("Projection of other Fit");
   graph->SetFillColor(1);
   graph->SetLineStyle(3);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,-0.8842105,0);
   graph->SetPoint(1,-0.8842105,14.49478);
   graph->SetPoint(2,-0.8,14.49478);
   graph->SetPoint(3,-0.7157895,16.08441);
   graph->SetPoint(4,-0.6736842,17.09633);
   graph->SetPoint(5,-0.6315789,18.29883);
   graph->SetPoint(6,-0.5894737,19.73817);
   graph->SetPoint(7,-0.5473684,21.47339);
   graph->SetPoint(8,-0.5052632,23.57949);
   graph->SetPoint(9,-0.4631579,26.15086);
   graph->SetPoint(10,-0.4421053,27.64652);
   graph->SetPoint(11,-0.4210526,29.30397);
   graph->SetPoint(12,-0.4,31.14125);
   graph->SetPoint(13,-0.3789474,33.17747);
   graph->SetPoint(14,-0.3578947,35.43243);
   graph->SetPoint(15,-0.3368421,37.92584);
   graph->SetPoint(16,-0.3157895,40.67637);
   graph->SetPoint(17,-0.2947368,43.70013);
   graph->SetPoint(18,-0.2736842,47.00867);
   graph->SetPoint(19,-0.2526316,50.60644);
   graph->SetPoint(20,-0.2315789,54.48756);
   graph->SetPoint(21,-0.2105263,58.63224);
   graph->SetPoint(22,-0.1894737,63.00279);
   graph->SetPoint(23,-0.1684211,67.53992);
   graph->SetPoint(24,-0.1263158,76.75285);
   graph->SetPoint(25,-0.1052632,81.18509);
   graph->SetPoint(26,-0.08421053,85.30297);
   graph->SetPoint(27,-0.06315789,88.94208);
   graph->SetPoint(28,-0.05263158,90.53069);
   graph->SetPoint(29,-0.04210526,91.93936);
   graph->SetPoint(30,-0.03157895,93.15036);
   graph->SetPoint(31,-0.02105263,94.14791);
   graph->SetPoint(32,-0.01052632,94.91868);
   graph->SetPoint(33,-6.245005e-17,95.45212);
   graph->SetPoint(34,0.01052632,95.74083);
   graph->SetPoint(35,0.02105263,95.77093);
   graph->SetPoint(36,0.03157895,95.41956);
   graph->SetPoint(37,0.04210526,94.65864);
   graph->SetPoint(38,0.05263158,93.50713);
   graph->SetPoint(39,0.06315789,91.99306);
   graph->SetPoint(40,0.07368421,90.15193);
   graph->SetPoint(41,0.08421053,88.02494);
   graph->SetPoint(42,0.09473684,85.65696);
   graph->SetPoint(43,0.1052632,83.0946);
   graph->SetPoint(44,0.1263158,77.57086);
   graph->SetPoint(45,0.1684211,66.05756);
   graph->SetPoint(46,0.1894737,60.55926);
   graph->SetPoint(47,0.2105263,55.43676);
   graph->SetPoint(48,0.2315789,50.76195);
   graph->SetPoint(49,0.2526316,46.55956);
   graph->SetPoint(50,0.2736842,42.82204);
   graph->SetPoint(51,0.2947368,39.52198);
   graph->SetPoint(52,0.3157895,36.62142);
   graph->SetPoint(53,0.3368421,34.07831);
   graph->SetPoint(54,0.3578947,31.85054);
   graph->SetPoint(55,0.3789474,29.89839);
   graph->SetPoint(56,0.4,28.18565);
   graph->SetPoint(57,0.4210526,26.68015);
   graph->SetPoint(58,0.4631579,24.18191);
   graph->SetPoint(59,0.5052632,22.22125);
   graph->SetPoint(60,0.5473684,20.66393);
   graph->SetPoint(61,0.5894737,19.41187);
   graph->SetPoint(62,0.6315789,18.39333);
   graph->SetPoint(63,0.7157895,16.85917);
   graph->SetPoint(64,0.8,15.78015);
   graph->SetPoint(65,0.8,15.78015);
   graph->SetPoint(66,0.8842105,15.78015);
   graph->SetPoint(67,0.8842105,0);
   graph->Draw("l");
   
   TH1 *frame_0b5d2db0 = new TH1D("frame_0b5d2db0","A RooPlot of "sinMHTphiJet"",19,-0.8,0.8);
   frame_0b5d2db0->SetMaximum(489.6021);
   frame_0b5d2db0->SetDirectory(0);
   frame_0b5d2db0->SetStats(0);
   frame_0b5d2db0->SetMarkerStyle(8);
   frame_0b5d2db0->GetXaxis()->SetTitle("sin(#phi_{MHT-Jet})");
   frame_0b5d2db0->GetXaxis()->SetLabelFont(132);
   frame_0b5d2db0->GetXaxis()->SetLabelSize(0.05);
   frame_0b5d2db0->GetXaxis()->SetTitleSize(0.06);
   frame_0b5d2db0->GetXaxis()->SetTitleFont(132);
   frame_0b5d2db0->GetYaxis()->SetTitle("Events");
   frame_0b5d2db0->GetYaxis()->SetLabelFont(132);
   frame_0b5d2db0->GetYaxis()->SetLabelSize(0.05);
   frame_0b5d2db0->GetYaxis()->SetTitleSize(0.06);
   frame_0b5d2db0->GetYaxis()->SetTitleFont(132);
   frame_0b5d2db0->GetZaxis()->SetLabelFont(132);
   frame_0b5d2db0->GetZaxis()->SetLabelSize(0.05);
   frame_0b5d2db0->GetZaxis()->SetTitleSize(0.06);
   frame_0b5d2db0->GetZaxis()->SetTitleFont(132);
   frame_0b5d2db0->Draw("axissame");
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
