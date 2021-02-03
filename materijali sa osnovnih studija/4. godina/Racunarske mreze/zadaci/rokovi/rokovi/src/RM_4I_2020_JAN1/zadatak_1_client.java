package RM_4I_2020_JAN1;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class zadatak_1_client {

    public static void main(String[] args) {

        try (Socket client = new Socket("localhost", 1996);
             BufferedReader networkIn = new BufferedReader(new InputStreamReader(client.getInputStream()));
             BufferedWriter networkOut = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()));
             Scanner in = new Scanner(System.in);
            ){

                while(true){
                    String option = in.nextLine();
                    String[] splits = in.nextLine().split(" ");
                    if(splits[0].equalsIgnoreCase("bye")) {
                        //System.out.println(option[0]);
                        networkOut.write(splits[0]);
                        networkOut.newLine();
                        networkOut.flush();
                    }
                    else if(splits[0].equalsIgnoreCase("sel")){
                        networkOut.write(option);
                        networkOut.newLine();
                        networkOut.flush();

                    }else if(splits[0].equalsIgnoreCase("ins")){
                        networkOut.write(option);
                        networkOut.newLine();
                        networkOut.flush();

                    }else if(splits[0].equalsIgnoreCase("upd")){
                        networkOut.write(option);
                        networkOut.newLine();
                        networkOut.flush();
                    }else{
                        System.out.println("bad request");
                    }

                    System.out.println(networkIn.readLine());

                }


        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}
