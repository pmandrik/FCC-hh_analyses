
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRoot.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootStackDrawer.cpp"

using namespace mRoot;

void prep_hists(string var, string out_path, int nbins = 25, int lumi_factor = 1, bool cut = false){
  // string path = "/afs/cern.ch/work/p/pmandrik/fcc_100TeV/6_tmva/tqH/output/test_big_3_hists";
  string path = "/afs/cern.ch/work/p/pmandrik/fcc_100TeV/6_tmva/H/output/hists";

  TFile * file = TFile::Open((path + "/" + "total.root").c_str());
  vector<TH1D*> * hists = get_all_with_type<TH1D>(file, "TH1D");

  TFile * file_out = new TFile((out_path + "/" + "hists_limits.root").c_str(), "RECREATE");

  double left_entry  = 1;
  double right_entry = -1;

  for(auto hist : *hists){
    string name = hist->GetName();
    if(name.find(var) == std::string::npos) continue;

    left_entry  = TMath::Min(left_entry,  hist->GetBinCenter(hist->FindFirstBinAbove(0)) );
    right_entry = TMath::Max(right_entry, hist->GetBinCenter(hist->FindLastBinAbove(0))  );
  }

  for(auto hist : *hists){
    string name = hist->GetName();
    if(name.find(var) == std::string::npos) continue;
    // cout << hist->GetName() << " " << left_entry << " " << right_entry << endl;

    TH1D * new_hist = new TH1D((string(hist->GetName()) + "_" + to_string(nbins) + "_" + to_string(lumi_factor)).c_str(), hist->GetTitle(), nbins, left_entry, right_entry);        
    for(int i = 1; i <= hist->GetXaxis()->GetNbins(); i++){
      if(name.find("bsH") != std::string::npos or name.find("bdH") != std::string::npos)
        new_hist->Fill(hist->GetBinCenter(i), 0.001*hist->GetBinContent(i) / float(lumi_factor) );
      else 
        new_hist->Fill(hist->GetBinCenter(i), hist->GetBinContent(i) / float(lumi_factor) );
     // cout << i << " " << hist->GetBinContent(i) << endl;
    }
  }

  // file_out->ls();
  file_out->Write();
  file_out->Close();
}

