from ultralytics import YOLO
import numpy as np

model = YOLO("D:\Repository\ArtefactDetection\yoloWeights/yolov10n.pt")

results = model.train(data="D:\Repository\ArtefactDetection\yoloWeights/custom_data.yaml", epochs = 1000)