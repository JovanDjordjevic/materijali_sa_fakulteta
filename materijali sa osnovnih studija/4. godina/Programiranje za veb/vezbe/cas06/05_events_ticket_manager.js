// ovde samo pravimo malo kompleksniji primer koji koristi dogadjaje

const events = require('events');

class TicketManager extends events.EventEmitter{
    constructor(supply){
        super();
        this.supply = supply;
    }

    buy(email, price){
        if(this.supply > 0){
            this.supply--;
            // primetimo da pozivamo emit iz this, to je ovde okej jer ce se znati 
            // da je to ovaj konkretan objekat iz konteksta (generalno pazimo da ne pozivamo emit
            // na globalnim this ili negde gde se ne moze zakljuciti iz konteksta)
            this.emit('buy', email, price, Date.now());
            return;
        }

        this.emit('error', new Error("No more tickets!"));
    }
}


class DBService {
    save(email, price, timestamp){
        console.log(`INSERT INTO purchases VALUES (${email}, ${price}, ${timestamp})`);
    }  
}


class EmailService{
    send(email, price){
        console.log(`TO: ${email} \nBody: you have purchased a ticket for ${price}`);
    }
}


const ticketManager = new TicketManager(2);
const emailService = new EmailService();
const dbService = new DBService();

// NOTE: ovo u komentaru ispod nije validno jer ta email klasa ne nasledjuje EventEmitter!!!
// emailService.on('buy', () => {...});

// inace objekat moze da osluskuje samo dogadjaje koje on sam i emituje, dakle ticketManager jedino moze da osluskuje za buy i error dogadjaje
// ako bismo hteli da neki drugi objekat reaguje na njig, prvo bi taj objekat morao da nasledi EventEmitter, a onda 
// npr u ovoj obradi ispod, da se za taj drugi objekat emituje dogadjaj, npr emaiService.emit(...) a onda ispod negde u kodu da se 
// podesi i dogovarajuci 'on' za taj dogadjaj

// podesavamo osluskivanje dogadjaja
ticketManager.on('buy', (email, price, timestamp) => {
    emailService.send(email, price);
    dbService.save(email, price, timestamp);
});

ticketManager.on('error', (err) => {
    console.log(err);
});

// simuliramo neku kupovinu karata
ticketManager.buy('pera@email.com', 20); 
ticketManager.buy('mika@email.com', 30); 
ticketManager.buy('steva@email.com', 10); 