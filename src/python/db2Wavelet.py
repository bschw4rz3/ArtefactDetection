import sys
import pywt
from waveletMethods import calculateWavelet

waveletName = 'db2'

ex = pywt.DiscreteContinuousWavelet(waveletName)
class DiscreteContinuousWaveletEx(type(ex)):
    def __init__(self, name=u'', filter_bank=None):
        super(type(ex), self)
        pywt.DiscreteContinuousWavelet.__init__(self, name, filter_bank)
        self.complex_cwt = False

wavelet = DiscreteContinuousWaveletEx(waveletName)

# perform CWT
calculateWavelet(sys.argv[1], sys.argv[2], wavelet)