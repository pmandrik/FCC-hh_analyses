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

class CheckTreeProducer(Analyzer):
    def beginLoop(self, setup):
        super(CheckTreeProducer, self).beginLoop(setup)
        self.rootfile = TFile('/'.join([self.dirName, 'check_tree.root']), 'recreate')
        self.tree = Tree( 'events', '')

        bookParticle(self.tree, 'gen_fcnc_t')
        bookParticle(self.tree, 'gen_fcnc_higgs')
        bookParticle(self.tree, 'gen_fcnc_u')
        bookParticle(self.tree, 'gen_fcnc_b1')
        bookParticle(self.tree, 'gen_fcnc_b2')

        self.tree.var('delta_R', float)

        bookParticle(self.tree, 'gen_sm_t')

    def combine_particle(self, reference, candidates):
        if len(candidates) < 2: return None, None

        reference_e = reference._tlv.E()
        reference_m = reference._tlv.M()

        delta_m = 9999999
        delta_e = 9999999
        best_indexes = [0,1]
        for i, candidate_a in enumerate(candidates):
          for j, candidate_b in enumerate(candidates):
            if i >= j : continue
            candidate_v = candidate_a._tlv + candidate_b._tlv
            if abs(reference_m  - candidate_v.M() ) > delta_m: continue
            if abs(reference_e - candidate_v.E()) > delta_e: continue
            delta_m = abs(reference_m  - candidate_v.M() )
            delta_e = abs(reference_e - candidate_v.E())
            best_indexes = [i, j]
 
        return candidates[best_indexes[0]], candidates[best_indexes[1]]

    def combine_particle_ref(self, reference_candidates, fixed_candidate, candidates):
        delta_m = 9999999
        delta_e = 9999999
        best_indexes = [0,0]
        for i, reference_candidate in enumerate(reference_candidates):
          for j, candidate in enumerate(candidates):
            candidate_v = fixed_candidate._tlv + candidate._tlv

            #print " ~~~~ "
            #candidate_v.Print()
            #print " + "
            #fixed_candidate._tlv.Print()
            #print " = "
            #reference_candidate._tlv.Print()
            #print " ~~~~ "

            if abs(reference_candidate._tlv.M()  - candidate_v.M() ) > delta_m: continue
            if abs(reference_candidate._tlv.E() - candidate_v.E()) > delta_e: continue
            delta_m  = abs(reference_candidate._tlv.M()  - candidate_v.M() )
            delta_e = abs(reference_candidate._tlv.E() - candidate_v.E())
            best_indexes = [i, j]
            #print "!Q!!"
 
        return reference_candidates[best_indexes[0]], candidates[best_indexes[1]]

    def combine_opposite(self, reference, candidates):
        delta_phi  = 0
        best_index = 0
        for i, candidate in enumerate(candidates):
          if reference is candidate: continue
          if reference._tlv.DeltaPhi( candidate._tlv ) < delta_phi : continue
          best_index = i
          delta_phi  = reference._tlv.DeltaPhi( candidate._tlv )
          
        return candidates[best_index]

    def process(self, event):
        self.tree.reset()

        gen_particles = getattr(event, self.cfg_ana.gen_particles)

        gen_hs      = [ genParticle for genParticle in gen_particles if genParticle._pid      == 25 and genParticle._status == 22]
        gen_us      = [ genParticle for genParticle in gen_particles if abs(genParticle._pid) == 2 ] #  and genParticle._status == 23]
        gen_bs      = [ genParticle for genParticle in gen_particles if abs(genParticle._pid) == 5 ] #  and genParticle._status == 23]
        gen_ts      = [ genParticle for genParticle in gen_particles if abs(genParticle._pid) == 6 ] #  and genParticle._status == 22]

        if not len(gen_hs) : return
        if not len(gen_us) : return
        if not len(gen_ts) : return
        if not len(gen_bs) : return

        #for particle in gen_ts + gen_hs + gen_us + gen_bs:
        #  print particle

        #print "===================="
        gen_higgs = gen_hs[0] # always a one

        fcnc_h_b1, fcnc_h_b2 = self.combine_particle(gen_higgs, gen_bs)
        fcnc_top , fcnc_u    = self.combine_particle_ref(gen_ts, gen_higgs, gen_us)
        sm_top               = self.combine_opposite(fcnc_top, gen_ts)
        
        fillParticle(self.tree, 'gen_fcnc_t',     fcnc_top)
        fillParticle(self.tree, 'gen_fcnc_higgs', gen_higgs)
        fillParticle(self.tree, 'gen_fcnc_u',     fcnc_u)
        fillParticle(self.tree, 'gen_fcnc_b1',    fcnc_h_b1)
        fillParticle(self.tree, 'gen_fcnc_b2',    fcnc_h_b2)

        delta_R = max( fcnc_u._tlv.DeltaR(fcnc_h_b1._tlv), fcnc_u._tlv.DeltaR(fcnc_h_b2._tlv), fcnc_h_b1._tlv.DeltaR(fcnc_h_b2._tlv) )
        self.tree.fill('delta_R', delta_R)

        fillParticle(self.tree, 'gen_sm_t', sm_top)

        self.tree.tree.Fill()

    def write(self, setup):
        self.rootfile.Write()
        self.rootfile.Close()

class FakePhotonTreeProducer(Analyzer):
    def beginLoop(self, setup):
        super(FakePhotonTreeProducer, self).beginLoop(setup)
        self.rootfile = TFile('/'.join([self.dirName, 'check_tree.root']), 'recreate')
        self.tree = Tree( 'events', '')

    def process(self, event):
        self.tree.reset()

        gen_particles = getattr(event, self.cfg_ana.gen_particles)
        gen_final_particles = [ genParticle for genParticle in gen_particles if genParticle._status == 1 ]

        gen_photons = [ genParticle for genParticle in gen_particles if genParticle._pid      == 22 and genParticle._status == 23 ]
        gen_us      = [ genParticle for genParticle in gen_particles if abs(genParticle._pid) == 2  and genParticle._status == 23 ]
        gen_ts      = [ genParticle for genParticle in gen_particles if abs(genParticle._pid) == 6  and genParticle._status == 22 ]

        # fake photons ================
        photons   = getattr(event, self.cfg_ana.photons)
        if not len(photons) : return
        photon = photons[0]

        for part in gen_final_particles:
          delta_r  = photon._tlv.DeltaR( part._tlv )
          delta_pt = abs(photon._tlv.Pt() - part._tlv.Pt())
          if delta_r > 1.0 : continue
          if delta_pt > 500 : continue
          
          print part._pid, part._tlv.Pt(), part._tlv.Eta(), part._tlv.Phi(), delta_r, delta_pt

        for photon in photons:
          print "reco-photon", photon._tlv.Pt(), photon._tlv.Eta(), photon._tlv.Phi()
        

        self.tree.tree.Fill()

    def write(self, setup):
        self.rootfile.Write()
        self.rootfile.Close()


##################################################################################################################################################
##################################################################################################################################################
##################################################################################################################################################
class TreeProducer(Analyzer):
    N_JETS = 20
    def beginLoop(self, setup):
        super(TreeProducer, self).beginLoop(setup)
        self.rootfile = TFile('/'.join([self.dirName, 'tree.root']), 'recreate')
        self.tree = Tree( 'events', '')


        self.tree.var('weight', float)
        float_vars = []
        int_vars   = []

        self.book_container_jet("pfjets02", 10, True)
        # self.book_container_jet("pfjets04")
        self.book_container_jet("pfjets08", 5, False)

        self.book_container_jet("pfjets04_btag", 8, False)
        self.book_container("leptons")

        for var in float_vars:
          self.tree.var(var, float)

        for var in int_vars:
          self.tree.var(var, float)

        bookMet(self.tree, 'met')

        bookParticle(self.tree, 'gen_fcnc_t')
        bookParticle(self.tree, 'gen_fcnc_higgs')
        bookParticle(self.tree, 'gen_fcnc_u')
        bookParticle(self.tree, 'gen_fcnc_b1')
        bookParticle(self.tree, 'gen_fcnc_b2')
        bookParticle(self.tree, 'gen_sm_t')
        self.tree.var('delta_R', float)

    def process(self, event):
        self.tree.reset()
        self.tree.fill('weight' , sign(event.weight) )

        ################## GEN PART ################## ################## ################## ################## ################## 
        gen_particles = getattr(event, self.cfg_ana.gen_particles)

        gen_hs, gen_us, gen_bs, gen_ts = [], [], [], []
        for genParticle in gen_particles:
          if genParticle._pid      == 25 and genParticle._status == 22 : gen_hs += [ genParticle ]
          if abs(genParticle._pid) == 2 : gen_us += [ genParticle ]
          if abs(genParticle._pid) == 5 : gen_bs += [ genParticle ]
          if abs(genParticle._pid) == 6 : gen_ts += [ genParticle ]

        fcnc_h_b1, fcnc_h_b2 = None, None
        fcnc_top, sm_top, fcnc_u = None, None, None
        if len(gen_hs) and len(gen_us) and len(gen_ts) and len(gen_bs) :
          gen_higgs = gen_hs[0] # always a one

          fcnc_h_b1, fcnc_h_b2 = self.combine_particle(gen_higgs, gen_bs)
          fcnc_top , fcnc_u    = self.combine_particle_ref(gen_ts, gen_higgs, gen_us)
          sm_top               = self.combine_opposite(fcnc_top, gen_ts)
          
          fillParticle(self.tree, 'gen_fcnc_t',     fcnc_top)
          fillParticle(self.tree, 'gen_fcnc_higgs', gen_higgs)
          fillParticle(self.tree, 'gen_fcnc_u',     fcnc_u)
          fillParticle(self.tree, 'gen_fcnc_b1',    fcnc_h_b1)
          fillParticle(self.tree, 'gen_fcnc_b2',    fcnc_h_b2)

          delta_R = max( fcnc_u._tlv.DeltaR(fcnc_h_b1._tlv), fcnc_u._tlv.DeltaR(fcnc_h_b2._tlv), fcnc_h_b1._tlv.DeltaR(fcnc_h_b2._tlv) )
          self.tree.fill('delta_R', delta_R)

          fillParticle(self.tree, 'gen_sm_t', sm_top)

        ################## REAL PART ################## ################## ################## ################## ################## 
        pfjets02      = getattr(event, self.cfg_ana.selected_pfjets02)
        pfjets04      = getattr(event, self.cfg_ana.selected_pfjets04)
        pfjets08      = getattr(event, self.cfg_ana.selected_pfjets08)
        jets_btag     = getattr(event, self.cfg_ana.selected_bjets)

        jets_collections       = [ pfjets02,   pfjets04,   pfjets08 ]
        jets_collections_names = ['pfjets02', 'pfjets04', 'pfjets08']

        met = getattr(event, self.cfg_ana.met)

        leptons   = getattr(event, self.cfg_ana.leptons)

        ################## FILL PART ################## 
        fillMet(self.tree, 'met', met)

        self.fill_container_jet(pfjets02, "pfjets02", 10, True)
        #self.fill_container_jet(pfjets04, "pfjets04", )
        self.fill_container_jet(pfjets08, "pfjets08", 5, False)

        self.fill_container_jet(jets_btag, "pfjets04_btag", 8, False)
        self.fill_container(leptons, "leptons")

        self.tree.tree.Fill()

    ############################################################################ HELP FUNCTIONS ###########################################

    def book_container_jet(self, name, size=10, container_only=False):
      self.book_container( name )

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
      self.fill_container( container, name )

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

    def book_container(self, name):
      self.tree.var(name + "_N", float)
      for i in xrange(10):
        self.book_tlv(name + "_" + str(i))

    def fill_container(self, container, name):
      self.tree.fill(name + "_N" , len(container) )
      for i in xrange(10):
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

    def jet_top_mass_candidate(jets):
        # best top mass
        best_top_mass_jet = None
        second_top_mass_jet = None
        delta_mass = 9999999;
        delta_mass_second = 9999999;
        for jet in jets:
          new_delta = abs(jet._tlv.M() - 172.4)
          if new_delta < delta_mass :
            second_top_mass_jet = best_top_mass_jet
            delta_mass_second   = delta_mass
            best_top_mass_jet = jet
            delta_mass        = new_delta
          elif new_delta < delta_mass_second:
            second_top_mass_jet = jet
            delta_mass_second   = new_delta

        return best_top_mass_jet, second_top_mass_jet


    def combine_particle(self, reference, candidates):
        if len(candidates) < 2: return None, None

        reference_e = reference._tlv.E()
        reference_m = reference._tlv.M()

        delta_m = 9999999
        delta_e = 9999999
        best_indexes = [0,1]
        for i, candidate_a in enumerate(candidates):
          for j, candidate_b in enumerate(candidates):
            if i >= j : continue
            candidate_v = candidate_a._tlv + candidate_b._tlv
            if abs(reference_m  - candidate_v.M() ) > delta_m: continue
            if abs(reference_e - candidate_v.E()) > delta_e: continue
            delta_m = abs(reference_m  - candidate_v.M() )
            delta_e = abs(reference_e - candidate_v.E())
            best_indexes = [i, j]
 
        return candidates[best_indexes[0]], candidates[best_indexes[1]]

    def combine_particle_ref(self, reference_candidates, fixed_candidate, candidates):
        delta_m = 9999999
        delta_e = 9999999
        best_indexes = [0,0]
        for i, reference_candidate in enumerate(reference_candidates):
          for j, candidate in enumerate(candidates):
            candidate_v = fixed_candidate._tlv + candidate._tlv

            #print " ~~~~ "
            #candidate_v.Print()
            #print " + "
            #fixed_candidate._tlv.Print()
            #print " = "
            #reference_candidate._tlv.Print()
            #print " ~~~~ "

            if abs(reference_candidate._tlv.M()  - candidate_v.M() ) > delta_m: continue
            if abs(reference_candidate._tlv.E() - candidate_v.E()) > delta_e: continue
            delta_m  = abs(reference_candidate._tlv.M()  - candidate_v.M() )
            delta_e = abs(reference_candidate._tlv.E() - candidate_v.E())
            best_indexes = [i, j]
            #print "!Q!!"
 
        return reference_candidates[best_indexes[0]], candidates[best_indexes[1]]

    def combine_opposite(self, reference, candidates):
        delta_phi  = 0
        best_index = 0
        for i, candidate in enumerate(candidates):
          if reference is candidate: continue
          if abs(reference._tlv.DeltaPhi( candidate._tlv )) < delta_phi : continue
          best_index = i
          delta_phi  = abs(reference._tlv.DeltaPhi( candidate._tlv ))
        return candidates[best_index]

    def write(self, setup):
        self.rootfile.Write()
        self.rootfile.Close()

"""
        # NEW PART ==============>
        gen_particles = getattr(event, self.cfg_ana.gen_particles)
        genPhotons = [ genParticle for genParticle in gen_particles if genParticle._pid == 22]
        genPhoton = genPhotons[0] if len(genPhotons) else None
        genPhoton_v = genPhoton._tlv if genPhoton else None

        # check how well genPhotons and photon matched - OK
        if genPhoton_v:
          self.tree.fill('dR_Photon_genPhoton' ,  photon_v.DeltaR( genPhoton_v ) )
          fillParticle(self.tree, 'gen_photon', genPhoton);

        # tops and tbars
        tops  = [ genParticle for genParticle in gen_particles if genParticle._pid == 6]
        tbars = [ genParticle for genParticle in gen_particles if genParticle._pid == -6]

        top_v  = tops[0]._tlv if len(tops) else None
        tbar_v = tbars[0]._tlv if len(tbars) else None

        if top_v : self.tree.fill('top_pt' ,  top_v.Pt() )

        # check how well Photon separated from t and matched with tbar - OK
        if top_v :
          self.tree.fill('dPhi_Photon_t' ,   photon_v.DeltaPhi( top_v ) ) 
          self.tree.fill('dR_Photon_t' ,     photon_v.DeltaR( top_v ) )   
        if tbar_v :
          self.tree.fill('dPhi_Photon_tbar' , photon_v.DeltaPhi( tbar_v ) )  
          self.tree.fill('dR_Photon_tbar' ,   photon_v.DeltaR( tbar_v ) )  

        # check Photon and different jets dR
        self.tree.fill( "jets_size", len(jets) )
        self.tree.fill( "fatjets_size", len(fatjets) )
        for ijet, jet in enumerate(jets):
          break
          self.tree.vecvars['dPhi_Photon_jets'][ijet] = photon_v.DeltaPhi(jet._tlv)
          self.tree.vecvars['dR_Photon_jets'][ijet]  = photon_v.DeltaR( jet._tlv )
          if top_v  : self.tree.vecvars['dR_t_jets'][ijet]        = top_v.DeltaR( jet._tlv )
          if tbar_v : self.tree.vecvars['dR_tbar_jets'][ijet]     = tbar_v.DeltaR( jet._tlv )

        # check Photon and different btagged jets dR
        self.tree.fill( "jets_btag_size", len(jets_btag) )
        for ijet, jet in enumerate(jets_btag):
          break
          self.tree.vecvars['dPhi_Photon_jets_btag'][ijet] = photon_v.DeltaPhi(jet._tlv)
          self.tree.vecvars['dR_Photon_jets_btag'][ijet]   = photon_v.DeltaR( jet._tlv )
          if top_v  : self.tree.vecvars['dR_t_jets_btag'][ijet]        = top_v.DeltaR( jet._tlv )
          if tbar_v : self.tree.vecvars['dR_tbar_jets_btag'][ijet]     = tbar_v.DeltaR( jet._tlv )

        self.tree.fill( "jets_ltag_size", len(jets_ltag) )
        for ijet, jet in enumerate(jets_ltag):
          break
          self.tree.vecvars['dPhi_Photon_jets_ltag'][ijet] = photon_v.DeltaPhi(jet._tlv)
          self.tree.vecvars['dR_Photon_jets_ltag'][ijet]   = photon_v.DeltaR( jet._tlv )
          if top_v  : self.tree.vecvars['dR_t_jets_ltag'][ijet]        = top_v.DeltaR( jet._tlv )
          if tbar_v : self.tree.vecvars['dR_tbar_jets_ltag'][ijet]     = tbar_v.DeltaR( jet._tlv )

        # check Photon and nearest jet px py pz
        nearest_jet = self.get_best_matched(jets, photon_v)
        nearest_jet_v = nearest_jet._tlv
        top_candidate_1_v = nearest_jet_v + photon_v

        jet_btag = jets_btag[0] # bjet candidate
        jet_btag_v = jet_btag._tlv
      
        # check u-quark and jets distributions
        uquarks  = [ genParticle for genParticle in gen_particles if abs(genParticle._pid) == 2]
        if len(uquarks):
          uquark   = uquarks[0]
          uquark_v = uquark._tlv
          self.tree.fill('dR_photon_uquark', photon_v.DeltaR(uquark_v) ) 
          self.tree.fill('dPhi_photon_uquark', photon_v.DeltaPhi(uquark_v) ) 

          if genPhoton_v:
            self.tree.fill('dR_genPhoton_uquark', genPhoton_v.DeltaR(uquark_v) ) 
            self.tree.fill('dPhi_genPhoton_uquark', genPhoton_v.DeltaPhi(uquark_v) ) 

          self.tree.fill('dPhi_uquark_nearestJet', photon_v.DeltaPhi(nearest_jet_v)  ) 
          self.tree.fill('dR_uquark_nearestJet', photon_v.DeltaR(nearest_jet_v)  ) 
          self.tree.fill('M_Photon_uquark', (photon_v + uquark_v).M() ) 

        lepton_v = None
        if len(leptons):
          fillParticle(self.tree, 'lepton', leptons[0])
          self.tree.fill('lepton_relIso', leptons[0].iso.sumpt/leptons[0].pt())
          self.tree.fill('lepton_channel', 1 )

          lepton_v  = leptons[0]._tlv
          met_v     = met._tlv

          W_v = lepton_v + met_v
          top_candidate_2_v = W_v + jet_btag_v

          self.tree.fill('M_lepton_met', W_v.M() )
          self.tree.fill('M_bjet_lepton_met', top_candidate_2_v.M() )

          self.tree.fill('dPhi_top_candidates', top_candidate_2_v.DeltaPhi(top_candidate_1_v) )
          self.tree.fill('dR_top_candidates',   top_candidate_2_v.DeltaR(top_candidate_1_v) )
          self.tree.fill('photon_x_lepton',     photon_v.Dot(lepton_v) )
          self.tree.fill('lepton_x_bjet',       lepton_v.Dot(jet_btag_v) )

          self.tree.fill('dR_lepton_bjet',       lepton_v.DeltaR(jet_btag_v) )
          self.tree.fill('dPhi_lepton_bjet',     lepton_v.DeltaPhi(jet_btag_v) )
        else :
          self.tree.fill('M_lepton_met',      -99999 )
          self.tree.fill('M_bjet_lepton_met', -99999 )

          self.tree.fill('dPhi_top_candidates', -99999 )
          self.tree.fill('dR_top_candidates',   -99999 )
          self.tree.fill('photon_x_lepton',     -99999 )
          self.tree.fill('lepton_x_bjet',       -99999 )

          self.tree.fill('dR_lepton_bjet',      -99999 )
          self.tree.fill('dPhi_lepton_bjet',    -99999 )

        # fill all other collections
        pjets = [ self.get_best_matched(jets_collection, photon_v   ) for jets_collection in jets_collections]
        bjets = [ self.get_best_matched(jets_collection, jet_btag_v ) for jets_collection in jets_collections]

        for pjet, collection in zip(pjets, jets_collections_names):
          if pjet : 
            self.tree.fill("ptag_" + collection + "_size", 1)
            self.fill_jet(pjet, "ptag_" + collection, photon_v, jet_btag_v, lepton_v)
          else :
            self.tree.fill("ptag_" + collection + "_size", 0)

        for bjet, collection in zip(bjets, jets_collections_names):
          if bjet : 
            self.tree.fill("btag_" + collection + "_size", 1)
            self.fill_jet(bjet, "btag_" + collection, photon_v, jet_btag_v, lepton_v)
          else :
            self.tree.fill("btag_" + collection + "_size", 0)

        # best photon + jet to top mass:
        best_mass_jet = None
        delta_mass = 9999;
        for jet in fatjets:
          new_delta = abs((jet._tlv + photon_v).M() - 174)
          if new_delta < delta_mass :
            best_mass_jet = jet
            delta_mass = new_delta
        if best_mass_jet : self.fill_jet(best_mass_jet, "BestMass_jet", photon_v, jet_btag_v, lepton_v)       # best photon + jet mass

        # best top mass
        best_top_mass_jet = None
        second_top_mass_jet = None
        delta_mass = 9999999;
        delta_mass_second = 9999999;
        for jet in fatjets:
          new_delta = abs(jet._tlv.M() - 172.4)
          if new_delta < delta_mass :
            second_top_mass_jet = best_top_mass_jet
            delta_mass_second   = delta_mass
            best_top_mass_jet = jet
            delta_mass        = new_delta
          elif new_delta < delta_mass_second:
            second_top_mass_jet = jet
            delta_mass_second   = new_delta

            #print best_top_mass_jet, second_top_mass_jet
        #print "best ", best_top_mass_jet, second_top_mass_jet

        # book_jet( "BestTop_jet" )        # best top mass
        # book_jet( "BestTopSecond_jet" )  # best second top mass
        if best_top_mass_jet :   self.fill_jet(best_top_mass_jet,   "BestTopMass_jet",   photon_v, jet_btag_v, lepton_v)       # best photon + jet mass
        if second_top_mass_jet : self.fill_jet(second_top_mass_jet, "SecondTopMass_jet", photon_v, jet_btag_v, lepton_v)       # best photon + jet mass
"""


"""
          if False:
            print dir(fatjets[0])
            fjet_b = fatjets[0]
            for fjet in fatjets:
              print "SoftDrop : "
              injet = TLorentzVector()
              for subjet in fjet.subjetsSoftDrop:
                subjet_v = subjet._tlv
                injet += subjet_v
                print fjet.pt(), subjet.pt(), "[", jet_btag.pt(), jet_btag_v.DeltaR(subjet_v) , "] [", genPhoton.pt(), genPhoton_v.DeltaR(subjet_v), "]"
              injet.Print()
              fjet._tlv.Print()

              print fjet.tau3, fjet.tau1, fjet.tau2

              # 'photonfatjet_tau1', 'photonfatjet_tau2', 'photonfatjet_tau3', 'photonjet04_tau1', 'photonjet04_tau2', 'photonjet04_tau3'
              # 'bfatjet_tau1', 'bfatjet_tau2', 'bfatjet_tau3', 'bjet04_tau1', 'bjet04_tau2', 'bjet04_tau3'

              #print "Constituents : "
              #for subjet in fjet.jetConstituents:
              #  subjet_v = subjet._tlv
              #  print fjet.pt(), subjet.pt(), "[", jet_btag.pt(), jet_btag_v.DeltaR(subjet_v) , "] [", genPhoton.pt(), genPhoton_v.DeltaR(subjet_v), "]"


        #print "subjets : "
        #for fjet in jets:
        #  for subjet in fjet.subjetsSoftDrop:
        #    subjet_v = subjet._tlv
        #    print fjet.pt(), subjet.pt(), "[", jet_btag.pt(), jet_btag_v.DeltaR(subjet_v) , "] [", genPhoton.pt(), genPhoton_v.DeltaR(subjet_v), "]"
"""
        
"""
        print "||-------->"
        if genPhoton_v.DeltaR(uquark_v) < 0.1:
          print genPhoton_v.DeltaR(uquark_v)
          for u in uquarks: 
            print "--"
            print genPhoton
            print u
            print genPhoton_v.DeltaR(u._tlv)
        print "<--------||"
"""





