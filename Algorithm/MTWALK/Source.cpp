#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <deque>
#include <algorithm>
#include <vector>

#include <conio.h>

using namespace std;
struct ToaDo {
	int x, y;
	ToaDo(int x1, int y1) {
		this->x = x1;
		this->y = y1;
	}
	ToaDo() {

	}
};
struct Cell {
	int _min, _max;
	Cell(int min, int max) {
		this->_min = min;
		this->_max = max;
	}
	Cell() {

	}
};

int A[123][123];
int B[123][123];
int n;
bool valid(ToaDo td) {
	return td.x >= 0 && td.x < n && td.y >= 0 && td.y < n;
}

int _Y[] = { 0,0,1,-1 };
int _X[] = { 1,-1,0,0 };
bool BFS(Cell c) {
	deque<ToaDo> DQ;
	ToaDo td = ToaDo(0, 0);
	DQ.push_back(td);
	while (!DQ.empty()) {
		//cout << td.x << " " << td.y << endl;
		td = DQ.front();
		DQ.pop_front();
		if (valid(td) && B[td.x][td.y] == 0) {
			if (A[td.x][td.y] <= A[0][0] + c._max && A[td.x][td.y] >= A[0][0] - c._min) {
				B[td.x][td.y] = 1;
				if (td.x == n - 1 && td.y == n - 1) {
					for (int i = 0; i < n; ++i) {
						for (int j = 0; j < n; ++j) {
							B[i][j] = 0;
						}
					}
					return true;
				}
				for (int i = 0; i < 4; ++i) {
					int newX = td.x + _X[i];
					int newY = td.y + _Y[i];
					if (valid(ToaDo(newX, newY)) && B[newX][newY] == 0) {
						DQ.push_back(ToaDo(newX, newY));
					}
				}
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			B[i][j] = 0;
		}
	}
	return false;
}
int main() {
	freopen("input.txt", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> A[i][j];
		}
	}
	for (int i = 0; i < 111; ++i) {
		if (BFS(Cell(i, i))) {
			for (int j = 0; j <= i; ++j) {
				if (BFS(Cell(j, i - j))) {
					cout << i << endl;
					_getch();
					return 0;
				}
			}
		}
	}
	_getch();
	return 0;
}