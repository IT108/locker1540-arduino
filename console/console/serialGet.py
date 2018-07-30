import serial
import time


def get_card(comport):
    ser = serial.Serial(comport, 9600)
    delt = 0
    last = 0
    while 1:
        time.sleep(0.01)
        delt = ser.in_waiting - last
        if ser.in_waiting > 1 and delt == 0:
            x = ser.read(ser.in_waiting)
            x = x[1:9]
            print(x)
        last = ser.in_waiting
