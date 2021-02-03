package RM_4I_2020_SEP2;

import java.io.IOException;
import java.net.*;
import java.nio.ByteBuffer;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class zadatak_2_server {

    public static Map<Long, Long> accounts = Collections.synchronizedMap(new HashMap<Long, Long>());

    public static void main(String[] args) {
            (new InputThread()).start();
            (new DatagramThread()).start();
    }


    public static class InputThread extends Thread{
        InputThread(){}

        @Override
        public void run() {
            System.out.println("InputThread started");
            try (Scanner sc = new Scanner(System.in)){
                while(true) {
                    System.out.println("Input ACCOUNT_NUMBER ACCOUNT_BALANCE");
                    long accountNumber = sc.nextLong();
                    long accountBalance = sc.nextLong();
                    if (!accounts.containsKey(accountNumber))
                        accounts.put(accountNumber, accountBalance);
                    System.out.println("input processed");
                }
            }
        }
    }


    public static class DatagramThread extends Thread{
        private DatagramSocket server;
        DatagramThread(){
            try {
                this.server = new DatagramSocket(12345);
            } catch (SocketException e) {
                e.printStackTrace();
            }
        }

        @Override
        public void run() {
            System.out.println("DatagramThread started");
            try{
                while(true){
                    DatagramPacket request = new DatagramPacket(new byte[8], 8);
                    this.server.receive(request);
                    System.out.println("Datagram arrived");

                    long accountNumber = ByteBuffer.wrap(request.getData()).getLong();
                    long returnValue = -1;
                    if(accounts.containsKey(accountNumber)){
                        returnValue = accounts.get(accountNumber);
                    }

                    byte[] responseBuf = ByteBuffer.allocate(8).putLong(returnValue).array();
                    DatagramPacket response = new DatagramPacket(responseBuf, responseBuf.length,
                            request.getAddress(), request.getPort());
                    this.server.send(response);
                }
            }catch (IOException e){
                e.printStackTrace();
                server.close();
            }
            System.out.println("DatagramThrad ended");
        }
    }

}
