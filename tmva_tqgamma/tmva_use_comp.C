
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRoot.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootStackDrawer.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootStyle.cpp"
#include "tmva_use.C"

using namespace mRoot;

vector<ChanalData> get_processes(vector<ChanalData> channels, vector<string> usefull_channels){
  vector<ChanalData> answer;

  for(auto ch : channels){
    int ifind = -1;
    for(int i = 0; i < answer.size(); i++)
      if(answer.at(i).process_name == ch.process_name) ifind = i;

    if( usefull_channels.size() ){
      int jfind = -1;
      for(int i = 0; i < usefull_channels.size(); i++)
        if(usefull_channels.at(i) == ch.process_name) jfind = i;
      if(jfind == -1) continue;
    }
    
    if(ifind != -1)
      answer.at(ifind).file_names.push_back( ch.physic_name );
    else{
      ChanalData new_ch = ch;
      new_ch.file_names = { ch.physic_name };
      answer.push_back( new_ch );
    }
  }

  return answer;
}

void print_processes_vars(vector<PlotVariable> vars, vector<ChanalData> processes, string samples_path, string output_path, string x_label = "Jet M [GeV]", string fmode = "pf"){
  for(auto proc : processes){
    HistDrawer<> * drawer = new HistDrawer<>();
    for(int i = 0; i < vars.size(); i++){
      string variable   = vars.at(i).var_name;
      string label      = vars.at(i).xaxis_name;
      int nbins         = vars.at(i).nbins;
      double xmin       = vars.at(i).xmin;
      double xmax       = vars.at(i).xmax;

      TH1D * hist = new TH1D( (proc.short_name + "_" + variable).c_str(), label.c_str(), nbins, xmin, xmax);
      for( string file_name : proc.file_names ){
        string input_file = samples_path + "/" +  file_name + ".root";
        cout << variable << " ... " << input_file << endl;
        TH1D * tmp_hist = get_hist( input_file, variable, nbins, xmin, xmax );
        tmp_hist->Print();
        hist->Add( tmp_hist );
      }

      //if(i > 3) drawer->signals.push_back( hist );
      drawer->backgrounds.push_back( hist );
    }

    auto canvas1 = mRoot::draw_hists_FCC( drawer, output_path , "comp_" + fmode + "_" + proc.short_name + "_fcc.png", x_label, proc.process_name );
  }
}

vector<PlotVariable> get_jet_variable(vector<string> jet_types, vector<string> jet_cones, string postfix, int nbins = 50, double xmin = 0, double xmax = 400){
  vector<PlotVariable> vars;
  for(auto type : jet_types)
    for(auto cone : jet_cones){
      string name = "ptag_" + type + "jets" + cone + postfix; // "_softDroppedJet_m";
      string label = type + "-jet R = 0." + cone.substr(1);
      vars.push_back( PlotVariable(label, xmin, xmax, nbins, name) );
    }
  return vars;
}

void tmva_use_comp(string samples_path, string output_path){
  auto channels  = get_channals( );
  auto processes = get_processes( channels, {"t #rightarrow #gamma u"} );
  vector<PlotVariable> vars;

  double xmin = 0;
  double xmax = 400;
  int nbins = 50;

  // compare different variables for signals and backgrounds ------------------------------- //
  // mass of photon jet  ------------------------------- //
  if(true){
    vector<string> jet_types = {"pf"/*, "trk", "calo"*/};
    vector<string> jet_cones = {"02", "04",  "08"};

    vars = get_jet_variable({"pf"/*, "trk", "calo"*/}, {"02", "04",  "08"}, "_m", nbins, xmin, xmax);
    print_processes_vars(vars, processes, samples_path, output_path);
  }
  // mass of photon jet after softdrop ------------------------------- //
  if(true){
    vars = get_jet_variable({"pf"/*, "trk", "calo"*/}, {"02", "04",  "08"}, "_softDroppedJet_m");
    print_processes_vars(vars, processes, samples_path, output_path, "Soft Dropped Jet M [GeV]", "SoftDroppedJetM");
  }

  // pt, e and of photon jet after softdrop ------------------------------- //
  if(true){
    vector<string> svars = {"_softDroppedJet_pt",            "_softDroppedJet_m",            "_softDroppedJet_e",
                            "_leadingSoftDroppedSubJet_pt",  "_leadingSoftDroppedSubJet_m",  "_leadingSoftDroppedSubJet_e", 
                            "_trailingSoftDroppedSubJet_pt", "_trailingSoftDroppedSubJet_m", "_trailingSoftDroppedSubJet_e"};
    vector<string> slabels = {"Soft Dropped Jet p_{T}",              "Soft Dropped Jet M",              "Soft Dropped Jet E",
                              "Leading Soft Dropped Sub Jet p_{T}",  "Leading Soft Dropped Sub Jet M",  "Leading Soft Dropped Sub Jet E", 
                              "Trailing Soft Dropped Sub Jet p_{T}", "Trailing Soft Dropped Sub Jet M", "Trailing Soft Dropped Sub Jet E"};
    
    for(int i = 0; i < svars.size(); i++){
        if(svars.at(i).at( svars.at(i).size() -1 ) == 'm' ) xmax = 400;
        else                                                xmax = 5000;

        vector<PlotVariable> tmp_vars = get_jet_variable({"pf"/*, "trk", "calo"*/}, {"02", "04", "08"}, svars.at(i), nbins, xmin, xmax);
        print_processes_vars(tmp_vars, processes, samples_path, output_path, slabels.at(i)  + " [GeV]", svars.at(i));
    }
  }
 
  if(true){
    print_variables(samples_path + "/mgp8_pp_tt_aut.root", {"ptag_pfjets08_pt", "ptag_pfjets08_softDroppedJet_pt", "ptag_pfjets08_leadingSoftDroppedSubJet_pt", "ptag_pfjets08_trailingSoftDroppedSubJet_pt"}, 25);
    cout << "---" << endl;
    print_variables(samples_path + "/mgp8_pp_tt_aut.root", {"ptag_pfjets08_e", "ptag_pfjets08_softDroppedJet_e", "ptag_pfjets08_leadingSoftDroppedSubJet_e", "ptag_pfjets08_trailingSoftDroppedSubJet_e"}, 25);
  }
  

}



