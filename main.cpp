
// CBC���[�h��p�����u���b�N�Í���
// CBC���[�h�Ƃ�
// CBC���[�h�Ƃ�Ciper Block Chaining���[�h�̗���1�O�̈Í��u���b�N��
// �����u���b�N��XOR������Ă���Í������s���B

#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>

#define Block 1

// ���O��Ԓ�`
using namespace std;

// �֐��v���g�^�C�v�錾
void cipher(char* dst);

int main(int argc, char* argv[])
{

    if (argc <= 1)
    {
        cout << "�R�}���h���C����������ł��B" << endl;
        cout << "Enter�L�[�ŏI��" << endl;
        getchar();
        return 0;
    }
    else
    {
        cout << argc << endl;
    }

    string fileName = argv[1];

    cout << fileName << endl;

    ////�C���v�b�g�t�@�C������string�ϐ�
    //string fileName;

    ////�t�@�C��������o�C�i���t�@�C���œǂݍ���
    //cout << "�Í�������t�@�C��������͂��Ă�������\n";

    ////�L�[�{�[�h���͂���t�@�C�������擾����
    //// ��getline�Ƃ́H
    //// �X�g���[��������s�����������܂Łi1�s���ׂāj
    //// ���邢�͉�����delim�Ŏw�肳�ꂽ�����܂ł̕��������͂���B
    //getline(cin, fileName);  

    //cout << fileName << endl;

    // �t�@�C�����J��
    ifstream ifs(fileName, ios::binary);

    if (!ifs)
    {
        cout << "��ł��B" << endl;
        cout << "Enter�L�[�ŏI��" << endl;
        getchar();
        return 0;
    }

    //if (argv[3] != nullptr)
    //{
    //    printf("%s\n", argv[3]);
    //}
    //else
    //{
    //    printf("NULL\n");
    //    return 0;
    //}

    const char* cstr2 = argv[3];

    string outFileName = cstr2;

    cout << outFileName << endl;


    ////�A�E�g�v�b�g�t�@�C������string�ϐ�
    //string outFileName;

    ////ofstream��ǂݎ�胂�[�h�ŊJ���A�����Ɉړ�
    //cout << "�o�͂���t�@�C��������͂��Ă�������\n";

    //////�L�[�{�[�h���͂���t�@�C�������擾����
    //getline(cin, outFileName);

    // ����������Ă��Ȃ��t�@�C�����o��
    ofstream ofs(outFileName, ios::app | ios::binary);

    //�ǂݍ��݃f�[�^
    // ifs���R�s�[���锠
    char data[Block];

    //�������x�N�g��
    char initialData[Block];
    memset(initialData, 'I', Block);

    //1�O�̈Í��u���b�N
    char cipherBlockPre[Block];

    //�Í��u���b�N
    char cipherBlock[Block];

    //�f�[�^�Ǎ�
    ifs.read(data, Block);

    //�u���b�N�����Ƃɏ���
    for (int i = 0; i < Block; i++)
    {
        cipherBlock[i] = data[i] ^ initialData[i];
    }

    //�Í���
    cipher(cipherBlock);

    //�Í��������u���b�N���o��
    ofs.write(cipherBlock, Block);

    //1�O�̈Í��u���b�N�ɈÍ��������u���b�N���i�[
    memcpy(cipherBlockPre, cipherBlock, Block);

    int count = 0;

    do {

        ++count;
        cout << count << endl;

        //�f�[�^�Ǎ�
        ifs.read(data, Block);

        //�u���b�N�����Ƃɏ���
        for (int i = 0; i < Block; i++)
        {
            cipherBlock[i] = data[i] ^ cipherBlockPre[i];
        }

        //�Í���
        cipher(cipherBlock);

        //�Í��������u���b�N���o��
        ofs.write(cipherBlock, Block);

        //1�O�̈Í��u���b�N�ɈÍ��������u���b�N���i�[
        memcpy(cipherBlockPre, cipherBlock, Block);

    } while (!ifs.eof());

    return 0;

}

void cipher(char* dst)
{
    //�Í���
    char cipherBlockTemp[Block];

    memset(cipherBlockTemp, 'S', Block);

    //�u���b�N�����Ƃɏ���
    for (int i = 0; i < Block; i++)
    {
        //XOR�Í�
        dst[i] = dst[i] ^ cipherBlockTemp[i];
    }

    return;
}
