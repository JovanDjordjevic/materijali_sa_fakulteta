package RM_4I_2020_SEP1;

import java.io.IOException;
import java.net.*;
import java.nio.ByteBuffer;
import java.util.Scanner;

public class zadatak_2_client {

    public static void main(String[] args) {
        try (DatagramSocket client = new DatagramSocket();
             Scanner sc = new Scanner(System.in);){
             System.out.println("unesi poziciju x y");
                int x = sc.nextInt();
                int y = sc.nextInt();

            byte[] buf = ByteBuffer.allocate(8).putInt(x).putInt(y).array();

            InetAddress host = InetAddress.getLocalHost();
            DatagramPacket request = new DatagramPacket(buf, buf.length, host, 12345);
            client.send(request);

            //0 ako nije 1 ako jeste
            DatagramPacket response = new DatagramPacket(new byte[4], 4);
            client.receive(response);

            int res = ByteBuffer.wrap(response.getData()).getInt();

            if(res == 0){
                System.out.println("Nije pokriven");
            }else if( res == 1){
                System.out.println("Jeste pokriven");
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
