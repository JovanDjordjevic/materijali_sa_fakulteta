package RM_4I_2020_JAN1;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ConcurrentHashMap;

//ovaj zadatak mi ne radi, mrzi me da popravljam

public class zadatak_1_server {

    public static int nextAvailableId = 1;

    public static void main(String[] args) {
        try(ServerSocket server = new ServerSocket(1996);){

            // id : "naziv elo"
            ConcurrentHashMap<Integer, String> players = new ConcurrentHashMap<>();

            while(true){
                Socket client = server.accept();
                new Thread(new zadatak_1_server_thread(client, players));
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static synchronized int getNextAvailableId() {
        nextAvailableId++;
        return nextAvailableId-1;
    }
}
