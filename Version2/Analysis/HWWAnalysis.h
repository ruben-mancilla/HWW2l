///////////////////////////////////////////////////////////////////////////////
#define arraysize(x) (sizeof(x) / sizeof((x)[0]))
/////////////////-------------------------------------------///////////////////
#include <TROOT.h>
#include <TChain.h>
#include "TFile.h"
#include "TString.h"
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

class HWWAnalysis{
public :
    
////////////// TTreeReader and TChain statement///////////////////////////////
///-----------------------------------------------------------------------///
    TChain *fchain = new TChain("mini"); //!pointer to the analyzed TChain
    TTreeReader fReader; //!the tree reader

////////////////////// Readers to access the data///////////////////////////
    TTreeReaderValue<Int_t> runNumber = {fReader, "runNumber"};
    TTreeReaderValue<Int_t> eventNumber = {fReader, "eventNumber"};
    TTreeReaderValue<Int_t> channelNumber = {fReader, "channelNumber"};
    TTreeReaderValue<Float_t> mcWeight = {fReader, "mcWeight"};
    TTreeReaderValue<Float_t> scaleFactor_PILEUP = {fReader, "scaleFactor_PILEUP"};
    TTreeReaderValue<Float_t> scaleFactor_ELE = {fReader, "scaleFactor_ELE"};
    TTreeReaderValue<Float_t> scaleFactor_MUON = {fReader, "scaleFactor_MUON"};
    TTreeReaderValue<Float_t> scaleFactor_PHOTON = {fReader, "scaleFactor_PHOTON"};
    TTreeReaderValue<Float_t> scaleFactor_TAU = {fReader, "scaleFactor_TAU"};
    TTreeReaderValue<Float_t> scaleFactor_BTAG = {fReader, "scaleFactor_BTAG"};
    TTreeReaderValue<Float_t> scaleFactor_LepTRIGGER = {fReader, "scaleFactor_LepTRIGGER"};
    TTreeReaderValue<Float_t> scaleFactor_PhotonTRIGGER = {fReader, "scaleFactor_PhotonTRIGGER"};
    TTreeReaderValue<Bool_t> trigE = {fReader, "trigE"};
    TTreeReaderValue<Bool_t> trigM = {fReader, "trigM"};
    TTreeReaderValue<Bool_t> trigP = {fReader, "trigP"};
    TTreeReaderValue<UInt_t> lep_n = {fReader, "lep_n"};
    TTreeReaderValue<vector<bool>> lep_truthMatched = {fReader, "lep_truthMatched"};
    TTreeReaderValue<vector<bool>> lep_trigMatched = {fReader, "lep_trigMatched"};
    TTreeReaderArray<float> lep_pt = {fReader, "lep_pt"};
    TTreeReaderArray<float> lep_eta = {fReader, "lep_eta"};
    TTreeReaderArray<float> lep_phi = {fReader, "lep_phi"};
    TTreeReaderArray<float> lep_E = {fReader, "lep_E"};
    TTreeReaderArray<float> lep_z0 = {fReader, "lep_z0"};
    TTreeReaderArray<int> lep_charge = {fReader, "lep_charge"};
    TTreeReaderArray<unsigned int> lep_type = {fReader, "lep_type"};
    TTreeReaderValue<vector<bool>> lep_isTightID = {fReader, "lep_isTightID"};
    TTreeReaderArray<float> lep_ptcone30 = {fReader, "lep_ptcone30"};
    TTreeReaderArray<float> lep_etcone20 = {fReader, "lep_etcone20"};
    TTreeReaderArray<float> lep_trackd0pvunbiased = {fReader, "lep_trackd0pvunbiased"};
    TTreeReaderArray<float> lep_tracksigd0pvunbiased = {fReader, "lep_tracksigd0pvunbiased"};
    TTreeReaderValue<Float_t> met_et = {fReader, "met_et"};
    TTreeReaderValue<Float_t> met_phi = {fReader, "met_phi"};
    TTreeReaderValue<UInt_t> jet_n = {fReader, "jet_n"};
    TTreeReaderArray<float> jet_pt = {fReader, "jet_pt"};
    TTreeReaderArray<float> jet_eta = {fReader, "jet_eta"};
    TTreeReaderArray<float> jet_phi = {fReader, "jet_phi"};
    TTreeReaderArray<float> jet_E = {fReader, "jet_E"};
    TTreeReaderArray<float> jet_jvt = {fReader, "jet_jvt"};
    TTreeReaderArray<int> jet_trueflav = {fReader, "jet_trueflav"};
    TTreeReaderValue<vector<bool>> jet_truthMatched = {fReader, "jet_truthMatched"};
    TTreeReaderArray<float> jet_MV2c10 = {fReader, "jet_MV2c10"};
   
    // Global variables histograms
    TH1F *hist_etmiss      = 0;
    TH1F *hist_mLL         = 0; 
    TH1F *hist_ptLL        = 0;  
    TH1F *hist_dPhi_LL      = 0;
    TH1F *hist_mt          = 0;
    TH1F *hist_dPhiLLmet      = 0;

    TH1F *histI_etmiss      = 0;
    TH1F *histI_mLL         = 0;
    TH1F *histI_ptLL        = 0;
    TH1F *histI_dPhi_LL      = 0;
    TH1F *histI_mt          = 0;
    TH1F *histI_dPhiLLmet      = 0;

    // Leading Lepton histograms
    TH1F *hist_leadleptpt   = 0;
    TH1F *hist_leadlepteta  = 0;
    TH1F *hist_leadleptE    = 0;
    TH1F *hist_leadleptphi  = 0;
    TH1F *hist_leadleptch   = 0;
    TH1F *hist_leadleptID   = 0;
    TH1F *hist_leadlept_ptc  = 0;
    TH1F *hist_leadleptetc  = 0;
    TH1F *hist_leadlepz0    = 0;
    TH1F *hist_leadlepd0    = 0;

    // Subleading Lepton histograms
    TH1F *hist_subleadleptpt  = 0;
    TH1F *hist_subleadlepteta = 0;
    TH1F *hist_subleadleptE   = 0;
    TH1F *hist_subleadleptphi = 0;
    TH1F *hist_subleadleptch  = 0;
    TH1F *hist_subleadleptID  = 0;
    TH1F *hist_subleadlept_ptc = 0;
    TH1F *hist_subleadleptetc = 0;
    TH1F *hist_subleadlepz0   = 0;
    TH1F *hist_subleadlepd0   = 0;

    // Jet variables histograms
    TH1F *hist_n_jets       = 0;
    TH1F *hist_n_bjets       = 0;

    TH1F *histI_n_jets       = 0;
    TH1F *histI_n_bjets       = 0;

    TH1F *hist_leadjet_pt       = 0;
    TH1F *hist_leadjet_eta      = 0;
    
    HWWAnalysis(TTree * /*tree*/ =0) { }  //builder
    virtual ~HWWAnalysis() {}             //destroyer
    virtual void    Init(TChain *tree);
    virtual Bool_t  Process(TChain* tree, TString s);
    virtual void    Terminate(TString s);
    virtual void    FillHistogramsGlobal( double m, float w , TString s);
    virtual void    FillHistogramsLeadlept( double m, float w , TString s);
    virtual void    FillHistogramsSubleadlept( double m, float w , TString s);
    virtual void    define_histograms();
    virtual void    WriteHistograms();
    virtual void    reset_histograms();   
    
}; 
    
void HWWAnalysis::Init(TChain *tree)
{
   // Set (or update) the which tree to reader from
   fReader.SetTree(tree);
}

void HWWAnalysis::Terminate(TString m){
   
    TString filename_option = m;
    std::cout << "Writting with name option: " << filename_option << std::endl;
    TString output_name="Analysis/Output_HWWAnalysis/"+filename_option+".root";
    const char* filename = output_name;

    TFile physicsoutput(filename,"recreate");
    WriteHistograms();
    physicsoutput.Close();
}

bool fileExists( std::string const& name )
{
  struct stat buffer;   
  return (stat(name.c_str(), &buffer) == 0); 
}