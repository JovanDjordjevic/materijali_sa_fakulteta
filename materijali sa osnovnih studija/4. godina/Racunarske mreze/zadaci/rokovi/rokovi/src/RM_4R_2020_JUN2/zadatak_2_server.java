package RM_4R_2020_JUN2;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.nio.ByteBuffer;

public class zadatak_2_server {

    public static int datagramIndex = 1;

    public static void main(String[] args) {
        try(DatagramSocket server = new DatagramSocket(10101);
        ){

            while (true){

                DatagramPacket request = new DatagramPacket(new byte[4], 4);
                server.receive(request);
                System.out.println("Datagram recieved. Index: " + datagramIndex + " Sender: " + request.getAddress());
                datagramIndex++;

                int reqestNumber = ByteBuffer.wrap(request.getData()).getInt();
                String binaryNum = Integer.toBinaryString(reqestNumber);
                //System.out.println(binaryNum);
                byte[] responseBuf = binaryNum.getBytes();

                DatagramPacket response = new DatagramPacket(responseBuf, responseBuf.length,request.getAddress(), request.getPort());
                server.send(response);

            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
