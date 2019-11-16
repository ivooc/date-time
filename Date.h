#ifndef _DATE_H__
#define _DATE_H__

#include <ctime>
#include <string>
#include <regex>
#include <vector>

class Date {
	std::string dataString;
	static const std::regex re;
	static const std::vector<std::string> explode(const std::string&, const char&);
	static time_t stringToTime(const std::string&);
public:
	Date(); // constroi um Date com a hora de agora
	Date(const std::string&); // constroi um Date com a hora passada por string em formato dd/mm/yyyy
	Date& Hoje(); // seta a data para o dia de hoje
	const std::string pegarData() const; // retorna string dd/mm/yyyy
	void setarData(const std::string&); // seta a data do objeto
	void adicionarDias(const int&); // adiciona dias
	int difDias (const Date&) const; // retorna dias de diferenca entre o parametro e o objeto (parametro - objeto)
	bool operator< (const Date&) const;
	bool operator== (const Date&) const;
	bool operator== (const std::string&) const;
	bool operator!= (const Date&) const;
	bool operator!= (const std::string&) const;
	friend std::ostream& operator<< (std::ostream&, const Date&);
	friend std::istream& operator>> (std::istream&, Date&);
	~Date();
};

#endif