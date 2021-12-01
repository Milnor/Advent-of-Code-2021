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
            

def main():
    #with urllib.request.urlopen('https://adventofcode.com/2021/day/1/input') as f:
    measurements = []
    with open('depth.txt') as f:
        measurements = f.readlines()
    print(countIncrease(measurements))

if __name__ == "__main__":
    main()
