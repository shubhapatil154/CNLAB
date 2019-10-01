#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
using namespace ns3;
NS_LOG_COMPONENT_DEFINE("SecondScriptExample");
int main(int argc,char *argv[])
{
	bool verbose= true;
	uint32_t nCsma = 2;

	CommandLine cmd;
	cmd.AddValue("nCsma","Number of\"extra\"CSMA nodes/devices",nCsma);
	cmd.AddValue("verbose","Tell echo applications to log if true",verbose);
	
	cmd.Parse(argc,argv);

	if(verbose)
	{
		LogComponentEnable("UdpEchoClientApplication",LOG_LEVEL_INFO);
		LogComponentEnable("UdpEchoServerApplication",LOG_LEVEL_INFO);
	}

	nCsma=nCsma==0?1:nCsma;

	NodeContainer p2pNodes;
	p2pNodes.Create(2);

	NodeContainer p2pNodes1;
	p2pNodes1.Create(2);

	NodeContainer csmaNodes;
	csmaNodes.Add(p2pNodes.Get(1));
	csmaNodes.Create(nCsma);
	csmaNodes.Add(p2pNodes1.Get(0));

	PointToPointHelper pointToPoint;
	pointToPoint.SetDeviceAttribute("DataRate",StringValue("5Mbps"));
	pointToPoint.SetChannelAttribute("Delay",StringValue("2ms"));

	CsmaHelper csma;
	csma.SetChannelAttribute("DataRate",StringValue("100Mbps"));
	csma.SetChannelAttribute("Delay",TimeValue(NanoSeconds(6560)));

	PointToPointHelper pointToPoint1;
	pointToPoint1.SetDeviceAttribute("DataRate",StringValue("5Mbps"));
	pointToPoint1.SetChannelAttribute("Delay",StringValue("2ms"));

	NetDeviceContainer p2pDevices;
	p2pDevices = pointToPoint.Install(p2pNodes);

	NetDeviceContainer csmaDevices;
	csmaDevices = csma.Install(csmaNodes);

	
	NetDeviceContainer p2pDevices1;
	p2pDevices1 = pointToPoint1.Install(p2pNodes1);

	InternetStackHelper stack;
	stack.Install(p2pNodes.Get(0));
	stack.Install(csmaNodes);
	stack.Install(p2pNodes1.Get(1));

	Ipv4AddressHelper address;
	address.SetBase("10.1.1.0","255.255.255.0");
	Ipv4InterfaceContainer p2pInterfaces;
	p2pInterfaces=address.Assign(p2pDevices);

	address.SetBase("10.1.2.0","255.255.255.0");
	Ipv4InterfaceContainer csmaInterfaces;
	csmaInterfaces=address.Assign(csmaDevices);

	address.SetBase("10.1.3.0","255.255.255.0");
	Ipv4InterfaceContainer p2pInterfaces1;
	p2pInterfaces1=address.Assign(p2pDevices1);

	UdpEchoServerHelper echoServer(9);

	ApplicationContainer serverApps=echoServer.Install(csmaNodes.Get(nCsma));
	serverApps.Start(Seconds(1.0));
	serverApps.Stop(Seconds(10.0));

	UdpEchoServerHelper echoServer1(10);
	
	ApplicationContainer serverApps1=echoServer1.Install(csmaNodes.Get(nCsma));
	serverApps1.Start(Seconds(1.0));
	serverApps1.Stop(Seconds(10.0));

	UdpEchoClientHelper echoClient(csmaInterfaces.GetAddress(nCsma),9);
	echoClient.SetAttribute("MaxPackets",UintegerValue(1));
	echoClient.SetAttribute("Interval",TimeValue(Seconds(1.0)));
	echoClient.SetAttribute("PacketSize",UintegerValue(1024));

	ApplicationContainer clientApps=echoClient.Install(p2pNodes.Get(0));
	clientApps.Start(Seconds(2.0));
	clientApps.Stop(Seconds(10.0));

	
	UdpEchoClientHelper echoClient1(csmaInterfaces.GetAddress(nCsma),10);
	echoClient.SetAttribute("MaxPackets",UintegerValue(2));
	echoClient.SetAttribute("Interval",TimeValue(Seconds(1.0)));
	echoClient.SetAttribute("PacketSize",UintegerValue(512));


	ApplicationContainer clientApps1=echoClient1.Install(p2pNodes1.Get(1));
	clientApps1.Start(Seconds(2.0));
	clientApps1.Stop(Seconds(10.0));

	Ipv4GlobalRoutingHelper::PopulateRoutingTables();
	pointToPoint.EnablePcapAll("second");
	csma.EnablePcap("second",csmaDevices.Get(1),true);
	pointToPoint1.EnablePcapAll("second");

	Simulator::Run();
	Simulator::Destroy();
	return 0;
}

/***********************************************OUTPUT**********************************************************************/

At time 2s client sent 1024 bytes to 10.1.2.3 port 9
At time 2s client sent 100 bytes to 10.1.2.3 port 10
At time 2.0078s server received 1024 bytes from 10.1.1.1 port 49153
At time 2.0078s server sent 1024 bytes to 10.1.1.1 port 49153
At time 2.00825s server received 100 bytes from 10.1.3.2 port 49153
At time 2.00825s server sent 100 bytes to 10.1.3.2 port 49153
At time 2.0135s client received 100 bytes from 10.1.2.3 port 10
At time 2.01461s client received 1024 bytes from 10.1.2.3 port 9
At time 3s client sent 100 bytes to 10.1.2.3 port 10
At time 3.00223s server received 100 bytes from 10.1.3.2 port 49153
At time 3.00223s server sent 100 bytes to 10.1.3.2 port 49153
At time 3.00445s client received 100 bytes from 10.1.2.3 port 10
At time 4s client sent 100 bytes to 10.1.2.3 port 10
At time 4.00223s server received 100 bytes from 10.1.3.2 port 49153
At time 4.00223s server sent 100 bytes to 10.1.3.2 port 49153
At time 4.00445s client received 100 bytes from 10.1.2.3 port 10
At time 5s client sent 100 bytes to 10.1.2.3 port 10
At time 5.00223s server received 100 bytes from 10.1.3.2 port 49153
At time 5.00223s server sent 100 bytes to 10.1.3.2 port 49153
At time 5.00445s client received 100 bytes from 10.1.2.3 port 10
At time 6s client sent 100 bytes to 10.1.2.3 port 10
At time 6.00223s server received 100 bytes from 10.1.3.2 port 49153
At time 6.00223s server sent 100 bytes to 10.1.3.2 port 49153
At time 6.00445s client received 100 bytes from 10.1.2.3 port 10
At time 7s client sent 100 bytes to 10.1.2.3 port 10
At time 7.00223s server received 100 bytes from 10.1.3.2 port 49153
At time 7.00223s server sent 100 bytes to 10.1.3.2 port 49153
At time 7.00445s client received 100 bytes from 10.1.2.3 port 10
At time 8s client sent 100 bytes to 10.1.2.3 port 10
At time 8.00223s server received 100 bytes from 10.1.3.2 port 49153
At time 8.00223s server sent 100 bytes to 10.1.3.2 port 49153
At time 8.00445s client received 100 bytes from 10.1.2.3 port 10
At time 9s client sent 100 bytes to 10.1.2.3 port 10
At time 9.00223s server received 100 bytes from 10.1.3.2 port 49153
At time 9.00223s server sent 100 bytes to 10.1.3.2 port 49153
At time 9.00445s client received 100 bytes from 10.1.2.3 port 10
