package i03_resource_getter;

import java.io.*;
import java.net.URL;
import java.net.URLConnection;

final class BinaryFileDownloader {

	public static void main(String[] args) {
		try {
			URL url = new URL("http://www.matf.bg.ac.rs/images/matf.gif");
			URLConnection connection = url.openConnection();

			//getContentType nam vraca MIME tip podatka do kohg vodi url, npr za ovaj gif bice  image/gif
			String contentType = connection.getContentType();
			int contentLength = connection.getContentLength();
			if (contentLength == -1 || contentType.startsWith("text"))
				throw new IOException("Content is not a binary file!");

			//od podatka do kog vodu URL mozemo napraviti inputStream ovom metodom
			//a mi sad jos hocemo i baferisani jer je bolji
			BufferedInputStream input = new BufferedInputStream(connection.getInputStream());
			//getFile ce vratiti sve ovo: images/matf.gif, pa hocemo da nekako izvucemo samo matf.gif da bi ga pod tim imenom i sacuvali
			//pazimo samo da ako u url nemamo putanju, program ce puci
			String filename = url.getFile();
			filename = filename.substring(filename.lastIndexOf('/') + 1);
			System.out.println(filename);

			try (BufferedOutputStream out = new BufferedOutputStream(
				new FileOutputStream("c04_URL_URLConnection/i03_resource_getter/" + filename)
			)) {
				for (int i = 0; i < contentLength; i++) {
					int b = input.read();
					out.write(b);
				}
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
