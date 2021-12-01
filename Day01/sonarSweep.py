#!/usr/bin/env python3

#import urllib.request

def countIncrease(depth):
    count = 0
    previous = -1
    for measurement in depth:
        if previous == -1:
            pass
        else:
            if int(measurement) > previous:
                count += 1
        previous = int(measurement)
    return count
            
def windowSums(depth):
    windows = []
    for i in range(len(depth)-2):
        sum = int(depth[i]) + int(depth[i+1]) + int(depth[i+2])
        windows.append(sum)
    return windows

def main():
    #with urllib.request.urlopen('https://adventofcode.com/2021/day/1/input') as f:
    measurements = []
    with open('depth.txt') as f:
        measurements = f.readlines()
    windows = windowSums(measurements)
    #print("dir = {}".format(dir(windows)))
    #print("type = {}".format(type(windows)))
    print("[!] individual increases:/t {}".format(countIncrease(measurements)))
    print("[!] window increases:/t {}".format(countIncrease(windows)))

if __name__ == "__main__":
    main()
