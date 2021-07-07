#include "polygon.hpp"
#include <iostream>
#include <dlfcn.h> //ovo je biblioteka u kojoj su makroi koji sluze za dlopen, kao ovaj RTLD_LAZY (?)  jel ovo samo za linuks (?)

int main()
{
    using std::cerr;
    using std::cout;
    using std::endl;

    // Ucitavamo plugin biblioteku (dlopen sistemski poziv koji ucitava dinamisku biblioteku)
    //ovaj LAZY flag kaze da se nista zapravo ne ucita dok se ne pozove dlsym  ispod
    void *matf_library_handle = dlopen("libmatf.so", RTLD_LAZY);
    if (!matf_library_handle)
    {
        cerr << "Cannot load library: " << dlerror() << '\n';
        return 1;
    }

    // Resetujemo greske
    dlerror();

    // Ucitavamo simbol (dlsym je sistemski poziv koji iz biblioteke ucitava simbol pod "")
    // posto se ovo dinamicki razresava, ovde nece proci static_cast jer se static radi u toku kompilacije
    //NOTE: ovde nebi radio ni dynamic_cast
    create_t *create_triangle = reinterpret_cast<create_t *>( dlsym(matf_library_handle, "create") );
    const char *dlsym_error = dlerror();
    if (dlsym_error)
    {
        cerr << "Cannot load symbol create: " << dlsym_error << endl;
        return 1;
    }

    destroy_t *destroy_triangle = reinterpret_cast<destroy_t *>( dlsym(matf_library_handle, "destroy") );
    dlsym_error = dlerror();
    if (dlsym_error)
    {
        cerr << "Cannot load symbol destroy: " << dlsym_error << endl;
        return 1;
    }

    // Kreiramo instancu klase
    polygon *poly = create_triangle();

    poly->set_side_length(12);
    cout << "Povrsina trougla je: " << poly->area() << endl;

    // Ucistavamo instancu klase
    destroy_triangle(poly);

    // Zatvaramo biblioteku
    dlclose(matf_library_handle);

    return 0;
}