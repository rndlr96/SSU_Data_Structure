#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

template <class T>
class Bag{//템플릿 클래스 백 선언
	private:
		T* array;
		int capacity;
		int top;
	public:
		Bag(int bagCapacity = 3);//capacity의디폴트값이 3인 Bag생성자 선언
		~Bag();
		int size() const;
		int IsEmpty() const;
		T& Element() const;
		void Push(const T&);
		void Pop();
		void ChangeSize1D(T*&, int, int);
};

template <class T>
Bag<T>::Bag(int bagCapacity): capacity(bagCapacity){//Bag 클래스의 생성자
	if(capacity < 1) throw string("Capacity must be > 0");//capacity가 1보다 작으면 예외처리
	array = new T[capacity];
	top = -1;
}

template <class T>
Bag<T>::~Bag() {delete []array;}//array에 동적할당된 공간을 회수하는 소멸자

template <class T>
void Bag<T>::ChangeSize1D(T*& a, const int oldSize, const int newSize)//Bag이 가득 찼다면 공간 2배
{
	if(newSize < 0) throw string("New length must be >= 0");
	T* temp = new T[newSize];
	int number = min(oldSize, newSize);//oldsize와 newsize중 더 작은 크기를 number에 저장
	copy(a, a+number, temp);
	delete []a;//과거 배열 메모리 반환
	a = temp;
}

template <class T>
void Bag<T>::Push(const T& x){//T형 변수 백에 삽입하는 함수
	if(capacity == top+1)
	{
		ChangeSize1D(array, capacity, 2*capacity);//더 이상 공간이 없을대 공간이 2배인 배열을 만들어 복사
		capacity*=2;
	}
	array[++top] = x;
}

template <class T>
void Bag<T>::Pop(){//bag의 중간에 있는 값 제거후 왼쪽으로 한칸씩 밀기
	if(IsEmpty()) throw string("Bag is empty, cannot delete");//capacity가 0일 경우 예외처리
	int deletePos = top/2;//중간의 위치
	copy(array+deletePos+1, array+top+1, array+deletePos);//왼쪽으로 밀기
	array[top--].~T();//소멸자 불러와 메모리 회수
}

template <class T>
inline T& Bag<T>::Element() const{//가운데 값 출력하는 함수
	if(IsEmpty()) string("Bag is empty");
	return array[top/2];
}

template <class T>
inline int Bag<T>::IsEmpty() const{//bag에 변수가 들어가 있으면 0 들어가있지 않으면 1 반환
	if(top==-1)
		return 1;
	else
		return 0;
}

template <class T>
inline int Bag<T>::size() const{//Bag에 저장되어있는 변수의 개수 반환
	return top+1;
}

class Bizcard{
	public:
		Bizcard():name(NULL), phone(NULL){}//디폴트 생성자 정의
		Bizcard(const char * tname, const char * tphone){//name과 phone에 동적활당하고 문자열 복사
			name = new char[strlen(tname)+1];
			strcpy(name, tname);
			phone = new char[strlen(tphone)+1];
			strcpy(phone, tphone);
		}
		~Bizcard(){//name과 phone의 메모리 회수하고 소멸시키는 소멸자
			name = NULL;
			phone = NULL;
			delete[] name;
			delete[] phone;
		}
		void ShowInfo() const{//name과 phone 정보 출력하는 함수
			cout<<name<<endl;
			cout<<phone<<endl;
		}
	private:
		char* name;
		char* phone;
};

int main(void){
	Bag<int> a = Bag<int>();//int형 함수 탬플릿 인스턴스화
	cout<<"size : "<<a.size()<<endl;
	try{//a.IsEmpth()에서 예외 발생시 catch로 이동
		if(a.IsEmpty()==1)
			cout<<"Bag is empty"<<endl;
		else
			cout<<"Bag is not empty"<<endl;
	}
	catch(string a){
		cout<<a<<endl;
	}
	try{//a.Element()에서 예외 발생시 catch로 이동
		cout<<"num : "<<a.Element()<<endl;
	}
	catch(string a){
		cout<<a<<endl;
	}
	cout<<endl;

	a.Push(11);//정수 push
	a.Push(22);
	a.Push(33);
	cout<<"size : "<<a.size()<<endl;
	try{
		if(a.IsEmpty()==1)
			cout<<"Bag is empty"<<endl;
		else
			cout<<"Bag is not empty"<<endl;
	}
	catch(string a){
		cout<<a<<endl;
	}
	try{
		cout<<"num : "<<a.Element()<<endl;
	}
	catch(string a){
		cout<<a<<endl;
	}
	cout<<endl;

	a.Push(111);//정수 push
	a.Push(222);
	a.Push(333);
	a.Push(444);
	cout<<"size : "<<a.size()<<endl;
	try{
		if(a.IsEmpty()==1)
			cout<<"Bag is empty"<<endl;
		else
			cout<<"Bag is not empty"<<endl;
	}
	catch(string a){
		cout<<a<<endl;
	}
	try{
		cout<<"num : "<<a.Element()<<endl;
	}
	catch(string a){
		cout<<a<<endl;
	}
	cout<<endl;

	a.Pop();//int형bag의 가운데 것을 빼고 한칸씩 왼쪽으로 민다.
	a.Pop();  
	cout<<"size : "<<a.size()<<endl;
	try{
		if(a.IsEmpty()==1)
			cout<<"Bag is empty"<<endl;
		else
			cout<<"Bag is not empty"<<endl;
	}
	catch(string a){
		cout<<a<<endl;
	}
	try{
		cout<<"num : "<<a.Element()<<endl;
	}
	catch(string a){
		cout<<a<<endl;
	}
	cout<<endl;

	Bag<Bizcard>* bizcard = new Bag<Bizcard>();//Bizcard형 함수 태플릿 선언
	cout<<"size : "<<bizcard->size()<<endl;
	try{
		if(bizcard->IsEmpty()==1)
			cout<<"Bag is empty"<<endl;
		else
			cout<<"Bag is not empty"<<endl;
	}
	catch(string a){
		cout<<a<<endl;
	}
	try{
		if(bizcard->IsEmpty()==1)//Bag이 비어있다면 "Bag is empty"를 catch로 던져주어 showinfo() 생략
			throw string("Bag is empty");
		bizcard->Element().ShowInfo();
	}
	catch(string a){
		cout<<a<<endl;
	}
	cout<<endl;

    Bizcard biz1("JUNG","010-8484-2039");//Bizcard형 객체 생성
	bizcard->Push(biz1);//Bizcard 객체를 push로 bag에 넣어준다.
    Bizcard biz2("LEE","010-3444-6935");
	bizcard->Push(biz2);
	Bizcard biz3("KIM","010-5034-0530");
	bizcard->Push(biz3);
	cout<<"size : "<<bizcard->size()<<endl;
	try{
		if(bizcard->IsEmpty()==1)
			cout<<"Bag is empty"<<endl;
		else
			cout<<"Bag is not empty"<<endl;
	}
	catch(string a){
		cout<<a<<endl;
	}
	try{
		bizcard->Element().ShowInfo();
	}
	catch(string a){
		cout<<a<<endl;
	}
	cout<<endl;

	Bizcard biz4("SEU","010-9295-5323");
	bizcard->Push(biz4);
	Bizcard biz5("SONG","010-1234-3563");
	bizcard->Push(biz5);
	Bizcard biz6("PARK","010-4321-5326");
	bizcard->Push(biz6);
	Bizcard biz7("YOU","010-6543-9568");
	bizcard->Push(biz7);
	cout<<"size : "<<bizcard->size()<<endl;
	try{
		if(bizcard->IsEmpty()==1)
			cout<<"Bag is empty"<<endl;
		else
			cout<<"Bag is not empty"<<endl;
	}
	catch(string a){
		cout<<a<<endl;
	}
	try{
		bizcard->Element().ShowInfo();
	}
	catch(string a){
		cout<<a<<endl;
	}
	cout<<endl;

	bizcard->Pop();//Bizcard Bag의 가운데 값 제거 후 왼쪽으로 밀기
	bizcard->Pop();
	cout<<"size : "<<bizcard->size()<<endl;
	try{
		if(bizcard->IsEmpty()==1)
			cout<<"Bag is empty"<<endl;
		else
			cout<<"Bag is not empty"<<endl;
	}
	catch(string a){
		cout<<a<<endl;
	}
	try{
		bizcard->Element().ShowInfo();
	}
	catch(string a){
		cout<<a<<endl;
	}
	cout<<endl;
	return 0;
}
