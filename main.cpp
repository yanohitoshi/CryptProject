
// CBCモードを用いたブロック暗号化
// CBCモードとは
// CBCモードとはCiper Block Chainingモードの略で1つ前の暗号ブロックと
// 平文ブロックのXORを取ってから暗号化を行う。

#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#define Block 1

// 名前空間定義
using namespace std;

// 関数プロトタイプ宣言
void cipher(char* dst);

int main()
{
    //インプットファイル名のstring変数
    string fileName;

    //ファイル名からバイナリファイルで読み込む
    cout << "暗号化するファイル名を入力してください\n";

    //キーボード入力からファイル名を取得する
    // ※getlineとは？
    // ストリームから改行文字が現れるまで（1行すべて）
    // あるいは仮引数delimで指定された文字までの文字列を入力する。
    getline(cin, fileName);

    // ファイルを開く
    ifstream ifs(fileName, std::ios::binary);

    //アウトプットファイル名のstring変数
    string outFileName;

    //ofstreamを読み取りモードで開き、末尾に移動
    cout << "出力するファイル名を入力してください\n";

    //キーボード入力からファイル名を取得する
    getline(cin, outFileName);
    ofstream ofs(outFileName, std::ios::app | std::ios::binary);

    //読み込みデータ
    char data[Block];

    //初期化ベクトル
    char initialData[Block];
    memset(initialData, 'I', Block);

    //1つ前の暗号ブロック
    char cipherBlockPre[Block];

    //暗号ブロック
    char cipherBlock[Block];

    //データ読込
    ifs.read(data, Block);

    //ブロック長ごとに処理
    for (int i = 0; i < Block; i++)
    {
        cipherBlock[i] = data[i] ^ initialData[i];
    }

    //暗号化
    cipher(cipherBlock);

    //暗号化したブロックを出力
    ofs.write(cipherBlock, Block);

    //1つ前の暗号ブロックに暗号化したブロックを格納
    memcpy(cipherBlockPre, cipherBlock, Block);

    do {
        //データ読込
        ifs.read(data, Block);
        //データがなかった場合終了する。
        if (ifs.eof()) break;
        //ブロック長ごとに処理
        for (int i = 0; i < Block; i++)
        {
            cipherBlock[i] = data[i] ^ cipherBlockPre[i];
        }
        //暗号化
        cipher(cipherBlock);
        //暗号化したブロックを出力
        ofs.write(cipherBlock, Block);
        //1つ前の暗号ブロックに暗号化したブロックを格納
        memcpy(cipherBlockPre, cipherBlock, Block);
    } while (true);

}

void cipher(char* dst)
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
