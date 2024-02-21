#ifndef BOOKDATA_H_
#define BOOKDATA_H_

#include <string>
#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

//CLASS - BOOKDATA
class BookData
{
	private:
		string bookTitle;
		string isbn;
		string author;
		string publisher;

	public:
	/********************************************************************************
	* SETTERS
	********************************************************************************/
		void setTitle(string x)
		{
			bookTitle = x;
		}

		void setIsbn(string x)
		{
			isbn = x;
		}

		void setAuthor(string x)
		{
			author = x;
		}

		void setPub(string x)
		{
			publisher = x;
		}
		
		
		
	/********************************************************************************
	* GETTERS
	********************************************************************************/
		string getTitle() const
		{
			return bookTitle;
		}

		string getIsbn() const
		{
			return isbn;
		}

		string getAuthor() const
		{
			return author;
		}

		string getPub() const
		{
			return publisher;
		}
		
		
		
	/********************************************************************************
	* CONSTRUCTORS
	********************************************************************************/
		/*********************
		 * FUNCTION: BookData
		 * ------------------
		 * - sets all BookData variables to nothing
		 * - receives nothing
		 * RETURNS: nothing
		 ********************/
		BookData()
		{
			setTitle("not set");
			setIsbn("not set");
			setAuthor("not set");
			setPub("not set");
		}
		
		/*********************
		 * FUNCTION: BookData
		 * ------------------
		 * - sets all BookData variables to the arguments
		 * - receives 4 strings
		 * RETURNS: nothing
		 ********************/
		BookData(string title, string isbn, string author, string publisher)
		{
			setTitle(title);
			setIsbn(isbn);
			setAuthor(author);
			setPub(publisher);
		}
		

	/********************************************************************************
	* DESTRUCTOR
	********************************************************************************/
		~BookData(void)
		{
			//cout << "OBJECT IS BEING DELETED.\n";
		}

	/********************************************************************************
	* PRINT
	********************************************************************************/
		virtual void print()
		{
			cout << "Title: "     << getTitle()  << endl;
			cout << "ISBN: "      << getIsbn()   << endl;
			cout << "Author: "    << getAuthor() << endl;
			cout << "Publisher: " << getPub()    << endl;
		}


	/********************************************************************************
	* OVERLOADED OPERATORS
	********************************************************************************/
	bool operator>=(const BookData& other_Book) const {
		bool found = false;

		if (this != &other_Book) { //avoid self evaluation
			if (this != &other_Book) { //avoid self evaluation

				if ((strcmp(this->isbn.c_str(),
						other_Book.isbn.c_str())) >= 0) {
					found = true;
				}

			}
		}

		return found;
	}




	bool operator==(const BookData& other_Book) const {
		bool found = false;

		if (this != &other_Book) { //avoid self evaluation
			if (this != &other_Book) { //avoid self evaluation

				if ((strcmp(this->isbn.c_str(), other_Book.isbn.c_str()))
						== 0) {
					found = true;
				}

			}
		}

		return found;
	}

	bool operator!=(const BookData& other_Book) const {

		bool found = false;

		if (this != &other_Book) { //avoid self evaluation
			if (this != &other_Book) { //avoid self evaluation

				if ((strcmp(this->isbn.c_str(), other_Book.isbn.c_str()))
						== 0) {
					found = true;
				}

			}
		}

		return !found;
	}


	friend ostream& operator<<(ostream& osObject, const BookData& c) {
		osObject << left << setfill(' ') << " " << setw(29)
				<< c.bookTitle.substr(0, 28) << setw(11) << c.isbn << setw(15)
				<< c.author.substr(0, 14) << setw(11)
				<< c.publisher.substr(0, 14) << endl;
		return osObject;
	}
};

#endif
