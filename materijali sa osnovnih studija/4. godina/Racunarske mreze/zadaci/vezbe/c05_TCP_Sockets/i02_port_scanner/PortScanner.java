package i02_port_scanner;

import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Date;

//programcic koji testira na kojim portovima neki server slusa klijenate

final class PortScanner {

	public static void main(String[] args) {
		//posto je rad sa alasom spor i ovaj program bi mnogo trajao, mozemo da probamo i:
		//String host = "localhost"
		String host = "alas.matf.bg.ac.rs";
		System.out.println("Start time: " + new Date());

		//npr pordjemo kroz sve moguce portove
		for (int port = 1; port < 65536; port++) {

			// \r - je carriage return. Ovaj spec simbol kaze da se ispis vraca na pcoetak linije (obrnuto od \n)
			//pazimo samo da posto ce se prepisati preko onoga sto je vec napisano, da pazimo da ne ostaje djubre od proslog puta
			// pokreni program da vidis ispis koji dobijamo. \r prelazi na sledecu liniju tek kada ispisemo \n
			System.out.printf("\rTesting port: %5d", port);
			
			try (Socket s = new Socket(host, port)) {
				System.out.println("\rSocket data: " + s);
				System.out.println("Found @ " + new Date());
			} catch (UnknownHostException ex) {
				ex.printStackTrace();
				break;
			} catch (IOException ex) {
				// Ignored, no server listening on port
			}
		}

		System.out.println("\rEnd time: " + new Date());
	}

}
