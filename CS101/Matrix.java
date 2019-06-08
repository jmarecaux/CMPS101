// Jules Marecaux
// jrmareca
// Matrix.java
// Array of Linked lists implementation of a matrix with math functions
// -------------------------------------------------------------------

public class Matrix {
	private class Entry {
		int column;
		double data;
		
		Entry(int col, double num) {
			
			column = col;
			data = num;

		}
	
		public String toString() {
		
			return ("(" + column + ", " + data + ")");
		
		}

		public boolean equals(Object x) {
		
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
			throw new RuntimeException("Matrix Error: Matrix() cannot have negative number of columns");
		}
		row = new List[n];
		for(int i = 0; i < n; i++) {
			row[i] = new List();
		}
		nnz = 0;
		size = n;
	}
	
	// Access Functions ------------------------------------------------

	int getSize() {
		return size;
	}
	
	int getNNZ() {
		return nnz;
	}

	public boolean equals(Object x) {
		boolean bool = true;
		Matrix M;
		if(x instanceof Matrix) {
			M = (Matrix) x;
			if(this.size != M.size) {
				bool = false;
				return bool;
			}
			for(int i = 0; i < size; i++) {
				if(this.row[i].equals(M.row[i])) {
					bool = true;
				}
				else {
					bool = false;
					return bool;
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
		Matrix M = new Matrix(size);
		Entry E;
		for(int i = 0; i < size; i++) {
			for(row[i].moveFront(); row[i].index() >= 0; row[i].moveNext()) {
				E = (Entry) row[i].get();
				M.row[i].append(E);
			}
		}
		M.nnz = this.nnz;
		return M;
	}
	
	void changeEntry(int i, int j, double x) {
		
		if(i < 1 || i > size || j < 1 || j > size) {
			throw new RuntimeException("Error on changeEntry(): input out of bounds");
		}
		Entry A = new Entry(j, x);
		Entry E;
		
		boolean isEntry = false;
		Entry temp = new Entry(0, 0.0);
		
		row[i].moveFront();
		while(row[i].index() != -1) {
			temp = (Entry) row[i].get();
			int col = temp.column;
			if( col == j ) {
				isEntry = true;
				break;
			}
			row[i].moveNext();
		}

		if(isEntry) {
			temp.data = x;
		}
		if(!isEntry) { }
	}

	Matrix scalarMult(double x) {
		
		Matrix M = copy();
		for(int i = 0; i < size; i++) {
			M.row[i].moveFront();
			while(M.row[i].index() != -1) {

				Entry E = (Entry) M.row[i].get();
				M.changeEntry(i + 1, E.column, (x * E.data));
				M.row[i].moveNext();
			}
			M.row[i].moveNext();
		}
		return M;
	}
	
	Matrix add(Matrix M) {
		if(getSize() != M.getSize()) {
			throw new RuntimeException("Error on matrix: cannot add different sized matrices");
		}
		if(M == this) {
			Matrix A = copy();
			return A.scalarMult(2);
		}
		Matrix B = new Matrix(size);
		for(int i = 1; i <= size; i++) {
			Entry one = (Entry) row[i].get();
			Entry two = (Entry) row[i].get();
			
			one.data = one.data + two.data;
			
			B.row[i].append(one);
			
		}
		return B;
	}


		
	public String toString() {
		String matrix = "";
		for(int i = 1; i < size; i++) {
			if(row[i].length() > 0) {
				matrix += (i + ": " + row[i] + "\n");
			}
		}
		return matrix;
	}

}

























