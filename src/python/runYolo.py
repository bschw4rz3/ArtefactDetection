import sys
from ultralytics import YOLOv10

filePath = sys.argv[1];
print(filePath)
exit;

#model = YOLOv10('D:\\Repository\\ArtefactDetection\\src\\python\\runs\\detect\\train22\\weights\\best.pt')
model = YOLOv10('D:\\Repository\\ArtefactDetection\\src\\python\\runs\\detect\\train7\\weights\\best.pt')

results = model(source=f'{filePath}', conf=0.25, verbose=False)

#print(results[0].boxes.xyxy)
#results[0].show()

print(results[0].boxes.cls.cpu().tolist())

