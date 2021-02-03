package RM_4I_2019_JAN2;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.net.UnknownHostException;

//netacan

public class zadatak_1_client {

    public static void main(String[] args) {
        try(Socket client = new Socket("localhost", 12345);
            BufferedReader networkIn = new BufferedReader(new InputStreamReader(client.getInputStream()))
           ){

            for(int i = 0; i < 5; i++){
                System.out.println(networkIn.readLine());
            }

        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
