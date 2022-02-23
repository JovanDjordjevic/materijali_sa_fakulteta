# pravi se klasa koja u sebi ima neka polja koja su gdbu potrebna da bi je registrovao kao novu komandu (?)
# klasa mora da nasledi gdb.Command
class ContOrRun(gdb.Command):
    def __init__(self):
        # ovo initu se prolsedjuje ime kako ce pozivati komanda u gdbu (cont_or_run), a ovaj drugi param oznacava da je to komanda
        super(ContOrRun, self).__init__('cont_or_run', gdb.COMMAND_USER)
    
    # nasa klasa mora da implementira metod invoke koji prima ove parametre
    # arg je argument koji se prosledi komnandi, nas primer nece koristiti ovo
    # from_tty je oznaka da li je komanda izvrsena iz unix shella (tty je neki stari naziv za unix shell (?)), necemo ni ovo da korsitimo
    def invoke(self, arg, from_tty):
        # hocemo da ako je program pokrenut izvrsi continue, a ako program nije pokrenut da se izvrsi run
        # gdb ima nesto sto se zove inferiors, to je lista programa koji su trenutno ucitani za debagovanje (ugl ce to biti samo jedan program, ali postoji mogucnost
        # i da debagujemo vise programa u isto vreme)
        # selected_inferior nam daje program koji je trenutno ucitan za debagovanje, a da bismo dobili informaciju da li je porkenut ili ne,
        # mozemo da vidimo koliko niti mu je dodeljeno (0 znaci nije pokrenut, vise od 1 znaci jeste)
        if len(gdb.selected_inferior().threads()) > 0:
            gdb.execute('continue')
        else:
            gdb.execute('run')

# sada kada smo definisali klasu, treba samo da napravimo jednu njenu instancu
# i kada zelimo da korsitimo nasu komandu iz trenutne gdb sesije, navescemo putanju do ovog pajton fajla
ContOrRun()