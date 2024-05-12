import pyshark
import matplotlib.pyplot as plt

def extract_congestion_window(pcap_file):
    cap = pyshark.FileCapture(pcap_file)

    cwnd_values = []
    for packet in cap:
        try:
            cwnd = int(packet.tcp.window_size)
            cwnd_values.append(cwnd)
        except AttributeError:
            pass  # Some packets might not have TCP window size information

    return cwnd_values

def plot_congestion_window(cwnd_values):
    plt.plot(cwnd_values)
    plt.title('Congestion Window Evolution')
    plt.xlabel('Packet Number')
    plt.ylabel('Congestion Window Size')
    plt.show()

pcap_file_path = '/Users/parasdhiman/Downloads/final.pcap'
cwnd_values = extract_congestion_window(pcap_file_path)
plot_congestion_window(cwnd_values)




import pyshark
import matplotlib.pyplot as plt

def extract_congestion_window_and_time(pcap_file):
    cap = pyshark.FileCapture(pcap_file)

    cwnd_values = []
    time_values = []

    for packet in cap:
        try:
            cwnd = int(packet.tcp.window_size)
            time = float(packet.sniff_timestamp)

            cwnd_values.append(cwnd)
            time_values.append(time)
        except AttributeError:
            pass  # Some packets might not have TCP window size or timestamp information

    return cwnd_values, time_values

def plot_congestion_window_over_time(cwnd_values, time_values):
    plt.plot(time_values, cwnd_values, marker='o', linestyle='-', color='b')
    plt.title('Congestion Window Over Time')
    plt.xlabel('Time (seconds)')
    plt.ylabel('Congestion Window Size')
    plt.grid(True)
    plt.show()

pcap_file_path = '/Users/parasdhiman/Downloads/final.pcap'
cwnd_values, time_values = extract_congestion_window_and_time(pcap_file_path)
plot_congestion_window_over_time(cwnd_values, time_values)
