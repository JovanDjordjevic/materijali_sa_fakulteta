package i01_udp_sockets_intro;

import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

final class UDPIntro {

	/*
		Java’s implementation of UDP is split into two classes:
		DatagramPacket and DatagramSocket. The DatagramPacket class stuffs bytes of
		data into UDP packets called datagrams and lets you unstuff datagrams that
		you receive. A DatagramSocket sends as well as receives UDP datagrams. To
		send data, you put the data in a DatagramPacket and send the packet using a
		DatagramSocket. To receive data, you take a DatagramPacket object from a
		DatagramSocket and then inspect the contents of the packet. In UDP,
		everything about a datagram, including the address to which it is directed,
		is included in the packet itself; the socket only needs to know the local
		port on which to listen or send.
	*/

	//u UDP protokolu, imamo samo jedan tip soketa i za client i za server

	public static void main(String[] args) {
		// Specific local port will be used for servers, random if not specified
		try (DatagramSocket ds = new DatagramSocket()) {

			// For sending, we need to provide endpoint - receiver's IP and port
			InetAddress host = InetAddress.getByName("host");

			//primetimo da psotoji puno razLicitih konstruktora za DatagramPacket, jer istiu ovu klasu korsitimo i za slanje i za primanje podataka
			//ako saljemo konstruktoru cemo dati i informaciju o adresi i portu na koji saljemo
			//prvi arg je bajt niz u kom su podaci,a  drugi je njegova duzina u bajtovima (?)
			DatagramPacket send = new DatagramPacket(new byte[512], 512, host, 12345);

			// For receiving, we do not specify endpoint (kad primamo podatke, ne trebaju nam host i port)
			DatagramPacket recv = new DatagramPacket(new byte[512], 512);

			// We use DatagramSocket class to send and receive DatagramPackets
			ds.send(send);
			ds.receive(recv);

			//kad uradimo recieve, iz recv mozemo izvuci neke ptorebne podatke

		} catch (IOException e) { //pravljenje DatagramSocekta baca SocketException, a new DatagramPacket baca UnknownHostException
			e.printStackTrace();  //ali to su obe potklase IOExceptiona tako da mozemod a ih spojimo u jedan blok
		}
	}

}
