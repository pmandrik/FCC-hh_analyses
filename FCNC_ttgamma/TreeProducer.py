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

        bookParticle(self.tree, 'gen_photon')
        bookParticle(self.tree, 'gen_u')
        bookParticle(self.tree, 'gen_t')

        self.tree.var("dR_gen_u_gen_photon",       float)
        self.tree.var("dR_gen_t_gen_photon",       float)
        self.tree.var("M_gen_u_gen_photon",        float)
        self.tree.var("dR_gen_t_gen_u_gen_photon", float)

    def process(self, event):
        self.tree.reset()

        gen_particles = getattr(event, self.cfg_ana.gen_particles)

        gen_photons = [ genParticle for genParticle in gen_particles if genParticle._pid      == 22 and genParticle._status == 23]
        gen_us      = [ genParticle for genParticle in gen_particles if abs(genParticle._pid) == 2  and genParticle._status == 23]
        gen_ts      = [ genParticle for genParticle in gen_particles if abs(genParticle._pid) == 6  and genParticle._status == 22]

        if not len(gen_photons) : return
        if not len(gen_us)      : return
        if not len(gen_ts)      : return

        #print "===================="
        gen_photon = gen_photons[0] # always a one
        gen_u = gen_us[0]

        for u_candidate in gen_us:
          if abs((gen_photon._tlv + u_candidate._tlv).M() - 174) < abs((gen_photon._tlv + gen_u._tlv).M() - 174):
            gen_u = u_candidate

        gen_t = gen_ts[0]
        for t_candidate in gen_ts:
          if (gen_photon._tlv + gen_u._tlv).DeltaR( t_candidate._tlv ) < (gen_photon._tlv + gen_u._tlv).DeltaR( gen_t._tlv ):
            gen_t = t_candidate

        fillParticle(self.tree, 'gen_photon', gen_photon)
        fillParticle(self.tree, 'gen_u', gen_u)
        fillParticle(self.tree, 'gen_t', gen_t)
        self.tree.fill("dR_gen_u_gen_photon", gen_u._tlv.DeltaR( gen_photon._tlv ) ) 
        self.tree.fill("dR_gen_t_gen_photon", gen_t._tlv.DeltaR( gen_photon._tlv ) ) 
        self.tree.fill("M_gen_u_gen_photon",  (gen_photon._tlv + gen_u._tlv).M() ) 
        self.tree.fill("dR_gen_t_gen_u_gen_photon", gen_t._tlv.DeltaR( gen_photon._tlv + gen_u._tlv ) ) 
  
        # fake photons ================
        photons   = getattr(event, self.cfg_ana.photons)


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

        gen_photons = [ genParticle for genParticle in gen_particles if genParticle._pid      == 22 and genParticle._status == 23]
        gen_us      = [ genParticle for genParticle in gen_particles if abs(genParticle._pid) == 2  and genParticle._status == 23]
        gen_ts      = [ genParticle for genParticle in gen_particles if abs(genParticle._pid) == 6  and genParticle._status == 22]

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


class TreeProducer(Analyzer):
    N_JETS = 20
    def beginLoop(self, setup):
        super(TreeProducer, self).beginLoop(setup)
        self.rootfile = TFile('/'.join([self.dirName, 'tree.root']), 'recreate')
        self.tree = Tree( 'events', '')


        self.tree.var('weight', float)
        float_vars = ['top_pt', 'dR_Photon_genPhoton', 'dPhi_Photon_t', 'dPhi_Photon_tbar', 'dR_Photon_t', 'dR_Photon_tbar']
        float_vars+= ['M_lepton_met', 'M_bjet_lepton_met', 'dPhi_top_candidates', 'dR_top_candidates']
        #float_vars+= ['bfatjet_tau1', 'bfatjet_tau2', 'bfatjet_tau3', 'bjet_tau1', 'bjet_tau2', 'bjet_tau3']
        #float_vars+= ['photonfatjet_tau1', 'photonfatjet_tau2', 'photonfatjet_tau3', 'photonjet04_tau1', 'photonjet04_tau2', 'photonjet04_tau3']
        float_vars+= ['dR_photon_uquark', 'dPhi_photon_uquark', 'dPhi_uquark_nearestJet', 'dR_uquark_nearestJet', 'M_Photon_uquark']
        float_vars+= ['dR_genPhoton_uquark', 'dPhi_genPhoton_uquark']
        float_vars+= ['photon_x_lepton', 'lepton_x_bjet']
        float_vars+= ['dR_lepton_bjet', 'dPhi_lepton_bjet']
        int_vars   = ['jets_size', "fatjets_size", "lepton_channel", 'jets_btag_size', 'jets_ltag_size']

        for var in float_vars:
          self.tree.var(var, float)

        for var in int_vars:
          self.tree.var(var, float)

        bookParticle(self.tree, 'lepton')
        bookParticle(self.tree, 'photon')
        bookParticle(self.tree, 'gen_photon')
        bookMet(self.tree, 'met')

        self.tree.var("photon_relIso", float)
        self.tree.var("lepton_relIso", float)

        jets_names  = [  'btag_pfjets02',   'btag_pfjets04',   'btag_pfjets08',  'ptag_pfjets02',  'ptag_pfjets04',  'ptag_pfjets08']
        jets_names += ['btag_calojets02', 'btag_calojets04', 'btag_calojets08', 'btag_trkjets02', 'btag_trkjets04', 'btag_trkjets08']
        jets_names += ['ptag_calojets02', 'ptag_calojets04', 'ptag_calojets08', 'ptag_trkjets02', 'ptag_trkjets04', 'ptag_trkjets08']

        def book_jet( jet ):
          self.tree.var(jet + "_size", float)
          bookParticle(self.tree, jet)
          self.tree.var(jet + "_tau1", float)
          self.tree.var(jet + "_tau2", float)
          self.tree.var(jet + "_tau3", float)
          self.tree.var(jet + "_tau31" , float)
          self.tree.var(jet + "_tau32" , float)
          self.tree.var(jet + "_tau21" , float )
          self.tree.var(jet + "_subjetsSoftDrop_size", float)
          bookParticle(self.tree, jet + "_softDroppedJet")
          bookParticle(self.tree, jet + "_leadingSoftDroppedSubJet")
          bookParticle(self.tree, jet + "_trailingSoftDroppedSubJet")
          self.tree.var('photon_x_' + jet, float )
          self.tree.var('dPhi_Photon_' + jet, float )
          self.tree.var('dR_Photon_' + jet, float )
          self.tree.var('bjet_x_' + jet, float )
          self.tree.var('dPhi_bjet_' + jet, float )
          self.tree.var('dR_bjet_' + jet, float )
          self.tree.var('lepton_x_' + jet, float )
          self.tree.var('dPhi_lepton_' + jet, float )
          self.tree.var('dR_lepton_' + jet, float )

          self.tree.var('M_Photon_' + jet, float )

        for jet in jets_names:
          book_jet( jet )

        book_jet( "BestMass_jet" )       # best photon + jet mass
        book_jet( "BestTopMass_jet" )        # best top mass
        book_jet( "SecondTopMass_jet" )  # best second top mass

        jets_names = ["jets", "jets_btag", "jets_ltag"]
        for name in jets_names:
          break
          self.tree.var(name + "_size", the_type=int)
          self.tree.vector('dPhi_Photon_' + name,  name + "_size", self.N_JETS, float)
          self.tree.vector('dR_Photon_' + name,    name + "_size", self.N_JETS, float)
          self.tree.vector('dR_t_' + name,    name + "_size", self.N_JETS, float)
          self.tree.vector('dR_tbar_' + name, name + "_size", self.N_JETS, float)

    def get_v(self, part):
        return TLorentzVector(part.px(), part.py(), part.pz(), part.E() )

    def get_tag_jets(self, jets):
        tagged = []
        ntagged = []
        for jet in jets:
          if jet.tags['bf'] > 0 : tagged += [ jet ]
          else : ntagged  += [ jet ]
        return tagged, ntagged

    def get_best_matched(self, jets, direction_v):
        if not len(jets) : return False
        best_jet = jets[0]
        min_dR = 9999
        for i, jet in enumerate(jets):
          if min_dR > direction_v.DeltaR(jet._tlv) : 
            min_dR = direction_v.DeltaR(jet._tlv)
            best_jet = jets[i]
        return best_jet

    def fill_jet(self, jet, collection, photon_v, bjet_v, lepton_v):
        fillParticle(self.tree, collection, jet)
        self.tree.fill(collection + '_tau1' ,     jet.tau1 )
        self.tree.fill(collection + '_tau2' ,     jet.tau2 ) 
        self.tree.fill(collection + '_tau3' ,     jet.tau3 )

        if jet.tau2 > 0 :
          self.tree.fill(collection + "_tau32" , jet.tau3 / jet.tau2)
        else :
          self.tree.fill(collection + "_tau32" , -1)
          # print collection, jet

        if jet.tau1 > 0 :
          self.tree.fill(collection + "_tau31" , jet.tau3 / jet.tau1)
          self.tree.fill(collection + "_tau21" , jet.tau2 / jet.tau1 )
        else : 
          self.tree.fill(collection + "_tau31" , -1)
          self.tree.fill(collection + "_tau21" , -1 )
          # print collection, jet

        self.tree.fill(collection + '_subjetsSoftDrop_size' ,     len(jet.subjetsSoftDrop) )
        if len(jet.subjetsSoftDrop) > 0: fillParticle(self.tree, collection + "_softDroppedJet"           , jet.subjetsSoftDrop[0])
        if len(jet.subjetsSoftDrop) > 1: fillParticle(self.tree, collection + "_leadingSoftDroppedSubJet" , jet.subjetsSoftDrop[1])
        if len(jet.subjetsSoftDrop) > 2: fillParticle(self.tree, collection + "_trailingSoftDroppedSubJet", jet.subjetsSoftDrop[2])

        self.tree.fill('photon_x_' + collection, photon_v.Dot( jet._tlv ) )
        self.tree.fill('dPhi_Photon_'+ collection, photon_v.DeltaPhi( jet._tlv ) )
        self.tree.fill('dR_Photon_'+ collection, photon_v.DeltaR( jet._tlv ) )
        self.tree.fill('M_Photon_' + collection, (photon_v + jet._tlv).M() )

        self.tree.fill('bjet_x_' + collection, bjet_v.Dot( jet._tlv ) )
        self.tree.fill('dPhi_bjet_'+ collection, bjet_v.DeltaPhi( jet._tlv ) )
        self.tree.fill('dR_bjet_'+ collection, bjet_v.DeltaR( jet._tlv ) )

        if lepton_v :
          self.tree.fill('lepton_x_' + collection,   lepton_v.Dot( jet._tlv ) )
          self.tree.fill('dPhi_lepton_'+ collection, lepton_v.DeltaPhi( jet._tlv ) )
          self.tree.fill('dR_lepton_'+ collection,   lepton_v.DeltaR( jet._tlv ) )

    def process(self, event):
        self.tree.reset()
        self.tree.fill('weight' , sign(event.weight) )

        #print dir(event)
        """print dir(event)
        ['analyzers', 'electrons', 'eventWeight', 'gen_particles', 'iEv', 'input', 'jets02', 'jets04', 'jets08', 'met', 'muons', 'pfcharged', 'pfneutrals', 'pfphotons', 
        'photons', 'print_nstrip', 'print_patterns', 'selected_bjets', 'selected_electrons', 'selected_fatjets', 'selected_leptons', 'selected_ljets', 
        'selected_muons', 'selected_photons', 'setup', 'weight']
        """
        
        jets      = getattr(event, 'pfjets04')
        fatjets   = getattr(event, self.cfg_ana.selected_fatjets)

        pfjets02      = getattr(event, 'pfjets02')
        
        calojets02 = getattr(event, 'calojets02')
        calojets04 = getattr(event, 'calojets04')
        calojets08 = getattr(event, 'calojets08')

        trkjets02 = getattr(event, 'trkjets02')
        trkjets04 = getattr(event, 'trkjets04')
        trkjets08 = getattr(event, 'trkjets08')

        jets_collections       = [ pfjets02,        jets,    fatjets,  calojets02,   calojets04,   calojets08,   trkjets02,   trkjets04,   trkjets08 ]
        jets_collections_names = ['pfjets02', 'pfjets04', 'pfjets08', 'calojets02', 'calojets04', 'calojets08', 'trkjets02', 'trkjets04', 'trkjets08']

        jets_ltag = getattr(event, self.cfg_ana.selected_ljets)
        jets_btag = getattr(event, self.cfg_ana.selected_bjets)

        met = getattr(event, self.cfg_ana.met)
        # print event.__dict__.keys()

        photons   = getattr(event, 'selected_photons')
        #photons_old   = getattr(event, 'photons')
        leptons   = getattr(event, self.cfg_ana.leptons)

        photon   = photons[0] # safe
        iso_photon = photons[0]
        photon_v = photon._tlv

        # print iso_photon.iso.sumpt, photons_old[0].iso.sumpt

        # met
        fillMet(self.tree, 'met', met)

        # photons
        fillParticle(self.tree, 'photon', photon)

        self.tree.fill('photon_relIso', iso_photon.iso.sumpt/photon.pt())

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

        self.tree.tree.Fill()

    def write(self, setup):
        self.rootfile.Write()
        self.rootfile.Close()

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





