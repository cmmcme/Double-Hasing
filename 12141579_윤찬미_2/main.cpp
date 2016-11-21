#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

int n, q;	//�迭�� ũ�� n��  2�� �ؽ��� ���� ���� q�� ���� �Լ����� ���Ǳ� ������ ���������� �����Ѵ�
double m;	// �ʱ� ������ ���� m loadfactor�� �Ҷ� �Ҽ������� ���;��ϱ� ������ double�� ���������.
int Probe = 1;	//Probe Ƚ���� ���� ���� 1�� �ʱ�ȭ �Ѵ�.

typedef struct Hash		//�⺻�� Hash ����ü ����
{
	int keyval;  //�й�
	int TotalS;   //����
	string EM;  //�̸���
	Hash() : keyval(0), TotalS(0) {};  //�� ���� �ʱ�ȭ �Ѵ�.

}Hash;

Hash *Position;	//��ġ�� ������ ���� ����ϴ� Hash�� ������ ������ �����Ѵ�.

void insert_stu(Hash *h, int Num, string Email)   //�л� �Է¹޴°�
{
	int key = Num%n;            //1�� �ؽ�
	int jump = q - (Num%q);     //2�� �ؽ�

	Probe = 1;	//ù key������ ���� Probe�� 1�̱� ������ �ʱ�ȭ �����ش�.

	if (h[key].keyval == 0)   //1�� �ؽ��� ������ Ű���� �ε����� �����������
	{
		h[key].keyval = Num;	//�й�
		h[key].EM = Email;		//�̸��� �� �Է����ְ�
		m++;					//�� ������ 1�� ������Ų��.
	}
	else    //1�� �ؽ̿� ������� ������
	{
		while (h[key].keyval != 0)	//����� �ִ� ������ 2�� �ؽ� ���� �����ش�
		{
			key += jump;
			key = key%n;	//key�� �迭�� ������ ���� ������ �� ���⶧���� mod n�� ���ش�.
			Probe++;		//2�� �ؽ� ���� �����ִ� ���� Probe�� �����ϴ� ���̱� ������ Probe�� 1���������ش�
		}
		//����� �ִ� ���� ã����
		h[key].keyval = Num;	//�й�
		h[key].EM = Email;		//�̸����� �Է����ְ�
		m++;					//�� ������ 1�� ������Ų��.
	}
	cout << fixed;		//�Ҽ��� 3°�ڸ����� �ݿø� �ؾ��ϹǷ� fixed�� ���ش�.
	double load_factor = m / n;	//loadfactor�� ���ϴ� ���̴�.
	cout << Probe << " " << setprecision(2) << load_factor << endl;
}

void Search(Hash *h, int Num)   //�̸����̳� ������ �ٲ��ְų� �й��� ������ ������ �Ҷ� ��ġ�� ã���ִ� �Լ��̴�.
{
	Probe = 1;	//Probe�� �ʱ�ȭ ��Ų��.

	int key = Num%n;            //1�� �ؽ�
	int jump = q - (Num%q);     //2�� �ؽ�

	while (h[key].keyval != Num)	//�Էµ� ������ ������ ���� �ݺ����� �����Ѵ�.
	{
		if (h[key].keyval == 0)	//���� Ű���� ����� �ִٸ� �� �й��� �������� �ʴ� ����
		{
			cout << Probe << " Not found" << endl;	//Probe�� ����Ѵ�.
			return;
		}

		key += jump;	//2�� �ؽ��� ���� �����ָ� ã�Ƴ�����.
		key = key%n;	//key�� �迭�� ������ ���� ã�� �� ���⶧���� mod n�� ���ش�.
		Probe++;		////2�� �ؽ� ���� �����ִ� ���� Probe�� �����ϴ� ���̱� ������ Probe�� 1���������ش�
	}
	Position = &h[key];	//Hash�� ������ ���� Position�� ã�� Ű�� ��ġ�� �����Ѵ�.
}

void insert_score(Hash *h, int Num, int S) //���� �߰�
{
	Search(h, Num);		//Num�̶�� �ؽ����̺����� �й��� ��ġ�� ã�´�.

	if (Position != NULL)	//��ġ�� ������� ������
	{
		if (Position->TotalS + S>24)	//�� �й��� �������� 24������ ������
			cout << Probe << " Exceeded" << endl;	//�ʰ��ߴٰ� ����Ѵ�.
		else					//�ʰ����� �ʾ�����
		{
			Position->TotalS += S;	//������ �߰����ش�.
			cout << Probe << " " << Position->TotalS << endl;	//probeȽ���� ������ �� ������ ����Ѵ�.
		}
	}
}

void Trans(Hash *h, int Num, string Email)    //�̸��� ����
{
	Search(h, Num);		//Num�̶�� �й��� �ؽ����̺����� ��ġ�� ã�´�.

	if (Position != NULL)	//��ġ�� ������� ������
	{
		Position->EM = Email;	//�̸����� �������ְ�,
		cout << Probe << endl;	//Probe Ƚ���� ����Ѵ�.
	}
}

void print(Hash *h, int Num)	//Num�й��� ������ ����ϴ� �Լ��̴�.
{
	Search(h, Num);	//Num�й��� ��ġ�� ã�´�.
	if (Position != NULL)	//��ġ�� ������� ������
		cout << Probe << " " << Num << " " << Position->TotalS << " " << Position->EM << endl;		//ProbeȽ��, �й�, ������, �̸����� ����Ѵ�.
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	string file;	//���� �̸�
	int Num;   //�й�
	int S;  //����
	string E;   //�̸���
	char Q;     //����
	cin >> file;
	ifstream In(file);	//���� ������� ���� file�̶�� �̸��� ������ ������ �Է¹޴´�.

	In >> n >> m >> q;    //�� ���� �ȿ��� n���̺��� ũ��  m����� ȸ���� q�Ҽ� �� �Է¹ް�,

	Hash *arr = new Hash[n];    //�ؽ� �迭 ũ�⸦ �����Ѵ�.

	while (In >> Num >> S >> E) {	//�й�, ����, �̸����� ���ʷ� �Է����ش�.

		int key = Num%n;            //1�� �ؽ�
		int jump = q - (Num%q);     //2�� �ؽ�

		if (arr[key].keyval == 0)   //1�� �ؽ̿� �����������
		{
			arr[key].keyval = Num;		//�й�
			arr[key].TotalS = S;		//����
			arr[key].EM = E;			//�̸����� �Է��Ѵ�.
		}
		else    //1�� �ؽ̿� ������� ������
		{
			while (arr[key].keyval != 0)	//����ִ� �迭�� ��ġ���� �ݺ��Ѵ�. 
			{
				key += jump;		//	key���� 2�� �ؽ��� ���� �����ش�.
				key = key%n;		// �迭�� ������ ���� ���� ������ �� �� ���� ������ mod n �� ���ش�.
			}
			arr[key].keyval = Num;	//����� �ִ� ��ġ�� �����Ͽ��� ��, �й�
			arr[key].TotalS = S;	//����
			arr[key].EM = E;		//�̸��� �� �߰��Ѵ�.

		}
	}

	while (1) {
		cin >> Q;	//������ �޴´�.
		switch (Q) {
		case 'A':       //�л� �Է�
			cin >> Num >> E;
			insert_stu(arr, Num, E);
			Position = NULL;
			break;

		case 'U':   //��������(����) �߰�
			cin >> Num >> S;
			insert_score(arr, Num, S);
			Position = NULL;
			break;

		case 'M':   //�̸��� �ּ� ����
			cin >> Num >> E;
			Trans(arr, Num, E);
			Position = NULL;
			break;

		case 'P':   //�л� ���� ���
			cin >> Num;
			print(arr, Num);
			Position = NULL;
			break;

		case 'Q':	//Q�� ������ �ݺ����� �����Ѵ�.
			return 0;
		}
	}
}