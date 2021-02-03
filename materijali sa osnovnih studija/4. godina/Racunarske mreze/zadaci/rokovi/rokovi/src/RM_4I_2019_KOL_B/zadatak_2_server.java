package RM_4I_2019_KOL_B;

//radjeno na windowsu

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class zadatak_2_server {

    public static void main(String[] args) {
        int port = 31415;

        try (ServerSocket server = new ServerSocket(port);){
            while(true){
                Socket client = server.accept();
                new Thread(new zadatak_2_server_thread(client)).start();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
