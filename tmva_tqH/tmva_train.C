

#include "analyse_cfg.C"

struct Variable{
  Variable(){}
  Variable(string expression, string title="", string unit=""){
    this->expression = expression;
    this->title = title;
    this->unit  = unit;
  }

  string expression, title, unit;
  double xmin, xmax;
};

vector<Variable> get_variables_train(string mode){
  vector<string> answer;
  answer = {"log(sm_top_fat_jet_pt)", "log(fcnc_top_fat_jet_pt)", "log(top_jet_scalar)", 
                 "sm_tau_21", "sm_tau_31", "sm_tau_32", 
                 "fcnc_tau_21", "fcnc_tau_31", "fcnc_tau_32",
                 "sm_top_sd_m", "fcnc_top_sd_m",
                 "fcnc_leadin_mass", "fcnc_bH_mass", "fcnc_bW_mass",
                 "sm_leadin_mass", "sm_bH_mass", "sm_bW_mass",
                 "mass_disbalance",
                 "log(H_x_fatjet)", "log(W_x_fatjet)",
                 "log(H_pt)", "log(W_pt)" };

  vector<Variable> vanswer;
  for(auto s : answer){
    vanswer.push_back( Variable(s) );
  }

  return vanswer;
}

TTree * get_tree(string path, string file_name, string tree_name){
  TFile * file = TFile::Open( (path + "/" + file_name).c_str() );
  // file->ls();
  auto tree = (TTree*) file->Get(tree_name.c_str());
  // cout << file << " " << tree << endl;
  return (TTree*) file->Get(tree_name.c_str());
}

void tmva_train(){
  string input_dir = "./output/test_big_3/";
  string output_dir = "./output/test_big_3_tmva/";
  string submode = "test_0";
  string postfix = "_0";

  TFile* outputFile = TFile::Open( (output_dir + "/TMVA_" + submode + ".root").c_str(), "RECREATE" );
  TMVA::Factory *factory = new TMVA::Factory( "TMVA_" + submode + postfix, outputFile, "" );
  // TMVA::DataLoader *dataloader=new TMVA::DataLoader( ("TMVA_" + mode + "_" + to_string(try_index) + ".root").c_str() );

  factory->SetWeightExpression("weight");
  auto channels = get_datasets();
  double extra_weight = 1;
  for(auto channel : channels){
    auto origin = get_tree(input_dir, "H_" + channel->process_name + ".root",     "events");
    auto tree = get_tree(input_dir, "H_" + channel->process_name + "_split.root",     "train");
    auto tree_data = get_tree(input_dir, "H_" + channel->process_name + "_split.root",     "data");
    cout << origin << " " << tree << " " << tree_data << endl;
    if(not origin) continue;
    if(not tree) continue;
    if(not tree_data) continue;
    cout << channel->process_name << " " << tree ->GetEntries() << " " << tree_data->GetEntries() << " " << origin->GetEntries() << endl;
    if(tree->GetEntries() == 0) continue;

    if(channel->signal){
      // tree->Print();
      factory->AddSignalTree    (tree, extra_weight, TMVA::Types::kTraining);
      factory->AddSignalTree    (tree_data, extra_weight, TMVA::Types::kTesting);
    }
    else{
      factory->AddBackgroundTree(tree, extra_weight, TMVA::Types::kTraining);
      factory->AddBackgroundTree(tree_data, extra_weight, TMVA::Types::kTesting);
    }
  }

  auto variables = get_variables_train( submode.c_str() );
  for(auto var : variables){
    cout << "will use variable ... " << var.title << " " << var.expression << endl;
    // factory->AddVariable( var.c_str(), 'F' );
    factory->AddVariable( var.expression, var.title, var.unit, 'F' );
  }

  factory->PrepareTrainingAndTestTree("", 0, 0, 10000, 10000, "SplitMode=Random:!V:SplitSeed=100");
  
  factory->BookMethod( TMVA::Types::kBDT, "BDT_0a", "nCuts=100:MaxDepth=5:NTrees=100" );
  factory->BookMethod( TMVA::Types::kBDT, "BDT_1a", "nCuts=100:MaxDepth=5:NTrees=175" );
  factory->BookMethod( TMVA::Types::kBDT, "BDT_2a", "nCuts=100:MaxDepth=5:NTrees=200" );
  factory->BookMethod( TMVA::Types::kBDT, "BDT_3a", "nCuts=100:MaxDepth=5:NTrees=250" );
  factory->BookMethod( TMVA::Types::kBDT, "BDT_4a", "nCuts=100:MaxDepth=5:NTrees=500" );

  factory->BookMethod( TMVA::Types::kBDT, "BDT_0b", "nCuts=50:MaxDepth=5:NTrees=100" );
  factory->BookMethod( TMVA::Types::kBDT, "BDT_1b", "nCuts=150:MaxDepth=5:NTrees=175" );
  factory->BookMethod( TMVA::Types::kBDT, "BDT_2b", "nCuts=200:MaxDepth=5:NTrees=200" );
  factory->BookMethod( TMVA::Types::kBDT, "BDT_3b", "nCuts=300:MaxDepth=5:NTrees=250" );
  factory->BookMethod( TMVA::Types::kBDT, "BDT_4b", "nCuts=500:MaxDepth=5:NTrees=500" );

  factory->BookMethod( TMVA::Types::kBDT, "BDT_0c", "nCuts=50:MaxDepth=5:NTrees=200" );
  factory->BookMethod( TMVA::Types::kBDT, "BDT_1c", "nCuts=150:MaxDepth=5:NTrees=200" );
  factory->BookMethod( TMVA::Types::kBDT, "BDT_2c", "nCuts=200:MaxDepth=5:NTrees=200" );
  factory->BookMethod( TMVA::Types::kBDT, "BDT_3c", "nCuts=300:MaxDepth=5:NTrees=200" );
  factory->BookMethod( TMVA::Types::kBDT, "BDT_4c", "nCuts=500:MaxDepth=5:NTrees=200" );

  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();
}



