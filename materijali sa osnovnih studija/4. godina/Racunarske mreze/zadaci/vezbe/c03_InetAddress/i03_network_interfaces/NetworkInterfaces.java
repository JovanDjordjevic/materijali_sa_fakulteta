package i03_network_interfaces;

import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Comparator;
import java.util.Enumeration;

final class NetworkInterfaces {

	// https://docs.oracle.com/javase/tutorial/networking/nifs/listing.html
	
	public static void main(String[] args) {

		// Lists all network interfaces

		try {
			//network interfejs je nesto sto razdvaja nas racunar od interneta (?)
			//moze biti fizicki (npr mrezna kartica, ethernet) i virtuelni (npr u virtuelnim masinama (?))

			// Classic enumeration variant
			//Enumeration<NetworkInterface> je tip koji vraca getNetworkInterfaces() metod.
			//Ovaj metod vraca sve network interfejse koji postoje na sistemu (?)
			Enumeration<NetworkInterface> interfaces = NetworkInterface.getNetworkInterfaces();
			while (interfaces.hasMoreElements()) {
				NetworkInterface ni = interfaces.nextElement();
				System.out.println(ni);
				System.out.println("\t" + ni.getName() + "\t" + ni.getDisplayName() + "\t" + ni.getIndex());

				//na slican nacin mozemo dohvatiti i sve IP adrese (?)
				Enumeration<InetAddress> addresses = ni.getInetAddresses();
				while (addresses.hasMoreElements())
					System.out.println("\t" + addresses.nextElement());
			}

			System.out.println("--- \"loops are evil\" ---");

			// Stream<T> variant
			//primetimo da smo imali jos jedan metod: networkInterfaces() koji vraca iste podatke kao i ovaj getNetworkInterfaces, samo sto
			//ih vrati kao Stream<NetworkInterface> a ne kao Enumeration
			//Radimo isto sto i malopre samo sa stream pristupom
			NetworkInterface.networkInterfaces()
					.sorted(Comparator.comparingInt(NetworkInterface::getIndex)) //ovo smo radili za primer, nismo zapravo morali da sortiramo nista
																				 //mogli smo i sami da pismo komparator funkciju, ali smo koristili ugradjenu, i poredili po indeksu
					.map(ni ->		//ako samo provamo .forEach(System.out::println) na ovo sto smo dobili sortiranjem, ispisivacemo objekte, tako da mozemo prvo mapirati u neki zapis koji zelimo
							ni.toString() + "\n\t"
							+ ni.getName() + "\t" + ni.getDisplayName() + "\t" + ni.getIndex() + "\n\t"
							+ ni.inetAddresses()
									.map(InetAddress::toString)
									.reduce((acc, ip) -> acc + "\n\t" + ip)	//reduce vraca Optional<String> iz razloga sto kolekcija mzoe biti prazna
									.orElse("?")							//pa mzoemo ovo da radimo ako je taj Optional prazan
					)
					.forEach(System.out::println)
					;
		} catch (SocketException ex) {
			ex.printStackTrace();
		}
	}

}
