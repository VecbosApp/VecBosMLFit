{
//=========Macro generated from canvas: c/fitResult
//=========  (Sun Mar 15 11:02:39 2009) by ROOT version5.18/00a
   TCanvas *c = new TCanvas("c", "fitResult",4,21,600,300);
   gStyle->SetOptStat(0);
   c->Range(-1.031325,-112.2788,0.8963855,589.4638);
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
   
   TH1 *frame_0a402b08 = new TH1D("frame_0a402b08","A RooPlot of "sinMHTphiJet"",15,-0.8,0.8);
   frame_0a402b08->SetMaximum(554.3767);
   frame_0a402b08->SetDirectory(0);
   frame_0a402b08->SetStats(0);
   frame_0a402b08->SetMarkerStyle(8);
   frame_0a402b08->GetXaxis()->SetTitle("sin(#phi_{MHT-Jet})");
   frame_0a402b08->GetXaxis()->SetLabelFont(132);
   frame_0a402b08->GetXaxis()->SetLabelSize(0.05);
   frame_0a402b08->GetXaxis()->SetTitleSize(0.06);
   frame_0a402b08->GetXaxis()->SetTitleFont(132);
   frame_0a402b08->GetYaxis()->SetTitle("Events");
   frame_0a402b08->GetYaxis()->SetLabelFont(132);
   frame_0a402b08->GetYaxis()->SetLabelSize(0.05);
   frame_0a402b08->GetYaxis()->SetTitleSize(0.06);
   frame_0a402b08->GetYaxis()->SetTitleFont(132);
   frame_0a402b08->GetZaxis()->SetLabelFont(132);
   frame_0a402b08->GetZaxis()->SetLabelSize(0.05);
   frame_0a402b08->GetZaxis()->SetTitleSize(0.06);
   frame_0a402b08->GetZaxis()->SetTitleFont(132);
   frame_0a402b08->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(15);
   grae->SetName("ttjetsMADGRAPH_plot__sinMHTphiJet");
   grae->SetTitle("Histogram of ttjetsMADGRAPH_plot__sinMHTphiJet");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,-0.7466667,96);
   grae->SetPointError(0,0.05333333,0.05333333,9.780866,10.83201);
   grae->SetPoint(1,-0.64,106);
   grae->SetPointError(1,0.05333333,0.05333333,9.807764,10.80776);
   grae->SetPoint(2,-0.5333333,152);
   grae->SetPointError(2,0.05333333,0.05333333,11.83896,12.83896);
   grae->SetPoint(3,-0.4266667,163);
   grae->SetPointError(3,0.05333333,0.05333333,12.27693,13.27693);
   grae->SetPoint(4,-0.32,220);
   grae->SetPointError(4,0.05333333,0.05333333,14.34082,15.34082);
   grae->SetPoint(5,-0.2133333,305);
   grae->SetPointError(5,0.05333333,0.05333333,16.97141,17.97141);
   grae->SetPoint(6,-0.1066667,420);
   grae->SetPointError(6,0.05333333,0.05333333,20,21);
   grae->SetPoint(7,6.938894e-18,505);
   grae->SetPointError(7,0.05333333,0.05333333,21.97777,22.97777);
   grae->SetPoint(8,0.1066667,424);
   grae->SetPointError(8,0.05333333,0.05333333,20.09733,21.09733);
   grae->SetPoint(9,0.2133333,321);
   grae->SetPointError(9,0.05333333,0.05333333,17.42345,18.42345);
   grae->SetPoint(10,0.32,226);
   grae->SetPointError(10,0.05333333,0.05333333,14.54161,15.54161);
   grae->SetPoint(11,0.4266667,175);
   grae->SetPointError(11,0.05333333,0.05333333,12.7382,13.7382);
   grae->SetPoint(12,0.5333333,144);
   grae->SetPointError(12,0.05333333,0.05333333,11.51041,12.51041);
   grae->SetPoint(13,0.64,94);
   grae->SetPointError(13,0.05333333,0.05333333,9.678085,10.72977);
   grae->SetPoint(14,0.7466667,91);
   grae->SetPointError(14,0.05333333,0.05333333,9.521834,10.57436);
   grae->Draw("p");
   
   TGraph *graph = new TGraph(63);
   graph->SetName("curve_myFitProjected");
   graph->SetTitle("Projection of Ratio WtoENu");
   graph->SetFillColor(1);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,-0.9066667,0);
   graph->SetPoint(1,-0.9066667,97.77326);
   graph->SetPoint(2,-0.8,97.77326);
   graph->SetPoint(3,-0.7466667,102.0549);
   graph->SetPoint(4,-0.6933333,107.2976);
   graph->SetPoint(5,-0.64,113.7958);
   graph->SetPoint(6,-0.5866667,121.9559);
   graph->SetPoint(7,-0.5333333,132.343);
   graph->SetPoint(8,-0.5066667,138.6074);
   graph->SetPoint(9,-0.48,145.7464);
   graph->SetPoint(10,-0.4533333,153.9068);
   graph->SetPoint(11,-0.4266667,163.26);
   graph->SetPoint(12,-0.4,174.0036);
   graph->SetPoint(13,-0.3733333,186.3611);
   graph->SetPoint(14,-0.3466667,200.5785);
   graph->SetPoint(15,-0.32,216.9147);
   graph->SetPoint(16,-0.2933333,235.6229);
   graph->SetPoint(17,-0.2666667,256.9168);
   graph->SetPoint(18,-0.24,280.9184);
   graph->SetPoint(19,-0.2133333,307.5826);
   graph->SetPoint(20,-0.1866667,336.5984);
   graph->SetPoint(21,-0.16,367.2787);
   graph->SetPoint(22,-0.1333333,398.4647);
   graph->SetPoint(23,-0.1066667,428.49);
   graph->SetPoint(24,-0.09333333,442.4239);
   graph->SetPoint(25,-0.08,455.2587);
   graph->SetPoint(26,-0.06666667,466.7038);
   graph->SetPoint(27,-0.05333333,476.4794);
   graph->SetPoint(28,-0.04,484.3313);
   graph->SetPoint(29,-0.02666667,490.0445);
   graph->SetPoint(30,-0.01333333,493.457);
   graph->SetPoint(31,6.938894e-18,494.471);
   graph->SetPoint(32,0.01333333,493.3289);
   graph->SetPoint(33,0.02666667,490.2544);
   graph->SetPoint(34,0.04,485.3145);
   graph->SetPoint(35,0.05333333,478.6145);
   graph->SetPoint(36,0.06666667,470.2936);
   graph->SetPoint(37,0.08,460.518);
   graph->SetPoint(38,0.09333333,449.474);
   graph->SetPoint(39,0.1066667,437.3604);
   graph->SetPoint(40,0.1333333,410.7381);
   graph->SetPoint(41,0.16,382.228);
   graph->SetPoint(42,0.2133333,324.8177);
   graph->SetPoint(43,0.24,297.8155);
   graph->SetPoint(44,0.2666667,272.7154);
   graph->SetPoint(45,0.2933333,249.7784);
   graph->SetPoint(46,0.32,229.0835);
   graph->SetPoint(47,0.3466667,210.5835);
   graph->SetPoint(48,0.3733333,194.152);
   graph->SetPoint(49,0.4,179.6193);
   graph->SetPoint(50,0.4266667,166.7973);
   graph->SetPoint(51,0.4533333,155.4966);
   graph->SetPoint(52,0.48,145.5367);
   graph->SetPoint(53,0.5066667,136.751);
   graph->SetPoint(54,0.5333333,128.9899);
   graph->SetPoint(55,0.5866667,116.0268);
   graph->SetPoint(56,0.64,105.7759);
   graph->SetPoint(57,0.6933333,97.58331);
   graph->SetPoint(58,0.7466667,90.96327);
   graph->SetPoint(59,0.8,85.55569);
   graph->SetPoint(60,0.8,85.55569);
   graph->SetPoint(61,0.9066667,85.55569);
   graph->SetPoint(62,0.9066667,0);
   graph->Draw("l");
   
   TH1 *frame_0a402b08 = new TH1D("frame_0a402b08","A RooPlot of "sinMHTphiJet"",15,-0.8,0.8);
   frame_0a402b08->SetMaximum(554.3767);
   frame_0a402b08->SetDirectory(0);
   frame_0a402b08->SetStats(0);
   frame_0a402b08->SetMarkerStyle(8);
   frame_0a402b08->GetXaxis()->SetTitle("sin(#phi_{MHT-Jet})");
   frame_0a402b08->GetXaxis()->SetLabelFont(132);
   frame_0a402b08->GetXaxis()->SetLabelSize(0.05);
   frame_0a402b08->GetXaxis()->SetTitleSize(0.06);
   frame_0a402b08->GetXaxis()->SetTitleFont(132);
   frame_0a402b08->GetYaxis()->SetTitle("Events");
   frame_0a402b08->GetYaxis()->SetLabelFont(132);
   frame_0a402b08->GetYaxis()->SetLabelSize(0.05);
   frame_0a402b08->GetYaxis()->SetTitleSize(0.06);
   frame_0a402b08->GetYaxis()->SetTitleFont(132);
   frame_0a402b08->GetZaxis()->SetLabelFont(132);
   frame_0a402b08->GetZaxis()->SetLabelSize(0.05);
   frame_0a402b08->GetZaxis()->SetTitleSize(0.06);
   frame_0a402b08->GetZaxis()->SetTitleFont(132);
   frame_0a402b08->Draw("axissame");
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
