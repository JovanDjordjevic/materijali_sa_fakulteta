package RM_4R_2020_JUN1;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class zadatak_1_server {

    public static void main(String[] args) {
        try(ServerSocket server = new ServerSocket(10000)){

            while (true){
                try{
                    Socket client = server.accept();
                    (new UserThread(client)).start();

                }catch (IOException e) {
                    e.printStackTrace();
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public static class UserThread extends Thread{
        Socket client;
        Double sum = 0.0;
        UserThread(Socket client) { this.client = client; }

        @Override
        public void run() {
            try(BufferedReader userIn = new BufferedReader(new InputStreamReader(client.getInputStream()));
                BufferedWriter userOut = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()));
               ){

                String line;
                while ((line = userIn.readLine()) != null){
                    if(line.equalsIgnoreCase("kraj")) {break;}
                    Double value = Double.parseDouble(line);
                    sum += value;
                    System.out.println(value);
                }

                System.out.println("Sum:" + sum.toString());
                userOut.write(sum.toString());
                userOut.newLine();
                userOut.flush();

            } catch (IOException e) {
                e.printStackTrace();
            }finally {
                try {
                    this.client.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

}
