from heppy.framework.analyzer import Analyzer
from heppy.statistics.tree import Tree
from heppy.analyzers.ntuple import *
from numpy import sign
from ROOT import TFile, TVector2, TLorentzVector

from copy import copy

class WeightTreeProducer(Analyzer):
    def beginLoop(self, setup):
        super(WeightTreeProducer, self).beginLoop(setup)
        self.rootfile = TFile('/'.join([self.dirName, 'weight_tree.root']), 'recreate')
        self.tree = Tree( 'events', '')
        self.tree.var('weight', float)

    def process(self, event):
        self.tree.reset()
        self.tree.fill('weight', event.weight)
        self.tree.tree.Fill()

    def write(self, setup):
        self.rootfile.Write()
        self.rootfile.Close()

class TreeProducer(Analyzer):
    def beginLoop(self, setup):
        super(TreeProducer, self).beginLoop(setup)
        self.rootfile = TFile('/'.join([self.dirName, 'tree.root']), 'recreate')
        self.tree = Tree( 'events', '')


        self.tree.var('weight', float)
        float_vars = []
        int_vars   = []

        self.book_container_jet("pfjets04"     , 3, False)
        self.book_container_jet("pfjets04_btag", 3, False)

        self.book_tlv("photon_0")
        self.book_tlv("photon_1")
        self.book_tlv("rec_higgs")

        bookParticle(self.tree, 'gen_higgs')
        self.tree.var('delta_R', float)

    def process(self, event):
        self.tree.reset()
        self.tree.fill('weight' , sign(event.weight) )

        ################## GEN PART ################## ################## ################## ################## ################## 
        gen_particles = getattr(event, self.cfg_ana.gen_particles)

        for genParticle in gen_particles:
          if genParticle._pid      == 25 and genParticle._status == 22 : 
            fillParticle(self.tree, 'gen_higgs', genParticle)
            break

        ################## REAL PART ################## ################## ################## ################## ################## 
        pfjets04          = getattr(event, self.cfg_ana.selected_pfjets04)
        pfjets04_btag     = getattr(event, self.cfg_ana.selected_bjets)

        photons           = getattr(event, self.cfg_ana.selected_photons)

        self.fill_container_jet(     pfjets04, "pfjets04",      3, False)
        self.fill_container_jet(pfjets04_btag, "pfjets04_btag", 3, False)

        p0 = photons[0]._tlv
        p1 = photons[1]._tlv
        h = p0 + p1
        
        self.fill_tlv( "photon_0",  p0 )
        self.fill_tlv( "photon_1",  p1 )
        self.fill_tlv( "rec_higgs", h  )

        self.tree.tree.Fill()

    ############################################################################ HELP FUNCTIONS ###########################################

    def book_container_jet(self, name, size=10, container_only=False):
      self.book_container( name, size )

      if container_only : return
      for i in xrange( size ):
        nname = name + "_" + str(i)
        self.tree.var(nname +  '_tau1', float)
        self.tree.var(nname +  '_tau2', float)
        self.tree.var(nname +  '_tau3', float)
        self.tree.var(nname + '_subjetsSoftDrop_size' )
        bookParticle(self.tree, nname + "_softDroppedJet"           )
        bookParticle(self.tree, nname + "_leadingSoftDroppedSubJet" )
        bookParticle(self.tree, nname + "_trailingSoftDroppedSubJet")

    def fill_container_jet(self, container, name, size = 10, container_only=False):
      self.fill_container( container, name, size )

      if container_only : return
      for i in xrange(size):
        if i >= len(container) : return
        nname = name + "_" + str(i)
        jet = container[i]
        self.tree.fill(nname +  '_tau1',  jet.tau1 )
        self.tree.fill(nname +  '_tau2' , jet.tau2 ) 
        self.tree.fill(nname +  '_tau3' , jet.tau3 )

        self.tree.fill(nname + '_subjetsSoftDrop_size' ,     len(jet.subjetsSoftDrop) )
        if len(jet.subjetsSoftDrop) > 0: fillParticle(self.tree, nname + "_softDroppedJet"           , jet.subjetsSoftDrop[0])
        if len(jet.subjetsSoftDrop) > 1: fillParticle(self.tree, nname + "_leadingSoftDroppedSubJet" , jet.subjetsSoftDrop[1])
        if len(jet.subjetsSoftDrop) > 2: fillParticle(self.tree, nname + "_trailingSoftDroppedSubJet", jet.subjetsSoftDrop[2])

    def book_container(self, name, size=10):
      self.tree.var(name + "_N", float)
      for i in xrange( size ):
        self.book_tlv(name + "_" + str(i))

    def fill_container(self, container, name, size=10):
      self.tree.fill(name + "_N" , len(container) )
      for i in xrange( size ):
        if i >= len(container) : return
        self.fill_tlv(name + "_" + str(i), container[i]._tlv )

    def book_tlv(self, name):
      self.tree.var(name + "_pt", float)
      self.tree.var(name + "_eta", float)
      self.tree.var(name + "_phi", float)
      self.tree.var(name + "_e", float)
      self.tree.var(name + "_m", float)

    def fill_tlv(self, name, tlv):
      self.tree.fill(name + "_pt" , tlv.Pt() )
      self.tree.fill(name + "_eta", tlv.Eta() )
      self.tree.fill(name + "_phi", tlv.Phi() )
      self.tree.fill(name + "_e"  , tlv.E() )
      self.tree.fill(name + "_m"  , tlv.M() )

    def write(self, setup):
        self.rootfile.Write()
        self.rootfile.Close()




