////////////////////////////////////////////////////////////////////////////////////////////////
// We are going to create a function that contains the String with the names of the samples 
//to analyze
//-----------------------------------------------------------------------------------------------
#include "TROOT.h"
#include <vector>
#include <string>

void array_samples(vector<string> &f, int option){
    
    if (option==0){
        string a[]={"dataA","dataB","dataC","dataD","ZqqZll","WqqZll","WpqqWmlv","WplvWmqq",
                    "WlvZqq","llll","lllv","llvv","lvvv","single_top_tchan","single_antitop_tchan",
                    "single_top_schan","single_antitop_schan","single_top_wtchan","single_antitop_wtchan",
                    "Zee","Zmumu","Ztautau","ttbar_lep","Wplusenu","Wplusmunu","Wplustaunu","Wminusenu",
                    "Wminusmunu","Wminustaunu","ggH125_WW2lep","VBFH125_WW2lep"};
        int array_size=sizeof(a)/sizeof(a[0]);
        for (int i=0;i<array_size;i++){
            f.push_back(a[i]);
        }
    }
    
    if (option==1){
        string a[]={"dataA","dataB","dataC","dataD"};
        int array_size=sizeof(a)/sizeof(a[0]);
        for (int i=0;i<array_size;i++){
            f.push_back(a[i]);
        }
    }
  
    if (option==2){
        string a[]={"ZqqZll","WqqZll","WpqqWmlv","WplvWmqq","WlvZqq"};
        int array_size=sizeof(a)/sizeof(a[0]);
        for (int i=0;i<array_size;i++){
             f.push_back(a[i]);
        } 
    }
    
    if (option==3){
        string a[]={"llll","lllv","llvv","lvvv"};
        int array_size=sizeof(a)/sizeof(a[0]);
        for (int i=0;i<array_size;i++){
             f.push_back(a[i]);
        } 
    }
    
    if (option==4){
        string a[]={"single_top_tchan","single_antitop_tchan","single_top_schan","single_antitop_schan",
                     "single_top_wtchan","single_antitop_wtchan"};
        int array_size=sizeof(a)/sizeof(a[0]);
        for (int i=0;i<array_size;i++){
             f.push_back(a[i]);
        } 
    }
    
    if (option==5){
        string a[]={"Zee"};
        int array_size=sizeof(a)/sizeof(a[0]);
        for (int i=0;i<array_size;i++){
             f.push_back(a[i]);
        } 
    }
    
    if (option==6){
        string a[]={"Zmumu"};
        int array_size=sizeof(a)/sizeof(a[0]);
        for (int i=0;i<array_size;i++){
             f.push_back(a[i]);
        } 
    }
    
    if (option==7){
        string a[]={"Ztautau","ttbar_lep","Wplusenu","Wplusmunu", "Wplustaunu","Wminusenu",
                     "Wminusmunu","Wminustaunu","ggH125_WW2lep","VBFH125_WW2lep"};
        int array_size=sizeof(a)/sizeof(a[0]);
        for (int i=0;i<array_size;i++){
             f.push_back(a[i]);
        } 
    }
}
