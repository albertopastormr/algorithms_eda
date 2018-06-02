﻿// Alberto Pastor Moreno
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
long int iniciarSumMin(std::vector<std::vector<int> > const & m){
	long int sol = m[0][0];
	int r = 0;
	for (int g = 1; g < m[0].size(); g++){
		if (g % 3 == 0) r++; 
		sol += m[r][g];
	}
	return sol;
}

std::vector<int> acumulado(std::vector<std::vector<int> > const & m){
	std::vector<int> minimos(m[0].size());
	for (int k = 0; k < m[0].size(); k++){ // Llena el vector de minimos con el minimo de cada nivel ( el precio minimo de cada producto)
		int mini = m[0][k];
		for (int l = 0; l < m.size(); l++) if (m[l][k] < mini) mini = m[l][k];
	}
	// Acumula
	for (int u = minimos.size() - 1; u > 0; u--) minimos[u - 1] += minimos[u];
	return minimos;
}

// función que resuelve el problema
void compras(std::vector<std::vector<int> > const & m, int k, std::vector<int> & marcas, bool & exito, long int & sum, long int & sumMin, std::vector<int> const & acum) {
	for (int x = 0; x < m.size(); x++){ // m.size() = numSup
		sum += m[x][k];
		marcas[x]++;
		if (marcas[x] <= 3){
			if (k + 1 == m[0].size()){
				if (sum < sumMin) {
					sumMin = sum;
					exito = true;
				}
			}
			else  if (sum + acum[k+1] < sumMin) compras(m, k + 1, marcas, exito, sum, sumMin, acum);
		}
		marcas[x]--;
		sum -= m[x][k];
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	int numSup, numProd;
	std::cin >> numSup >> numProd;
	if (numProd == 0) std::cout << "Sin solucion factible\n";
	else{
		std::vector<std::vector<int> > m(numSup, std::vector<int>(numProd));
		for (int i = 0; i < numSup; i++) // Lectura Matriz de entrada
			for (int j = 0; j < numProd; j++)
				std::cin >> m[i][j];
		std::vector<int> marcas(numSup); // Vector de marcaje de los supermercados
		for (int r = 0; r < numSup; r++) marcas[r] = 0; // Inicializacion del vector marcas a 0
		bool exito = false;
		long int sum = 0;
		long int sumMin = iniciarSumMin(m); // Inicializo sumMin a la primera posible combinacion
		std::vector<int> acum = acumulado(m); // Vector con los minimos acumulados para estimar en compras()
		compras(m, 0, marcas, exito, sum, sumMin, acum);
		// escribir sol
		if (!exito) std::cout << "Sin solucion factible\n";
		else std::cout << sumMin << "\n";
	}
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}