﻿// Alberto Pastor Moreno	
// E46

/*
Coste O(n)
Ecuacion recurrencia:
T(n):	- c0			si n = 0, 1
- c1 + 2*T(n/2) si n>1
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

int mincam(std::vector<int> const & v, int ini, int fin){
	int sol;
	if (ini + 1 == fin){
		sol = v[ini];
	}
	else{
		int mitad = (ini + fin) / 2;
		int solIz = mincam(v, ini, mitad);
		int solDr = mincam(v, mitad, fin);
		if (solIz <= solDr){
			sol = solIz;
		}
		else{
			sol = solDr;
		}
	}
	return sol;
}

// función que resuelve el problema
int resolver(std::vector<int> const & v) {
	return mincam(v, 0, v.size());
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int numElem;
	std::cin >> numElem;
	if (!std::cin)
		return false;
	std::vector<int> v(numElem);
	for (int i = 0; i < numElem; i++){
		std::cin >> v[i];
	}
	int sol = resolver(v);
		// escribir sol
	std::cout << sol << "\n";
	return true;

}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	while (resuelveCaso())
		;


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}