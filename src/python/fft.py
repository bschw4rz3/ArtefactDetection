import matplotlib.pyplot as plt
import numpy as np
import sys
import scipy.fft
import numbers
from decimal import Decimal
from waveletMethods import *

inputArray = readInputNp(sys.argv[1])

output = scipy.fft.fft(inputArray)

writeOutput(sys.argv[2], output)