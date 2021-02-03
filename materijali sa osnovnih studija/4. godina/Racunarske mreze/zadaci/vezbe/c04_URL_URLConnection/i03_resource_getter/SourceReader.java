package i03_resource_getter;

import java.io.*;
import java.net.URL;
import java.net.URLConnection;

final class SourceReader {

	private static final String URL_STRING = "http://poincare.matf.bg.ac.rs/~ivan_ristovic";

	public static void main(String[] args) throws IOException {

		URL u = new URL(URL_STRING);

		//jel ovo greska ? otvara se stream nad URL a ne nad URLConnection ?
		try (BufferedReader in = new BufferedReader(
				new InputStreamReader(u.openStream())
		)) {

			String line;
			while ((line = in.readLine()) != null)
				System.out.println(line);

		} catch (IOException ex) {
			ex.printStackTrace();
		}

		//prvi pristup nije dobar iz razloga sto mozda na adresi ima npr neka cirilica i onda ona mozda ne bude lepo ispisana
		//bolji pristup je da ispisujemo u encodingu koji se korsiti na adresi (ako on psotoji)
		URLConnection conn = u.openConnection();
		String encoding = conn.getContentEncoding();
		if (encoding == null)
			encoding = "UTF-8";
		try (BufferedReader in = new BufferedReader(
				new InputStreamReader(
						conn.getInputStream(),
						encoding
				)
		)) {
			// Because the characters are encoded, we use UTF-8
			// now so all characters can be properly visualized
			// conn.getContentEncoding() can also be used but it
			// is not so stable, returns mostly null

			String line;
			while ((line = in.readLine()) != null)
				System.out.println(line);

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
