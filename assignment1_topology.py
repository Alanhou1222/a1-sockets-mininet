#!/usr/bin/env python
"""
Measurement topology for EECS489, Winter 2024, Assignment 1
"""

from mininet.cli import CLI
from mininet.net import Mininet
from mininet.link import TCLink
from mininet.topo import Topo
from mininet.log import setLogLevel

class AssignmentNetworks(Topo):
    def __init__(self, **opts):
        Topo.__init__(self, **opts)
        # This part adds each individual host
        # and returns an object of each one
        h1 = self.addHost('h1')
        h2 = self.addHost('h2')
        h3 = self.addHost('h3')
        h4 = self.addHost('h4')
        h5 = self.addHost('h5')
        h6 = self.addHost('h6')
        h7 = self.addHost('h7')
        h8 = self.addHost('h8')
        h9 = self.addHost('h9')
        h10 = self.addHost('h10')

        # This part adds each switch in the network
        s1 = self.addSwitch('s1')
        s2 = self.addSwitch('s2')
        s3 = self.addSwitch('s3')
        s4 = self.addSwitch('s4')
        s5 = self.addSwitch('s5')
        s6 = self.addSwitch('s6')

        # This part specifies the links from host to switch
        self.addLink(h1, s1)
        self.addLink(h2, s1)
        self.addLink(h5, s1)
        self.addLink(h3, s2)
        self.addLink(h4, s3)
        self.addLink(h7, s4)
        self.addLink(h8, s5)
        self.addLink(h6, s6)
        self.addLink(h9, s6)
        self.addLink(h10, s6)

        # This specifies the links between switches, with additional
        # information for the bandwidth and delay specified
        self.addLink(s1, s2, bw=20, delay='40ms')
        self.addLink(s2, s3, bw=40, delay='10ms')
        self.addLink(s2, s4, bw=30, delay='30ms')
        self.addLink(s3, s5, bw=25, delay='5ms')
        self.addLink(s5, s6, bw=25, delay='5ms')
        
        
if __name__ == '__main__':
    setLogLevel( 'info' )

    # Create data network
    topo = AssignmentNetworks()
    net = Mininet(topo=topo, link=TCLink, autoSetMacs=True,
           autoStaticArp=True)

    # Run network
    net.start()
    h1 = net.get('h1')
    h2 = net.get('h2')
    h3 = net.get('h3')
    h4 = net.get('h4')
    h5 = net.get('h5')
    h6 = net.get('h6')
    h7 = net.get('h7')
    h8 = net.get('h8')
    h9 = net.get('h9')
    h10 = net.get('h10')
    # Q1
    # h1.cmd('ping -c 20 10.0.0.3 > latency_L1.txt')
    # h3.cmd('ping -c 20 10.0.0.4 > latency_L2.txt')
    # h3.cmd('ping -c 20 10.0.0.7 > latency_L3.txt')
    # h4.cmd('ping -c 20 10.0.0.8 > latency_L4.txt')
    # h8.cmd('ping -c 20 10.0.0.9 > latency_L5.txt')

    # h3.cmd('iperf3 -s -p 8888 --one-off &')
    # h1.cmd('iperf3 -c 10.0.0.3 -p 8888 -t 20 > throughput_L1.txt')
    # h4.cmd('iperf3 -s -p 8888 --one-off &')
    # h3.cmd('iperf3 -c 10.0.0.4 -p 8888 -t 20 > throughput_L2.txt')
    # h7.cmd('iperf3 -s -p 8888 --one-off &')
    # h3.cmd('iperf3 -c 10.0.0.7 -p 8888 -t 20 > throughput_L3.txt')
    # h8.cmd('iperf3 -s -p 8888 --one-off &')
    # h4.cmd('iperf3 -c 10.0.0.8 -p 8888 -t 20 > throughput_L4.txt')
    # h9.cmd('iperf3 -s -p 8888 --one-off &')
    # h8.cmd('iperf3 -c 10.0.0.9 -p 8888 -t 20 > throughput_L5.txt')

    # Q2
    # h1.cmd('ping -c 20 10.0.0.10 > latency_Q2.txt')
    # h10.cmd('iperf3 -s -p 8888 --one-off &')
    # h1.cmd('iperf3 -c 10.0.0.10 -p 8888 -t 20 > throughput_Q2.txt')

    # Q3
    # h1.cmd('ping -c 20 10.0.0.10 > latency_Q3_1_10.txt &')
    # h2.cmd('ping -c 20 10.0.0.9 > latency_Q3_2_9.txt &')
    # h5.cmd('ping -c 20 10.0.0.6 > latency_Q3_5_6.txt')
    # h10.cmd('iperf3 -s -p 8888 --one-off &')
    # h9.cmd('iperf3 -s -p 7777 --one-off &')
    # h6.cmd('iperf3 -s -p 6666 --one-off &')
    # h1.cmd('iperf3 -c 10.0.0.10 -p 8888 -t 20 > throughput_Q3_1_10.txt &')
    # h2.cmd('iperf3 -c 10.0.0.9 -p 7777 -t 20 > throughput_Q3_2_9.txt &')
    # h5.cmd('iperf3 -c 10.0.0.6 -p 6666 -t 20 > throughput_Q3_5_6.txt')

    # Q4
    h1.cmd('ping -c 20 10.0.0.10 > latency_h1-h10.txt &')
    h3.cmd('ping -c 20 10.0.0.8 > latency_h3-h8.txt')
    h10.cmd('iperf3 -s -p 8888 --one-off &')
    h8.cmd('iperf3 -s -p 7777 --one-off &')
    h1.cmd('iperf3 -c 10.0.0.10 -p 8888 -t 20 > throughput_h1-h10.txt &')
    h3.cmd('iperf3 -c 10.0.0.8 -p 7777 -t 20 > throughput_h3-h8.txt')
    CLI( net )
    net.stop()

