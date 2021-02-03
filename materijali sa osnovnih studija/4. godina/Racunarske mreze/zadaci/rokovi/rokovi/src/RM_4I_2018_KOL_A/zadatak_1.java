package RM_4I_2018_KOL_A;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

//mrzi me da proveravam da tacno broj dana odgovara mesecu i da je godina prestupna...

public class zadatak_1 {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        System.out.println("Unesi putnaju do fajla");
        //String path = sc.nextLine();
        String path = "/home/student/Desktop/rokovi/test/timestamps.txt";
        sc.close();

        try (FileInputStream fis = new FileInputStream(new File(path));
             BufferedReader in = new BufferedReader(new InputStreamReader(fis, StandardCharsets.UTF_8));
             FileOutputStream fout = new FileOutputStream(new File("/home/student/Desktop/rokovi/src/RM_4I_2018_KOL_A/output.txt"));
             BufferedWriter out = new BufferedWriter(new OutputStreamWriter( fout,StandardCharsets.UTF_8))
            ){

            //pretp da su u ulaznom fajlu svaka niska u po jednoj liniji
            String line;
            while( (line = in.readLine()) != null){
                if(line.length() != 10){ continue; }

                String[] numbers = line.split("-");
                if(numbers.length != 3) { continue; }

                int day = Integer.parseInt(numbers[0]);
                int month = Integer.parseInt(numbers[1]);
                int year = Integer.parseInt(numbers[2]);
                if(day <= 0 || day >= 31 || month<=0 || month >=13 || year <2000) { continue; }

                out.write(line);
                out.newLine();
                out.flush();
            }


        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("nepostojeci fajl/neuspesno otvaranje streama");
        }



    }

}
