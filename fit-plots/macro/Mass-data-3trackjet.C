{
//=========Macro generated from canvas: c/fitResult
//=========  (Wed Mar 11 12:20:37 2009) by ROOT version5.18/00a
   TCanvas *c = new TCanvas("c", "fitResult",4,21,600,300);
   gStyle->SetOptStat(0);
   c->Range(52.77108,-10.67096,113.012,56.02255);
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
   
   TH1 *frame_0af436b0 = new TH1D("frame_0af436b0","A RooPlot of "Mass [GeV/c^{2}]"",19,60,110);
   frame_0af436b0->SetMaximum(52.68788);
   frame_0af436b0->SetDirectory(0);
   frame_0af436b0->SetStats(0);
   frame_0af436b0->SetMarkerStyle(8);
   frame_0af436b0->GetXaxis()->SetTitle("m_{ee}[GeV/c^{2}]");
   frame_0af436b0->GetXaxis()->SetLabelFont(132);
   frame_0af436b0->GetXaxis()->SetLabelSize(0.05);
   frame_0af436b0->GetXaxis()->SetTitleSize(0.06);
   frame_0af436b0->GetXaxis()->SetTitleFont(132);
   frame_0af436b0->GetYaxis()->SetTitle("Events");
   frame_0af436b0->GetYaxis()->SetLabelFont(132);
   frame_0af436b0->GetYaxis()->SetLabelSize(0.05);
   frame_0af436b0->GetYaxis()->SetTitleSize(0.06);
   frame_0af436b0->GetYaxis()->SetTitleFont(132);
   frame_0af436b0->GetZaxis()->SetLabelFont(132);
   frame_0af436b0->GetZaxis()->SetLabelSize(0.05);
   frame_0af436b0->GetZaxis()->SetTitleSize(0.06);
   frame_0af436b0->GetZaxis()->SetTitleFont(132);
   frame_0af436b0->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(19);
   grae->SetName("data_plot__mass");
   grae->SetTitle("Histogram of data_plot__mass");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,61.31579,0.7860941);
   grae->SetPointError(0,1.315789,1.315789,0.3156496,0.3156496);
   grae->SetPoint(1,63.94737,1.495432);
   grae->SetPointError(1,1.315789,1.315789,0.519874,0.519874);
   grae->SetPoint(2,66.57895,0.597358);
   grae->SetPointError(2,1.315789,1.315789,0.1407986,0.1407986);
   grae->SetPoint(3,69.21053,2.77098);
   grae->SetPointError(3,1.315789,1.315789,0.824824,0.824824);
   grae->SetPoint(4,71.84211,1.717355);
   grae->SetPointError(4,1.315789,1.315789,0.5926051,0.5926051);
   grae->SetPoint(5,74.47368,1.163566);
   grae->SetPointError(5,1.315789,1.315789,0.5091714,0.5091714);
   grae->SetPoint(6,77.10526,2.383124);
   grae->SetPointError(6,1.315789,1.315789,0.7706595,0.7706595);
   grae->SetPoint(7,79.73684,3.862919);
   grae->SetPointError(7,1.315789,1.315789,1.01131,1.01131);
   grae->SetPoint(8,82.36842,5.498384);
   grae->SetPointError(8,1.315789,1.315789,1.196984,1.196984);
   grae->SetPoint(9,85,10.13906);
   grae->SetPointError(9,1.315789,1.315789,1.687917,1.687917);
   grae->SetPoint(10,87.63158,21.12747);
   grae->SetPointError(10,1.315789,1.315789,2.451227,2.451227);
   grae->SetPoint(11,90.26316,46.08174);
   grae->SetPointError(11,1.315789,1.315789,3.626253,3.626253);
   grae->SetPoint(12,92.89474,33.71821);
   grae->SetPointError(12,1.315789,1.315789,3.094655,3.094655);
   grae->SetPoint(13,95.52632,10.65453);
   grae->SetPointError(13,1.315789,1.315789,1.711061,1.711061);
   grae->SetPoint(14,98.15789,3.967734);
   grae->SetPointError(14,1.315789,1.315789,0.9698925,0.9698925);
   grae->SetPoint(15,100.7895,3.669054);
   grae->SetPointError(15,1.315789,1.315789,0.9647691,0.9647691);
   grae->SetPoint(16,103.4211,2.549057);
   grae->SetPointError(16,1.315789,1.315789,0.774224,0.774224);
   grae->SetPoint(17,106.0526,0.6201614);
   grae->SetPointError(17,1.315789,1.315789,0.3068028,0.3068028);
   grae->SetPoint(18,108.6842,0.6865345);
   grae->SetPointError(18,1.315789,1.315789,0.3103718,0.3103718);
   grae->Draw("p");
   
   TGraph *graph = new TGraph(80);
   graph->SetName("curve_myFitProjected");
   graph->SetTitle("Projection of Ratio ZtoEE");
   graph->SetFillColor(1);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,57.36842,0);
   graph->SetPoint(1,57.36842,1.301726);
   graph->SetPoint(2,60,1.301726);
   graph->SetPoint(3,62.63158,1.344929);
   graph->SetPoint(4,65.26316,1.399461);
   graph->SetPoint(5,67.89474,1.472074);
   graph->SetPoint(6,70.52632,1.574828);
   graph->SetPoint(7,73.15789,1.730965);
   graph->SetPoint(8,75.78947,1.98979);
   graph->SetPoint(9,78.42105,2.46941);
   graph->SetPoint(10,79.73684,2.87748);
   graph->SetPoint(11,81.05263,3.498776);
   graph->SetPoint(12,81.71053,3.934381);
   graph->SetPoint(13,82.36842,4.491556);
   graph->SetPoint(14,83.02632,5.213178);
   graph->SetPoint(15,83.68421,6.158867);
   graph->SetPoint(16,84.34211,7.410909);
   graph->SetPoint(17,84.67105,8.18533);
   graph->SetPoint(18,85,9.0807);
   graph->SetPoint(19,85.32895,10.11626);
   graph->SetPoint(20,85.65789,11.3133);
   graph->SetPoint(21,85.98684,12.6947);
   graph->SetPoint(22,86.31579,14.28414);
   graph->SetPoint(23,86.64474,16.1046);
   graph->SetPoint(24,86.97368,18.17628);
   graph->SetPoint(25,87.30263,20.51345);
   graph->SetPoint(26,87.63158,23.12049);
   graph->SetPoint(27,87.96053,25.98699);
   graph->SetPoint(28,88.28947,29.08235);
   graph->SetPoint(29,88.94737,35.70718);
   graph->SetPoint(30,89.27632,39.03685);
   graph->SetPoint(31,89.60526,42.1982);
   graph->SetPoint(32,89.76974,43.66624);
   graph->SetPoint(33,89.93421,45.03164);
   graph->SetPoint(34,90.09868,46.27393);
   graph->SetPoint(35,90.26316,47.37349);
   graph->SetPoint(36,90.42763,48.31217);
   graph->SetPoint(37,90.59211,49.07389);
   graph->SetPoint(38,90.75658,49.64522);
   graph->SetPoint(39,90.92105,50.01583);
   graph->SetPoint(40,91.08553,50.17893);
   graph->SetPoint(41,91.25,50.09101);
   graph->SetPoint(42,91.41447,49.64697);
   graph->SetPoint(43,91.57895,48.85483);
   graph->SetPoint(44,91.74342,47.73898);
   graph->SetPoint(45,91.90789,46.33272);
   graph->SetPoint(46,92.07237,44.67619);
   graph->SetPoint(47,92.23684,42.81408);
   graph->SetPoint(48,92.40132,40.79326);
   graph->SetPoint(49,92.56579,38.6605);
   graph->SetPoint(50,92.89474,34.23453);
   graph->SetPoint(51,93.22368,29.8445);
   graph->SetPoint(52,93.55263,25.7154);
   graph->SetPoint(53,93.71711,23.79477);
   graph->SetPoint(54,93.88158,21.9846);
   graph->SetPoint(55,94.04605,20.29041);
   graph->SetPoint(56,94.21053,18.71432);
   graph->SetPoint(57,94.375,17.25563);
   graph->SetPoint(58,94.53947,15.91149);
   graph->SetPoint(59,94.70395,14.67743);
   graph->SetPoint(60,94.86842,13.54784);
   graph->SetPoint(61,95.19737,11.57649);
   graph->SetPoint(62,95.52632,9.943698);
   graph->SetPoint(63,95.85526,8.596241);
   graph->SetPoint(64,96.18421,7.485438);
   graph->SetPoint(65,96.51316,6.568868);
   graph->SetPoint(66,96.84211,5.81071);
   graph->SetPoint(67,97.17105,5.181339);
   graph->SetPoint(68,97.5,4.656585);
   graph->SetPoint(69,98.15789,3.846531);
   graph->SetPoint(70,98.81579,3.265682);
   graph->SetPoint(71,99.47368,2.839836);
   graph->SetPoint(72,100.7895,2.27675);
   graph->SetPoint(73,102.1053,1.935579);
   graph->SetPoint(74,104.7368,1.562389);
   graph->SetPoint(75,107.3684,1.370972);
   graph->SetPoint(76,110,1.256298);
   graph->SetPoint(77,110,1.256298);
   graph->SetPoint(78,112.6316,1.256298);
   graph->SetPoint(79,112.6316,0);
   graph->Draw("l");
   
   graph = new TGraph(44);
   graph->SetName("curve_myFitProjected");
   graph->SetTitle("Projection of Ratio ZtoEE");
   graph->SetFillColor(1);
   graph->SetLineStyle(2);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,57.36842,0);
   graph->SetPoint(1,57.36842,0.4910256);
   graph->SetPoint(2,60,0.4910256);
   graph->SetPoint(3,61.31579,0.4951452);
   graph->SetPoint(4,62.63158,0.4989806);
   graph->SetPoint(5,63.94737,0.5025319);
   graph->SetPoint(6,65.26316,0.505799);
   graph->SetPoint(7,66.57895,0.508782);
   graph->SetPoint(8,67.89474,0.5114808);
   graph->SetPoint(9,69.21053,0.5138954);
   graph->SetPoint(10,70.52632,0.5160259);
   graph->SetPoint(11,71.84211,0.5178723);
   graph->SetPoint(12,73.15789,0.5194344);
   graph->SetPoint(13,74.47368,0.5207125);
   graph->SetPoint(14,75.78947,0.5217063);
   graph->SetPoint(15,77.10526,0.522416);
   graph->SetPoint(16,78.42105,0.5228416);
   graph->SetPoint(17,79.73684,0.522983);
   graph->SetPoint(18,81.05263,0.5228402);
   graph->SetPoint(19,82.36842,0.5224133);
   graph->SetPoint(20,83.68421,0.5217022);
   graph->SetPoint(21,85,0.520707);
   graph->SetPoint(22,86.31579,0.5194276);
   graph->SetPoint(23,87.63158,0.517864);
   graph->SetPoint(24,88.94737,0.5160163);
   graph->SetPoint(25,90.26316,0.5138845);
   graph->SetPoint(26,91.57895,0.5114684);
   graph->SetPoint(27,92.89474,0.5087683);
   graph->SetPoint(28,94.21053,0.5057839);
   graph->SetPoint(29,95.52632,0.5025154);
   graph->SetPoint(30,96.84211,0.4989628);
   graph->SetPoint(31,98.15789,0.495126);
   graph->SetPoint(32,99.47368,0.491005);
   graph->SetPoint(33,100.7895,0.4865999);
   graph->SetPoint(34,102.1053,0.4819106);
   graph->SetPoint(35,103.4211,0.4769372);
   graph->SetPoint(36,104.7368,0.4716796);
   graph->SetPoint(37,106.0526,0.4661378);
   graph->SetPoint(38,107.3684,0.4603119);
   graph->SetPoint(39,108.6842,0.4542019);
   graph->SetPoint(40,110,0.4478076);
   graph->SetPoint(41,110,0.4478076);
   graph->SetPoint(42,112.6316,0.4478076);
   graph->SetPoint(43,112.6316,0);
   graph->Draw("l");
   
   TH1 *frame_0af436b0 = new TH1D("frame_0af436b0","A RooPlot of "Mass [GeV/c^{2}]"",19,60,110);
   frame_0af436b0->SetMaximum(52.68788);
   frame_0af436b0->SetDirectory(0);
   frame_0af436b0->SetStats(0);
   frame_0af436b0->SetMarkerStyle(8);
   frame_0af436b0->GetXaxis()->SetTitle("m_{ee}[GeV/c^{2}]");
   frame_0af436b0->GetXaxis()->SetLabelFont(132);
   frame_0af436b0->GetXaxis()->SetLabelSize(0.05);
   frame_0af436b0->GetXaxis()->SetTitleSize(0.06);
   frame_0af436b0->GetXaxis()->SetTitleFont(132);
   frame_0af436b0->GetYaxis()->SetTitle("Events");
   frame_0af436b0->GetYaxis()->SetLabelFont(132);
   frame_0af436b0->GetYaxis()->SetLabelSize(0.05);
   frame_0af436b0->GetYaxis()->SetTitleSize(0.06);
   frame_0af436b0->GetYaxis()->SetTitleFont(132);
   frame_0af436b0->GetZaxis()->SetLabelFont(132);
   frame_0af436b0->GetZaxis()->SetLabelSize(0.05);
   frame_0af436b0->GetZaxis()->SetTitleSize(0.06);
   frame_0af436b0->GetZaxis()->SetTitleFont(132);
   frame_0af436b0->Draw("axissame");
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
