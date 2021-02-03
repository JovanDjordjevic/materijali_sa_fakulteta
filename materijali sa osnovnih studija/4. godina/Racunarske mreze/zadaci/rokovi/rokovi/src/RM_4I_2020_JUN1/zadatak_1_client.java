package RM_4I_2020_JUN1;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class zadatak_1_client {

    public static void main(String[] args) {
        try(Socket client = new Socket("localhost", 7337);
            BufferedReader networkIn = new BufferedReader(new InputStreamReader(client.getInputStream()));
            BufferedWriter networkOut = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()));
            Scanner sc = new Scanner(System.in);
        ){

            System.out.println("Unesi komande:");

            while(sc.hasNext()){
                String s = sc.nextLine();
                String[] userInput = s.split(" ");

                if(userInput[0].trim().equalsIgnoreCase("bye")){
                    networkOut.write(s);
                    networkOut.newLine();
                    networkOut.flush();
                    break;
                }else if(userInput[0].trim().equalsIgnoreCase("list")){
                    networkOut.write(s);
                    networkOut.newLine();
                    networkOut.flush();

                    String reply ="";
                    while( (reply = networkIn.readLine()) != null){
                        System.out.println(reply);
                    }
                }else if(userInput[0].trim().equalsIgnoreCase("reply")){
                    networkOut.write(s);
                    networkOut.newLine();
                    networkOut.flush();

                    System.out.println(networkIn.readLine());
                }else if(userInput[0].trim().equalsIgnoreCase("post")){
                    networkOut.write(s);
                    networkOut.newLine();
                    networkOut.flush();

                    System.out.println(networkIn.readLine());
                }else{
                    System.out.println("bad request");
                }
            }

        }catch(IOException e){
            e.printStackTrace();
        }
    }

}
