package RM_4I_2019_SEP1;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class zadatak_1_server {

    public static void main(String[] args) {
        System.out.println("Starting server");
        try(ServerSocket server = new ServerSocket(12345)){

            while(true){
                Socket client = server.accept();
                (new UserThread(client)).start();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public static class UserThread extends Thread{
        private Socket client;
        UserThread(Socket client) {this.client = client; }

        @Override
        public void run() {
            try(BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
                BufferedWriter out = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()));
               ){
                System.out.println("client accepted and thread started");
                String path = in.readLine();
                try(FileInputStream fis = new FileInputStream(new File(path));
                    BufferedReader fileIn = new BufferedReader(new InputStreamReader(fis));
                   ){

                    byte indicator = 0;
                    out.write(indicator);
                    out.newLine();
                    out.flush();

                    String line;
                    while((line = fileIn.readLine()) != null){
                        out.write(line);
                        out.newLine();
                        out.flush();
                    }

                }catch (FileNotFoundException e){
                    byte indicator = 1;
                    out.write(indicator);
                    out.newLine();
                    out.flush();
                    client.close();
                }


            } catch (IOException e) {
                e.printStackTrace();
                try {
                    client.close();
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
            }
        }
    }

}
