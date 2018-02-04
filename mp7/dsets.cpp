/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num)
{
	for (int i=0;i<=num;++i){
		_sets.push_back(-1);
	}
}

int DisjointSets::find(int elem)
{
	if (_sets[elem]<0) return elem;
	return find(_sets[elem]);
}

//union by size
void DisjointSets::setunion(int a, int b)
{
	int root1 = find(a);
	int root2 = find(b);
	if (root1 == root2) return;

	int temp = _sets[root1] + _sets[root2];
	if (_sets[root1] <= _sets[root2]){
		_sets[root2] = root1;
		_sets[root1] = temp;
	}
	else{
		_sets[root1] = root2;
		_sets[root2] = temp;
	}
}