
#include <string>
using namespace std;

class Matrix {

	public:

		// Default Constructor
		Matrix();		
		// Additional Constructors
		Matrix( int row, int col );
		
		Matrix( int row, int col, int **table );

		~Matrix(); //delocation matrix on the heap
		// Do you think you need a Destructor?  Why or why not?
	

		bool setElement(int x, int i, int j);
		int getElement(int i, int j); //return element on matrix
			
		int setsizeofrows(); //set from matrix
		int getsizeofrows(); //return from class
	
		int setsizeofcolns();//set from matrix
		int getsizeofcols(); //return from class
	
		// Other Member Functions
		Matrix copy();						// Create a Copy of This Matrix
		void addTo( Matrix &m );				// Add Matrix m to this matrix
		Matrix subMatrix(int i, int j);     // Obtain the upper-left submatrix of this matrix
		string toString();					// String Conversion Method


	private:

		// Stack Data Members
		int    rowsNum; //the rowNum private content 
		int    colsNum;
		// Heap Data Members - Do you need to release them?  Where, when, and how?
		int    **matrixData;

};
