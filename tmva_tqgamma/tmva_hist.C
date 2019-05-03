
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRoot.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootAnalyser.cpp"
#include "tmva_use_comp.C"

using namespace mRoot;

void tune_for_stat_hist(TH1D * h, bool tune){
  if(tune) return;
  return;
  int nbinsx = h->GetXaxis()->GetNbins();
  for(int i = 1; i <= nbinsx; i++){
    if( h->GetBinContent(i) < 1.0 ) h->SetBinContent(i, 1.0);
  }
}

map<string, PlotVariable> get_variables_new(){
  map<string, PlotVariable> custom_variables;

  /*[[[cog

    import cog
    import sys

    import imp

    mRootCOG = imp.load_source('mRootCOG', '/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootCOG.py')
    mRootCOGAnalyser = imp.load_source('mRootCOGAnalyser', '/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootCOGAnalyser.py')

    def get_jet_name(jet): # "ptag_pfjets02"
      RAD = "R=0." + jet[-1]
      TAG = ""
      if "ptag" == jet[0:4] : TAG = "#gamma-"
      if "btag" == jet[0:4] : TAG = "b-"
      if "BestMass_jet" == jet :
        TAG = "Best t-Mass_{j+#gamma} "
        R = "R=0.8"
      if "BestTopMass_jet" == jet : 
        TAG = "Best t-jet candidate "
        RAD = "R=0.8"
      if "SecondTopMass_jet" == jet : 
        TAG = "Second t-jet candidate "
        RAD = "R=0.8"

      TYPE = "PF"
      if "calo" in jet : TYPE = "Calo"
      if "trk"  in jet : TYPE = "Track"
      
      jet_name = TAG + TYPE + "-Jet " + RAD + " "
      return jet_name
      
    
    default_plots = []
    tmva_plots    = []
    cut_plots     = []
    corr_plots    = []

    custom_variables = []
    # custom_variables["weight_k"] = mRootCOGAnalyser.PlotVariable("weight_k", "BDT kinematic", -1, 1);
    # custom_variables["weight_b"] = mRootCOGAnalyser.PlotVariable("weight_b", "BDT top jet tagging", -1, 1);
    # custom_variables["weight_p"] = mRootCOGAnalyser.PlotVariable("weight_p", "BDT photon jet tagging", -1, 1);
    # custom_variables["weight_f"] = mRootCOGAnalyser.PlotVariable("weight_f", "BDT combined", -1, 1);

    custom_variables += [ mRootCOGAnalyser.PlotVariable("photon_eta", "Photon #eta", -3, 3),
                          mRootCOGAnalyser.PlotVariable("photon_pt", "Photon p_{T} [GeV]", 0, 3500),
                          # mRootCOGAnalyser.PlotVariable("bJet_eta", "b-jet #eta", -3, 3),
                          # mRootCOGAnalyser.PlotVariable("bJet_pt", "b-jet p_{T} [GeV]", 0, 3500),
                          mRootCOGAnalyser.PlotVariable("top_pt", "t p_{T} [GeV]", 0, 3500),
                          mRootCOGAnalyser.PlotVariable("ptag_bestJet_m",   "Best #gamma-jet M [GeV]", 0, 400, 50),
                          mRootCOGAnalyser.PlotVariable("ptag_bestJet_pt",  "Best #gamma-jet p_{T} [GeV]", 0, 3500),
                          mRootCOGAnalyser.PlotVariable("ptag_bestJet_eta", "Best #gamma-jet #eta", -3, 3),
                          mRootCOGAnalyser.PlotVariable("btag_pfjets04_eta", "b-jet #eta", -3, 3),

                          mRootCOGAnalyser.PlotVariable("ptag_bestJet_tau1",  "best #gamma-jet #tau_{1}",  0, 0.7),
                          mRootCOGAnalyser.PlotVariable("ptag_bestJet_tau2",  "best #gamma-jet #tau_{2}",  0, 0.5),
                          mRootCOGAnalyser.PlotVariable("ptag_bestJet_tau3",  "best #gamma-jet #tau_{3}",  0, 0.4),
                          mRootCOGAnalyser.PlotVariable("ptag_bestJet_tau31", "best #gamma-jet #tau_{31}", 0, 1),
                          mRootCOGAnalyser.PlotVariable("ptag_bestJet_tau32", "best #gamma-jet #tau_{32}", 0, 1.0),
                          mRootCOGAnalyser.PlotVariable("ptag_bestJet_tau21", "best #gamma-jet #tau_{21}", 0, 1.0),

                          mRootCOGAnalyser.PlotVariable("ptag_pfjets08_tau1",  "#gamma-PF-jet R=0.8 #tau_{1}",  0, 0.7),
                          mRootCOGAnalyser.PlotVariable("ptag_pfjets08_tau2",  "#gamma-PF-jet R=0.8 #tau_{2}",  0, 0.5),
                          mRootCOGAnalyser.PlotVariable("ptag_pfjets08_tau3",  "#gamma-PF-jet R=0.8 #tau_{3}",  0, 0.4),
                          mRootCOGAnalyser.PlotVariable("ptag_pfjets08_tau31", "#gamma-PF-jet R=0.8 #tau_{31}", 0, 1),
                          mRootCOGAnalyser.PlotVariable("ptag_pfjets08_tau32", "#gamma-PF-jet R=0.8 #tau_{32}", 0, 1.0),
                          mRootCOGAnalyser.PlotVariable("ptag_pfjets08_tau21", "#gamma-PF-jet R=0.8 #tau_{21}", 0, 1.0),

                          mRootCOGAnalyser.PlotVariable("btag_pfjets08_tau1",  "b-PF-jet R=0.8 #tau_{1}",  0, 1.0, draw_mode="b"),
                          mRootCOGAnalyser.PlotVariable("btag_pfjets08_tau2",  "b-PF-jet R=0.8 #tau_{2}",  0, 1.0, draw_mode="b"),
                          mRootCOGAnalyser.PlotVariable("btag_pfjets08_tau3",  "b-PF-jet R=0.8 #tau_{3}",  0, 1.0, draw_mode="b"),
                          mRootCOGAnalyser.PlotVariable("btag_pfjets08_tau31", "b-PF-jet R=0.8 #tau_{31}", 0, 1.0, draw_mode="b"),
                          mRootCOGAnalyser.PlotVariable("btag_pfjets08_tau32", "b-PF-jet R=0.8 #tau_{32}", 0, 1.0, draw_mode="b"),
                          mRootCOGAnalyser.PlotVariable("btag_pfjets08_tau21", "b-PF-jet R=0.8 #tau_{21}", 0, 1.0, draw_mode="b"),

                          mRootCOGAnalyser.PlotVariable("btag_pfjets04_tau1",  "b-PF-jet R=0.4 #tau_{1}",  0, 1.0, draw_mode="b"),
                          mRootCOGAnalyser.PlotVariable("btag_pfjets04_tau2",  "b-PF-jet R=0.4 #tau_{2}",  0, 1.0, draw_mode="b"),
                          mRootCOGAnalyser.PlotVariable("btag_pfjets04_tau3",  "b-PF-jet R=0.4 #tau_{3}",  0, 1.0, draw_mode="b"),
                          mRootCOGAnalyser.PlotVariable("btag_pfjets04_tau31", "b-PF-jet R=0.4 #tau_{31}", 0, 1.0, draw_mode="b"),
                          mRootCOGAnalyser.PlotVariable("btag_pfjets04_tau32", "b-PF-jet R=0.4 #tau_{32}", 0, 1.0, draw_mode="b"),
                          mRootCOGAnalyser.PlotVariable("btag_pfjets04_tau21", "b-PF-jet R=0.4 #tau_{21}", 0, 1.0, draw_mode="b"),

                          mRootCOGAnalyser.PlotVariable("photon_x_ptag_bestJet",    "(P_{#gamma}, P_{best j#gamma-et}) [GeV^{2}]",    0, 1000),

                          mRootCOGAnalyser.PlotVariable("lepton_x_btag_pfjets08",        "(P_{lepton}, P_{b-PF-jet R=0.8}) [GeV^{2}]",    0, 10**5),
                          mRootCOGAnalyser.PlotVariable("dPhi_lepton_btag_pfjets08",     "#Delta #phi(lepton, b-PF-jet R=0.8)", -1.5, 1.5),
                          mRootCOGAnalyser.PlotVariable("dR_lepton_btag_pfjets08",       "#Delta R(lepton, b-PF-jet R=0.8)",    0, 3.0),
                          mRootCOGAnalyser.PlotVariable("lepton_x_btag_pfjets04",        "(P_{lepton}, P_{b-PF-jet R=0.4}) [GeV^{2}]",    0, 10**5),
                          mRootCOGAnalyser.PlotVariable("dPhi_lepton_btag_pfjets04",     "#Delta #phi(lepton, b-PF-jet R=0.4)", -1.0, 1.0),
                          mRootCOGAnalyser.PlotVariable("dR_lepton_btag_pfjets04",       "#Delta R(lepton, b-PF-jet R=0.4)",    0, 1.2),

                          mRootCOGAnalyser.PlotVariable("M_lepton_met",        "M(lepton, MET) [GeV]",                    0, 800),
                          mRootCOGAnalyser.PlotVariable("M_bjet_lepton_met",   "M(lepton, MET, b-PF-jet R=0.4) [GeV]",    0, 800),

                          mRootCOGAnalyser.PlotVariable("dPhi_Photon_ptag_bestJet", '#Delta #phi(#gamma, best #gamma-jet)', -0.5, 0.5),
                          mRootCOGAnalyser.PlotVariable("dR_Photon_ptag_bestJet",   '#Delta R(#gamma, best #gamma-jet)',    0, 0.4),
                          mRootCOGAnalyser.PlotVariable("M_Photon_ptag_bestJet",    'M(#gamma, best #gamma-jet)',           0, 400),
                          mRootCOGAnalyser.PlotVariable("bjet_x_ptag_bestJet",      '(P_{b-jet}, P_{best #gamma-jet}) [GeV^{2}]',     0, 10**7),
                          mRootCOGAnalyser.PlotVariable("dPhi_bjet_ptag_bestJet",   '#Delta #phi(b-jet, best #gamma-jet)',  -3.14, 3.14),
                          mRootCOGAnalyser.PlotVariable("dR_bjet_ptag_bestJet",     '#Delta R(b-jet, best #gamma-jet)',     0, 5),

                          mRootCOGAnalyser.PlotVariable("lepton_relIso",     'lepton relative isolation',     0, 50),
                          mRootCOGAnalyser.PlotVariable("photon_relIso",     '#gamma relative isolation',     0, 25),


                          mRootCOGAnalyser.PlotVariable("photon_x_ptag_pfjets08",   '(P_{#gamma-jet}, P_{#gamma-jet}) [GeV^{2}]',     0, 30000),
                          mRootCOGAnalyser.PlotVariable("bjet_x_ptag_pfjets08",     '(P_{b-jet}, P_{#gamma-jet}) [GeV^{2}]',          0, 10000000),

                          mRootCOGAnalyser.PlotVariable("weight_tune_3_BDT_0_000",     'BDT',     -0.7, 0.8, 10000),
                          mRootCOGAnalyser.PlotVariable("weight_tune_3_BDT_1_000",     'BDT',     -0.7, 0.8, 10000),
                          mRootCOGAnalyser.PlotVariable("weight_tune_3_BDT_2_000",     'BDT',     -0.7, 0.8, 10000),
                          mRootCOGAnalyser.PlotVariable("weight_tune_3_BDT_3_000",     'BDT',     -0.7, 0.8, 10000),
                          mRootCOGAnalyser.PlotVariable("weight_tune_3_BDT_4_000",     'BDT',     -0.7, 0.8, 10000),
                          mRootCOGAnalyser.PlotVariable("weight_tune_3_BDT_5_000",     'BDT',     -0.7, 0.8, 10000),
                          mRootCOGAnalyser.PlotVariable("weight_tune_3_BDT_6_000",     'BDT',     -0.7, 0.8, 10000),

                          mRootCOGAnalyser.PlotVariable("weight_tune_5_BDT_3_000",     'BDT',     -0.7, 0.8, 10000),
                         ]
    best_BDT_cut = "weight_tune_3_BDT_3_000"

    jets = ["ptag_pfjets02",  "ptag_pfjets04",   "ptag_pfjets08",   "btag_pfjets02",   "btag_pfjets04",   "btag_pfjets08", 
            "ptag_calojets02","ptag_calojets04", "ptag_calojets08", "btag_calojets02", "btag_calojets04", "btag_calojets08",
            "ptag_trkjets02", "ptag_trkjets04",  "ptag_trkjets08",  "btag_trkjets02",  "btag_trkjets04",  "btag_trkjets08",
            "BestMass_jet",   "BestTopMass_jet", "SecondTopMass_jet"
           ]
    fixes  = ["_e", "_pt", "_m", ]
    # fixes += ["_tau1", "_tau2", "_tau3", "_tau31", "_tau32", "_tau21"]
                                      
    fixes_names  = ["E [GeV]", "p_{T} [GeV]", "M [GeV]", "p_{T} [GeV]", "M [GeV]", "E [GeV]", "#tau_{1}", "#tau_{2}", "#tau_{3}", "#tau_{31}", "#tau_{32}", "#tau_{21}"]
    fixes_xmaxs  = [8000,       2000,          400,       8000,          400,       8000,      1,          1,          1,          1,           1,           1         ]
    for jet in jets:
      mode = "ab"
      if "calo" in jet : mode = ""
      if "trk"  in jet : mode = "" 
      for fix, axis, xmax in zip(fixes, fixes_names, fixes_xmaxs):
        nbins = 30
        if axis == "M [GeV]" : nbins = 50
        jet_name = get_jet_name( jet )
        custom_variables += [ mRootCOGAnalyser.PlotVariable(jet + fix, jet_name + axis, 0, xmax, nbins, mode) ]

    fixes       = ["_softDroppedJet_pt", "_softDroppedJet_m", "_softDroppedJet_e",
                   "_leadingSoftDroppedSubJet_pt", "_leadingSoftDroppedSubJet_m", "_leadingSoftDroppedSubJet_e", 
                   "_trailingSoftDroppedSubJet_pt", "_trailingSoftDroppedSubJet_m", "_trailingSoftDroppedSubJet_e"]
    fixes_prefixes = ["Soft-dropped", "Soft-dropped", "Soft-dropped",
                      "Leading", "Leading", "Leading",
                      "Trailing", "Trailing", "Trailing"]
    fixes_names = ["Pt [GeV]", "M [GeV]", "E [GeV]", "Pt [GeV]", "M [GeV]", "E [GeV]", "Pt [GeV]", "M [GeV]", "E [GeV]"]
    fixes_xmaxs = [8000,             400,      8000,       8000,       400,      8000,       8000,       400,     8000 ]
    for jet in jets:
      R = "(R=0." + jet[-1]+")"
      TAG = "#gamma-" if "p" == jet[0] else "b-"
      TYPE = ""
      mode = "ab"
      if jet in ["BestMass_jet", "BestTopMass_jet", "SecondTopMass_jet"]: mode = ""
      SUB = "Sub"
      #if TAG == "b-" : mode = ""
      if "calo" in jet : 
        mode = ""
        TYPE = "Calo-"
      if "trk"  in jet :
        mode = "" 
        TYPE = "Track-"
      for fix, axis, xmax, prefix in zip(fixes, fixes_names, fixes_xmaxs, fixes_prefixes):
        SUB = "Sub"
        if "Soft-dropped" == prefix : SUB = ""
        nbins = 30
        if axis == "M [GeV]" : nbins = 50
        jet_name = prefix + " " + TAG + TYPE + "" + SUB + "jet " + R + " "
        custom_variables += [ mRootCOGAnalyser.PlotVariable(jet + fix, jet_name + axis, 0, xmax, nbins, mode) ]

    prefixes    = ['dPhi_Photon_',                 'dR_Photon_',                 'M_Photon_',           'dPhi_bjet_',                   'dR_bjet_',         ]
    fixes_names = ['#Delta #phi(#gamma, %(jet)s)', '#Delta R(#gamma, %(jet)s)',  'M(#gamma, %(jet)s)',  '#Delta #phi(b-jet, %(jet)s)',  '#Delta R(b-jet)',  ]
    fixes_xmaxs = [0.35,                           0.35,                        400,                     3.14,                          8,                  ]
    for jet in jets:
      mode = ""
      if "calo" in jet : mode = ""
      if "trk"  in jet : mode = ""
      if jet == "ptag_pfjets04" : mode = "ab"
      for fix, axis, xmax in zip(prefixes, fixes_names, fixes_xmaxs):
        nbins = 30
        jet_name = get_jet_name( jet )
        axis_name = axis % {"jet" : jet_name}
        custom_variables += [ mRootCOGAnalyser.PlotVariable(fix + jet, axis_name, 0, xmax, nbins, mode) ]

    # correlation plots
    corr_plots    = []
    corr_plots.append( mRootCOGAnalyser.CorrPlot( "ptag_pfjets08_softDroppedJet_m", "ptag_pfjets08_leadingSoftDroppedSubJet_m"))
    corr_plots.append( mRootCOGAnalyser.CorrPlot( "ptag_pfjets08_softDroppedJet_m", "ptag_pfjets08_softDroppedJet_pt"))
    corr_plots.append( mRootCOGAnalyser.CorrPlot( "ptag_pfjets08_softDroppedJet_m", "ptag_pfjets04_softDroppedJet_m"))
    corr_plots.append( mRootCOGAnalyser.CorrPlot( "ptag_pfjets08_m", "ptag_pfjets08_softDroppedJet_m"))
    corr_plots.append( mRootCOGAnalyser.CorrPlot( "BestTopMass_jet_m", "SecondTopMass_jet_m" ))
    corr_plots.append( mRootCOGAnalyser.CorrPlot( "ptag_bestJet_eta", "btag_pfjets04_eta" ))

    for cor in corr_plots:
      for var in custom_variables:
        if var.key == cor.var_x: cor.var_x = var
        if var.key == cor.var_y: cor.var_y = var
      if type(cor.var_x) == type("12"): print("////", cor.var_x, " <====-")
      if type(cor.var_y) == type("12"): print("////", cor.var_y, " <====-")
        

    # comparable plots
    comp_plots = []
    # p-tag
    comp_plots.append( mRootCOGAnalyser.CompPlot( "mgp8_pp_tt_aut", "t #rightarrow #gamma u", ["ptag_pfjets04_m",  "ptag_pfjets08_m", "ptag_calojets04_m",  "ptag_calojets08_m", "ptag_trkjets04_m",  "ptag_trkjets08_m"], ["PF-Jet R=0.4", "PF-Jet R=0.8", "Calo-Jet R=0.4", "Calo-Jet R=0.8", "Track-Jet R=0.4", "Track-Jet R=0.8"], "#gamma-Jet M [GeV]") )
    comp_plots.append( mRootCOGAnalyser.CompPlot( "mgp8_pp_tt_aut", "t #rightarrow #gamma u", ["btag_pfjets04_m",  "btag_pfjets08_m", "btag_calojets04_m",  "btag_calojets08_m", "btag_trkjets04_m",  "btag_trkjets08_m"], ["PF-Jet R=0.4", "PF-Jet R=0.8", "Calo-Jet R=0.4", "Calo-Jet R=0.8", "Track-Jet R=0.4", "Track-Jet R=0.8"], "b-Jet M [GeV]") )
    
    comp_plots.append( mRootCOGAnalyser.CompPlot( "mgp8_pp_tt_aut", "t #rightarrow #gamma u", ["ptag_pfjets02_m",  "ptag_pfjets04_m",  "ptag_pfjets08_m", "ptag_bestJet_m"], ["PF-Jet R=0.2", "PF-Jet R=0.4", "PF-Jet R=0.8", "Best Jet"], "#gamma-Jet M [GeV]") )
    comp_plots.append( mRootCOGAnalyser.CompPlot( "mgp8_pp_tt_aut", "t #rightarrow #gamma u", ["ptag_pfjets02_m",  "ptag_pfjets04_m",  "ptag_pfjets08_m", "ptag_bestJet_m"], ["PF-Jet R=0.2", "PF-Jet R=0.4", "PF-Jet R=0.8", "Best Jet"], "#gamma-Jet M [GeV]", "nolog") )
    (comp_plots[-1]).xmin = 150
    (comp_plots[-1]).xmax = 250
    comp_plots.append( mRootCOGAnalyser.CompPlot( "mgp8_pp_tt_aut", "t #rightarrow #gamma u", ["ptag_pfjets02_softDroppedJet_m",  "ptag_pfjets04_softDroppedJet_m",  "ptag_pfjets08_softDroppedJet_m", "ptag_bestJet_m"], ["SoftDropped PF-Jet R=0.2", "SoftDropped PF-Jet R=0.4", "SoftDropped PF-Jet R=0.8", "Best Jet"], "#gamma-Jet M [GeV]") )
    comp_plots.append( mRootCOGAnalyser.CompPlot( "mgp8_pp_tt_aut", "t #rightarrow #gamma u", ["ptag_pfjets02_softDroppedJet_m",  "ptag_pfjets04_softDroppedJet_m",  "ptag_pfjets08_softDroppedJet_m", "ptag_bestJet_m"], ["SoftDropped PF-Jet R=0.2", "SoftDropped PF-Jet R=0.4", "SoftDropped PF-Jet R=0.8", "Best Jet"], "#gamma-Jet M [GeV]", "nolog") )
    (comp_plots[-1]).xmin = 150
    (comp_plots[-1]).xmax = 250

    comp_plots.append( mRootCOGAnalyser.CompPlot( "mgp8_pp_tt_aut", "t #rightarrow #gamma u", ["ptag_pfjets02_softDroppedJet_m",  "ptag_pfjets04_softDroppedJet_m",  "ptag_pfjets08_softDroppedJet_m", "ptag_bestJet_m"], ["SoftDropped PF-Jet R=0.2", "SoftDropped PF-Jet R=0.4", "SoftDropped PF-Jet R=0.8", "Best Jet"], "#gamma-Jet M [GeV]", "nolog") )
    comp_plots.append( mRootCOGAnalyser.CompPlot( "mgp8_pp_tt_aut", "t #rightarrow #gamma u", ["ptag_pfjets02_m",  "ptag_pfjets04_m",  "ptag_pfjets08_m", "ptag_pfjets02_softDroppedJet_m",  "ptag_pfjets04_softDroppedJet_m",  "ptag_pfjets08_softDroppedJet_m"], ["PF-Jet R=0.2", "PF-Jet R=0.4", "PF-Jet R=0.8", "SoftDropped PF-Jet R=0.2", "SoftDropped PF-Jet R=0.4", "SoftDropped PF-Jet R=0.8"], "#gamma-Jet M [GeV]") )
    comp_plots.append( mRootCOGAnalyser.CompPlot( "mgp8_pp_tt_aut", "t #rightarrow #gamma u", ["ptag_pfjets02_e",  "ptag_pfjets04_e",  "ptag_pfjets08_e", "ptag_pfjets02_softDroppedJet_e",  "ptag_pfjets04_softDroppedJet_e",  "ptag_pfjets08_softDroppedJet_e"], ["PF-Jet R=0.2", "PF-Jet R=0.4", "PF-Jet R=0.8", "SoftDropped PF-Jet R=0.2", "SoftDropped PF-Jet R=0.4", "SoftDropped PF-Jet R=0.8"], "#gamma-Jet E [GeV]") )
    # b-tag
    comp_plots.append( mRootCOGAnalyser.CompPlot( "mgp8_pp_tt_aut", "t #rightarrow #gamma u", ["btag_pfjets02_m",   "btag_pfjets04_m",   "btag_pfjets08_m"], ["PF-Jet R=0.2", "PF-Jet R=0.4", "PF-Jet R=0.8"], "b-Jet M [GeV]") )
    comp_plots.append( mRootCOGAnalyser.CompPlot( "mgp8_pp_tt_aut", "t #rightarrow #gamma u", ["btag_pfjets04_m", "btag_pfjets04_softDroppedJet_m",   "btag_pfjets08_m", "btag_pfjets08_softDroppedJet_m"], 
                                                                             ["PF-Jet R=0.4", "SoftDropped PF-Jet R=0.4", "PF-Jet R=0.8", "SoftDropped PF-Jet R=0.8"], "b-Jet M [GeV]") )
    comp_plots.append( mRootCOGAnalyser.CompPlot( "mgp8_pp_tt_aut", "t #rightarrow #gamma u", ["btag_pfjets04_m", "btag_pfjets04_softDroppedJet_m",   "btag_pfjets08_m", "btag_pfjets08_softDroppedJet_m"], 
                                                                             ["PF-Jet R=0.4", "SoftDropped PF-Jet R=0.4", "PF-Jet R=0.8", "SoftDropped PF-Jet R=0.8"], "b-Jet M [GeV]", "nolog") )

    comp_plots.append( mRootCOGAnalyser.CompPlot( "mgp8_pp_tt_aut", "t #rightarrow #gamma u", 
     ["ptag_pfjets08_m", "ptag_pfjets08_softDroppedJet_m", "ptag_pfjets08_leadingSoftDroppedSubJet_m", "ptag_pfjets08_trailingSoftDroppedSubJet_m"], 
     ["PF-Jet R=0.8",  "SoftDropped PF-Jet R=0.8", "Leading PF-SubJet R=0.8", "Trailing PF-SubJet R=0.8"], "#gamma-Jet M [GeV]") )

    comp_plots.append( mRootCOGAnalyser.CompPlot( "mgp8_pp_tt_aut", "t #rightarrow #gamma u", 
     ["ptag_pfjets08_e", "ptag_pfjets08_softDroppedJet_e", "ptag_pfjets08_leadingSoftDroppedSubJet_e", "ptag_pfjets08_trailingSoftDroppedSubJet_e"], 
     ["PF-Jet R=0.8",  "SoftDropped PF-Jet R=0.8", "Leading PF-SubJet R=0.8", "Trailing PF-SubJet R=0.8"], "#gamma-Jet E [GeV]") )

    comp_plots.append( mRootCOGAnalyser.CompPlot( "mgp8_pp_tt_aut", "t #rightarrow #gamma u", 
     ["ptag_pfjets04_m", "ptag_pfjets04_softDroppedJet_m", "ptag_pfjets04_leadingSoftDroppedSubJet_m", "ptag_pfjets04_trailingSoftDroppedSubJet_m"], 
     ["PF-Jet R=0.4",  "SoftDropped PF-Jet R=0.4", "Leading PF-SubJet R=0.4", "Trailing PF-SubJet R=0.4"], "#gamma-Jet M [GeV]") )

    comp_plots.append( mRootCOGAnalyser.CompPlot( "mgp8_pp_tt_aut", "t #rightarrow #gamma u", 
     ["ptag_pfjets04_e", "ptag_pfjets04_softDroppedJet_e", "ptag_pfjets04_leadingSoftDroppedSubJet_e", "ptag_pfjets04_trailingSoftDroppedSubJet_e"], 
     ["PF-Jet R=0.4",  "SoftDropped PF-Jet R=0.4", "Leading PF-SubJet R=0.4", "Trailing PF-SubJet R=0.4"], "#gamma-Jet E [GeV]") )

    # cut plots
    cut_plots = [ ]

    for i in xrange(0, 10):
      cut = "%.2f" % float(i / 10.)
      cut_plots.append( mRootCOGAnalyser.CutPlot("ptag_pfjets08_softDroppedJet_m", "*v_" + best_BDT_cut + " > " + cut, " "))
      cut_plots.append( mRootCOGAnalyser.CutPlot("BestTopMass_jet_m", "*v_" + best_BDT_cut + " > " + cut, " "))

    cut_plots = [ ]

    cut_plots.append( mRootCOGAnalyser.CutPlot("ptag_pfjets08_m", "*v_ptag_pfjets08_m < 140", "PF-Jet R=0.8 M<140") )
    cut_plots.append( mRootCOGAnalyser.CutPlot("ptag_pfjets08_leadingSoftDroppedSubJet_m", "*v_ptag_pfjets08_softDroppedJet_m > 250", "SoftDropped PF-Jet R=0.8 M>250") )
    cut_plots.append( mRootCOGAnalyser.CutPlot("ptag_pfjets04_softDroppedJet_m", "*v_ptag_pfjets08_softDroppedJet_m > 250", "SoftDropped PF-Jet R=0.8 M>250") )

    vars_tmva = ["ptag_bestJet_m",
      "ptag_bestJet_pt", "ptag_bestJet_eta", 
      "photon_pt",
      "dR_Photon_ptag_bestJet", "dPhi_Photon_ptag_bestJet",
      "ptag_bestJet_tau32", "ptag_bestJet_tau21",
      "ptag_pfjets08_tau32", "ptag_pfjets08_tau21",
      "SecondTopMass_jet_m", "BestTopMass_jet_m",
      "btag_pfjets08_m",
      "btag_pfjets04_pt", "btag_pfjets04_eta", 
      "btag_pfjets08_tau21", "btag_pfjets08_tau32",
      #"lepton_x_bjet",
      "dR_lepton_btag_pfjets08",
      "dR_bjet_ptag_bestJet", "dPhi_bjet_ptag_bestJet",
      "bjet_x_ptag_bestJet",
      #"lepton_x_ptag_pfjets08",
      #"photon_x_bjet"
    ]
    #for variable in vars_tmva:
    #  cut_plots.append( mRootCOGAnalyser.CutPlot(variable, "*v_weight_tune_3_BDT_0_000 > 0.0", "BDT > 0.0") )


    signal_cut   = "(*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)"
    signal_title = "Best #gamma-Jet M#in[150, 200] GeV"
    cut_vars  = ["ptag_bestJet_tau1", "ptag_bestJet_tau2", "ptag_bestJet_tau3", "ptag_bestJet_tau31", "ptag_bestJet_tau32", "ptag_bestJet_tau21"]
    cut_vars += ["ptag_pfjets08_tau1", "ptag_pfjets08_tau2", "ptag_pfjets08_tau3", "ptag_pfjets08_tau31", "ptag_pfjets08_tau32", "ptag_pfjets08_tau21"]
    cut_vars += ['photon_x_ptag_bestJet','dPhi_Photon_ptag_bestJet','dR_Photon_ptag_bestJet','M_Photon_ptag_bestJet', 'bjet_x_ptag_bestJet', 'dPhi_bjet_ptag_bestJet', 'dR_bjet_ptag_bestJet']
    for cut in cut_vars :
      cut_plots.append( mRootCOGAnalyser.CutPlot(cut, signal_cut, signal_title) )
    cut_plots.append( mRootCOGAnalyser.CutPlot(cut, signal_cut, signal_title) )

    for var in custom_variables:
      for cut in cut_plots:
        if var.key == cut.var: cut.var = var

    for var in custom_variables:
      cog.outl( 'custom_variables["' + var.key + '"] = PlotVariable("' + var.name + '", ' + str(var.xmin) + ', ' + str(var.xmax) +');')
      if 'a' in var.draw_mode : default_plots  += [ mRootCOGAnalyser.DefaultPlot(var, "default") ]
      if 'b' in var.draw_mode : tmva_plots     += [ mRootCOGAnalyser.DefaultPlot(var, "tmva") ]
      
      if not var.draw_mode : 
        var.frozen = True
        for comp in comp_plots:
          if var.key in comp.vars:
            var.frozen = False

        for cut in cut_plots:
          if var.key == cut.var.key:
            var.frozen = False

        for cor in corr_plots:
          if var.key == cor.var_x or var.key == cor.var_y :
            var.frozen = False
      
  ]]]*/
  custom_variables["photon_eta"] = PlotVariable("Photon #eta", -3, 3);
  custom_variables["photon_pt"] = PlotVariable("Photon p_{T} [GeV]", 0, 3500);
  custom_variables["top_pt"] = PlotVariable("t p_{T} [GeV]", 0, 3500);
  custom_variables["ptag_bestJet_m"] = PlotVariable("Best #gamma-jet M [GeV]", 0, 400);
  custom_variables["ptag_bestJet_pt"] = PlotVariable("Best #gamma-jet p_{T} [GeV]", 0, 3500);
  custom_variables["ptag_bestJet_eta"] = PlotVariable("Best #gamma-jet #eta", -3, 3);
  custom_variables["btag_pfjets04_eta"] = PlotVariable("b-jet #eta", -3, 3);
  custom_variables["ptag_bestJet_tau1"] = PlotVariable("best #gamma-jet #tau_{1}", 0, 0.7);
  custom_variables["ptag_bestJet_tau2"] = PlotVariable("best #gamma-jet #tau_{2}", 0, 0.5);
  custom_variables["ptag_bestJet_tau3"] = PlotVariable("best #gamma-jet #tau_{3}", 0, 0.4);
  custom_variables["ptag_bestJet_tau31"] = PlotVariable("best #gamma-jet #tau_{31}", 0, 1);
  custom_variables["ptag_bestJet_tau32"] = PlotVariable("best #gamma-jet #tau_{32}", 0, 1.0);
  custom_variables["ptag_bestJet_tau21"] = PlotVariable("best #gamma-jet #tau_{21}", 0, 1.0);
  custom_variables["ptag_pfjets08_tau1"] = PlotVariable("#gamma-PF-jet R=0.8 #tau_{1}", 0, 0.7);
  custom_variables["ptag_pfjets08_tau2"] = PlotVariable("#gamma-PF-jet R=0.8 #tau_{2}", 0, 0.5);
  custom_variables["ptag_pfjets08_tau3"] = PlotVariable("#gamma-PF-jet R=0.8 #tau_{3}", 0, 0.4);
  custom_variables["ptag_pfjets08_tau31"] = PlotVariable("#gamma-PF-jet R=0.8 #tau_{31}", 0, 1);
  custom_variables["ptag_pfjets08_tau32"] = PlotVariable("#gamma-PF-jet R=0.8 #tau_{32}", 0, 1.0);
  custom_variables["ptag_pfjets08_tau21"] = PlotVariable("#gamma-PF-jet R=0.8 #tau_{21}", 0, 1.0);
  custom_variables["btag_pfjets08_tau1"] = PlotVariable("b-PF-jet R=0.8 #tau_{1}", 0, 1.0);
  custom_variables["btag_pfjets08_tau2"] = PlotVariable("b-PF-jet R=0.8 #tau_{2}", 0, 1.0);
  custom_variables["btag_pfjets08_tau3"] = PlotVariable("b-PF-jet R=0.8 #tau_{3}", 0, 1.0);
  custom_variables["btag_pfjets08_tau31"] = PlotVariable("b-PF-jet R=0.8 #tau_{31}", 0, 1.0);
  custom_variables["btag_pfjets08_tau32"] = PlotVariable("b-PF-jet R=0.8 #tau_{32}", 0, 1.0);
  custom_variables["btag_pfjets08_tau21"] = PlotVariable("b-PF-jet R=0.8 #tau_{21}", 0, 1.0);
  custom_variables["btag_pfjets04_tau1"] = PlotVariable("b-PF-jet R=0.4 #tau_{1}", 0, 1.0);
  custom_variables["btag_pfjets04_tau2"] = PlotVariable("b-PF-jet R=0.4 #tau_{2}", 0, 1.0);
  custom_variables["btag_pfjets04_tau3"] = PlotVariable("b-PF-jet R=0.4 #tau_{3}", 0, 1.0);
  custom_variables["btag_pfjets04_tau31"] = PlotVariable("b-PF-jet R=0.4 #tau_{31}", 0, 1.0);
  custom_variables["btag_pfjets04_tau32"] = PlotVariable("b-PF-jet R=0.4 #tau_{32}", 0, 1.0);
  custom_variables["btag_pfjets04_tau21"] = PlotVariable("b-PF-jet R=0.4 #tau_{21}", 0, 1.0);
  custom_variables["photon_x_ptag_bestJet"] = PlotVariable("(P_{#gamma}, P_{best j#gamma-et}) [GeV^{2}]", 0, 1000);
  custom_variables["lepton_x_btag_pfjets08"] = PlotVariable("(P_{lepton}, P_{b-PF-jet R=0.8}) [GeV^{2}]", 0, 100000);
  custom_variables["dPhi_lepton_btag_pfjets08"] = PlotVariable("#Delta #phi(lepton, b-PF-jet R=0.8)", -1.5, 1.5);
  custom_variables["dR_lepton_btag_pfjets08"] = PlotVariable("#Delta R(lepton, b-PF-jet R=0.8)", 0, 3.0);
  custom_variables["lepton_x_btag_pfjets04"] = PlotVariable("(P_{lepton}, P_{b-PF-jet R=0.4}) [GeV^{2}]", 0, 100000);
  custom_variables["dPhi_lepton_btag_pfjets04"] = PlotVariable("#Delta #phi(lepton, b-PF-jet R=0.4)", -1.0, 1.0);
  custom_variables["dR_lepton_btag_pfjets04"] = PlotVariable("#Delta R(lepton, b-PF-jet R=0.4)", 0, 1.2);
  custom_variables["M_lepton_met"] = PlotVariable("M(lepton, MET) [GeV]", 0, 800);
  custom_variables["M_bjet_lepton_met"] = PlotVariable("M(lepton, MET, b-PF-jet R=0.4) [GeV]", 0, 800);
  custom_variables["dPhi_Photon_ptag_bestJet"] = PlotVariable("#Delta #phi(#gamma, best #gamma-jet)", -0.5, 0.5);
  custom_variables["dR_Photon_ptag_bestJet"] = PlotVariable("#Delta R(#gamma, best #gamma-jet)", 0, 0.4);
  custom_variables["M_Photon_ptag_bestJet"] = PlotVariable("M(#gamma, best #gamma-jet)", 0, 400);
  custom_variables["bjet_x_ptag_bestJet"] = PlotVariable("(P_{b-jet}, P_{best #gamma-jet}) [GeV^{2}]", 0, 10000000);
  custom_variables["dPhi_bjet_ptag_bestJet"] = PlotVariable("#Delta #phi(b-jet, best #gamma-jet)", -3.14, 3.14);
  custom_variables["dR_bjet_ptag_bestJet"] = PlotVariable("#Delta R(b-jet, best #gamma-jet)", 0, 5);
  custom_variables["lepton_relIso"] = PlotVariable("lepton relative isolation", 0, 50);
  custom_variables["photon_relIso"] = PlotVariable("#gamma relative isolation", 0, 25);
  custom_variables["photon_x_ptag_pfjets08"] = PlotVariable("(P_{#gamma-jet}, P_{#gamma-jet}) [GeV^{2}]", 0, 30000);
  custom_variables["bjet_x_ptag_pfjets08"] = PlotVariable("(P_{b-jet}, P_{#gamma-jet}) [GeV^{2}]", 0, 10000000);
  custom_variables["weight_tune_3_BDT_0_000"] = PlotVariable("BDT", -0.7, 0.8);
  custom_variables["weight_tune_3_BDT_1_000"] = PlotVariable("BDT", -0.7, 0.8);
  custom_variables["weight_tune_3_BDT_2_000"] = PlotVariable("BDT", -0.7, 0.8);
  custom_variables["weight_tune_3_BDT_3_000"] = PlotVariable("BDT", -0.7, 0.8);
  custom_variables["weight_tune_3_BDT_4_000"] = PlotVariable("BDT", -0.7, 0.8);
  custom_variables["weight_tune_3_BDT_5_000"] = PlotVariable("BDT", -0.7, 0.8);
  custom_variables["weight_tune_3_BDT_6_000"] = PlotVariable("BDT", -0.7, 0.8);
  custom_variables["weight_tune_5_BDT_3_000"] = PlotVariable("BDT", -0.7, 0.8);
  custom_variables["ptag_pfjets02_e"] = PlotVariable("#gamma-PF-Jet R=0.2 E [GeV]", 0, 8000);
  custom_variables["ptag_pfjets02_pt"] = PlotVariable("#gamma-PF-Jet R=0.2 p_{T} [GeV]", 0, 2000);
  custom_variables["ptag_pfjets02_m"] = PlotVariable("#gamma-PF-Jet R=0.2 M [GeV]", 0, 400);
  custom_variables["ptag_pfjets04_e"] = PlotVariable("#gamma-PF-Jet R=0.4 E [GeV]", 0, 8000);
  custom_variables["ptag_pfjets04_pt"] = PlotVariable("#gamma-PF-Jet R=0.4 p_{T} [GeV]", 0, 2000);
  custom_variables["ptag_pfjets04_m"] = PlotVariable("#gamma-PF-Jet R=0.4 M [GeV]", 0, 400);
  custom_variables["ptag_pfjets08_e"] = PlotVariable("#gamma-PF-Jet R=0.8 E [GeV]", 0, 8000);
  custom_variables["ptag_pfjets08_pt"] = PlotVariable("#gamma-PF-Jet R=0.8 p_{T} [GeV]", 0, 2000);
  custom_variables["ptag_pfjets08_m"] = PlotVariable("#gamma-PF-Jet R=0.8 M [GeV]", 0, 400);
  custom_variables["btag_pfjets02_e"] = PlotVariable("b-PF-Jet R=0.2 E [GeV]", 0, 8000);
  custom_variables["btag_pfjets02_pt"] = PlotVariable("b-PF-Jet R=0.2 p_{T} [GeV]", 0, 2000);
  custom_variables["btag_pfjets02_m"] = PlotVariable("b-PF-Jet R=0.2 M [GeV]", 0, 400);
  custom_variables["btag_pfjets04_e"] = PlotVariable("b-PF-Jet R=0.4 E [GeV]", 0, 8000);
  custom_variables["btag_pfjets04_pt"] = PlotVariable("b-PF-Jet R=0.4 p_{T} [GeV]", 0, 2000);
  custom_variables["btag_pfjets04_m"] = PlotVariable("b-PF-Jet R=0.4 M [GeV]", 0, 400);
  custom_variables["btag_pfjets08_e"] = PlotVariable("b-PF-Jet R=0.8 E [GeV]", 0, 8000);
  custom_variables["btag_pfjets08_pt"] = PlotVariable("b-PF-Jet R=0.8 p_{T} [GeV]", 0, 2000);
  custom_variables["btag_pfjets08_m"] = PlotVariable("b-PF-Jet R=0.8 M [GeV]", 0, 400);
  custom_variables["ptag_calojets02_e"] = PlotVariable("#gamma-Calo-Jet R=0.2 E [GeV]", 0, 8000);
  custom_variables["ptag_calojets02_pt"] = PlotVariable("#gamma-Calo-Jet R=0.2 p_{T} [GeV]", 0, 2000);
  custom_variables["ptag_calojets02_m"] = PlotVariable("#gamma-Calo-Jet R=0.2 M [GeV]", 0, 400);
  custom_variables["ptag_calojets04_e"] = PlotVariable("#gamma-Calo-Jet R=0.4 E [GeV]", 0, 8000);
  custom_variables["ptag_calojets04_pt"] = PlotVariable("#gamma-Calo-Jet R=0.4 p_{T} [GeV]", 0, 2000);
  custom_variables["ptag_calojets04_m"] = PlotVariable("#gamma-Calo-Jet R=0.4 M [GeV]", 0, 400);
  custom_variables["ptag_calojets08_e"] = PlotVariable("#gamma-Calo-Jet R=0.8 E [GeV]", 0, 8000);
  custom_variables["ptag_calojets08_pt"] = PlotVariable("#gamma-Calo-Jet R=0.8 p_{T} [GeV]", 0, 2000);
  custom_variables["ptag_calojets08_m"] = PlotVariable("#gamma-Calo-Jet R=0.8 M [GeV]", 0, 400);
  custom_variables["btag_calojets02_e"] = PlotVariable("b-Calo-Jet R=0.2 E [GeV]", 0, 8000);
  custom_variables["btag_calojets02_pt"] = PlotVariable("b-Calo-Jet R=0.2 p_{T} [GeV]", 0, 2000);
  custom_variables["btag_calojets02_m"] = PlotVariable("b-Calo-Jet R=0.2 M [GeV]", 0, 400);
  custom_variables["btag_calojets04_e"] = PlotVariable("b-Calo-Jet R=0.4 E [GeV]", 0, 8000);
  custom_variables["btag_calojets04_pt"] = PlotVariable("b-Calo-Jet R=0.4 p_{T} [GeV]", 0, 2000);
  custom_variables["btag_calojets04_m"] = PlotVariable("b-Calo-Jet R=0.4 M [GeV]", 0, 400);
  custom_variables["btag_calojets08_e"] = PlotVariable("b-Calo-Jet R=0.8 E [GeV]", 0, 8000);
  custom_variables["btag_calojets08_pt"] = PlotVariable("b-Calo-Jet R=0.8 p_{T} [GeV]", 0, 2000);
  custom_variables["btag_calojets08_m"] = PlotVariable("b-Calo-Jet R=0.8 M [GeV]", 0, 400);
  custom_variables["ptag_trkjets02_e"] = PlotVariable("#gamma-Track-Jet R=0.2 E [GeV]", 0, 8000);
  custom_variables["ptag_trkjets02_pt"] = PlotVariable("#gamma-Track-Jet R=0.2 p_{T} [GeV]", 0, 2000);
  custom_variables["ptag_trkjets02_m"] = PlotVariable("#gamma-Track-Jet R=0.2 M [GeV]", 0, 400);
  custom_variables["ptag_trkjets04_e"] = PlotVariable("#gamma-Track-Jet R=0.4 E [GeV]", 0, 8000);
  custom_variables["ptag_trkjets04_pt"] = PlotVariable("#gamma-Track-Jet R=0.4 p_{T} [GeV]", 0, 2000);
  custom_variables["ptag_trkjets04_m"] = PlotVariable("#gamma-Track-Jet R=0.4 M [GeV]", 0, 400);
  custom_variables["ptag_trkjets08_e"] = PlotVariable("#gamma-Track-Jet R=0.8 E [GeV]", 0, 8000);
  custom_variables["ptag_trkjets08_pt"] = PlotVariable("#gamma-Track-Jet R=0.8 p_{T} [GeV]", 0, 2000);
  custom_variables["ptag_trkjets08_m"] = PlotVariable("#gamma-Track-Jet R=0.8 M [GeV]", 0, 400);
  custom_variables["btag_trkjets02_e"] = PlotVariable("b-Track-Jet R=0.2 E [GeV]", 0, 8000);
  custom_variables["btag_trkjets02_pt"] = PlotVariable("b-Track-Jet R=0.2 p_{T} [GeV]", 0, 2000);
  custom_variables["btag_trkjets02_m"] = PlotVariable("b-Track-Jet R=0.2 M [GeV]", 0, 400);
  custom_variables["btag_trkjets04_e"] = PlotVariable("b-Track-Jet R=0.4 E [GeV]", 0, 8000);
  custom_variables["btag_trkjets04_pt"] = PlotVariable("b-Track-Jet R=0.4 p_{T} [GeV]", 0, 2000);
  custom_variables["btag_trkjets04_m"] = PlotVariable("b-Track-Jet R=0.4 M [GeV]", 0, 400);
  custom_variables["btag_trkjets08_e"] = PlotVariable("b-Track-Jet R=0.8 E [GeV]", 0, 8000);
  custom_variables["btag_trkjets08_pt"] = PlotVariable("b-Track-Jet R=0.8 p_{T} [GeV]", 0, 2000);
  custom_variables["btag_trkjets08_m"] = PlotVariable("b-Track-Jet R=0.8 M [GeV]", 0, 400);
  custom_variables["BestMass_jet_e"] = PlotVariable("Best t-Mass_{j+#gamma} PF-Jet R=0.t E [GeV]", 0, 8000);
  custom_variables["BestMass_jet_pt"] = PlotVariable("Best t-Mass_{j+#gamma} PF-Jet R=0.t p_{T} [GeV]", 0, 2000);
  custom_variables["BestMass_jet_m"] = PlotVariable("Best t-Mass_{j+#gamma} PF-Jet R=0.t M [GeV]", 0, 400);
  custom_variables["BestTopMass_jet_e"] = PlotVariable("Best t-jet candidate PF-Jet R=0.8 E [GeV]", 0, 8000);
  custom_variables["BestTopMass_jet_pt"] = PlotVariable("Best t-jet candidate PF-Jet R=0.8 p_{T} [GeV]", 0, 2000);
  custom_variables["BestTopMass_jet_m"] = PlotVariable("Best t-jet candidate PF-Jet R=0.8 M [GeV]", 0, 400);
  custom_variables["SecondTopMass_jet_e"] = PlotVariable("Second t-jet candidate PF-Jet R=0.8 E [GeV]", 0, 8000);
  custom_variables["SecondTopMass_jet_pt"] = PlotVariable("Second t-jet candidate PF-Jet R=0.8 p_{T} [GeV]", 0, 2000);
  custom_variables["SecondTopMass_jet_m"] = PlotVariable("Second t-jet candidate PF-Jet R=0.8 M [GeV]", 0, 400);
  custom_variables["ptag_pfjets02_softDroppedJet_pt"] = PlotVariable("Soft-dropped #gamma-jet (R=0.2) Pt [GeV]", 0, 8000);
  custom_variables["ptag_pfjets02_softDroppedJet_m"] = PlotVariable("Soft-dropped #gamma-jet (R=0.2) M [GeV]", 0, 400);
  custom_variables["ptag_pfjets02_softDroppedJet_e"] = PlotVariable("Soft-dropped #gamma-jet (R=0.2) E [GeV]", 0, 8000);
  custom_variables["ptag_pfjets02_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading #gamma-Subjet (R=0.2) Pt [GeV]", 0, 8000);
  custom_variables["ptag_pfjets02_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading #gamma-Subjet (R=0.2) M [GeV]", 0, 400);
  custom_variables["ptag_pfjets02_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading #gamma-Subjet (R=0.2) E [GeV]", 0, 8000);
  custom_variables["ptag_pfjets02_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing #gamma-Subjet (R=0.2) Pt [GeV]", 0, 8000);
  custom_variables["ptag_pfjets02_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing #gamma-Subjet (R=0.2) M [GeV]", 0, 400);
  custom_variables["ptag_pfjets02_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing #gamma-Subjet (R=0.2) E [GeV]", 0, 8000);
  custom_variables["ptag_pfjets04_softDroppedJet_pt"] = PlotVariable("Soft-dropped #gamma-jet (R=0.4) Pt [GeV]", 0, 8000);
  custom_variables["ptag_pfjets04_softDroppedJet_m"] = PlotVariable("Soft-dropped #gamma-jet (R=0.4) M [GeV]", 0, 400);
  custom_variables["ptag_pfjets04_softDroppedJet_e"] = PlotVariable("Soft-dropped #gamma-jet (R=0.4) E [GeV]", 0, 8000);
  custom_variables["ptag_pfjets04_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading #gamma-Subjet (R=0.4) Pt [GeV]", 0, 8000);
  custom_variables["ptag_pfjets04_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading #gamma-Subjet (R=0.4) M [GeV]", 0, 400);
  custom_variables["ptag_pfjets04_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading #gamma-Subjet (R=0.4) E [GeV]", 0, 8000);
  custom_variables["ptag_pfjets04_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing #gamma-Subjet (R=0.4) Pt [GeV]", 0, 8000);
  custom_variables["ptag_pfjets04_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing #gamma-Subjet (R=0.4) M [GeV]", 0, 400);
  custom_variables["ptag_pfjets04_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing #gamma-Subjet (R=0.4) E [GeV]", 0, 8000);
  custom_variables["ptag_pfjets08_softDroppedJet_pt"] = PlotVariable("Soft-dropped #gamma-jet (R=0.8) Pt [GeV]", 0, 8000);
  custom_variables["ptag_pfjets08_softDroppedJet_m"] = PlotVariable("Soft-dropped #gamma-jet (R=0.8) M [GeV]", 0, 400);
  custom_variables["ptag_pfjets08_softDroppedJet_e"] = PlotVariable("Soft-dropped #gamma-jet (R=0.8) E [GeV]", 0, 8000);
  custom_variables["ptag_pfjets08_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading #gamma-Subjet (R=0.8) Pt [GeV]", 0, 8000);
  custom_variables["ptag_pfjets08_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading #gamma-Subjet (R=0.8) M [GeV]", 0, 400);
  custom_variables["ptag_pfjets08_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading #gamma-Subjet (R=0.8) E [GeV]", 0, 8000);
  custom_variables["ptag_pfjets08_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing #gamma-Subjet (R=0.8) Pt [GeV]", 0, 8000);
  custom_variables["ptag_pfjets08_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing #gamma-Subjet (R=0.8) M [GeV]", 0, 400);
  custom_variables["ptag_pfjets08_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing #gamma-Subjet (R=0.8) E [GeV]", 0, 8000);
  custom_variables["btag_pfjets02_softDroppedJet_pt"] = PlotVariable("Soft-dropped b-jet (R=0.2) Pt [GeV]", 0, 8000);
  custom_variables["btag_pfjets02_softDroppedJet_m"] = PlotVariable("Soft-dropped b-jet (R=0.2) M [GeV]", 0, 400);
  custom_variables["btag_pfjets02_softDroppedJet_e"] = PlotVariable("Soft-dropped b-jet (R=0.2) E [GeV]", 0, 8000);
  custom_variables["btag_pfjets02_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading b-Subjet (R=0.2) Pt [GeV]", 0, 8000);
  custom_variables["btag_pfjets02_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading b-Subjet (R=0.2) M [GeV]", 0, 400);
  custom_variables["btag_pfjets02_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading b-Subjet (R=0.2) E [GeV]", 0, 8000);
  custom_variables["btag_pfjets02_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing b-Subjet (R=0.2) Pt [GeV]", 0, 8000);
  custom_variables["btag_pfjets02_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing b-Subjet (R=0.2) M [GeV]", 0, 400);
  custom_variables["btag_pfjets02_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing b-Subjet (R=0.2) E [GeV]", 0, 8000);
  custom_variables["btag_pfjets04_softDroppedJet_pt"] = PlotVariable("Soft-dropped b-jet (R=0.4) Pt [GeV]", 0, 8000);
  custom_variables["btag_pfjets04_softDroppedJet_m"] = PlotVariable("Soft-dropped b-jet (R=0.4) M [GeV]", 0, 400);
  custom_variables["btag_pfjets04_softDroppedJet_e"] = PlotVariable("Soft-dropped b-jet (R=0.4) E [GeV]", 0, 8000);
  custom_variables["btag_pfjets04_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading b-Subjet (R=0.4) Pt [GeV]", 0, 8000);
  custom_variables["btag_pfjets04_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading b-Subjet (R=0.4) M [GeV]", 0, 400);
  custom_variables["btag_pfjets04_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading b-Subjet (R=0.4) E [GeV]", 0, 8000);
  custom_variables["btag_pfjets04_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing b-Subjet (R=0.4) Pt [GeV]", 0, 8000);
  custom_variables["btag_pfjets04_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing b-Subjet (R=0.4) M [GeV]", 0, 400);
  custom_variables["btag_pfjets04_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing b-Subjet (R=0.4) E [GeV]", 0, 8000);
  custom_variables["btag_pfjets08_softDroppedJet_pt"] = PlotVariable("Soft-dropped b-jet (R=0.8) Pt [GeV]", 0, 8000);
  custom_variables["btag_pfjets08_softDroppedJet_m"] = PlotVariable("Soft-dropped b-jet (R=0.8) M [GeV]", 0, 400);
  custom_variables["btag_pfjets08_softDroppedJet_e"] = PlotVariable("Soft-dropped b-jet (R=0.8) E [GeV]", 0, 8000);
  custom_variables["btag_pfjets08_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading b-Subjet (R=0.8) Pt [GeV]", 0, 8000);
  custom_variables["btag_pfjets08_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading b-Subjet (R=0.8) M [GeV]", 0, 400);
  custom_variables["btag_pfjets08_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading b-Subjet (R=0.8) E [GeV]", 0, 8000);
  custom_variables["btag_pfjets08_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing b-Subjet (R=0.8) Pt [GeV]", 0, 8000);
  custom_variables["btag_pfjets08_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing b-Subjet (R=0.8) M [GeV]", 0, 400);
  custom_variables["btag_pfjets08_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing b-Subjet (R=0.8) E [GeV]", 0, 8000);
  custom_variables["ptag_calojets02_softDroppedJet_pt"] = PlotVariable("Soft-dropped #gamma-Calo-jet (R=0.2) Pt [GeV]", 0, 8000);
  custom_variables["ptag_calojets02_softDroppedJet_m"] = PlotVariable("Soft-dropped #gamma-Calo-jet (R=0.2) M [GeV]", 0, 400);
  custom_variables["ptag_calojets02_softDroppedJet_e"] = PlotVariable("Soft-dropped #gamma-Calo-jet (R=0.2) E [GeV]", 0, 8000);
  custom_variables["ptag_calojets02_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading #gamma-Calo-Subjet (R=0.2) Pt [GeV]", 0, 8000);
  custom_variables["ptag_calojets02_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading #gamma-Calo-Subjet (R=0.2) M [GeV]", 0, 400);
  custom_variables["ptag_calojets02_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading #gamma-Calo-Subjet (R=0.2) E [GeV]", 0, 8000);
  custom_variables["ptag_calojets02_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing #gamma-Calo-Subjet (R=0.2) Pt [GeV]", 0, 8000);
  custom_variables["ptag_calojets02_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing #gamma-Calo-Subjet (R=0.2) M [GeV]", 0, 400);
  custom_variables["ptag_calojets02_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing #gamma-Calo-Subjet (R=0.2) E [GeV]", 0, 8000);
  custom_variables["ptag_calojets04_softDroppedJet_pt"] = PlotVariable("Soft-dropped #gamma-Calo-jet (R=0.4) Pt [GeV]", 0, 8000);
  custom_variables["ptag_calojets04_softDroppedJet_m"] = PlotVariable("Soft-dropped #gamma-Calo-jet (R=0.4) M [GeV]", 0, 400);
  custom_variables["ptag_calojets04_softDroppedJet_e"] = PlotVariable("Soft-dropped #gamma-Calo-jet (R=0.4) E [GeV]", 0, 8000);
  custom_variables["ptag_calojets04_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading #gamma-Calo-Subjet (R=0.4) Pt [GeV]", 0, 8000);
  custom_variables["ptag_calojets04_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading #gamma-Calo-Subjet (R=0.4) M [GeV]", 0, 400);
  custom_variables["ptag_calojets04_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading #gamma-Calo-Subjet (R=0.4) E [GeV]", 0, 8000);
  custom_variables["ptag_calojets04_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing #gamma-Calo-Subjet (R=0.4) Pt [GeV]", 0, 8000);
  custom_variables["ptag_calojets04_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing #gamma-Calo-Subjet (R=0.4) M [GeV]", 0, 400);
  custom_variables["ptag_calojets04_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing #gamma-Calo-Subjet (R=0.4) E [GeV]", 0, 8000);
  custom_variables["ptag_calojets08_softDroppedJet_pt"] = PlotVariable("Soft-dropped #gamma-Calo-jet (R=0.8) Pt [GeV]", 0, 8000);
  custom_variables["ptag_calojets08_softDroppedJet_m"] = PlotVariable("Soft-dropped #gamma-Calo-jet (R=0.8) M [GeV]", 0, 400);
  custom_variables["ptag_calojets08_softDroppedJet_e"] = PlotVariable("Soft-dropped #gamma-Calo-jet (R=0.8) E [GeV]", 0, 8000);
  custom_variables["ptag_calojets08_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading #gamma-Calo-Subjet (R=0.8) Pt [GeV]", 0, 8000);
  custom_variables["ptag_calojets08_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading #gamma-Calo-Subjet (R=0.8) M [GeV]", 0, 400);
  custom_variables["ptag_calojets08_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading #gamma-Calo-Subjet (R=0.8) E [GeV]", 0, 8000);
  custom_variables["ptag_calojets08_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing #gamma-Calo-Subjet (R=0.8) Pt [GeV]", 0, 8000);
  custom_variables["ptag_calojets08_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing #gamma-Calo-Subjet (R=0.8) M [GeV]", 0, 400);
  custom_variables["ptag_calojets08_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing #gamma-Calo-Subjet (R=0.8) E [GeV]", 0, 8000);
  custom_variables["btag_calojets02_softDroppedJet_pt"] = PlotVariable("Soft-dropped b-Calo-jet (R=0.2) Pt [GeV]", 0, 8000);
  custom_variables["btag_calojets02_softDroppedJet_m"] = PlotVariable("Soft-dropped b-Calo-jet (R=0.2) M [GeV]", 0, 400);
  custom_variables["btag_calojets02_softDroppedJet_e"] = PlotVariable("Soft-dropped b-Calo-jet (R=0.2) E [GeV]", 0, 8000);
  custom_variables["btag_calojets02_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading b-Calo-Subjet (R=0.2) Pt [GeV]", 0, 8000);
  custom_variables["btag_calojets02_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading b-Calo-Subjet (R=0.2) M [GeV]", 0, 400);
  custom_variables["btag_calojets02_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading b-Calo-Subjet (R=0.2) E [GeV]", 0, 8000);
  custom_variables["btag_calojets02_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing b-Calo-Subjet (R=0.2) Pt [GeV]", 0, 8000);
  custom_variables["btag_calojets02_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing b-Calo-Subjet (R=0.2) M [GeV]", 0, 400);
  custom_variables["btag_calojets02_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing b-Calo-Subjet (R=0.2) E [GeV]", 0, 8000);
  custom_variables["btag_calojets04_softDroppedJet_pt"] = PlotVariable("Soft-dropped b-Calo-jet (R=0.4) Pt [GeV]", 0, 8000);
  custom_variables["btag_calojets04_softDroppedJet_m"] = PlotVariable("Soft-dropped b-Calo-jet (R=0.4) M [GeV]", 0, 400);
  custom_variables["btag_calojets04_softDroppedJet_e"] = PlotVariable("Soft-dropped b-Calo-jet (R=0.4) E [GeV]", 0, 8000);
  custom_variables["btag_calojets04_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading b-Calo-Subjet (R=0.4) Pt [GeV]", 0, 8000);
  custom_variables["btag_calojets04_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading b-Calo-Subjet (R=0.4) M [GeV]", 0, 400);
  custom_variables["btag_calojets04_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading b-Calo-Subjet (R=0.4) E [GeV]", 0, 8000);
  custom_variables["btag_calojets04_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing b-Calo-Subjet (R=0.4) Pt [GeV]", 0, 8000);
  custom_variables["btag_calojets04_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing b-Calo-Subjet (R=0.4) M [GeV]", 0, 400);
  custom_variables["btag_calojets04_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing b-Calo-Subjet (R=0.4) E [GeV]", 0, 8000);
  custom_variables["btag_calojets08_softDroppedJet_pt"] = PlotVariable("Soft-dropped b-Calo-jet (R=0.8) Pt [GeV]", 0, 8000);
  custom_variables["btag_calojets08_softDroppedJet_m"] = PlotVariable("Soft-dropped b-Calo-jet (R=0.8) M [GeV]", 0, 400);
  custom_variables["btag_calojets08_softDroppedJet_e"] = PlotVariable("Soft-dropped b-Calo-jet (R=0.8) E [GeV]", 0, 8000);
  custom_variables["btag_calojets08_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading b-Calo-Subjet (R=0.8) Pt [GeV]", 0, 8000);
  custom_variables["btag_calojets08_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading b-Calo-Subjet (R=0.8) M [GeV]", 0, 400);
  custom_variables["btag_calojets08_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading b-Calo-Subjet (R=0.8) E [GeV]", 0, 8000);
  custom_variables["btag_calojets08_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing b-Calo-Subjet (R=0.8) Pt [GeV]", 0, 8000);
  custom_variables["btag_calojets08_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing b-Calo-Subjet (R=0.8) M [GeV]", 0, 400);
  custom_variables["btag_calojets08_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing b-Calo-Subjet (R=0.8) E [GeV]", 0, 8000);
  custom_variables["ptag_trkjets02_softDroppedJet_pt"] = PlotVariable("Soft-dropped #gamma-Track-jet (R=0.2) Pt [GeV]", 0, 8000);
  custom_variables["ptag_trkjets02_softDroppedJet_m"] = PlotVariable("Soft-dropped #gamma-Track-jet (R=0.2) M [GeV]", 0, 400);
  custom_variables["ptag_trkjets02_softDroppedJet_e"] = PlotVariable("Soft-dropped #gamma-Track-jet (R=0.2) E [GeV]", 0, 8000);
  custom_variables["ptag_trkjets02_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading #gamma-Track-Subjet (R=0.2) Pt [GeV]", 0, 8000);
  custom_variables["ptag_trkjets02_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading #gamma-Track-Subjet (R=0.2) M [GeV]", 0, 400);
  custom_variables["ptag_trkjets02_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading #gamma-Track-Subjet (R=0.2) E [GeV]", 0, 8000);
  custom_variables["ptag_trkjets02_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing #gamma-Track-Subjet (R=0.2) Pt [GeV]", 0, 8000);
  custom_variables["ptag_trkjets02_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing #gamma-Track-Subjet (R=0.2) M [GeV]", 0, 400);
  custom_variables["ptag_trkjets02_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing #gamma-Track-Subjet (R=0.2) E [GeV]", 0, 8000);
  custom_variables["ptag_trkjets04_softDroppedJet_pt"] = PlotVariable("Soft-dropped #gamma-Track-jet (R=0.4) Pt [GeV]", 0, 8000);
  custom_variables["ptag_trkjets04_softDroppedJet_m"] = PlotVariable("Soft-dropped #gamma-Track-jet (R=0.4) M [GeV]", 0, 400);
  custom_variables["ptag_trkjets04_softDroppedJet_e"] = PlotVariable("Soft-dropped #gamma-Track-jet (R=0.4) E [GeV]", 0, 8000);
  custom_variables["ptag_trkjets04_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading #gamma-Track-Subjet (R=0.4) Pt [GeV]", 0, 8000);
  custom_variables["ptag_trkjets04_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading #gamma-Track-Subjet (R=0.4) M [GeV]", 0, 400);
  custom_variables["ptag_trkjets04_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading #gamma-Track-Subjet (R=0.4) E [GeV]", 0, 8000);
  custom_variables["ptag_trkjets04_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing #gamma-Track-Subjet (R=0.4) Pt [GeV]", 0, 8000);
  custom_variables["ptag_trkjets04_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing #gamma-Track-Subjet (R=0.4) M [GeV]", 0, 400);
  custom_variables["ptag_trkjets04_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing #gamma-Track-Subjet (R=0.4) E [GeV]", 0, 8000);
  custom_variables["ptag_trkjets08_softDroppedJet_pt"] = PlotVariable("Soft-dropped #gamma-Track-jet (R=0.8) Pt [GeV]", 0, 8000);
  custom_variables["ptag_trkjets08_softDroppedJet_m"] = PlotVariable("Soft-dropped #gamma-Track-jet (R=0.8) M [GeV]", 0, 400);
  custom_variables["ptag_trkjets08_softDroppedJet_e"] = PlotVariable("Soft-dropped #gamma-Track-jet (R=0.8) E [GeV]", 0, 8000);
  custom_variables["ptag_trkjets08_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading #gamma-Track-Subjet (R=0.8) Pt [GeV]", 0, 8000);
  custom_variables["ptag_trkjets08_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading #gamma-Track-Subjet (R=0.8) M [GeV]", 0, 400);
  custom_variables["ptag_trkjets08_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading #gamma-Track-Subjet (R=0.8) E [GeV]", 0, 8000);
  custom_variables["ptag_trkjets08_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing #gamma-Track-Subjet (R=0.8) Pt [GeV]", 0, 8000);
  custom_variables["ptag_trkjets08_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing #gamma-Track-Subjet (R=0.8) M [GeV]", 0, 400);
  custom_variables["ptag_trkjets08_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing #gamma-Track-Subjet (R=0.8) E [GeV]", 0, 8000);
  custom_variables["btag_trkjets02_softDroppedJet_pt"] = PlotVariable("Soft-dropped b-Track-jet (R=0.2) Pt [GeV]", 0, 8000);
  custom_variables["btag_trkjets02_softDroppedJet_m"] = PlotVariable("Soft-dropped b-Track-jet (R=0.2) M [GeV]", 0, 400);
  custom_variables["btag_trkjets02_softDroppedJet_e"] = PlotVariable("Soft-dropped b-Track-jet (R=0.2) E [GeV]", 0, 8000);
  custom_variables["btag_trkjets02_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading b-Track-Subjet (R=0.2) Pt [GeV]", 0, 8000);
  custom_variables["btag_trkjets02_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading b-Track-Subjet (R=0.2) M [GeV]", 0, 400);
  custom_variables["btag_trkjets02_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading b-Track-Subjet (R=0.2) E [GeV]", 0, 8000);
  custom_variables["btag_trkjets02_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing b-Track-Subjet (R=0.2) Pt [GeV]", 0, 8000);
  custom_variables["btag_trkjets02_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing b-Track-Subjet (R=0.2) M [GeV]", 0, 400);
  custom_variables["btag_trkjets02_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing b-Track-Subjet (R=0.2) E [GeV]", 0, 8000);
  custom_variables["btag_trkjets04_softDroppedJet_pt"] = PlotVariable("Soft-dropped b-Track-jet (R=0.4) Pt [GeV]", 0, 8000);
  custom_variables["btag_trkjets04_softDroppedJet_m"] = PlotVariable("Soft-dropped b-Track-jet (R=0.4) M [GeV]", 0, 400);
  custom_variables["btag_trkjets04_softDroppedJet_e"] = PlotVariable("Soft-dropped b-Track-jet (R=0.4) E [GeV]", 0, 8000);
  custom_variables["btag_trkjets04_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading b-Track-Subjet (R=0.4) Pt [GeV]", 0, 8000);
  custom_variables["btag_trkjets04_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading b-Track-Subjet (R=0.4) M [GeV]", 0, 400);
  custom_variables["btag_trkjets04_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading b-Track-Subjet (R=0.4) E [GeV]", 0, 8000);
  custom_variables["btag_trkjets04_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing b-Track-Subjet (R=0.4) Pt [GeV]", 0, 8000);
  custom_variables["btag_trkjets04_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing b-Track-Subjet (R=0.4) M [GeV]", 0, 400);
  custom_variables["btag_trkjets04_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing b-Track-Subjet (R=0.4) E [GeV]", 0, 8000);
  custom_variables["btag_trkjets08_softDroppedJet_pt"] = PlotVariable("Soft-dropped b-Track-jet (R=0.8) Pt [GeV]", 0, 8000);
  custom_variables["btag_trkjets08_softDroppedJet_m"] = PlotVariable("Soft-dropped b-Track-jet (R=0.8) M [GeV]", 0, 400);
  custom_variables["btag_trkjets08_softDroppedJet_e"] = PlotVariable("Soft-dropped b-Track-jet (R=0.8) E [GeV]", 0, 8000);
  custom_variables["btag_trkjets08_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading b-Track-Subjet (R=0.8) Pt [GeV]", 0, 8000);
  custom_variables["btag_trkjets08_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading b-Track-Subjet (R=0.8) M [GeV]", 0, 400);
  custom_variables["btag_trkjets08_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading b-Track-Subjet (R=0.8) E [GeV]", 0, 8000);
  custom_variables["btag_trkjets08_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing b-Track-Subjet (R=0.8) Pt [GeV]", 0, 8000);
  custom_variables["btag_trkjets08_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing b-Track-Subjet (R=0.8) M [GeV]", 0, 400);
  custom_variables["btag_trkjets08_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing b-Track-Subjet (R=0.8) E [GeV]", 0, 8000);
  custom_variables["BestMass_jet_softDroppedJet_pt"] = PlotVariable("Soft-dropped b-jet (R=0.t) Pt [GeV]", 0, 8000);
  custom_variables["BestMass_jet_softDroppedJet_m"] = PlotVariable("Soft-dropped b-jet (R=0.t) M [GeV]", 0, 400);
  custom_variables["BestMass_jet_softDroppedJet_e"] = PlotVariable("Soft-dropped b-jet (R=0.t) E [GeV]", 0, 8000);
  custom_variables["BestMass_jet_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading b-Subjet (R=0.t) Pt [GeV]", 0, 8000);
  custom_variables["BestMass_jet_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading b-Subjet (R=0.t) M [GeV]", 0, 400);
  custom_variables["BestMass_jet_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading b-Subjet (R=0.t) E [GeV]", 0, 8000);
  custom_variables["BestMass_jet_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing b-Subjet (R=0.t) Pt [GeV]", 0, 8000);
  custom_variables["BestMass_jet_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing b-Subjet (R=0.t) M [GeV]", 0, 400);
  custom_variables["BestMass_jet_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing b-Subjet (R=0.t) E [GeV]", 0, 8000);
  custom_variables["BestTopMass_jet_softDroppedJet_pt"] = PlotVariable("Soft-dropped b-jet (R=0.t) Pt [GeV]", 0, 8000);
  custom_variables["BestTopMass_jet_softDroppedJet_m"] = PlotVariable("Soft-dropped b-jet (R=0.t) M [GeV]", 0, 400);
  custom_variables["BestTopMass_jet_softDroppedJet_e"] = PlotVariable("Soft-dropped b-jet (R=0.t) E [GeV]", 0, 8000);
  custom_variables["BestTopMass_jet_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading b-Subjet (R=0.t) Pt [GeV]", 0, 8000);
  custom_variables["BestTopMass_jet_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading b-Subjet (R=0.t) M [GeV]", 0, 400);
  custom_variables["BestTopMass_jet_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading b-Subjet (R=0.t) E [GeV]", 0, 8000);
  custom_variables["BestTopMass_jet_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing b-Subjet (R=0.t) Pt [GeV]", 0, 8000);
  custom_variables["BestTopMass_jet_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing b-Subjet (R=0.t) M [GeV]", 0, 400);
  custom_variables["BestTopMass_jet_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing b-Subjet (R=0.t) E [GeV]", 0, 8000);
  custom_variables["SecondTopMass_jet_softDroppedJet_pt"] = PlotVariable("Soft-dropped b-jet (R=0.t) Pt [GeV]", 0, 8000);
  custom_variables["SecondTopMass_jet_softDroppedJet_m"] = PlotVariable("Soft-dropped b-jet (R=0.t) M [GeV]", 0, 400);
  custom_variables["SecondTopMass_jet_softDroppedJet_e"] = PlotVariable("Soft-dropped b-jet (R=0.t) E [GeV]", 0, 8000);
  custom_variables["SecondTopMass_jet_leadingSoftDroppedSubJet_pt"] = PlotVariable("Leading b-Subjet (R=0.t) Pt [GeV]", 0, 8000);
  custom_variables["SecondTopMass_jet_leadingSoftDroppedSubJet_m"] = PlotVariable("Leading b-Subjet (R=0.t) M [GeV]", 0, 400);
  custom_variables["SecondTopMass_jet_leadingSoftDroppedSubJet_e"] = PlotVariable("Leading b-Subjet (R=0.t) E [GeV]", 0, 8000);
  custom_variables["SecondTopMass_jet_trailingSoftDroppedSubJet_pt"] = PlotVariable("Trailing b-Subjet (R=0.t) Pt [GeV]", 0, 8000);
  custom_variables["SecondTopMass_jet_trailingSoftDroppedSubJet_m"] = PlotVariable("Trailing b-Subjet (R=0.t) M [GeV]", 0, 400);
  custom_variables["SecondTopMass_jet_trailingSoftDroppedSubJet_e"] = PlotVariable("Trailing b-Subjet (R=0.t) E [GeV]", 0, 8000);
  custom_variables["dPhi_Photon_ptag_pfjets02"] = PlotVariable("#Delta #phi(#gamma, #gamma-PF-Jet R=0.2 )", 0, 0.35);
  custom_variables["dR_Photon_ptag_pfjets02"] = PlotVariable("#Delta R(#gamma, #gamma-PF-Jet R=0.2 )", 0, 0.35);
  custom_variables["M_Photon_ptag_pfjets02"] = PlotVariable("M(#gamma, #gamma-PF-Jet R=0.2 )", 0, 400);
  custom_variables["dPhi_bjet_ptag_pfjets02"] = PlotVariable("#Delta #phi(b-jet, #gamma-PF-Jet R=0.2 )", 0, 3.14);
  custom_variables["dR_bjet_ptag_pfjets02"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_ptag_pfjets04"] = PlotVariable("#Delta #phi(#gamma, #gamma-PF-Jet R=0.4 )", 0, 0.35);
  custom_variables["dR_Photon_ptag_pfjets04"] = PlotVariable("#Delta R(#gamma, #gamma-PF-Jet R=0.4 )", 0, 0.35);
  custom_variables["M_Photon_ptag_pfjets04"] = PlotVariable("M(#gamma, #gamma-PF-Jet R=0.4 )", 0, 400);
  custom_variables["dPhi_bjet_ptag_pfjets04"] = PlotVariable("#Delta #phi(b-jet, #gamma-PF-Jet R=0.4 )", 0, 3.14);
  custom_variables["dR_bjet_ptag_pfjets04"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_ptag_pfjets08"] = PlotVariable("#Delta #phi(#gamma, #gamma-PF-Jet R=0.8 )", 0, 0.35);
  custom_variables["dR_Photon_ptag_pfjets08"] = PlotVariable("#Delta R(#gamma, #gamma-PF-Jet R=0.8 )", 0, 0.35);
  custom_variables["M_Photon_ptag_pfjets08"] = PlotVariable("M(#gamma, #gamma-PF-Jet R=0.8 )", 0, 400);
  custom_variables["dPhi_bjet_ptag_pfjets08"] = PlotVariable("#Delta #phi(b-jet, #gamma-PF-Jet R=0.8 )", 0, 3.14);
  custom_variables["dR_bjet_ptag_pfjets08"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_btag_pfjets02"] = PlotVariable("#Delta #phi(#gamma, b-PF-Jet R=0.2 )", 0, 0.35);
  custom_variables["dR_Photon_btag_pfjets02"] = PlotVariable("#Delta R(#gamma, b-PF-Jet R=0.2 )", 0, 0.35);
  custom_variables["M_Photon_btag_pfjets02"] = PlotVariable("M(#gamma, b-PF-Jet R=0.2 )", 0, 400);
  custom_variables["dPhi_bjet_btag_pfjets02"] = PlotVariable("#Delta #phi(b-jet, b-PF-Jet R=0.2 )", 0, 3.14);
  custom_variables["dR_bjet_btag_pfjets02"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_btag_pfjets04"] = PlotVariable("#Delta #phi(#gamma, b-PF-Jet R=0.4 )", 0, 0.35);
  custom_variables["dR_Photon_btag_pfjets04"] = PlotVariable("#Delta R(#gamma, b-PF-Jet R=0.4 )", 0, 0.35);
  custom_variables["M_Photon_btag_pfjets04"] = PlotVariable("M(#gamma, b-PF-Jet R=0.4 )", 0, 400);
  custom_variables["dPhi_bjet_btag_pfjets04"] = PlotVariable("#Delta #phi(b-jet, b-PF-Jet R=0.4 )", 0, 3.14);
  custom_variables["dR_bjet_btag_pfjets04"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_btag_pfjets08"] = PlotVariable("#Delta #phi(#gamma, b-PF-Jet R=0.8 )", 0, 0.35);
  custom_variables["dR_Photon_btag_pfjets08"] = PlotVariable("#Delta R(#gamma, b-PF-Jet R=0.8 )", 0, 0.35);
  custom_variables["M_Photon_btag_pfjets08"] = PlotVariable("M(#gamma, b-PF-Jet R=0.8 )", 0, 400);
  custom_variables["dPhi_bjet_btag_pfjets08"] = PlotVariable("#Delta #phi(b-jet, b-PF-Jet R=0.8 )", 0, 3.14);
  custom_variables["dR_bjet_btag_pfjets08"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_ptag_calojets02"] = PlotVariable("#Delta #phi(#gamma, #gamma-Calo-Jet R=0.2 )", 0, 0.35);
  custom_variables["dR_Photon_ptag_calojets02"] = PlotVariable("#Delta R(#gamma, #gamma-Calo-Jet R=0.2 )", 0, 0.35);
  custom_variables["M_Photon_ptag_calojets02"] = PlotVariable("M(#gamma, #gamma-Calo-Jet R=0.2 )", 0, 400);
  custom_variables["dPhi_bjet_ptag_calojets02"] = PlotVariable("#Delta #phi(b-jet, #gamma-Calo-Jet R=0.2 )", 0, 3.14);
  custom_variables["dR_bjet_ptag_calojets02"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_ptag_calojets04"] = PlotVariable("#Delta #phi(#gamma, #gamma-Calo-Jet R=0.4 )", 0, 0.35);
  custom_variables["dR_Photon_ptag_calojets04"] = PlotVariable("#Delta R(#gamma, #gamma-Calo-Jet R=0.4 )", 0, 0.35);
  custom_variables["M_Photon_ptag_calojets04"] = PlotVariable("M(#gamma, #gamma-Calo-Jet R=0.4 )", 0, 400);
  custom_variables["dPhi_bjet_ptag_calojets04"] = PlotVariable("#Delta #phi(b-jet, #gamma-Calo-Jet R=0.4 )", 0, 3.14);
  custom_variables["dR_bjet_ptag_calojets04"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_ptag_calojets08"] = PlotVariable("#Delta #phi(#gamma, #gamma-Calo-Jet R=0.8 )", 0, 0.35);
  custom_variables["dR_Photon_ptag_calojets08"] = PlotVariable("#Delta R(#gamma, #gamma-Calo-Jet R=0.8 )", 0, 0.35);
  custom_variables["M_Photon_ptag_calojets08"] = PlotVariable("M(#gamma, #gamma-Calo-Jet R=0.8 )", 0, 400);
  custom_variables["dPhi_bjet_ptag_calojets08"] = PlotVariable("#Delta #phi(b-jet, #gamma-Calo-Jet R=0.8 )", 0, 3.14);
  custom_variables["dR_bjet_ptag_calojets08"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_btag_calojets02"] = PlotVariable("#Delta #phi(#gamma, b-Calo-Jet R=0.2 )", 0, 0.35);
  custom_variables["dR_Photon_btag_calojets02"] = PlotVariable("#Delta R(#gamma, b-Calo-Jet R=0.2 )", 0, 0.35);
  custom_variables["M_Photon_btag_calojets02"] = PlotVariable("M(#gamma, b-Calo-Jet R=0.2 )", 0, 400);
  custom_variables["dPhi_bjet_btag_calojets02"] = PlotVariable("#Delta #phi(b-jet, b-Calo-Jet R=0.2 )", 0, 3.14);
  custom_variables["dR_bjet_btag_calojets02"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_btag_calojets04"] = PlotVariable("#Delta #phi(#gamma, b-Calo-Jet R=0.4 )", 0, 0.35);
  custom_variables["dR_Photon_btag_calojets04"] = PlotVariable("#Delta R(#gamma, b-Calo-Jet R=0.4 )", 0, 0.35);
  custom_variables["M_Photon_btag_calojets04"] = PlotVariable("M(#gamma, b-Calo-Jet R=0.4 )", 0, 400);
  custom_variables["dPhi_bjet_btag_calojets04"] = PlotVariable("#Delta #phi(b-jet, b-Calo-Jet R=0.4 )", 0, 3.14);
  custom_variables["dR_bjet_btag_calojets04"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_btag_calojets08"] = PlotVariable("#Delta #phi(#gamma, b-Calo-Jet R=0.8 )", 0, 0.35);
  custom_variables["dR_Photon_btag_calojets08"] = PlotVariable("#Delta R(#gamma, b-Calo-Jet R=0.8 )", 0, 0.35);
  custom_variables["M_Photon_btag_calojets08"] = PlotVariable("M(#gamma, b-Calo-Jet R=0.8 )", 0, 400);
  custom_variables["dPhi_bjet_btag_calojets08"] = PlotVariable("#Delta #phi(b-jet, b-Calo-Jet R=0.8 )", 0, 3.14);
  custom_variables["dR_bjet_btag_calojets08"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_ptag_trkjets02"] = PlotVariable("#Delta #phi(#gamma, #gamma-Track-Jet R=0.2 )", 0, 0.35);
  custom_variables["dR_Photon_ptag_trkjets02"] = PlotVariable("#Delta R(#gamma, #gamma-Track-Jet R=0.2 )", 0, 0.35);
  custom_variables["M_Photon_ptag_trkjets02"] = PlotVariable("M(#gamma, #gamma-Track-Jet R=0.2 )", 0, 400);
  custom_variables["dPhi_bjet_ptag_trkjets02"] = PlotVariable("#Delta #phi(b-jet, #gamma-Track-Jet R=0.2 )", 0, 3.14);
  custom_variables["dR_bjet_ptag_trkjets02"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_ptag_trkjets04"] = PlotVariable("#Delta #phi(#gamma, #gamma-Track-Jet R=0.4 )", 0, 0.35);
  custom_variables["dR_Photon_ptag_trkjets04"] = PlotVariable("#Delta R(#gamma, #gamma-Track-Jet R=0.4 )", 0, 0.35);
  custom_variables["M_Photon_ptag_trkjets04"] = PlotVariable("M(#gamma, #gamma-Track-Jet R=0.4 )", 0, 400);
  custom_variables["dPhi_bjet_ptag_trkjets04"] = PlotVariable("#Delta #phi(b-jet, #gamma-Track-Jet R=0.4 )", 0, 3.14);
  custom_variables["dR_bjet_ptag_trkjets04"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_ptag_trkjets08"] = PlotVariable("#Delta #phi(#gamma, #gamma-Track-Jet R=0.8 )", 0, 0.35);
  custom_variables["dR_Photon_ptag_trkjets08"] = PlotVariable("#Delta R(#gamma, #gamma-Track-Jet R=0.8 )", 0, 0.35);
  custom_variables["M_Photon_ptag_trkjets08"] = PlotVariable("M(#gamma, #gamma-Track-Jet R=0.8 )", 0, 400);
  custom_variables["dPhi_bjet_ptag_trkjets08"] = PlotVariable("#Delta #phi(b-jet, #gamma-Track-Jet R=0.8 )", 0, 3.14);
  custom_variables["dR_bjet_ptag_trkjets08"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_btag_trkjets02"] = PlotVariable("#Delta #phi(#gamma, b-Track-Jet R=0.2 )", 0, 0.35);
  custom_variables["dR_Photon_btag_trkjets02"] = PlotVariable("#Delta R(#gamma, b-Track-Jet R=0.2 )", 0, 0.35);
  custom_variables["M_Photon_btag_trkjets02"] = PlotVariable("M(#gamma, b-Track-Jet R=0.2 )", 0, 400);
  custom_variables["dPhi_bjet_btag_trkjets02"] = PlotVariable("#Delta #phi(b-jet, b-Track-Jet R=0.2 )", 0, 3.14);
  custom_variables["dR_bjet_btag_trkjets02"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_btag_trkjets04"] = PlotVariable("#Delta #phi(#gamma, b-Track-Jet R=0.4 )", 0, 0.35);
  custom_variables["dR_Photon_btag_trkjets04"] = PlotVariable("#Delta R(#gamma, b-Track-Jet R=0.4 )", 0, 0.35);
  custom_variables["M_Photon_btag_trkjets04"] = PlotVariable("M(#gamma, b-Track-Jet R=0.4 )", 0, 400);
  custom_variables["dPhi_bjet_btag_trkjets04"] = PlotVariable("#Delta #phi(b-jet, b-Track-Jet R=0.4 )", 0, 3.14);
  custom_variables["dR_bjet_btag_trkjets04"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_btag_trkjets08"] = PlotVariable("#Delta #phi(#gamma, b-Track-Jet R=0.8 )", 0, 0.35);
  custom_variables["dR_Photon_btag_trkjets08"] = PlotVariable("#Delta R(#gamma, b-Track-Jet R=0.8 )", 0, 0.35);
  custom_variables["M_Photon_btag_trkjets08"] = PlotVariable("M(#gamma, b-Track-Jet R=0.8 )", 0, 400);
  custom_variables["dPhi_bjet_btag_trkjets08"] = PlotVariable("#Delta #phi(b-jet, b-Track-Jet R=0.8 )", 0, 3.14);
  custom_variables["dR_bjet_btag_trkjets08"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_BestMass_jet"] = PlotVariable("#Delta #phi(#gamma, Best t-Mass_{j+#gamma} PF-Jet R=0.t )", 0, 0.35);
  custom_variables["dR_Photon_BestMass_jet"] = PlotVariable("#Delta R(#gamma, Best t-Mass_{j+#gamma} PF-Jet R=0.t )", 0, 0.35);
  custom_variables["M_Photon_BestMass_jet"] = PlotVariable("M(#gamma, Best t-Mass_{j+#gamma} PF-Jet R=0.t )", 0, 400);
  custom_variables["dPhi_bjet_BestMass_jet"] = PlotVariable("#Delta #phi(b-jet, Best t-Mass_{j+#gamma} PF-Jet R=0.t )", 0, 3.14);
  custom_variables["dR_bjet_BestMass_jet"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_BestTopMass_jet"] = PlotVariable("#Delta #phi(#gamma, Best t-jet candidate PF-Jet R=0.8 )", 0, 0.35);
  custom_variables["dR_Photon_BestTopMass_jet"] = PlotVariable("#Delta R(#gamma, Best t-jet candidate PF-Jet R=0.8 )", 0, 0.35);
  custom_variables["M_Photon_BestTopMass_jet"] = PlotVariable("M(#gamma, Best t-jet candidate PF-Jet R=0.8 )", 0, 400);
  custom_variables["dPhi_bjet_BestTopMass_jet"] = PlotVariable("#Delta #phi(b-jet, Best t-jet candidate PF-Jet R=0.8 )", 0, 3.14);
  custom_variables["dR_bjet_BestTopMass_jet"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  custom_variables["dPhi_Photon_SecondTopMass_jet"] = PlotVariable("#Delta #phi(#gamma, Second t-jet candidate PF-Jet R=0.8 )", 0, 0.35);
  custom_variables["dR_Photon_SecondTopMass_jet"] = PlotVariable("#Delta R(#gamma, Second t-jet candidate PF-Jet R=0.8 )", 0, 0.35);
  custom_variables["M_Photon_SecondTopMass_jet"] = PlotVariable("M(#gamma, Second t-jet candidate PF-Jet R=0.8 )", 0, 400);
  custom_variables["dPhi_bjet_SecondTopMass_jet"] = PlotVariable("#Delta #phi(b-jet, Second t-jet candidate PF-Jet R=0.8 )", 0, 3.14);
  custom_variables["dR_bjet_SecondTopMass_jet"] = PlotVariable("#Delta R(b-jet)", 0, 8);
  //[[[end]]]

  return custom_variables;
}

FileHists process_file(ChanalData process, string samples_path){
  FileHists answer;
  map<string, TH1D*> hists_1d;
  map<string, TH2D*> hists_2d;

  /*[[[cog
    for var in custom_variables :
      if var.frozen : continue
      name = "(process.process_name + \"" + mRootCOG.get_cog_key() + "\").c_str()"
      title = "process.process_name.c_str()"
      var.hist_name = mRootCOG.cpp_TH1(name, title, var.nbins, var.xmin, var.xmax)
      string = "answer.hists_1d[ \"" + var.key + "\"] = " + var.hist_name + ";"
      cog.outl( string )

    for plot in cut_plots :
      var = plot.var
      name = "(process.process_name + \"" + mRootCOG.get_cog_key() + "\").c_str()"
      title = "process.process_name.c_str()"
      plot.hist_cut_name = mRootCOG.cpp_TH1(name, title, var.nbins, var.xmin, var.xmax)
      string = "answer.hists_1d[ \"" + plot.hist_cut_name + "\"] = " + plot.hist_cut_name + ";"
      cog.outl( string )

    for plot in corr_plots : 
      var_x = plot.var_x
      var_y = plot.var_y
      name = "(process.process_name + \"" + mRootCOG.get_cog_key() + "\").c_str()"
      title = "process.process_name.c_str()"
      plot.hist_name = mRootCOG.cpp_TH2(name, title, var_x.nbins, var_x.xmin, var_x.xmax, var_y.nbins, var_y.xmin, var_y.xmax)
      string = "answer.hists_2d[ \"" + plot.hist_name + "\"] = " + plot.hist_name + ";"
      cog.outl( string )
  ]]]*/
  TH1D* hist_1 = new TH1D((process.process_name + "0").c_str(), process.process_name.c_str(), 30, -3, 3);
  answer.hists_1d[ "photon_eta"] = hist_1;
  TH1D* hist_3 = new TH1D((process.process_name + "2").c_str(), process.process_name.c_str(), 30, 0, 3500);
  answer.hists_1d[ "photon_pt"] = hist_3;
  TH1D* hist_5 = new TH1D((process.process_name + "4").c_str(), process.process_name.c_str(), 30, 0, 3500);
  answer.hists_1d[ "top_pt"] = hist_5;
  TH1D* hist_7 = new TH1D((process.process_name + "6").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "ptag_bestJet_m"] = hist_7;
  TH1D* hist_9 = new TH1D((process.process_name + "8").c_str(), process.process_name.c_str(), 30, 0, 3500);
  answer.hists_1d[ "ptag_bestJet_pt"] = hist_9;
  TH1D* hist_11 = new TH1D((process.process_name + "10").c_str(), process.process_name.c_str(), 30, -3, 3);
  answer.hists_1d[ "ptag_bestJet_eta"] = hist_11;
  TH1D* hist_13 = new TH1D((process.process_name + "12").c_str(), process.process_name.c_str(), 30, -3, 3);
  answer.hists_1d[ "btag_pfjets04_eta"] = hist_13;
  TH1D* hist_15 = new TH1D((process.process_name + "14").c_str(), process.process_name.c_str(), 30, 0, 0.7);
  answer.hists_1d[ "ptag_bestJet_tau1"] = hist_15;
  TH1D* hist_17 = new TH1D((process.process_name + "16").c_str(), process.process_name.c_str(), 30, 0, 0.5);
  answer.hists_1d[ "ptag_bestJet_tau2"] = hist_17;
  TH1D* hist_19 = new TH1D((process.process_name + "18").c_str(), process.process_name.c_str(), 30, 0, 0.4);
  answer.hists_1d[ "ptag_bestJet_tau3"] = hist_19;
  TH1D* hist_21 = new TH1D((process.process_name + "20").c_str(), process.process_name.c_str(), 30, 0, 1);
  answer.hists_1d[ "ptag_bestJet_tau31"] = hist_21;
  TH1D* hist_23 = new TH1D((process.process_name + "22").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "ptag_bestJet_tau32"] = hist_23;
  TH1D* hist_25 = new TH1D((process.process_name + "24").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "ptag_bestJet_tau21"] = hist_25;
  TH1D* hist_27 = new TH1D((process.process_name + "26").c_str(), process.process_name.c_str(), 30, 0, 0.7);
  answer.hists_1d[ "ptag_pfjets08_tau1"] = hist_27;
  TH1D* hist_29 = new TH1D((process.process_name + "28").c_str(), process.process_name.c_str(), 30, 0, 0.5);
  answer.hists_1d[ "ptag_pfjets08_tau2"] = hist_29;
  TH1D* hist_31 = new TH1D((process.process_name + "30").c_str(), process.process_name.c_str(), 30, 0, 0.4);
  answer.hists_1d[ "ptag_pfjets08_tau3"] = hist_31;
  TH1D* hist_33 = new TH1D((process.process_name + "32").c_str(), process.process_name.c_str(), 30, 0, 1);
  answer.hists_1d[ "ptag_pfjets08_tau31"] = hist_33;
  TH1D* hist_35 = new TH1D((process.process_name + "34").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "ptag_pfjets08_tau32"] = hist_35;
  TH1D* hist_37 = new TH1D((process.process_name + "36").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "ptag_pfjets08_tau21"] = hist_37;
  TH1D* hist_39 = new TH1D((process.process_name + "38").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "btag_pfjets08_tau1"] = hist_39;
  TH1D* hist_41 = new TH1D((process.process_name + "40").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "btag_pfjets08_tau2"] = hist_41;
  TH1D* hist_43 = new TH1D((process.process_name + "42").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "btag_pfjets08_tau3"] = hist_43;
  TH1D* hist_45 = new TH1D((process.process_name + "44").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "btag_pfjets08_tau31"] = hist_45;
  TH1D* hist_47 = new TH1D((process.process_name + "46").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "btag_pfjets08_tau32"] = hist_47;
  TH1D* hist_49 = new TH1D((process.process_name + "48").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "btag_pfjets08_tau21"] = hist_49;
  TH1D* hist_51 = new TH1D((process.process_name + "50").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "btag_pfjets04_tau1"] = hist_51;
  TH1D* hist_53 = new TH1D((process.process_name + "52").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "btag_pfjets04_tau2"] = hist_53;
  TH1D* hist_55 = new TH1D((process.process_name + "54").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "btag_pfjets04_tau3"] = hist_55;
  TH1D* hist_57 = new TH1D((process.process_name + "56").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "btag_pfjets04_tau31"] = hist_57;
  TH1D* hist_59 = new TH1D((process.process_name + "58").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "btag_pfjets04_tau32"] = hist_59;
  TH1D* hist_61 = new TH1D((process.process_name + "60").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "btag_pfjets04_tau21"] = hist_61;
  TH1D* hist_63 = new TH1D((process.process_name + "62").c_str(), process.process_name.c_str(), 30, 0, 1000);
  answer.hists_1d[ "photon_x_ptag_bestJet"] = hist_63;
  TH1D* hist_65 = new TH1D((process.process_name + "64").c_str(), process.process_name.c_str(), 30, 0, 100000);
  answer.hists_1d[ "lepton_x_btag_pfjets08"] = hist_65;
  TH1D* hist_67 = new TH1D((process.process_name + "66").c_str(), process.process_name.c_str(), 30, -1.5, 1.5);
  answer.hists_1d[ "dPhi_lepton_btag_pfjets08"] = hist_67;
  TH1D* hist_69 = new TH1D((process.process_name + "68").c_str(), process.process_name.c_str(), 30, 0, 3.0);
  answer.hists_1d[ "dR_lepton_btag_pfjets08"] = hist_69;
  TH1D* hist_71 = new TH1D((process.process_name + "70").c_str(), process.process_name.c_str(), 30, 0, 100000);
  answer.hists_1d[ "lepton_x_btag_pfjets04"] = hist_71;
  TH1D* hist_73 = new TH1D((process.process_name + "72").c_str(), process.process_name.c_str(), 30, -1.0, 1.0);
  answer.hists_1d[ "dPhi_lepton_btag_pfjets04"] = hist_73;
  TH1D* hist_75 = new TH1D((process.process_name + "74").c_str(), process.process_name.c_str(), 30, 0, 1.2);
  answer.hists_1d[ "dR_lepton_btag_pfjets04"] = hist_75;
  TH1D* hist_77 = new TH1D((process.process_name + "76").c_str(), process.process_name.c_str(), 30, 0, 800);
  answer.hists_1d[ "M_lepton_met"] = hist_77;
  TH1D* hist_79 = new TH1D((process.process_name + "78").c_str(), process.process_name.c_str(), 30, 0, 800);
  answer.hists_1d[ "M_bjet_lepton_met"] = hist_79;
  TH1D* hist_81 = new TH1D((process.process_name + "80").c_str(), process.process_name.c_str(), 30, -0.5, 0.5);
  answer.hists_1d[ "dPhi_Photon_ptag_bestJet"] = hist_81;
  TH1D* hist_83 = new TH1D((process.process_name + "82").c_str(), process.process_name.c_str(), 30, 0, 0.4);
  answer.hists_1d[ "dR_Photon_ptag_bestJet"] = hist_83;
  TH1D* hist_85 = new TH1D((process.process_name + "84").c_str(), process.process_name.c_str(), 30, 0, 400);
  answer.hists_1d[ "M_Photon_ptag_bestJet"] = hist_85;
  TH1D* hist_87 = new TH1D((process.process_name + "86").c_str(), process.process_name.c_str(), 30, 0, 10000000);
  answer.hists_1d[ "bjet_x_ptag_bestJet"] = hist_87;
  TH1D* hist_89 = new TH1D((process.process_name + "88").c_str(), process.process_name.c_str(), 30, -3.14, 3.14);
  answer.hists_1d[ "dPhi_bjet_ptag_bestJet"] = hist_89;
  TH1D* hist_91 = new TH1D((process.process_name + "90").c_str(), process.process_name.c_str(), 30, 0, 5);
  answer.hists_1d[ "dR_bjet_ptag_bestJet"] = hist_91;
  TH1D* hist_93 = new TH1D((process.process_name + "92").c_str(), process.process_name.c_str(), 30, 0, 50);
  answer.hists_1d[ "lepton_relIso"] = hist_93;
  TH1D* hist_95 = new TH1D((process.process_name + "94").c_str(), process.process_name.c_str(), 30, 0, 25);
  answer.hists_1d[ "photon_relIso"] = hist_95;
  TH1D* hist_97 = new TH1D((process.process_name + "96").c_str(), process.process_name.c_str(), 30, 0, 30000);
  answer.hists_1d[ "photon_x_ptag_pfjets08"] = hist_97;
  TH1D* hist_99 = new TH1D((process.process_name + "98").c_str(), process.process_name.c_str(), 30, 0, 10000000);
  answer.hists_1d[ "bjet_x_ptag_pfjets08"] = hist_99;
  TH1D* hist_101 = new TH1D((process.process_name + "100").c_str(), process.process_name.c_str(), 10000, -0.7, 0.8);
  answer.hists_1d[ "weight_tune_3_BDT_0_000"] = hist_101;
  TH1D* hist_103 = new TH1D((process.process_name + "102").c_str(), process.process_name.c_str(), 10000, -0.7, 0.8);
  answer.hists_1d[ "weight_tune_3_BDT_1_000"] = hist_103;
  TH1D* hist_105 = new TH1D((process.process_name + "104").c_str(), process.process_name.c_str(), 10000, -0.7, 0.8);
  answer.hists_1d[ "weight_tune_3_BDT_2_000"] = hist_105;
  TH1D* hist_107 = new TH1D((process.process_name + "106").c_str(), process.process_name.c_str(), 10000, -0.7, 0.8);
  answer.hists_1d[ "weight_tune_3_BDT_3_000"] = hist_107;
  TH1D* hist_109 = new TH1D((process.process_name + "108").c_str(), process.process_name.c_str(), 10000, -0.7, 0.8);
  answer.hists_1d[ "weight_tune_3_BDT_4_000"] = hist_109;
  TH1D* hist_111 = new TH1D((process.process_name + "110").c_str(), process.process_name.c_str(), 10000, -0.7, 0.8);
  answer.hists_1d[ "weight_tune_3_BDT_5_000"] = hist_111;
  TH1D* hist_113 = new TH1D((process.process_name + "112").c_str(), process.process_name.c_str(), 10000, -0.7, 0.8);
  answer.hists_1d[ "weight_tune_3_BDT_6_000"] = hist_113;
  TH1D* hist_115 = new TH1D((process.process_name + "114").c_str(), process.process_name.c_str(), 10000, -0.7, 0.8);
  answer.hists_1d[ "weight_tune_5_BDT_3_000"] = hist_115;
  TH1D* hist_117 = new TH1D((process.process_name + "116").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets02_e"] = hist_117;
  TH1D* hist_119 = new TH1D((process.process_name + "118").c_str(), process.process_name.c_str(), 30, 0, 2000);
  answer.hists_1d[ "ptag_pfjets02_pt"] = hist_119;
  TH1D* hist_121 = new TH1D((process.process_name + "120").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "ptag_pfjets02_m"] = hist_121;
  TH1D* hist_123 = new TH1D((process.process_name + "122").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets04_e"] = hist_123;
  TH1D* hist_125 = new TH1D((process.process_name + "124").c_str(), process.process_name.c_str(), 30, 0, 2000);
  answer.hists_1d[ "ptag_pfjets04_pt"] = hist_125;
  TH1D* hist_127 = new TH1D((process.process_name + "126").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "ptag_pfjets04_m"] = hist_127;
  TH1D* hist_129 = new TH1D((process.process_name + "128").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets08_e"] = hist_129;
  TH1D* hist_131 = new TH1D((process.process_name + "130").c_str(), process.process_name.c_str(), 30, 0, 2000);
  answer.hists_1d[ "ptag_pfjets08_pt"] = hist_131;
  TH1D* hist_133 = new TH1D((process.process_name + "132").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "ptag_pfjets08_m"] = hist_133;
  TH1D* hist_135 = new TH1D((process.process_name + "134").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets02_e"] = hist_135;
  TH1D* hist_137 = new TH1D((process.process_name + "136").c_str(), process.process_name.c_str(), 30, 0, 2000);
  answer.hists_1d[ "btag_pfjets02_pt"] = hist_137;
  TH1D* hist_139 = new TH1D((process.process_name + "138").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "btag_pfjets02_m"] = hist_139;
  TH1D* hist_141 = new TH1D((process.process_name + "140").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets04_e"] = hist_141;
  TH1D* hist_143 = new TH1D((process.process_name + "142").c_str(), process.process_name.c_str(), 30, 0, 2000);
  answer.hists_1d[ "btag_pfjets04_pt"] = hist_143;
  TH1D* hist_145 = new TH1D((process.process_name + "144").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "btag_pfjets04_m"] = hist_145;
  TH1D* hist_147 = new TH1D((process.process_name + "146").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets08_e"] = hist_147;
  TH1D* hist_149 = new TH1D((process.process_name + "148").c_str(), process.process_name.c_str(), 30, 0, 2000);
  answer.hists_1d[ "btag_pfjets08_pt"] = hist_149;
  TH1D* hist_151 = new TH1D((process.process_name + "150").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "btag_pfjets08_m"] = hist_151;
  TH1D* hist_153 = new TH1D((process.process_name + "152").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "ptag_calojets04_m"] = hist_153;
  TH1D* hist_155 = new TH1D((process.process_name + "154").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "ptag_calojets08_m"] = hist_155;
  TH1D* hist_157 = new TH1D((process.process_name + "156").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "btag_calojets04_m"] = hist_157;
  TH1D* hist_159 = new TH1D((process.process_name + "158").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "btag_calojets08_m"] = hist_159;
  TH1D* hist_161 = new TH1D((process.process_name + "160").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "ptag_trkjets04_m"] = hist_161;
  TH1D* hist_163 = new TH1D((process.process_name + "162").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "ptag_trkjets08_m"] = hist_163;
  TH1D* hist_165 = new TH1D((process.process_name + "164").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "btag_trkjets04_m"] = hist_165;
  TH1D* hist_167 = new TH1D((process.process_name + "166").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "btag_trkjets08_m"] = hist_167;
  TH1D* hist_169 = new TH1D((process.process_name + "168").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "BestMass_jet_e"] = hist_169;
  TH1D* hist_171 = new TH1D((process.process_name + "170").c_str(), process.process_name.c_str(), 30, 0, 2000);
  answer.hists_1d[ "BestMass_jet_pt"] = hist_171;
  TH1D* hist_173 = new TH1D((process.process_name + "172").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "BestMass_jet_m"] = hist_173;
  TH1D* hist_175 = new TH1D((process.process_name + "174").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "BestTopMass_jet_e"] = hist_175;
  TH1D* hist_177 = new TH1D((process.process_name + "176").c_str(), process.process_name.c_str(), 30, 0, 2000);
  answer.hists_1d[ "BestTopMass_jet_pt"] = hist_177;
  TH1D* hist_179 = new TH1D((process.process_name + "178").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "BestTopMass_jet_m"] = hist_179;
  TH1D* hist_181 = new TH1D((process.process_name + "180").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "SecondTopMass_jet_e"] = hist_181;
  TH1D* hist_183 = new TH1D((process.process_name + "182").c_str(), process.process_name.c_str(), 30, 0, 2000);
  answer.hists_1d[ "SecondTopMass_jet_pt"] = hist_183;
  TH1D* hist_185 = new TH1D((process.process_name + "184").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "SecondTopMass_jet_m"] = hist_185;
  TH1D* hist_187 = new TH1D((process.process_name + "186").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets02_softDroppedJet_pt"] = hist_187;
  TH1D* hist_189 = new TH1D((process.process_name + "188").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "ptag_pfjets02_softDroppedJet_m"] = hist_189;
  TH1D* hist_191 = new TH1D((process.process_name + "190").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets02_softDroppedJet_e"] = hist_191;
  TH1D* hist_193 = new TH1D((process.process_name + "192").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets02_leadingSoftDroppedSubJet_pt"] = hist_193;
  TH1D* hist_195 = new TH1D((process.process_name + "194").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "ptag_pfjets02_leadingSoftDroppedSubJet_m"] = hist_195;
  TH1D* hist_197 = new TH1D((process.process_name + "196").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets02_leadingSoftDroppedSubJet_e"] = hist_197;
  TH1D* hist_199 = new TH1D((process.process_name + "198").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets02_trailingSoftDroppedSubJet_pt"] = hist_199;
  TH1D* hist_201 = new TH1D((process.process_name + "200").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "ptag_pfjets02_trailingSoftDroppedSubJet_m"] = hist_201;
  TH1D* hist_203 = new TH1D((process.process_name + "202").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets02_trailingSoftDroppedSubJet_e"] = hist_203;
  TH1D* hist_205 = new TH1D((process.process_name + "204").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets04_softDroppedJet_pt"] = hist_205;
  TH1D* hist_207 = new TH1D((process.process_name + "206").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "ptag_pfjets04_softDroppedJet_m"] = hist_207;
  TH1D* hist_209 = new TH1D((process.process_name + "208").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets04_softDroppedJet_e"] = hist_209;
  TH1D* hist_211 = new TH1D((process.process_name + "210").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets04_leadingSoftDroppedSubJet_pt"] = hist_211;
  TH1D* hist_213 = new TH1D((process.process_name + "212").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "ptag_pfjets04_leadingSoftDroppedSubJet_m"] = hist_213;
  TH1D* hist_215 = new TH1D((process.process_name + "214").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets04_leadingSoftDroppedSubJet_e"] = hist_215;
  TH1D* hist_217 = new TH1D((process.process_name + "216").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets04_trailingSoftDroppedSubJet_pt"] = hist_217;
  TH1D* hist_219 = new TH1D((process.process_name + "218").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "ptag_pfjets04_trailingSoftDroppedSubJet_m"] = hist_219;
  TH1D* hist_221 = new TH1D((process.process_name + "220").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets04_trailingSoftDroppedSubJet_e"] = hist_221;
  TH1D* hist_223 = new TH1D((process.process_name + "222").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets08_softDroppedJet_pt"] = hist_223;
  TH1D* hist_225 = new TH1D((process.process_name + "224").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "ptag_pfjets08_softDroppedJet_m"] = hist_225;
  TH1D* hist_227 = new TH1D((process.process_name + "226").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets08_softDroppedJet_e"] = hist_227;
  TH1D* hist_229 = new TH1D((process.process_name + "228").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets08_leadingSoftDroppedSubJet_pt"] = hist_229;
  TH1D* hist_231 = new TH1D((process.process_name + "230").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "ptag_pfjets08_leadingSoftDroppedSubJet_m"] = hist_231;
  TH1D* hist_233 = new TH1D((process.process_name + "232").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets08_leadingSoftDroppedSubJet_e"] = hist_233;
  TH1D* hist_235 = new TH1D((process.process_name + "234").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets08_trailingSoftDroppedSubJet_pt"] = hist_235;
  TH1D* hist_237 = new TH1D((process.process_name + "236").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "ptag_pfjets08_trailingSoftDroppedSubJet_m"] = hist_237;
  TH1D* hist_239 = new TH1D((process.process_name + "238").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "ptag_pfjets08_trailingSoftDroppedSubJet_e"] = hist_239;
  TH1D* hist_241 = new TH1D((process.process_name + "240").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets02_softDroppedJet_pt"] = hist_241;
  TH1D* hist_243 = new TH1D((process.process_name + "242").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "btag_pfjets02_softDroppedJet_m"] = hist_243;
  TH1D* hist_245 = new TH1D((process.process_name + "244").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets02_softDroppedJet_e"] = hist_245;
  TH1D* hist_247 = new TH1D((process.process_name + "246").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets02_leadingSoftDroppedSubJet_pt"] = hist_247;
  TH1D* hist_249 = new TH1D((process.process_name + "248").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "btag_pfjets02_leadingSoftDroppedSubJet_m"] = hist_249;
  TH1D* hist_251 = new TH1D((process.process_name + "250").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets02_leadingSoftDroppedSubJet_e"] = hist_251;
  TH1D* hist_253 = new TH1D((process.process_name + "252").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets02_trailingSoftDroppedSubJet_pt"] = hist_253;
  TH1D* hist_255 = new TH1D((process.process_name + "254").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "btag_pfjets02_trailingSoftDroppedSubJet_m"] = hist_255;
  TH1D* hist_257 = new TH1D((process.process_name + "256").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets02_trailingSoftDroppedSubJet_e"] = hist_257;
  TH1D* hist_259 = new TH1D((process.process_name + "258").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets04_softDroppedJet_pt"] = hist_259;
  TH1D* hist_261 = new TH1D((process.process_name + "260").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "btag_pfjets04_softDroppedJet_m"] = hist_261;
  TH1D* hist_263 = new TH1D((process.process_name + "262").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets04_softDroppedJet_e"] = hist_263;
  TH1D* hist_265 = new TH1D((process.process_name + "264").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets04_leadingSoftDroppedSubJet_pt"] = hist_265;
  TH1D* hist_267 = new TH1D((process.process_name + "266").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "btag_pfjets04_leadingSoftDroppedSubJet_m"] = hist_267;
  TH1D* hist_269 = new TH1D((process.process_name + "268").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets04_leadingSoftDroppedSubJet_e"] = hist_269;
  TH1D* hist_271 = new TH1D((process.process_name + "270").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets04_trailingSoftDroppedSubJet_pt"] = hist_271;
  TH1D* hist_273 = new TH1D((process.process_name + "272").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "btag_pfjets04_trailingSoftDroppedSubJet_m"] = hist_273;
  TH1D* hist_275 = new TH1D((process.process_name + "274").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets04_trailingSoftDroppedSubJet_e"] = hist_275;
  TH1D* hist_277 = new TH1D((process.process_name + "276").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets08_softDroppedJet_pt"] = hist_277;
  TH1D* hist_279 = new TH1D((process.process_name + "278").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "btag_pfjets08_softDroppedJet_m"] = hist_279;
  TH1D* hist_281 = new TH1D((process.process_name + "280").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets08_softDroppedJet_e"] = hist_281;
  TH1D* hist_283 = new TH1D((process.process_name + "282").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets08_leadingSoftDroppedSubJet_pt"] = hist_283;
  TH1D* hist_285 = new TH1D((process.process_name + "284").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "btag_pfjets08_leadingSoftDroppedSubJet_m"] = hist_285;
  TH1D* hist_287 = new TH1D((process.process_name + "286").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets08_leadingSoftDroppedSubJet_e"] = hist_287;
  TH1D* hist_289 = new TH1D((process.process_name + "288").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets08_trailingSoftDroppedSubJet_pt"] = hist_289;
  TH1D* hist_291 = new TH1D((process.process_name + "290").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "btag_pfjets08_trailingSoftDroppedSubJet_m"] = hist_291;
  TH1D* hist_293 = new TH1D((process.process_name + "292").c_str(), process.process_name.c_str(), 30, 0, 8000);
  answer.hists_1d[ "btag_pfjets08_trailingSoftDroppedSubJet_e"] = hist_293;
  TH1D* hist_295 = new TH1D((process.process_name + "294").c_str(), process.process_name.c_str(), 30, 0, 0.35);
  answer.hists_1d[ "dPhi_Photon_ptag_pfjets04"] = hist_295;
  TH1D* hist_297 = new TH1D((process.process_name + "296").c_str(), process.process_name.c_str(), 30, 0, 0.35);
  answer.hists_1d[ "dR_Photon_ptag_pfjets04"] = hist_297;
  TH1D* hist_299 = new TH1D((process.process_name + "298").c_str(), process.process_name.c_str(), 30, 0, 400);
  answer.hists_1d[ "M_Photon_ptag_pfjets04"] = hist_299;
  TH1D* hist_301 = new TH1D((process.process_name + "300").c_str(), process.process_name.c_str(), 30, 0, 3.14);
  answer.hists_1d[ "dPhi_bjet_ptag_pfjets04"] = hist_301;
  TH1D* hist_303 = new TH1D((process.process_name + "302").c_str(), process.process_name.c_str(), 30, 0, 8);
  answer.hists_1d[ "dR_bjet_ptag_pfjets04"] = hist_303;
  TH1D* hist_305 = new TH1D((process.process_name + "304").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "hist_305"] = hist_305;
  TH1D* hist_307 = new TH1D((process.process_name + "306").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "hist_307"] = hist_307;
  TH1D* hist_309 = new TH1D((process.process_name + "308").c_str(), process.process_name.c_str(), 50, 0, 400);
  answer.hists_1d[ "hist_309"] = hist_309;
  TH1D* hist_311 = new TH1D((process.process_name + "310").c_str(), process.process_name.c_str(), 30, 0, 0.7);
  answer.hists_1d[ "hist_311"] = hist_311;
  TH1D* hist_313 = new TH1D((process.process_name + "312").c_str(), process.process_name.c_str(), 30, 0, 0.5);
  answer.hists_1d[ "hist_313"] = hist_313;
  TH1D* hist_315 = new TH1D((process.process_name + "314").c_str(), process.process_name.c_str(), 30, 0, 0.4);
  answer.hists_1d[ "hist_315"] = hist_315;
  TH1D* hist_317 = new TH1D((process.process_name + "316").c_str(), process.process_name.c_str(), 30, 0, 1);
  answer.hists_1d[ "hist_317"] = hist_317;
  TH1D* hist_319 = new TH1D((process.process_name + "318").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "hist_319"] = hist_319;
  TH1D* hist_321 = new TH1D((process.process_name + "320").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "hist_321"] = hist_321;
  TH1D* hist_323 = new TH1D((process.process_name + "322").c_str(), process.process_name.c_str(), 30, 0, 0.7);
  answer.hists_1d[ "hist_323"] = hist_323;
  TH1D* hist_325 = new TH1D((process.process_name + "324").c_str(), process.process_name.c_str(), 30, 0, 0.5);
  answer.hists_1d[ "hist_325"] = hist_325;
  TH1D* hist_327 = new TH1D((process.process_name + "326").c_str(), process.process_name.c_str(), 30, 0, 0.4);
  answer.hists_1d[ "hist_327"] = hist_327;
  TH1D* hist_329 = new TH1D((process.process_name + "328").c_str(), process.process_name.c_str(), 30, 0, 1);
  answer.hists_1d[ "hist_329"] = hist_329;
  TH1D* hist_331 = new TH1D((process.process_name + "330").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "hist_331"] = hist_331;
  TH1D* hist_333 = new TH1D((process.process_name + "332").c_str(), process.process_name.c_str(), 30, 0, 1.0);
  answer.hists_1d[ "hist_333"] = hist_333;
  TH1D* hist_335 = new TH1D((process.process_name + "334").c_str(), process.process_name.c_str(), 30, 0, 1000);
  answer.hists_1d[ "hist_335"] = hist_335;
  TH1D* hist_337 = new TH1D((process.process_name + "336").c_str(), process.process_name.c_str(), 30, -0.5, 0.5);
  answer.hists_1d[ "hist_337"] = hist_337;
  TH1D* hist_339 = new TH1D((process.process_name + "338").c_str(), process.process_name.c_str(), 30, 0, 0.4);
  answer.hists_1d[ "hist_339"] = hist_339;
  TH1D* hist_341 = new TH1D((process.process_name + "340").c_str(), process.process_name.c_str(), 30, 0, 400);
  answer.hists_1d[ "hist_341"] = hist_341;
  TH1D* hist_343 = new TH1D((process.process_name + "342").c_str(), process.process_name.c_str(), 30, 0, 10000000);
  answer.hists_1d[ "hist_343"] = hist_343;
  TH1D* hist_345 = new TH1D((process.process_name + "344").c_str(), process.process_name.c_str(), 30, -3.14, 3.14);
  answer.hists_1d[ "hist_345"] = hist_345;
  TH1D* hist_347 = new TH1D((process.process_name + "346").c_str(), process.process_name.c_str(), 30, 0, 5);
  answer.hists_1d[ "hist_347"] = hist_347;
  TH1D* hist_349 = new TH1D((process.process_name + "348").c_str(), process.process_name.c_str(), 30, 0, 5);
  answer.hists_1d[ "hist_349"] = hist_349;
  TH2D* hist_351 = new TH2D((process.process_name + "350").c_str(), process.process_name.c_str(), 50, 0, 400, 50, 0, 400);
  answer.hists_2d[ "hist_351"] = hist_351;
  TH2D* hist_353 = new TH2D((process.process_name + "352").c_str(), process.process_name.c_str(), 50, 0, 400, 30, 0, 8000);
  answer.hists_2d[ "hist_353"] = hist_353;
  TH2D* hist_355 = new TH2D((process.process_name + "354").c_str(), process.process_name.c_str(), 50, 0, 400, 50, 0, 400);
  answer.hists_2d[ "hist_355"] = hist_355;
  TH2D* hist_357 = new TH2D((process.process_name + "356").c_str(), process.process_name.c_str(), 50, 0, 400, 50, 0, 400);
  answer.hists_2d[ "hist_357"] = hist_357;
  TH2D* hist_359 = new TH2D((process.process_name + "358").c_str(), process.process_name.c_str(), 50, 0, 400, 50, 0, 400);
  answer.hists_2d[ "hist_359"] = hist_359;
  TH2D* hist_361 = new TH2D((process.process_name + "360").c_str(), process.process_name.c_str(), 30, -3, 3, 30, -3, 3);
  answer.hists_2d[ "hist_361"] = hist_361;
  //[[[end]]]

  // INPUT =========================================+>
  cout << "TTTTTTTTTT <- 1" << endl;
  mRoot::EventReader <Double_t> event;
  for( string file_name : process.file_names ){
    // string input_file = samples_path + "/" +  file_name + ".root";
    string input_file = samples_path + "/" +  file_name + "_split.root";
    cout << input_file << endl;
    TFile * file = TFile::Open(input_file.c_str());
    TTree * train_tree = nullptr;

    // event.Init( file, "ttree" );
    train_tree = (TTree*)file->Get("train");
    event.Init( file, "data" );

    /*[[[cog
      for var in custom_variables :
        # if var.frozen : continue
        string = "Double_t * v_" + var.key + " = event.GetVar(\"" + var.key + "\");" ;
        cog.outl( string )

    ]]]*/
    Double_t * v_photon_eta = event.GetVar("photon_eta");
    Double_t * v_photon_pt = event.GetVar("photon_pt");
    Double_t * v_top_pt = event.GetVar("top_pt");
    Double_t * v_ptag_bestJet_m = event.GetVar("ptag_bestJet_m");
    Double_t * v_ptag_bestJet_pt = event.GetVar("ptag_bestJet_pt");
    Double_t * v_ptag_bestJet_eta = event.GetVar("ptag_bestJet_eta");
    Double_t * v_btag_pfjets04_eta = event.GetVar("btag_pfjets04_eta");
    Double_t * v_ptag_bestJet_tau1 = event.GetVar("ptag_bestJet_tau1");
    Double_t * v_ptag_bestJet_tau2 = event.GetVar("ptag_bestJet_tau2");
    Double_t * v_ptag_bestJet_tau3 = event.GetVar("ptag_bestJet_tau3");
    Double_t * v_ptag_bestJet_tau31 = event.GetVar("ptag_bestJet_tau31");
    Double_t * v_ptag_bestJet_tau32 = event.GetVar("ptag_bestJet_tau32");
    Double_t * v_ptag_bestJet_tau21 = event.GetVar("ptag_bestJet_tau21");
    Double_t * v_ptag_pfjets08_tau1 = event.GetVar("ptag_pfjets08_tau1");
    Double_t * v_ptag_pfjets08_tau2 = event.GetVar("ptag_pfjets08_tau2");
    Double_t * v_ptag_pfjets08_tau3 = event.GetVar("ptag_pfjets08_tau3");
    Double_t * v_ptag_pfjets08_tau31 = event.GetVar("ptag_pfjets08_tau31");
    Double_t * v_ptag_pfjets08_tau32 = event.GetVar("ptag_pfjets08_tau32");
    Double_t * v_ptag_pfjets08_tau21 = event.GetVar("ptag_pfjets08_tau21");
    Double_t * v_btag_pfjets08_tau1 = event.GetVar("btag_pfjets08_tau1");
    Double_t * v_btag_pfjets08_tau2 = event.GetVar("btag_pfjets08_tau2");
    Double_t * v_btag_pfjets08_tau3 = event.GetVar("btag_pfjets08_tau3");
    Double_t * v_btag_pfjets08_tau31 = event.GetVar("btag_pfjets08_tau31");
    Double_t * v_btag_pfjets08_tau32 = event.GetVar("btag_pfjets08_tau32");
    Double_t * v_btag_pfjets08_tau21 = event.GetVar("btag_pfjets08_tau21");
    Double_t * v_btag_pfjets04_tau1 = event.GetVar("btag_pfjets04_tau1");
    Double_t * v_btag_pfjets04_tau2 = event.GetVar("btag_pfjets04_tau2");
    Double_t * v_btag_pfjets04_tau3 = event.GetVar("btag_pfjets04_tau3");
    Double_t * v_btag_pfjets04_tau31 = event.GetVar("btag_pfjets04_tau31");
    Double_t * v_btag_pfjets04_tau32 = event.GetVar("btag_pfjets04_tau32");
    Double_t * v_btag_pfjets04_tau21 = event.GetVar("btag_pfjets04_tau21");
    Double_t * v_photon_x_ptag_bestJet = event.GetVar("photon_x_ptag_bestJet");
    Double_t * v_lepton_x_btag_pfjets08 = event.GetVar("lepton_x_btag_pfjets08");
    Double_t * v_dPhi_lepton_btag_pfjets08 = event.GetVar("dPhi_lepton_btag_pfjets08");
    Double_t * v_dR_lepton_btag_pfjets08 = event.GetVar("dR_lepton_btag_pfjets08");
    Double_t * v_lepton_x_btag_pfjets04 = event.GetVar("lepton_x_btag_pfjets04");
    Double_t * v_dPhi_lepton_btag_pfjets04 = event.GetVar("dPhi_lepton_btag_pfjets04");
    Double_t * v_dR_lepton_btag_pfjets04 = event.GetVar("dR_lepton_btag_pfjets04");
    Double_t * v_M_lepton_met = event.GetVar("M_lepton_met");
    Double_t * v_M_bjet_lepton_met = event.GetVar("M_bjet_lepton_met");
    Double_t * v_dPhi_Photon_ptag_bestJet = event.GetVar("dPhi_Photon_ptag_bestJet");
    Double_t * v_dR_Photon_ptag_bestJet = event.GetVar("dR_Photon_ptag_bestJet");
    Double_t * v_M_Photon_ptag_bestJet = event.GetVar("M_Photon_ptag_bestJet");
    Double_t * v_bjet_x_ptag_bestJet = event.GetVar("bjet_x_ptag_bestJet");
    Double_t * v_dPhi_bjet_ptag_bestJet = event.GetVar("dPhi_bjet_ptag_bestJet");
    Double_t * v_dR_bjet_ptag_bestJet = event.GetVar("dR_bjet_ptag_bestJet");
    Double_t * v_lepton_relIso = event.GetVar("lepton_relIso");
    Double_t * v_photon_relIso = event.GetVar("photon_relIso");
    Double_t * v_photon_x_ptag_pfjets08 = event.GetVar("photon_x_ptag_pfjets08");
    Double_t * v_bjet_x_ptag_pfjets08 = event.GetVar("bjet_x_ptag_pfjets08");
    Double_t * v_weight_tune_3_BDT_0_000 = event.GetVar("weight_tune_3_BDT_0_000");
    Double_t * v_weight_tune_3_BDT_1_000 = event.GetVar("weight_tune_3_BDT_1_000");
    Double_t * v_weight_tune_3_BDT_2_000 = event.GetVar("weight_tune_3_BDT_2_000");
    Double_t * v_weight_tune_3_BDT_3_000 = event.GetVar("weight_tune_3_BDT_3_000");
    Double_t * v_weight_tune_3_BDT_4_000 = event.GetVar("weight_tune_3_BDT_4_000");
    Double_t * v_weight_tune_3_BDT_5_000 = event.GetVar("weight_tune_3_BDT_5_000");
    Double_t * v_weight_tune_3_BDT_6_000 = event.GetVar("weight_tune_3_BDT_6_000");
    Double_t * v_weight_tune_5_BDT_3_000 = event.GetVar("weight_tune_5_BDT_3_000");
    Double_t * v_ptag_pfjets02_e = event.GetVar("ptag_pfjets02_e");
    Double_t * v_ptag_pfjets02_pt = event.GetVar("ptag_pfjets02_pt");
    Double_t * v_ptag_pfjets02_m = event.GetVar("ptag_pfjets02_m");
    Double_t * v_ptag_pfjets04_e = event.GetVar("ptag_pfjets04_e");
    Double_t * v_ptag_pfjets04_pt = event.GetVar("ptag_pfjets04_pt");
    Double_t * v_ptag_pfjets04_m = event.GetVar("ptag_pfjets04_m");
    Double_t * v_ptag_pfjets08_e = event.GetVar("ptag_pfjets08_e");
    Double_t * v_ptag_pfjets08_pt = event.GetVar("ptag_pfjets08_pt");
    Double_t * v_ptag_pfjets08_m = event.GetVar("ptag_pfjets08_m");
    Double_t * v_btag_pfjets02_e = event.GetVar("btag_pfjets02_e");
    Double_t * v_btag_pfjets02_pt = event.GetVar("btag_pfjets02_pt");
    Double_t * v_btag_pfjets02_m = event.GetVar("btag_pfjets02_m");
    Double_t * v_btag_pfjets04_e = event.GetVar("btag_pfjets04_e");
    Double_t * v_btag_pfjets04_pt = event.GetVar("btag_pfjets04_pt");
    Double_t * v_btag_pfjets04_m = event.GetVar("btag_pfjets04_m");
    Double_t * v_btag_pfjets08_e = event.GetVar("btag_pfjets08_e");
    Double_t * v_btag_pfjets08_pt = event.GetVar("btag_pfjets08_pt");
    Double_t * v_btag_pfjets08_m = event.GetVar("btag_pfjets08_m");
    Double_t * v_ptag_calojets02_e = event.GetVar("ptag_calojets02_e");
    Double_t * v_ptag_calojets02_pt = event.GetVar("ptag_calojets02_pt");
    Double_t * v_ptag_calojets02_m = event.GetVar("ptag_calojets02_m");
    Double_t * v_ptag_calojets04_e = event.GetVar("ptag_calojets04_e");
    Double_t * v_ptag_calojets04_pt = event.GetVar("ptag_calojets04_pt");
    Double_t * v_ptag_calojets04_m = event.GetVar("ptag_calojets04_m");
    Double_t * v_ptag_calojets08_e = event.GetVar("ptag_calojets08_e");
    Double_t * v_ptag_calojets08_pt = event.GetVar("ptag_calojets08_pt");
    Double_t * v_ptag_calojets08_m = event.GetVar("ptag_calojets08_m");
    Double_t * v_btag_calojets02_e = event.GetVar("btag_calojets02_e");
    Double_t * v_btag_calojets02_pt = event.GetVar("btag_calojets02_pt");
    Double_t * v_btag_calojets02_m = event.GetVar("btag_calojets02_m");
    Double_t * v_btag_calojets04_e = event.GetVar("btag_calojets04_e");
    Double_t * v_btag_calojets04_pt = event.GetVar("btag_calojets04_pt");
    Double_t * v_btag_calojets04_m = event.GetVar("btag_calojets04_m");
    Double_t * v_btag_calojets08_e = event.GetVar("btag_calojets08_e");
    Double_t * v_btag_calojets08_pt = event.GetVar("btag_calojets08_pt");
    Double_t * v_btag_calojets08_m = event.GetVar("btag_calojets08_m");
    Double_t * v_ptag_trkjets02_e = event.GetVar("ptag_trkjets02_e");
    Double_t * v_ptag_trkjets02_pt = event.GetVar("ptag_trkjets02_pt");
    Double_t * v_ptag_trkjets02_m = event.GetVar("ptag_trkjets02_m");
    Double_t * v_ptag_trkjets04_e = event.GetVar("ptag_trkjets04_e");
    Double_t * v_ptag_trkjets04_pt = event.GetVar("ptag_trkjets04_pt");
    Double_t * v_ptag_trkjets04_m = event.GetVar("ptag_trkjets04_m");
    Double_t * v_ptag_trkjets08_e = event.GetVar("ptag_trkjets08_e");
    Double_t * v_ptag_trkjets08_pt = event.GetVar("ptag_trkjets08_pt");
    Double_t * v_ptag_trkjets08_m = event.GetVar("ptag_trkjets08_m");
    Double_t * v_btag_trkjets02_e = event.GetVar("btag_trkjets02_e");
    Double_t * v_btag_trkjets02_pt = event.GetVar("btag_trkjets02_pt");
    Double_t * v_btag_trkjets02_m = event.GetVar("btag_trkjets02_m");
    Double_t * v_btag_trkjets04_e = event.GetVar("btag_trkjets04_e");
    Double_t * v_btag_trkjets04_pt = event.GetVar("btag_trkjets04_pt");
    Double_t * v_btag_trkjets04_m = event.GetVar("btag_trkjets04_m");
    Double_t * v_btag_trkjets08_e = event.GetVar("btag_trkjets08_e");
    Double_t * v_btag_trkjets08_pt = event.GetVar("btag_trkjets08_pt");
    Double_t * v_btag_trkjets08_m = event.GetVar("btag_trkjets08_m");
    Double_t * v_BestMass_jet_e = event.GetVar("BestMass_jet_e");
    Double_t * v_BestMass_jet_pt = event.GetVar("BestMass_jet_pt");
    Double_t * v_BestMass_jet_m = event.GetVar("BestMass_jet_m");
    Double_t * v_BestTopMass_jet_e = event.GetVar("BestTopMass_jet_e");
    Double_t * v_BestTopMass_jet_pt = event.GetVar("BestTopMass_jet_pt");
    Double_t * v_BestTopMass_jet_m = event.GetVar("BestTopMass_jet_m");
    Double_t * v_SecondTopMass_jet_e = event.GetVar("SecondTopMass_jet_e");
    Double_t * v_SecondTopMass_jet_pt = event.GetVar("SecondTopMass_jet_pt");
    Double_t * v_SecondTopMass_jet_m = event.GetVar("SecondTopMass_jet_m");
    Double_t * v_ptag_pfjets02_softDroppedJet_pt = event.GetVar("ptag_pfjets02_softDroppedJet_pt");
    Double_t * v_ptag_pfjets02_softDroppedJet_m = event.GetVar("ptag_pfjets02_softDroppedJet_m");
    Double_t * v_ptag_pfjets02_softDroppedJet_e = event.GetVar("ptag_pfjets02_softDroppedJet_e");
    Double_t * v_ptag_pfjets02_leadingSoftDroppedSubJet_pt = event.GetVar("ptag_pfjets02_leadingSoftDroppedSubJet_pt");
    Double_t * v_ptag_pfjets02_leadingSoftDroppedSubJet_m = event.GetVar("ptag_pfjets02_leadingSoftDroppedSubJet_m");
    Double_t * v_ptag_pfjets02_leadingSoftDroppedSubJet_e = event.GetVar("ptag_pfjets02_leadingSoftDroppedSubJet_e");
    Double_t * v_ptag_pfjets02_trailingSoftDroppedSubJet_pt = event.GetVar("ptag_pfjets02_trailingSoftDroppedSubJet_pt");
    Double_t * v_ptag_pfjets02_trailingSoftDroppedSubJet_m = event.GetVar("ptag_pfjets02_trailingSoftDroppedSubJet_m");
    Double_t * v_ptag_pfjets02_trailingSoftDroppedSubJet_e = event.GetVar("ptag_pfjets02_trailingSoftDroppedSubJet_e");
    Double_t * v_ptag_pfjets04_softDroppedJet_pt = event.GetVar("ptag_pfjets04_softDroppedJet_pt");
    Double_t * v_ptag_pfjets04_softDroppedJet_m = event.GetVar("ptag_pfjets04_softDroppedJet_m");
    Double_t * v_ptag_pfjets04_softDroppedJet_e = event.GetVar("ptag_pfjets04_softDroppedJet_e");
    Double_t * v_ptag_pfjets04_leadingSoftDroppedSubJet_pt = event.GetVar("ptag_pfjets04_leadingSoftDroppedSubJet_pt");
    Double_t * v_ptag_pfjets04_leadingSoftDroppedSubJet_m = event.GetVar("ptag_pfjets04_leadingSoftDroppedSubJet_m");
    Double_t * v_ptag_pfjets04_leadingSoftDroppedSubJet_e = event.GetVar("ptag_pfjets04_leadingSoftDroppedSubJet_e");
    Double_t * v_ptag_pfjets04_trailingSoftDroppedSubJet_pt = event.GetVar("ptag_pfjets04_trailingSoftDroppedSubJet_pt");
    Double_t * v_ptag_pfjets04_trailingSoftDroppedSubJet_m = event.GetVar("ptag_pfjets04_trailingSoftDroppedSubJet_m");
    Double_t * v_ptag_pfjets04_trailingSoftDroppedSubJet_e = event.GetVar("ptag_pfjets04_trailingSoftDroppedSubJet_e");
    Double_t * v_ptag_pfjets08_softDroppedJet_pt = event.GetVar("ptag_pfjets08_softDroppedJet_pt");
    Double_t * v_ptag_pfjets08_softDroppedJet_m = event.GetVar("ptag_pfjets08_softDroppedJet_m");
    Double_t * v_ptag_pfjets08_softDroppedJet_e = event.GetVar("ptag_pfjets08_softDroppedJet_e");
    Double_t * v_ptag_pfjets08_leadingSoftDroppedSubJet_pt = event.GetVar("ptag_pfjets08_leadingSoftDroppedSubJet_pt");
    Double_t * v_ptag_pfjets08_leadingSoftDroppedSubJet_m = event.GetVar("ptag_pfjets08_leadingSoftDroppedSubJet_m");
    Double_t * v_ptag_pfjets08_leadingSoftDroppedSubJet_e = event.GetVar("ptag_pfjets08_leadingSoftDroppedSubJet_e");
    Double_t * v_ptag_pfjets08_trailingSoftDroppedSubJet_pt = event.GetVar("ptag_pfjets08_trailingSoftDroppedSubJet_pt");
    Double_t * v_ptag_pfjets08_trailingSoftDroppedSubJet_m = event.GetVar("ptag_pfjets08_trailingSoftDroppedSubJet_m");
    Double_t * v_ptag_pfjets08_trailingSoftDroppedSubJet_e = event.GetVar("ptag_pfjets08_trailingSoftDroppedSubJet_e");
    Double_t * v_btag_pfjets02_softDroppedJet_pt = event.GetVar("btag_pfjets02_softDroppedJet_pt");
    Double_t * v_btag_pfjets02_softDroppedJet_m = event.GetVar("btag_pfjets02_softDroppedJet_m");
    Double_t * v_btag_pfjets02_softDroppedJet_e = event.GetVar("btag_pfjets02_softDroppedJet_e");
    Double_t * v_btag_pfjets02_leadingSoftDroppedSubJet_pt = event.GetVar("btag_pfjets02_leadingSoftDroppedSubJet_pt");
    Double_t * v_btag_pfjets02_leadingSoftDroppedSubJet_m = event.GetVar("btag_pfjets02_leadingSoftDroppedSubJet_m");
    Double_t * v_btag_pfjets02_leadingSoftDroppedSubJet_e = event.GetVar("btag_pfjets02_leadingSoftDroppedSubJet_e");
    Double_t * v_btag_pfjets02_trailingSoftDroppedSubJet_pt = event.GetVar("btag_pfjets02_trailingSoftDroppedSubJet_pt");
    Double_t * v_btag_pfjets02_trailingSoftDroppedSubJet_m = event.GetVar("btag_pfjets02_trailingSoftDroppedSubJet_m");
    Double_t * v_btag_pfjets02_trailingSoftDroppedSubJet_e = event.GetVar("btag_pfjets02_trailingSoftDroppedSubJet_e");
    Double_t * v_btag_pfjets04_softDroppedJet_pt = event.GetVar("btag_pfjets04_softDroppedJet_pt");
    Double_t * v_btag_pfjets04_softDroppedJet_m = event.GetVar("btag_pfjets04_softDroppedJet_m");
    Double_t * v_btag_pfjets04_softDroppedJet_e = event.GetVar("btag_pfjets04_softDroppedJet_e");
    Double_t * v_btag_pfjets04_leadingSoftDroppedSubJet_pt = event.GetVar("btag_pfjets04_leadingSoftDroppedSubJet_pt");
    Double_t * v_btag_pfjets04_leadingSoftDroppedSubJet_m = event.GetVar("btag_pfjets04_leadingSoftDroppedSubJet_m");
    Double_t * v_btag_pfjets04_leadingSoftDroppedSubJet_e = event.GetVar("btag_pfjets04_leadingSoftDroppedSubJet_e");
    Double_t * v_btag_pfjets04_trailingSoftDroppedSubJet_pt = event.GetVar("btag_pfjets04_trailingSoftDroppedSubJet_pt");
    Double_t * v_btag_pfjets04_trailingSoftDroppedSubJet_m = event.GetVar("btag_pfjets04_trailingSoftDroppedSubJet_m");
    Double_t * v_btag_pfjets04_trailingSoftDroppedSubJet_e = event.GetVar("btag_pfjets04_trailingSoftDroppedSubJet_e");
    Double_t * v_btag_pfjets08_softDroppedJet_pt = event.GetVar("btag_pfjets08_softDroppedJet_pt");
    Double_t * v_btag_pfjets08_softDroppedJet_m = event.GetVar("btag_pfjets08_softDroppedJet_m");
    Double_t * v_btag_pfjets08_softDroppedJet_e = event.GetVar("btag_pfjets08_softDroppedJet_e");
    Double_t * v_btag_pfjets08_leadingSoftDroppedSubJet_pt = event.GetVar("btag_pfjets08_leadingSoftDroppedSubJet_pt");
    Double_t * v_btag_pfjets08_leadingSoftDroppedSubJet_m = event.GetVar("btag_pfjets08_leadingSoftDroppedSubJet_m");
    Double_t * v_btag_pfjets08_leadingSoftDroppedSubJet_e = event.GetVar("btag_pfjets08_leadingSoftDroppedSubJet_e");
    Double_t * v_btag_pfjets08_trailingSoftDroppedSubJet_pt = event.GetVar("btag_pfjets08_trailingSoftDroppedSubJet_pt");
    Double_t * v_btag_pfjets08_trailingSoftDroppedSubJet_m = event.GetVar("btag_pfjets08_trailingSoftDroppedSubJet_m");
    Double_t * v_btag_pfjets08_trailingSoftDroppedSubJet_e = event.GetVar("btag_pfjets08_trailingSoftDroppedSubJet_e");
    Double_t * v_ptag_calojets02_softDroppedJet_pt = event.GetVar("ptag_calojets02_softDroppedJet_pt");
    Double_t * v_ptag_calojets02_softDroppedJet_m = event.GetVar("ptag_calojets02_softDroppedJet_m");
    Double_t * v_ptag_calojets02_softDroppedJet_e = event.GetVar("ptag_calojets02_softDroppedJet_e");
    Double_t * v_ptag_calojets02_leadingSoftDroppedSubJet_pt = event.GetVar("ptag_calojets02_leadingSoftDroppedSubJet_pt");
    Double_t * v_ptag_calojets02_leadingSoftDroppedSubJet_m = event.GetVar("ptag_calojets02_leadingSoftDroppedSubJet_m");
    Double_t * v_ptag_calojets02_leadingSoftDroppedSubJet_e = event.GetVar("ptag_calojets02_leadingSoftDroppedSubJet_e");
    Double_t * v_ptag_calojets02_trailingSoftDroppedSubJet_pt = event.GetVar("ptag_calojets02_trailingSoftDroppedSubJet_pt");
    Double_t * v_ptag_calojets02_trailingSoftDroppedSubJet_m = event.GetVar("ptag_calojets02_trailingSoftDroppedSubJet_m");
    Double_t * v_ptag_calojets02_trailingSoftDroppedSubJet_e = event.GetVar("ptag_calojets02_trailingSoftDroppedSubJet_e");
    Double_t * v_ptag_calojets04_softDroppedJet_pt = event.GetVar("ptag_calojets04_softDroppedJet_pt");
    Double_t * v_ptag_calojets04_softDroppedJet_m = event.GetVar("ptag_calojets04_softDroppedJet_m");
    Double_t * v_ptag_calojets04_softDroppedJet_e = event.GetVar("ptag_calojets04_softDroppedJet_e");
    Double_t * v_ptag_calojets04_leadingSoftDroppedSubJet_pt = event.GetVar("ptag_calojets04_leadingSoftDroppedSubJet_pt");
    Double_t * v_ptag_calojets04_leadingSoftDroppedSubJet_m = event.GetVar("ptag_calojets04_leadingSoftDroppedSubJet_m");
    Double_t * v_ptag_calojets04_leadingSoftDroppedSubJet_e = event.GetVar("ptag_calojets04_leadingSoftDroppedSubJet_e");
    Double_t * v_ptag_calojets04_trailingSoftDroppedSubJet_pt = event.GetVar("ptag_calojets04_trailingSoftDroppedSubJet_pt");
    Double_t * v_ptag_calojets04_trailingSoftDroppedSubJet_m = event.GetVar("ptag_calojets04_trailingSoftDroppedSubJet_m");
    Double_t * v_ptag_calojets04_trailingSoftDroppedSubJet_e = event.GetVar("ptag_calojets04_trailingSoftDroppedSubJet_e");
    Double_t * v_ptag_calojets08_softDroppedJet_pt = event.GetVar("ptag_calojets08_softDroppedJet_pt");
    Double_t * v_ptag_calojets08_softDroppedJet_m = event.GetVar("ptag_calojets08_softDroppedJet_m");
    Double_t * v_ptag_calojets08_softDroppedJet_e = event.GetVar("ptag_calojets08_softDroppedJet_e");
    Double_t * v_ptag_calojets08_leadingSoftDroppedSubJet_pt = event.GetVar("ptag_calojets08_leadingSoftDroppedSubJet_pt");
    Double_t * v_ptag_calojets08_leadingSoftDroppedSubJet_m = event.GetVar("ptag_calojets08_leadingSoftDroppedSubJet_m");
    Double_t * v_ptag_calojets08_leadingSoftDroppedSubJet_e = event.GetVar("ptag_calojets08_leadingSoftDroppedSubJet_e");
    Double_t * v_ptag_calojets08_trailingSoftDroppedSubJet_pt = event.GetVar("ptag_calojets08_trailingSoftDroppedSubJet_pt");
    Double_t * v_ptag_calojets08_trailingSoftDroppedSubJet_m = event.GetVar("ptag_calojets08_trailingSoftDroppedSubJet_m");
    Double_t * v_ptag_calojets08_trailingSoftDroppedSubJet_e = event.GetVar("ptag_calojets08_trailingSoftDroppedSubJet_e");
    Double_t * v_btag_calojets02_softDroppedJet_pt = event.GetVar("btag_calojets02_softDroppedJet_pt");
    Double_t * v_btag_calojets02_softDroppedJet_m = event.GetVar("btag_calojets02_softDroppedJet_m");
    Double_t * v_btag_calojets02_softDroppedJet_e = event.GetVar("btag_calojets02_softDroppedJet_e");
    Double_t * v_btag_calojets02_leadingSoftDroppedSubJet_pt = event.GetVar("btag_calojets02_leadingSoftDroppedSubJet_pt");
    Double_t * v_btag_calojets02_leadingSoftDroppedSubJet_m = event.GetVar("btag_calojets02_leadingSoftDroppedSubJet_m");
    Double_t * v_btag_calojets02_leadingSoftDroppedSubJet_e = event.GetVar("btag_calojets02_leadingSoftDroppedSubJet_e");
    Double_t * v_btag_calojets02_trailingSoftDroppedSubJet_pt = event.GetVar("btag_calojets02_trailingSoftDroppedSubJet_pt");
    Double_t * v_btag_calojets02_trailingSoftDroppedSubJet_m = event.GetVar("btag_calojets02_trailingSoftDroppedSubJet_m");
    Double_t * v_btag_calojets02_trailingSoftDroppedSubJet_e = event.GetVar("btag_calojets02_trailingSoftDroppedSubJet_e");
    Double_t * v_btag_calojets04_softDroppedJet_pt = event.GetVar("btag_calojets04_softDroppedJet_pt");
    Double_t * v_btag_calojets04_softDroppedJet_m = event.GetVar("btag_calojets04_softDroppedJet_m");
    Double_t * v_btag_calojets04_softDroppedJet_e = event.GetVar("btag_calojets04_softDroppedJet_e");
    Double_t * v_btag_calojets04_leadingSoftDroppedSubJet_pt = event.GetVar("btag_calojets04_leadingSoftDroppedSubJet_pt");
    Double_t * v_btag_calojets04_leadingSoftDroppedSubJet_m = event.GetVar("btag_calojets04_leadingSoftDroppedSubJet_m");
    Double_t * v_btag_calojets04_leadingSoftDroppedSubJet_e = event.GetVar("btag_calojets04_leadingSoftDroppedSubJet_e");
    Double_t * v_btag_calojets04_trailingSoftDroppedSubJet_pt = event.GetVar("btag_calojets04_trailingSoftDroppedSubJet_pt");
    Double_t * v_btag_calojets04_trailingSoftDroppedSubJet_m = event.GetVar("btag_calojets04_trailingSoftDroppedSubJet_m");
    Double_t * v_btag_calojets04_trailingSoftDroppedSubJet_e = event.GetVar("btag_calojets04_trailingSoftDroppedSubJet_e");
    Double_t * v_btag_calojets08_softDroppedJet_pt = event.GetVar("btag_calojets08_softDroppedJet_pt");
    Double_t * v_btag_calojets08_softDroppedJet_m = event.GetVar("btag_calojets08_softDroppedJet_m");
    Double_t * v_btag_calojets08_softDroppedJet_e = event.GetVar("btag_calojets08_softDroppedJet_e");
    Double_t * v_btag_calojets08_leadingSoftDroppedSubJet_pt = event.GetVar("btag_calojets08_leadingSoftDroppedSubJet_pt");
    Double_t * v_btag_calojets08_leadingSoftDroppedSubJet_m = event.GetVar("btag_calojets08_leadingSoftDroppedSubJet_m");
    Double_t * v_btag_calojets08_leadingSoftDroppedSubJet_e = event.GetVar("btag_calojets08_leadingSoftDroppedSubJet_e");
    Double_t * v_btag_calojets08_trailingSoftDroppedSubJet_pt = event.GetVar("btag_calojets08_trailingSoftDroppedSubJet_pt");
    Double_t * v_btag_calojets08_trailingSoftDroppedSubJet_m = event.GetVar("btag_calojets08_trailingSoftDroppedSubJet_m");
    Double_t * v_btag_calojets08_trailingSoftDroppedSubJet_e = event.GetVar("btag_calojets08_trailingSoftDroppedSubJet_e");
    Double_t * v_ptag_trkjets02_softDroppedJet_pt = event.GetVar("ptag_trkjets02_softDroppedJet_pt");
    Double_t * v_ptag_trkjets02_softDroppedJet_m = event.GetVar("ptag_trkjets02_softDroppedJet_m");
    Double_t * v_ptag_trkjets02_softDroppedJet_e = event.GetVar("ptag_trkjets02_softDroppedJet_e");
    Double_t * v_ptag_trkjets02_leadingSoftDroppedSubJet_pt = event.GetVar("ptag_trkjets02_leadingSoftDroppedSubJet_pt");
    Double_t * v_ptag_trkjets02_leadingSoftDroppedSubJet_m = event.GetVar("ptag_trkjets02_leadingSoftDroppedSubJet_m");
    Double_t * v_ptag_trkjets02_leadingSoftDroppedSubJet_e = event.GetVar("ptag_trkjets02_leadingSoftDroppedSubJet_e");
    Double_t * v_ptag_trkjets02_trailingSoftDroppedSubJet_pt = event.GetVar("ptag_trkjets02_trailingSoftDroppedSubJet_pt");
    Double_t * v_ptag_trkjets02_trailingSoftDroppedSubJet_m = event.GetVar("ptag_trkjets02_trailingSoftDroppedSubJet_m");
    Double_t * v_ptag_trkjets02_trailingSoftDroppedSubJet_e = event.GetVar("ptag_trkjets02_trailingSoftDroppedSubJet_e");
    Double_t * v_ptag_trkjets04_softDroppedJet_pt = event.GetVar("ptag_trkjets04_softDroppedJet_pt");
    Double_t * v_ptag_trkjets04_softDroppedJet_m = event.GetVar("ptag_trkjets04_softDroppedJet_m");
    Double_t * v_ptag_trkjets04_softDroppedJet_e = event.GetVar("ptag_trkjets04_softDroppedJet_e");
    Double_t * v_ptag_trkjets04_leadingSoftDroppedSubJet_pt = event.GetVar("ptag_trkjets04_leadingSoftDroppedSubJet_pt");
    Double_t * v_ptag_trkjets04_leadingSoftDroppedSubJet_m = event.GetVar("ptag_trkjets04_leadingSoftDroppedSubJet_m");
    Double_t * v_ptag_trkjets04_leadingSoftDroppedSubJet_e = event.GetVar("ptag_trkjets04_leadingSoftDroppedSubJet_e");
    Double_t * v_ptag_trkjets04_trailingSoftDroppedSubJet_pt = event.GetVar("ptag_trkjets04_trailingSoftDroppedSubJet_pt");
    Double_t * v_ptag_trkjets04_trailingSoftDroppedSubJet_m = event.GetVar("ptag_trkjets04_trailingSoftDroppedSubJet_m");
    Double_t * v_ptag_trkjets04_trailingSoftDroppedSubJet_e = event.GetVar("ptag_trkjets04_trailingSoftDroppedSubJet_e");
    Double_t * v_ptag_trkjets08_softDroppedJet_pt = event.GetVar("ptag_trkjets08_softDroppedJet_pt");
    Double_t * v_ptag_trkjets08_softDroppedJet_m = event.GetVar("ptag_trkjets08_softDroppedJet_m");
    Double_t * v_ptag_trkjets08_softDroppedJet_e = event.GetVar("ptag_trkjets08_softDroppedJet_e");
    Double_t * v_ptag_trkjets08_leadingSoftDroppedSubJet_pt = event.GetVar("ptag_trkjets08_leadingSoftDroppedSubJet_pt");
    Double_t * v_ptag_trkjets08_leadingSoftDroppedSubJet_m = event.GetVar("ptag_trkjets08_leadingSoftDroppedSubJet_m");
    Double_t * v_ptag_trkjets08_leadingSoftDroppedSubJet_e = event.GetVar("ptag_trkjets08_leadingSoftDroppedSubJet_e");
    Double_t * v_ptag_trkjets08_trailingSoftDroppedSubJet_pt = event.GetVar("ptag_trkjets08_trailingSoftDroppedSubJet_pt");
    Double_t * v_ptag_trkjets08_trailingSoftDroppedSubJet_m = event.GetVar("ptag_trkjets08_trailingSoftDroppedSubJet_m");
    Double_t * v_ptag_trkjets08_trailingSoftDroppedSubJet_e = event.GetVar("ptag_trkjets08_trailingSoftDroppedSubJet_e");
    Double_t * v_btag_trkjets02_softDroppedJet_pt = event.GetVar("btag_trkjets02_softDroppedJet_pt");
    Double_t * v_btag_trkjets02_softDroppedJet_m = event.GetVar("btag_trkjets02_softDroppedJet_m");
    Double_t * v_btag_trkjets02_softDroppedJet_e = event.GetVar("btag_trkjets02_softDroppedJet_e");
    Double_t * v_btag_trkjets02_leadingSoftDroppedSubJet_pt = event.GetVar("btag_trkjets02_leadingSoftDroppedSubJet_pt");
    Double_t * v_btag_trkjets02_leadingSoftDroppedSubJet_m = event.GetVar("btag_trkjets02_leadingSoftDroppedSubJet_m");
    Double_t * v_btag_trkjets02_leadingSoftDroppedSubJet_e = event.GetVar("btag_trkjets02_leadingSoftDroppedSubJet_e");
    Double_t * v_btag_trkjets02_trailingSoftDroppedSubJet_pt = event.GetVar("btag_trkjets02_trailingSoftDroppedSubJet_pt");
    Double_t * v_btag_trkjets02_trailingSoftDroppedSubJet_m = event.GetVar("btag_trkjets02_trailingSoftDroppedSubJet_m");
    Double_t * v_btag_trkjets02_trailingSoftDroppedSubJet_e = event.GetVar("btag_trkjets02_trailingSoftDroppedSubJet_e");
    Double_t * v_btag_trkjets04_softDroppedJet_pt = event.GetVar("btag_trkjets04_softDroppedJet_pt");
    Double_t * v_btag_trkjets04_softDroppedJet_m = event.GetVar("btag_trkjets04_softDroppedJet_m");
    Double_t * v_btag_trkjets04_softDroppedJet_e = event.GetVar("btag_trkjets04_softDroppedJet_e");
    Double_t * v_btag_trkjets04_leadingSoftDroppedSubJet_pt = event.GetVar("btag_trkjets04_leadingSoftDroppedSubJet_pt");
    Double_t * v_btag_trkjets04_leadingSoftDroppedSubJet_m = event.GetVar("btag_trkjets04_leadingSoftDroppedSubJet_m");
    Double_t * v_btag_trkjets04_leadingSoftDroppedSubJet_e = event.GetVar("btag_trkjets04_leadingSoftDroppedSubJet_e");
    Double_t * v_btag_trkjets04_trailingSoftDroppedSubJet_pt = event.GetVar("btag_trkjets04_trailingSoftDroppedSubJet_pt");
    Double_t * v_btag_trkjets04_trailingSoftDroppedSubJet_m = event.GetVar("btag_trkjets04_trailingSoftDroppedSubJet_m");
    Double_t * v_btag_trkjets04_trailingSoftDroppedSubJet_e = event.GetVar("btag_trkjets04_trailingSoftDroppedSubJet_e");
    Double_t * v_btag_trkjets08_softDroppedJet_pt = event.GetVar("btag_trkjets08_softDroppedJet_pt");
    Double_t * v_btag_trkjets08_softDroppedJet_m = event.GetVar("btag_trkjets08_softDroppedJet_m");
    Double_t * v_btag_trkjets08_softDroppedJet_e = event.GetVar("btag_trkjets08_softDroppedJet_e");
    Double_t * v_btag_trkjets08_leadingSoftDroppedSubJet_pt = event.GetVar("btag_trkjets08_leadingSoftDroppedSubJet_pt");
    Double_t * v_btag_trkjets08_leadingSoftDroppedSubJet_m = event.GetVar("btag_trkjets08_leadingSoftDroppedSubJet_m");
    Double_t * v_btag_trkjets08_leadingSoftDroppedSubJet_e = event.GetVar("btag_trkjets08_leadingSoftDroppedSubJet_e");
    Double_t * v_btag_trkjets08_trailingSoftDroppedSubJet_pt = event.GetVar("btag_trkjets08_trailingSoftDroppedSubJet_pt");
    Double_t * v_btag_trkjets08_trailingSoftDroppedSubJet_m = event.GetVar("btag_trkjets08_trailingSoftDroppedSubJet_m");
    Double_t * v_btag_trkjets08_trailingSoftDroppedSubJet_e = event.GetVar("btag_trkjets08_trailingSoftDroppedSubJet_e");
    Double_t * v_BestMass_jet_softDroppedJet_pt = event.GetVar("BestMass_jet_softDroppedJet_pt");
    Double_t * v_BestMass_jet_softDroppedJet_m = event.GetVar("BestMass_jet_softDroppedJet_m");
    Double_t * v_BestMass_jet_softDroppedJet_e = event.GetVar("BestMass_jet_softDroppedJet_e");
    Double_t * v_BestMass_jet_leadingSoftDroppedSubJet_pt = event.GetVar("BestMass_jet_leadingSoftDroppedSubJet_pt");
    Double_t * v_BestMass_jet_leadingSoftDroppedSubJet_m = event.GetVar("BestMass_jet_leadingSoftDroppedSubJet_m");
    Double_t * v_BestMass_jet_leadingSoftDroppedSubJet_e = event.GetVar("BestMass_jet_leadingSoftDroppedSubJet_e");
    Double_t * v_BestMass_jet_trailingSoftDroppedSubJet_pt = event.GetVar("BestMass_jet_trailingSoftDroppedSubJet_pt");
    Double_t * v_BestMass_jet_trailingSoftDroppedSubJet_m = event.GetVar("BestMass_jet_trailingSoftDroppedSubJet_m");
    Double_t * v_BestMass_jet_trailingSoftDroppedSubJet_e = event.GetVar("BestMass_jet_trailingSoftDroppedSubJet_e");
    Double_t * v_BestTopMass_jet_softDroppedJet_pt = event.GetVar("BestTopMass_jet_softDroppedJet_pt");
    Double_t * v_BestTopMass_jet_softDroppedJet_m = event.GetVar("BestTopMass_jet_softDroppedJet_m");
    Double_t * v_BestTopMass_jet_softDroppedJet_e = event.GetVar("BestTopMass_jet_softDroppedJet_e");
    Double_t * v_BestTopMass_jet_leadingSoftDroppedSubJet_pt = event.GetVar("BestTopMass_jet_leadingSoftDroppedSubJet_pt");
    Double_t * v_BestTopMass_jet_leadingSoftDroppedSubJet_m = event.GetVar("BestTopMass_jet_leadingSoftDroppedSubJet_m");
    Double_t * v_BestTopMass_jet_leadingSoftDroppedSubJet_e = event.GetVar("BestTopMass_jet_leadingSoftDroppedSubJet_e");
    Double_t * v_BestTopMass_jet_trailingSoftDroppedSubJet_pt = event.GetVar("BestTopMass_jet_trailingSoftDroppedSubJet_pt");
    Double_t * v_BestTopMass_jet_trailingSoftDroppedSubJet_m = event.GetVar("BestTopMass_jet_trailingSoftDroppedSubJet_m");
    Double_t * v_BestTopMass_jet_trailingSoftDroppedSubJet_e = event.GetVar("BestTopMass_jet_trailingSoftDroppedSubJet_e");
    Double_t * v_SecondTopMass_jet_softDroppedJet_pt = event.GetVar("SecondTopMass_jet_softDroppedJet_pt");
    Double_t * v_SecondTopMass_jet_softDroppedJet_m = event.GetVar("SecondTopMass_jet_softDroppedJet_m");
    Double_t * v_SecondTopMass_jet_softDroppedJet_e = event.GetVar("SecondTopMass_jet_softDroppedJet_e");
    Double_t * v_SecondTopMass_jet_leadingSoftDroppedSubJet_pt = event.GetVar("SecondTopMass_jet_leadingSoftDroppedSubJet_pt");
    Double_t * v_SecondTopMass_jet_leadingSoftDroppedSubJet_m = event.GetVar("SecondTopMass_jet_leadingSoftDroppedSubJet_m");
    Double_t * v_SecondTopMass_jet_leadingSoftDroppedSubJet_e = event.GetVar("SecondTopMass_jet_leadingSoftDroppedSubJet_e");
    Double_t * v_SecondTopMass_jet_trailingSoftDroppedSubJet_pt = event.GetVar("SecondTopMass_jet_trailingSoftDroppedSubJet_pt");
    Double_t * v_SecondTopMass_jet_trailingSoftDroppedSubJet_m = event.GetVar("SecondTopMass_jet_trailingSoftDroppedSubJet_m");
    Double_t * v_SecondTopMass_jet_trailingSoftDroppedSubJet_e = event.GetVar("SecondTopMass_jet_trailingSoftDroppedSubJet_e");
    Double_t * v_dPhi_Photon_ptag_pfjets02 = event.GetVar("dPhi_Photon_ptag_pfjets02");
    Double_t * v_dR_Photon_ptag_pfjets02 = event.GetVar("dR_Photon_ptag_pfjets02");
    Double_t * v_M_Photon_ptag_pfjets02 = event.GetVar("M_Photon_ptag_pfjets02");
    Double_t * v_dPhi_bjet_ptag_pfjets02 = event.GetVar("dPhi_bjet_ptag_pfjets02");
    Double_t * v_dR_bjet_ptag_pfjets02 = event.GetVar("dR_bjet_ptag_pfjets02");
    Double_t * v_dPhi_Photon_ptag_pfjets04 = event.GetVar("dPhi_Photon_ptag_pfjets04");
    Double_t * v_dR_Photon_ptag_pfjets04 = event.GetVar("dR_Photon_ptag_pfjets04");
    Double_t * v_M_Photon_ptag_pfjets04 = event.GetVar("M_Photon_ptag_pfjets04");
    Double_t * v_dPhi_bjet_ptag_pfjets04 = event.GetVar("dPhi_bjet_ptag_pfjets04");
    Double_t * v_dR_bjet_ptag_pfjets04 = event.GetVar("dR_bjet_ptag_pfjets04");
    Double_t * v_dPhi_Photon_ptag_pfjets08 = event.GetVar("dPhi_Photon_ptag_pfjets08");
    Double_t * v_dR_Photon_ptag_pfjets08 = event.GetVar("dR_Photon_ptag_pfjets08");
    Double_t * v_M_Photon_ptag_pfjets08 = event.GetVar("M_Photon_ptag_pfjets08");
    Double_t * v_dPhi_bjet_ptag_pfjets08 = event.GetVar("dPhi_bjet_ptag_pfjets08");
    Double_t * v_dR_bjet_ptag_pfjets08 = event.GetVar("dR_bjet_ptag_pfjets08");
    Double_t * v_dPhi_Photon_btag_pfjets02 = event.GetVar("dPhi_Photon_btag_pfjets02");
    Double_t * v_dR_Photon_btag_pfjets02 = event.GetVar("dR_Photon_btag_pfjets02");
    Double_t * v_M_Photon_btag_pfjets02 = event.GetVar("M_Photon_btag_pfjets02");
    Double_t * v_dPhi_bjet_btag_pfjets02 = event.GetVar("dPhi_bjet_btag_pfjets02");
    Double_t * v_dR_bjet_btag_pfjets02 = event.GetVar("dR_bjet_btag_pfjets02");
    Double_t * v_dPhi_Photon_btag_pfjets04 = event.GetVar("dPhi_Photon_btag_pfjets04");
    Double_t * v_dR_Photon_btag_pfjets04 = event.GetVar("dR_Photon_btag_pfjets04");
    Double_t * v_M_Photon_btag_pfjets04 = event.GetVar("M_Photon_btag_pfjets04");
    Double_t * v_dPhi_bjet_btag_pfjets04 = event.GetVar("dPhi_bjet_btag_pfjets04");
    Double_t * v_dR_bjet_btag_pfjets04 = event.GetVar("dR_bjet_btag_pfjets04");
    Double_t * v_dPhi_Photon_btag_pfjets08 = event.GetVar("dPhi_Photon_btag_pfjets08");
    Double_t * v_dR_Photon_btag_pfjets08 = event.GetVar("dR_Photon_btag_pfjets08");
    Double_t * v_M_Photon_btag_pfjets08 = event.GetVar("M_Photon_btag_pfjets08");
    Double_t * v_dPhi_bjet_btag_pfjets08 = event.GetVar("dPhi_bjet_btag_pfjets08");
    Double_t * v_dR_bjet_btag_pfjets08 = event.GetVar("dR_bjet_btag_pfjets08");
    Double_t * v_dPhi_Photon_ptag_calojets02 = event.GetVar("dPhi_Photon_ptag_calojets02");
    Double_t * v_dR_Photon_ptag_calojets02 = event.GetVar("dR_Photon_ptag_calojets02");
    Double_t * v_M_Photon_ptag_calojets02 = event.GetVar("M_Photon_ptag_calojets02");
    Double_t * v_dPhi_bjet_ptag_calojets02 = event.GetVar("dPhi_bjet_ptag_calojets02");
    Double_t * v_dR_bjet_ptag_calojets02 = event.GetVar("dR_bjet_ptag_calojets02");
    Double_t * v_dPhi_Photon_ptag_calojets04 = event.GetVar("dPhi_Photon_ptag_calojets04");
    Double_t * v_dR_Photon_ptag_calojets04 = event.GetVar("dR_Photon_ptag_calojets04");
    Double_t * v_M_Photon_ptag_calojets04 = event.GetVar("M_Photon_ptag_calojets04");
    Double_t * v_dPhi_bjet_ptag_calojets04 = event.GetVar("dPhi_bjet_ptag_calojets04");
    Double_t * v_dR_bjet_ptag_calojets04 = event.GetVar("dR_bjet_ptag_calojets04");
    Double_t * v_dPhi_Photon_ptag_calojets08 = event.GetVar("dPhi_Photon_ptag_calojets08");
    Double_t * v_dR_Photon_ptag_calojets08 = event.GetVar("dR_Photon_ptag_calojets08");
    Double_t * v_M_Photon_ptag_calojets08 = event.GetVar("M_Photon_ptag_calojets08");
    Double_t * v_dPhi_bjet_ptag_calojets08 = event.GetVar("dPhi_bjet_ptag_calojets08");
    Double_t * v_dR_bjet_ptag_calojets08 = event.GetVar("dR_bjet_ptag_calojets08");
    Double_t * v_dPhi_Photon_btag_calojets02 = event.GetVar("dPhi_Photon_btag_calojets02");
    Double_t * v_dR_Photon_btag_calojets02 = event.GetVar("dR_Photon_btag_calojets02");
    Double_t * v_M_Photon_btag_calojets02 = event.GetVar("M_Photon_btag_calojets02");
    Double_t * v_dPhi_bjet_btag_calojets02 = event.GetVar("dPhi_bjet_btag_calojets02");
    Double_t * v_dR_bjet_btag_calojets02 = event.GetVar("dR_bjet_btag_calojets02");
    Double_t * v_dPhi_Photon_btag_calojets04 = event.GetVar("dPhi_Photon_btag_calojets04");
    Double_t * v_dR_Photon_btag_calojets04 = event.GetVar("dR_Photon_btag_calojets04");
    Double_t * v_M_Photon_btag_calojets04 = event.GetVar("M_Photon_btag_calojets04");
    Double_t * v_dPhi_bjet_btag_calojets04 = event.GetVar("dPhi_bjet_btag_calojets04");
    Double_t * v_dR_bjet_btag_calojets04 = event.GetVar("dR_bjet_btag_calojets04");
    Double_t * v_dPhi_Photon_btag_calojets08 = event.GetVar("dPhi_Photon_btag_calojets08");
    Double_t * v_dR_Photon_btag_calojets08 = event.GetVar("dR_Photon_btag_calojets08");
    Double_t * v_M_Photon_btag_calojets08 = event.GetVar("M_Photon_btag_calojets08");
    Double_t * v_dPhi_bjet_btag_calojets08 = event.GetVar("dPhi_bjet_btag_calojets08");
    Double_t * v_dR_bjet_btag_calojets08 = event.GetVar("dR_bjet_btag_calojets08");
    Double_t * v_dPhi_Photon_ptag_trkjets02 = event.GetVar("dPhi_Photon_ptag_trkjets02");
    Double_t * v_dR_Photon_ptag_trkjets02 = event.GetVar("dR_Photon_ptag_trkjets02");
    Double_t * v_M_Photon_ptag_trkjets02 = event.GetVar("M_Photon_ptag_trkjets02");
    Double_t * v_dPhi_bjet_ptag_trkjets02 = event.GetVar("dPhi_bjet_ptag_trkjets02");
    Double_t * v_dR_bjet_ptag_trkjets02 = event.GetVar("dR_bjet_ptag_trkjets02");
    Double_t * v_dPhi_Photon_ptag_trkjets04 = event.GetVar("dPhi_Photon_ptag_trkjets04");
    Double_t * v_dR_Photon_ptag_trkjets04 = event.GetVar("dR_Photon_ptag_trkjets04");
    Double_t * v_M_Photon_ptag_trkjets04 = event.GetVar("M_Photon_ptag_trkjets04");
    Double_t * v_dPhi_bjet_ptag_trkjets04 = event.GetVar("dPhi_bjet_ptag_trkjets04");
    Double_t * v_dR_bjet_ptag_trkjets04 = event.GetVar("dR_bjet_ptag_trkjets04");
    Double_t * v_dPhi_Photon_ptag_trkjets08 = event.GetVar("dPhi_Photon_ptag_trkjets08");
    Double_t * v_dR_Photon_ptag_trkjets08 = event.GetVar("dR_Photon_ptag_trkjets08");
    Double_t * v_M_Photon_ptag_trkjets08 = event.GetVar("M_Photon_ptag_trkjets08");
    Double_t * v_dPhi_bjet_ptag_trkjets08 = event.GetVar("dPhi_bjet_ptag_trkjets08");
    Double_t * v_dR_bjet_ptag_trkjets08 = event.GetVar("dR_bjet_ptag_trkjets08");
    Double_t * v_dPhi_Photon_btag_trkjets02 = event.GetVar("dPhi_Photon_btag_trkjets02");
    Double_t * v_dR_Photon_btag_trkjets02 = event.GetVar("dR_Photon_btag_trkjets02");
    Double_t * v_M_Photon_btag_trkjets02 = event.GetVar("M_Photon_btag_trkjets02");
    Double_t * v_dPhi_bjet_btag_trkjets02 = event.GetVar("dPhi_bjet_btag_trkjets02");
    Double_t * v_dR_bjet_btag_trkjets02 = event.GetVar("dR_bjet_btag_trkjets02");
    Double_t * v_dPhi_Photon_btag_trkjets04 = event.GetVar("dPhi_Photon_btag_trkjets04");
    Double_t * v_dR_Photon_btag_trkjets04 = event.GetVar("dR_Photon_btag_trkjets04");
    Double_t * v_M_Photon_btag_trkjets04 = event.GetVar("M_Photon_btag_trkjets04");
    Double_t * v_dPhi_bjet_btag_trkjets04 = event.GetVar("dPhi_bjet_btag_trkjets04");
    Double_t * v_dR_bjet_btag_trkjets04 = event.GetVar("dR_bjet_btag_trkjets04");
    Double_t * v_dPhi_Photon_btag_trkjets08 = event.GetVar("dPhi_Photon_btag_trkjets08");
    Double_t * v_dR_Photon_btag_trkjets08 = event.GetVar("dR_Photon_btag_trkjets08");
    Double_t * v_M_Photon_btag_trkjets08 = event.GetVar("M_Photon_btag_trkjets08");
    Double_t * v_dPhi_bjet_btag_trkjets08 = event.GetVar("dPhi_bjet_btag_trkjets08");
    Double_t * v_dR_bjet_btag_trkjets08 = event.GetVar("dR_bjet_btag_trkjets08");
    Double_t * v_dPhi_Photon_BestMass_jet = event.GetVar("dPhi_Photon_BestMass_jet");
    Double_t * v_dR_Photon_BestMass_jet = event.GetVar("dR_Photon_BestMass_jet");
    Double_t * v_M_Photon_BestMass_jet = event.GetVar("M_Photon_BestMass_jet");
    Double_t * v_dPhi_bjet_BestMass_jet = event.GetVar("dPhi_bjet_BestMass_jet");
    Double_t * v_dR_bjet_BestMass_jet = event.GetVar("dR_bjet_BestMass_jet");
    Double_t * v_dPhi_Photon_BestTopMass_jet = event.GetVar("dPhi_Photon_BestTopMass_jet");
    Double_t * v_dR_Photon_BestTopMass_jet = event.GetVar("dR_Photon_BestTopMass_jet");
    Double_t * v_M_Photon_BestTopMass_jet = event.GetVar("M_Photon_BestTopMass_jet");
    Double_t * v_dPhi_bjet_BestTopMass_jet = event.GetVar("dPhi_bjet_BestTopMass_jet");
    Double_t * v_dR_bjet_BestTopMass_jet = event.GetVar("dR_bjet_BestTopMass_jet");
    Double_t * v_dPhi_Photon_SecondTopMass_jet = event.GetVar("dPhi_Photon_SecondTopMass_jet");
    Double_t * v_dR_Photon_SecondTopMass_jet = event.GetVar("dR_Photon_SecondTopMass_jet");
    Double_t * v_M_Photon_SecondTopMass_jet = event.GetVar("M_Photon_SecondTopMass_jet");
    Double_t * v_dPhi_bjet_SecondTopMass_jet = event.GetVar("dPhi_bjet_SecondTopMass_jet");
    Double_t * v_dR_bjet_SecondTopMass_jet = event.GetVar("dR_bjet_SecondTopMass_jet");
    //[[[end]]]

    Double_t *weight;
    weight = event.GetVar("weight");
    // weight = new Double_t; *weight = 1;
    double lumi = 30 * 1000 * 1000;
    double xfactor;

    int nevents_train = 0;
    if(train_tree) nevents_train = train_tree->GetEntries();
    int nevents = event.tree->GetEntries();

    cout << file_name << " " << nevents << endl;
    // continue;

    double extra_weight = 1.0;
    if( process.signal ){
      // extra_weight = 11.82 * 2.0 * 2.0 * 0.428 * pow(0.001, 2) / (3069 / 10. * 1.0 * 1.0);
      extra_weight = 1.;
    }

    double train_reweight_factor = double(nevents + nevents_train) / nevents;
    for(int i = 0; i < nevents; i++){
      if(not (i%TMath::Max(int(0.05*nevents), 1))) cout << file_name << " " << i << "/" << nevents << endl;
      event.tree->GetEntry(i);

      // msg( "v_BestMass_jet_m = ", *v_BestMass_jet_m, *v_ptag_pfjets08_m );

      xfactor = (*weight) * lumi * train_reweight_factor * extra_weight;
      /*[[[cog
        for var in custom_variables :
          if var.frozen : continue
          string = var.hist_name + "->Fill( *v_" + var.key + ", xfactor);"
          cog.outl( string )

        for plot in cut_plots:
          string = plot.hist_cut_name + "->Fill( *v_" + plot.var.key + ", xfactor);"
          mRootCOG.if_then_else(plot.cut, string)

        for plot in corr_plots:
          string = plot.hist_name + "->Fill( *v_" + plot.var_x.key + ", *v_" + plot.var_y.key + ", xfactor);"
          cog.outl( string )
      ]]]*/
      hist_1->Fill( *v_photon_eta, xfactor);
      hist_3->Fill( *v_photon_pt, xfactor);
      hist_5->Fill( *v_top_pt, xfactor);
      hist_7->Fill( *v_ptag_bestJet_m, xfactor);
      hist_9->Fill( *v_ptag_bestJet_pt, xfactor);
      hist_11->Fill( *v_ptag_bestJet_eta, xfactor);
      hist_13->Fill( *v_btag_pfjets04_eta, xfactor);
      hist_15->Fill( *v_ptag_bestJet_tau1, xfactor);
      hist_17->Fill( *v_ptag_bestJet_tau2, xfactor);
      hist_19->Fill( *v_ptag_bestJet_tau3, xfactor);
      hist_21->Fill( *v_ptag_bestJet_tau31, xfactor);
      hist_23->Fill( *v_ptag_bestJet_tau32, xfactor);
      hist_25->Fill( *v_ptag_bestJet_tau21, xfactor);
      hist_27->Fill( *v_ptag_pfjets08_tau1, xfactor);
      hist_29->Fill( *v_ptag_pfjets08_tau2, xfactor);
      hist_31->Fill( *v_ptag_pfjets08_tau3, xfactor);
      hist_33->Fill( *v_ptag_pfjets08_tau31, xfactor);
      hist_35->Fill( *v_ptag_pfjets08_tau32, xfactor);
      hist_37->Fill( *v_ptag_pfjets08_tau21, xfactor);
      hist_39->Fill( *v_btag_pfjets08_tau1, xfactor);
      hist_41->Fill( *v_btag_pfjets08_tau2, xfactor);
      hist_43->Fill( *v_btag_pfjets08_tau3, xfactor);
      hist_45->Fill( *v_btag_pfjets08_tau31, xfactor);
      hist_47->Fill( *v_btag_pfjets08_tau32, xfactor);
      hist_49->Fill( *v_btag_pfjets08_tau21, xfactor);
      hist_51->Fill( *v_btag_pfjets04_tau1, xfactor);
      hist_53->Fill( *v_btag_pfjets04_tau2, xfactor);
      hist_55->Fill( *v_btag_pfjets04_tau3, xfactor);
      hist_57->Fill( *v_btag_pfjets04_tau31, xfactor);
      hist_59->Fill( *v_btag_pfjets04_tau32, xfactor);
      hist_61->Fill( *v_btag_pfjets04_tau21, xfactor);
      hist_63->Fill( *v_photon_x_ptag_bestJet, xfactor);
      hist_65->Fill( *v_lepton_x_btag_pfjets08, xfactor);
      hist_67->Fill( *v_dPhi_lepton_btag_pfjets08, xfactor);
      hist_69->Fill( *v_dR_lepton_btag_pfjets08, xfactor);
      hist_71->Fill( *v_lepton_x_btag_pfjets04, xfactor);
      hist_73->Fill( *v_dPhi_lepton_btag_pfjets04, xfactor);
      hist_75->Fill( *v_dR_lepton_btag_pfjets04, xfactor);
      hist_77->Fill( *v_M_lepton_met, xfactor);
      hist_79->Fill( *v_M_bjet_lepton_met, xfactor);
      hist_81->Fill( *v_dPhi_Photon_ptag_bestJet, xfactor);
      hist_83->Fill( *v_dR_Photon_ptag_bestJet, xfactor);
      hist_85->Fill( *v_M_Photon_ptag_bestJet, xfactor);
      hist_87->Fill( *v_bjet_x_ptag_bestJet, xfactor);
      hist_89->Fill( *v_dPhi_bjet_ptag_bestJet, xfactor);
      hist_91->Fill( *v_dR_bjet_ptag_bestJet, xfactor);
      hist_93->Fill( *v_lepton_relIso, xfactor);
      hist_95->Fill( *v_photon_relIso, xfactor);
      hist_97->Fill( *v_photon_x_ptag_pfjets08, xfactor);
      hist_99->Fill( *v_bjet_x_ptag_pfjets08, xfactor);
      hist_101->Fill( *v_weight_tune_3_BDT_0_000, xfactor);
      hist_103->Fill( *v_weight_tune_3_BDT_1_000, xfactor);
      hist_105->Fill( *v_weight_tune_3_BDT_2_000, xfactor);
      hist_107->Fill( *v_weight_tune_3_BDT_3_000, xfactor);
      hist_109->Fill( *v_weight_tune_3_BDT_4_000, xfactor);
      hist_111->Fill( *v_weight_tune_3_BDT_5_000, xfactor);
      hist_113->Fill( *v_weight_tune_3_BDT_6_000, xfactor);
      hist_115->Fill( *v_weight_tune_5_BDT_3_000, xfactor);
      hist_117->Fill( *v_ptag_pfjets02_e, xfactor);
      hist_119->Fill( *v_ptag_pfjets02_pt, xfactor);
      hist_121->Fill( *v_ptag_pfjets02_m, xfactor);
      hist_123->Fill( *v_ptag_pfjets04_e, xfactor);
      hist_125->Fill( *v_ptag_pfjets04_pt, xfactor);
      hist_127->Fill( *v_ptag_pfjets04_m, xfactor);
      hist_129->Fill( *v_ptag_pfjets08_e, xfactor);
      hist_131->Fill( *v_ptag_pfjets08_pt, xfactor);
      hist_133->Fill( *v_ptag_pfjets08_m, xfactor);
      hist_135->Fill( *v_btag_pfjets02_e, xfactor);
      hist_137->Fill( *v_btag_pfjets02_pt, xfactor);
      hist_139->Fill( *v_btag_pfjets02_m, xfactor);
      hist_141->Fill( *v_btag_pfjets04_e, xfactor);
      hist_143->Fill( *v_btag_pfjets04_pt, xfactor);
      hist_145->Fill( *v_btag_pfjets04_m, xfactor);
      hist_147->Fill( *v_btag_pfjets08_e, xfactor);
      hist_149->Fill( *v_btag_pfjets08_pt, xfactor);
      hist_151->Fill( *v_btag_pfjets08_m, xfactor);
      hist_153->Fill( *v_ptag_calojets04_m, xfactor);
      hist_155->Fill( *v_ptag_calojets08_m, xfactor);
      hist_157->Fill( *v_btag_calojets04_m, xfactor);
      hist_159->Fill( *v_btag_calojets08_m, xfactor);
      hist_161->Fill( *v_ptag_trkjets04_m, xfactor);
      hist_163->Fill( *v_ptag_trkjets08_m, xfactor);
      hist_165->Fill( *v_btag_trkjets04_m, xfactor);
      hist_167->Fill( *v_btag_trkjets08_m, xfactor);
      hist_169->Fill( *v_BestMass_jet_e, xfactor);
      hist_171->Fill( *v_BestMass_jet_pt, xfactor);
      hist_173->Fill( *v_BestMass_jet_m, xfactor);
      hist_175->Fill( *v_BestTopMass_jet_e, xfactor);
      hist_177->Fill( *v_BestTopMass_jet_pt, xfactor);
      hist_179->Fill( *v_BestTopMass_jet_m, xfactor);
      hist_181->Fill( *v_SecondTopMass_jet_e, xfactor);
      hist_183->Fill( *v_SecondTopMass_jet_pt, xfactor);
      hist_185->Fill( *v_SecondTopMass_jet_m, xfactor);
      hist_187->Fill( *v_ptag_pfjets02_softDroppedJet_pt, xfactor);
      hist_189->Fill( *v_ptag_pfjets02_softDroppedJet_m, xfactor);
      hist_191->Fill( *v_ptag_pfjets02_softDroppedJet_e, xfactor);
      hist_193->Fill( *v_ptag_pfjets02_leadingSoftDroppedSubJet_pt, xfactor);
      hist_195->Fill( *v_ptag_pfjets02_leadingSoftDroppedSubJet_m, xfactor);
      hist_197->Fill( *v_ptag_pfjets02_leadingSoftDroppedSubJet_e, xfactor);
      hist_199->Fill( *v_ptag_pfjets02_trailingSoftDroppedSubJet_pt, xfactor);
      hist_201->Fill( *v_ptag_pfjets02_trailingSoftDroppedSubJet_m, xfactor);
      hist_203->Fill( *v_ptag_pfjets02_trailingSoftDroppedSubJet_e, xfactor);
      hist_205->Fill( *v_ptag_pfjets04_softDroppedJet_pt, xfactor);
      hist_207->Fill( *v_ptag_pfjets04_softDroppedJet_m, xfactor);
      hist_209->Fill( *v_ptag_pfjets04_softDroppedJet_e, xfactor);
      hist_211->Fill( *v_ptag_pfjets04_leadingSoftDroppedSubJet_pt, xfactor);
      hist_213->Fill( *v_ptag_pfjets04_leadingSoftDroppedSubJet_m, xfactor);
      hist_215->Fill( *v_ptag_pfjets04_leadingSoftDroppedSubJet_e, xfactor);
      hist_217->Fill( *v_ptag_pfjets04_trailingSoftDroppedSubJet_pt, xfactor);
      hist_219->Fill( *v_ptag_pfjets04_trailingSoftDroppedSubJet_m, xfactor);
      hist_221->Fill( *v_ptag_pfjets04_trailingSoftDroppedSubJet_e, xfactor);
      hist_223->Fill( *v_ptag_pfjets08_softDroppedJet_pt, xfactor);
      hist_225->Fill( *v_ptag_pfjets08_softDroppedJet_m, xfactor);
      hist_227->Fill( *v_ptag_pfjets08_softDroppedJet_e, xfactor);
      hist_229->Fill( *v_ptag_pfjets08_leadingSoftDroppedSubJet_pt, xfactor);
      hist_231->Fill( *v_ptag_pfjets08_leadingSoftDroppedSubJet_m, xfactor);
      hist_233->Fill( *v_ptag_pfjets08_leadingSoftDroppedSubJet_e, xfactor);
      hist_235->Fill( *v_ptag_pfjets08_trailingSoftDroppedSubJet_pt, xfactor);
      hist_237->Fill( *v_ptag_pfjets08_trailingSoftDroppedSubJet_m, xfactor);
      hist_239->Fill( *v_ptag_pfjets08_trailingSoftDroppedSubJet_e, xfactor);
      hist_241->Fill( *v_btag_pfjets02_softDroppedJet_pt, xfactor);
      hist_243->Fill( *v_btag_pfjets02_softDroppedJet_m, xfactor);
      hist_245->Fill( *v_btag_pfjets02_softDroppedJet_e, xfactor);
      hist_247->Fill( *v_btag_pfjets02_leadingSoftDroppedSubJet_pt, xfactor);
      hist_249->Fill( *v_btag_pfjets02_leadingSoftDroppedSubJet_m, xfactor);
      hist_251->Fill( *v_btag_pfjets02_leadingSoftDroppedSubJet_e, xfactor);
      hist_253->Fill( *v_btag_pfjets02_trailingSoftDroppedSubJet_pt, xfactor);
      hist_255->Fill( *v_btag_pfjets02_trailingSoftDroppedSubJet_m, xfactor);
      hist_257->Fill( *v_btag_pfjets02_trailingSoftDroppedSubJet_e, xfactor);
      hist_259->Fill( *v_btag_pfjets04_softDroppedJet_pt, xfactor);
      hist_261->Fill( *v_btag_pfjets04_softDroppedJet_m, xfactor);
      hist_263->Fill( *v_btag_pfjets04_softDroppedJet_e, xfactor);
      hist_265->Fill( *v_btag_pfjets04_leadingSoftDroppedSubJet_pt, xfactor);
      hist_267->Fill( *v_btag_pfjets04_leadingSoftDroppedSubJet_m, xfactor);
      hist_269->Fill( *v_btag_pfjets04_leadingSoftDroppedSubJet_e, xfactor);
      hist_271->Fill( *v_btag_pfjets04_trailingSoftDroppedSubJet_pt, xfactor);
      hist_273->Fill( *v_btag_pfjets04_trailingSoftDroppedSubJet_m, xfactor);
      hist_275->Fill( *v_btag_pfjets04_trailingSoftDroppedSubJet_e, xfactor);
      hist_277->Fill( *v_btag_pfjets08_softDroppedJet_pt, xfactor);
      hist_279->Fill( *v_btag_pfjets08_softDroppedJet_m, xfactor);
      hist_281->Fill( *v_btag_pfjets08_softDroppedJet_e, xfactor);
      hist_283->Fill( *v_btag_pfjets08_leadingSoftDroppedSubJet_pt, xfactor);
      hist_285->Fill( *v_btag_pfjets08_leadingSoftDroppedSubJet_m, xfactor);
      hist_287->Fill( *v_btag_pfjets08_leadingSoftDroppedSubJet_e, xfactor);
      hist_289->Fill( *v_btag_pfjets08_trailingSoftDroppedSubJet_pt, xfactor);
      hist_291->Fill( *v_btag_pfjets08_trailingSoftDroppedSubJet_m, xfactor);
      hist_293->Fill( *v_btag_pfjets08_trailingSoftDroppedSubJet_e, xfactor);
      hist_295->Fill( *v_dPhi_Photon_ptag_pfjets04, xfactor);
      hist_297->Fill( *v_dR_Photon_ptag_pfjets04, xfactor);
      hist_299->Fill( *v_M_Photon_ptag_pfjets04, xfactor);
      hist_301->Fill( *v_dPhi_bjet_ptag_pfjets04, xfactor);
      hist_303->Fill( *v_dR_bjet_ptag_pfjets04, xfactor);
      if(*v_ptag_pfjets08_m < 140){hist_305->Fill( *v_ptag_pfjets08_m, xfactor);
      }
      if(*v_ptag_pfjets08_softDroppedJet_m > 250){hist_307->Fill( *v_ptag_pfjets08_leadingSoftDroppedSubJet_m, xfactor);
      }
      if(*v_ptag_pfjets08_softDroppedJet_m > 250){hist_309->Fill( *v_ptag_pfjets04_softDroppedJet_m, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_311->Fill( *v_ptag_bestJet_tau1, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_313->Fill( *v_ptag_bestJet_tau2, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_315->Fill( *v_ptag_bestJet_tau3, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_317->Fill( *v_ptag_bestJet_tau31, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_319->Fill( *v_ptag_bestJet_tau32, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_321->Fill( *v_ptag_bestJet_tau21, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_323->Fill( *v_ptag_pfjets08_tau1, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_325->Fill( *v_ptag_pfjets08_tau2, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_327->Fill( *v_ptag_pfjets08_tau3, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_329->Fill( *v_ptag_pfjets08_tau31, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_331->Fill( *v_ptag_pfjets08_tau32, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_333->Fill( *v_ptag_pfjets08_tau21, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_335->Fill( *v_photon_x_ptag_bestJet, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_337->Fill( *v_dPhi_Photon_ptag_bestJet, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_339->Fill( *v_dR_Photon_ptag_bestJet, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_341->Fill( *v_M_Photon_ptag_bestJet, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_343->Fill( *v_bjet_x_ptag_bestJet, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_345->Fill( *v_dPhi_bjet_ptag_bestJet, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_347->Fill( *v_dR_bjet_ptag_bestJet, xfactor);
      }
      if((*v_ptag_bestJet_m > 150) and (*v_ptag_bestJet_m < 200)){hist_349->Fill( *v_dR_bjet_ptag_bestJet, xfactor);
      }
      hist_351->Fill( *v_ptag_pfjets08_softDroppedJet_m, *v_ptag_pfjets08_leadingSoftDroppedSubJet_m, xfactor);
      hist_353->Fill( *v_ptag_pfjets08_softDroppedJet_m, *v_ptag_pfjets08_softDroppedJet_pt, xfactor);
      hist_355->Fill( *v_ptag_pfjets08_softDroppedJet_m, *v_ptag_pfjets04_softDroppedJet_m, xfactor);
      hist_357->Fill( *v_ptag_pfjets08_m, *v_ptag_pfjets08_softDroppedJet_m, xfactor);
      hist_359->Fill( *v_BestTopMass_jet_m, *v_SecondTopMass_jet_m, xfactor);
      hist_361->Fill( *v_ptag_bestJet_eta, *v_btag_pfjets04_eta, xfactor);
      //[[[end]]]

      //if(i > 1000) break;
    }

    file->Close();
  }

  return answer;
}

void tmva_hist(string input_folder, string output_path){
  /*
    1. set list of files
    2. set list of variables for 
    3. process all files and fill histograms at once 
  */
  
  
  // 1. set list of files
  // auto channels  = get_channals( "/afs/cern.ch/work/p/pmandrik/fcc_100TeV/4_analyser/heppy/OUTPUT/fcnc_apr_03" );
  auto channels  = get_channals( "" );
  auto processes = get_processes( channels, {} );

  // 2. set list of variables for 
  /*[[[cog
    for plot in default_plots + tmva_plots + comp_plots + cut_plots:
      plot.drawer = "drawer_" + mRootCOG.get_cog_key()
      mRootCOG.cpp_class("HistDrawer<> *", plot.drawer, [])

    for plot in corr_plots:
      plot.drawer = "drawer_" + mRootCOG.get_cog_key()
      mRootCOG.cpp_class("HistDrawer<TH2D> *", plot.drawer, [])

  ]]]*/
  HistDrawer<> * drawer_362 = new HistDrawer<> ();
  HistDrawer<> * drawer_363 = new HistDrawer<> ();
  HistDrawer<> * drawer_364 = new HistDrawer<> ();
  HistDrawer<> * drawer_365 = new HistDrawer<> ();
  HistDrawer<> * drawer_366 = new HistDrawer<> ();
  HistDrawer<> * drawer_367 = new HistDrawer<> ();
  HistDrawer<> * drawer_368 = new HistDrawer<> ();
  HistDrawer<> * drawer_369 = new HistDrawer<> ();
  HistDrawer<> * drawer_370 = new HistDrawer<> ();
  HistDrawer<> * drawer_371 = new HistDrawer<> ();
  HistDrawer<> * drawer_372 = new HistDrawer<> ();
  HistDrawer<> * drawer_373 = new HistDrawer<> ();
  HistDrawer<> * drawer_374 = new HistDrawer<> ();
  HistDrawer<> * drawer_375 = new HistDrawer<> ();
  HistDrawer<> * drawer_376 = new HistDrawer<> ();
  HistDrawer<> * drawer_377 = new HistDrawer<> ();
  HistDrawer<> * drawer_378 = new HistDrawer<> ();
  HistDrawer<> * drawer_379 = new HistDrawer<> ();
  HistDrawer<> * drawer_380 = new HistDrawer<> ();
  HistDrawer<> * drawer_381 = new HistDrawer<> ();
  HistDrawer<> * drawer_382 = new HistDrawer<> ();
  HistDrawer<> * drawer_383 = new HistDrawer<> ();
  HistDrawer<> * drawer_384 = new HistDrawer<> ();
  HistDrawer<> * drawer_385 = new HistDrawer<> ();
  HistDrawer<> * drawer_386 = new HistDrawer<> ();
  HistDrawer<> * drawer_387 = new HistDrawer<> ();
  HistDrawer<> * drawer_388 = new HistDrawer<> ();
  HistDrawer<> * drawer_389 = new HistDrawer<> ();
  HistDrawer<> * drawer_390 = new HistDrawer<> ();
  HistDrawer<> * drawer_391 = new HistDrawer<> ();
  HistDrawer<> * drawer_392 = new HistDrawer<> ();
  HistDrawer<> * drawer_393 = new HistDrawer<> ();
  HistDrawer<> * drawer_394 = new HistDrawer<> ();
  HistDrawer<> * drawer_395 = new HistDrawer<> ();
  HistDrawer<> * drawer_396 = new HistDrawer<> ();
  HistDrawer<> * drawer_397 = new HistDrawer<> ();
  HistDrawer<> * drawer_398 = new HistDrawer<> ();
  HistDrawer<> * drawer_399 = new HistDrawer<> ();
  HistDrawer<> * drawer_400 = new HistDrawer<> ();
  HistDrawer<> * drawer_401 = new HistDrawer<> ();
  HistDrawer<> * drawer_402 = new HistDrawer<> ();
  HistDrawer<> * drawer_403 = new HistDrawer<> ();
  HistDrawer<> * drawer_404 = new HistDrawer<> ();
  HistDrawer<> * drawer_405 = new HistDrawer<> ();
  HistDrawer<> * drawer_406 = new HistDrawer<> ();
  HistDrawer<> * drawer_407 = new HistDrawer<> ();
  HistDrawer<> * drawer_408 = new HistDrawer<> ();
  HistDrawer<> * drawer_409 = new HistDrawer<> ();
  HistDrawer<> * drawer_410 = new HistDrawer<> ();
  HistDrawer<> * drawer_411 = new HistDrawer<> ();
  HistDrawer<> * drawer_412 = new HistDrawer<> ();
  HistDrawer<> * drawer_413 = new HistDrawer<> ();
  HistDrawer<> * drawer_414 = new HistDrawer<> ();
  HistDrawer<> * drawer_415 = new HistDrawer<> ();
  HistDrawer<> * drawer_416 = new HistDrawer<> ();
  HistDrawer<> * drawer_417 = new HistDrawer<> ();
  HistDrawer<> * drawer_418 = new HistDrawer<> ();
  HistDrawer<> * drawer_419 = new HistDrawer<> ();
  HistDrawer<> * drawer_420 = new HistDrawer<> ();
  HistDrawer<> * drawer_421 = new HistDrawer<> ();
  HistDrawer<> * drawer_422 = new HistDrawer<> ();
  HistDrawer<> * drawer_423 = new HistDrawer<> ();
  HistDrawer<> * drawer_424 = new HistDrawer<> ();
  HistDrawer<> * drawer_425 = new HistDrawer<> ();
  HistDrawer<> * drawer_426 = new HistDrawer<> ();
  HistDrawer<> * drawer_427 = new HistDrawer<> ();
  HistDrawer<> * drawer_428 = new HistDrawer<> ();
  HistDrawer<> * drawer_429 = new HistDrawer<> ();
  HistDrawer<> * drawer_430 = new HistDrawer<> ();
  HistDrawer<> * drawer_431 = new HistDrawer<> ();
  HistDrawer<> * drawer_432 = new HistDrawer<> ();
  HistDrawer<> * drawer_433 = new HistDrawer<> ();
  HistDrawer<> * drawer_434 = new HistDrawer<> ();
  HistDrawer<> * drawer_435 = new HistDrawer<> ();
  HistDrawer<> * drawer_436 = new HistDrawer<> ();
  HistDrawer<> * drawer_437 = new HistDrawer<> ();
  HistDrawer<> * drawer_438 = new HistDrawer<> ();
  HistDrawer<> * drawer_439 = new HistDrawer<> ();
  HistDrawer<> * drawer_440 = new HistDrawer<> ();
  HistDrawer<> * drawer_441 = new HistDrawer<> ();
  HistDrawer<> * drawer_442 = new HistDrawer<> ();
  HistDrawer<> * drawer_443 = new HistDrawer<> ();
  HistDrawer<> * drawer_444 = new HistDrawer<> ();
  HistDrawer<> * drawer_445 = new HistDrawer<> ();
  HistDrawer<> * drawer_446 = new HistDrawer<> ();
  HistDrawer<> * drawer_447 = new HistDrawer<> ();
  HistDrawer<> * drawer_448 = new HistDrawer<> ();
  HistDrawer<> * drawer_449 = new HistDrawer<> ();
  HistDrawer<> * drawer_450 = new HistDrawer<> ();
  HistDrawer<> * drawer_451 = new HistDrawer<> ();
  HistDrawer<> * drawer_452 = new HistDrawer<> ();
  HistDrawer<> * drawer_453 = new HistDrawer<> ();
  HistDrawer<> * drawer_454 = new HistDrawer<> ();
  HistDrawer<> * drawer_455 = new HistDrawer<> ();
  HistDrawer<> * drawer_456 = new HistDrawer<> ();
  HistDrawer<> * drawer_457 = new HistDrawer<> ();
  HistDrawer<> * drawer_458 = new HistDrawer<> ();
  HistDrawer<> * drawer_459 = new HistDrawer<> ();
  HistDrawer<> * drawer_460 = new HistDrawer<> ();
  HistDrawer<> * drawer_461 = new HistDrawer<> ();
  HistDrawer<> * drawer_462 = new HistDrawer<> ();
  HistDrawer<> * drawer_463 = new HistDrawer<> ();
  HistDrawer<> * drawer_464 = new HistDrawer<> ();
  HistDrawer<> * drawer_465 = new HistDrawer<> ();
  HistDrawer<> * drawer_466 = new HistDrawer<> ();
  HistDrawer<> * drawer_467 = new HistDrawer<> ();
  HistDrawer<> * drawer_468 = new HistDrawer<> ();
  HistDrawer<> * drawer_469 = new HistDrawer<> ();
  HistDrawer<> * drawer_470 = new HistDrawer<> ();
  HistDrawer<> * drawer_471 = new HistDrawer<> ();
  HistDrawer<> * drawer_472 = new HistDrawer<> ();
  HistDrawer<> * drawer_473 = new HistDrawer<> ();
  HistDrawer<> * drawer_474 = new HistDrawer<> ();
  HistDrawer<> * drawer_475 = new HistDrawer<> ();
  HistDrawer<> * drawer_476 = new HistDrawer<> ();
  HistDrawer<> * drawer_477 = new HistDrawer<> ();
  HistDrawer<> * drawer_478 = new HistDrawer<> ();
  HistDrawer<> * drawer_479 = new HistDrawer<> ();
  HistDrawer<> * drawer_480 = new HistDrawer<> ();
  HistDrawer<> * drawer_481 = new HistDrawer<> ();
  HistDrawer<> * drawer_482 = new HistDrawer<> ();
  HistDrawer<> * drawer_483 = new HistDrawer<> ();
  HistDrawer<> * drawer_484 = new HistDrawer<> ();
  HistDrawer<> * drawer_485 = new HistDrawer<> ();
  HistDrawer<> * drawer_486 = new HistDrawer<> ();
  HistDrawer<> * drawer_487 = new HistDrawer<> ();
  HistDrawer<> * drawer_488 = new HistDrawer<> ();
  HistDrawer<> * drawer_489 = new HistDrawer<> ();
  HistDrawer<> * drawer_490 = new HistDrawer<> ();
  HistDrawer<> * drawer_491 = new HistDrawer<> ();
  HistDrawer<> * drawer_492 = new HistDrawer<> ();
  HistDrawer<> * drawer_493 = new HistDrawer<> ();
  HistDrawer<> * drawer_494 = new HistDrawer<> ();
  HistDrawer<> * drawer_495 = new HistDrawer<> ();
  HistDrawer<> * drawer_496 = new HistDrawer<> ();
  HistDrawer<> * drawer_497 = new HistDrawer<> ();
  HistDrawer<> * drawer_498 = new HistDrawer<> ();
  HistDrawer<> * drawer_499 = new HistDrawer<> ();
  HistDrawer<> * drawer_500 = new HistDrawer<> ();
  HistDrawer<> * drawer_501 = new HistDrawer<> ();
  HistDrawer<> * drawer_502 = new HistDrawer<> ();
  HistDrawer<> * drawer_503 = new HistDrawer<> ();
  HistDrawer<> * drawer_504 = new HistDrawer<> ();
  HistDrawer<> * drawer_505 = new HistDrawer<> ();
  HistDrawer<> * drawer_506 = new HistDrawer<> ();
  HistDrawer<> * drawer_507 = new HistDrawer<> ();
  HistDrawer<> * drawer_508 = new HistDrawer<> ();
  HistDrawer<> * drawer_509 = new HistDrawer<> ();
  HistDrawer<> * drawer_510 = new HistDrawer<> ();
  HistDrawer<> * drawer_511 = new HistDrawer<> ();
  HistDrawer<> * drawer_512 = new HistDrawer<> ();
  HistDrawer<> * drawer_513 = new HistDrawer<> ();
  HistDrawer<> * drawer_514 = new HistDrawer<> ();
  HistDrawer<> * drawer_515 = new HistDrawer<> ();
  HistDrawer<> * drawer_516 = new HistDrawer<> ();
  HistDrawer<> * drawer_517 = new HistDrawer<> ();
  HistDrawer<> * drawer_518 = new HistDrawer<> ();
  HistDrawer<> * drawer_519 = new HistDrawer<> ();
  HistDrawer<> * drawer_520 = new HistDrawer<> ();
  HistDrawer<> * drawer_521 = new HistDrawer<> ();
  HistDrawer<> * drawer_522 = new HistDrawer<> ();
  HistDrawer<> * drawer_523 = new HistDrawer<> ();
  HistDrawer<> * drawer_524 = new HistDrawer<> ();
  HistDrawer<> * drawer_525 = new HistDrawer<> ();
  HistDrawer<> * drawer_526 = new HistDrawer<> ();
  HistDrawer<> * drawer_527 = new HistDrawer<> ();
  HistDrawer<> * drawer_528 = new HistDrawer<> ();
  HistDrawer<> * drawer_529 = new HistDrawer<> ();
  HistDrawer<> * drawer_530 = new HistDrawer<> ();
  HistDrawer<> * drawer_531 = new HistDrawer<> ();
  HistDrawer<> * drawer_532 = new HistDrawer<> ();
  HistDrawer<> * drawer_533 = new HistDrawer<> ();
  HistDrawer<> * drawer_534 = new HistDrawer<> ();
  HistDrawer<> * drawer_535 = new HistDrawer<> ();
  HistDrawer<> * drawer_536 = new HistDrawer<> ();
  HistDrawer<> * drawer_537 = new HistDrawer<> ();
  HistDrawer<> * drawer_538 = new HistDrawer<> ();
  HistDrawer<> * drawer_539 = new HistDrawer<> ();
  HistDrawer<> * drawer_540 = new HistDrawer<> ();
  HistDrawer<> * drawer_541 = new HistDrawer<> ();
  HistDrawer<> * drawer_542 = new HistDrawer<> ();
  HistDrawer<> * drawer_543 = new HistDrawer<> ();
  HistDrawer<> * drawer_544 = new HistDrawer<> ();
  HistDrawer<> * drawer_545 = new HistDrawer<> ();
  HistDrawer<> * drawer_546 = new HistDrawer<> ();
  HistDrawer<> * drawer_547 = new HistDrawer<> ();
  HistDrawer<> * drawer_548 = new HistDrawer<> ();
  HistDrawer<> * drawer_549 = new HistDrawer<> ();
  HistDrawer<> * drawer_550 = new HistDrawer<> ();
  HistDrawer<> * drawer_551 = new HistDrawer<> ();
  HistDrawer<> * drawer_552 = new HistDrawer<> ();
  HistDrawer<> * drawer_553 = new HistDrawer<> ();
  HistDrawer<> * drawer_554 = new HistDrawer<> ();
  HistDrawer<> * drawer_555 = new HistDrawer<> ();
  HistDrawer<> * drawer_556 = new HistDrawer<> ();
  HistDrawer<> * drawer_557 = new HistDrawer<> ();
  HistDrawer<> * drawer_558 = new HistDrawer<> ();
  HistDrawer<> * drawer_559 = new HistDrawer<> ();
  HistDrawer<> * drawer_560 = new HistDrawer<> ();
  HistDrawer<> * drawer_561 = new HistDrawer<> ();
  HistDrawer<> * drawer_562 = new HistDrawer<> ();
  HistDrawer<> * drawer_563 = new HistDrawer<> ();
  HistDrawer<> * drawer_564 = new HistDrawer<> ();
  HistDrawer<> * drawer_565 = new HistDrawer<> ();
  HistDrawer<> * drawer_566 = new HistDrawer<> ();
  HistDrawer<> * drawer_567 = new HistDrawer<> ();
  HistDrawer<> * drawer_568 = new HistDrawer<> ();
  HistDrawer<> * drawer_569 = new HistDrawer<> ();
  HistDrawer<> * drawer_570 = new HistDrawer<> ();
  HistDrawer<> * drawer_571 = new HistDrawer<> ();
  HistDrawer<> * drawer_572 = new HistDrawer<> ();
  HistDrawer<> * drawer_573 = new HistDrawer<> ();
  HistDrawer<> * drawer_574 = new HistDrawer<> ();
  HistDrawer<> * drawer_575 = new HistDrawer<> ();
  HistDrawer<> * drawer_576 = new HistDrawer<> ();
  HistDrawer<> * drawer_577 = new HistDrawer<> ();
  HistDrawer<> * drawer_578 = new HistDrawer<> ();
  HistDrawer<> * drawer_579 = new HistDrawer<> ();
  HistDrawer<> * drawer_580 = new HistDrawer<> ();
  HistDrawer<> * drawer_581 = new HistDrawer<> ();
  HistDrawer<> * drawer_582 = new HistDrawer<> ();
  HistDrawer<> * drawer_583 = new HistDrawer<> ();
  HistDrawer<> * drawer_584 = new HistDrawer<> ();
  HistDrawer<> * drawer_585 = new HistDrawer<> ();
  HistDrawer<> * drawer_586 = new HistDrawer<> ();
  HistDrawer<> * drawer_587 = new HistDrawer<> ();
  HistDrawer<> * drawer_588 = new HistDrawer<> ();
  HistDrawer<> * drawer_589 = new HistDrawer<> ();
  HistDrawer<> * drawer_590 = new HistDrawer<> ();
  HistDrawer<> * drawer_591 = new HistDrawer<> ();
  HistDrawer<> * drawer_592 = new HistDrawer<> ();
  HistDrawer<> * drawer_593 = new HistDrawer<> ();
  HistDrawer<> * drawer_594 = new HistDrawer<> ();
  HistDrawer<> * drawer_595 = new HistDrawer<> ();
  HistDrawer<> * drawer_596 = new HistDrawer<> ();
  HistDrawer<> * drawer_597 = new HistDrawer<> ();
  HistDrawer<> * drawer_598 = new HistDrawer<> ();
  HistDrawer<> * drawer_599 = new HistDrawer<> ();
  HistDrawer<> * drawer_600 = new HistDrawer<> ();
  HistDrawer<> * drawer_601 = new HistDrawer<> ();
  HistDrawer<> * drawer_602 = new HistDrawer<> ();
  HistDrawer<> * drawer_603 = new HistDrawer<> ();
  HistDrawer<> * drawer_604 = new HistDrawer<> ();
  HistDrawer<> * drawer_605 = new HistDrawer<> ();
  HistDrawer<> * drawer_606 = new HistDrawer<> ();
  HistDrawer<> * drawer_607 = new HistDrawer<> ();
  HistDrawer<> * drawer_608 = new HistDrawer<> ();
  HistDrawer<> * drawer_609 = new HistDrawer<> ();
  HistDrawer<> * drawer_610 = new HistDrawer<> ();
  HistDrawer<> * drawer_611 = new HistDrawer<> ();
  HistDrawer<> * drawer_612 = new HistDrawer<> ();
  HistDrawer<> * drawer_613 = new HistDrawer<> ();
  HistDrawer<> * drawer_614 = new HistDrawer<> ();
  HistDrawer<> * drawer_615 = new HistDrawer<> ();
  HistDrawer<> * drawer_616 = new HistDrawer<> ();
  HistDrawer<> * drawer_617 = new HistDrawer<> ();
  HistDrawer<> * drawer_618 = new HistDrawer<> ();
  HistDrawer<> * drawer_619 = new HistDrawer<> ();
  HistDrawer<> * drawer_620 = new HistDrawer<> ();
  HistDrawer<> * drawer_621 = new HistDrawer<> ();
  HistDrawer<> * drawer_622 = new HistDrawer<> ();
  HistDrawer<> * drawer_623 = new HistDrawer<> ();
  HistDrawer<> * drawer_624 = new HistDrawer<> ();
  HistDrawer<> * drawer_625 = new HistDrawer<> ();
  HistDrawer<> * drawer_626 = new HistDrawer<> ();
  HistDrawer<> * drawer_627 = new HistDrawer<> ();
  HistDrawer<> * drawer_628 = new HistDrawer<> ();
  HistDrawer<> * drawer_629 = new HistDrawer<> ();
  HistDrawer<> * drawer_630 = new HistDrawer<> ();
  HistDrawer<> * drawer_631 = new HistDrawer<> ();
  HistDrawer<> * drawer_632 = new HistDrawer<> ();
  HistDrawer<> * drawer_633 = new HistDrawer<> ();
  HistDrawer<> * drawer_634 = new HistDrawer<> ();
  HistDrawer<> * drawer_635 = new HistDrawer<> ();
  HistDrawer<> * drawer_636 = new HistDrawer<> ();
  HistDrawer<> * drawer_637 = new HistDrawer<> ();
  HistDrawer<> * drawer_638 = new HistDrawer<> ();
  HistDrawer<> * drawer_639 = new HistDrawer<> ();
  HistDrawer<> * drawer_640 = new HistDrawer<> ();
  HistDrawer<> * drawer_641 = new HistDrawer<> ();
  HistDrawer<> * drawer_642 = new HistDrawer<> ();
  HistDrawer<> * drawer_643 = new HistDrawer<> ();
  HistDrawer<> * drawer_644 = new HistDrawer<> ();
  HistDrawer<> * drawer_645 = new HistDrawer<> ();
  HistDrawer<> * drawer_646 = new HistDrawer<> ();
  HistDrawer<> * drawer_647 = new HistDrawer<> ();
  HistDrawer<> * drawer_648 = new HistDrawer<> ();
  HistDrawer<> * drawer_649 = new HistDrawer<> ();
  HistDrawer<> * drawer_650 = new HistDrawer<> ();
  HistDrawer<> * drawer_651 = new HistDrawer<> ();
  HistDrawer<> * drawer_652 = new HistDrawer<> ();
  HistDrawer<> * drawer_653 = new HistDrawer<> ();
  HistDrawer<> * drawer_654 = new HistDrawer<> ();
  HistDrawer<> * drawer_655 = new HistDrawer<> ();
  HistDrawer<> * drawer_656 = new HistDrawer<> ();
  HistDrawer<> * drawer_657 = new HistDrawer<> ();
  HistDrawer<> * drawer_658 = new HistDrawer<> ();
  HistDrawer<> * drawer_659 = new HistDrawer<> ();
  HistDrawer<> * drawer_660 = new HistDrawer<> ();
  HistDrawer<> * drawer_661 = new HistDrawer<> ();
  HistDrawer<> * drawer_662 = new HistDrawer<> ();
  HistDrawer<> * drawer_663 = new HistDrawer<> ();
  HistDrawer<> * drawer_664 = new HistDrawer<> ();
  HistDrawer<> * drawer_665 = new HistDrawer<> ();
  HistDrawer<> * drawer_666 = new HistDrawer<> ();
  HistDrawer<> * drawer_667 = new HistDrawer<> ();
  HistDrawer<> * drawer_668 = new HistDrawer<> ();
  HistDrawer<> * drawer_669 = new HistDrawer<> ();
  HistDrawer<> * drawer_670 = new HistDrawer<> ();
  HistDrawer<> * drawer_671 = new HistDrawer<> ();
  HistDrawer<> * drawer_672 = new HistDrawer<> ();
  HistDrawer<> * drawer_673 = new HistDrawer<> ();
  HistDrawer<> * drawer_674 = new HistDrawer<> ();
  HistDrawer<> * drawer_675 = new HistDrawer<> ();
  HistDrawer<> * drawer_676 = new HistDrawer<> ();
  HistDrawer<TH2D> * drawer_677 = new HistDrawer<TH2D> ();
  HistDrawer<TH2D> * drawer_678 = new HistDrawer<TH2D> ();
  HistDrawer<TH2D> * drawer_679 = new HistDrawer<TH2D> ();
  HistDrawer<TH2D> * drawer_680 = new HistDrawer<TH2D> ();
  HistDrawer<TH2D> * drawer_681 = new HistDrawer<TH2D> ();
  HistDrawer<TH2D> * drawer_682 = new HistDrawer<TH2D> ();
  //[[[end]]]

  TFile * output_hists = new TFile( (output_path + "/hists.root").c_str(), "RECREATE");
  for(auto process : processes){
    auto f_hists = process_file( process, input_folder );
    string title; 
    if(process.signal) title = "signal";
    else               title = "background";

    output_hists->cd();
    /*[[[cog
    # hists_to_save = ["weight_tune_2_BDT_0_r", "weight_tune_2_BDT_3_r", "weight_tune_2_BDT_7_r", "weight_tune_2_BDT_11_r"]
    hists_to_save = [ "weight_tune_3_BDT_" + str(i) + "_000" for i in xrange(0, 7) ]
    hists_to_save += [ "weight_tune_5_BDT_3_000" ]
    for hist_name in hists_to_save :
      string = "f_hists.get_th1d(\"" + hist_name + "\")->SetName( (process.short_name + \"_" + hist_name + "\").c_str() );"
      cog.outl( string )
      string = "tune_for_stat_hist( f_hists.get_th1d(\"" + hist_name + "\"), process.signal );"
      cog.outl( string )
      string = "f_hists.get_th1d(\"" + hist_name + "\")->Write();"
      cog.outl( string )

    for plot in default_plots + tmva_plots:
      string = plot.drawer + "->Add( f_hists.get_th1d(\"" + plot.var.key + "\"), process.signal);"
      cog.outl( string )

    for plot in corr_plots :
      string = plot.drawer + "->Add( f_hists.get_th2d(\"" + plot.hist_name + "\"), process.signal);"
      cog.outl( string )

    for plot in comp_plots:
      string = "if(\"" + plot.channel + "\" == process.physic_name){"
      cog.outl( string )
      for variable, titles in zip(plot.vars, plot.vars_names):
        hist_name = "hist_" + mRootCOG.get_cog_key()
        cog.outl( "TH1D * " + hist_name + " = (TH1D*) f_hists.get_th1d(\"" + variable + "\")->Clone();")
        cog.outl( hist_name + "->SetTitle(\"" + titles + "\");")
        string = plot.drawer + "->Add( " + hist_name + ", false);"
        cog.outl( string )
      cog.outl( "}" )

    for plot in cut_plots:
      hist_name_0 = "hist_0_" + mRootCOG.get_cog_key()
      hist_name_1 = "hist_1_" + mRootCOG.get_cog_key()
      cog.outl( "TH1D * " + hist_name_0 + " = (TH1D*) f_hists.get_th1d(\"" + plot.var.key + "\")->Clone();")
      cog.outl( "TH1D * " + hist_name_1 + " = (TH1D*) f_hists.get_th1d(\"" + plot.hist_cut_name + "\")->Clone();")

      string_0 = hist_name_0 + "->SetTitle( title.c_str() );"
      string_1 = hist_name_1 + "->SetTitle( (title + \" after cut\").c_str() );"
      cog.outl( string_0 )
      cog.outl( string_1 )

      string_0 = plot.drawer + "->AddCummulative(" + hist_name_0 + ", process.signal, 0);"
      string_1 = plot.drawer + "->AddCummulative(" + hist_name_1 + ", process.signal, 1);"
      cog.outl( string_0 )
      cog.outl( string_1 )

    ]]]*/
    f_hists.get_th1d("weight_tune_3_BDT_0_000")->SetName( (process.short_name + "_weight_tune_3_BDT_0_000").c_str() );
    tune_for_stat_hist( f_hists.get_th1d("weight_tune_3_BDT_0_000"), process.signal );
    f_hists.get_th1d("weight_tune_3_BDT_0_000")->Write();
    f_hists.get_th1d("weight_tune_3_BDT_1_000")->SetName( (process.short_name + "_weight_tune_3_BDT_1_000").c_str() );
    tune_for_stat_hist( f_hists.get_th1d("weight_tune_3_BDT_1_000"), process.signal );
    f_hists.get_th1d("weight_tune_3_BDT_1_000")->Write();
    f_hists.get_th1d("weight_tune_3_BDT_2_000")->SetName( (process.short_name + "_weight_tune_3_BDT_2_000").c_str() );
    tune_for_stat_hist( f_hists.get_th1d("weight_tune_3_BDT_2_000"), process.signal );
    f_hists.get_th1d("weight_tune_3_BDT_2_000")->Write();
    f_hists.get_th1d("weight_tune_3_BDT_3_000")->SetName( (process.short_name + "_weight_tune_3_BDT_3_000").c_str() );
    tune_for_stat_hist( f_hists.get_th1d("weight_tune_3_BDT_3_000"), process.signal );
    f_hists.get_th1d("weight_tune_3_BDT_3_000")->Write();
    f_hists.get_th1d("weight_tune_3_BDT_4_000")->SetName( (process.short_name + "_weight_tune_3_BDT_4_000").c_str() );
    tune_for_stat_hist( f_hists.get_th1d("weight_tune_3_BDT_4_000"), process.signal );
    f_hists.get_th1d("weight_tune_3_BDT_4_000")->Write();
    f_hists.get_th1d("weight_tune_3_BDT_5_000")->SetName( (process.short_name + "_weight_tune_3_BDT_5_000").c_str() );
    tune_for_stat_hist( f_hists.get_th1d("weight_tune_3_BDT_5_000"), process.signal );
    f_hists.get_th1d("weight_tune_3_BDT_5_000")->Write();
    f_hists.get_th1d("weight_tune_3_BDT_6_000")->SetName( (process.short_name + "_weight_tune_3_BDT_6_000").c_str() );
    tune_for_stat_hist( f_hists.get_th1d("weight_tune_3_BDT_6_000"), process.signal );
    f_hists.get_th1d("weight_tune_3_BDT_6_000")->Write();
    f_hists.get_th1d("weight_tune_5_BDT_3_000")->SetName( (process.short_name + "_weight_tune_5_BDT_3_000").c_str() );
    tune_for_stat_hist( f_hists.get_th1d("weight_tune_5_BDT_3_000"), process.signal );
    f_hists.get_th1d("weight_tune_5_BDT_3_000")->Write();
    drawer_362->Add( f_hists.get_th1d("photon_eta"), process.signal);
    drawer_363->Add( f_hists.get_th1d("photon_pt"), process.signal);
    drawer_364->Add( f_hists.get_th1d("top_pt"), process.signal);
    drawer_365->Add( f_hists.get_th1d("ptag_bestJet_m"), process.signal);
    drawer_366->Add( f_hists.get_th1d("ptag_bestJet_pt"), process.signal);
    drawer_367->Add( f_hists.get_th1d("ptag_bestJet_eta"), process.signal);
    drawer_368->Add( f_hists.get_th1d("btag_pfjets04_eta"), process.signal);
    drawer_369->Add( f_hists.get_th1d("ptag_bestJet_tau1"), process.signal);
    drawer_370->Add( f_hists.get_th1d("ptag_bestJet_tau2"), process.signal);
    drawer_371->Add( f_hists.get_th1d("ptag_bestJet_tau3"), process.signal);
    drawer_372->Add( f_hists.get_th1d("ptag_bestJet_tau31"), process.signal);
    drawer_373->Add( f_hists.get_th1d("ptag_bestJet_tau32"), process.signal);
    drawer_374->Add( f_hists.get_th1d("ptag_bestJet_tau21"), process.signal);
    drawer_375->Add( f_hists.get_th1d("ptag_pfjets08_tau1"), process.signal);
    drawer_376->Add( f_hists.get_th1d("ptag_pfjets08_tau2"), process.signal);
    drawer_377->Add( f_hists.get_th1d("ptag_pfjets08_tau3"), process.signal);
    drawer_378->Add( f_hists.get_th1d("ptag_pfjets08_tau31"), process.signal);
    drawer_379->Add( f_hists.get_th1d("ptag_pfjets08_tau32"), process.signal);
    drawer_380->Add( f_hists.get_th1d("ptag_pfjets08_tau21"), process.signal);
    drawer_381->Add( f_hists.get_th1d("photon_x_ptag_bestJet"), process.signal);
    drawer_382->Add( f_hists.get_th1d("lepton_x_btag_pfjets08"), process.signal);
    drawer_383->Add( f_hists.get_th1d("dPhi_lepton_btag_pfjets08"), process.signal);
    drawer_384->Add( f_hists.get_th1d("dR_lepton_btag_pfjets08"), process.signal);
    drawer_385->Add( f_hists.get_th1d("lepton_x_btag_pfjets04"), process.signal);
    drawer_386->Add( f_hists.get_th1d("dPhi_lepton_btag_pfjets04"), process.signal);
    drawer_387->Add( f_hists.get_th1d("dR_lepton_btag_pfjets04"), process.signal);
    drawer_388->Add( f_hists.get_th1d("M_lepton_met"), process.signal);
    drawer_389->Add( f_hists.get_th1d("M_bjet_lepton_met"), process.signal);
    drawer_390->Add( f_hists.get_th1d("dPhi_Photon_ptag_bestJet"), process.signal);
    drawer_391->Add( f_hists.get_th1d("dR_Photon_ptag_bestJet"), process.signal);
    drawer_392->Add( f_hists.get_th1d("M_Photon_ptag_bestJet"), process.signal);
    drawer_393->Add( f_hists.get_th1d("bjet_x_ptag_bestJet"), process.signal);
    drawer_394->Add( f_hists.get_th1d("dPhi_bjet_ptag_bestJet"), process.signal);
    drawer_395->Add( f_hists.get_th1d("dR_bjet_ptag_bestJet"), process.signal);
    drawer_396->Add( f_hists.get_th1d("lepton_relIso"), process.signal);
    drawer_397->Add( f_hists.get_th1d("photon_relIso"), process.signal);
    drawer_398->Add( f_hists.get_th1d("photon_x_ptag_pfjets08"), process.signal);
    drawer_399->Add( f_hists.get_th1d("bjet_x_ptag_pfjets08"), process.signal);
    drawer_400->Add( f_hists.get_th1d("weight_tune_3_BDT_0_000"), process.signal);
    drawer_401->Add( f_hists.get_th1d("weight_tune_3_BDT_1_000"), process.signal);
    drawer_402->Add( f_hists.get_th1d("weight_tune_3_BDT_2_000"), process.signal);
    drawer_403->Add( f_hists.get_th1d("weight_tune_3_BDT_3_000"), process.signal);
    drawer_404->Add( f_hists.get_th1d("weight_tune_3_BDT_4_000"), process.signal);
    drawer_405->Add( f_hists.get_th1d("weight_tune_3_BDT_5_000"), process.signal);
    drawer_406->Add( f_hists.get_th1d("weight_tune_3_BDT_6_000"), process.signal);
    drawer_407->Add( f_hists.get_th1d("weight_tune_5_BDT_3_000"), process.signal);
    drawer_408->Add( f_hists.get_th1d("ptag_pfjets02_e"), process.signal);
    drawer_409->Add( f_hists.get_th1d("ptag_pfjets02_pt"), process.signal);
    drawer_410->Add( f_hists.get_th1d("ptag_pfjets02_m"), process.signal);
    drawer_411->Add( f_hists.get_th1d("ptag_pfjets04_e"), process.signal);
    drawer_412->Add( f_hists.get_th1d("ptag_pfjets04_pt"), process.signal);
    drawer_413->Add( f_hists.get_th1d("ptag_pfjets04_m"), process.signal);
    drawer_414->Add( f_hists.get_th1d("ptag_pfjets08_e"), process.signal);
    drawer_415->Add( f_hists.get_th1d("ptag_pfjets08_pt"), process.signal);
    drawer_416->Add( f_hists.get_th1d("ptag_pfjets08_m"), process.signal);
    drawer_417->Add( f_hists.get_th1d("btag_pfjets02_e"), process.signal);
    drawer_418->Add( f_hists.get_th1d("btag_pfjets02_pt"), process.signal);
    drawer_419->Add( f_hists.get_th1d("btag_pfjets02_m"), process.signal);
    drawer_420->Add( f_hists.get_th1d("btag_pfjets04_e"), process.signal);
    drawer_421->Add( f_hists.get_th1d("btag_pfjets04_pt"), process.signal);
    drawer_422->Add( f_hists.get_th1d("btag_pfjets04_m"), process.signal);
    drawer_423->Add( f_hists.get_th1d("btag_pfjets08_e"), process.signal);
    drawer_424->Add( f_hists.get_th1d("btag_pfjets08_pt"), process.signal);
    drawer_425->Add( f_hists.get_th1d("btag_pfjets08_m"), process.signal);
    drawer_426->Add( f_hists.get_th1d("BestMass_jet_e"), process.signal);
    drawer_427->Add( f_hists.get_th1d("BestMass_jet_pt"), process.signal);
    drawer_428->Add( f_hists.get_th1d("BestMass_jet_m"), process.signal);
    drawer_429->Add( f_hists.get_th1d("BestTopMass_jet_e"), process.signal);
    drawer_430->Add( f_hists.get_th1d("BestTopMass_jet_pt"), process.signal);
    drawer_431->Add( f_hists.get_th1d("BestTopMass_jet_m"), process.signal);
    drawer_432->Add( f_hists.get_th1d("SecondTopMass_jet_e"), process.signal);
    drawer_433->Add( f_hists.get_th1d("SecondTopMass_jet_pt"), process.signal);
    drawer_434->Add( f_hists.get_th1d("SecondTopMass_jet_m"), process.signal);
    drawer_435->Add( f_hists.get_th1d("ptag_pfjets02_softDroppedJet_pt"), process.signal);
    drawer_436->Add( f_hists.get_th1d("ptag_pfjets02_softDroppedJet_m"), process.signal);
    drawer_437->Add( f_hists.get_th1d("ptag_pfjets02_softDroppedJet_e"), process.signal);
    drawer_438->Add( f_hists.get_th1d("ptag_pfjets02_leadingSoftDroppedSubJet_pt"), process.signal);
    drawer_439->Add( f_hists.get_th1d("ptag_pfjets02_leadingSoftDroppedSubJet_m"), process.signal);
    drawer_440->Add( f_hists.get_th1d("ptag_pfjets02_leadingSoftDroppedSubJet_e"), process.signal);
    drawer_441->Add( f_hists.get_th1d("ptag_pfjets02_trailingSoftDroppedSubJet_pt"), process.signal);
    drawer_442->Add( f_hists.get_th1d("ptag_pfjets02_trailingSoftDroppedSubJet_m"), process.signal);
    drawer_443->Add( f_hists.get_th1d("ptag_pfjets02_trailingSoftDroppedSubJet_e"), process.signal);
    drawer_444->Add( f_hists.get_th1d("ptag_pfjets04_softDroppedJet_pt"), process.signal);
    drawer_445->Add( f_hists.get_th1d("ptag_pfjets04_softDroppedJet_m"), process.signal);
    drawer_446->Add( f_hists.get_th1d("ptag_pfjets04_softDroppedJet_e"), process.signal);
    drawer_447->Add( f_hists.get_th1d("ptag_pfjets04_leadingSoftDroppedSubJet_pt"), process.signal);
    drawer_448->Add( f_hists.get_th1d("ptag_pfjets04_leadingSoftDroppedSubJet_m"), process.signal);
    drawer_449->Add( f_hists.get_th1d("ptag_pfjets04_leadingSoftDroppedSubJet_e"), process.signal);
    drawer_450->Add( f_hists.get_th1d("ptag_pfjets04_trailingSoftDroppedSubJet_pt"), process.signal);
    drawer_451->Add( f_hists.get_th1d("ptag_pfjets04_trailingSoftDroppedSubJet_m"), process.signal);
    drawer_452->Add( f_hists.get_th1d("ptag_pfjets04_trailingSoftDroppedSubJet_e"), process.signal);
    drawer_453->Add( f_hists.get_th1d("ptag_pfjets08_softDroppedJet_pt"), process.signal);
    drawer_454->Add( f_hists.get_th1d("ptag_pfjets08_softDroppedJet_m"), process.signal);
    drawer_455->Add( f_hists.get_th1d("ptag_pfjets08_softDroppedJet_e"), process.signal);
    drawer_456->Add( f_hists.get_th1d("ptag_pfjets08_leadingSoftDroppedSubJet_pt"), process.signal);
    drawer_457->Add( f_hists.get_th1d("ptag_pfjets08_leadingSoftDroppedSubJet_m"), process.signal);
    drawer_458->Add( f_hists.get_th1d("ptag_pfjets08_leadingSoftDroppedSubJet_e"), process.signal);
    drawer_459->Add( f_hists.get_th1d("ptag_pfjets08_trailingSoftDroppedSubJet_pt"), process.signal);
    drawer_460->Add( f_hists.get_th1d("ptag_pfjets08_trailingSoftDroppedSubJet_m"), process.signal);
    drawer_461->Add( f_hists.get_th1d("ptag_pfjets08_trailingSoftDroppedSubJet_e"), process.signal);
    drawer_462->Add( f_hists.get_th1d("btag_pfjets02_softDroppedJet_pt"), process.signal);
    drawer_463->Add( f_hists.get_th1d("btag_pfjets02_softDroppedJet_m"), process.signal);
    drawer_464->Add( f_hists.get_th1d("btag_pfjets02_softDroppedJet_e"), process.signal);
    drawer_465->Add( f_hists.get_th1d("btag_pfjets02_leadingSoftDroppedSubJet_pt"), process.signal);
    drawer_466->Add( f_hists.get_th1d("btag_pfjets02_leadingSoftDroppedSubJet_m"), process.signal);
    drawer_467->Add( f_hists.get_th1d("btag_pfjets02_leadingSoftDroppedSubJet_e"), process.signal);
    drawer_468->Add( f_hists.get_th1d("btag_pfjets02_trailingSoftDroppedSubJet_pt"), process.signal);
    drawer_469->Add( f_hists.get_th1d("btag_pfjets02_trailingSoftDroppedSubJet_m"), process.signal);
    drawer_470->Add( f_hists.get_th1d("btag_pfjets02_trailingSoftDroppedSubJet_e"), process.signal);
    drawer_471->Add( f_hists.get_th1d("btag_pfjets04_softDroppedJet_pt"), process.signal);
    drawer_472->Add( f_hists.get_th1d("btag_pfjets04_softDroppedJet_m"), process.signal);
    drawer_473->Add( f_hists.get_th1d("btag_pfjets04_softDroppedJet_e"), process.signal);
    drawer_474->Add( f_hists.get_th1d("btag_pfjets04_leadingSoftDroppedSubJet_pt"), process.signal);
    drawer_475->Add( f_hists.get_th1d("btag_pfjets04_leadingSoftDroppedSubJet_m"), process.signal);
    drawer_476->Add( f_hists.get_th1d("btag_pfjets04_leadingSoftDroppedSubJet_e"), process.signal);
    drawer_477->Add( f_hists.get_th1d("btag_pfjets04_trailingSoftDroppedSubJet_pt"), process.signal);
    drawer_478->Add( f_hists.get_th1d("btag_pfjets04_trailingSoftDroppedSubJet_m"), process.signal);
    drawer_479->Add( f_hists.get_th1d("btag_pfjets04_trailingSoftDroppedSubJet_e"), process.signal);
    drawer_480->Add( f_hists.get_th1d("btag_pfjets08_softDroppedJet_pt"), process.signal);
    drawer_481->Add( f_hists.get_th1d("btag_pfjets08_softDroppedJet_m"), process.signal);
    drawer_482->Add( f_hists.get_th1d("btag_pfjets08_softDroppedJet_e"), process.signal);
    drawer_483->Add( f_hists.get_th1d("btag_pfjets08_leadingSoftDroppedSubJet_pt"), process.signal);
    drawer_484->Add( f_hists.get_th1d("btag_pfjets08_leadingSoftDroppedSubJet_m"), process.signal);
    drawer_485->Add( f_hists.get_th1d("btag_pfjets08_leadingSoftDroppedSubJet_e"), process.signal);
    drawer_486->Add( f_hists.get_th1d("btag_pfjets08_trailingSoftDroppedSubJet_pt"), process.signal);
    drawer_487->Add( f_hists.get_th1d("btag_pfjets08_trailingSoftDroppedSubJet_m"), process.signal);
    drawer_488->Add( f_hists.get_th1d("btag_pfjets08_trailingSoftDroppedSubJet_e"), process.signal);
    drawer_489->Add( f_hists.get_th1d("dPhi_Photon_ptag_pfjets04"), process.signal);
    drawer_490->Add( f_hists.get_th1d("dR_Photon_ptag_pfjets04"), process.signal);
    drawer_491->Add( f_hists.get_th1d("M_Photon_ptag_pfjets04"), process.signal);
    drawer_492->Add( f_hists.get_th1d("dPhi_bjet_ptag_pfjets04"), process.signal);
    drawer_493->Add( f_hists.get_th1d("dR_bjet_ptag_pfjets04"), process.signal);
    drawer_494->Add( f_hists.get_th1d("photon_eta"), process.signal);
    drawer_495->Add( f_hists.get_th1d("photon_pt"), process.signal);
    drawer_496->Add( f_hists.get_th1d("top_pt"), process.signal);
    drawer_497->Add( f_hists.get_th1d("ptag_bestJet_m"), process.signal);
    drawer_498->Add( f_hists.get_th1d("ptag_bestJet_pt"), process.signal);
    drawer_499->Add( f_hists.get_th1d("ptag_bestJet_eta"), process.signal);
    drawer_500->Add( f_hists.get_th1d("btag_pfjets04_eta"), process.signal);
    drawer_501->Add( f_hists.get_th1d("ptag_bestJet_tau1"), process.signal);
    drawer_502->Add( f_hists.get_th1d("ptag_bestJet_tau2"), process.signal);
    drawer_503->Add( f_hists.get_th1d("ptag_bestJet_tau3"), process.signal);
    drawer_504->Add( f_hists.get_th1d("ptag_bestJet_tau31"), process.signal);
    drawer_505->Add( f_hists.get_th1d("ptag_bestJet_tau32"), process.signal);
    drawer_506->Add( f_hists.get_th1d("ptag_bestJet_tau21"), process.signal);
    drawer_507->Add( f_hists.get_th1d("ptag_pfjets08_tau1"), process.signal);
    drawer_508->Add( f_hists.get_th1d("ptag_pfjets08_tau2"), process.signal);
    drawer_509->Add( f_hists.get_th1d("ptag_pfjets08_tau3"), process.signal);
    drawer_510->Add( f_hists.get_th1d("ptag_pfjets08_tau31"), process.signal);
    drawer_511->Add( f_hists.get_th1d("ptag_pfjets08_tau32"), process.signal);
    drawer_512->Add( f_hists.get_th1d("ptag_pfjets08_tau21"), process.signal);
    drawer_513->Add( f_hists.get_th1d("btag_pfjets08_tau1"), process.signal);
    drawer_514->Add( f_hists.get_th1d("btag_pfjets08_tau2"), process.signal);
    drawer_515->Add( f_hists.get_th1d("btag_pfjets08_tau3"), process.signal);
    drawer_516->Add( f_hists.get_th1d("btag_pfjets08_tau31"), process.signal);
    drawer_517->Add( f_hists.get_th1d("btag_pfjets08_tau32"), process.signal);
    drawer_518->Add( f_hists.get_th1d("btag_pfjets08_tau21"), process.signal);
    drawer_519->Add( f_hists.get_th1d("btag_pfjets04_tau1"), process.signal);
    drawer_520->Add( f_hists.get_th1d("btag_pfjets04_tau2"), process.signal);
    drawer_521->Add( f_hists.get_th1d("btag_pfjets04_tau3"), process.signal);
    drawer_522->Add( f_hists.get_th1d("btag_pfjets04_tau31"), process.signal);
    drawer_523->Add( f_hists.get_th1d("btag_pfjets04_tau32"), process.signal);
    drawer_524->Add( f_hists.get_th1d("btag_pfjets04_tau21"), process.signal);
    drawer_525->Add( f_hists.get_th1d("photon_x_ptag_bestJet"), process.signal);
    drawer_526->Add( f_hists.get_th1d("lepton_x_btag_pfjets08"), process.signal);
    drawer_527->Add( f_hists.get_th1d("dPhi_lepton_btag_pfjets08"), process.signal);
    drawer_528->Add( f_hists.get_th1d("dR_lepton_btag_pfjets08"), process.signal);
    drawer_529->Add( f_hists.get_th1d("lepton_x_btag_pfjets04"), process.signal);
    drawer_530->Add( f_hists.get_th1d("dPhi_lepton_btag_pfjets04"), process.signal);
    drawer_531->Add( f_hists.get_th1d("dR_lepton_btag_pfjets04"), process.signal);
    drawer_532->Add( f_hists.get_th1d("M_lepton_met"), process.signal);
    drawer_533->Add( f_hists.get_th1d("M_bjet_lepton_met"), process.signal);
    drawer_534->Add( f_hists.get_th1d("dPhi_Photon_ptag_bestJet"), process.signal);
    drawer_535->Add( f_hists.get_th1d("dR_Photon_ptag_bestJet"), process.signal);
    drawer_536->Add( f_hists.get_th1d("M_Photon_ptag_bestJet"), process.signal);
    drawer_537->Add( f_hists.get_th1d("bjet_x_ptag_bestJet"), process.signal);
    drawer_538->Add( f_hists.get_th1d("dPhi_bjet_ptag_bestJet"), process.signal);
    drawer_539->Add( f_hists.get_th1d("dR_bjet_ptag_bestJet"), process.signal);
    drawer_540->Add( f_hists.get_th1d("lepton_relIso"), process.signal);
    drawer_541->Add( f_hists.get_th1d("photon_relIso"), process.signal);
    drawer_542->Add( f_hists.get_th1d("photon_x_ptag_pfjets08"), process.signal);
    drawer_543->Add( f_hists.get_th1d("bjet_x_ptag_pfjets08"), process.signal);
    drawer_544->Add( f_hists.get_th1d("weight_tune_3_BDT_0_000"), process.signal);
    drawer_545->Add( f_hists.get_th1d("weight_tune_3_BDT_1_000"), process.signal);
    drawer_546->Add( f_hists.get_th1d("weight_tune_3_BDT_2_000"), process.signal);
    drawer_547->Add( f_hists.get_th1d("weight_tune_3_BDT_3_000"), process.signal);
    drawer_548->Add( f_hists.get_th1d("weight_tune_3_BDT_4_000"), process.signal);
    drawer_549->Add( f_hists.get_th1d("weight_tune_3_BDT_5_000"), process.signal);
    drawer_550->Add( f_hists.get_th1d("weight_tune_3_BDT_6_000"), process.signal);
    drawer_551->Add( f_hists.get_th1d("weight_tune_5_BDT_3_000"), process.signal);
    drawer_552->Add( f_hists.get_th1d("ptag_pfjets02_e"), process.signal);
    drawer_553->Add( f_hists.get_th1d("ptag_pfjets02_pt"), process.signal);
    drawer_554->Add( f_hists.get_th1d("ptag_pfjets02_m"), process.signal);
    drawer_555->Add( f_hists.get_th1d("ptag_pfjets04_e"), process.signal);
    drawer_556->Add( f_hists.get_th1d("ptag_pfjets04_pt"), process.signal);
    drawer_557->Add( f_hists.get_th1d("ptag_pfjets04_m"), process.signal);
    drawer_558->Add( f_hists.get_th1d("ptag_pfjets08_e"), process.signal);
    drawer_559->Add( f_hists.get_th1d("ptag_pfjets08_pt"), process.signal);
    drawer_560->Add( f_hists.get_th1d("ptag_pfjets08_m"), process.signal);
    drawer_561->Add( f_hists.get_th1d("btag_pfjets02_e"), process.signal);
    drawer_562->Add( f_hists.get_th1d("btag_pfjets02_pt"), process.signal);
    drawer_563->Add( f_hists.get_th1d("btag_pfjets02_m"), process.signal);
    drawer_564->Add( f_hists.get_th1d("btag_pfjets04_e"), process.signal);
    drawer_565->Add( f_hists.get_th1d("btag_pfjets04_pt"), process.signal);
    drawer_566->Add( f_hists.get_th1d("btag_pfjets04_m"), process.signal);
    drawer_567->Add( f_hists.get_th1d("btag_pfjets08_e"), process.signal);
    drawer_568->Add( f_hists.get_th1d("btag_pfjets08_pt"), process.signal);
    drawer_569->Add( f_hists.get_th1d("btag_pfjets08_m"), process.signal);
    drawer_570->Add( f_hists.get_th1d("BestMass_jet_e"), process.signal);
    drawer_571->Add( f_hists.get_th1d("BestMass_jet_pt"), process.signal);
    drawer_572->Add( f_hists.get_th1d("BestMass_jet_m"), process.signal);
    drawer_573->Add( f_hists.get_th1d("BestTopMass_jet_e"), process.signal);
    drawer_574->Add( f_hists.get_th1d("BestTopMass_jet_pt"), process.signal);
    drawer_575->Add( f_hists.get_th1d("BestTopMass_jet_m"), process.signal);
    drawer_576->Add( f_hists.get_th1d("SecondTopMass_jet_e"), process.signal);
    drawer_577->Add( f_hists.get_th1d("SecondTopMass_jet_pt"), process.signal);
    drawer_578->Add( f_hists.get_th1d("SecondTopMass_jet_m"), process.signal);
    drawer_579->Add( f_hists.get_th1d("ptag_pfjets02_softDroppedJet_pt"), process.signal);
    drawer_580->Add( f_hists.get_th1d("ptag_pfjets02_softDroppedJet_m"), process.signal);
    drawer_581->Add( f_hists.get_th1d("ptag_pfjets02_softDroppedJet_e"), process.signal);
    drawer_582->Add( f_hists.get_th1d("ptag_pfjets02_leadingSoftDroppedSubJet_pt"), process.signal);
    drawer_583->Add( f_hists.get_th1d("ptag_pfjets02_leadingSoftDroppedSubJet_m"), process.signal);
    drawer_584->Add( f_hists.get_th1d("ptag_pfjets02_leadingSoftDroppedSubJet_e"), process.signal);
    drawer_585->Add( f_hists.get_th1d("ptag_pfjets02_trailingSoftDroppedSubJet_pt"), process.signal);
    drawer_586->Add( f_hists.get_th1d("ptag_pfjets02_trailingSoftDroppedSubJet_m"), process.signal);
    drawer_587->Add( f_hists.get_th1d("ptag_pfjets02_trailingSoftDroppedSubJet_e"), process.signal);
    drawer_588->Add( f_hists.get_th1d("ptag_pfjets04_softDroppedJet_pt"), process.signal);
    drawer_589->Add( f_hists.get_th1d("ptag_pfjets04_softDroppedJet_m"), process.signal);
    drawer_590->Add( f_hists.get_th1d("ptag_pfjets04_softDroppedJet_e"), process.signal);
    drawer_591->Add( f_hists.get_th1d("ptag_pfjets04_leadingSoftDroppedSubJet_pt"), process.signal);
    drawer_592->Add( f_hists.get_th1d("ptag_pfjets04_leadingSoftDroppedSubJet_m"), process.signal);
    drawer_593->Add( f_hists.get_th1d("ptag_pfjets04_leadingSoftDroppedSubJet_e"), process.signal);
    drawer_594->Add( f_hists.get_th1d("ptag_pfjets04_trailingSoftDroppedSubJet_pt"), process.signal);
    drawer_595->Add( f_hists.get_th1d("ptag_pfjets04_trailingSoftDroppedSubJet_m"), process.signal);
    drawer_596->Add( f_hists.get_th1d("ptag_pfjets04_trailingSoftDroppedSubJet_e"), process.signal);
    drawer_597->Add( f_hists.get_th1d("ptag_pfjets08_softDroppedJet_pt"), process.signal);
    drawer_598->Add( f_hists.get_th1d("ptag_pfjets08_softDroppedJet_m"), process.signal);
    drawer_599->Add( f_hists.get_th1d("ptag_pfjets08_softDroppedJet_e"), process.signal);
    drawer_600->Add( f_hists.get_th1d("ptag_pfjets08_leadingSoftDroppedSubJet_pt"), process.signal);
    drawer_601->Add( f_hists.get_th1d("ptag_pfjets08_leadingSoftDroppedSubJet_m"), process.signal);
    drawer_602->Add( f_hists.get_th1d("ptag_pfjets08_leadingSoftDroppedSubJet_e"), process.signal);
    drawer_603->Add( f_hists.get_th1d("ptag_pfjets08_trailingSoftDroppedSubJet_pt"), process.signal);
    drawer_604->Add( f_hists.get_th1d("ptag_pfjets08_trailingSoftDroppedSubJet_m"), process.signal);
    drawer_605->Add( f_hists.get_th1d("ptag_pfjets08_trailingSoftDroppedSubJet_e"), process.signal);
    drawer_606->Add( f_hists.get_th1d("btag_pfjets02_softDroppedJet_pt"), process.signal);
    drawer_607->Add( f_hists.get_th1d("btag_pfjets02_softDroppedJet_m"), process.signal);
    drawer_608->Add( f_hists.get_th1d("btag_pfjets02_softDroppedJet_e"), process.signal);
    drawer_609->Add( f_hists.get_th1d("btag_pfjets02_leadingSoftDroppedSubJet_pt"), process.signal);
    drawer_610->Add( f_hists.get_th1d("btag_pfjets02_leadingSoftDroppedSubJet_m"), process.signal);
    drawer_611->Add( f_hists.get_th1d("btag_pfjets02_leadingSoftDroppedSubJet_e"), process.signal);
    drawer_612->Add( f_hists.get_th1d("btag_pfjets02_trailingSoftDroppedSubJet_pt"), process.signal);
    drawer_613->Add( f_hists.get_th1d("btag_pfjets02_trailingSoftDroppedSubJet_m"), process.signal);
    drawer_614->Add( f_hists.get_th1d("btag_pfjets02_trailingSoftDroppedSubJet_e"), process.signal);
    drawer_615->Add( f_hists.get_th1d("btag_pfjets04_softDroppedJet_pt"), process.signal);
    drawer_616->Add( f_hists.get_th1d("btag_pfjets04_softDroppedJet_m"), process.signal);
    drawer_617->Add( f_hists.get_th1d("btag_pfjets04_softDroppedJet_e"), process.signal);
    drawer_618->Add( f_hists.get_th1d("btag_pfjets04_leadingSoftDroppedSubJet_pt"), process.signal);
    drawer_619->Add( f_hists.get_th1d("btag_pfjets04_leadingSoftDroppedSubJet_m"), process.signal);
    drawer_620->Add( f_hists.get_th1d("btag_pfjets04_leadingSoftDroppedSubJet_e"), process.signal);
    drawer_621->Add( f_hists.get_th1d("btag_pfjets04_trailingSoftDroppedSubJet_pt"), process.signal);
    drawer_622->Add( f_hists.get_th1d("btag_pfjets04_trailingSoftDroppedSubJet_m"), process.signal);
    drawer_623->Add( f_hists.get_th1d("btag_pfjets04_trailingSoftDroppedSubJet_e"), process.signal);
    drawer_624->Add( f_hists.get_th1d("btag_pfjets08_softDroppedJet_pt"), process.signal);
    drawer_625->Add( f_hists.get_th1d("btag_pfjets08_softDroppedJet_m"), process.signal);
    drawer_626->Add( f_hists.get_th1d("btag_pfjets08_softDroppedJet_e"), process.signal);
    drawer_627->Add( f_hists.get_th1d("btag_pfjets08_leadingSoftDroppedSubJet_pt"), process.signal);
    drawer_628->Add( f_hists.get_th1d("btag_pfjets08_leadingSoftDroppedSubJet_m"), process.signal);
    drawer_629->Add( f_hists.get_th1d("btag_pfjets08_leadingSoftDroppedSubJet_e"), process.signal);
    drawer_630->Add( f_hists.get_th1d("btag_pfjets08_trailingSoftDroppedSubJet_pt"), process.signal);
    drawer_631->Add( f_hists.get_th1d("btag_pfjets08_trailingSoftDroppedSubJet_m"), process.signal);
    drawer_632->Add( f_hists.get_th1d("btag_pfjets08_trailingSoftDroppedSubJet_e"), process.signal);
    drawer_633->Add( f_hists.get_th1d("dPhi_Photon_ptag_pfjets04"), process.signal);
    drawer_634->Add( f_hists.get_th1d("dR_Photon_ptag_pfjets04"), process.signal);
    drawer_635->Add( f_hists.get_th1d("M_Photon_ptag_pfjets04"), process.signal);
    drawer_636->Add( f_hists.get_th1d("dPhi_bjet_ptag_pfjets04"), process.signal);
    drawer_637->Add( f_hists.get_th1d("dR_bjet_ptag_pfjets04"), process.signal);
    drawer_677->Add( f_hists.get_th2d("hist_351"), process.signal);
    drawer_678->Add( f_hists.get_th2d("hist_353"), process.signal);
    drawer_679->Add( f_hists.get_th2d("hist_355"), process.signal);
    drawer_680->Add( f_hists.get_th2d("hist_357"), process.signal);
    drawer_681->Add( f_hists.get_th2d("hist_359"), process.signal);
    drawer_682->Add( f_hists.get_th2d("hist_361"), process.signal);
    if("mgp8_pp_tt_aut" == process.physic_name){
    TH1D * hist_683 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_m")->Clone();
    hist_683->SetTitle("PF-Jet R=0.4");
    drawer_638->Add( hist_683, false);
    TH1D * hist_684 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_m")->Clone();
    hist_684->SetTitle("PF-Jet R=0.8");
    drawer_638->Add( hist_684, false);
    TH1D * hist_685 = (TH1D*) f_hists.get_th1d("ptag_calojets04_m")->Clone();
    hist_685->SetTitle("Calo-Jet R=0.4");
    drawer_638->Add( hist_685, false);
    TH1D * hist_686 = (TH1D*) f_hists.get_th1d("ptag_calojets08_m")->Clone();
    hist_686->SetTitle("Calo-Jet R=0.8");
    drawer_638->Add( hist_686, false);
    TH1D * hist_687 = (TH1D*) f_hists.get_th1d("ptag_trkjets04_m")->Clone();
    hist_687->SetTitle("Track-Jet R=0.4");
    drawer_638->Add( hist_687, false);
    TH1D * hist_688 = (TH1D*) f_hists.get_th1d("ptag_trkjets08_m")->Clone();
    hist_688->SetTitle("Track-Jet R=0.8");
    drawer_638->Add( hist_688, false);
    }
    if("mgp8_pp_tt_aut" == process.physic_name){
    TH1D * hist_689 = (TH1D*) f_hists.get_th1d("btag_pfjets04_m")->Clone();
    hist_689->SetTitle("PF-Jet R=0.4");
    drawer_639->Add( hist_689, false);
    TH1D * hist_690 = (TH1D*) f_hists.get_th1d("btag_pfjets08_m")->Clone();
    hist_690->SetTitle("PF-Jet R=0.8");
    drawer_639->Add( hist_690, false);
    TH1D * hist_691 = (TH1D*) f_hists.get_th1d("btag_calojets04_m")->Clone();
    hist_691->SetTitle("Calo-Jet R=0.4");
    drawer_639->Add( hist_691, false);
    TH1D * hist_692 = (TH1D*) f_hists.get_th1d("btag_calojets08_m")->Clone();
    hist_692->SetTitle("Calo-Jet R=0.8");
    drawer_639->Add( hist_692, false);
    TH1D * hist_693 = (TH1D*) f_hists.get_th1d("btag_trkjets04_m")->Clone();
    hist_693->SetTitle("Track-Jet R=0.4");
    drawer_639->Add( hist_693, false);
    TH1D * hist_694 = (TH1D*) f_hists.get_th1d("btag_trkjets08_m")->Clone();
    hist_694->SetTitle("Track-Jet R=0.8");
    drawer_639->Add( hist_694, false);
    }
    if("mgp8_pp_tt_aut" == process.physic_name){
    TH1D * hist_695 = (TH1D*) f_hists.get_th1d("ptag_pfjets02_m")->Clone();
    hist_695->SetTitle("PF-Jet R=0.2");
    drawer_640->Add( hist_695, false);
    TH1D * hist_696 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_m")->Clone();
    hist_696->SetTitle("PF-Jet R=0.4");
    drawer_640->Add( hist_696, false);
    TH1D * hist_697 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_m")->Clone();
    hist_697->SetTitle("PF-Jet R=0.8");
    drawer_640->Add( hist_697, false);
    TH1D * hist_698 = (TH1D*) f_hists.get_th1d("ptag_bestJet_m")->Clone();
    hist_698->SetTitle("Best Jet");
    drawer_640->Add( hist_698, false);
    }
    if("mgp8_pp_tt_aut" == process.physic_name){
    TH1D * hist_699 = (TH1D*) f_hists.get_th1d("ptag_pfjets02_m")->Clone();
    hist_699->SetTitle("PF-Jet R=0.2");
    drawer_641->Add( hist_699, false);
    TH1D * hist_700 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_m")->Clone();
    hist_700->SetTitle("PF-Jet R=0.4");
    drawer_641->Add( hist_700, false);
    TH1D * hist_701 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_m")->Clone();
    hist_701->SetTitle("PF-Jet R=0.8");
    drawer_641->Add( hist_701, false);
    TH1D * hist_702 = (TH1D*) f_hists.get_th1d("ptag_bestJet_m")->Clone();
    hist_702->SetTitle("Best Jet");
    drawer_641->Add( hist_702, false);
    }
    if("mgp8_pp_tt_aut" == process.physic_name){
    TH1D * hist_703 = (TH1D*) f_hists.get_th1d("ptag_pfjets02_softDroppedJet_m")->Clone();
    hist_703->SetTitle("SoftDropped PF-Jet R=0.2");
    drawer_642->Add( hist_703, false);
    TH1D * hist_704 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_softDroppedJet_m")->Clone();
    hist_704->SetTitle("SoftDropped PF-Jet R=0.4");
    drawer_642->Add( hist_704, false);
    TH1D * hist_705 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_softDroppedJet_m")->Clone();
    hist_705->SetTitle("SoftDropped PF-Jet R=0.8");
    drawer_642->Add( hist_705, false);
    TH1D * hist_706 = (TH1D*) f_hists.get_th1d("ptag_bestJet_m")->Clone();
    hist_706->SetTitle("Best Jet");
    drawer_642->Add( hist_706, false);
    }
    if("mgp8_pp_tt_aut" == process.physic_name){
    TH1D * hist_707 = (TH1D*) f_hists.get_th1d("ptag_pfjets02_softDroppedJet_m")->Clone();
    hist_707->SetTitle("SoftDropped PF-Jet R=0.2");
    drawer_643->Add( hist_707, false);
    TH1D * hist_708 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_softDroppedJet_m")->Clone();
    hist_708->SetTitle("SoftDropped PF-Jet R=0.4");
    drawer_643->Add( hist_708, false);
    TH1D * hist_709 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_softDroppedJet_m")->Clone();
    hist_709->SetTitle("SoftDropped PF-Jet R=0.8");
    drawer_643->Add( hist_709, false);
    TH1D * hist_710 = (TH1D*) f_hists.get_th1d("ptag_bestJet_m")->Clone();
    hist_710->SetTitle("Best Jet");
    drawer_643->Add( hist_710, false);
    }
    if("mgp8_pp_tt_aut" == process.physic_name){
    TH1D * hist_711 = (TH1D*) f_hists.get_th1d("ptag_pfjets02_softDroppedJet_m")->Clone();
    hist_711->SetTitle("SoftDropped PF-Jet R=0.2");
    drawer_644->Add( hist_711, false);
    TH1D * hist_712 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_softDroppedJet_m")->Clone();
    hist_712->SetTitle("SoftDropped PF-Jet R=0.4");
    drawer_644->Add( hist_712, false);
    TH1D * hist_713 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_softDroppedJet_m")->Clone();
    hist_713->SetTitle("SoftDropped PF-Jet R=0.8");
    drawer_644->Add( hist_713, false);
    TH1D * hist_714 = (TH1D*) f_hists.get_th1d("ptag_bestJet_m")->Clone();
    hist_714->SetTitle("Best Jet");
    drawer_644->Add( hist_714, false);
    }
    if("mgp8_pp_tt_aut" == process.physic_name){
    TH1D * hist_715 = (TH1D*) f_hists.get_th1d("ptag_pfjets02_m")->Clone();
    hist_715->SetTitle("PF-Jet R=0.2");
    drawer_645->Add( hist_715, false);
    TH1D * hist_716 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_m")->Clone();
    hist_716->SetTitle("PF-Jet R=0.4");
    drawer_645->Add( hist_716, false);
    TH1D * hist_717 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_m")->Clone();
    hist_717->SetTitle("PF-Jet R=0.8");
    drawer_645->Add( hist_717, false);
    TH1D * hist_718 = (TH1D*) f_hists.get_th1d("ptag_pfjets02_softDroppedJet_m")->Clone();
    hist_718->SetTitle("SoftDropped PF-Jet R=0.2");
    drawer_645->Add( hist_718, false);
    TH1D * hist_719 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_softDroppedJet_m")->Clone();
    hist_719->SetTitle("SoftDropped PF-Jet R=0.4");
    drawer_645->Add( hist_719, false);
    TH1D * hist_720 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_softDroppedJet_m")->Clone();
    hist_720->SetTitle("SoftDropped PF-Jet R=0.8");
    drawer_645->Add( hist_720, false);
    }
    if("mgp8_pp_tt_aut" == process.physic_name){
    TH1D * hist_721 = (TH1D*) f_hists.get_th1d("ptag_pfjets02_e")->Clone();
    hist_721->SetTitle("PF-Jet R=0.2");
    drawer_646->Add( hist_721, false);
    TH1D * hist_722 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_e")->Clone();
    hist_722->SetTitle("PF-Jet R=0.4");
    drawer_646->Add( hist_722, false);
    TH1D * hist_723 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_e")->Clone();
    hist_723->SetTitle("PF-Jet R=0.8");
    drawer_646->Add( hist_723, false);
    TH1D * hist_724 = (TH1D*) f_hists.get_th1d("ptag_pfjets02_softDroppedJet_e")->Clone();
    hist_724->SetTitle("SoftDropped PF-Jet R=0.2");
    drawer_646->Add( hist_724, false);
    TH1D * hist_725 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_softDroppedJet_e")->Clone();
    hist_725->SetTitle("SoftDropped PF-Jet R=0.4");
    drawer_646->Add( hist_725, false);
    TH1D * hist_726 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_softDroppedJet_e")->Clone();
    hist_726->SetTitle("SoftDropped PF-Jet R=0.8");
    drawer_646->Add( hist_726, false);
    }
    if("mgp8_pp_tt_aut" == process.physic_name){
    TH1D * hist_727 = (TH1D*) f_hists.get_th1d("btag_pfjets02_m")->Clone();
    hist_727->SetTitle("PF-Jet R=0.2");
    drawer_647->Add( hist_727, false);
    TH1D * hist_728 = (TH1D*) f_hists.get_th1d("btag_pfjets04_m")->Clone();
    hist_728->SetTitle("PF-Jet R=0.4");
    drawer_647->Add( hist_728, false);
    TH1D * hist_729 = (TH1D*) f_hists.get_th1d("btag_pfjets08_m")->Clone();
    hist_729->SetTitle("PF-Jet R=0.8");
    drawer_647->Add( hist_729, false);
    }
    if("mgp8_pp_tt_aut" == process.physic_name){
    TH1D * hist_730 = (TH1D*) f_hists.get_th1d("btag_pfjets04_m")->Clone();
    hist_730->SetTitle("PF-Jet R=0.4");
    drawer_648->Add( hist_730, false);
    TH1D * hist_731 = (TH1D*) f_hists.get_th1d("btag_pfjets04_softDroppedJet_m")->Clone();
    hist_731->SetTitle("SoftDropped PF-Jet R=0.4");
    drawer_648->Add( hist_731, false);
    TH1D * hist_732 = (TH1D*) f_hists.get_th1d("btag_pfjets08_m")->Clone();
    hist_732->SetTitle("PF-Jet R=0.8");
    drawer_648->Add( hist_732, false);
    TH1D * hist_733 = (TH1D*) f_hists.get_th1d("btag_pfjets08_softDroppedJet_m")->Clone();
    hist_733->SetTitle("SoftDropped PF-Jet R=0.8");
    drawer_648->Add( hist_733, false);
    }
    if("mgp8_pp_tt_aut" == process.physic_name){
    TH1D * hist_734 = (TH1D*) f_hists.get_th1d("btag_pfjets04_m")->Clone();
    hist_734->SetTitle("PF-Jet R=0.4");
    drawer_649->Add( hist_734, false);
    TH1D * hist_735 = (TH1D*) f_hists.get_th1d("btag_pfjets04_softDroppedJet_m")->Clone();
    hist_735->SetTitle("SoftDropped PF-Jet R=0.4");
    drawer_649->Add( hist_735, false);
    TH1D * hist_736 = (TH1D*) f_hists.get_th1d("btag_pfjets08_m")->Clone();
    hist_736->SetTitle("PF-Jet R=0.8");
    drawer_649->Add( hist_736, false);
    TH1D * hist_737 = (TH1D*) f_hists.get_th1d("btag_pfjets08_softDroppedJet_m")->Clone();
    hist_737->SetTitle("SoftDropped PF-Jet R=0.8");
    drawer_649->Add( hist_737, false);
    }
    if("mgp8_pp_tt_aut" == process.physic_name){
    TH1D * hist_738 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_m")->Clone();
    hist_738->SetTitle("PF-Jet R=0.8");
    drawer_650->Add( hist_738, false);
    TH1D * hist_739 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_softDroppedJet_m")->Clone();
    hist_739->SetTitle("SoftDropped PF-Jet R=0.8");
    drawer_650->Add( hist_739, false);
    TH1D * hist_740 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_leadingSoftDroppedSubJet_m")->Clone();
    hist_740->SetTitle("Leading PF-SubJet R=0.8");
    drawer_650->Add( hist_740, false);
    TH1D * hist_741 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_trailingSoftDroppedSubJet_m")->Clone();
    hist_741->SetTitle("Trailing PF-SubJet R=0.8");
    drawer_650->Add( hist_741, false);
    }
    if("mgp8_pp_tt_aut" == process.physic_name){
    TH1D * hist_742 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_e")->Clone();
    hist_742->SetTitle("PF-Jet R=0.8");
    drawer_651->Add( hist_742, false);
    TH1D * hist_743 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_softDroppedJet_e")->Clone();
    hist_743->SetTitle("SoftDropped PF-Jet R=0.8");
    drawer_651->Add( hist_743, false);
    TH1D * hist_744 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_leadingSoftDroppedSubJet_e")->Clone();
    hist_744->SetTitle("Leading PF-SubJet R=0.8");
    drawer_651->Add( hist_744, false);
    TH1D * hist_745 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_trailingSoftDroppedSubJet_e")->Clone();
    hist_745->SetTitle("Trailing PF-SubJet R=0.8");
    drawer_651->Add( hist_745, false);
    }
    if("mgp8_pp_tt_aut" == process.physic_name){
    TH1D * hist_746 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_m")->Clone();
    hist_746->SetTitle("PF-Jet R=0.4");
    drawer_652->Add( hist_746, false);
    TH1D * hist_747 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_softDroppedJet_m")->Clone();
    hist_747->SetTitle("SoftDropped PF-Jet R=0.4");
    drawer_652->Add( hist_747, false);
    TH1D * hist_748 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_leadingSoftDroppedSubJet_m")->Clone();
    hist_748->SetTitle("Leading PF-SubJet R=0.4");
    drawer_652->Add( hist_748, false);
    TH1D * hist_749 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_trailingSoftDroppedSubJet_m")->Clone();
    hist_749->SetTitle("Trailing PF-SubJet R=0.4");
    drawer_652->Add( hist_749, false);
    }
    if("mgp8_pp_tt_aut" == process.physic_name){
    TH1D * hist_750 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_e")->Clone();
    hist_750->SetTitle("PF-Jet R=0.4");
    drawer_653->Add( hist_750, false);
    TH1D * hist_751 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_softDroppedJet_e")->Clone();
    hist_751->SetTitle("SoftDropped PF-Jet R=0.4");
    drawer_653->Add( hist_751, false);
    TH1D * hist_752 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_leadingSoftDroppedSubJet_e")->Clone();
    hist_752->SetTitle("Leading PF-SubJet R=0.4");
    drawer_653->Add( hist_752, false);
    TH1D * hist_753 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_trailingSoftDroppedSubJet_e")->Clone();
    hist_753->SetTitle("Trailing PF-SubJet R=0.4");
    drawer_653->Add( hist_753, false);
    }
    TH1D * hist_0_754 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_m")->Clone();
    TH1D * hist_1_755 = (TH1D*) f_hists.get_th1d("hist_305")->Clone();
    hist_0_754->SetTitle( title.c_str() );
    hist_1_755->SetTitle( (title + " after cut").c_str() );
    drawer_654->AddCummulative(hist_0_754, process.signal, 0);
    drawer_654->AddCummulative(hist_1_755, process.signal, 1);
    TH1D * hist_0_756 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_leadingSoftDroppedSubJet_m")->Clone();
    TH1D * hist_1_757 = (TH1D*) f_hists.get_th1d("hist_307")->Clone();
    hist_0_756->SetTitle( title.c_str() );
    hist_1_757->SetTitle( (title + " after cut").c_str() );
    drawer_655->AddCummulative(hist_0_756, process.signal, 0);
    drawer_655->AddCummulative(hist_1_757, process.signal, 1);
    TH1D * hist_0_758 = (TH1D*) f_hists.get_th1d("ptag_pfjets04_softDroppedJet_m")->Clone();
    TH1D * hist_1_759 = (TH1D*) f_hists.get_th1d("hist_309")->Clone();
    hist_0_758->SetTitle( title.c_str() );
    hist_1_759->SetTitle( (title + " after cut").c_str() );
    drawer_656->AddCummulative(hist_0_758, process.signal, 0);
    drawer_656->AddCummulative(hist_1_759, process.signal, 1);
    TH1D * hist_0_760 = (TH1D*) f_hists.get_th1d("ptag_bestJet_tau1")->Clone();
    TH1D * hist_1_761 = (TH1D*) f_hists.get_th1d("hist_311")->Clone();
    hist_0_760->SetTitle( title.c_str() );
    hist_1_761->SetTitle( (title + " after cut").c_str() );
    drawer_657->AddCummulative(hist_0_760, process.signal, 0);
    drawer_657->AddCummulative(hist_1_761, process.signal, 1);
    TH1D * hist_0_762 = (TH1D*) f_hists.get_th1d("ptag_bestJet_tau2")->Clone();
    TH1D * hist_1_763 = (TH1D*) f_hists.get_th1d("hist_313")->Clone();
    hist_0_762->SetTitle( title.c_str() );
    hist_1_763->SetTitle( (title + " after cut").c_str() );
    drawer_658->AddCummulative(hist_0_762, process.signal, 0);
    drawer_658->AddCummulative(hist_1_763, process.signal, 1);
    TH1D * hist_0_764 = (TH1D*) f_hists.get_th1d("ptag_bestJet_tau3")->Clone();
    TH1D * hist_1_765 = (TH1D*) f_hists.get_th1d("hist_315")->Clone();
    hist_0_764->SetTitle( title.c_str() );
    hist_1_765->SetTitle( (title + " after cut").c_str() );
    drawer_659->AddCummulative(hist_0_764, process.signal, 0);
    drawer_659->AddCummulative(hist_1_765, process.signal, 1);
    TH1D * hist_0_766 = (TH1D*) f_hists.get_th1d("ptag_bestJet_tau31")->Clone();
    TH1D * hist_1_767 = (TH1D*) f_hists.get_th1d("hist_317")->Clone();
    hist_0_766->SetTitle( title.c_str() );
    hist_1_767->SetTitle( (title + " after cut").c_str() );
    drawer_660->AddCummulative(hist_0_766, process.signal, 0);
    drawer_660->AddCummulative(hist_1_767, process.signal, 1);
    TH1D * hist_0_768 = (TH1D*) f_hists.get_th1d("ptag_bestJet_tau32")->Clone();
    TH1D * hist_1_769 = (TH1D*) f_hists.get_th1d("hist_319")->Clone();
    hist_0_768->SetTitle( title.c_str() );
    hist_1_769->SetTitle( (title + " after cut").c_str() );
    drawer_661->AddCummulative(hist_0_768, process.signal, 0);
    drawer_661->AddCummulative(hist_1_769, process.signal, 1);
    TH1D * hist_0_770 = (TH1D*) f_hists.get_th1d("ptag_bestJet_tau21")->Clone();
    TH1D * hist_1_771 = (TH1D*) f_hists.get_th1d("hist_321")->Clone();
    hist_0_770->SetTitle( title.c_str() );
    hist_1_771->SetTitle( (title + " after cut").c_str() );
    drawer_662->AddCummulative(hist_0_770, process.signal, 0);
    drawer_662->AddCummulative(hist_1_771, process.signal, 1);
    TH1D * hist_0_772 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_tau1")->Clone();
    TH1D * hist_1_773 = (TH1D*) f_hists.get_th1d("hist_323")->Clone();
    hist_0_772->SetTitle( title.c_str() );
    hist_1_773->SetTitle( (title + " after cut").c_str() );
    drawer_663->AddCummulative(hist_0_772, process.signal, 0);
    drawer_663->AddCummulative(hist_1_773, process.signal, 1);
    TH1D * hist_0_774 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_tau2")->Clone();
    TH1D * hist_1_775 = (TH1D*) f_hists.get_th1d("hist_325")->Clone();
    hist_0_774->SetTitle( title.c_str() );
    hist_1_775->SetTitle( (title + " after cut").c_str() );
    drawer_664->AddCummulative(hist_0_774, process.signal, 0);
    drawer_664->AddCummulative(hist_1_775, process.signal, 1);
    TH1D * hist_0_776 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_tau3")->Clone();
    TH1D * hist_1_777 = (TH1D*) f_hists.get_th1d("hist_327")->Clone();
    hist_0_776->SetTitle( title.c_str() );
    hist_1_777->SetTitle( (title + " after cut").c_str() );
    drawer_665->AddCummulative(hist_0_776, process.signal, 0);
    drawer_665->AddCummulative(hist_1_777, process.signal, 1);
    TH1D * hist_0_778 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_tau31")->Clone();
    TH1D * hist_1_779 = (TH1D*) f_hists.get_th1d("hist_329")->Clone();
    hist_0_778->SetTitle( title.c_str() );
    hist_1_779->SetTitle( (title + " after cut").c_str() );
    drawer_666->AddCummulative(hist_0_778, process.signal, 0);
    drawer_666->AddCummulative(hist_1_779, process.signal, 1);
    TH1D * hist_0_780 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_tau32")->Clone();
    TH1D * hist_1_781 = (TH1D*) f_hists.get_th1d("hist_331")->Clone();
    hist_0_780->SetTitle( title.c_str() );
    hist_1_781->SetTitle( (title + " after cut").c_str() );
    drawer_667->AddCummulative(hist_0_780, process.signal, 0);
    drawer_667->AddCummulative(hist_1_781, process.signal, 1);
    TH1D * hist_0_782 = (TH1D*) f_hists.get_th1d("ptag_pfjets08_tau21")->Clone();
    TH1D * hist_1_783 = (TH1D*) f_hists.get_th1d("hist_333")->Clone();
    hist_0_782->SetTitle( title.c_str() );
    hist_1_783->SetTitle( (title + " after cut").c_str() );
    drawer_668->AddCummulative(hist_0_782, process.signal, 0);
    drawer_668->AddCummulative(hist_1_783, process.signal, 1);
    TH1D * hist_0_784 = (TH1D*) f_hists.get_th1d("photon_x_ptag_bestJet")->Clone();
    TH1D * hist_1_785 = (TH1D*) f_hists.get_th1d("hist_335")->Clone();
    hist_0_784->SetTitle( title.c_str() );
    hist_1_785->SetTitle( (title + " after cut").c_str() );
    drawer_669->AddCummulative(hist_0_784, process.signal, 0);
    drawer_669->AddCummulative(hist_1_785, process.signal, 1);
    TH1D * hist_0_786 = (TH1D*) f_hists.get_th1d("dPhi_Photon_ptag_bestJet")->Clone();
    TH1D * hist_1_787 = (TH1D*) f_hists.get_th1d("hist_337")->Clone();
    hist_0_786->SetTitle( title.c_str() );
    hist_1_787->SetTitle( (title + " after cut").c_str() );
    drawer_670->AddCummulative(hist_0_786, process.signal, 0);
    drawer_670->AddCummulative(hist_1_787, process.signal, 1);
    TH1D * hist_0_788 = (TH1D*) f_hists.get_th1d("dR_Photon_ptag_bestJet")->Clone();
    TH1D * hist_1_789 = (TH1D*) f_hists.get_th1d("hist_339")->Clone();
    hist_0_788->SetTitle( title.c_str() );
    hist_1_789->SetTitle( (title + " after cut").c_str() );
    drawer_671->AddCummulative(hist_0_788, process.signal, 0);
    drawer_671->AddCummulative(hist_1_789, process.signal, 1);
    TH1D * hist_0_790 = (TH1D*) f_hists.get_th1d("M_Photon_ptag_bestJet")->Clone();
    TH1D * hist_1_791 = (TH1D*) f_hists.get_th1d("hist_341")->Clone();
    hist_0_790->SetTitle( title.c_str() );
    hist_1_791->SetTitle( (title + " after cut").c_str() );
    drawer_672->AddCummulative(hist_0_790, process.signal, 0);
    drawer_672->AddCummulative(hist_1_791, process.signal, 1);
    TH1D * hist_0_792 = (TH1D*) f_hists.get_th1d("bjet_x_ptag_bestJet")->Clone();
    TH1D * hist_1_793 = (TH1D*) f_hists.get_th1d("hist_343")->Clone();
    hist_0_792->SetTitle( title.c_str() );
    hist_1_793->SetTitle( (title + " after cut").c_str() );
    drawer_673->AddCummulative(hist_0_792, process.signal, 0);
    drawer_673->AddCummulative(hist_1_793, process.signal, 1);
    TH1D * hist_0_794 = (TH1D*) f_hists.get_th1d("dPhi_bjet_ptag_bestJet")->Clone();
    TH1D * hist_1_795 = (TH1D*) f_hists.get_th1d("hist_345")->Clone();
    hist_0_794->SetTitle( title.c_str() );
    hist_1_795->SetTitle( (title + " after cut").c_str() );
    drawer_674->AddCummulative(hist_0_794, process.signal, 0);
    drawer_674->AddCummulative(hist_1_795, process.signal, 1);
    TH1D * hist_0_796 = (TH1D*) f_hists.get_th1d("dR_bjet_ptag_bestJet")->Clone();
    TH1D * hist_1_797 = (TH1D*) f_hists.get_th1d("hist_347")->Clone();
    hist_0_796->SetTitle( title.c_str() );
    hist_1_797->SetTitle( (title + " after cut").c_str() );
    drawer_675->AddCummulative(hist_0_796, process.signal, 0);
    drawer_675->AddCummulative(hist_1_797, process.signal, 1);
    TH1D * hist_0_798 = (TH1D*) f_hists.get_th1d("dR_bjet_ptag_bestJet")->Clone();
    TH1D * hist_1_799 = (TH1D*) f_hists.get_th1d("hist_349")->Clone();
    hist_0_798->SetTitle( title.c_str() );
    hist_1_799->SetTitle( (title + " after cut").c_str() );
    drawer_676->AddCummulative(hist_0_798, process.signal, 0);
    drawer_676->AddCummulative(hist_1_799, process.signal, 1);
    //[[[end]]]
  } 

  /*[[[cog
    for plot in default_plots :
      var = plot.var
      drawer_name = plot.drawer
      string = "auto canvas_def_" + drawer_name + " = mRoot::draw_hists_FCC(" + drawer_name + ", output_path, \"A_" + var.key + "_def_fcc.pdf\", \"" + var.name + "\", \"\", \"default\");"
      cog.outl( string )

    for plot in tmva_plots :
      var = plot.var
      drawer_name = plot.drawer
      string = "auto canvas_tmva_" + drawer_name + " = mRoot::draw_hists_FCC(" + drawer_name + ", output_path, \"B_" + var.key + "_tmva_fcc.pdf\", \"" + var.name + "\", \"\", \"tmva\");"
      cog.outl( string )

    for plot in corr_plots :
      var_x = plot.var_x
      var_y = plot.var_y
      drawer_name = plot.drawer
      cog.outl( drawer_name+"->label_x = \"" + var_x.name + "\";" )
      cog.outl( drawer_name+"->label_y = \"" + var_y.name + "\";" )
      cog.outl( drawer_name+"->signals.pop_back();" )
      string = "auto canvas_def_" + drawer_name + " = mRoot::draw_hists_FCC(" + drawer_name + ", output_path, \"C_CORRELATION_" + mRootCOG.get_cog_key() + "_def_fcc.pdf\", \"\", \"\", \"correlation\");"
      cog.outl( string )

    for cplot in comp_plots:
      drawer_name = cplot.drawer
      dmode = '\"default\"'
      if cplot.draw_mode == "nolog" : dmode = '\"default nolog\"'
      if cplot.xmin and cplot.xmax:
        cog.outl( drawer_name+"->xmax = " + str(cplot.xmax) + ";" )
        cog.outl( drawer_name+"->xmin = " + str(cplot.xmin) + ";" )
      string = "auto canvas_comp_" +  drawer_name + " = mRoot::draw_hists_FCC(" + drawer_name + ", output_path, \"D_COMPARISON_" + mRootCOG.get_cog_key() + "_" + cplot.channel + "_fcc.pdf\", \"" + cplot.title + "\", \"" + cplot.short_name + "\", "+ dmode +");"
      cog.outl( string )

    for plot in cut_plots:
      var = plot.var
      drawer_name = plot.drawer
      string = "auto canvas_def_" + drawer_name + " = mRoot::draw_hists_FCC(" + drawer_name + ", output_path, \"F_CUT_" + mRootCOG.get_cog_key() + "_fcc.pdf\", \"" + var.name + "\", \"" + plot.cut_title + "\", \"cut\");"
      cog.outl( string )
  ]]]*/
  auto canvas_def_drawer_362 = mRoot::draw_hists_FCC(drawer_362, output_path, "A_photon_eta_def_fcc.pdf", "Photon #eta", "", "default");
  auto canvas_def_drawer_363 = mRoot::draw_hists_FCC(drawer_363, output_path, "A_photon_pt_def_fcc.pdf", "Photon p_{T} [GeV]", "", "default");
  auto canvas_def_drawer_364 = mRoot::draw_hists_FCC(drawer_364, output_path, "A_top_pt_def_fcc.pdf", "t p_{T} [GeV]", "", "default");
  auto canvas_def_drawer_365 = mRoot::draw_hists_FCC(drawer_365, output_path, "A_ptag_bestJet_m_def_fcc.pdf", "Best #gamma-jet M [GeV]", "", "default");
  auto canvas_def_drawer_366 = mRoot::draw_hists_FCC(drawer_366, output_path, "A_ptag_bestJet_pt_def_fcc.pdf", "Best #gamma-jet p_{T} [GeV]", "", "default");
  auto canvas_def_drawer_367 = mRoot::draw_hists_FCC(drawer_367, output_path, "A_ptag_bestJet_eta_def_fcc.pdf", "Best #gamma-jet #eta", "", "default");
  auto canvas_def_drawer_368 = mRoot::draw_hists_FCC(drawer_368, output_path, "A_btag_pfjets04_eta_def_fcc.pdf", "b-jet #eta", "", "default");
  auto canvas_def_drawer_369 = mRoot::draw_hists_FCC(drawer_369, output_path, "A_ptag_bestJet_tau1_def_fcc.pdf", "best #gamma-jet #tau_{1}", "", "default");
  auto canvas_def_drawer_370 = mRoot::draw_hists_FCC(drawer_370, output_path, "A_ptag_bestJet_tau2_def_fcc.pdf", "best #gamma-jet #tau_{2}", "", "default");
  auto canvas_def_drawer_371 = mRoot::draw_hists_FCC(drawer_371, output_path, "A_ptag_bestJet_tau3_def_fcc.pdf", "best #gamma-jet #tau_{3}", "", "default");
  auto canvas_def_drawer_372 = mRoot::draw_hists_FCC(drawer_372, output_path, "A_ptag_bestJet_tau31_def_fcc.pdf", "best #gamma-jet #tau_{31}", "", "default");
  auto canvas_def_drawer_373 = mRoot::draw_hists_FCC(drawer_373, output_path, "A_ptag_bestJet_tau32_def_fcc.pdf", "best #gamma-jet #tau_{32}", "", "default");
  auto canvas_def_drawer_374 = mRoot::draw_hists_FCC(drawer_374, output_path, "A_ptag_bestJet_tau21_def_fcc.pdf", "best #gamma-jet #tau_{21}", "", "default");
  auto canvas_def_drawer_375 = mRoot::draw_hists_FCC(drawer_375, output_path, "A_ptag_pfjets08_tau1_def_fcc.pdf", "#gamma-PF-jet R=0.8 #tau_{1}", "", "default");
  auto canvas_def_drawer_376 = mRoot::draw_hists_FCC(drawer_376, output_path, "A_ptag_pfjets08_tau2_def_fcc.pdf", "#gamma-PF-jet R=0.8 #tau_{2}", "", "default");
  auto canvas_def_drawer_377 = mRoot::draw_hists_FCC(drawer_377, output_path, "A_ptag_pfjets08_tau3_def_fcc.pdf", "#gamma-PF-jet R=0.8 #tau_{3}", "", "default");
  auto canvas_def_drawer_378 = mRoot::draw_hists_FCC(drawer_378, output_path, "A_ptag_pfjets08_tau31_def_fcc.pdf", "#gamma-PF-jet R=0.8 #tau_{31}", "", "default");
  auto canvas_def_drawer_379 = mRoot::draw_hists_FCC(drawer_379, output_path, "A_ptag_pfjets08_tau32_def_fcc.pdf", "#gamma-PF-jet R=0.8 #tau_{32}", "", "default");
  auto canvas_def_drawer_380 = mRoot::draw_hists_FCC(drawer_380, output_path, "A_ptag_pfjets08_tau21_def_fcc.pdf", "#gamma-PF-jet R=0.8 #tau_{21}", "", "default");
  auto canvas_def_drawer_381 = mRoot::draw_hists_FCC(drawer_381, output_path, "A_photon_x_ptag_bestJet_def_fcc.pdf", "(P_{#gamma}, P_{best j#gamma-et}) [GeV^{2}]", "", "default");
  auto canvas_def_drawer_382 = mRoot::draw_hists_FCC(drawer_382, output_path, "A_lepton_x_btag_pfjets08_def_fcc.pdf", "(P_{lepton}, P_{b-PF-jet R=0.8}) [GeV^{2}]", "", "default");
  auto canvas_def_drawer_383 = mRoot::draw_hists_FCC(drawer_383, output_path, "A_dPhi_lepton_btag_pfjets08_def_fcc.pdf", "#Delta #phi(lepton, b-PF-jet R=0.8)", "", "default");
  auto canvas_def_drawer_384 = mRoot::draw_hists_FCC(drawer_384, output_path, "A_dR_lepton_btag_pfjets08_def_fcc.pdf", "#Delta R(lepton, b-PF-jet R=0.8)", "", "default");
  auto canvas_def_drawer_385 = mRoot::draw_hists_FCC(drawer_385, output_path, "A_lepton_x_btag_pfjets04_def_fcc.pdf", "(P_{lepton}, P_{b-PF-jet R=0.4}) [GeV^{2}]", "", "default");
  auto canvas_def_drawer_386 = mRoot::draw_hists_FCC(drawer_386, output_path, "A_dPhi_lepton_btag_pfjets04_def_fcc.pdf", "#Delta #phi(lepton, b-PF-jet R=0.4)", "", "default");
  auto canvas_def_drawer_387 = mRoot::draw_hists_FCC(drawer_387, output_path, "A_dR_lepton_btag_pfjets04_def_fcc.pdf", "#Delta R(lepton, b-PF-jet R=0.4)", "", "default");
  auto canvas_def_drawer_388 = mRoot::draw_hists_FCC(drawer_388, output_path, "A_M_lepton_met_def_fcc.pdf", "M(lepton, MET) [GeV]", "", "default");
  auto canvas_def_drawer_389 = mRoot::draw_hists_FCC(drawer_389, output_path, "A_M_bjet_lepton_met_def_fcc.pdf", "M(lepton, MET, b-PF-jet R=0.4) [GeV]", "", "default");
  auto canvas_def_drawer_390 = mRoot::draw_hists_FCC(drawer_390, output_path, "A_dPhi_Photon_ptag_bestJet_def_fcc.pdf", "#Delta #phi(#gamma, best #gamma-jet)", "", "default");
  auto canvas_def_drawer_391 = mRoot::draw_hists_FCC(drawer_391, output_path, "A_dR_Photon_ptag_bestJet_def_fcc.pdf", "#Delta R(#gamma, best #gamma-jet)", "", "default");
  auto canvas_def_drawer_392 = mRoot::draw_hists_FCC(drawer_392, output_path, "A_M_Photon_ptag_bestJet_def_fcc.pdf", "M(#gamma, best #gamma-jet)", "", "default");
  auto canvas_def_drawer_393 = mRoot::draw_hists_FCC(drawer_393, output_path, "A_bjet_x_ptag_bestJet_def_fcc.pdf", "(P_{b-jet}, P_{best #gamma-jet}) [GeV^{2}]", "", "default");
  auto canvas_def_drawer_394 = mRoot::draw_hists_FCC(drawer_394, output_path, "A_dPhi_bjet_ptag_bestJet_def_fcc.pdf", "#Delta #phi(b-jet, best #gamma-jet)", "", "default");
  auto canvas_def_drawer_395 = mRoot::draw_hists_FCC(drawer_395, output_path, "A_dR_bjet_ptag_bestJet_def_fcc.pdf", "#Delta R(b-jet, best #gamma-jet)", "", "default");
  auto canvas_def_drawer_396 = mRoot::draw_hists_FCC(drawer_396, output_path, "A_lepton_relIso_def_fcc.pdf", "lepton relative isolation", "", "default");
  auto canvas_def_drawer_397 = mRoot::draw_hists_FCC(drawer_397, output_path, "A_photon_relIso_def_fcc.pdf", "#gamma relative isolation", "", "default");
  auto canvas_def_drawer_398 = mRoot::draw_hists_FCC(drawer_398, output_path, "A_photon_x_ptag_pfjets08_def_fcc.pdf", "(P_{#gamma-jet}, P_{#gamma-jet}) [GeV^{2}]", "", "default");
  auto canvas_def_drawer_399 = mRoot::draw_hists_FCC(drawer_399, output_path, "A_bjet_x_ptag_pfjets08_def_fcc.pdf", "(P_{b-jet}, P_{#gamma-jet}) [GeV^{2}]", "", "default");
  auto canvas_def_drawer_400 = mRoot::draw_hists_FCC(drawer_400, output_path, "A_weight_tune_3_BDT_0_000_def_fcc.pdf", "BDT", "", "default");
  auto canvas_def_drawer_401 = mRoot::draw_hists_FCC(drawer_401, output_path, "A_weight_tune_3_BDT_1_000_def_fcc.pdf", "BDT", "", "default");
  auto canvas_def_drawer_402 = mRoot::draw_hists_FCC(drawer_402, output_path, "A_weight_tune_3_BDT_2_000_def_fcc.pdf", "BDT", "", "default");
  auto canvas_def_drawer_403 = mRoot::draw_hists_FCC(drawer_403, output_path, "A_weight_tune_3_BDT_3_000_def_fcc.pdf", "BDT", "", "default");
  auto canvas_def_drawer_404 = mRoot::draw_hists_FCC(drawer_404, output_path, "A_weight_tune_3_BDT_4_000_def_fcc.pdf", "BDT", "", "default");
  auto canvas_def_drawer_405 = mRoot::draw_hists_FCC(drawer_405, output_path, "A_weight_tune_3_BDT_5_000_def_fcc.pdf", "BDT", "", "default");
  auto canvas_def_drawer_406 = mRoot::draw_hists_FCC(drawer_406, output_path, "A_weight_tune_3_BDT_6_000_def_fcc.pdf", "BDT", "", "default");
  auto canvas_def_drawer_407 = mRoot::draw_hists_FCC(drawer_407, output_path, "A_weight_tune_5_BDT_3_000_def_fcc.pdf", "BDT", "", "default");
  auto canvas_def_drawer_408 = mRoot::draw_hists_FCC(drawer_408, output_path, "A_ptag_pfjets02_e_def_fcc.pdf", "#gamma-PF-Jet R=0.2 E [GeV]", "", "default");
  auto canvas_def_drawer_409 = mRoot::draw_hists_FCC(drawer_409, output_path, "A_ptag_pfjets02_pt_def_fcc.pdf", "#gamma-PF-Jet R=0.2 p_{T} [GeV]", "", "default");
  auto canvas_def_drawer_410 = mRoot::draw_hists_FCC(drawer_410, output_path, "A_ptag_pfjets02_m_def_fcc.pdf", "#gamma-PF-Jet R=0.2 M [GeV]", "", "default");
  auto canvas_def_drawer_411 = mRoot::draw_hists_FCC(drawer_411, output_path, "A_ptag_pfjets04_e_def_fcc.pdf", "#gamma-PF-Jet R=0.4 E [GeV]", "", "default");
  auto canvas_def_drawer_412 = mRoot::draw_hists_FCC(drawer_412, output_path, "A_ptag_pfjets04_pt_def_fcc.pdf", "#gamma-PF-Jet R=0.4 p_{T} [GeV]", "", "default");
  auto canvas_def_drawer_413 = mRoot::draw_hists_FCC(drawer_413, output_path, "A_ptag_pfjets04_m_def_fcc.pdf", "#gamma-PF-Jet R=0.4 M [GeV]", "", "default");
  auto canvas_def_drawer_414 = mRoot::draw_hists_FCC(drawer_414, output_path, "A_ptag_pfjets08_e_def_fcc.pdf", "#gamma-PF-Jet R=0.8 E [GeV]", "", "default");
  auto canvas_def_drawer_415 = mRoot::draw_hists_FCC(drawer_415, output_path, "A_ptag_pfjets08_pt_def_fcc.pdf", "#gamma-PF-Jet R=0.8 p_{T} [GeV]", "", "default");
  auto canvas_def_drawer_416 = mRoot::draw_hists_FCC(drawer_416, output_path, "A_ptag_pfjets08_m_def_fcc.pdf", "#gamma-PF-Jet R=0.8 M [GeV]", "", "default");
  auto canvas_def_drawer_417 = mRoot::draw_hists_FCC(drawer_417, output_path, "A_btag_pfjets02_e_def_fcc.pdf", "b-PF-Jet R=0.2 E [GeV]", "", "default");
  auto canvas_def_drawer_418 = mRoot::draw_hists_FCC(drawer_418, output_path, "A_btag_pfjets02_pt_def_fcc.pdf", "b-PF-Jet R=0.2 p_{T} [GeV]", "", "default");
  auto canvas_def_drawer_419 = mRoot::draw_hists_FCC(drawer_419, output_path, "A_btag_pfjets02_m_def_fcc.pdf", "b-PF-Jet R=0.2 M [GeV]", "", "default");
  auto canvas_def_drawer_420 = mRoot::draw_hists_FCC(drawer_420, output_path, "A_btag_pfjets04_e_def_fcc.pdf", "b-PF-Jet R=0.4 E [GeV]", "", "default");
  auto canvas_def_drawer_421 = mRoot::draw_hists_FCC(drawer_421, output_path, "A_btag_pfjets04_pt_def_fcc.pdf", "b-PF-Jet R=0.4 p_{T} [GeV]", "", "default");
  auto canvas_def_drawer_422 = mRoot::draw_hists_FCC(drawer_422, output_path, "A_btag_pfjets04_m_def_fcc.pdf", "b-PF-Jet R=0.4 M [GeV]", "", "default");
  auto canvas_def_drawer_423 = mRoot::draw_hists_FCC(drawer_423, output_path, "A_btag_pfjets08_e_def_fcc.pdf", "b-PF-Jet R=0.8 E [GeV]", "", "default");
  auto canvas_def_drawer_424 = mRoot::draw_hists_FCC(drawer_424, output_path, "A_btag_pfjets08_pt_def_fcc.pdf", "b-PF-Jet R=0.8 p_{T} [GeV]", "", "default");
  auto canvas_def_drawer_425 = mRoot::draw_hists_FCC(drawer_425, output_path, "A_btag_pfjets08_m_def_fcc.pdf", "b-PF-Jet R=0.8 M [GeV]", "", "default");
  auto canvas_def_drawer_426 = mRoot::draw_hists_FCC(drawer_426, output_path, "A_BestMass_jet_e_def_fcc.pdf", "Best t-Mass_{j+#gamma} PF-Jet R=0.t E [GeV]", "", "default");
  auto canvas_def_drawer_427 = mRoot::draw_hists_FCC(drawer_427, output_path, "A_BestMass_jet_pt_def_fcc.pdf", "Best t-Mass_{j+#gamma} PF-Jet R=0.t p_{T} [GeV]", "", "default");
  auto canvas_def_drawer_428 = mRoot::draw_hists_FCC(drawer_428, output_path, "A_BestMass_jet_m_def_fcc.pdf", "Best t-Mass_{j+#gamma} PF-Jet R=0.t M [GeV]", "", "default");
  auto canvas_def_drawer_429 = mRoot::draw_hists_FCC(drawer_429, output_path, "A_BestTopMass_jet_e_def_fcc.pdf", "Best t-jet candidate PF-Jet R=0.8 E [GeV]", "", "default");
  auto canvas_def_drawer_430 = mRoot::draw_hists_FCC(drawer_430, output_path, "A_BestTopMass_jet_pt_def_fcc.pdf", "Best t-jet candidate PF-Jet R=0.8 p_{T} [GeV]", "", "default");
  auto canvas_def_drawer_431 = mRoot::draw_hists_FCC(drawer_431, output_path, "A_BestTopMass_jet_m_def_fcc.pdf", "Best t-jet candidate PF-Jet R=0.8 M [GeV]", "", "default");
  auto canvas_def_drawer_432 = mRoot::draw_hists_FCC(drawer_432, output_path, "A_SecondTopMass_jet_e_def_fcc.pdf", "Second t-jet candidate PF-Jet R=0.8 E [GeV]", "", "default");
  auto canvas_def_drawer_433 = mRoot::draw_hists_FCC(drawer_433, output_path, "A_SecondTopMass_jet_pt_def_fcc.pdf", "Second t-jet candidate PF-Jet R=0.8 p_{T} [GeV]", "", "default");
  auto canvas_def_drawer_434 = mRoot::draw_hists_FCC(drawer_434, output_path, "A_SecondTopMass_jet_m_def_fcc.pdf", "Second t-jet candidate PF-Jet R=0.8 M [GeV]", "", "default");
  auto canvas_def_drawer_435 = mRoot::draw_hists_FCC(drawer_435, output_path, "A_ptag_pfjets02_softDroppedJet_pt_def_fcc.pdf", "Soft-dropped #gamma-jet (R=0.2) Pt [GeV]", "", "default");
  auto canvas_def_drawer_436 = mRoot::draw_hists_FCC(drawer_436, output_path, "A_ptag_pfjets02_softDroppedJet_m_def_fcc.pdf", "Soft-dropped #gamma-jet (R=0.2) M [GeV]", "", "default");
  auto canvas_def_drawer_437 = mRoot::draw_hists_FCC(drawer_437, output_path, "A_ptag_pfjets02_softDroppedJet_e_def_fcc.pdf", "Soft-dropped #gamma-jet (R=0.2) E [GeV]", "", "default");
  auto canvas_def_drawer_438 = mRoot::draw_hists_FCC(drawer_438, output_path, "A_ptag_pfjets02_leadingSoftDroppedSubJet_pt_def_fcc.pdf", "Leading #gamma-Subjet (R=0.2) Pt [GeV]", "", "default");
  auto canvas_def_drawer_439 = mRoot::draw_hists_FCC(drawer_439, output_path, "A_ptag_pfjets02_leadingSoftDroppedSubJet_m_def_fcc.pdf", "Leading #gamma-Subjet (R=0.2) M [GeV]", "", "default");
  auto canvas_def_drawer_440 = mRoot::draw_hists_FCC(drawer_440, output_path, "A_ptag_pfjets02_leadingSoftDroppedSubJet_e_def_fcc.pdf", "Leading #gamma-Subjet (R=0.2) E [GeV]", "", "default");
  auto canvas_def_drawer_441 = mRoot::draw_hists_FCC(drawer_441, output_path, "A_ptag_pfjets02_trailingSoftDroppedSubJet_pt_def_fcc.pdf", "Trailing #gamma-Subjet (R=0.2) Pt [GeV]", "", "default");
  auto canvas_def_drawer_442 = mRoot::draw_hists_FCC(drawer_442, output_path, "A_ptag_pfjets02_trailingSoftDroppedSubJet_m_def_fcc.pdf", "Trailing #gamma-Subjet (R=0.2) M [GeV]", "", "default");
  auto canvas_def_drawer_443 = mRoot::draw_hists_FCC(drawer_443, output_path, "A_ptag_pfjets02_trailingSoftDroppedSubJet_e_def_fcc.pdf", "Trailing #gamma-Subjet (R=0.2) E [GeV]", "", "default");
  auto canvas_def_drawer_444 = mRoot::draw_hists_FCC(drawer_444, output_path, "A_ptag_pfjets04_softDroppedJet_pt_def_fcc.pdf", "Soft-dropped #gamma-jet (R=0.4) Pt [GeV]", "", "default");
  auto canvas_def_drawer_445 = mRoot::draw_hists_FCC(drawer_445, output_path, "A_ptag_pfjets04_softDroppedJet_m_def_fcc.pdf", "Soft-dropped #gamma-jet (R=0.4) M [GeV]", "", "default");
  auto canvas_def_drawer_446 = mRoot::draw_hists_FCC(drawer_446, output_path, "A_ptag_pfjets04_softDroppedJet_e_def_fcc.pdf", "Soft-dropped #gamma-jet (R=0.4) E [GeV]", "", "default");
  auto canvas_def_drawer_447 = mRoot::draw_hists_FCC(drawer_447, output_path, "A_ptag_pfjets04_leadingSoftDroppedSubJet_pt_def_fcc.pdf", "Leading #gamma-Subjet (R=0.4) Pt [GeV]", "", "default");
  auto canvas_def_drawer_448 = mRoot::draw_hists_FCC(drawer_448, output_path, "A_ptag_pfjets04_leadingSoftDroppedSubJet_m_def_fcc.pdf", "Leading #gamma-Subjet (R=0.4) M [GeV]", "", "default");
  auto canvas_def_drawer_449 = mRoot::draw_hists_FCC(drawer_449, output_path, "A_ptag_pfjets04_leadingSoftDroppedSubJet_e_def_fcc.pdf", "Leading #gamma-Subjet (R=0.4) E [GeV]", "", "default");
  auto canvas_def_drawer_450 = mRoot::draw_hists_FCC(drawer_450, output_path, "A_ptag_pfjets04_trailingSoftDroppedSubJet_pt_def_fcc.pdf", "Trailing #gamma-Subjet (R=0.4) Pt [GeV]", "", "default");
  auto canvas_def_drawer_451 = mRoot::draw_hists_FCC(drawer_451, output_path, "A_ptag_pfjets04_trailingSoftDroppedSubJet_m_def_fcc.pdf", "Trailing #gamma-Subjet (R=0.4) M [GeV]", "", "default");
  auto canvas_def_drawer_452 = mRoot::draw_hists_FCC(drawer_452, output_path, "A_ptag_pfjets04_trailingSoftDroppedSubJet_e_def_fcc.pdf", "Trailing #gamma-Subjet (R=0.4) E [GeV]", "", "default");
  auto canvas_def_drawer_453 = mRoot::draw_hists_FCC(drawer_453, output_path, "A_ptag_pfjets08_softDroppedJet_pt_def_fcc.pdf", "Soft-dropped #gamma-jet (R=0.8) Pt [GeV]", "", "default");
  auto canvas_def_drawer_454 = mRoot::draw_hists_FCC(drawer_454, output_path, "A_ptag_pfjets08_softDroppedJet_m_def_fcc.pdf", "Soft-dropped #gamma-jet (R=0.8) M [GeV]", "", "default");
  auto canvas_def_drawer_455 = mRoot::draw_hists_FCC(drawer_455, output_path, "A_ptag_pfjets08_softDroppedJet_e_def_fcc.pdf", "Soft-dropped #gamma-jet (R=0.8) E [GeV]", "", "default");
  auto canvas_def_drawer_456 = mRoot::draw_hists_FCC(drawer_456, output_path, "A_ptag_pfjets08_leadingSoftDroppedSubJet_pt_def_fcc.pdf", "Leading #gamma-Subjet (R=0.8) Pt [GeV]", "", "default");
  auto canvas_def_drawer_457 = mRoot::draw_hists_FCC(drawer_457, output_path, "A_ptag_pfjets08_leadingSoftDroppedSubJet_m_def_fcc.pdf", "Leading #gamma-Subjet (R=0.8) M [GeV]", "", "default");
  auto canvas_def_drawer_458 = mRoot::draw_hists_FCC(drawer_458, output_path, "A_ptag_pfjets08_leadingSoftDroppedSubJet_e_def_fcc.pdf", "Leading #gamma-Subjet (R=0.8) E [GeV]", "", "default");
  auto canvas_def_drawer_459 = mRoot::draw_hists_FCC(drawer_459, output_path, "A_ptag_pfjets08_trailingSoftDroppedSubJet_pt_def_fcc.pdf", "Trailing #gamma-Subjet (R=0.8) Pt [GeV]", "", "default");
  auto canvas_def_drawer_460 = mRoot::draw_hists_FCC(drawer_460, output_path, "A_ptag_pfjets08_trailingSoftDroppedSubJet_m_def_fcc.pdf", "Trailing #gamma-Subjet (R=0.8) M [GeV]", "", "default");
  auto canvas_def_drawer_461 = mRoot::draw_hists_FCC(drawer_461, output_path, "A_ptag_pfjets08_trailingSoftDroppedSubJet_e_def_fcc.pdf", "Trailing #gamma-Subjet (R=0.8) E [GeV]", "", "default");
  auto canvas_def_drawer_462 = mRoot::draw_hists_FCC(drawer_462, output_path, "A_btag_pfjets02_softDroppedJet_pt_def_fcc.pdf", "Soft-dropped b-jet (R=0.2) Pt [GeV]", "", "default");
  auto canvas_def_drawer_463 = mRoot::draw_hists_FCC(drawer_463, output_path, "A_btag_pfjets02_softDroppedJet_m_def_fcc.pdf", "Soft-dropped b-jet (R=0.2) M [GeV]", "", "default");
  auto canvas_def_drawer_464 = mRoot::draw_hists_FCC(drawer_464, output_path, "A_btag_pfjets02_softDroppedJet_e_def_fcc.pdf", "Soft-dropped b-jet (R=0.2) E [GeV]", "", "default");
  auto canvas_def_drawer_465 = mRoot::draw_hists_FCC(drawer_465, output_path, "A_btag_pfjets02_leadingSoftDroppedSubJet_pt_def_fcc.pdf", "Leading b-Subjet (R=0.2) Pt [GeV]", "", "default");
  auto canvas_def_drawer_466 = mRoot::draw_hists_FCC(drawer_466, output_path, "A_btag_pfjets02_leadingSoftDroppedSubJet_m_def_fcc.pdf", "Leading b-Subjet (R=0.2) M [GeV]", "", "default");
  auto canvas_def_drawer_467 = mRoot::draw_hists_FCC(drawer_467, output_path, "A_btag_pfjets02_leadingSoftDroppedSubJet_e_def_fcc.pdf", "Leading b-Subjet (R=0.2) E [GeV]", "", "default");
  auto canvas_def_drawer_468 = mRoot::draw_hists_FCC(drawer_468, output_path, "A_btag_pfjets02_trailingSoftDroppedSubJet_pt_def_fcc.pdf", "Trailing b-Subjet (R=0.2) Pt [GeV]", "", "default");
  auto canvas_def_drawer_469 = mRoot::draw_hists_FCC(drawer_469, output_path, "A_btag_pfjets02_trailingSoftDroppedSubJet_m_def_fcc.pdf", "Trailing b-Subjet (R=0.2) M [GeV]", "", "default");
  auto canvas_def_drawer_470 = mRoot::draw_hists_FCC(drawer_470, output_path, "A_btag_pfjets02_trailingSoftDroppedSubJet_e_def_fcc.pdf", "Trailing b-Subjet (R=0.2) E [GeV]", "", "default");
  auto canvas_def_drawer_471 = mRoot::draw_hists_FCC(drawer_471, output_path, "A_btag_pfjets04_softDroppedJet_pt_def_fcc.pdf", "Soft-dropped b-jet (R=0.4) Pt [GeV]", "", "default");
  auto canvas_def_drawer_472 = mRoot::draw_hists_FCC(drawer_472, output_path, "A_btag_pfjets04_softDroppedJet_m_def_fcc.pdf", "Soft-dropped b-jet (R=0.4) M [GeV]", "", "default");
  auto canvas_def_drawer_473 = mRoot::draw_hists_FCC(drawer_473, output_path, "A_btag_pfjets04_softDroppedJet_e_def_fcc.pdf", "Soft-dropped b-jet (R=0.4) E [GeV]", "", "default");
  auto canvas_def_drawer_474 = mRoot::draw_hists_FCC(drawer_474, output_path, "A_btag_pfjets04_leadingSoftDroppedSubJet_pt_def_fcc.pdf", "Leading b-Subjet (R=0.4) Pt [GeV]", "", "default");
  auto canvas_def_drawer_475 = mRoot::draw_hists_FCC(drawer_475, output_path, "A_btag_pfjets04_leadingSoftDroppedSubJet_m_def_fcc.pdf", "Leading b-Subjet (R=0.4) M [GeV]", "", "default");
  auto canvas_def_drawer_476 = mRoot::draw_hists_FCC(drawer_476, output_path, "A_btag_pfjets04_leadingSoftDroppedSubJet_e_def_fcc.pdf", "Leading b-Subjet (R=0.4) E [GeV]", "", "default");
  auto canvas_def_drawer_477 = mRoot::draw_hists_FCC(drawer_477, output_path, "A_btag_pfjets04_trailingSoftDroppedSubJet_pt_def_fcc.pdf", "Trailing b-Subjet (R=0.4) Pt [GeV]", "", "default");
  auto canvas_def_drawer_478 = mRoot::draw_hists_FCC(drawer_478, output_path, "A_btag_pfjets04_trailingSoftDroppedSubJet_m_def_fcc.pdf", "Trailing b-Subjet (R=0.4) M [GeV]", "", "default");
  auto canvas_def_drawer_479 = mRoot::draw_hists_FCC(drawer_479, output_path, "A_btag_pfjets04_trailingSoftDroppedSubJet_e_def_fcc.pdf", "Trailing b-Subjet (R=0.4) E [GeV]", "", "default");
  auto canvas_def_drawer_480 = mRoot::draw_hists_FCC(drawer_480, output_path, "A_btag_pfjets08_softDroppedJet_pt_def_fcc.pdf", "Soft-dropped b-jet (R=0.8) Pt [GeV]", "", "default");
  auto canvas_def_drawer_481 = mRoot::draw_hists_FCC(drawer_481, output_path, "A_btag_pfjets08_softDroppedJet_m_def_fcc.pdf", "Soft-dropped b-jet (R=0.8) M [GeV]", "", "default");
  auto canvas_def_drawer_482 = mRoot::draw_hists_FCC(drawer_482, output_path, "A_btag_pfjets08_softDroppedJet_e_def_fcc.pdf", "Soft-dropped b-jet (R=0.8) E [GeV]", "", "default");
  auto canvas_def_drawer_483 = mRoot::draw_hists_FCC(drawer_483, output_path, "A_btag_pfjets08_leadingSoftDroppedSubJet_pt_def_fcc.pdf", "Leading b-Subjet (R=0.8) Pt [GeV]", "", "default");
  auto canvas_def_drawer_484 = mRoot::draw_hists_FCC(drawer_484, output_path, "A_btag_pfjets08_leadingSoftDroppedSubJet_m_def_fcc.pdf", "Leading b-Subjet (R=0.8) M [GeV]", "", "default");
  auto canvas_def_drawer_485 = mRoot::draw_hists_FCC(drawer_485, output_path, "A_btag_pfjets08_leadingSoftDroppedSubJet_e_def_fcc.pdf", "Leading b-Subjet (R=0.8) E [GeV]", "", "default");
  auto canvas_def_drawer_486 = mRoot::draw_hists_FCC(drawer_486, output_path, "A_btag_pfjets08_trailingSoftDroppedSubJet_pt_def_fcc.pdf", "Trailing b-Subjet (R=0.8) Pt [GeV]", "", "default");
  auto canvas_def_drawer_487 = mRoot::draw_hists_FCC(drawer_487, output_path, "A_btag_pfjets08_trailingSoftDroppedSubJet_m_def_fcc.pdf", "Trailing b-Subjet (R=0.8) M [GeV]", "", "default");
  auto canvas_def_drawer_488 = mRoot::draw_hists_FCC(drawer_488, output_path, "A_btag_pfjets08_trailingSoftDroppedSubJet_e_def_fcc.pdf", "Trailing b-Subjet (R=0.8) E [GeV]", "", "default");
  auto canvas_def_drawer_489 = mRoot::draw_hists_FCC(drawer_489, output_path, "A_dPhi_Photon_ptag_pfjets04_def_fcc.pdf", "#Delta #phi(#gamma, #gamma-PF-Jet R=0.4 )", "", "default");
  auto canvas_def_drawer_490 = mRoot::draw_hists_FCC(drawer_490, output_path, "A_dR_Photon_ptag_pfjets04_def_fcc.pdf", "#Delta R(#gamma, #gamma-PF-Jet R=0.4 )", "", "default");
  auto canvas_def_drawer_491 = mRoot::draw_hists_FCC(drawer_491, output_path, "A_M_Photon_ptag_pfjets04_def_fcc.pdf", "M(#gamma, #gamma-PF-Jet R=0.4 )", "", "default");
  auto canvas_def_drawer_492 = mRoot::draw_hists_FCC(drawer_492, output_path, "A_dPhi_bjet_ptag_pfjets04_def_fcc.pdf", "#Delta #phi(b-jet, #gamma-PF-Jet R=0.4 )", "", "default");
  auto canvas_def_drawer_493 = mRoot::draw_hists_FCC(drawer_493, output_path, "A_dR_bjet_ptag_pfjets04_def_fcc.pdf", "#Delta R(b-jet)", "", "default");
  auto canvas_tmva_drawer_494 = mRoot::draw_hists_FCC(drawer_494, output_path, "B_photon_eta_tmva_fcc.pdf", "Photon #eta", "", "tmva");
  auto canvas_tmva_drawer_495 = mRoot::draw_hists_FCC(drawer_495, output_path, "B_photon_pt_tmva_fcc.pdf", "Photon p_{T} [GeV]", "", "tmva");
  auto canvas_tmva_drawer_496 = mRoot::draw_hists_FCC(drawer_496, output_path, "B_top_pt_tmva_fcc.pdf", "t p_{T} [GeV]", "", "tmva");
  auto canvas_tmva_drawer_497 = mRoot::draw_hists_FCC(drawer_497, output_path, "B_ptag_bestJet_m_tmva_fcc.pdf", "Best #gamma-jet M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_498 = mRoot::draw_hists_FCC(drawer_498, output_path, "B_ptag_bestJet_pt_tmva_fcc.pdf", "Best #gamma-jet p_{T} [GeV]", "", "tmva");
  auto canvas_tmva_drawer_499 = mRoot::draw_hists_FCC(drawer_499, output_path, "B_ptag_bestJet_eta_tmva_fcc.pdf", "Best #gamma-jet #eta", "", "tmva");
  auto canvas_tmva_drawer_500 = mRoot::draw_hists_FCC(drawer_500, output_path, "B_btag_pfjets04_eta_tmva_fcc.pdf", "b-jet #eta", "", "tmva");
  auto canvas_tmva_drawer_501 = mRoot::draw_hists_FCC(drawer_501, output_path, "B_ptag_bestJet_tau1_tmva_fcc.pdf", "best #gamma-jet #tau_{1}", "", "tmva");
  auto canvas_tmva_drawer_502 = mRoot::draw_hists_FCC(drawer_502, output_path, "B_ptag_bestJet_tau2_tmva_fcc.pdf", "best #gamma-jet #tau_{2}", "", "tmva");
  auto canvas_tmva_drawer_503 = mRoot::draw_hists_FCC(drawer_503, output_path, "B_ptag_bestJet_tau3_tmva_fcc.pdf", "best #gamma-jet #tau_{3}", "", "tmva");
  auto canvas_tmva_drawer_504 = mRoot::draw_hists_FCC(drawer_504, output_path, "B_ptag_bestJet_tau31_tmva_fcc.pdf", "best #gamma-jet #tau_{31}", "", "tmva");
  auto canvas_tmva_drawer_505 = mRoot::draw_hists_FCC(drawer_505, output_path, "B_ptag_bestJet_tau32_tmva_fcc.pdf", "best #gamma-jet #tau_{32}", "", "tmva");
  auto canvas_tmva_drawer_506 = mRoot::draw_hists_FCC(drawer_506, output_path, "B_ptag_bestJet_tau21_tmva_fcc.pdf", "best #gamma-jet #tau_{21}", "", "tmva");
  auto canvas_tmva_drawer_507 = mRoot::draw_hists_FCC(drawer_507, output_path, "B_ptag_pfjets08_tau1_tmva_fcc.pdf", "#gamma-PF-jet R=0.8 #tau_{1}", "", "tmva");
  auto canvas_tmva_drawer_508 = mRoot::draw_hists_FCC(drawer_508, output_path, "B_ptag_pfjets08_tau2_tmva_fcc.pdf", "#gamma-PF-jet R=0.8 #tau_{2}", "", "tmva");
  auto canvas_tmva_drawer_509 = mRoot::draw_hists_FCC(drawer_509, output_path, "B_ptag_pfjets08_tau3_tmva_fcc.pdf", "#gamma-PF-jet R=0.8 #tau_{3}", "", "tmva");
  auto canvas_tmva_drawer_510 = mRoot::draw_hists_FCC(drawer_510, output_path, "B_ptag_pfjets08_tau31_tmva_fcc.pdf", "#gamma-PF-jet R=0.8 #tau_{31}", "", "tmva");
  auto canvas_tmva_drawer_511 = mRoot::draw_hists_FCC(drawer_511, output_path, "B_ptag_pfjets08_tau32_tmva_fcc.pdf", "#gamma-PF-jet R=0.8 #tau_{32}", "", "tmva");
  auto canvas_tmva_drawer_512 = mRoot::draw_hists_FCC(drawer_512, output_path, "B_ptag_pfjets08_tau21_tmva_fcc.pdf", "#gamma-PF-jet R=0.8 #tau_{21}", "", "tmva");
  auto canvas_tmva_drawer_513 = mRoot::draw_hists_FCC(drawer_513, output_path, "B_btag_pfjets08_tau1_tmva_fcc.pdf", "b-PF-jet R=0.8 #tau_{1}", "", "tmva");
  auto canvas_tmva_drawer_514 = mRoot::draw_hists_FCC(drawer_514, output_path, "B_btag_pfjets08_tau2_tmva_fcc.pdf", "b-PF-jet R=0.8 #tau_{2}", "", "tmva");
  auto canvas_tmva_drawer_515 = mRoot::draw_hists_FCC(drawer_515, output_path, "B_btag_pfjets08_tau3_tmva_fcc.pdf", "b-PF-jet R=0.8 #tau_{3}", "", "tmva");
  auto canvas_tmva_drawer_516 = mRoot::draw_hists_FCC(drawer_516, output_path, "B_btag_pfjets08_tau31_tmva_fcc.pdf", "b-PF-jet R=0.8 #tau_{31}", "", "tmva");
  auto canvas_tmva_drawer_517 = mRoot::draw_hists_FCC(drawer_517, output_path, "B_btag_pfjets08_tau32_tmva_fcc.pdf", "b-PF-jet R=0.8 #tau_{32}", "", "tmva");
  auto canvas_tmva_drawer_518 = mRoot::draw_hists_FCC(drawer_518, output_path, "B_btag_pfjets08_tau21_tmva_fcc.pdf", "b-PF-jet R=0.8 #tau_{21}", "", "tmva");
  auto canvas_tmva_drawer_519 = mRoot::draw_hists_FCC(drawer_519, output_path, "B_btag_pfjets04_tau1_tmva_fcc.pdf", "b-PF-jet R=0.4 #tau_{1}", "", "tmva");
  auto canvas_tmva_drawer_520 = mRoot::draw_hists_FCC(drawer_520, output_path, "B_btag_pfjets04_tau2_tmva_fcc.pdf", "b-PF-jet R=0.4 #tau_{2}", "", "tmva");
  auto canvas_tmva_drawer_521 = mRoot::draw_hists_FCC(drawer_521, output_path, "B_btag_pfjets04_tau3_tmva_fcc.pdf", "b-PF-jet R=0.4 #tau_{3}", "", "tmva");
  auto canvas_tmva_drawer_522 = mRoot::draw_hists_FCC(drawer_522, output_path, "B_btag_pfjets04_tau31_tmva_fcc.pdf", "b-PF-jet R=0.4 #tau_{31}", "", "tmva");
  auto canvas_tmva_drawer_523 = mRoot::draw_hists_FCC(drawer_523, output_path, "B_btag_pfjets04_tau32_tmva_fcc.pdf", "b-PF-jet R=0.4 #tau_{32}", "", "tmva");
  auto canvas_tmva_drawer_524 = mRoot::draw_hists_FCC(drawer_524, output_path, "B_btag_pfjets04_tau21_tmva_fcc.pdf", "b-PF-jet R=0.4 #tau_{21}", "", "tmva");
  auto canvas_tmva_drawer_525 = mRoot::draw_hists_FCC(drawer_525, output_path, "B_photon_x_ptag_bestJet_tmva_fcc.pdf", "(P_{#gamma}, P_{best j#gamma-et}) [GeV^{2}]", "", "tmva");
  auto canvas_tmva_drawer_526 = mRoot::draw_hists_FCC(drawer_526, output_path, "B_lepton_x_btag_pfjets08_tmva_fcc.pdf", "(P_{lepton}, P_{b-PF-jet R=0.8}) [GeV^{2}]", "", "tmva");
  auto canvas_tmva_drawer_527 = mRoot::draw_hists_FCC(drawer_527, output_path, "B_dPhi_lepton_btag_pfjets08_tmva_fcc.pdf", "#Delta #phi(lepton, b-PF-jet R=0.8)", "", "tmva");
  auto canvas_tmva_drawer_528 = mRoot::draw_hists_FCC(drawer_528, output_path, "B_dR_lepton_btag_pfjets08_tmva_fcc.pdf", "#Delta R(lepton, b-PF-jet R=0.8)", "", "tmva");
  auto canvas_tmva_drawer_529 = mRoot::draw_hists_FCC(drawer_529, output_path, "B_lepton_x_btag_pfjets04_tmva_fcc.pdf", "(P_{lepton}, P_{b-PF-jet R=0.4}) [GeV^{2}]", "", "tmva");
  auto canvas_tmva_drawer_530 = mRoot::draw_hists_FCC(drawer_530, output_path, "B_dPhi_lepton_btag_pfjets04_tmva_fcc.pdf", "#Delta #phi(lepton, b-PF-jet R=0.4)", "", "tmva");
  auto canvas_tmva_drawer_531 = mRoot::draw_hists_FCC(drawer_531, output_path, "B_dR_lepton_btag_pfjets04_tmva_fcc.pdf", "#Delta R(lepton, b-PF-jet R=0.4)", "", "tmva");
  auto canvas_tmva_drawer_532 = mRoot::draw_hists_FCC(drawer_532, output_path, "B_M_lepton_met_tmva_fcc.pdf", "M(lepton, MET) [GeV]", "", "tmva");
  auto canvas_tmva_drawer_533 = mRoot::draw_hists_FCC(drawer_533, output_path, "B_M_bjet_lepton_met_tmva_fcc.pdf", "M(lepton, MET, b-PF-jet R=0.4) [GeV]", "", "tmva");
  auto canvas_tmva_drawer_534 = mRoot::draw_hists_FCC(drawer_534, output_path, "B_dPhi_Photon_ptag_bestJet_tmva_fcc.pdf", "#Delta #phi(#gamma, best #gamma-jet)", "", "tmva");
  auto canvas_tmva_drawer_535 = mRoot::draw_hists_FCC(drawer_535, output_path, "B_dR_Photon_ptag_bestJet_tmva_fcc.pdf", "#Delta R(#gamma, best #gamma-jet)", "", "tmva");
  auto canvas_tmva_drawer_536 = mRoot::draw_hists_FCC(drawer_536, output_path, "B_M_Photon_ptag_bestJet_tmva_fcc.pdf", "M(#gamma, best #gamma-jet)", "", "tmva");
  auto canvas_tmva_drawer_537 = mRoot::draw_hists_FCC(drawer_537, output_path, "B_bjet_x_ptag_bestJet_tmva_fcc.pdf", "(P_{b-jet}, P_{best #gamma-jet}) [GeV^{2}]", "", "tmva");
  auto canvas_tmva_drawer_538 = mRoot::draw_hists_FCC(drawer_538, output_path, "B_dPhi_bjet_ptag_bestJet_tmva_fcc.pdf", "#Delta #phi(b-jet, best #gamma-jet)", "", "tmva");
  auto canvas_tmva_drawer_539 = mRoot::draw_hists_FCC(drawer_539, output_path, "B_dR_bjet_ptag_bestJet_tmva_fcc.pdf", "#Delta R(b-jet, best #gamma-jet)", "", "tmva");
  auto canvas_tmva_drawer_540 = mRoot::draw_hists_FCC(drawer_540, output_path, "B_lepton_relIso_tmva_fcc.pdf", "lepton relative isolation", "", "tmva");
  auto canvas_tmva_drawer_541 = mRoot::draw_hists_FCC(drawer_541, output_path, "B_photon_relIso_tmva_fcc.pdf", "#gamma relative isolation", "", "tmva");
  auto canvas_tmva_drawer_542 = mRoot::draw_hists_FCC(drawer_542, output_path, "B_photon_x_ptag_pfjets08_tmva_fcc.pdf", "(P_{#gamma-jet}, P_{#gamma-jet}) [GeV^{2}]", "", "tmva");
  auto canvas_tmva_drawer_543 = mRoot::draw_hists_FCC(drawer_543, output_path, "B_bjet_x_ptag_pfjets08_tmva_fcc.pdf", "(P_{b-jet}, P_{#gamma-jet}) [GeV^{2}]", "", "tmva");
  auto canvas_tmva_drawer_544 = mRoot::draw_hists_FCC(drawer_544, output_path, "B_weight_tune_3_BDT_0_000_tmva_fcc.pdf", "BDT", "", "tmva");
  auto canvas_tmva_drawer_545 = mRoot::draw_hists_FCC(drawer_545, output_path, "B_weight_tune_3_BDT_1_000_tmva_fcc.pdf", "BDT", "", "tmva");
  auto canvas_tmva_drawer_546 = mRoot::draw_hists_FCC(drawer_546, output_path, "B_weight_tune_3_BDT_2_000_tmva_fcc.pdf", "BDT", "", "tmva");
  auto canvas_tmva_drawer_547 = mRoot::draw_hists_FCC(drawer_547, output_path, "B_weight_tune_3_BDT_3_000_tmva_fcc.pdf", "BDT", "", "tmva");
  auto canvas_tmva_drawer_548 = mRoot::draw_hists_FCC(drawer_548, output_path, "B_weight_tune_3_BDT_4_000_tmva_fcc.pdf", "BDT", "", "tmva");
  auto canvas_tmva_drawer_549 = mRoot::draw_hists_FCC(drawer_549, output_path, "B_weight_tune_3_BDT_5_000_tmva_fcc.pdf", "BDT", "", "tmva");
  auto canvas_tmva_drawer_550 = mRoot::draw_hists_FCC(drawer_550, output_path, "B_weight_tune_3_BDT_6_000_tmva_fcc.pdf", "BDT", "", "tmva");
  auto canvas_tmva_drawer_551 = mRoot::draw_hists_FCC(drawer_551, output_path, "B_weight_tune_5_BDT_3_000_tmva_fcc.pdf", "BDT", "", "tmva");
  auto canvas_tmva_drawer_552 = mRoot::draw_hists_FCC(drawer_552, output_path, "B_ptag_pfjets02_e_tmva_fcc.pdf", "#gamma-PF-Jet R=0.2 E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_553 = mRoot::draw_hists_FCC(drawer_553, output_path, "B_ptag_pfjets02_pt_tmva_fcc.pdf", "#gamma-PF-Jet R=0.2 p_{T} [GeV]", "", "tmva");
  auto canvas_tmva_drawer_554 = mRoot::draw_hists_FCC(drawer_554, output_path, "B_ptag_pfjets02_m_tmva_fcc.pdf", "#gamma-PF-Jet R=0.2 M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_555 = mRoot::draw_hists_FCC(drawer_555, output_path, "B_ptag_pfjets04_e_tmva_fcc.pdf", "#gamma-PF-Jet R=0.4 E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_556 = mRoot::draw_hists_FCC(drawer_556, output_path, "B_ptag_pfjets04_pt_tmva_fcc.pdf", "#gamma-PF-Jet R=0.4 p_{T} [GeV]", "", "tmva");
  auto canvas_tmva_drawer_557 = mRoot::draw_hists_FCC(drawer_557, output_path, "B_ptag_pfjets04_m_tmva_fcc.pdf", "#gamma-PF-Jet R=0.4 M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_558 = mRoot::draw_hists_FCC(drawer_558, output_path, "B_ptag_pfjets08_e_tmva_fcc.pdf", "#gamma-PF-Jet R=0.8 E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_559 = mRoot::draw_hists_FCC(drawer_559, output_path, "B_ptag_pfjets08_pt_tmva_fcc.pdf", "#gamma-PF-Jet R=0.8 p_{T} [GeV]", "", "tmva");
  auto canvas_tmva_drawer_560 = mRoot::draw_hists_FCC(drawer_560, output_path, "B_ptag_pfjets08_m_tmva_fcc.pdf", "#gamma-PF-Jet R=0.8 M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_561 = mRoot::draw_hists_FCC(drawer_561, output_path, "B_btag_pfjets02_e_tmva_fcc.pdf", "b-PF-Jet R=0.2 E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_562 = mRoot::draw_hists_FCC(drawer_562, output_path, "B_btag_pfjets02_pt_tmva_fcc.pdf", "b-PF-Jet R=0.2 p_{T} [GeV]", "", "tmva");
  auto canvas_tmva_drawer_563 = mRoot::draw_hists_FCC(drawer_563, output_path, "B_btag_pfjets02_m_tmva_fcc.pdf", "b-PF-Jet R=0.2 M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_564 = mRoot::draw_hists_FCC(drawer_564, output_path, "B_btag_pfjets04_e_tmva_fcc.pdf", "b-PF-Jet R=0.4 E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_565 = mRoot::draw_hists_FCC(drawer_565, output_path, "B_btag_pfjets04_pt_tmva_fcc.pdf", "b-PF-Jet R=0.4 p_{T} [GeV]", "", "tmva");
  auto canvas_tmva_drawer_566 = mRoot::draw_hists_FCC(drawer_566, output_path, "B_btag_pfjets04_m_tmva_fcc.pdf", "b-PF-Jet R=0.4 M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_567 = mRoot::draw_hists_FCC(drawer_567, output_path, "B_btag_pfjets08_e_tmva_fcc.pdf", "b-PF-Jet R=0.8 E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_568 = mRoot::draw_hists_FCC(drawer_568, output_path, "B_btag_pfjets08_pt_tmva_fcc.pdf", "b-PF-Jet R=0.8 p_{T} [GeV]", "", "tmva");
  auto canvas_tmva_drawer_569 = mRoot::draw_hists_FCC(drawer_569, output_path, "B_btag_pfjets08_m_tmva_fcc.pdf", "b-PF-Jet R=0.8 M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_570 = mRoot::draw_hists_FCC(drawer_570, output_path, "B_BestMass_jet_e_tmva_fcc.pdf", "Best t-Mass_{j+#gamma} PF-Jet R=0.t E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_571 = mRoot::draw_hists_FCC(drawer_571, output_path, "B_BestMass_jet_pt_tmva_fcc.pdf", "Best t-Mass_{j+#gamma} PF-Jet R=0.t p_{T} [GeV]", "", "tmva");
  auto canvas_tmva_drawer_572 = mRoot::draw_hists_FCC(drawer_572, output_path, "B_BestMass_jet_m_tmva_fcc.pdf", "Best t-Mass_{j+#gamma} PF-Jet R=0.t M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_573 = mRoot::draw_hists_FCC(drawer_573, output_path, "B_BestTopMass_jet_e_tmva_fcc.pdf", "Best t-jet candidate PF-Jet R=0.8 E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_574 = mRoot::draw_hists_FCC(drawer_574, output_path, "B_BestTopMass_jet_pt_tmva_fcc.pdf", "Best t-jet candidate PF-Jet R=0.8 p_{T} [GeV]", "", "tmva");
  auto canvas_tmva_drawer_575 = mRoot::draw_hists_FCC(drawer_575, output_path, "B_BestTopMass_jet_m_tmva_fcc.pdf", "Best t-jet candidate PF-Jet R=0.8 M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_576 = mRoot::draw_hists_FCC(drawer_576, output_path, "B_SecondTopMass_jet_e_tmva_fcc.pdf", "Second t-jet candidate PF-Jet R=0.8 E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_577 = mRoot::draw_hists_FCC(drawer_577, output_path, "B_SecondTopMass_jet_pt_tmva_fcc.pdf", "Second t-jet candidate PF-Jet R=0.8 p_{T} [GeV]", "", "tmva");
  auto canvas_tmva_drawer_578 = mRoot::draw_hists_FCC(drawer_578, output_path, "B_SecondTopMass_jet_m_tmva_fcc.pdf", "Second t-jet candidate PF-Jet R=0.8 M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_579 = mRoot::draw_hists_FCC(drawer_579, output_path, "B_ptag_pfjets02_softDroppedJet_pt_tmva_fcc.pdf", "Soft-dropped #gamma-jet (R=0.2) Pt [GeV]", "", "tmva");
  auto canvas_tmva_drawer_580 = mRoot::draw_hists_FCC(drawer_580, output_path, "B_ptag_pfjets02_softDroppedJet_m_tmva_fcc.pdf", "Soft-dropped #gamma-jet (R=0.2) M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_581 = mRoot::draw_hists_FCC(drawer_581, output_path, "B_ptag_pfjets02_softDroppedJet_e_tmva_fcc.pdf", "Soft-dropped #gamma-jet (R=0.2) E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_582 = mRoot::draw_hists_FCC(drawer_582, output_path, "B_ptag_pfjets02_leadingSoftDroppedSubJet_pt_tmva_fcc.pdf", "Leading #gamma-Subjet (R=0.2) Pt [GeV]", "", "tmva");
  auto canvas_tmva_drawer_583 = mRoot::draw_hists_FCC(drawer_583, output_path, "B_ptag_pfjets02_leadingSoftDroppedSubJet_m_tmva_fcc.pdf", "Leading #gamma-Subjet (R=0.2) M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_584 = mRoot::draw_hists_FCC(drawer_584, output_path, "B_ptag_pfjets02_leadingSoftDroppedSubJet_e_tmva_fcc.pdf", "Leading #gamma-Subjet (R=0.2) E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_585 = mRoot::draw_hists_FCC(drawer_585, output_path, "B_ptag_pfjets02_trailingSoftDroppedSubJet_pt_tmva_fcc.pdf", "Trailing #gamma-Subjet (R=0.2) Pt [GeV]", "", "tmva");
  auto canvas_tmva_drawer_586 = mRoot::draw_hists_FCC(drawer_586, output_path, "B_ptag_pfjets02_trailingSoftDroppedSubJet_m_tmva_fcc.pdf", "Trailing #gamma-Subjet (R=0.2) M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_587 = mRoot::draw_hists_FCC(drawer_587, output_path, "B_ptag_pfjets02_trailingSoftDroppedSubJet_e_tmva_fcc.pdf", "Trailing #gamma-Subjet (R=0.2) E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_588 = mRoot::draw_hists_FCC(drawer_588, output_path, "B_ptag_pfjets04_softDroppedJet_pt_tmva_fcc.pdf", "Soft-dropped #gamma-jet (R=0.4) Pt [GeV]", "", "tmva");
  auto canvas_tmva_drawer_589 = mRoot::draw_hists_FCC(drawer_589, output_path, "B_ptag_pfjets04_softDroppedJet_m_tmva_fcc.pdf", "Soft-dropped #gamma-jet (R=0.4) M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_590 = mRoot::draw_hists_FCC(drawer_590, output_path, "B_ptag_pfjets04_softDroppedJet_e_tmva_fcc.pdf", "Soft-dropped #gamma-jet (R=0.4) E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_591 = mRoot::draw_hists_FCC(drawer_591, output_path, "B_ptag_pfjets04_leadingSoftDroppedSubJet_pt_tmva_fcc.pdf", "Leading #gamma-Subjet (R=0.4) Pt [GeV]", "", "tmva");
  auto canvas_tmva_drawer_592 = mRoot::draw_hists_FCC(drawer_592, output_path, "B_ptag_pfjets04_leadingSoftDroppedSubJet_m_tmva_fcc.pdf", "Leading #gamma-Subjet (R=0.4) M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_593 = mRoot::draw_hists_FCC(drawer_593, output_path, "B_ptag_pfjets04_leadingSoftDroppedSubJet_e_tmva_fcc.pdf", "Leading #gamma-Subjet (R=0.4) E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_594 = mRoot::draw_hists_FCC(drawer_594, output_path, "B_ptag_pfjets04_trailingSoftDroppedSubJet_pt_tmva_fcc.pdf", "Trailing #gamma-Subjet (R=0.4) Pt [GeV]", "", "tmva");
  auto canvas_tmva_drawer_595 = mRoot::draw_hists_FCC(drawer_595, output_path, "B_ptag_pfjets04_trailingSoftDroppedSubJet_m_tmva_fcc.pdf", "Trailing #gamma-Subjet (R=0.4) M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_596 = mRoot::draw_hists_FCC(drawer_596, output_path, "B_ptag_pfjets04_trailingSoftDroppedSubJet_e_tmva_fcc.pdf", "Trailing #gamma-Subjet (R=0.4) E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_597 = mRoot::draw_hists_FCC(drawer_597, output_path, "B_ptag_pfjets08_softDroppedJet_pt_tmva_fcc.pdf", "Soft-dropped #gamma-jet (R=0.8) Pt [GeV]", "", "tmva");
  auto canvas_tmva_drawer_598 = mRoot::draw_hists_FCC(drawer_598, output_path, "B_ptag_pfjets08_softDroppedJet_m_tmva_fcc.pdf", "Soft-dropped #gamma-jet (R=0.8) M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_599 = mRoot::draw_hists_FCC(drawer_599, output_path, "B_ptag_pfjets08_softDroppedJet_e_tmva_fcc.pdf", "Soft-dropped #gamma-jet (R=0.8) E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_600 = mRoot::draw_hists_FCC(drawer_600, output_path, "B_ptag_pfjets08_leadingSoftDroppedSubJet_pt_tmva_fcc.pdf", "Leading #gamma-Subjet (R=0.8) Pt [GeV]", "", "tmva");
  auto canvas_tmva_drawer_601 = mRoot::draw_hists_FCC(drawer_601, output_path, "B_ptag_pfjets08_leadingSoftDroppedSubJet_m_tmva_fcc.pdf", "Leading #gamma-Subjet (R=0.8) M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_602 = mRoot::draw_hists_FCC(drawer_602, output_path, "B_ptag_pfjets08_leadingSoftDroppedSubJet_e_tmva_fcc.pdf", "Leading #gamma-Subjet (R=0.8) E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_603 = mRoot::draw_hists_FCC(drawer_603, output_path, "B_ptag_pfjets08_trailingSoftDroppedSubJet_pt_tmva_fcc.pdf", "Trailing #gamma-Subjet (R=0.8) Pt [GeV]", "", "tmva");
  auto canvas_tmva_drawer_604 = mRoot::draw_hists_FCC(drawer_604, output_path, "B_ptag_pfjets08_trailingSoftDroppedSubJet_m_tmva_fcc.pdf", "Trailing #gamma-Subjet (R=0.8) M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_605 = mRoot::draw_hists_FCC(drawer_605, output_path, "B_ptag_pfjets08_trailingSoftDroppedSubJet_e_tmva_fcc.pdf", "Trailing #gamma-Subjet (R=0.8) E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_606 = mRoot::draw_hists_FCC(drawer_606, output_path, "B_btag_pfjets02_softDroppedJet_pt_tmva_fcc.pdf", "Soft-dropped b-jet (R=0.2) Pt [GeV]", "", "tmva");
  auto canvas_tmva_drawer_607 = mRoot::draw_hists_FCC(drawer_607, output_path, "B_btag_pfjets02_softDroppedJet_m_tmva_fcc.pdf", "Soft-dropped b-jet (R=0.2) M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_608 = mRoot::draw_hists_FCC(drawer_608, output_path, "B_btag_pfjets02_softDroppedJet_e_tmva_fcc.pdf", "Soft-dropped b-jet (R=0.2) E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_609 = mRoot::draw_hists_FCC(drawer_609, output_path, "B_btag_pfjets02_leadingSoftDroppedSubJet_pt_tmva_fcc.pdf", "Leading b-Subjet (R=0.2) Pt [GeV]", "", "tmva");
  auto canvas_tmva_drawer_610 = mRoot::draw_hists_FCC(drawer_610, output_path, "B_btag_pfjets02_leadingSoftDroppedSubJet_m_tmva_fcc.pdf", "Leading b-Subjet (R=0.2) M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_611 = mRoot::draw_hists_FCC(drawer_611, output_path, "B_btag_pfjets02_leadingSoftDroppedSubJet_e_tmva_fcc.pdf", "Leading b-Subjet (R=0.2) E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_612 = mRoot::draw_hists_FCC(drawer_612, output_path, "B_btag_pfjets02_trailingSoftDroppedSubJet_pt_tmva_fcc.pdf", "Trailing b-Subjet (R=0.2) Pt [GeV]", "", "tmva");
  auto canvas_tmva_drawer_613 = mRoot::draw_hists_FCC(drawer_613, output_path, "B_btag_pfjets02_trailingSoftDroppedSubJet_m_tmva_fcc.pdf", "Trailing b-Subjet (R=0.2) M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_614 = mRoot::draw_hists_FCC(drawer_614, output_path, "B_btag_pfjets02_trailingSoftDroppedSubJet_e_tmva_fcc.pdf", "Trailing b-Subjet (R=0.2) E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_615 = mRoot::draw_hists_FCC(drawer_615, output_path, "B_btag_pfjets04_softDroppedJet_pt_tmva_fcc.pdf", "Soft-dropped b-jet (R=0.4) Pt [GeV]", "", "tmva");
  auto canvas_tmva_drawer_616 = mRoot::draw_hists_FCC(drawer_616, output_path, "B_btag_pfjets04_softDroppedJet_m_tmva_fcc.pdf", "Soft-dropped b-jet (R=0.4) M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_617 = mRoot::draw_hists_FCC(drawer_617, output_path, "B_btag_pfjets04_softDroppedJet_e_tmva_fcc.pdf", "Soft-dropped b-jet (R=0.4) E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_618 = mRoot::draw_hists_FCC(drawer_618, output_path, "B_btag_pfjets04_leadingSoftDroppedSubJet_pt_tmva_fcc.pdf", "Leading b-Subjet (R=0.4) Pt [GeV]", "", "tmva");
  auto canvas_tmva_drawer_619 = mRoot::draw_hists_FCC(drawer_619, output_path, "B_btag_pfjets04_leadingSoftDroppedSubJet_m_tmva_fcc.pdf", "Leading b-Subjet (R=0.4) M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_620 = mRoot::draw_hists_FCC(drawer_620, output_path, "B_btag_pfjets04_leadingSoftDroppedSubJet_e_tmva_fcc.pdf", "Leading b-Subjet (R=0.4) E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_621 = mRoot::draw_hists_FCC(drawer_621, output_path, "B_btag_pfjets04_trailingSoftDroppedSubJet_pt_tmva_fcc.pdf", "Trailing b-Subjet (R=0.4) Pt [GeV]", "", "tmva");
  auto canvas_tmva_drawer_622 = mRoot::draw_hists_FCC(drawer_622, output_path, "B_btag_pfjets04_trailingSoftDroppedSubJet_m_tmva_fcc.pdf", "Trailing b-Subjet (R=0.4) M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_623 = mRoot::draw_hists_FCC(drawer_623, output_path, "B_btag_pfjets04_trailingSoftDroppedSubJet_e_tmva_fcc.pdf", "Trailing b-Subjet (R=0.4) E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_624 = mRoot::draw_hists_FCC(drawer_624, output_path, "B_btag_pfjets08_softDroppedJet_pt_tmva_fcc.pdf", "Soft-dropped b-jet (R=0.8) Pt [GeV]", "", "tmva");
  auto canvas_tmva_drawer_625 = mRoot::draw_hists_FCC(drawer_625, output_path, "B_btag_pfjets08_softDroppedJet_m_tmva_fcc.pdf", "Soft-dropped b-jet (R=0.8) M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_626 = mRoot::draw_hists_FCC(drawer_626, output_path, "B_btag_pfjets08_softDroppedJet_e_tmva_fcc.pdf", "Soft-dropped b-jet (R=0.8) E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_627 = mRoot::draw_hists_FCC(drawer_627, output_path, "B_btag_pfjets08_leadingSoftDroppedSubJet_pt_tmva_fcc.pdf", "Leading b-Subjet (R=0.8) Pt [GeV]", "", "tmva");
  auto canvas_tmva_drawer_628 = mRoot::draw_hists_FCC(drawer_628, output_path, "B_btag_pfjets08_leadingSoftDroppedSubJet_m_tmva_fcc.pdf", "Leading b-Subjet (R=0.8) M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_629 = mRoot::draw_hists_FCC(drawer_629, output_path, "B_btag_pfjets08_leadingSoftDroppedSubJet_e_tmva_fcc.pdf", "Leading b-Subjet (R=0.8) E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_630 = mRoot::draw_hists_FCC(drawer_630, output_path, "B_btag_pfjets08_trailingSoftDroppedSubJet_pt_tmva_fcc.pdf", "Trailing b-Subjet (R=0.8) Pt [GeV]", "", "tmva");
  auto canvas_tmva_drawer_631 = mRoot::draw_hists_FCC(drawer_631, output_path, "B_btag_pfjets08_trailingSoftDroppedSubJet_m_tmva_fcc.pdf", "Trailing b-Subjet (R=0.8) M [GeV]", "", "tmva");
  auto canvas_tmva_drawer_632 = mRoot::draw_hists_FCC(drawer_632, output_path, "B_btag_pfjets08_trailingSoftDroppedSubJet_e_tmva_fcc.pdf", "Trailing b-Subjet (R=0.8) E [GeV]", "", "tmva");
  auto canvas_tmva_drawer_633 = mRoot::draw_hists_FCC(drawer_633, output_path, "B_dPhi_Photon_ptag_pfjets04_tmva_fcc.pdf", "#Delta #phi(#gamma, #gamma-PF-Jet R=0.4 )", "", "tmva");
  auto canvas_tmva_drawer_634 = mRoot::draw_hists_FCC(drawer_634, output_path, "B_dR_Photon_ptag_pfjets04_tmva_fcc.pdf", "#Delta R(#gamma, #gamma-PF-Jet R=0.4 )", "", "tmva");
  auto canvas_tmva_drawer_635 = mRoot::draw_hists_FCC(drawer_635, output_path, "B_M_Photon_ptag_pfjets04_tmva_fcc.pdf", "M(#gamma, #gamma-PF-Jet R=0.4 )", "", "tmva");
  auto canvas_tmva_drawer_636 = mRoot::draw_hists_FCC(drawer_636, output_path, "B_dPhi_bjet_ptag_pfjets04_tmva_fcc.pdf", "#Delta #phi(b-jet, #gamma-PF-Jet R=0.4 )", "", "tmva");
  auto canvas_tmva_drawer_637 = mRoot::draw_hists_FCC(drawer_637, output_path, "B_dR_bjet_ptag_pfjets04_tmva_fcc.pdf", "#Delta R(b-jet)", "", "tmva");
  drawer_677->label_x = "Soft-dropped #gamma-jet (R=0.8) M [GeV]";
  drawer_677->label_y = "Leading #gamma-Subjet (R=0.8) M [GeV]";
  drawer_677->signals.pop_back();
  auto canvas_def_drawer_677 = mRoot::draw_hists_FCC(drawer_677, output_path, "C_CORRELATION_800_def_fcc.pdf", "", "", "correlation");
  drawer_678->label_x = "Soft-dropped #gamma-jet (R=0.8) M [GeV]";
  drawer_678->label_y = "Soft-dropped #gamma-jet (R=0.8) Pt [GeV]";
  drawer_678->signals.pop_back();
  auto canvas_def_drawer_678 = mRoot::draw_hists_FCC(drawer_678, output_path, "C_CORRELATION_801_def_fcc.pdf", "", "", "correlation");
  drawer_679->label_x = "Soft-dropped #gamma-jet (R=0.8) M [GeV]";
  drawer_679->label_y = "Soft-dropped #gamma-jet (R=0.4) M [GeV]";
  drawer_679->signals.pop_back();
  auto canvas_def_drawer_679 = mRoot::draw_hists_FCC(drawer_679, output_path, "C_CORRELATION_802_def_fcc.pdf", "", "", "correlation");
  drawer_680->label_x = "#gamma-PF-Jet R=0.8 M [GeV]";
  drawer_680->label_y = "Soft-dropped #gamma-jet (R=0.8) M [GeV]";
  drawer_680->signals.pop_back();
  auto canvas_def_drawer_680 = mRoot::draw_hists_FCC(drawer_680, output_path, "C_CORRELATION_803_def_fcc.pdf", "", "", "correlation");
  drawer_681->label_x = "Best t-jet candidate PF-Jet R=0.8 M [GeV]";
  drawer_681->label_y = "Second t-jet candidate PF-Jet R=0.8 M [GeV]";
  drawer_681->signals.pop_back();
  auto canvas_def_drawer_681 = mRoot::draw_hists_FCC(drawer_681, output_path, "C_CORRELATION_804_def_fcc.pdf", "", "", "correlation");
  drawer_682->label_x = "Best #gamma-jet #eta";
  drawer_682->label_y = "b-jet #eta";
  drawer_682->signals.pop_back();
  auto canvas_def_drawer_682 = mRoot::draw_hists_FCC(drawer_682, output_path, "C_CORRELATION_805_def_fcc.pdf", "", "", "correlation");
  auto canvas_comp_drawer_638 = mRoot::draw_hists_FCC(drawer_638, output_path, "D_COMPARISON_806_mgp8_pp_tt_aut_fcc.pdf", "#gamma-Jet M [GeV]", "t #rightarrow #gamma u", "default");
  auto canvas_comp_drawer_639 = mRoot::draw_hists_FCC(drawer_639, output_path, "D_COMPARISON_807_mgp8_pp_tt_aut_fcc.pdf", "b-Jet M [GeV]", "t #rightarrow #gamma u", "default");
  auto canvas_comp_drawer_640 = mRoot::draw_hists_FCC(drawer_640, output_path, "D_COMPARISON_808_mgp8_pp_tt_aut_fcc.pdf", "#gamma-Jet M [GeV]", "t #rightarrow #gamma u", "default");
  drawer_641->xmax = 250;
  drawer_641->xmin = 150;
  auto canvas_comp_drawer_641 = mRoot::draw_hists_FCC(drawer_641, output_path, "D_COMPARISON_809_mgp8_pp_tt_aut_fcc.pdf", "#gamma-Jet M [GeV]", "t #rightarrow #gamma u", "default nolog");
  auto canvas_comp_drawer_642 = mRoot::draw_hists_FCC(drawer_642, output_path, "D_COMPARISON_810_mgp8_pp_tt_aut_fcc.pdf", "#gamma-Jet M [GeV]", "t #rightarrow #gamma u", "default");
  drawer_643->xmax = 250;
  drawer_643->xmin = 150;
  auto canvas_comp_drawer_643 = mRoot::draw_hists_FCC(drawer_643, output_path, "D_COMPARISON_811_mgp8_pp_tt_aut_fcc.pdf", "#gamma-Jet M [GeV]", "t #rightarrow #gamma u", "default nolog");
  auto canvas_comp_drawer_644 = mRoot::draw_hists_FCC(drawer_644, output_path, "D_COMPARISON_812_mgp8_pp_tt_aut_fcc.pdf", "#gamma-Jet M [GeV]", "t #rightarrow #gamma u", "default nolog");
  auto canvas_comp_drawer_645 = mRoot::draw_hists_FCC(drawer_645, output_path, "D_COMPARISON_813_mgp8_pp_tt_aut_fcc.pdf", "#gamma-Jet M [GeV]", "t #rightarrow #gamma u", "default");
  auto canvas_comp_drawer_646 = mRoot::draw_hists_FCC(drawer_646, output_path, "D_COMPARISON_814_mgp8_pp_tt_aut_fcc.pdf", "#gamma-Jet E [GeV]", "t #rightarrow #gamma u", "default");
  auto canvas_comp_drawer_647 = mRoot::draw_hists_FCC(drawer_647, output_path, "D_COMPARISON_815_mgp8_pp_tt_aut_fcc.pdf", "b-Jet M [GeV]", "t #rightarrow #gamma u", "default");
  auto canvas_comp_drawer_648 = mRoot::draw_hists_FCC(drawer_648, output_path, "D_COMPARISON_816_mgp8_pp_tt_aut_fcc.pdf", "b-Jet M [GeV]", "t #rightarrow #gamma u", "default");
  auto canvas_comp_drawer_649 = mRoot::draw_hists_FCC(drawer_649, output_path, "D_COMPARISON_817_mgp8_pp_tt_aut_fcc.pdf", "b-Jet M [GeV]", "t #rightarrow #gamma u", "default nolog");
  auto canvas_comp_drawer_650 = mRoot::draw_hists_FCC(drawer_650, output_path, "D_COMPARISON_818_mgp8_pp_tt_aut_fcc.pdf", "#gamma-Jet M [GeV]", "t #rightarrow #gamma u", "default");
  auto canvas_comp_drawer_651 = mRoot::draw_hists_FCC(drawer_651, output_path, "D_COMPARISON_819_mgp8_pp_tt_aut_fcc.pdf", "#gamma-Jet E [GeV]", "t #rightarrow #gamma u", "default");
  auto canvas_comp_drawer_652 = mRoot::draw_hists_FCC(drawer_652, output_path, "D_COMPARISON_820_mgp8_pp_tt_aut_fcc.pdf", "#gamma-Jet M [GeV]", "t #rightarrow #gamma u", "default");
  auto canvas_comp_drawer_653 = mRoot::draw_hists_FCC(drawer_653, output_path, "D_COMPARISON_821_mgp8_pp_tt_aut_fcc.pdf", "#gamma-Jet E [GeV]", "t #rightarrow #gamma u", "default");
  auto canvas_def_drawer_654 = mRoot::draw_hists_FCC(drawer_654, output_path, "F_CUT_822_fcc.pdf", "#gamma-PF-Jet R=0.8 M [GeV]", "PF-Jet R=0.8 M<140", "cut");
  auto canvas_def_drawer_655 = mRoot::draw_hists_FCC(drawer_655, output_path, "F_CUT_823_fcc.pdf", "Leading #gamma-Subjet (R=0.8) M [GeV]", "SoftDropped PF-Jet R=0.8 M>250", "cut");
  auto canvas_def_drawer_656 = mRoot::draw_hists_FCC(drawer_656, output_path, "F_CUT_824_fcc.pdf", "Soft-dropped #gamma-jet (R=0.4) M [GeV]", "SoftDropped PF-Jet R=0.8 M>250", "cut");
  auto canvas_def_drawer_657 = mRoot::draw_hists_FCC(drawer_657, output_path, "F_CUT_825_fcc.pdf", "best #gamma-jet #tau_{1}", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_658 = mRoot::draw_hists_FCC(drawer_658, output_path, "F_CUT_826_fcc.pdf", "best #gamma-jet #tau_{2}", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_659 = mRoot::draw_hists_FCC(drawer_659, output_path, "F_CUT_827_fcc.pdf", "best #gamma-jet #tau_{3}", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_660 = mRoot::draw_hists_FCC(drawer_660, output_path, "F_CUT_828_fcc.pdf", "best #gamma-jet #tau_{31}", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_661 = mRoot::draw_hists_FCC(drawer_661, output_path, "F_CUT_829_fcc.pdf", "best #gamma-jet #tau_{32}", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_662 = mRoot::draw_hists_FCC(drawer_662, output_path, "F_CUT_830_fcc.pdf", "best #gamma-jet #tau_{21}", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_663 = mRoot::draw_hists_FCC(drawer_663, output_path, "F_CUT_831_fcc.pdf", "#gamma-PF-jet R=0.8 #tau_{1}", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_664 = mRoot::draw_hists_FCC(drawer_664, output_path, "F_CUT_832_fcc.pdf", "#gamma-PF-jet R=0.8 #tau_{2}", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_665 = mRoot::draw_hists_FCC(drawer_665, output_path, "F_CUT_833_fcc.pdf", "#gamma-PF-jet R=0.8 #tau_{3}", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_666 = mRoot::draw_hists_FCC(drawer_666, output_path, "F_CUT_834_fcc.pdf", "#gamma-PF-jet R=0.8 #tau_{31}", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_667 = mRoot::draw_hists_FCC(drawer_667, output_path, "F_CUT_835_fcc.pdf", "#gamma-PF-jet R=0.8 #tau_{32}", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_668 = mRoot::draw_hists_FCC(drawer_668, output_path, "F_CUT_836_fcc.pdf", "#gamma-PF-jet R=0.8 #tau_{21}", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_669 = mRoot::draw_hists_FCC(drawer_669, output_path, "F_CUT_837_fcc.pdf", "(P_{#gamma}, P_{best j#gamma-et}) [GeV^{2}]", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_670 = mRoot::draw_hists_FCC(drawer_670, output_path, "F_CUT_838_fcc.pdf", "#Delta #phi(#gamma, best #gamma-jet)", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_671 = mRoot::draw_hists_FCC(drawer_671, output_path, "F_CUT_839_fcc.pdf", "#Delta R(#gamma, best #gamma-jet)", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_672 = mRoot::draw_hists_FCC(drawer_672, output_path, "F_CUT_840_fcc.pdf", "M(#gamma, best #gamma-jet)", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_673 = mRoot::draw_hists_FCC(drawer_673, output_path, "F_CUT_841_fcc.pdf", "(P_{b-jet}, P_{best #gamma-jet}) [GeV^{2}]", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_674 = mRoot::draw_hists_FCC(drawer_674, output_path, "F_CUT_842_fcc.pdf", "#Delta #phi(b-jet, best #gamma-jet)", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_675 = mRoot::draw_hists_FCC(drawer_675, output_path, "F_CUT_843_fcc.pdf", "#Delta R(b-jet, best #gamma-jet)", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  auto canvas_def_drawer_676 = mRoot::draw_hists_FCC(drawer_676, output_path, "F_CUT_844_fcc.pdf", "#Delta R(b-jet, best #gamma-jet)", "Best #gamma-Jet M#in[150, 200] GeV", "cut");
  //[[[end]]]
  output_hists->Close();
}













