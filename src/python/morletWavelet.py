import sys
from waveletMethods import calculateWavelet

wavelet = "morl"

# perform CWT
calculateWavelet(sys.argv[1], sys.argv[2], wavelet)
