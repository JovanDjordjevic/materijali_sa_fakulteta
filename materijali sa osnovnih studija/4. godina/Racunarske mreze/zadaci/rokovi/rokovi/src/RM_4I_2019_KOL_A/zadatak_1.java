package RM_4I_2019_KOL_A;

import java.io.*;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.atomic.AtomicInteger;

public class zadatak_1 {

    //NOTE: ne mogu da testiram jer nemam konkretne potrebne primere, testirao sam na nekim mojim fajlovima i radi
    //radjeno na windowsu

    public static void main(String[] args){

        Scanner in = new Scanner(System.in);
        System.out.println("ulaz:  ");
        String input = in.next();
        in.close();
        char findThisChar = input.charAt(0);

        AtomicInteger counter = new AtomicInteger(0);

        try(BufferedReader br = new BufferedReader(
                new InputStreamReader(
                new FileInputStream("C:\\Users\\Jovan\\Desktop\\RM\\rokovi\\test\\urls.txt")
                ));
        ){
            int numberOfLines = 0;
            List<String> lines = new ArrayList<String>();
            String line = "";
            while((line = br.readLine()) != null){
                //System.out.println( line);
                lines.add(line);
                numberOfLines++;
            }
            System.out.println("lines: " + numberOfLines);

            List<Thread> threads = new ArrayList<Thread>();

            for (String l : lines) {
                try {
                    URL u = new URL(l);
                    if(u.getProtocol().equalsIgnoreCase("file") && l.endsWith(".txt")){
                        Thread t = new zadatak_1_thread(u, findThisChar, counter);
                        threads.add(t);
                        t.start();
                    }
                }catch (MalformedURLException e){
                    System.out.println("not found: " + l);
                }
            }

            for(Thread t : threads){
                t.join();
            }

            System.out.println("result: " + counter);

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }


    }

}
