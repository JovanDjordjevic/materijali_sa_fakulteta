package RM_4I_2020_JAN1;

import java.io.IOException;
import java.net.*;
import java.nio.ByteBuffer;
import java.util.Scanner;

public class zadatak_2_client {

    public static void main(String[] args) {
        try(DatagramSocket socket = new DatagramSocket();
            Scanner sc = new Scanner(System.in);
           ){
            InetAddress host = InetAddress.getByName("localhost");

            System.out.println("unesi broj");
            int broj = sc.nextInt();
            if(broj > 80 || broj < 0){
                System.out.println("broj nije validan");
            }else {
                byte[] buf = ByteBuffer.allocate(4).putInt(broj).array();

                //initial request
                DatagramPacket request = new DatagramPacket(buf, buf.length, host, 12345);
                socket.send(request);

                for(int i = 0; i < broj; i++){
                    DatagramPacket response = new DatagramPacket(new byte[8], 8);
                    socket.receive(response);
                    long fib = ByteBuffer.wrap(response.getData()).getLong();
                    System.out.println(i+1 + ". broj: " + fib);
                }


            }
        } catch (SocketException | UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
