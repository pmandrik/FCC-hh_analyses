
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
  //[[[end]]]
  output_hists->Close();
}













