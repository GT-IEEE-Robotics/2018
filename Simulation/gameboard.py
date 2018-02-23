from Tkinter import *
import math
import time
import random
import numpy as np

WIDTH = 960
HEIGHT = 480
CANVAS_MID_X = WIDTH/2
CANVAS_MID_Y = HEIGHT/2
SIDE = WIDTH/4

robot_center = [100, 240, 0]
treasureOnRobot = 0
flagTurned = 0
rotationLoopTime = .01
loopTime = .01
pushButtonForA = 0
pushButtonForC = 0
ir_list = [0,0,0]

root = Tk()
canvas = Canvas(root, bg="white", height=HEIGHT, width=WIDTH)
canvas.pack()

def setRateOfTranslationMovement(time):
    global loopTime
    loopTime = time

def setRateOfRotationMovement(time):
    global rotationLoopTime
    rotationLoopTime = time

def getIRCode():
    global ir_list
    ir_list[0] = random.randint(0,1)
    ir_list[1] = random.randint(0,1)
    ir_list[2] = random.randint(0,1)
    return ir_list

def draw_square(center, color="black"):
    angle = center[2]
    angle = math.radians(float(angle))
    cos_val = math.cos(angle)
    sin_val = math.sin(angle)
    cx, cy = center[0:2]
    points = [[0,0],[0,0],[0,0],[0,0]]
    points[0] = [cx - 57, cy - 57]
    points[1] = [cx - 57, cy + 57]
    points[2] = [cx + 57, cy + 57]
    points[3] = [cx + 57, cy - 57]
    new_points = []
    for x_old, y_old in points:
        x_old -= cx
        y_old -= cy
        x_new = x_old * cos_val - y_old * sin_val
        y_new = x_old * sin_val + y_old * cos_val
        new_points.append([x_new + cx, y_new + cy])
    canvas.create_polygon(new_points, fill=color)

def draw_treasure_chest_on_robot(center):
    if (treasureOnRobot == 0):
        return 0
    angle = center[2]
    angle = math.radians(float(angle))
    cos_val = math.cos(angle)
    sin_val = math.sin(angle)
    cx, cy = center[0:2]
    points = [[0,0],[0,0],[0,0],[0,0]]
    points[0] = [cx - 20, cy - 20]
    points[1] = [cx - 20, cy + 20]
    points[2] = [cx + 20, cy + 20]
    points[3] = [cx + 20, cy - 20]
    new_points = []
    for x_old, y_old in points:
        x_old -= cx
        y_old -= cy
        x_new = x_old * cos_val - y_old * sin_val
        y_new = x_old * sin_val + y_old * cos_val
        new_points.append([x_new + cx, y_new + cy])
    canvas.create_polygon(new_points, fill="grey")

def calculate_error():
    randnum = random.gauss(0,1)
    direction = -1
    if (randnum > 0):
       direction = 1
    error = random.gauss(0, 1) * direction
    return error

def robot_move(robot_center, direction, magnitude):
    global loopTime
    if (direction == "North"):
        #breakCondition = break_condition(robot_center)
        #if (breakCondition == 1):
        #    return robot_center
        error = calculate_error()
        magnitude = magnitude * -1
        curr_magnitude = 0
        while(curr_magnitude > magnitude):
            draw_square(robot_center, "white")
            angle = math.radians(float(robot_center[2]))
            old_magnitude = math.hypot(robot_center[0], robot_center[1])
            robot_center[0] = robot_center[0] - math.sin(angle)* error/5 - math.sin(angle) * 1
            robot_center[1] = robot_center[1] - math.cos(angle) * 1 - math.cos(angle) * error/5
            if (error <= 0):
                robot_center[2] = robot_center[2] - error / 10
            if (error > 0):
                robot_center[2] = robot_center[2] + error / 10
            curr_magnitude = curr_magnitude + math.hypot(robot_center[0],robot_center[1]) - old_magnitude
            init()
            draw_square(robot_center, "red")
            draw_treasure_chest_on_robot(robot_center)
            breakCondition = break_condition(robot_center)
            if (breakCondition == 1):
                break
            canvas.update()
            time.sleep(loopTime)
    if (direction == "South"):
        #breakCondition = break_condition(robot_center)
        #if (breakCondition == 1):
        #    return robot_center
        error = calculate_error()
        curr_magnitude = 0
        while(curr_magnitude < magnitude):
            draw_square(robot_center, "white")
            angle = math.radians(float(robot_center[2]))
            old_magnitude = math.hypot(robot_center[0], robot_center[1])
            robot_center[0] = robot_center[0] + math.sin(angle)* error/5 + math.sin(angle) * 1
            robot_center[1] = robot_center[1] + math.cos(angle) * 1 + math.cos(angle) * error/5
            if (error > 0):
                robot_center[2] = robot_center[2] - error / 10
            if (error <= 0):
                robot_center[2] = robot_center[2] + error / 10
            curr_magnitude = curr_magnitude + math.hypot(robot_center[0],robot_center[1]) - old_magnitude
            init()
            draw_square(robot_center, "red")
            draw_treasure_chest_on_robot(robot_center)
            breakCondition = break_condition(robot_center)
            if (breakCondition == 1):
                break
            canvas.update()
            time.sleep(loopTime)
    if (direction == "East"):
        #breakCondition = break_condition(robot_center)
        #if (breakCondition == 1):
        #    return robot_center
        error = calculate_error()
        curr_magnitude = 0
        while(curr_magnitude < magnitude):
            draw_square(robot_center, "white")
            angle = math.radians(float(robot_center[2]))
            old_magnitude = math.hypot(robot_center[0], robot_center[1])
            robot_center[1] = robot_center[1] + math.sin(angle)* error/5 + math.sin(angle) * 1
            robot_center[0] = robot_center[0] + math.cos(angle) * 1 + math.cos(angle) * error/5
            if (error > 0):
                robot_center[2] = robot_center[2] - error / 10
            if (error <= 0):
                robot_center[2] = robot_center[2] + error / 10
            curr_magnitude = curr_magnitude + math.hypot(robot_center[0],robot_center[1]) - old_magnitude
            init()
            draw_square(robot_center, "red")
            draw_treasure_chest_on_robot(robot_center)
            breakCondition = break_condition(robot_center)
            if (breakCondition == 1):
                break
            canvas.update()
            time.sleep(loopTime)
    if (direction == "West"):
        #breakCondition = break_condition(robot_center)
        #if (breakCondition == 1):
        #    return robot_center
        error = calculate_error()
        magnitude = magnitude * -1
        curr_magnitude = 0
        while(curr_magnitude > magnitude):
            draw_square(robot_center, "white")
            angle = math.radians(float(robot_center[2]))
            old_magnitude = math.hypot(robot_center[0], robot_center[1])
            robot_center[1] = robot_center[1] - math.sin(angle) * error/5 - math.sin(angle) * 1
            robot_center[0] = robot_center[0] - math.cos(angle) * 1 - math.cos(angle) * error/5
            if (error > 0):
                robot_center[2] = robot_center[2] + error / 10
            if (error <= 0):
                robot_center[2] = robot_center[2] - error / 10
            curr_magnitude = curr_magnitude + math.hypot(robot_center[0],robot_center[1]) - old_magnitude
            init()
            draw_square(robot_center, "red")
            draw_treasure_chest_on_robot(robot_center)
            breakCondition = break_condition(robot_center)
            if (breakCondition == 1):
                break
            canvas.update()
            time.sleep(loopTime)
    return robot_center

def robot_rotate(robot_center, angle, direction):
    global rotationLoopTime
    if (direction == "ccw"):
        #breakCondition = break_condition(robot_center)
        #if (breakCondition == 1):
        #    return robot_center
        angle = angle + angle * .5 * random.random()
        final_angle = robot_center[2] - angle
        while(final_angle < robot_center[2]):
            draw_square(robot_center, "white")
            robot_center[2] = robot_center[2] - 1
            init()
            draw_square(robot_center, "red")
            draw_treasure_chest_on_robot(robot_center)
            breakCondition = break_condition(robot_center)
            if (breakCondition == 1):
                break
            canvas.update()
            time.sleep(rotationLoopTime)
    if (direction == "cw"):
        #breakCondition = break_condition(robot_center)
        #if (breakCondition == 1):
        #    return robot_center
        angle = angle - angle * .5 * random.random()
        final_angle = robot_center[2] + angle
        while(final_angle > robot_center[2]):
            draw_square(robot_center, "white")
            robot_center[2] = robot_center[2] + 1
            init()
            draw_square(robot_center, "red")
            draw_treasure_chest_on_robot(robot_center)
            breakCondition = break_condition(robot_center)
            if (breakCondition == 1):
                break
            canvas.update()
            time.sleep(rotationLoopTime)
    return robot_center

def init():
    global pushButtonForA
    global pushButtonForC
    global treasureOnRobot
    global flagTurned
    vertices = [40, 180, 160, 180, 160, 300, 40, 300] #for starting point
    vertices_water = [213, 0, 308, 0, 308, 480, 213, 480] #for water
    vertices_stageb_top = [510, 0, 570, 0, 570, 30, 510, 30]
    vertices_stageb_bottom = [510, 450, 570, 450, 570, 480, 510, 480]
    vertices_flagturner = [840, 180, 960, 180, 960, 300, 840, 300]
    vertices_ramp = [213, 150, 333, 150, 333, 330, 213, 330]
    vertices_pushButton1 = [90, 0, 110, 0, 110, 20, 90, 20]
    vertices_pushButton2 = [90, 480, 110, 480, 110, 460, 90, 460]
    canvas.create_polygon(vertices_pushButton1,fill = "red")
    canvas.create_polygon(vertices_pushButton2, fill = "red")
    if (pushButtonForA == 1):
        canvas.create_polygon(vertices_pushButton1,fill = "green")
    if (pushButtonForC == 1):
        canvas.create_polygon(vertices_pushButton2,fill = "green")
    if (treasureOnRobot == 0):
        vertices_treasure_chest = [725, 220, 765, 220, 765, 260, 725, 260]
        canvas.create_polygon(vertices_treasure_chest, fill = "grey")
    canvas.create_polygon(vertices, fill="black")
    canvas.create_polygon(vertices_water, fill = "blue")
    canvas.create_polygon(vertices_stageb_top, fill = "black")
    canvas.create_polygon(vertices_stageb_bottom, fill = "black")
    if (flagTurned == 0):
        canvas.create_polygon(vertices_flagturner, fill = "black")
    else:
        canvas.create_polygon(vertices_flagturner, fill = "green")
    canvas.create_polygon(vertices_ramp, fill = "brown")

def break_condition(robot_center):
    angle = robot_center[2]
    angle = math.radians(float(angle))
    cos_val = math.cos(angle)
    sin_val = math.sin(angle)
    cx, cy = robot_center[0:2]
    points = [[0,0],[0,0],[0,0],[0,0]]
    points[0] = [cx - 57, cy - 57]
    points[1] = [cx - 57, cy + 57]
    points[2] = [cx + 57, cy + 57]
    points[3] = [cx + 57, cy - 57]
    new_points = []
    for x_old, y_old in points:
        x_old -= cx
        y_old -= cy
        x_new = x_old * cos_val - y_old * sin_val
        y_new = x_old * sin_val + y_old * cos_val
        new_points.append([x_new + cx, y_new + cy])
    for i, j in new_points:
        if (i < 0):
            return 1
        elif (j > 480):
            return 1
        elif (i > 960):
            return 1
        elif (j < 0):
            return 1
        elif (i > 213 and i < 308 and j < 150):
            return 1
        elif (i > 213 and i < 308 and j > 330):
            return 1
    return 0

sides = [[0, 0],
         [0, 480],
         [960, 480],
         [960, 0]]


def magnitude(vector):
   return np.sqrt(np.dot(np.array(vector),np.array(vector)))


def norm(vector):
   return np.array(vector)/magnitude(np.array(vector))


def lineRayIntersectionPoint(rayOrigin, rayDirection, point1, point2):
    # Convert to numpy arrays
    rayOrigin = np.array(rayOrigin, dtype=np.float)
    rayDirection = np.array(norm(rayDirection), dtype=np.float)
    point1 = np.array(point1, dtype=np.float)
    point2 = np.array(point2, dtype=np.float)
    # Ray-Line Segment Intersection Test in 2D
    # http://bit.ly/1CoxdrG
    try:
        v1 = rayOrigin - point1
        v2 = point2 - point1
        v3 = np.array([-rayDirection[1], rayDirection[0]])
        t1 = np.cross(v2, v1) / np.dot(v2, v3)
        t2 = np.dot(v1, v3) / np.dot(v2, v3)
        if t1 >= 0.0 and t2 >= 0.0 and t2 <= 1.0:
            return [rayOrigin + t1 * rayDirection]
    except:
        return None
    return None


def getDistanceSensorReadings():
    angle = robot_center[2]
    if (angle < -10 or angle > 10):
        return [0,0,0,0,0,0,0,0]
    angle = math.radians(float(angle))
    cos_val = math.cos(angle)
    sin_val = math.sin(angle)
    cx, cy = robot_center[0:2]
    points = [[0,0],[0,0],[0,0],[0,0]]
    points[0] = [cx - 57, cy - 57]
    points[1] = [cx - 57, cy + 57]
    points[2] = [cx + 57, cy + 57]
    points[3] = [cx + 57, cy - 57]
    new_points = []
    for x_old, y_old in points:
        x_old -= cx
        y_old -= cy
        x_new = x_old * cos_val - y_old * sin_val
        y_new = x_old * sin_val + y_old * cos_val
        new_points.append([x_new + cx, y_new + cy])
    distance_sensor_readings = [0,0,0,0,0,0,0,0]
    distance_sensor_readings[0] = (new_points[0][1] / cos_val) / 10
    distance_sensor_readings[1] = (new_points[3][1] / cos_val) / 10
    distance_sensor_readings[2] = ((960 - new_points[3][0]) / cos_val) / 10
    distance_sensor_readings[3] = ((960 - new_points[2][0]) / cos_val) / 10
    distance_sensor_readings[4] = ((480 - new_points[2][1]) / cos_val) / 10
    distance_sensor_readings[5] = ((480 - new_points[1][1]) / cos_val) / 10
    distance_sensor_readings[6] = (new_points[1][0] / cos_val) / 10
    distance_sensor_readings[7] = (new_points[0][0] / cos_val) / 10
    return distance_sensor_readings


def robotMove(magnitude, direction):
    global robot_center
    draw_square(robot_center, "red")
    robot_center = robot_move(robot_center, direction, magnitude)

def robotRotate(magnitude, direction):
    global robot_center
    draw_square(robot_center, "red")
    robot_center = robot_rotate(robot_center, magnitude, direction)

def printDistances(distanceSensors):
    print "Sensor1 = ", distanceSensors[0]
    print "Sensor2 = ", distanceSensors[1]
    print "Sensor3 = ", distanceSensors[2]
    print "Sensor4 = ", distanceSensors[3]
    print "Sensor5 = ", distanceSensors[4]
    print "Sensor6 = ", distanceSensors[5]
    print "Sensor7 = ", distanceSensors[6]
    print "Sensor8 = ", distanceSensors[7]

def partAC():
    global pushButtonForA
    global pushButtonForC
    time.sleep(2)
    angle = robot_center[2]
    angle = math.radians(float(angle))
    cos_val = math.cos(angle)
    sin_val = math.sin(angle)
    cx, cy = robot_center[0:2]
    points = [[0,0],[0,0],[0,0],[0,0]]
    points[0] = [cx - 57, cy - 57]
    points[1] = [cx - 57, cy + 57]
    points[2] = [cx + 57, cy + 57]
    points[3] = [cx + 57, cy - 57]
    new_points = []
    for x_old, y_old in points:
        x_old -= cx
        y_old -= cy
        x_new = x_old * cos_val - y_old * sin_val
        y_new = x_old * sin_val + y_old * cos_val
        new_points.append([x_new + cx, y_new + cy])
    if (new_points[0][1] < 240):
        for x,y in new_points:
            if (x < 30 or x > 170):
                    return 0
            if (y > 125):
                    return 0
        pushButtonForA = 1
        return 1
    else:
        for x,y in new_points:
            if (x < 30 or x > 170):
                return 0
            if (y < 355):
                return 0
        pushButtonForC = 1
    return 1

def treasurePickerUpper():
    global treasureOnRobot
    time.sleep(2)
    angle = robot_center[2]
    angle = math.radians(float(angle))
    cos_val = math.cos(angle)
    sin_val = math.sin(angle)
    cx, cy = robot_center[0:2]
    points = [[0,0],[0,0],[0,0],[0,0]]
    points[0] = [cx - 57, cy - 57]
    points[1] = [cx - 57, cy + 57]
    points[2] = [cx + 57, cy + 57]
    points[3] = [cx + 57, cy - 57]
    new_points = []
    for x_old, y_old in points:
        x_old -= cx
        y_old -= cy
        x_new = x_old * cos_val - y_old * sin_val
        y_new = x_old * sin_val + y_old * cos_val
        new_points.append([x_new + cx, y_new + cy])
    for x,y in new_points:
        if (x < 765 or x > 885):
            return 0
        if (y < 180 or y > 300):
            return 0
    treasureOnRobot = 1
    draw_square(robot_center, "red")
    return 1

def flagTurner():
    global flagTurned
    time.sleep(2)
    angle = robot_center[2]
    angle = math.radians(float(angle))
    cos_val = math.cos(angle)
    sin_val = math.sin(angle)
    cx, cy = robot_center[0:2]
    points = [[0,0],[0,0],[0,0],[0,0]]
    points[0] = [cx - 60, cy - 57]
    points[1] = [cx - 57, cy + 57]
    points[2] = [cx + 57, cy + 57]
    points[3] = [cx + 57, cy - 57]
    new_points = []
    for x_old, y_old in points:
        x_old -= cx
        y_old -= cy
        x_new = x_old * cos_val - y_old * sin_val
        y_new = x_old * sin_val + y_old * cos_val
        new_points.append([x_new + cx, y_new + cy])
    for x,y in new_points:
        if (x < 840 or x):
            return 0
        if (y < 180 or y > 300):
            return 0
    flagTurned = 1
    init()
    draw_square(robot_center, "red")
    draw_treasure_chest_on_robot(robot_center)
    return 1
