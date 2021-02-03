package i01_time_service;

import java.io.IOException;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;

final class TimeServer {
	
	public final static int DEFAULT_PORT = 4242;

	//ovde bukvalno imitiramo odgovor kojis e dobije sa https://tf.nist.gov/tf-cgi/servers.cgi
	//tj vracamo 4 bajta koji kad se spoje daju broj sekundi od pocetka 1900te godine
	//narvno da smo ovo mogli drugacije da radimo

	public static void main(String[] args) {
		long differenceBetweenEpochs = 2208988800L;

		try (ServerSocket server = new ServerSocket(DEFAULT_PORT)) {
			//noinspection InfiniteLoopStatement
			while (true) {
				try (Socket client = server.accept()) {
					Date now = new Date();
					long msSince1970 = now.getTime();
					long secondsSince1970 = msSince1970 / 1000;
					long secondsSince1900 = secondsSince1970 + differenceBetweenEpochs;

					byte[] time = new byte[4];
					time[0] = (byte) (secondsSince1900 >> 24); //sift udesno za 3 bajta
					time[1] = (byte) (secondsSince1900 >> 16); //za 2
					time[2] = (byte) (secondsSince1900 >> 8);  //za 1
					time[3] = (byte) (secondsSince1900);

					OutputStream out = client.getOutputStream();
					out.write(time);
					out.flush();
				} catch (IOException ex) {
					ex.printStackTrace();
				}
			}
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}

}
