

// #include "analyse_cfg.C"
#include "tmva_train.C"

void tmva_add(string input_file, string tmva_input, string TMVA_NAME="BDT", string postfix_in_tree="_000"){
  // setup reader
  TMVA::Reader* tmva_reader = new TMVA::Reader( "<options>" );
  auto variables = get_variables_train("");
  vector<float*> values_f;
  for(auto var : variables){
    string vname = var.expression;
    values_f.push_back( new float );
    tmva_reader->AddVariable( vname.c_str(), (values_f.at( values_f.size() - 1 )) );
  }

  auto tmva_method = tmva_reader->BookMVA( TMVA_NAME.c_str(), tmva_input.c_str() );

  cout << tmva_method << endl;
  cout << tmva_method->GetMvaValue() << endl;
  cout << tmva_reader->GetMVAError() << endl;

  // setup file to update 
  TFile *f = new TFile(input_file.c_str(),"update");

  cout << "Input file to update " << f << endl;

  // vector<TTree*> trees = {(TTree*)f->Get("data"), (TTree*)f->Get("train")};
  vector<TTree*> trees = {(TTree*)f->Get("data")};
  for(auto tree : trees){
    cout << "Tree to update " << tree << endl;
    double tmva_value;
    auto br = tree->Branch(("weight_" + TMVA_NAME + postfix_in_tree).c_str(), &tmva_value);

    vector<TTreeFormula*> values;
    for(int i = 0; i < variables.size(); i++)
      values.push_back( new TTreeFormula(variables.at(i).expression.c_str(), variables.at(i).expression.c_str(), tree) );

    for(int i = 0; i < tree->GetEntries(); i++){
      tree->GetEntry(i); 
      for(int i = 0; i < values_f.size(); i++) *(values_f[i]) = values.at(i)->EvalInstance();
      tmva_value = tmva_method->GetMvaValue(); 
      br->Fill();
    }

    tree->Print();
    tree->Write();
  }
  f->Close();
}

struct tmva_add_args{
  string input_file;
  string tmva_input;
  string submode;
  string TMVA_NAME;
  string postfix_in_tree;
};

void * tmva_add_wrapper(void * a){
  tmva_add_args * args = (tmva_add_args*) a; 
  cout << "Start with " << args->input_file << endl;
  tmva_add(args->input_file, args->tmva_input, args->TMVA_NAME, args->postfix_in_tree);
  cout << "Done with " << args->input_file << endl;
  // TThread::Exit(0);
  return 0;
}

void combo(string TMVA_NAME="BDT_0a", string postfix_in_tree="_000"){

  string samples_path = "./output/test_big_3";
  string tmva_path    = "./weights";
  string tmva_file_name = "TMVA_test_0_0_";

  auto channels = get_datasets( false );

  vector<TThread*> threads;
  for(auto channel : channels){
    tmva_add_args * args = new tmva_add_args();
    args->input_file       = samples_path + "/" +  "H_" + channel->process_name + "_split.root";
    args->tmva_input       = tmva_path + "/" + tmva_file_name + TMVA_NAME + ".weights.xml";
    args->TMVA_NAME        = TMVA_NAME;
    args->postfix_in_tree  = postfix_in_tree;
    TThread* new_thread = new TThread(channel->process_name.c_str(), &tmva_add_wrapper, (void*) args);
    threads.push_back( new_thread );
  }

  threads_care( threads, 10 );
}







