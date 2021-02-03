package RM_4R_2020_JAN1;

import java.io.IOException;
import java.net.*;
import java.nio.ByteBuffer;
import java.util.Scanner;

//stigao do ovde i shvatio da je isti zadatak bio na nekom pre roku, sa fibonacijem

public class zadatak_1_client {

    public static void main(String[] args) {

        try(DatagramSocket client = new DatagramSocket();
            Scanner sc = new Scanner(System.in);
            ) {

            System.out.println("Unesi broj");
            int broj = sc.nextInt();

            byte[] data = ByteBuffer.allocate(4).putInt(broj).array();

            InetAddress host = InetAddress.getByName("localhost");
            DatagramPacket request = new DatagramPacket(data, 4, host, 12345);
            client.send(request);




        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}
