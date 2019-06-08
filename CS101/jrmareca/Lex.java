// -------------------------------------------------------------------
// Jules Marecaux
// jrmareca
// 1574177
// Lex.java
// PA1
// -------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;

public class Lex {

	public static void main(String[] args) throws IOException {
		
		Scanner in = null;
		PrintWriter out = null;
		String line = null;
		String[] token = null;
		int n, lineNumber = 0;
		
		if(args.length != 2) {
			System.err.println("Usage: Lex infile outfile");
			System.exit(1);
		}
		
		in = new Scanner(new File(args[0]));
		out = new PrintWriter(new FileWriter(args[1]));

		List L = new List();
		
		while(in.hasNextLine()) {
			lineNumber++;
			in.nextLine();
		}
		
		in.close();
		
		String[] array = new String[lineNumber];
		
		in = new Scanner(new File(args[0]));
		
		for(int j = 0; j < lineNumber; j++) {
			line = in.nextLine() + " ";
			token = line.split("\\s+");
			n = token.length;
			array[j] = line;
		}
		
		int j;
		L.append(0);
		//"insertion sort" as I organize the list in lex order one by one to array
		for(int i = 1; i < array.length; i++) {
			j = i - 1;
			String temp = array[i];
			L.moveFront();

			while( L.index() != -1) {
				if(array[L.get()].compareTo(array[i])>0) {
					L.insertBefore(i);
					break;
				}
				L.moveNext();
				if(L.index() == -1) {
					L.append(i);
				}
			}
		}
		
		L.moveFront();
		
		while(L.index() >= 0) {
			out.println(array[L.get()]);
			L.moveNext();
		}
		
		
		in.close();
		out.close();
/*
		in = null;

		token = new String[linecount];

		in = new Scanner(new File(args[0]));
		
		for(int i = 0; i < token.length; i++) {
			token[i] = in.nextLine;
		*/
	}
}

		
