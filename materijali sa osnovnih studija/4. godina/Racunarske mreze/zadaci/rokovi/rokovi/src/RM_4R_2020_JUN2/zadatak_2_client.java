package RM_4R_2020_JUN2;

import java.io.IOException;
import java.net.*;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class zadatak_2_client {
    public static void main(String[] args) {
        try(DatagramSocket client = new DatagramSocket();
            Scanner sc = new Scanner(System.in)){

            while(true){
                String line = sc.nextLine();
                if(line.equalsIgnoreCase("kraj")){ break; }

                int number = Integer.parseInt(line);
                byte[] buf = ByteBuffer.allocate(4).putInt(number).array();
                InetAddress host = InetAddress.getByName("localhost");
                DatagramPacket request = new DatagramPacket(buf, buf.length, host, 10101);
                client.send(request);

                DatagramPacket response = new DatagramPacket(new byte[1024], 1024);
                client.receive(response);

                System.out.println(new String(response.getData(), 0 ,response.getLength(), StandardCharsets.US_ASCII));
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
