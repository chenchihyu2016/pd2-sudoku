struct Backtrack{
  int value;
  int x;
  int y;
  int rank;
};
class Sudoku{
public:
  Sudoku();
  ~Sudoku();
  void readIn();
  void solve();
  void changeNum( int number_a, int number_b );
  void changeRow( int a, int b );
  void changeCol( int a, int b );
  void flip( bool number );
  void rotate( int number );
  void transform();
  void giveQuestion();
  void print();
private:
  int** matrix;
  int** copy;
  bool exam();
  bool examMultiSol( int counter );
  bool row_col_exam();
  bool cell_exam();
  int count_zero();
  void findAllZero( Backtrack* Stack );
  void wash( Backtrack *Stack, int counter, int number );
  int assign_value( bool mutiple, Backtrack *Stack, int current_state );
  bool Safe( int posX, int posY, int value );
  bool row_col_safe( int posX, int posY, int value );
  bool cell_safe( int posX, int posY, int value );
  void swap( int* element_1, int* element_2 );
  bool solve_sub( bool multiple, Backtrack* Stack, int counter );
  void reset_the_sudoku( Backtrack* Stack, int counter );
  void copyFunc();
  bool NotTheSame();
  int countRank( int posX, int posY );
  void sortStack( Backtrack* Stack, int p, int r );
  int partition( Backtrack* Stack, int p, int r );
  void swapFunc( Backtrack* element_A, Backtrack* element_B );
};
