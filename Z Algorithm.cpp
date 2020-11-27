/**
 * The Z array of a string S[0..n-1] gives for each suffix S[i..n-1],
 * 0<=i<=n-1, the length of the longest common prefix with S. Example:
 *
 *    i  |  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
 *  -----+---------------------------------------------------
 *  S[i] |  a  a  a  b  a  a  b  b  a  a  a  b  a  a  a  a  b
 *  Z[i] | 17  2  1  0  2  1  0  0  6  2  1  0  3  4  2  1  0
 *
 * The Z algorithm computes the Z array in linear time, which has many
 * applications in string matching. For example, we can find all matches
 * of a pattern P[0..m-1] in a text T[0..n-1] in O(m+n) time by building
 * the Z array for S=P$T, where $ is a special character that does not
 * occur in P or T. Then Z values equal to m correspond to matches of P
 * in T. Furthermore, the good suffix preprocessing of Boyer-Moore is
 * notoriously difficult to implement in linear time, but the problem
 * becomes trivial using the Z algorithm for the reverse pattern S=P^r.
 */

/**
 * "Classical" Z algorithm based on Gusfield's book "Algorithms on
 * Strings, Trees and Sequences" (1997) is shown below. Basically, the
 * algorithm consists of three cases that are handled independently of
 * each other in the outermost loop (Remark: Gusfield defines 'r' as the
 * position of the rightmost character in the Z-box; in the code below,
 * 'r' points to the next position so that 'r-l' gives the length of the
 * Z-box, which simplifies the code considerably).
 */
void Z1(const char *S, int n, int *Z) {
    int i, l, r;
    Z[0] = n;
    l = r = 0;
    for (i = 1; i < n; i++) {
        if (i >= r) {
            l = r = i;
            while (r < n && S[r-l] == S[r]) r++;
            Z[i] = r-l;
        } else {
            if (Z[i-l] < r-i) {
                Z[i] = Z[i-l];
            } else {
                l = i;
                while (r < n && S[r-l] == S[r]) r++;
                Z[i] = r-l;
            }
        }
    }
}

/**
 * In my opinion, it is unfortunate that the Z algorithm is almost
 * always taught using Gusfield's description of the algorithm, which is
 * overly complicated and error-prone to implement in practice. Although
 * there exist elegant algorithms to compute the Z array in O(n) time,
 * these are not widely known in the literature or the Internet. Hence,
 * let us describe some of the better algorithms.
 */

 /**
 * Here is a significantly simpler algorithm to build the Z array. The
 * origin of the algorithm is unknown, but a similar version has been
 * presented in: https://e-maxx-eng.github.io/string/z-function.html
 */
#define MAX(a,b) ((a) < (b) ? (b) : (a))
#define MIN(a,b) ((a) > (b) ? (b) : (a))
void Z2(const char *S, int n, int *Z) {
    int i, l = 0, r = 0;
    Z[0] = n;
    for(i = 1; i < n; i++) {
        Z[i] = MAX(0, MIN(Z[i - l], r - i));
        while (i + Z[i] < n && S[Z[i]] == S[i + Z[i]]) Z[i]++;
        if (i + Z[i] > r) l = i, r = i + Z[i];
    }
}

/**
 * As a premature optimizer, I did not like the way the previous method
 * used the MAX/MIN macros, nor the way it used the intermediate results
 * in the Z array to index the input string S. Thus, my version of the Z
 * algorithm with these unnecessary "improvements" is given below.
 */
void Z3(const char *S, int n, int *Z) {
    int k, l, r;
    Z[0] = n;
    for (l = r = 1; l < n; r += (l > r)) {
        while (r < n && S[r-l] == S[r]) r++;
        Z[l] = r-l;
        for (k = l++; Z[l-k] < r-l; l++) Z[l] = Z[l-k];
    }
}

/**
 * Finally, a specialized algorithm for '\0'-terminated strings.
 */
void Z4(const char *S, int *Z) {
    int k, l, r;
    for (l = r = 1; S[l]; r += (l > r)) {
        while (S[r-l] == S[r]) r++;
        Z[l] = r-l;
        for (k = l++; Z[l-k] < r-l; l++) Z[l] = Z[l-k];
    }
    Z[0] = l;
}
int main(){

}
