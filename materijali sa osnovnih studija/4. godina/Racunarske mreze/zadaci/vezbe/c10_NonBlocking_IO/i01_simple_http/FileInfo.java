package i01_simple_http;

import java.io.FileInputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;

final class FileInfo {

    static FileInfo get(Path path, Charset encoding) throws IOException {
        try (var fin = new FileInputStream(path.toString())){
            //nad file input streamom mozemo otvoriti kanal
            FileChannel fc = fin.getChannel();
            //a nad tim kanalom imamo metod map koji mapira sadrzaj u bytebuffer sto nam bas i treba
            //ovo je lakse nego da rucno citamo ceo fajl i ubacujemo u bytebufer
            //argumenti za map su (map_mode, pocetna_pozicija, krajnja_pozicija)
            ByteBuffer data = fc.map(FileChannel.MapMode.READ_ONLY, 0, fc.size());
            //probeContentType() nam bas vraca tip fajla,s to nam je zgodno jer hocemo da pravimo MIME type sami
            return new FileInfo(Files.probeContentType(path), encoding, data);
        } catch (IOException ex){
            ex.printStackTrace();
            throw ex;
        }
    }


    private final String MIMEType;
    private final Charset encoding;
    private final ByteBuffer data;


    private FileInfo(String MIMEType, Charset encoding, ByteBuffer data) {
        this.MIMEType = MIMEType;
        this.encoding = encoding;
        this.data = data;
    }


    String getMIMEType() {
        return this.MIMEType;
    }

    Charset getEncoding() {
        return this.encoding;
    }

    ByteBuffer getData() {
        return this.data;
    }
}
