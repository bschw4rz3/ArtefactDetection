import sys
from ultralytics import YOLO

filePath = sys.argv[1];
#print(filePath)
#exit;

#model = YOLO('D:\\Repository\\ArtefactDetection\\src\\python\\runs\\detect\\train22\\weights\\best.pt')
#model = YOLO('D:\\Repository\\ArtefactDetection\\src\\python\\runs\\detect\\train8\\weights\\best.pt')

#model = YOLO('D:\\Repository\\ArtefactDetection\\data\\yolo\\classic\\data\\runs\\detect\\train\\weights\\best.pt')
#model = YOLO('D:\\Repository\\ArtefactDetection\\data\\yolo\\synthetisch\\data\\runs\\detect\\train\\weights\\best.pt')
model = YOLO('D:\\Repository\\ArtefactDetection\\data\\yolo\\modified\\data\\runs\\detect\\train\\weights\\best.pt')

results = model(source=f'{filePath}', conf=0.25, verbose=False)

#print(results[0].boxes.xyxy)
#results[0].show()

print(results[0].boxes.cls.cpu().tolist())

