#include <stdio.h>
#include <stdbool.h>

int main()
{
	// P0, P1, P2, P3, P4 are the Process names here

	int n, m;
	n = 5; // Number of processes
	m = 3; // Number of resources
	int alloc[5][3] = { { 0, 1, 0 }, // P0 // Allocation Matrix
						{ 2, 0, 0 }, // P1
						{ 3, 0, 2 }, // P2
						{ 2, 1, 1 }, // P3
						{ 0, 0, 2 }  // P4
						};

	int max[5][3] = { { 7, 5, 3 }, // P0 // MAX Matrix
					{ 3, 2, 2 }, // P1
					{ 9, 0, 2 }, // P2
					{ 2, 2, 2 }, // P3
					{ 4, 3, 3 }  // P4
					};

	int avail[3] = { 3, 3, 2 }; // Available Resources

	// f[n] array to track, which process has been visited
	int f[n];
	// Initializing f[n] with 0
	for (int k = 0; k < n; k++) {
		f[k] = 0;
	}

	// Making the neend matrix
	int need[n][m];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			need[i][j] = max[i][j] - alloc[i][j];
	}

	// Main
	int work[n][m], ans[n], ind = 0;
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			if (f[i] == 0) {
				int flag = 0;
				// Checking if all the resources are available
				for (int j = 0; j < m; j++) {
					if (need[i][j] > avail[j]){
						flag = 1;
						break;
					}
				}
				
				// Updating the available resources and marking the process as visited
				if (flag == 0) {
					ans[ind++] = i;
					for (int y = 0; y < m; y++)
						avail[y] += alloc[i][y];
						// work[i][y] = avail[y];
					f[i] = 1;
				}
			}
		}
	}

	int flag = 1;
	for(int i=0;i<n;i++)
	{
		if(f[i]==0)
		{
			flag=0;
			printf("The following system is not safe");
			break;
		}
	}
	
	if(flag==1)
	{
		printf("Following is the SAFE Sequence\n");
		for (int i = 0; i < n - 1; i++)
			printf(" P%d ->", ans[i]);
			printf(" P%d", ans[n - 1]);
	}
	
	printf("\n\n");

	return (0);
}
