#include "quad_tree.h"



int main()
{
	vector<vector<int>> vct, vct1;
	vct.resize(2);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			vct[i].push_back(j);
		}
	}
	tree<int> tr(vct);
	vct1 = tr.converte_to_matrix();

	system("pause");
	return 0;
}