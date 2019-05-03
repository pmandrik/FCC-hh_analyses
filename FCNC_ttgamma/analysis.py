import os
import copy
import heppy.framework.config as cfg
import logging
import imp
# next 2 lines necessary to deal with reimports from ipython
logging.shutdown()
reload(logging)
logging.basicConfig(level=logging.WARNING)

def get_my_component(ps_name):
  from os import listdir
  from os.path import isfile, join
  prefix = "root://eospublic.cern.ch//eos/experiment/fcc/hh/generation/DelphesEvents/fcc_v02/" + ps_name + "//"
  mypath = "/eos/experiment/fcc/hh/generation/DelphesEvents/fcc_v02/" + ps_name
  try:
    files_list = [prefix + f for f in listdir(mypath) if isfile(join(mypath, f)) and f.endswith('.root')]
    # print files_list
    return cfg.MCComponent(ps_name, files=files_list)
  except:
    return None

class dummy(): pass

sample = None
try:
  sample=imp.load_source('heppylist', '/afs/cern.ch/work/h/helsens/public/FCCDicts/FCC_heppySampleList_fcc_v02.py')
except:
  sample=imp.load_source('heppylist', 'FCC_heppySampleList_fcc_v02.py')

sample.mg_pp_tt_act_cut500 = get_my_component("mgp8_pp_tt_act_cut500")
sample.mg_pp_tt_aut_cut500 = get_my_component("mgp8_pp_tt_aut_cut500")

print len(sample.mgp8_pp_wa.files)
print len(sample.mgp8_pp_t123j_5f.files)

"""
sample.mgp8_pp_z0123j_4f_HT_0_150              = get_my_component("mgp8_pp_z0123j_4f_HT_0_150")
sample.mgp8_pp_z0123j_4f_HT_150_300            = get_my_component("mgp8_pp_z0123j_4f_HT_150_300")
sample.mgp8_pp_z0123j_4f_HT_300_500            = get_my_component("mgp8_pp_z0123j_4f_HT_300_500")
sample.mgp8_pp_z0123j_4f_HT_500_1000           = get_my_component("mgp8_pp_z0123j_4f_HT_500_1000")
sample.mgp8_pp_z0123j_4f_HT_1000_2000          = get_my_component("mgp8_pp_z0123j_4f_HT_1000_2000")
sample.mgp8_pp_z0123j_4f_HT_2000_5000          = get_my_component("mgp8_pp_z0123j_4f_HT_2000_5000")
sample.mgp8_pp_z0123j_4f_HT_5000_100000        = get_my_component("mgp8_pp_z0123j_4f_HT_5000_100000")

sample.mgp8_pp_tt_aut                          = get_my_component("mgp8_pp_tt_aut")
sample.mgp8_pp_tt_act                          = get_my_component("mgp8_pp_tt_act")
sample.mgp8_pp_tt_hadronic_aut                 = get_my_component("mgp8_pp_tt_hadronic_aut")

sample.mgp8_pp_tt012j_5f_HT_0_600              = get_my_component("mgp8_pp_tt012j_5f_HT_0_600")
sample.mgp8_pp_tt012j_5f_HT_600_1200           = get_my_component("mgp8_pp_tt012j_5f_HT_600_1200")
sample.mgp8_pp_tt012j_5f_HT_1200_2100          = get_my_component("mgp8_pp_tt012j_5f_HT_1200_2100")
sample.mgp8_pp_tt012j_5f_HT_2100_3400          = get_my_component("mgp8_pp_tt012j_5f_HT_2100_3400")
sample.mgp8_pp_tt012j_5f_HT_3400_5300          = get_my_component("mgp8_pp_tt012j_5f_HT_3400_5300")
sample.mgp8_pp_tt012j_5f_HT_5300_8100          = get_my_component("mgp8_pp_tt012j_5f_HT_5300_8100")
sample.mgp8_pp_tt012j_5f_HT_8100_15000         = get_my_component("mgp8_pp_tt012j_5f_HT_8100_15000")
sample.mgp8_pp_tt012j_5f_HT_15000_25000        = get_my_component("mgp8_pp_tt012j_5f_HT_15000_25000")
sample.mgp8_pp_tt012j_5f_HT_25000_35000        = get_my_component("mgp8_pp_tt012j_5f_HT_25000_35000")
sample.mgp8_pp_tt012j_5f_HT_35000_100000       = get_my_component("mgp8_pp_tt012j_5f_HT_35000_100000")

sample.mgp8_pp_tta                             = get_my_component("mgp8_pp_tta")
sample.mgp8_pp_t123j_5f                        = get_my_component("mgp8_pp_t123j_5f")
sample.mgp8_pp_tajets                          = get_my_component("mgp8_pp_tajets")
sample.mgp8_pp_wa                              = get_my_component("mgp8_pp_wa")

sample.mgp8_pp_w0123j_4f_HT_0_150              = get_my_component("mgp8_pp_w0123j_4f_HT_0_150")
sample.mgp8_pp_w0123j_4f_HT_150_300            = get_my_component("mgp8_pp_w0123j_4f_HT_150_300")
sample.mgp8_pp_w0123j_4f_HT_300_500            = get_my_component("mgp8_pp_w0123j_4f_HT_300_500")
sample.mgp8_pp_w0123j_4f_HT_500_1000           = get_my_component("mgp8_pp_w0123j_4f_HT_500_1000")
sample.mgp8_pp_w0123j_4f_HT_1000_2000          = get_my_component("mgp8_pp_w0123j_4f_HT_1000_2000")
sample.mgp8_pp_w0123j_4f_HT_2000_5000          = get_my_component("mgp8_pp_w0123j_4f_HT_2000_5000")
sample.mgp8_pp_w0123j_4f_HT_5000_100000        = get_my_component("mgp8_pp_w0123j_4f_HT_5000_100000")

sample.mgp8_pp_jjja_5f                         = get_my_component("mgp8_pp_jjja_5f")
"""

selectedComponents_full = [
  # signal
  sample.mgp8_pp_tt_aut,
  sample.mgp8_pp_tt_act,

  sample.mg_pp_tt_act_cut500,
  sample.mg_pp_tt_aut_cut500,

  sample.mgp8_pp_tt_hadronic_aut,

  # ttbar
# sample.mgp8_pp_ttj_4f,                            # 16,410,000
# sample.mgp8_pp_tt012j_5f,                         # 4,615,391
# sample.p8_pp_tt_Pt2500toInf,                      # 10,400,000

  sample.mgp8_pp_tt012j_5f_HT_0_600,                # 100,000
  sample.mgp8_pp_tt012j_5f_HT_600_1200,             #
  sample.mgp8_pp_tt012j_5f_HT_1200_2100,            #
  sample.mgp8_pp_tt012j_5f_HT_2100_3400,            #
  sample.mgp8_pp_tt012j_5f_HT_3400_5300,            #
  sample.mgp8_pp_tt012j_5f_HT_5300_8100,            #
  sample.mgp8_pp_tt012j_5f_HT_8100_15000,           #
  sample.mgp8_pp_tt012j_5f_HT_15000_25000,          #
  sample.mgp8_pp_tt012j_5f_HT_25000_35000,          #
  sample.mgp8_pp_tt012j_5f_HT_35000_100000,         #

  sample.mgp8_pp_tt_5f_HT_500_1000,
  sample.mgp8_pp_tt_5f_HT_1000_2000,
  sample.mgp8_pp_tt_5f_HT_2000_5000,
  sample.mgp8_pp_tt_5f_HT_5000_10000,
  sample.mgp8_pp_tt_5f_HT_10000_27000,
  sample.mgp8_pp_tt_5f_HT_27000_100000,

  # ttbar + photon
  sample.mgp8_pp_tta,

  # singletop
  sample.mgp8_pp_t123j_5f,                          # 191,417

  # singletop + photon
  sample.mgp8_pp_tajets,

  # W + gamma
  sample.mgp8_pp_wa,

  # W + jets
  sample.mgp8_pp_w0123j_4f_HT_0_150,
  sample.mgp8_pp_w0123j_4f_HT_150_300,
  sample.mgp8_pp_w0123j_4f_HT_300_500,
  sample.mgp8_pp_w0123j_4f_HT_500_1000,
  sample.mgp8_pp_w0123j_4f_HT_1000_2000,
  sample.mgp8_pp_w0123j_4f_HT_2000_5000,
  sample.mgp8_pp_w0123j_4f_HT_5000_100000,

  # Z + jets
  sample.mgp8_pp_z0123j_4f_HT_0_150,
  sample.mgp8_pp_z0123j_4f_HT_150_300,
  sample.mgp8_pp_z0123j_4f_HT_300_500,
  sample.mgp8_pp_z0123j_4f_HT_500_1000,
  sample.mgp8_pp_z0123j_4f_HT_1000_2000,
  sample.mgp8_pp_z0123j_4f_HT_2000_5000,
  sample.mgp8_pp_z0123j_4f_HT_5000_100000,

  # photon
  sample.mgp8_pp_jjja_5f,                           # 197,400,000

                        ### sample.mgp8_pp_tt_tlep_act,
                        ### sample.mgp8_pp_tt_tlep_aut,

                        ### sample.p8_pp_tt_Pt2500toInf,                    # ttbar
                        ### sample.mgp8_pp_t123j_5f,                        # single top (s,t channels)+ 1/2/3 jets 
                        ### sample.mgp8_pp_tt012j_5f_HT_0_600,              # top pair + 0/1/2 jets	0 < HT < 600 
                        ### sample.mgp8_pp_tt012j_5f_HT_1200_2100,          # top pair + 0/1/2 jets	1200 < HT < 2100
                        ### sample.mgp8_pp_tt012j_5f_HT_15000_25000,        # top pair + 0/1/2 jets	15000 < HT < 25000
                        ### sample.mgp8_pp_jjja_5f,                         # photon +jets		 
                        ### sample.mgp8_pp_vj_4f_M_5000_inf,                # w/z+ 1j 
                     ]

path = '/eos/experiment/fcc/hh/generation/DelphesEvents/fcc_v02/'
testComponents = [ 
      cfg.Component( 'example', files = [ path + "mgp8_pp_tt_aut/events_163628792.root" ]),
      #cfg.Component( 'example', files = [ path + "mgp8_pp_w0123j_4f_HT_1000_2000/events_000000100.root" ]),
      #cfg.Component( 'tt012j_5f_HT_600_1200', files = [ path + "mgp8_pp_tt012j_5f_HT_600_1200/events_000000001.root" ]),
      #cfg.Component( 'pp_jjja_5f', files = [ path + "mgp8_pp_jjja_5f/events_000004933.root" ]),
      #cfg.Component( 'mgp8_pp_w0123j_4f_HT_2000_5000', files = [ path + 'mgp8_pp_w0123j_4f_HT_2000_5000/events_000000083.root' ]),
 ]

signalComponents = [
  # signal
  sample.mgp8_pp_tt_aut,
  sample.mgp8_pp_tt_act,
  sample.mgp8_pp_tt_hadronic_aut,
]


selectedComponents_new = [
  sample.mgp8_pp_tt_5f_HT_500_1000,
  sample.mgp8_pp_tt_5f_HT_1000_2000,
  sample.mgp8_pp_tt_5f_HT_2000_5000,
  sample.mgp8_pp_tt_5f_HT_5000_10000,
  sample.mgp8_pp_tt_5f_HT_10000_27000,
  sample.mgp8_pp_tt_5f_HT_27000_100000,
]

sample.mgp8_pp_tt_aut.splitFactor                       = 100
sample.mgp8_pp_tt_act.splitFactor                       = 100
sample.mgp8_pp_tt_hadronic_aut.splitFactor              = 100

try:
  sample.mg_pp_tt_act_cut500.splitFactor              = 100
  sample.mg_pp_tt_aut_cut500.splitFactor              = 100
except : pass

sample.mgp8_pp_tta.splitFactor                          = 100
sample.mgp8_pp_wa.splitFactor                           = 100
sample.mgp8_pp_tajets.splitFactor                       = 100

# sample.mgp8_pp_tt012j_5f.splitFactor                    = 500
# sample.mgp8_pp_ttj_4f.splitFactor                       = 500
# sample.p8_pp_tt_Pt2500toInf.splitFactor                 = 500

sample.mgp8_pp_w0123j_4f_HT_0_150.splitFactor           =  50
sample.mgp8_pp_w0123j_4f_HT_150_300.splitFactor         =  50
sample.mgp8_pp_w0123j_4f_HT_300_500.splitFactor         =  50
sample.mgp8_pp_w0123j_4f_HT_500_1000.splitFactor        =  50
sample.mgp8_pp_w0123j_4f_HT_1000_2000.splitFactor       =  50
sample.mgp8_pp_w0123j_4f_HT_2000_5000.splitFactor       =  50
sample.mgp8_pp_w0123j_4f_HT_5000_100000.splitFactor     =  50

sample.mgp8_pp_z0123j_4f_HT_0_150.splitFactor           =  50
sample.mgp8_pp_z0123j_4f_HT_150_300.splitFactor         =  50
sample.mgp8_pp_z0123j_4f_HT_300_500.splitFactor         =  50
sample.mgp8_pp_z0123j_4f_HT_500_1000.splitFactor        =  50
sample.mgp8_pp_z0123j_4f_HT_1000_2000.splitFactor       =  50
sample.mgp8_pp_z0123j_4f_HT_2000_5000.splitFactor       =  50
sample.mgp8_pp_z0123j_4f_HT_5000_100000.splitFactor     =  50

sample.mgp8_pp_tt012j_5f_HT_0_600.splitFactor           =  50
sample.mgp8_pp_tt012j_5f_HT_600_1200.splitFactor        =  50
sample.mgp8_pp_tt012j_5f_HT_1200_2100.splitFactor       =  50
sample.mgp8_pp_tt012j_5f_HT_2100_3400.splitFactor       =  50
sample.mgp8_pp_tt012j_5f_HT_3400_5300.splitFactor       =  50
sample.mgp8_pp_tt012j_5f_HT_5300_8100.splitFactor       =  50
sample.mgp8_pp_tt012j_5f_HT_8100_15000.splitFactor      =  50
sample.mgp8_pp_tt012j_5f_HT_15000_25000.splitFactor     =  50
sample.mgp8_pp_tt012j_5f_HT_25000_35000.splitFactor     =  50
sample.mgp8_pp_tt012j_5f_HT_35000_100000.splitFactor    =  50
sample.mgp8_pp_t123j_5f.splitFactor                     =  100
sample.mgp8_pp_jjja_5f.splitFactor                      =  2000

sample.mgp8_pp_tt_5f_HT_500_1000.splitFactor                      =  250
sample.mgp8_pp_tt_5f_HT_1000_2000.splitFactor                     =  250
sample.mgp8_pp_tt_5f_HT_2000_5000.splitFactor                     =  250
sample.mgp8_pp_tt_5f_HT_5000_10000.splitFactor                    =  250
sample.mgp8_pp_tt_5f_HT_10000_27000.splitFactor                   =  250
sample.mgp8_pp_tt_5f_HT_27000_100000.splitFactor                  =  250

from heppy.FCChhAnalyses.analyzers.Reader import Reader

source = cfg.Analyzer(
    Reader,

    weights = 'mcEventWeights',

    # gen_particles = 'skimmedGenParticles',
    gen_particles = 'skimmedGenParticles',

    electrons = 'electrons',
    electronITags = 'electronITags',
    electronsToMC = 'electronsToMC',

    muons = 'muons',
    muonITags = 'muonITags',
    muonsToMC = 'muonsToMC',

    pfjets02 = 'pfjets02',
    pfjets04 = 'pfjets04',
    pfjets08 = 'pfjets08',
    # pfjets15 = 'pfjets15',

    calojets02 = 'calojets02',
    calojets04 = 'calojets04',
    calojets08 = 'calojets08',

    trkjets02 = 'trkjets02',
    trkjets04 = 'trkjets04',
    trkjets08 = 'trkjets08',

    #bTags02 = 'pfbTags02',
    pfbTags04 = 'pfbTags04',
    #pfjetConst04 = 'pfjetConst04',
    #pfjetConst08 = 'pfjetConst08',

    pfsubjetsSoftDrop02 = 'pfsubjetsSoftDrop02',  pfsubjetsSoftDropTagged02 = 'pfsubjetsSoftDropTagged02',
    calosubjetsSoftDrop02 = 'calosubjetsSoftDrop02',  calosubjetsSoftDropTagged02 = 'calosubjetsSoftDropTagged02',
    trksubjetsSoftDrop02 = 'trksubjetsSoftDrop02',  trksubjetsSoftDropTagged02 = 'trksubjetsSoftDropTagged02',

    pfsubjetsSoftDrop08 = 'pfsubjetsSoftDrop08',  pfsubjetsSoftDropTagged08 = 'pfsubjetsSoftDropTagged08',
    calosubjetsSoftDrop08 = 'calosubjetsSoftDrop08',  calosubjetsSoftDropTagged08 = 'calosubjetsSoftDropTagged08',
    trksubjetsSoftDrop08 = 'trksubjetsSoftDrop08',  trksubjetsSoftDropTagged08 = 'trksubjetsSoftDropTagged08',

    # pfsubjetsTrimming04 = 'pfsubjetsTrimming04',  pfsubjetsTrimmingTagged04 = 'pfsubjetsTrimmingTagged04',
    # pfsubjetsPruning04 = 'pfsubjetsPruning04',    pfsubjetsPruningTagged04  = 'pfsubjetsPruningTagged04',
    pfsubjetsSoftDrop04 = 'pfsubjetsSoftDrop04',  pfsubjetsSoftDropTagged04 = 'pfsubjetsSoftDropTagged04',
    calosubjetsSoftDrop04 = 'calosubjetsSoftDrop04',  calosubjetsSoftDropTagged04 = 'calosubjetsSoftDropTagged04',
    trksubjetsSoftDrop04 = 'trksubjetsSoftDrop04',  trksubjetsSoftDropTagged04 = 'trksubjetsSoftDropTagged04',

    pfjetsOneSubJettiness02 = 'pfjetsOneSubJettiness02', pfjetsTwoSubJettiness02 = 'pfjetsTwoSubJettiness02', pfjetsThreeSubJettiness02 = 'pfjetsThreeSubJettiness02',
    pfjetsOneSubJettiness04 = 'pfjetsOneSubJettiness04', pfjetsTwoSubJettiness04 = 'pfjetsTwoSubJettiness04', pfjetsThreeSubJettiness04 = 'pfjetsThreeSubJettiness04',
    pfjetsOneSubJettiness08 = 'pfjetsOneSubJettiness08', pfjetsTwoSubJettiness08 = 'pfjetsTwoSubJettiness08', pfjetsThreeSubJettiness08 = 'pfjetsThreeSubJettiness08',

    calojetsOneSubJettiness02 = 'calojetsOneSubJettiness02', calojetsTwoSubJettiness02 = 'calojetsTwoSubJettiness02', calojetsThreeSubJettiness02 = 'calojetsThreeSubJettiness02',
    calojetsOneSubJettiness04 = 'calojetsOneSubJettiness04', calojetsTwoSubJettiness04 = 'calojetsTwoSubJettiness04', calojetsThreeSubJettiness04 = 'calojetsThreeSubJettiness04',
    calojetsOneSubJettiness08 = 'calojetsOneSubJettiness08', calojetsTwoSubJettiness08 = 'calojetsTwoSubJettiness08', calojetsThreeSubJettiness08 = 'calojetsThreeSubJettiness08',

    trkjetsOneSubJettiness02 = 'trkjetsOneSubJettiness02', trkjetsTwoSubJettiness02 = 'trkjetsTwoSubJettiness02', trkjetsThreeSubJettiness02 = 'trkjetsThreeSubJettiness02',
    trkjetsOneSubJettiness04 = 'trkjetsOneSubJettiness04', trkjetsTwoSubJettiness04 = 'trkjetsTwoSubJettiness04', trkjetsThreeSubJettiness04 = 'trkjetsThreeSubJettiness04',
    trkjetsOneSubJettiness08 = 'trkjetsOneSubJettiness08', trkjetsTwoSubJettiness08 = 'trkjetsTwoSubJettiness08', trkjetsThreeSubJettiness08 = 'trkjetsThreeSubJettiness08',
    #bTags08 = 'pfbTags08',
    #bTags15 = 'pfbTags15',

    photons = 'photons',
    
    pfphotons = 'pfphotons',
    pfcharged = 'pfcharged',
    pfneutrals = 'pfneutrals',

    met = 'met',
)

from ROOT import gSystem
gSystem.Load("libdatamodelDict")
from EventStore import EventStore as Events

#############################
##   Reco Level Analysis   ##
#############################

# select isolated muons with pT > 25 GeV and relIso < 0.4
from heppy.analyzers.Selector import Selector
selected_muons = cfg.Analyzer(
    Selector,
    'selected_muons',
    output = 'selected_muons',
    input_objects = 'muons',
    filter_func = lambda ptc: ptc.pt()>25 and abs(ptc.eta()) < 3.0
)

# select electrons with pT > 25 GeV and relIso < 0.4
selected_electrons = cfg.Analyzer(
    Selector,
    'selected_electrons',
    output = 'selected_electrons',
    input_objects = 'electrons',
    filter_func = lambda ptc: ptc.pt()>25 and abs(ptc.eta()) < 3.0
)

from heppy.analyzers.Merger import Merger
selected_leptons = cfg.Analyzer(
      Merger,
      instance_label = 'selected_leptons',
      inputs = ['selected_electrons','selected_muons'],
      output = 'selected_leptons'
)

# select photons pT > 50 GeV 
selected_photons = cfg.Analyzer(
    Selector,
    'selected_photons',
    output = 'selected_photons',
    input_objects = 'photons',
    filter_func = lambda ptc: ptc.pt()> 200. and abs(ptc.eta()) < 3.0
)

# select l-jet above 30 GeV
selected_ljets = cfg.Analyzer(
    Selector,
    'selected_ljets',
    output = 'selected_ljets',
    input_objects = 'pfjets04',
    filter_func = lambda jet: jet.pt()>30.  and jet.tags['bf'] == 0 and abs(jet.eta()) < 3.0
)

# select b-jet above 30 GeV
selected_bjets = cfg.Analyzer(
    Selector,
    'selected_bjets',
    output = 'selected_bjets',
    input_objects = 'pfjets04',
    filter_func = lambda jet: jet.pt()>30.  and jet.tags['bf'] > 0 and abs(jet.eta()) < 3.0
)

# select selected_fatjets above 30 GeV
selected_fatjets = cfg.Analyzer(
    Selector,
    'selected_fatjets',
    output = 'selected_fatjets',
    input_objects = 'pfjets08',
    filter_func = lambda jet: jet.pt()>30. and abs(jet.eta()) < 3.0
)


# apply event selection. 
from heppy.FCChhAnalyses.FCNC_ttgamma.selection import Selection
selection = cfg.Analyzer(
    Selection,
    instance_label='cuts'
)

# produce particle collection to be used for fsr photon isolation
from heppy.analyzers.Merger import Merger
iso_candidates = cfg.Analyzer(
      Merger,
      instance_label = 'iso_candidates',
      inputs = ['pfphotons','pfcharged','pfneutrals'],
      output = 'iso_candidates'
)
# compute fsr photon isolation w/r other particles in the event.
from heppy.analyzers.IsolationAnalyzer import IsolationAnalyzer
from heppy.particles.isolation import EtaPhiCircle

iso_photons = cfg.Analyzer(
    IsolationAnalyzer,
    candidates = 'selected_photons',
    particles = 'iso_candidates',
    iso_area = EtaPhiCircle(0.8),
)

# store interesting quantities into flat ROOT tree
from heppy.FCChhAnalyses.FCNC_ttgamma.TreeProducer import *
reco_tree = cfg.Analyzer(
    TreeProducer,
    photons='selected_photons',
    leptons='selected_leptons',
    selected_bjets='selected_bjets',
    selected_ljets='selected_ljets',
    selected_fatjets='selected_fatjets',
    met='met',
#    jets02="jets02",
    jets04="jets04",
#    jets08="jets08",
#    jets15="jets15",
    gen_particles='gen_particles',
)

reco_weights_tree = cfg.Analyzer(
    WeightTreeProducer
)

reco_tree_check = cfg.Analyzer(
    CheckTreeProducer,
    gen_particles='gen_particles',
    photons='selected_photons',
)

reco_tree_fakephotons = cfg.Analyzer(
    FakePhotonTreeProducer,
    gen_particles='gen_particles',
    photons='selected_photons',
)

# definition of a sequence of analyzers,
# the analyzers will process each event in this order
# https://www.amazon.de/gp/offer-listing/B0001FTV54/ref=olp_page_1?ie=UTF8&f_all=true&qid=1521377893&sr=8-1
sequence = cfg.Sequence( [
    source,
    reco_weights_tree,
    selected_muons,
    selected_electrons,
    selected_leptons,
    selected_photons,
    selected_ljets,
    selected_bjets,
    selected_fatjets,
    iso_candidates,
    iso_photons,
    #reco_tree_check,
    selection,
    # reco_tree_fakephotons,
    reco_tree,
    ] )


config = cfg.Config(
    components = selectedComponents_full,
    # components = selectedComponents_new,
    # components = testComponents,
    # components = signalComponents,
    sequence = sequence,
    services = [],
    events_class = Events
)

if __name__ == '__main__':
    import sys
    from heppy.framework.looper import Looper

    def next():
        loop.process(loop.iEvent+1)

    loop = Looper( 'looper', config,
                   nEvents=100,
                   nPrint=0,
                   timeReport=True)
    loop.process(6)
    print loop.event

"""
  Traceback (most recent call last):
  File "/afs/cern.ch/work/p/pmandrik/fcc_100TeV/4_analyser/heppy/framework/looper.py", line 473, in <module>
    looper.loop()
  File "/afs/cern.ch/work/p/pmandrik/fcc_100TeV/4_analyser/heppy/framework/looper.py", line 280, in loop
    self.process( iEv )
  File "/afs/cern.ch/work/p/pmandrik/fcc_100TeV/4_analyser/heppy/framework/looper.py", line 367, in process
    return self._run_analyzers_on_event()
  File "/afs/cern.ch/work/p/pmandrik/fcc_100TeV/4_analyser/heppy/framework/looper.py", line 384, in _run_analyzers_on_event
    ret = analyzer.process( self.event )
  File "/afs/cern.ch/work/p/pmandrik/fcc_100TeV/4_analyser/heppy/FCChhAnalyses/analyzers/Reader.py", line 141, in process
    jetcoll = get_collection(Jet, '{}jets{}'.format(algo,cone))
  File "/afs/cern.ch/work/p/pmandrik/fcc_100TeV/4_analyser/heppy/FCChhAnalyses/analyzers/Reader.py", line 85, in get_collection
    'collection {} is missing'.format(coll_name)
heppy.FCChhAnalyses.analyzers.Reader.MissingCollection: collection pfjets15 is missing
"""



