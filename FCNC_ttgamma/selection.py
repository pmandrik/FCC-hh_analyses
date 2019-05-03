
from heppy.framework.analyzer import Analyzer
from heppy.statistics.counter import Counter

class Selection(Analyzer):

    def beginLoop(self, setup):
        super(Selection, self).beginLoop(setup)
        self.counters.addCounter('cut_flow') 
        self.counters['cut_flow'].register('All events')
        self.counters['cut_flow'].register('1 or 0 leptons')
        self.counters['cut_flow'].register('At least 1 photon')
        self.counters['cut_flow'].register('Exectly 1 photon')
        self.counters['cut_flow'].register('At least 2 jets')
        self.counters['cut_flow'].register('Exectly 1 b-jet')
        self.counters['cut_flow'].register('dR photon bjet > 0.8')
        self.counters['cut_flow'].register('At least 2 fatjets')

        #self.counters['cut_flow'].register('No leptons - hadronic channel')
        #self.counters['cut_flow'].register('No leptons - leptonic channel')
        self.sum_of_weights = 0

    def process(self, event):
        self.sum_of_weights += event.weight

        self.counters['cut_flow'].inc('All events')
        
        # At least ...
        if len(event.selected_leptons)>1: return False
        self.counters['cut_flow'].inc('1 or 0 leptons')

        if len(event.selected_photons)<1: return False
        self.counters['cut_flow'].inc('At least 1 photon')

        if len(event.selected_photons)!=1: return False
        self.counters['cut_flow'].inc('Exectly 1 photon')

        if len(event.selected_bjets) + len(event.selected_ljets) < 2 : return False
        self.counters['cut_flow'].inc('At least 2 jets')

        if len(event.selected_bjets) != 1: return False
        self.counters['cut_flow'].inc('Exectly 1 b-jet')

        bjet_v   = event.selected_bjets[0]._tlv
        photon_v = event.selected_photons[0]._tlv
        if photon_v.DeltaR(bjet_v) < 0.8 : return False
        self.counters['cut_flow'].inc('dR photon bjet > 0.8')

        if len(event.selected_fatjets) < 2: return False
        self.counters['cut_flow'].inc('At least 2 fatjets')

        #if len(event.selected_leptons) != 0: return False
        #self.counters['cut_flow'].inc('No leptons - hadronic channel')

        # if len(event.selected_leptons) == 0: return False
        # self.counters['cut_flow'].inc('No leptons - leptonic channel')

        return True












