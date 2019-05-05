
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
  custom_variables["weight_BDT_0a_000"] = PlotVariable("weight_BDT_0a_000", -1, 1);
  custom_variables["weight_BDT_2a_000"] = PlotVariable("weight_BDT_2a_000", -1, 1);
  custom_variables["weight_BDT_4a_000"] = PlotVariable("weight_BDT_4a_000", -1, 1);
  custom_variables["weight_BDT_0b_000"] = PlotVariable("weight_BDT_0b_000", -1, 1);
  custom_variables["weight_BDT_2b_000"] = PlotVariable("weight_BDT_2b_000", -1, 1);
  custom_variables["weight_BDT_4b_000"] = PlotVariable("weight_BDT_4b_000", -1, 1);
  custom_variables["weight_BDT_0c_000"] = PlotVariable("weight_BDT_0c_000", -1, 1);
  custom_variables["weight_BDT_2c_000"] = PlotVariable("weight_BDT_2c_000", -1, 1);
  custom_variables["weight_BDT_4c_000"] = PlotVariable("weight_BDT_4c_000", -1, 1);
  custom_variables["sm_top_fat_jet_pt"] = PlotVariable("sm_top_fat_jet_pt", 0, 2000);
  custom_variables["fcnc_top_fat_jet_pt"] = PlotVariable("fcnc_top_fat_jet_pt", 0, 2000);
  custom_variables["top_jet_scalar"] = PlotVariable("top_jet_scalar", 0, 5000000);
  custom_variables["sm_tau_21"] = PlotVariable("sm_tau_21", 0, 1);
  custom_variables["sm_tau_31"] = PlotVariable("sm_tau_31", 0, 1);
  custom_variables["sm_tau_32"] = PlotVariable("sm_tau_32", 0, 1);
  custom_variables["fcnc_tau_21"] = PlotVariable("fcnc_tau_21", 0, 1);
  custom_variables["fcnc_tau_31"] = PlotVariable("fcnc_tau_31", 0, 1);
  custom_variables["fcnc_tau_32"] = PlotVariable("fcnc_tau_32", 0, 1);
  custom_variables["sm_top_sd_m"] = PlotVariable("sm_top_sd_m", 0, 300);
  custom_variables["fcnc_top_sd_m"] = PlotVariable("fcnc_top_sd_m", 0, 300);
  custom_variables["fcnc_leadin_mass"] = PlotVariable("fcnc_leadin_mass", 0, 300);
  custom_variables["fcnc_bH_mass"] = PlotVariable("fcnc_bH_mass", 0, 300);
  custom_variables["fcnc_bW_mass"] = PlotVariable("fcnc_bW_mass", 0, 300);
  custom_variables["sm_leadin_mass"] = PlotVariable("sm_leadin_mass", 0, 300);
  custom_variables["sm_bH_mass"] = PlotVariable("sm_bH_mass", 0, 300);
  custom_variables["sm_bW_mass"] = PlotVariable("sm_bW_mass", 0, 300);
  custom_variables["mass_disbalance"] = PlotVariable("mass_disbalance", 0, 1);
  custom_variables["H_x_fatjet"] = PlotVariable("H_x_fatjet", 0, 50000);
  custom_variables["W_x_fatjet"] = PlotVariable("W_x_fatjet", 0, 50000);
  custom_variables["H_pt"] = PlotVariable("H_pt", 0, 2000);
  custom_variables["W_pt"] = PlotVariable("W_pt", 0, 2000);
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
  TH1D hist_0 = TH1D((dataset->process_name + "_weight_BDT_0a_000").c_str(), "weight_BDT_0a_000", 100000, -1, 1);
  TH1D hist_1 = TH1D((dataset->process_name + "_weight_BDT_2a_000").c_str(), "weight_BDT_2a_000", 100000, -1, 1);
  TH1D hist_2 = TH1D((dataset->process_name + "_weight_BDT_4a_000").c_str(), "weight_BDT_4a_000", 100000, -1, 1);
  TH1D hist_3 = TH1D((dataset->process_name + "_weight_BDT_0b_000").c_str(), "weight_BDT_0b_000", 100000, -1, 1);
  TH1D hist_4 = TH1D((dataset->process_name + "_weight_BDT_2b_000").c_str(), "weight_BDT_2b_000", 100000, -1, 1);
  TH1D hist_5 = TH1D((dataset->process_name + "_weight_BDT_4b_000").c_str(), "weight_BDT_4b_000", 100000, -1, 1);
  TH1D hist_6 = TH1D((dataset->process_name + "_weight_BDT_0c_000").c_str(), "weight_BDT_0c_000", 100000, -1, 1);
  TH1D hist_7 = TH1D((dataset->process_name + "_weight_BDT_2c_000").c_str(), "weight_BDT_2c_000", 100000, -1, 1);
  TH1D hist_8 = TH1D((dataset->process_name + "_weight_BDT_4c_000").c_str(), "weight_BDT_4c_000", 100000, -1, 1);
  TH1D hist_9 = TH1D((dataset->process_name + "_sm_top_fat_jet_pt").c_str(), "sm_top_fat_jet_pt", 30, 0, 2000);
  TH1D hist_10 = TH1D((dataset->process_name + "_fcnc_top_fat_jet_pt").c_str(), "fcnc_top_fat_jet_pt", 30, 0, 2000);
  TH1D hist_11 = TH1D((dataset->process_name + "_top_jet_scalar").c_str(), "top_jet_scalar", 30, 0, 5000000);
  TH1D hist_12 = TH1D((dataset->process_name + "_sm_tau_21").c_str(), "sm_tau_21", 30, 0, 1);
  TH1D hist_13 = TH1D((dataset->process_name + "_sm_tau_31").c_str(), "sm_tau_31", 30, 0, 1);
  TH1D hist_14 = TH1D((dataset->process_name + "_sm_tau_32").c_str(), "sm_tau_32", 30, 0, 1);
  TH1D hist_15 = TH1D((dataset->process_name + "_fcnc_tau_21").c_str(), "fcnc_tau_21", 30, 0, 1);
  TH1D hist_16 = TH1D((dataset->process_name + "_fcnc_tau_31").c_str(), "fcnc_tau_31", 30, 0, 1);
  TH1D hist_17 = TH1D((dataset->process_name + "_fcnc_tau_32").c_str(), "fcnc_tau_32", 30, 0, 1);
  TH1D hist_18 = TH1D((dataset->process_name + "_sm_top_sd_m").c_str(), "sm_top_sd_m", 30, 0, 300);
  TH1D hist_19 = TH1D((dataset->process_name + "_fcnc_top_sd_m").c_str(), "fcnc_top_sd_m", 30, 0, 300);
  TH1D hist_20 = TH1D((dataset->process_name + "_fcnc_leadin_mass").c_str(), "fcnc_leadin_mass", 30, 0, 300);
  TH1D hist_21 = TH1D((dataset->process_name + "_fcnc_bH_mass").c_str(), "fcnc_bH_mass", 30, 0, 300);
  TH1D hist_22 = TH1D((dataset->process_name + "_fcnc_bW_mass").c_str(), "fcnc_bW_mass", 30, 0, 300);
  TH1D hist_23 = TH1D((dataset->process_name + "_sm_leadin_mass").c_str(), "sm_leadin_mass", 30, 0, 300);
  TH1D hist_24 = TH1D((dataset->process_name + "_sm_bH_mass").c_str(), "sm_bH_mass", 30, 0, 300);
  TH1D hist_25 = TH1D((dataset->process_name + "_sm_bW_mass").c_str(), "sm_bW_mass", 30, 0, 300);
  TH1D hist_26 = TH1D((dataset->process_name + "_mass_disbalance").c_str(), "mass_disbalance", 30, 0, 1);
  TH1D hist_27 = TH1D((dataset->process_name + "_H_x_fatjet").c_str(), "H_x_fatjet", 30, 0, 50000);
  TH1D hist_28 = TH1D((dataset->process_name + "_W_x_fatjet").c_str(), "W_x_fatjet", 30, 0, 50000);
  TH1D hist_29 = TH1D((dataset->process_name + "_H_pt").c_str(), "H_pt", 30, 0, 2000);
  TH1D hist_30 = TH1D((dataset->process_name + "_W_pt").c_str(), "W_pt", 30, 0, 2000);
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
    Double_t * v_weight_BDT_0a_000 = event.GetVar("weight_BDT_0a_000");
    Double_t * v_weight_BDT_2a_000 = event.GetVar("weight_BDT_2a_000");
    Double_t * v_weight_BDT_4a_000 = event.GetVar("weight_BDT_4a_000");
    Double_t * v_weight_BDT_0b_000 = event.GetVar("weight_BDT_0b_000");
    Double_t * v_weight_BDT_2b_000 = event.GetVar("weight_BDT_2b_000");
    Double_t * v_weight_BDT_4b_000 = event.GetVar("weight_BDT_4b_000");
    Double_t * v_weight_BDT_0c_000 = event.GetVar("weight_BDT_0c_000");
    Double_t * v_weight_BDT_2c_000 = event.GetVar("weight_BDT_2c_000");
    Double_t * v_weight_BDT_4c_000 = event.GetVar("weight_BDT_4c_000");
    Double_t * v_sm_top_fat_jet_pt = event.GetVar("sm_top_fat_jet_pt");
    Double_t * v_fcnc_top_fat_jet_pt = event.GetVar("fcnc_top_fat_jet_pt");
    Double_t * v_top_jet_scalar = event.GetVar("top_jet_scalar");
    Double_t * v_sm_tau_21 = event.GetVar("sm_tau_21");
    Double_t * v_sm_tau_31 = event.GetVar("sm_tau_31");
    Double_t * v_sm_tau_32 = event.GetVar("sm_tau_32");
    Double_t * v_fcnc_tau_21 = event.GetVar("fcnc_tau_21");
    Double_t * v_fcnc_tau_31 = event.GetVar("fcnc_tau_31");
    Double_t * v_fcnc_tau_32 = event.GetVar("fcnc_tau_32");
    Double_t * v_sm_top_sd_m = event.GetVar("sm_top_sd_m");
    Double_t * v_fcnc_top_sd_m = event.GetVar("fcnc_top_sd_m");
    Double_t * v_fcnc_leadin_mass = event.GetVar("fcnc_leadin_mass");
    Double_t * v_fcnc_bH_mass = event.GetVar("fcnc_bH_mass");
    Double_t * v_fcnc_bW_mass = event.GetVar("fcnc_bW_mass");
    Double_t * v_sm_leadin_mass = event.GetVar("sm_leadin_mass");
    Double_t * v_sm_bH_mass = event.GetVar("sm_bH_mass");
    Double_t * v_sm_bW_mass = event.GetVar("sm_bW_mass");
    Double_t * v_mass_disbalance = event.GetVar("mass_disbalance");
    Double_t * v_H_x_fatjet = event.GetVar("H_x_fatjet");
    Double_t * v_W_x_fatjet = event.GetVar("W_x_fatjet");
    Double_t * v_H_pt = event.GetVar("H_pt");
    Double_t * v_W_pt = event.GetVar("W_pt");
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
      hist_0.Fill( *v_weight_BDT_0a_000, xfactor);
      hist_1.Fill( *v_weight_BDT_2a_000, xfactor);
      hist_2.Fill( *v_weight_BDT_4a_000, xfactor);
      hist_3.Fill( *v_weight_BDT_0b_000, xfactor);
      hist_4.Fill( *v_weight_BDT_2b_000, xfactor);
      hist_5.Fill( *v_weight_BDT_4b_000, xfactor);
      hist_6.Fill( *v_weight_BDT_0c_000, xfactor);
      hist_7.Fill( *v_weight_BDT_2c_000, xfactor);
      hist_8.Fill( *v_weight_BDT_4c_000, xfactor);
      hist_9.Fill( *v_sm_top_fat_jet_pt, xfactor);
      hist_10.Fill( *v_fcnc_top_fat_jet_pt, xfactor);
      hist_11.Fill( *v_top_jet_scalar, xfactor);
      hist_12.Fill( *v_sm_tau_21, xfactor);
      hist_13.Fill( *v_sm_tau_31, xfactor);
      hist_14.Fill( *v_sm_tau_32, xfactor);
      hist_15.Fill( *v_fcnc_tau_21, xfactor);
      hist_16.Fill( *v_fcnc_tau_31, xfactor);
      hist_17.Fill( *v_fcnc_tau_32, xfactor);
      hist_18.Fill( *v_sm_top_sd_m, xfactor);
      hist_19.Fill( *v_fcnc_top_sd_m, xfactor);
      hist_20.Fill( *v_fcnc_leadin_mass, xfactor);
      hist_21.Fill( *v_fcnc_bH_mass, xfactor);
      hist_22.Fill( *v_fcnc_bW_mass, xfactor);
      hist_23.Fill( *v_sm_leadin_mass, xfactor);
      hist_24.Fill( *v_sm_bH_mass, xfactor);
      hist_25.Fill( *v_sm_bW_mass, xfactor);
      hist_26.Fill( *v_mass_disbalance, xfactor);
      hist_27.Fill( *v_H_x_fatjet, xfactor);
      hist_28.Fill( *v_W_x_fatjet, xfactor);
      hist_29.Fill( *v_H_pt, xfactor);
      hist_30.Fill( *v_W_pt, xfactor);
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














