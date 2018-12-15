#!/usr/bin/env python3
"""
Shows how to toss a capsule to a container.
"""
from mujoco_py import load_model_from_path, MjSim, MjViewer
import os
import scipy.misc
import cv2
import matplotlib.pyplot as plt
import numpy as np

model = load_model_from_path("model.xml")
sim = MjSim(model)

viewer = MjViewer(sim)


sim_state = sim.get_state()
count = 1

def get_image_ball_center(image_src):
    src = image_src
    im_width  = image_src.shape[0]
    im_height = image_src.shape[1]
    #grayimg = np.zeros((im_width,im_height),dtype=np.int8)
    pixcount = 0
    pixwx = 0.0
    pixwy = 0.0
#===================================================================
    grayimg = np.zeros((256,256),dtype=np.int8)
    for i in range (0,256):
       for j in range(0,256):
          diff = ( np.abs(src[i][j][0]-255) + np.abs(src[i][j][1]-30) + np.abs(src[i][j][2]-30) )/3
          if(diff > 50 ):
              grayimg[i][j] = 0
          else :
              grayimg[i][j] = 255
#plt.imshow(grayimg)
    ret, markers = cv2.connectedComponents(grayimg)
    objcnt= np.array(np.zeros(ret))
    objx  = np.array(np.zeros(ret))
    objy  = np.array(np.zeros(ret))

    for i in range (0,256):
       for j in range(0,256):
          val = markers[i][j]
          objcnt[val] = objcnt[val] + 1
          objx[val] = objx[val] + i
          objy[val] = objy[val] + j

    for i in range (0, ret):
        print("===========================\n")
        print( (objx[i]/objcnt[i] - 128.0 ) * 0.03352941)
        print( (objy[i]/objcnt[i] - 128.0 ) * 0.03352941)
    return ret    
 
while True:
    sim.set_state(sim_state)
    #for j in range(0,6) :
    sim.data.ctrl[:] = 0.0
    #for i in range (0, 2000) :
    #sim.data.ctrl[j] = -3.14159 + (i * 6.283)/2000.0
    sim.step()
    viewer.render()

    count = count+1;
    if count > 10 :
       #sim.model.vis.map_.zfar = 0.8
       #sim.model.vis.map_.zfar = 0.1
       img = sim.render(512, 512, camera_name="cam4")
       scipy.misc.imsave('outfile4.png', img)
       get_image_ball_center(img)
       break;
    #if i%100==0 :
    #print(sim.data.ctrl)
 
    if os.getenv('TESTING') is not None:
        break
