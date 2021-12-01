#!/usr/bin/env python3
""" Quick prototype for Advent of Code 2021 Challenges """

def count_increase(depth):
    """ Count number of times that n+1 is greater than n """
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

def window_sums(depth):
    """ Convert list of data points to sums of three-point sliding windows """
    windows = []
    for i in range(len(depth)-2):
        int_sum = int(depth[i]) + int(depth[i+1]) + int(depth[i+2])
        windows.append(int_sum)
    return windows

def main():
    """ Parse data and display results of Day 1 Challenges """
    measurements = []
    with open('../../data/01depth.txt') as data_file:
        measurements = data_file.readlines()
    windows = window_sums(measurements)
    print("[!] individual increases:\t {}".format(count_increase(measurements)))
    print("[!] window increases:\t\t {}".format(count_increase(windows)))

if __name__ == "__main__":
    main()
