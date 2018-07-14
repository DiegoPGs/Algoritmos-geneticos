#pragma once
#include "vector"
#include <stack>
#include "algorithm"
#include "cmath"
#include "ctime"
#include "random"

#include "iostream"
#include "cstdlib"

//DEFINITION

//AUX
void mostrar(std::vector<std::vector<int>>& poblacion);
inline int bit_Aleatorio();
int get_Aptitude(std::vector<int>& individue);
//INITIALIZATION
std::vector<std::vector<int>> crear_Poblacion(int tamPoblacion, int tamano);
// Changed this function
void agregar_Individuo(std::vector<std::vector<int>>& poblacion, std::vector<int>& individuo);
//CROSSING
std::vector<int> chromosome_Crossing_Two_Point(std::vector<int>& parent1, std::vector<int>& parent2, int size, bool sex);
std::vector<int> chromosome_Crossing_Cross_Uniform(std::vector<int>& parent1, std::vector<int>& parent2, int size, bool sex);
std::vector<int> chromosome_Crossing_Cross_Accented(std::vector<int>& parent1, std::vector<int>& parent2, int size, bool sex);
std::vector<int> order_Crossover(std::vector<int>& parent1, std::vector<int>& parent2, int size, bool sex);
//MUTATION
std::vector<int> mutate_Insertion(std::vector<int>& individue);
std::vector<int> mutate_Displacement(std::vector<int>& individue);
std::vector<int> mutate_Reciprocal_Exchange(std::vector<int>& individue);
std::vector<int> mutate_Heuristical(std::vector<int>& individue);

//IMPLEMENTETATION

//AUX
void mostrar(std::vector<std::vector<int>>& poblacion) {
	auto aux = poblacion;
	for (int i = 0; i != poblacion.size(); ++i) {
		std::cout << "individuo " << i << ": ";
		auto individuo = poblacion[i];
		for (int j = 0; j != individuo.size(); ++j) {
			std::cout << individuo[j] << ' ';
		}
		std::cout << std::endl;
	}
}

// Made the function `inline` to let the compiler optimize easier its uses
inline int bit_Aleatorio() {
	return std::rand() % 2;
}

int get_Aptitude(std::vector<int>& individue) {
	int sum = 0;
	// changed `o`name to `power` to reflect better its purpose
	int power = individue.size() - 1;
	// Changed to reflect bitwise operators and make it more efficiente
	// as well as make it easier to read
	for( auto bit : individue )
		sum += bit * (1 << power--); // Clean and simple, yet the same
	return sum;
}
//INITIALIZATION
std::vector<std::vector<int>> crear_Poblacion(int tamPoblacion, int tamano) {
	// Optimized generation through the use of the vector constructor
	std::vector<std::vector<int>> aux(tamPoblacion, std::vector<int>(tamano));
	// Now let's simplify the `for` to reflect better the changes
	for( auto& individual : aux )
		std::generate( individual.begin(), individual.end(), bit_Aleatorio() );
	return aux;
}

// Tried to fill the hole in the code here
void agregar_Individuo(std::vector<std::vector<int>>& poblacion, std::vector<int>& individuo) {
	// Commenting out in case it's needed back
	// std::vector<std::vector<int>> pob = poblacion;
	// std::vector<int> aux;
	poblacion.emplace_back( individuo ); // Try to place it at the back with `std::move` semantics as well
}

//CROSSING
std::vector<int> chromosome_Crossing_Two_Point(std::vector<int>& parent1, std::vector<int>& parent2, int size, bool sex) {
	std::vector<int> aux(size);
	int piv1 = std::rand() % size;
	int piv2 = std::rand() % size;

	// Changed logic a little to avoid an extra computation
	while (piv1 == piv2) piv2 = std::rand() % size;

	bool point = true;

	for (int i = 0; i != size; ++i) {
		if (i == piv1 || i == piv2)
			point = !point;
		if (point) {
			if (sex)
				aux[i] = parent1[i];
			else
				aux[i] = parent2[i];
		}
		else {
			if (sex)
				aux[i] = parent2[i];
			else
				aux[i] = parent1[i];
		}
	}
	return aux;
}
std::vector<int> chromosome_Crossing_Cross_Uniform(std::vector<int>& parent1, std::vector<int>& parent2, int size, bool sex) {
	std::vector<int> aux(size / 2), aux2(size / 2);

	for (int i = 0; i < (size / 2); i++) {
		if (bit_Aleatorio()) {
			aux[i] = parent1[i];
			aux2[i] = parent2[i];
		}
		else {
			aux[i] = parent2[i];
			aux2[i] = parent1[i];
		}
	}
	if (sex) {
		aux.insert(aux.end(), aux2.begin(), aux2.end());
		return aux;
	}
	else {
		aux2.insert(aux2.end(), aux.begin(), aux.end());
		return aux2;
	}
}
std::vector<int> chromosome_Crossing_Cross_Accented(std::vector<int>& parent1, std::vector<int>& parent2, int size, bool sex) {
	std::vector<int> aux(size), offspring(size);
	int stc_iterator = 0;

	for (int i = 0; i < size; i++) {
		if (bit_Aleatorio())
			stc_iterator++;
		aux[i] = stc_iterator;
		{
			if (aux[i] == stc_iterator - 1) {
				if (sex)
					offspring[i] = parent2[i];
				else
					offspring[i] = parent1[i];
			}
			else {
				if (sex)
					offspring[i] = parent1[i];
				else
					offspring[i] = parent2[i];
			}
		}
	}
	return offspring;
}
/*
ox
pmx
position based
order based crossover
cx
*/
std::vector<int> order_Crossover(std::vector<int>& parent1, std::vector<int>& parent2, int size, bool sex) {
	//parent A substring selection
	std::vector<int> aux(size);
	std::stack<int> substring;
	int piv1 = std::rand() % size;
	int piv2 = std::rand() % size;

	do {
		piv2 = std::rand() % size;
	} while (piv1 == piv2);

	for (int i = 0; i != size; ++i) {
		// Cleared an unneeded `if` since both ways lead to the same path
		// Since the condition to insert `i` to `substring` is `i >= piv1 and i <= piv2` we can simplify here
		// and save the computation of `std::find` in the vector
		if ( i >= piv1 and i <= piv2 ) {
			// as we just need to check if the ith element is in the range and exists
			// but it exists when is in the range, thus we can ease the computations
			if (sex) aux[i] = parent1[i];
			else aux[i] = parent2[i];
		}
		else {
			if (sex) {
				aux[i] = parent2[i];
			}
			else
				aux[i] = parent1[i];
		}
		return aux;
	}
	std::cout << std::endl;
	// I need to read more to modify this part.
	//string generation with the substring parent A
	for (int i = 0; i != size; ++i) {
		
	}

	return aux;
}



//MUTATION
std::vector<int> mutate_Insertion(std::vector<int>& individue) {
	// Simplified the copy of `individue` with the copy constructor
	std::vector<int> aux(individue);
	int piv1 = std::rand() % individue.size();
	int piv2 = std::rand() % individue.size();
	// Changed the logic to reduce by one computation the `while` loop
	while (piv1 == piv2) piv2 = std::rand() % individue.size();
	// Thus, removed the `for` that copied `individue` to `aux`
	aux[piv1] = individue[piv2];
	return aux;
}
std::vector<int> mutate_Displacement(std::vector<int>& individue) {
	// Simplified the copy of `individue` with the copy constructor
	std::vector<int> aux(individue);
	int piv = std::rand() % individue.size() - 1;
	// Changed the logic to reduce one computation in the `while` loop
	while (piv == 0) piv = std::rand() % individue.size() - 1;
	for (int i = 0; i != piv; ++i) {
		aux[i] = individue[i];
	}
	// Replaced the for that copies elements from `individue` to `aux`.
	std::copy( individue.begin() + piv + 1, individue.end(), aux.begin() + piv );
	// for (int i = piv; i != individue.size() - 1; ++i) {
	// 	aux[i] = individue[i + 1];
	// }
	// Fixed an `off-by-one' vector access
	aux[individue.size() - 1] = bit_Aleatorio();
	return aux;
}
std::vector<int> mutate_Reciprocal_Exchange(std::vector<int>& individue) {
	// Simplified the copy of `individue` with the copy constructor
	std::vector<int> aux(individue);
	int piv1 = std::rand() % individue.size();
	int piv2 = std::rand() % individue.size();
	// Changed the logic to reduce one computation in the `while` loop
	while (piv1 == piv2) piv2 = std::rand() % individue.size();
	aux[piv1] = individue[piv2];
	aux[piv2] = individue[piv1];

	return aux;
}
std::vector<int> mutate_Heuristical(std::vector<int>& individue) {
	std::vector<int> aux(individue.size()), substring;
	std::random_device rd;
	std::mt19937 g(rd());
	int piv1 = (std::rand() % individue.size())/2;
	int piv2 = piv1 + (std::rand() % 4);
	// Changed the logic to reduce one computation in the `while` loop
	// though I think maybe this can be avoided if we add an offset to
	// the initialization of `piv2` (make it modulo 3 and add always 1)
	while (piv2 == piv1) piv2 = piv1 + (std::rand() % 4);

	for (int i = 0; i != individue.size(); ++i)
		// Removed an innecesary decision tree and made code clearer
		if (i >= piv1 && i <= piv2) substring.emplace_back(i);

	std::shuffle(substring.begin(), substring.end(), g);
	for (int i = 0; i != individue.size(); ++i) {
		if (std::find(substring.begin(), substring.end(), i) != substring.end()) {
			aux[i] = individue[substring.back()];
			substring.pop_back();
		}
		else
			aux[i] = individue[i];
	}
	
	return aux;
}
