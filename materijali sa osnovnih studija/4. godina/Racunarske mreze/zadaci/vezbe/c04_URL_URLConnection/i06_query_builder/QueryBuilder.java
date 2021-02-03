package i06_query_builder;

import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;

//ovo nam je pomocna klasa koja ce generisati nas query URL za REST API
//main je u QyeryBuilerTest. Ovaj primer radi GET request, a sledeci radi POST request

// Constructs a GET request URL by concatenating base URL and query key-value pairs
// BASE_URL?key1=value1&key2=value2& ... &keyn=valuen
public class QueryBuilder {

	//StringBuffer je slicno kao StringBuilder (moglismo i to da koristimo), samo sto
	//je StringBuffer thread safe!
	private StringBuffer query;
	private boolean hasQuery;

	public QueryBuilder(String baseUrl) {
		this.query = new StringBuffer(baseUrl);
	}

	public void append(String name, String value) {
		//query pocinje sa ? a svaki naredni par se nadovezuje sa &
		//npr:  nesto/endpoint/?key=value&key1=value1  itd, zato moramo da pazimo da samo jednom nadovezemo ?
		//a svaki anredni put &
		this.query.append(this.hasQuery ? '&' : '?');
		this.hasQuery = true;       //podrazumevano je false (nismo ga sami inicijalizovali, a mogli smo)(u javi su svi primitivni tipovi po defaulutu
									//psotavljeni na sve nule u memoriji pa od tipa zavisi kako se to cita, npr sve 0 su false kad se tretiraju kao boolean)
									//nakon prvog poziva append funkcije ovo je true i vise nikada se nece nadovezati ? na pocetku
		this.encode(name, value);
	}

	// We need to "URL encode" the strings. Why? Consider the case when our
	// string has a '&' character. Also, spaces and slashes can mess up the
	// URL - naturally they need to be "escaped" in a way. That is what
	// "URL encoding" is all about. We cannot use \ escapes so there is a
	// special mapping for special characters (read more @
	// http://www.cheat-sheets.org/sites/html.su/urlencoding.html)
	// URLEncoder class already has a method which does all the work for us.
	private void encode(String name, String value) {
		this.query.append(URLEncoder.encode(name, StandardCharsets.UTF_8));
		this.query.append('=');
		this.query.append(URLEncoder.encode(value, StandardCharsets.UTF_8));
	}

	//postoji i URLDecoder klasa koja samo radi obrnuto od URLEncoder

	@Override
	public String toString() {
		return this.query.toString();
	}

	public URL toUrl() throws MalformedURLException {
		return new URL(this.toString());
	}
}
