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
    print files_list
    return cfg.MCComponent(ps_name, files=files_list)
  except:
    return None

class dummy(): pass

sample = None
try:
  sample=imp.load_source('heppylist', '/afs/cern.ch/work/h/helsens/public/FCCDicts/FCC_heppySampleList_fcc_v02.py')
except:
  sample=imp.load_source('heppylist', 'FCC_heppySampleList_fcc_v02.py')

sample.mgp8_pp_bdbar_hjets_aa_v2 = get_my_component( "mgp8_pp_bdbar_hjets_aa_v2" )
sample.mgp8_pp_bsbar_hjets_aa_v2 = get_my_component( "mgp8_pp_bsbar_hjets_aa_v2" )
sample.mgp8_pp_dbbar_hjets_aa_v2 = get_my_component( "mgp8_pp_dbbar_hjets_aa_v2" )
sample.mgp8_pp_sbbar_hjets_aa_v2 = get_my_component( "mgp8_pp_sbbar_hjets_aa_v2" )

sample.mgp8_pp_bdbar_hjets_aa = get_my_component( "mgp8_pp_bdbar_hjets_aa" )
sample.mgp8_pp_bsbar_hjets_aa = get_my_component( "mgp8_pp_bsbar_hjets_aa" )
sample.mgp8_pp_dbbar_hjets_aa = get_my_component( "mgp8_pp_dbbar_hjets_aa" )
sample.mgp8_pp_sbbar_hjets_aa = get_my_component( "mgp8_pp_sbbar_hjets_aa" )

selectedComponents_full_v2 = [
  # signal
  sample.mgp8_pp_bdbar_hjets_aa_v2,
  sample.mgp8_pp_bsbar_hjets_aa_v2,
  sample.mgp8_pp_dbbar_hjets_aa_v2,
  sample.mgp8_pp_sbbar_hjets_aa_v2,
]

selectedComponents_full = [
  # signal
  sample.mgp8_pp_bdbar_hjets_aa,
  sample.mgp8_pp_bsbar_hjets_aa,
  sample.mgp8_pp_dbbar_hjets_aa,
  sample.mgp8_pp_sbbar_hjets_aa,

  # backgrounds # 0
  sample.mgp8_pp_aa012j_mhcut_5f_HT_0_100,     # 544,604
  sample.mgp8_pp_aa012j_mhcut_5f_HT_100_300,     # 786,653
  sample.mgp8_pp_aa012j_mhcut_5f_HT_300_500,     # 1,019,907
  sample.mgp8_pp_aa012j_mhcut_5f_HT_500_700,     # 1,021,396
  sample.mgp8_pp_aa012j_mhcut_5f_HT_700_900,     # 1,046,410
  sample.mgp8_pp_aa012j_mhcut_5f_HT_900_1100,     # 716,416
  sample.mgp8_pp_aa012j_mhcut_5f_HT_1100_100000,     # 1,173,068

  sample.mgp8_gg_aa01j_mhcut_5f_HT_0_200,      # 804,318
  sample.mgp8_gg_aa01j_mhcut_5f_HT_200_500,    # 457,307
  sample.mgp8_gg_aa01j_mhcut_5f_HT_500_100000, # 191,121

  # backgrounds # 1
  sample.mgp8_pp_h012j_5f_haa,                 # 4,845,886
                     ]

sample.mgp8_pp_bdbar_hjets_aa_v2.splitFactor                   =  75
sample.mgp8_pp_bsbar_hjets_aa_v2.splitFactor                   =  75
sample.mgp8_pp_dbbar_hjets_aa_v2.splitFactor                   =  75
sample.mgp8_pp_sbbar_hjets_aa_v2.splitFactor                   =  75

sample.mgp8_pp_bdbar_hjets_aa.splitFactor                   =  50
sample.mgp8_pp_bsbar_hjets_aa.splitFactor                   =  50
sample.mgp8_pp_dbbar_hjets_aa.splitFactor                   =  50
sample.mgp8_pp_sbbar_hjets_aa.splitFactor                   =  50

sample.mgp8_pp_aa012j_mhcut_5f_HT_0_100.splitFactor         =  50
sample.mgp8_pp_aa012j_mhcut_5f_HT_100_300.splitFactor       =  55
sample.mgp8_pp_aa012j_mhcut_5f_HT_300_500.splitFactor       =  100
sample.mgp8_pp_aa012j_mhcut_5f_HT_500_700.splitFactor       =  100
sample.mgp8_pp_aa012j_mhcut_5f_HT_700_900.splitFactor       =  100
sample.mgp8_pp_aa012j_mhcut_5f_HT_900_1100.splitFactor      =  100
sample.mgp8_pp_aa012j_mhcut_5f_HT_1100_100000.splitFactor   =  100

sample.mgp8_gg_aa01j_mhcut_5f_HT_0_200.splitFactor          =  50
sample.mgp8_gg_aa01j_mhcut_5f_HT_200_500.splitFactor        =  25
sample.mgp8_gg_aa01j_mhcut_5f_HT_500_100000.splitFactor     =  10

sample.mgp8_pp_h012j_5f_haa.splitFactor                     =  200

path = '/eos/experiment/fcc/hh/generation/DelphesEvents/fcc_v02/mgp8_pp_bdbar_hjets_aa/'
testComponents = [ 
  cfg.Component( 'example_signal', files = [ path + "events_004790163.root"]),
]

from heppy.FCChhAnalyses.analyzers.Reader import Reader

source = cfg.Analyzer(
    Reader,

    weights = 'mcEventWeights',

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

    calojets02 = 'calojets02',
    calojets04 = 'calojets04',
    calojets08 = 'calojets08',

    trkjets02 = 'trkjets02',
    trkjets04 = 'trkjets04',
    trkjets08 = 'trkjets08',

    pfbTags04 = 'pfbTags04',

    pfsubjetsSoftDrop02 = 'pfsubjetsSoftDrop02',  pfsubjetsSoftDropTagged02 = 'pfsubjetsSoftDropTagged02',
    pfsubjetsSoftDrop08 = 'pfsubjetsSoftDrop08',  pfsubjetsSoftDropTagged08 = 'pfsubjetsSoftDropTagged08',
    pfsubjetsSoftDrop04 = 'pfsubjetsSoftDrop04',  pfsubjetsSoftDropTagged04 = 'pfsubjetsSoftDropTagged04',

    pfjetsOneSubJettiness02 = 'pfjetsOneSubJettiness02', pfjetsTwoSubJettiness02 = 'pfjetsTwoSubJettiness02', pfjetsThreeSubJettiness02 = 'pfjetsThreeSubJettiness02',
    pfjetsOneSubJettiness04 = 'pfjetsOneSubJettiness04', pfjetsTwoSubJettiness04 = 'pfjetsTwoSubJettiness04', pfjetsThreeSubJettiness04 = 'pfjetsThreeSubJettiness04',
    pfjetsOneSubJettiness08 = 'pfjetsOneSubJettiness08', pfjetsTwoSubJettiness08 = 'pfjetsTwoSubJettiness08', pfjetsThreeSubJettiness08 = 'pfjetsThreeSubJettiness08',

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
from heppy.analyzers.Selector import Selector
selected_muons = cfg.Analyzer(
    Selector,
    'selected_muons',
    output = 'selected_muons',
    input_objects = 'muons',
    filter_func = lambda ptc: ptc.pt()>25 and abs(ptc.eta()) < 3.0
)
selected_electrons = cfg.Analyzer(
    Selector,
    'selected_electrons',
    output = 'selected_electrons',
    input_objects = 'electrons',
    filter_func = lambda ptc: ptc.pt()>25 and abs(ptc.eta()) < 3.0
)
selected_photons = cfg.Analyzer(
    Selector,
    'selected_photons',
    output = 'selected_photons',
    input_objects = 'photons',
    filter_func = lambda ptc: ptc.pt()> 25. and abs(ptc.eta()) < 4.0 and ptc.iso.sumpt/ptc.pt()<0.15
)
from heppy.analyzers.Merger import Merger
selected_leptons = cfg.Analyzer(
      Merger,
      instance_label = 'selected_leptons',
      inputs = ['selected_electrons','selected_muons'],
      output = 'selected_leptons'
)
#############################
selected_pfjets02 = cfg.Analyzer(
    Selector,
    'selected_pfjets02',
    output = 'selected_pfjets02',
    input_objects = 'pfjets02',
    filter_func = lambda jet: jet.pt()>30. and abs(jet.eta()) < 3.0
)
selected_pfjets04 = cfg.Analyzer(
    Selector,
    'selected_pfjets04',
    output = 'selected_pfjets04',
    input_objects = 'pfjets04',
    filter_func = lambda jet: jet.pt()>30. and abs(jet.eta()) < 3.0
)
selected_pfjets08 = cfg.Analyzer(
    Selector,
    'selected_pfjets08',
    output = 'selected_pfjets08',
    input_objects = 'pfjets08',
    filter_func = lambda jet: jet.pt()>30. and abs(jet.eta()) < 3.0
)

selected_bjets = cfg.Analyzer(
    Selector,
    'selected_bjets',
    output = 'selected_bjets',
    input_objects = 'selected_pfjets04',
    filter_func = lambda jet: jet.tags['bf'] > 0
)
#############################
# apply event selection
from heppy.FCChhAnalyses.FCChh.FCNC_h.selection import Selection
selection = cfg.Analyzer(
    Selection,
    instance_label='cuts'
)
#############################
# store interesting quantities into flat ROOT tree
from heppy.FCChhAnalyses.FCChh.FCNC_h.TreeProducer import *
reco_tree = cfg.Analyzer(
    TreeProducer,
    leptons='selected_leptons',

    selected_bjets='selected_bjets',
    selected_pfjets02='selected_pfjets02',
    selected_pfjets04='selected_pfjets04',
    selected_pfjets08='selected_pfjets08',
    selected_photons='selected_photons',

    met='met',
    gen_particles='gen_particles',
)

reco_weights_tree = cfg.Analyzer(
    WeightTreeProducer
)

# definition of a sequence of analyzers,
# the analyzers will process each event in this order
# https://www.amazon.de/gp/offer-listing/B0001FTV54/ref=olp_page_1?ie=UTF8&f_all=true&qid=1521377893&sr=8-1
from heppy.analyzers.examples.simple.Stopper import Stopper
stopper = cfg.Analyzer(
  Stopper,
  iEv = 500
)

sequence = cfg.Sequence( [
    source,
    reco_weights_tree,
    #selected_muons,
    #selected_electrons,
    selected_photons,
    #selected_leptons,
    #selected_pfjets02,
    selected_pfjets04,
    #selected_pfjets08,
    selected_bjets,
    # reco_tree_check,
    selection,
    # reco_tree_fakephotons,
    reco_tree,
    # stopper
    ] )


config = cfg.Config(
    components = selectedComponents_full_v2,
    # components = selectedComponents_full,
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



