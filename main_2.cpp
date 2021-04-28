//https://qiita.com/p1ro3/items/6bb1c78a6c27109f6b93
//https://qiita.com/asksaito/items/1793b8d8b3069b0b8d68
// CBCモードを用いたブロック暗号化
// CBCモードとは
// CBCモードとはCiper Block Chainingモードの略で1つ前の暗号ブロックと
// 平文ブロック(元のデータのブロック)のXORを取ってから暗号化を行う。

//-------------------暗号化と復号化におけるキーワード-------------------//
// 平文とは?
// 暗号化されていない元のデータのこと。
//
// 暗号文とは?
// 何らかの暗号アルゴリズムで秘匿化されたデータのこと。
//
// 初期ベクトル
// 同じ平文が同じ暗号文にならないようにするために使用するデータのこと。
// 平文中に同じデータが繰り返し出てきた際、すべてが同じ暗号文に変換されてしまうと、
// その頻度などから平文が推測されやすくなってしまう。
// 初期ベクトルは鍵と違って他人に知られても問題ないもの。
// 
// 
// 暗号モードとは?（英語:cipher mode）
// 初期ベクトルをどのように使用するか決めるモードのこと。
// 初期ベクトルの利用方法はいくつかの種類がる。
// ECB・CBC・PCBC・CFB・OFB・CTR・CTS・2DEM・ABC・IGEなど
//
// パディングとは?
// 暗号アルゴリズムにもよるが、暗号化をするにあたり平文のデータ長は、
// 何らかの倍数長でなければならない。
// 平文が倍数長になっていない場合、
// 平文に無駄なデータを付加することをパディングすると言う。
// パディングデータは復号時には除去される。
//
//----------------------------------------------------------------------//

#include <iostream>
#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>

#define Block 1

// 名前空間定義
using namespace std;

// 暗号を平文に復号する関数
void decode(char* dst);

int main()
{

    string fileName;    //ファイル名


    //ファイル名からバイナリファイルで読み込む
    std::cout << "復号化するファイル名を入力してください\n";
    //キーボード入力からファイル名を取得する
    getline(cin, fileName);
    std::ifstream ifs(fileName, std::ios::binary);

    string outFileName; //ファイル名
    //ofstreamを読み取りモードで開き、末尾に移動
    std::cout << "出力するファイル名を入力してください\n";
    //キーボード入力からファイル名を取得する
    getline(cin, outFileName);
    std::ofstream ofs(outFileName, std::ios::app | std::ios::binary);

    //読み込みデータ
    char data[Block];

    //初期化ベクトル
    char initialData[Block];
    memset(initialData, 'I', Block);

    //一時保存読み込みデータ
    char dataTemp[Block];

    //1つ前の暗号ブロック
    char cipherBlockPre[Block];

    //復号ブロック
    char decodeBlock[Block];

    //データ読込
    ifs.read(data, Block);
    //1つ前の暗号ブロックに暗号化されているブロックを格納
    memcpy(cipherBlockPre, data, Block);
    //復号化
    decode(data);
    //ブロック長ごとに処理
    for (int i = 0; i < Block; i++)
    {
        decodeBlock[i] = data[i] ^ initialData[i];
    }
    //暗号化したブロックを出力
    ofs.write(decodeBlock, Block);
    do {
        //データ読込
        ifs.read(data, Block);
        //データがなかった場合終了する。
        memcpy(dataTemp, data, Block);
        //復号化
        decode(data);
        if (ifs.eof()) break;
        //ブロック長ごとに処理
        for (int i = 0; i < Block; i++)
        {
            decodeBlock[i] = data[i] ^ cipherBlockPre[i];
        }
        //暗号化したブロックを出力
        ofs.write(decodeBlock, Block);
        //1つ前の暗号ブロックに暗号化されているブロックを格納
        memcpy(cipherBlockPre, dataTemp, Block);
    } while (true);

}

//復号化
void decode(char* dst)
{
    //暗号鍵
    char cipherBlockTemp[Block];
    memset(cipherBlockTemp, 'S', Block);

    //ブロック長ごとに処理
    for (int i = 0; i < Block; i++)
    {
        //XOR暗号
        dst[i] = dst[i] ^ cipherBlockTemp[i];
    }

    return;
}

