
#include "analyse_cfg.C"

// python -m cogapp.__main__ -o plot_hists.C plot_hists_cog.C; root -l -b -q plot_hists.C 

class PlotVariable{
  public:
  PlotVariable(){}
  PlotVariable(string key, double min, double max){
    key = key;
    min = min;
    max = max;
  }

  string key;
  double min, max;
};

map<string, PlotVariable> get_variables(){
  map<string, PlotVariable> custom_variables;

  /*[[[cog
    from mRootCOG import *
    from mRootCOGAnalyser import *
    from AnalyseHEPPY import *

    variables = [PlotVariable("weight_BDT_0a_000", -1, 1, 100000),
                 PlotVariable("weight_BDT_2a_000", -1, 1, 100000) ,
                 PlotVariable("weight_BDT_4a_000", -1, 1, 100000) ,
                 PlotVariable("weight_BDT_0b_000", -1, 1, 100000),
                 PlotVariable("weight_BDT_2b_000", -1, 1, 100000),
                 PlotVariable("weight_BDT_4b_000", -1, 1, 100000),
                 PlotVariable("weight_BDT_0c_000", -1, 1, 100000),
                 PlotVariable("weight_BDT_2c_000", -1, 1, 100000),
                 PlotVariable("weight_BDT_4c_000", -1, 1, 100000),
                 PlotVariable("sm_top_fat_jet_pt", 0, 2000),
                 PlotVariable("fcnc_top_fat_jet_pt", 0, 2000),
                 PlotVariable("top_jet_scalar", 0, 5000000),
                 PlotVariable("sm_tau_21", 0, 1),
                 PlotVariable("sm_tau_31", 0, 1),
                 PlotVariable("sm_tau_32", 0, 1),
                 PlotVariable("fcnc_tau_21", 0, 1),
                 PlotVariable("fcnc_tau_31", 0, 1),
                 PlotVariable("fcnc_tau_32", 0, 1),
                 PlotVariable("sm_top_sd_m", 0, 300),
                 PlotVariable("fcnc_top_sd_m", 0, 300),
                 PlotVariable("fcnc_leadin_mass", 0, 300),
                 PlotVariable("fcnc_bH_mass", 0, 300),
                 PlotVariable("fcnc_bW_mass", 0, 300),
                 PlotVariable("sm_leadin_mass", 0, 300),
                 PlotVariable("sm_bH_mass", 0, 300),
                 PlotVariable("sm_bW_mass", 0, 300),
                 PlotVariable("mass_disbalance", 0, 1),
                 PlotVariable("H_x_fatjet", 0, 50000),
                 PlotVariable("W_x_fatjet", 0, 50000),
                 PlotVariable("H_pt", 0, 2000),
                 PlotVariable("W_pt", 0, 2000),
    ]
    
    for var in variables:
      cog.outl( 'custom_variables["' + var.key + '"] = PlotVariable("' + var.key + '", ' + str(var.xmin) + ', ' + str(var.xmax) +');')
  ]]]*/
  //[[[end]]]

  return custom_variables;
};

int plot_from_file(DataSet * dataset, string input_file, string output_file_name, map<string, PlotVariable> * custom_variables){

  TFile * output_file = TFile::Open(output_file_name.c_str(), "RECREATE");
  /*[[[cog
    for var in variables :
      if var.frozen : continue
      name = "(dataset->process_name + \"" + "_" + var.key + "\").c_str()"
      title = "\"" + var.key + "\""
      var.hist_name = cpp_TH1(name, title, var.nbins, var.xmin, var.xmax, type="D")
  ]]]*/
  //[[[end]]]

  TFile * file = TFile::Open(input_file.c_str(), "READ");
  TTree * train_tree = nullptr;

  mRoot::EventReader <Double_t> event;
  train_tree = (TTree*)file->Get("train");
  event.Init( file, "data" );

    /*[[[cog
      for var in variables :
        # if var.frozen : continue
        string = "Double_t * v_" + var.key + " = event.GetVar(\"" + var.key + "\");" ;
        cog.outl( string )

    ]]]*/
    //[[[end]]]

  // reweight due to train
  int nevents_train = 0;
  if(train_tree) nevents_train = train_tree->GetEntries();
  int nevents = event.tree->GetEntries();
  double train_reweight_factor = double(nevents + nevents_train) / nevents;

  Double_t *weight;
  weight = event.GetVar("weight");
  double lumi = 30 * 1000 * 1000;
  double xfactor;

  double extra_weight = 1.0;
  if( dataset->signal ){
      // extra_weight = 11.82 * 2.0 * 2.0 * 0.428 * pow(0.001, 2) / (3069 / 10. * 1.0 * 1.0);
      extra_weight = 0.01;
  }

  for(int i = 0; i < nevents; i++){
      if(not (i%TMath::Max(int(0.05*nevents), 1))) cout << input_file << " " << i << "/" << nevents << endl;
      event.tree->GetEntry(i);
    
      xfactor = (*weight) * lumi * train_reweight_factor * extra_weight;

      /*[[[cog
        for var in variables :
          if var.frozen : continue
          string = var.hist_name + ".Fill( *v_" + var.key + ", xfactor);"
          cog.outl( string )
      ]]]*/
      //[[[end]]]

      //if(i > 1000) break;
  }

  output_file->cd();
  output_file->Write();
  output_file->Close();

  file->Close();

  return 0;
}

struct plot_from_file_args{
  string output_file_name;
  string input_file_name;
  DataSet * dataset;
  map<string, PlotVariable> * custom_variables;
};

void * plot_from_file_wrapper(void * a){
  plot_from_file_args * args = (plot_from_file_args*) a; 
  cout << "Start with " << args->input_file_name << endl;
  plot_from_file(args->dataset, args->input_file_name, args->output_file_name, args->custom_variables);
  cout << "Done with "  << args->input_file_name << endl;
  // TThread::Exit(0);
  return 0;
}

int plot_hists(){
  vector<DataSet*> datasets = get_datasets( false );

  map<string, PlotVariable> variables = get_variables();

  vector<TThread*> threads;
  for(auto dataset : datasets){
    plot_from_file_args * args   = new plot_from_file_args();
    args->output_file_name = "./output/test_big_3_hists/" + dataset->process_name + "_hists.root";
    args->input_file_name  = "./output/test_big_3/H_" + dataset->process_name + "_split.root";
    args->dataset = dataset;
    args->custom_variables = & variables;
    TThread* new_thread = new TThread(dataset->process_name.c_str(), &plot_from_file_wrapper, (void*) args);
    threads.push_back( new_thread );
  }

  threads_care( threads, 10 );
  return 0;
}














