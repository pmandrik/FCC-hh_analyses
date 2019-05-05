
#include "analyse_cfg.C"

string OUTPUT_PATH = "./output/test_big_3/";
float max_events_to_analyse =  99999999;

void select_single_dataset(void * d){
  DataSet * dataset = (DataSet *)d;
  cout << "Begin with " << dataset->process_name << endl;

  string file_name = dataset->files.at(0);
  string out_name = OUTPUT_PATH + "H_" + dataset->process_name + ".root";

  mRoot::EventReader <Double_t> * event = new mRoot::EventReader <Double_t>();
  TFile * file = TFile::Open( file_name.c_str() );
  event->Init( file, "events" );
  int nevents = event->tree->GetEntries();

  TFile * file_out = new TFile( out_name.c_str(), "RECREATE");
  file_out->cd();
  TTree * tree_out = new TTree("events", "events");

  /*[[[cog
    from mRootCOGAnalyser import *
    from AnalyseHEPPY import *

    tlvs = []
    vars = ["met_pt"]
    vecs = []

    for vec in vecs:
      tlvs += [ vec ]
      tlv_parts = ["e", "pt", "eta", "phi", "m"]
      for part in tlv_parts:
        vars += [ vec + "_" + part ]

    collections_sizes = [10,                  5,               8]
    jet_collections   = ["pfjets02", "pfjets08", "pfjets04_btag"]    
    
    for jet, size in zip( jet_collections, collections_sizes):
      v, t = get_jets( jet, size )
      vars += v
      tlvs += t

    analyser = EventReaderAnalyser()
    analyser.variables = vars
    analyser.tlvs      = tlvs

    analyser.define_vars()
    analyser.define_tlvs()

    # sencetive variables:
    plotter = Plotter()
    set_analyse_hists( plotter )
    plotter.init_hists()


    # VARS TO SAVE
    for var in vars_to_save:
      line = "double " + var + "; tree_out->Branch(\"" + var + "\", &" + var +");"
      cog.outl( line )
  ]]]*/
  //[[[end]]]

  file->cd();
  nevents = TMath::Min((int)max_events_to_analyse, (int)nevents);
  for(int i = 0; i < nevents; i++){
    event->tree->GetEntry(i);
    if(not (i%TMath::Max(int(0.05*nevents), 1))) cout << out_name << " " << i << "/" << nevents << endl;

    weight = dataset->xsec / dataset->weight_sum;
    /*[[[cog
      analyser.set_tlvs()

      for collection, size in zip(jet_collections, collections_sizes):
        type = "TLorentzVector"
        parts = [ collection + "_" + str(i) for i in xrange(size) ]
        mRootCOG.cpp_vector(collection + "_v" , type, parts)

        parts = [ collection + "_" + str(i) + "_softDroppedJet" for i in xrange(size) ]
        mRootCOG.cpp_vector(collection + "_softDroppedJet_v" , type, parts)

        type = "double*"
        for var in part_vars:
          parts = [ collection + "_" + str(i) + "_" + var for i in xrange(size) ]
          mRootCOG.cpp_vector(collection + "_" + var + "_v", type, parts)
    ]]]*/
    //[[[end]]]

    // variables to save
    *pfjets02_N = TMath::Min(10., *pfjets02_N);
    // *pfjets04_N = TMath::Min(10., *pfjets04_N);
    *pfjets08_N = TMath::Min(5., *pfjets08_N);
    *pfjets04_btag_N = TMath::Min(8., *pfjets04_btag_N);

    pfjets02_v.erase(pfjets02_v.begin()           + *pfjets02_N, pfjets02_v.end() );
    pfjets08_v.erase(pfjets08_v.begin()           + *pfjets08_N, pfjets08_v.end() );
    pfjets04_btag_v.erase(pfjets04_btag_v.begin() + *pfjets04_btag_N, pfjets04_btag_v.end() );
    
    // 0) study variables                      - 1 days
    /*
        sm_top_fat_jet   = leading sinly b-tagged jet
        fcnc_top_fat_jet = leading double b-tagged jet
        tau
    */

    vector< vector<int> > pfjets08_04tags = {};
    vector< vector<int> > pfjets08_02tags = {};
    int sm_top_fat_jet_index = -1, fcnc_top_fat_jet_index = -1;
    for(int i = 0; i < *pfjets08_N; i++){
      TLorentzVector tlv_08 = pfjets08_v.at( i );

      vector<int> taggs_04 = {};
      for(int j = 0; j < *pfjets04_btag_N; j++){
        TLorentzVector tlv_4 = pfjets04_btag_v.at(j);
        if( tlv_08.DeltaR( tlv_4 ) < 0.8 ) 
          taggs_04.push_back( j );
      }
      vector<int> taggs_02 = {};
      for(int j = 0; j < *pfjets02_N; j++){
        TLorentzVector tlv_2 = pfjets02_v.at(j);
        if( tlv_08.DeltaR( tlv_2 ) < 0.8 ) 
          taggs_02.push_back( j );
      }

      pfjets08_04tags.push_back( taggs_04 );
      pfjets08_02tags.push_back( taggs_02 );
      //cout << i << " " << taggs_04.size() << endl;
      if( taggs_04.size() == 1 and sm_top_fat_jet_index   == -1) sm_top_fat_jet_index   = i;
      if( taggs_04.size() >= 2 and fcnc_top_fat_jet_index == -1) fcnc_top_fat_jet_index = i;
    }

    // cout << sm_top_fat_jet_index << " " << fcnc_top_fat_jet_index << endl;
    if(sm_top_fat_jet_index == -1 or fcnc_top_fat_jet_index == -1) continue;
    // continue;
    TLorentzVector sm_top_fat_jet_v    = pfjets08_v.at( sm_top_fat_jet_index ) ;
    TLorentzVector fcnc_top_fat_jet_v  = pfjets08_v.at( fcnc_top_fat_jet_index ) ;

    // python -m cogapp.__main__ -o select_offline.C select_offline_cog_fnal.C; root -l -b -q select_offline.C 
    sm_top_fat_jet_pt    = sm_top_fat_jet_v.Pt();
    fcnc_top_fat_jet_pt  = fcnc_top_fat_jet_v.Pt();
    top_jet_scalar       = sm_top_fat_jet_v.Dot( fcnc_top_fat_jet_v );

    // taus
    int sm_i = sm_top_fat_jet_index;
    int fc_i = fcnc_top_fat_jet_index;
    sm_tau_21   = -1; if( *pfjets08_tau1_v.at( sm_i ) > 0 ) {sm_tau_21 = *pfjets08_tau2_v.at(sm_i ) / *pfjets08_tau1_v.at( sm_i );}
    sm_tau_31   = -1; if( *pfjets08_tau1_v.at( sm_i ) > 0 ) {sm_tau_31 = *pfjets08_tau3_v.at(sm_i ) / *pfjets08_tau1_v.at( sm_i );}
    sm_tau_32   = -1; if( *pfjets08_tau2_v.at( sm_i ) > 0 ) {sm_tau_32 = *pfjets08_tau3_v.at(sm_i ) / *pfjets08_tau2_v.at( sm_i );}

    fcnc_tau_21 = -1; if( *pfjets08_tau1_v.at( fc_i ) > 0 ) {fcnc_tau_21 = *pfjets08_tau2_v.at(fc_i ) / *pfjets08_tau1_v.at( fc_i );}
    fcnc_tau_31 = -1; if( *pfjets08_tau1_v.at( fc_i ) > 0 ) {fcnc_tau_31 = *pfjets08_tau3_v.at(fc_i ) / *pfjets08_tau1_v.at( fc_i );}
    fcnc_tau_32 = -1; if( *pfjets08_tau2_v.at( fc_i ) > 0 ) {fcnc_tau_32 = *pfjets08_tau3_v.at(fc_i ) / *pfjets08_tau2_v.at( fc_i );}

    // mass softdropped
    sm_top_sd_m   = pfjets08_softDroppedJet_v.at(sm_i ).M();
    fcnc_top_sd_m = pfjets08_softDroppedJet_v.at( fc_i ).M();

    // combinations of small jets into pairs
    //sm_top_fat_jet_v.Print();
    // vector<CombPart> *sm_parts = get_combination_2( &pfjets02_softDroppedJet_v, sm_top_fat_jet_v, 1.0 );
    vector<CombPart> *sm_parts = get_combination_2( &pfjets02_v, sm_top_fat_jet_v, 1.0 );
    //fcnc_top_fat_jet_v.Print();
    // vector<CombPart> *fc_parts = get_combination_2( &pfjets02_softDroppedJet_v, fcnc_top_fat_jet_v, 1.0 );
    vector<CombPart> *fc_parts = get_combination_2( &pfjets02_v, fcnc_top_fat_jet_v, 1.0 );

    // leading mass, best_H_mass, best_W_mass
    fcnc_leadin_mass = -1; 
    fcnc_bH_mass = -1;
    fcnc_bW_mass = -1;
    sm_leadin_mass = -1; 
    sm_bH_mass = -1;
    sm_bW_mass = -1;
    TLorentzVector H_tlv, W_tlv;
    for(int i = 0; i < sm_parts->size(); i++){
      CombPart * part = &( sm_parts->at(i) );
      auto tlv = part->GetTlv();

      if(not i) sm_leadin_mass = tlv.M();
      if( TMath::Abs(sm_bH_mass - 125) > TMath::Abs(tlv.M() - 125) ) {sm_bH_mass = tlv.M(); ;}
      if( TMath::Abs(sm_bW_mass - 80 ) > TMath::Abs(tlv.M() - 90 ) ) {sm_bW_mass = tlv.M(); W_tlv = tlv;}
    }

    for(int i = 0; i < fc_parts->size(); i++){
      CombPart * part = &( fc_parts->at(i) );
      auto tlv = part->GetTlv();

      if(not i) fcnc_leadin_mass = tlv.M();
      if( TMath::Abs(fcnc_bH_mass - 125) > TMath::Abs(tlv.M() - 125) ) {fcnc_bH_mass = tlv.M(); H_tlv = tlv;}
      if( TMath::Abs(fcnc_bW_mass - 80 ) > TMath::Abs(tlv.M() - 90 ) ) {fcnc_bW_mass = tlv.M(); ;}
    }

    //  "mass_disbalance", "H_x_fatjet", "W_x_fatjet", "H_pt", "W_pt",
    mass_disbalance = TMath::Abs(sm_top_sd_m - fcnc_top_sd_m) / TMath::Max(sm_top_sd_m, fcnc_top_sd_m);
    H_pt = -1; H_x_fatjet = -1; W_pt = -1; W_x_fatjet = -1;

    if(fcnc_bH_mass > 0){
      H_pt = H_tlv.Pt();
      H_x_fatjet = H_tlv.Dot( fcnc_top_fat_jet_v );
    }

    if(sm_bW_mass > 0){
      W_pt = W_tlv.Pt();
      W_x_fatjet = W_tlv.Dot( sm_top_fat_jet_v );
    }

    delete sm_parts;
    delete fc_parts;

    /*
        "mass_disbalance", "H_x_fatjet", "W_x_fatjet", "H_pt", "W_pt",

    if( bfatjet_1_bsubjet.M() < 20 and bfatjet_2_bsubjet.M() > 20)                                   {my_tag = false;  tagged = true;}
    else if( bfatjet_1_bsubjet.M() > 20 and bfatjet_2_bsubjet.M() < 20 )                             {my_tag = true;  tagged = true;}
    else if( *bfatjet_1_tau3 / *bfatjet_1_tau1 > 0.15 and *bfatjet_2_tau3 / *bfatjet_2_tau1 < 0.15 ) {my_tag = true;  tagged = true;}
    else if( *bfatjet_1_tau3 / *bfatjet_1_tau1 < 0.15 and *bfatjet_2_tau3 / *bfatjet_2_tau1 > 0.15 ) {my_tag = false;  tagged = true;}
    else if( *bfatjet_1_tau2 / *bfatjet_1_tau1 > 0.25 and *bfatjet_2_tau2 / *bfatjet_2_tau1 < 0.25 ) {my_tag = true;  tagged = true;}
    else if( *bfatjet_1_tau2 / *bfatjet_1_tau1 < 0.25 and *bfatjet_2_tau2 / *bfatjet_2_tau1 > 0.25 ) {my_tag = false;  tagged = true;}
    else if( leading_comb_1_m > 85 and leading_comb_2_m < 85) {my_tag = true;  tagged = true;}
    else if( leading_comb_1_m < 85 and leading_comb_2_m > 85) {my_tag = false;  tagged = true;}
    else if( has_in_W_range_1 and not has_in_W_range_2 ) {my_tag = false;  tagged = true;}
    else if( has_in_W_range_2 and not has_in_W_range_1 ) {my_tag = true;  tagged = true;}
    // else my_tag = false;
    */

    /*[[[cog
      plotter.fill_hists();
    ]]]*/
    //[[[end]]]

    file_out->cd();
    tree_out->Fill();
  }

  file_out->cd();
  tree_out->Write();
  /*[[[cog
    plotter.write_hists();
  ]]]*/
  //[[[end]]]
  file_out->Close();
  file->Close();
  cout << "End with " << dataset->process_name << endl;
  return;
}

void select_offline(){
  auto datasets = get_datasets();

  vector<TThread*> threads;
  for(auto dataset : datasets){
    TThread* new_thread = new TThread(dataset->process_name.c_str(), &select_single_dataset, (void*) dataset);
    threads.push_back( new_thread );
  }

  threads_care( threads, 5 );
}









