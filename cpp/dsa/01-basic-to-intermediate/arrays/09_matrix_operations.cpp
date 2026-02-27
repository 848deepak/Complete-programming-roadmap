// ============================================================
// DSA | C++ → Arrays: 2D Arrays & Matrix Operations
// ============================================================
// DESCRIPTION:
//   Matrix (2D array) operations used in interviews and competitive
//   programming: traversal, transpose, rotation, spiral order,
//   search in row-column sorted matrix, matrix multiplication.
//
// COMPILE & RUN:
//   g++ -std=c++17 09_matrix_operations.cpp -o out && ./out
//
// SAMPLE OUTPUT:
//   Original matrix:
//   1  2  3
//   4  5  6
//   7  8  9
//   Transpose:
//   1  4  7
//   ...
// ============================================================

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

using Matrix = vector<vector<int>>;

// ============================================================
// HELPER: Print matrix
// ============================================================
void printMatrix(const string& label, const Matrix& m) {
    cout << label << ":\n";
    for (const auto& row : m) {
        for (int i = 0; i < (int)row.size(); i++)
            cout << setw(4) << row[i];
        cout << "\n";
    }
    cout << "\n";
}

// ============================================================
// SECTION 1: TRANSPOSE
// ============================================================
// Transppose: swap element at [i][j] with [j][i].
// Only works for square matrices in-place; use new matrix for non-square.
//
// Time: O(n²)  |  Space: O(1) for in-place square
// ------------------------------------------------------------ 

/**
 * Transposes an n×n matrix in-place.
 * Element A[i][j] swaps with A[j][i].
 */
void transposeInPlace(Matrix& m) {
    int n = (int)m.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {   // only upper triangle
            swap(m[i][j], m[j][i]);
        }
    }
}

/**
 * Transposes any r×c matrix into a c×r matrix (new allocation).
 */
Matrix transposeNew(const Matrix& m) {
    int r = (int)m.size(), c = (int)m[0].size();
    Matrix result(c, vector<int>(r));
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            result[j][i] = m[i][j];
    return result;
}

// ============================================================
// SECTION 2: ROTATE MATRIX 90° CLOCKWISE
// ============================================================
// Method: Transpose → then reverse each row.
// Rotating 90° anti-clockwise: reverse each row → transpose.
//
// Time: O(n²)  |  Space: O(1) in-place
// ------------------------------------------------------------ 

/**
 * Rotates n×n matrix 90° clockwise in-place.
 * Step 1: Transpose
 * Step 2: Reverse each row
 */
void rotate90Clockwise(Matrix& m) {
    // Step 1: Transpose
    transposeInPlace(m);

    // Step 2: Reverse each row
    for (auto& row : m)
        reverse(row.begin(), row.end());
}

// ============================================================
// SECTION 3: SPIRAL ORDER TRAVERSAL
// ============================================================
// Traverse the matrix in spiral fashion:
// right → down → left → up, shrinking boundaries each cycle.
//
// Time: O(m×n) — visits every element once
// Space: O(1) extra (excluding output)
// ------------------------------------------------------------ 

/**
 * Returns all elements of matrix m in spiral order.
 */
vector<int> spiralOrder(const Matrix& m) {
    vector<int> result;
    if (m.empty()) return result;

    int top    = 0,          bottom = (int)m.size() - 1;
    int left_  = 0,          right  = (int)m[0].size() - 1;

    while (top <= bottom && left_ <= right) {
        // Traverse right across top row
        for (int j = left_; j <= right; j++) result.push_back(m[top][j]);
        top++;

        // Traverse down right column
        for (int i = top; i <= bottom; i++) result.push_back(m[i][right]);
        right--;

        // Traverse left across bottom row (if still valid)
        if (top <= bottom) {
            for (int j = right; j >= left_; j--) result.push_back(m[bottom][j]);
            bottom--;
        }

        // Traverse up left column (if still valid)
        if (left_ <= right) {
            for (int i = bottom; i >= top; i--) result.push_back(m[i][left_]);
            left_++;
        }
    }

    return result;
}

// ============================================================
// SECTION 4: SEARCH IN ROW-COLUMN SORTED MATRIX
// ============================================================
// Every row is sorted left to right.
// Every column is sorted top to bottom.
//
// Strategy: Start at top-right corner.
//   - target == element → found!
//   - target  < element → eliminate this column (go left)
//   - target  > element → eliminate this row (go down)
//
// Time: O(m + n)  |  Space: O(1)
// ------------------------------------------------------------ 

/**
 * Searches for target in a row-column sorted matrix.
 * Returns {row, col} if found, {-1, -1} otherwise.
 */
pair<int,int> searchSortedMatrix(const Matrix& m, int target) {
    if (m.empty()) return {-1, -1};
    int row = 0, col = (int)m[0].size() - 1;   // start top-right

    while (row < (int)m.size() && col >= 0) {
        if      (m[row][col] == target) return {row, col};
        else if (m[row][col]  > target) col--;    // eliminate column
        else                            row++;    // eliminate row
    }

    return {-1, -1};
}

// ============================================================
// SECTION 5: MATRIX MULTIPLICATION
// ============================================================
// A(m×k) × B(k×n) = C(m×n)
// C[i][j] = sum of A[i][...] · B[...][j]
//
// Time: O(m × k × n)  |  Space: O(m × n) for result
// ------------------------------------------------------------ 

/**
 * Multiplies matrices A (r1×c1) and B (r2×c2).
 * Requires c1 == r2.
 */
Matrix multiply(const Matrix& A, const Matrix& B) {
    int r1 = (int)A.size(), c1 = (int)A[0].size();
    int r2 = (int)B.size(), c2 = (int)B[0].size();

    if (c1 != r2) throw invalid_argument("Incompatible matrix dimensions");

    Matrix C(r1, vector<int>(c2, 0));

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                C[i][j] += A[i][k] * B[k][j];  // dot product of row i and col j
            }
        }
    }

    return C;
}

// ============================================================
// SECTION 6: SET MATRIX ZEROES
// ============================================================
// If element m[i][j] == 0, set its entire row AND column to 0.
// Efficient approach: use first row/col as markers.
//
// Time: O(m×n)  |  Space: O(1) in-place (with first row/col trick)
// ------------------------------------------------------------ 

void setZeroes(Matrix& m) {
    if (m.empty()) return;
    int rows = (int)m.size(), cols = (int)m[0].size();

    bool firstRowHasZero = false, firstColHasZero = false;

    // Check if first row/col have a zero
    for (int j = 0; j < cols; j++) if (m[0][j] == 0) firstRowHasZero = true;
    for (int i = 0; i < rows; i++) if (m[i][0] == 0) firstColHasZero = true;

    // Use first row and col as markers
    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < cols; j++) {
            if (m[i][j] == 0) {
                m[i][0] = 0;   // mark row i
                m[0][j] = 0;   // mark col j
            }
        }
    }

    // Zero out marked rows and columns
    for (int i = 1; i < rows; i++)
        if (m[i][0] == 0)
            for (int j = 1; j < cols; j++) m[i][j] = 0;

    for (int j = 1; j < cols; j++)
        if (m[0][j] == 0)
            for (int i = 1; i < rows; i++) m[i][j] = 0;

    // Zero first row and col if originally needed
    if (firstRowHasZero) for (int j = 0; j < cols; j++) m[0][j] = 0;
    if (firstColHasZero) for (int i = 0; i < rows; i++) m[i][0] = 0;
}

// ============================================================
// MAIN
// ============================================================
int main() {

    // --- Transpose ---
    cout << "=== TRANSPOSE ===" << "\n";
    Matrix m1 = {{1,2,3},{4,5,6},{7,8,9}};
    printMatrix("Original", m1);
    transposeInPlace(m1);
    printMatrix("Transposed (in-place)", m1);

    Matrix rect = {{1,2,3,4},{5,6,7,8}};   // 2×4
    printMatrix("Original 2x4", rect);
    auto tRect = transposeNew(rect);
    printMatrix("Transposed to 4x2", tRect);

    // --- Rotate 90° Clockwise ---
    cout << "=== ROTATE 90° CLOCKWISE ===" << "\n";
    Matrix m2 = {{1,2,3},{4,5,6},{7,8,9}};
    printMatrix("Before rotation", m2);
    rotate90Clockwise(m2);
    printMatrix("After 90° CW rotation", m2);

    // --- Spiral Order ---
    cout << "=== SPIRAL ORDER TRAVERSAL ===" << "\n";
    Matrix m3 = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    printMatrix("Matrix 3x4", m3);
    auto spiral = spiralOrder(m3);
    cout << "Spiral: [";
    for (int i = 0; i < (int)spiral.size(); i++)
        cout << spiral[i] << (i+1<(int)spiral.size()?",":"");
    cout << "]\n\n";

    // --- Search in sorted matrix ---
    cout << "=== SEARCH IN ROW-COLUMN SORTED MATRIX ===" << "\n";
    Matrix sorted = {
        { 1,  4,  7, 11},
        { 2,  5,  8, 12},
        { 3,  6,  9, 16},
        {10, 13, 14, 17}
    };
    printMatrix("Sorted matrix", sorted);
    for (int target : {5, 20, 14}) {
        auto [r, c] = searchSortedMatrix(sorted, target);
        if (r != -1)
            cout << "search(" << target << "): found at [" << r << "][" << c << "]\n";
        else
            cout << "search(" << target << "): not found\n";
    }

    // --- Matrix Multiplication ---
    cout << "\n=== MATRIX MULTIPLICATION ===" << "\n";
    Matrix A = {{1,2},{3,4}};
    Matrix B = {{5,6},{7,8}};
    printMatrix("A", A);
    printMatrix("B", B);
    printMatrix("A × B", multiply(A, B));

    // --- Set Matrix Zeroes ---
    cout << "=== SET MATRIX ZEROES ===" << "\n";
    Matrix mz = {{1,1,1},{1,0,1},{1,1,1}};
    printMatrix("Before", mz);
    setZeroes(mz);
    printMatrix("After setZeroes", mz);

    return 0;
}

// ============================================================
// COMPLEXITY SUMMARY
//   Transpose         : O(n²) time, O(1) extra (in-place)
//   Rotate 90° CW     : O(n²) time, O(1) extra
//   Spiral traversal  : O(m×n) time, O(1) extra
//   Search sorted     : O(m+n) time, O(1) space
//   Matrix multiply   : O(m×k×n) time, O(m×n) space
//   Set zeroes        : O(m×n) time, O(1) space
// ============================================================
