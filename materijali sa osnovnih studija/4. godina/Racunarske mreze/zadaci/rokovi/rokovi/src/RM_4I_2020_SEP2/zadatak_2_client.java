package RM_4I_2020_SEP2;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.ByteBuffer;
import java.util.Scanner;

public class zadatak_2_client {

    public static void main(String[] args) {
        try(DatagramSocket client = new DatagramSocket();
            Scanner sc = new Scanner(System.in)){

            System.out.println("Unesi broj racuna");
            long brojRacuna = sc.nextLong();
            byte[] requestBuf = ByteBuffer.allocate(8).putLong(brojRacuna).array();
            InetAddress host = InetAddress.getLocalHost();

            DatagramPacket request = new DatagramPacket(requestBuf, requestBuf.length, host, 12345);
            client.send(request);

            DatagramPacket response = new DatagramPacket(new byte[8], 8);
            client.receive(response);

            System.out.println(ByteBuffer.wrap(response.getData()).getLong());
            
        } catch (IOException e) {
            e.printStackTrace();
        }
    }



}
