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
from sample1 import imgcpt

model = load_model_from_path("model.xml")
sim = MjSim(model)

viewer = MjViewer(sim)


sim_state = sim.get_state()
count = 1

def get_image_ball_center(image_src):
    im_width  = image_src.shape[0]
    im_height = image_src.shape[1]
    #grayimg = np.zeros((im_width,im_height),dtype=np.int8)
    pixcount = 0
    pixwx = 0.0
    pixwy = 0.0
    for i in range (0,im_width):
        for j in range(0,im_height):
            diff = ( np.abs(image_src[i][j][0]-127) + np.abs(image_src[i][j][1]-212)  + np.abs(image_src[i][j][2]-110) * 2 )/3
            if(diff > 30 ):
                #grayimg[i][j] = 255
                pixwx = pixwx + i
                pixwy = pixwy + j
                pixcount = pixcount + 1
            #else :
                #grayimg[i][j] = 0
        position = np.array([pixwx/pixcount,pixwy/pixcount])
    return position    
 
while True:
    sim.set_state(sim_state)
    #for j in range(0,6) :
    sim.data.ctrl[:] = 0.0
    #for i in range (0, 2000) :
    #sim.data.ctrl[j] = -3.14159 + (i * 6.283)/2000.0
    sim.step()
    viewer.render()
    img = sim.render(720, 720, camera_name="cam4", depth=True)
    print( type(img))
    print( img[1] )
    print( np.max(img[1]) )
    print( np.min(img[1]) )
    kk = img[1]
    #kk =
    #kk * 1600.0
    '''
    for i in range (0,256):
        for j in range(0,256):
            #if kk[i][j] > 256:
            val =  (kk[i][j] - 0.5945638) /(0.99736613 -0.5945638) *1500 
            if val > 255:
                  val =255
            kk[i][j] = val 
    scipy.misc.imsave('depth3.png', kk)
    '''
    '''
    sim.data.set_joint_qpos('target:joint', target_q)
        self.data.set_joint_qvel('target:joint', np.array([0, 0, 0, 0, 0, 0]))
        self.sim.forward()
    '''
    #print(get_image_ball_center(img))
    count = count+1;
    boj_id = (sim.model.body_name2id("cylinder_01"));
    #print(sim._xpos);
    print(sim.data.body_xpos[boj_id]);
    if count > 10 :
       np.savetxt('depth_data.csv', img[1], delimiter = ',')
       print( imgcpt(img[1]) )
       break;
    #if i%100==0 :
    #print(sim.data.ctrl)
 
    if os.getenv('TESTING') is not None:
        break
