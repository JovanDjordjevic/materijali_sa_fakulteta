package i05_pooled_weblog;

import java.io.IOException;
import java.net.InetAddress;
import java.util.List;

final class LookupRunnable implements Runnable {
	private PooledWeblog log;
	private final List<String> entries;

	
	LookupRunnable(PooledWeblog log) {
		this.log = log;
		// Holding a reference to entry list, so the code will be simpler
		this.entries = log.getEntries();
	}
	

	@Override
	public void run() {
		// Each iteration, the thread is taking an entry from the list an processing it
		for (String entry = this.getNextEntry(); entry != null; entry = this.getNextEntry()) {
			String workResult = this.analyzeEntryAndGetResult(entry);
			if (workResult == null)
				continue; 	// unexpected contents, go to next line

			try {
				this.log.log(workResult);
			} catch (IOException ex) {
				ex.printStackTrace();
			}

			// Yielding means that the thread is not doing anything particularly
			// important and if any other threads or processes need to be run,
			// they should run. Otherwise, the current thread will continue
			Thread.yield();
		}
	}

	private String getNextEntry() {
		synchronized (this.entries) {
			while (this.entries.size() == 0) {
				// If the list is empty we need to check if the job is done
				if (this.log.isFinished()) {
					System.err.println("Thread exiting: " + Thread.currentThread());
					return null;
				}

				// If the log isn't processed fully, we wait for a line
				// to be added so we can remove it and process it
				try {
					this.entries.wait();
				} catch (InterruptedException ex) {
					ex.printStackTrace();
				}
			}
			// At this point we may have multiple threads notified
			// that an element is added to the list so the loop
			// condition does not stand. Normally all threads
			// would come to this point in code. However, since
			// we are still inside a synchronized block only one
			// thread will "continue" from the wait() onwards, and
			// remove the entry from the queue. Other threads will
			// then continue execution from the `wait()` line one
			// by one, and loop since the list is now again empty.
			return entries.remove(0);
		}
	}

	private String analyzeEntryAndGetResult(String entry) {
		//ako pogledmao kako log fajl izgleda, vidimo da je od pocetka do prvog space-a neka ip adresa
		//ako nemamo  space u liniji znaci da to nije validna linija, vracamo null jer smo napravili takod a proveravamo null u run()
		int index = entry.indexOf(' ');
		if (index == -1)
			return null;

		String remoteHost = entry.substring(0, index); //od pocetka do indeksa prvog space-a
		String theRest = entry.substring(index);	   //od indeksa prvog space-a do kraja

		// Lookup the host IP address to find hostname (napravimo InetAddress objkeat od hosta ciju ip adresui imamo i uzmemo njegovo ime)
		//NOTE: ako ne postoji host name koji odgovara ip adresi, vratice se samo ip adresa
		try {
			remoteHost = InetAddress.getByName(remoteHost).getHostName();
		} catch (Exception ex) {
			ex.printStackTrace();
		}

		// Here we can do some special logic with theRest string, for example
		// we can take a look at the timestamps and calculate the periods of
		// the day when the server is under heavy load. Ofcourse, this is just
		// an example and we can do whatever we want or need depending of what
		// our app needs to do. For this example we will just print the rest
		return remoteHost + theRest;
	}
}
