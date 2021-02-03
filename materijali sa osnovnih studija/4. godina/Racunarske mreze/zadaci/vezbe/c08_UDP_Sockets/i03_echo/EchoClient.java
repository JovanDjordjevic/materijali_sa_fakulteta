
package i03_echo;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;

final class EchoClient implements AutoCloseable {
	private final DatagramSocket socket;
	private final InetAddress address;
	private final int port;


	EchoClient(String host, int port) throws IOException {
		this.socket = new DatagramSocket();
		this.socket.setSoTimeout(5000);
		this.address = InetAddress.getByName(host);
		this.port = port;
	}


	String sendEcho(String msg) throws IOException {
		// Get message bytes
		byte[] buf = msg.getBytes(StandardCharsets.UTF_8);
		System.err.println("Client send: " + msg + " " + Arrays.toString(buf));

		// Create packet and send to server
		DatagramPacket request = new DatagramPacket(buf, buf.length, this.address, this.port);
		this.socket.send(request);

		// Get response (server treba da vrati isti string koji smo mu poslali, tako da mozemo i ovde da korsitimo buf.length)
		DatagramPacket response = new DatagramPacket(buf, buf.length);
		this.socket.receive(response);
		System.err.println("Client recv: " + Arrays.toString(response.getData()));

		// Return parsed resposnse data (da bis e ispisalo u Test klasi)
		return new String(response.getData(), 0, response.getLength(), StandardCharsets.UTF_8);
	}

	//moramo AutoCloseable da bitmo u Test klasi mogli da koristimo try with resources
	@Override
	public void close() {
		this.socket.close();
	}
}
