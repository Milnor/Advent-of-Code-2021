#!/usr/bin/env python3
""" Quick prototype for Advent of Code 2021 Challenges """

import sys

def calculate_position(moves):
    """ Calculate x,y position based on movement input """
    x = 0
    y = 0
    for line in moves:
        if line.startswith("forward"):
            x += int(line[-2])
        elif line.startswith("up"):
            y -= int(line[-2])
        elif line.startswith("down"):
            y += int(line[-2])
        else:
            sys.stderr.write("[-] bad movement input: {}\n".format(line))

    return x, y


def main():
    """ Parse data and display results of Day 1 Challenges """
    movements = []
    with open('../../data/02movement.txt') as data_file:
        movements = data_file.readlines()

    horiz, depth = calculate_position(movements)
    print("[!] horizontal position:\t{}\n".format(horiz))
    print("[!] depth:\t\t\t{}\n".format(depth))
    print("[!] result:\t\t\t{}\n".format(horiz * depth))


if __name__ == "__main__":
    main()
