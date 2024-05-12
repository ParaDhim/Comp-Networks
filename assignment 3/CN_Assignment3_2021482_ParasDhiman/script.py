import pandas as pd
import matplotlib.pyplot as plt
from scapy.all import *
lst = ["epoll.pcap","epoll1.pcap","epoll2.pcap","fork.pcap","poll.pcap","poll1.pcap","poll2.pcap","select.pcap","select1.pcap","select2.pcap","server1c.pcap","server2c.pcap","server11.pcap","server12.pcap","thread.pcap"]
# Read the pcap file
for nm in lst:
    pcap_file = nm
    packets = rdpcap(pcap_file)

    data = []
    for packet in packets:
        if TCP in packet and IP in packet:
            src_ip = packet[IP].src
            dst_ip = packet[IP].dst
            src_port = packet[TCP].sport
            dst_port = packet[TCP].dport
            length = len(packet)
            timestamp = packet.time

            data.append({
                "src_ip": src_ip,
                "dst_ip": dst_ip,
                "src_port": src_port,
                "dst_port": dst_port,
                "length": length,
                "timestamp": timestamp,
            })

    df = pd.DataFrame(data)

    grouped = df.groupby(['src_ip', 'dst_ip', 'src_port', 'dst_port'])

    metrics = pd.DataFrame()
    metrics['Average Throughput (bps)'] = grouped['length'].sum() * 8 / (grouped['timestamp'].max() - grouped['timestamp'].min() + 0.1)
    metrics['Average Latency (ms)'] = (grouped['timestamp'].max() - grouped['timestamp'].min()) * 1000

    metrics['Average Throughput (bps)'] = pd.to_numeric(metrics['Average Throughput (bps)'], errors='coerce')
    metrics['Average Latency (ms)'] = pd.to_numeric(metrics['Average Latency (ms)'], errors='coerce')

    # Calculate overall average throughput and latency
    average_throughput = metrics['Average Throughput (bps)'].mean()
    average_latency = metrics['Average Latency (ms)'].mean()

    print(f"Average Throughput for TCP Flows: {average_throughput} bps")
    print(f"Average Latency for TCP Flows: {average_latency} ms")

    # Convert columns to NumPy arrays before indexing
    throughput_values = metrics['Average Throughput (bps)'].to_numpy()
    latency_values = metrics['Average Latency (ms)'].to_numpy()

    # Plot the data
    plt.figure(figsize=(12, 6))
    plt.subplot(1, 2, 1)
    plt.plot(range(len(metrics)), throughput_values, marker='o')
    plt.title('Average Throughput for TCP Flows')
    plt.ylabel('Throughput (bps)')
    plt.xlabel('Flow')

    plt.subplot(1, 2, 2)
    plt.plot(range(len(metrics)), latency_values, marker='o')
    plt.title('Average Latency for TCP Flows')
    plt.ylabel('Latency (ms)')
    plt.xlabel('Flow')

    plt.tight_layout()
    plt.show()