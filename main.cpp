
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

int main()
{
    //�C���v�b�g�t�@�C������string�ϐ�
    string fileName;

    //�t�@�C��������o�C�i���t�@�C���œǂݍ���
    cout << "�Í�������t�@�C��������͂��Ă�������\n";

    //�L�[�{�[�h���͂���t�@�C�������擾����
    // ��getline�Ƃ́H
    // �X�g���[��������s�����������܂Łi1�s���ׂāj
    // ���邢�͉�����delim�Ŏw�肳�ꂽ�����܂ł̕��������͂���B
    getline(cin, fileName);

    // �t�@�C�����J��
    ifstream ifs(fileName, std::ios::binary);

    //�A�E�g�v�b�g�t�@�C������string�ϐ�
    string outFileName;

    //ofstream��ǂݎ�胂�[�h�ŊJ���A�����Ɉړ�
    cout << "�o�͂���t�@�C��������͂��Ă�������\n";

    //�L�[�{�[�h���͂���t�@�C�������擾����
    getline(cin, outFileName);
    ofstream ofs(outFileName, std::ios::app | std::ios::binary);

    //�ǂݍ��݃f�[�^
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

    do {
        //�f�[�^�Ǎ�
        ifs.read(data, Block);
        //�f�[�^���Ȃ������ꍇ�I������B
        if (ifs.eof()) break;
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
    } while (true);

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
