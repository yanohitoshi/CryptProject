#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	//�C���v�b�g����t�@�C����
	string inFileName;

	//�t�@�C��������o�C�i���t�@�C���œǂݍ���
	cout << "�Í�������t�@�C��������͂��Ă�������\n";

	//�L�[�{�[�h���͂���t�@�C�������擾����
	getline(cin, inFileName);
	ifstream ifs(inFileName, ios::binary);

	//�A�E�g�v�b�g����t�@�C����
	string outFileName;

	//ofstream��ǂݎ�胂�[�h�ŊJ���A�����Ɉړ�
	cout << "�o�͂���t�@�C��������͂��Ă�������\n";

	//�L�[�{�[�h���͂���t�@�C�������擾����
	getline(cin, outFileName);
	ofstream ofs(outFileName, ios::app | ios::binary);

	return 0;
}
