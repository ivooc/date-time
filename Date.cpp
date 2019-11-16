#include "Date.h"

// expressao regular para avaliar validade de uma data no formato dd/mm/yyyy
// ver https://regexr.com/3b9td (adaptado)
const regex Date::re("(^(((0[1-9]|1[0-9]|2[0-8])[/](0[1-9]|1[012]))|((29|30|31)[/](0[13578]|1[02]))|((29|30)[/](0[4,6,9]|11)))[/](19|[2-9][0-9])[[:digit:]][[:digit:]]$)|(^29[/]02[/](19|[2-9][0-9])(00|04|08|12|16|20|24|28|32|36|40|44|48|52|56|60|64|68|72|76|80|84|88|92|96)$)");

//http://www.cplusplus.com/articles/2wA0RXSz/
const vector<string> Date::explode(const string& s, const char& c) {
	string buff{ "" };
	vector<string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}
time_t Date::stringToTime(const string& s) {
	vector<string> tokens{ explode(s, '/') };
	int dia, mes, ano;
	dia = stoi(tokens[0]);
	mes = stoi(tokens[1]);
	ano = stoi(tokens[2]);
	struct tm dataStruct = {0};
	dataStruct.tm_isdst = -1;
	dataStruct.tm_mday = dia;
	dataStruct.tm_mon = mes - 1;
	dataStruct.tm_year = ano - 1900;
	time_t aux = mktime(&dataStruct);
	if (aux != -1) return aux;
	else throw "falha na conversao";
}
Date::Date() {
	char aux[11];
	time_t Agora = time(0); // recebe a hora de agora
	size_t numCharConv = strftime(aux, 11, "%d/%m/%Y", localtime(&Agora)); // converte uma estrutura de hora para string em formato dd/mm/yyyy e retorna o numero de caracteres convertidos
	if (numCharConv > 0) dataString = aux; // se 0, o numero de caracteres foi excedido
	else throw "a conversao da data para string falhou";
}
Date::Date(const string& ds) {
	if (regex_match(ds, Date::re))
		dataString = ds;
	else throw "data invalida";
}
Date& Date::Hoje() {
	Date aux;
	dataString = aux.dataString;
	return *this;
}
const string Date::pegarData() const {
	return dataString;
}
void Date::setarData(const string& d) {
	if (regex_match(d, Date::re)) {
		dataString = d;
	}
	else throw "data invalida";
}
void Date::adicionarDias(const int& dias) {
	time_t dataT = stringToTime(dataString);
	dataT += static_cast<time_t> (dias * 86400); // acrescenta os dias em segundos a data atual
	char aux[11];
	size_t numCharConv = strftime(aux, 11, "%d/%m/%Y", localtime(&dataT)); // converte uma estrutura de hora para string em formato dd/mm/yyyy e retorna o numero de caracteres convertidos
	if (numCharConv > 0) dataString = aux; // se 0, o numero de caracteres foi excedido
	else throw "maximo de caracteres excedido";
}
int Date::difDias (const Date& d) const {
	double difSegundos = difftime(stringToTime(d.dataString), stringToTime(dataString));
	return static_cast<int> (static_cast<long int> (difSegundos) / 86400);
}
bool Date::operator< (const Date& d) const {
    return (difDias(d) > 0)? true : false;
}
bool Date::operator== (const Date& d) const {
	return (dataString == d.dataString);
}
bool Date::operator== (const string& s) const {
	return (dataString == s);
}
bool Date::operator!= (const Date& d) const {
	return (dataString != d.dataString);
}
bool Date::operator!= (const string& s) const {
	return (dataString != s);
}
ostream& operator<< (ostream& out, const Date& d) {
	out << d.dataString;
	return out;
}
istream& operator>> (istream& in, Date& d) {
	char s[11];
	in.getline(s, 11);
	if (regex_match(s, Date::re)) {
		d.dataString = s;
	}
	else throw "data invalida";
	return in;
}
Date::~Date() {}
