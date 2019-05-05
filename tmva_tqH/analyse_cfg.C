
#include "mRoot.cpp"
#include "mRootAnalyser.cpp"
#include "mRootAnalyseAlgo.cpp"
#include "mRootThread.cpp"

using namespace mRoot;

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

DataSet* get_dataset(string process_name, string latex_name, string short_name, double xsec, string path, bool calc_weights, bool signal){
  DataSet* answer = new DataSet(process_name, latex_name, short_name);
  answer->xsec = xsec;
  answer->signal = signal;

  string fpath = path + "/" + process_name + "/heppy.FCChhAnalyses.FCChh.FCNC_tqH.TreeProducer.TreeProducer_1/tree.root";
  string wpath = path + "/" + process_name + "/heppy.FCChhAnalyses.FCChh.FCNC_tqH.TreeProducer.WeightTreeProducer_1/weight_tree.root";
  string log_path = path + "/" + process_name + "/heppy.FCChhAnalyses.FCChh.FCNC_tqH_old.selection.Selection_cuts/cut_flow.txt";

  answer->AddFile( fpath );

  std::ifstream log_file( log_path.c_str() );
  std::string line;
  while (std::getline(log_file, line)){
    if(line.find("All events") == std::string::npos) continue;
    int pos = line.find("All events");
    double number = get_number( line.substr( pos + 10 ) );
    answer->nevents += number;
    break;
  }

  if(calc_weights){
    TFile * f = TFile::Open( fpath.c_str() );
    TTree * tree = (TTree*)gDirectory->Get("events");
    if(not tree) msg("no tree !!!");
    answer->nevents = tree->GetEntries();
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
    cout << process_name << " " << w_events << " " << weight_sum << " " << answer->nevents << endl;
    w->Close();
    answer->weight_sum = weight_sum;
  }

  return answer;
}

vector<DataSet*> get_datasets(bool calc_weights = true){

  string wpath = "/afs/cern.ch/work/p/pmandrik/fcc_100TeV/4_analyser/heppy/OUTPUT/test_big_0";
         wpath = "/afs/cern.ch/work/p/pmandrik/fcc_100TeV/4_analyser/heppy/OUTPUT/test_n";
         wpath = "/afs/cern.ch/work/p/pmandrik/fcc_100TeV/4_analyser/heppy/OUTPUT/test_fnal";
         wpath = "/afs/cern.ch/work/p/pmandrik/fcc_100TeV/4_analyser/heppy/OUTPUT/test_big_2";

///afs/cern.ch/work/p/pmandrik/fcc_100TeV/4_analyser/heppy/OUTPUT/test_big_2/mgp8_pp_tt_tcH_pt500/heppy.FCChhAnalyses.FCChh.FCNC_tqH_old.TreeProducer.TreeProducer_1/tree.root

  vector<DataSet*> answer = {
      get_dataset("mgp8_pp_tt_tuH_pt500",                 "t #rightarrow uH",       "tuH",          1.,       wpath,   calc_weights, true),
      get_dataset("mgp8_pp_tt_tcH_pt500",                 "t #rightarrow cH",       "tcH",          1.,       wpath,   calc_weights, true),
      // ttbar
      get_dataset("mgp8_pp_tt012j_5f_HT_0_600",           "t#bar{t}",               "ttbar",        3.207*10000.*1.74*0.507,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_tt012j_5f_HT_600_1200",        "t#bar{t}",               "ttbar",        8883*1.74*0.352,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_tt012j_5f_HT_1200_2100",       "t#bar{t}",               "ttbar",        1737*1.74*0.328,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_tt012j_5f_HT_2100_3400",       "t#bar{t}",               "ttbar",        284.3*1.74*0.315,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_tt012j_5f_HT_3400_5300",       "t#bar{t}",               "ttbar",        44.91*1.74*0.306,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_tt012j_5f_HT_5300_8100",       "t#bar{t}",               "ttbar",        6.484*1.74*0.298,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_tt012j_5f_HT_8100_15000",      "t#bar{t}",               "ttbar",        0.8583*1.74*0.294,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_tt012j_5f_HT_15000_25000",     "t#bar{t}",               "ttbar",        0.0219*1.74*0.296,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_tt012j_5f_HT_25000_35000",     "t#bar{t}",               "ttbar",        0.0004247*1.74*0.307,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_tt012j_5f_HT_35000_100000",    "t#bar{t}",               "ttbar",        1.459/100000.*1.74*0.323,       wpath,   calc_weights, false),
      // W + jets
      get_dataset("mgp8_pp_w0123j_4f_HT_0_150",           "W+jets",               "Wjets",        1.478*1000000.*1.20* 0.69,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_w0123j_4f_HT_150_300",         "W+jets",               "Wjets",        8.377*10000.*1.20* 0.256,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_w0123j_4f_HT_300_500",         "W+jets",               "Wjets",        2.493*10000.*1.20* 0.263,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_w0123j_4f_HT_500_1000",        "W+jets",               "Wjets",        1.037*10000.*1.20* 0.262,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_w0123j_4f_HT_1000_2000",       "W+jets",               "Wjets",        1917*1.20* 0.255,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_w0123j_4f_HT_2000_5000",       "W+jets",               "Wjets",        273.7*1.20* 0.245,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_w0123j_4f_HT_5000_100000",     "W+jets",               "Wjets",        11.11*1.20* 0.231,       wpath,   calc_weights, false),
      // Z + jets
      get_dataset("mgp8_pp_z0123j_4f_HT_0_150",           "Z+jets",               "Zjets",        465800    *1.20 * 0.713,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_z0123j_4f_HT_150_300",         "Z+jets",               "Zjets",        29440    *1.20 * 0.261,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_z0123j_4f_HT_300_500",         "Z+jets",               "Zjets",        8958    *1.20 * 0.27,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_z0123j_4f_HT_500_1000",        "Z+jets",               "Zjets",        3756    *1.20* 0.267,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_z0123j_4f_HT_1000_2000",       "Z+jets",               "Zjets",        703.8  *1.20 * 0.259,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_z0123j_4f_HT_2000_5000",       "Z+jets",               "Zjets",        102.3  *1.20* 0.248,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_z0123j_4f_HT_5000_100000",     "Z+jets",               "Zjets",        4.196*1.20* 0.234,       wpath,   calc_weights, false),
      // tt +Z/W
      get_dataset("mgp8_pp_ttz_5f",           "other",               "other",        38.05*1.68,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_ttw_5f",           "other",               "other",        6.545*2.5,       wpath,   calc_weights, false),
      // tt+h
      get_dataset("mgp8_pp_tth01j_5f_HT_0_1100",           "other",               "other",        36.94*1.22*0.612,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_tth01j_5f_HT_1100_2700",        "other",               "other",        7.466*1.22*0.613,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_tth01j_5f_HT_2700_4900",        "other",               "other",        0.4224*1.22*0.636,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_tth01j_5f_HT_4900_8100",        "other",               "other",        0.0336*1.22*0.642,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_tth01j_5f_HT_8100_100000",      "other",               "other",        0.002924*1.22*0.644,       wpath,   calc_weights, false),
      // single top
      get_dataset("mgp8_pp_t123j_5f",           "other",               "other",        7524*2.16*0.288,       wpath,   calc_weights, false),
      // QCD
      get_dataset("mgp8_pp_jj012j_5f_HT_0_500",           "Multijet",               "qcd",        6.517*1000000000.*1.0*0.141,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_jj012j_5f_HT_500_1000",        "Multijet",               "qcd",        1.642*10000000.*0.092,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_jj012j_5f_HT_2000_4000",       "Multijet",               "qcd",        1.32*100000.*0.057,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_jj012j_5f_HT_4000_7200",       "Multijet",               "qcd",        7316*	0.048,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_jj012j_5f_HT_7200_15000",      "Multijet",               "qcd",        474.9*0.043,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_jj012j_5f_HT_15000_25000",     "Multijet",               "qcd",        7.349*0.041,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_jj012j_5f_HT_25000_35000",     "Multijet",               "qcd",        0.1759*0.041,       wpath,   calc_weights, false),
      get_dataset("mgp8_pp_jj012j_5f_HT_35000_100000",    "Multijet",               "qcd",        0.007654*0.043,       wpath,   calc_weights, false),
  };

  
  return answer;
}






