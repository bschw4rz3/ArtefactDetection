python -m pip uninstall torch idna opencv-python numpy PyWavelets matplotlib var_dump scipy ultralytics psutil
python -m pip install --ignore-installed pip idna==3.7 opencv-python==4.8.0.74 numpy==1.26.0 PyWavelets matplotlib var_dump scipy ultralytics --no-warn-script-location

python -m pip uninstall numpy
python -m pip install --upgrade numpy

python -m pip uninstall opencv-python  
python -m pip install --upgrade opencv-python