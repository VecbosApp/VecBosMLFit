#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <pair.h>

#include <TFile.h>
#include <TTree.h>
#include <TChain.h>

#include <RooFitResult.h>
#include <RooArgList.h>
#include <RooRealVar.h>

using namespace std;

std::pair<float, float> getParameterVal(RooFitResult *fitres, const char *name);

void printPdfTablesZ(const char *jetflavour="calojet") {

  char nametextfile[200];
  sprintf(nametextfile,"pdfParameters_Zee_%s.tex",jetflavour);

  ofstream textfile;
  textfile.open(nametextfile, ios_base::trunc);
  textfile.precision(2);

  textfile << "\\documentclass{article}" << endl;
  textfile << "\\begin{document}" << endl;

  textfile << "\n\n\n\n" << endl;

  // ==============
  // signal PDFs
  // ==============

  textfile << "% ===== SIGNAL Z->EE PDFS PARAMETERS ==== %" << endl; 
  textfile << "\n\n\n\n" << endl;

  // mee Cruijff
  textfile << "% SIGNAL MEE CRUIJFF\n" << endl;
  vector<string> params_sig_mass;
  params_sig_mass.push_back("sig_Mass_mean");
  params_sig_mass.push_back("sig_Mass_sigmaL");
  params_sig_mass.push_back("sig_Mass_sigmaR");
  params_sig_mass.push_back("sig_Mass_alphaL");
  params_sig_mass.push_back("sig_Mass_alphaR");

  vector<string> params_sig_mass_name;
  params_sig_mass_name.push_back("$mean$");
  params_sig_mass_name.push_back("$\\sigma_L$");
  params_sig_mass_name.push_back("$\\sigma_R$");
  params_sig_mass_name.push_back("$\\alpha_L$");
  params_sig_mass_name.push_back("$\\alpha_R$");

  textfile << "\\begin{table}[p]" << endl
           << "\\begin{small}" << endl
           << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|}" << endl
           << "\\hline" << endl
           << "parameter & Z+1jet & Z+2jets & Z+3jets & Z+4jets \t\\\\" << endl
           << "\\hline" << endl;

  for( int par=0; par<(int)params_sig_mass.size(); par++ ) {

    textfile << params_sig_mass_name[par] << "\t&\t";

    for( int jet=1; jet<=4; jet++ ) {
      char namefile[200];
      sprintf(namefile,"shapesZee/root/fitRes-Zonly-%d%s.root",jet,jetflavour);
      TFile file(namefile);
      RooFitResult *fitres = (RooFitResult*)file.Get("nll");
      pair<float,float> value = getParameterVal(fitres, params_sig_mass[par].c_str());
      textfile << fixed << value.first << " $\\pm$ " << value.second << "\t"; 
      if(jet<4) textfile << "&\t";
      else textfile << "\\\\" << endl;
    }
  }

  textfile << "\\hline" << endl
           << "\\end{tabular}" << endl
           << "\\label{tab:sig_mass}" << endl
           << "\\end{center}" << endl
           << "\\end{small}" << endl
           << "\\end{table}" << endl;


  textfile << "\n\n\n\n\n\n" << endl;

  // sinMHTphiMET Cruijff
  textfile << "% SIGNAL sinMHTphiMET CRUIJFF\n " << endl;
  vector<string> params_sig_sinMHTphiMET;
  params_sig_sinMHTphiMET.push_back("sig_sinMHTphiMET_mean");
  params_sig_sinMHTphiMET.push_back("sig_sinMHTphiMET_sigmaL");
  params_sig_sinMHTphiMET.push_back("sig_sinMHTphiMET_sigmaR");
  params_sig_sinMHTphiMET.push_back("sig_sinMHTphiMET_alphaL");
  params_sig_sinMHTphiMET.push_back("sig_sinMHTphiMET_alphaR");

  vector<string> params_sig_sinMHTphiMET_name;
  params_sig_sinMHTphiMET_name.push_back("$mean$");
  params_sig_sinMHTphiMET_name.push_back("$\\sigma_L$");
  params_sig_sinMHTphiMET_name.push_back("$\\sigma_R$");
  params_sig_sinMHTphiMET_name.push_back("$\\alpha_L$");
  params_sig_sinMHTphiMET_name.push_back("$\\alpha_R$");

  textfile << "\\begin{table}[p]" << endl
           << "\\begin{small}" << endl
           << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|}" << endl
           << "\\hline" << endl
           << "parameter & Z+1jet & Z+2jets & Z+3jets & Z+4jets \t\\\\" << endl
           << "\\hline" << endl;

  for( int par=0; par<(int)params_sig_sinMHTphiMET.size(); par++ ) {

    textfile << params_sig_sinMHTphiMET_name[par] << "\t&\t";

    for( int jet=1; jet<=4; jet++ ) {
      char namefile[200];
      sprintf(namefile,"shapesZee/root/fitRes-Zonly-%d%s.root",jet,jetflavour);
      TFile file(namefile);
      RooFitResult *fitres = (RooFitResult*)file.Get("nll");
      pair<float,float> value = getParameterVal(fitres, params_sig_sinMHTphiMET[par].c_str());
      textfile << fixed << value.first << " $\\pm$ " << value.second << "\t"; 
      if(jet<4) textfile << "&\t";
      else textfile << "\\\\" << endl;
    }
  }

  textfile << "\\hline" << endl
           << "\\end{tabular}" << endl
           << "\\label{tab:sig_sinMHTphiMET}" << endl
           << "\\end{center}" << endl
           << "\\end{small}" << endl
           << "\\end{table}" << endl;



  textfile << "\n\n\n\n" << endl;




  // ==============
  // background PDFs
  // ==============

  textfile << "% ===== BACKGROUND Z->EE PDFS PARAMETERS ==== %" << endl;
  textfile << "\n\n\n\n" << endl;


  // bkg mee poly 2
  textfile << "% BKG MEE POLY 2\n" << endl;
  vector<string> params_bkg_mass;
  params_bkg_mass.push_back("bkg_Mass_p1");
  params_bkg_mass.push_back("bkg_Mass_p2");

  vector<string> params_bkg_mass_name;
  params_bkg_mass_name.push_back("$p_1$");
  params_bkg_mass_name.push_back("$p_2$");

  textfile << "\\begin{table}[p]" << endl
           << "\\begin{small}" << endl
           << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|}" << endl
           << "\\hline" << endl
           << "parameter & Z+1jet & Z+2jets & Z+3jets & Z+4jets \t\\\\" << endl
           << "\\hline" << endl;

  for( int par=0; par<(int)params_bkg_mass.size(); par++ ) {

    textfile << params_bkg_mass_name[par] << "\t&\t";

    for( int jet=1; jet<=4; jet++ ) {
      char namefile[200];
      sprintf(namefile,"shapesZee/root/fitRes-bkgonly-%d%s.root",jet,jetflavour);
      TFile file(namefile);
      RooFitResult *fitres = (RooFitResult*)file.Get("nll");
      pair<float,float> value = getParameterVal(fitres, params_bkg_mass[par].c_str());
      textfile << fixed << value.first << " $\\pm$ " << value.second << "\t"; 
      if(jet<4) textfile << "&\t";
      else textfile << "\\\\" << endl;
    }
  }

  textfile << "\\hline" << endl
           << "\\end{tabular}" << endl
           << "\\label{tab:bkg_mass}" << endl
           << "\\end{center}" << endl
           << "\\end{small}" << endl
           << "\\end{table}" << endl;


  textfile << "\n\n\n\n\n\n" << endl;

  // bkg sinMHTphiMET poly 1
  textfile << "% BKG sinMHTphiMET POLY 1\n" << endl;
  vector<string> params_bkg_sinMHTphiMET;
  params_bkg_sinMHTphiMET.push_back("bkg_sinMHTphiMET_p1");

  vector<string> params_bkg_sinMHTphiMET_name;
  params_bkg_sinMHTphiMET_name.push_back("$p_1$");

  textfile << "\\begin{table}[p]" << endl
           << "\\begin{small}" << endl
           << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|}" << endl
           << "\\hline" << endl
           << "parameter & Z+1jet & Z+2jets & Z+3jets & Z+4jets \t\\\\" << endl
           << "\\hline" << endl;

  for( int par=0; par<(int)params_bkg_sinMHTphiMET.size(); par++ ) {

    textfile << params_bkg_sinMHTphiMET_name[par] << "\t&\t";

    for( int jet=1; jet<=4; jet++ ) {
      char namefile[200];
      sprintf(namefile,"shapesZee/root/fitRes-bkgonly-%d%s.root",jet,jetflavour);
      TFile file(namefile);
      RooFitResult *fitres = (RooFitResult*)file.Get("nll");
      pair<float,float> value = getParameterVal(fitres, params_bkg_sinMHTphiMET[par].c_str());
      textfile << fixed << value.first << " $\\pm$ " << value.second << "\t"; 
      if(jet<4) textfile << "&\t";
      else textfile << "\\\\" << endl;
    }
  }

  textfile << "\\hline" << endl
           << "\\end{tabular}" << endl
           << "\\label{tab:bkg_sinMHTphiMET}" << endl
           << "\\end{center}" << endl
           << "\\end{small}" << endl
           << "\\end{table}" << endl;

  textfile << "\\end{document}" << endl;


}


std::pair<float, float> getParameterVal(RooFitResult *fitres, const char *name) {

  RooArgList floatingList = fitres->floatParsFinal();
  RooRealVar *var = (RooRealVar*)floatingList.find(name);

  if(var==0) return std::make_pair(0,0);

  float val = var->getVal();
  float err = var->getError();

  return std::make_pair(val,err);

}
