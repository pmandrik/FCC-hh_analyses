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

sample.mgp8_pp_tt_tuH = get_my_component( "mgp8_pp_tt_tuH" )
sample.mgp8_pp_tt_tuH_pt500 = get_my_component( "mgp8_pp_tt_tuH_pt500" )

selectedComponents_full = [
  # signal
  sample.mgp8_pp_tt_tuH,
  sample.mgp8_pp_tt_tuH_pt500,

  # singletop
  sample.mgp8_pp_t123j_5f,                          # 754,853

  # ttbar
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

  # W + jets
  sample.mgp8_pp_w0123j_4f_HT_0_150,
  sample.mgp8_pp_w0123j_4f_HT_150_300,
  sample.mgp8_pp_w0123j_4f_HT_300_500,
  sample.mgp8_pp_w0123j_4f_HT_500_1000,
  sample.mgp8_pp_w0123j_4f_HT_1000_2000,
  sample.mgp8_pp_w0123j_4f_HT_2000_5000,
  sample.mgp8_pp_w0123j_4f_HT_5000_100000,

  # tt+z/w
  sample.mgp8_pp_ttz_5f,
  sample.mgp8_pp_ttw_5f,

  # tt+h
  sample.mgp8_pp_tth01j_5f_HT_0_1100,
  sample.mgp8_pp_tth01j_5f_HT_1100_2700,
  sample.mgp8_pp_tth01j_5f_HT_2700_4900,
  sample.mgp8_pp_tth01j_5f_HT_4900_8100,
  sample.mgp8_pp_tth01j_5f_HT_8100_100000,

  # QCD
  sample.mgp8_pp_jj012j_5f_HT_0_500,
  sample.mgp8_pp_jj012j_5f_HT_500_1000,
  sample.mgp8_pp_jj012j_5f_HT_1000_2000,
  sample.mgp8_pp_jj012j_5f_HT_2000_4000,
  sample.mgp8_pp_jj012j_5f_HT_4000_7200,
  sample.mgp8_pp_jj012j_5f_HT_7200_15000,
  sample.mgp8_pp_jj012j_5f_HT_15000_25000,
  sample.mgp8_pp_jj012j_5f_HT_25000_35000,
  sample.mgp8_pp_jj012j_5f_HT_35000_100000,

  sample.mgp8_pp_tt_5f_HT_500_1000,
  sample.mgp8_pp_tt_5f_HT_1000_2000,
  sample.mgp8_pp_tt_5f_HT_2000_5000,
  sample.mgp8_pp_tt_5f_HT_5000_10000,
  sample.mgp8_pp_tt_5f_HT_10000_27000,
  sample.mgp8_pp_tt_5f_HT_27000_100000,
                     ]

sample.mgp8_pp_tt_tuH.splitFactor           =  10
sample.mgp8_pp_tt_tuH_pt500.splitFactor     =  50

sample.mgp8_pp_t123j_5f.splitFactor     =  20

sample.mgp8_pp_tt012j_5f_HT_0_600.splitFactor          =  5
sample.mgp8_pp_tt012j_5f_HT_600_1200.splitFactor       =  10
sample.mgp8_pp_tt012j_5f_HT_1200_2100.splitFactor      =  15
sample.mgp8_pp_tt012j_5f_HT_2100_3400.splitFactor      =  15
sample.mgp8_pp_tt012j_5f_HT_3400_5300.splitFactor      =  15
sample.mgp8_pp_tt012j_5f_HT_5300_8100.splitFactor      =  25
sample.mgp8_pp_tt012j_5f_HT_8100_15000.splitFactor     =  25
sample.mgp8_pp_tt012j_5f_HT_15000_25000.splitFactor    =  25
sample.mgp8_pp_tt012j_5f_HT_25000_35000.splitFactor    =  25
sample.mgp8_pp_tt012j_5f_HT_35000_100000.splitFactor   =  15

sample.mgp8_pp_tt_5f_HT_500_1000.splitFactor       =  75
sample.mgp8_pp_tt_5f_HT_1000_2000.splitFactor      =  75
sample.mgp8_pp_tt_5f_HT_2000_5000.splitFactor      =  75
sample.mgp8_pp_tt_5f_HT_5000_10000.splitFactor     =  75
sample.mgp8_pp_tt_5f_HT_10000_27000.splitFactor    =  75
sample.mgp8_pp_tt_5f_HT_27000_100000.splitFactor   =  75

sample.mgp8_pp_w0123j_4f_HT_0_150.splitFactor          =  10
sample.mgp8_pp_w0123j_4f_HT_150_300.splitFactor        =  10
sample.mgp8_pp_w0123j_4f_HT_300_500.splitFactor        =  10
sample.mgp8_pp_w0123j_4f_HT_500_1000.splitFactor       =  10
sample.mgp8_pp_w0123j_4f_HT_1000_2000.splitFactor      =  10
sample.mgp8_pp_w0123j_4f_HT_2000_5000.splitFactor      =  10
sample.mgp8_pp_w0123j_4f_HT_5000_100000.splitFactor    =  10

sample.mgp8_pp_ttz_5f.splitFactor   =  40
sample.mgp8_pp_ttw_5f.splitFactor   =  40

sample.mgp8_pp_tth01j_5f_HT_0_1100.splitFactor        =  35
sample.mgp8_pp_tth01j_5f_HT_1100_2700.splitFactor     =  35
sample.mgp8_pp_tth01j_5f_HT_2700_4900.splitFactor     =  35
sample.mgp8_pp_tth01j_5f_HT_4900_8100.splitFactor     =  35
sample.mgp8_pp_tth01j_5f_HT_8100_100000.splitFactor   =  35

sample.mgp8_pp_jj012j_5f_HT_0_500.splitFactor         =  20
sample.mgp8_pp_jj012j_5f_HT_500_1000.splitFactor      =  200
sample.mgp8_pp_jj012j_5f_HT_1000_2000.splitFactor     =  50
sample.mgp8_pp_jj012j_5f_HT_2000_4000.splitFactor     =  40
sample.mgp8_pp_jj012j_5f_HT_4000_7200.splitFactor     =  30
sample.mgp8_pp_jj012j_5f_HT_7200_15000.splitFactor    =  20
sample.mgp8_pp_jj012j_5f_HT_15000_25000.splitFactor   =  20
sample.mgp8_pp_jj012j_5f_HT_25000_35000.splitFactor   =  10
sample.mgp8_pp_jj012j_5f_HT_35000_100000.splitFactor  =  10

path = '/eos/experiment/fcc/hh/generation/DelphesEvents/fcc_v02/'
path_tqH = path + "mgp8_pp_tt_tuH/"
testComponents = [ 
  #cfg.Component( 'example_signal', files = [ path + "mgp8_pp_tt_tuH_pt500/events_177969217.root" ]),
  cfg.Component( 'example_signal', files = [ path_tqH + "events_060629295.root", path_tqH + "events_069200134.root", path_tqH + "events_072865185.root", path_tqH + "events_074748323.root", path_tqH + "events_088445041.root" ]),
  # cfg.Component( 'example_tt', files = [ path + "mgp8_pp_tt012j_5f_HT_600_1200/events_000000010.root", path + "mgp8_pp_tt012j_5f_HT_1200_2100/events_099859778.root", path + "mgp8_pp_tt012j_5f_HT_2100_3400/events_077850681.root" ]),
]

selectedComponents_new = [
  sample.mgp8_pp_jj012j_5f_HT_500_1000,
]

# sample.mgp8_pp_tt_aut.splitFactor                       = 100

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

    # pfsubjetsTrimming04 = 'pfsubjetsTrimming04',  pfsubjetsTrimmingTagged04 = 'pfsubjetsTrimmingTagged04',
    # pfsubjetsPruning04 = 'pfsubjetsPruning04',    pfsubjetsPruningTagged04  = 'pfsubjetsPruningTagged04',

    pfsubjetsSoftDrop02 = 'pfsubjetsSoftDrop02',  pfsubjetsSoftDropTagged02 = 'pfsubjetsSoftDropTagged02',
    pfsubjetsSoftDrop08 = 'pfsubjetsSoftDrop08',  pfsubjetsSoftDropTagged08 = 'pfsubjetsSoftDropTagged08',
    pfsubjetsSoftDrop04 = 'pfsubjetsSoftDrop04',  pfsubjetsSoftDropTagged04 = 'pfsubjetsSoftDropTagged04',

    pfjetsOneSubJettiness02 = 'pfjetsOneSubJettiness02', pfjetsTwoSubJettiness02 = 'pfjetsTwoSubJettiness02', pfjetsThreeSubJettiness02 = 'pfjetsThreeSubJettiness02',
    pfjetsOneSubJettiness04 = 'pfjetsOneSubJettiness04', pfjetsTwoSubJettiness04 = 'pfjetsTwoSubJettiness04', pfjetsThreeSubJettiness04 = 'pfjetsThreeSubJettiness04',
    pfjetsOneSubJettiness08 = 'pfjetsOneSubJettiness08', pfjetsTwoSubJettiness08 = 'pfjetsTwoSubJettiness08', pfjetsThreeSubJettiness08 = 'pfjetsThreeSubJettiness08',
    
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
from heppy.FCChhAnalyses.FCChh.FCNC_tqH.selection import Selection
selection = cfg.Analyzer(
    Selection,
    instance_label='cuts'
)
#############################
# store interesting quantities into flat ROOT tree
from heppy.FCChhAnalyses.FCChh.FCNC_tqH.TreeProducer import *
reco_tree = cfg.Analyzer(
    TreeProducer,
    leptons='selected_leptons',

    selected_bjets='selected_bjets',
    selected_pfjets02='selected_pfjets02',
    selected_pfjets04='selected_pfjets04',
    selected_pfjets08='selected_pfjets08',

    met='met',
    gen_particles='gen_particles',
)

reco_weights_tree = cfg.Analyzer(
    WeightTreeProducer
)

reco_tree_check = cfg.Analyzer(
    CheckTreeProducer,
    gen_particles='gen_particles',
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
    selected_muons,
    selected_electrons,
    selected_leptons,
    selected_pfjets02,
    selected_pfjets04,
    selected_pfjets08,
    selected_bjets,
    # reco_tree_check,
    selection,
    # reco_tree_fakephotons,
    reco_tree,
    # stopper
    ] )


config = cfg.Config(
    # components = selectedComponents_full,
    components = selectedComponents_new,
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



