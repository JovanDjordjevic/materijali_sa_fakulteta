package i01_chargen;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.Channels;
import java.nio.channels.SocketChannel;
import java.nio.channels.WritableByteChannel;

final class ChargenClientNonBlocking {
	
	public static void main(String[] args) {
		String host = "localhost";
		int port = 19000;

		//kada hocemo da imamo neblokirajuci IO, korsitimo kanale. Konkretno ovde koristimo SocketChannel. On se konstruise statickom metodom open() iz
		//SocekChannle klase, kao arg mora da primi SocketAdressu,tu dajemo hostname i port servera na koji se povezujemo
		//taj SocketChannel koji napravimo korsiticemo za komunikaciu, u njemu imamo read i write metode
		//open je blokirajuci poziv, on ce interno raditi connect tako da moramo da uhvatimo IOException
		try {
			SocketAddress address = new InetSocketAddress(host, port);
			SocketChannel client = SocketChannel.open(address);

			//primetimo da za razliku od onoga sto smo radili sa socketima, ovde i u read i write metode prosledjumeo ByteBuffer u kom su podaci
			//ByteBuffer je samo wrapper za obicni byte[], ali psoto nam je u radu sa kanalima potrebno jos informacija (nedovoljan anm je samo size koji daje  byte[])
			//koristimo ByteBuffer (treba nam da znmo koliko smo procitali, dokle smo stigli itd, pise ispod)

			/*
			 A buffer is a linear, finite sequence of elements of a specific primitive type.
			 Aside from its content, the essential properties of a buffer are its capacity,
			 limit, and position:
			 - Capacity is the number of elements it contains. The capacity of a buffer
			   is never negative and never changes.
			 - Limit is the index of the first element that should not be read or written.
			   A buffer's limit is never negative and is never greater than its capacity.
			 - Position is the index of the next element to be read or written. A buffer's
			   position is never negative and is never greater than its limit.
			 */
			ByteBuffer buffer = ByteBuffer.allocate(74);

			//mozemo napraviti kanal do BILO KOG input ili output streama
			//ovo nam omogucava da sa ovim kanalom kkomuniciramo isto kao sa serverom
			WritableByteChannel out = Channels.newChannel(System.out);

			//iako je ovo neblokirajuci API, kanali se po defaultu otvaraju u blokirajucem rezimu, pa moramo rucno da stavimo da ne blokiraju
			client.configureBlocking(false);
			
			// In non-blocking mode, read() may return 0 because it doesn’t read anything. 
			// Therefore the loop needs to be a little different:
			while (true) {

				// Put whatever code here you want to run every pass through the loop
				// whether anything is read or not

				// Then perform read, and check if anything is read
				//client.read(buffer) procita bajtove iz socketa i ubacuje u buffer, a vraca broj procitanih bajtova
				int n = client.read(buffer);
				if (n > 0) {
					//posto isti bafer koristimo i za citanje i za pisanje, potrebno je da ga na neki nacin pripremimo
					// NOTE: kada prvi put napravimo bafer, on je vec spreman za read od pcoetka bafera
					//ali za WRITE moramo da ga pripremimo, pozivamo metod flip() (ovaj metod ne okrece bukvalno bafer):
					// [1 2 3 4 5 x x x x x] capacity = 10, (na pocetku pre iakkvog citanja, P=0, L=capacity
					//            P       L    ovde su limit i pozicija (posle prvog ovog citanja 1 2 3 4 5)
					//flip radi: L=P, P=0
					//  P         L
					//nakon write, moramo da pripremimo vafer za sledeci READ, to radi metod clear()
					// clear radi: P=0, L=capacity (clear se samo tako zove, on ne cisti bukvano bafer, nego samo menja ovce interne pokazivace)

					/*
					In addition to methods for accessing the position, limit, and capacity
					values and for marking and resetting, Buffer class also defines the following
					operations upon buffers:
    				- clear() makes a buffer ready for a new sequence of channel-read or relative put
    				  operations: It sets the limit to the capacity and the position to zero.
    				- flip() makes a buffer ready for a new sequence of channel-write or relative get
    				  operations: It sets the limit to the current position and then sets the position to zero.
    				- rewind() makes a buffer ready for re-reading the data that it already contains:
    				  It leaves the limit unchanged and sets the position to zero.
					 */

					// Prepare the buffer for writing
					buffer.flip();
					// Perform write (nad onim kanalom koji smo otrvorili gore ka stdout)
					out.write(buffer);
					// Prepare the buffer for reading
					buffer.clear();

				} else if (n == -1) {
					// This shouldn't happen unless the server is misbehaving.
					break;
				}
			}
		} catch (IOException ex) {
			ex.printStackTrace( );
		}
		
	}
}
