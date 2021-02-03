package i05_header_printer;

import java.io.IOException;
import java.net.URL;
import java.net.URLConnection;
import java.util.Scanner;

final class HeaderPrinter {

	// What are header fields? https://en.wikipedia.org/wiki/List_of_HTTP_header_fields     - ovde su svi headeri koji postoje
	// https://www.w3schools.com/tags/ref_httpmethods.asp
	
	public static void main(String[] args) {

		//ocekuje se da se ucita url po url sa stdin
		Scanner sc = new Scanner(System.in);
		while (sc.hasNext()) {
			try {
				String line = sc.nextLine();
				if (line.trim().equals(""))
					continue;
				if (line.equalsIgnoreCase("exit"))
					break;
					
				URL u = new URL(line);
				URLConnection uc = u.openConnection();

				//headeri su svi oblika:    ime_headera:sadrzaj
				//osim prvog. Prvi header je drugaciji:   verzija_protokola status_code     npr:    HTTP/1.1 200 OK
				//mogu se dohvatati na razne nacine, po imenu, po broju itd. Mi ovde dohvatamo po broju
				System.out.println("--------------------------------------");
				System.out.println("0th header: " + uc.getHeaderField(0));
				for (int i = 1; ; i++) {
					String header = uc.getHeaderField(i);   //vrati null kad ne bude vise headera
					if (header == null)
						break;
					//kljuc headera je ime_headera
					System.out.println(uc.getHeaderFieldKey(i) + ": " + header);
				}
				System.out.println("--------------------------------------");
			} catch (IOException ex) {
				ex.printStackTrace();
			}
		}
		sc.close();
	}

}
