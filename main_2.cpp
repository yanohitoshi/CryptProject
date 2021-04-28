//https://qiita.com/p1ro3/items/6bb1c78a6c27109f6b93
//https://qiita.com/asksaito/items/1793b8d8b3069b0b8d68
// CBC���[�h��p�����u���b�N�Í���
// CBC���[�h�Ƃ�
// CBC���[�h�Ƃ�Ciper Block Chaining���[�h�̗���1�O�̈Í��u���b�N��
// �����u���b�N(���̃f�[�^�̃u���b�N)��XOR������Ă���Í������s���B

//-------------------�Í����ƕ������ɂ�����L�[���[�h-------------------//
// �����Ƃ�?
// �Í�������Ă��Ȃ����̃f�[�^�̂��ƁB
//
// �Í����Ƃ�?
// ���炩�̈Í��A���S���Y���Ŕ铽�����ꂽ�f�[�^�̂��ƁB
//
// �����x�N�g��
// ���������������Í����ɂȂ�Ȃ��悤�ɂ��邽�߂Ɏg�p����f�[�^�̂��ƁB
// �������ɓ����f�[�^���J��Ԃ��o�Ă����ہA���ׂĂ������Í����ɕϊ�����Ă��܂��ƁA
// ���̕p�x�Ȃǂ��畽������������₷���Ȃ��Ă��܂��B
// �����x�N�g���͌��ƈ���đ��l�ɒm���Ă����Ȃ����́B
// 
// 
// �Í����[�h�Ƃ�?�i�p��:cipher mode�j
// �����x�N�g�����ǂ̂悤�Ɏg�p���邩���߂郂�[�h�̂��ƁB
// �����x�N�g���̗��p���@�͂������̎�ނ���B
// ECB�ECBC�EPCBC�ECFB�EOFB�ECTR�ECTS�E2DEM�EABC�EIGE�Ȃ�
//
// �p�f�B���O�Ƃ�?
// �Í��A���S���Y���ɂ���邪�A�Í���������ɂ����蕽���̃f�[�^���́A
// ���炩�̔{�����łȂ���΂Ȃ�Ȃ��B
// �������{�����ɂȂ��Ă��Ȃ��ꍇ�A
// �����ɖ��ʂȃf�[�^��t�����邱�Ƃ��p�f�B���O����ƌ����B
// �p�f�B���O�f�[�^�͕������ɂ͏��������B
//
//----------------------------------------------------------------------//

#include <iostream>
#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>

#define Block 1

// ���O��Ԓ�`
using namespace std;

// �Í��𕽕��ɕ�������֐�
void decode(char* dst);

int main()
{

    string fileName;    //�t�@�C����


    //�t�@�C��������o�C�i���t�@�C���œǂݍ���
    std::cout << "����������t�@�C��������͂��Ă�������\n";
    //�L�[�{�[�h���͂���t�@�C�������擾����
    getline(cin, fileName);
    std::ifstream ifs(fileName, std::ios::binary);

    string outFileName; //�t�@�C����
    //ofstream��ǂݎ�胂�[�h�ŊJ���A�����Ɉړ�
    std::cout << "�o�͂���t�@�C��������͂��Ă�������\n";
    //�L�[�{�[�h���͂���t�@�C�������擾����
    getline(cin, outFileName);
    std::ofstream ofs(outFileName, std::ios::app | std::ios::binary);

    //�ǂݍ��݃f�[�^
    char data[Block];

    //�������x�N�g��
    char initialData[Block];
    memset(initialData, 'I', Block);

    //�ꎞ�ۑ��ǂݍ��݃f�[�^
    char dataTemp[Block];

    //1�O�̈Í��u���b�N
    char cipherBlockPre[Block];

    //�����u���b�N
    char decodeBlock[Block];

    //�f�[�^�Ǎ�
    ifs.read(data, Block);
    //1�O�̈Í��u���b�N�ɈÍ�������Ă���u���b�N���i�[
    memcpy(cipherBlockPre, data, Block);
    //������
    decode(data);
    //�u���b�N�����Ƃɏ���
    for (int i = 0; i < Block; i++)
    {
        decodeBlock[i] = data[i] ^ initialData[i];
    }
    //�Í��������u���b�N���o��
    ofs.write(decodeBlock, Block);
    do {
        //�f�[�^�Ǎ�
        ifs.read(data, Block);
        //�f�[�^���Ȃ������ꍇ�I������B
        memcpy(dataTemp, data, Block);
        //������
        decode(data);
        if (ifs.eof()) break;
        //�u���b�N�����Ƃɏ���
        for (int i = 0; i < Block; i++)
        {
            decodeBlock[i] = data[i] ^ cipherBlockPre[i];
        }
        //�Í��������u���b�N���o��
        ofs.write(decodeBlock, Block);
        //1�O�̈Í��u���b�N�ɈÍ�������Ă���u���b�N���i�[
        memcpy(cipherBlockPre, dataTemp, Block);
    } while (true);

}

//������
void decode(char* dst)
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

