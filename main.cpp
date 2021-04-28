#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	//インプットするファイル名
	string inFileName;

	//ファイル名からバイナリファイルで読み込む
	cout << "暗号化するファイル名を入力してください\n";

	//キーボード入力からファイル名を取得する
	getline(cin, inFileName);
	ifstream ifs(inFileName, ios::binary);

	//アウトプットするファイル名
	string outFileName;

	//ofstreamを読み取りモードで開き、末尾に移動
	cout << "出力するファイル名を入力してください\n";

	//キーボード入力からファイル名を取得する
	getline(cin, outFileName);
	ofstream ofs(outFileName, ios::app | ios::binary);

	return 0;
}
