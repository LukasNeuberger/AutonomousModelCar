import numpy as np
import cv2
import paho.mqtt.client as mqtt
import base64

cap = cv2.VideoCapture(0)
client = mqtt.Client()
client.connect("localhost", 1883, 60)

while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()
    client.publish("/image", frame.tobytes())


# When everything done, release the capture
cap.release()
