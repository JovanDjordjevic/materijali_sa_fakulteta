package i03_daytime_service;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

//primer klijenta koji trazi od servera trenutno vreme

//u ovom primeru je pokazao NetCat alat. Na linuksu, kad ga isntaliramo, mozmeo napraviti nekakav mock server
//koji ce nam sluziti za testiranje klijenta pre nego sto smo napisali deo koda koji je server
//Otvorimo 2 terminala i kucamo ove komande:
// nc -l 1234  (je kao server. On slusa (to je -l) na portu 12345)
//nc localhost 12345 (je kao client, on se konektuje na adresu localhost na port 12345)
//sada ono sto napisemo na jednom terminalu bice poslato drugom
//Mozemo i samo napraviti server i onda kada pokrenemo nas program, iz tog terminala gde je server mozemo da posaljemo neku poruku
//Obrnuto, mozemo napraviti i samo klijent da bismo testirali nas server

final class DaytimeClient {

	public static void main(String[] args) {
		//posto testiramo lokalno, dovoljno nam je ovo
		String hostname = "localhost";

		System.err.println("Connecting to " + hostname);
		try (Socket sock = new Socket(hostname, DaytimeServer.DEFAULT_PORT)) {   //u dugoj klasi smo definisali ovaj neki port, nebitno nam je koji je u ovom primeru
			System.err.println("Connected!");
			try (BufferedReader in = new BufferedReader(
					new InputStreamReader(sock.getInputStream()))
			) {
				// We expect that server will send a line upon connection
				//mogli smo BufferedInputStream umesto Readers, nego posto smo npr odlucili da server salje jednu liniju, a u
				//Reader vec imaom ugradjen metod za to, koristimo Reader
				String time = in.readLine().trim();
				System.out.println("It is " + time + " at " + hostname);
			}
		} catch (IOException ex) {
			ex.printStackTrace();
		}

	}

}
