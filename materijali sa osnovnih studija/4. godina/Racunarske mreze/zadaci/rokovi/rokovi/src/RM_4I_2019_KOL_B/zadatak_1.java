package RM_4I_2019_KOL_B;

import java.io.IOException;
import java.net.URL;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

//radjeno na windowsu, nisam mogao da testiram lepo

public class zadatak_1 {

    static int regularFileCounter = 0;
    static List<URL> urls = new ArrayList<URL>();
    static List<Thread> threads = new ArrayList<Thread>();
    static AtomicInteger counter = new AtomicInteger(0);


    public static void main(String[] args) throws InterruptedException {

        walkDirectory(Paths.get("C:\\Users\\Jovan\\Desktop\\RM\\rokovi\\test"));
        System.out.println("files: " + regularFileCounter);
        for(URL url : urls){
            System.out.println("url:    " + url);
            Thread t = new Thread(new zadatak_1_thread(url, counter));
            threads.add(t);
            t.start();
        }

        for(Thread t : threads){
            t.join();
        }

        System.out.println("result: " + counter);

    }

    static void walkDirectory(Path path){
        try(DirectoryStream<Path> ds = Files.newDirectoryStream(path);) {
            for(Path p : ds){
                if(Files.isDirectory(p)){
                    walkDirectory(p);
                }else if(Files.isRegularFile(p)){
                    regularFileCounter++;
                    if(p.toString().endsWith(".c")){
                        urls.add( new URL("FILE://" + p.toString()) );
                    }
                }

            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
