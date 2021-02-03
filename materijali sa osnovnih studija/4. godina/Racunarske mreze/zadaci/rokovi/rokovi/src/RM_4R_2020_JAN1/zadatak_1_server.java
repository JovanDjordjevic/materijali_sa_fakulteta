package RM_4R_2020_JAN1;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

//stigao do ovde i shvatio da je isti zadatak bio na nekom pre roku, sa fibonacijem

public class zadatak_1_server {

    public static void main(String[] args) {

        try(DatagramSocket server = new DatagramSocket(12345)){

            while(true){

                try {
                    DatagramPacket request = new DatagramPacket(new byte[4], 4);
                    server.receive(request);
                    System.out.println("Stigao datagram");


                } catch (IOException e) {
                    e.printStackTrace();
                }

            }

        } catch (SocketException e) {
            e.printStackTrace();
        }

    }

}
