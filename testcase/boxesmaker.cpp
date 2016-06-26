#include <cstdio>
#include <cstdlib>
#include <ctime>

const int MaxN = 100;
const int MaxLen = 10;
using namespace std;

int main()
{
	File* fout = fopen("box.txt", "w");
	int N = rand() % MaxN + 1;
	fout( "%d\n" , N);
	for (int i = 0; i < N; ++i)
	{
		int x = rand() % MaxLen + 1;
		int y = rand() % MaxLen + 1;
		int z = rand() % MaxLen + 1;
		fout( "%d %d %d\n", x, y, z);
	}
	return 0;
}
