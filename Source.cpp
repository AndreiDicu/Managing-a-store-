#include<iostream>
#include<fstream>
#include<vector>
#include<conio.h>

using namespace std;

class ICommon {
public:
	virtual void show() = 0;
	virtual void total() = 0;
	virtual void afiseaza()
	{
		cout << "\nNimic de afisat!";
	}
	virtual bool verificaParola()
	{
		cout << "\nNimic de modificat!";
		return false;
	}
};

class Facturi : public ICommon {

private:

	const float CodFactura;
	int NrFactura;
	float* Total;
	char* NumeProdus;

public:

	const float getCodFactura() {
		return this->CodFactura;
	}

	int getNrFactura() {
		return this->NrFactura;
	}

	float* getTotal() {
		if (Total)
			return this->Total;
	}

	char* getNumeProdus() {
		if (NumeProdus)
			return this->NumeProdus;
	}

	void setNrFactura(int NrFactura) {
		this->NrFactura = NrFactura;
	}

	void setTotal(float* Total, int NrFactura) {
		if (Total) {
			if (this->Total)
				delete[] this->Total;
			this->NrFactura = NrFactura;
			this->Total = new float[NrFactura];
			for (int i = 0; i < NrFactura; i++)
				this->Total[i] = Total[i];
		}
	}

	void setNumeProdus(char* NumeProdus) {
		if (NumeProdus) {
			if (this->NumeProdus)
				delete[] this->NumeProdus;
			this->NumeProdus = new char[strlen(NumeProdus) + 1];
			strcpy(this->NumeProdus, NumeProdus);
		}
	}

	Facturi() :CodFactura(1) {
		this->NrFactura = 0;
		this->Total = new float[NrFactura];
		for (int i = 0; i < NrFactura; i++)
			this->Total[i] = Total[i];
		this->NumeProdus = new char[strlen("NumeProdus") + 1];
		strcpy(this->NumeProdus, "NumeProdus");
	}

	Facturi(char* NumeProdus, float* Total, int NrFactura, const float newCodFactura) :CodFactura(newCodFactura)
	{
		this->NumeProdus = new char[strlen(NumeProdus) + 1];
		strcpy(this->NumeProdus, NumeProdus);
		this->NrFactura = NrFactura;
		this->Total = new float[NrFactura];
		for (int i = 0; i < NrFactura; i++)
			this->Total[i] = Total[i];
	}

	Facturi(const Facturi & fact) :CodFactura(fact.CodFactura) {
		this->NumeProdus = new char[strlen(fact.NumeProdus) + 1];
		strcpy(this->NumeProdus, fact.NumeProdus);
		this->NrFactura = fact.NrFactura;
		this->Total = new float[fact.NrFactura];
		for (int i = 0; i < fact.NrFactura; i++)
			this->Total[i] = fact.Total[i];
	}

	Facturi operator=(const Facturi & fact) {
		if (this->NumeProdus)
			delete this->NumeProdus;
		if (this->Total)
			delete this->Total;
		this->NumeProdus = new char[strlen(fact.NumeProdus) + 1];
		strcpy(this->NumeProdus, fact.NumeProdus);
		this->NrFactura = fact.NrFactura;
		this->Total = new float[fact.NrFactura];
		for (int i = 0; i < fact.NrFactura; i++)
			this->Total[i] = fact.Total[i];
		return *this;
	}

	Facturi operator -=(int minus)
	{
		if (this->Total[2] >= minus)
			this->Total[2] -= minus;
		else cout << "IMPOSIBIL";
		return *this;
	}

	Facturi operator+=(Facturi fact)
	{
		for (int i = 0; i<NrFactura; i++)
			this->Total[i] += fact.Total[i];
		return *this;
	}

	void show() {
		cout << endl << "Cod factura: " << this->CodFactura << endl;
		cout << "Nr factura: " << this->NrFactura << endl;
		cout << "Nume produs: " << this->NumeProdus << endl;
		for (int i = 0; i < this->NrFactura; i++)
			cout << "Total " << i + 1 << " : " << this->Total[i] << endl;
	}

	void total() {
		float sum = 0.0F;
		for (int i = 0; i < this->NrFactura; i++)
			sum += this->Total[i];
		cout << "Totalul este: " << sum;
	}

	friend ostream& operator<<(ostream &cout, Facturi &fact);
	friend istream& operator >> (istream &cin, Facturi &fact);

	friend ofstream& operator<<(ofstream& cout, Facturi &fact) {
		cout << endl << "Cod factura: " << fact.CodFactura << endl;
		cout << "Nr factura: " << fact.NrFactura << endl;
		cout << "Nume produs: " << fact.NumeProdus << endl;
		for (int i = 0; i < fact.NrFactura; i++)
			cout << "Total " << i + 1 << " : " << fact.Total[i] << endl;
		return cout;
	}

	~Facturi() {
		if (this->NumeProdus)
			delete this->NumeProdus;
		if (this->Total)
			delete this->Total;
	}
};

ostream& operator<<(ostream& cout, Facturi &fact) {
	cout << endl << "Cod factura: " << fact.CodFactura << endl;
	cout << "Nr factura: " << fact.NrFactura << endl;
	cout << "Nume produs: " << fact.NumeProdus << endl;
	for (int i = 0; i < fact.NrFactura; i++)
		cout << "Total " << i + 1 << " : " << fact.Total[i] << endl;
	return cout;
}

istream& operator >> (istream& cin, Facturi &fact) {
	char buffer[50];
	cout << endl << "Nr factura:  ";
	cin >> fact.NrFactura;
	cout << "Nume produs:  ";
	cin >> buffer;
	fact.NumeProdus = new char[strlen(buffer) + 1];
	strcpy(fact.NumeProdus, buffer);
	fact.Total = new float[fact.NrFactura];
	for (int i = 0; i < fact.NrFactura; i++)
	{
		cout << "Total   " << i + 1 << " : ";
		cin >> fact.Total[i];
	}
	return cin;
}

class Utilizator : public ICommon {

private:

	char* NumeCasier;
	int Lungime;
	char* Parola = nullptr;
	const float CodCasier;
	static int Vizite;

public:

	char* getNumeCasier() {
		if (NumeCasier)
			return this->NumeCasier;
	}

	int getLungime() {
		return this->Lungime;
	}

	char* getParola() {
		if (Parola)
			return this->Parola;
	}

	const float getCodCasier() {
		return this->CodCasier;
	}

	static int getVizite() {
		return Vizite;
	}

	void setNumeCasier(char* NumeCasier) {
		if (NumeCasier) {
			if (this->NumeCasier)
				this->NumeCasier = new char[strlen("Utilizator") + 1];
			strcpy(this->NumeCasier, "NumeCasier");
		}
	}

	void setLungime(int Lungime) {
		this->Lungime = Lungime;
	}

	void setParola(char* Parola, int Lungime) {
		delete[] this->Parola;
		this->Parola = new char[strlen(Parola) + 1];
		strcpy(this->Parola, Parola);
		this->Lungime = Lungime;
	}

	Utilizator & operator+(int x)
	{
		Lungime += x;
		return *this;
	}

	Utilizator & operator-(int x)
	{
		Lungime -= x;
		return *this;
	}

	Utilizator & operator*(int x)
	{
		Lungime *= x;
		return *this;
	}

	Utilizator & operator/(int x)
	{
		Lungime -= x;
		return *this;
	}

	Utilizator & operator++()
	{
		Lungime++;
		return *this;
	}

	Utilizator & operator--()
	{
		Lungime--;
		return *this;
	}

	Utilizator & operator()(int x)
	{
		Lungime += x;
		return *this;
	}

	friend bool operator!(const Utilizator &u)
	{
		if (!u.Parola)
			return true;
		return false;
	}

	Utilizator() :CodCasier(1) {
		this->NumeCasier = new char[strlen("NumeCasier") + 1];
		strcpy(this->NumeCasier, "NumeCasier");
		this->Lungime = 0;
		Vizite++;
	}

	Utilizator(char* NumeCasier, int Lungime, char* Parola, const float newCodCasier) :CodCasier(newCodCasier)
	{
		this->NumeCasier = new char[strlen(NumeCasier) + 1];
		strcpy(this->NumeCasier, NumeCasier);
		delete[] this->Parola;
		this->Parola = new char[strlen(Parola) + 1];
		strcpy(this->Parola, Parola);
		this->Lungime = Lungime;
		Vizite++;

	}

	Utilizator(const Utilizator & cas) :CodCasier(cas.CodCasier) {
		this->NumeCasier = new char[strlen(cas.NumeCasier) + 1];
		strcpy(this->NumeCasier, cas.NumeCasier);
		this->Lungime = cas.Lungime;
		delete[] this->Parola;
		this->Parola = new char[strlen(cas.Parola) + 1];
		strcpy(this->Parola, cas.Parola);
		cas.Vizite++;
	}

	Utilizator& operator=(const Utilizator &cas) {
		this->NumeCasier = new char[strlen(cas.NumeCasier) + 1];
		strcpy(this->NumeCasier, cas.NumeCasier);
		this->Lungime = cas.Lungime;
		delete[] this->Parola;
		this->Parola = new char[strlen(cas.Parola) + 1];
		strcpy(this->Parola, cas.Parola);
		cas.Vizite++;
		return *this;
	}

	Utilizator& operator+=(int plus)
	{
		if ((this->Parola[1] + plus) <= 9)
		{
			this->Parola[1] = Parola[1] + plus;
			cout << endl << "parola modificata" << endl;
		}
		else cout << endl << "imposibil!" << endl;
		return *this;

	}

	Utilizator& operator-=(int minus)
	{
		if (this->Parola[0] >= minus)
		{
			this->Parola[0] = Parola[0] - minus;
			cout << endl << "parola modificata" << endl;
		}
		else cout << endl << "imposibil!" << endl;
		return *this;

	}

	void show() {
		cout << "Utilizator: " << this->NumeCasier << endl;
		cout << "Parola: ";
		for (int i = 0; i < this->Lungime; i++)
			cout << this->Parola[i];
		cout << endl << "Cod casier: " << this->CodCasier << endl;
		cout << "Vizite: " << this->Vizite << endl;
	}

	void total() {
		float sum = 0.0F;
		for (int i = 0; i < this->Lungime; i++)
			sum += this->Parola[i];
		cout << "Totalul este: " << sum;

	}

	bool verificaParola()
	{
		if (Parola)
		{
			if (strlen(Parola) > 0)
				return true;
		}
		return false;
	}

	friend ostream& operator<<(ostream & cout, Utilizator & cas);
	friend istream& operator >> (istream & cin, Utilizator &cas);

	friend ofstream & operator<<(ofstream &cout, Utilizator & cas) {
		cout << "Casier : " << cas.NumeCasier << endl;
		cout << "Parola : ";
		for (int i = 0; i < cas.Lungime; i++)
			cout << cas.Parola[i];
		cout << endl << "Cod casier: " << cas.CodCasier << endl;
		cout << "Vizite: " << cas.Vizite << endl;
		return cout;
	}

	char operator[](int x)
	{
		if (Parola)
		{
			if (x >= 0 && x << strlen(Parola))
				return Parola[x];
		}
	}

	friend ifstream & operator >> (ifstream &fin, Utilizator &cas)
	{
		char buffer[50];
		fin >> cas.Lungime;
		fin >> buffer;
		cas.NumeCasier = new char[strlen(buffer) + 1];
		strcpy(cas.NumeCasier, buffer);
		char temp[50];
		fin >> temp;
		delete[] cas.Parola;
		cas.Parola = new char[strlen(temp) + 1];
		strcpy(cas.Parola, temp);
		return fin;
	}

	~Utilizator() {

		if (this->NumeCasier)
			delete this->NumeCasier;
		if (this->Parola)
			delete this->Parola;
	}
};

ostream & operator<<(ostream &cout, Utilizator & cas) {
	cout << "Casier : " << cas.NumeCasier << endl;
	cout << "Parola : ";
	for (int i = 0; i < cas.Lungime; i++)
		cout << cas.Parola[i];
	cout << endl << "Cod casier: " << cas.CodCasier << endl;
	cout << "Vizite: " << cas.Vizite << endl;
	return cout;
}

istream & operator >> (istream & cin, Utilizator & cas) {
	char buffer[50];
	cout << "Lungimea parolei : ";
	cin >> cas.Lungime;
	cout << "Nume : ";
	cin >> buffer;
	cas.NumeCasier = new char[strlen(buffer) + 1];
	strcpy(cas.NumeCasier, buffer);
	cout << "Parola : " << endl;
	string parola = "";
	char x = getch();
	while (x != 13)
	{
		x = getch();
		cout << "*";
		parola += x;
	}
	char* temp = new char[strlen(parola.data()) + 1];
	strcpy(temp, parola.data());
	delete[] cas.Parola;
	cas.Parola = new char[strlen(temp) + 1];
	strcpy(cas.Parola, temp);
	return cin;
}

class BorderouAchizitie : public ICommon {

private:

	const float CodAprovizionare;
	static int NrAprovizionare;
	int NrProduse;
	int* SumaAprovizionare;
	char* Furnizor;

public:

	float getCodAprovizionare() {
		return this->CodAprovizionare;
	}

	int getNrAprovizionare() {
		return this->NrAprovizionare;
	}

	int getNrProduse() {
		return this->NrProduse;
	}

	int* getSumaAprovizionare() {
		if (SumaAprovizionare)
			return this->SumaAprovizionare;
	}

	char* getFurnizor() {
		if (Furnizor)
			return this->Furnizor;
	}

	void setNrAprovizionare(int NrAprovizionare) {
		this->NrAprovizionare = NrAprovizionare;
	}

	void setNrProduse(int NrProduse) {
		this->NrProduse = NrProduse;
	}

	void setSumaAprovizionare(int* SumaAprovizionare, int NrProduse) {
		if (SumaAprovizionare) {
			if (this->SumaAprovizionare)
				this->NrProduse = NrProduse;
			this->SumaAprovizionare = new int[NrProduse];
			for (int i = 0; i < NrProduse; i++)
				this->SumaAprovizionare[i] = SumaAprovizionare[i];
		}
	}

	void setFurnizor(char* Furnizor) {
		if (Furnizor) {
			if (this->Furnizor)
				this->Furnizor = new char[strlen(Furnizor) + 1];
			strcpy(this->Furnizor, Furnizor);
		}
	}

	BorderouAchizitie() :CodAprovizionare(1) {
		this->NrAprovizionare = 0;
		this->Furnizor = new char[strlen("Furnizor") + 1];
		strcpy(this->Furnizor, "Furnizor");
		this->NrProduse = 0;
		this->SumaAprovizionare = new int[NrProduse];
		for (int i = 0; i < NrProduse; i++)
			this->SumaAprovizionare[i] = 10 * (i + 2);
		NrAprovizionare++;
	}

	BorderouAchizitie(char* Furnizor, int* SumaAprovizionare, int NrProduse, const float newCodAprovizionare) :CodAprovizionare(newCodAprovizionare) {
		this->Furnizor = new char[strlen(Furnizor) + 1];
		strcpy(this->Furnizor, Furnizor);
		this->NrProduse = NrProduse;
		this->SumaAprovizionare = new int[NrProduse];
		for (int i = 0; i < NrProduse; i++)
			this->SumaAprovizionare[i] = SumaAprovizionare[i];
		NrAprovizionare++;
	}

	BorderouAchizitie(const BorderouAchizitie & bord) :CodAprovizionare(bord.CodAprovizionare) {
		this->NrProduse = bord.NrProduse;
		this->Furnizor = new char[strlen(bord.Furnizor) + 1];
		strcpy(this->Furnizor, bord.Furnizor);
		this->SumaAprovizionare = new int[bord.NrProduse];
		for (int i = 0; i < bord.NrProduse; i++)
			this->SumaAprovizionare[i] = bord.SumaAprovizionare[i];
		bord.NrAprovizionare++;
	}

	BorderouAchizitie  operator=(const BorderouAchizitie & bord) {
		this->NrProduse = bord.NrProduse;
		this->Furnizor = new char[strlen(bord.Furnizor) + 1];
		strcpy(this->Furnizor, bord.Furnizor);
		this->SumaAprovizionare = new int[bord.NrProduse];
		for (int i = 0; i < bord.NrProduse; i++)
			this->SumaAprovizionare[i] = bord.SumaAprovizionare[i];
		bord.NrAprovizionare++;
		return *this;
	}

	BorderouAchizitie& operator -=(int minus)
	{
		if (this->SumaAprovizionare[0] >= minus) {
			this->SumaAprovizionare[0] = SumaAprovizionare[0] - minus;
			cout << endl << "Cantitate modificata" << endl;
		}
		else cout << "IMPOSIBIL!";
		return *this;
	}

	BorderouAchizitie& operator +=(int plus)
	{
		this->SumaAprovizionare[1] = SumaAprovizionare[1] + plus;
		cout << endl << "Cantitate modificata" << endl;
		return *this;
	}

	void show() {

		cout << "Furnizor: " << this->Furnizor << endl;
		cout << "Cod aprovizionare: " << this->CodAprovizionare << endl;
		cout << "Nr aprovizionare: " << this->NrAprovizionare << endl;
		cout << "Nr produse: " << this->NrProduse << endl;
		cout << "Suma aprovizionare: " << endl;
		for (int i = 0; i < this->NrProduse; i++)
			cout << "Suma " << i + 1 << " : " << this->SumaAprovizionare[i] << endl;
	}

	void total() {
		float sum = 0.0F;
		for (int i = 0; i < this->NrProduse; i++)
			sum += this->SumaAprovizionare[i];
		cout << "Totalul este: " << sum;
	}

	friend ostream& operator<<(ostream & cout, BorderouAchizitie & bord);
	friend istream& operator >> (istream &cin, BorderouAchizitie & bord);

	friend ofstream& operator<<(ofstream & cout, BorderouAchizitie & bord) {
		cout << "Furnizor: " << bord.Furnizor << endl;
		cout << "Cod aprovizionare: " << bord.CodAprovizionare << endl;
		cout << "Nr aprovizionare: " << bord.NrAprovizionare << endl;
		cout << "Nr produse: " << bord.NrProduse << endl;
		cout << "Suma aprovizionare: " << endl;
		for (int i = 0; i < bord.NrProduse; i++)
			cout << "Suma " << i + 1 << " : " << bord.SumaAprovizionare[i] << endl;
		return cout;
	}


	~BorderouAchizitie() {
		if (this->Furnizor)
			delete this->Furnizor;
		if (this->SumaAprovizionare)
			delete this->SumaAprovizionare;
	}
};

ostream& operator<<(ostream & cout, BorderouAchizitie & bord) {
	cout << "Furnizor: " << bord.Furnizor << endl;
	cout << "Cod aprovizionare: " << bord.CodAprovizionare << endl;
	cout << "Nr aprovizionare: " << bord.NrAprovizionare << endl;
	cout << "Nr produse: " << bord.NrProduse << endl;
	cout << "Suma aprovizionare: " << endl;
	for (int i = 0; i < bord.NrProduse; i++)
		cout << "Suma " << i + 1 << " : " << bord.SumaAprovizionare[i] << endl;
	return cout;
}

istream & operator >> (istream &cin, BorderouAchizitie & bord) {
	char buffer[50];
	cout << endl << "Furnizor:";
	cin >> buffer;
	bord.Furnizor = new char[strlen(buffer) + 1];
	strcpy(bord.Furnizor, buffer);
	cout << "Nr produse:";
	cin >> bord.NrProduse;
	bord.SumaAprovizionare = new int[bord.NrProduse];
	for (int i = 0; i < bord.NrProduse; i++) {
		cout << "Produs " << i + 1 << " : ";
		cin >> bord.SumaAprovizionare[i];
	}
	cout << endl;
	return cin;
}

class Magazin : public ICommon {

private:

	char* Nume;
	float Suprafata;
	int NrProduse;
	int* Vanzari;

public:

	char* getNume() {
		if (Nume)
			return this->Nume;
	}

	float getSuprafata() {
		return this->Suprafata;
	}

	int getNrProduse() {
		return this->NrProduse;
	}

	int* getVanzari() {
		if (Vanzari)
			return this->Vanzari;
	}

	void setNume(char* Nume) {
		if (Nume) {
			if (this->Nume)
				this->Nume = new char[strlen(Nume) + 1];
			strcpy(this->Nume, Nume);
		}
	}

	void setSuprafata(float Suprafata) {
		this->Suprafata = Suprafata;
	}

	void setNrProduse(int NrProduse) {
		this->NrProduse = NrProduse;
	}

	void setVanzari(int* Vanzari) {
		if (Vanzari) {
			if (this->Vanzari)
				this->Vanzari = new int[NrProduse];
			for (int i = 0; i < NrProduse; i++)
				this->Vanzari[i] = Vanzari[i];
		}
	}

	Magazin() {
		this->Nume = NULL;
		this->Suprafata = 0.0F;
		this->NrProduse = 0;
		this->Vanzari = NULL;
	}

	Magazin(char* Nume, float Suprafata, int NrProduse, int* Vanzari) {
		this->Nume = new char[strlen(Nume) + 1];
		strcpy(this->Nume, Nume);
		this->Suprafata = Suprafata;
		this->NrProduse = NrProduse;
		this->Vanzari = new int[NrProduse];
		for (int i = 0; i<NrProduse; i++)
			this->Vanzari[i] = Vanzari[i];
	}

	Magazin(const Magazin & mag) {
		if (this->Nume)
		{
			this->Nume = new char[strlen(mag.Nume) + 1];
			strcpy(this->Nume, mag.Nume);
		}
		else this->Nume = NULL;
		this->Suprafata = mag.Suprafata;
		this->NrProduse = mag.NrProduse;
		if (this->Vanzari)
		{
			this->Vanzari = new int[mag.NrProduse];
			for (int i = 0; i<mag.NrProduse; i++)
				this->Vanzari[i] = mag.Vanzari[i];
		}
		else this->Vanzari = NULL;
	}

	Magazin & operator=(const Magazin & mag) {
		if (this->Nume)
			delete this->Nume;
		this->Nume = new char[strlen(mag.Nume) + 1];
		strcpy(this->Nume, mag.Nume);
		this->Suprafata = mag.Suprafata;
		this->NrProduse = mag.NrProduse;
		if (this->Vanzari)
			delete this->Vanzari;
		this->Vanzari = new int[mag.NrProduse];
		for (int i = 0; i<NrProduse; i++)
			this->Vanzari[i] = mag.Vanzari[i];
		return *this;

	}

	explicit operator int() {
		return Suprafata;
	}

	Magazin& operator+=(float plus)
	{
		this->Suprafata += plus;
		return *this;
	}

	Magazin& operator-=(float minus)
	{
		if (this->Suprafata >= minus)
			this->Suprafata -= minus;
		else cout << "IMPOSIBIL";
		return *this;
	}

	void show() {
		cout << "Magazin: " << this->Nume << endl;
		cout << "Suprafata: " << this->Suprafata << " metri patrati" << endl;
		cout << "Nr produse: " << this->NrProduse << endl;
		for (int i = 0; i < this->NrProduse; i++)
			cout << "Vanzari: " << this->Vanzari[i] << endl;
	}

	void afiseaza() {
		cout << "Magazin: " << this->Nume << " - ";
		cout << "Suprafata: " << this->Suprafata << " metri patrati" << " - ";
		cout << "Nr produse: " << this->NrProduse << " - ";
		for (int i = 0; i < this->NrProduse; i++)
			cout << "Vanzari: " << this->Vanzari[i] << ", ";
		cout << endl;
	}

	void total() {
		float sum = 0.0F;
		for (int i = 0; i < this->NrProduse; i++)
			sum += this->Vanzari[i];
		cout << "Totalul este: " << sum;
	}

	friend ostream & operator << (ostream &cout, Magazin &mag);
	friend istream & operator >> (istream &cin, Magazin &mag);

	friend ofstream & operator << (ofstream &cout, Magazin &mag) {
		cout << "Nume: " << mag.Nume << endl;
		cout << "Suprafata: " << mag.Suprafata << " metri patrati" << endl;
		cout << "Nr Produse: " << mag.NrProduse << endl;
		for (int i = 0; i < mag.NrProduse; i++)
			cout << "Vanzari: " << mag.Vanzari[i] << endl;
		return cout;
	}

	~Magazin() {
		if (this->Nume)
			delete this->Nume;
		if (this->Vanzari)
			delete this->Vanzari;
		this->NrProduse = 0;
		this->Suprafata = 0.0F;
	}
};

ostream & operator << (ostream &cout, Magazin &mag) {
	cout << "Nume: " << mag.Nume << endl;
	cout << "Suprafata: " << mag.Suprafata << " metri patrati" << endl;
	cout << "Nr Produse: " << mag.NrProduse << endl;
	for (int i = 0; i < mag.NrProduse; i++)
		cout << "Vanzari: " << mag.Vanzari[i] << endl;
	return cout;
}

istream & operator >> (istream &cin, Magazin &mag) {
	char buffer[50];
	if (mag.Nume)
		delete mag.Nume;
	if (mag.Vanzari)
		delete mag.Vanzari;
	cout << "Nume: ";
	cin >> buffer;
	mag.Nume = new char[strlen(buffer) + 1];
	strcpy(mag.Nume, buffer);
	cout << "Suprafata : ";
	cin >> mag.Suprafata;
	cout << "Nr produse: ";
	cin >> mag.NrProduse;
	mag.Vanzari = new int[mag.NrProduse];
	for (int i = 0; i < mag.NrProduse; i++)
	{
		cout << "Vanzari " << i + 1 << " : ";
		cin >> mag.Vanzari[i];
	}
	cout << endl;
	return cin;
}

class Produs {

protected:

	int id;
	char nume[100];
	float pret;

public:

	virtual void afisare()
	{
		cout << "ID: " << id << endl << "Nume: " << nume << endl << "Pret: " << pret << endl;
	}

	int getId()
	{
		return id;
	}

	void setId(int id)
	{
		this->id = id;
	}

	char* getNume()
	{
		return nume;
	}

	void setNume(char nume[])
	{
		strcpy(this->nume, nume);
	}

	float getPret()
	{
		return pret;
	}

	void setPret(float pret)
	{
		this->pret = pret;
	}

	Produs()
	{
		id = 0;
		strcpy(nume, "Produs_Anonim");
		pret = 0;

	}

	Produs(int id, char nume[], float pret)
	{
		this->id = id;
		strcpy(this->nume, nume);
		this->pret = pret;
	}

	Produs(const Produs &p)
	{
		this->id = p.id;
		strcpy(this->nume, p.nume);
		this->pret = p.pret;
	}

	Produs & operator=(const Produs &p)
	{
		this->id = p.id;
		strcpy(this->nume, p.nume);
		this->pret = p.pret;
		return *this;
	}

	void operator=(Produs &p)
	{
		this->id = p.id;
		strcpy(this->nume, p.nume);
		this->pret = p.pret;

	}
	friend ofstream & operator<<(ofstream &out, Produs &p)

	{
		out << p.id << endl;
		out << p.nume << endl;
		out << p.pret << endl;
		return out;
	}

	friend ostream & operator<<(ostream &out, Produs &p)
	{
		out << "ID: " << p.id << endl;
		out << "Nume: " << p.nume << endl;
		out << "Pret: " << p.pret << endl;
		return out;
	}



	friend ifstream & operator >> (ifstream &in, Produs &p)
	{
		if (in.is_open())
		{
			in >> p.id;
			in >> p.nume;
			in >> p.pret;
		}
		else
			throw exception("Eroare citire din fisier!\n");
		return in;
	}

	friend istream & operator >> (istream &in, Produs &p)
	{
		cout << "id: ";
		in >> p.id;
		cout << "nume: ";
		in >> p.nume;
		cout << "pret: ";
		in >> p.pret;
		return in;
	}

	~Produs()
	{
	}
};

class Locatie
{
protected:
	char *adresa;
public:
	Locatie()
	{
		adresa = new char[strlen("Adresa_anonima") + 1];
		strcpy(adresa, "Adresa_anonima");
	}

	Locatie(char *n)
	{
		adresa = new char[strlen(n) + 1];
		strcpy(adresa, n);
	}

	Locatie(Locatie &l)
	{
		adresa = new char[strlen(l.adresa) + 1];
		strcpy(adresa, l.adresa);
	}

	char *getAdresa()
	{
		return adresa;
	}

	virtual void afiseazaInformatii() = 0;

	virtual void metodaVirtuala() = 0;
	~Locatie()
	{}
};

class Market : public Locatie
{
protected:
	int suprafata;
public:
	Market() : Locatie()
	{
		suprafata = 100;
	}

	Market(char *n, int sup) : Locatie(n)
	{
		suprafata = sup;
	}

	Market(Market &m) : Locatie(m)
	{
		suprafata = m.suprafata;
	}

	int getSuprafata()
	{
		return suprafata;
	}

	void setSuprafata(int n)
	{
		if (n > 0)
			suprafata = n;
	}

	void afiseazaInformatii()
	{
		cout << "Marketul se afla la locatia" << adresa << " si are suprafata de " << suprafata << " metri patrati." << endl;
	}

	void metodaVirtuala()
	{
		cout << "Se apeleaza metoda virtuala din Market.";
	}

	~Market()
	{}
};

class Hipermarket : public Market
{
private:
	int nrAngajati;
public:
	Hipermarket() : Market()
	{
		nrAngajati = 200;
	}

	Hipermarket(char *n, int sup, int nr) : Market(n, sup)
	{
		nrAngajati = nr;
	}
	Hipermarket(Hipermarket &h) : Market(h)
	{
		nrAngajati = h.nrAngajati;
	}

	void afiseazaInformatii()
	{
		cout << "Hipermarketul se afla la adresa" << getAdresa() << ", are suprafata de " << suprafata << " si are " << nrAngajati << " angajati" << endl;
	}
	~Hipermarket() {

	}

};

class Depozit : public Locatie
{
private:
	BorderouAchizitie *borderou;
	int NrBorderou;
public:
	Depozit() : Locatie()
	{
		NrBorderou = 0;
		borderou = 0;
	}

	Depozit(char *n, int nr, BorderouAchizitie *cat) :Locatie(n)
	{
		NrBorderou = nr;
		if (nr > 0)
		{
			borderou = new BorderouAchizitie[nr];
			for (int i = 0; i < nr; i++)
				borderou[i] = cat[i];
		}
		else borderou = 0;
	}

	~Depozit()
	{
		delete[] borderou;
	}

	void afiseazaInformatii()
	{
		cout << "Depozitul se afla la adresa " << adresa << " si se afla " << NrBorderou << "numar borderou" << endl;
	}

	void metodaVirtuala()
	{
		cout << "Se afiseaza metoda virtuala din Depozit" << endl;
	}

};

class Bautura : public Produs
{
private:
	int nrSeturi;
	int* seturi;
public:
	Bautura() : Produs()
	{
		nrSeturi = 0;
		seturi = 0;
	}

	Bautura(int id, char nume[], float pret, int nr, int *sets) : Produs(id, nume, pret)
	{
		nrSeturi = nr;
		sets = new int[nr];
		for (int i = 0; i < nr; i++)
			seturi[i] = sets[i];
	}

	Bautura(Bautura &b) : Produs(b)
	{
		nrSeturi = b.nrSeturi;
		seturi = new int[nrSeturi];
		for (int i = 0; i < nrSeturi; i++)
			seturi[i] = b.seturi[i];
	}

	void operator=(Bautura &b)
	{
		this->id = b.id;
		strcpy(this->nume, b.nume);
		this->pret = b.pret;
		nrSeturi = b.nrSeturi;
		seturi = new int[nrSeturi];
		for (int i = 0; i < nrSeturi; i++)
			seturi[i] = b.seturi[i];
	}

	void afisare()
	{
		cout << "ID: " << id << endl << "Nume: " << nume << endl << "Pret: " << pret << endl;
		cout << "Numar seturi: " << nrSeturi << endl;
		for (int i = 0; i < nrSeturi; i++)
			cout << seturi[i] << " ";
		cout << endl;
	}


	int getNrSeturi()
	{
		return nrSeturi;
	}

	void setNrSeturi(int x)
	{
		if (x>0)
			nrSeturi = x;
	}

	int* getSeturi() {
		return seturi;
	}

	void setSeturi(int x, int*vector)
	{
		if (x > 0)
		{
			if (seturi != 0)
				delete[] seturi;
			seturi = new int[x];
			for (int i = 0; i < x; i++)
				seturi[i] = vector[i];
		}
	}

	friend istream& operator >> (istream& in, Bautura &p)
	{
		cout << "id: ";
		in >> p.id;
		cout << "nume: ";
		in >> p.nume;
		cout << "pret: ";
		in >> p.pret;
		cout << "numar seturi: ";
		in >> p.nrSeturi;
		p.seturi = new int[p.nrSeturi];
		for (int i = 0; i < p.nrSeturi; i++)
		{
			cout << "Setul[" << i << "]=";
			in >> p.seturi[i];
		}

		return in;
	}

	friend ostream& operator<<(ostream& out, Bautura &b)
	{
		out << "ID: " << b.id << endl << "Nume: " << b.nume << endl << "Pret: " << b.pret << endl;
		out << "Numar seturi: " << b.nrSeturi << endl;
		for (int i = 0; i < b.nrSeturi; i++)
			cout << b.seturi[i] << " ";
		out << endl;
		return out;
	}

	int operator[](int index)
	{
		if (index < nrSeturi)
			return seturi[index];
		else return -1;
	}

	Bautura operator+(int x)
	{
		for (int i = 0; i < nrSeturi; i++)
			seturi[i] += x;
	}

	Bautura operator-(int x)
	{
		for (int i = 0; i < nrSeturi; i++)
			if (x <= seturi[i])
				seturi[i] -= x;
	}

	Bautura operator-=(int x)
	{
		for (int i = 0; i < nrSeturi; i++)
			if (x <= seturi[i])
				seturi[i] -= x;
	}

	Bautura operator+=(int x)
	{
		for (int i = 0; i < nrSeturi; i++)
			if (x <= seturi[i])
				seturi[i] += x;
	}

	Bautura operator*(int x)
	{
		for (int i = 0; i < nrSeturi; i++)
			seturi[i] *= x;
	}

	Bautura operator*=(int x)
	{
		for (int i = 0; i < nrSeturi; i++)
			seturi[i] *= x;
	}

	Bautura operator/(int x)
	{
		if (x>0)
			for (int i = 0; i < nrSeturi; i++)
				seturi[i] /= x;
	}

	Bautura operator/=(int x)
	{
		if (x>0)
			for (int i = 0; i < nrSeturi; i++)
				seturi[i] -= x;
	}


	bool operator!()
	{
		return !nrSeturi;
	}

};

int Utilizator::Vizite = 0;
int BorderouAchizitie::NrAprovizionare = 0;

int main(int argc, char** argv) {
	if (argc > 2)
	{
		ofstream a(argv[0]), b(argv[1]), c(argv[2]), d(argv[3]), e(argv[4]);
		float total[] = { 20, 30, 40, 70.9 };
		Facturi Facturi1("Cuptor", total, 4, 12);
		cout << Facturi1 << endl;
		Facturi Facturi5;
		Facturi5 = Facturi1;
		cout << endl << Facturi5 << endl;
		Facturi Facturi2 = Facturi1;
		cout << Facturi2 << endl;
		Facturi Facturi3;
		cin >> Facturi3;
		cout << Facturi3 << endl;
		system("PAUSE");
		Facturi Facturi4;
		Facturi4 = Facturi2;
		Facturi4 -= 7;
		cout << endl << Facturi4 << endl;
		system("PAUSE");
		Facturi Facturi6;
		Facturi6 = Facturi1;
		Facturi6 += Facturi1;
		cout << Facturi6 << endl;
		system("PAUSE");
		Facturi1.setNumeProdus("Produse de post");
		cout << "Produs:  " << Facturi1.getNumeProdus() << endl;
		system("PAUSE");
		Facturi1.show();
		system("PAUSE");
		Facturi1.total();
		system("PAUSE");
		char* ch = "44444";
		a << Facturi1 << Facturi2 << Facturi3 << Facturi4 << Facturi5 << Facturi6;
		Utilizator casa1("Test", 5, ch, 8);
		cout << casa1 << endl;
		Utilizator casa3;
		casa3 = casa1;
		cout << endl << casa3;
		system("PAUSE");
		Utilizator casa2 = casa1;
		cout << casa2;
		system("PAUSE");
		Utilizator casa6;
		cin >> casa6;
		cout << endl << casa6;
		Utilizator casa4 = casa1;
		casa4 += 5;
		cout << endl << casa4;
		system("PAUSE");
		Utilizator casa5 = casa1;
		casa5 -= 3;
		cout << endl << casa5;
		system("PAUSE");
		casa1.setLungime(casa1.getLungime());
		cout << "Lungimea Utilizator 1: " << casa1.getLungime() << endl;
		system("PAUSE");
		casa1.show();
		system("PAUSE");
		casa1.total();
		system("PAUSE");
		int Amount[] = { 10, 11, 12, 13, 15 };
		b << casa1 << casa2 << casa3 << casa4 << casa5 << casa6;
		BorderouAchizitie borderou1("Test", Amount, 5, 21);
		cout << borderou1 << endl;
		BorderouAchizitie borderou3;
		borderou3 = borderou1;
		cout << endl << borderou3 << endl;
		system("PAUSE");
		BorderouAchizitie borderou5;
		borderou5 = borderou1;
		cout << endl << borderou5 << endl;
		BorderouAchizitie borderou2;
		cin >> borderou2;
		cout << borderou2;
		BorderouAchizitie borderou6;
		borderou6 = borderou1;
		borderou6 -= 5;
		cout << endl << borderou6 << endl;
		system("PAUSE");
		BorderouAchizitie borderou4 = borderou1;
		borderou4 += 10;
		cout << endl << borderou4 << endl;
		system("PAUSE");
		borderou1.setFurnizor(borderou1.getFurnizor());
		cout << "Furnizor : " << borderou1.getFurnizor() << endl;
		system("PAUSE");
		borderou1.show();
		system("PAUSE");
		borderou1.total();
		system("PAUSE");
		int vanzari[] = { 10, 15, 20, 25, 88 };
		c << borderou1 << borderou2 << borderou3 << borderou4 << borderou5 << borderou6;
		Magazin mag1("Mega", 2.2, 5, vanzari);
		cout << endl;
		cout << mag1 << endl;
		Magazin mag2;
		mag2 = mag1;
		cout << endl << mag2 << endl;
		Magazin mag3 = mag2;
		cout << mag3 << endl;
		Magazin mag4;
		cin >> mag4;
		cout << mag4 << endl;
		Magazin mag5 = mag4;
		mag5 += 7.2F;
		cout << mag5 << endl;
		cout << "Suprafata int este: " << int(mag4) << endl;
		system("PAUSE");
		Magazin mag6 = mag4;
		mag6 -= 10.2F;
		cout << mag6 << endl;
		system("PAUSE");
		mag1.setSuprafata(mag1.getSuprafata());
		cout << "Suprafata: " << mag1.getSuprafata() << endl;
		system("PAUSE");
		mag1.show();
		system("PAUSE");
		mag1.total();
		system("PAUSE");
		float cantitate[] = { 10, 20, 30.3, 40, 50 };
		d << mag1 << mag2 << mag3 << mag4 << mag5 << mag6;
		Produs stoc3;
		cin >> stoc3;
		cout << endl << stoc3 << endl;
		system("PAUSE");
		e << stoc3;
	}
	else
	{
		ifstream B("Utilizatori.bin", fstream::binary);
		vector<Utilizator> utilizatori;
		for (Utilizator u; B >> u;)
			utilizatori.push_back(u);
		while (true)
		{
			char nume[100];
			char ch;
			cout << "\nIntroduceti numele: ";
			cin >> nume;
			cout << "\nIntroduceti parola: ";
			string parola = "";
			ch = _getch();
			while (ch != 13)
			{
				parola.push_back(ch);
				cout << '*';
				ch = _getch();
			}
			bool match = false;
			for (int i = 0; i < utilizatori.size(); i++)
			{
				if ((strcmp(utilizatori.at(i).getNumeCasier(), nume) == 0) && (strcmp(utilizatori.at(i).getParola(), parola.data()) == 0))
				{
					match = true;
					vector<Facturi>* facturi = new vector<Facturi>();
					ofstream a("Facturi.txt"), c("Borderouri.txt"), d("Magazine.bin"), e("StocuriProduse.txt");
					while (true)
					{
						char temp[100];
						cout << "\n\nTastati optiunea dorita dintre cele de mai jos exact la fel:" << endl;
						cout << "\nAdauga_Utilizator\nVizualizare_Utilizatori\nAdauga_Produs\nAdauga_Magazin\nFacturare\nBorderou\nIesire\n\n";
						cin >> temp;
						if (strcmp(temp, "Adauga_Utilizator") == 0)
						{
							ofstream b("Utilizatori.bin");
							Utilizator u;
							cin >> u;
							utilizatori.push_back(u);
							char* ch = "44444";
							Utilizator casa1("Test", 5, ch, 8);
							cout << casa1 << endl;
							Utilizator casa3;
							casa3 = casa1;
							cout << endl << casa3;
							system("PAUSE");
							Utilizator casa2 = casa1;
							cout << casa2;
							system("PAUSE");
							Utilizator casa6;
							cin >> casa6;
							cout << endl << casa6;
							Utilizator casa4 = casa1;
							casa4 += 5;
							cout << endl << casa4;
							system("PAUSE");
							Utilizator casa5 = casa1;
							casa5 -= 3;
							cout << endl << casa5;
							system("PAUSE");
							casa1.setLungime(casa1.getLungime());
							cout << "Lungimea Utilizator 1: " << casa1.getLungime() << endl;
							system("PAUSE");
							casa1.show();
							system("PAUSE");
							casa1.total();
							system("PAUSE");
							utilizatori.push_back(casa1);
							utilizatori.push_back(casa2);
							utilizatori.push_back(casa3);
							utilizatori.push_back(casa4);
							utilizatori.push_back(casa5);
							for (int i = 0; i < utilizatori.size(); i++)
								utilizatori.at(i).show();
							b << casa1 << casa2 << casa3 << casa4 << casa5 << casa6;
							system("PAUSE");
						}
						if (strcmp(temp, "Vizualizare_Utilizatori") == 0)
						{
							for (int i = 0; i < utilizatori.size(); i++)
							{
								cout << "ID: " << utilizatori.at(i).getCodCasier() << endl;
								cout << "User: " << utilizatori.at(i).getNumeCasier() << endl;
							}
							system("PAUSE");
						}
						else if (strcmp(temp, "Adauga_Produs") == 0)
						{
							float cantitate[] = { 10, 20, 30.3, 40, 50 };
							Produs stoc3;
							cin >> stoc3;
							cout << endl << stoc3 << endl;
							system("PAUSE");
							e << stoc3;
							system("pause");
						}
						else if (strcmp(temp, "Adauga_Magazin") == 0)
						{
							int vanzari[] = { 10, 15, 20, 25, 88 };
							Magazin mag1("Mega", 2.2, 5, vanzari);
							cout << endl;
							cout << mag1 << endl;
							Magazin mag2;
							mag2 = mag1;
							cout << endl << mag2 << endl;
							Magazin mag3 = mag2;
							cout << mag3 << endl;
							Magazin mag4;
							cin >> mag4;
							cout << mag4 << endl;
							Magazin mag5 = mag4;
							mag5 += 7.2F;
							cout << mag5 << endl;
							cout << "Suprafata int este: " << int(mag4) << endl;
							system("PAUSE");
							Magazin mag6 = mag4;
							mag6 -= 10.2F;
							cout << mag6 << endl;
							system("PAUSE");
							mag1.setSuprafata(mag1.getSuprafata());
							cout << "Suprafata: " << mag1.getSuprafata() << endl;
							system("PAUSE");
							mag1.show();
							system("PAUSE");
							mag1.total();
							system("PAUSE");
							d << mag1 << mag2 << mag3 << mag4 << mag5 << mag6;
							system("pause");
						}
						else if (strcmp(temp, "Facturare") == 0)
						{
							float total[] = { 20, 30, 40, 70.9 };
							Facturi Facturi1("Cuptor", total, 4, 12);
							cout << Facturi1 << endl;
							Facturi Facturi5;
							Facturi5 = Facturi1;
							cout << endl << Facturi5 << endl;
							Facturi Facturi2 = Facturi1;
							cout << Facturi2 << endl;
							Facturi Facturi3;
							cin >> Facturi3;
							cout << Facturi3 << endl;
							system("PAUSE");
							Facturi Facturi4;
							Facturi4 = Facturi2;
							Facturi4 -= 7;
							cout << endl << Facturi4 << endl;
							system("PAUSE");
							Facturi Facturi6;
							Facturi6 = Facturi1;
							Facturi6 += Facturi1;
							cout << Facturi6 << endl;
							system("PAUSE");
							Facturi1.setNumeProdus("Produse de post");
							cout << "Produs:  " << Facturi1.getNumeProdus() << endl;
							system("PAUSE");
							Facturi1.show();
							system("PAUSE");
							Facturi1.total();
							system("PAUSE");
							facturi->push_back(Facturi1);
							facturi->push_back(Facturi2);
							facturi->push_back(Facturi3);
							facturi->push_back(Facturi4);
							facturi->push_back(Facturi5);
							facturi->push_back(Facturi6);
							for (int i = 0; i < facturi->size(); i++)
								facturi->at(i).show();
							a << Facturi1 << Facturi2 << Facturi3 << Facturi4 << Facturi5 << Facturi6;
							system("pause");
						}
						else if (strcmp(temp, "Borderou") == 0)
						{
							int Amount[] = { 10, 11, 12, 13, 15 };
							BorderouAchizitie borderou1("Test", Amount, 5, 21);
							cout << borderou1 << endl;
							BorderouAchizitie borderou3;
							borderou3 = borderou1;
							cout << endl << borderou3 << endl;
							system("PAUSE");
							BorderouAchizitie borderou5;
							borderou5 = borderou1;
							cout << endl << borderou5 << endl;
							BorderouAchizitie borderou2;
							cin >> borderou2;
							cout << borderou2;
							BorderouAchizitie borderou6;
							borderou6 = borderou1;
							borderou6 -= 5;
							cout << endl << borderou6 << endl;
							system("PAUSE");
							BorderouAchizitie borderou4 = borderou1;
							borderou4 += 10;
							cout << endl << borderou4 << endl;
							system("PAUSE");
							borderou1.setFurnizor(borderou1.getFurnizor());
							cout << "Furnizor : " << borderou1.getFurnizor() << endl;
							system("PAUSE");
							borderou1.show();
							system("PAUSE");
							borderou1.total();
							system("PAUSE");
							c << borderou1 << borderou2 << borderou3 << borderou4 << borderou5 << borderou6;
							system("pause");
						}
						else if (strcmp(temp, "Iesire") == 0)
						{
							cout << "\nLa revedere!" << endl << endl;
							exit(0);
						}
					}
				}
			}
			if (match == false)
			{
				cout << "\nOptiune incorecta, incercati din nou!" << endl << endl;
				system("pause");
			}
		}
	}
}
