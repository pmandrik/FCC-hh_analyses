
from heppy.framework.analyzer import Analyzer
from heppy.statistics.counter import Counter

class Selection(Analyzer):

    def beginLoop(self, setup):
        super(Selection, self).beginLoop(setup)
        self.counters.addCounter('cut_flow') 
        self.counters['cut_flow'].register('All events')
        self.counters['cut_flow'].register('At least 2 photons')
        self.counters['cut_flow'].register('At least 1 photon with pt > 30 GeV')
        self.counters['cut_flow'].register('|m_aa - 125| < 20')
        self.sum_of_weights = 0

    def process(self, event):
        self.sum_of_weights += event.weight

        self.counters['cut_flow'].inc('All events')
        
        # At least ...
        if len(event.selected_photons)<2: return False
        self.counters['cut_flow'].inc('At least 2 photons')

        if event.selected_photons[0]._tlv.Pt() < 30 : return False
        self.counters['cut_flow'].inc('At least 1 photon with pt > 30 GeV')

        if abs( (event.selected_photons[0]._tlv + event.selected_photons[1]._tlv).M() - 125.) > 20. : return False
        self.counters['cut_flow'].inc('|m_aa - 125| < 20')

        return True












