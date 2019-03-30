#include <vector>
#include "adpRegistermaschine.h"
#include <sstream>
#include <fstream>
#include <map>
#include <iomanip>
#include <stdio.h>

int adp02_registermaschine_main() {
	const bool debug = false; 
	try {
		Registermaschine r;
		char filename[200]; 
		std::cout << "Enter filename with absolute path (for example C:\\x.rm): "; 
		std::cin >> filename; 
		
		r.readFromFile(filename);
		if (debug) r.printConsole();
		r.execute(debug);

		return 0;
	} catch (std::exception err) {
		std::cout << "ERROR: " << err.what() << std::endl; 
	} catch (char * errChar) {
		std::cout << "ERROR: " << errChar << std::endl; 
		return -1; 
	} 
}

void Registermaschine::readFromFile(const char * filename) {
	std::shared_ptr<std::vector<RegisterCommand> > result = std::shared_ptr<std::vector<RegisterCommand> >(new std::vector<RegisterCommand>);
	std::map<std::string, int> sprungmarken; 
	std::map<int, std::string> sprung; 

	char lineFile[60], cmdcmd[4]; 
	int index = 0; 
	char cc; 

	result->reserve(200); 
	std::ifstream programmfile;
	try {
		programmfile.open(filename); 
		if (programmfile.fail()) {
			throw std::runtime_error("IO-ERROR: cannot find file " + std::string(filename)); 
		}
		while (1) {
			if (programmfile.eof()) break;
			programmfile.getline(lineFile, 59);
			//Kommentare ignorieren 
			cc = *lineFile;
			if (cc == '/' || cc == '\0' || cc == ' ') {
				continue;
			}

			lineFile[59] = '\0';

			//in Grossbuchstaben
			for (int i = 0; i < 60; i++) {
				cc = lineFile[i];
				if (cc >= 'a' && cc <= 'z') {
					cc -= ('a' - 'A');
				} else if (cc == '\0' || cc == '/') {
					break;
				}
				lineFile[i] = cc;
			}

			cc = *lineFile;
			if (cc == ':') {
				std::istringstream linestream(lineFile + 1); 
				std::string xxx; 
				linestream >> xxx; 
				sprungmarken.insert(std::pair<std::string, int>(xxx, index));

			} else if (lineFile[3] = ' ') {
				RegisterCommand cmd;
				cmd.setCmd(lineFile); 
				std::istringstream linestream(lineFile + 4);
				if (cc == 'J') {
					std::string xxx; 
					linestream >> xxx; 
					sprung[index] = xxx; 
				} else {
					linestream >> cmd.param; 
				}
				result->push_back(cmd); 
				index++; 
			}
		}

		for (std::map<int, std::string>::iterator it = sprung.begin(); it != sprung.end(); it++) {
			if (sprungmarken.count(it->second)) {
				int ziel = sprungmarken[(it->second)];
				(*result)[it->first].param = ziel; 
			} else {
				//versuche Sprungmarke als int direkt als Adresse zu interpretieren 
				int ziel = -1; 
				std::istringstream ss(it->second); 
				ss >> ziel; 
				if (ziel >= 0) {
					(*result)[it->first].param = ziel; 
				} else {
					throw std::runtime_error("fehlende Sprungmarke: " + it->second); 
				}
			}
		}

		this->prog = result; 

	} catch (std::exception err) {
		std::cout << "IO-ERROR " << err.what() << std::endl; 
		programmfile.close(); 
	}

}

void Registermaschine::printConsole() {
	int size = this->prog->size(); 
	std::ostringstream out; 
	for (int i = 0; i < size; i++) {
		RegisterCommand * cmd = &((*prog)[i]); 
		out << std::setw(3) << i << ": " << *cmd << std::endl; 
	}
	std::cout << out.str(); 
}

void Registermaschine::execute(bool debug, int start) {
	this->pc = start; 
	while (this->pc >= 0 && this->pc < this->prog->size()) {
		RegisterCommand * cmd = &((*(this->prog))[this->pc]); 
		if (cmd == nullptr || !(cmd->isExecutable())) {
			throw std::runtime_error("ERROR instruction null"); 
		} 
		if (debug) {
			std::cout << "PC:" << this->pc << ": " << *cmd << std::endl; 
		}
		cmd->executeOn(this);



	}
}

void Registermaschine::add(int index) {
	this->ram[0] += this->ram[index]; 
	this->pc++;
}
void Registermaschine::sub(int index) {
	this->ram[0] -= this->ram[index]; 
	this->pc++;
}
void Registermaschine::mul(int index) {
	this->ram[0] *= this->ram[index]; 
	this->pc++;
}
void Registermaschine::div(int index) {
	int divisor = this->ram[index]; 
	if (divisor != 0) {
		this->ram[0] /= divisor; 
	} else {
		std::cout << "ERROR: division by 0" << std::endl; 
		this->hlt(1); 
	}
	this->pc++;
}
void Registermaschine::lda(int index) {
	this->ram[0] = this->ram[index]; 
	this->pc++;
}
void Registermaschine::ldk(int index) {
	this->ram[0] = index; 
	this->pc++;
}
void Registermaschine::sta(int index) {
	this->ram[index] = this->ram[0]; 
	this->pc++;
}
void Registermaschine::inp(int index) {
	std::cout << "Eingabe: "; 
	std::cin >> this->ram[index]; 
	this->pc++;
}
void Registermaschine::out(int index) {
	std::cout << "Ausgabe: " << this->ram[index] << std::endl; 
	this->pc++; 
}
void Registermaschine::hlt(int index) {
	this->pc = -1; 
}
void Registermaschine::jmp(int index) {
	this->pc = index; 
}
void Registermaschine::jez(int index) {
	if (this->ram[0] == 0) {
		this->pc = index; 
	} else {
		this->pc++; 
	}
}
void Registermaschine::jne(int index) {
	if (this->ram[0] != 0) {
		this->pc = index; 
	} else {
		this->pc++;
	}
}
void Registermaschine::jlz(int index) {
	if (this->ram[0] < 0) {
		this->pc = index;
	} else {
		this->pc++;
	}
}
void Registermaschine::jle(int index) {
	if (this->ram[0] <= 0) {
		this->pc = index;
	} else {
		this->pc++;
	}

}
void Registermaschine::jgz(int index) {
	if (this->ram[0] > 0) {
		this->pc = index;
	} else {
		this->pc++;
	}
}
void Registermaschine::jge(int index) {
	if (this->ram[0] >= 0) {
		this->pc = index;
	} else {
		this->pc++;
	}
}

