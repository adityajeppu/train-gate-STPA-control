import serial
import time
import bpy
import math


ser = serial.Serial('COM11', 115200)
ser.close()
ser.open()

##objects
car1 = bpy.data.collections['car1'].all_objects
car2 = bpy.data.collections['car2'].all_objects
train = bpy.data.collections['Collection'].all_objects['train']
gate1l = bpy.data.collections['Collection'].all_objects['gate1_left']  #4
gate1r = bpy.data.collections['Collection'].all_objects['gate1_right']   #2
gate2l = bpy.data.collections['Collection'].all_objects['gate2_left']   #3
gate2r = bpy.data.collections['Collection'].all_objects['gate2_right']   #1

red = bpy.data.collections['Collection'].all_objects['Cube.004']
orange = bpy.data.collections['Collection'].all_objects['Cube.005']
green = bpy.data.collections['Collection'].all_objects['Cube.006']
reset_car1 = [7.296009063720703, 16.949875831604004, 23.837894439697266, 32.48568344116211, 42.40331268310547, 49.83244323730469]
reset_car2 = [-59.08498764038086, -51.431121826171875, -42.5431022644043, -33.89531326293945, -23.977684020996094, -16.548553466796875]
for j in range(6):
    car1[j].location[0] = reset_car1[j]
    car2[j].location[0] = reset_car2[j]
train.location[1] = 250
train.location[0] = -3.3609373569488525

def car1move():
    for i in range(6):
        car1[i].location[0] -= 1.1
        if(car1[i].location.x <= -32):
            car1[i].hide_viewport = True
            car1[i].location[0] += 60
            car1[i].hide_viewport = False
        bpy.ops.wm.redraw_timer(type = 'DRAW_WIN_SWAP', iterations=1)

def car2move():
    for i in range(6):
        car2[i].location[0] += 1.1
        if(car2[i].location.x >= 20):
            car2[i].hide_viewport = True
            car2[i].location[0] -= 60
            car2[i].hide_viewport = False
        bpy.ops.wm.redraw_timer(type = 'DRAW_WIN_SWAP', iterations=1)     
            
#testing       
close = False
values = []  
loop = True
check = True
while(loop):
    time.sleep(.2)
    values = ser.readline().decode().split()
    if(values[0] == 'STOP'):
        break;
    if(values[4] == '1'):
        red.hide_viewport = True
        orange.hide_viewport = True
        green.hide_viewport = False
    if(values[4] == '2'):
        red.hide_viewport = True
        orange.hide_viewport = False
        green.hide_viewport = True
    if(values[4] == '3'):
        red.hide_viewport = False
        orange.hide_viewport = True
        green.hide_viewport = True
    train.location[1] = int(values[6])/10
    bpy.ops.wm.redraw_timer(type = 'DRAW_WIN_SWAP', iterations=1) 
    gate1l.rotation_euler[0] = int(values[2])*(math.pi/180)
    gate2l.rotation_euler[0] = int(values[3])*(math.pi/180)
    gate1r.rotation_euler[0] = int(values[0])*(math.pi/180)
    gate2r.rotation_euler[0] = int(values[1])*(math.pi/180)
    bpy.ops.wm.redraw_timer(type = 'DRAW_WIN_SWAP', iterations=1) 
    print(values)
    if(int(values[5]) == 2 or close):
        close = True
        if(check):
            indices1 = []
            indices2 = []
            for i in range(6):
                if(car1[i].location[0] < 5): 
                    indices1.append(i)
                if(car2[i].location[0] > -13): 
                    indices2.append(i)

            left1 = list(range(6))
            left2 = list(range(6))
            for i in indices1:
                left1.remove(i)

            for j in indices2:
                left2.remove(j) 
               
            max1 = 0        
            for i in left1:
               if(car1[i].location[0] > max1):
                   max1 = car1[i].location[0]
                   
            max2 = 0
            for j in left2:
                if(car2[j].location[0] < max2):
                    max2 = car2[j].location[0]
            
            check = False
            
        if (len(indices1) != 0 or len(indices2) != 0):
            for k1 in indices1:
                car1[k1].location[0] -= 2
                if(car1[k1].location[0] <= -33):
                    car1[k1].hide_viewport = True
                    car1[k1].location[0] = max1+9
                    max1 += 9
                    car1[k1].hide_viewport = False
                    indices1.remove(k1)
                    
            for k2 in indices2:
                car2[k2].location[0] += 2
                if(car2[k2].location[0] >= 20):
                    car2[k2].hide_viewport = True
                    car2[k2].location[0] = max2-9
                    max2-=9
                    car2[k2].hide_viewport = False
                    indices2.remove(k2)
                    
            bpy.ops.wm.redraw_timer(type = 'DRAW_WIN_SWAP', iterations=1)         
            
        else:
            close = False
           
    elif (int(values[5]) == 1):
        car1move()
        car2move()

    
#serial reading
ser.close()    
