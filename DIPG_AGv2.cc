#pragma once
#include "vector"
#include "algorithm"
#include "cmath"
#include "ctime"

#include "iostream"
#include "cstdlib"

//AUX
void mostrar(std::vector<std::vector<int>>& poblacion);
int bit_Aleatorio();
int get_Aptitude(std::vector<int>& individue);
//INITIALIZATION
std::vector<std::vector<int>> crear_Poblacion(int tamPoblacion, int tamano);
std::vector<std::vector<int>> agregar_Individuo(std::vector<std::vector<int>> poblacion, std::vector<int> individuo);
//CROSSING
std::vector<int> chromosome_Crossing_Two_Point(std::vector<int>& parent1, std::vector<int>& parent2, int size, bool flag);
std::vector<int> chromosome_Crossing_Cross_Uniform(std::vector<int>& parent1, std::vector<int>& parent2, int size, bool flag);
std::vector<int> chromosome_Crossing_Cross_Accented(std::vector<int>& parent1, std::vector<int>& parent2, int size, bool flag);
std::vector<int> order_Crossover(std::vector<int>& parent1, std::vector<int>& parent2, int size, bool flag);
//MUTATION
std::vector<int> mutate_Insertion(std::vector<int>& individue);
std::vector<int> mutate_Displacement(std::vector<int>& individue);
std::vector<int> mutate_Reciprocal_Exchange(std::vector<int>& individue);
std::vector<int> mutate_Heuristical(std::vector<int>& individue);




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
int bit_Aleatorio() {
	return std::rand() % 2;
}
int get_Aptitude(std::vector<int>& individue) {
	int sum = 0;
	int o = 0;
	for (int i = individue.size() - 1; i >= 0; --i) {
		sum += individue[i] * pow(2, o);
		++o;
	}
	return sum;
}
//INITIALIZATION
std::vector<std::vector<int>> crear_Poblacion(int tamPoblacion, int tamano) {
	std::vector<std::vector<int>> aux;
	for (int i = 0; i != tamPoblacion; ++i) {
		std::vector<int> individue(tamano);
		std::generate(individue.begin(), individue.end(), bit_Aleatorio);
		aux.insert(aux.end(), individue);
	}
	return aux;
}
std::vector<std::vector<int>> agregar_Individuo(std::vector<std::vector<int>>& poblacion, std::vector<int>& individuo) {
	std::vector<std::vector<int>> pob = poblacion;
	std::vector<int> aux;

	return pob;
}
//CROSSING
std::vector<int> chromosome_Crossing_Two_Point(std::vector<int>& parent1, std::vector<int>& parent2, int size, bool flag) {
	std::vector<int> aux(size);
	int piv1 = std::rand() % size;
	int piv2 = std::rand() % size;

	do {
		piv2 = std::rand() % size;
	} while (piv1 == piv2);

	bool point = true;

	for (int i = 0; i != size; ++i) {
		if (i == piv1 || i == piv2)
point = !point;
if (point) {
	if (flag)
		aux[i] = parent1[i];
	else
		aux[i] = parent2[i];
}
else {
	if (flag)
		aux[i] = parent2[i];
	else
		aux[i] = parent1[i];
}
	}
	return aux;
}
std::vector<int> chromosome_Crossing_Cross_Uniform(std::vector<int>& parent1, std::vector<int>& parent2, int size, bool flag) {
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
	if (flag) {
		aux.insert(aux.end(), aux2.begin(), aux2.end());
		return aux;
	}
	else {
		aux2.insert(aux2.end(), aux.begin(), aux.end());
		return aux2;
	}
}
std::vector<int> chromosome_Crossing_Cross_Accented(std::vector<int>& parent1, std::vector<int>& parent2, int size, bool flag) {
	std::vector<int> aux(size), offspring(size);
	int stc_iterator = 0;

	for (int i = 0; i < size; i++) {
		if (bit_Aleatorio())
			stc_iterator++;
		aux[i] = stc_iterator;
		{
			if (aux[i] == stc_iterator - 1) {
				if (flag)
					offspring[i] = parent2[i];
				else
					offspring[i] = parent1[i];
			}
			else {
				if (flag)
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
std::vector<int> order_Crossover(std::vector<int>& parent1, std::vector<int>& parent2, int size, bool flag) {
	//parent A substring selection
	std::vector<int> aux(size), substring;
	int piv1 = std::rand() % size;
	int piv2 = std::rand() % size;

	do {
		piv2 = std::rand() % size;
	} while (piv1 == piv2);

	for (int i = 0; i != size; ++i) {
		bool marca = false;
		if (i == piv1 || i == piv2)
			marca = not marca;
		if (marca) {
			if (flag)
				substring.insert(substring.end(), parent1[i]);
			else
				substring.insert(substring.end(), parent2[i]);
		}
		else {
			if (flag)
				substring.insert(substring.end(), parent2[i]);
			else
				substring.insert(substring.end(), parent1[i]);
		}
	}
	std::cout << std::endl;
	//string generation with the substring parent A
	for (int i = 0; i != size; ++i) {
		bool marca = false;
		//if (std::find(std::begin(substring), std::end(substring), parent1[i]) != std::);

		auto result1 = std::find(std::begin(substring), std::end(substring), parent1[i]);
		if (result1 != substring.end())
			int i;
	}

	return aux;
}

//MUTATION
std::vector<int> mutate_Insertion(std::vector<int>& individue) {
	std::vector<int> aux(individue.size());
	int piv1 = std::rand() % individue.size();
	int piv2 = std::rand() % individue.size();

	do {
		piv2 = std::rand() % individue.size();
	} while (piv1 == piv2);
	for (int i = 0; i != individue.size(); ++i) {
		aux[i] = individue[i];
	}
	aux[piv1] = individue[piv2];

	return aux;
}
std::vector<int> mutate_Displacement(std::vector<int>& individue) {
	std::vector<int> aux(individue.size());
	int piv = std::rand() % individue.size();

	do {
		piv = std::rand() % individue.size() - 1;
	} while ((piv == 0));
	for (int i = 0; i != piv; ++i) {
		aux[i] = individue[i];
	}
	for (int i = piv; i != individue.size() - 1; ++i) {
		aux[i] = individue[i + 1];
	}
	aux[individue.size()] = bit_Aleatorio();

	return aux;
}
std::vector<int> mutate_Reciprocal_Exchange(std::vector<int>& individue) {
	std::vector<int> aux(individue.size());
	int piv1 = std::rand() % individue.size();
	int piv2 = std::rand() % individue.size();

	do {
		piv2 = std::rand() % individue.size();
	} while (piv1 == piv2);
	for (int i = 0; i != individue.size(); ++i) {
		aux[i] = individue[i];
	}
	aux[piv1] = individue[piv2];
	aux[piv2] = individue[piv1];

	return aux;
}
std::vector<int> mutate_Heuristical(std::vector<int>& individue) {
	std::vector<int> aux(individue.size());
	std::vector<int> sub_Aux(3);
	int piv = std::rand() % individue.size();

	do {
		piv = std::rand() % individue.size();
	} while ((piv == 0) || (piv == individue.size()));

	sub_Aux[0] = individue[piv - 1];
	sub_Aux[1] = individue[piv];
	sub_Aux[2] = individue[piv + 1];
	/*
	for (int i = 0; i != individue.size(); ++i) {
		aux[i] = individue[i];
		switch (i) {
		case piv - 1:
			break;
		case piv:
			break;
		case piv + 1:
			break;
		default:
			break;
		}
	}
	*/
	return aux;
}
