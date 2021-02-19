// include ROOT and C++ headers
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <TF1.h>
#include <TH1.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TFile.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TEnv.h>
#include <THStack.h>
#include <TFile.h>
#include <TTree.h>
#include <TKey.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLatex.h>
#include <TImage.h>
#include <TLine.h>
#include <TColor.h>
#include <TROOT.h>
#include <TH2F.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TMathText.h>
#include <TFrame.h>
#include <TArrow.h>
#include <TGaxis.h>

// include main header located in the same directory
#include "Plotting.h"

//######################### F L A G S ###############################//

// debugging flag, set to 1 for checks
#define DEBUG 0

// yields flag, set to 1 top print data and MC yields
#define YIELDS 0

// normalised signal flag, set to 1 to add normalised signal to the plots (can be used for Higgs, SingleTop, ZPrime, SUSY)
#define NORMSIG 0

// save to pdf flag, by default plots saved as png
#define SAVEPDF 1

// save to root format flag
#define SAVEROOT 1


Plotting::Plotting(){
  lumi = 0;
}

///
Plotting::~Plotting(){
}

///
void Plotting::SetLumi(double l){
  lumi = l;
}

void Plotting::SetOption(std::string analysis){
  option = analysis;
}

void Plotting::SetInputLocation(std::string loc){
  readname = loc;
}


///
void Plotting::run(){
  
  getHistoSettings();
  
  AtlasStyle();
  
  WhichFiles();
  
  readFiles(); 
  
  makePlots();
  
  return;
}

///
void Plotting::AtlasStyle(){
  TStyle *atlasStyle = new TStyle("ATLAS","Atlas style");
  Int_t icol=0; // WHITE
  atlasStyle->SetFrameBorderMode(icol);
  atlasStyle->SetFrameFillColor(icol);
  atlasStyle->SetCanvasBorderMode(icol);
  atlasStyle->SetCanvasColor(icol);
  atlasStyle->SetPadBorderMode(icol);
  atlasStyle->SetPadColor(icol);
  atlasStyle->SetStatColor(icol);
  atlasStyle->SetPaperSize(20,26);
  atlasStyle->SetPadTopMargin(0.05);
  atlasStyle->SetPadRightMargin(0.05); 
  atlasStyle->SetPadBottomMargin(0.16);
  atlasStyle->SetPadLeftMargin(0.16); 
  atlasStyle->SetTitleXOffset(1.4);
  atlasStyle->SetTitleYOffset(1.4);
  Int_t font=42; // Helvetica
  Double_t tsize=0.05;
  atlasStyle->SetTextFont(font);
  atlasStyle->SetTextSize(tsize);
  atlasStyle->SetLabelFont(font,"x");
  atlasStyle->SetTitleFont(font,"x");
  atlasStyle->SetLabelFont(font,"y");
  atlasStyle->SetTitleFont(font,"y");
  atlasStyle->SetLabelFont(font,"z");
  atlasStyle->SetTitleFont(font,"z");
  atlasStyle->SetLabelSize(tsize,"x");
  atlasStyle->SetTitleSize(tsize,"x");
  atlasStyle->SetLabelSize(tsize,"y");
  atlasStyle->SetTitleSize(tsize,"y");
  atlasStyle->SetLabelSize(tsize,"z");
  atlasStyle->SetTitleSize(tsize,"z");
  atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
  atlasStyle->SetHistLineWidth(2.);
  atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
  atlasStyle->SetEndErrorSize(0.);
  atlasStyle->SetOptTitle(0);
  atlasStyle->SetOptStat(0);
  atlasStyle->SetOptFit(0);
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();
}

///
void Plotting::ATLASLabel(Double_t x,Double_t y) 
{
  TLatex l;
  l.SetNDC();
  l.SetTextFont(72);
  l.SetTextColor(kBlack);
  l.SetTextSize(0.05);  
  double delx = 0.13; //0.16
  l.DrawLatex(x,y,"ATLAS");
  TLatex p; 
  p.SetNDC();
  p.SetTextFont(42);
  p.SetTextColor(kBlack);
  p.SetTextSize(0.05);  
  //p.DrawLatex(x+delx,y,"Open Data");
  p.DrawLatex(x+delx,y,"Preliminary Open Data");
  //p.DrawLatex(x+delx,y,"Internal Open Data");

  return;
}

///
void Plotting::WhichFiles(){
  // read input file with the names of the samples
  std::string ifile;
  ifile = "Plotting/inputfiles/Files_HWW.txt";
 
  std::cout << "Analysis: " << option << ", reading input from: " << ifile.c_str() << " \n " << std::endl;

  ifstream input(ifile.c_str());
  std::string line;
  while(getline(input,line)){
    if (line.find("#") != line.npos )continue; // a # is a comment and not read
    std::string name, xsec, sumw, eff;
    istringstream linestream(line);
    getline(linestream, name, '|');
    getline(linestream, xsec, '|');
    getline(linestream, sumw, '|');
    getline(linestream, eff);
    if (DEBUG) cout << name << " " << xsec << " " << sumw << " " << eff << endl;
    float sumw_eff = atof(sumw.c_str()) * atof(eff.c_str());
    SF[name] = std::make_pair(atof(xsec.c_str()), sumw_eff);    
    
  }
  return;
}

///
void Plotting::readFiles(){
    
  std::cout << "Reading files from: " << readname << " \n " << std::endl;
  std::cout<<"=====processing HWWAnalysis====="<<std::endl;
  std::cout << "\n" << std::endl;

  std::map<std::string,std::pair<double,double> >::const_iterator SFiter;
  for(SFiter = SF.begin(); SFiter != SF.end(); SFiter++){
    std::string readme = readname + "/" + SFiter->first + ".root";
    if (DEBUG)  std::cout << "Reading file: " << readme << std::endl;
    TFile* file  = TFile::Open(readme.c_str(), "READ");
    
    createHistoSet(file, SFiter->first);
    
    // apply Scale Factors: scaling is done by calculating the luminosity of the sample via xsec/(sumw*red_eff) and  multiplying the target luminosity
    if(std::strstr((SFiter->first).c_str(),"data") == NULL ){
      std::vector<std::string> v_n; v_n.clear();
      std::string n = SFiter->first;
      v_n.push_back(n);
      for(unsigned int i = 0; i < v_n.size(); ++i){
        std::map<std::string,TH1F*>::const_iterator fIter = histo[v_n[i]].begin();
        std::map<std::string,TH1F*>::const_iterator lIter = histo[v_n[i]].end();
        double scf = 1;
	scf = (lumi *  SFiter->second.first) / SFiter->second.second ; 
        for(; fIter!=lIter;++fIter){
	  if (DEBUG) std::cout<<"Scaling histogram: "<< fIter->first << " by a factor of: " << scf << std::endl;
	  fIter->second->Scale(scf);

          // MC overflow
	  if(std::strstr((fIter->first).c_str(),"four_lep") == NULL )
          if( abs(fIter->second->GetBinContent(fIter->second->GetNbinsX()+1)) > 0){
            fIter->second->AddBinContent(fIter->second->GetNbinsX(), fIter->second->GetBinContent(fIter->second->GetNbinsX()+1));
          }

        }
      }
    }
    
  }
  return;
}

///
void Plotting::createHistoSet(TFile* file, std::string proc){
  
  std::vector<HistoHandler*>::iterator fIter = hset.begin();
  std::vector<HistoHandler*>::iterator lIter = hset.end();
  
  for(; fIter != lIter; ++fIter){
    std::string n;
    n  = (*fIter)->GetName();
    if (DEBUG) cout << "reading histogram: " << n << endl;
    createHistogram(file, n, proc);  
  }
  
  return;
}

///
void Plotting::createHistogram(TFile* file, std::string hname ,  std::string proc){
  
  histo[proc][hname] = (TH1F*)file->Get(hname.c_str()); 
  
  return;
}

///
void Plotting::makePlots(){
  
  TCanvas* c;
  c = new TCanvas("c","c",700,750);
  TPad* pad0; //upper
  TPad* pad1; //lower
  TPad* padX; //mask
  TPad* pad2X; //mask

  pad0 = new TPad("pad0","pad0",0,0.29,1,1,0,0,0);
  pad0->SetTickx(false);
  pad0->SetTicky(false);
  pad0->SetTopMargin(0.05);
  pad0->SetBottomMargin(0);
  pad0->SetLeftMargin(0.14);
  pad0->SetRightMargin(0.05);
  pad0->SetFrameBorderMode(0);
  pad0->SetTopMargin(0.06);

  pad1 = new TPad("pad1","pad1",0,0,1,0.29,0,0,0);
  pad1->SetTickx(false);
  pad1->SetTicky(false);
  pad1->SetTopMargin(0.0);
  pad1->SetBottomMargin(0.5);
  pad1->SetLeftMargin(0.14);
  pad1->SetRightMargin(0.05);
  pad1->SetFrameBorderMode(0);

 
  padX = new TPad("pad1","pad1",0.08, 0.27, 0.135, 0.29, 0, 0, 0);
  padX->SetTickx(false);  padX->SetTicky(false);  padX->SetTopMargin(0.0);
  padX->SetBottomMargin(0.5);  padX->SetLeftMargin(0.14);  padX->SetRightMargin(0.05);  padX->SetFrameBorderMode(0);

  pad2X = new TPad("pad1","pad1",0.08, 0.132, 0.135, 0.16, 0, 0, 0);
  pad2X->SetTickx(false);  pad2X->SetTicky(false);  pad2X->SetTopMargin(0.0);
  pad2X->SetBottomMargin(0.5);  pad2X->SetLeftMargin(0.14);  pad2X->SetRightMargin(0.05);  pad2X->SetFrameBorderMode(0);


  pad1->Draw();
  pad0->Draw();
  padX->Draw();
  if(!(option.find("HyyAnalysis") != option.npos)) 	    pad2X->Draw();

  pad0->cd();
  
  ///////////////////////////////////////////////////////////////////////
  // we create the maps of the histograms for each sample

  // data
  std::map<std::string,TH1F*> data; 
  
  //Higgs to WW
  std::map<std::string,TH1F*> ggH125_WW2lep;
  std::map<std::string,TH1F*> VBFH125_WW2lep;
    
  // default top pair production, only single + dilepton decays of ttbar
  std::map<std::string,TH1F*> ttbar_lep;  

  // Z boson Powheg samples (one sample per decay flavour) = not supposed to describe well large jet multiplicity regions
  std::map<std::string,TH1F*> Zee;
  std::map<std::string,TH1F*> Zmumu;
  std::map<std::string,TH1F*> Ztautau;
    
  // Diboson Sherpa (WW, WZ, ZZ) 
  std::map<std::string,TH1F*>  WlvZqq; 
  std::map<std::string,TH1F*>  WplvWmqq; 
  std::map<std::string,TH1F*>  WpqqWmlv; 
  std::map<std::string,TH1F*>  ZqqZll; 
  std::map<std::string,TH1F*>  WqqZll; 
  std::map<std::string,TH1F*>  llll;
  std::map<std::string,TH1F*>  lllv;
  std::map<std::string,TH1F*>  llvv;
  std::map<std::string,TH1F*>  lvvv;
  
  // W+jets Powheg samples (one sample per charge and decay flavour) = not supposed to describe well large jet multiplicity regions
  std::map<std::string,TH1F*> Wplusenu;
  std::map<std::string,TH1F*> Wplusmunu;
  std::map<std::string,TH1F*> Wplustaunu;
  std::map<std::string,TH1F*> Wminusenu;
  std::map<std::string,TH1F*> Wminusmunu;
  std::map<std::string,TH1F*> Wminustaunu;
  
  // single top (t, s, tW-channels)
  std::map<std::string,TH1F*> single_top_tchan;
  std::map<std::string,TH1F*> single_antitop_tchan;
  std::map<std::string,TH1F*> single_top_wtchan;
  std::map<std::string,TH1F*> single_antitop_wtchan;
  std::map<std::string,TH1F*> single_top_schan;
  std::map<std::string,TH1F*> single_antitop_schan;
  
  ///////////////////////////////////////////////////////////////////////
  // Actual reading of the input files
  // The names must be the same as in Files_***.txt 

  // read data
  data = histo["data"];

  // read H->WW (very minor WH and ZH contributions are neglected)
  if(option.find("HWWAnalysis") != option.npos){
    ggH125_WW2lep = histo["ggH125_WW2lep"];
    VBFH125_WW2lep = histo["VBFH125_WW2lep"];
  }

  // reading ttbar 
  ttbar_lep = histo["ttbar_lep"];
  
  // reading Powheg Z+jets samples, used in HWW analyses 
  if(option.find("HWWAnalysis") != option.npos)
    {
      Zee = histo["Zee"];
      Zmumu = histo["Zmumu"];
      Ztautau = histo["Ztautau"];
    }
  
  // reading Powheg W+jets samples, used in HWW 
  if( option.find("HWWAnalysis") != option.npos ) 
    {
      Wplusenu = histo["Wplusenu"];
      Wplusmunu= histo["Wplusmunu"];
      Wplustaunu= histo["Wplustaunu"];  
      Wminusenu= histo["Wminusenu"];
      Wminusmunu= histo["Wminusmunu"];
      Wminustaunu= histo["Wminustaunu"];
    }
  
  // reading diboson samples, used in all analyses
  WlvZqq= histo["WlvZqq"];
  WplvWmqq= histo["WplvWmqq"];
  WpqqWmlv= histo["WpqqWmlv"];
  ZqqZll= histo["ZqqZll"];
  WqqZll= histo["WqqZll"];
  llll= histo["llll"];
  lllv= histo["lllv"];
  llvv= histo["llvv"];
  lvvv= histo["lvvv"];
  
  // reading single top samples, used in all analyses
  single_top_tchan= histo["single_top_tchan"];
  single_antitop_tchan= histo["single_antitop_tchan"];
  single_top_wtchan= histo["single_top_wtchan"];
  single_antitop_wtchan= histo["single_antitop_wtchan"];
  single_top_schan= histo["single_top_schan"];
  single_antitop_schan= histo["single_antitop_schan"];  
  

  ///////////////////////////////////////////////////////////////////////
  // Finally, the plotting part begins here
  
  std::map<std::string,TH1F*>::const_iterator fIter;
  std::map<std::string,TH1F*>::const_iterator lIter;
  fIter = data.begin(); lIter = data.end();

  // iterator over the names of the histograms per file
  for(; fIter != lIter; ++fIter){
    
    std::cout<<"Plotting histogram: "<< fIter->first << std::endl;
    
    // data style
    fIter->second->SetMarkerStyle(20);
    fIter->second->SetMarkerColor(kBlack);
    fIter->second->SetMarkerSize(1.2);
    fIter->second->SetLineWidth(2);
    fIter->second->SetMinimum(0.1);
    gStyle->SetEndErrorSize(1.); 
    TGaxis::SetMaxDigits(4); // maximum digits in Y axis title
    
    fIter->second->GetYaxis()->SetTitleOffset(1.2);
    if(!(option.find("HyyAnalysis") != option.npos))  fIter->second->Draw("E1");

    // create histograms and merge several MCs into them
    // general
    TH1F* diboson = new TH1F();
    TH1F* W = new TH1F();
    TH1F* Z = new TH1F();
    TH1F* ttbar = new TH1F();
    TH1F* stop = new TH1F();

    //special
    TH1F* V = new TH1F();
    TH1F* W_Z = new TH1F();
    TH1F* Z_Z = new TH1F();
    TH1F* WWZ = new TH1F();
    TH1F* VV = new TH1F();
    TH1F* top = new TH1F();
    TH1F* topV = new TH1F();
    TH1F* Higgs = new TH1F();
    TH1F* Z_tautau = new TH1F();
    TH1F* stop_tq = new TH1F();
    TH1F* stop_tWtb = new TH1F();
    TH1F* ZVV = new TH1F();
    TH1F* ZPrime = new TH1F();
    
    // merge for HWW _Analysis
    
    Higgs = (TH1F*)ggH125_WW2lep[fIter->first]->Clone();
    Higgs->Add(VBFH125_WW2lep[fIter->first]);
    Higgs->SetFillColor(kRed);
    Higgs->SetLineWidth(0);

    ttbar = (TH1F*)ttbar_lep[fIter->first]->Clone();
    ttbar->SetFillColor(kOrange-3);
    ttbar->SetLineWidth(0);

    diboson = (TH1F*)WlvZqq[fIter->first]->Clone();
    diboson->Add(WplvWmqq[fIter->first]);
    diboson->Add(WpqqWmlv[fIter->first]);
    diboson->Add(ZqqZll[fIter->first]);
    diboson->Add(WqqZll[fIter->first]);
    diboson->Add(llll[fIter->first]);
    diboson->Add(lllv[fIter->first]);           
    diboson->Add(llvv[fIter->first]);
    diboson->Add(lvvv[fIter->first]);
    diboson->SetFillColor(kBlue-6);
    diboson->SetLineWidth(0);
    diboson->Scale(1.3); //normalisation scaling, from WW control region we need a factor of 1.3, underestimation of WZ cross section requires a normalisation factor of 1.15-1.2, also contributions with misidentified leptons are not estimated nor added => a total of 1.3 is taken

    V = (TH1F*)Wplusenu[fIter->first]->Clone();
    V->Add(Wplusmunu[fIter->first]);
    V->Add(Wplustaunu[fIter->first]);
    V->Add(Wminusenu[fIter->first]);
    V->Add(Wminusmunu[fIter->first]);
    V->Add(Wminustaunu[fIter->first]);
    V->Add(Ztautau[fIter->first]);
    V->Add(Zee[fIter->first]);
    V->Add(Zmumu[fIter->first]);
    V->SetFillColor(kGreen-3);
    V->SetLineWidth(0);

    stop = (TH1F*)single_top_tchan[fIter->first]->Clone();
    stop->Add(single_antitop_tchan[fIter->first]);
    stop->Add(single_top_wtchan[fIter->first]);
    stop->Add(single_antitop_wtchan[fIter->first]);
    stop->Add(single_top_schan[fIter->first]);
    stop->Add(single_antitop_schan[fIter->first]);
    stop->SetFillColor(kAzure+8);
    stop->SetLineWidth(0);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    
    // main stack of MCs
    THStack* stack = new THStack();
   
    // statistical error histogram
    TH1F* histstack = new TH1F();
      
    // The order of the stack defines which samples will appear on top of each other
    stack->Add(stop);
    stack->Add(ttbar);
    stack->Add(V);
    stack->Add(diboson);
    stack->Add(Higgs);

    histstack = (TH1F*)ttbar->Clone();
    histstack->Add(diboson);
    histstack->Add(V);
    histstack->Add(stop);
    histstack->Add(Higgs);
    

    // data overflow
    if(std::strstr((fIter->first).c_str(),"four_lep") == NULL ){
      if( abs(fIter->second->GetBinContent(fIter->second->GetNbinsX()+1)) > 0){
     fIter->second->AddBinContent(fIter->second->GetNbinsX(), fIter->second->GetBinContent(fIter->second->GetNbinsX()+1));
      }
    }
    /////////////////////////////////////////////////////////////////////////////
    // BEGIN PLOTTING //


    histstack->SetFillStyle(3454);
    histstack->SetFillColor(kBlue+2);
    histstack->SetLineColor(kBlack);
    histstack->SetLineWidth(2);
    histstack->SetMarkerSize(0);
    histstack->SetLineColor(kWhite);
    
    // obtain the statistical uncertainty
    float err;
    int nbin = histstack->GetNbinsX();
    for(int i_bin=0;i_bin<=nbin;i_bin++){
      err = histstack->GetBinError(i_bin);
      histstack->SetBinError(i_bin, err ); 
    }
      
    // calculate normalized signals
    TH1F* Higgs_normsig = new TH1F();
    Higgs_normsig = (TH1F*)Higgs->Clone();
    Higgs_normsig->Scale(histstack->Integral()/Higgs_normsig->Integral());
    Higgs_normsig->SetLineColor(kRed);
    Higgs_normsig->SetFillStyle(0);
    Higgs_normsig->SetLineStyle(2);
    Higgs_normsig->SetFillColor(2);
    Higgs_normsig->SetLineWidth(2);
    
    // set Yaxis maximum
    float yMaxScale = 2.;
    fIter->second->SetMaximum(yMaxScale*TMath::Max( TMath::Max(fIter->second->GetMaximum(),histstack->GetMaximum()), Higgs_normsig->GetMaximum() ) );
    
    // latex options 
    TLatex l;
    l.SetNDC();
    l.SetTextColor(kBlack);
    l.SetTextFont(42);
    l.SetTextSize(0.04);
    l.DrawLatex(0.18,0.71,"H #rightarrow WW* #rightarrow e#nu #mu#nu, N_{jet} #leq 1");

    TLatex l2;
    l2.SetNDC();
    l2.SetTextSize(0.04);  
    l2.SetTextColor(kBlack);
    l2.DrawLatex(0.18,0.79, Form("#sqrt{s} = 13 TeV, 10 fb^{-1}")); 
    
    //create legend
    TLegend* leg;
    leg  = new TLegend();
    leg  = new TLegend(0.70,0.50,0.93,0.925);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextAlign(32);
    leg->SetTextFont(42);
    leg->SetTextSize(0.05);
    leg->SetMargin(0.22);
    leg->SetTextAlign(32);
    
    // fill legend depending on the analysis, the order reflects the stack order
    // ------------------------------------------------------- //   
    leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
    leg-> AddEntry(Higgs , "Higgs", "f");
    leg-> AddEntry(diboson , "Diboson", "f");
    leg-> AddEntry(V,  "V+jets", "f");
    leg-> AddEntry(ttbar, "t#bar{t}", "f");
    leg-> AddEntry(stop, "Single top", "f");
    leg-> AddEntry(histstack,"Stat. unc.","f");
    if(NORMSIG) if(fIter->first.find("histI") != option.npos) leg-> AddEntry(Higgs_normsig, "Higgs_{norm}" ,"l");
      
    if(YIELDS){
	cout << "Number of events:" << "Data: " << data[fIter->first]->Integral() << 
	  ",  Higgs: " << Higgs->Integral()  << 
	  ",  Diboson: " << diboson->Integral()  <<
	  ",  V+jets: " << V->Integral()  <<
	  ",  ttbar: " << ttbar ->Integral()  <<
	  ",  stop: " <<  stop->Integral()  <<
	  ",  Total pred.: "<< diboson->Integral() + V->Integral() + ttbar ->Integral() + stop->Integral() << 
	  endl;
      }
    

    // draw everything 
    stack->Draw("HISTsame");
    histstack->Draw("e2same");
    fIter->second->Draw("sameE1");
    
    // draw the normalised signal in the plots
    if(NORMSIG){
      if(option.find("HWWAnalysis")          != option.npos){if(fIter->first.find("histI") != option.npos)Higgs_normsig->Draw("HISTsame");}
    }

    leg->Draw("same");

    ATLASLabel(0.18, 0.87);
    

    ////////////////////////////////////////////////////////////////////////////////
    // lower pad contains the ratio of data to MC
    // for Hyy, it contains the rest of data and fit
    pad1->cd();
    pad1->GetFrame()->SetY1(2);
    pad1->Draw();

    // create the ratio plot  
    TH1F *h_ratio = (TH1F*)data[fIter->first]->Clone("h_ratio");

    if(! (option.find("HyyAnalysis") != option.npos) ){
      h_ratio->Divide((TH1F*)histstack->Clone());
      h_ratio->GetYaxis()->SetTitle("Data / Pred   ");
//      h_ratio->GetYaxis()->SetTitle("Data / Pred      ");
    }
      
    // add a line in 1
    TLine *hline;
    hline = new TLine(h_ratio->GetXaxis()->GetXmin(),1,h_ratio->GetXaxis()->GetXmax(),1);
    hline->SetLineColor(kGray+2);
    hline->SetLineWidth(2);
    hline->SetLineStyle(1);

    gStyle->SetEndErrorSize(1.);
    h_ratio->GetYaxis()->CenterTitle();
    h_ratio->GetYaxis()->SetNdivisions(504,false);

    h_ratio->Draw("0E1");
    hline->Draw();

    // cosmetics
    h_ratio->SetMinimum(0);
    h_ratio->SetMaximum(2);
    if(option.find("HyyAnalysis") != option.npos){
        if(fIter->first.find("_cat_") != option.npos){ h_ratio->SetMinimum(-30);      h_ratio->SetMaximum(60); }
	else{    h_ratio->SetMinimum(-125);      h_ratio->SetMaximum(250); }
    }

    h_ratio->GetXaxis()->SetTitle(  fIter->second->GetXaxis()->GetTitle()  );
    h_ratio->GetXaxis()->SetTitleSize(0.15);
    h_ratio->GetXaxis()->SetLabelSize(0.13);
    h_ratio->GetXaxis()->SetTitleOffset(1.2);
    h_ratio->GetYaxis()->SetTitleSize(0.12);
    h_ratio->GetYaxis()->SetTitleOffset(0.45);
    h_ratio->GetYaxis()->SetLabelSize(0.10);
    h_ratio->GetYaxis()->SetLabelOffset(0.01);
    h_ratio->GetXaxis()->SetLabelOffset(0.035);


    data[fIter->first]->GetXaxis()->SetLabelSize(0);
    gPad->RedrawAxis();
    pad1->cd();
    if( ! (option.find("HyyAnalysis") != option.npos)) pad1->cd()->SetGridy();

    h_ratio->Draw("SAME0E1");
    h_ratio->Draw("SAMEAXIS");
    h_ratio->GetYaxis()->Draw();
    h_ratio->Draw("SAME0E1");

    pad0->cd();
    TAxis * Ay1 = NULL;
    Ay1 = fIter->second->GetXaxis();
    Ay1->SetLabelSize(0);
    Ay1->SetTitleSize(0);

    ////////////////////////////////////////////////////////
    gPad->RedrawAxis();
 
    // printing the canvas to a png (pdf...) file    
    PrintCanvas(c,fIter->first);
    
  }
  
  return;
}

///
void Plotting::PrintCanvas(TCanvas* c1, string title){
  
  string outFolder="Plotting/histograms";
  std::string tpng = outFolder+"/"+title+".png";
  c1->SaveAs(tpng.c_str());
 
  if (SAVEPDF)
   { 
     std::string tpdf = outFolder+"/"+title+".pdf";
     c1->SaveAs(tpdf.c_str());
   }

  if (SAVEROOT)
   { 
     std::string troot = outFolder+"/"+title+".root";
     c1->SaveAs(troot.c_str());
   }

  return;
}

///
void Plotting::getHistoSettings(){

  // we check the naming of the 12 analyses
  if( option.find("HWWAnalysis") != option.npos) cout << "Analysis option found, proceeding..." << endl;
  else { cout << "Analysis option not found! \n usage: [HWWAnalysis]  [ location of OutputDir_AnalysisName ] \n " << endl; exit(1);}

 
  // save names of the histograms for later  
  hset.clear();
  
  // read in configuration file
  std::string ifile;

  ifile = "Plotting/list_histos/HistoList_HWWAnalysis.txt";
  
  std::cout << "Reading list of histograms from: " << ifile.c_str() << " \n " << std::endl;

  ifstream input(ifile.c_str());
  std::string line;
  while(getline(input,line)){
    if (line.find("#") != line.npos )continue; // a # is a comment and not read
    std::string n;
    istringstream linestream(line);
    getline(linestream, n, '\n');
    HistoHandler* h = new HistoHandler(n);
    hset.push_back(h); 
  }
  return;
}

///
HistoHandler::HistoHandler(){
}

///
HistoHandler:: HistoHandler(std::string name){
  _name = name;
}

///
HistoHandler::~HistoHandler(){
}

///
std::string HistoHandler::GetName(){
  return _name;
}
///////////////////////////////////////////////////////
