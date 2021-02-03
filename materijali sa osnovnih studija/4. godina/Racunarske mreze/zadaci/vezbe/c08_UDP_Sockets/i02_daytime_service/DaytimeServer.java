package i02_daytime_service;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.util.Date;
import java.util.logging.*;
import java.io.*;

final class DaytimeServer {
    private static final int PORT = 12345;
    private static final int BUF_SIZE = 1024;
    //ovo su neki javini loggeri za ispisivanje poruka, nije bitno za predmet
    private static final Logger audit = Logger.getLogger("requests");   //NOTE: ovo je stajalo u materijalima, nije on radio na vezbama
    private static final Logger errors = Logger.getLogger("errors");     //NOTE: ovo je stajalo u materijalima, nije on radio na vezbama

    public static void main(String[] args) {
        //u implementaciji servera,  ovom konstruktoru mozemo da prosledimo PORT na komce on da slusa
        //alternativno, mozemo i kosntruktor bez argumenata pa u kodu ispod da uradimo bind serveraza neki port
        try (DatagramSocket socket = new DatagramSocket(PORT)) {
            //noinspection InfiniteLoopStatement
            while (true) {
                try {
                    // Wait for packet...
                    //iako je u klijentu request kji saljemo 1 bajt, sa serverske strane se obicno rezervise vise mesta
                    //da bi mogli razliciti podaci da se prime (?)
                    //NOTE: server PRIMA request paket, zato ne treba navoditi host i port, a informacije o hostu i portu klijenta
                    //ce biti izvucene iz ovog paketa ugradjenium metodama
                    DatagramPacket request = new DatagramPacket(new byte[BUF_SIZE], BUF_SIZE);
                    socket.receive(request);

                    // Packet received, create date string as byte array
                    String daytime = new Date().toString();
                    //pravimo byte niz od stringa jer se podaci salju kao byte[]
                    byte[] data = daytime.getBytes(StandardCharsets.US_ASCII);

                    // Send back the data (ovde izvlacimo podatke o klijentuiz requesta)
                    DatagramPacket response = new DatagramPacket(data, data.length,
                            request.getAddress(), request.getPort());
                    socket.send(response);

                    //primetimo da semo kada smo radili TCP, imali smo situaciju da je slanje podataka klijentu sporije jer moramo da cekamo
                    //acknowledgement da je klijent primio podatke, pa samim tim kada je klijent spor, to blokira komunikaciju sa ostalima
                    //pa smo zato za klijente uvodili zasebne niti. UDP protokol nema acknowledgement, i slanje je instant, tako da nas ovde ne koci
                    //send operacija, tj necemo osetiti obradu klijenta, tako da nam ne trebaju niti (bar u ovm primeru (?))

                    // Log processed client (optional)  //NOTE: ovo je stajalo u materijalima, nije on radio na vezbama
                    audit.info(daytime + " " + request.getAddress());
                } catch (IOException | RuntimeException ex) {
                    errors.log(Level.SEVERE, ex.getMessage(), ex);
                }
            }
        } catch (IOException ex) {
            errors.log(Level.SEVERE, ex.getMessage(), ex);
        }
    }
}
