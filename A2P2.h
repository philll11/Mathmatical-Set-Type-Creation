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
		const Set<EType> & operator=( const Set & rhs );
		Set<EType> & operator=( Set && rhs );
		Set<EType> operator+( const Set & rhs ) const; //set union
		Set operator*( const Set & rhs ) const; //set intersection
		//methods
		bool isElement( const EType & x ) const;
		bool isEmpty( ) const;
		int getSize( ) const;
		
		//display on out all elements in the set between {..}
		void print( ostream & out = cout ) const;	
		void setToEmptySet( );
		
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

template <typename EType>
Set<EType>::Set() : mFirst(nullptr), mSize(0) {}

template <typename EType>
Set<EType>::Set( const Set & rhs ) {
	mFirst = nullptr;
	mSize = 0;
	Node *currentNode = rhs.mFirst;	
	while(currentNode != nullptr) {
		this->insert(currentNode->mData);
		currentNode = currentNode->mNext;			
	}
}

template <typename EType>
Set<EType>::Set(Set &&rhs) {
	mSize = rhs.mSize;
	mFirst = rhs.mFirst;
	rhs.mSize = 0;
	rhs.mFirst = nullptr;
}

template <typename EType>
Set<EType>::~Set() {
	delete mFirst;
	mSize = 0;
}

template <typename EType>
const Set<EType>& Set<EType>::operator=( const Set & rhs ) {
	if(this != &rhs) {
		this->setToEmptySet();
		mSize = 0;
		Node *currentNode = rhs.mFirst;		
		while(currentNode != nullptr) {
			this->insert(currentNode->mData);
			currentNode = currentNode->mNext;			
		}
	}
	return *this;
}

template <typename EType>
Set<EType> & Set<EType>::operator=( Set && rhs ) {
	this->setToEmptySet();	
	mFirst = rhs.mFirst;
	mSize = rhs.mSize;	
	rhs.mFirst = nullptr;
	rhs.mSize = 0;	
	return *this;	
}

template <typename EType>
Set<EType> Set<EType>::operator+( const Set & rhs ) const {	
	Set *tempSet = new Set();
	Node *currentLhs = this->mFirst;	
	while(currentLhs != nullptr) {
		tempSet->insert(currentLhs->mData);
		currentLhs = currentLhs->mNext;
	}	
	Node *currentRhs = rhs.mFirst;	
	while(currentRhs != nullptr) {
		tempSet->insert(currentRhs->mData);
		currentRhs = currentRhs->mNext;
	}
	return *tempSet;
}

/* Works but produces a warning
template <typename EType>
Set<EType> Set<EType>::operator+( const Set & rhs ) const {
	Node *currentNode = rhs.mFirst;	
	while(currentNode != nullptr) {
		this->insert(currentNode->mData);
		currentNode = currentNode->mNext;
	}
	return *this;
}
*/
template <typename EType>
Set<EType> Set<EType>::operator*( const Set & rhs ) const {
	Set *tempSet = new Set();
	Node *currentNode = rhs.mFirst;
	while(currentNode != nullptr) {
		if(isElement(currentNode->mData)) {
			tempSet->insert(currentNode->mData);		
		}		
		currentNode = currentNode->mNext;
	}
	return *tempSet;
}

template <typename EType>
bool Set<EType>::isElement( const EType & x ) const {	
	Node *currentNode = mFirst;
	while(currentNode != nullptr) {		
		if(currentNode->mData == x) {
			return true;
		}
		currentNode = currentNode->mNext;			
	}
	return false;
}

template <typename EType>
bool Set<EType>::isEmpty( ) const {
	if(mFirst == nullptr) {
		return true;
	}
	return false;
}

template <typename EType>
int Set<EType>::getSize( ) const {
	return mSize;
}

template <typename EType>
void Set<EType>::print(ostream &out) const {
	Node *currentNode = mFirst;	
	while(currentNode != nullptr) {
		cout << currentNode->mData;
		currentNode = currentNode->mNext;
	}
}

template <typename EType>
void Set<EType>::setToEmptySet( ) {
	delete[] mFirst;
	mFirst = nullptr;
	mSize = 0;
}

template <typename EType>
void Set<EType>::insert(const EType &x) {
	if(!isElement(x)) {
		Node *currentNode = new Node(x);
		currentNode->mNext = mFirst;
		++mSize;
		mFirst = currentNode;
	}
}

template <typename EType>
void Set<EType>::remove(const EType &x) {
	if(mFirst == nullptr) { throw RemoveFromEmpty("List is empty"); }
	Node *currentNode = mFirst;
	Node *prevNode = nullptr;	
	while(currentNode != nullptr) {
		if(currentNode->mData == x) { break; }
		prevNode = currentNode;
		currentNode = currentNode->mNext;
	}
	if(currentNode == nullptr) { throw NonExistingElem("Element does not exist"); }
	prevNode->mNext = currentNode->mNext;
	delete currentNode;
	--mSize;
}


//	Not sure about this method. Ask Yukkie what it should do
//========part e-the output operator:
template <typename EType>
ostream & operator<<(ostream &out, const Set<EType> &rhs) {
	rhs.print(out);
	return out;
}

void info() {
	cout << "159.234 Assignment 2P1" << endl;
	cout << "Leonard Phillips   15232331" << endl;
	cout << endl;
}

#endif




























