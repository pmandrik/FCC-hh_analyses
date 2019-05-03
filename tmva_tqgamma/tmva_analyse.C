

#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRoot.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootAnalyser.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootThread.cpp"
#include "tmva_use_comp.C"

#define DEBUG_PRINT false

void tmva_analyse_file(TFile * file, string out_name, double xfactor, bool do_top_cut = false){
  // INPUT =========================================+>
  mRoot::EventReader <Double_t> event;
  event.Init( file, "events" );
  int nevents = event.tree->GetEntries();

  // OUTPUT =========================================+>
  TFile * file_out = new TFile( out_name.c_str(), "RECREATE");
  TTree * tree_out = new TTree("ttree", "ttree");

  /*[[[cog
  import cog

  def def_var( var ):
    cog.outl( "Double_t * " + var + " = event.GetVar(\"" +var + "\");" )

  def def_l( l ):
    cog.outl( "TLorentzVector " + l + ";" )

  vnames = ['ptag_bestJet_m_0_100', 'ptag_bestJet_m_250', 'dE_photon_bestjet',
            'ptag_quarkCandidate_m', 'ptag_quarkCandidate_pt', 'ptag_quarkCandidate_eta', 'ptag_quarkCandidate_phi']

  atributes = ["_eta", "_phi", "_m", "_pt", "_e", "_tau1", "_tau2", "_tau3", "_tau31", "_tau32", "_tau21"]
  def clone_jet(jet_out, jet_in):
    for atr in atributes:
      cog.outl( "   " + jet_out + atr + " = *" + jet_in + atr + ";" )

  def define_jet(jet_out):
    answer = []
    for atr in atributes: answer += [jet_out + atr]
    return answer

  vnames += define_jet("ptag_bestJet");
  vnames += ['photon_x_ptag_bestJet','dPhi_Photon_ptag_bestJet','dR_Photon_ptag_bestJet','M_Photon_ptag_bestJet',
             'bjet_x_ptag_bestJet', 'dPhi_bjet_ptag_bestJet', 'dR_bjet_ptag_bestJet']
  for name in vnames:
    outline  = "Double_t " + name + "; \n"
    outline += 'tree_out->Branch("' + name + '",    &' + name + ');'
    cog.outl( outline )

  vars_to_use = ["weight", "dR_lepton_btag_pfjets08",  "lepton_relIso", "photon_relIso", "top_pt"]
  for var in vars_to_use :
    def_var( var )

  lorents = ["ptag_quarkCandidate"]
  for l in lorents : def_l( l )
    
  ]]]*/
  Double_t ptag_bestJet_m_0_100; 
  tree_out->Branch("ptag_bestJet_m_0_100",    &ptag_bestJet_m_0_100);
  Double_t ptag_bestJet_m_250; 
  tree_out->Branch("ptag_bestJet_m_250",    &ptag_bestJet_m_250);
  Double_t dE_photon_bestjet; 
  tree_out->Branch("dE_photon_bestjet",    &dE_photon_bestjet);
  Double_t ptag_quarkCandidate_m; 
  tree_out->Branch("ptag_quarkCandidate_m",    &ptag_quarkCandidate_m);
  Double_t ptag_quarkCandidate_pt; 
  tree_out->Branch("ptag_quarkCandidate_pt",    &ptag_quarkCandidate_pt);
  Double_t ptag_quarkCandidate_eta; 
  tree_out->Branch("ptag_quarkCandidate_eta",    &ptag_quarkCandidate_eta);
  Double_t ptag_quarkCandidate_phi; 
  tree_out->Branch("ptag_quarkCandidate_phi",    &ptag_quarkCandidate_phi);
  Double_t ptag_bestJet_eta; 
  tree_out->Branch("ptag_bestJet_eta",    &ptag_bestJet_eta);
  Double_t ptag_bestJet_phi; 
  tree_out->Branch("ptag_bestJet_phi",    &ptag_bestJet_phi);
  Double_t ptag_bestJet_m; 
  tree_out->Branch("ptag_bestJet_m",    &ptag_bestJet_m);
  Double_t ptag_bestJet_pt; 
  tree_out->Branch("ptag_bestJet_pt",    &ptag_bestJet_pt);
  Double_t ptag_bestJet_e; 
  tree_out->Branch("ptag_bestJet_e",    &ptag_bestJet_e);
  Double_t ptag_bestJet_tau1; 
  tree_out->Branch("ptag_bestJet_tau1",    &ptag_bestJet_tau1);
  Double_t ptag_bestJet_tau2; 
  tree_out->Branch("ptag_bestJet_tau2",    &ptag_bestJet_tau2);
  Double_t ptag_bestJet_tau3; 
  tree_out->Branch("ptag_bestJet_tau3",    &ptag_bestJet_tau3);
  Double_t ptag_bestJet_tau31; 
  tree_out->Branch("ptag_bestJet_tau31",    &ptag_bestJet_tau31);
  Double_t ptag_bestJet_tau32; 
  tree_out->Branch("ptag_bestJet_tau32",    &ptag_bestJet_tau32);
  Double_t ptag_bestJet_tau21; 
  tree_out->Branch("ptag_bestJet_tau21",    &ptag_bestJet_tau21);
  Double_t photon_x_ptag_bestJet; 
  tree_out->Branch("photon_x_ptag_bestJet",    &photon_x_ptag_bestJet);
  Double_t dPhi_Photon_ptag_bestJet; 
  tree_out->Branch("dPhi_Photon_ptag_bestJet",    &dPhi_Photon_ptag_bestJet);
  Double_t dR_Photon_ptag_bestJet; 
  tree_out->Branch("dR_Photon_ptag_bestJet",    &dR_Photon_ptag_bestJet);
  Double_t M_Photon_ptag_bestJet; 
  tree_out->Branch("M_Photon_ptag_bestJet",    &M_Photon_ptag_bestJet);
  Double_t bjet_x_ptag_bestJet; 
  tree_out->Branch("bjet_x_ptag_bestJet",    &bjet_x_ptag_bestJet);
  Double_t dPhi_bjet_ptag_bestJet; 
  tree_out->Branch("dPhi_bjet_ptag_bestJet",    &dPhi_bjet_ptag_bestJet);
  Double_t dR_bjet_ptag_bestJet; 
  tree_out->Branch("dR_bjet_ptag_bestJet",    &dR_bjet_ptag_bestJet);
  Double_t * weight = event.GetVar("weight");
  Double_t * dR_lepton_btag_pfjets08 = event.GetVar("dR_lepton_btag_pfjets08");
  Double_t * lepton_relIso = event.GetVar("lepton_relIso");
  Double_t * photon_relIso = event.GetVar("photon_relIso");
  Double_t * top_pt = event.GetVar("top_pt");
  TLorentzVector ptag_quarkCandidate;
  //[[[end]]]

  vector<string> def_variables = get_variables(); // {"ptag_pfjets08_m", "ptag_pfjets08_softDroppedJet_m"}; 
  for(auto name : def_variables){
    tree_out->Branch(name.c_str(), event.GetVar( name ));
  }

  /*[[[cog

  jets  = ["ptag_pfjets02", "ptag_pfjets04", "ptag_pfjets08", "btag_pfjets04", "btag_pfjets08"]
  drops = ["", "_softDroppedJet", "_leadingSoftDroppedSubJet", "_trailingSoftDroppedSubJet"]
  fixes  = ["_pt", "_eta", "_phi", "_e", "_m", "_tau1", "_tau2", "_tau3", "_tau31", "_tau32", "_tau21"]

  vars = []
  for jet in jets :
    for drop in drops :
      for fix in fixes :
        vars += [ jet + drop + fix ]
  for var in vars: def_var( var )

  lorents = []
  for jet in jets :
    for drop in drops :
      lorents += [ jet + drop ]
  for l in lorents : def_l( l )

  names = ["photon"]
  vars = []
  for name in names :
    for fix in fixes :
      vars += [ name + fix]

  for var in vars   : def_var( var )
  for name in names : def_l( name )
  lorents += names

  ]]]*/
  Double_t * ptag_pfjets02_pt = event.GetVar("ptag_pfjets02_pt");
  Double_t * ptag_pfjets02_eta = event.GetVar("ptag_pfjets02_eta");
  Double_t * ptag_pfjets02_phi = event.GetVar("ptag_pfjets02_phi");
  Double_t * ptag_pfjets02_e = event.GetVar("ptag_pfjets02_e");
  Double_t * ptag_pfjets02_m = event.GetVar("ptag_pfjets02_m");
  Double_t * ptag_pfjets02_tau1 = event.GetVar("ptag_pfjets02_tau1");
  Double_t * ptag_pfjets02_tau2 = event.GetVar("ptag_pfjets02_tau2");
  Double_t * ptag_pfjets02_tau3 = event.GetVar("ptag_pfjets02_tau3");
  Double_t * ptag_pfjets02_tau31 = event.GetVar("ptag_pfjets02_tau31");
  Double_t * ptag_pfjets02_tau32 = event.GetVar("ptag_pfjets02_tau32");
  Double_t * ptag_pfjets02_tau21 = event.GetVar("ptag_pfjets02_tau21");
  Double_t * ptag_pfjets02_softDroppedJet_pt = event.GetVar("ptag_pfjets02_softDroppedJet_pt");
  Double_t * ptag_pfjets02_softDroppedJet_eta = event.GetVar("ptag_pfjets02_softDroppedJet_eta");
  Double_t * ptag_pfjets02_softDroppedJet_phi = event.GetVar("ptag_pfjets02_softDroppedJet_phi");
  Double_t * ptag_pfjets02_softDroppedJet_e = event.GetVar("ptag_pfjets02_softDroppedJet_e");
  Double_t * ptag_pfjets02_softDroppedJet_m = event.GetVar("ptag_pfjets02_softDroppedJet_m");
  Double_t * ptag_pfjets02_softDroppedJet_tau1 = event.GetVar("ptag_pfjets02_softDroppedJet_tau1");
  Double_t * ptag_pfjets02_softDroppedJet_tau2 = event.GetVar("ptag_pfjets02_softDroppedJet_tau2");
  Double_t * ptag_pfjets02_softDroppedJet_tau3 = event.GetVar("ptag_pfjets02_softDroppedJet_tau3");
  Double_t * ptag_pfjets02_softDroppedJet_tau31 = event.GetVar("ptag_pfjets02_softDroppedJet_tau31");
  Double_t * ptag_pfjets02_softDroppedJet_tau32 = event.GetVar("ptag_pfjets02_softDroppedJet_tau32");
  Double_t * ptag_pfjets02_softDroppedJet_tau21 = event.GetVar("ptag_pfjets02_softDroppedJet_tau21");
  Double_t * ptag_pfjets02_leadingSoftDroppedSubJet_pt = event.GetVar("ptag_pfjets02_leadingSoftDroppedSubJet_pt");
  Double_t * ptag_pfjets02_leadingSoftDroppedSubJet_eta = event.GetVar("ptag_pfjets02_leadingSoftDroppedSubJet_eta");
  Double_t * ptag_pfjets02_leadingSoftDroppedSubJet_phi = event.GetVar("ptag_pfjets02_leadingSoftDroppedSubJet_phi");
  Double_t * ptag_pfjets02_leadingSoftDroppedSubJet_e = event.GetVar("ptag_pfjets02_leadingSoftDroppedSubJet_e");
  Double_t * ptag_pfjets02_leadingSoftDroppedSubJet_m = event.GetVar("ptag_pfjets02_leadingSoftDroppedSubJet_m");
  Double_t * ptag_pfjets02_leadingSoftDroppedSubJet_tau1 = event.GetVar("ptag_pfjets02_leadingSoftDroppedSubJet_tau1");
  Double_t * ptag_pfjets02_leadingSoftDroppedSubJet_tau2 = event.GetVar("ptag_pfjets02_leadingSoftDroppedSubJet_tau2");
  Double_t * ptag_pfjets02_leadingSoftDroppedSubJet_tau3 = event.GetVar("ptag_pfjets02_leadingSoftDroppedSubJet_tau3");
  Double_t * ptag_pfjets02_leadingSoftDroppedSubJet_tau31 = event.GetVar("ptag_pfjets02_leadingSoftDroppedSubJet_tau31");
  Double_t * ptag_pfjets02_leadingSoftDroppedSubJet_tau32 = event.GetVar("ptag_pfjets02_leadingSoftDroppedSubJet_tau32");
  Double_t * ptag_pfjets02_leadingSoftDroppedSubJet_tau21 = event.GetVar("ptag_pfjets02_leadingSoftDroppedSubJet_tau21");
  Double_t * ptag_pfjets02_trailingSoftDroppedSubJet_pt = event.GetVar("ptag_pfjets02_trailingSoftDroppedSubJet_pt");
  Double_t * ptag_pfjets02_trailingSoftDroppedSubJet_eta = event.GetVar("ptag_pfjets02_trailingSoftDroppedSubJet_eta");
  Double_t * ptag_pfjets02_trailingSoftDroppedSubJet_phi = event.GetVar("ptag_pfjets02_trailingSoftDroppedSubJet_phi");
  Double_t * ptag_pfjets02_trailingSoftDroppedSubJet_e = event.GetVar("ptag_pfjets02_trailingSoftDroppedSubJet_e");
  Double_t * ptag_pfjets02_trailingSoftDroppedSubJet_m = event.GetVar("ptag_pfjets02_trailingSoftDroppedSubJet_m");
  Double_t * ptag_pfjets02_trailingSoftDroppedSubJet_tau1 = event.GetVar("ptag_pfjets02_trailingSoftDroppedSubJet_tau1");
  Double_t * ptag_pfjets02_trailingSoftDroppedSubJet_tau2 = event.GetVar("ptag_pfjets02_trailingSoftDroppedSubJet_tau2");
  Double_t * ptag_pfjets02_trailingSoftDroppedSubJet_tau3 = event.GetVar("ptag_pfjets02_trailingSoftDroppedSubJet_tau3");
  Double_t * ptag_pfjets02_trailingSoftDroppedSubJet_tau31 = event.GetVar("ptag_pfjets02_trailingSoftDroppedSubJet_tau31");
  Double_t * ptag_pfjets02_trailingSoftDroppedSubJet_tau32 = event.GetVar("ptag_pfjets02_trailingSoftDroppedSubJet_tau32");
  Double_t * ptag_pfjets02_trailingSoftDroppedSubJet_tau21 = event.GetVar("ptag_pfjets02_trailingSoftDroppedSubJet_tau21");
  Double_t * ptag_pfjets04_pt = event.GetVar("ptag_pfjets04_pt");
  Double_t * ptag_pfjets04_eta = event.GetVar("ptag_pfjets04_eta");
  Double_t * ptag_pfjets04_phi = event.GetVar("ptag_pfjets04_phi");
  Double_t * ptag_pfjets04_e = event.GetVar("ptag_pfjets04_e");
  Double_t * ptag_pfjets04_m = event.GetVar("ptag_pfjets04_m");
  Double_t * ptag_pfjets04_tau1 = event.GetVar("ptag_pfjets04_tau1");
  Double_t * ptag_pfjets04_tau2 = event.GetVar("ptag_pfjets04_tau2");
  Double_t * ptag_pfjets04_tau3 = event.GetVar("ptag_pfjets04_tau3");
  Double_t * ptag_pfjets04_tau31 = event.GetVar("ptag_pfjets04_tau31");
  Double_t * ptag_pfjets04_tau32 = event.GetVar("ptag_pfjets04_tau32");
  Double_t * ptag_pfjets04_tau21 = event.GetVar("ptag_pfjets04_tau21");
  Double_t * ptag_pfjets04_softDroppedJet_pt = event.GetVar("ptag_pfjets04_softDroppedJet_pt");
  Double_t * ptag_pfjets04_softDroppedJet_eta = event.GetVar("ptag_pfjets04_softDroppedJet_eta");
  Double_t * ptag_pfjets04_softDroppedJet_phi = event.GetVar("ptag_pfjets04_softDroppedJet_phi");
  Double_t * ptag_pfjets04_softDroppedJet_e = event.GetVar("ptag_pfjets04_softDroppedJet_e");
  Double_t * ptag_pfjets04_softDroppedJet_m = event.GetVar("ptag_pfjets04_softDroppedJet_m");
  Double_t * ptag_pfjets04_softDroppedJet_tau1 = event.GetVar("ptag_pfjets04_softDroppedJet_tau1");
  Double_t * ptag_pfjets04_softDroppedJet_tau2 = event.GetVar("ptag_pfjets04_softDroppedJet_tau2");
  Double_t * ptag_pfjets04_softDroppedJet_tau3 = event.GetVar("ptag_pfjets04_softDroppedJet_tau3");
  Double_t * ptag_pfjets04_softDroppedJet_tau31 = event.GetVar("ptag_pfjets04_softDroppedJet_tau31");
  Double_t * ptag_pfjets04_softDroppedJet_tau32 = event.GetVar("ptag_pfjets04_softDroppedJet_tau32");
  Double_t * ptag_pfjets04_softDroppedJet_tau21 = event.GetVar("ptag_pfjets04_softDroppedJet_tau21");
  Double_t * ptag_pfjets04_leadingSoftDroppedSubJet_pt = event.GetVar("ptag_pfjets04_leadingSoftDroppedSubJet_pt");
  Double_t * ptag_pfjets04_leadingSoftDroppedSubJet_eta = event.GetVar("ptag_pfjets04_leadingSoftDroppedSubJet_eta");
  Double_t * ptag_pfjets04_leadingSoftDroppedSubJet_phi = event.GetVar("ptag_pfjets04_leadingSoftDroppedSubJet_phi");
  Double_t * ptag_pfjets04_leadingSoftDroppedSubJet_e = event.GetVar("ptag_pfjets04_leadingSoftDroppedSubJet_e");
  Double_t * ptag_pfjets04_leadingSoftDroppedSubJet_m = event.GetVar("ptag_pfjets04_leadingSoftDroppedSubJet_m");
  Double_t * ptag_pfjets04_leadingSoftDroppedSubJet_tau1 = event.GetVar("ptag_pfjets04_leadingSoftDroppedSubJet_tau1");
  Double_t * ptag_pfjets04_leadingSoftDroppedSubJet_tau2 = event.GetVar("ptag_pfjets04_leadingSoftDroppedSubJet_tau2");
  Double_t * ptag_pfjets04_leadingSoftDroppedSubJet_tau3 = event.GetVar("ptag_pfjets04_leadingSoftDroppedSubJet_tau3");
  Double_t * ptag_pfjets04_leadingSoftDroppedSubJet_tau31 = event.GetVar("ptag_pfjets04_leadingSoftDroppedSubJet_tau31");
  Double_t * ptag_pfjets04_leadingSoftDroppedSubJet_tau32 = event.GetVar("ptag_pfjets04_leadingSoftDroppedSubJet_tau32");
  Double_t * ptag_pfjets04_leadingSoftDroppedSubJet_tau21 = event.GetVar("ptag_pfjets04_leadingSoftDroppedSubJet_tau21");
  Double_t * ptag_pfjets04_trailingSoftDroppedSubJet_pt = event.GetVar("ptag_pfjets04_trailingSoftDroppedSubJet_pt");
  Double_t * ptag_pfjets04_trailingSoftDroppedSubJet_eta = event.GetVar("ptag_pfjets04_trailingSoftDroppedSubJet_eta");
  Double_t * ptag_pfjets04_trailingSoftDroppedSubJet_phi = event.GetVar("ptag_pfjets04_trailingSoftDroppedSubJet_phi");
  Double_t * ptag_pfjets04_trailingSoftDroppedSubJet_e = event.GetVar("ptag_pfjets04_trailingSoftDroppedSubJet_e");
  Double_t * ptag_pfjets04_trailingSoftDroppedSubJet_m = event.GetVar("ptag_pfjets04_trailingSoftDroppedSubJet_m");
  Double_t * ptag_pfjets04_trailingSoftDroppedSubJet_tau1 = event.GetVar("ptag_pfjets04_trailingSoftDroppedSubJet_tau1");
  Double_t * ptag_pfjets04_trailingSoftDroppedSubJet_tau2 = event.GetVar("ptag_pfjets04_trailingSoftDroppedSubJet_tau2");
  Double_t * ptag_pfjets04_trailingSoftDroppedSubJet_tau3 = event.GetVar("ptag_pfjets04_trailingSoftDroppedSubJet_tau3");
  Double_t * ptag_pfjets04_trailingSoftDroppedSubJet_tau31 = event.GetVar("ptag_pfjets04_trailingSoftDroppedSubJet_tau31");
  Double_t * ptag_pfjets04_trailingSoftDroppedSubJet_tau32 = event.GetVar("ptag_pfjets04_trailingSoftDroppedSubJet_tau32");
  Double_t * ptag_pfjets04_trailingSoftDroppedSubJet_tau21 = event.GetVar("ptag_pfjets04_trailingSoftDroppedSubJet_tau21");
  Double_t * ptag_pfjets08_pt = event.GetVar("ptag_pfjets08_pt");
  Double_t * ptag_pfjets08_eta = event.GetVar("ptag_pfjets08_eta");
  Double_t * ptag_pfjets08_phi = event.GetVar("ptag_pfjets08_phi");
  Double_t * ptag_pfjets08_e = event.GetVar("ptag_pfjets08_e");
  Double_t * ptag_pfjets08_m = event.GetVar("ptag_pfjets08_m");
  Double_t * ptag_pfjets08_tau1 = event.GetVar("ptag_pfjets08_tau1");
  Double_t * ptag_pfjets08_tau2 = event.GetVar("ptag_pfjets08_tau2");
  Double_t * ptag_pfjets08_tau3 = event.GetVar("ptag_pfjets08_tau3");
  Double_t * ptag_pfjets08_tau31 = event.GetVar("ptag_pfjets08_tau31");
  Double_t * ptag_pfjets08_tau32 = event.GetVar("ptag_pfjets08_tau32");
  Double_t * ptag_pfjets08_tau21 = event.GetVar("ptag_pfjets08_tau21");
  Double_t * ptag_pfjets08_softDroppedJet_pt = event.GetVar("ptag_pfjets08_softDroppedJet_pt");
  Double_t * ptag_pfjets08_softDroppedJet_eta = event.GetVar("ptag_pfjets08_softDroppedJet_eta");
  Double_t * ptag_pfjets08_softDroppedJet_phi = event.GetVar("ptag_pfjets08_softDroppedJet_phi");
  Double_t * ptag_pfjets08_softDroppedJet_e = event.GetVar("ptag_pfjets08_softDroppedJet_e");
  Double_t * ptag_pfjets08_softDroppedJet_m = event.GetVar("ptag_pfjets08_softDroppedJet_m");
  Double_t * ptag_pfjets08_softDroppedJet_tau1 = event.GetVar("ptag_pfjets08_softDroppedJet_tau1");
  Double_t * ptag_pfjets08_softDroppedJet_tau2 = event.GetVar("ptag_pfjets08_softDroppedJet_tau2");
  Double_t * ptag_pfjets08_softDroppedJet_tau3 = event.GetVar("ptag_pfjets08_softDroppedJet_tau3");
  Double_t * ptag_pfjets08_softDroppedJet_tau31 = event.GetVar("ptag_pfjets08_softDroppedJet_tau31");
  Double_t * ptag_pfjets08_softDroppedJet_tau32 = event.GetVar("ptag_pfjets08_softDroppedJet_tau32");
  Double_t * ptag_pfjets08_softDroppedJet_tau21 = event.GetVar("ptag_pfjets08_softDroppedJet_tau21");
  Double_t * ptag_pfjets08_leadingSoftDroppedSubJet_pt = event.GetVar("ptag_pfjets08_leadingSoftDroppedSubJet_pt");
  Double_t * ptag_pfjets08_leadingSoftDroppedSubJet_eta = event.GetVar("ptag_pfjets08_leadingSoftDroppedSubJet_eta");
  Double_t * ptag_pfjets08_leadingSoftDroppedSubJet_phi = event.GetVar("ptag_pfjets08_leadingSoftDroppedSubJet_phi");
  Double_t * ptag_pfjets08_leadingSoftDroppedSubJet_e = event.GetVar("ptag_pfjets08_leadingSoftDroppedSubJet_e");
  Double_t * ptag_pfjets08_leadingSoftDroppedSubJet_m = event.GetVar("ptag_pfjets08_leadingSoftDroppedSubJet_m");
  Double_t * ptag_pfjets08_leadingSoftDroppedSubJet_tau1 = event.GetVar("ptag_pfjets08_leadingSoftDroppedSubJet_tau1");
  Double_t * ptag_pfjets08_leadingSoftDroppedSubJet_tau2 = event.GetVar("ptag_pfjets08_leadingSoftDroppedSubJet_tau2");
  Double_t * ptag_pfjets08_leadingSoftDroppedSubJet_tau3 = event.GetVar("ptag_pfjets08_leadingSoftDroppedSubJet_tau3");
  Double_t * ptag_pfjets08_leadingSoftDroppedSubJet_tau31 = event.GetVar("ptag_pfjets08_leadingSoftDroppedSubJet_tau31");
  Double_t * ptag_pfjets08_leadingSoftDroppedSubJet_tau32 = event.GetVar("ptag_pfjets08_leadingSoftDroppedSubJet_tau32");
  Double_t * ptag_pfjets08_leadingSoftDroppedSubJet_tau21 = event.GetVar("ptag_pfjets08_leadingSoftDroppedSubJet_tau21");
  Double_t * ptag_pfjets08_trailingSoftDroppedSubJet_pt = event.GetVar("ptag_pfjets08_trailingSoftDroppedSubJet_pt");
  Double_t * ptag_pfjets08_trailingSoftDroppedSubJet_eta = event.GetVar("ptag_pfjets08_trailingSoftDroppedSubJet_eta");
  Double_t * ptag_pfjets08_trailingSoftDroppedSubJet_phi = event.GetVar("ptag_pfjets08_trailingSoftDroppedSubJet_phi");
  Double_t * ptag_pfjets08_trailingSoftDroppedSubJet_e = event.GetVar("ptag_pfjets08_trailingSoftDroppedSubJet_e");
  Double_t * ptag_pfjets08_trailingSoftDroppedSubJet_m = event.GetVar("ptag_pfjets08_trailingSoftDroppedSubJet_m");
  Double_t * ptag_pfjets08_trailingSoftDroppedSubJet_tau1 = event.GetVar("ptag_pfjets08_trailingSoftDroppedSubJet_tau1");
  Double_t * ptag_pfjets08_trailingSoftDroppedSubJet_tau2 = event.GetVar("ptag_pfjets08_trailingSoftDroppedSubJet_tau2");
  Double_t * ptag_pfjets08_trailingSoftDroppedSubJet_tau3 = event.GetVar("ptag_pfjets08_trailingSoftDroppedSubJet_tau3");
  Double_t * ptag_pfjets08_trailingSoftDroppedSubJet_tau31 = event.GetVar("ptag_pfjets08_trailingSoftDroppedSubJet_tau31");
  Double_t * ptag_pfjets08_trailingSoftDroppedSubJet_tau32 = event.GetVar("ptag_pfjets08_trailingSoftDroppedSubJet_tau32");
  Double_t * ptag_pfjets08_trailingSoftDroppedSubJet_tau21 = event.GetVar("ptag_pfjets08_trailingSoftDroppedSubJet_tau21");
  Double_t * btag_pfjets04_pt = event.GetVar("btag_pfjets04_pt");
  Double_t * btag_pfjets04_eta = event.GetVar("btag_pfjets04_eta");
  Double_t * btag_pfjets04_phi = event.GetVar("btag_pfjets04_phi");
  Double_t * btag_pfjets04_e = event.GetVar("btag_pfjets04_e");
  Double_t * btag_pfjets04_m = event.GetVar("btag_pfjets04_m");
  Double_t * btag_pfjets04_tau1 = event.GetVar("btag_pfjets04_tau1");
  Double_t * btag_pfjets04_tau2 = event.GetVar("btag_pfjets04_tau2");
  Double_t * btag_pfjets04_tau3 = event.GetVar("btag_pfjets04_tau3");
  Double_t * btag_pfjets04_tau31 = event.GetVar("btag_pfjets04_tau31");
  Double_t * btag_pfjets04_tau32 = event.GetVar("btag_pfjets04_tau32");
  Double_t * btag_pfjets04_tau21 = event.GetVar("btag_pfjets04_tau21");
  Double_t * btag_pfjets04_softDroppedJet_pt = event.GetVar("btag_pfjets04_softDroppedJet_pt");
  Double_t * btag_pfjets04_softDroppedJet_eta = event.GetVar("btag_pfjets04_softDroppedJet_eta");
  Double_t * btag_pfjets04_softDroppedJet_phi = event.GetVar("btag_pfjets04_softDroppedJet_phi");
  Double_t * btag_pfjets04_softDroppedJet_e = event.GetVar("btag_pfjets04_softDroppedJet_e");
  Double_t * btag_pfjets04_softDroppedJet_m = event.GetVar("btag_pfjets04_softDroppedJet_m");
  Double_t * btag_pfjets04_softDroppedJet_tau1 = event.GetVar("btag_pfjets04_softDroppedJet_tau1");
  Double_t * btag_pfjets04_softDroppedJet_tau2 = event.GetVar("btag_pfjets04_softDroppedJet_tau2");
  Double_t * btag_pfjets04_softDroppedJet_tau3 = event.GetVar("btag_pfjets04_softDroppedJet_tau3");
  Double_t * btag_pfjets04_softDroppedJet_tau31 = event.GetVar("btag_pfjets04_softDroppedJet_tau31");
  Double_t * btag_pfjets04_softDroppedJet_tau32 = event.GetVar("btag_pfjets04_softDroppedJet_tau32");
  Double_t * btag_pfjets04_softDroppedJet_tau21 = event.GetVar("btag_pfjets04_softDroppedJet_tau21");
  Double_t * btag_pfjets04_leadingSoftDroppedSubJet_pt = event.GetVar("btag_pfjets04_leadingSoftDroppedSubJet_pt");
  Double_t * btag_pfjets04_leadingSoftDroppedSubJet_eta = event.GetVar("btag_pfjets04_leadingSoftDroppedSubJet_eta");
  Double_t * btag_pfjets04_leadingSoftDroppedSubJet_phi = event.GetVar("btag_pfjets04_leadingSoftDroppedSubJet_phi");
  Double_t * btag_pfjets04_leadingSoftDroppedSubJet_e = event.GetVar("btag_pfjets04_leadingSoftDroppedSubJet_e");
  Double_t * btag_pfjets04_leadingSoftDroppedSubJet_m = event.GetVar("btag_pfjets04_leadingSoftDroppedSubJet_m");
  Double_t * btag_pfjets04_leadingSoftDroppedSubJet_tau1 = event.GetVar("btag_pfjets04_leadingSoftDroppedSubJet_tau1");
  Double_t * btag_pfjets04_leadingSoftDroppedSubJet_tau2 = event.GetVar("btag_pfjets04_leadingSoftDroppedSubJet_tau2");
  Double_t * btag_pfjets04_leadingSoftDroppedSubJet_tau3 = event.GetVar("btag_pfjets04_leadingSoftDroppedSubJet_tau3");
  Double_t * btag_pfjets04_leadingSoftDroppedSubJet_tau31 = event.GetVar("btag_pfjets04_leadingSoftDroppedSubJet_tau31");
  Double_t * btag_pfjets04_leadingSoftDroppedSubJet_tau32 = event.GetVar("btag_pfjets04_leadingSoftDroppedSubJet_tau32");
  Double_t * btag_pfjets04_leadingSoftDroppedSubJet_tau21 = event.GetVar("btag_pfjets04_leadingSoftDroppedSubJet_tau21");
  Double_t * btag_pfjets04_trailingSoftDroppedSubJet_pt = event.GetVar("btag_pfjets04_trailingSoftDroppedSubJet_pt");
  Double_t * btag_pfjets04_trailingSoftDroppedSubJet_eta = event.GetVar("btag_pfjets04_trailingSoftDroppedSubJet_eta");
  Double_t * btag_pfjets04_trailingSoftDroppedSubJet_phi = event.GetVar("btag_pfjets04_trailingSoftDroppedSubJet_phi");
  Double_t * btag_pfjets04_trailingSoftDroppedSubJet_e = event.GetVar("btag_pfjets04_trailingSoftDroppedSubJet_e");
  Double_t * btag_pfjets04_trailingSoftDroppedSubJet_m = event.GetVar("btag_pfjets04_trailingSoftDroppedSubJet_m");
  Double_t * btag_pfjets04_trailingSoftDroppedSubJet_tau1 = event.GetVar("btag_pfjets04_trailingSoftDroppedSubJet_tau1");
  Double_t * btag_pfjets04_trailingSoftDroppedSubJet_tau2 = event.GetVar("btag_pfjets04_trailingSoftDroppedSubJet_tau2");
  Double_t * btag_pfjets04_trailingSoftDroppedSubJet_tau3 = event.GetVar("btag_pfjets04_trailingSoftDroppedSubJet_tau3");
  Double_t * btag_pfjets04_trailingSoftDroppedSubJet_tau31 = event.GetVar("btag_pfjets04_trailingSoftDroppedSubJet_tau31");
  Double_t * btag_pfjets04_trailingSoftDroppedSubJet_tau32 = event.GetVar("btag_pfjets04_trailingSoftDroppedSubJet_tau32");
  Double_t * btag_pfjets04_trailingSoftDroppedSubJet_tau21 = event.GetVar("btag_pfjets04_trailingSoftDroppedSubJet_tau21");
  Double_t * btag_pfjets08_pt = event.GetVar("btag_pfjets08_pt");
  Double_t * btag_pfjets08_eta = event.GetVar("btag_pfjets08_eta");
  Double_t * btag_pfjets08_phi = event.GetVar("btag_pfjets08_phi");
  Double_t * btag_pfjets08_e = event.GetVar("btag_pfjets08_e");
  Double_t * btag_pfjets08_m = event.GetVar("btag_pfjets08_m");
  Double_t * btag_pfjets08_tau1 = event.GetVar("btag_pfjets08_tau1");
  Double_t * btag_pfjets08_tau2 = event.GetVar("btag_pfjets08_tau2");
  Double_t * btag_pfjets08_tau3 = event.GetVar("btag_pfjets08_tau3");
  Double_t * btag_pfjets08_tau31 = event.GetVar("btag_pfjets08_tau31");
  Double_t * btag_pfjets08_tau32 = event.GetVar("btag_pfjets08_tau32");
  Double_t * btag_pfjets08_tau21 = event.GetVar("btag_pfjets08_tau21");
  Double_t * btag_pfjets08_softDroppedJet_pt = event.GetVar("btag_pfjets08_softDroppedJet_pt");
  Double_t * btag_pfjets08_softDroppedJet_eta = event.GetVar("btag_pfjets08_softDroppedJet_eta");
  Double_t * btag_pfjets08_softDroppedJet_phi = event.GetVar("btag_pfjets08_softDroppedJet_phi");
  Double_t * btag_pfjets08_softDroppedJet_e = event.GetVar("btag_pfjets08_softDroppedJet_e");
  Double_t * btag_pfjets08_softDroppedJet_m = event.GetVar("btag_pfjets08_softDroppedJet_m");
  Double_t * btag_pfjets08_softDroppedJet_tau1 = event.GetVar("btag_pfjets08_softDroppedJet_tau1");
  Double_t * btag_pfjets08_softDroppedJet_tau2 = event.GetVar("btag_pfjets08_softDroppedJet_tau2");
  Double_t * btag_pfjets08_softDroppedJet_tau3 = event.GetVar("btag_pfjets08_softDroppedJet_tau3");
  Double_t * btag_pfjets08_softDroppedJet_tau31 = event.GetVar("btag_pfjets08_softDroppedJet_tau31");
  Double_t * btag_pfjets08_softDroppedJet_tau32 = event.GetVar("btag_pfjets08_softDroppedJet_tau32");
  Double_t * btag_pfjets08_softDroppedJet_tau21 = event.GetVar("btag_pfjets08_softDroppedJet_tau21");
  Double_t * btag_pfjets08_leadingSoftDroppedSubJet_pt = event.GetVar("btag_pfjets08_leadingSoftDroppedSubJet_pt");
  Double_t * btag_pfjets08_leadingSoftDroppedSubJet_eta = event.GetVar("btag_pfjets08_leadingSoftDroppedSubJet_eta");
  Double_t * btag_pfjets08_leadingSoftDroppedSubJet_phi = event.GetVar("btag_pfjets08_leadingSoftDroppedSubJet_phi");
  Double_t * btag_pfjets08_leadingSoftDroppedSubJet_e = event.GetVar("btag_pfjets08_leadingSoftDroppedSubJet_e");
  Double_t * btag_pfjets08_leadingSoftDroppedSubJet_m = event.GetVar("btag_pfjets08_leadingSoftDroppedSubJet_m");
  Double_t * btag_pfjets08_leadingSoftDroppedSubJet_tau1 = event.GetVar("btag_pfjets08_leadingSoftDroppedSubJet_tau1");
  Double_t * btag_pfjets08_leadingSoftDroppedSubJet_tau2 = event.GetVar("btag_pfjets08_leadingSoftDroppedSubJet_tau2");
  Double_t * btag_pfjets08_leadingSoftDroppedSubJet_tau3 = event.GetVar("btag_pfjets08_leadingSoftDroppedSubJet_tau3");
  Double_t * btag_pfjets08_leadingSoftDroppedSubJet_tau31 = event.GetVar("btag_pfjets08_leadingSoftDroppedSubJet_tau31");
  Double_t * btag_pfjets08_leadingSoftDroppedSubJet_tau32 = event.GetVar("btag_pfjets08_leadingSoftDroppedSubJet_tau32");
  Double_t * btag_pfjets08_leadingSoftDroppedSubJet_tau21 = event.GetVar("btag_pfjets08_leadingSoftDroppedSubJet_tau21");
  Double_t * btag_pfjets08_trailingSoftDroppedSubJet_pt = event.GetVar("btag_pfjets08_trailingSoftDroppedSubJet_pt");
  Double_t * btag_pfjets08_trailingSoftDroppedSubJet_eta = event.GetVar("btag_pfjets08_trailingSoftDroppedSubJet_eta");
  Double_t * btag_pfjets08_trailingSoftDroppedSubJet_phi = event.GetVar("btag_pfjets08_trailingSoftDroppedSubJet_phi");
  Double_t * btag_pfjets08_trailingSoftDroppedSubJet_e = event.GetVar("btag_pfjets08_trailingSoftDroppedSubJet_e");
  Double_t * btag_pfjets08_trailingSoftDroppedSubJet_m = event.GetVar("btag_pfjets08_trailingSoftDroppedSubJet_m");
  Double_t * btag_pfjets08_trailingSoftDroppedSubJet_tau1 = event.GetVar("btag_pfjets08_trailingSoftDroppedSubJet_tau1");
  Double_t * btag_pfjets08_trailingSoftDroppedSubJet_tau2 = event.GetVar("btag_pfjets08_trailingSoftDroppedSubJet_tau2");
  Double_t * btag_pfjets08_trailingSoftDroppedSubJet_tau3 = event.GetVar("btag_pfjets08_trailingSoftDroppedSubJet_tau3");
  Double_t * btag_pfjets08_trailingSoftDroppedSubJet_tau31 = event.GetVar("btag_pfjets08_trailingSoftDroppedSubJet_tau31");
  Double_t * btag_pfjets08_trailingSoftDroppedSubJet_tau32 = event.GetVar("btag_pfjets08_trailingSoftDroppedSubJet_tau32");
  Double_t * btag_pfjets08_trailingSoftDroppedSubJet_tau21 = event.GetVar("btag_pfjets08_trailingSoftDroppedSubJet_tau21");
  TLorentzVector ptag_pfjets02;
  TLorentzVector ptag_pfjets02_softDroppedJet;
  TLorentzVector ptag_pfjets02_leadingSoftDroppedSubJet;
  TLorentzVector ptag_pfjets02_trailingSoftDroppedSubJet;
  TLorentzVector ptag_pfjets04;
  TLorentzVector ptag_pfjets04_softDroppedJet;
  TLorentzVector ptag_pfjets04_leadingSoftDroppedSubJet;
  TLorentzVector ptag_pfjets04_trailingSoftDroppedSubJet;
  TLorentzVector ptag_pfjets08;
  TLorentzVector ptag_pfjets08_softDroppedJet;
  TLorentzVector ptag_pfjets08_leadingSoftDroppedSubJet;
  TLorentzVector ptag_pfjets08_trailingSoftDroppedSubJet;
  TLorentzVector btag_pfjets04;
  TLorentzVector btag_pfjets04_softDroppedJet;
  TLorentzVector btag_pfjets04_leadingSoftDroppedSubJet;
  TLorentzVector btag_pfjets04_trailingSoftDroppedSubJet;
  TLorentzVector btag_pfjets08;
  TLorentzVector btag_pfjets08_softDroppedJet;
  TLorentzVector btag_pfjets08_leadingSoftDroppedSubJet;
  TLorentzVector btag_pfjets08_trailingSoftDroppedSubJet;
  Double_t * photon_pt = event.GetVar("photon_pt");
  Double_t * photon_eta = event.GetVar("photon_eta");
  Double_t * photon_phi = event.GetVar("photon_phi");
  Double_t * photon_e = event.GetVar("photon_e");
  Double_t * photon_m = event.GetVar("photon_m");
  Double_t * photon_tau1 = event.GetVar("photon_tau1");
  Double_t * photon_tau2 = event.GetVar("photon_tau2");
  Double_t * photon_tau3 = event.GetVar("photon_tau3");
  Double_t * photon_tau31 = event.GetVar("photon_tau31");
  Double_t * photon_tau32 = event.GetVar("photon_tau32");
  Double_t * photon_tau21 = event.GetVar("photon_tau21");
  TLorentzVector photon;
  //[[[end]]]

  int i_passed = 0;
  int top_cut = 0;
  for(int i = 0; i < nevents; i++ ){
    event.tree->GetEntry(i);
    if(not (i%TMath::Max(int(0.05*nevents), 1))) cout << out_name << " " << i << "/" << nevents << endl;

    // cuts here ====================>
    if(*ptag_pfjets08_pt < 400) continue;
    if(*btag_pfjets08_pt < 400) continue;

    if( do_top_cut ){
      if( *top_pt > 1000 ){
       top_cut ++;
       continue;
      }
    }

    // variables here ====================>
    /*[[[cog
      def set_l( name ):
        cog.outl( name + ".SetPtEtaPhiM(*" + name + "_pt, *" + name + "_eta, *"+ name + "_phi, *"+ name + "_m);" )

      for var in lorents:
        set_l( var )

      ]]]*/
    ptag_pfjets02.SetPtEtaPhiM(*ptag_pfjets02_pt, *ptag_pfjets02_eta, *ptag_pfjets02_phi, *ptag_pfjets02_m);
    ptag_pfjets02_softDroppedJet.SetPtEtaPhiM(*ptag_pfjets02_softDroppedJet_pt, *ptag_pfjets02_softDroppedJet_eta, *ptag_pfjets02_softDroppedJet_phi, *ptag_pfjets02_softDroppedJet_m);
    ptag_pfjets02_leadingSoftDroppedSubJet.SetPtEtaPhiM(*ptag_pfjets02_leadingSoftDroppedSubJet_pt, *ptag_pfjets02_leadingSoftDroppedSubJet_eta, *ptag_pfjets02_leadingSoftDroppedSubJet_phi, *ptag_pfjets02_leadingSoftDroppedSubJet_m);
    ptag_pfjets02_trailingSoftDroppedSubJet.SetPtEtaPhiM(*ptag_pfjets02_trailingSoftDroppedSubJet_pt, *ptag_pfjets02_trailingSoftDroppedSubJet_eta, *ptag_pfjets02_trailingSoftDroppedSubJet_phi, *ptag_pfjets02_trailingSoftDroppedSubJet_m);
    ptag_pfjets04.SetPtEtaPhiM(*ptag_pfjets04_pt, *ptag_pfjets04_eta, *ptag_pfjets04_phi, *ptag_pfjets04_m);
    ptag_pfjets04_softDroppedJet.SetPtEtaPhiM(*ptag_pfjets04_softDroppedJet_pt, *ptag_pfjets04_softDroppedJet_eta, *ptag_pfjets04_softDroppedJet_phi, *ptag_pfjets04_softDroppedJet_m);
    ptag_pfjets04_leadingSoftDroppedSubJet.SetPtEtaPhiM(*ptag_pfjets04_leadingSoftDroppedSubJet_pt, *ptag_pfjets04_leadingSoftDroppedSubJet_eta, *ptag_pfjets04_leadingSoftDroppedSubJet_phi, *ptag_pfjets04_leadingSoftDroppedSubJet_m);
    ptag_pfjets04_trailingSoftDroppedSubJet.SetPtEtaPhiM(*ptag_pfjets04_trailingSoftDroppedSubJet_pt, *ptag_pfjets04_trailingSoftDroppedSubJet_eta, *ptag_pfjets04_trailingSoftDroppedSubJet_phi, *ptag_pfjets04_trailingSoftDroppedSubJet_m);
    ptag_pfjets08.SetPtEtaPhiM(*ptag_pfjets08_pt, *ptag_pfjets08_eta, *ptag_pfjets08_phi, *ptag_pfjets08_m);
    ptag_pfjets08_softDroppedJet.SetPtEtaPhiM(*ptag_pfjets08_softDroppedJet_pt, *ptag_pfjets08_softDroppedJet_eta, *ptag_pfjets08_softDroppedJet_phi, *ptag_pfjets08_softDroppedJet_m);
    ptag_pfjets08_leadingSoftDroppedSubJet.SetPtEtaPhiM(*ptag_pfjets08_leadingSoftDroppedSubJet_pt, *ptag_pfjets08_leadingSoftDroppedSubJet_eta, *ptag_pfjets08_leadingSoftDroppedSubJet_phi, *ptag_pfjets08_leadingSoftDroppedSubJet_m);
    ptag_pfjets08_trailingSoftDroppedSubJet.SetPtEtaPhiM(*ptag_pfjets08_trailingSoftDroppedSubJet_pt, *ptag_pfjets08_trailingSoftDroppedSubJet_eta, *ptag_pfjets08_trailingSoftDroppedSubJet_phi, *ptag_pfjets08_trailingSoftDroppedSubJet_m);
    btag_pfjets04.SetPtEtaPhiM(*btag_pfjets04_pt, *btag_pfjets04_eta, *btag_pfjets04_phi, *btag_pfjets04_m);
    btag_pfjets04_softDroppedJet.SetPtEtaPhiM(*btag_pfjets04_softDroppedJet_pt, *btag_pfjets04_softDroppedJet_eta, *btag_pfjets04_softDroppedJet_phi, *btag_pfjets04_softDroppedJet_m);
    btag_pfjets04_leadingSoftDroppedSubJet.SetPtEtaPhiM(*btag_pfjets04_leadingSoftDroppedSubJet_pt, *btag_pfjets04_leadingSoftDroppedSubJet_eta, *btag_pfjets04_leadingSoftDroppedSubJet_phi, *btag_pfjets04_leadingSoftDroppedSubJet_m);
    btag_pfjets04_trailingSoftDroppedSubJet.SetPtEtaPhiM(*btag_pfjets04_trailingSoftDroppedSubJet_pt, *btag_pfjets04_trailingSoftDroppedSubJet_eta, *btag_pfjets04_trailingSoftDroppedSubJet_phi, *btag_pfjets04_trailingSoftDroppedSubJet_m);
    btag_pfjets08.SetPtEtaPhiM(*btag_pfjets08_pt, *btag_pfjets08_eta, *btag_pfjets08_phi, *btag_pfjets08_m);
    btag_pfjets08_softDroppedJet.SetPtEtaPhiM(*btag_pfjets08_softDroppedJet_pt, *btag_pfjets08_softDroppedJet_eta, *btag_pfjets08_softDroppedJet_phi, *btag_pfjets08_softDroppedJet_m);
    btag_pfjets08_leadingSoftDroppedSubJet.SetPtEtaPhiM(*btag_pfjets08_leadingSoftDroppedSubJet_pt, *btag_pfjets08_leadingSoftDroppedSubJet_eta, *btag_pfjets08_leadingSoftDroppedSubJet_phi, *btag_pfjets08_leadingSoftDroppedSubJet_m);
    btag_pfjets08_trailingSoftDroppedSubJet.SetPtEtaPhiM(*btag_pfjets08_trailingSoftDroppedSubJet_pt, *btag_pfjets08_trailingSoftDroppedSubJet_eta, *btag_pfjets08_trailingSoftDroppedSubJet_phi, *btag_pfjets08_trailingSoftDroppedSubJet_m);
    photon.SetPtEtaPhiM(*photon_pt, *photon_eta, *photon_phi, *photon_m);
      //[[[end]]]
    
    // if( ptag_pfjets08_softDroppedJet.M())
    // if( ptag_pfjets08.M() > 100) continue;
    
    // msg( *v_BestMass_jet_m );
    #if DEBUG_PRINT
      msg( "===><======><======><======><======><======><======><======><===" );
      msg( photon.E() );
      msg( "== R=08 == ", ptag_pfjets08.DeltaR( photon ) );
      msg( ptag_pfjets08.E(), ptag_pfjets08_softDroppedJet.E(), ptag_pfjets08_leadingSoftDroppedSubJet.E(), ptag_pfjets08_trailingSoftDroppedSubJet.E() );
      msg( ptag_pfjets08.M(), ptag_pfjets08_softDroppedJet.M(), ptag_pfjets08_leadingSoftDroppedSubJet.M(), ptag_pfjets08_trailingSoftDroppedSubJet.M() );
      msg( "== R=04 == ", ptag_pfjets04.DeltaR( photon ) );
      msg( ptag_pfjets04.E(), ptag_pfjets04_softDroppedJet.E(), ptag_pfjets04_leadingSoftDroppedSubJet.E(), ptag_pfjets04_trailingSoftDroppedSubJet.E() );
      msg( ptag_pfjets04.M(), ptag_pfjets04_softDroppedJet.M(), ptag_pfjets04_leadingSoftDroppedSubJet.M(), ptag_pfjets04_trailingSoftDroppedSubJet.M() );
      msg( "== R=02 == ", ptag_pfjets02.DeltaR( photon ) );
      msg( ptag_pfjets02.E(), ptag_pfjets02_softDroppedJet.E(), ptag_pfjets02_leadingSoftDroppedSubJet.E(), ptag_pfjets02_trailingSoftDroppedSubJet.E() );
      msg( ptag_pfjets02.M(), ptag_pfjets02_softDroppedJet.M(), ptag_pfjets02_leadingSoftDroppedSubJet.M(), ptag_pfjets02_trailingSoftDroppedSubJet.M() );
    #endif

    vector<TLorentzVector> jets = {ptag_pfjets08, ptag_pfjets08_softDroppedJet, ptag_pfjets08_leadingSoftDroppedSubJet, ptag_pfjets08_trailingSoftDroppedSubJet, 
                                   ptag_pfjets02, ptag_pfjets02_softDroppedJet, ptag_pfjets02_leadingSoftDroppedSubJet, ptag_pfjets02_trailingSoftDroppedSubJet, 
                                   ptag_pfjets04, ptag_pfjets04_softDroppedJet, ptag_pfjets04_leadingSoftDroppedSubJet, ptag_pfjets04_trailingSoftDroppedSubJet};
     
    double best_m = 99999,      best_photon_e = 99999;
    int    best_jet_index = 0, best_photon_jet_index = 0, best_quark_index = 0;
    for(int j = 0; j < jets.size(); j++ ){
      if( jets.at(j).CosTheta()*jets.at(j).CosTheta() >= 1) continue;

      //jets.at(j).Print();
      //cout << jets.at(j).CosTheta() << endl;

      if( TMath::Abs(jets.at(j).M() - 174) < best_m){
        best_m = TMath::Abs(jets.at(j).M() - 174);
        best_jet_index = j;
      }
      if( TMath::Abs(jets.at(j).E() - photon.E()) < best_photon_e ){
        best_photon_e = TMath::Abs(jets.at(j).E() - photon.E());
        best_photon_jet_index = j;
      }
    }

    dE_photon_bestjet = photon.E() - jets.at(best_photon_jet_index).E();

    // fill mass
    if(ptag_pfjets08.M() < 100) ptag_bestJet_m_0_100 = ptag_bestJet_m; else ptag_bestJet_m_0_100 = -1;
    if(ptag_pfjets08.M() > 250) ptag_bestJet_m_250   = ptag_bestJet_m; else ptag_bestJet_m_250   = -1;

    // fill best ptag jet
    auto ptag_best_jet = jets.at( best_jet_index );
    auto bjet = btag_pfjets04;

    /*[[[cog
      jets = ["ptag_pfjets08", "ptag_pfjets08_softDroppedJet", "ptag_pfjets08_leadingSoftDroppedSubJet", "ptag_pfjets08_trailingSoftDroppedSubJet", 
              "ptag_pfjets02", "ptag_pfjets02_softDroppedJet", "ptag_pfjets02_leadingSoftDroppedSubJet", "ptag_pfjets02_trailingSoftDroppedSubJet", 
              "ptag_pfjets04", "ptag_pfjets04_softDroppedJet", "ptag_pfjets04_leadingSoftDroppedSubJet", "ptag_pfjets04_trailingSoftDroppedSubJet"]

      for i, jet in enumerate(jets):
        cog.outl( "if(" + str(i) + " == best_jet_index ){ " )
        clone_jet("ptag_bestJet", jet)
        cog.outl( "} else " )
      cog.outl( "{}" )

    ]]]*/
    if(0 == best_jet_index ){ 
       ptag_bestJet_eta = *ptag_pfjets08_eta;
       ptag_bestJet_phi = *ptag_pfjets08_phi;
       ptag_bestJet_m = *ptag_pfjets08_m;
       ptag_bestJet_pt = *ptag_pfjets08_pt;
       ptag_bestJet_e = *ptag_pfjets08_e;
       ptag_bestJet_tau1 = *ptag_pfjets08_tau1;
       ptag_bestJet_tau2 = *ptag_pfjets08_tau2;
       ptag_bestJet_tau3 = *ptag_pfjets08_tau3;
       ptag_bestJet_tau31 = *ptag_pfjets08_tau31;
       ptag_bestJet_tau32 = *ptag_pfjets08_tau32;
       ptag_bestJet_tau21 = *ptag_pfjets08_tau21;
    } else 
    if(1 == best_jet_index ){ 
       ptag_bestJet_eta = *ptag_pfjets08_softDroppedJet_eta;
       ptag_bestJet_phi = *ptag_pfjets08_softDroppedJet_phi;
       ptag_bestJet_m = *ptag_pfjets08_softDroppedJet_m;
       ptag_bestJet_pt = *ptag_pfjets08_softDroppedJet_pt;
       ptag_bestJet_e = *ptag_pfjets08_softDroppedJet_e;
       ptag_bestJet_tau1 = *ptag_pfjets08_softDroppedJet_tau1;
       ptag_bestJet_tau2 = *ptag_pfjets08_softDroppedJet_tau2;
       ptag_bestJet_tau3 = *ptag_pfjets08_softDroppedJet_tau3;
       ptag_bestJet_tau31 = *ptag_pfjets08_softDroppedJet_tau31;
       ptag_bestJet_tau32 = *ptag_pfjets08_softDroppedJet_tau32;
       ptag_bestJet_tau21 = *ptag_pfjets08_softDroppedJet_tau21;
    } else 
    if(2 == best_jet_index ){ 
       ptag_bestJet_eta = *ptag_pfjets08_leadingSoftDroppedSubJet_eta;
       ptag_bestJet_phi = *ptag_pfjets08_leadingSoftDroppedSubJet_phi;
       ptag_bestJet_m = *ptag_pfjets08_leadingSoftDroppedSubJet_m;
       ptag_bestJet_pt = *ptag_pfjets08_leadingSoftDroppedSubJet_pt;
       ptag_bestJet_e = *ptag_pfjets08_leadingSoftDroppedSubJet_e;
       ptag_bestJet_tau1 = *ptag_pfjets08_leadingSoftDroppedSubJet_tau1;
       ptag_bestJet_tau2 = *ptag_pfjets08_leadingSoftDroppedSubJet_tau2;
       ptag_bestJet_tau3 = *ptag_pfjets08_leadingSoftDroppedSubJet_tau3;
       ptag_bestJet_tau31 = *ptag_pfjets08_leadingSoftDroppedSubJet_tau31;
       ptag_bestJet_tau32 = *ptag_pfjets08_leadingSoftDroppedSubJet_tau32;
       ptag_bestJet_tau21 = *ptag_pfjets08_leadingSoftDroppedSubJet_tau21;
    } else 
    if(3 == best_jet_index ){ 
       ptag_bestJet_eta = *ptag_pfjets08_trailingSoftDroppedSubJet_eta;
       ptag_bestJet_phi = *ptag_pfjets08_trailingSoftDroppedSubJet_phi;
       ptag_bestJet_m = *ptag_pfjets08_trailingSoftDroppedSubJet_m;
       ptag_bestJet_pt = *ptag_pfjets08_trailingSoftDroppedSubJet_pt;
       ptag_bestJet_e = *ptag_pfjets08_trailingSoftDroppedSubJet_e;
       ptag_bestJet_tau1 = *ptag_pfjets08_trailingSoftDroppedSubJet_tau1;
       ptag_bestJet_tau2 = *ptag_pfjets08_trailingSoftDroppedSubJet_tau2;
       ptag_bestJet_tau3 = *ptag_pfjets08_trailingSoftDroppedSubJet_tau3;
       ptag_bestJet_tau31 = *ptag_pfjets08_trailingSoftDroppedSubJet_tau31;
       ptag_bestJet_tau32 = *ptag_pfjets08_trailingSoftDroppedSubJet_tau32;
       ptag_bestJet_tau21 = *ptag_pfjets08_trailingSoftDroppedSubJet_tau21;
    } else 
    if(4 == best_jet_index ){ 
       ptag_bestJet_eta = *ptag_pfjets02_eta;
       ptag_bestJet_phi = *ptag_pfjets02_phi;
       ptag_bestJet_m = *ptag_pfjets02_m;
       ptag_bestJet_pt = *ptag_pfjets02_pt;
       ptag_bestJet_e = *ptag_pfjets02_e;
       ptag_bestJet_tau1 = *ptag_pfjets02_tau1;
       ptag_bestJet_tau2 = *ptag_pfjets02_tau2;
       ptag_bestJet_tau3 = *ptag_pfjets02_tau3;
       ptag_bestJet_tau31 = *ptag_pfjets02_tau31;
       ptag_bestJet_tau32 = *ptag_pfjets02_tau32;
       ptag_bestJet_tau21 = *ptag_pfjets02_tau21;
    } else 
    if(5 == best_jet_index ){ 
       ptag_bestJet_eta = *ptag_pfjets02_softDroppedJet_eta;
       ptag_bestJet_phi = *ptag_pfjets02_softDroppedJet_phi;
       ptag_bestJet_m = *ptag_pfjets02_softDroppedJet_m;
       ptag_bestJet_pt = *ptag_pfjets02_softDroppedJet_pt;
       ptag_bestJet_e = *ptag_pfjets02_softDroppedJet_e;
       ptag_bestJet_tau1 = *ptag_pfjets02_softDroppedJet_tau1;
       ptag_bestJet_tau2 = *ptag_pfjets02_softDroppedJet_tau2;
       ptag_bestJet_tau3 = *ptag_pfjets02_softDroppedJet_tau3;
       ptag_bestJet_tau31 = *ptag_pfjets02_softDroppedJet_tau31;
       ptag_bestJet_tau32 = *ptag_pfjets02_softDroppedJet_tau32;
       ptag_bestJet_tau21 = *ptag_pfjets02_softDroppedJet_tau21;
    } else 
    if(6 == best_jet_index ){ 
       ptag_bestJet_eta = *ptag_pfjets02_leadingSoftDroppedSubJet_eta;
       ptag_bestJet_phi = *ptag_pfjets02_leadingSoftDroppedSubJet_phi;
       ptag_bestJet_m = *ptag_pfjets02_leadingSoftDroppedSubJet_m;
       ptag_bestJet_pt = *ptag_pfjets02_leadingSoftDroppedSubJet_pt;
       ptag_bestJet_e = *ptag_pfjets02_leadingSoftDroppedSubJet_e;
       ptag_bestJet_tau1 = *ptag_pfjets02_leadingSoftDroppedSubJet_tau1;
       ptag_bestJet_tau2 = *ptag_pfjets02_leadingSoftDroppedSubJet_tau2;
       ptag_bestJet_tau3 = *ptag_pfjets02_leadingSoftDroppedSubJet_tau3;
       ptag_bestJet_tau31 = *ptag_pfjets02_leadingSoftDroppedSubJet_tau31;
       ptag_bestJet_tau32 = *ptag_pfjets02_leadingSoftDroppedSubJet_tau32;
       ptag_bestJet_tau21 = *ptag_pfjets02_leadingSoftDroppedSubJet_tau21;
    } else 
    if(7 == best_jet_index ){ 
       ptag_bestJet_eta = *ptag_pfjets02_trailingSoftDroppedSubJet_eta;
       ptag_bestJet_phi = *ptag_pfjets02_trailingSoftDroppedSubJet_phi;
       ptag_bestJet_m = *ptag_pfjets02_trailingSoftDroppedSubJet_m;
       ptag_bestJet_pt = *ptag_pfjets02_trailingSoftDroppedSubJet_pt;
       ptag_bestJet_e = *ptag_pfjets02_trailingSoftDroppedSubJet_e;
       ptag_bestJet_tau1 = *ptag_pfjets02_trailingSoftDroppedSubJet_tau1;
       ptag_bestJet_tau2 = *ptag_pfjets02_trailingSoftDroppedSubJet_tau2;
       ptag_bestJet_tau3 = *ptag_pfjets02_trailingSoftDroppedSubJet_tau3;
       ptag_bestJet_tau31 = *ptag_pfjets02_trailingSoftDroppedSubJet_tau31;
       ptag_bestJet_tau32 = *ptag_pfjets02_trailingSoftDroppedSubJet_tau32;
       ptag_bestJet_tau21 = *ptag_pfjets02_trailingSoftDroppedSubJet_tau21;
    } else 
    if(8 == best_jet_index ){ 
       ptag_bestJet_eta = *ptag_pfjets04_eta;
       ptag_bestJet_phi = *ptag_pfjets04_phi;
       ptag_bestJet_m = *ptag_pfjets04_m;
       ptag_bestJet_pt = *ptag_pfjets04_pt;
       ptag_bestJet_e = *ptag_pfjets04_e;
       ptag_bestJet_tau1 = *ptag_pfjets04_tau1;
       ptag_bestJet_tau2 = *ptag_pfjets04_tau2;
       ptag_bestJet_tau3 = *ptag_pfjets04_tau3;
       ptag_bestJet_tau31 = *ptag_pfjets04_tau31;
       ptag_bestJet_tau32 = *ptag_pfjets04_tau32;
       ptag_bestJet_tau21 = *ptag_pfjets04_tau21;
    } else 
    if(9 == best_jet_index ){ 
       ptag_bestJet_eta = *ptag_pfjets04_softDroppedJet_eta;
       ptag_bestJet_phi = *ptag_pfjets04_softDroppedJet_phi;
       ptag_bestJet_m = *ptag_pfjets04_softDroppedJet_m;
       ptag_bestJet_pt = *ptag_pfjets04_softDroppedJet_pt;
       ptag_bestJet_e = *ptag_pfjets04_softDroppedJet_e;
       ptag_bestJet_tau1 = *ptag_pfjets04_softDroppedJet_tau1;
       ptag_bestJet_tau2 = *ptag_pfjets04_softDroppedJet_tau2;
       ptag_bestJet_tau3 = *ptag_pfjets04_softDroppedJet_tau3;
       ptag_bestJet_tau31 = *ptag_pfjets04_softDroppedJet_tau31;
       ptag_bestJet_tau32 = *ptag_pfjets04_softDroppedJet_tau32;
       ptag_bestJet_tau21 = *ptag_pfjets04_softDroppedJet_tau21;
    } else 
    if(10 == best_jet_index ){ 
       ptag_bestJet_eta = *ptag_pfjets04_leadingSoftDroppedSubJet_eta;
       ptag_bestJet_phi = *ptag_pfjets04_leadingSoftDroppedSubJet_phi;
       ptag_bestJet_m = *ptag_pfjets04_leadingSoftDroppedSubJet_m;
       ptag_bestJet_pt = *ptag_pfjets04_leadingSoftDroppedSubJet_pt;
       ptag_bestJet_e = *ptag_pfjets04_leadingSoftDroppedSubJet_e;
       ptag_bestJet_tau1 = *ptag_pfjets04_leadingSoftDroppedSubJet_tau1;
       ptag_bestJet_tau2 = *ptag_pfjets04_leadingSoftDroppedSubJet_tau2;
       ptag_bestJet_tau3 = *ptag_pfjets04_leadingSoftDroppedSubJet_tau3;
       ptag_bestJet_tau31 = *ptag_pfjets04_leadingSoftDroppedSubJet_tau31;
       ptag_bestJet_tau32 = *ptag_pfjets04_leadingSoftDroppedSubJet_tau32;
       ptag_bestJet_tau21 = *ptag_pfjets04_leadingSoftDroppedSubJet_tau21;
    } else 
    if(11 == best_jet_index ){ 
       ptag_bestJet_eta = *ptag_pfjets04_trailingSoftDroppedSubJet_eta;
       ptag_bestJet_phi = *ptag_pfjets04_trailingSoftDroppedSubJet_phi;
       ptag_bestJet_m = *ptag_pfjets04_trailingSoftDroppedSubJet_m;
       ptag_bestJet_pt = *ptag_pfjets04_trailingSoftDroppedSubJet_pt;
       ptag_bestJet_e = *ptag_pfjets04_trailingSoftDroppedSubJet_e;
       ptag_bestJet_tau1 = *ptag_pfjets04_trailingSoftDroppedSubJet_tau1;
       ptag_bestJet_tau2 = *ptag_pfjets04_trailingSoftDroppedSubJet_tau2;
       ptag_bestJet_tau3 = *ptag_pfjets04_trailingSoftDroppedSubJet_tau3;
       ptag_bestJet_tau31 = *ptag_pfjets04_trailingSoftDroppedSubJet_tau31;
       ptag_bestJet_tau32 = *ptag_pfjets04_trailingSoftDroppedSubJet_tau32;
       ptag_bestJet_tau21 = *ptag_pfjets04_trailingSoftDroppedSubJet_tau21;
    } else 
    {}
    //[[[end]]]

    //cout << "<<" << endl;
    //cout << "best_jet_index = " << best_jet_index << endl; 
    //ptag_best_jet.Print();
    photon_x_ptag_bestJet    = photon.Dot(ptag_best_jet);
    dPhi_Photon_ptag_bestJet = photon.DeltaPhi(ptag_best_jet);
    dR_Photon_ptag_bestJet   = photon.DeltaR(ptag_best_jet);
    M_Photon_ptag_bestJet    = (photon + ptag_best_jet).M();
    bjet_x_ptag_bestJet      = bjet.Dot(ptag_best_jet);
    dPhi_bjet_ptag_bestJet   = bjet.DeltaPhi(ptag_best_jet);
    dR_bjet_ptag_bestJet     = bjet.DeltaR(ptag_best_jet);
    //cout << ">>" << endl;

    // fill photon quark candidtate 
         if(best_photon_jet_index == 2)  best_quark_index = 3;
    else if(best_photon_jet_index == 3)  best_quark_index = 2;
    else if(best_photon_jet_index == 6)  best_quark_index = 7;
    else if(best_photon_jet_index == 7)  best_quark_index = 6;
    else if(best_photon_jet_index == 10) best_quark_index = 11;
    else if(best_photon_jet_index == 11) best_quark_index = 10;
    if(best_quark_index != -1) ptag_quarkCandidate = jets.at( best_quark_index );
    else                       ptag_quarkCandidate = TLorentzVector();
    ptag_quarkCandidate_m    = ptag_quarkCandidate.M();
    ptag_quarkCandidate_eta  = ptag_quarkCandidate.Eta();
    ptag_quarkCandidate_phi  = ptag_quarkCandidate.Phi();
    ptag_quarkCandidate_pt   = ptag_quarkCandidate.Pt();

    // OTHER
    if(*dR_lepton_btag_pfjets08 < 0) (*dR_lepton_btag_pfjets08) = -1.0;

    // histograms here  ====================>
    (*weight) *= xfactor;
    tree_out->Fill();
    // if(i_passed++ > 1000) break;
  }

  if( top_cut ) cout << top_cut << " <=top_cut" << endl;

  file_out->cd();
  tree_out->Write();
  file_out->Close();
  return 0;
}

struct tmva_analyse_file_args{
  TFile * file;
  double weight;
  string out_path;
  bool do_top_cut;
};

void tmva_analyse_file_wrapper(void * a){
  tmva_analyse_file_args * args = (tmva_analyse_file_args*) a; 
  cout << "Start with " << args->out_path << endl;
  tmva_analyse_file( args->file, args->out_path, args->weight, args->do_top_cut);
  cout << "Done with " << args->out_path << endl;
  // TThread::Exit(0);
  args->file->Close();
  return 0;
}

void tmva_analyse(string samples_path, string out_path){
  // string samples_path = "/afs/cern.ch/work/p/pmandrik/fcc_100TeV/4_analyser/heppy/OUTPUT/fcnc_mar_18";
  auto channels  = get_channals( samples_path );

  return;
  vector<TThread*> threads;
  for(auto channel : channels){

    // if(channel.physic_name != "mgp8_pp_tajets" and channel.physic_name != "mgp8_pp_jjja_5f") continue;

    tmva_analyse_file_args * args = new tmva_analyse_file_args();
    args->file     = TFile::Open( channel.file_names.at(0).c_str() );
    args->weight   = channel.xsec / channel.weight_sum;
    args->out_path = out_path + "/" + channel.physic_name + ".root";
    args->do_top_cut = ((channel.physic_name == "mgp8_pp_tt_aut_cut500") or (channel.physic_name == "mgp8_pp_tt_act_cut500"));
/*
    cout << "tread(" << tread << ") " << "!>begin " << channel.file_names.at(0) << " " << channel.xsec << endl;
    TFile * file = TFile::Open( channel.file_names.at(0).c_str() );
    tmva_analyse_file( file, out_path + "/" + channel.physic_name + ".root", channel.xsec / channel.weight_sum);
    cout << "tread(" << tread << ") " << "!>done" << endl;
*/
    TThread* new_thread = new TThread(channel.physic_name.c_str(), &tmva_analyse_file_wrapper, (void*) args);
    threads.push_back( new_thread );
  }

  threads_care( threads, 5 );
}







