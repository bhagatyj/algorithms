#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// http://www.geeksforgeeks.org/check-whether-a-given-string-is-an-interleaving-of-two-other-given-strings-set-2/
//
//
bool isInterleave(char* s1, char* s2, char* s3) {
	int len1, len2, len3, i, j, k, answer;
	int **ans;

	len1 = strlen(s1);
	len2 = strlen(s2);
	len3 = strlen(s3);

	printf("len1:%d len2:%d len3:%d\n", len1, len2, len3);

    if ( (len1 == 0) && (len2 == 0) && (len3 == 0) ) {
        return true;
    }

	if (len3 != len1+len2) { return false; }
    if (len1 == 0) { return ! strcmp(s2, s3) ; }
    if (len2 == 0) { return ! strcmp(s1, s3) ; }

	ans = (int **) malloc( (len1+1) * sizeof( int * ) );
	for ( i=0; i<(len1+1); i++) {
		ans[i] = (int *) malloc( (len2+1) * sizeof( int ) );
		memset( ans[i], 0, (len2+1) * sizeof( int ) );
	}

	ans[0][0] = 1;

	for ( i=1; i<=len1; i++) {
		if ( s1[i-1] == s3[i-1] ) {
			ans[i][0] = ans[i-1][0];
		}
	}
	for ( j=1; j<=len2; j++) {
		if ( s2[j-1] == s3[j-1] ) {
			ans[0][j] = ans[0][j-1];
		}
	}
	for ( i=1; i<=len1; i++ ) {
		for ( j=1; j<=len2; j++ ) {
			// Derive the rest of the cells
			if ( ( s3[i+j-1] == s1[i-1] ) &&
				 ( s3[i+j-1] != s2[j-1] ) ) {
				ans[i][j] = ans[i-1][j];
				continue;
			} 
			if ( ( s3[i+j-1] != s1[i-1] ) &&
				 ( s3[i+j-1] == s2[j-1] ) ) {
				ans[i][j] = ans[i][j-1];
				continue;
			}
			if ( ( s3[i+j-1] == s1[i-1] ) &&
				 ( s3[i+j-1] == s2[j-1] ) ) {
				ans[i][j] = ans[i][j-1] || ans[i-1][j];
				continue;
			}
		}
	}
	answer = ans[len1][len2];
	for ( i=0; i<=(len1); i++) {
		free(ans[i]);
	}
	free(ans);
	return answer;
}


int main () {
	char *s1 = "aabcc";
	char *s2 = "dbbca";
	char *s3 = "aadbbcbcac";
	char *s4 = "aadbbbaccc";

	char *sa1 = "abbbbbbcabbacaacccababaabcccabcacbcaabbbacccaaaaaababbbacbb";
	char *sa2 = "ccaacabbacaccacababbbbabbcacccacccccaabaababacbbacabbbbabc";
	char *sa3 = "cacbabbacbbbabcbaacbbaccacaacaacccabababbbababcccbabcabbaccabcccacccaabbcbcaccccaaaaabaaaaababbbbacbbabacbbacabbbbabc";

	assert(isInterleave("aa", "", "aa") == 1);
	assert(isInterleave("", "ab", "ab") == 1);
	assert(isInterleave("aa", "ab", "abaa") == 1);
	assert(isInterleave("aabcc", "dbbca", "aadbbcbcac") == 1);
	assert(isInterleave("aabcc", "dbbca", "aadbbbaccc") == 0);
	assert(isInterleave(sa1, sa2, sa3) == 1);
	char *sb1 = "bbbbbabbbbabaababaaaabbababbaaabbabbaaabaaaaababbbababbbbbabbbbababbabaabababbbaabababababbbaaababaa";
	char *sb2 = "babaaaabbababbbabbbbaabaabbaabbbbaabaaabaababaaaabaaabbaaabaaaabaabaabbbbbbbbbbbabaaabbababbabbabaab";
	char *sb3 = "babbbabbbaaabbababbbbababaabbabaabaaabbbbabbbaaabbbaaaaabbbbaabbaaabababbaaaaaabababbababaababbababbbababbbbaaaabaabbabbaaaaabbabbaaaabbbaabaaabaababaababbaaabbbbbabbbbaabbabaabbbbabaaabbababbabbabbab";
	assert(isInterleave(sb1, sb2, sb3) == 0);
 
	char *sc1 = "cbcccbabbccbbcccbbbcabbbabcababbbbbbaccaccbabbaacbaabbbc";
	char *sc2 = "abcbbcaababccacbaaaccbabaabbaaabcbababbcccbbabbbcbbb";
	char *sc3 = "abcbcccbacbbbbccbcbcacacbbbbacabbbabbcacbcaabcbaaacbcbbbabbbaacacbbaaaabccbcbaabbbaaabbcccbcbabababbbcbbbcbb";
	assert(isInterleave(sc1, sc2, sc3) == 1);
}

