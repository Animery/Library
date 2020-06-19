#pragma once

#include <iostream>
#include <map>
#include <string>
//#include <iterator>
//#include <algorithm>
#include <vector>
#include <fstream>

class Library
{
public:
	void createReader(std::string &name);
	void showReader();
	void createBook(std::string &name);
	void showBook();
	void giveBook(std::string &reader, std::string &book);
	void takeBook(std::string &reader, std::string &book);
	void saveData();
	void openData();
	void deleteReader(std::string &reader);
	void deleteBook(std::string &book);

private:
	class Book;
	class Reader
	{
	public:
		Reader(std::string &name);
		std::string _nameReader;
		std::vector<std::weak_ptr<Book>> _listBook;
	};
	class Book
	{
	public:
		Book(std::string &name);
		std::string _nameBook;
		std::weak_ptr<Reader> _reader;
	};
	std::multimap <std::string, std::shared_ptr<Book>> _libBook;
	std::map <std::string, std::shared_ptr<Reader>> _libReader;
};

