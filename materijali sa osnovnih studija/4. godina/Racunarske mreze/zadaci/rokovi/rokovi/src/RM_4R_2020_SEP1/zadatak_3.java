package RM_4R_2020_SEP1;

//zadatak 1 i 2 su isti kao na sep1 roku na I smeru

import java.io.*;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

public class zadatak_3 {

    public static List<String> files = new ArrayList<String>();
    public static Map<String, Integer> wordCounts = Collections.synchronizedMap(new HashMap<String, Integer>());

    public static void main(String[] args) {

        try(Scanner sc = new Scanner(System.in)){
            System.out.println("Unesi putanju do direktorijuma");
            //String dirPath = sc.nextLine();
            String dirPath = "/home/student/Desktop/rokovi/test";

            walk(Paths.get(dirPath));
            System.out.println();

            List<FileThread> threads = new ArrayList<FileThread>();

            for(String file : files){
                FileThread t = new FileThread(file);
                t.start();
                threads.add(t);
            }

            for(FileThread ft : threads){
                ft.join();
            }

            List<Map.Entry<String, Integer>> entries = new ArrayList<>(wordCounts.entrySet());
            Collections.sort(entries, new Comparator<Map.Entry<String, Integer>>() {
                @Override
                public int compare(Map.Entry<String, Integer> o1, Map.Entry<String, Integer> o2) {
                    return Integer.compare(o2.getValue(), o1.getValue());
                }
            });

            for(var entry : entries){
                System.out.println(entry.getKey() + ": " + entry.getValue());
            }


        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }


    public static void walk(Path dirPath){
        try(DirectoryStream<Path> ds = Files.newDirectoryStream(dirPath)){

            for (Path p : ds){
                if(Files.isRegularFile(p) && p.toString().endsWith(".txt")){
                    int linesRead = 0;
                    try(BufferedReader fileReader = new BufferedReader(new InputStreamReader(new FileInputStream(new File(p.toString())))); ) {
                        String line;
                        while ((line = fileReader.readLine()) != null) {
                            linesRead++;
                        }

                        System.out.println(p.toString() + "     line count: " + linesRead);
                        files.add(p.toString());
                    }
                }else if(Files.isDirectory(p)){
                    walk(p);
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }



    public static class FileThread extends Thread{
        private String file;
        FileThread(String file) {this.file = file;}

        @Override
        public void run() {
            try(BufferedReader fileIn = new BufferedReader(new InputStreamReader(new FileInputStream(new File(this.file))))){

                String line;
                while ((line = fileIn.readLine()) != null){
                    String[] words = line.split(" ");
                    for(String word : words){
                        synchronized (wordCounts){
                            wordCounts.merge(word, 1, Integer::sum);
                        }
                    }
                }

            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

}
