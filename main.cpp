
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

int main(int argc, char* argv[])
{

    if (argc <= 1)
    {
        cout << "コマンドライン引数が空です。" << endl;
        cout << "Enterキーで終了" << endl;
        getchar();
        return 0;
    }
    else
    {
        cout << argc << endl;
    }

    string fileName = argv[1];

    cout << fileName << endl;

    ////インプットファイル名のstring変数
    //string fileName;

    ////ファイル名からバイナリファイルで読み込む
    //cout << "暗号化するファイル名を入力してください\n";

    ////キーボード入力からファイル名を取得する
    //// ※getlineとは？
    //// ストリームから改行文字が現れるまで（1行すべて）
    //// あるいは仮引数delimで指定された文字までの文字列を入力する。
    //getline(cin, fileName);  

    //cout << fileName << endl;

    // ファイルを開く
    ifstream ifs(fileName, ios::binary);

    if (!ifs)
    {
        cout << "空です。" << endl;
        cout << "Enterキーで終了" << endl;
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


    ////アウトプットファイル名のstring変数
    //string outFileName;

    ////ofstreamを読み取りモードで開き、末尾に移動
    //cout << "出力するファイル名を入力してください\n";

    //////キーボード入力からファイル名を取得する
    //getline(cin, outFileName);

    // 何も書かれていないファイルを出力
    ofstream ofs(outFileName, ios::app | ios::binary);

    //読み込みデータ
    // ifsをコピーする箱
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

    int count = 0;

    do {

        ++count;
        cout << count << endl;

        //データ読込
        ifs.read(data, Block);

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

    } while (!ifs.eof());

    return 0;

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
