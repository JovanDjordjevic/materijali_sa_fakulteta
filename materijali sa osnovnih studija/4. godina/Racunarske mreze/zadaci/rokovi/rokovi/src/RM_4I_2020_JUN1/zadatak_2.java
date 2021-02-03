package RM_4I_2020_JUN1;

import java.io.*;
import java.net.*;
import java.util.Scanner;
import java.util.logging.Handler;

//nisam radio parsiranje urla i radjenje svih zahteva koje server podrzava

public class zadatak_2 {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        System.out.println("unesi adresu");
        String urlString = in.next();
        in.close();

        try {
            URL u = new URL(null, urlString, new Handler());
            URLConnection con = u.openConnection();

            try(BufferedReader networkIn = new BufferedReader(new InputStreamReader(con.getInputStream()))
                ){

                String line;
                while ((line = networkIn.readLine())!=null)
                    System.out.println(line);
            }


        } catch (IOException e) {
            e.printStackTrace();
        }


    }


    public static class ForumConnection extends URLConnection{

        private Socket connection = null;

        ForumConnection(URL u){
            super(u);
        }

        @Override
        public synchronized InputStream getInputStream() throws IOException {
            if(!connected){
                connect();
                return connection.getInputStream();
            }
            else return null;
        }

        @Override
        public synchronized void connect() throws IOException {
            if(!connected){
                int port = this.url.getPort();
                if(port <= 0 || port >= 65535){
                    port = 7337;
                }
                this.connection = new Socket(url.getHost(), port);

                BufferedWriter out = new BufferedWriter(new OutputStreamWriter(connection.getOutputStream()));
                out.write("list");
                out.newLine();
                out.flush();

                this.connected = true;
            }
        }
    }

    public static class Handler extends URLStreamHandler{

        @Override
        protected int getDefaultPort() {
            return 7337;
        }

        @Override
        protected URLConnection openConnection(URL u) throws IOException {
            return new ForumConnection(u);
        }
    }
}
