#include <iostream>
#include "A2P2.h"

using namespace std;

/*
//It works only for sets of integers
template <typename T = int>
void testCopyCtr(Set<T> st) {
	cout<< func <<": ";
	st.insert(23); //because of this statement
	st.print();
	cout<<endl;
}
*/
int main( ){
	info(); //authors details
	Set<int> s1, s2; 
	try{
		//s1.remove( 8 );
		s1.insert( 8 );
		s1.insert( 3 );
		s1.insert( 1 );
		s1.insert( 4 );
		s1.insert( 1 );
		//s1.remove( 8 );
		s1.insert( 2 );
		s2.insert( 4 );
		s2.insert( 2 );
		s2.insert( 6 );
		//s1.remove( 10 );
		
		
		cout << "S1: " << s1 << ", size = " << s1.getSize( ) << endl;
		cout << "S2: " << s2 << ", size = " << s2.getSize( ) << endl;
		/*
		Set<int> s3 = s1+ s2; //union
		Set<int> s4 = s1* s2; //intersection
		swap(s1, s2);
		cout << "s1 + s2: " << s3 << endl;
		cout << "s1 * s2: " << s4 << endl;
		Set<int> s5 = s4 = s3 = s2 = s1 = s1;
		cout << "S1: " << s1 << ", size= " << s1.getSize( ) << endl;
		cout << "S2: " << s2 << ", size= " << s2.getSize( ) << endl;
		cout << "S3: " << s3 << ", size= " << s3.getSize( ) << endl;
		cout << "S4: " << s4 << ", size= " << s4.getSize( ) << endl;
		cout << "S5: " << s5 << ", size= " << s5.getSize( ) << endl;
		cout << "S4 again : " << s4 << endl;
		testCopyCtr(s4);
		Set<float> sf;
		sf.remove(3);
		*/
	}
	catch(RemoveFromEmpty ex) {
		cout<<endl<<ex.what()<<endl;
		cout<<"Nothing to be done\n";
	}
	catch(NonExistingElem ex) {
		cout<<endl<<ex.what()<<endl;
		cout<<"Nothing to be done\n";
	}
	cout<<"All is well when it ends well!\n";	
	return 0;
}

void info() {
	cout << "159.234 Assignment 2P1" << endl;
	cout << "Leonard Phillips   15232331" << endl;
	cout << endl;
}