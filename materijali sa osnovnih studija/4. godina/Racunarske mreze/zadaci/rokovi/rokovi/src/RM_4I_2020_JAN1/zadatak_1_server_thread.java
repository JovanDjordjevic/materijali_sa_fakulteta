package RM_4I_2020_JAN1;

import java.io.*;
import java.net.Socket;
import java.util.concurrent.ConcurrentHashMap;

public class zadatak_1_server_thread extends Thread {

    private Socket client;
    ConcurrentHashMap<Integer, String> players;

    zadatak_1_server_thread(Socket client, ConcurrentHashMap<Integer, String> players){
        this.players = players;
        this.client = client;
    }

    @Override
    public void run() {

        try(BufferedReader clientIn = new BufferedReader(new InputStreamReader(client.getInputStream()));
            BufferedWriter clientOut = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()))
        ){
            while(true) {
                String[] request = clientIn.readLine().split(" ");

                if(request[0].equalsIgnoreCase("bye")){
                    System.out.println(request);
                    break;
                }
                else if(request[0].equalsIgnoreCase("sel")){
                    System.out.println(request);
                    int id = Integer.parseInt(request[1]);
                    if(players.containsKey(id)){
                        String[] data = players.get(id).split(" ");
                        clientOut.write(data[0] + ": " + data[1]);
                        clientOut.newLine();
                        clientOut.flush();
                    }else{
                        clientOut.write("Player with that id doesn't exist");
                        clientOut.newLine();
                        clientOut.flush();
                    }
                }else if(request[0].equalsIgnoreCase("ins")){
                    System.out.println(request);
                    int id = zadatak_1_server.getNextAvailableId();
                    players.put(id, request[0] + " 1300");
                    clientOut.write("ins je uspesno izvrsen");
                    clientOut.newLine();
                    clientOut.flush();
                }else if(request[0].equalsIgnoreCase("upd")){
                    System.out.println(request);
                    int id = Integer.parseInt(request[1]);
                    int deltae = Integer.parseInt(request[2]);
                    String[] playerData = players.get(id).split(" ");
                    players.put(id, playerData[0] + " " + Integer.parseInt(playerData[1]) + deltae);
                    clientOut.write("upd je uspesno izvrsen");
                    clientOut.newLine();
                    clientOut.flush();
                }

            }

        } catch (IOException e) {
            e.printStackTrace();
        }finally {
            try {
                client.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }
}