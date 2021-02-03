package i01_client_sockets_intro;

import java.io.*;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;

final class ServerSocketsIntro {

    public static void main(String[] args) {
        int port = 9000;

        //za servere ne koristimo istu klasu kao za klijent, vec specijalnu ServerSocket. Razlika je sto je serverskom socketu
        //potrebno da ima 5. 6. i 7. operaciju iz one liste iz proslog primera,a  to imamo u ServerSocket klasi
        //dok klijent mora da zna i adresu servera i port, za ServerSocket nam je dovoljan samo port za koji cemo ga vezati
        //imamo opciju i da ne navedemo port u ovom kosntruktoru, ali onda moramo rucno pozvati bind metod posle
        try (ServerSocket server = new ServerSocket(port)) {

            // Accept clients and open sockets towards them - blocking call
            //poenta servera je da slusa(listen) i prima(accept) klijente. To se u javi radi jednom metodom (accept)
            //Kada se pozove accept, to je blokirajuce poziv. Ovde se ceka na klijenta (listen). Kada se klijent pojavi, vrati se socket
            //kojim sa tim klijentom mozemo da komuniciramo
            Socket client = server.accept();

        } catch (IOException ex) {
            ex.printStackTrace();
        }

        try (ServerSocket server = new ServerSocket()) {
            // Bind server manually if port isn't specified via constructor
            server.bind(new InetSocketAddress(port));

            // Usually servers are infinite loops
            //noinspection InfiniteLoopStatement
            while (true) {
                // Accept client
                Socket client = server.accept();
                // Do work with a client
                serve(client);
            }

        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private static void serve(Socket client) {
        // Serve client, usually in a separate thread
    }
}
