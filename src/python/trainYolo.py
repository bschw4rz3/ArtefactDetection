from ultralytics import YOLO
import numpy as np
import argparse

parser = argparse.ArgumentParser(description="Yolo Trainer")
parser.add_argument("--resume", action="store_true", help="Whether to resume training from a .pt checkpoint")
args = parser.parse_args()

if args.resume:
    model = YOLO("D:\\Repository\\ArtefactDetection\\src\\python\\runs\\detect\\train5\\weights\\best.pt")
    results = model.train(
      resume=True
    , cache=True
    #, device=0
    )
else:
    model = YOLO("D:\Repository\ArtefactDetection\data\yolo/yolov10n.pt")
    results = model.train(
        data="D:\Repository\ArtefactDetection\data\yolo\modified\custom_data.yaml"
        ,epochs = 1000 
        ,cache=True 
    #   ,device=0
    )