import numpy as np

var = 16

a = np.array([[3e+00, 2e+00, 1e+00], [1e+00, 6e+00, 2e+00],
              [5e+00, 2e+00, 3e+00], [4e+00, 2e+00, 1e+00]])
b = np.array([21, 2.2e+01, 2.3e+01, 21])


def main():
    u, sigma, v_t = np.linalg.svd(a, full_matrices=False)
    print(f'Singular values σ:\n{np.diag(sigma)}')
    print(f'\nLeft-singular vectors:\n{u}')
    print(f'\nRight-singular vectors:\n{v_t}')

    print(f'\nVerification of Decomposition:{u.dot(np.diag(sigma)).dot(v_t)}')

    matrix_rank = np.linalg.matrix_rank(a)
    print(f'Matrix rank: {matrix_rank}')
    # LEAST-SQUARES SOLUTION FOR SYSTEMS WITH FULL-RANK MATRIX
    if matrix_rank == (max(a.shape)):
        print(f"Given matrix is full-rank matrix. Matrix rank is equal to min{a.shape}")
        x = np.linalg.matrix_power(a.conj().T.dot(a), -1).dot(a.conj().T.dot(b))
        print(f'\nLeast-squares solution x: {x}')

        # Error of solution ||b-A*x||
        eps = np.linalg.norm(b - a.dot(x))
        print('\nError of the least-squares solution: ||b-A*x|| =', eps)
    else:
        # LEAST-SQUARES SOLUTION FOR SYSTEMS WITH MATRIX OF ANY RANK
        n = a.shape[1]
        sigma_inv = np.diag(np.hstack([1 / sigma[:matrix_rank], np.zeros(n - matrix_rank)]))
        A_plus = v_t.conj().T.dot(sigma_inv).dot(u.conj().T)
        print('\nMoore–Penrose pseudoinverse of A:')
        print(A_plus)

        # Least-squares solution
        x = A_plus.dot(b)
        print(f'\nLeast-squares solution x: {x}')

        # Error of solution ||b-A*x||
        eps = np.linalg.norm(b - a.dot(x))
        print('\nError of the least-squares solution: ||b-A*x|| =', eps)


main()

