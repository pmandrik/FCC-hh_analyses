

#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRoot.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootAnalyser.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootThread.cpp"
#include "tmva_use_comp.C"

void get_eff(){
  auto channels = get_channals();
  
  string samples_path = "/afs/cern.ch/work/p/pmandrik/fcc_100TeV/6_tmva/tqgamma/OUTPUT/fcnc_may_29";
  for(auto channel : channels){
    string inp_name = samples_path + "/" +channel.physic_name + ".root";
    TFile * file = TFile::Open( inp_name.c_str(), "READ" );
    TTree * tree = (TTree*) file->Get("ttree");
    cout << channel.physic_name << " " << tree->GetEntries() << endl;
  }
}
