package RM_4I_2020_SEP3;

import java.io.IOException;
import java.net.*;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class zadatak_2_client {
    public static void main(String[] args) {
        try(DatagramSocket client = new DatagramSocket();
            Scanner sc = new Scanner(System.in);
            ){

            System.out.println("unesi naziv fajla i dva broja");
            byte[] naziv = (sc.nextLine() + " ").getBytes();
            byte[] pos1 = (sc.nextLine() + " ").getBytes();
            byte[] pos2 = sc.nextLine().getBytes();

            byte[] requestBuf = ByteBuffer.allocate(naziv.length + pos1.length + pos2.length).put(naziv).put(pos1).put(pos2).array();

            InetAddress host = InetAddress.getByName("localhost");
            DatagramPacket request = new DatagramPacket(requestBuf, requestBuf.length, host, 12121);
            client.send(request);

            DatagramPacket response = new DatagramPacket(new byte[4096], 4096);
            client.receive(response);

            System.out.println(new String(response.getData(), 0, response.getLength(), StandardCharsets.US_ASCII));

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
