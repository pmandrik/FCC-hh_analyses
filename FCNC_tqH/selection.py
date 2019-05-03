
from heppy.framework.analyzer import Analyzer
from heppy.statistics.counter import Counter

class Selection(Analyzer):

    def beginLoop(self, setup):
        super(Selection, self).beginLoop(setup)
        self.counters.addCounter('cut_flow') 
        self.counters['cut_flow'].register('All events')
        self.counters['cut_flow'].register('At least 2 fatjets')
        self.counters['cut_flow'].register('At least 3 b-tagged jets')
        #self.counters['cut_flow'].register('At least 2 b-tagged fat jets')
        #self.counters['cut_flow'].register('Leading b-tagged fat jets pt > 500 GeV')
        #self.counters['cut_flow'].register('Second  b-tagged fat jets pt > 300 GeV')
        #self.counters['cut_flow'].register('|\Delta\Phi(Leading,Second) - #pi| < 1.0')

        # self.counters['cut_flow'].register('1 or 0 leptons')
        # self.counters['cut_flow'].register('Exectly 1 b-jet')
        self.sum_of_weights = 0

    def process(self, event):
        self.sum_of_weights += event.weight

        self.counters['cut_flow'].inc('All events')
        
        # At least ...
        if len(event.selected_pfjets08) < 2: return False
        self.counters['cut_flow'].inc('At least 2 fatjets')

        if len(event.selected_bjets) < 3: return False
        self.counters['cut_flow'].inc('At least 3 b-tagged jets')


        

        #if len(event.selected_leptons) != 0: return False
        #self.counters['cut_flow'].inc('No leptons - hadronic channel')

        # if len(event.selected_leptons) == 0: return False
        # self.counters['cut_flow'].inc('No leptons - leptonic channel')

        return True












