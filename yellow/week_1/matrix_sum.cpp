#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

// Реализуйте здесь
// * класс Matrix
class Matrix {
private:
  int rows, columns;
  std::vector<std::vector<int>> matrix;

public:
  Matrix() : rows(0), columns(0) {}

  Matrix(int num_rows, int num_cols) : rows(num_rows), columns(num_cols) {
    if (num_rows < 0 || num_cols < 0) {
      throw std::out_of_range("index out of range");
    }
    matrix.reserve(rows);
    for (int i = 0; i < rows; ++i) {
      std::vector<int> v(columns, 0);
      matrix.push_back(v);
    }
  }

  ~Matrix() {
    for (int i = 0; i < rows; ++i) {
      matrix[i].clear();
    }
    matrix.clear();
  }

  void Reset(int num_rows, int num_cols) {
    if (num_rows < 0 || num_cols < 0) {
      throw std::out_of_range("index out of range");
    }
    Matrix m(rows, columns);
    this->swap(m);
  }

  int At(int row, int collumn) const {
    if ((row < 0 || row > matrix.size()) ||
        (collumn < 0 || collumn > matrix[rows - 1].size())) {
      throw std::out_of_range("index out of range");
    }
    return matrix[row][collumn];
  }

  int &At(int row, int collumn) {
    if ((row < 0 || row > matrix.size()) ||
        (collumn < 0 || collumn > matrix[rows - 1].size())) {
      throw std::out_of_range("index out of range");
    }
    return matrix[row][collumn];
  }

  int GetNumRows() const { return rows; }

  int GetNumColumns() const { return columns; }

  std::vector<int> &operator[](int index) { return matrix[index]; }

  void swap(Matrix &other) {
    std::swap(matrix, other.matrix);
    std::swap(rows, other.rows);
    std::swap(columns, other.columns);
  }
};

// * оператор ввода для класса Matrix из потока istream
std::istream &operator>>(std::istream &stream, Matrix &m) {
  int rows, columns;
  stream >> rows >> columns;
  Matrix matrix(rows, columns);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      int val = 0;
      stream >> val;
      matrix[i][j] = val;
    }
  }
  m.swap(matrix);
  return stream;
}
// * оператор вывода класса Matrix в поток ostream
std::ostream &operator<<(std::ostream &stream, const Matrix &m) {
  stream << m.GetNumRows() << ' ' << m.GetNumColumns() << '\n';
  for (int i = 0; i < m.GetNumRows(); ++i) {
    for (int j = 0; j < m.GetNumColumns(); ++j) {
      stream << m.At(i, j) << ' ';
    }
    stream << '\n';
  }
  return stream;
}
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix

int main() {
  Matrix one;
  // Matrix two;

  std::cin >> one /*>> two*/;
  std::cout << one;
  // cout << one + two << endl;
  return 0;
}
