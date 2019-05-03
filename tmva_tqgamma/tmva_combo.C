
#include "tmva_train.C"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootThread.cpp"


void tmva_add(string input_file, string tmva_input, string submode, string TMVA_NAME="BDT", string postfix_in_tree="_000"){
  // setup reader
  TMVA::Reader* tmva_reader = new TMVA::Reader( "<options>" );
  auto variables = get_variables_train( submode );
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

  // vector<TTree*> trees = {(TTree*)f->Get("data"), (TTree*)f->Get("train")};
  vector<TTree*> trees = {(TTree*)f->Get("data")};
  for(auto tree : trees){
    double tmva_value;
    auto br = tree->Branch(("weight_" + submode + "_" + TMVA_NAME + postfix_in_tree).c_str(), &tmva_value);

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
  tmva_add(args->input_file, args->tmva_input, args->submode, args->TMVA_NAME, args->postfix_in_tree);
  cout << "Done with " << args->input_file << endl;
  // TThread::Exit(0);
  return 0;
}

void tmva_combo(string samples_path, string tmva_path, string postfix, string mode, string TMVA_NAME="BDT", string postfix_in_tree="_000"){

  auto channels = get_channals( );

/*
    for(auto channel : channels){
      string file = samples_path + "/" +  channel.physic_name + "_split.root";
      // tmva_add(file, tmva_path + "/" + "TMVA_p" + postfix + "_BDT.weights.xml", "p");
      // tmva_add(file, tmva_path + "/" + "TMVA_b" + postfix + "_BDT.weights.xml", "b");
      // tmva_add(file, tmva_path + "/" + "TMVA_k" + postfix + "_BDT.weights.xml", "k");
      tmva_add(file, tmva_path + "/" + "TMVA_" + mode + postfix + "_" + TMVA_NAME + ".weights.xml", mode, TMVA_NAME, postfix_in_tree);
    }
*/

  vector<TThread*> threads;
  for(auto channel : channels){
    string file = samples_path + "/" +  channel.physic_name + "_split.root";
    tmva_add_args * args = new tmva_add_args();
    args->input_file       = samples_path + "/" +  channel.physic_name + "_split.root";
    args->tmva_input       = tmva_path + "/" + "TMVA_" + mode + postfix + "_" + TMVA_NAME + ".weights.xml";
    args->submode          = mode;
    args->TMVA_NAME        = TMVA_NAME;
    args->postfix_in_tree  = postfix_in_tree;
    TThread* new_thread = new TThread(channel.physic_name.c_str(), &tmva_add_wrapper, (void*) args);
    threads.push_back( new_thread );
  }

  threads_care( threads, 10 );
}



