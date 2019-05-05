
#include "analyse_cfg.C"

string OUTPUT_PATH = "./output/test_big_0/";
float max_events_to_analyse =  9999999999;

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
  TTree * tree_out = new TTree("events", "events");


  double efficiency_0 = 0, efficiency_1 = 0, efficiency_2 = 0, efficiency_3 = 0, efficiency_max = 0;
  double efficiency_4 = 0, efficiency_5 = 0, efficiency_6 = 0, efficiency_7 = 0, efficiency_8 = 0;
  /*[[[cog
    from mRootCOGAnalyser import *
    from AnalyseHEPPY import *

    tlvs = []
    vars = ["met_pt"]
    vecs = ["gen_fcnc_b1", "gen_fcnc_b2", "gen_fcnc_u"]

    for vec in vecs:
      tlvs += [ vec ]
      tlv_parts = ["e", "pt", "eta", "phi", "m"]
      for part in tlv_parts:
        vars += [ vec + "_" + part ]

    collections_size = 16
    jet_collections = ["pfjets02", "pfjets04", "pfjets08", "pfjets04_btag"]    
    
    for jet in jet_collections:
      v, t = get_jets( jet, collections_size )
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
  ]]]*/
  //[[[end]]]

  nevents = TMath::Min((int)max_events_to_analyse, (int)nevents);
  for(int i = 0; i < nevents; i++ ){
    event->tree->GetEntry(i);
    if(not (i%TMath::Max(int(0.05*nevents), 1))) cout << out_name << " " << i << "/" << nevents << endl;

    /*[[[cog
      analyser.set_tlvs()

      for collection in jet_collections:
        type = "TLorentzVector"
        parts = [ collection + "_" + str(i) for i in xrange(collections_size) ]
        mRootCOG.cpp_vector(collection + "_v" , type, parts)
    ]]]*/
    //[[[end]]]

    *pfjets02_N = TMath::Min(16., *pfjets02_N);
    *pfjets04_N = TMath::Min(10., *pfjets04_N);
    *pfjets08_N = TMath::Min(16., *pfjets08_N);
    *pfjets04_btag_N = TMath::Min(16., *pfjets04_btag_N);

    pfjets02_v.erase(pfjets02_v.begin()           + *pfjets02_N, pfjets02_v.end() );
    pfjets04_v.erase(pfjets04_v.begin()           + *pfjets04_N, pfjets04_v.end() );
    pfjets08_v.erase(pfjets08_v.begin()           + *pfjets08_N, pfjets08_v.end() );
    pfjets04_btag_v.erase(pfjets04_btag_v.begin() + *pfjets04_btag_N, pfjets04_btag_v.end() );

    vector<bool> btags;
    for(int i = 0; i < pfjets04_v.size(); i++){
      TLorentzVector tlv_1 = pfjets04_v.at( i );
      for(int i = 0; i < pfjets04_btag_v.size(); i++){
        TLorentzVector tlv_2 = pfjets04_btag_v.at(i);
        if( tlv_1.DeltaR( pfjets04_btag_v.at(i) ) > 0.0001 ) continue;
        btags.push_back( true );
        break;
      }
      btags.push_back( false );
    }

    double best_dR_1 = 99999; int best_index_b1 = 0;
    double best_dR_2 = 99999; int best_index_b2 = 0;
    double best_dR_3 = 99999; int best_index_u = 0;
    for(int i = 0; i < pfjets04_v.size(); i++){
      TLorentzVector tlv = pfjets04_v.at( i );

      if( gen_fcnc_b1.DeltaR( tlv ) < best_dR_1 ){
        best_dR_1 =  gen_fcnc_b1.DeltaR( tlv );
        best_index_b1 = i;
      }
      if( gen_fcnc_b2.DeltaR( tlv ) < best_dR_1 ){
        best_dR_2 =  gen_fcnc_b2.DeltaR( tlv );
        best_index_b2 = i;
      }
      if( gen_fcnc_u.DeltaR( tlv ) < best_dR_3 ){
        best_dR_3 =  gen_fcnc_u.DeltaR( tlv );
        best_index_u = i;
      }
    }

    if(best_dR_1 > 0.5) best_index_b1 = -1;
    if(best_dR_2 > 0.5) best_index_b2 = -1;
    if(best_dR_3 > 0.5) best_index_u  = -1;

    dR_bb->Fill( best_dR_1 );
    dR_bb->Fill( best_dR_2 );

    if(best_index_b1 != -1 and best_index_b2 != -1){
      bb_mass->Fill( (pfjets04_v.at( best_index_b1 ) + pfjets04_v.at( best_index_b2 )).M() );

      if( best_index_u != -1 )
        ubb_mass->Fill( (pfjets04_v.at( best_index_b1 ) + pfjets04_v.at( best_index_b2 ) + pfjets04_v.at( best_index_u) ).M() );
    }

    // if(best_index_b1 == -1 or best_index_b2 == -1 or best_index_u == -1) continue;

    //============================================================================================
    // jj candidate
    auto jj_candidates     = mRoot::get_combination_2( & pfjets04_v );
    vector<CombPart> jj_candidate_0tag_v;
    vector<CombPart> jj_candidate_1tag_v;
    vector<CombPart> jj_candidate_2tag_v;

    for(auto part : *jj_candidates){
      auto tlv = part.GetTlv();
      auto tlv_1 = part.GetTlvPart( 0 );
      auto tlv_2 = part.GetTlvPart( 1 );

      bool btag_1 = btags.at( part.indexes.at(0) );
      bool btag_2 = btags.at( part.indexes.at(1) );
      int btag_index = 0;
      if( btag_1 ) btag_index++;
      if( btag_2 ) btag_index++;

      if(btag_index == 0) jj_candidate_0tag->Fill( part.GetTlv().M() );
      if(btag_index == 1) jj_candidate_1tag->Fill( part.GetTlv().M() );
      if(btag_index == 2) jj_candidate_2tag->Fill( part.GetTlv().M() );

      if(btag_index == 0) jj_candidate_0tag_v.push_back( part );
      if(btag_index == 1) jj_candidate_1tag_v.push_back( part );
      if(btag_index == 2) jj_candidate_2tag_v.push_back( part );
    }

    // jjj candidates
    auto jjj_candidate_2tag = add_combination(&jj_candidate_2tag_v, &pfjets04_v);
    auto jjj_candidate_1tag = add_combination(&jj_candidate_1tag_v, &pfjets04_v);

    vector<CombPart> jjj_fcnc_candidates;

    for(int i = 0, size = jjj_candidate_2tag->size(); i < size; i++){
      CombPart * part = &( jjj_candidate_2tag->at(i) );
      bool btag_3 = btags.at( part->indexes.at(1) );
      if( btag_3 ) continue;
      jjj_fcnc_candidates.push_back( *part );
    }

    for(int i = 0, size = jjj_candidate_1tag->size(); i < size; i++){
      CombPart * part = &( jjj_candidate_1tag->at(i) );
      bool btag_3 = btags.at( part->indexes.at(1) );
      if( btag_3 ) continue;
      jjj_fcnc_candidates.push_back( *part );
    }

    // score candidates
    //cout << best_index_b1 << " " << best_index_b2 << " " << best_index_u << " <==== " << endl;
    vector<float> scores_tH;
    vector<bool>  scores_tH_true;
    for(int i = 0, size = jjj_fcnc_candidates.size(); i < size; i++){
      CombPart * part = &( jjj_fcnc_candidates.at(i) );
      auto tlv = part->GetTlv();
      auto tlv_1 = part->GetTlvPart( 0 );
      auto tlv_2 = part->GetTlvPart( 1 );
      auto tlv_3 = part->GetTlvPart( 2 );

      auto tlv_12 = tlv_1 + tlv_2;
      
      float score = TMath::Sqrt( pow(tlv_12.M() - 125, 2) + pow(tlv.M() - 175, 2) );
      scores_tH.push_back( score );

      //cout << part->indexes.at(0) << " " << part->indexes.at(1) << " " << part->indexes.at(2) << endl;

      if( best_index_b1 == part->indexes.at(0) or best_index_b1 == part->indexes.at(1) ){
        if( best_index_b2 == part->indexes.at(0) or best_index_b2 == part->indexes.at(1) ){
          if( best_index_u == part->indexes.at(2) ){
            scores_tH_true.push_back( true );
            efficiency_max += 1.;
            continue;
          }
        }
      }

      scores_tH_true.push_back( false );
    }

    vector<size_t> score_indexes = sort_indexes( scores_tH );
    if( scores_tH_true.at( score_indexes.at(0) ) ) efficiency_0 += 1;

    // for(int i = 0; i < scores_tH_true.size(); i++)

    
    // check if one quark is not a part of W
    //vector<CombPart> jj_candidate_0tag_v;
    //vector<CombPart> jj_candidate_1tag_v;
    //vector<CombPart> jj_candidate_2tag_v;
    vector<float> scores_W;
    for(int i = 0, size = jjj_fcnc_candidates.size(); i < size; i++){
      CombPart * part = &( jjj_fcnc_candidates.at(i) );
      auto tlv = part->GetTlv();
      auto tlv_1 = part->GetTlvPart( 0 );
      auto tlv_2 = part->GetTlvPart( 1 );
      auto tlv_3 = part->GetTlvPart( 2 );
      float min_score = 99999;
      for(int j = 0, size_2 = pfjets04_v.size(); j < size_2; j++){
        TLorentzVector tlv_j = pfjets04_v.at( j );

        if( j == part->indexes.at(0) ) continue;
        if( j == part->indexes.at(1) ) continue;
        if( j == part->indexes.at(2) ) continue;

        float score_1 = TMath::Abs((tlv_j + tlv_1).M() - 80.);
        float score_2 = TMath::Abs((tlv_j + tlv_2).M() - 80.);
        float score_3 = TMath::Abs((tlv_j + tlv_3).M() - 80.);
        if(min_score > score_1) min_score = score_1;
        if(min_score > score_2) min_score = score_2;
        if(min_score > score_3) min_score = score_3;
      }
      scores_W.push_back( min_score );
    }

    //for(int i = 0; i < score_indexes.size(); i++){
    // cout << scores_W.at( score_indexes.at(i) ) << " " << scores_tH.at( score_indexes.at(i) ) << " " << scores_tH_true.at( score_indexes.at(i) ) << endl;
    //}
    //cout << "==========================" << endl;
    vector<float> scores_tH_cleared;
    for(int i = 0, size = jjj_fcnc_candidates.size(); i < size; i++){
      //if()
    }

    if( score_indexes.size() ){
      CombPart * part_1 = &jjj_fcnc_candidates.at( score_indexes.at(0) );
      H_pt_resolution->Fill( (gen_fcnc_b1 + gen_fcnc_b2).Pt() - part_1->GetTlv().Pt() );
    }


    // cout << score_indexes.size() << endl;
    if( score_indexes.size() > 3){
      CombPart * part_1 = &jjj_fcnc_candidates.at( score_indexes.at(0) );
      CombPart * part_2 = &jjj_fcnc_candidates.at( score_indexes.at(1) );
      CombPart * part_3 = &jjj_fcnc_candidates.at( score_indexes.at(2) );

      jjj_fcnc_candidate_score_0->Fill( part_1->GetTlv().M() );
      jjj_fcnc_candidate_score_1->Fill( part_2->GetTlv().M() );
      jjj_fcnc_candidate_score_2->Fill( part_3->GetTlv().M() );

      jj_fcnc_candidate_score_0->Fill( (part_1->GetTlvPart( 0 ) + part_3->GetTlvPart( 1 )).M() );
      jj_fcnc_candidate_score_1->Fill( (part_2->GetTlvPart( 0 ) + part_3->GetTlvPart( 1 )).M() );
      jj_fcnc_candidate_score_2->Fill( (part_3->GetTlvPart( 0 ) + part_3->GetTlvPart( 1 )).M() );

      H_pt_resolution_2->Fill( (gen_fcnc_b1 + gen_fcnc_b2).Pt() - part_2->GetTlv().Pt() );
      H_pt_resolution_3->Fill( (gen_fcnc_b1 + gen_fcnc_b2).Pt() - part_3->GetTlv().Pt() );
    }
    //============================================================================================
    /*[[[cog
      plotter.fill_hists();
    ]]]*/
    hist_0->Fill( *met_pt);
    //[[[end]]]

    delete jj_candidates;
    delete jjj_candidate_1tag;
    delete jjj_candidate_2tag;
    // delete t_candidates;

    tree_out->Fill();
  }

  file_out->cd();
  tree_out->Write();
  /*[[[cog
    plotter.write_hists();
  ]]]*/
  //[[[end]]]
  file_out->Close();
  cout << "End with " << dataset->process_name << endl;


  cout << "efficiency_0 " << efficiency_0 << endl;
  cout << "efficiency_1 " << efficiency_1 << endl;
  cout << "efficiency_2 " << efficiency_2 << endl;
  cout << "efficiency_3 " << efficiency_3 << endl;
  cout << "efficiency_max " << efficiency_max << endl;


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









