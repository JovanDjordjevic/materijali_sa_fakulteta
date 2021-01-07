import cv2
import numpy as np

#ako cete testirati za neke vase slike, mora apsolutna putanja ovde

levo = cv2.imread('C:/Users/Jovan/Desktop/PPGR/domaci_2/levo.jpg')
desno = cv2.imread('C:/Users/Jovan/Desktop/PPGR/domaci_2/desno.jpg')

slike = [levo, desno]

panorama = cv2.Stitcher.create()
_, new_image = panorama.stitch(slike)
cv2.imshow('Panorama', new_image)
cv2.waitKey()
