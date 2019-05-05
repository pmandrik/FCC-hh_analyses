

def get_jets( collection_name, size ):
  answer_floats = []
  answer_tlvs   = []

  col_parts = ["N"]
  tlv_parts = ["e", "pt", "eta", "phi", "m"]
  jet_parts = ["tau1", "tau2", "tau3", "subjetsSoftDrop_size"]
  jet_tlv_parts = ["softDroppedJet", "leadingSoftDroppedSubJet", "trailingSoftDroppedSubJet"]

  for part in col_parts:
    answer_floats += [ collection_name + "_" + part ]
  
  for i in xrange(size):
    name = collection_name + "_" + str(i)
    answer_tlvs += [ name ]
    for part in tlv_parts + jet_parts:
      answer_floats += [ name + "_" + part ]
    
    for part in jet_tlv_parts:
      answer_tlvs += [ name + "_" + part ]
      for subpart in tlv_parts:
        answer_floats += [ name + "_" + part + "_" + subpart ]

  return answer_floats, answer_tlvs

def set_analyse_hists(plotter):

  plotter.add_TH1("test_a", 0, 400 )
  plotter.add_TH2("test_b", 0, 2, 0, 400)

vars_to_save = [ "weight",
                 "sm_top_fat_jet_pt", "fcnc_top_fat_jet_pt", "top_jet_scalar", 
                 "sm_tau_21", "sm_tau_31", "sm_tau_32", 
                 "fcnc_tau_21", "fcnc_tau_31", "fcnc_tau_32",
                 "sm_top_sd_m", "fcnc_top_sd_m",
                 "fcnc_leadin_mass", "fcnc_bH_mass", "fcnc_bW_mass",
                 "sm_leadin_mass", "sm_bH_mass", "sm_bW_mass",
                 "mass_disbalance",
                 "H_x_fatjet", "W_x_fatjet",
                 "H_pt", "W_pt",
]

part_vars = ["tau1", "tau2", "tau3"]














