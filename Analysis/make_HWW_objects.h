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
   TTreeReaderValue<Float_t> scaleFactor_LepTRIGGER = {fReader, "scaleFactor_LepTRIGGER"};
   TTreeReaderValue<Bool_t> trigE = {fReader, "trigE"};
   TTreeReaderValue<Bool_t> trigM = {fReader, "trigM"};
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
   TTreeReaderArray<float> jet_MV2c10 = {fReader, "jet_MV2c10"};
   
void Init(TTree *tree)
{
   // Set (or update) the which tree to reader from
   fReader.SetTree(tree);
}

void Terminate(string s){
   
    string filename_option = s;
    std::cout << "Writting with name option: " << filename_option << std::endl;
    string output_name="Analysis/Output_HWWAnalysis/"+filename_option+".root";
    const char* filename = output_name.c_str();

    TFile physicsoutput(filename,"recreate");
    WriteHistograms();
    physicsoutput.Close();
}

bool fileExists( std::string const& name )
{
  struct stat buffer;   
  return (stat(name.c_str(), &buffer) == 0); 
}
   