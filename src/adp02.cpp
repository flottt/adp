#include <iostream>
#include <vector>

/** berechnet die Summe der Quadratzahlen von 0 bis limit 
 * @param int limit Die letzte Zahl, die quadriert werden soll (limit selbst soll noch nicht quadriert sein) 
 * @return long long */
inline long long adp21_summeDerQuadrate(register int limit) {
	/** Akkumulator-Register */
	register long long result = 0; 
	for (register int i = 0; i <= limit; ++i) {
		result += i * i;
	}
	return result; 
}

int adp02_1_main() {
	/** Eingabeparameter n */
	int n = -1; 
	std::cout << "Berechne Summe der Quadratzahlen bis zum Quadrat von n = "; 
	std::cin >> n; 
	// Pruefung gueltige Eingabe 
	if (n < 0) {
		// ungueltige Eingabe 
		std::cout << "ungueltige Eingabe. " << std::endl; 
		std::cin.clear(); 
		return -1;
	} else {
		// gueltige Eingabe 
		long long sum = adp21_summeDerQuadrate(n); 
		std::cout << "Die Summe der Quadratzahlen von 0 bis " << n << " ist " << sum << std::endl; 
		return 0; 
	}
}

bool adp02_3_leseParameter(int & n, int & m) {
	std::cout << "Berechne f(n, m) fur n = "; 
	std::cin >> n; 
	if (n < 0) {
		std::cout << "ungueltige Eingabe. " << std::endl;
		std::cin.clear();
		return false;
	}
	std::cout << "und m = "; 
	std::cin >> m; 
	if (m < 0) {
		std::cout << "ungueltige Eingabe. " << std::endl;
		std::cin.clear();
		return false;
	}
	return true; 
}

long long adp02_3_calc_f_rec(int n, int m) {
	if (n == 0) {
		return m + 1; 
	} else if (m == 0) {
		return adp02_3_calc_f_rec(n - 1, 1);
	} else {
		return adp02_3_calc_f_rec(n - 1, adp02_3_calc_f_rec(n, m - 1)); 
	}
}

int adp02_3_calc_f_it(int n, int m) {
	std::vector<std::vector<int>> tabelle(n + 1); 
	std::vector<int> needs(n + 1, m); 
	std::vector<int> have(n + 1, -1); 
	int y = 0; 

	for (int i = 0; i <= n; ++i) {
		for (int j = have[i] + 1; j <= needs[i]; ++j) {
			if (i == 0) {
				tabelle[i].push_back(j + 1); 
				have[i] = j; 
			} else if (j == 0) {
				tabelle[i].push_back(tabelle[i - 1][1]); 
				have[i] = j; 
			} else {
				y = tabelle[i][j - 1]; 
				if (have[i - 1] >= y) {
					tabelle[i].push_back(tabelle[i - 1][y]);
					have[i] = j; 
				} else {
					needs[i - 1] = y; 
					if (i > 2) {
						std::cout << "benoetige f(" << (i - 1) << ", " << y << ")" << std::endl;
					}
					i -= 2; 
					break; 
				}
			}
		}
	}
	return tabelle[n][m]; 
}

int adp02_3_main() {
	/** Die in die Funktion einzusetzenden Parameter: f(n, m) */
	int n = -1, m = -1; 
	std::cout << "rekursive Loesung: "; 
	if (adp02_3_leseParameter(n, m)) {
		long long result = adp02_3_calc_f_rec(n, m); 
		std::cout << "f(" << n << ", " << m << ") = " << result << std::endl;
		return 0; 
	} else {
		return -1; 
	}
}

int adp02_3it_main() {
	/** Die in die Funktion einzusetzenden Parameter: f(n, m) */
	int n = -1, m = -1;
	std::cout << "rekursive Loesung: ";
	if (adp02_3_leseParameter(n, m)) {
		long long result = adp02_3_calc_f_it(n, m);
		std::cout << "f(" << n << ", " << m << ") = " << result << std::endl;
		return 0;
	} else {
		return -1;
	}
}