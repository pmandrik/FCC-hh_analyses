
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRoot.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootStackDrawer.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootStyle.cpp"
#include "tmva_prepare.C"

using namespace mRoot;

vector<string> get_variables(string input_file){
  TFile *f = new TFile(input_file.c_str(),"READ");
  TTree * tree = (TTree*)f->Get("data");

  TObjArray *vars = tree->GetListOfBranches();
  vector<string> answer;

  for(int i = 0; i < vars->GetEntries(); ++i){ 
    answer.push_back( vars->At(i)->GetName() ); 
  }

  return answer;
}

TH1D * get_hist(string input_file, string variable, int nbins, double min, double max){
  TH1D * answer = new TH1D( (input_file + "@" + variable).c_str(), (input_file + "@" + variable).c_str(), nbins, min, max);

  TFile *f = new TFile(input_file.c_str(),"READ");
  TTree * tree = (TTree*)f->Get("data");

  TTreeFormula * var_formula = new TTreeFormula(variable.c_str(), variable.c_str(), tree);
  TTreeFormula * weight_formula = new TTreeFormula("weight", "weight", tree);

  int n_events = tree->GetEntries();
  for(int i = 0; i < n_events; i++){
    tree->GetEntry(i); 
    answer->Fill( var_formula->EvalInstance(), weight_formula->EvalInstance() );
  }

  f->Close();

  return answer;
}

void print_variables(string input_file, vector<string> vars, int max_events){
  TFile *f = new TFile(input_file.c_str(),"READ");
  TTree * tree = (TTree*)f->Get("data");

  vector<TTreeFormula *> formulas;
  for(auto variable : vars){
    formulas.push_back( new TTreeFormula(variable.c_str(), variable.c_str(), tree) );
  }

  int n_events = TMath::Min((int)tree->GetEntries(), max_events);
  for(int i = 0; i < n_events; i++){
    tree->GetEntry(i); 
    for(auto var_formula : formulas)
      cout << var_formula->EvalInstance() << " ";
    cout << endl;
  }
}

struct PlotVariable {
  PlotVariable(){}
  PlotVariable(string title, double min, double max, int bins = 20, string vname=""){
    xmin = min;
    xmax = max;
    nbins = bins;
    xaxis_name = title;
    var_name   = vname;
  }

  int nbins;
  double xmin, xmax;
  string xaxis_name;
  string var_name;
};

void tmva_use(string samples_path, string output_path){

  map<string, PlotVariable> custom_variables;

  custom_variables["weight_k"] = PlotVariable("BDT kinematic", -1, 1);
  custom_variables["weight_b"] = PlotVariable("BDT top jet tagging", -1, 1);
  custom_variables["weight_p"] = PlotVariable("BDT photon jet tagging", -1, 1);
  custom_variables["weight_f"] = PlotVariable("BDT combined", -1, 1);

  custom_variables["photon_eta"]          = PlotVariable("Photon #eta", -3, 3);
  custom_variables["photon_pt"]           = PlotVariable("Photon p_{T} [GeV]", 0, 3500);
  custom_variables["bJet_eta"]            = PlotVariable("b-jet #eta", -3, 3);
  custom_variables["bJet_pt"]             = PlotVariable("b-jet p_{T} [GeV]", 0, 3500);
  custom_variables["top_pt"]              = PlotVariable("t p_{T} [GeV]", 0, 3500);
  custom_variables["nearestJet_pt"]       = PlotVariable("photon jet p_{T} [GeV]", 0, 2500);
  custom_variables["dR_Photon_bjet"]      = PlotVariable("#Delta R(#gamma, b-jet)", 0.7, 5.);
  custom_variables["M_Photon_nearestJet"] = PlotVariable("M(#gamma, photon jet)", 0, 500.);

  auto channels = get_channals( );
  // for every channel get histogram and combine them in stack?

  string file = samples_path + "/" +  channels.at(0).physic_name + ".root";
  auto variables = get_variables( file );
  cout << "Variables : " << endl;
  for(auto var : variables){
    cout << var << endl;
  }

  TChain * chain = new TChain("data");
  for(auto channel : channels)
    chain->Add( (samples_path + "/" +  channel.physic_name + ".root").c_str() );

  TFile * output_hists = new TFile( (output_path + "/hists.root").c_str(), "RECREATE");
  bool frun = true;

  if(false){
    variables.clear();
    for(auto it = custom_variables.begin(); it != custom_variables.end(); it++)
      variables.push_back( it->first );
  }

  for(auto variable : variables){
    auto finder = custom_variables.find(variable);
    if(false) if(custom_variables.find(variable) != custom_variables.end()) continue;

    int nbins = 20;
    double xmin = chain->GetMinimum( variable.c_str() );
    double xmax = chain->GetMaximum( variable.c_str() );
    cout << variable << " [" << xmin << ", " << xmax << "]" << endl;
    // xmin = his->GetXaxis()->GetXmin();
    // xmax = his->GetXaxis()->GetXmax();
    if(xmax > 1000 or xmin < -1000){
      chain->Draw( (variable + ">>his").c_str() );
      TH1F *his = (TH1F *)gDirectory->Get("his");
      double mean = his->GetMean();
      double rms  = his->GetRMS();
      if(xmax > 0 and xmax >  mean + 2 * rms) xmax = mean + 2 * rms;
      if(xmin < 0 and xmin < -mean - 2 * rms) xmin = mean - 2 * rms;
    }
    cout << variable << " [" << xmin << ", " << xmax << "] # 3" << endl;

    string variable_title = variable;
    // if(var.title.size()) title = var.title;

    if(custom_variables.find(variable) != custom_variables.end()){
      xmin = finder->second.xmin;
      xmax = finder->second.xmax;
      variable_title = finder->second.xaxis_name;
    }

    HistDrawer<> * drawer = new HistDrawer<>();
    HistDrawer<> * drawer_norm = new HistDrawer<>();
    map<string, TH1D*> hists;
    map<string, TH1D*> hists_norm;
    for(auto channel : channels){
      if( hists.find(channel.process_name) != hists.end() ) continue;

      TH1D * hist      = new TH1D( (channel.short_name + "_" + variable).c_str(), channel.process_name.c_str(), nbins, xmin, xmax);
      TH1D * hist_norm = new TH1D( (channel.short_name + "_" + variable + "_norm").c_str(), channel.process_name.c_str(), nbins, xmin, xmax);

      hists     [ channel.process_name ] = hist;
      hists_norm[ channel.process_name ] = hist_norm;

      if(not channel.signal){
        drawer->backgrounds.push_back( hist );
        drawer_norm->backgrounds.push_back( hist_norm );
      }
      else{
        drawer->signals.push_back( hist );
        drawer_norm->signals.push_back( hist_norm );
      }
    }

    for(auto channel : channels){
      string input_file = samples_path + "/" +  channel.physic_name + ".root";
      auto hist = get_hist( input_file, variable, nbins, xmin, xmax );
      hist->SetTitle( channel.process_name.c_str() );

      auto hist_norm = (TH1D*)hist->Clone( (string(hist->GetName()) + "_norm").c_str() );

      hists.find( channel.process_name )->second->Add( hist );
      hists_norm.find( channel.process_name )->second->Add( hist_norm );
    }

    for(auto it = hists_norm.begin(); it != hists_norm.end(); it++)
      it->second->Scale(1.0/it->second->Integral("width"));

    output_hists->cd();
    for(auto it = hists.begin(); it != hists.end(); it++){
      it->second->Write();
      if(frun){
        cout << "Sample: \"FIXME\"\nType: BACKGROUND\nTitle:\"FIXME\"\nFillColor: " + to_string( it->second->GetLineColor() ) +"\nLineColor: " + to_string( it->second->GetLineColor() ) << endl;
        cout << "HistoFile: \"hists\" \n HistoName: \"" << it->second->GetName() << "\" \nNormalizedByTheory:FALSE " << endl;
      }
    }
    frun = false;

    auto canvas1 = mRoot::draw_hists_FCC( drawer, output_path , "c_" + variable + "_fcc.png", variable_title );
    auto canvas2 = mRoot::draw_hists_FCC( drawer_norm, output_path , "c_" + variable + "_fcc.png", variable_title );
    canvas1->Write();
    canvas2->Write();

  }
  output_hists->Close();
}



