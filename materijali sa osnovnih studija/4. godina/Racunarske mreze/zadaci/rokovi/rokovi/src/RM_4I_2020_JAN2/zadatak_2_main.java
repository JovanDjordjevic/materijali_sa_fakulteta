package RM_4I_2020_JAN2;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.util.Scanner;

public class zadatak_2_main {

    public static void main(String[] args) {
        try (Scanner sc = new Scanner(System.in)){
            System.out.println("unesi url");
            String urlString = sc.next();

            URL url = new URL(null, urlString, new zadatak_2_Handler());
            URLConnection connection = url.openConnection();

            try(BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));){
                String line;
                while((line = in.readLine()) != null){
                    System.out.println(line);
                }
            }

        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
