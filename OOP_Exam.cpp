/*
 DATE DE INTRARE: (1 inseamna statie Urbana 2 inseamna extra urbana)
 4
 1 BvReginaElisabeta 1 3 2 66 601 DA
 2 StrApeductului 1 1 3004
 1 Splai 1 6 1 601 DA
 2 StrChiajna 1 1 3004
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
class statie {
protected:
	std::string strada;
	int numar;
	std::vector<int> mijloaceTr;
	std::string codStatie;
public:
	virtual void read(std::istream &input) = 0;
	virtual void print(std::ostream &output) = 0;
	std::string getAdresa() { return strada; }
	std::vector<int> getMijloaceTr() { return mijloaceTr; }
};
class statieUrbana : public statie {
	std::string punctDeActizitionareLegitimatie;
	const int codUrban;
	int sector;
	std::string idUrban;
public:
	statieUrbana() : codUrban(getCod()) { idUrban = "SU-"; };
	statieUrbana(std::string strada, int numar, int sector, std::vector<int> mijloaceTr, std::string codStatie, std::string punctDeActizitionareLegitimatie);
	statieUrbana(statieUrbana &S);
	int getCod() {
		static int lastCod = 0;
		lastCod++;
		return lastCod;
	}
	void operator=(statieUrbana &S);
	void read(std::istream &input) {
		input >> strada;
		input >> numar;
		input >> sector;
		int n;
		input >> n;
		for (int i = 1; i <= n; i++) {
			int mijloc;
			input >> mijloc;
			mijloaceTr.push_back(mijloc);
		}
		input >> punctDeActizitionareLegitimatie;

	}
	void print(std::ostream &output) {
		output << strada << " ";
		output << numar << " ";
		output << sector << " ";
		for (auto mij : mijloaceTr)
			output << mij << " ";
		output << punctDeActizitionareLegitimatie << " ";
		output << idUrban << codUrban << " \n";
	}
};

statieUrbana::statieUrbana(std::string strada, int numar, int sector, std::vector<int> mijloaceTr, std::string codStatie, std::string punctDeActizitionareLegitimatie) : codUrban(getCod()) {
	this->strada = strada;
	this->numar = numar;
	this->sector = sector;
	this->mijloaceTr = mijloaceTr;
	this->codStatie = codStatie;
	this->punctDeActizitionareLegitimatie = punctDeActizitionareLegitimatie;
	idUrban = "SU-";
}

statieUrbana::statieUrbana(statieUrbana &S) : codUrban(S.codUrban) {
	this->strada = S.strada;
	this->numar = S.numar;
	this->sector = S.sector;
	this->mijloaceTr = S.mijloaceTr;
	this->codStatie = S.codStatie;
	this->punctDeActizitionareLegitimatie = S.punctDeActizitionareLegitimatie;
}

void statieUrbana::operator=(statieUrbana &S) {
	this->strada = S.strada;
	this->numar = S.numar;
	this->sector = S.sector;
	this->mijloaceTr = S.mijloaceTr;
	this->codStatie = S.codStatie;
	this->punctDeActizitionareLegitimatie = S.punctDeActizitionareLegitimatie;
}


class statieExtraUrbana : public statie {
	const int codExtraUrban;
	std::string idExtraUrban;
public:
	statieExtraUrbana() : codExtraUrban(getCod()) { idExtraUrban = "SE-"; };
	statieExtraUrbana(std::string strada, int numar, std::vector<int> mijloaceTr, std::string codStatie, std::string punctDeActizitionareLegitimatie);
	statieExtraUrbana(statieExtraUrbana &S);
	int getCod() {
		static int lastCod = 0;
		lastCod++;
		return lastCod;
	}
	void operator=(statieExtraUrbana &S);
	void read(std::istream &input) {
		input >> strada;
		input >> numar;
		int n;
		input >> n;
		for (int i = 1; i <= n; i++) {
			int mijloc;
			input >> mijloc;
			mijloaceTr.push_back(mijloc);
		}

	}
	void print(std::ostream &output) {
		output << strada << " ";
		output << numar << " ";
		for (auto mij : mijloaceTr)
			output << mij << " ";
		output << idExtraUrban << codExtraUrban << " \n";
	}
};

statieExtraUrbana::statieExtraUrbana(std::string strada, int numar, std::vector<int> mijloaceTr, std::string codStatie, std::string punctDeActizitionareLegitimatie) : codExtraUrban(getCod()) {
	this->strada = strada;
	this->numar = numar;
	this->mijloaceTr = mijloaceTr;
	this->codStatie = codStatie;
	idExtraUrban = "SE-";
}

statieExtraUrbana::statieExtraUrbana(statieExtraUrbana &S) : codExtraUrban(S.codExtraUrban) {
	this->strada = S.strada;
	this->numar = S.numar;
	this->mijloaceTr = S.mijloaceTr;
	this->codStatie = S.codStatie;
}

void statieExtraUrbana::operator=(statieExtraUrbana &S) {
	this->strada = S.strada;
	this->numar = S.numar;
	this->mijloaceTr = S.mijloaceTr;
	this->codStatie = S.codStatie;
}

class punctDeinformareOras {
	std::vector<statie*> statii;
public:
	punctDeinformareOras() {};
	~punctDeinformareOras();
	void read(std::istream &input);
	void print(std::ostream &output);
	std::vector<statie*> getStatii() { return statii; }
};

void punctDeinformareOras::read(std::istream &input) {
	int nrStatii;
	input >> nrStatii;
	for (int i = 1; i <= nrStatii; i++) {
		int optiune;
		input >> optiune;
		try {
			if (optiune != 1 && optiune != 2) throw optiune;
			if (optiune == 1) {
				statieUrbana *S = new statieUrbana;
				S->read(input);
				statii.push_back(S);
			}
			if (optiune == 2) {
				statieExtraUrbana *S = new statieExtraUrbana;
				S->read(input);
				statii.push_back(S);
			}
		}
		catch (int optiune) {
			std::cout << "optiunea trebuie sa fie 1(urbana) sau 2(extraurbana) optiune dvs a fost " << optiune;
		}
	}
}

void punctDeinformareOras::print(std::ostream &output) {
	for (auto pstatie : statii) {
		pstatie->print(output);
	}
}

punctDeinformareOras::~punctDeinformareOras() {
	for (auto pstatie : statii) {
		if (statieUrbana *pu = dynamic_cast<statieUrbana*>(pstatie)) {
			delete pu;
		}
		else {
			statieExtraUrbana *pe = static_cast<statieExtraUrbana*>(pstatie);
			delete pe;
		}

	}
}

void cautaStatieDupaAdresa(std::string Adresa, punctDeinformareOras &O) {
	auto vecStatii = O.getStatii();
	for (auto pStatie : vecStatii) {
		if (pStatie->getAdresa() == Adresa) pStatie->print(std::cout);
	}
}
void gasesteStatiiPrinCareTreceAutobuzul(int NrMijlocTransport, punctDeinformareOras &O) {
	auto vecStatii = O.getStatii();
	for (auto pStatie : vecStatii) {
		auto vecMijlocTransport = pStatie->getMijloaceTr();
		for (auto mijlocTransport : vecMijlocTransport) {
			if (mijlocTransport == NrMijlocTransport) pStatie->print(std::cout);
		}
	}
}
std::istream &operator>> (std::istream &input, statieUrbana &S) {
	S.read(input);
	return input;
}
std::istream &operator>> (std::istream &input, statieExtraUrbana &S) {
	S.read(input);
	return input;
}
std::istream &operator>> (std::istream &input, punctDeinformareOras &S) {
	S.read(input);
	return input;
}
std::ostream &operator<< (std::ostream &output, statieUrbana &S) {
	S.print(output);
	return output;
}
std::ostream &operator<<(std::ostream &output, statieExtraUrbana &S) {
	S.print(output);
	return output;
}
std::ostream &operator<<(std::ostream &output, punctDeinformareOras &S) {
	S.print(output);
	return output;
}
int main() {
	punctDeinformareOras P;
	P.read(std::cin);
	P.print(std::cout);
	std::cout << "\n";
	cautaStatieDupaAdresa("Splai", P);
	std::cout << "\n";
	gasesteStatiiPrinCareTreceAutobuzul(601, P);
	return 0;
}
