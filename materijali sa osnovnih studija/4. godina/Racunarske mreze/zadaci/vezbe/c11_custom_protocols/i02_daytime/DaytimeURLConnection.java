package i02_daytime;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.SequenceInputStream;
import java.net.Socket;
import java.net.URL;
import java.net.URLConnection;
import java.nio.charset.StandardCharsets;

final class DaytimeURLConnection extends URLConnection {
    public final static int DEFAULT_PORT = 8765;

    private Socket connection = null;


    DaytimeURLConnection(URL u) {
        super(u);
    }


    @Override
    public synchronized InputStream getInputStream() throws IOException {
        if (!this.connected)
            connect();
        String header = "<html><head><title>The Time at " + url.getHost()
                + "</title></head><body><h1>";
        String footer = "</h1></body></html>";
        InputStream in1 = new ByteArrayInputStream(header.getBytes(StandardCharsets.ISO_8859_1));
        InputStream in2 = this.connection.getInputStream();
        InputStream in3 = new ByteArrayInputStream(footer.getBytes(StandardCharsets.ISO_8859_1));
        //SequenceInputStream spaja 2 input streama. kad se zavrsi sa prvim, prelazi se na drugi
        return new SequenceInputStream(new SequenceInputStream(in1, in2), in3);
    }

    @Override
    public String getContentType() {
        return "text/html";
    }

    @Override
    public synchronized void connect() throws IOException {
        if (!this.connected) {
            int port = this.url.getPort();
            if (port <= 0 || port > 65535) {
                port = DEFAULT_PORT;
            }
            this.connection = new Socket(url.getHost(), port);
            this.connected = true;
        }
    }
}