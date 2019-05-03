
// mix_2017_25ns_WinterMC_PUScenarioV1_PoissonOOTPU_cfi

#include "tmva_prepare.C"

/*
    "log(ptag_pfjets08_pt)",
    "log(btag_pfjets08_pt)", 

    "log(photon_pt)", 

    "ptag_pfjets08_tau21", V
    "btag_pfjets08_tau32", V
    "btag_pfjets08_tau21", V

    "btag_pfjets08_softDroppedJet_m", V
    "ptag_pfjets08_softDroppedJet_m", V

 
    "log(bjet_x_ptag_pfjets08)",
    "log(photon_x_ptag_pfjets08)",

    "BestTopMass_jet_softDroppedJet_m", 
    "SecondTopMass_jet_softDroppedJet_m", 
*/










vector<Variable> get_variables_train(string mode){
  vector<string> answer;
  answer = {
    "ptag_pfjets08_softDroppedJet_m", 
    "btag_pfjets08_softDroppedJet_m",

    "log(ptag_pfjets08_pt)",
    "log(btag_pfjets08_pt)",
    "log(photon_pt)", 

    "ptag_pfjets08_tau21",
    "btag_pfjets08_tau32", 
    "btag_pfjets08_tau21",

    "log(bjet_x_ptag_pfjets08)",
    "log(photon_x_ptag_pfjets08)",

    "BestTopMass_jet_softDroppedJet_m", 
    "SecondTopMass_jet_softDroppedJet_m"
  };

/*
  answer = {
    // photon tag
    "ptag_pfjets08_softDroppedJet_m", "log(ptag_pfjets08_pt)",
    // "ptag_pfjets04_softDroppedJet_m", // "log(ptag_pfjets04_pt)",  // tune 1
    // "ptag_pfjets04_eta - ptag_pfjets08_eta",  // tune 2
    "log(photon_pt)", 
    "dR_Photon_ptag_pfjets08",
    //"dPhi_Photon_ptag_pfjets04", "photon_eta - ptag_pfjets04_eta", // tune 1
    "ptag_pfjets08_tau21", // "ptag_bestJet_tau31", 
    //"ptag_pfjets04_tau21", // "ptag_pfjets08_tau31", 
    "log(photon_x_ptag_pfjets08)",
    //"log(photon_x_ptag_pfjets04)",
    //"log(photon_relIso)",
    // b-jet tag
    "BestTopMass_jet_softDroppedJet_m", "SecondTopMass_jet_softDroppedJet_m", 
                                        //"log(abs(BestTopMass_jet_pt-SecondTopMass_jet_pt))", 
                                        //"BestTopMass_jet_eta - SecondTopMass_jet_eta",

    "btag_pfjets08_softDroppedJet_m", "log(btag_pfjets08_pt)", 
    "btag_pfjets08_tau32", "btag_pfjets08_tau21",
    //"log(lepton_x_btag_pfjets08)",
     // "dPhi_bjet_btag_pfjets08", "btag_pfjets04_eta - btag_pfjets08_eta",
    //"dR_bjet_btag_pfjets08",
     // "dR_lepton_btag_pfjets08", // tune 1
    //"log(lepton_relIso)", // tune 3
    //"lepton_relIso", // tune 3
    // kinematic
    //"dPhi_bjet_ptag_pfjets08", "btag_pfjets04_eta - ptag_pfjets08_eta",
    "dR_bjet_ptag_pfjets08",
    // "dPhi_Photon_btag_pfjets08", "photon_eta - btag_pfjets08_eta", // tune 1

    "log(  bjet_x_ptag_pfjets08)",
    //"log(lepton_x_ptag_pfjets08)", // tune 1
    //"log(photon_x_btag_pfjets08)", // tune 1
  };
*/

  if(mode == "calo"){
  }

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

void tmva_train(string input_dir, string output_dir, string submode, string postfix){

  TFile* outputFile = TFile::Open( (output_dir + "/TMVA_" + submode + ".root").c_str(), "RECREATE" );
  TMVA::Factory *factory = new TMVA::Factory( "TMVA_" + submode + postfix, outputFile, "" );
  // TMVA::DataLoader *dataloader=new TMVA::DataLoader( ("TMVA_" + mode + "_" + to_string(try_index) + ".root").c_str() );

  factory->SetWeightExpression("weight");
  auto channels = get_channals();
  double extra_weight = 1;
  for(auto channel : channels){
    auto origin = get_tree(input_dir, channel.physic_name + ".root",     "ttree");
    auto tree = get_tree(input_dir, channel.physic_name + "_split.root",     "train");
    auto tree_data = get_tree(input_dir, channel.physic_name + "_split.root",     "data");
    cout << channel.physic_name << " " << tree ->GetEntries() << " " << tree_data->GetEntries() << " " << origin->GetEntries() << endl;
    if(tree->GetEntries() == 0) continue;

    if(channel.signal){
      if(channel.physic_name != "mgp8_pp_tt_aut" and channel.physic_name != "mgp8_pp_tt_aut_cut500") continue;
    }
    if(channel.signal){
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

//factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLP", options_map.find( try_index )->second.c_str() );
  factory->PrepareTrainingAndTestTree("", 0, 0, 10000, 10000, "SplitMode=Random:!V:SplitSeed=100");
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_0", "nCuts=100:MaxDepth=5:NTrees=40" );
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_1", "nCuts=100:MaxDepth=5:NTrees=75" );

  //factory->BookMethod( TMVA::Types::kBDT, "BDT_0", "nCuts=100:MaxDepth=5:NTrees=100" );
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_1", "nCuts=100:MaxDepth=5:NTrees=125" );
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_2", "nCuts=100:MaxDepth=5:NTrees=150" );
  factory->BookMethod( TMVA::Types::kBDT, "BDT_3", "nCuts=100:MaxDepth=5:NTrees=175" );
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_4", "nCuts=100:MaxDepth=5:NTrees=200" );
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_5", "nCuts=100:MaxDepth=5:NTrees=250" );
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_6", "nCuts=100:MaxDepth=5:NTrees=500" );

  //factory->BookMethod( TMVA::Types::kBDT, "BDT_3", "nCuts=100:MaxDepth=5:NTrees=250" );
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_4", "nCuts=100:MaxDepth=5:NTrees=500" );
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_5", "nCuts=100:MaxDepth=5:NTrees=1000" );
  // factory->BookMethod( TMVA::Types::kBDT, "BDT_3", "nCuts=150:MaxDepth=5:NTrees=1000" );
  // factory->BookMethod( TMVA::Types::kBDT, "BDT_4", "nCuts=200:MaxDepth=5:NTrees=1000" );


  //factory->BookMethod( TMVA::Types::kBDT, "BDT_1", "nCuts=100:MaxDepth=25:NTrees=100" );
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_2", "SeparationType=CrossEntropy:nCuts=100:MaxDepth=25:NTrees=100" );
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_3", "SeparationType=SDivSqrtSPlusB:nCuts=100:MaxDepth=25:NTrees=100" );
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_3", "SeparationType=SDivSqrtSPlusB:nCuts=25:MaxDepth=5:NTrees=1000" );
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_4", "SeparationType=SDivSqrtSPlusB:nCuts=25:MaxDepth=5:NTrees=1000:AdaBoostBeta=0.75" );
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_5", "SeparationType=SDivSqrtSPlusB:nCuts=25:MaxDepth=5:NTrees=1000:AdaBoostBeta=0.25" );
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_6", "SeparationType=SDivSqrtSPlusB:nCuts=25:MaxDepth=5:NTrees=1000:MinNodeSize=0.10" );
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_7", "SeparationType=SDivSqrtSPlusB:nCuts=25:MaxDepth=5:NTrees=1000:MinNodeSize=0.025" );
  //factory->BookMethod( TMVA::Types::kBDT, "BDT_11","BoostType=Grad:nCuts=25:SeparationType=SDivSqrtSPlusB:MaxDepth=5:NTrees=1000:Shrinkage=0.30" );

  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();
}


/*

Raw limits 6.13725e-09 8.23927e-09 1.14346e-08 1.62006e-08 2.23854e-08
Br limits 9.15807e-08 1.22947e-07 1.70628e-07 2.41747e-07 3.34037e-07
kappa limits 0.000462573 0.000535966 0.000631399 0.000751551 0.000883437

*/



