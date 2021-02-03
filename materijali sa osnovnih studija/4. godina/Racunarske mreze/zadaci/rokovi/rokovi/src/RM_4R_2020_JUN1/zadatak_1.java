package RM_4R_2020_JUN1;

import java.io.*;
import java.net.MalformedURLException;
import java.net.URL;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.atomic.AtomicBoolean;

public class zadatak_1 {

    public static Map<String, Integer> lineCounts = Collections.synchronizedMap(new HashMap<>());
    public static AtomicBoolean threadIsWriting = new AtomicBoolean(false);

    public static void main(String[] args) {
        String urlsPath = "/home/student/Desktop/rokovi/test/urls";
        try(DirectoryStream<Path> ds = Files.newDirectoryStream(Paths.get(urlsPath))){
            for(Path p : ds){

                try(BufferedReader fileIn = new BufferedReader(new InputStreamReader(new FileInputStream(new File(p.toString()))))
                   ){
                      lineCounts.put(p.toString(),0);
                      String line;
                      while( (line = fileIn.readLine()) != null){
                          lineCounts.merge(p.toString(), 1, Integer::sum);
                      }
                    }
            }

            for(String key : lineCounts.keySet()){
                System.out.println(key + " " + lineCounts.get(key));
            }
            System.out.println();

            //ostavio sam id deo koda iznad da bih imao i ispis broja linija i statistike o protokolima,
            //iako se u zadataku izglda trazi da drugo zameni prvo
            for(String key : lineCounts.keySet()){
               (new FileThread(key)).start();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static class FileThread extends Thread{
        private String filePath;
        private Map<String, Integer> stats = new HashMap<>();
        FileThread(String file){
            this.filePath = file;
        }

        @Override
        public void run() {
            try(BufferedReader fileIn = new BufferedReader(new InputStreamReader(new FileInputStream(new File(filePath))))
            ){
                String line;
                while((line = fileIn.readLine()) != null){
                    try{
                        URL url = new URL(line);
                        stats.merge(url.getProtocol(), 1, Integer::sum);

                    }catch (MalformedURLException e){
                        continue;
                    }
                }
                synchronized (threadIsWriting) {
                    while (threadIsWriting.get()){
                        try{
                            threadIsWriting.wait();
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }

                    threadIsWriting.set(true);
                    System.out.println("- " + filePath);
                    for (String key : stats.keySet()) {
                        System.out.println("\t" + key + ": " + stats.get(key));
                    }

                    threadIsWriting.set(false);
                    threadIsWriting.notifyAll();
                }
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

}
