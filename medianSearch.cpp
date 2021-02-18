#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

int getKeyValue( const char curr) {
	int res = 0;
	switch ( curr) {
		case 'A':
			res = 1;
			break;
		case 'C':
			res = 2;
			break;
		case 'G':
			res = 3;
			break;
		case 'T':
			res = 4;
			break;
	}
	return res;
}

char getKey( const int curr) {
	char res = 'U';
	switch ( curr) {
		case 1:
			res = 'A';
			break;
		case 2:
			res = 'C';
			break;
		case 3:
			res = 'G';
			break;
		case 4:
			res = 'T';
			break;
	}
	return res;
}

void convertKeys( const string &dna, int **&seq, const int &t, const int &n) {
	int seqNo = 0, seqPtr = 0;

	seq = new int *[t];
	for ( int i = 0; i < t; i++)
		seq[i] = new int[n];

	for ( int i = 0; i < dna.length(); i++) {
		char current = dna.at(i);
		if ( current == 10) {
			seqNo++;
			seqPtr = 0;
		}
		else {
			seq[seqNo][seqPtr] = getKeyValue( current);
			seqPtr++;
		}
	}

}

int totalDistance( int *&pattern, int **&seq, const int t, const int n, int k) {
	int totalDist = 0;

	for ( int i = 0; i < t; i++) {
		int bestDist = n;
		for ( int j = 0; j < n-k+1; j++) {
			int currDist = 0;
			for ( int q = 0; q < k; q++) {
				if ( pattern[q] != seq[i][j+q])
					currDist++;
			}
			if ( currDist < bestDist)
				bestDist = currDist;
		}
		totalDist = totalDist + bestDist;
	}
	return totalDist;
}

void nextVertex( int *&s, int &i, const int k, const int maxKey) {
	if ( i < k) {
		s[i] = 1;
		i++;
		return;
	}
	else {
		for ( int j = k-1; j >= 0; j--) {
			if ( s[j] < maxKey) {
				s[j] = s[j] + 1;
				i = j + 1;
				return;
			}
		}
	}
	i = 0;
}

void byPass( int *&s, int &i, const int k, const int maxKey) {
	for ( int j = i-1; j >= 0; j--) {
		if ( s[j] < maxKey) {
			s[j] = s[j] + 1;
			i = j + 1;
			return;
		}
	}
	i = 0;
}

int* MedianStringSearch( int **&seq, const int t, const int n, const int k) {
	int *s = new int[k], *bestWord = new int[k];
	int bestDist = n, optDist;
	
	for ( int i = 0; i < k; i++)
		s[i] = 1;

	int i = 1;
	while ( i > 0) {
		int *prefix = new int[i];
		if ( i < k) {
			for ( int j = 0; j < i; j++) {
				prefix[j] = s[j];
			}
			optDist = totalDistance( s, seq, t, n, i);
			if ( optDist > bestDist)
				byPass( s, i, k, 4);
			else
				nextVertex( s, i, k, 4);
		}
		else {
			int currDist = totalDistance( s, seq, t, n, k);
			if ( currDist < bestDist) {
				bestDist = currDist;
				for ( int j = 0; j < k; j++)
					bestWord[j] = s[j];
			}
			nextVertex( s, i, k, 4);
		}
	}
	delete [] s;
	return bestWord;
}

int main( int argc, char **argv)
{
	string dna = "";
	int **seq;
	int t = 0, n = 0, k = 0;

	if (argc < 2) {
		cout << "Input file required.\n";
		return 1;
	}
	else if ( argc < 3) {
		cout << "Output file required.\n";
		return 1;
	}
	else {		
		ifstream inFile;
		inFile.open( argv[1]);

		if ( inFile.is_open()) {
			string line;
			while ( getline( inFile, line)) {
				if ( k == 0) {
					k = stoi(line);
				}
				else {
					n = line.length();
					dna = dna + line + "\n";
					t++;
				}
			}
			inFile.close();
		}
	}
	if ( dna.compare( "") == 0) {
		cout << "Input file is corrupted.\n";
		return 1;
	}

	convertKeys( dna, seq, t, n);

	int *res = MedianStringSearch( seq, t, n, k);
	string resStr = "";
	for ( int i = 0; i < k; i++) {
		resStr = resStr + getKey(res[i]);
	}
	resStr = resStr + "\n";

	ofstream outFile;
	outFile.open( argv[2]);
	if ( outFile.is_open()) {
		outFile << resStr;
		outFile.close();
	}

	// this part sometimes throws errors, I was not able to identify the problem
	// here as it looks fine and works for some inputs and not for input0.txt
	for ( int i = 0; i < t; i++) {
		free(seq[i]);
	}
	delete [] seq;
	delete [] res;

    return 0;
}


