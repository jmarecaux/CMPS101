// -------------------------------------------------------------------
//	List.java
//	Integer list ADT
//	Jules Marecaux
//	jrmareca
//	1574177
//	------------------------------------------------------------------

public class List {

	private class Node {

		int data;
		Node next;
		Node prev;

		Node(int datain) {

			data = datain;
			next = null;
			prev = null;

		}
	
		public String toString() {
			return String.valueOf(data);
		}
	
	}

	private Node front;
	private Node back;
	private int length;
	private Node cursor;
	private int index;

	List() {

		front  = null;
		back   = null;
		length = 0;
		index = -1;
		cursor = null;

	}

	//Access functions -----------------------------------------------

	int length() {
		return length;
	}
	
	int index() {
		if( cursor != null ) {
			return index;
		}
		
		return -1;
	}
	
	int front() {

		if(length <= 0) {
			throw new RuntimeException("Error on List.front(): length is not greater than 0");
		}

		return front.data;

	}

	int back() {
	
		if(length <= 0) {
			throw new RuntimeException("Error on List.back(): length is not greater than 0");
		}

		return back.data;

	}

	int get() {
		
		if(index() < 0) {
			throw new RuntimeException("Error on List.get(): invalid index.");
		}
		if(length <= 0) {
			throw new RuntimeException("Error on List.get(): length is not greater than 0.");
		}
		
		return cursor.data;
	
	}

	boolean equals(List L) {

		if(length != L.length()) return false;


		Node A = front;
		Node B = L.front;
		boolean eqList = true;
		while(A != null && B != null) {
			eqList = (A.data == B.data);
			A = A.next;
			B = B.next;
		}
		
		return eqList;

	}

	//	Manipulation procedures --------------------------------------

	void clear() {
		
		length = 0;
		cursor = null;
		front  = null;
		back   = null;
		index = -1;
		
	}
	
	void moveFront() {
		if(length > 0){
			index = 0;
			cursor = front;
			
		}
	}

	void moveBack() {
		if(length > 0) {
			index = length - 1;
			cursor = back;
		}
	}
	
	void movePrev() {
		if( index == 0 ) {
			index = -1;
			cursor = null;
		}
		else if(index > 0) {
		
			index--;
			cursor = cursor.prev;

		}
	}

	void moveNext() {
		
		if( index == length - 1 && cursor != null) {

			index = -1;
			cursor = null;
	
		}
		else if(index < length - 1 && cursor != null) {
			
			index++;
			cursor = cursor.next;
		
		}
	}

	void prepend(int data) {

		Node N = new Node(data);
		
		if(length == 0) {
			front = N;
			back  = N;
		}
		else {
			front.prev = N;
			N.next = front;
			front = N;
		}
		length++;
	}

	void append(int data) {
		
		Node N = new Node(data);
	
		if(length == 0) {
			front = N;
			back = N;
		}
		else {
			back.next = N;
			N.prev = back;
			back = N;
		}
		length++;
	}

	void insertBefore(int data) {
		
		if(length < 1) {
			throw new RuntimeException("Error on List.insertBefore(): Length is less than 1.");
		}
		if(index() == -1) {
			throw new RuntimeException("Error on List.insertBefore(): Index is invalid.");
		}

		Node N = new Node(data);
		
		if(cursor != front) {
			cursor.prev.next = N;
			N.prev = cursor.prev;
			cursor.prev = N;
			N.next = cursor;
			
		}
		else {
			cursor.prev = N;
			front = N;
			N.next = cursor;
		}
		length++;

	}
	
	void insertAfter(int data) {
		
		if(length<1) {
			throw new RuntimeException("Error on List.insertAfter(): Length is less than 1.");
		}
		if(index() == -1) {
			throw new RuntimeException("Error on List.insertAfter(): Index is invalid.");
		}
		
		Node N = new Node(data);
		
		if(cursor != back) {
			cursor.next.prev = N;
			N.prev = cursor;
			N.next = cursor.next;
			cursor.next = N;
		}
		else {
			cursor.next = N;
			back = N;
			back.prev = cursor;
		}
		length++;
		
	}
		
	void deleteFront() {
		
		if( length <= 0 ) {
			throw new RuntimeException("Error on List.deleteFront(): Length is less than 1.");
		}
		
		if( index == 0 ) {
			cursor = null;
			index = -1;
			front = front.next;
			front.prev = null;
		}
		
		front = front.next;
		front.prev = null;
		
		length--;
		
	}

	void deleteBack() {

		if( length <= 0 ) {
			throw new RuntimeException("error on List.deleteBack(): Length is less than 1.");
		}
		if( index == length - 1) {
			cursor = null;
			index = -1;
			back = back.prev;
			back.next = null;
		}
		if (length == 1 ) {
			clear();
			return;
		}
		back = back.prev;
		back.prev = null;
		
		length--;
		
	}

	void delete() {
			
		if( index <= -1 ) {
			throw new RuntimeException("Error on List.delete(): Index is invalid.");
		}
		if( length <= 0 ) {
			throw new RuntimeException("Error on List.delete(): length is less than 1.");
		}
		if( cursor == front ) {
			deleteFront();
		}
		else if ( cursor == back ) {
			deleteBack();
		}
		else {
			cursor.prev.next = cursor.next;
			cursor.next.prev = cursor.prev;
			cursor = null;
			index = -1;
			length--;
		}			
	}

	public String toString() {

		Node N = front;
		String out = new String();

		while(N != null) {
			out = out + String.valueOf(N.data) + " ";
			N = N.next;
		}
		return out;
	}			

	List copy() {
		
		List M = new List();
		Node N = front;
		
		while (N != null) {
			M.append(N.data);
			N = N.next;
		}
		return M;
	}
}

/*	List concat(List L) {

		this.back.next = L.front;
		L.front.prev = this.back;
		this.cursor = null;
		this.index = -1;

		return 

	}

}
*/



















