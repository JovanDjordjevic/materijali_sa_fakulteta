package RM_4I_2020_JAN1;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.nio.ByteBuffer;

public class zadatak_2_server {

    public static void main(String[] args) {

        long[] fibonaci = new long[81];
        fibonaci[0] = 0;
        fibonaci[1] = 1;
        for (int i = 2; i < fibonaci.length-1; i++){
            fibonaci[i] = fibonaci[i-1] + fibonaci[i-2];
        }

        try (DatagramSocket socket = new DatagramSocket(12345);) {

            while (true) {
                try {
                    DatagramPacket request = new DatagramPacket(new byte[4], 4);
                    socket.receive(request);
                    System.out.println("Stigao datagram!");

                    int broj = ByteBuffer.wrap(request.getData()).getInt();
                    //System.out.println(broj);

                    for(int i = 0; i < broj; i++){
                        byte[] buf = ByteBuffer.allocate(8).putLong(fibonaci[i]).array();
                        DatagramPacket response = new DatagramPacket(buf, buf.length, request.getAddress(), request.getPort());
                        socket.send(response);
                    }

                } catch (IOException e) {
                    e.printStackTrace();
                }

            }

        } catch (SocketException e) {
            e.printStackTrace();
        }
    }
}
