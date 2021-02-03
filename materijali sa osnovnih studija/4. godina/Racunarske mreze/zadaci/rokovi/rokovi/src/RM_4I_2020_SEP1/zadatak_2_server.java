package RM_4I_2020_SEP1;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.Scanner;

public class zadatak_2_server {

    public static Integer[][] teren;

    public static void main(String[] args) {
        try(DatagramSocket server = new DatagramSocket(12345);
            Scanner sc = new Scanner(new File("/home/student/Desktop/rokovi/src/RM_4I_2020_SEP1/terrain.txt"));
           ){

            ucitajFajl(sc);
            System.out.println("Ucitan fajl");
            try{
                while(true) {
                    byte[] requestBuffer = new byte[8];
                    DatagramPacket request = new DatagramPacket(requestBuffer, requestBuffer.length);
                    server.receive(request);

                    System.out.println("Primljen client");

                    int requestX = ByteBuffer.wrap(request.getData()).getInt(0);
                    int requestY = ByteBuffer.wrap(request.getData()).getInt(4);
                    int responseInt;

                    if (teren[requestX][requestY] == 1) {
                        responseInt = 1;
                    } else {
                        responseInt = 0;
                    }

                    byte[] responseBuffer = ByteBuffer.allocate(4).putInt(responseInt).array();

                    DatagramPacket response = new DatagramPacket(responseBuffer, responseBuffer.length, request.getAddress(), request.getPort());
                    server.send(response);
                }
            }catch (IOException e){
                e.printStackTrace();
            }finally{
                server.close();
            }


        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void ucitajFajl(Scanner sc){
        // m sirina n visina
        int m = sc.nextInt();
        int n = sc.nextInt();

        teren = new Integer[n][m];
        for (int i = 0 ;i<n ; i++){
            for(int j = 0; j<m; j++){
                teren[i][j] = 0;
            }
        }

        while(sc.hasNextInt()){
            int x = sc.nextInt();
            int y = sc.nextInt();
            int r = sc.nextInt();

            //ovo nije ono sto se trazi u zadataku !!!!
            teren[y][x] = 1;
        }

        //for(Integer[] tmp :teren)
        //    System.out.println(Arrays.toString(tmp));
    }
}
