package i04_conditional_downloader;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;
import java.util.Date;

final class ConditionalDownloader {
	
	private static final long MILLISECONDS_PER_DAY = 24 * 60 * 60 * 1000;
	private static final String URL_STRING = "http://www.matf.bg.ac.rs/";

	//npr hocmeo da preuzmemo fajl samo ako je modifikovan  skoro
	
	public static void main(String[] args) {
		Date today = new Date();
		
		try {
			URL u = new URL(URL_STRING);
			URLConnection uc = u.openConnection();
			//iz headera odgovora moze se izvuci informacija kada je poslednja izmena bila.
			// getIfModifiedSince() vraca long koji predstavlja broj ms od pocetka epohe pa se od toga maze napraviti Date
			//mzoemo mu postaviti datum sa  setIfModifiedSince
			System.out.println("Will retrieve file if it's modified since " + new Date(uc.getIfModifiedSince()));

			uc.setIfModifiedSince((new Date(today.getTime() - MILLISECONDS_PER_DAY)).getTime());
			System.out.println("Will retrieve file if it's modified since " + new Date(uc.getIfModifiedSince()));

			BufferedReader in = new BufferedReader(new InputStreamReader(uc.getInputStream()));

			String line;
			while ((line = in.readLine()) != null)
				System.out.println(line);
			
			in.close();
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}
}
