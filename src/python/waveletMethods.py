import matplotlib.pyplot as plt
import numpy as np
import sys
import pywt
import numbers
from decimal import Decimal
from var_dump import var_dump

def readInput(inputFileName):
        #read input
    realSignal = []
    imagSignal = []

    datei = open(inputFileName,'r')
    inputArray = datei.read().split('\n')

    for a in inputArray:
        valueStrings = a.split('+')
        
        if len(valueStrings) == 2:    
            realValue = valueStrings[0]
            imagValue = valueStrings[1].strip("j ")
            
            #inputSignal.append(complex(Decimal(realValue), Decimal(imagValue)))
            realSignal.append(Decimal(realValue))
            imagSignal.append(Decimal(imagValue))

    realSignal = np.array(realSignal, dtype=float)
    imagSignal = np.array(imagSignal, dtype=float)
    return np.vectorize(complex)(realSignal, imagSignal)

def writeOutput(outputFileName, cwtmatr):
    import json
    
    class NumpyEncoder(json.JSONEncoder):
        def default(self, obj):
            if isinstance(obj, np.ndarray):
                return obj.tolist()
            return super().default(obj)

    cwtmatr = np.round(cwtmatr, 2)

    #jsonString = json.dumps(cwtmatr, cls=NumpyEncoder)
    #f = open(sys.argv[2], 'wb')
    #f.write(jsonString)

    import io, json
    with io.open(outputFileName, 'w', encoding='utf-8') as f:
      f.write(json.dumps(cwtmatr, ensure_ascii=False, cls=NumpyEncoder))

def calculateWavelet(inputFileName, outputFileName, wavelet):
    complexInput = readInput(inputFileName)

    time = np.linspace(0, 1, len(complexInput))

    # logarithmic scale for scales, as suggested by Torrence & Compo:
    widths = np.geomspace(1, 1024, num=100)
    sampling_period = np.diff(time).mean()
    cwtmatr, freqs = pywt.cwt(complexInput, widths, wavelet, sampling_period=sampling_period)

    # absolute take absolute value of complex result
    cwtmatr = np.abs(cwtmatr[:-1, :-1])

    # plot result using matplotlib's pcolormesh (image with annoted axes)
    #fig, axs = plt.subplots(2, 1)
    #pcm = axs[0].pcolormesh(time, freqs, cwtmatr)
    #axs[0].set_yscale("log")
    #axs[0].set_xlabel("Time (s)")
    #axs[0].set_ylabel("Frequency (Hz)")
    #axs[0].set_title("Continuous Wavelet Transform (Scaleogram)")
    #fig.colorbar(pcm, ax=axs[0])

    # plot fourier transform for comparison
    #from numpy.fft import rfft, rfftfreq

    #yf = rfft(complexInput)
    #xf = rfftfreq(len(complexInput), sampling_period)
    #plt.semilogx(xf, np.abs(yf))
    #axs[1].set_xlabel("Frequency (Hz)")
    #axs[1].set_title("Fourier Transform")
    #plt.tight_layout()
    #plt.show()
    
    writeOutput(outputFileName, cwtmatr)
    
    