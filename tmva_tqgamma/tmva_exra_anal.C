

#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRoot.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootAnalyser.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootThread.cpp"
#include "tmva_use_comp.C"

#define DEBUG_PRINT false

TGraphErrors * get_graph_for_cone(double R_edge, TH2D * hist){
  TGraphErrors * gr = new TGraphErrors (100);

  for(int x = 1; x <= 100; x++){
    double pt = 3000. / 100 * x - 3000. / 100 * 0.5;

    double in_cone  = 0;
    double out_cone = 0;
    for(int y = 1; y <= 1000; y++){
      double R = 10. / 1000 * y - 10. / 1000 * 0.5;
      double entries = hist->GetBinContent(x, y);
      if(R < R_edge) in_cone  += entries;
      else        out_cone += entries;
    }
    cout << pt << " " << in_cone << " " << out_cone << endl;

    double frac_in_cone     = 0, frac_in_cone_err = 0;
    if(out_cone + out_cone > 1){
      frac_in_cone     = in_cone / (in_cone + out_cone);
      frac_in_cone_err = TMath::Sqrt(in_cone) / (in_cone + out_cone);
    }

    gr->SetPoint( x, pt, frac_in_cone );
    gr->SetPointError( x, 3000. / 100 / 2., frac_in_cone_err );
  }

  return gr;
}

TGraphErrors * get_graph_events(double R_edge, TH2D * hist){
  TGraphErrors * gr = new TGraphErrors (100);

  for(int x = 1; x <= 100; x++){
    double pt = 3000. / 100 * x - 3000. / 100 * 0.5;

    double in_cone  = 0;
    double out_cone = 0;
    for(int y = 1; y <= 1000; y++){
      double R = 10. / 1000 * y - 10. / 1000 * 0.5;
      double entries = hist->GetBinContent(x, y);
      if(R < R_edge) in_cone  += entries;
      else        out_cone += entries;
    }
    cout << pt << " " << in_cone << " " << out_cone << endl;

    double frac_in_cone     = 0, frac_in_cone_err = 0;
    if(out_cone + out_cone > 1){
      frac_in_cone     = in_cone;
      frac_in_cone_err = TMath::Sqrt(in_cone);
    }

    gr->SetPoint( x, pt, frac_in_cone );
    gr->SetPointError( x, 3000. / 100 / 2., frac_in_cone_err );
  }

  return gr;
}

void tmva_analyse_file(TFile * file, string out_name, double xfactor){
  // INPUT =========================================+>
  mRoot::EventReader <Double_t> event;
  event.Init( file, "events" );
  int nevents = event.tree->GetEntries();

  // OUTPUT =========================================+>
  TFile * file_out = new TFile( out_name.c_str(), "RECREATE");

  /*[[[cog
  import cog

  def def_var( var ):
    cog.outl( "Double_t * " + var + " = event.GetVar(\"" +var + "\");" )

  def def_l( l ):
    cog.outl( "TLorentzVector " + l + ";" )

  vars_to_use = ["gen_t_pt", "dR_gen_u_gen_photon", "gen_t_m", "M_gen_u_gen_photon", "gen_u_eta", "gen_photon_eta"]
  vars_to_use +=  ["gen_u_pt", "gen_photon_pt"]
  for var in vars_to_use :
    def_var( var )
    
  ]]]*/
  //[[[end]]]

  TH2D * h4 = new TH2D("top_pt vs dR_genPhoton_uquark", "top_pt vs dR_genPhoton_uquark", 100, 0, 3000, 1000, 0, 10);
  TH2D * h5 = new TH2D("top_pt vs dR_genPhoton_uquark cut", "top_pt vs dR_genPhoton_uquark cut", 100, 0, 3000, 1000, 0, 10);

  int i_passed = 0;
  for(int i = 0; i < nevents; i++ ){
    event.tree->GetEntry(i);
    if(not (i%TMath::Max(int(0.05*nevents), 1))) cout << out_name << " " << i << "/" << nevents << endl;

    // histograms here  ====================>
    // cout << *M_gen_u_gen_photon << " " << *gen_t_m << " " << *gen_t_m - *M_gen_u_gen_photon << endl;

    if( TMath::Abs(*M_gen_u_gen_photon - *gen_t_m) > 0.01 ) continue;
    h4->Fill( *gen_t_pt, *dR_gen_u_gen_photon );

    if( TMath::Abs(*gen_u_eta) > 3 or TMath::Abs(*gen_photon_eta) > 3 ) continue;
    if( TMath::Abs(*gen_u_pt) < 30 or TMath::Abs(*gen_photon_pt) < 30 ) continue;
    h5->Fill( *gen_t_pt, *dR_gen_u_gen_photon );
    // if(i_passed++ > 1000) break;
  }

  file_out->cd();
  TGraphErrors * gr  = get_graph_for_cone(0.8, h4);
  TGraphErrors * gr2 = get_graph_for_cone(0.8, h5);
  TGraphErrors * gr3 = get_graph_for_cone(0.6, h5);
  TGraphErrors * gr4 = get_graph_for_cone(0.4, h5);

  TGraphErrors * gr5  = get_graph_events(0.8, h5);
  TGraphErrors * gr6  = get_graph_events(0.6, h5);
  TGraphErrors * gr7  = get_graph_events(0.4, h5);

  gr->Write("graph");
  gr2->Write("graph2");
  gr3->Write("graph3");
  gr4->Write("graph4");

  gr5->Write("graph_ev1");
  gr6->Write("graph_ev2");
  gr7->Write("graph_ev3");

  file_out->cd();
  file_out->Write();
  file_out->Close();
  return 0;
}

struct tmva_analyse_file_args{
  TFile * file;
  double weight;
  string out_path;
};

void tmva_analyse_file_wrapper(void * a){
  tmva_analyse_file_args * args = (tmva_analyse_file_args*) a; 
  cout << "Start with " << args->out_path << endl;
  tmva_analyse_file( args->file, args->out_path, 0 );
  cout << "Done with " << args->out_path << endl;
  // TThread::Exit(0);
  args->file->Close();
  return 0;
}

void tmva_exra_anal_tmp(string samples_path, string out_path){
  // string samples_path = "/afs/cern.ch/work/p/pmandrik/fcc_100TeV/4_analyser/heppy/OUTPUT/fcnc_mar_18";
         samples_path    = "/afs/cern.ch/work/p/pmandrik/fcc_100TeV/4_analyser/heppy/OUTPUT/fcnc_may_24/";
  string samples_postfix = "/heppy.FCChhAnalyses.FCNC_ttgamma.TreeProducer.CheckTreeProducer_1/check_tree.root";
  vector<string> files = { "mgp8_pp_tt_aut", "mgp8_pp_tt_hadronic_aut" };
  vector<TThread*> threads;
  for(auto file : files){

    tmva_analyse_file_args * args = new tmva_analyse_file_args();
    args->file     = TFile::Open( (samples_path + file + samples_postfix).c_str() );
    args->out_path = out_path + "/" + file + "_hists_v2" + ".root";

    TThread* new_thread = new TThread(file.c_str(), &tmva_analyse_file_wrapper, (void*) args);
    threads.push_back( new_thread );
  }

  threads_care( threads, 5 );
}







