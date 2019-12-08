from argparse import ArgumentParser
import csv
import matplotlib.pyplot as plt

if __name__ == "__main__":
    # parse command-line argument(s)
    parser = ArgumentParser(description="Plots encoder data from a CSV log file.")
    parser.add_argument("file", help="path to the CSV log file")
    args = parser.parse_args()
    
    # read the data from the CSV file
    timestamps = []
    positions = []
    with open(args.file) as f:
        for timestamp, position in csv.reader(f):
            timestamps.append(int(timestamp))
            positions.append(float(position))
    
    # plot the data
    plt.title("Motor log")
    plt.plot(timestamps, positions)
    plt.xlabel("Milliseconds since PROS initialized")
    plt.ylabel("Current draw (mA)")
    plt.show()
