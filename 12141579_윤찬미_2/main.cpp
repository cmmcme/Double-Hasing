#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

int n, q;	//배열의 크기 n과  2차 해싱을 위한 변수 q는 여러 함수에서 사용되기 때문에 전역변수로 선언한다
double m;	// 초기 아이템 개수 m loadfactor를 할때 소수점으로 나와야하기 때문에 double로 선언해줬다.
int Probe = 1;	//Probe 횟수를 세는 변수 1로 초기화 한다.

typedef struct Hash		//기본적 Hash 구조체 선언
{
	int keyval;  //학번
	int TotalS;   //학점
	string EM;  //이메일
	Hash() : keyval(0), TotalS(0) {};  //각 값을 초기화 한다.

}Hash;

Hash *Position;	//서치를 했을때 값을 기억하는 Hash형 포인터 변수를 선언한다.

void insert_stu(Hash *h, int Num, string Email)   //학생 입력받는것
{
	int key = Num%n;            //1차 해싱
	int jump = q - (Num%q);     //2차 해싱

	Probe = 1;	//첫 key값으로 가면 Probe가 1이기 때문에 초기화 시켜준다.

	if (h[key].keyval == 0)   //1차 해싱을 했을대 키값의 인덱스가 비어져있으면
	{
		h[key].keyval = Num;	//학번
		h[key].EM = Email;		//이메일 을 입력해주고
		m++;					//총 갯수를 1개 증가시킨다.
	}
	else    //1차 해싱에 비어있지 않으면
	{
		while (h[key].keyval != 0)	//비어져 있는 곳까지 2차 해싱 값을 더해준다
		{
			key += jump;
			key = key%n;	//key가 배열의 끝으로 가면 삽입할 수 없기때문에 mod n을 해준다.
			Probe++;		//2차 해싱 값을 더해주는 것은 Probe를 실행하는 것이기 때문에 Probe를 1증가시켜준다
		}
		//비어져 있는 곳을 찾으면
		h[key].keyval = Num;	//학번
		h[key].EM = Email;		//이메일을 입력해주고
		m++;					//총 갯수를 1개 증가시킨다.
	}
	cout << fixed;		//소수점 3째자리에서 반올림 해야하므로 fixed를 해준다.
	double load_factor = m / n;	//loadfactor를 구하는 식이다.
	cout << Probe << " " << setprecision(2) << load_factor << endl;
}

void Search(Hash *h, int Num)   //이메일이나 학점을 바꿔주거나 학번의 내용을 프린터 할때 위치를 찾아주는 함수이다.
{
	Probe = 1;	//Probe를 초기화 시킨다.

	int key = Num%n;            //1차 해싱
	int jump = q - (Num%q);     //2차 해싱

	while (h[key].keyval != Num)	//입력된 학점과 같을때 까지 반복문을 실행한다.
	{
		if (h[key].keyval == 0)	//만약 키값이 비어져 있다면 그 학번이 존재하지 않는 것임
		{
			cout << Probe << " Not found" << endl;	//Probe를 출력한다.
			return;
		}

		key += jump;	//2차 해싱의 값을 더해주며 찾아나간다.
		key = key%n;	//key가 배열의 끝으로 가면 찾을 수 없기때문에 mod n을 해준다.
		Probe++;		////2차 해싱 값을 더해주는 것은 Probe를 실행하는 것이기 때문에 Probe를 1증가시켜준다
	}
	Position = &h[key];	//Hash형 포인터 변수 Position은 찾은 키의 위치를 저장한다.
}

void insert_score(Hash *h, int Num, int S) //학점 추가
{
	Search(h, Num);		//Num이라는 해쉬테이블에서의 학번의 위치를 찾는다.

	if (Position != NULL)	//위치가 비어있지 않으면
	{
		if (Position->TotalS + S>24)	//그 학번의 총학점이 24학점을 넘으면
			cout << Probe << " Exceeded" << endl;	//초과했다고 출력한다.
		else					//초과하지 않았으면
		{
			Position->TotalS += S;	//학점을 추가해준다.
			cout << Probe << " " << Position->TotalS << endl;	//probe횟수와 더해준 총 학점을 출력한다.
		}
	}
}

void Trans(Hash *h, int Num, string Email)    //이메일 변경
{
	Search(h, Num);		//Num이라는 학번의 해쉬테이블에서의 위치를 찾는다.

	if (Position != NULL)	//위치가 비어있지 않으면
	{
		Position->EM = Email;	//이메일은 변경해주고,
		cout << Probe << endl;	//Probe 횟수를 출력한다.
	}
}

void print(Hash *h, int Num)	//Num학번의 정보를 출력하는 함수이다.
{
	Search(h, Num);	//Num학번의 위치를 찾는다.
	if (Position != NULL)	//위치가 비어있지 않으면
		cout << Probe << " " << Num << " " << Position->TotalS << " " << Position->EM << endl;		//Probe횟수, 학번, 총학점, 이메일을 출력한다.
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	string file;	//파일 이름
	int Num;   //학번
	int S;  //학점
	string E;   //이메일
	char Q;     //질문
	cin >> file;
	ifstream In(file);	//파일 입출력을 통해 file이라는 이름을 가지는 파일을 입력받는다.

	In >> n >> m >> q;    //그 파일 안에서 n테이블의 크기  m저장된 회원수 q소수 를 입력받고,

	Hash *arr = new Hash[n];    //해쉬 배열 크기를 지정한다.

	while (In >> Num >> S >> E) {	//학번, 학점, 이메일을 차례로 입력해준다.

		int key = Num%n;            //1차 해싱
		int jump = q - (Num%q);     //2차 해싱

		if (arr[key].keyval == 0)   //1차 해싱에 비어져있으면
		{
			arr[key].keyval = Num;		//학번
			arr[key].TotalS = S;		//학점
			arr[key].EM = E;			//이메일을 입력한다.
		}
		else    //1차 해싱에 비어있지 않으면
		{
			while (arr[key].keyval != 0)	//비어있는 배열의 위치까지 반복한다. 
			{
				key += jump;		//	key값에 2차 해싱의 값을 더해준다.
				key = key%n;		// 배열의 끝까지 가고 나서 삽입을 할 수 없기 때문에 mod n 을 해준다.
			}
			arr[key].keyval = Num;	//비어져 있는 위치에 도달하였을 때, 학번
			arr[key].TotalS = S;	//학점
			arr[key].EM = E;		//이메일 을 추가한다.

		}
	}

	while (1) {
		cin >> Q;	//질문을 받는다.
		switch (Q) {
		case 'A':       //학생 입력
			cin >> Num >> E;
			insert_stu(arr, Num, E);
			Position = NULL;
			break;

		case 'U':   //수강과목(학점) 추가
			cin >> Num >> S;
			insert_score(arr, Num, S);
			Position = NULL;
			break;

		case 'M':   //이메일 주소 변경
			cin >> Num >> E;
			Trans(arr, Num, E);
			Position = NULL;
			break;

		case 'P':   //학생 정보 출력
			cin >> Num;
			print(arr, Num);
			Position = NULL;
			break;

		case 'Q':	//Q가 들어오면 반복문을 종료한다.
			return 0;
		}
	}
}