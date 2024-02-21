#ifndef SOLDBOOK_H_
#define SOLDBOOK_H_

#include <string>
#include "inventoryBook.h"

using namespace std;

//CLASS - SOLDBOOK
class SoldBook: public InventoryBook
{
	private:
		double taxRate;
		int    qtySold;
		double tax;
		double subtotal;
		double total;
		
	public:
	/********************************************************************************
	* SETTERS
	********************************************************************************/
		void setTaxRate(double x)
		{
			taxRate = x;
		}

		void setQtySold(int x)
		{
			qtySold = x;
		}

		void setTax(double x, int y)
		{
			tax    = x;
			taxRate = y;
		}

		void setSubtotal(double x)
		{
			subtotal = x;
		}

		void setTotal(double x)
		{
			total = x;
		}

		
	/********************************************************************************
	* GETTERS
	********************************************************************************/
		double getTaxRate() const
		{
			return taxRate;
		}

		int    getQtySold() const
		{
			return qtySold;
		}

		double getTax() const
		{
			return tax;
		}

		double getSubtotal() const
		{
			return subtotal;
		}

		double getTotal() const
		{
			return total;
		}


		
	/********************************************************************************
	* CONSTRUCTORS
	********************************************************************************/
		/*********************
		 * FUNCTION: SoldBook
		 * ------------------
		 * - sets all variables to nothing
		 * - receives nothing
		 * RETURNS: nothing
		 ********************/
		SoldBook()
		{
			setTaxRate(0.0);
			setQtySold(0);
			setTax(0.0, 0);
		}
		
		/*********************
		 * FUNCTION: SoldBook
		 * ------------------
		 * - sets all variables to the arguments
		 * - receives everything
		 * RETURNS: nothing
		 ********************/
		SoldBook(string bookTitle, string isbn, string author, string publisher,
				 string dateAdded, int qtyOnHand, double wholesale, double retail,
				 double taxRate, int qtySold, double tax):InventoryBook(bookTitle, isbn, author, publisher, dateAdded, qtyOnHand, wholesale, retail)
		{
			setTaxRate(taxRate);
			setQtySold(qtySold);
			setTax(tax, qtySold);
		}

	/********************************************************************************
	* PRINT
	********************************************************************************/
		void print()
		{
			BookData::print();
			InventoryBook::print();

			cout << fixed << setprecision(2);
			cout << "Tax Rate: " << getTaxRate()  << endl;
			cout << "Qty Sold: " << getQtySold()  << endl;
			cout << "Tax: "      << getTax()      << endl;
			cout << "Subtotal: " << getSubtotal() << endl;
			cout << "Total: "    << getTotal()    << endl;
		}
};


#endif /* PERSON_H_ */
