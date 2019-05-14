
card_template_match_ZZ_prev = """
import model {MODEL}
define p = {PROTON_PARTS}
define j = {JET_PARTS}
add process p p > h   NP=1 QED=0 QCD=99 @0
add process p p > h j NP=1 QED=0 QCD=99 @1
output {OUTPUT_NAME}
"""

MODEL="Higgs_Effective_Couplings_UFO__Higgs_top_FCNC_UFO-card"
MODEL="Higgs_top_FCNC_UFO-5f_tqH"

quars_up   = ['u', 'c', 't']
quars_down = ['d', 's', 'b']

def make_card(quark1, quark2):
  dic = {}
  dic["OUTPUT_NAME"] = "xsec_"+quark1+quark2+"bar_to_H"
  dic["PROTON_PARTS"] = quark1 + " " + quark2 + "~ "

  dic["MODEL"] = MODEL

  file = open( dic["OUTPUT_NAME"] + ".txt", "w" )
  print card_template.format( **dic )
  file.write( card_template.format( **dic ) )
  file.close()
  
def make_card_width(quark1, quark2):
  dic = {}
  dic["OUTPUT_NAME"] = "width_H_to_"+quark1+quark2+"bar"
  dic["DECAY_PARTS"] = quark1 + " " + quark2 + "~ "

  dic["MODEL"] = MODEL

  file = open( dic["OUTPUT_NAME"] + ".txt", "w" )
  print card_template_2.format( **dic )
  file.write( card_template_2.format( **dic ) )
  file.close()
  
def make_card_associated(quark1, quark2, bar = False):
  dic = {}

  dic["OUTPUT_NAME"] = "associated_g" + quark1 + "_to_H" + quark2
  dic["QUARK_IN"]    = quark1
  dic["QUARK_OUT"]   = quark2
  dic["MODEL"]       = MODEL
  dic["PROTON_PARTS"] = quark1 + " g"
  
  if bar:
    dic["OUTPUT_NAME"] = "associated_g" + quark1 + "bar_to_H" + quark2 + "bar"
    dic["QUARK_IN"]    = quark1 + "~"
    dic["QUARK_OUT"]   = quark2 + "~"
    dic["MODEL"]       = MODEL

  file = open( dic["OUTPUT_NAME"] + ".txt", "w" )
  print card_template_3.format( **dic )
  file.write( card_template_3.format( **dic ) )
  file.close()
  
def make_card_matching(quark1, quark2):
  dic = {}

  dic["OUTPUT_NAME"] = "match_" + quark1 + quark2 + "g_h01j"
  dic["PROTON_PARTS"]    = "g " + quark1 + "~ " + quark2 + "~ " + quark1 + " " + quark2
  dic["JET_PARTS"]       = "g " + quark1 + "~ " + quark2 + "~ " + quark1 + " " + quark2
  dic["MODEL"]       = MODEL

  file = open( dic["OUTPUT_NAME"] + ".txt", "w" )
  print card_template_match.format( **dic )
  file.write( card_template_match.format( **dic ) )
  file.close()

def make_card_matching_ZZ(quark1, quark2, forward=True):
  dic = {}

  if forward : 
    dic["PROTON_PARTS"]    = "g " + quark2 + "~ " + quark1 
    dic["JET_PARTS"]       = "g " + quark2 + " " + quark1 + "~ "
    dic["OUTPUT_NAME"] = "match_" + quark1 + quark2 + "g_h01j"
  else : 
    dic["PROTON_PARTS"]    = "g " + quark2 + " " + quark1 + "~ "
    dic["JET_PARTS"]       = "g " + quark2 + "~ " + quark1 + " "
    dic["OUTPUT_NAME"] = "match_" + quark1 + quark2 + "g_h01j" + "_bar"
  dic["MODEL"]       = MODEL
  

  file = open( dic["OUTPUT_NAME"] + ".txt", "w" )
  #print card_template_match.format( **dic )
  #file.write( card_template_match.format( **dic ) )
  print card_template_match_ZZ.format( **dic )
  file.write( card_template_match_ZZ.format( **dic ) )
  file.close()

if False:
  for i, quark1 in enumerate(quars_up):
    for j, quark2 in enumerate(quars_up):
      make_card(quark1, quark2)
      make_card_associated(quark1, quark2, True)
      make_card_associated(quark1, quark2, False)
      
      if j < i : continue
      make_card_width(quark1, quark2)
      
  for i, quark1 in enumerate(quars_down):
    for j, quark2 in enumerate(quars_down):
      make_card(quark1, quark2)
      make_card_associated(quark1, quark2, True)
      make_card_associated(quark1, quark2, False)
      
      if j < i : continue
      make_card_width(quark1, quark2)

if True:
  make_card_matching_ZZ("s", "b", True)
  make_card_matching_ZZ("s", "b", False)

  make_card_matching_ZZ("d", "b", True)
  make_card_matching_ZZ("d", "b", False)









