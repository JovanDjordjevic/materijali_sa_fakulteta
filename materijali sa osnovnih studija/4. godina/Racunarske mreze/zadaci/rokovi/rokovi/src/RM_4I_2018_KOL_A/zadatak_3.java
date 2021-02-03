package RM_4I_2018_KOL_A;

import java.io.*;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Scanner;

//nemam njegov test primer ne mogu lepod a testiram
//pretpostavio sam da je data bas cela ipv6 ardesa:  AAAA:AAAA:AAAA:AAAA

public class zadatak_3 {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("unesi putanu do log fajla");
        //String path = sc.nextLine();
        String path = "/home/student/Desktop/rokovi/test/testfile.txt";

        try (FileInputStream fis = new FileInputStream(new File(path));
             BufferedReader fileIn = new BufferedReader(new InputStreamReader(fis));
            ){

            String line;
            while( (line = fileIn.readLine()) != null){
                //String[] params = line.split(":");
                //String date = params[0].replace('[' , ' ').replace(']' , ' ').trim();
                //String ip = params[1];
                //String address = params[2];

                String[] params = new String[3];
                params[0] = line.substring(1, line.indexOf(':')-1);
                int version = 0;

                if(line.chars().filter(c -> c == ':').count() > 3){
                    //verovatno ipv6
                    version = 6;
                    params[1] = line.substring(line.indexOf(':')+1, line.indexOf(':') + 20);
                    params[2] = line.substring(line.indexOf(':') + 21);
                }else{
                    //verovatno ipv4
                    version = 4;
                    params[1] = line.substring(line.indexOf(':')+1, line.indexOf(':') + 12);
                    params[2] = line.substring(line.indexOf(':') + 13);
                }

                //System.out.println(params[0] + " " + params[1] + " "+ params[2]);

                try {
                    URL u = new URL(params[2]);
                    if(u.getProtocol().equalsIgnoreCase("file") || u.getProtocol().equalsIgnoreCase("ftp")){
                        System.out.println("v" + version + ":" + u.getProtocol() + ":" + u.getFile());
                    }
                } catch (MalformedURLException e) {
                    //e.printStackTrace();
                    continue;
                }

            }

        } catch (IOException e) {
            e.printStackTrace();
        }


        sc.close();
    }

}
