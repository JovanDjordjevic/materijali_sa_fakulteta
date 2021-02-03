package i03_echo;

import java.io.IOException;

final class EchoTest {

	public static void main(String[] args) throws IOException {
		try (EchoServer server = new EchoServer(12345);
			 EchoClient client = new EchoClient("localhost", 12345);
		) {
			server.start();

			//priemtimo jednu stvar specificnu za UDP. Posto u ovom protokolu nema nikakve kontrole slanja niti three way handhsake,
			//ako pokrenemo samo klijent bez da pokrenemo server, nece se desiti nista lose. Send ce proci bez problema, klijent ce poslati paket
			//a to sto nema ko taj paket da primi nije njegov problem. Tj ima problem samo ako coekujemo i neki odgovor,
			//tj blokirace se na cekanju response-a. Ovo mozemo da izbegnemo ako psotavimo neki timeout nad soketom klijenta
			//tako ce klijent maksimalno neki broj sekundi da ceka na recieve i posle toga ce da baci excception

			String echo;
			echo = client.sendEcho("(test1) hello!");
			System.out.println("(test1) returned: " + echo);
			echo = client.sendEcho("(test2) works?");
			System.out.println("(test2) returned: " + echo);
			echo = client.sendEcho("(test3) \uD83D\uDE0B");  //ovo \u... su kodovi za unicode karaktere
			System.out.println("(test3) returned: " + echo);

			client.sendEcho("end");
		}

		System.out.println("Test finished.");
	}

}
