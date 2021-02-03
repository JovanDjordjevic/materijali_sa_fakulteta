package i06_query_builder;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.Random;
import java.util.Scanner;

final class QueryBuilderTest {

	public static void main(String[] args) {

		int jokeId = new Random().nextInt(500) + 1;  //~500  gornja granica jer smo videli da otprilike ima toliko sala
		//ako odemo na ovja sajt videcemo da je to kao neki JSON u kome su chuck norris sale
		String endpoint = "http://api.icndb.com/jokes/" + jokeId  + "/";

		QueryBuilder qb = new QueryBuilder(endpoint);
		//sa stdin cemo unositi neke parametre koje cemo nadovezivati parove (kljuc vrednost) na nas query

		try (Scanner sc = new Scanner(System.in)) {
			System.out.println("Enter your first name:");
			qb.append("firstName", sc.nextLine());
			System.out.println("Enter your last name:");
			qb.append("lastName", sc.nextLine());
		}

		System.err.print("Sending GET request: ");
		System.err.println(qb);  //predefinisacemo toString tako da ispisuje url
		
		try {
			URL u = qb.toUrl();

			String json;
			try (BufferedReader in = new BufferedReader(new InputStreamReader(u.openStream()))) {
				json = in.readLine();  //dovoljno nam je readLine jer smo primetili da ce odgovor stici kao jedna linija
			}

			// Extract joke field value from json response
			int jokeFieldPos = json.indexOf("joke") + 8;
			String joke = json.substring(jokeFieldPos, json.indexOf('"', jokeFieldPos));

			System.out.println("A random joke to brighten up your day:");
			System.out.println(joke);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
