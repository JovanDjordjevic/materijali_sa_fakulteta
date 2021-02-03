package RM_4I_2019_KOL_A;

import java.io.*;
import java.net.URL;
import java.net.URLConnection;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.atomic.AtomicInteger;

public class zadatak_1_thread extends Thread{
        private  URL u;
        private char findThisChar;
        AtomicInteger counter;

        zadatak_1_thread(URL u, char c, AtomicInteger counter){
            this.u = u;
            this.findThisChar = c;
            this.counter = counter;
        }

        @Override
        public void run() {
            URLConnection uc = null;
            try {
                uc = u.openConnection();
                BufferedReader br = new BufferedReader(new InputStreamReader(uc.getInputStream(), StandardCharsets.UTF_8));

                //nemam potrebne linkove iz primera pa testiram ovako sa mojim fajlom
                //BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream("C:\\Users\\Jovan\\Desktop\\RM\\rokovi\\test\\urls.txt"), StandardCharsets.UTF_8));
                String line = "";
                while((line = br.readLine()) != null){
                    for(char c : line.toCharArray()){
                        if( c == this.findThisChar){
                            this.counter.getAndIncrement();
                        }
                    }
                }
            } catch (IOException e) {
                //e.printStackTrace();
                System.out.println("neuspela konekcija");
            }
        }

}
