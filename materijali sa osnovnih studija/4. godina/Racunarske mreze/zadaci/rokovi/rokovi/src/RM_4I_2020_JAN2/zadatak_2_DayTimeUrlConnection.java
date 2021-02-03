package RM_4I_2020_JAN2;

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.net.URL;
import java.net.URLConnection;

public class zadatak_2_DayTimeUrlConnection extends URLConnection {

    private Socket connection = null;

    zadatak_2_DayTimeUrlConnection(URL u){
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
        if(!this.connected){
            int port = this.url.getPort();
            if(port <= 0 || port >= 65535){
                port = 12345;
            }
            this.connection = new Socket(url.getHost(), port);
            this.connected = true;
        }
    }

}
