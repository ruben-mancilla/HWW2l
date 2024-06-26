//////////////////////////////////////////////////////////////////////////////////////////
// We create a Tchain to be used in the physical analysis of H-> WW-> lvlv//
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TProof.h"
#include "TString.h"

TChain *main_HWWAnalysis(int proof, TString s)
{
  // path to your local directory *or* URL, please change the default one!
  /* Local path example */
  TString path = "/home/rufisica/Documentos/Dataset_Thesis/";

  /* The URL to the ATLAS Open Data website repository */
  //TString path = "http://www.universidad.ch/ATLAS/outreach/open-data-2020/2lep/";

  //***************************************************************************************************//
  // adding chains of all MC and data samples
  //***************************************************************************************************//
  
  TChain *f = new TChain("mini");
    
  if (proof == 1)  TProof::Open("");
    
 /////////////////Data /////////////////
  
  if (s.Contains("dataA")){
    TChain *chain_data = new TChain("mini");
    chain_data->AddFile(path+"Data/data_A.2lep.root");
    if (proof == 1)  chain_data->SetProof();
    f = chain_data;
  }  
  
  if (s.Contains("dataB")){
    TChain *chain_data = new TChain("mini");
    chain_data->AddFile(path+"Data/data_B.2lep.root");
    if (proof == 1)  chain_data->SetProof();
    f = chain_data;
  }
    
  if (s.Contains("dataC")){
    TChain *chain_data = new TChain("mini");
    chain_data->AddFile(path+"Data/data_C.2lep.root");
    if (proof == 1)  chain_data->SetProof();
    f = chain_data;
  }
    
  if (s.Contains("dataD")){
    TChain *chain_data = new TChain("mini");
    chain_data->AddFile(path+"Data/data_D.2lep.root");
    if (proof == 1)  chain_data->SetProof();
    f = chain_data;
  }
  
  //////////////////////  MC samples
    
    // diboson
  if (s.Contains("ZqqZll")) {
    TChain *chain_ZqqZll = new TChain("mini");
    chain_ZqqZll->AddFile(path+"MC/mc_363356.ZqqZll.2lep.root");
    if (proof == 1)  chain_ZqqZll->SetProof();
    f = chain_ZqqZll;
  }
    
  if (s.Contains("WqqZll")) {
    TChain *chain_WqqZll = new TChain("mini");
    chain_WqqZll->AddFile(path+"MC/mc_363358.WqqZll.2lep.root");
    if (proof == 1)  chain_WqqZll->SetProof();
    f = chain_WqqZll;
  }
    
  if (s.Contains("WpqqWmlv")) {    
    TChain *chain_WpqqWmlv = new TChain("mini");
    chain_WpqqWmlv->AddFile(path+"MC/mc_363359.WpqqWmlv.2lep.root");
    if (proof == 1)  chain_WpqqWmlv->SetProof();
    f = chain_WpqqWmlv;
  }
    
  if (s.Contains("WplvWmqq")) {
    TChain *chain_WplvWmqq = new TChain("mini");
    chain_WplvWmqq->AddFile(path+"MC/mc_363360.WplvWmqq.2lep.root");
    if (proof == 1)  chain_WplvWmqq->SetProof();
    f = chain_WplvWmqq;
  }
    
  if (s.Contains("WlvZqq")) {  
    TChain *chain_WlvZqq = new TChain("mini");
    chain_WlvZqq->AddFile(path+"MC/mc_363489.WlvZqq.2lep.root");
    if (proof == 1)  chain_WlvZqq->SetProof();
    f = chain_WlvZqq;
  }
 
  if (s.Contains("llll")) {
    TChain *chain_llll = new TChain("mini");
    chain_llll->AddFile(path+"MC/mc_363490.llll.2lep.root");
    if (proof == 1)  chain_llll->SetProof();
    f = chain_llll;
  }
    
  if (s.Contains("lllv")) {   
    TChain *chain_lllv = new TChain("mini");
    chain_lllv->AddFile(path+"MC/mc_363491.lllv.2lep.root");
    if (proof == 1)  chain_lllv->SetProof();
    f = chain_lllv;
  }
    
  if (s.Contains("llvv")) {
    TChain *chain_llvv = new TChain("mini");
    chain_llvv->AddFile(path+"MC/mc_363492.llvv.2lep.root");
    if (proof == 1)  chain_llvv->SetProof();
    f = chain_llvv;
  }
    
  if (s.Contains("lvvv")) {   
    TChain *chain_lvvv = new TChain("mini");
    chain_lvvv->AddFile(path+"MC/mc_363493.lvvv.2lep.root");
    if (proof == 1)  chain_lvvv->SetProof();
    f = chain_lvvv;
  }
    
    //single top
  if (s.Contains("single_top_tchan")) {
    TChain *chain_single_top_tchan = new TChain("mini");
    chain_single_top_tchan->AddFile(path+"MC/mc_410011.single_top_tchan.2lep.root");
    if (proof == 1)  chain_single_top_tchan->SetProof();
    f = chain_single_top_tchan;
  }
    
  if (s.Contains("single_antitop_tchan")) {
    TChain *chain_single_antitop_tchan = new TChain("mini");
    chain_single_antitop_tchan->AddFile(path+"MC/mc_410012.single_antitop_tchan.2lep.root");
    if (proof == 1)  chain_single_antitop_tchan->SetProof();
    f = chain_single_antitop_tchan;
  }
    
  if (s.Contains("single_top_schan")) { 
    TChain *chain_single_top_schan = new TChain("mini");
    chain_single_top_schan->AddFile(path+"MC/mc_410025.single_top_schan.2lep.root");
    if (proof == 1)  chain_single_top_schan->SetProof();
    f = chain_single_top_schan;
  }
    
  if (s.Contains("single_antitop_schan")) {  
    TChain *chain_single_antitop_schan = new TChain("mini");
    chain_single_antitop_schan->AddFile(path+"MC/mc_410026.single_antitop_schan.2lep.root");
    if (proof == 1)  chain_single_antitop_schan->SetProof();
    f = chain_single_antitop_schan;
  }
    
  if (s.Contains("single_top_wtchan")) { 
    TChain *chain_single_top_wtchan = new TChain("mini");
    chain_single_top_wtchan->AddFile(path+"MC/mc_410013.single_top_wtchan.2lep.root");
    if (proof == 1)  chain_single_top_wtchan->SetProof();
    f = chain_single_top_wtchan;
  }
     
  if (s.Contains("single_antitop_wtchan")) {   
    TChain *chain_single_antitop_wtchan = new TChain("mini");
    chain_single_antitop_wtchan->AddFile(path+"MC/mc_410014.single_antitop_wtchan.2lep.root");
    if (proof == 1)  chain_single_antitop_wtchan->SetProof();
    f = chain_single_antitop_wtchan;
  }


    // Z+jets inclusive
  if (s.Contains("Zee")) {
    TChain *chain_Zee = new TChain("mini");
    chain_Zee->AddFile(path+"MC/mc_361106.Zee.2lep.root");
    if (proof == 1)  chain_Zee->SetProof();
    f = chain_Zee;
  }

  if (s.Contains("Zmumu")) {
    TChain *chain_Zmumu = new TChain("mini");
    chain_Zmumu->AddFile(path+"MC/mc_361107.Zmumu.2lep.root");
    if (proof == 1)  chain_Zmumu->SetProof();
    f = chain_Zmumu;
  }


  if (s.Contains("Ztautau")) {
    TChain *chain_Ztautau = new TChain("mini");
    chain_Ztautau->AddFile(path+"MC/mc_361108.Ztautau.2lep.root");
    if (proof == 1)  chain_Ztautau->SetProof();
    f = chain_Ztautau;
  }

    //ttbar
  if (s.Contains("ttbar_lep")) {
    TChain *chain_ttbar_lep = new TChain("mini");
    chain_ttbar_lep->AddFile(path+"MC/mc_410000.ttbar_lep.2lep.root");
    if (proof == 1)  chain_ttbar_lep->SetProof();
    f = chain_ttbar_lep;
  }
    
  // W+jets inclusive
  if (s.Contains("Wplusenu")) {
    TChain *chain_Wplusenu = new TChain("mini");
    chain_Wplusenu->AddFile(path+"MC/mc_361100.Wplusenu.2lep.root");
    if (proof == 1)  chain_Wplusenu->SetProof();
    f = chain_Wplusenu;
  }
    
  if (s.Contains("Wplusmunu")) {
    TChain *chain_Wplusmunu = new TChain("mini");
    chain_Wplusmunu->AddFile(path+"MC/mc_361101.Wplusmunu.2lep.root");
    if (proof == 1)  chain_Wplusmunu->SetProof();
    f = chain_Wplusmunu;
  }

  if (s.Contains("Wplustaunu")) {
    TChain *chain_Wplustaunu = new TChain("mini");
    chain_Wplustaunu->AddFile(path+"MC/mc_361102.Wplustaunu.2lep.root");
    if (proof == 1)  chain_Wplustaunu->SetProof();
    f = chain_Wplustaunu;
  }

  if (s.Contains("Wminusenu")) {
    TChain *chain_Wminusenu = new TChain("mini");
    chain_Wminusenu->AddFile(path+"MC/mc_361103.Wminusenu.2lep.root");
    if (proof == 1)  chain_Wminusenu->SetProof();
    f = chain_Wminusenu;
  }

  if (s.Contains("Wminusmunu")) {
    TChain *chain_Wminusmunu = new TChain("mini");
    chain_Wminusmunu->AddFile(path+"MC/mc_361104.Wminusmunu.2lep.root");
    if (proof == 1)  chain_Wminusmunu->SetProof();
    f = chain_Wminusmunu;
  }

  if (s.Contains("Wminustaunu")) {
    TChain *chain_Wminustaunu = new TChain("mini");
    chain_Wminustaunu->AddFile(path+"MC/mc_361105.Wminustaunu.2lep.root");
    if (proof == 1)  chain_Wminustaunu->SetProof();
    f = chain_Wminustaunu;
  }

  // ggH
  if (s.Contains("ggH125_WW2lep")) {
    TChain *chain_ggH125_WW = new TChain("mini");
    chain_ggH125_WW->AddFile(path+"MC/mc_345324.ggH125_WW2lep.2lep.root");
    if (proof == 1)  chain_ggH125_WW->SetProof();
    f = chain_ggH125_WW;
  }

  // VBF
  if (s.Contains("VBFH125_WW2lep")) {
    TChain *chain_VBFH125_WW = new TChain("mini");
    chain_VBFH125_WW->AddFile(path+"MC/mc_345323.VBFH125_WW2lep.2lep.root");
    if (proof == 1)  chain_VBFH125_WW->SetProof();
    f = chain_VBFH125_WW;
  } 
  
  return f;
    
}