package RM_4I_2019_KOL_B;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.atomic.AtomicInteger;

public class zadatak_1_thread extends Thread{

    private URL url;
    private AtomicInteger counter;

    zadatak_1_thread(URL url, AtomicInteger counter){
        this.url = url;
        this.counter = counter;
    }

    @Override
    public void run() {
        try {
            //NOTE: na windowsu ovo izgleda pravi problem, daje UnknownHostException, ne znam kako da handlujem, na linuxu bi verovatno bilo lakse
            //svaki naredni ispit/klk bice radjen na linuxu, na virtuelnoj masini za kurs
            URLConnection connection = url.openConnection();
            BufferedReader br = new BufferedReader( new InputStreamReader(connection.getInputStream(), StandardCharsets.US_ASCII));
            while((br.readLine()) != null){
                counter.getAndIncrement();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
