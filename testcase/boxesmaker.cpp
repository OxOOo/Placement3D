#include <cstdio>
#include <cstdlib>
#include <ctime>

const int MaxN = 20;
const int MaxLen = 10;
using namespace std;

int main()
{
	srand(time(0));
	FILE* fout = fopen("box.txt", "w");
	int N = 100;
	fprintf(fout, "%d\n" , N);
	for (int i = 0; i < N; ++i)
	{
		int x = rand() % MaxLen + 1;
		int y = rand() % MaxLen + 1;
		int z = rand() % MaxLen + 1;
		fprintf(fout, "%d %d %d\n", x, y, z);
	}
	return 0;
}
