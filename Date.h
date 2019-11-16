#ifndef _DATE_H__
#define _DATE_H__

#include <ctime>
#include <string>
#include <regex>
#include <vector>

using namespace std;

class Date {
	string dataString;
	static const regex re;
	static const vector<string> explode(const string&, const char&);
	static time_t stringToTime(const string&);
public:
	Date(); // constroi um Date com a hora de agora
	Date(const string&); // constroi um Date com a hora passada por string em formato dd/mm/yyyy
	Date& Hoje(); // seta a data para o dia de hoje
	const string pegarData() const; // retorna string dd/mm/yyyy
	void setarData(const string&); // seta a data do objeto
	void adicionarDias(const int&); // adiciona dias
	int difDias (const Date&) const; // retorna dias de diferenca entre o parametro e o objeto (parametro - objeto)
	bool operator< (const Date&) const;
	bool operator== (const Date&) const;
	bool operator== (const string&) const;
	bool operator!= (const Date&) const;
	bool operator!= (const string&) const;
	friend ostream& operator<< (ostream&, const Date&);
	friend istream& operator>> (istream&, Date&);
	~Date();
};

#endif