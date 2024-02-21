#ifndef INVENTORYBOOK_H_
#define INVENTORYBOOK_H_

#include "bookdata.h"
#include <windows.h>


//CLASS - INVENTORYBOOK
class InventoryBook: public BookData
{
	private:
		string dateAdded;
		int    qtyOnHand;
		double wholesale;
		double retail;
		int    sortCode;  //for sorting
		
	public:
	/********************************************************************************
	* SETTERS
	********************************************************************************/
		void setDateAdded(string x)
		{
			dateAdded = x;
		}

		void setQtyOnHand(int x)
		{
			qtyOnHand = x;
		}

		void setWholesale(double x)
		{
			wholesale = x;
		}

		void setRetail(double x)
		{
			retail = x;
		}
		
		void setSortCode(int x)
		{
			sortCode = x;
		}
		
	/********************************************************************************
	* GETTERS
	********************************************************************************/
		string getDateAdded() const
		{
			return dateAdded;
		}

		int getQtyOnHand() const
		{
			return qtyOnHand;
		}

		double getWholesale() const
		{
			return wholesale;
		}

		double getRetail() const
		{
			return retail;
		}

		int getSortCode() const
		{
			return sortCode;
		}
		
	/********************************************************************************
	* OTHER
	********************************************************************************/
		void isEmpty()
		{
			//stuff
		}

		void removeBook()
		{
			//stuff
		}

	/********************************************************************************
	* CONSTRUCTORS
	********************************************************************************/
		/******************************
		* FUNCTION - InventoryBook
		* ------------
		* - sets everything to nothing
		* - receives & returns nothing
		******************************/
		InventoryBook()
		{
			setDateAdded("not set");
			setQtyOnHand(0);
			setWholesale(0.0);
			setRetail(0.0);
			setSortCode(0);
		}
		
		/******************************
		* FUNCTION - InventoryBook
		* ------------
		* - sets everything to the arguments
		* - receives the proper arguments
		* - returns nothing
		******************************/
		InventoryBook(string bookTitle, string isbn, string author, string publisher,
				string dateAdded, int qtyOnHand, double wholesale, double retail):BookData(bookTitle, isbn, author, publisher)
		{
			setDateAdded(dateAdded);
			setQtyOnHand(qtyOnHand);
			setWholesale(wholesale);
			setRetail(retail);
			setSortCode(0);
		}
	/********************************************************************************
	* PRINT
	********************************************************************************/
		void print()
		{
			BookData::print();

			cout <<  "Date Added: "        << getDateAdded()                             << endl;
			cout <<  "Quantity-On-Hand: "  << getQtyOnHand()                             << endl;
			cout <<  "Wholesale Cost: $ "  << fixed << setprecision(2) << getWholesale() << endl;
			cout <<  "Retail Price: $ "    << fixed << setprecision(2) << getRetail()    << endl;
		}
		
	/********************************************************************************
	* OVERLOADED OPERATORS
	********************************************************************************/
	bool operator>=(const InventoryBook& other_Book) const{
					bool found       = false;
					bool greaterThan = false;
					string temp1     = this->getTitle();
					string temp2     = other_Book.getTitle();
					string one;
					string two;
					int oneTemp      = 0;
					int twoTemp      = 0;

					if (this != &other_Book){ //avoid self evaluation
						switch (other_Book.sortCode){
							case 0: // Title
								if (temp1.compare(temp2) >= 0)
										found = true;
								break;

							case 1: // Qty on Hand

									if (this->qtyOnHand <= other_Book.qtyOnHand){
										found = true;
									}

								break;

							case 2: // Wholesale price

									if (this->wholesale <= other_Book.wholesale){
										found = true;
									}

								break;

							case 3: // Date Added
									greaterThan = false;
									one = this->getDateAdded().substr (6,10);
									oneTemp = atoi(one.c_str());

									two = other_Book.dateAdded.substr (6,10);
									twoTemp = atoi(two.c_str());


									if (oneTemp > twoTemp)
										greaterThan = true;
									else{
										if (oneTemp == twoTemp){
											one = this->getDateAdded().substr (0,2);
											oneTemp = atoi(one.c_str());

											two = other_Book.dateAdded.substr (0,2);
											twoTemp = atoi(two.c_str());

											if (oneTemp > twoTemp)
												greaterThan = true;
											else{
												if (oneTemp == twoTemp){
													one = this->getDateAdded().substr (3,5);
													oneTemp = atoi(one.c_str());
												//	cout << "oneDay =" << oneTemp << endl;

													two = other_Book.dateAdded.substr (3,5);
													twoTemp = atoi(two.c_str());
												//	cout << "twoDay =" << twoTemp << endl;

													if (oneTemp > twoTemp)
														greaterThan = true;
												}

											}
										}


									}
								found = greaterThan;
								break;
						}
					}

					return found;
				}


				bool operator==(const InventoryBook& other_Book) const{

					bool found = false;
					string temp1 = this->getTitle();
					string temp2 = other_Book.getTitle();

					if (this != &other_Book){ //avoid self evaluation

						switch (other_Book.sortCode){
							case 0: // Title
								if (temp1.compare(temp2)== 0)
										found = true;
								break;

							case 1: // Qty on Hand

									if (this->qtyOnHand == other_Book.qtyOnHand){
										found = true;
									}

								break;
							case 2: // Wholesale price

									if (this->wholesale == other_Book.wholesale){
										found = true;
									}

								break;

							case 3: // Date Added
								if (this->getDateAdded().compare(other_Book.dateAdded) == 0 ){
										found = true;
									}
								break;
						}

					}

					return found;
				}

				bool operator!=(const InventoryBook& other_Book) const{

					bool found = false;
					string temp1 = this->getTitle();
					string temp2 = other_Book.getTitle();

					if (this != &other_Book){ //avoid self evaluation

						switch (other_Book.sortCode){
							case 0: // Title
								if (temp1.compare(temp2) != 0)
										found = true;
								break;

							case 1: // Qty on Hand
								if (this->qtyOnHand != other_Book.qtyOnHand){
										found = true;
									}

								break;
							case 2: // Wholesale price

									if (this->wholesale != other_Book.wholesale){
										found = true;
									}

								break;

							case 3: // Date Added
								break;
						}

					}

					return !found;
				}


	};


#endif
