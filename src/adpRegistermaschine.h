#ifndef __ADP_02_REGISTERMASCHINE_H__
#define __ADP_02_REGISTERMASCHINE_H__

#include <memory>
#include <vector>
#include <exception>
#include <iostream>

class Registermaschine {
private: 
	const char COMMANDS[80] = "ADD SUB MUL DIV LDA LDK STA INP OUT HLT JMP JEZ JNE JLZ JLE JGZ JGE ";

	struct RegisterCommand {
		/** command identifier */
		char cmd; 

		/** command parameter */
		int param; 

		/**function pointer to proper function */
		void(Registermaschine::*exec)(int); 
		
		/** default constructor */
		RegisterCommand() : cmd('\0'), exec(nullptr), param(-1) {
		}

		/** default copy constructor */
		RegisterCommand(const RegisterCommand & that) : cmd(that.cmd), param(that.param), exec(that.exec) {
		}

		/** destructor */
		~RegisterCommand() {
			this->exec = nullptr; 
			this->cmd = 0; 
		}

		/** test if command is executable */
		bool isExecutable() {
			return (this->cmd >= 1 && this->exec != nullptr); 
		}

		void executeOn(Registermaschine * r) {
			void (Registermaschine::*exe)(int) = this->exec; 
			(r->*exe)(this->param); 
			
		}

		/** setter for param */
		void setParam(int p) {
			this->param = p; 
		}

		friend std::ostream & operator << (std::ostream & stream, const RegisterCommand & that) {
			switch ((int)(that.cmd)) {
			case 0: stream << "---"; break;
			case 1: stream << "ADD " << that.param; break;
			case 2: stream << "SUB " << that.param; break;
			case 3: stream << "MUL " << that.param; break;
			case 4: stream << "DIV " << that.param; break;
			case 5: stream << "LDA " << that.param; break;
			case 6: stream << "LDK " << that.param; break;
			case 7: stream << "STA " << that.param; break;
			case 8: stream << "INP " << that.param; break;
			case 9: stream << "OUT " << that.param; break;
			case 10: stream << "HLT " << that.param; break;
			case 11: stream << "JMP " << that.param; break;
			case 12: stream << "JEZ " << that.param; break;
			case 13: stream << "JNE " << that.param; break;
			case 14: stream << "JLZ " << that.param; break;
			case 15: stream << "JLE " << that.param; break;
			case 16: stream << "JGZ " << that.param; break;
			case 17: stream << "JGE " << that.param; break;
			default: stream << "-ER " << that.param; break;
			}
			return stream; 
		}

		/** setter for commands cmd */
		void setCmd(char * c) {
			this->cmd = '\0'; 
			switch (*c) {
			case 'A':  //ADD
				this->cmd = 1; 
				this->exec = &(Registermaschine::add); 
				break; 
			case 'S':  //SUB //STA
				if (c[1] == 'U') {
					this->cmd = 2; 
					this->exec = &(Registermaschine::sub);
				} else {
					this->cmd = 7; 
					this->exec = &(Registermaschine::sta);
				}
				break; 
			case 'M':  //MUL
				this->cmd = 3; 
				this->exec = &(Registermaschine::mul);
				break;  //DIV
			case 'D': 
				this->cmd = 4; 
				this->exec = &(Registermaschine::div); 
				break; 
			case 'L': 
				if (c[2] == 'A') {
					this->cmd = 5; 
					this->exec = &(Registermaschine::lda); 
				} else {
					this->cmd = 6; 
					this->exec = &(Registermaschine::ldk); 
				}
				break; 
			case 'I':  //INP
				this->cmd = 8; 
				this->exec = &(Registermaschine::inp); 
				break; 
			case 'O':  //OUT
				this->cmd = 9; 
				this->exec = &(Registermaschine::out);
				break;  
			case 'H':  //HLT
				this->cmd = 10; 
				this->exec = &(Registermaschine::hlt);
				break; 
			case 'J':  //JMPs 
				if (c[1] == 'E') { 
					this->cmd = 12; 
					this->exec = &(Registermaschine::jez);
				} else if (c[1] == 'N') { 
					this->cmd = 13; 
					this->exec = &(Registermaschine::jne);
				} else if (c[1] == 'L' && c[2] == 'Z') { 
					this->cmd = 14; 
					this->exec = &(Registermaschine::jlz);
				} else if (c[1] == 'L' && c[2] == 'E') { 
					this->cmd = 15; 
					this->exec = &(Registermaschine::jle);
				} else if (c[1] == 'G' && c[2] == 'Z') { 
					this->cmd = 16; 
					this->exec = &(Registermaschine::jgz);
				} else if (c[1] == 'G' && c[2] == 'E') {
					this->cmd = 17;
					this->exec = &(Registermaschine::jge);
				} else {
					this->cmd = 11;
					this->exec = &(Registermaschine::jmp);
				}
				break; 
			} //end switch
		} //end function setCmd
	};
private: 
	
	
public: 
	void readFromFile(const char * filename); 

	std::shared_ptr<std::vector<RegisterCommand> > prog; 
	int ram[100]; 
	int pc = 0; 
	void printConsole(); 
	void execute(bool debug = false, int start = 0); 


	void add(int index);
	void sub(int index);
	void mul(int index);
	void div(int index);
	void lda(int index);
	void ldk(int index);
	void sta(int index);
	void inp(int index);
	void out(int index);
	void hlt(int index);
	void jmp(int index);
	void jez(int index);
	void jne(int index);
	void jlz(int index);
	void jle(int index);
	void jgz(int index);
	void jge(int index);
};



#endif //__ADP_02_REGISTERMASCHINE_H__