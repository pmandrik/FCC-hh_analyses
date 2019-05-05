
#include "analyse_cfg.C"

vector<DataSet*> get_processes(const vector<DataSet*> & channels, vector<string> usefull_channels){
  vector<DataSet*> answer;

  for(auto ch : channels){
    int ifind = -1;
    for(int i = 0; i < answer.size(); i++)
      if(answer.at(i)->latex_name == ch->latex_name) ifind = i;

    if( usefull_channels.size() ){
      int jfind = -1;
      for(int i = 0; i < usefull_channels.size(); i++)
        if(usefull_channels.at(i) == ch->latex_name) jfind = i;
      if(jfind == -1) continue;
    }
    
    if(ifind != -1){
      DataSet * old_ch = answer.at(ifind);
      old_ch->files.push_back( ch->process_name );

      for(TH1D* hist_new : ch->hists){
        for(TH1D* hist_old : old_ch->hists){
          if( string(hist_old->GetTitle()) == string(hist_new->GetTitle()) ){
            hist_old->Add( hist_new );
          }
        }
      }
    } else { 
      DataSet * new_ch = new DataSet();    
      new_ch->signal = ch->signal;
      new_ch->process_name = ch->process_name;   
      new_ch->latex_name   = ch->latex_name;    
      new_ch->short_name   = ch->short_name;
      new_ch->files = { ch->process_name };
      new_ch->hists = ch->hists;

      for(TH1D* hist : new_ch->hists){
        hist->SetName( (ch->short_name + "_" + hist->GetTitle()).c_str() );
      }

      answer.push_back( new_ch );  
    }
  }

  return answer;
}


void hist_combainer(){

  vector<DataSet*> datasets = get_datasets( false );

  string out_file_name = "./output/test_big_3_hists/total.root";
  TFile * file = TFile::Open( out_file_name.c_str(), "RECREATE");

  // read
  for(auto dataset : datasets){
    string file_name = "./output/test_big_3_hists/" + dataset->process_name + "_hists.root";

    TFile * file = TFile::Open( file_name.c_str(), "READ");
    vector<TH1D*> * hists = get_all_with_type<TH1D>(file, "TH1D");
    vector<TH1D*> hists_clone;
    
    for(TH1D* hist : *hists) hists_clone.push_back( new TH1D(*hist) ); // SetDirectory(0);
    for(TH1D* hist : *hists) 
      cout << ((TH1D*)hist)->GetName() << " " << ((TH1D*)hist)->GetTitle() << " " << ((TH1D*)hist)->GetEntries() << endl;

    for(TH1D* hist : hists_clone) ((TH1D*)hist)->SetDirectory(0);
    file->Close();

    // cout << "---> X" << endl;
    // for(TH1D* hist : hists_clone) ((TH1D*)hist)->Print();
    dataset->hists = hists_clone;
  }

  cout << " ---------> X <--------- " << endl;
  // get process from datasets
  file->cd();
  vector<DataSet*> processes = get_processes( datasets, {} );
  for(auto process : processes){
    for(auto hist : process->hists){
      cout << ((TH1D*)hist)->GetName() << " " << ((TH1D*)hist)->GetEntries() << endl;
      hist->Write();
    }
  }

  // file->ls();
}















