import select
import socket
import time
import sys

from impacket import ImpactDecoder, ImpactPacket

src = "127.0.0.1"
#src = raw_input("source ip:\n")
dst = "127.0.0.1"
#dst = raw_input("destination ip:\n")

# Create a new IP packet and set its source and destination addresses.

ip = ImpactPacket.IP()
ip.set_ip_src(src)
ip.set_ip_dst(dst)

# Create a new ICMP packet of type ECHO.

icmp = ImpactPacket.ICMP()
icmp.set_icmp_type(icmp.ICMP_ECHO)

# Include a 156-character long payload inside the ICMP packet.
icmp.contains(ImpactPacket.Data("A"*156))

# Have the IP packet contain the ICMP packet (along with its payload).
ip.contains(icmp)

# Open a raw socket. Special permissions are usually required.
s = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_ICMP)
s.setsockopt(socket.IPPROTO_IP, socket.IP_HDRINCL, 1)

seq_id = 0
while 1:
    # Give the ICMP packet the next ID in the sequence.
	seq_id += 1
	icmp.set_icmp_id(seq_id)

	# Calculate its checksum.
	icmp.set_icmp_cksum(0)
	icmp.auto_checksum = 1

	# Send it to the target host.
	s.sendto(ip.get_packet(), (dst, 0))

	# Wait for incoming replies.
	if s in select.select([s],[],[],1)[0]:
	   reply = s.recvfrom(2000)[0]

	   # Use ImpactDecoder to reconstruct the packet hierarchy.
	   rip = ImpactDecoder.IPDecoder().decode(reply)
	   # Extract the ICMP packet from its container (the IP packet).
	   ricmp = rip.child()
       
       if rip.get_ip_dst() == src and rip.get_ip_src() == dst and icmp.ICMP_ECHOREPLY == ricmp.get_icmp_type():
           print "Ping reply for sequence #%d" % ricmp.get_icmp_id()
           
       time.sleep(1)