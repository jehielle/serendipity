// ----------------------------------------------------------------------------
// File name: main.cpp                                                        -
// Project name: Serendipity                                                  -
// ----------------------------------------------------------------------------
// Creator's name and email: Jehielle David jdavid21@saddleback.edu           -
// Course-Section: CS1B                                                       -
// Creation Date: 4/26/18                                                     -
// Date of Last Modification: 5/08/18                                         -
// ----------------------------------------------------------------------------
// Purpose: Serendipity                                                       -
// ----------------------------------------------------------------------------
// Algorithm:                                                                 -
// Step 1: Make various instructions for the computer to help it create a     -
//         book.                                                              -
// Step 2: Make the book and print it out.                                    -
// Step 3: Make a transaction object and print it out.                        -
// ----------------------------------------------------------------------------
// -                          DATA DICTIONARY                                 -
// - CONSTANTS                                                                -
// -                                                                          -
// - NAME              DATA TYPE    VALUE                                     -
// - ---------------   ----------   --------                                  -
// -                                                                          -
// - VARIABLES                                                                -
// -                                                                          -
// - NAME              DATA TYPE    INITIAL VALUE                             -
// - ---------------   ----------   -------------                             -
// ----------------------------------------------------------------------------
#include "bookdata.h"
#include "inventoryBook.h"
#include "soldBook.h"

#include "linkedList.h"
#include "orderedLinkedList.h"

#include<cstdlib>
#include<fstream>
#include<ctime>
#include<limits>

//DATE AND TIME
const string dateAndTime()
{
	time_t  t = time(0);
	struct  tm  tmstruct;
	char    s[80];
	tmstruct = *localtime(&t);

	strftime(s, 80, "%m/%d/%Y %X", &tmstruct);

	return s;
}

/***************************************
 * PROTOTYPES
 ***************************************/

//CASHIER
void cashier(orderedLinkedList<InventoryBook> &tList, orderedLinkedList<InventoryBook> &qohList,
			 orderedLinkedList<InventoryBook> &wpList, orderedLinkedList<InventoryBook> &daList);

//INVENTORY MENU
void invmenu(orderedLinkedList<InventoryBook> &tList, orderedLinkedList<InventoryBook> &qohList,
			orderedLinkedList<InventoryBook> &wpList, orderedLinkedList<InventoryBook> &daList);
void lookUpBook(orderedLinkedList<InventoryBook> tList);
void addBook(orderedLinkedList<InventoryBook> &tList, orderedLinkedList<InventoryBook> &qohList,
		     orderedLinkedList<InventoryBook> &wpList, orderedLinkedList<InventoryBook> &daList);
void editBook(orderedLinkedList<InventoryBook> &tList, orderedLinkedList<InventoryBook> &qohList,
			  orderedLinkedList<InventoryBook> &wpList, orderedLinkedList<InventoryBook> &daList);
void deleteBook(orderedLinkedList<InventoryBook> &tList, orderedLinkedList<InventoryBook> &qohList,
				orderedLinkedList<InventoryBook> &wpList, orderedLinkedList<InventoryBook> &daList);

//REPORTS
void reports(orderedLinkedList<InventoryBook> tList, orderedLinkedList<InventoryBook>  qohList, 
			 orderedLinkedList<InventoryBook> wpList, orderedLinkedList<InventoryBook> daList);
void repListing(orderedLinkedList<InventoryBook> tList);
void repWholesale(orderedLinkedList<InventoryBook> tList);
void repRetail(orderedLinkedList<InventoryBook> tList);
void repQty(orderedLinkedList<InventoryBook> qohList);
void repCost(orderedLinkedList<InventoryBook> wpList);
void repAge(orderedLinkedList<InventoryBook> daList);

//BOOK INFO
void BookInfo(orderedLinkedList<InventoryBook> tList, linkedListIterator<InventoryBook> myIterator);

//WRITING DATA
void WriteData(orderedLinkedList<InventoryBook> tList);
void WriteSoldBook(orderedLinkedList<SoldBook> tList);

int main()
{
	ofstream fout; //WRITE INTO FILE
	ifstream fin; //READ FROM FILE

	string titleM;
	string isbnM;
	string authorM;
	string publisherM;
	string dateAddedM;
	int    qtyOnHandM;
	double wholesaleM;
	double retailM;

	int choice;
	
	InventoryBook *book;

	orderedLinkedList<InventoryBook> tList;   //title list
	tList.initializeList();

	orderedLinkedList<InventoryBook> qohList; //qty o/h list
	qohList.initializeList();
	
	orderedLinkedList<InventoryBook> wpList;  //wholesale price list
	wpList.initializeList();
	
	orderedLinkedList<InventoryBook> daList;  //date added list
	daList.initializeList();

	//OPEN FILE
	fin.open("database.txt");

	do
	{
		//GET INFO FROM FILE
		getline(fin, titleM);
		getline(fin, isbnM);
		getline(fin, authorM);
		getline(fin, publisherM);
		getline(fin, dateAddedM);
		fin >> qtyOnHandM;
		fin >> wholesaleM;
		fin >> retailM;
		fin.ignore(numeric_limits<streamsize>::max(), '\n');

		InventoryBook *newBook = new InventoryBook(titleM, isbnM, authorM, publisherM, dateAddedM, qtyOnHandM, wholesaleM, retailM);
		(*newBook).setSortCode(0);
		tList.insert(*newBook);
		(*newBook).setSortCode(1);
		qohList.insert(*newBook);
		(*newBook).setSortCode(2);
		wpList.insert(*newBook);
		(*newBook).setSortCode(3);
		daList.insert(*newBook);
	}while(!fin.eof());

	//CLOSE FILE
	fin.close();

	system("CLS");

	//DO WHILE - repeat until user exits
	do
	{
		cout << "*****************************************" << endl;
		cout << "*        SERENDIPITY BOOKSELLERS        *" << endl;
		cout << "*               MAIN MENU               *" << endl;
		cout << "*****************************************" << endl;
		cout << "* <1> Cashier Module                    *" << endl;
		cout << "* <2> Inventory Database Module         *" << endl;
		cout << "* <3> Report Module                     *" << endl;
		cout << "* <4> Exit                              *" << endl;
		cout << "*****************************************" << endl;
		cout << " > CHOICE: ";
		
		//CHECKING FOR INVALID INPUT
		do
		{
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.clear();
			
			if(choice != 1 && choice != 2 && choice != 3 && choice != 4)
			{
				cout << "\n\n*** ERROR - PLEASE INPUT 1-4 ***\n\n";
			}
		}while(choice != 1 && choice != 2 && choice != 3 && choice != 4);
		
		system("CLS");

		//SWITCH
		switch(choice)
		{
			case 1: cashier(tList, qohList, wpList, daList);
			break;
			
			case 2: invmenu(tList, qohList, wpList, daList);
			break;
			
			case 3: reports(tList, qohList, wpList, daList);
			break;
		}
	}while(choice != 4);
	
	return 0;
}





/*********************************************************************
* 
* FUNCTIONS
* 
*********************************************************************/
/*********************************************************************
* FUNCTION - CASHIER
*********************************************************************/
void cashier(orderedLinkedList<InventoryBook> &tList, orderedLinkedList<InventoryBook> &qohList,
			 orderedLinkedList<InventoryBook> &wpList, orderedLinkedList<InventoryBook> &daList)
{
	string bookSearch;
	string bookSearchedFor;
	string isbnSearch;
	size_t foundTitle;
	int    tempQtyOnHand;
	int    tempQtySold;
	int    userQty = 0;
	double subtotal = 0.00;
	char   choice;

	linkedListIterator<InventoryBook> myIterator;
	linkedListIterator<SoldBook> receiptIterator;
	orderedLinkedList<SoldBook> receipt;
	receipt.initializeList();

	InventoryBook *newBook = new InventoryBook;
	SoldBook *receiptBook  = new SoldBook;

	do
	{//always need .begin(), .end(), and ++ with iterator
		for (myIterator = tList.begin(); myIterator != tList.end(); ++myIterator)
		{
			receiptBook->setTitle((*myIterator).getTitle());
			receiptBook->setIsbn((*myIterator).getIsbn());
			receiptBook->setAuthor((*myIterator).getAuthor());
			receiptBook->setPub((*myIterator).getPub());
			receiptBook->setDateAdded((*myIterator).getDateAdded());
			receiptBook->setQtyOnHand((*myIterator).getQtyOnHand());
			receiptBook->setWholesale((*myIterator).getWholesale());
			receiptBook->setRetail((*myIterator).getRetail());
			(*receiptBook).setSortCode(0);
			receipt.insert(*receiptBook);
		}

		do
		{
			cout << "SERENDIPITY BOOKSELLERS" << endl;
			cout << "    CASHIER MODULE     " << endl;

			cout << "Date: " << dateAndTime();
			cout << endl;

			cout << "\n>> BOOK SEARCH <<\n";
			cout << "Please enter either the book's ISBN or title to search for the book: ";;
			getline(cin, bookSearch);

			//TO STOP CASE SENSITIVITY
			for(unsigned int index = 0; index < bookSearch.length(); index++)
			{
				if(isupper(bookSearch[index]))
				{
					bookSearch[index] = tolower(bookSearch[index]);
				}
			}

			receiptIterator = receipt.begin();
			do
			{
				//TO STOP CASE SENSITIVITY
				bookSearchedFor = (*receiptIterator).getTitle();
				for(unsigned int index = 0; index < bookSearchedFor.length(); index++)
				{
					if(isupper(bookSearchedFor[index]))
					{
						bookSearchedFor[index] = tolower(bookSearchedFor[index]);
					}
				}
				isbnSearch = (*receiptIterator).getIsbn();
				for(unsigned int index = 0; index < isbnSearch.length(); index++)
				{
					if(isupper(isbnSearch[index]))
					{
						isbnSearch[index] = tolower(isbnSearch[index]);
					}
				}

				// find title from partial search term
				foundTitle = bookSearchedFor.find(bookSearch);
				// if title or isbn is found
				if(foundTitle != string::npos || isbnSearch == bookSearch)
				{
					//TITLE
					if(foundTitle != string::npos)
					{
						cout << "RESULT: >" << (*receiptIterator).getTitle() << endl;
						cout << "View this book? (Y/N): ";
					}

					//ISBN
					if(isbnSearch == bookSearch)
					{
						cout << "RESULT: >" << (*receiptIterator).getIsbn() << endl;
						cout << "View this book? (Y/N): ";
					}

					cin >> choice;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				//IF USER DOES WANT TO VIEW BOOK
				if(toupper(choice) == 'Y')
				{
					cout << endl;
					(*receiptIterator).SoldBook::print();
					cout << endl;

					cout << "Add " << (*receiptIterator).getTitle() << " to cart? (Y/N): ";
					cin >> choice;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					//IF USER DOES WANT TO ADD BOOK TO CART
					if(toupper(choice == 'Y'))
					{
						//IF BOOK IS NOT IN STOCK
						if((*receiptIterator).getQtyOnHand() == 0)
						{
							cout << "\n*** ERROR - BOOK IS SOLD OUT ***\n\n";
							++receiptIterator;
							break;
						}
						//IF BOOK IS, IN FACT, IN STOCK
						cout << "Quantity of Book (Enter 0 to cancel): ";
						cin  >> userQty;
						while (cin.fail() || (*receiptIterator).getQtyOnHand() < userQty || userQty <= 0)
						{
							if((*receiptIterator).getQtyOnHand() < userQty)
							{
								cout << "\n*** ERROR. THERE IS ONLY " << (*receiptIterator).getQtyOnHand() << " CURRENTLY ON HAND. ***\n\n";
								cout << "REENTER QUANTITY: ";
								cin  >> userQty;
							}
							if(cin.fail() || userQty < 0)
							{
								cout << "\n*** ERROR. REENTER QUANTITY. ***\n\n";
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								cin >> userQty;
							}
							else if (userQty == 0)
							{
								break;
							}
						}//END WHILE FOR CHECKING THE QUANTITY

						if(userQty == 0)
						{
							cout << "\n*** DID NOT ADD BOOK TO CART. ***\n\n";
							receiptIterator = receipt.end();
							break;
						}
						//OTHERWISE...
						cout << "\n*** BOOK ADDED TO CART. ***\n\n";

						//CHANGING QUANTITY OF BOOKS
						tempQtySold   = (*receiptIterator).getQtySold() + userQty;
						tempQtyOnHand = (*receiptIterator).getQtyOnHand() - userQty;

						receiptBook->setTitle((*receiptIterator).getTitle());
						receiptBook->setIsbn((*receiptIterator).getIsbn());
						receiptBook->setAuthor((*receiptIterator).getAuthor());
						receiptBook->setPub((*receiptIterator).getPub());
						receiptBook->setDateAdded((*receiptIterator).getDateAdded());
						receiptBook->setQtyOnHand(tempQtyOnHand);
						receiptBook->setWholesale((*receiptIterator).getWholesale());
						receiptBook->setRetail((*receiptIterator).getRetail());
						receiptBook->setQtySold(tempQtySold);
						receiptBook->setTax((*receiptIterator).getRetail(), tempQtySold);

						receipt.deleteNode(*receiptIterator);

						(*receiptBook).setSortCode(0);
						receipt.insert(*receiptBook);
						break;

					}//END IF USER ADDS BOOK TO CART
					else
					{
						break;
						++receiptIterator;
					}
				}//END IF USER WANTS TO VIEW BOOK
				else
				{
					//IF USER DOES NOT WANT TO ADD BOOK AFTER ALL
					system("CLS");

					cout << "SERENDIPITY BOOKSELLERS" << endl;
					cout << "    CASHIER MODULE     " << endl;

					cout << "Date: " << dateAndTime();
					cout << endl;

					cout << "\n>> BOOK SEARCH <<\n";
					cout << "Please enter either the book's ISBN or title to search for the book: ";;
					getline(cin, bookSearch);

					++receiptIterator;
					continue;
				}
			} while (receiptIterator != receipt.end());

			// IF BOOK NOT FOUND
			if (receiptIterator == receipt.end() || (foundTitle == string::npos && (*receiptIterator).getIsbn() == bookSearch)
				|| toupper(choice) != 'Y')
			{
				cout << "\n\n*** BOOK WAS NOT FOUND. ***\n\n";
			}

			//EXIT MENU
			cout << "<C>ontinue Shopping"   << endl;
			cout << "<P>roceed to Checkout" << endl;
			cout << "<F>orget this ever happened and exit cashier module" << endl;
			do
			{
				cout << "CHOICE";
				cin >> choice;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				switch(toupper(choice))
				{
					case 'C'://CONTINUE SHOPPING
					break;

					case 'P'://PROCEED TO CHECKOUT
					break;

					case 'F'://FORGET
					cout << "Are you sure you want to exit? (Y/N): ";
					cin >> choice;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					if (toupper(choice) == 'Y')
					{
						break;
					}
					else
					{
						choice = 'C';
					}
					break;
				}
			}while(choice == '0');//MENU CHOICE
		}while(toupper(choice) == 'C');//CONTINUE SHOPPING OR NOT?

		//PRINTING RECEIPT
		if(toupper(choice) == 'P')
		{
			myIterator = tList.begin();
			for(receiptIterator = receipt.begin(); receiptIterator != receipt.end(); ++receiptIterator)
			{
				tList.deleteNode(*myIterator);
				qohList.deleteNode(*myIterator);
				wpList.deleteNode(*myIterator);
				daList.deleteNode(*myIterator);
				++myIterator;
			}

			for (receiptIterator = receipt.begin(); receiptIterator != receipt.end(); ++receiptIterator)
			{
				//NEW INFO WRITTEN
				newBook->setTitle((*receiptIterator).getTitle());
				newBook->setIsbn((*receiptIterator).getIsbn());
				newBook->setAuthor((*receiptIterator).getAuthor());
				newBook->setPub((*receiptIterator).getPub());
				newBook->setDateAdded((*receiptIterator).getDateAdded());
				newBook->setQtyOnHand((*receiptIterator).getQtyOnHand());
				newBook->setWholesale((*receiptIterator).getWholesale());
				newBook->setRetail((*receiptIterator).getRetail());

				(*newBook).setSortCode(0);
				tList.insert(*newBook);
				(*newBook).setSortCode(1);
				qohList.insert(*newBook);
				(*newBook).setSortCode(2);
				wpList.insert(*newBook);
				(*newBook).setSortCode(3);
				daList.insert(*newBook);
			}
			WriteData(tList);
			WriteSoldBook(receipt);

			system("PAUSE");
			system("CLS");

			//SALES SLIP
			cout << "SERENDIPITY BOOKSELLERS" << endl;
			cout << "    CASHIER MODULE     " << endl;

			cout << "Date: " << dateAndTime();
			cout << endl;

			cout << left;
			cout << setw(5)  << "Qty";
			cout << setw(15) << "ISBN";
			cout << setw(25) << "Title";
			cout << setw(12) << "Price";
			cout << 			"Total";
			cout << endl;

			cout << "_________________________________________________________________";
			cout << endl;

			for (receiptIterator = receipt.begin(); receiptIterator != receipt.end(); ++receiptIterator)
			{
				if ((*receiptIterator).getQtySold() > 0)
				{
					cout << left;
					cout << fixed << setprecision(2);

					cout << setw(5)  << (*receiptIterator).getQtySold();
					cout << setw(15) << (*receiptIterator).getIsbn();
					cout << setw(25) << ((*receiptIterator).getTitle()).substr(0,23);
					cout <<      "$";
					cout << setw(11) << (*receiptIterator).getRetail();
					cout <<      "$";
					cout << right;
					cout << setw(6)  << ((*receiptIterator).getRetail() * double((*receiptIterator).getQtySold()));
					cout << endl << endl;
				}
			}

			//CALC - SUBTOTAL
			for (receiptIterator = receipt.begin(); receiptIterator != receipt.end(); ++receiptIterator)
			{
				if ((*receiptIterator).getQtySold() > 0)
				{
					subtotal = subtotal + ((*receiptIterator).getRetail() * double((*receiptIterator).getQtySold()));
				}
			}

			//CALC & OUT - TOTALS
			cout << endl << endl;
			cout << "Subtotal" << "$" << subtotal;
			cout << "Tax"      << "$" << subtotal * 0.06;
			cout << "Total"    << "$" << (subtotal * 0.06) + subtotal ;
			cout << endl;

			cout << "\nThank you for Shopping at Serendipity!\n\n";

			cout << "Process another transaction (Y/N)?: ";
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}//END PRINTING THE RECEIPT
		else
		{
			break;
		}
	} while (toupper(choice) == 'Y');

	system("PAUSE");

}

/*********************************************************************
* FUNCTION - INVMENU
*********************************************************************/
void invmenu(orderedLinkedList<InventoryBook> &tList, orderedLinkedList<InventoryBook> &qohList,
			orderedLinkedList<InventoryBook> &wpList, orderedLinkedList<InventoryBook> &daList)
{
	int choice;
	
	choice = 0;
	
	do
	{
		cout << "*****************************************"  << endl;
		cout << "*        SERENDIPITY BOOKSELLERS        *"  << endl;
		cout << "*          INVENTORY DATABASE           *"  << endl;
		cout << "*****************************************"  << endl;
		cout << "* <1> Look Up a Book                    *"  << endl;
		cout << "* <2> Add a Book                        *"  << endl;
		cout << "* <3> Edit a Book\'s Record              *" << endl;
		cout << "* <4> Delete a Book                     *"  << endl;
		cout << "* <5> Return to the Main Menu           *"  << endl;
		cout << "*****************************************"  << endl;
		cout << " > CHOICE: ";
		
		//CHECKING FOR INVALID INPUT
		do
		{
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.clear();
			
			if(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5)
			{
				cout << "\n\n*** ERROR - PLEASE INPUT 1-5 ***\n\n";
			}
		}while(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5);
		
		system("CLS");
		
		//SWITCH
		switch(choice)
		{
			case 1: lookUpBook(tList);
			break;
			
			case 2: addBook(tList, qohList, wpList, daList);
			break;
			
			case 3: editBook(tList, qohList, wpList, daList);
			break;
			
			case 4: deleteBook(tList, qohList, wpList, daList);
			break;
		}
		
		system("PAUSE");
		system("CLS");
		
	}while(choice != 5);
}

/*********************************************************************
* FUNCTION - LOOK UP BOOK
*********************************************************************/
void lookUpBook(orderedLinkedList<InventoryBook> tList)
{
	linkedListIterator<InventoryBook> myIterator;
	int    choice;
	string search;
	string bookSearchedFor;
	bool   found;
	char   yesOrNo;

	found = false;
	
	myIterator = tList.begin();

	cout << ">>> BOOK LOOK UP <<<";
	cout << endl << endl;
	cout << "> Search by title or ISBN: " << endl << endl;
	cout << "  <1> Search by title"       << endl;
	cout << "  <2> Search by ISBN"        << endl;

	//CHECK FOR INVALID INPUT
	do
	{
		cout << "CHOICE: ";
		cin  >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if(choice != 1 && choice != 2)
		{
			cout << "\n*** ERROR - INPUT EITHER 1 OR 2 ***\n\n";
		}
	}while(choice != 1 && choice != 2);

	//SWITCH STATEMENT
	switch(choice)
	{
		case 1: //SEARCHING BY TITLE
			cout << ">Enter title of book to be searched: ";
			getline(cin, search);
		break;

		case 2: //SEARCHING BY ISBN
			cout << ">Enter ISBN of book to be searched: ";
			getline(cin, search);
		break;
	}

	//IF THE SEARCHED VALUE IS IN CAPS
	for(unsigned int index = 0; index < search.length(); index++)
	{
		if (isupper(search[index]))
		{
			search[index] = tolower(search[index]);
		}
	}

	cout << "SEARCHING..." << endl << endl;

	//BEGIN SEARCH USING ITERATOR
	while(myIterator != tList.end() && !found)
	{
		if(choice == 1) //SEARCH BY TITLE
		{
			bookSearchedFor = (*myIterator).getTitle();
			for(unsigned int index = 0; index < bookSearchedFor.length(); index++)
			{
				if (isupper(bookSearchedFor[index]))
				{
					bookSearchedFor[index] = tolower(bookSearchedFor[index]);
				}
			}

			if(bookSearchedFor.find(search) != string::npos)
			{
				cout << "BOOK FOUND: " << bookSearchedFor << endl;
				cout << "Is this the book you want? (Y/N): ";
				cin.get(yesOrNo);
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				switch(toupper(yesOrNo))
				{
					case 'Y': found = true;
							  cout << endl;
							  BookInfo(tList, myIterator);
					break;

					case 'N': found = false;
					break;
				}
			}
		}//END SEARCH BY TITLE
		else if(choice == 2) //SEARCH BY ISBN
		{
			if((*myIterator).getIsbn().find(search) != string::npos)
			{
				cout << "BOOK FOUND: " << (*myIterator).getTitle() << endl;
				cout << "Is this the book you want? (Y/N): ";
				cin.get(yesOrNo);
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				switch(toupper(yesOrNo))
				{
					case 'Y': found = true;
							  cout << endl;
							  BookInfo(tList, myIterator);
					break;

					case 'N': found = false;
					break;
				}
			}
		}//END SEARCH BY ISBN
		++myIterator;
	}//END WHILE

}

/*********************************************************************
* FUNCTION - ADD BOOK
*********************************************************************/
void addBook(orderedLinkedList<InventoryBook> &tList, orderedLinkedList<InventoryBook> &qohList,
			 orderedLinkedList<InventoryBook> &wpList, orderedLinkedList<InventoryBook> &daList)
{
	string tempTitle     = "EMPTY";
	string tempIsbn      = "EMPTY";
	string tempAuthor    = "EMPTY";
	string tempPub       = "EMPTY";
	string tempDate      = "EMPTY";
	int    tempQtyOnHand = 0;
	double tempWholesale = 0.0;
	double tempRetail    = 0.0;

	int    choice;
	InventoryBook *newBook = new InventoryBook;

	cout << "SERENDIPITY BOOKSELLERS" << endl;
	cout << "        ADD BOOK       " << endl;
	cout <<                              endl << endl;
	cout << " CURRENT BOOK COUNT: "   << tList.length();
	cout <<                              endl << endl;


	cout << left;
	cout << setw(36) << " <1>  Enter Book Title"              << "> --" << tempTitle;
	cout << endl;
	cout << setw(36) << " <2>  Enter ISBN"                    << "> --" << tempIsbn;
	cout << endl;
	cout << setw(36) << " <3>  Enter Author"                  << "> --" << tempAuthor;
	cout << endl;
	cout << setw(36) << " <4>  Enter Publisher"               << "> --" << tempPub;
	cout << endl;
	cout << setw(36) << " <5>  Enter Date Added (mm/dd/yyyy)" << "> --" << tempDate;
	cout << endl;
	cout << setw(36) << " <6>  Enter Quantity On Hand"        << "> --" << tempQtyOnHand;
	cout << endl;
	cout << setw(36) << " <7>  Enter Wholesale Cost"          << "> --$"<< tempWholesale;
	cout << endl;
	cout << setw(36) << " <8>  Enter Retail Price"            << "> --$"<< tempRetail;
	cout << endl;
	cout << setw(36) << " <9>  Save Book to Database";
	cout << endl;
	cout << setw(36) << " <0>  Return to Inventory Menu";
	cout << endl;

	cout << ">Choice (0-9): ";
	cin  >> choice;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.clear();

	switch(choice)
	{
		case 1:
		cout << "Book Title >";
		getline(cin, tempTitle);
		break;

		case 2:
		cout << "ISBN >";
		getline(cin, tempIsbn);
		break;

		case 3:
		cout << "Author >";
		getline(cin, tempAuthor);
		break;

		case 4:
		cout << "Publisher >";
		getline(cin, tempPub);
		break;

		case 5:
		cout << "Date >";
		getline(cin, tempDate);
		break;

		case 6:
		cout << "Quantity >";
		cin  >> tempQtyOnHand;
		while (cin.fail())
		{
			cout << "\n***ERROR. PLEASE ENTER A VALID NUMBER.***\n\n";
			cout << "Quantity >";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.clear();
			cin >> tempQtyOnHand;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		break;

		case 7:
		cout << "Wholesale Price >";
		cin  >> tempWholesale;
		while (cin.fail())
		{
			cout << "\n***ERROR. PLEASE ENTER A VALID NUMBER.***\n\n";
			cout << "Wholesale Price >";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.clear();
			cin >> tempWholesale;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		break;

		case 8:
		cout << "Retail Price >";
		cin  >> tempRetail;
		while (cin.fail())
		{
			cout << "\n***ERROR. PLEASE ENTER A VALID NUMBER.***\n\n";
			cout << "Retail Price >";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.clear();
			cin >> tempRetail;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		break;

		case 9:
		newBook->setTitle(tempTitle);
		newBook->setIsbn(tempIsbn);
		newBook->setAuthor(tempAuthor);
		newBook->setPub(tempPub);
		newBook->setDateAdded(tempDate);
		newBook->setQtyOnHand(tempQtyOnHand);
		newBook->setWholesale(tempWholesale);
		newBook->setRetail(tempRetail);

		(*newBook).setSortCode(0);
		tList.insert(*newBook);
		(*newBook).setSortCode(1);
		qohList.insert(*newBook);
		(*newBook).setSortCode(2);
		wpList.insert(*newBook);
		(*newBook).setSortCode(3);
		daList.insert(*newBook);

		WriteData(tList);

		//RESET EMPTY VALUES
		tempTitle     = "EMPTY";
		tempIsbn      = "EMPTY";
		tempAuthor    = "EMPTY";
		tempPub       = "EMPTY";
		tempDate      = "EMPTY";
		tempQtyOnHand = 0;
		tempWholesale = 0.0;
		tempRetail    = 0.0;
		break;
	}	// end switch


}

/*********************************************************************
* FUNCTION - EDIT BOOK
*********************************************************************/
void editBook(orderedLinkedList<InventoryBook> &tList, orderedLinkedList<InventoryBook> &qohList,
			  orderedLinkedList<InventoryBook> &wpList, orderedLinkedList<InventoryBook> &daList)
{
	linkedListIterator<InventoryBook> myIterator;
	string search;
	string bookSearchedFor;
	bool   found;
	char   yesOrNo;     //is this the book they were looking for?
	char   editYesOrNo; //is this the book they want to edit?
	size_t titleSearch;
	int    editChoice;

	string tempTitle;
	string tempIsbn;
	string tempAuthor;
	string tempPub;
	string tempDate;
	int    tempQtyOnHand;
	double tempWholesale;
	double tempRetail;

	InventoryBook *newBook = new InventoryBook;
	found = false;

	cout << "SERENDIPITY BOOKSELLERS" << endl;
	cout << "       EDIT BOOK       " << endl << endl;

	cout << ">Enter title of book to be searched: ";
	getline(cin, search);

	//IF THE SEARCHED VALUE IS IN CAPS
	for(unsigned int index = 0; index < search.length(); index++)
	{
		if (isupper(search[index]))
		{
			search[index] = tolower(search[index]);
		}
	}

	cout << "SEARCHING..." << endl << endl;

	myIterator = tList.begin();
	//SEARCH BY TITLE
	while(myIterator != tList.end() && !found)
	{
		bookSearchedFor = (*myIterator).getTitle();
		for(unsigned int index = 0; index < bookSearchedFor.length(); index++)
		{
			if (isupper(bookSearchedFor[index]))
			{
				bookSearchedFor[index] = tolower(bookSearchedFor[index]);
			}
		}

		titleSearch = bookSearchedFor.find(search);
		if(titleSearch != string::npos)
		{
			cout << "BOOK FOUND: " << bookSearchedFor << endl;
			cout << "Is this the book you want? (Y/N): ";
			cin.get(yesOrNo);
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch(toupper(yesOrNo))
			{
				case 'Y': found = true;
						  cout << endl;
						  BookInfo(tList, myIterator);
						  cout << endl;
						  cout << "Is this the book you want to EDIT? (Y/N): ";
						  cin.get(editYesOrNo);
						  cin.ignore(numeric_limits<streamsize>::max(), '\n');

						  tempTitle     = (*myIterator).getTitle();
						  tempIsbn      = (*myIterator).getIsbn();
						  tempAuthor    = (*myIterator).getAuthor();
						  tempPub       = (*myIterator).getPub();
						  tempDate      = (*myIterator).getDateAdded();
						  tempQtyOnHand = (*myIterator).getQtyOnHand();
						  tempWholesale = (*myIterator).getWholesale();
						  tempRetail    = (*myIterator).getRetail();

				break;

				case 'N': found = false;
				break;
			}
		}
	++myIterator;
	}//END WHILE

	//IF BOOK NOT FOUND
	if(myIterator == tList.end() || titleSearch == string::npos)
	{
		cout << "\nBOOK NOT FOUND.\n\n";
		system("PAUSE");
	}

	//IF THEY DO WANT TO EDIT THE BOOK
	if(toupper(yesOrNo) == 'Y')
	{
		system("PAUSE");
		system("CLS");

		cout << "SERENDIPITY BOOKSELLERS" << endl;
		cout << "       EDIT BOOK       " << endl << endl;

		//OUTPUTTING MENU
		cout << left;
		cout << setw(36) << " <1>  Enter Book Title"              << "> --" << tempTitle;
		cout << endl;
		cout << setw(36) << " <2>  Enter ISBN"                    << "> --" << tempIsbn;
		cout << endl;
		cout << setw(36) << " <3>  Enter Author"                  << "> --" << tempAuthor;
		cout << endl;
		cout << setw(36) << " <4>  Enter Publisher"               << "> --" << tempPub;
		cout << endl;
		cout << setw(36) << " <5>  Enter Date Added (mm/dd/yyyy)" << "> --" << tempDate;
		cout << endl;
		cout << setw(36) << " <6>  Enter Quantity On Hand"        << "> --" << tempQtyOnHand;
		cout << endl;
		cout << setw(36) << " <7>  Enter Wholesale Cost"          << "> --$"<< tempWholesale;
		cout << endl;
		cout << setw(36) << " <8>  Enter Retail Price"            << "> --$"<< tempRetail;
		cout << endl;
		cout << setw(36) << " <9>  Save Book to Database";
		cout << endl;
		cout << setw(36) << " <0>  Return to Inventory Menu";
		cout << endl;
		cout << endl     << endl;

		cout << setw(23) << "Choice (1-9): ";
		cin  >> editChoice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.clear();

		switch(editChoice)
		{
			case 1:
			cout << "Book Title >";
			getline(cin, tempTitle);
			break;

			case 2:
			cout << "ISBN >";
			getline(cin, tempIsbn);
			break;

			case 3:
			cout << "Author >";
			getline(cin, tempAuthor);
			break;

			case 4:
			cout << "Publisher >";
			getline(cin, tempPub);
			break;

			case 5:
			cout << "Date >";
			getline(cin, tempDate);
			break;

			case 6:
			cout << "Quantity >";
			cin  >> tempQtyOnHand;
			while(cin.fail() || tempQtyOnHand < 0)
			{
				cout << "\n***ERROR. PLEASE ENTER A VALID NUMBER.***\n\n";
				cout << "Quantity >";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> tempQtyOnHand;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			break;

			case 7:
			cout << "Wholesale Cost >";
			cin  >> tempWholesale;
			while(cin.fail() || tempWholesale < 0)
			{
				cout << "\n***ERROR. PLEASE ENTER A VALID NUMBER.***\n\n";
				cout << "Quantity >";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> tempWholesale;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			break;

			case 8:
			cout << "Retail Price >";
			cin  >> tempRetail;
			while(cin.fail() || tempRetail < 0)
			{
					cout << "\n***ERROR. PLEASE ENTER A VALID NUMBER.***\n\n";
					cout << "Quantity >";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> tempRetail;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			break;

			case 9:
			// delete old book with previous info
			tList.deleteNode(*myIterator);
			qohList.deleteNode(*myIterator);
			wpList.deleteNode(*myIterator);
			daList.deleteNode(*myIterator);
			// add information to new book
			newBook->setTitle(tempTitle);
			newBook->setIsbn(tempIsbn);
			newBook->setAuthor(tempAuthor);
			newBook->setPub(tempPub);
			newBook->setDateAdded(tempDate);
			newBook->setQtyOnHand(tempQtyOnHand);
			newBook->setWholesale(tempWholesale);
			newBook->setRetail(tempRetail);
			// insert new book to lists
			(*newBook).setSortCode(0);
			tList.insert(*newBook);
			(*newBook).setSortCode(1);
			qohList.insert(*newBook);
			(*newBook).setSortCode(2);
			wpList.insert(*newBook);
			(*newBook).setSortCode(3);
			daList.insert(*newBook);

			WriteData(tList);
			cout << "\nBOOK SAVED.\n\n";
			system("PAUSE");
			break;
		}//END SWITCH FOR EDIT MENU

	}//END IF USER DOES WANT TO EDIT BOOK

}

/*********************************************************************
* FUNCTION - DELETE BOOK
*********************************************************************/
void deleteBook(orderedLinkedList<InventoryBook> &tList, orderedLinkedList<InventoryBook> &qohList,
				orderedLinkedList<InventoryBook> &wpList, orderedLinkedList<InventoryBook> &daList)
{
	linkedListIterator<InventoryBook> myIterator;
	myIterator = tList.begin();

	char      yesOrNo;
	string    search; //node the user wants to delete
	string    bookSearchedFor;
	bool      found;
	
	found = false;

	cout << "SERENDIPITY BOOKSELLERS" << endl;
	cout << "     DELETE BOOK       " << endl;
	cout <<                              endl << endl;
	cout << " CURRENT BOOK COUNT: "   << tList.length() << endl << endl;
	
	cout << ">Enter title of book to be deleted: ";
	getline(cin, search);

	//IF THE SEARCHED VALUE IS IN CAPS
	for(unsigned int index = 0; index < search.length(); index++)
	{
		if (isupper(search[index]))
		{
			search[index] = tolower(search[index]);
		}
	}

	cout << "SEARCHING..." << endl << endl;

	//SEARCH BY TITLE
	while(myIterator != tList.end() && !found)
	{
		bookSearchedFor = (*myIterator).getTitle();
		for(unsigned int index = 0; index < bookSearchedFor.length(); index++)
		{
			if (isupper(bookSearchedFor[index]))
			{
				bookSearchedFor[index] = tolower(bookSearchedFor[index]);
			}
		}
		if(bookSearchedFor.find(search) != string::npos)
		{
			cout << "BOOK FOUND: " << bookSearchedFor << endl;
			cout << "Delete this book? (Y/N): ";
			cin.get(yesOrNo);
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch(toupper(yesOrNo))
			{
				case 'Y': found = true;
						  cout << endl;
						  cout << tList.length() << '\n' << qohList.length() << '\n' << wpList.length() << '\n' << daList.length() << '\n';
						  tList.deleteNode(*myIterator);
						  qohList.deleteNode(*myIterator);
						  wpList.deleteNode(*myIterator);
						  daList.deleteNode(*myIterator);
				break;

				case 'N': found = false;
				break;
			}
		}
		++myIterator;
	}//END WHILE

	if(found == false)
	{
		cout << "\nBOOK NOT FOUND.\n\n";
	}

}

/*********************************************************************
* FUNCTION - REPORTS
*********************************************************************/
void reports(orderedLinkedList<InventoryBook> tList, orderedLinkedList<InventoryBook> qohList,
			 orderedLinkedList<InventoryBook> wpList, orderedLinkedList<InventoryBook> daList)
{
	int choice;
	
	choice = 0;
	
	do
	{
		cout << "*****************************************" << endl;
		cout << "*        SERENDIPITY BOOKSELLERS        *" << endl;
		cout << "*            REPORTS MENU               *" << endl;
		cout << "*****************************************" << endl;
		cout << "* <1> Inventory Listing                 *" << endl;
		cout << "* <2> Inventory Wholesale Value         *" << endl;
		cout << "* <3> Inventory Retail Value            *" << endl;
		cout << "* <4> Listing by Quantity               *" << endl;
		cout << "* <5> Listing by Cost                   *" << endl;
		cout << "* <6> Listing by Age                    *" << endl;
		cout << "* <7> Return to the Main Menu           *" << endl;
		cout << "*****************************************" << endl;
		cout << " > CHOICE: ";
		
		//CHECKING FOR INVALID INPUT
		do
		{
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.clear();
			
			if(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7)
			{
				cout << "\n\n*** ERROR - PLEASE INPUT 1-7 ***\n\n";
			}
		}while(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7);
		
		system("CLS");
		
		//SWITCH
		switch(choice)
		{
			case 1: repListing(tList);
			break;
			
			case 2: repWholesale(tList);
			break;
			
			case 3: repRetail(tList);
			break;
			
			case 4: repQty(qohList);
			break;
			
			case 5: repCost(wpList);
			break;
			
			case 6: repAge(daList);
			break;
		}
		
		system("PAUSE");
		system("CLS");
		
	}while(choice != 7);
	
}

/*********************************************************************
* FUNCTION - REPLISTING
*********************************************************************/
void repListing(orderedLinkedList<InventoryBook> tList)
{
	linkedListIterator<InventoryBook> myIterator;

	cout << "     SERENDIPITY BOOKSELLERS" << endl;
	cout << "          REPORT LISTING    " << endl << endl;
	
	cout << "DATE: "  << dateAndTime();
	cout << " PAGE: ";
	cout << "     ";
	cout << "CURRENT BOOK COUNT: " << tList.length();
	cout << endl << endl;

	cout << left;
	cout << setw(26) << "TITLE";
	cout << setw(11) << "ISBN";
	cout << setw(16) << "AUTHOR";
	cout << setw(16) << "PUBLISHER";
	cout << setw(11) << "DATE ADDED";
	cout << setw(8)  << "QTY O/H";
	cout << setw(15) << "WHOLESALE COST";
	cout << setw(13) << "RETAIL PRICE";
	cout << endl;
	
	cout << setw(26) << "-------------------------";
	cout << setw(11) << "----------";
	cout << setw(16) << "---------------";
	cout << setw(16) << "---------------";
	cout << setw(11) << "----------";
	cout << setw(8)  << "-------";
	cout << setw(15) << "--------------";
	cout << setw(13) << "------------";
	cout << endl;
	
	cout << fixed << setprecision(2);
	
	//OUTPUT - linked list
	for(myIterator = tList.begin(); myIterator != tList.end(); ++myIterator)
	{
		cout << left;
		cout <<         setw(26) << (*myIterator).getTitle().substr(0, 24);
		cout <<         setw(11) << (*myIterator).getIsbn().substr(0, 10);
		cout <<         setw(16) << (*myIterator).getAuthor().substr(0, 15);
		cout <<         setw(16) << (*myIterator).getPub().substr(0, 15);
		cout <<         setw(11) << (*myIterator).getDateAdded().substr(0, 10);
		cout <<         setw(8)  << (*myIterator).getQtyOnHand();
		cout << "$ " << setw(15) << (*myIterator).getWholesale();
		cout << "$ " << setw(13) << (*myIterator).getRetail();
		cout << endl;
	}
	
	cout << endl;
}

/*********************************************************************
* FUNCTION - repWholesale
*********************************************************************/
void repWholesale(orderedLinkedList<InventoryBook> tList)
{
	double subtotal;
	double grandTotal;
	
	subtotal   = 0;
	grandTotal = 0;
	
	cout << "     SERENDIPITY BOOKSELLERS  " << endl;
	cout << "     REPORT WHOLESALE LISTING " << endl << endl;
	
	cout << "DATE: "  << dateAndTime();
	cout << " PAGE: ";
	cout << "     ";
	cout << "CURRENT BOOK COUNT: " << tList.length();
	cout << endl << endl;

	cout << left;
	cout << setw(26) << "TITLE";
	cout << setw(11) << "ISBN";
	cout << setw(8)  << "QTY O/H";
	cout << setw(15) << "WHOLESALE COST";
	cout << endl;
	
	cout << setw(26) << "-------------------------";
	cout << setw(11) << "----------";
	cout << setw(8)  << "-------";
	cout << setw(15) << "--------------";
	cout << endl;
	
	cout << fixed << setprecision(2);

	//CREATE ITERATOR
	linkedListIterator<InventoryBook> myIterator;
	
	//OUTPUT - linked list
	for(myIterator = tList.begin(); myIterator != tList.end(); ++myIterator)
	{
		cout << left;
		cout <<         setw(26) << (*myIterator).getTitle().substr(0, 24);
		cout <<         setw(11) << (*myIterator).getIsbn().substr(0, 10);
		cout <<         setw(8)  << (*myIterator).getQtyOnHand();
		cout << "$ " << setw(15) << (*myIterator).getWholesale();
		cout << endl;
		
		//CALC - subtotal and grandTotal
		subtotal   = (*myIterator).getQtyOnHand() * (*myIterator).getWholesale();
		grandTotal = grandTotal + subtotal;
	}
	
	cout << endl;
	cout << "TOTAL: $" << grandTotal;
	cout << endl       << endl;
}


/*********************************************************************
* FUNCTION - repRetail
*********************************************************************/
void repRetail(orderedLinkedList<InventoryBook> tList)
{
	double subtotal;
	double grandTotal;

	subtotal   = 0;
	grandTotal = 0;

	cout << "     SERENDIPITY BOOKSELLERS" << endl;
	cout << "      REPORT RETAIL LISTING " << endl << endl;
	
	cout << "DATE: "  << dateAndTime();
	cout << " PAGE: ";
	cout << "     ";
	cout << "CURRENT BOOK COUNT: " << tList.length();
	cout << endl << endl;

	cout << left;
	cout << setw(26) << "TITLE";
	cout << setw(11) << "ISBN";
	cout << setw(8)  << "QTY O/H";
	cout << setw(15) << "RETAIL COST";
	cout << endl;
	
	cout << setw(26) << "-------------------------";
	cout << setw(11) << "----------";
	cout << setw(8)  << "-------";
	cout << setw(15) << "--------------";
	cout << endl;
	
	cout << fixed << setprecision(2);

	//CREATE ITERATOR
	linkedListIterator<InventoryBook> myIterator;
	
	//OUTPUT - linked list
	for(myIterator = tList.begin(); myIterator != tList.end(); ++myIterator)
	{
		cout << left;
		cout <<         setw(26) << (*myIterator).getTitle().substr(0, 24);
		cout <<         setw(11) << (*myIterator).getIsbn().substr(0, 10);
		cout <<         setw(8)  << (*myIterator).getQtyOnHand();
		cout << "$ " << setw(15) << (*myIterator).getRetail();
		cout << endl;
		
		//CALC - subtotal and grandTotal
		subtotal   = (*myIterator).getQtyOnHand() * (*myIterator).getRetail();
		grandTotal = grandTotal + subtotal;
	}
	
	cout << endl;
	cout << "TOTAL: $" << grandTotal;
	cout << endl       << endl;
}


/*********************************************************************
* FUNCTION - repQty
*********************************************************************/
void repQty(orderedLinkedList<InventoryBook> qohList)
{
	cout << "     SERENDIPITY BOOKSELLERS" << endl;
	cout << "     REPORT QTY O/H LISTING " << endl << endl;
	
	cout << "DATE: "  << dateAndTime();
	cout << " PAGE: ";
	cout << "     ";
	cout << "CURRENT BOOK COUNT: " << qohList.length();
	cout << endl << endl;

	cout << left;
	cout << setw(26) << "TITLE";
	cout << setw(11) << "ISBN";
	cout << setw(8)  << "QTY O/H";
	cout << endl;
	
	cout << setw(26) << "-------------------------";
	cout << setw(11) << "----------";
	cout << setw(8)  << "-------";
	cout << endl;
	
	//CREATE ITERATOR
	linkedListIterator<InventoryBook> myIterator;
	
	//OUTPUT - linked list
	for(myIterator = qohList.begin(); myIterator != qohList.end(); ++myIterator)
	{
		cout << left;
		cout <<         setw(26) << (*myIterator).getTitle().substr(0, 24);
		cout <<         setw(11) << (*myIterator).getIsbn().substr(0, 10);
		cout <<         setw(8)  << (*myIterator).getQtyOnHand();
		cout << endl;
	}
	
	cout << endl;
}


/*********************************************************************
* FUNCTION - repCost
*********************************************************************/
void repCost(orderedLinkedList<InventoryBook> wpList)
{
	cout << "     SERENDIPITY BOOKSELLERS  " << endl;
	cout << "     REPORT WHOLESALE LISTING " << endl << endl;
	
	cout << "DATE: "  << dateAndTime();
	cout << " PAGE: ";
	cout << "     ";
	cout << "CURRENT BOOK COUNT: " << wpList.length();
	cout << endl << endl;

	cout << left;
	cout << setw(26) << "TITLE";
	cout << setw(11) << "ISBN";
	cout << setw(8)  << "QTY O/H";
	cout << setw(15) << "WHOLESALE COST";
	cout << endl;
	
	cout << setw(26) << "-------------------------";
	cout << setw(11) << "----------";
	cout << setw(8)  << "-------";
	cout << setw(15) << "--------------";
	cout << endl;
	
	cout << fixed << setprecision(2);

	//CREATE ITERATOR
	linkedListIterator<InventoryBook> myIterator;
	
	//OUTPUT - linked list
	for(myIterator = wpList.begin(); myIterator != wpList.end(); ++myIterator)
	{
		cout << left;
		cout <<         setw(26) << (*myIterator).getTitle().substr(0, 24);
		cout <<         setw(11) << (*myIterator).getIsbn().substr(0, 10);
		cout <<         setw(8)  << (*myIterator).getQtyOnHand();
		cout << "$ " << setw(15) << (*myIterator).getWholesale();
		cout << endl;
	}
	
	cout << endl;
}


/*********************************************************************
* FUNCTION - repAge
*********************************************************************/
void repAge(orderedLinkedList<InventoryBook> daList)
{
	cout << "     SERENDIPITY BOOKSELLERS  " << endl;
	cout << "       REPORT AGE LISTING     " << endl << endl;
	
	cout << "DATE: "  << dateAndTime();
	cout << " PAGE: ";
	cout << "     ";
	cout << "CURRENT BOOK COUNT: " << daList.length();
	cout << endl << endl;

	cout << left;
	cout << setw(26) << "TITLE";
	cout << setw(11) << "ISBN";
	cout << setw(8)  << "QTY O/H";
	cout << setw(11) << "DATE ADDED";
	cout << endl;
	
	cout << setw(26) << "-------------------------";
	cout << setw(11) << "----------";
	cout << setw(8)  << "-------";
	cout << setw(11) << "----------";
	cout << endl;
	
		//CREATE ITERATOR
	linkedListIterator<InventoryBook> myIterator;
	
	//OUTPUT - linked list
	for(myIterator = daList.begin(); myIterator != daList.end(); ++myIterator)
	{
		cout << left;
		cout <<         setw(26) << (*myIterator).getTitle().substr(0, 24);
		cout <<         setw(11) << (*myIterator).getIsbn().substr(0, 10);
		cout <<         setw(8)  << (*myIterator).getQtyOnHand();
		cout <<         setw(11) << (*myIterator).getDateAdded();
		cout << endl;
	}
	
	cout << endl;
	
}

/*********************************************************************
* FUNCTION - BOOKINFO
*********************************************************************/
void BookInfo(orderedLinkedList<InventoryBook> tList, linkedListIterator<InventoryBook> myIterator)
{
	cout << "SERENDIPITY BOOKSELLERS" << endl;
	cout << "       BOOK INFO       " << endl;


	cout << "Title: "            << (*myIterator).getTitle()     << endl;

	cout << "ISBN: "             << (*myIterator).getIsbn()      << endl;

	cout << "Author: "           << (*myIterator).getAuthor()    << endl;

	cout << "Publisher: "        << (*myIterator).getPub()       << endl;

	cout << "Date Added: "       << (*myIterator).getDateAdded() << endl;

	cout << "Quantity-On-Hand: " << (*myIterator).getQtyOnHand() << endl;

	cout << "Wholesale Cost: "   << (*myIterator).getWholesale() << endl;

	cout << "Retail Price: "     << (*myIterator).getRetail()    << endl << endl;
}


/*********************************************************************
* FUNCTION - WRITEDATA
*********************************************************************/
void WriteData(orderedLinkedList<InventoryBook> tList)
{
	ofstream fout;
	linkedListIterator<InventoryBook> myIterator;

	//OPEN FILE
	fout.open("database.txt");

	if (!fout)
	{
		cout << "\n\n***ERROR - DATABASE.TXT NOT FOUND***\n\n";
	}
	else
	{
		myIterator = tList.begin();
		do
		{
			fout << (*myIterator).getTitle()     << endl;
			fout << (*myIterator).getIsbn()      << endl;
			fout << (*myIterator).getAuthor()    << endl;
			fout << (*myIterator).getPub()       << endl;
			fout << (*myIterator).getDateAdded() << endl;
			fout << (*myIterator).getQtyOnHand() << endl;
			fout << (*myIterator).getWholesale() << endl;
			fout << (*myIterator).getRetail()    << endl;
			++myIterator;

			if(myIterator != tList.end())
			{
				fout << '\n';
			}
		}while(myIterator != tList.end());
	}

	//CLOSE FILE
	fout.close();
}

/*********************************************************************
* FUNCTION - WRITESOLDBOOK
*********************************************************************/
void WriteSoldBook(orderedLinkedList<SoldBook> receipt)
{
	ofstream fout;
	linkedListIterator<SoldBook> myIterator;	// iterator

	fout.open("soldBookRecord.txt", fout.app);
	if (!fout)
	{
		cout << "\n*** ERROR. SOLDBOOKRECORD.TXT NOT FOUND. ***\n\n";
		return;
	}
	else
	{
		for (myIterator = receipt.begin(); myIterator != receipt.end(); ++myIterator)
		{
			if ((*myIterator).getQtySold() > 0)
			{
				fout << (*myIterator).getTitle()     << endl;
				fout << (*myIterator).getIsbn()      << endl;
				fout << (*myIterator).getAuthor()    << endl;
				fout << (*myIterator).getPub()       << endl;
				fout << (*myIterator).getDateAdded() << endl;
				fout << (*myIterator).getQtyOnHand() << endl;
				fout << (*myIterator).getWholesale() << endl;
				fout << (*myIterator).getRetail()    << endl;
				fout << (*myIterator).getTaxRate()   << endl;
				fout << (*myIterator).getQtySold()   << endl;
				fout << (*myIterator).getTax()       << endl;
				fout << '\n';
			}
		}
	}
	fout.close();

}
