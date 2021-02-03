package i02_intgen;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.nio.channels.SocketChannel;

final class IntgenClient {

	public static void main(String[] args) {
		InetSocketAddress addr = new InetSocketAddress("localhost", IntgenServer.DEFAULT_PORT);

		// Client is left in `blocking` mode on purpose, since there is no other
		// work he has to do other than receive data from server
		try (SocketChannel client = SocketChannel.open(addr)) {

			// We allocate 4 bytes - enough for one integer
			ByteBuffer buffer = ByteBuffer.allocate(4);

			// We can create a "view" of the underlying bytes
			//ovako je lakse za rad, mozemo obican bytebuffer tretiraki kao neki integer buffer
			IntBuffer view = buffer.asIntBuffer();

			//znamo da server salje brojeve od 0 pa navise, i testiramo ono sto smo primili
			for (int expected = 0; ; expected++) {

				// Since read() might not fill the whole buffer,
				// we do it in a loop
				//u prolsom primeru nismo morali ovo da radimo jer smo samo ispisivali na standardni izlaz
				//ali ovde moramo da sacekamo da sva 4 bajta iz bafera budu puna da bismo mogli da posmatramo podatak kao integer
				while (buffer.hasRemaining())
					client.read(buffer);

				//NOTE: posto je u ovom primeru posao klijenta samo da cita ono sto server salje, prihvatljivo je da imamo neko manje blokiranje u read()
				//tako da nismo morali ovde da radimo configure da bude neblokirajuci, naravno mogli smo ako bas zelimo

				int received = view.get();

				// Prepare for next read() call
				buffer.clear();

				// Prepare for next get() call
				view.rewind();

				if (received != expected) {
					System.err.println("Expected: " + expected + "; got: " + received);
					break;
				}

				System.out.println(received);
			}
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}

}
