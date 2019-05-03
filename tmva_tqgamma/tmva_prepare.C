
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRoot.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootStackDrawer.cpp"

using namespace mRoot;

struct ChanalData{
  string physic_name, process_name, short_name;
  vector<string> file_names;
  bool signal;
  int nevents;
  double full_events_number;
  double weight_sum, xsec;
};


double get_number(string line){
  string nuber_line;
  int begin = -1, end = -1;
  for(int i = 0; i < line.size(); i++){
    if( begin == -1 and line.at(i) >= '0' and line.at(i) <= '9' ) begin = i;
    if( begin != -1 and (line.at(i) < '0' or line.at(i) > '9')  ){
      end = i;
      break;
    }
  }
  nuber_line = line.substr( begin, end-begin );
  return atof( nuber_line.c_str() );
}

ChanalData get_chanal(string physic_name, string input_path, bool calc_weights, bool is_signal, float xsec, string process_name, string short_name){
  // msg("add channel ", physic_name, input_path);
  ChanalData answer;
  answer.physic_name = physic_name;
  answer.process_name = process_name;
  answer.signal      =  is_signal;
  answer.xsec        =  xsec;
  answer.short_name  =  short_name;
  
  if(input_path.size()){
    string fpath = input_path + "/" + physic_name + "/heppy.FCChhAnalyses.FCNC_ttgamma.TreeProducer.TreeProducer_1/tree.root";
    string wpath = input_path + "/" + physic_name + "/heppy.FCChhAnalyses.FCNC_ttgamma.TreeProducer.WeightTreeProducer_1/weight_tree.root";
    string log_path = input_path + "/" + physic_name + "/heppy.FCChhAnalyses.FCNC_ttgamma.selection.Selection_cuts/cut_flow.txt";


    std::ifstream log_file( log_path.c_str() );
    std::string line;
    while (std::getline(log_file, line)){
      
      if(line.find("All events") == std::string::npos) continue;
      int pos = line.find("All events");
      double number = get_number( line.substr( pos + 10 ) );

      // cout << line << endl;
      // cout << "number = " << number << endl;

      answer.full_events_number = number;
      break;
    }

    if(calc_weights){
      TFile * f = TFile::Open( fpath.c_str() );
      TTree * tree = (TTree*)gDirectory->Get("events");
      if(not tree) msg("no tree !!!");
      answer.nevents = tree->GetEntries();
      f->Close();

      TFile * w = TFile::Open( wpath.c_str() );
      TTree * wtree = (TTree*)gDirectory->Get("events");
      if(not wtree) msg("no tree !!!");
      long long int w_events = wtree->GetEntries();
      Double_t weight;
      Double_t weight_sum = 0;
      wtree->SetBranchAddress("weight", &weight);
      for(long long int i = 0; i < w_events; i++){
        wtree->GetEntry(i);
        weight_sum += weight;
      }
      cout << physic_name << " " << w_events << " " << answer.nevents << " " << answer.xsec << endl;
      // cout << "full_events_number = " << answer.full_events_number << " w_events = "  << w_events << " weight_sum = " << weight_sum << endl;
      w->Close();

      answer.weight_sum = weight_sum;
      // cout << physic_name << " " << answer.nevents << endl;
    }

    answer.file_names.push_back( fpath );
  }

  return answer;
}

/*

check new ttbar sample - Done
care about normalisation after splitting of the MC events into training ant testing samples - Done
W bug - Done

ttbar comparison

*/

vector<ChanalData> get_channals(string input_path="", bool calc_weights = true){
   // xsec*effmatch*kfactor/sumw
   double fcnc_branch     = 0.428 * pow(0.001, 2);
   double ttbar_xsec_1000 = 11.82 * 2.0;
   double ttbar_xsec_500  = 213.5 * 2.0; // 11.82 * 2.0; // xsec * k_factor

   double fcnc_xsec_1000           = ttbar_xsec_1000 * fcnc_branch * 2;
   double fcnc_xsec_500            = ttbar_xsec_500  * fcnc_branch * 2;
   double fcnc_xsec_500_minus_1000 = fcnc_xsec_500 - fcnc_xsec_1000;

   vector<ChanalData> answer = {
      // get_chanal("mgp8_pp_tt_aut",                      input_path, calc_weights, true,    fcnc_xsec_1000,             "t #rightarrow #gamma u", "tau"),
      // get_chanal("mgp8_pp_tt_act",                      input_path, calc_weights, true,    fcnc_xsec_1000,             "t #rightarrow #gamma c", "tac"),
      get_chanal("mgp8_pp_tt_aut_cut500",               input_path, calc_weights, true,    fcnc_xsec_500,              "t #rightarrow #gamma u", "tau"),
      get_chanal("mgp8_pp_tt_act_cut500",               input_path, calc_weights, true,    fcnc_xsec_500,              "t #rightarrow #gamma c", "tac"),

      // get_chanal("mgp8_pp_tt_hadronic_aut",             input_path, calc_weights, true,   1.526*1000000 / 100 * 1.0 * 1.0, "t #rightarrow #gamma u no boost", "tau no boost"),
      get_chanal("mgp8_pp_jjja_5f",                     input_path, calc_weights, false,  1.023*100000. * 1.2 * 1.0, "#gamma + jets", "ajets"),

   // get_chanal("mgp8_pp_ttj_4f",                      input_path, false,  4789.,         "t#bar{t} + jets", "ttjets"),
   // get_chanal("mgp8_pp_tt012j_5f",                   input_path, false,  4.311*10000. * 1.74	* 0.466,  "t#bar{t} + jets", "ttjets"),

/*
      get_chanal("mgp8_pp_tt012j_5f_HT_0_600",          input_path, calc_weights, false,  3.207*10000. * 1.74	* 0.507,  "t#bar{t} + jets", "ttjets"),
      get_chanal("mgp8_pp_tt012j_5f_HT_600_1200",       input_path, calc_weights, false,  8883.        * 1.74	* 0.352,  "t#bar{t} + jets", "ttjets"),
      get_chanal("mgp8_pp_tt012j_5f_HT_1200_2100",      input_path, calc_weights, false,  1737.        * 1.74	* 0.328,  "t#bar{t} + jets", "ttjets"),          
      get_chanal("mgp8_pp_tt012j_5f_HT_2100_3400",      input_path, calc_weights, false,  284.3        * 1.74	* 0.315,  "t#bar{t} + jets", "ttjets"),
      get_chanal("mgp8_pp_tt012j_5f_HT_3400_5300",      input_path, calc_weights, false,  44.91        * 1.74	* 0.306,  "t#bar{t} + jets", "ttjets"),
      get_chanal("mgp8_pp_tt012j_5f_HT_5300_8100",      input_path, calc_weights, false,  6.484        * 1.74	* 0.298,  "t#bar{t} + jets", "ttjets"),
      get_chanal("mgp8_pp_tt012j_5f_HT_8100_15000",     input_path, calc_weights, false,  0.8583       * 1.74	* 0.294,  "t#bar{t} + jets", "ttjets"),
      get_chanal("mgp8_pp_tt012j_5f_HT_15000_25000",    input_path, calc_weights, false,  0.0219       * 1.74	* 0.296,  "t#bar{t} + jets", "ttjets"),
      get_chanal("mgp8_pp_tt012j_5f_HT_25000_35000",    input_path, calc_weights, false,  0.0004247    * 1.74	* 0.307,  "t#bar{t} + jets", "ttjets"),
      get_chanal("mgp8_pp_tt012j_5f_HT_35000_100000",   input_path, calc_weights, false,  1.459/100000.* 1.74	* 0.323,  "t#bar{t} + jets", "ttjets"),
*/

      get_chanal("mgp8_pp_z0123j_4f_HT_0_150",          input_path, calc_weights, false,  1478000.0 * 1.2 * 0.713,      "Z + jets", "Zjets"),
      get_chanal("mgp8_pp_z0123j_4f_HT_150_300",        input_path, calc_weights, false,  83770.0   * 1.2 * 0.261,      "Z + jets", "Zjets"),
      get_chanal("mgp8_pp_z0123j_4f_HT_300_500",        input_path, calc_weights, false,  24930.0   * 1.2 * 0.27,       "Z + jets", "Zjets"),
      get_chanal("mgp8_pp_z0123j_4f_HT_500_1000",       input_path, calc_weights, false,  10370.0   * 1.2 * 0.267,      "Z + jets", "Zjets"),
      get_chanal("mgp8_pp_z0123j_4f_HT_1000_2000",      input_path, calc_weights, false,  1917.0    * 1.2 * 0.259,      "Z + jets", "Zjets"),
      get_chanal("mgp8_pp_z0123j_4f_HT_2000_5000",      input_path, calc_weights, false,  273.7     * 1.2 * 0.248,      "Z + jets", "Zjets"),
      get_chanal("mgp8_pp_z0123j_4f_HT_5000_100000",    input_path, calc_weights, false,  11.11     * 1.2 * 0.234,      "Z + jets", "Zjets"),

      //get_chanal("mgp8_pp_w0123j_4f_HT_0_150",          input_path, calc_weights, false,  465800.0  * 1.2 * 0.69,       "W + jets", "Wjets"),
      //get_chanal("mgp8_pp_w0123j_4f_HT_150_300",        input_path, calc_weights, false,  29440.0   * 1.2 * 0.256,      "W + jets", "Wjets"),
      //get_chanal("mgp8_pp_w0123j_4f_HT_300_500",        input_path, calc_weights, false,  8958.0    * 1.2 * 0.263,      "W + jets", "Wjets"),
      get_chanal("mgp8_pp_w0123j_4f_HT_500_1000",       input_path, calc_weights, false,  3756.0    * 1.2 * 0.262,      "W + jets", "Wjets"),
      get_chanal("mgp8_pp_w0123j_4f_HT_1000_2000",      input_path, calc_weights, false,  703.8     * 1.2 * 0.255,      "W + jets", "Wjets"),
      get_chanal("mgp8_pp_w0123j_4f_HT_2000_5000",      input_path, calc_weights, false,  102.3     * 1.2 * 0.245,      "W + jets", "Wjets"),
      get_chanal("mgp8_pp_w0123j_4f_HT_5000_100000",    input_path, calc_weights, false,  4.196     * 1.2 * 0.231,      "W + jets", "Wjets"),

      get_chanal("mgp8_pp_tt_5f_HT_500_1000",       input_path, calc_weights, false,  2019           * 2 * 1,  "t#bar{t}", "ttjets"),
      get_chanal("mgp8_pp_tt_5f_HT_1000_2000",      input_path, calc_weights, false,  202.8          * 2 * 1,  "t#bar{t}", "ttjets"),
      get_chanal("mgp8_pp_tt_5f_HT_2000_5000",      input_path, calc_weights, false,  11.63          * 2 * 1,  "t#bar{t}", "ttjets"),
      get_chanal("mgp8_pp_tt_5f_HT_5000_10000",     input_path, calc_weights, false,  0.135          * 2 * 1,  "t#bar{t}", "ttjets"),
      get_chanal("mgp8_pp_tt_5f_HT_10000_27000",    input_path, calc_weights, false,  0.002716       * 2 * 1,  "t#bar{t}", "ttjets"),
      get_chanal("mgp8_pp_tt_5f_HT_27000_100000",   input_path, calc_weights, false,  1.564/1000000. * 2 * 1,  "t#bar{t}", "ttjets"),

      get_chanal("mgp8_pp_t123j_5f",                    input_path, calc_weights, false,  7524.        * 2.16	* 0.288,  "t + jets", "tjets"),

      get_chanal("mgp8_pp_tta",                         input_path, calc_weights, false,  109.5        * 2.0    * 1,      "other"/*"t#bar{t} + #gamma"*/, "other"),
      get_chanal("mgp8_pp_tajets",                      input_path, calc_weights, false,  0.08281      * 1    * 1,      "other"/*"t + #gamma + jets"*/, "other"),
      get_chanal("mgp8_pp_wa",                          input_path, calc_weights, false,  655          * 1    * 1,      "other"/*"W + #gamma"*/, "other"),

/*
'mg_pp_tt012j_5f_HT_0_600':['top pair + 0/1/2 jets','0 < HT < 600','xqcut = 60, qCut = 90','3.207e+04','1.74','0.507'],
'mg_pp_tt012j_5f_HT_600_1200':['top pair + 0/1/2 jets','600 < HT < 1200','xqcut = 60, qCut = 90','8883','1.74','0.352'],
'mg_pp_tt012j_5f_HT_1200_2100':['top pair + 0/1/2 jets','1200 < HT < 2100','xqcut = 60, qCut = 90','1737','1.74','0.328'],
'mg_pp_tt012j_5f_HT_2100_3400':['top pair + 0/1/2 jets','2100 < HT < 3400','xqcut = 60, qCut = 90','284.3','1.74','0.315'],
'mg_pp_tt012j_5f_HT_3400_5300':['top pair + 0/1/2 jets','3400 < HT < 5300','xqcut = 60, qCut = 90','44.91','1.74','0.306'],
'mg_pp_tt012j_5f_HT_5300_8100':['top pair + 0/1/2 jets','5300 < HT < 8100','xqcut = 60, qCut = 90','6.484','1.74','0.298'],
'mg_pp_tt012j_5f_HT_8100_15000':['top pair + 0/1/2 jets','8100 < HT < 15000','xqcut = 60, qCut = 90','0.8583','1.74','0.294'],
'mg_pp_tt012j_5f_HT_15000_25000':['top pair + 0/1/2 jets','15000 < HT < 25000','xqcut = 60, qCut = 90','0.0219','1.74','0.296'],
'mg_pp_tt012j_5f_HT_25000_35000':['top pair + 0/1/2 jets','25000 < HT < 35000','xqcut = 60, qCut = 90','0.0004247','1.74','0.307'],
'mg_pp_tt012j_5f_HT_35000_100000':['top pair + 0/1/2 jets','35000 < HT < 100000','xqcut = 60, qCut = 90','1.459e-05','1.74','0.323'],
*/

  };

  return answer;
}

vector<string> get_variables(){
  vector<string> answer = {// def
                           "weight", "dR_photon_uquark", "dPhi_photon_uquark", "top_pt", "dPhi_Photon_t", "dPhi_Photon_tbar", "dR_Photon_t", "dR_Photon_tbar",
                           "jets_size", "fatjets_size", "lepton_channel", "jets_btag_size", "jets_ltag_size",
                           // for photon jet tag
                           "photon_eta", "photon_pt",
                           // for top bjet tag
                           "bJet_eta", "bJet_pt", "M_lepton_met", "M_bjet_lepton_met", "lepton_x_bjet", "lepton_channel",
                           // top bjet and photon jet kinematic
                           "dPhi_top_candidates", "dR_top_candidates", "photon_x_bjet", "photon_x_lepton",
                           "lepton_relIso", "photon_relIso",

                           // default plots
/*                           
                           // for photon jet tag
                           "photonfatjet_tau1", "photonfatjet_tau2", "photonfatjet_tau3", "photonjet04_tau1", "photonjet04_tau2", "photonjet04_tau3",
                           "photon_pt", "photon_eta", "nearestJet_pt", "nearestJet_eta", "photon_x_photonjet04", "photon_x_photonfatjet",
                           "dR_Photon_nearestJet", "dPhi_Photon_nearestJet", "M_Photon_nearestJet",
                           "photonfatjet_pt", "photonfatjet_eta",
                           // for top bjet tag
                           "bfatjet_tau1", "bfatjet_tau2", "bfatjet_tau3", "bjet04_tau1", "bjet04_tau2", "bjet04_tau3",
                           "lepton_channel", "lepton_x_bfatjet", "M_lepton_met", "M_bjet_lepton_met", "lepton_x_bjet", 
                           "fatjets_size", "bjet_x_bfatjet", "bJet_pt", "bJet_eta",
                           "bfatjet_pt", "bfatjet_eta", 
                           // top bjet and photon jet kinematic
                           "photon_x_bjet", "photon_x_lepton", "bjet_x_photonjet04", "bjet_x_photonfatjet",
                           "dR_Photon_bjet", "dPhi_Photon_bjet",
                           // default plots
                            "top_pt", "dR_photon_uquark", "dPhi_photon_uquark", "dPhi_uquark_nearestJet", "dR_uquark_nearestJet",
                            "dR_Photon_genPhoton", "dPhi_Photon_t", "dPhi_Photon_tbar", "dR_Photon_t", "dR_Photon_tbar", "met_pt",
*/
                          };

  vector<string> jet_names = { "btag_pfjets02",   "btag_pfjets04",   "btag_pfjets08",   "ptag_pfjets02",  "ptag_pfjets04",  "ptag_pfjets08", 
        "btag_calojets02", "btag_calojets04", "btag_calojets08", "btag_trkjets02", "btag_trkjets04", "btag_trkjets08",
        "ptag_calojets02", "ptag_calojets04", "ptag_calojets08", "ptag_trkjets02", "ptag_trkjets04", "ptag_trkjets08",
        "BestMass_jet", "BestTopMass_jet", "SecondTopMass_jet" };

  vector<string> jet_postfixes = {"_pt", "_m", "_e", "_eta",
                                  "_tau1", "_tau2", "_tau3", "_tau31", "_tau32", "_tau21", 
                                  "_softDroppedJet_pt", "_softDroppedJet_m", "_softDroppedJet_e", 
                                  "_leadingSoftDroppedSubJet_pt",  "_leadingSoftDroppedSubJet_m",  "_leadingSoftDroppedSubJet_e",
                                  "_trailingSoftDroppedSubJet_pt", "_trailingSoftDroppedSubJet_m", "_trailingSoftDroppedSubJet_e"  };

  vector<string> jet_prefixes = { "photon_x_", "dPhi_Photon_", "dR_Photon_", "bjet_x_", "dPhi_bjet_", "dR_bjet_", "lepton_x_", "dPhi_lepton_", "dR_lepton_", "M_Photon_" };

  for(auto jname : jet_names){
    for(auto pname : jet_postfixes)
      answer.push_back( jname + pname );

    for(auto pname : jet_prefixes)
      answer.push_back( pname + jname );
  }

  return answer;
}

/*
vector<Variable> get_variables_train(string mode){
  vector<string> answer;
  if(mode == "p"){
    answer = {"photonfatjet_tau1", "photonfatjet_tau2", "photonfatjet_tau3", "photonjet04_tau1", "photonjet04_tau2", "photonjet04_tau3",
              "log(photon_pt)", "photon_eta", "log(nearestJet_pt)", "nearestJet_eta", "log(photon_x_photonjet04)", "log(photon_x_photonfatjet)",
              "dR_Photon_nearestJet", "dPhi_Photon_nearestJet", "log(M_Photon_nearestJet)",
              "log(photonfatjet_pt)", "photonfatjet_eta",
             };
  }
  if(mode == "b"){
      answer = {"bfatjet_tau1", "bfatjet_tau2", "bfatjet_tau3", "bjet04_tau1", "bjet04_tau2", "bjet04_tau3",
                "lepton_channel", "log(lepton_x_bfatjet)", "M_lepton_met", "M_bjet_lepton_met", "log(lepton_x_bjet)",
                "fatjets_size", "log(bjet_x_bfatjet)", "log(bJet_pt)", "bJet_eta",
                "log(bfatjet_pt)", "bfatjet_eta",
               };
  }
  if(mode == "k"){
    answer = {"log(photon_x_bjet)", "log(photon_x_lepton)", "log(bjet_x_photonjet04)", "log(bjet_x_photonfatjet)",
              "dR_Photon_bjet", "dPhi_Photon_bjet", "log(bJet_pt)", "log(photon_pt)", "bJet_eta", "photon_eta",
              "log(photonfatjet_pt)", "photonfatjet_eta", "log(bfatjet_pt)", "bfatjet_eta",
             };
  }
  if(mode == "f"){
    answer = {"weight_p", "weight_b", "weight_k"};
  }

  vector<Variable> vanswer;
  for(auto s : answer){
    vanswer.push_back( Variable(s) );
  }

  return vanswer;
} */

string get_cut(){
  return "(ptag_pfjets04_pt < 400)";
  return "(0)";
  return "(nearestJet_pt < 400)";
}

void tmva_prepare(string com_path, string com_out_path, int tread=-1){

  // setup channels
  string path;
  path = "/afs/cern.ch/work/p/pmandrik/fcc_100TeV/4_analyser/heppy/OUTPUT/fcnc_mar_7_full_2/";
  if(com_path.size()) path = com_path;

  auto channels = get_channals( path );

  return;

  string out_path = "OUTPUT/mar_07";
  if(com_out_path.size()) out_path = com_out_path;

  // set variables
  vector<string> varialbes = get_variables();
  vector<float*> values_f;
  for(auto vname : varialbes){
    values_f.push_back( new float );
    // values.push_back( new TTreeFormula(vname.c_str(), vname.c_str(), nullptr) );
    // tmva_reader->AddVariable( vname.c_str(), (values_f.at( values.size() - 1 )) );
  }
  string cut = get_cut();

  int chanal_tread = -1;
  for(ChanalData cd : channels){
    chanal_tread++;
    if(tread >= 0 and chanal_tread != tread) continue;
    chanal_tread++;

    TChain * chain = new TChain();
    for(string fname : cd.file_names) chain->Add( (fname + "/events" ).c_str());
    vector<TTreeFormula*> values;
    for(int i = 0; i < varialbes.size(); i++)
      values.push_back( new TTreeFormula(varialbes.at(i).c_str(), varialbes.at(i).c_str(), chain) );
    TTreeFormula * cut_formula = new TTreeFormula(cut.c_str(), cut.c_str(), chain);


    TFile *outfile = new TFile( (out_path + "/" + cd.physic_name + ".root").c_str(), "RECREATE");
    TTree *train = new TTree();
    TTree *data  = new TTree();

    train->SetName("train"); train->SetTitle("train");
    data->SetName("data");   data->SetTitle("data");

    for(int i = 0; i < varialbes.size(); i++){
      train->Branch(varialbes.at(i).c_str(), values_f.at(i));
      data->Branch(varialbes.at(i).c_str(), values_f.at(i));
    }

    float lumi = 30 * 1000 * 1000; // 30000000

    cout << "tread(" << tread << ") " << "!>begin" << endl;
    int selected_events = cd.nevents;
    int train_n_events = TMath::Max(TMath::Min(0.10*cd.nevents, 2*75000.), 0.);
    int train_n_events_counter = 0;
    bool first_time = true;
    for(int i = 0; i < cd.nevents; i++){
      chain->GetEntry(i);

      // cout << cut_formula->EvalInstance() << endl;
      if( cut_formula->EvalInstance() > 0 ){
        selected_events -= 1;
        train_n_events = TMath::Max(TMath::Min(0.10*selected_events, 2*75000.), 0.);
        continue;
      }
      // cout << "Fill" << endl;

      for(int i = 0; i < values_f.size(); i++) *(values_f[i]) = values.at(i)->EvalInstance();

      //                                     pb      ab
      *(values_f[0]) = (*(values_f[0])) * cd.xsec * lumi / cd.full_events_number; // weight
      if(first_time) cout << "tread(" << tread << ") " << cd.physic_name << " " << *(values_f[0]) << endl;
      first_time = false;

      if(not (i%TMath::Max(int(0.1*cd.nevents), 1))) cout << "tread(" << tread << ") " << cd.physic_name << " " << i << "/" << cd.nevents << endl;
      if( train_n_events_counter < train_n_events ){
        train->Fill();
        train_n_events_counter++;
        continue;
      }
      data->Fill();
    }

    train->Write();
    data->Write();
    outfile->ls();
    msg ( outfile->Get("events") );
    cout << "tread(" << tread << ") " << "<!done " << train->GetEntries() << "+" << data->GetEntries() << "/" << cd.nevents << endl;
    outfile->Close();
  }

  cout << "Done tread(" << tread << ")" << endl;
}



























