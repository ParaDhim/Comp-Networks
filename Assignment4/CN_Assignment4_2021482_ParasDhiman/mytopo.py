from mininet.topo import Topo

class MyTopo(Topo):
	def build(self):
		#add switches
		s1 = self.addSwitch('s1')
		s2 = self.addSwitch('s2')
		s3 = self.addSwitch('s3')

		#add hosts
		h1 = self.addHost('h1')
		h2 = self.addHost('h2')
		h3 = self.addHost('h3')
		h4 = self.addHost('h4')
		h5 = self.addHost('h5')
		h6 = self.addHost('h6')

		#add links
		self.addLink(h1,s1)
		self.addLink(h2,s1)

		self.addLink(h3,s2)
		self.addLink(h4,s2)
		self.addLink(h2,s2)

		self.addLink(h5,s3)
		self.addLink(h2,s3)
		self.addLink(h6,s3)

		#add links with delay (packet loss)
		self.addLink(s1, s2, delay = '100ms', loss = 80)
		self.addLink(s2, s3, delay = '100ms', loss = 80)
topos = {'mytopo': (lambda: MyTopo())}
