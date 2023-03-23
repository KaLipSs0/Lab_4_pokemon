#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Nested struct for Pokemon characteristics
struct Characteristics {
	int life;
	int attack;
	int defense;
};

// Main Pokemon struct
struct Pokemon {
	int id;
	string name;
	string type;
	Characteristics characteristics;
	vector<string> weaknesses;
};

// Read information about Pokemon from a file into a vector
vector<Pokemon> readPokemonData(string filename) {
	vector<Pokemon> pokemonList;

	ifstream inputFile;
	inputFile.open(filename);

	if (!inputFile) {
		cout << "Error opening file " << filename << endl;
	}
	else {
		string line;
		while (getline(inputFile, line)) {
			Pokemon newPokemon;
			newPokemon.id = stoi(line);
			getline(inputFile, newPokemon.name);
			getline(inputFile, newPokemon.type);
			inputFile >> newPokemon.characteristics.life >> newPokemon.characteristics.attack >> newPokemon.characteristics.defense;
			inputFile.ignore();
			string weaknessesLine;
			getline(inputFile, weaknessesLine);
			size_t pos = 0;
			while ((pos = weaknessesLine.find(' ')) != string::npos) {
				string weakness = weaknessesLine.substr(0, pos);
				newPokemon.weaknesses.push_back(weakness);
				weaknessesLine.erase(0, pos + 1);
			}
			newPokemon.weaknesses.push_back(weaknessesLine); // Add last weakness
			pokemonList.push_back(newPokemon);
		}
		inputFile.close();
	}

	return pokemonList;
}

// Print information about a particular Pokemon
void printPokemonInfo(Pokemon p) {
	cout << "ID: " << p.id << endl;
	cout << "Name: " << p.name << endl;
	cout << "Type: " << p.type << endl;
	cout << "Characteristics: " << endl;
	cout << " Life: " << p.characteristics.life << endl;
	cout << " Attack: " << p.characteristics.attack << endl;
	cout << " Defense: " << p.characteristics.defense << endl;
	cout << "Weaknesses: ";
	for (string weakness : p.weaknesses) {
		cout << weakness << " ";
	}
	cout << endl;
}

// Write Pokemon with attack less than defense to file
void writePokemonToFile(vector<Pokemon> pokemonList, string filename) {
	ofstream outputFile;
	outputFile.open(filename);

	if (!outputFile) {
		cout << "Error opening file " << filename << endl;
	}
	else {
		for (Pokemon p : pokemonList) {
			if (p.characteristics.attack < p.characteristics.defense) {
				outputFile << "ID: " << p.id << endl;
				outputFile << "Name: " << p.name << endl;
				outputFile << "Type: " << p.type << endl;
				outputFile << "Characteristics: " << endl;
				outputFile << " Life: " << p.characteristics.life << endl;
				outputFile << " Attack: " << p.characteristics.attack << endl;
				outputFile << " Defense: " << p.characteristics.defense << endl;
				outputFile << "Weaknesses: ";
				for (string weakness : p.weaknesses) {
					outputFile << weakness << " ";
				}
				outputFile << endl;
			}
		}
		outputFile.close();
	}
}

int main() {
	// Read Pokemon data from file
	vector<Pokemon> pokemonList = readPokemonData("pokemon.txt");

	// Print information about each Pokemon
	for (Pokemon p : pokemonList) {
		printPokemonInfo(p);
	}

	// Write Pokemon with attack less than defense to file
	writePokemonToFile(pokemonList, "weak_pokemon.txt");

	return 0;
}