
// Field = <F, T, xor, and>
// Field = <0, 1, ^, &> $$> x ^ x = 0

// Ring = Fild x Field x ... x Field $$> <x1, x2, ..., xK> XOR <x1, x2, ..., xK> = <0, 0, ..., 0>
// U(Ring) = {0, 1}^64
// <0, 1> * <1, 0> = <0, 0>

// V xor V = False

unsigned int missing(unsigned int arr[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum = sum ^ arr[i];
        sum = sum ^ i;
    }
    sum = sum ^ n;
    return sum;
}

// T(n) = Theta(n)
// M(n) = Theta(1)