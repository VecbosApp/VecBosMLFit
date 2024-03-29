{
//=========Macro generated from canvas: c/fitResult
//=========  (Sun Mar 15 11:06:46 2009) by ROOT version5.18/00a
   TCanvas *c = new TCanvas("c", "fitResult",4,21,600,300);
   gStyle->SetOptStat(0);
   c->Range(-1.807229,-2.540232,263.253,13.33622);
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
   
   TH1 *frame_0ab1f428 = new TH1D("frame_0ab1f428","A RooPlot of "Transverse W Mass [GeV/c^{2}]"",7,30,250);
   frame_0ab1f428->SetMaximum(12.5424);
   frame_0ab1f428->SetDirectory(0);
   frame_0ab1f428->SetStats(0);
   frame_0ab1f428->SetMarkerStyle(8);
   frame_0ab1f428->GetXaxis()->SetTitle("M_{T}[GeV/c^{2}]");
   frame_0ab1f428->GetXaxis()->SetLabelFont(132);
   frame_0ab1f428->GetXaxis()->SetLabelSize(0.05);
   frame_0ab1f428->GetXaxis()->SetTitleSize(0.06);
   frame_0ab1f428->GetXaxis()->SetTitleFont(132);
   frame_0ab1f428->GetYaxis()->SetTitle("Events");
   frame_0ab1f428->GetYaxis()->SetLabelFont(132);
   frame_0ab1f428->GetYaxis()->SetLabelSize(0.05);
   frame_0ab1f428->GetYaxis()->SetTitleSize(0.06);
   frame_0ab1f428->GetYaxis()->SetTitleFont(132);
   frame_0ab1f428->GetZaxis()->SetLabelFont(132);
   frame_0ab1f428->GetZaxis()->SetLabelSize(0.05);
   frame_0ab1f428->GetZaxis()->SetTitleSize(0.06);
   frame_0ab1f428->GetZaxis()->SetTitleFont(132);
   frame_0ab1f428->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(7);
   grae->SetName("other_plot__Mt");
   grae->SetTitle("Histogram of other_plot__Mt");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,45.71429,8);
   grae->SetPointError(0,15.71429,15.71429,2.768386,3.945141);
   grae->SetPoint(1,77.14286,6);
   grae->SetPointError(1,15.71429,15.71429,2.379931,3.583641);
   grae->SetPoint(2,108.5714,5);
   grae->SetPointError(2,15.71429,15.71429,2.159691,3.382473);
   grae->SetPoint(3,140,4);
   grae->SetPointError(3,15.71429,15.71429,1.914339,3.162753);
   grae->SetPoint(4,171.4286,2);
   grae->SetPointError(4,15.71429,15.71429,1.291815,2.63786);
   grae->SetPoint(5,202.8571,2);
   grae->SetPointError(5,15.71429,15.71429,1.291815,2.63786);
   grae->SetPoint(6,234.2857,0);
   grae->SetPointError(6,15.71429,15.71429,0,1.147874);
   grae->Draw("p");
   
   TGraph *graph = new TGraph(36);
   graph->SetName("curve_myFitProjected");
   graph->SetTitle("Projection of Ratio WtoENu");
   graph->SetFillColor(1);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,-1.428571,0);
   graph->SetPoint(1,-1.428571,8.08204);
   graph->SetPoint(2,30,8.08204);
   graph->SetPoint(3,33.92857,8.104913);
   graph->SetPoint(4,37.85714,8.109464);
   graph->SetPoint(5,41.78571,8.095367);
   graph->SetPoint(6,45.71429,8.062708);
   graph->SetPoint(7,49.64286,8.011712);
   graph->SetPoint(8,53.57143,7.942728);
   graph->SetPoint(9,57.5,7.856227);
   graph->SetPoint(10,61.42857,7.752797);
   graph->SetPoint(11,69.28571,7.498028);
   graph->SetPoint(12,77.14286,7.185147);
   graph->SetPoint(13,85,6.822197);
   graph->SetPoint(14,92.85714,6.418194);
   graph->SetPoint(15,100.7143,5.982757);
   graph->SetPoint(16,108.5714,5.525732);
   graph->SetPoint(17,124.2857,4.585288);
   graph->SetPoint(18,140,3.667274);
   graph->SetPoint(19,147.8571,3.234682);
   graph->SetPoint(20,155.7143,2.826962);
   graph->SetPoint(21,163.5714,2.447981);
   graph->SetPoint(22,171.4286,2.100372);
   graph->SetPoint(23,179.2857,1.785601);
   graph->SetPoint(24,187.1429,1.504086);
   graph->SetPoint(25,195,1.255338);
   graph->SetPoint(26,202.8571,1.038123);
   graph->SetPoint(27,210.7143,0.8506221);
   graph->SetPoint(28,218.5714,0.6905969);
   graph->SetPoint(29,226.4286,0.5555364);
   graph->SetPoint(30,234.2857,0.4427927);
   graph->SetPoint(31,242.1429,0.3496941);
   graph->SetPoint(32,250,0.2736378);
   graph->SetPoint(33,250,0.2736378);
   graph->SetPoint(34,281.4286,0.2736378);
   graph->SetPoint(35,281.4286,0);
   graph->Draw("l");
   
   TH1 *frame_0ab1f428 = new TH1D("frame_0ab1f428","A RooPlot of "Transverse W Mass [GeV/c^{2}]"",7,30,250);
   frame_0ab1f428->SetMaximum(12.5424);
   frame_0ab1f428->SetDirectory(0);
   frame_0ab1f428->SetStats(0);
   frame_0ab1f428->SetMarkerStyle(8);
   frame_0ab1f428->GetXaxis()->SetTitle("M_{T}[GeV/c^{2}]");
   frame_0ab1f428->GetXaxis()->SetLabelFont(132);
   frame_0ab1f428->GetXaxis()->SetLabelSize(0.05);
   frame_0ab1f428->GetXaxis()->SetTitleSize(0.06);
   frame_0ab1f428->GetXaxis()->SetTitleFont(132);
   frame_0ab1f428->GetYaxis()->SetTitle("Events");
   frame_0ab1f428->GetYaxis()->SetLabelFont(132);
   frame_0ab1f428->GetYaxis()->SetLabelSize(0.05);
   frame_0ab1f428->GetYaxis()->SetTitleSize(0.06);
   frame_0ab1f428->GetYaxis()->SetTitleFont(132);
   frame_0ab1f428->GetZaxis()->SetLabelFont(132);
   frame_0ab1f428->GetZaxis()->SetLabelSize(0.05);
   frame_0ab1f428->GetZaxis()->SetTitleSize(0.06);
   frame_0ab1f428->GetZaxis()->SetTitleFont(132);
   frame_0ab1f428->Draw("axissame");
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
