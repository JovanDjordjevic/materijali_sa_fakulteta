package i01_intro;
import java.net.Inet4Address;
import java.net.Inet6Address;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.Arrays;

final class InetAddressIntro {

	/*
		Devices connected to the Internet are called nodes. Nodes that are computers are called
		hosts. Each node or host is identified by at least one unique number called an Internet
		address or an IP address. Most current IP addresses are four bytes long; these are
		referred to as IPv4 addresses. However, a small but growing number of IP addresses are
		16 bytes long; these are called IPv6 addresses. (4 and 6 refer to the version of the
		Internet Protocol, not the number of the bytes in the address.) Both IPv4 and IPv6
		addresses are ordered sequences of bytes, like an array. They aren’t numbers, and they
		aren’t ordered in any predictable or useful sense. An IPv4 address is normally written
		as four unsigned bytes, each ranging from 0 to 255, with the most significant byte first.
		Bytes are separated by periods for the convenience of human eyes. For example, the
		address for `hermes.oit.unc.edu` is `152.2.21.2`. This is called the dotted quad format.
		An IPv6 address is normally written as eight blocks of four hexadecimal digits separated
		by colons. For example, at the time of this writing, the address of `www.ipv6.com.cn` is
		2001:0250:02FF:0210:0250:8BFF:FEDE:67C8. Leading zeros do not need to be written. Thus,
		the address of `www.ipv6.com.cn` can be written as 2001:250:2FF:210:250:8BFF:FEDE:67C8.
		A double colon, at most one of which may appear in any address, indicates multiple zero
		blocks. For example, FEDC:0000:0000:0000:00DC:0000:7076:0010 could be written more
		compactly as FEDC::DC:0:7076:10. In mixed networks of IPv6 and IPv4, the last four bytes
		of the IPv6 address are sometimes written as an IPv4 dotted quad address. For example,
		FEDC:BA98:7654:3210:FEDC:BA98:7654:3210 could be written as
		FEDC:BA98:7654:3210:FEDC:BA98:118.84.50.16.
	*/

	@SuppressWarnings("unused")
	public static void main(String[] args) {
		
		// InetAddress represents an IPv4 (32b) or IPv4 (128b) address
		InetAddress address;      //ovo je bazna klasas za ove dve ispod. Ima jos podklasa, ali mi cemo koristiti ove za sada
 		Inet4Address ipv4addr;
		Inet6Address ipv6addr;

		// IPv6 addresses might not work for you, it all depends of your provider and
		// whether you have the IPv6 support

		//Inet4Address i Inet6Address su klase koje ne mogu da se instanciraju na nacin na koji ocekujemo:   ne moze  ... = new Inet4Address()
		//instance ove klase dobijamo koriscenjem InetAddress.getByName() metoda
		//API je ovakav zato sto npr necemo morati da brinemo ako sutra neko napravi Inet100Adress klasu (?)
		//Ovaj nacin rada (tj ovaj design pattern) se zove "factory" metoda

		try {
			System.out.println(InetAddress.getByName("www.google.com"));		//npr na vezbama ispis za ovaj pzoiv je bio:   google.com/216.58.212.46   tj. host_name/ip_adresa
			System.out.println(InetAddress.getByName("www.facebook.com"));
			System.out.println(InetAddress.getByName("www.v6.facebook.com"));
			//getAllByName  metod ce nam za prosledjeni host vratiti sve ip adrese preko kojih mozemo da mu pristupimo. Konkretno za google.com
			//na vezbama je dobio jednu ip4 i jednu ip6 adresu. Ako ne koristimo Arrays.toString, necemo dobiti sadrzaj niza nego vracen objekat, ono npr [Ljava.net.InetAdress;@19469ea2
			System.out.println(Arrays.toString(InetAddress.getAllByName("google.com")));
			System.out.println(Arrays.toString(InetAddress.getAllByName("www.v6.facebook.com")));
			System.out.println(InetAddress.getByName("208.201.239.101"));
			System.out.println();

			//LocalHsot dodje kao adresa naseg lokalnog racunara. Ono sto saljemo na local host adresu zapravo nam se vraca, ovo moze da bude korisno
			//poziv ovog metoda na vezbama mu je dao:  ubuntu/127.0.1.1
			System.out.println(InetAddress.getLocalHost());

			// Beware of negative bytes in byte[] address array!
			// We will see how to convert these later
			System.out.println(InetAddress.getByName("www.math.rs"));
			//getAdress vraca niz bajtova ip adrese. Neki su negativni jer su u adresi ti brojevi unsigned, a posto Java nema unsigned (?) pri kastovanju dolazi do prekoracenja (?)
			//tj onni koji su negativni su oni koji su prekoracili 128
			System.out.println(Arrays.toString(InetAddress.getByName("www.math.rs").getAddress()));
			
			try {
				//gledamo sta se desi ako probamo rucno da kastujemo dobijeni objkeat iz getByName poziva u Inet4Addres. Rezultat poziva ce biti razlicit u zavisnosti da li je dohvacena
				//ip4 ili ip6 adresa. Ako je dohvacena 4, super, kast ce prosci. Ali ako je dohvacena 6 dobijcemo ClassCastException
				ipv4addr = (Inet4Address) InetAddress.getByName("ipv6.google.com");
			} catch (ClassCastException ex) {
				System.out.println("Cast failed!");
			}

			ipv6addr = (Inet6Address) InetAddress.getByName("ipv6.google.com");
			System.out.println(ipv6addr.getHostName());
			System.out.println(ipv6addr.getCanonicalHostName());  //ovo je ime provajdera (?)
			System.out.println(ipv6addr.getHostAddress());
			System.out.println();
			
			InetAddress matfShort = InetAddress.getByName("www.math.rs");
			InetAddress matfFull = InetAddress.getByName("www.matf.bg.ac.rs");
			System.out.println(matfShort);
			System.out.println(matfFull);
			//znamo da matf ima dve adrese, pa hocemo da vidimo kako se porede. Ako proveravamo sa equals metodom, vratice se true zato sto se porede po vracenim IP adresama
			//to je ovde bilo ponasanje koje zelimo
			if (matfShort.equals(matfFull))
				System.out.println("www.math.rs is the same as www.matf.bg.ac.rs");
			else
				System.out.println("www.math.rs is not the same as www.matf.bg.ac.rs");
			
		} catch (UnknownHostException ex) {
			ex.printStackTrace();
		}

		/* Sample output
			www.google.com/172.217.169.164
			www.facebook.com/69.171.250.35
			www.v6.facebook.com/2a03:2880:f1ff:83:face:b00c:0:25de
			[www.v6.facebook.com/2a03:2880:f1ff:83:face:b00c:0:25de]
			[google.com/172.217.169.206, google.com/2a00:1450:4017:80b:0:0:0:200e]
			/208.201.239.101

			ubuntu/127.0.1.1
			www.math.rs/147.91.66.10
			[-109, 91, 66, 10]
			Cast failed!
			ipv6.google.com
			2a00:1450:4017:802:0:0:0:200e
			2a00:1450:4017:802:0:0:0:200e

			www.math.rs/147.91.66.10
			www.matf.bg.ac.rs/147.91.66.10
			www.math.rs is the same as www.matf.bg.ac.rs
		 */
	}

}
