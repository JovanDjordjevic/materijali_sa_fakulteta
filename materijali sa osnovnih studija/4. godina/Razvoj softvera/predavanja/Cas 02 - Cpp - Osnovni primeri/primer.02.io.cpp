#include <iostream>

using namespace std;

//	Imena se definisu u "prostorima imena". 
//	Standardna biblioteka (skoro cela) je u prostoru imena "std".
//	Puno kvalifikovano ime objekta "cout" je "std::cout".
//	Direktivom "using namespace std" se sva imena iz "std" 
//	uvode u globalni prostor imena.

//	Direktiva je preporucljiva u glavnom programu i kratkim programima,
//	ali nije preporucljiva pri pisanju biblioteka.

int main() {
	cout << "Zdravo\n";
}

