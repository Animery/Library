#include "Interface.h"


int menu()
{
	char menu_count;
	std::cout << "========================" << std::endl;
	std::cout << "Key:\na. new Book\nb. new Reader\nc. Show Book List\nd. Show Reader List\ne. Give out a book";
	std::cout << "\nf. Return a book\ng. Clear Screen\nh. Delete Reader\ni. Delete Book\nj. Save data\nk. Save and exit\nl. Exit without save" << std::endl;
	do
	{
		std::cout << "\nEnter key: ";
		std::cin >> menu_count;
		if (menu_count < 'a' || menu_count > 'l')
		{
			std::cout << "try again. a-l\t";
		}
	} while (menu_count < 'a' || menu_count > 'l');
	return menu_count;
}

bool select(Library& obj, char menu_count)
{
	std::string book = "";
	std::string reader = "";

	switch (menu_count)
	{
	case 'a':
		std::cout << "\nEnter name book - ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, book);
		obj.createBook(book);
		return true;
	case 'b':
		std::cout << "\nEnter name reader - ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, reader);
		obj.createReader(reader);
		return true;
	case 'c':
		obj.showBook();
		return true;
	case 'd':
		obj.showReader();
		return true;
	case 'e':
		std::cout << "\nEnter name reader - ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, reader);

		std::cout << "\nEnter name book - ";
		std::getline(std::cin, book);

		obj.giveBook(reader, book);
		return true;
	case 'f':
		std::cout << "\nEnter name reader - ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, reader);

		std::cout << "\nEnter name book - ";
		std::getline(std::cin, book);

		obj.takeBook(reader, book);
		return true;
	case 'g':
		system("cls");
		return true;
	case 'h':
		std::cout << "\nEnter name reader - ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, reader);
		obj.deleteReader(reader);
		return true;
	case 'i':
		std::cout << "\nEnter name book - ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, book);
		obj.deleteBook(book);
		return true;
	case 'j':
		obj.saveData();
		return true;
	case 'k':
		obj.saveData();
		std::cout << "Work finish";
		return false;
	case 'l':
		std::cout << "Work finish";
		return false;
	default:
		return true;
	}
}