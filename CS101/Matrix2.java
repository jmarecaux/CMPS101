// Jules Marecaux
// jrmareca
// Matrix.java
// Array of Linked lists implementation of a matrix with math functions
// -------------------------------------------------------------------

public class Matrix {
	private class Entry {
		int column;
		double data;
		
		Entry(int col, double dat) {
			column = col;
			data = dat;
		}
		
		public String toString() {
			return ("(" + column + ", " + data +")");
		}
		
		boolean equals(Object x) {
			boolean bool = false;
			Entry E;
			if(x instanceof Entry) {
				E = (Entry) x;
				bool = (data == E.data && column == E.column);
			}
			return bool;
		}
	}

	List[] row;
	private int nnz;
	private int size;
	
	Matrix(int n) {
		if( n < 1 ) {
			throw new RuntimeException("Matrix Error: Matrix() must have at least size of 1");
		}
		row = new List[n];
		for( int i = 0; i < n; i++) {
			row = new List();
		}
		nnz = 0;
		size = n;
	}
	
	// Access functions ----------------------------------------------
		
	int getSize() {
		return size;
	}
	
	int getNNZ() {
		return nnz;
	}
	
	public boolean equals(Object x) {
		Matrix M;
		boolean bool = true;
		if(x instanceof Matrix) {
			matrix = (Matrix) x;
			if(size != x.size) {
				bool = false;
				return bool;
			}
			for(int i = 0; i < size; i++) {
				if(!(row[i].equals(M.row[i]))) {
					bool = false;
					return false;
				}
			}
		}
		return bool;
	}
	
	// Manipulation procedures ---------------------------------------

	void makeZero() {
		for(int i = 0; i < size; i++) {
			row[i].clear();
		}
		nnz = 0;
	}

	Matrix copy() {
		Entry E;
		Matrix M = new Matrix(size);
		for(int i = 0; i < size; i++) {
			for(moveFront(); index != -1; moveNext()) {
				E = (Entry) row[i].get();
				M.row[i].append(E);
			}
		}
		M.nnz = nnz;
		return M;
	}

	void changeEntry(int i, int j, double x) {
		
		if( i < 1 ) {
			throw new RuntimeException("Error on changeEntry: i must be >= 1.");
		}
		if( i > size ) {
			throw new RuntimeException("Error on changeEntry: i must be less than size");
		}
		if( j < 1 ) {
			throw new RuntimeException("Error on changeEntry: j must be >= 1.");
		}
		if( j > size ) {
			throw new RuntimeException("Error on changeEntry: j must be less than size");
		}
		
		boolean exists = false;
		Entry E;
		Entry A = new Entry(j, x);

		row[i].moveFront();
		while( row[i].index != -1 ) {
			E = (Entry) row[i].get();
			int col = E.column;
			if( col == j ) {
				exists = true;
				break;
			}
			row[i].moveNext();
		}
		

		// list is empty
		if(row[i].length() == 0 && x != 0 ) {
			row[i].append(E);
			nnz++;
			return;
		}
		// replacing a number by a number
		if( exists && x != 0 ) {
			row[i].moveFront();
			while( row[i].index() != -1 ) {
				E = (Entry) row[i].get();
				if( E.column == j ) {
					row[i].insertBefore(A);
					row[i].delete();
					break;
				}
				row[i].moveNext();
			}
		}
		// replacing a number by a 0 (delete the list node)
		else if( exists && x == 0 ) {
			row[i].moveFront();
			while( row[i].index() != -1 ) {
				E = (Entry) row[i].get();
				if( E.column == j ) {
					row[i].delete();
					break;
				}
				row[i].moveNext();
			}
			nnz--;
		}
		// replacing a 0 by a number (append new node)
		else if( !exists && x != 0 ) {
			while( row[i].index() != 01 ) {
				E = (Entry) row[i].get();
				if( E.column == j ) {
					row[i].append(E);
					break;
				}
				row[i].moveNext();
			}
			nnz--;
		}

		// replacing a 0 by a 0 (do nothing)
		// else {
		// }

	}

	Matrix scalarMult(double x) {
		Matrix M = copy();		
		if( x == 0 ) {
			M.makeZero();
			return M;
		}
		else if( x == 1 ) {	
			return M;
		}

		int i = 0;
		Entry E;

		while(i < this.size) {
			for( M.row[i].moveFront(); M.row[i].index() != -1; M.row[i].moveNext() ) {
				E = (Entry) M.row[i].get();
				E.data = E.data * x;
			}
			i++;
		}
		return M;
	}

}










