#include "Library.h"


void Library::createReader(std::string& name)
{
	if (name.empty() || name[0] == ' ')
	{
		std::cout << "invalid name for reader" << std::endl;
		return;
	}
	for (auto& i : name) if (i == ' ') i = '_';
	auto it = _libReader.find(name);
	if (it == _libReader.end())
	{
		try
		{
			_libReader[name] = std::make_shared<Reader>(Reader(name));
		}
		catch (const std::exception & ex)
		{
			std::cerr << "Error create Reader: " << ex.what();
			return;
		}
	}
	else
	{
		std::cout << "Uncorrect name" << std::endl;
	}
}

void Library::showReader()
{
	int count_reader = 1;
	int count_book;
	std::cout << "\n=======================\n" << "List reader:\n\n";
	for (const auto& i : _libReader)
	{
		std::string tempReaderName = i.second->_nameReader;
		for (auto& i : tempReaderName) if (i == '_') i = ' ';
		std::cout << count_reader << ". " << tempReaderName << "\t";
		count_reader++;
		count_book = 1;
		for (const auto& it_listBook : i.second->_listBook)
		{
			if (it_listBook.lock() != nullptr)
			{
				std::string tempBookName = it_listBook.lock()->_nameBook;
				for (auto& i : tempBookName) if (i == '_') i = ' ';
				std::cout << count_book << "." << tempBookName << " ";
				count_book++;
			}
		}
		std::cout << std::endl;
	}
	std::cout << "=======================\n";
}

void Library::createBook(std::string& name)
{
	if (name.empty() || name[0] == ' ')
	{
		std::cout << "invalid name for book" << std::endl;
		return;
	}
	for (auto& i : name) if (i == ' ') i = '_';
	try
	{
		_libBook.emplace(name, std::make_shared<Book>(Book(name)));
	}
	catch (const std::exception & ex)
	{
		std::cerr << "Error create Book: " << ex.what();
		return;
	}
}

void Library::showBook()
{
	int count_book = 1;
	std::cout << "\n=======================\n" << "List book:\n\n";
	for (const auto& i : _libBook)
	{
		std::string tempBookName = i.second->_nameBook;
		for (auto& i : tempBookName) if (i == '_') i = ' ';
		std::cout << count_book << ". " << tempBookName << "\t\t";
		count_book++;
		if (i.second->_reader.lock() != nullptr)
		{
			std::string tempReaderName = i.second->_reader.lock()->_nameReader;
			for (auto& i : tempReaderName) if (i == '_') i = ' ';
			std::cout << tempReaderName;
		}
		std::cout << std::endl;
	}
	std::cout << "=======================\n";
}

void Library::giveBook(std::string& reader, std::string& book)
{
	for (auto& i : book) if (i == ' ') i = '_';
	for (auto& i : reader) if (i == ' ') i = '_';
	auto it_reader = _libReader.find(reader);
	if (it_reader != _libReader.end())
	{
		auto iter_book = _libBook.equal_range(book);
		if (iter_book.first != iter_book.second)
		{
			bool check_book = true;
			for (auto it = iter_book.first; it != iter_book.second; ++it)
			{
				if (it->second->_reader.lock() == nullptr)
				{
					bool check_vector = true;
					for (auto& it_vector : it_reader->second->_listBook)
					{
						if (it_vector.lock() == nullptr)
						{
							it_vector = it->second;
							check_vector = false;
							it->second->_reader = it_reader->second;
							break;
						}
					}
					if (check_vector)
					{
						try
						{
							it_reader->second->_listBook.push_back(it->second);
						}
						catch (const std::exception & ex)
						{
							std::cerr << "Error: " << ex.what();
							return;
						}
					}
					it->second->_reader = it_reader->second;
					check_book = false;
					break;
				}
			}
			if (check_book)
			{
				std::cout << "No free book " << std::endl;
				return;
			}
		}
		else std::cout << "Book not found" << std::endl;
	}
	else std::cout << "Invalid Reader" << std::endl;
}

void Library::takeBook(std::string& reader, std::string& book)
{
	for (auto& i : book) if (i == ' ') i = '_';
	for (auto& i : reader) if (i == ' ') i = '_';
	auto it_reader = _libReader.find(reader);
	if (it_reader != _libReader.end())
	{
		auto iter_book = _libBook.equal_range(book);
		if (iter_book.first != iter_book.second)
		{
			for (auto& it_listBook : it_reader->second->_listBook)
			{
				if (it_listBook.lock()->_nameBook == book)
				{
					it_listBook.lock()->_reader.reset();
					it_listBook.reset();
					return;
				}
			}
		}
		else std::cout << "Invalid Book" << std::endl;
	}
	else std::cout << "Invalid Reader" << std::endl;
}

void Library::saveData()
{
	std::ofstream dataBook;
	dataBook.exceptions(std::ofstream::badbit | std::ofstream::failbit);
	std::ofstream dataReader;
	dataReader.exceptions(std::ofstream::badbit | std::ofstream::failbit);

	try
	{
		std::string fileBook = "DataBook.txt";
		dataBook.open(fileBook);
		std::string fileReader = "DataReader.txt";
		dataReader.open(fileReader);
	}
	catch (const std::exception & ex)
	{
		std::cout << ex.what() << std::endl;
		std::cout << "can't opem file " << std::endl;
		return;
	}


	for (const auto& i : _libBook)
	{
		dataBook << i.second->_nameBook << std::endl;
	}
	dataBook.close();

	for (const auto& i : _libReader)
	{
		dataReader << i.second->_nameReader;
		for (auto& it_listBook : i.second->_listBook)
		{
			if (it_listBook.lock() != nullptr)
			{
				dataReader << " " << it_listBook.lock()->_nameBook;
			}
		}
		dataReader << std::endl;
	}
	dataReader.close();
	std::cout << "Save files" << std::endl;
}

void Library::openData()
{
	std::string str;
	std::string reader;
	std::string book;

	std::ifstream file;
	file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	try
	{
		std::string bookList = "DataBook.txt";
		file.open(bookList);
	}
	catch (const std::exception & ex)
	{
		std::cout << ex.what() << std::endl;
		std::cout << "can't opem file with BookList" << std::endl;
		return;
	}

	while (file)
	{
		try
		{
			std::getline(file, str);
			if (!str.empty()) createBook(str);
		}
		catch (const std::exception & ex) {}
	}
	file.close();

	try
	{
		std::string readerList = "DataReader.txt";
		file.open(readerList);
	}
	catch (const std::exception & ex)
	{
		std::cout << ex.what() << std::endl;
		std::cout << "can't opem file with ReaderList" << std::endl;
		return;
	}

	while (file)
	{
		try
		{
			std::getline(file, str);
			if (!str.empty() || str != " ")
			{
				auto it_1 = str.begin();
				auto it_2 = str.begin();

				it_2 = find(it_1, str.end(), ' ');
				reader = "";
				copy(it_1, it_2, back_inserter(reader));
				if (!reader.empty()) createReader(reader);
				else throw  std::logic_error("Bad Reader name in base");
				if (it_2 < str.end())
				{
					it_1 = it_2 + 1;
					while (it_2 < str.end())
					{
						book = "";
						it_2 = find(it_1, str.end(), ' ');
						copy(it_1, it_2, back_inserter(book));
						if (!book.empty()) giveBook(reader, book);
						if (it_2 < str.end()) it_1 = it_2 + 1;
					}
				}
			}
		}
		catch (const std::logic_error & ex)
		{
			std::cout << ex.what() << std::endl;
		}
		catch (const std::exception & ex) {}
	}
}

void Library::deleteReader(std::string& reader)
{
	for (auto& i : reader) if (i == ' ') i = '_';
	if (_libReader.find(reader) == _libReader.end())
	{
		for (auto& i : reader) if (i == '_') i = ' ';
		std::cout << reader << " not found";
		return;
	}
	_libReader.erase(reader);
}

void Library::deleteBook(std::string& book)
{
	for (auto& i : book) if (i == ' ') i = '_';
	auto it_bookkey = _libBook.find(book);
	if (it_bookkey != _libBook.end())
	{
		if (_libBook.count(book) == 1) _libBook.erase(book);
		else
		{
			auto iter_book = _libBook.equal_range(book);
			if (iter_book.first != iter_book.second)
			{
				std::cout << "\n" << _libBook.count(book);
				for (auto& i : book) if (i == '_') i = ' ';
				std::cout << " - " << book << "\nList:" << std::endl;
				int count = 1;
				std::string reader;
				for (auto it = iter_book.first; it != iter_book.second; it++)
				{
					if (it->second->_reader.lock() != nullptr)
					{
						reader = it->second->_reader.lock()->_nameReader;
						for (auto& i : reader) if (i == '_') i = ' ';
						std::cout << count << ". " << reader << std::endl;
						count++;
					}
				}
				std::cout << "\nEnter name reader - ";
				reader.clear();

				std::getline(std::cin, reader); // ?

				bool check_reader = true;
				if (!reader.empty())
				{
					for (auto& i : reader) if (i == ' ') i = '_';
					for (auto it = iter_book.first; it != iter_book.second; it++)
					{
						if (it->second->_reader.lock() != nullptr)
						{
							if (it->second->_reader.lock()->_nameReader == reader)
							{
								_libBook.erase(it);
								check_reader = false;
								break;
							}
						}
					}
				}
				else
				{
					for (auto it = iter_book.first; it != iter_book.second; it++)
					{
						if (it->second->_reader.lock() == nullptr)
						{
							_libBook.erase(it);
							check_reader = false;
							break;
						}
					}
				}
				for (auto& i : reader) if (i == '_') i = ' ';
				if (check_reader) std::cout << reader << "  book not found ";
			}
		}
	}
	else std::cout << "Book not found" << std::endl;
}



Library::Reader::Reader(std::string& name)
{
	_nameReader = name;
}

Library::Book::Book(std::string& name)
{
	_nameBook = name;
}