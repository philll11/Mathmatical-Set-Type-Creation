#ifndef A2P2_H
#define A2P2_H
#include <exception>
#include <iostream>

using namespace std;

//========part a-Comments here:
//========part b-author's details
void info();

//========part c-exception classes:
class RemoveFromEmpty : public exception{
	public:
		RemoveFromEmpty(const string _mMessage);
		virtual const char* what() const noexcept;
	private:
		string mMessage;
};

RemoveFromEmpty::RemoveFromEmpty(const string _mMessage) : mMessage(_mMessage) {}

const char* RemoveFromEmpty::what() const noexcept {
	return mMessage.c_str();	
}

class NonExistingElem : public exception{
//to be thrown when the element to be removed is not found in
//the set --------code missing 
	public:
		NonExistingElem(string _mMessage); 
		virtual const char* what() const noexcept;
	private:
		string mMessage;
};

NonExistingElem::NonExistingElem(string _mMessage) : mMessage(_mMessage) {}

const char* NonExistingElem::what() const noexcept {
	return mMessage.c_str();	
}


//========part d-Set class template
template <typename EType>
class Set{
	public:
		//constructors
		Set( );
		Set( const Set & rhs );
		Set( Set && rhs );		
		//destructor
		~Set( );
		//operators overloaded
		//Set & operator=( const Set & rhs );
		//Set & operator=( Set && rhs );
		//Set operator+( const Set & rhs ) const; //set union
		//Set operator*( const Set & rhs ) const; //set intersection
		//methods
		bool isElement( const EType & x ) const;
		bool isEmpty( ) const;
		int getSize( ) const;
		
		//display on out all elements in the set between {..}
		void print( ostream & out = cout ) const;		
		//void setToEmptySet( );
		
		//methods to work with individual elements of a set
		void insert( const EType & x );
		void remove( const EType & x );
		
	private:
		struct Node{// type of the elements of the set
			EType mData;
			Node *mNext;
			Node( const EType & d = EType( ), Node *n = nullptr )
			: mData( d ), mNext( n ) { }
		};
		Node *mFirst;
		int mSize; // to have an efficient getSize().
};
//Write the definitions of all Set function members here:
template <typename EType>
Set<EType>::Set() : mFirst(new Node()), mSize(0) {}

template <typename EType>
Set<EType>::Set( const Set & rhs ) : mSize(rhs.mSize), mFirst(new Node()) {	
	mFirst = rhs->mFirst;
}

template <typename EType>
Set<EType>::Set(Set &&rhs) {
	mSize = rhs.mSize;
	mFirst = rhs->mFrist;
	
	rhs.mSize = 0;
	rhs->mFirst = nullptr;
}

template <typename EType>
Set<EType>::~Set() {
	delete mFirst;
}
/*
Set & operator=( const Set & rhs ) {
	
	
}
*/
template <typename EType>
bool Set<EType>::isElement( const EType & x ) const {
	Node *temp = mFirst;
	while(temp->mNext != nullptr) {
		if(temp->mData == x) {
			return true;
		}
		temp = temp->mNext;			
	}
	return false;
}

template <typename EType>
bool Set<EType>::isEmpty( ) const {
	if(mFirst->mNext == nullptr) {
		return true;
	}
	return false;
}

template <typename EType>
int Set<EType>::getSize( ) const {
	return mSize;
}


//	Add to the back not the front
template <typename EType>
void Set<EType>::print(ostream &out) const {
	Node *current = mFirst;	
	while(true) {
		if(current == nullptr) { break; }
		cout << current->mData;
		current = current->mNext;
	}
}

// Issue with mFirst. The first node in the list had a 0 and need to be written over.
template <typename EType>
void Set<EType>::insert(const EType &x) {
	Node *current = mFirst;
	while(true) {
		if(current->mNext == nullptr) {
			Node *temp = new Node(x);
			current->mNext = temp;
			++mSize;
			break;
		} else {
			current = current->mNext;
		}
	}
}

template <typename EType>
void Set<EType>::remove(const EType &x) {
	if(mFirst->mNext == nullptr) { throw RemoveFromEmpty("List is empty"); }
	Node *current = mFirst;
	Node *prev = nullptr;	
	while(current != nullptr) {
		if(current->mData == x) { break; }
		prev = current;
		current = current->mNext;
	}
	if(current == nullptr) {
		throw NonExistingElem("Element does not exist");
	}
	if(prev == nullptr) {
		mFirst = current->mNext;
	}
	else {
		prev->mNext = current->mNext;
	}
	delete current;
	--mSize;
}


//	Not sure about this method. Ask Yukkie what it should do
//========part e-the output operator:
template <typename EType>
ostream & operator<<(ostream &out, const Set<EType> &rhs) {
	rhs.print(out);
	return out;
}

#endif




























