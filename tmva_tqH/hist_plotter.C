
#include "analyse_cfg.C"

#include "mRootAnalyser.cpp"
#include "mRootStyle.cpp"

class PlotVariable{
  public:
  PlotVariable(){}
  PlotVariable(string key, string label, double min, double max, int dummy = 0){
    this->key = key;
    this->label = label;
    this->min = min;
    this->max = max;
  }
  string label;
  string key;
  string draw_type;
  double min, max;
};

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
      new_ch->process_name = ch->process_name;   
      new_ch->latex_name   = ch->latex_name;    
      new_ch->short_name   = ch->short_name;
      new_ch->signal = ch->signal;
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

vector<PlotVariable> get_variables(){
  vector<PlotVariable> answer = { PlotVariable("weight_BDT_0a_000", "BDT", -1, 1, 100000),
      PlotVariable("weight_BDT_2a_000", "BDT", -1, 1, 100000) ,
      PlotVariable("weight_BDT_4a_000", "BDT", -1, 1, 100000) ,
      PlotVariable("weight_BDT_0b_000", "BDT", -1, 1, 100000),
      PlotVariable("weight_BDT_2b_000", "BDT", -1, 1, 100000),
      PlotVariable("weight_BDT_4b_000", "BDT", -1, 1, 100000),
      PlotVariable("weight_BDT_0c_000", "BDT", -1, 1, 100000),
      PlotVariable("weight_BDT_2c_000", "BDT", -1, 1, 100000),
      PlotVariable("weight_BDT_4c_000", "BDT", -1, 1, 100000),
      PlotVariable("sm_top_fat_jet_pt", "", 0, 1000),
      PlotVariable("fcnc_top_fat_jet_pt", "", 0, 1000),
      PlotVariable("top_jet_scalar", "", 0, 2000),
      PlotVariable("sm_tau_21", "", 0, 1),
      PlotVariable("sm_tau_31", "", 0, 1),
      PlotVariable("sm_tau_32", "", 0, 1),
      PlotVariable("fcnc_tau_21", "", 0, 1),
      PlotVariable("fcnc_tau_31", "", 0, 1),
      PlotVariable("fcnc_tau_32", "", 0, 1),
      PlotVariable("sm_top_sd_m", "", 0, 300),
      PlotVariable("fcnc_top_sd_m", "", 0, 300),
      PlotVariable("fcnc_leadin_mass", "", 0, 300),
      PlotVariable("fcnc_bH_mass", "", 0, 300),
      PlotVariable("fcnc_bW_mass", "", 0, 300),
      PlotVariable("sm_leadin_mass", "", 0, 300),
      PlotVariable("sm_bH_mass", "", 0, 300),
      PlotVariable("sm_bW_mass", "", 0, 300),
      PlotVariable("mass_disbalance", "", 0, 1),
      PlotVariable("H_x_fatjet", "", 0, 2000),
      PlotVariable("W_x_fatjet", "", 0, 2000),
      PlotVariable("H_pt", "", 0, 1000),
      PlotVariable("W_pt", "", 0, 1000),
    };
  return answer;
}

void hist_plotter(){
  vector<DataSet*> datasets = get_datasets( false );
  vector<DataSet*> processes = get_processes( datasets, {});

  string out_file_name = "./output/test_big_3_plots/total_plots.root";
  TFile * file_out = TFile::Open( out_file_name.c_str(), "RECREATE");

  string inp_file_name = "./output/test_big_3_hists/total.root";
  TFile * file_inp = TFile::Open( inp_file_name.c_str(), "READ");

  vector<TH1D*> * hists = get_all_with_type<TH1D>(file_inp, "TH1D");
  map< string, TH1D*> hists_map;
  for(auto hist: *hists)
    hists_map[ hist->GetName() ] = hist;

  vector<PlotVariable> variables = get_variables();
  for(auto variable : variables){
    cout << "QQQ" << endl;
    file_inp->cd();
    HistDrawer<> drawer = HistDrawer<>();
    
    cout << "QQQ" << endl;
    for(auto process : processes){
      string name = process->short_name + "_" + variable.key;
    cout << name << endl;
      TH1D* hist = hists_map.find( name )->second;
    cout <<  hist << endl;

      if( process->signal ) hist->Scale( 2.0 );
      // if( variable.label == string("BDT") ) hist->Rebin(2000);

    cout <<  process->latex_name << endl;

      hist->SetTitle( process->latex_name.c_str() );
      drawer.Add( hist, process->signal);
    }
    
    cout << variable.label << " >>> " << variable.key << endl;

 // TCanvas * draw_hists_FCC( HistDrawer<T> * drawer, string path, string name, string label, string extra_title = "", string mode = "default"){
    TCanvas* canv = mRoot::draw_hists_FCC(& drawer, "./output/test_big_2_plots/", "B_" + variable.key + "_tmva_fcc.png", variable.label, "", "tmva");

    file_out->cd();
    canv->SetName( variable.key.c_str() );
    canv->Write();
  }

}













