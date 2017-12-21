import math
from math import sqrt
import numbers

def zeroes(height, width):
        """
        Creates a matrix of zeroes.
        """
        g = [[0.0 for _ in range(width)] for __ in range(height)]
        return Matrix(g)

def identity(n):
        """
        Creates a n x n identity matrix.
        """
        I = zeroes(n, n)
        for i in range(n):
            I.g[i][i] = 1.0
        return I

class Matrix(object):
    """
    Math matrix class

    Attributes:
        g: The data grid
        h: The matrix height
        w: The matrix width

    Important note:
    Determinant and inversion only supported up to a size of 2x2.
    """
    # Constructor
    def __init__(self, grid):
        self.g = grid
        self.h = len(grid)
        self.w = len(grid[0])

    #
    # Primary matrix math methods
    #############################

    def determinant(self):
        """
        Calculates the determinant of a 1x1 or 2x2 matrix.
        """
        if not self.is_square():
            raise (ValueError, "Cannot calculate determinant of non-square matrix.")
        if self.h > 2:
            raise (NotImplementedError, "Calculating determinant not implemented for matrices larger than 2x2.")

        # 1x1 matrix
        if self.h == 1:
            return self.g[0][0]

        # 2x2 matrix
        if self.h == 2:
            a = self.g[0][0]
            b = self.g[0][1]
            c = self.g[1][0]
            d = self.g[1][1]
            return a*d - b*c

        # Fallback
        return None

    def trace(self):
        """
        Calculates the trace of a matrix (sum of diagonal entries).
        """
        if not self.is_square():
            raise (ValueError, "Cannot calculate the trace of a non-square matrix.")

        result = 0.0

        # sum main diagonal
        for i in range(self.h):
            result += self[i][i]

        return result

    def inverse(self):
        """
        Calculates the inverse of a 1x1 or 2x2 Matrix.
        """
        if not self.is_square():
            raise (ValueError, "Non-square Matrix does not have an inverse.")
        if self.h > 2:
            raise (NotImplementedError, "inversion not implemented for matrices larger than 2x2.")

        det = self.determinant()

        # Prevent division by zero, inversion not possible if determinant is zero
        if det == 0.:
            raise ValueError('The matrix has no inverse')

        # 1x1 matrix
        if self.h == 1:
            inverse = [[1 / det]]

        # 2x2 matrix
        if self.h == 2:
            a = self.g[0][0]
            b = self.g[0][1]
            c = self.g[1][0]
            d = self.g[1][1]

            scaler = 1.0 / det

            inverse = [[d * scaler, -b * scaler], [-c * scaler, a * scaler]]

        return Matrix(inverse)

    def T(self):
        """
        Returns a transposed copy of this Matrix.
        """

        matrix_transpose = []

        new_col_count = self.h
        new_row_count = self.w

        for i in range(new_row_count):
            new_row = []

            for j in range(new_col_count):
                new_row.append(self.g[j][i])

            matrix_transpose.append(new_row)

        return Matrix(matrix_transpose)

    def is_square(self):
        """
        Returns if width matches height
        :return: True if the matrix is square
        """
        return self.h == self.w

    #
    # Begin Operator Overloading
    ############################
    def __getitem__(self, idx):
        """
        Defines the behavior of using square brackets [] on instances
        of this class.

        Example:

        > my_matrix = Matrix([ [1, 2], [3, 4] ])
        > my_matrix[0]
          [1, 2]

        > my_matrix[0][0]
          1
        """
        return self.g[idx]

    def __repr__(self):
        """
        Defines the behavior of calling print on an instance of this class.
        """
        s = ""
        for row in self.g:
            s += " ".join(["{} ".format(x) for x in row])
            s += "\n"
        return s

    def __add__(self, other):
        """
        Defines the behavior of the + operator

        other: The matrix to be added
        """
        if self.h != other.h or self.w != other.w:
            raise (ValueError, "Matrices can only be added if the dimensions are the same")

        result = []

        for row_a, row_b in zip(self.g, other.g):
            new_row = []
            for col_a, col_b in zip(row_a, row_b):
                new_row.append(col_a + col_b)
            result.append(new_row)

        return Matrix(result)

    def __neg__(self):
        """
        Defines the behavior of - operator (NOT subtraction)

        Example:

        > my_matrix = Matrix([ [1, 2], [3, 4] ])
        > negative  = -my_matrix
        > print(negative)
          -1.0  -2.0
          -3.0  -4.0
        """

        result = []

        for row in self.g:
            new_row = []
            for col in row:
                new_row.append(-col)
            result.append(new_row)

        return Matrix(result)

    def __sub__(self, other):
        """
        Defines the behavior of - operator (as subtraction)

        other: The matrix to be subtracted
        """
        result = []
        if self.h != other.h or self.w != other.w:
            raise (ValueError, "Matrices can only be subtracted if the dimensions are the same")

        for row_a, row_b in zip(self.g, other.g):
            new_row = []
            for col_a, col_b in zip(row_a, row_b):
                new_row.append(col_a - col_b)
            result.append(new_row)

        return Matrix(result)

    def __mul__(self, other):
        """
        Defines the behavior of * operator (matrix multiplication)

        other: The matrix to be multiplied with.
        """
        product = []

        transp_b = other.T()

        if self.w != other.h:   # Verify 1:1 relation of own column count vs other's row count
            raise (ValueError, "Matrices can only be multiplied if the own row count matches the other's column count")

        for row_index in range(self.h):
            new_row = []

            for col_index in range(transp_b.h):
                # calculate dot product of both given vectors
                result = 0.
                for a, b in zip(self.g[row_index], transp_b.g[col_index]):
                    result += a * b

                new_row.append(result)

            product.append(new_row)

        return Matrix(product)

    def __rmul__(self, other):
        """
        Called when the thing on the left of the * is not a matrix.

        Example:

        > identity = Matrix([ [1,0], [0,1] ])
        > doubled  = 2 * identity
        > print(doubled)
          2.0  0.0
          0.0  2.0
        """
        if isinstance(other, numbers.Number):
            result = []
            for row in self.g:
                new_row = []
                for col in row:
                    new_row.append(col*other)
                result.append(new_row)
            return Matrix(result)
            