package RM_4I_2020_JAN2;

import java.io.IOException;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLStreamHandler;

public class zadatak_2_Handler extends URLStreamHandler {

    @Override
    protected int getDefaultPort() {
        return 12345;
    }

    @Override
    protected URLConnection openConnection(URL u) throws IOException {
        return new zadatak_2_DayTimeUrlConnection(u);
    }
}
